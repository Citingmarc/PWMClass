# PWMClass

A class to be called on interrupts to manage a template PWM signal.  
Every 256 calls the PWM signal completes one cycle.  <br/>
The timer on the interrupt should be defined by the desired period / 256.  

### Usage

* Add a #Include PWMClass.h to the headers
* Create a class variable on initialization, giving the duty cycle (uint_8 [range 0-255], template OutputPin)
* On each interrupt cycle call the functor PWM()
* The period of the signal will be determined by 1/256 * the timer of the interrupt

``` C++ 

#include "PWMClass.h"

int main()
{
    PWM<int> PWM(75, 0); /** int for a sample template type ; 75 = dutycycle ; 0 = pin to change */
    int pulse = 0;

    for (int i = 0; i < 255*2 ; ++i) { /** Execute for 2 cycles */

        pulse = PWM();
        
        std::cout << "i= " << i << " output = " << pulse << std::endl; /** Output PWM */
    }

    std::cin.get(); 
    return 0; 

}

``` 

### UnitTesting

The class is tested by the Google unit test library
Two main tests:

* Duty cycle read and wright 

* Output PWM capability on two factos:
* Total time on for X number of cycles
* Total times switched from 0 to 1 on X number of cycles

To run the test open PWMGenerator.sln and compile/run the project


