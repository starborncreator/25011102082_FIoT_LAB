
# **README**

# STM32 – Short Press vs Long Press LED Control

## Experiment Details

**Experiment:** Short Press vs Long Press Detection

**Microcontroller:** STM32

**Development Board:** NUCLEO-F401RE

**Development Environment:** STM32CubeIDE

**Programming Language:** Embedded C

**Interface:** GPIO

---

## TASK 8C – Short Press vs Long Press

### 1. Objective

To modify the existing STM32 push-button application to distinguish between short and long button presses based on the duration for which the button remains pressed.

The application performs different LED operations depending on the detected button press duration.

A short press toggles the LED state, whereas a long press activates continuous LED blinking mode.

### 2. Working Principle

The push button is configured as a GPIO input, while the LED is configured as a GPIO output.

The STM32 continuously monitors the push-button state and measures the duration of each button press.

Based on the measured duration, the application classifies the input into two categories:

- **Short Press:** Button pressed for less than 1 second.
- **Long Press:** Button pressed for 1 second or more.

Different actions are performed depending on the detected press type.

### 3. Button Press Classification

| Press Type | Duration |
|---|---|
| Short Press | Less than 1 second |
| Long Press | Greater than or equal to 1 second |

### 4. Functional Requirements

The system must implement the following behaviour:

| User Action | System Response |
|---|---|
| Short Press | Toggle LED |
| Long Press | LED enters continuous blinking mode |
| Next Short Press | Stop blinking |
| Long Press Again | Return to blinking mode |

### 5. LED Operating Modes

#### 5.1 Short Press – LED Toggle

When the button is pressed for less than 1 second:

1. Detect the button press.
2. Measure the press duration.
3. Classify it as a short press.
4. Toggle the LED state.
5. Maintain the updated LED state until the next valid event.

#### 5.2 Long Press – Continuous Blinking

When the button is pressed for 1 second or more:

1. Detect the button press.
2. Measure the duration.
3. Classify it as a long press.
4. Activate continuous LED blinking mode.
5. Continue blinking at the configured interval.

#### 5.3 Next Short Press – Stop Blinking

When a short press is detected while blinking mode is active:

1. Detect the short press.
2. Stop continuous LED blinking.
3. Return the LED to its normal state-controlled operation.

#### 5.4 Long Press Again – Return to Blinking Mode

When another long press is detected:

1. Detect the long press.
2. Activate continuous blinking mode again.
3. Continue periodic LED ON and OFF transitions.

### 6. Implementation Steps

1. Configure the push-button GPIO pin as an input.
2. Configure the LED GPIO pin as an output.
3. Initialize the GPIO peripherals.
4. Continuously monitor the push-button state.
5. Detect the button press event.
6. Record the time at which the button is pressed.
7. Monitor the button until it is released.
8. Calculate the total button press duration.
9. Compare the duration against the 1-second threshold.
10. Classify the event as a short press or long press.
11. If a short press is detected, toggle the LED or stop blinking mode if active.
12. If a long press is detected, activate continuous blinking mode.
13. Generate LED blinking using the configured time interval.
14. Repeat the process continuously.

### 7. Expected Behaviour

The application should respond differently depending on the button press duration.

**Short Press:**
- Duration below 1 second.
- Toggles the LED state.

**Long Press:**
- Duration of 1 second or more.
- Activates continuous LED blinking.

**Subsequent Short Press:**
- Stops the continuous blinking mode.

**Subsequent Long Press:**
- Activates blinking mode again.

### 8. Concepts Covered

- STM32 GPIO input configuration.
- GPIO output control.
- Push-button interfacing.
- Button press and release detection.
- Short-press detection.
- Long-press detection.
- Press-duration measurement.
- Time-based event classification.
- LED state toggling.
- Continuous LED blinking.
- Software timing mechanisms.
- Event-based programming.
- Embedded C programming.

### 9. Expected Results

1. Successfully detect push-button press and release events.
2. Measure button press duration.
3. Identify short presses below 1 second.
4. Identify long presses of 1 second or more.
5. Toggle the LED for short presses.
6. Activate continuous blinking for long presses.
7. Stop blinking when the next short press is detected.
8. Reactivate blinking when another long press is detected.

### 10. Result

Successfully implemented short-press and long-press detection using the STM32 microcontroller.

The application measures button press duration and performs different LED operations based on the detected event. Short presses toggle the LED state, while long presses activate continuous blinking mode. Subsequent button presses control the blinking operation as specified.

---

## Hardware Requirements

- STM32 Development Board (NUCLEO-F401RE)
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

- GPIO input configuration.
- GPIO output configuration.
- Push-button detection implementation.
- Short-press detection logic.
- Long-press detection logic.
- Press-duration measurement.
- LED toggling implementation.
- Continuous blinking mode.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
