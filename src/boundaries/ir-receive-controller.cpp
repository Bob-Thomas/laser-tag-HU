//
// Created by robbie on 29-6-2017.
//

#include "ir-receive-controller.hpp"

IrReceiveController::IrReceiveController(hwlib::target::pin_in &ir): task("Receive"), ir(ir) {

}

void IrReceiveController::addListener(Controller *c) {
    if(amountListeners < 3) {
        controllers[amountListeners] = c;
        amountListeners++;
    }
}

void IrReceiveController::main() {
    for(;;) {
        // polling for signal
        signal = ir.get();
        if(!foundSignal) {
            if (signal == 0) {
                foundSignal = true;
            } else {
                continue; // no signal, start over again..
            }
        }

        if(bitNumber >= 15){
            for(int i = 0; i < 16; i++) {
                hwlib::cout << bits[i] << " ";
            }
            hwlib::cout << "\n===\n";
            bitNumber = 0;
            foundSignal = false;
        }

        if(on + off < 21*pullTimeUs){
            !ir.get() ? on += pullTimeUs : off += pullTimeUs;
        }else{
            if (on > off) {
                // one bit
                bits[bitNumber] = true;
            } else {
                // zero bit
                if(bitNumber > 0) {
                    bits[bitNumber] = false;
                }
            }
            on = 0;
            off = 0;
            bitNumber++;
        }

        hwlib::wait_us(pullTimeUs);
    }
}