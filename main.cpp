/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Variables.h"
#include "Lights.h"

TrafficLight car13(ARDUINO_UNO_D10, ARDUINO_UNO_D9, ARDUINO_UNO_D8);
TrafficLight car24(ARDUINO_UNO_D3, ARDUINO_UNO_D5, ARDUINO_UNO_D6);

PedestrianLight pedestrian13(ARDUINO_UNO_A1, ARDUINO_UNO_A0);
PedestrianLight pedestrian24(ARDUINO_UNO_A4, ARDUINO_UNO_A3);

DigitalIn button(ARDUINO_UNO_D2);

BufferedSerial serialMonitor(USBTX, USBRX);

void start(){
    currentSpeed = 0;
    car13._greenLight = 1;
    pedestrian24._greenLight = 1;
    car24._redLight = 1;
    pedestrian13._redLight = 1;
}

void wait(int sec){
    unsigned long currentMillis = 0;
  unsigned long wantedMillis = (sec * 1000) / currentSpeed;

  while(currentMillis <= wantedMillis){
    wantedMillis = (sec * 1000) / currentSpeed;
    ThisThread::sleep_for(50ms);
    currentMillis += 50;
    while(currentSpeed == 0){
        serialMonitor.write("freeze\n", 10);
    }
  }
}

void buttonWork(){
    while(true){
        if(button == 1){
            serialMonitor.write("pressed\n", 10);
            currentSpeed++;
            if(currentSpeed == 3){
                currentSpeed = 0;
            }

            ThisThread::sleep_for(500ms);
        }
    }
}

void changeTo24(){
    // Pedestrians24 RED
  pedestrian24._greenLight = 0;
  pedestrian24._redLight = 1;
  // Car13 YELLOW
  car13._greenLight = 0;
  car13._yellowLight = 1;
  // Car24 RED YELLOW
  car24._yellowLight = 1;
  // wait
  wait(waitForSecInChange);
  // Car24 GREEN
  car24._yellowLight = 0;
  car24._redLight = 0;
  car24._greenLight = 1;
  // Car13 RED
  car13._yellowLight = 0;
  car13._redLight = 1;
  // Pedestrian13 GREEN
  pedestrian13._redLight = 0;
  pedestrian13._greenLight = 1;
}

void changeTo13(){
    // Pedestrians13 RED
  pedestrian13._greenLight = 0;
  pedestrian13._redLight = 1;
  // Car24 YELLOW
  car24._greenLight = 0;
  car24._yellowLight = 1;
  // Car13 RED YELLOW
  car13._yellowLight = 1;
  // wait
  wait(waitForSecInChange);
  // Car13 GREEN
  car13._yellowLight = 0;
  car13._redLight = 0;
  car13._greenLight = 1;
  // Car24 RED
  car24._yellowLight = 0;
  car24._redLight = 1;
  // Pedestrian24 GREEN
  pedestrian24._redLight = 0;
  pedestrian24._greenLight = 1;
}

int main()
{
    start();

    Thread thread;
    thread.start(buttonWork);

    while (true) {
        wait(waitForSecEachRound);
        changeTo24();
        wait(waitForSecEachRound);
        changeTo13();
    }
}