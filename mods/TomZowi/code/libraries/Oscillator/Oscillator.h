//--------------------------------------------------------------
//-- Oscillator.pde
//-- Generate sinusoidal oscillations in the servos
//--------------------------------------------------------------
//-- (c) Juan Gonzalez-Gomez (Obijuan), Dec 2011
//-- GPL license
//--------------------------------------------------------------
#ifndef Oscillator_h
#define Oscillator_h

#include <Servo.h>

//-- Macro for converting from degrees to radians
#ifndef DEG2RAD
  #define DEG2RAD(g) ((g)*M_PI)/180
#endif

class Oscillator
{
  public:
    Oscillator(short trim=0) {_trim=trim;};
    void attach(short pin, bool rev =false);
    void detach();
    
    void SetA(signed char A) {_A=(unsigned short)A;};
    void SetO(signed char O) {_O=(unsigned short)O;};
    void SetPh(float Ph) {_phase0=Ph;};
    void SetT(unsigned short T);
    void SetTrim(short trim){_trim=trim;};
    short getTrim() {return _trim;};
    void SetPosition(short position); 
    void Stop() {_stop=true;};
    void Play() {_stop=false;};
    void Reset() {_phase=0;};
    void refresh();
    
  private:
    bool next_sample();  
    
  private:
    //-- Servo that is attached to the oscillator
    Servo _servo;
    
    //-- Oscillators parameters
    unsigned short _A;  //-- Amplitude (degrees)
    unsigned short _O;  //-- Offset (degrees)
    unsigned short _T;  //-- Period (miliseconds)
    float _phase0;   //-- Phase (radians)
    
    //-- Internal variables
    short _pos;         //-- Current servo pos
    short _trim;        //-- Calibration offset
    float _phase;    //-- Current phase
    float _inc;      //-- Increment of phase
    float _N;        //-- Number of samples
    unsigned short _TS; //-- sampling period (ms)
    
    unsigned short _previousMillis; 
    unsigned short _currentMillis;
    
    //-- Oscillation mode. If true, the servo is stopped
    bool _stop;

    //-- Reverse mode
    bool _rev;
};

#endif
