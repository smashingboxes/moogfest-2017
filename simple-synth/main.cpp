#include "mbed.h"

PwmOut mypwm(D3);
AnalogIn potentiometer(A0);

int main() {
    while(1) {
        mypwm.period(1.0 / (220 + 1540 * potentiometer));
        mypwm.write(0.5);
        wait(0.01);
    }
}
