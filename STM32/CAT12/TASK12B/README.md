
# **README**

# STM32 – On-board Switch Control with State Remembrance

## Experiment Details

**Experiment:** On-board Switch Control with State Remembrance

**Microcontroller:** STM32F401RE

**Development Board:** NUCLEO-F401RE

**Development Environment:** STM32CubeIDE

**Programming Language:** Embedded C

---

## TASK 12B – On-board Switch Control with State Remembrance

### 1. Objective

To modify the existing STM32 LED blinking application so that the on-board push button controls the LED.

The LED should toggle its state whenever a valid button press is detected and remember its previous state after the button is released.

### 2. Working Principle

The on-board push button is configured as a GPIO input, while the on-board LED is configured as a GPIO output.

The microcontroller continuously monitors the push-button input to detect valid button presses.

Whenever a valid button press is detected:
1. The current LED state is read.
2. The LED state is toggled.
3. The updated state is maintained even after the button is released.
4. The system waits for the next valid button press.

The LED remains in its previous state until another valid button press is detected.

### 3. Implementation Steps

1. Create or modify the existing STM32 project for the NUCLEO-F401RE board.
2. Configure the on-board LED GPIO pin as an output.
3. Configure the on-board push-button GPIO pin as an input.
4. Initialize the GPIO peripherals.
5. Continuously monitor the push-button input.
6. Detect a valid button press.
7. Toggle the LED output state whenever a valid press is detected.
8. Maintain the LED's updated state after the button is released.
9. Wait for the next valid button press.
10. Repeat the process continuously.

### 4. Expected LED Behaviour

The LED toggles its state with every valid push-button press.

**Expected Sequence:**

| Button Action | LED State |
|---|---|
| Initial State | OFF |
| First Press | ON |
| Button Released | ON |
| Second Press | OFF |
| Button Released | OFF |
| Third Press | ON |
| Button Released | ON |

### 5. Expected Output

- The push button successfully controls the on-board LED.
- Each valid button press toggles the LED state.
- The LED retains its state after the button is released.
- The LED does not automatically return to its previous state upon button release.
- The system responds to successive button presses.

### 6. Concepts Covered

- STM32 GPIO input configuration.
- STM32 GPIO output configuration.
- Push-button interfacing.
- LED control using GPIO.
- Button press detection.
- State toggling.
- State remembrance.
- Digital input and output operations.
- Embedded C programming.

### 7. Result

Successfully implemented on-board push-button control using the STM32F401RE microcontroller.

The LED toggles its state whenever a valid button press is detected and retains its previous state after the button is released.

---

## Hardware Requirements

- NUCLEO-F401RE Development Board
- On-board User LED
- On-board Push Button
- USB Cable
- PC or Laptop

## Software Requirements

- STM32CubeIDE
- STM32 HAL Library (if HAL-based implementation is used)
- Embedded C

---

## Deliverables

- STM32 GPIO configuration.
- Push-button input implementation.
- LED output control implementation.
- State remembrance logic.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
