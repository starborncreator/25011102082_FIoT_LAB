
# **README**

# 8051 – UART Driver and Serial Debugging

## Experiment Details

**Experiment:** Interrupt-Driven UART Driver and Serial Communication

**Microcontroller:** 8051 (AT89S52)

**Development Environment:** Keil µVision

**Communication Interface:** UART

**Serial Terminal:** PuTTY

**Baud Rate:** 9600

**Communication Format:** 9600-8-N-1

---

## 1. Problem Statement

Develop a basic interrupt-driven UART driver for the 8051 microcontroller and establish serial communication with a PC terminal using a USB-to-TTL serial interface.

The UART is configured for 9600-8-N-1 communication to demonstrate character transmission and reception using PuTTY.

The implementation involves:

- UART initialization and configuration.
- UART character transmission.
- UART character reception.
- Interrupt-driven UART communication.
- Implementation of an RX ring buffer.
- Serial debugging through a PC terminal.

---

# TASK A – UART Initialization and Character Transmission

## 1. Objective

To configure the 8051 UART for asynchronous serial communication and continuously transmit a predefined message to a PC terminal using a USB-to-TTL converter.

## 2. UART Configuration

The 8051 UART is configured with the following parameters:

| Parameter | Configuration |
|---|---|
| UART Mode | Mode 1 (8-bit UART) |
| Operation | Asynchronous |
| Baud Rate | 9600 |
| Data Bits | 8 bits |
| Stop Bits | 1 |
| Parity | None |
| Communication | Full Duplex |

### Communication Format: 9600-8-N-1

- **9600:** Baud rate of 9600 bits per second.
- **8:** 8 data bits per character.
- **N:** No parity bit.
- **1:** One stop bit.

## 3. Working Principle

The 8051 UART is configured in Mode 1 for 8-bit asynchronous serial communication.

The microcontroller transmits data through its TXD pin. The transmitted serial data is received by the USB-to-TTL converter, which transfers the data to the PC through a USB connection.

PuTTY is used as the serial terminal to display the received characters.

The program continuously transmits the message:

**Hello from 8051**

### Communication Flow

```text
8051 Development Board
          |
          | TXD
          v
    USB-to-TTL Converter
          |
          | USB
          v
         PC
          |
          v
        PuTTY
          |
          v
  Hello from 8051
```

## 4. Hardware Connections

| 8051 Development Board | USB-to-TTL Converter |
|---|---|
| TXD (P3.1) | RXD |
| GND | GND |

The USB-to-TTL converter is connected to the PC through a USB port.

**Note:** The TXD output of the 8051 must be connected to the RXD input of the USB-to-TTL converter.

## 5. Implementation Steps

1. Configure the UART in Mode 1 (8-bit UART).
2. Configure the Timer 1 baud-rate generator.
3. Set the baud rate to 9600.
4. Configure serial communication for 8 data bits, no parity and 1 stop bit.
5. Enable the UART transmitter.
6. Implement a UART transmission function.
7. Load the character into the serial transmit buffer using SBUF.
8. Wait for the transmit interrupt flag (TI).
9. Clear the transmit flag.
10. Continuously transmit the message "Hello from 8051".

## 6. Expected Output

The message should appear continuously in the PuTTY terminal.

```text
Hello from 8051
Hello from 8051
Hello from 8051
Hello from 8051
...
```

---

# TASK B – UART Character Reception

## 1. Objective

To implement UART character reception and receive data transmitted from a PC terminal using the 8051 microcontroller.

## 2. Working Principle

The UART receiver continuously monitors incoming serial data through the RXD pin.

When a character is received:

1. The RI flag indicates that reception is complete.
2. The received character is read from the SBUF register.
3. The RI flag is cleared.
4. The received character can be processed or transmitted back to the PC.

This enables bidirectional serial communication between the microcontroller and the PC terminal.

## 3. Expected Behaviour

- Type a character in PuTTY.
- The character is transmitted to the 8051 through the USB-to-TTL converter.
- The 8051 receives the character through its RXD pin.
- The received character can be processed or echoed back to PuTTY.

---

# TASK C – Interrupt-Driven UART Driver

## 1. Objective

To implement an interrupt-driven UART driver that handles character transmission and reception without continuously polling the UART status flags.

