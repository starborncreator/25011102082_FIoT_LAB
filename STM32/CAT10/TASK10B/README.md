
# **README**

# ESP8266 – AT Command Interface Exploration

## Experiment Details

**Experiment:** Explore the ESP8266 AT Command Interface

**Microcontroller:** STM32

**Wi-Fi Module:** Wemos D1 Mini (ESP8266)

**Communication Interface:** UART

**Development Environment:** STM32CubeIDE

**Serial Terminal:** PuTTY / Arduino IDE Serial Monitor

**Firmware:** ESP8266 AT Firmware

---

## TASK 10B – Explore the ESP8266 AT Command Interface

### 1. Objective

To explore the ESP8266 AT command interface and understand how to configure and control the Wi-Fi module using AT commands.

The experiment involves investigating different AT commands to establish Wi-Fi connectivity, obtain network information, establish TCP connections, and transmit application data.

The commands are transmitted to the ESP8266 through UART, and the corresponding responses are received and displayed on the PC terminal.

### 2. Working Principle

The ESP8266 supports AT commands that allow users to control its Wi-Fi and network functionalities through a serial interface.

The STM32 communicates with the Wemos D1 Mini using UART. AT commands are transmitted from the STM32 or PC terminal, and the ESP8266 processes them and returns appropriate responses.

Each AT command is terminated with carriage return and line feed (CR/LF).

The returned response is used to verify whether the requested operation was successful.

### 3. AT Command Investigation

The following commands are investigated as part of the experiment.

| Requirement | AT Command | Purpose |
|---|---|---|
| Check modem response | `AT` | Verify communication with ESP8266 |
| Check firmware/version | `AT+GMR` | Display firmware and version information |
| Set Wi-Fi station mode | `AT+CWMODE=1` | Configure ESP8266 as a Wi-Fi station |
| Scan available networks | `AT+CWLAP` | Search for available Wi-Fi networks |
| Connect to an AP | `AT+CWJAP` | Connect to a Wi-Fi access point |
| Obtain network information | `AT+CIFSR` | Display assigned IP addresses |
| Establish TCP connection | `AT+CIPSTART` | Establish a TCP connection with a server |
| Send application data | `AT+CIPSEND` | Transmit data through the established connection |

---

## 4. Command Description and Usage

### 4.1 Check Modem Response – AT

**Objective:** To verify whether the ESP8266 is responding to AT commands.

**Command:**

```text
AT
```

**Expected Response:**

```text
OK
```

A successful OK response confirms that UART communication with the ESP8266 is working.

### 4.2 Check Firmware Version – AT+GMR

**Objective:** To retrieve the firmware and version information of the ESP8266.

**Command:**

```text
AT+GMR
```

**Purpose:**
- Identify the installed AT firmware.
- Check firmware version.
- Verify firmware compatibility.

**Expected Response:**

Firmware and SDK version information followed by:

```text
OK
```

### 4.3 Set Wi-Fi Station Mode – AT+CWMODE

**Objective:** To configure the ESP8266 to operate in Wi-Fi station mode.

**Command:**

```text
AT+CWMODE=1
```

**Purpose:**

- Configure the ESP8266 as a Wi-Fi station.
- Allow the module to connect to an existing Wi-Fi access point.

**Expected Response:**

```text
OK
```

### 4.4 Scan Available Networks – AT+CWLAP

**Objective:** To identify the available Wi-Fi networks in the surrounding area.

**Command:**

```text
AT+CWLAP
```

**Purpose:**
- Scan nearby Wi-Fi access points.
- Identify network SSIDs.
- Obtain signal strength information.
- Identify available security modes.

**Expected Response:**

A list of detected Wi-Fi networks followed by:

```text
OK
```

### 4.5 Connect to an Access Point – AT+CWJAP

**Objective:** To connect the ESP8266 to a Wi-Fi network.

**Command Format:**

```text
AT+CWJAP="SSID","PASSWORD"
```

**Example:**

```text
AT+CWJAP="MyWiFi","mypassword"
```

**Purpose:**
- Connect to the specified Wi-Fi network.
- Authenticate using the network password.
- Establish wireless connectivity.

**Expected Response:**

```text
WIFI CONNECTED
WIFI GOT IP
OK
```

*The actual response messages may vary depending on firmware version.*

### 4.6 Obtain Network Information – AT+CIFSR

