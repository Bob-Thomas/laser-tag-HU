//
// Created by Rene on 29/06/2017.
//

#include "ir-controller.hpp"


IrController::IrController(hwlib::target::d2_36kHz & diode):
    diode(diode)
{}

void IrController::sendBit(bool b){
    diode.set(1);
    hwlib::wait_us(b ? 1600 : 800);
    diode.set(0);
    hwlib::wait_us(b ? 800 : 1600);
}

void IrController::send(uint16_t bits){
    for(int i = 0; i < 16; ++i){
        sendBit(((bits & (1 << i))& (1 << i)) < 1);
    }
}