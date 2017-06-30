#include "wrap-hwlib.hh"
#include "rtos.hpp"
#include "stateController/init-game-controller.hpp"
#include "boundaries/ir-receive-controller.hpp"

class dave : public rtos::task<> {
    public:
        dave(hwlib::target::pin_out& p): task("Main"), p(p){
        }
    private:
        hwlib::target::pin_out& p;
        void main() {
            for(;;) {
                hwlib::wait_ms(200);
                p.set(0);
                hwlib::wait_ms(200);
                p.set(1);
            }
        }
};
int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto irPin = hwlib::target::pin_in(hwlib::target::pins::d22);
    //InitGameController initGame;
    IrReceiveController irReceiveController(irPin);
    //irReceiveController.addListener(&initGame);
    hwlib::wait_ms(1000);
    rtos::run();
    return 0;
}