**Objective:** To retrieve the IP address assigned to the ESP8266.

**Command:**

```text
AT+CIFSR
```

**Purpose:**
- Retrieve the station IP address.
- Verify successful network configuration.
- Obtain network interface information.

**Expected Response:**

The ESP8266 returns its assigned IP address followed by:

```text
OK
```

### 4.7 Establish TCP Connection – AT+CIPSTART

**Objective:** To establish a TCP connection between the ESP8266 and a remote server.

**Command Format:**

```text
AT+CIPSTART="TCP","SERVER_IP",PORT
```

**Example:**

```text
AT+CIPSTART="TCP","192.168.1.100",8080
```

**Purpose:**
- Specify the communication protocol.
- Identify the destination server.
- Specify the destination port.
- Establish a TCP connection.

**Expected Response:**

```text
CONNECT
OK
```

*The server IP address and port must correspond to an accessible TCP server.*

### 4.8 Send Application Data – AT+CIPSEND

**Objective:** To transmit application data through an established TCP connection.

**Command Format:**

```text
AT+CIPSEND=length
```

**Example:**

```text
AT+CIPSEND=5
```

After receiving the `>` prompt, transmit the required data.

```text
Hello
```

**Purpose:**
- Specify the number of bytes to transmit.
- Send application data through the TCP connection.
- Verify successful data transmission.

**Expected Response:**

```text
>
SEND OK
```

---

## 5. Implementation Procedure

1. Establish UART communication between STM32 and Wemos D1 Mini.
2. Verify the ESP8266 response using the `AT` command.
3. Retrieve firmware information using `AT+GMR`.
4. Configure Wi-Fi station mode using `AT+CWMODE=1`.
5. Scan available networks using `AT+CWLAP`.
6. Connect to a Wi-Fi access point using `AT+CWJAP`.
7. Retrieve the assigned IP address using `AT+CIFSR`.
8. Establish a TCP connection using `AT+CIPSTART`.
9. Transmit application data using `AT+CIPSEND`.
10. Observe and verify the responses through the PC terminal.

---

## 6. Expected Command Execution Sequence

The following sequence demonstrates the typical order of AT command execution.

```text
AT
 |
 v
AT+GMR
 |
 v
AT+CWMODE=1
 |
 v
AT+CWLAP
 |
 v
AT+CWJAP="SSID","PASSWORD"
 |
 v
AT+CIFSR
 |
 v
AT+CIPSTART="TCP","SERVER_IP",PORT
 |
 v
AT+CIPSEND=5
 |
 v
Hello
```

Each command should be executed after verifying the response to the previous command.

---

## 7. Expected Results

| Test | Command | Expected Result |
|---|---|---|
| Modem verification | AT | OK |
| Firmware verification | AT+GMR | Firmware information |
| Station mode configuration | AT+CWMODE=1 | OK |
| Network scanning | AT+CWLAP | Available networks |
| Wi-Fi connection | AT+CWJAP | Connected successfully |
| IP retrieval | AT+CIFSR | Assigned IP address |
| TCP connection | AT+CIPSTART | Connection established |
| Data transmission | AT+CIPSEND | SEND OK |

---

## 8. Concepts Covered

- ESP8266 AT command interface.
- UART communication.
- AT command transmission and reception.
- ESP8266 firmware identification.
- Wi-Fi station mode configuration.
- Wireless network scanning.
- Wi-Fi access point connection.
- IP address retrieval.
- TCP connection establishment.
- Application data transmission.
- Serial debugging.
- Network communication fundamentals.

---

## 9. Result

Successfully explored the ESP8266 AT command interface and investigated commands for modem verification, firmware identification, Wi-Fi configuration, network scanning, access point connection, IP address retrieval, TCP connection establishment, and application data transmission.

Verified the ESP8266 responses through UART communication using a PC serial terminal.

---

## Hardware Requirements

- STM32 Development Board
- Wemos D1 Mini (ESP8266)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

## Software Requirements

- STM32CubeIDE
- ESP8266 AT Firmware
- PuTTY / Arduino IDE Serial Monitor
- Embedded C

---

## Deliverables

- AT command investigation table.
- ESP8266 AT command execution.
- UART communication implementation.
- Command response observations.
- Wi-Fi connectivity verification.
- TCP connection verification.
- README documentation.
- GitHub repository containing the implementation.
