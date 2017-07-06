/**
 * \file      ir-receive-controller.hpp
 * \author    René de Kluis
 * \author    Robbie Valkenburg
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "ir-receive-controller.hpp"

IrReceiveController::IrReceiveController(hwlib::target::pin_in &ir, IController *controller):
        task("Receive"),
        ir(ir),
        controller(controller)
{}

void IrReceiveController::main() {
    for(;;) {
        if(!ir.get()) {
            auto signal = getData();
            hwlib::wait_ms(3);
            auto signal2 = getData();
            if (signal == signal2) {
                controller->getReceivedChannel()->write(Command(signal));
            }
        }
        hwlib::wait_us(400);
    }
}

uint8_t IrReceiveController::getBit(long long int start){
    if(start == 0){
        start = hwlib::now_us();
    }
    if(ir.get()){
        hwlib::wait_us(100);
        return (start - hwlib::now_us() >= 4000) ? uint8_t(2) : getBit(start);
    }
    hwlib::wait_us(1100);
    bool b = !ir.get();
    hwlib::wait_us(700);
    return b;
}

uint16_t IrReceiveController::getData(uint16_t bitStream, uint16_t i){
    if(i == 16){
        return bitStream;
    }
    auto bit = getBit();
    if(bit != 2) {
        bitStream = bitStream | (bit << i);
        return getData(bitStream, ++i);
    }
    return 2;

}

