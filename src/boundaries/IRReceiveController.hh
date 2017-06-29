//
// Created by robbie on 29-6-2017.
//

#ifndef LASER_IRRECEIVECONTROLLER_HH
#define LASER_IRRECEIVECONTROLLER_HH

#include "./rtos.hpp"

class IRReceiveController : public rtos::task<> {
private:
    int on = 0;
    int off = 0;
    u_int16 first_received_byte = 0;
    u_int16 received_byte = 0;
    int bit_index = 0;
    const int pull_time_us = 4;
    const int ms_between_signal = 3;
    bool is_second_listen = false;
    hwlib::pin_in &ir;
public:
    IRReceiveController(hwlib::pin_in &ir):ir(ir) {

    }
    void main() {
        for(;;) {
            // Add time to the state of the IR.
            ir.get()? on+= pull_time_us : off += pull_time_us;
            // Wait the time pull time with hwlib.
            hwlib::wait_us(pull_time_us);
            // If the the waited time is above the 2400 us, no correct signal.
            if ((off + on) > 2400) {
                // Reset the time.
                on, off = 0;
            } else {
                // If a 0 bit is received.
                if (on == 800 && off == 1600) {
                    // Check if there is a start bit in the byte.
                    if (received_byte >> 0 & 1) {
                        // Set 0 bit in the byte.
                        received_byte &= ~(1 << bit_index);
                        bit_index++;
                    }
                }
                // If the 1 bit is received.
                if (on == 1600 && off == 800) {
                    // Set 1 bit in the byte.
                    received_byte |= 1 << bit_index;
                    bit_index++;
                }
                // If more then 16 bits is received..
                if (bit_index > 16) {
                    bit_index = 0;
                    // Wait the time between the 2 commands.
                    hwlib::wait_ms(ms_between_signal);
                    // Check if second listen is true for this signal
                    if (is_second_listen) {
                        // Send the command to controllers... TODO..
                        //this.ctrl->ir_received(received_byte);
                    } else {
                        // Store the data in the first received byte.
                        first_received_byte = received_byte;
                        received_byte = 0;
                        is_second_listen = true;
                    }
                }
            }
        }
    }
};


#endif //LASER_IRRECEIVECONTROLLER_HH
