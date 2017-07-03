#include "wrap-hwlib.hh"
#include "rtos.hpp"
#include "stateController/init-game-controller.hpp"
#include "boundaries/ir-receive-controller.hpp"


int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto irPin = hwlib::target::pin_in(hwlib::target::pins::d22);
    IrReceiveController irReceiveController(irPin);
    hwlib::wait_ms(100);
    rtos::run();
    return 0;
}
