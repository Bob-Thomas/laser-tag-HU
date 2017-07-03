#include "hwlib.hpp"
#include "rtos.hpp"
#include "boundaries/ir-receive-controller.hpp"
#include "./boundaries/button_controller.hpp"
#include "./boundaries/keypad-controller.hpp"
#include "./boundaries/sound-controller.hpp"
#include "./interfaces/i-controller.hpp"

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
    auto in0  = hwlib::target::pin_in( hwlib::target::pins::a3 );
	auto in1  = hwlib::target::pin_in( hwlib::target::pins::a2 );
	auto in2  = hwlib::target::pin_in( hwlib::target::pins::a1 );
	auto in3  = hwlib::target::pin_in( hwlib::target::pins::a0 );
	auto out0 = hwlib::target::pin_oc( hwlib::target::pins::a7 );
	auto out1 = hwlib::target::pin_oc( hwlib::target::pins::a6 );
	auto out2 = hwlib::target::pin_oc( hwlib::target::pins::a5 );
	auto out3 = hwlib::target::pin_oc( hwlib::target::pins::a4 );


	// Setup necessary items for the keypad
	auto outPort = hwlib::port_oc_from_pins( out0, out1, out2, out3 );
	auto inPort = hwlib::port_in_from_pins( in0, in1, in2, in3 );
	auto matrix = hwlib::matrix_of_switches( outPort, inPort );
	auto keypad = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );

    auto lsp = hwlib::target::pin_out(hwlib::target::pins::d8);
    auto sound_controller = SoundController(lsp);
    auto controller_pin = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto controller = TestController(sound_controller);
    auto keypadController = KeypadController(keypad, &controller);
    auto button_controller = ButtonController(controller_pin, &controller);
    auto irPin = hwlib::target::pin_in(hwlib::target::pins::d22);
    IrReceiveController irReceiveController(irPin);
    hwlib::wait_ms(100);
    rtos::run();
    return 0;
}
