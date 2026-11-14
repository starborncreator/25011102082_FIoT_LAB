
# **README**

# STM32 – Connect Wemos ESP8266 to Wi-Fi

## Experiment Details

**Experiment:** Connect Wemos ESP8266 to Wi-Fi Using AT Commands

**Microcontroller:** STM32F410RB

**Wi-Fi Module:** Wemos D1 Mini (ESP8266)

**Communication Interface:** UART

**Development Environment:** STM32CubeIDE / Keil µVision

**Serial Terminal:** PuTTY

**Wi-Fi Mode:** Station Mode

---

## TASK 10C – Connect Wemos to Wi-Fi

### 1. Objective

To develop STM32 firmware that configures the Wemos ESP8266 module as a Wi-Fi station and connects it to a university or local Wi-Fi network using AT commands.

The STM32 communicates with the Wemos through UART, sends AT commands, receives responses, and forwards the received characters to the PC terminal for verification.

### 2. Working Principle

The STM32 acts as the controller, while the Wemos ESP8266 operates as a Wi-Fi station.

The STM32 sends AT commands to configure the ESP8266 and establish a connection with the selected Wi-Fi access point.

The Wemos processes each command and returns its response through UART.

The STM32 receives the response character by character and forwards it to the PC terminal.

The process involves:

1. Initialize UART communication.
2. Send the basic AT command.
3. Verify the Wemos response.
4. Configure Wi-Fi station mode.
5. Connect to the Wi-Fi access point.
6. Wait for the connection response.
7. Query network information.
8. Display the connection status and IP address on the PC terminal.

---

### 3. Hardware Requirements

- STM32F410RB Development Board
- Wemos D1 Mini (ESP8266)
- USB-to-TTL Converter (if required)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

### 4. Hardware Connections

| Wemos D1 Mini | STM32F410RB | Description |
|---|---|---|
| TX | UART RX | Data from Wemos to STM32 |
| RX | UART TX | Data from STM32 to Wemos |
| GND | GND | Common Ground |
| 3.3V | Appropriate 3.3V Supply | Power Supply |

**Connection Notes:**
- Connect Wemos TX to STM32 RX.
- Connect Wemos RX to STM32 TX.
- Ensure both boards share a common ground.
- Ensure UART logic levels are compatible.
- Provide a stable power supply for the ESP8266.

---

### 5. UART Communication

The STM32 uses UART to communicate with the Wemos ESP8266.

The UART configuration must match the baud rate configured in the ESP8266 AT firmware.

| Parameter | Configuration |
|---|---|
| Communication | UART |
| Data Bits | 8 |
| Stop Bits | 1 |
| Parity | None |
| Flow Control | None |
| Baud Rate | As configured in ESP8266 AT firmware |

The STM32 also forwards the received UART characters to the PC terminal through a separate UART interface.

### 6. AT Command Execution

The following AT commands are used to configure the ESP8266 and connect it to Wi-Fi.

#### 6.1 Check Modem Response

**Command:**

```text
AT
```

**Purpose:**

To verify UART communication between the STM32 and Wemos.

**Expected Response:**

```text
OK
```

#### 6.2 Configure Wi-Fi Station Mode

**Command:**

```text
AT+CWMODE=1
```

**Purpose:**

To configure the ESP8266 as a Wi-Fi station so that it can connect to an existing wireless network.

**Expected Response:**

```text
OK
```

#### 6.3 Connect to Wi-Fi Access Point

**Command Format:**

```text
AT+CWJAP="SSID","PASSWORD"
```

**Example:**

```text
AT+CWJAP="MyWiFi","password"
```

**Purpose:**

- Specify the Wi-Fi network name.
- Provide the network password.
- Establish a connection with the selected access point.

**Expected Response:**

```text
WIFI CONNECTED
WIFI GOT IP
OK
```

#### 6.4 Query Network Information

**Command:**

```text
AT+CIFSR
```

**Purpose:**

To retrieve the IP address assigned to the ESP8266 after successfully connecting to the Wi-Fi network.

**Expected Response:**

The ESP8266 returns its assigned station IP address followed by:

