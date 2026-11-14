
# **README**

# STM32 – HTTP Request Using ESP8266 AT Commands

## Experiment Details

**Experiment:** HTTP Request Using AT Commands

**Microcontroller:** STM32F410RB

**Wi-Fi Module:** Wemos D1 Mini (ESP8266)

**Communication Interface:** UART

**Protocol:** HTTP

**Development Environment:** STM32CubeIDE / Keil µVision

**Serial Terminal:** PuTTY

---

## TASK 11A – HTTP Request Using AT Commands

### 1. Objective

To develop STM32 firmware that uses ESP8266 AT commands to establish a TCP connection with an HTTP server and transmit an HTTP GET request.

The STM32 communicates with the Wemos ESP8266 through UART. The ESP8266 connects to a Wi-Fi network and establishes a TCP connection with the specified HTTP server.

The HTTP request is transmitted using AT commands, demonstrating basic HTTP communication through the ESP8266 module.

---

### 2. Working Principle

The STM32 acts as the controller and communicates with the Wemos ESP8266 using UART.

The ESP8266 uses its AT command interface to perform network operations.

The communication process involves:

1. Initialize UART communication between STM32 and Wemos.
2. Verify the ESP8266 response using the AT command.
3. Configure the ESP8266 in Wi-Fi station mode.
4. Connect the ESP8266 to a Wi-Fi access point.
5. Establish a TCP connection with the HTTP server.
6. Specify the length of the HTTP request.
7. Transmit the HTTP GET request.
8. Verify successful transmission through the ESP8266 response.

---

### 3. AT Commands Used

#### 3.1 Check Modem Response

**Command:**

```text
AT
```

**Purpose:**

To verify UART communication between STM32 and Wemos.

**Expected Response:**

```text
OK
```

#### 3.2 Configure Wi-Fi Station Mode

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

#### 3.3 Connect to Wi-Fi Access Point

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

#### 3.4 Establish TCP Connection

**Command Format:**

```text
AT+CIPSTART="TCP","SERVER_ADDRESS",80
```

**Example:**

```text
AT+CIPSTART="TCP","example.com",80
```

**Purpose:**

- Establish a TCP connection with the HTTP server.
- Specify the destination server address.
- Connect through port 80 for HTTP communication.

**Expected Response:**

```text
CONNECT
OK
```

#### 3.5 Specify HTTP Request Length

**Command Format:**

```text
AT+CIPSEND=<request_length>
```

**Purpose:**

To specify the total number of bytes in the HTTP request that will be transmitted.

**Expected Response:**

```text
>
```

The `>` prompt indicates that the ESP8266 is ready to receive the HTTP request data.

#### 3.6 Send HTTP GET Request

**HTTP Request:**

```http
GET / HTTP/1.1
Host: example.com
Connection: close

```

**Purpose:**

- Send an HTTP GET request to the server.
- Specify the requested resource.
- Identify the destination host.
- Request connection closure after the response.

The request must be terminated with an additional blank line using CR/LF sequences.

**Expected Response:**

```text
SEND OK
```

---

### 4. HTTP Request Format

The HTTP GET request follows the structure below:

```http
GET / HTTP/1.1
Host: example.com
Connection: close

```

| Field | Description |
|---|---|
| GET | HTTP request method |
| / | Requested resource |
| HTTP/1.1 | HTTP protocol version |
| Host | Destination server |
| Connection: close | Requests connection closure after the response |

---

### 5. Implementation Steps

1. Configure UART communication between STM32 and Wemos.
2. Initialize the required UART peripherals.
3. Transmit the `AT` command and verify the response.
4. Configure Wi-Fi station mode using `AT+CWMODE=1`.
5. Connect the Wemos to a Wi-Fi network using `AT+CWJAP`.
6. Establish a TCP connection using `AT+CIPSTART`.
7. Prepare the HTTP GET request.
8. Calculate the total HTTP request length, including CR/LF characters.
9. Transmit `AT+CIPSEND` with the calculated request length.
10. Wait for the `>` prompt from the ESP8266.
11. Transmit the complete HTTP GET request through UART.
12. Verify successful transmission using the `SEND OK` response.

---

### 6. Expected Command Execution Sequence

```text
AT
    |
    v
AT+CWMODE=1
    |
    v
AT+CWJAP="SSID","PASSWORD"
    |
    v
AT+CIPSTART="TCP","example.com",80
    |
    v
AT+CIPSEND=<request_length>
    |
    v
GET / HTTP/1.1
Host: example.com
Connection: close

    |
    v
SEND OK
```

Each command should be executed after verifying the response to the previous command.

---

### 7. Communication Flow

```text
          STM32F410RB
               |
               | UART AT Commands
               v
          Wemos ESP8266
               |
               | Wi-Fi
               v
          HTTP Server
               |
               v
        TCP Connection
               |
               v
        HTTP GET Request
```

---

### 8. Expected Results

1. Successfully establish UART communication between STM32 and Wemos.
2. Configure the ESP8266 in Wi-Fi station mode.
3. Connect the Wemos to a Wi-Fi network.
4. Establish a TCP connection with the HTTP server.
5. Successfully transmit an HTTP GET request.
6. Verify successful request transmission through the `SEND OK` response.

---

### 9. Concepts Covered

- STM32 UART communication.
- ESP8266 AT command interface.
- Wi-Fi station mode configuration.
- TCP connection establishment.
- HTTP GET request.
- AT+CIPSTART command.
- AT+CIPSEND command.
- HTTP request formatting.
- CR/LF termination.
- Serial communication and debugging.
- Embedded networking.

---

### 10. Result

Successfully established a TCP connection between the Wemos ESP8266 and an HTTP server using AT commands transmitted from the STM32F410RB.

Prepared and transmitted an HTTP GET request through the established TCP connection and verified successful data transmission using the ESP8266 response.

---

## Hardware Requirements

- STM32F410RB Development Board
- Wemos D1 Mini (ESP8266)
- Connecting Wires
- Appropriate Power Supply
- PC or Laptop

## Software Requirements

- STM32CubeIDE
- Keil µVision (if used)
- ESP8266 AT Firmware
- PuTTY Serial Terminal
- Embedded C

---

## Deliverables

- STM32 UART configuration.
- ESP8266 AT command implementation.
- Wi-Fi connection configuration.
- TCP connection establishment.
- HTTP GET request transmission.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
