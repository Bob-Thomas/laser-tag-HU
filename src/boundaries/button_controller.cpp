#include "button_controller.hpp"

ButtonController::ButtonController(hwlib::target::pin_in &button, IController* listener) : task("Button controller"),
 button(button), listener(listener), clock(this, 100* rtos::ms, "Button listener") {

}

void ButtonController::main() {
    for(;;) {
        wait(clock);
        if(!button.get() && !clicked) {
            listener->button_pressed();
            clicked = true;
        } else if (button.get() && clicked) {
            clicked = false;
        }

    }
}