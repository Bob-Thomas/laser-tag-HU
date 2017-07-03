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
    hwlib::target::pin_in &ir;
public:
    IrReceiveController(hwlib::target::pin_in &ir);
    void main();
    int16_t getBit(long long int start = 0);
    int getByte(int16_t bitStream = 0, int16_t i = 0);
};


#endif //LASER_irRECEIVECONTROLLER_HPP
