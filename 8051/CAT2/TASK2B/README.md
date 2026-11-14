
# **README**

# Bare-Metal Programming – LED Blinking

## Experiments

This repository contains the implementation of hardware bring-up and bare-metal LED blinking using a microcontroller development board. The experiment focuses on understanding the target hardware, configuring GPIO registers through direct register access, and implementing software-based delay functionality without relying on high-level hardware abstraction libraries.

---

## **TASK 1 – Hardware Board Bring-Up**

### Objective
To identify the microcontroller development board components, establish communication with the target microcontroller, and verify the hardware connections and power supply.

### Activities Performed

1. **Hardware Identification**
   - Identify the microcontroller and its CPU core.
   - Identify the debugger/programmer interface.
   - Identify the power source and operating voltage.
   - Locate the onboard user LED and its corresponding GPIO pin.

2. **Power Supply Verification**
   - Use a digital multimeter to verify the board's power rails.
   - Check the operating voltage and ensure proper power supply connections.

3. **GPIO Identification**
   - Refer to the microcontroller datasheet and board schematic.
   - Identify the GPIO port and pin connected to the onboard LED.
   - Determine whether the LED operates in active-high or active-low configuration.

4. **Communication Establishment**
   - Connect the host computer to the target microcontroller using the debugger/programmer.
   - Verify successful device detection and communication.

### Hardware Bring-Up Sheet

| Parameter | Student Entry |
|---|---|
| MCU | |
| CPU Core | |
| Operating Voltage | |
| Debug Interface | |
| LED GPIO Port | |
| LED GPIO Pin | |
| LED Active State | |
| LED Frequency (Hz) | |

---

## **TASK 2 – Bare-Metal LED Blink**

### Objective
To implement LED blinking at approximately 1 Hz using direct register access without using high-level GPIO libraries.

### Working Principle

The microcontroller GPIO pin connected to the onboard LED is configured as an output by directly modifying the corresponding hardware registers.

A software delay mechanism is implemented using nested loops to introduce a time interval between LED state transitions.

The LED is continuously switched between ON and OFF states, producing a blinking effect at approximately 1 Hz.

### Implementation Steps

1. Identify the GPIO port and pin connected to the onboard LED.
2. Enable the GPIO peripheral clock.
3. Configure the LED GPIO pin as an output using direct register access.
4. Implement a software delay using simple loops.
5. Set the GPIO output to turn ON the LED.
6. Execute the delay function.
7. Toggle the GPIO output to turn OFF the LED.
8. Execute the delay function again.
9. Repeat the process continuously.

### Expected Output

- The onboard LED turns ON.
- The LED remains ON for a specific time interval.
- The LED turns OFF after the delay.
- The process repeats continuously.
- The LED blinks at approximately 1 Hz.

---

## **TASK 3 – Custom Delay Library Function**

### Objective
To develop a customized library function for generating software delays and reuse it in the bare-metal LED blinking application.

### Implementation

- Create a separate header file (`delay.h`) containing the delay function declaration.
- Implement the delay functionality in a source file (`delay.c`).
- Include the custom delay library in the main application.
- Call the delay function whenever a time interval is required between LED state transitions.

### Benefits

- Promotes code reusability.
- Separates delay functionality from application logic.
- Improves code organization and maintainability.
- Allows the delay function to be reused in other embedded applications.

---

## **Hardware and Software Requirements**

### Hardware
- Microcontroller Development Board
- USB Cable
- Debugger/Programmer
- Digital Multimeter
- Host Computer

### Software
- Embedded C Compiler
- IDE / Development Environment
- Microcontroller Datasheet
- Board Schematic

---

## **Learning Outcomes**

- Understanding microcontroller hardware architecture and board bring-up.
- Identifying GPIO ports and pins using datasheets and schematics.
- Verifying power supply connections using a digital multimeter.
- Establishing communication between the host computer and target microcontroller.
- Configuring GPIO registers using direct register access.
- Implementing software-based delays using loops.
- Developing reusable custom library functions.
- Understanding bare-metal embedded programming without high-level hardware abstraction libraries.

---

## **Result**

Successfully performed hardware board bring-up, implemented bare-metal LED blinking using direct register access, and developed a custom library function for software delay generation.
