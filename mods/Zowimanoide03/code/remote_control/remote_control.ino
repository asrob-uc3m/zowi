//Zowimanoide03 Remote control

#include <Arduino.h>
#include <Servo.h>
#include <Oscillator.h>

#define N_OSC 8

#define TRIM_RR -2    //Leg Roll Right
#define TRIM_RL 5     //Leg Roll Left
#define TRIM_YR 0     //Leg Yaw Right
#define TRIM_YL -5     //Leg Yaw Left
#define TRIM_SR 62      //Shoulder Right
#define TRIM_SL -72 //-68      //Shoulder Left
#define TRIM_AR -38     //Arm Right
#define TRIM_AL 42//35    //Arm Left
#define TRIM_H 84      //Head

#define PIN_RR 10
#define PIN_RL 9
#define PIN_YR 11
#define PIN_YL 8
#define PIN_SR 12
#define PIN_SL 6
#define PIN_AR 13
#define PIN_AL 7
#define PIN_H 5
/**/#define PIN_RESET A0

Oscillator osc[N_OSC];

void run(unsigned char steps=1, short T=500);
void forward(unsigned char steps=1, short T=1000);
void backward(unsigned char steps=1, short T=1000);
void turnLfwd(unsigned char steps=1, short T=1000);
void turnRfwd(unsigned char steps=1, short T=1000);
void moonWalkL(unsigned char steps=1, short T=1000);
void moonWalkR(unsigned char steps=1, short T=1000);
void upDown(unsigned char steps=1, short T=700);
void home();
void frontattack();
void sidePunchL();
void sidePunchR();
void helmet();

void setup(){
/**/  digitalWrite(PIN_RESET, HIGH);

/**/  Serial.begin(57600);

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
  
  upDown();
  home();
  //slideR(2,1500);
  //slideL(2,1500);
  //forward(6, 1000);
  home();

}

unsigned char input, lastinput;

void loop()
{  
    if(Serial.available())
    {
        while (Serial.available()) input = Serial.read();
        //Serial.println(input);
        switch(input){
/**/        case ' ': //init characters for ATMEGA328
///**/        case '0':
/**/            reset();
/**/            break;
          
            case 'A': //btnUp
                forward(1, 800);
                break;
  
            case 'B': //btnUpRight
                turnRfwd(1, 800);
                break;
  
            case 'C': //btnDown
                backward(1, 800);
                break;
  
            case 'D': //btnUpLeft
                turnLfwd(1, 800);
                break;
  
            case 'E': //btnX
                if(lastinput=='E')
                {
                  batman();
                  delay(350);
                  home();
                  delay(250);
                }
                else
                {
                  outofmyway();
                  delay(350);
                  home();
                }
                break;

            case 'F': //btnA
                if(lastinput=='F')
                {
                  sidePunchRwipe();
                  delay(350);
                  home();
                  delay(250);
                  break;
                }
                else
                {
                  sidePunchR();
                  delay(350);
                  home();
                  break;
                }
  
            case 'G': //btnB
                if(lastinput=='G')
                {
                  forward(1, 800);
                  break;
                }
                else
                {
                  frontattack();
                  delay(300);
                  home();
                  break;
                }
                  
            case 'H': //btnY
                if(lastinput=='H')
                {
                  sidePunchLwipe();
                  delay(350);
                  home();
                  delay(250);
                  break;
                }
                else
                {
                  sidePunchL();
                  delay(350);
                  home();
                  break;
                }
  
            case 'I': //btnSelect
                moonWalkL();
                break;
  
            case 'J': //btnStart
                moonWalkR();
                break;

            case 'a': //btnHome
                home();
                break;

            case 'b': //btnRight
                slideR(1,1500);
                break;
                
            case 'c': //btnDownRight
                turnRbwd(1, 800);
                break;
                
            case 'd': //btnLeft
                slideL(1,1500);
                break;
                
            case 'e': //btnDownLeft
                turnLbwd(1, 800);
                break;            

            case '1': //btn1
                sidePunchLwipe();
                delay(350);
                break;
  
            case '2': //btn2
               
                break;
                
            case '3': //btn3
                sidePunchRwipe();
                delay(350);
                break;
                
            case '4': //btn4
                turnLfwd(1, 800);
                turnRbwd(1, 800);
                break;
  
            case '5': //btn5
                upDown();
                break;
  
            case '6': //btn6
                turnRfwd(1, 800);
                turnLbwd(1, 800);
                break;
  
            case '7': //btn7
                break;
  
            case '8': //btn8
                batman();
                delay(350);
                home();
                break;
  
            case '9': //btn9
                break;
  
            default:
                home();
                break;
        }
        if(input==lastinput)
        {
          lastinput=0;
        }
        else
        {
          lastinput=input;
        }
    }
    else
    {
      home();
    }
}

/**/void reset()
/**/{
/**/  delay(100);
/**/  digitalWrite(PIN_RESET, LOW);
/**/  delay(3000);
/**/}


void oscillate(signed char A[N_OSC], signed char O[N_OSC], short T, float phase_diff[N_OSC]){
    for (short i=0; i<8; i++) {
        osc[i].SetO(O[i]);
        osc[i].SetA(A[i]);
        osc[i].SetT(T);
        osc[i].SetPh(phase_diff[i]);
    }
    unsigned long ref=millis();
    for (unsigned long x=ref; x<T+ref; x=millis()){
        for (short i=0; i<8; i++){
            osc[i].refresh();
        }
    }
}