```text
OK
```

---

### 7. STM32 Firmware Implementation

The STM32 firmware is responsible for transmitting AT commands and receiving responses from the Wemos.

#### Implementation Steps

1. Configure the STM32 UART peripheral.
2. Initialize UART communication with the Wemos.
3. Initialize the UART interface used for PC terminal communication.
4. Transmit the `AT` command followed by CR/LF.
5. Receive the Wemos response through UART RX.
6. Forward the received characters to the PC terminal.
7. Transmit `AT+CWMODE=1` to configure station mode.
8. Receive and verify the response.
9. Transmit the `AT+CWJAP` command with the Wi-Fi SSID and password.
10. Wait for the Wi-Fi connection response.
11. Receive the `WIFI CONNECTED`, `WIFI GOT IP`, and `OK` responses.
12. Transmit `AT+CIFSR` to obtain network information.
13. Display the assigned IP address on the PC terminal.

### 8. Communication Flow

```text
             STM32
               |
               |
          Send AT Command
               |
               v
             Wemos
               |
               |
         Process Command
               |
               v
         Generate Response
               |
               |
               v
         STM32 UART RX
               |
               |
       Receive Characters
               |
               v
       Forward to PC UART
               |
               v
          PuTTY Terminal
```

---

### 9. Expected Terminal Output

The STM32 should display the following information on the PC terminal.

**Initial Modem Verification:**

```text
STM32-WiFi MODEM TEST

>> AT
<< OK
```

**Configure Station Mode:**

```text
>> AT+CWMODE=1
<< OK
```

**Connect to Wi-Fi:**

```text
>> AT+CWJAP="MyWiFi","password"

<< WIFI CONNECTED
<< WIFI GOT IP
<< OK
```

**Network Information:**

```text
>> AT+CIFSR

<< +CIFSR:STAIP,"xxx.xxx.xxx.xxx"
<< OK
```

*The displayed IP address depends on the connected Wi-Fi network.*

---

### 10. Verification

After executing the AT commands, the STM32 should report the following information through the PC terminal.

| Parameter | Expected Value |
|---|---|
| Wi-Fi Mode | STATION |
| Wi-Fi Status | CONNECTED |
| IP Address | Assigned Network IP |

Successful verification confirms that:

- UART communication between STM32 and Wemos is working.
- The ESP8266 is configured in station mode.
- The Wemos successfully connects to the selected Wi-Fi network.
- The ESP8266 obtains an IP address.
- The STM32 successfully receives and forwards the Wemos responses.

---

### 11. Concepts Covered

- STM32 UART configuration.
- ESP8266 AT command interface.
- UART data transmission and reception.
- Character-by-character UART reception.
- UART response forwarding.
- Wi-Fi station mode configuration.
- Access point connection.
- Wi-Fi authentication.
- IP address retrieval.
- Serial debugging using PuTTY.
- Embedded Wi-Fi communication.

---

### 12. Expected Results

1. Successfully establish UART communication between STM32 and Wemos.
2. Verify modem communication using the AT command.
3. Configure the ESP8266 in Wi-Fi station mode.
4. Connect the Wemos to the university or local Wi-Fi network.
5. Receive Wi-Fi connection status messages.
6. Retrieve the assigned IP address.
7. Display all responses on the PC terminal.

---

### 13. Result

Successfully configured the Wemos ESP8266 as a Wi-Fi station using AT commands transmitted from the STM32F410RB.

Established a connection with the selected Wi-Fi access point, received the connection status and IP address through UART, and forwarded the responses to the PC terminal for verification.

---

## Software Requirements

- STM32CubeIDE
- Keil µVision (if used)
- STM32 HAL Library
- ESP8266 AT Firmware
- PuTTY Serial Terminal
- Embedded C

## Hardware Requirements

- STM32F410RB Development Board
- Wemos D1 Mini (ESP8266)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

---

## Deliverables

- STM32 UART configuration.
- ESP8266 AT command implementation.
- Wi-Fi station mode configuration.
- Wi-Fi access point connection.
- Network status verification.
- IP address retrieval.
- PC terminal output.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