## 2. Working Principle

The UART interrupt mechanism allows the microcontroller to respond automatically when a character is transmitted or received.

The serial interrupt is triggered when the transmit or receive flag is set.

The UART Interrupt Service Routine (ISR) checks the interrupt flags and performs the corresponding operation.

### Interrupt Handling

**Transmission:**
- Check the TI flag.
- Identify transmission completion.
- Clear the TI flag.
- Handle the next character if required.

**Reception:**
- Check the RI flag.
- Read the received character from SBUF.
- Clear the RI flag.
- Store the character for further processing.

## 3. Implementation Steps

1. Enable serial interrupts using ES.
2. Enable global interrupts using EA.
3. Configure the UART interrupt service routine.
4. Check the RI and TI flags inside the ISR.
5. Handle received characters.
6. Handle transmission completion.
7. Ensure that received data is processed without blocking the main application.

---

# TASK D – Interrupt-Driven RX Ring Buffer

## 1. Objective

To implement a circular receive buffer for storing incoming UART characters using interrupt-driven reception.

## 2. Working Principle

An RX ring buffer is a circular memory structure used to temporarily store received UART characters.

Whenever a character arrives, the UART interrupt service routine reads the character from SBUF and stores it in the buffer.

The buffer uses two pointers:

- **Head:** Indicates the position where the next received character will be stored.
- **Tail:** Indicates the position from which the next character will be read.

After reaching the end of the buffer, the pointers wrap around to the beginning.

### Ring Buffer Operation

```text
       RX RING BUFFER

    +----+----+----+----+
    | H  |    |    | T  |
    +----+----+----+----+
       ^              |
       |              |
       +--------------+

H = Head Pointer
T = Tail Pointer
```

## 3. Implementation Steps

1. Declare a fixed-size character array for the RX buffer.
2. Initialize the head and tail pointers.
3. Receive characters through the UART interrupt.
4. Store each received character at the head position.
5. Increment the head pointer.
6. Wrap the head pointer to the beginning when it reaches the buffer limit.
7. Read received characters from the tail position in the main program.
8. Increment and wrap the tail pointer after reading.
9. Implement buffer-full detection to prevent overwriting unread data.

## 4. Advantages

- Prevents continuous polling of the UART receiver.
- Allows asynchronous data reception.
- Temporarily stores incoming characters.
- Separates UART reception from application processing.
- Improves communication efficiency.

---

# PuTTY Serial Terminal Configuration

Configure PuTTY with the following settings:

| Parameter | Value |
|---|---|
| Connection Type | Serial |
| Serial Line | Assigned COM Port |
| Speed | 9600 |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |

Select the correct COM port corresponding to the USB-to-TTL converter.

---

# Concepts Covered

- 8051 UART architecture.
- Asynchronous serial communication.
- UART Mode 1 configuration.
- Baud-rate generation using Timer 1.
- 9600-8-N-1 communication.
- Serial data transmission.
- Serial data reception.
- SBUF register operation.
- TI and RI flag handling.
- Interrupt-driven UART programming.
- UART Interrupt Service Routine.
- Circular buffer implementation.
- RX ring buffer management.
- USB-to-TTL interfacing.
- Serial debugging using PuTTY.

---

# Hardware Requirements

- 8051 Microcontroller (AT89S52)
- 8051 Development Board
- USB-to-TTL Serial Converter
- USB Cable
- Connecting Wires
- PC or Laptop

# Software Requirements

- Keil µVision IDE
- 8051 C Compiler
- PuTTY Serial Terminal
- Embedded C

---

# Expected Results

1. Successfully configure the 8051 UART for 9600-8-N-1 communication.
2. Establish serial communication between the 8051 and PC using a USB-to-TTL converter.
3. Continuously transmit "Hello from 8051" to PuTTY.
4. Receive characters from the PC terminal.
5. Implement interrupt-driven UART transmission and reception.
6. Implement an RX ring buffer to store incoming characters.
7. Verify serial communication through PuTTY.

---

# Result

Successfully implemented UART initialization, character transmission and reception using the 8051 microcontroller.

Established serial communication with a PC terminal through a USB-to-TTL interface and implemented interrupt-driven UART handling with an RX ring buffer.
