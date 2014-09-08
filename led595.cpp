/*
 * Led595
 *
 * Uses a 74HC595 shift register to print text on a 7seg display
 *
 * 2014 rccursach
 * rccursach.blogspot.com
 */

#include "led595.h"
#include "TimerOne.h"
#include <avr/pgmspace.h>


Led595::Led595(int* digitPins, int dp_size, int clock, int latch, int data){

  digitsCount = dp_size;
  dp = (int*)malloc(sizeof(int)*dp_size);
  memcpy(dp, digitPins, sizeof(int)*dp_size);
  
  cl = clock;
  la = latch;
  da = data;
  
  rotate = false;
  
  text = (char*)malloc(sizeof(char)*17);
  
  //Common cathode config
  led_on = LOW;
  led_off = HIGH;
  
  //start defining fonts
  //initFonts();
  
  //set pinmode
  for(int i = 0; i < digitsCount; i++){
    pinMode(dp[i],OUTPUT);
  }
  pinMode(cl, OUTPUT);
  pinMode(la, OUTPUT);
  pinMode(da, OUTPUT);
  
  Serial.begin(9600);
}

void Led595::start(void(*fun)()){
  //Timed refresh
  Timer1.initialize(26000);
  Timer1.attachInterrupt(fun);
}
  
Led595::~Led595(){
  //
}
  
void Led595::printString(char* str){
  
  //lock refreshInterrupt calls
  lockDisplay = true;
  
  int size = strlen(str);
  if(size > 16){size = 16;}
  strncpy(text,str,size+1);
  
  Serial.println(text);
  
  for(int i=0; i<digitsCount; i++){
    Serial.print(dp[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  //now refreshInterrupt() can be called safely:
  lockDisplay = false;
}

void Led595::rotateText(boolean rotate){
}

void Led595::refreshInterrupt(){
  //if display is locked skip this call
  if(lockDisplay){
    return;
  }
  //else update screen data
  
  Timer1.stop();
  //For each char of the string
  for(int i=0; i<strlen(text); i++){

    //if not rotating text
    if( i > digitsCount-1 || text[i] == '\0'){
      break;
    }
    
    //search font
    int chr_index = text[i];
    byte data;
    if(chr_index >= 0  && chr_index <= 127){
      data = pgm_read_byte_near(fonts + chr_index);
    }
    else{
      data = pgm_read_byte_near(fonts + 16);
    }
    
    //Turn on led
    digitalWrite(dp[i], led_on);

    //Shift out data
    shiftOut(da, cl, LSBFIRST, data);
    digitalWrite(la, HIGH);
    digitalWrite(la, LOW);
    delay(9);
    //clear display
    for(byte j=0; j<digitsCount; j++) {digitalWrite(dp[j], led_off);}
  }
  Timer1.resume();
}


