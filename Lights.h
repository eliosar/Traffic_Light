#include "mbed.h"
#include <cstdio>

class TrafficLight{
    public:
        DigitalOut _redLight;
        DigitalOut _yellowLight;
        DigitalOut _greenLight;

        TrafficLight(PinName red, PinName yellow, PinName green);
};

class PedestrianLight{
    public:
        DigitalOut _redLight;
        DigitalOut _greenLight;

        PedestrianLight(PinName red, PinName green);
};