#include "signal_bus.h"

SignalBus* SignalBus::instance = nullptr; 

SignalBus* SignalBus::getInstance()
{
    if(instance == nullptr){
        instance = new SignalBus(nullptr);
    }
    return instance;
}
