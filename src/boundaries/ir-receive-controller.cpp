//
// Created by robbie on 29-6-2017.
//

#include "ir-receive-controller.hpp"

IrReceiveController::IrReceiveController(hwlib::target::pin_in &ir):
        task("Receive"),
        ir(ir)
{}

void IrReceiveController::main() {
    for(;;) {
        if(!ir.get()){
            auto signal = getByte();
            auto signal2 = getByte();
            if(signal == signal2){
                for(int i = 0; i < 16; i++){
                    hwlib::cout << (signal >> (15-i)& 1);
                }
                hwlib::cout << "\n==\n";
            }
        }
        hwlib::wait_us(400);
    }
}

int16_t IrReceiveController::getBit(long long int start){
    if(start == 0){
        start = hwlib::now_us();
    }
    if(ir.get()){
        hwlib::wait_us(100);
        return (start - hwlib::now_us() >= 4800) ? int16_t(-1) : getBit(start);
    }
    hwlib::wait_us(1100);
    bool b = !ir.get();
    hwlib::wait_us(700);
    return b;
}

int IrReceiveController::getByte(int16_t bitStream, int16_t i){
    if(i == 16){
        return bitStream;
    }
    auto bit = getBit();
    if(bit != -1) {
        bitStream = bitStream | (bit << i);
        i++;
        return getByte(bitStream, i);
    }
    return -1;

}


