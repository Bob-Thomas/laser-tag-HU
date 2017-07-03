

#include "ir-receive-controller.hpp"

IrReceiveController::IrReceiveController(hwlib::target::pin_in &ir):
        task("Receive"),
        ir(ir)
{}

void IrReceiveController::main() {
    for(;;) {
        if(!ir.get()) {
            auto signal = getByte();
            hwlib::wait_ms(3);
            auto signal2 = getByte();
            if (signal == signal2) {
                //WHAT TO DO WITH THE SIGNAL.

                //Print signal (Just for debugging)
                for(int i = 0; i < 16; i++){
                    hwlib::cout << (signal >> (15-i)& 1);
                }
                hwlib::cout << "\n==\n";
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

uint16_t IrReceiveController::getByte(uint16_t bitStream, uint16_t i){
    if(i == 16){
        return bitStream;
    }
    auto bit = getBit();
    if(bit != 2) {
        bitStream = bitStream | (bit << i);
        return getByte(bitStream, ++i);
    }
    return 2;

}


