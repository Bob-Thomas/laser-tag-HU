#include "hwlib.hpp"
#include "rtos.hpp"
#include "boundaries/ir-receive-controller.hpp"
#include "./boundaries/button_controller.hpp"
#include "./boundaries/keypad-controller.hpp"
#include "./boundaries/sound-controller.hpp"
#include "./interfaces/i-controller.hpp"
#include "./stateController/player-task.hpp"
#include "./stateController/master-task.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    // oled
    namespace target = hwlib::target;
    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( sda, scl );
    auto pin_gnd = target::pin_out( target::pins::d19 );
    pin_gnd.set( 0 );
    auto pin_vcc = target::pin_out( target::pins::d18 );
    pin_vcc.set( 1 );

    // Bounadires
    auto oled = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );
    auto button_pin = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto lsp = hwlib::target::pin_out(hwlib::target::pins::d8);
    auto irPin = hwlib::target::pin_in(hwlib::target::pins::d43);
    auto irTransmitterPin = hwlib::target::d2_36kHz();

    auto sound_controller = SoundController(lsp);
    auto display_controller = DisplayController(oled);
    auto irTransmitter = IrController(irTransmitterPin);
    #if GAMEMODE == PLAYER
    auto gameTask = PlayerTask(sound_controller, display_controller, irTransmitter);
    #elif GAMEMODE == LEADER
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
    auto gameTask = MasterTask(display_controller, irTransmitter);
    auto keypadController = KeypadController(keypad, &gameTask);
    #endif
    auto irReceivedController = IrReceiveController(irPin, &gameTask);
    auto button_controller = ButtonController(button_pin, &gameTask);
    rtos::run();
    return 0;
}
