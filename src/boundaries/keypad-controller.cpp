#include "keypad-controller.hpp"

KeypadController::KeyPadController(hwlib::keypad<16> &keypad, IController *controller) :
                                        keypad(keypad), controller(controller) {

}

void KeypadController::main() {
    for(;;) {
        rtos::sleep(pollTime);
        if(keypad.char_available()) {
            controller->send_key(keypad.getc());
        }
    }
}