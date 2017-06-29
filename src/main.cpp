#include "wrap-hwlib.hh"
#include "rtos.hpp"
#include "./boundaries/ir-controller.hpp"

class dave : public rtos::task<> {
private:
    hwlib::target::d2_36kHz& p;
    IrController ir;
    uint16_t bits = 0b1010100011101011;
    void main() {
        while(1){
            ir.send(bits);
        }
    }
public:
    dave(hwlib::target::d2_36kHz& p):
            task("Main"),
            p(p),
            ir(p)
    {}
};
int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto p = hwlib::target::d2_36kHz();
    auto test = dave(p);
    rtos::run();
 return 0;
}
