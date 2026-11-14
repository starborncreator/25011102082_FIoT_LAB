
# **README**

# IoT Sensor Node – LED Mode Control Using Push Button

## Problem Statement

Develop the first user-interface subsystem for an IoT sensor node using a microcontroller. The system consists of four LEDs connected to GPIO output pins and one push-button connected to a GPIO input pin.

The microcontroller responds to button presses by switching between four different LED operating modes.

## Hardware Requirements

- Microcontroller Development Board
- 4 LEDs
- 4 Current-limiting resistors
- 1 Push-button
- Connecting wires
- Power supply

## GPIO Configuration

| Component | GPIO Configuration |
|---|---|
| LED 1 | GPIO Output |
| LED 2 | GPIO Output |
| LED 3 | GPIO Output |
| LED 4 | GPIO Output |
| Push Button | GPIO Input |

*Note: Actual GPIO port and pin numbers depend on the microcontroller development board.*

---

## TASK 1 – Running LED (Mode 1)

### Objective
To implement a running LED sequence in which one LED turns ON at a time in a predefined order.

### Working Principle

Initially, all four LEDs remain OFF. When the push-button is pressed for the first time, the system enters Mode 1.

The LEDs turn ON sequentially in the following order:

LED1 → LED2 → LED3 → LED4 → LED1 → ...

Only one LED remains ON at a time. A software delay is introduced between successive LED transitions to create a running effect.

### Expected Output

| LED 1 | LED 2 | LED 3 | LED 4 |
|---|---|---|---|
| 1 | 0 | 0 | 0 |
| 0 | 1 | 0 | 0 |
| 0 | 0 | 1 | 0 |
| 0 | 0 | 0 | 1 |
| Repeat | | | |

---

## TASK 2 – Binary Counter (Mode 2)

### Objective
To display a 4-bit binary counting sequence using four LEDs.

### Working Principle

When the push-button is pressed to enter Mode 2, the four LEDs represent a 4-bit binary number.

Each LED represents one binary bit. The LEDs display values from 0000 to 1111 in ascending order.

After reaching 1111, the counter resets to 0000 and repeats continuously.

### Expected Output

```text
0000
0001
0010
0011
0100
0101
0110
0111
1000
1001
1010
1011
1100
1101
1110
1111
0000
...
```

---

## TASK 3 – Alternating LED Pattern (Mode 3)

### Objective
To generate an alternating LED pattern using four LEDs.

### Working Principle

When the push-button is pressed to enter Mode 3, the LEDs display alternating binary patterns.

The two patterns alternate continuously:

- First pattern: 1010
- Second pattern: 0101

This creates an alternating ON/OFF pattern across the four LEDs.

### Expected Output

```text
1010
0101
1010
0101
...
```

---

## TASK 4 – All LED Flash (Mode 4)

### Objective
To blink all four LEDs simultaneously.

### Working Principle

When the push-button is pressed to enter Mode 4, all four LEDs turn ON simultaneously and then turn OFF simultaneously.

The sequence repeats continuously with a software-generated delay.

### Expected Output

```text
1111
0000
1111
0000
...
```

---

## Button Press and Mode Selection Logic

The push-button acts as the mode selection input.

The system begins with all LEDs OFF. Each valid button press switches the system to the next operating mode.

| Button Press | Operating Mode |
|---|---|
| Initial State | All LEDs OFF |
| 1st Press | Mode 1 – Running LED |
| 2nd Press | Mode 2 – Binary Counter |
| 3rd Press | Mode 3 – Alternating Pattern |
| 4th Press | Mode 4 – All LED Flash |
| 5th Press | Mode 1 – Running LED |

The mode selection follows a cyclic sequence.

### Implementation Logic

1. Configure four GPIO pins as outputs.
2. Configure the push-button GPIO pin as an input.
3. Initialize all four LEDs to OFF.
4. Continuously monitor the push-button input.
5. Detect a valid button press event.
6. Increment the mode variable.
7. Reset the mode variable after Mode 4 to return to Mode 1.
8. Execute the corresponding LED operating pattern based on the selected mode.
9. Repeat continuously.

### Important Considerations

- Detect button press events rather than continuously checking the pressed state.
- Implement suitable switch debouncing to avoid multiple mode changes from a single physical press.
- Ensure that changing modes interrupts the previous LED pattern.
- Initialize all LEDs to OFF before starting a new mode.

---

## Concepts Covered

- GPIO input and output configuration.
- Push-button interfacing.
- LED interfacing with microcontrollers.
- Button press event detection.
- Switch debouncing.
- State-based programming.
- Binary counting and bit manipulation.
- Sequential and alternating LED patterns.
- Software delay generation.
- Infinite loop execution.

---

## Expected Overall Result

Successfully implement a four-mode LED control system using a push-button and four GPIO-connected LEDs.

The system should switch cyclically between running LED, binary counter, alternating LED pattern, and all LED flash modes based on successive button presses.

---

## Deliverables

- Complete source code.
- Hardware connection details.
- README documentation.
- GitHub repository containing the implementation.
