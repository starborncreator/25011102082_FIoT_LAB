# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 2

**NAME OF EXP:** LED Blinking Using 8051 Microcontroller

**HARDWARE SETUP / PLATFORM:** 8051 Development Board, Keil µVision

---

## TASK 2A: SINGLE LED BLINKING

### 1. Circuit Diagram

**Components Required:**
- 8051 Microcontroller (AT89S52)
- 1 LED
- Current-limiting resistor (220Ω–330Ω)
- 5V Power Supply

**Connections:**
- LED Anode (+) → +5V through a current-limiting resistor.
- LED Cathode (-) → P1.0 of the 8051 microcontroller.
- Connect the microcontroller to a 5V power supply.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The program configures pin P1.0 as an output to control a single LED. The LED is connected in an active-low configuration. Therefore, setting P1.0 to LOW turns the LED ON, while setting it to HIGH turns the LED OFF.

A delay function is implemented using nested loops to generate a time interval between the ON and OFF states. This creates a visible blinking effect. The process repeats continuously inside an infinite loop.

**Pseudocode:**

1. Start the program.
2. Configure P1.0 as the LED control output.
3. Set P1.0 to LOW to turn ON the LED.
4. Call the delay function.
5. Set P1.0 to HIGH to turn OFF the LED.
6. Call the delay function.
7. Repeat steps 3–6 continuously.

**Code Base:**

\`\`\`c
#include <REG51.H>

sbit LED = P1^0;

void delay()
{
    int i, j;
    for(i = 0; i < 500; i++)
        for(j = 0; j < 100; j++);
}

void main()
{
    while(1)
    {
        LED = 0;   // LED ON
        delay();

        LED = 1;   // LED OFF
        delay();
    }
}
\`\`\`

### 3. Inference

The experiment demonstrates basic GPIO output control using the 8051 microcontroller (AT89S52). The LED connected to P1.0 blinks continuously with a delay between its ON and OFF states.

The experiment helps understand active-low LED interfacing, port pin manipulation, delay generation using software loops, and the use of infinite loops for continuous hardware operation.

**Result:** Successful implementation of single LED blinking using the 8051 microcontroller.
