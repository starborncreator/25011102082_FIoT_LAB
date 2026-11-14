
# **README**

# STM32 – Wemos UART Communication

## Experiment Details

**Experiment:** Establish STM32 ↔ Wemos UART Communication

**Microcontroller:** STM32

**Wi-Fi Module:** Wemos D1 Mini (ESP8266)

**Communication Interface:** UART

**Development Environment:** STM32CubeIDE

**Serial Terminal:** PuTTY / Tera Term

---

## TASK 9A – Establish STM32 ↔ Wemos UART Communication

### 1. Objective

To establish UART communication between an STM32 microcontroller and a Wemos D1 Mini (ESP8266) module.

Before implementing Wi-Fi functionality, the experiment verifies that both boards can successfully transmit and receive serial data.

The STM32 sends an AT command to the Wemos module and receives its response through UART. The received response is then transmitted to the PC terminal for verification.

### 2. Hardware Requirements

- STM32 Development Board
- Wemos D1 Mini (ESP8266)
- USB-to-TTL Serial Interface (if required for PC debugging)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

---

### 3. Hardware Connections

The STM32 and Wemos communicate through UART using cross-connected TX and RX pins.

| Wemos D1 Mini Pin | STM32 Pin | Description |
|---|---|---|
| TX | RX (e.g., PA3 / USART2_RX) | Data from Wemos to STM32 |
| RX | TX (e.g., PA2 / USART2_TX) | Data from STM32 to Wemos |
| GND | GND | Common Ground Reference |
| 5V / 3.3V | Appropriate Power Source | Power Supply |

**Important:**
- Connect the TX pin of Wemos to the RX pin of STM32.
- Connect the RX pin of Wemos to the TX pin of STM32.
- Both boards must share a common ground.
- Ensure that the power supply and UART logic voltage levels are compatible.

### 4. Working Principle

UART communication is established between the STM32 microcontroller and the Wemos D1 Mini.

The STM32 acts as the command transmitter, while the Wemos receives the command and processes it using its AT firmware.

The Wemos sends its response back to the STM32 through UART.

The STM32 receives the response and forwards it to the PC terminal through another UART interface.

### Communication Flow

```text
          STM32
            |
            | UART TX
            v
          Wemos
            |
            | UART TX
            v
          STM32
            |
            | UART to PC
            v
       PuTTY / Tera Term
```

---

### 5. AT Command Communication

#### Objective

To transmit AT commands from the STM32 to the Wemos and receive the corresponding responses.

#### Working Principle

The STM32 transmits the AT command followed by carriage return and line feed (CR/LF).

The Wemos receives the command, processes it using its AT firmware, and sends the response back to the STM32.

The STM32 receives the response and displays it on the PC terminal.

#### Command to Be Transmitted

```text
AT\r\n
```

The command is used to verify whether the Wemos responds to AT commands.

#### Expected Communication

**Step 1 – STM32 to Wemos**

```text
AT
```

**Step 2 – Wemos to STM32**

```text
OK
```

**Step 3 – STM32 to PC Terminal**

```text
OK
```

---

### 6. UART Configuration

Configure the UART peripherals of the STM32 for communication with the Wemos and PC terminal.

| Parameter | Configuration |
|---|---|
| Communication | UART |
| STM32 UART | Selected UART peripheral |
| Wemos Interface | UART |
| Baud Rate | According to Wemos AT firmware configuration |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |

The STM32 uses one UART interface to communicate with the Wemos and another UART interface to communicate with the PC terminal.

---

### 7. Implementation Steps

1. Identify the UART TX and RX pins of the STM32.
2. Identify the UART TX and RX pins of the Wemos D1 Mini.
3. Establish the hardware connections between both boards.
4. Connect the common ground.
5. Configure the STM32 UART peripheral in STM32CubeIDE.
6. Configure the UART communication parameters.
7. Initialize the UART peripherals.
8. Transmit the AT command from STM32 to Wemos.
9. Append CR/LF to the transmitted command.
10. Receive the Wemos response through the STM32 UART.
11. Forward the received response to the PC terminal.
12. Verify the response using PuTTY or Tera Term.

---

### 8. Expected Output

When the STM32 transmits the AT command, the Wemos should respond with OK.

**Expected Communication:**

```text
STM32 → Wemos

AT\r\n


Wemos → STM32

OK


STM32 → PC Terminal

OK
```

The successful reception of the OK response confirms UART communication between the STM32 and Wemos.

---

### 9. PC Terminal Verification

Use PuTTY or Tera Term to observe the response received from the Wemos.

The terminal should display:

```text
OK
```

This verifies that:
- The STM32 successfully transmitted the AT command.
- The Wemos received and processed the command.
- The Wemos transmitted its response.
- The STM32 successfully received and forwarded the response to the PC.

---

### 10. Concepts Covered

- STM32 UART configuration.
- ESP8266 UART communication.
- UART TX and RX interfacing.
- Serial communication between microcontrollers.
- Cross-connection of TX and RX pins.
- AT command communication.
- CR/LF command termination.
- UART data transmission and reception.
- Multiple UART peripheral configuration.
- Serial debugging using PuTTY / Tera Term.
- Embedded communication protocols.

---

### 11. Expected Results

1. Successfully establish UART communication between STM32 and Wemos D1 Mini.
2. Configure the STM32 UART peripheral.
3. Transmit AT commands from STM32 to Wemos.
4. Receive the Wemos response through STM32.
5. Forward the response to the PC terminal.
6. Verify successful communication through the expected OK response.

---

### 12. Result

Successfully established UART communication between the STM32 microcontroller and Wemos D1 Mini (ESP8266).

Transmitted the AT command from STM32 to Wemos, received the corresponding OK response, and displayed the response on the PC terminal using PuTTY / Tera Term.

---

## Software Requirements

- STM32CubeIDE
- STM32 HAL Library
- Keil µVision (if used for development)
- PuTTY / Tera Term

## Hardware Requirements

- STM32 Development Board
- Wemos D1 Mini (ESP8266)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

---

## Deliverables

- STM32 UART configuration.
- Wemos UART communication implementation.
- AT command transmission code.
- UART response reception code.
- PC terminal output.
- Hardware connection details.
- README documentation.
- GitHub repository containing the implementation.
