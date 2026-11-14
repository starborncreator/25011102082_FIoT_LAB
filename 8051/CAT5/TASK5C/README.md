
# **README**

# 8051 – Signal Generation and Stepper Motor Control

## Experiment Details

**Microcontroller:** 8051 (AT89S52)

**Development Environment:** Keil µVision

**Crystal Frequency:** 11.0592 MHz

**Timer:** Timer 0 Interrupt

---

# TASK 2 – Different Signal Types

## 1. Objective

To generate different digital signal patterns using the timer interrupt mechanism after successfully implementing square-wave generation.

The experiment involves generating four different types of digital waveforms:

1. Square Wave
2. Variable Duty-Cycle Wave
3. Pulse Train
4. Burst Signal

## 2. Working Principle

The timer interrupt is used to generate periodic changes in the GPIO output state.

By controlling the duration for which the GPIO pin remains HIGH or LOW, different digital waveforms can be generated.

The output waveform is observed and verified using an oscilloscope.

### 2.1 Square Wave

**Objective:** To generate a continuous square wave by alternating between HIGH and LOW states.

**Working Principle:**

The GPIO output is continuously toggled between logic HIGH and logic LOW at regular time intervals.

This produces a periodic square waveform.

**Expected Output:**

```text
101010101010
```

### 2.2 Variable Duty-Cycle Wave

**Objective:** To generate a waveform with varying HIGH and LOW durations.

**Working Principle:**

The duration of the HIGH state and LOW state is varied to produce a waveform with a different duty cycle.

**Expected Output:**

```text
1111000011110000
```

### 2.3 Pulse Train

**Objective:** To generate a sequence of pulses separated by LOW intervals.

**Working Principle:**

The GPIO output generates a HIGH pulse followed by a longer LOW interval. This sequence repeats to form a pulse train.

**Expected Output:**

```text
100000001000000010000000
```

### 2.4 Burst Signal

**Objective:** To generate groups of pulses separated by periods of inactivity.

**Working Principle:**

A group of pulses is generated continuously, followed by a LOW interval. Another group of pulses is then generated.

**Expected Output:**

```text
1010101010 0000000000 1010101010
```

## 3. Implementation Steps

1. Configure a GPIO pin as an output.
2. Configure Timer 0 to generate periodic interrupts.
3. Implement a timer interrupt service routine.
4. Generate a continuous square wave by toggling the GPIO pin.
5. Modify the HIGH and LOW durations to generate variable duty-cycle signals.
6. Generate pulses separated by LOW intervals.
7. Generate groups of pulses separated by inactive intervals.
8. Verify the generated waveforms using an oscilloscope.

## 4. Concepts Covered

- Digital signal generation.
- GPIO output control.
- Timer interrupt programming.
- Square-wave generation.
- Duty-cycle variation.
- Pulse train generation.
- Burst signal generation.
- Oscilloscope-based waveform verification.

---

# TASK 3 – Stepper Motor Control Using Timer Interrupts

## 1. Objective

To interface and control a stepper motor using the 8051 microcontroller and timer interrupts.

The timer interrupt is used to generate sequential stepping signals to rotate the motor.

The motor speed is controlled by varying the timer interval between successive steps.

## 2. Working Principle

A stepper motor rotates in discrete angular steps when its coils are energized in a specific sequence.

The microcontroller generates a sequence of digital output patterns to control the motor movement.

A timer interrupt determines when the next stepping pattern should be generated.

The four-step sequence used in this experiment is:

```text
1000
  |
  v
0100
  |
  v
0010
  |
  v
0001
  |
  v
Repeat
```

Each output pattern represents the activation of a particular motor phase.

The timer interval determines the motor speed. A shorter interval results in faster rotation, while a longer interval results in slower rotation.

## 3. Stepper Motor Speed Control

The motor speed is controlled by changing the time interval between successive steps.

### Speed Modes

| Speed Mode | Timer Interval | Motor Speed |
|---|---|---|
| Slow | 100 ms/step | Slow rotation |
| Medium | 50 ms/step | Medium rotation |
| Fast | 10 ms/step | Fast rotation |

### 3.1 Slow Speed

- Step interval: 100 ms.
- The motor takes more time between successive steps.
- Results in slower rotation.

### 3.2 Medium Speed

- Step interval: 50 ms.
- The motor steps at a moderate rate.
- Results in medium-speed rotation.

### 3.3 Fast Speed

- Step interval: 10 ms.
- The motor takes less time between successive steps.
- Results in faster rotation.

## 4. Implementation Steps

1. Configure the required GPIO pins as outputs.
2. Connect the motor control interface to the microcontroller.
3. Configure Timer 0 to generate periodic interrupts.
4. Initialize the step sequence.
5. Generate the first stepping pattern (1000).
6. Generate the next pattern (0100).
7. Continue with (0010) and (0001).
8. Repeat the sequence continuously.
9. Implement different speed modes by changing the timer interval.
10. Observe the motor rotation at slow, medium and fast speeds.

## 5. Stepper Motor Sequence

| Step Number | Output Pattern |
|:---:|:---:|
| 1 | 1000 |
| 2 | 0100 |
| 3 | 0010 |
| 4 | 0001 |
| 5 | 1000 |

The sequence repeats continuously to produce motor rotation.

## 6. Concepts Covered

- Stepper motor interfacing.
- GPIO output control.
- Timer interrupt configuration.
- Interrupt Service Routine (ISR).
- Sequential output generation.
- Stepper motor stepping sequence.
- Motor speed control.
- Timer interval calculation.
- Embedded C programming.

---

# Hardware Requirements

- 8051 Microcontroller (AT89S52)
- Stepper Motor
- Suitable Motor Driver
- 8051 Development Board
- 11.0592 MHz Crystal Oscillator
- Connecting Wires
- Power Supply
- Digital Oscilloscope

# Software Requirements

- Keil µVision IDE
- 8051 C Compiler
- Embedded C

---

# Learning Outcomes

- Understand different digital waveform generation techniques.
- Generate square waves using timer interrupts.
- Implement variable duty-cycle signals.
- Generate pulse trains and burst signals.
- Understand stepper motor operation.
- Generate sequential stepping patterns.
- Control motor speed by varying timer intervals.
- Develop interrupt-based embedded applications.

---

# Expected Results

1. Successfully generate square-wave signals.
2. Generate variable duty-cycle waveforms.
3. Implement pulse train and burst signal generation.
4. Interface a stepper motor with the 8051 microcontroller through a suitable driver.
5. Generate the required four-step sequence using timer interrupts.
6. Control motor speed at slow, medium and fast intervals.

---

# Final Result

Successfully implemented different digital signal generation techniques using timer interrupts and demonstrated stepper motor control using sequential GPIO output patterns.

The motor speed was varied by changing the timer interval between successive steps.
