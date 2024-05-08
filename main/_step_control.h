#ifndef _STEP_CONTROL_H
#define _STEP_CONTROL_H

#include "config.h"
#include "_led_control.h"

int step = 0;
int stepDelayShort = 350;
int stepDelay = 1200;
int a = 0;

// button state
int M2T_bs = 0;
int B2T_bs = 0;

void initialize_steppers(){
  pinMode(STEP_DIR, OUTPUT);
  pinMode(STEP_STEP, OUTPUT);
  pinMode(STEP_EN, OUTPUT);
  digitalWrite(STEP_EN, LOW);
  pinMode(STEP_DIR_TOP, OUTPUT);
  pinMode(STEP_STEP_TOP, OUTPUT);
  pinMode(STEP_EN_TOP, OUTPUT);
  digitalWrite(STEP_EN_TOP, LOW);
  pinMode(STEP_DIR_BOT, OUTPUT);
  pinMode(STEP_STEP_BOT, OUTPUT);
  pinMode(STEP_EN_BOT, OUTPUT);
  digitalWrite(STEP_EN_BOT, LOW);
}

// push up the link
void spinUp(){
    digitalWrite(STEP_DIR, LOW);
    for(int i  = 0; i < upcount*STEPS_PER_REV; i++){
      digitalWrite(STEP_STEP, HIGH);
      delayMicroseconds(stepDelayShort);
      digitalWrite(STEP_STEP, LOW);
      delayMicroseconds(stepDelayShort);
    }
}

// let down the link
void spinDown(){
  digitalWrite(STEP_DIR, HIGH);
  for(int i  = 0; i < upcount*STEPS_PER_REV; i++){
    digitalWrite(STEP_STEP, HIGH);
    delayMicroseconds(stepDelayShort);
    digitalWrite(STEP_STEP, LOW);
    delayMicroseconds(stepDelayShort);
  }
}

// rotate top stepper once
void rotateTop(){
  digitalWrite(STEP_DIR_TOP, HIGH);
  for(int i  = 0; i < STEPS_PER_REV2; i++){
    digitalWrite(STEP_STEP_TOP, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEP_STEP_TOP, LOW);
    delayMicroseconds(stepDelay);
  }
}

// rotate bottom stepper once
void rotateBot(){
  digitalWrite(STEP_DIR_BOT, HIGH);
  for(int i  = 0; i < STEPS_PER_REV2; i++){
    digitalWrite(STEP_STEP_BOT, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEP_STEP_BOT, LOW);
    delayMicroseconds(stepDelay);
  }
}

void mid2top(){
  spinUp();
  delay(200);
  rotateTop();
  delay(200);
  spinDown();
  show_white(100);
}

void bot2top(){
  rotateBot();
  delay(200);
  mid2top();
  show_white(100);
}

#endif