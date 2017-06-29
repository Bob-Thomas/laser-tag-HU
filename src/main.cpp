#include "wrap-hwlib.hh"
#include "rtos.hpp"
#include "./boundaries/ir-controller.hpp"

class dave : public rtos::task<> {
private:
    hwlib::target::d2_36kHz& p;
    IrController ir;
    uint16_t bits = 0b1010101010101010;
    void main() {
        while(1){
           ir.send(bits);
            hwlib::wait_ms(1000);
        }
    }
public:
    dave(hwlib::target::d2_36kHz& p):
            task("Main"),
            p(p),
            ir(p)
    {}
};

class receive : public rtos::task<>{
private:
    hwlib::target::pin_in& irReceiver;
    int highCount = 0;
    int lowCount = 0;
    void main(){
        while(1){

            for(int i = 0; i < 2400; ++i){
                if(irReceiver.get() == 0){
                    ++highCount;
                }else{
                    ++lowCount;
                }
                if(i%800 == 0){
                    hwlib::cout << (highCount > lowCount ? 1 : 0);
                }
                hwlib::wait_us(1);
            }
            hwlib::cout << "\n";
        }
    }
public:
    receive(hwlib::target::pin_in& irReceiver):
            irReceiver(irReceiver)
    {}
};

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto p = hwlib::target::d2_36kHz();
    //auto m = hwlib::target::pin_in(hwlib::target::pins::d24);
    //auto k = hwlib::target::pin_out(hwlib::target::pins::d26);
    //k.set(1);
    //auto test1 = receive(m);
    auto test2 = dave(p);
    rtos::run();
 return 0;
}
