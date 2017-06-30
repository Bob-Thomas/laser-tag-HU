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
        bool bits[16];
        int j = 0;
        while(j < 16) {
            on = 0;
            off = 0;
            for (int i = 0; i < 23; i++) {
                // Add time to the state of the IR.
                !ir.get() ? on += pullTimeUs : off += pullTimeUs;
                hwlib::wait_us(pullTimeUs);
            }

            if (on > off) {
                // one bit
                bits[j] = true;
                j++;
            } else {
                // zero bit
                if(j > 0) {
                    bits[j] = false;
                    j++;
                }
            }
        }

        foundSignal = false;
        for(int i = 0; i < 16; i++) {
            hwlib::cout << bits[i] << " ";
        }
        hwlib::cout << "\n===\n";
    }
}