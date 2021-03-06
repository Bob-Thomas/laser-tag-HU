/**
 * \file      button-controller.hpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */
#include "button-controller.hpp"

ButtonController::ButtonController(hwlib::target::pin_in &button, IController* listener) : task(1, "Button controller"),
 button(button), listener(listener), clock(this, 25* rtos::ms, "Button listener") {

}

void ButtonController::main() {
    for(;;) {
        wait(clock);
        if(button.get() && !clicked) {
            listener->buttonPressed();
            clicked = true;
        } else if (!button.get() && clicked) {
            clicked = false;
        }
        wait(clock);
    }
}