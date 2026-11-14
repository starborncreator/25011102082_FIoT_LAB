
# **README**

# 8051 – Timer 0 Interrupt-Based LED Blinking

## Experiment Details

**Experiment:** Timer 0 Configuration Using Interrupts

**Microcontroller:** 8051 (AT89S52)

**Development Environment:** Keil µVision

**Crystal Frequency:** 11.0592 MHz

---

## TASK 1 – Timer 0 Interrupt and LED Control

### 1. Objective

To configure Timer 0 of the 8051 microcontroller to generate precise periodic interrupts. Use the timer interrupt to establish a software time base and toggle an LED every 1 second.

The generated timing is verified using an oscilloscope.

---

### 2. Working Principle

Timer 0 is configured in 16-bit mode (Mode 1) to generate periodic interrupts.

The 8051 timer operates based on the machine cycle frequency, which is derived from the external crystal oscillator.

For a classic 12-clock 8051:

\`\`\`
Machine Cycle = 12 / Crystal Frequency
\`\`\`

With an 11.0592 MHz crystal:

\`\`\`
T_machine = 12 / 11.0592 MHz
          ≈ 1.085 µs
\`\`\`

A timer interrupt is generated approximately every 1 millisecond by loading the appropriate initial value into Timer 0.

Each time Timer 0 overflows:
1. The Timer 0 interrupt service routine (ISR) is executed.
2. The timer registers are reloaded.
3. A software counter is incremented.
4. After 1000 interrupts, one second has elapsed.
5. The LED state is toggled.

This process repeats continuously.

---

### 3. Timer Calculation

**Given:**
- Crystal Frequency = 11.0592 MHz
- Machine Cycle = 12 clock cycles
- Required Interrupt Period = 1 ms
- Timer Resolution = 16 bits

**Step 1: Calculate Machine Cycle Time**

\`\`\`
T_machine = 12 / 11.0592 MHz

          ≈ 1.085 µs
\`\`\`

**Step 2: Calculate Required Timer Counts**

For a 1 ms interrupt:

\`\`\`
N = 1 ms / 1.085 µs

  ≈ 922 counts
\`\`\`

**Step 3: Calculate Timer Preload Value**

Timer 0 is a 16-bit timer with a maximum count of 65536.

\`\`\`
Preload = 65536 - 922

        = 64614

        = FC66H
\`\`\`

Therefore, the Timer 0 registers are initialized as:

\`\`\`c
TH0 = 0xFC;
TL0 = 0x66;
\`\`\`

**Timer Configuration:**

| Parameter | Value |
|---|---|
| Timer | Timer 0 |
| Timer Mode | Mode 1 (16-bit) |
| Crystal Frequency | 11.0592 MHz |
| Machine Cycle Time | Approximately 1.085 µs |
| Interrupt Period | Approximately 1 ms |
| Timer Counts | 922 |
| TH0 | FC |
| TL0 | 66 |
| Interrupts per Second | 1000 |

---

### 4. Interrupt-Based Software Time Base

A software counter is maintained inside the Timer 0 interrupt service routine.

Every timer overflow generates an interrupt approximately every 1 millisecond.

The interrupt counter is incremented each time the ISR executes.

When the counter reaches 1000, approximately one second has elapsed, and the LED state is toggled.

**Execution Sequence:**

\`\`\`text
Crystal Oscillator (11.0592 MHz)
              |
              v
        Machine Cycle
              |
              v
        Timer 0 Counter
              |
              v
           Overflow
              |
              v
      Timer 0 Interrupt
              |
              v
     Software Time Base
         (1000 ms)
              |
              v
       LED State Toggle
              |
              v
       Repeat Continuously
\`\`\`

---

### 5. Implementation Steps

1. Configure Timer 0 in 16-bit Mode 1.
2. Calculate the timer preload value using the crystal frequency.
3. Load TH0 and TL0 with the calculated values.
4. Enable Timer 0 interrupts using ET0.
5. Enable global interrupts using EA.
6. Start Timer 0 using TR0.
7. Implement the Timer 0 interrupt service routine.
8. Reload the timer registers whenever an overflow occurs.
9. Maintain a software counter to track the elapsed time.
10. Toggle the LED after every 1000 timer interrupts.

---

### 6. Expected Output

- Timer 0 generates periodic interrupts approximately every 1 ms.
- The software counter tracks the elapsed time.
- The LED toggles after every 1-second interval.
- The LED continuously switches between ON and OFF states.

**Expected LED Behaviour:**

\`\`\`text
Time        LED State

0 sec       OFF
1 sec       ON
2 sec       OFF
3 sec       ON
4 sec       OFF
5 sec       ON
...
\`\`\`

The LED output can be observed using an oscilloscope to verify the generated timing.

---

### 7. Oscilloscope Verification

Connect the oscilloscope probe to the GPIO pin connected to the LED.

Observe the output waveform and verify:

- The LED output changes state approximately every 1 second.
- The complete ON-OFF cycle takes approximately 2 seconds.
- The output frequency is approximately 0.5 Hz for a 1-second toggle interval.

---

### 8. Concepts Covered

- 8051 Timer 0 configuration.
- 16-bit timer operation (Mode 1).
- Machine cycle calculation.
- Timer preload calculation.
- Interrupt generation and handling.
- Interrupt Service Routine (ISR).
- Software time-base generation.
- GPIO output control.
- LED interfacing.
- Oscilloscope-based timing verification.

---

### 9. Result

Successfully configured Timer 0 of the 8051 microcontroller in 16-bit mode to generate periodic interrupts. Implemented a software time base using timer interrupts to toggle an LED every 1 second.

The generated timing was verified using an oscilloscope.
