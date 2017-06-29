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
    for(;;) { //1 = true | 0 = false
        signal = ir.get();
        //hwlib::cout << signal << "\t";
        //if(signal == 0){
        //    foundSignal = true;
            //hwlib::cout << "piew\n";
       // }else{
            //hwlib::cout << "\tpow\n";
        //    continue;
        //}
        // Add time to the state of the IR.
        !signal ? on += pullTimeUs : off += pullTimeUs;

        // Wait the time pull time with hwlib.
        hwlib::wait_us(pullTimeUs);

        // If the the waited time is above the 2400 us, no correct signal.
        if ((off + on) > 2400) {
            // Reset the time.
            //hwlib::cout << "on: " << on << "\toff: ";
            //hwlib::cout << off << "\n";
            on = 0;
            off = 0;

        } else {
            // If a 0 bit is received.
            if (on == 800 && off == 1600) {
                // Check if there is a start bit in the byte.
                if (receivedByte >> 0 & 1) {
                    // Set 0 bit in the byte.
                    receivedByte &= ~(1 << bitIndex);
                    bitIndex++;
                }
            }
            // If the 1 bit is received.
            if (on == 1600 && off == 800) {
                // Set 1 bit in the byte.
                receivedByte |= 1 << bitIndex;
                bitIndex++;
            }
            // If more then 16 bits is received..
            if (bitIndex >= 15) {
                bitIndex = 0;
                foundSignal = false;
                for(int i = 0; i < 16; ++i){
                    hwlib::cout << (receivedByte & (1 << i));
                }
                hwlib::cout << "\n";
                // Wait the time between the 2 commands.
                hwlib::wait_ms(msBetweenSignal);
                // Check if second listen is true for this signal
                if (isSecondListen) {
                    // Send the command to controllers... TODO..
                    //this.ctrl->ir_received(receivedByte);
                    for (int i = 0; i < amountListeners; i++) {
                        controllers[i]->irReceived(Command(receivedByte));
                    }
                } else {
                    // Store the data in the first received byte.
                    firstReceivedByte = receivedByte;
                    receivedByte = 0;
                    isSecondListen = true;
                    break;
                }
            }
        }
    }
}