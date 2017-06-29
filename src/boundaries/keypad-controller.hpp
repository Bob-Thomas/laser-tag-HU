#ifdef KEYPAD_CONTROLLER_HPP
#define KEYPAD_CONTROLLER_HPP
#include "rtos.hpp"
#include "hwlib.hpp"
#include "../interfaces/i-controller.hpp"
class IController;
class KeyPadController : public rtos::task<> {
private:
    static constexpr pollTime = 200*rtos::ms;
    void main();
public:
    KeypadController(hwlib::keypad<16> &keypad, IController *controller);

};

#endif //KEYPAD_CONTROLLER_HPP