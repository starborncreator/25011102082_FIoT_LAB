
# **README**

# STM32 – String-Based Application Logic Using UART

## Experiment Details

**Experiment:** String-Based Application Logic

**Microcontroller:** STM32

**Development Board:** NUCLEO-F401RE

**Development Environment:** STM32CubeIDE

**Configuration Tool:** STM32CubeMX

**Programming Language:** Embedded C

**Communication Interface:** UART

**Serial Terminal:** PuTTY / Tera Term

**Driver:** STM32 HAL Library

---

## TASK 9B – String-Based Application Logic

### 1. Objective

To develop a UART-based command interface for an STM32 microcontroller that accepts string commands from a PC terminal and controls the onboard LED accordingly.

The application should identify the received command and execute the corresponding LED operation.

The system supports three commands:

- `LED ON` – Turns ON the onboard LED.
- `LED OFF` – Turns OFF the onboard LED.
- `LED TOGGLE` – Toggles the current LED state.

---

### 2. Working Principle

The STM32 communicates with the PC terminal through UART.

The user enters a command through the serial terminal, and the STM32 receives the transmitted string using its UART peripheral.

The received command is stored in a character buffer and compared against predefined command strings.

Based on the identified command, the STM32 performs the corresponding GPIO operation to control the onboard LED.

The command processing follows these steps:

1. Initialize UART communication.
2. Configure the onboard LED GPIO pin as an output.
3. Receive a string command from the PC terminal.
4. Store the received characters in a buffer.
5. Identify the complete command.
6. Compare the received string with predefined commands.
7. Execute the corresponding LED operation.
8. Continue waiting for the next command.

---

### 3. Supported UART Commands

The application must support the following commands:

#### 3.1 LED ON

**Command:**
```text
LED ON
```

**Operation:**

- Receive the command through UART.
- Identify the `LED ON` string.
- Set the LED GPIO output to HIGH.
- Turn ON the onboard LED.

**Expected Response:**
```text
LED turned ON
```

#### 3.2 LED OFF

**Command:**
```text
LED OFF
```

**Operation:**

- Receive the command through UART.
- Identify the `LED OFF` string.
- Set the LED GPIO output to LOW.
- Turn OFF the onboard LED.

**Expected Response:**
```text
LED turned OFF
```

#### 3.3 LED TOGGLE

**Command:**
```text
LED TOGGLE
```

**Operation:**

- Receive the command through UART.
- Identify the `LED TOGGLE` string.
- Reverse the current LED state.
- If the LED is ON, turn it OFF.
- If the LED is OFF, turn it ON.

**Expected Response:**
```text
LED toggled
```

---

### 4. UART String Reception

**Objective:** To receive complete command strings from the PC terminal.

**Working Principle:**

Unlike character-based communication, string-based communication requires the STM32 to collect multiple characters before processing a command.

The received characters are stored sequentially in a character buffer.

A suitable command termination condition, such as carriage return or newline, is used to identify the end of the command.

After receiving the complete string, the application processes the command.

**HAL Function Used:**

```c
HAL_UART_Receive()
```

The received characters are stored in a buffer for further processing.

---

### 5. Command Processing Logic

The received string is compared against the predefined commands.

| Received Command | GPIO Operation | Terminal Response |
|---|---|---|
| LED ON | Set LED HIGH | LED turned ON |
| LED OFF | Set LED LOW | LED turned OFF |
| LED TOGGLE | Reverse LED state | LED toggled |

The command comparison can be implemented using standard C string-handling functions.

**Example:**

```c
strcmp(command, "LED ON")
strcmp(command, "LED OFF")
strcmp(command, "LED TOGGLE")
```

---

### 6. Implementation Steps

1. Create or modify the existing STM32 project.
2. Configure the UART peripheral using STM32CubeMX.
3. Enable UART transmit and receive functionality.
4. Configure the onboard LED GPIO pin as an output.
5. Initialize the UART and GPIO peripherals.
6. Declare a character buffer for storing incoming commands.
7. Receive characters from the PC terminal.
8. Detect the command termination character.
9. Complete the received command string.
10. Compare the received string with predefined commands.
11. Execute the corresponding LED operation.
12. Transmit the appropriate confirmation message to the PC terminal.
13. Clear the buffer and wait for the next command.

---

### 7. Expected Terminal Output

**Example 1 – LED ON**

```text
> LED ON
LED turned ON
```

**Example 2 – LED OFF**

```text
> LED OFF
LED turned OFF
```

**Example 3 – LED TOGGLE**

```text
> LED TOGGLE
LED toggled
```

The LED should respond immediately to the received commands.

---

### 8. Communication Flow

```text
         PC TERMINAL
              |
              | UART TX
              v
          STM32 RX
              |
              v
       Receive String
              |
              v
        Store in Buffer
              |
              v
       Compare Command
              |
        +-----+------+
        |     |      |
        v     v      v
      LED ON LED OFF TOGGLE
        |     |      |
        v     v      v
       GPIO  GPIO   GPIO
       HIGH  LOW   TOGGLE
        |     |      |
        +-----+------+
              |
              v
       UART Response
              |
              v
         PC TERMINAL
```

---

### 9. Expected Results

1. Successfully establish UART communication between STM32 and PC.
2. Receive string commands through the serial terminal.
3. Store and process the received commands.
4. Identify the `LED ON` command and turn ON the onboard LED.
5. Identify the `LED OFF` command and turn OFF the onboard LED.
6. Identify the `LED TOGGLE` command and reverse the LED state.
7. Display the corresponding confirmation message on the PC terminal.
8. Successfully execute multiple commands sequentially.

---

### 10. Concepts Covered

- UART communication.
- STM32CubeMX UART configuration.
- STM32 HAL library.
- Character and string reception.
- UART transmit and receive functions.
- String handling in Embedded C.
- Character buffers.
- String comparison using `strcmp()`.
- Command parsing.
- GPIO output control.
- LED state management.
- Terminal-based command interfaces.
- Embedded application development.

---

### 11. Result

Successfully developed a UART-based command interface using the STM32 microcontroller.

Implemented string reception and command processing to control the onboard LED through the PC terminal.

The system successfully supports `LED ON`, `LED OFF`, and `LED TOGGLE` commands and provides corresponding confirmation messages through UART.

---

## Hardware Requirements

- STM32 Development Board (NUCLEO-F401RE)
- Onboard User LED
- USB Cable
- PC or Laptop

## Software Requirements

- STM32CubeIDE
- STM32CubeMX
- STM32 HAL Library
- PuTTY / Tera Term
- Embedded C

---

## Deliverables

- STM32 UART configuration.
- UART string reception implementation.
- Command buffer implementation.
- String comparison and command parsing.
- LED ON functionality.
- LED OFF functionality.
- LED TOGGLE functionality.
- UART response transmission.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
