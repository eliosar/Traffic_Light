#include "Lights.h"

TrafficLight::TrafficLight(PinName red, PinName yellow, PinName green):_redLight(red), _yellowLight(yellow), _greenLight(green){}

PedestrianLight::PedestrianLight(PinName red, PinName green):_redLight(red), _greenLight(green){}