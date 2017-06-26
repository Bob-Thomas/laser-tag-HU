#include "wrap-hwlib.hh"
#include "rtos.hpp"

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
    auto p = hwlib::target::pin_out(hwlib::target::pins::d13);
    auto test = dave(p);
    rtos::run();
 return 0;
}
