#include "wrap-hwlib.hh"
#include "rtos.hpp"
#include "./boundaries/button_controller.hpp"
#include "./interfaces/i-controller.hpp"

class TestController :  public IController, public rtos::task<> {
private:
    void main() {
        for(;;) {
            hwlib::wait_ms(1);
        }
    }
public:
    TestController() : task("test task") {}
    void button_pressed() {
        hwlib::cout << "GEKLIKT\n";
    }
};

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto controller_pin = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto controller = TestController();
    auto button_controller = ButtonController(controller_pin, &controller);
    rtos::run();
 return 0;
}
