#include "hwlib.hpp"
#include "../rtos/rtos.hpp"
int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    rtos::run();
 return 0;
}
