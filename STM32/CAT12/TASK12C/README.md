
# **README**

# STM32 – Short-Press and Long-Press Detection

## Experiment Details

**Experiment:** Short-Press and Long-Press Detection

**Microcontroller:** STM32F401RE

**Development Board:** NUCLEO-F401RE

**Development Environment:** STM32CubeIDE

**Programming Language:** Embedded C

---

## TASK 12C – Short-Press and Long-Press Detection

### 1. Objective

To extend the existing STM32 push-button application by implementing short-press and long-press detection.

The application should distinguish between a short button press and a long button press. The STM32 must perform different actions depending on the duration for which the push button is pressed.

### 2. Working Principle

The on-board push button is configured as a GPIO input, while the on-board LED is configured as a GPIO output.

The microcontroller monitors the push-button state and measures the duration for which the button remains pressed.

Based on the measured press duration, the application identifies whether the input is a short press or a long press.

Different actions are executed depending on the detected press type.

**Short Press:**
- Detect the button press.
- Measure the duration of the press.
- Identify it as a short press when the duration is below the configured threshold.
- Execute the corresponding short-press action.

**Long Press:**
- Detect the button press.
- Continue monitoring while the button remains pressed.
- Identify it as a long press when the configured duration threshold is reached.
- Execute the corresponding long-press action.

### 3. Button Press Detection

The application distinguishes between two types of button events.

| Press Type | Description |
|---|---|
| Short Press | Button is pressed and released within the configured short-press duration. |
| Long Press | Button remains pressed until the configured long-press duration is reached. |

### 4. Implementation Steps

1. Configure the on-board push button as a GPIO input.
2. Configure the on-board LED as a GPIO output.
3. Initialize the GPIO peripherals.
4. Continuously monitor the push-button state.
5. Detect the button press event.
6. Record the time at which the button is pressed.
7. Monitor the button until it is released.
8. Calculate the total button press duration.
9. Compare the measured duration with the configured threshold.
10. Identify whether the event is a short press or a long press.
11. Execute the corresponding action.
12. Repeat the process continuously.

### 5. Expected Behaviour

The application should distinguish between short and long button presses.

| Button Action | Expected Behaviour |
|---|---|
| Short Press | Execute the short-press action |
| Long Press | Execute the long-press action |
| Button Released | End the current press event |

The specific actions associated with short and long presses are defined by the application implementation.

### 6. Concepts Covered

- STM32 GPIO input configuration.
- Push-button interfacing.
- Button press and release detection.
- Short-press detection.
- Long-press detection.
- Press-duration measurement.
- Timer-based time measurement.
- Conditional logic.
- Event detection.
- Embedded C programming.

### 7. Expected Results

1. Successfully detect push-button press and release events.
2. Measure the duration of each button press.
3. Distinguish between short and long button presses.
4. Execute different actions based on the press duration.
5. Verify correct operation through the on-board LED.

### 8. Result

Successfully implemented short-press and long-press detection using the STM32F401RE microcontroller.

The application distinguishes between button presses based on their duration and performs different actions depending on whether a short press or long press is detected.

---

## Hardware Requirements

- NUCLEO-F401RE Development Board
- On-board User Push Button
- On-board User LED
- USB Cable
- PC or Laptop

## Software Requirements

- STM32CubeIDE
- STM32 HAL Library (if HAL-based implementation is used)
- Embedded C

---

## Deliverables

- STM32 GPIO configuration.
- Push-button detection implementation.
- Short-press detection logic.
- Long-press detection logic.
- Press-duration measurement.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
