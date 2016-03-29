#include <Arduino.h>
#include <Servo.h>
#include <Oscillator.h>

#define N_OSC 9

#define TRIM_RR -2    //Leg Roll Right
#define TRIM_RL 7     //Leg Roll Left
#define TRIM_YR 0     //Leg Yaw Right
#define TRIM_YL -5     //Leg Yaw Left
#define TRIM_SR 62      //Shoulder Right
#define TRIM_SL -68      //Shoulder Left
#define TRIM_AR -38     //Arm Right
#define TRIM_AL 30    //Arm Left
#define TRIM_H 84      //Head

#define PIN_RR 12
#define PIN_RL 11
#define PIN_YR 3
#define PIN_YL 2
#define PIN_SR 9
#define PIN_SL 5
#define PIN_AR 10
#define PIN_AL 4
#define PIN_H 6
/**/#define PIN_RESET A5

Oscillator osc[N_OSC];

void run(int steps=1, int T=500);
void walk(int steps=1, int T=1000);
void backward(int steps=1, int T=1000);
void turnL(int steps=1, int T=1000);
void turnR(int steps=1, int T=1000);
void moonWalkL(int steps=1, int T=1000);
void moonWalkR(int steps=1, int T=1000);
void upDown(int steps=1, int T=700);
void home();
void attack();
void punchL();
void punchR();
void helmet();

/**/char stateconnection=1;
/**/char newstateconnection=1;
/**/uint32_t countconnection=0;


void setup(){
/**/  digitalWrite(PIN_RESET, HIGH);

/**/  Serial.begin(19200);

/**/  pinMode(PIN_RESET, OUTPUT);

  osc[0].attach(PIN_RR);
  osc[1].attach(PIN_RL);
  osc[2].attach(PIN_YR);
  osc[3].attach(PIN_YL);
  osc[4].attach(PIN_SR);
  osc[5].attach(PIN_SL);
  osc[6].attach(PIN_AR);
  osc[7].attach(PIN_AL);
  //osc[8].attach(PIN_H);

  osc[0].SetTrim(TRIM_RR);
  osc[1].SetTrim(TRIM_RL);
  osc[2].SetTrim(TRIM_YR);
  osc[3].SetTrim(TRIM_YL);
  osc[4].SetTrim(TRIM_SR);
  osc[5].SetTrim(TRIM_SL);
  osc[6].SetTrim(TRIM_AR);
  osc[7].SetTrim(TRIM_AL);
  osc[8].SetTrim(TRIM_H);

  //ninuninu();
  home();
  upDown();
  

  helmet();
  //walk(6, 1000);

/**/  checkconnection();
}

/**/int inactivity=0;
char input;

void loop()
{ 
/**/checkconnection();
/**/if(stateconnection != newstateconnection)
/**/{
/**/  if(stateconnection == 0)
/**/  {
/**/    reset();
/**/  }
/**/  stateconnection = newstateconnection;
/**/}
  
  
  while(stateconnection==1)
  {
    if(Serial.available())
    {
        while (Serial.available()) input = Serial.read();
/**/    //Serial.print("Recibido: ");
        //Serial.println(input);
/**/    inactivity=0;
        switch(input){
            case 'A':
                walk(1, 750);
                break;
  
            case 'B':
                turnR(1, 800);
                break;
  
            case 'C':
                backward(1, 800);
                break;
  
            case 'D':
                turnL(1, 800);
                break;
  
            case 'E':
                upDown();
                break;
  
            case 'F':
                punchR();
                delay(350);
                home();
                delay(100);
                break;
  
            case 'G':
                attack();
                delay(350);
                home();
                delay(100);
                break;
  
            case 'H':
                punchL();
                delay(350);
                home();
                delay(100);
                break;
  
            case 'I':
                moonWalkL();
                break;
  
            case 'J':
                moonWalkR();
                break;
  
            default:
                home();
                break;
        }
    }
    else
    {
/**/      inactivity++;
/**/  //Serial.println(inactivity);
/**/  if(inactivity == 6000)
/**/  {       
/**/    inactivity=0;
/**/    //Serial.println("break");
/**/    break; 
/**/  }
      home();
    }
  }
}

/**/void reset()
/**/{
/**/  delay(100);
/**/  digitalWrite(PIN_RESET, LOW);
/**/  delay(3000);
/**/}

/**/void checkconnection()
/**/{
/**/  while (Serial.available())
/**/  {
/**/    Serial.read();
/**/  }
/**/  newstateconnection=1; //Default
/**/  Serial.print("AT");
/**/  Serial.flush();
/**/  countconnection=0;
/**/  while (Serial.available()<2 && countconnection <170000)
/**/  {
/**/    countconnection++;
/**/  }
/**/  if(Serial.available()==2)
/**/  {
/**/    if(Serial.read()== 'O')
/**/    {
/**/      if(Serial.read()== 'K')
/**/      {
/**/        newstateconnection=0;
/**/      }
/**/    }
/**/  }
/**/}

void oscillate(int A[N_OSC], int O[N_OSC], int T, double phase_diff[N_OSC]){
    for (int i=0; i<8; i++) {
        osc[i].SetO(O[i]);
        osc[i].SetA(A[i]);
        osc[i].SetT(T);
        osc[i].SetPh(phase_diff[i]);
    }
    double ref=millis();
    for (double x=ref; x<T+ref; x=millis()){
        for (int i=0; i<8; i++){
            osc[i].refresh();
        }
    }
}

void walk(int steps, int T){
    int A[8]= {15, 15, 25, 25, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnL(int steps, int T){
    int A[8]= {15, 15, 10, 30, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnR(int steps, int T){
    int A[8]= {15, 15, 30, 10, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void backward(int steps, int T){
    int A[8]= {15, 15, 25, 25, 20, 20, 15, 15};
    int O[8] = {0, 0, 0, 0, -60, 60, -30, 30};
    double phase_diff[8] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(90), DEG2RAD(90), DEG2RAD(0), DEG2RAD(0)};

    for(int i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void moonWalkR(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 20, 20};
    int O[8] = {-15, 15, 0, 0, -80, 80, 50, -50}; //50/110
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)}; //270/180

    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkL(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 20, 20};
    int O[8] = {-15, 15, 0, 0, -80, 80, 50, -50};//50/110
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};//90/180


    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[8]= {25, 25, 0, 0, 0, 0, 35, 35};
    int O[8] = {-25, 25, 0, 0, -60, 60, 0, 0,};
    double phase_diff[8] = {DEG2RAD(0), DEG2RAD(180), 0, 0,
                            0, 0, DEG2RAD(0), DEG2RAD(180)};

    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void home(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(50);
    osc[7].SetPosition(130);
    osc[8].SetPosition(90);
}

void attack(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(105);
    osc[5].SetPosition(75);
    osc[6].SetPosition(40);
    osc[7].SetPosition(140);
}

void punchL(){
    osc[0].SetPosition(40);
    osc[1].SetPosition(70);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(90);
    osc[7].SetPosition(30);
}

void punchR(){
    osc[0].SetPosition(110);
    osc[1].SetPosition(140);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(150);
    osc[7].SetPosition(90);
}

void helmet(){
    home();
    osc[8].SetPosition(60);
    delay(1000);
    osc[8].SetPosition(90);
}
