
# **README**

# STM32 – Event-Based LED Control with Debouncing

## Experiment Details

**Experiment:** Event-Based Control

**Microcontroller:** STM32

**Development Board:** NUCLEO-F401RE

**Development Environment:** STM32CubeIDE

**Programming Language:** Embedded C

**Interface:** GPIO

---

## TASK 8B – Event-Based Control

### 1. Objective

To modify the existing STM32 push-button and LED application so that every valid button press toggles the LED state.

The experiment focuses on detecting individual button press events and investigating switch bounce. A simple software debouncing technique is implemented to ensure that one physical button press produces exactly one LED toggle.

### 2. Working Principle

In a normal push-button application, mechanical contact bouncing may generate multiple rapid transitions when the button is pressed or released.

These unwanted transitions can cause the microcontroller to detect multiple button presses instead of one.

To prevent this, a software debouncing mechanism is introduced.

The STM32 continuously monitors the push-button input and identifies a valid press event.

Whenever a valid button press is detected:

1. The button press is identified.
2. A small software delay is introduced to handle switch bounce.
3. The button state is checked again to confirm the press.
4. The LED state is toggled once.
5. The system waits for the button to be released before detecting the next press.

The LED retains its updated state until another valid button press occurs.

### 3. Switch Bounce

**Objective:** To understand the effect of mechanical switch bouncing on GPIO input detection.

**Working Principle:**

Mechanical push buttons may produce multiple rapid HIGH and LOW transitions during a single physical press.

These transitions are called switch bounce.

Without debouncing, the STM32 may interpret one physical press as multiple input events, resulting in unwanted LED toggling.

A software delay and input-state verification are used to filter these unwanted transitions.

### 4. Event-Based LED Control

The LED changes its state only when a valid button press event is detected.

| Button Event | LED Operation |
|---|---|
| Initial State | OFF |
| First Valid Press | ON |
| Button Released | Remains ON |
| Second Valid Press | OFF |
| Button Released | Remains OFF |
| Third Valid Press | ON |

### 5. Implementation Steps

1. Configure the push-button GPIO pin as an input.
2. Configure the LED GPIO pin as an output.
3. Initialize the GPIO peripherals.
4. Continuously monitor the push-button state.
5. Detect a possible button press event.
6. Introduce a small software delay for debouncing.
7. Read the button state again to confirm a valid press.
8. Toggle the LED state when a valid press is detected.
9. Wait until the button is released.
10. Introduce debouncing for the release event if required.
11. Wait for the next valid button press.
12. Repeat the process continuously.

### 6. Expected Behaviour

The LED should toggle exactly once for every valid button press.

**Expected Sequence:**

```text
Initial State     → LED OFF

First Press       → LED ON
Button Released   → LED ON

Second Press      → LED OFF
Button Released   → LED OFF

Third Press       → LED ON
Button Released   → LED ON
```

### 7. Expected Output

- Successful GPIO initialization.
- Reliable push-button press detection.
- Software switch debouncing.
- Exactly one LED toggle per valid button press.
- LED retains its state after button release.
- No unwanted multiple toggles due to switch bounce.

### 8. Concepts Covered

- STM32 GPIO input configuration.
- GPIO output control.
- Push-button interfacing.
- Event-based programming.
- Switch bounce.
- Software debouncing.
- Button press and release detection.
- State toggling.
- Input-state verification.
- Embedded C programming.

### 9. Result

Successfully implemented event-based LED control using the STM32 microcontroller.

A software debouncing mechanism was introduced to eliminate unwanted switch-bounce effects and ensure that each valid push-button press produces exactly one LED state toggle.

---

## Hardware Requirements

- STM32 Development Board (NUCLEO-F401RE)
- On-board or External Push Button
- On-board or External LED
- Connecting Wires (if required)
- USB Cable
- PC or Laptop

## Software Requirements

- STM32CubeIDE
- STM32 HAL Library (if HAL-based implementation is used)
- Embedded C

---

## Deliverables

- GPIO input configuration.
- GPIO output configuration.
- Push-button event detection.
- Software debouncing implementation.
- LED state toggling logic.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
