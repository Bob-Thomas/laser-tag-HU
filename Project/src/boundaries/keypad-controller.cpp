/**
 * \file      keypad-controller.hpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */
#include "keypad-controller.hpp"

KeypadController::KeypadController(hwlib::keypad<16> &keypad, IController *controller) :
    task(2, "keypad task"),
    keypad(keypad),
    controller(controller)
{}

void KeypadController::main() {
    for(;;) {
        sleep(pollTime);
        if(keypad.char_available()) {
            controller->keypadPressed(keypad.getc());
        }
    }
}