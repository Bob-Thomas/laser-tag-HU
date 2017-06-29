//
// Created by robbie on 29-6-2017.
//

#ifndef LASER_irRECEIVECONTROLLER_HPP
#define LASER_irRECEIVECONTROLLER_HPP

#include "./rtos.hpp"
#include "../applicationLogic/command.hpp"
#include "../stateController/controller.hpp"

class IrReceiveController : public rtos::task<> {
private:
    int on = 0;
    int off = 0;
    short firstReceivedByte = 0;
    short receivedByte = 0;
    int bitIndex = 0;
    const int pullTimeUs = 4;
    const int msBetweenSignal = 3;
    bool isSecondListen = false;
    hwlib::target::pin_in &ir;
    Controller *controllers[3];
    int amountListeners = 0;
    bool foundSignal = false;
    bool signal;
public:
    IrReceiveController(hwlib::target::pin_in &ir);
    void addListener(Controller *c);
    void main();
};


#endif //LASER_irRECEIVECONTROLLER_HPP
