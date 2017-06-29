#include "keypad-controller.hpp"

KeypadController::KeypadController(hwlib::keypad<16> &keypad, IController *controller) :
                                       task("keypad task"), keypad(keypad), controller(controller) {

}

void KeypadController::main() {
    for(;;) {
        sleep(pollTime);
        if(keypad.char_available()) {
            controller->keypad_pressed(keypad.getc());
        }
    }
}