void forward(unsigned char steps, short T){
    signed char A[8]= {20, 20, 25, 25, 30, 30, 25, 25};
    signed char O[8] = { -2, -1, 0, 0, -60, 60, -20, 20};//-- anda con el interior
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(unsigned char i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnLfwd(unsigned char steps, short T){
    signed char A[8]= {20, 20, 10, 30, 30, 30, 25, 25};
    signed char O[8] = {-2, -1, 0, 0, -60, 60, -20, 20};
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(unsigned char i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnLbwd(unsigned char steps, short T){
    signed char A[8]= {20, 20, 10, 30, 30, 30, 25, 25};
    signed char O[8] = {-2, -1, 0, 0, -100, 100, -20, 20};
    float phase_diff[8] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(180), DEG2RAD(180)};

    for(unsigned char i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnRfwd(unsigned char steps, short T){
    signed char A[8]= {20, 20, 30, 10, 30, 30, 25, 25};
    signed char O[8] = {-2, -1, 0, 0, -60, 60, -20, 20};
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(0), DEG2RAD(0)};

    for(unsigned char i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void turnRbwd(unsigned char steps, short T){
    signed char A[8]= {20, 20, 30, 10, 30, 30, 25, 25};
    signed char O[8] = {-2, -1, 0, 0, -100, 100, -20, 20};
    float phase_diff[8] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(180), DEG2RAD(180)};

    for(unsigned char i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void backward(unsigned char steps, short T){
    signed char A[8]= {20, 20, 25, 25, 30, 30, 25, 25};
    signed char O[8] = {-2, -1, 0, 0, -100, 100, -20, 20};
    float phase_diff[8] = {DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(270), DEG2RAD(270), DEG2RAD(180), DEG2RAD(180)};

    for(unsigned char i=0;i<steps;i++) oscillate(A,O, T, phase_diff);
}

void slideR(unsigned char steps, short T){
    signed char A[8]= {40, 40, 0, 0, 0, 0, 15, 15};
    signed char O[8] = {-15, 15, 0, 0, -80, 80, -30, 30}; //50/110
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)}; //270/180

    for(unsigned char i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void slideL(unsigned char steps, short T){
    signed char A[8]= {40, 40, 0, 0, 0, 0, 15, 15};
    signed char O[8] = {-15, 15, 0, 0, -80, 80, -30, 30};//50/110
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};//90/180


    for(unsigned char i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkR(unsigned char steps, short T){
    signed char A[8]= {25, 25, 0, 0, 0, 0, 20, 20};
    signed char O[8] = {-15, 15, 0, 0, -80, 80, 50, -50}; //50/110
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(180), DEG2RAD(180), DEG2RAD(90), DEG2RAD(90)}; //270/180

    for(unsigned char i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkL(unsigned char steps, short T){
    signed char A[8]= {25, 25, 0, 0, 0, 0, 20, 20};
    signed char O[8] = {-15, 15, 0, 0, -80, 80, 50, -50};//50/110
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90),
                            DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};//90/180


    for(unsigned char i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(unsigned char steps, short T){
    signed char A[8]= {25, 25, 0, 0, 0, 0, 35, 35};
    signed char O[8] = {-25, 25, 0, 0, -60, 60, 0, 0,};
    float phase_diff[8] = {DEG2RAD(0), DEG2RAD(180), 0, 0,
                            0, 0, DEG2RAD(0), DEG2RAD(180)};

    for(unsigned char i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
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

void frontattack(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(115);
    osc[5].SetPosition(65);
    osc[6].SetPosition(40);
    osc[7].SetPosition(140);
    delay(150);
    osc[0].SetPosition(45);
    osc[1].SetPosition(135);
}

void outofmyway(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(115);
    osc[5].SetPosition(65);
    osc[6].SetPosition(40);
    osc[7].SetPosition(140);
    delay(200);
    osc[6].SetPosition(120);
    osc[7].SetPosition(60);   
}

void batman(){
    osc[0].SetPosition(90);
    osc[1].SetPosition(90);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(85);
    osc[5].SetPosition(85);
    osc[6].SetPosition(120);
    osc[7].SetPosition(60); 
    delay(200);
    osc[6].SetPosition(240);
    osc[7].SetPosition(-60);  
}

void sidePunchL(){
    osc[0].SetPosition(40);
    osc[1].SetPosition(70);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(120);
    osc[7].SetPosition(10);
}

void sidePunchLwipe(){
    osc[0].SetPosition(40);
    osc[1].SetPosition(70);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(120);
    osc[7].SetPosition(10);
    delay(200);
    osc[5].SetPosition(105);
    osc[7].SetPosition(-60);
    delay(400);
    osc[5].SetPosition(65);
    osc[7].SetPosition(130);
}

void sidePunchR(){
    osc[0].SetPosition(110);
    osc[1].SetPosition(140);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(170);
    osc[7].SetPosition(60);
}


void sidePunchRwipe(){
    osc[0].SetPosition(110);
    osc[1].SetPosition(140);
    osc[2].SetPosition(90);
    osc[3].SetPosition(90);
    osc[4].SetPosition(10);
    osc[5].SetPosition(170);
    osc[6].SetPosition(170);
    osc[7].SetPosition(60);
    delay(200);
    osc[4].SetPosition(65);
    osc[6].SetPosition(240);
    delay(400);
    osc[4].SetPosition(105);
    osc[6].SetPosition(50);
}

void helmet(){
    home();
    osc[8].SetPosition(60);
    delay(1000);
    osc[8].SetPosition(90);
}
