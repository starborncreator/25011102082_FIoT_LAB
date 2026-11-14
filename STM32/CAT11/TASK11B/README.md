
# **README**

# STM32 – HTTP Response Reception Using ESP8266

## Experiment Details

**Experiment:** HTTP Response Reception Using ESP8266

**Microcontroller:** STM32F410RB

**Wi-Fi Module:** Wemos D1 Mini (ESP8266)

**Communication Interface:** UART

**Protocol:** HTTP

**Development Environment:** STM32CubeIDE / Keil µVision

**Serial Terminal:** PuTTY

---

## TASK 11B – HTTP Response Reception

### 1. Objective

To receive and process the HTTP response returned by a web server through the Wemos ESP8266 and display the received response on the PC terminal using the STM32 microcontroller.

The STM32 receives the response data from the ESP8266 through UART and forwards the received characters to the PC terminal for verification.

### 2. Working Principle

After transmitting the HTTP GET request in Task A, the HTTP server processes the request and generates an HTTP response.

The Wemos ESP8266 receives the response through its established TCP connection and forwards the incoming data to the STM32 through UART.

The STM32 receives the response characters and transmits them to the PC terminal using another UART interface.

The HTTP response generally consists of:

- HTTP status line.
- Response headers.
- Blank line separating headers and body.
- HTTP response body.

### 3. HTTP Response Structure

An HTTP response generally follows the structure below:

```http
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: <length>
Connection: close

<html>
<body>
<h1>Hello World</h1>
</body>
</html>
```

### 4. HTTP Response Components

| Component | Description |
|---|---|
| HTTP Status Line | Indicates the server response status |
| Status Code | 200 indicates successful request |
| Content-Type | Specifies the type of returned data |
| Content-Length | Specifies the response body size |
| Connection | Indicates connection handling |
| Response Body | Contains the requested content |

### 5. UART Response Reception

**Objective:** To receive the HTTP response transmitted by the ESP8266 through UART.

**Working Principle:**

The STM32 continuously monitors the UART receive interface for incoming data.

When the ESP8266 sends response characters:

1. The STM32 receives the incoming UART data.
2. The received characters are stored in a buffer.
3. The received data is forwarded to the PC terminal.
4. The HTTP response is displayed for verification.

The ESP8266 may send the received network data with an `+IPD` prefix.

**Example:**

```text
+IPD,<length>:HTTP/1.1 200 OK
Content-Type: text/html

<html>
...
</html>
```

### 6. Implementation Steps

1. Initialize UART communication between STM32 and Wemos.
2. Initialize the UART interface used for PC terminal communication.
3. Establish a Wi-Fi connection using the ESP8266.
4. Establish a TCP connection with the HTTP server.
5. Transmit the HTTP GET request using `AT+CIPSEND`.
6. Wait for the HTTP response from the ESP8266.
7. Receive the incoming UART characters.
8. Store the received characters in a buffer.
9. Forward the received response to the PC terminal.
10. Display the HTTP status line, headers and response body.
11. Handle the end of the response and TCP connection closure.

### 7. Communication Flow

```text
          HTTP Server
               |
               | HTTP Response
               v
          Wemos ESP8266
               |
               | UART TX
               v
          STM32 UART RX
               |
               v
       Receive HTTP Data
               |
               v
         Store in Buffer
               |
               v
       Forward Through UART
               |
               v
          PC / PuTTY
```

### 8. Expected Terminal Output

**HTTP Response:**

```text
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: ...

<html>
<body>
...
</body>
</html>
```

The actual response depends on the HTTP server and the requested resource.

### 9. Verification

The following parameters should be verified:

| Parameter | Expected Result |
|---|---|
| TCP Connection | Successfully established |
| HTTP Request | Successfully transmitted |
| HTTP Response | Successfully received |
| HTTP Status Code | 200 OK (for a successful request) |
| UART Reception | Received characters correctly |
| PC Terminal | HTTP response displayed |

### 10. Concepts Covered

- HTTP response handling.
- STM32 UART reception.
- ESP8266 serial communication.
- TCP communication.
- HTTP status codes.
- HTTP response headers.
- HTTP response body.
- UART character reception.
- Buffer management.
- Serial data forwarding.
- Embedded networking.
- Serial debugging using PuTTY.

### 11. Expected Results

1. Successfully receive the HTTP response from the ESP8266.
2. Receive the response data through STM32 UART.
3. Store the incoming response characters in a buffer.
4. Forward the received data to the PC terminal.
5. Display the HTTP status line and response headers.
6. Display the HTTP response body.
7. Verify successful HTTP communication.

### 12. Result

Successfully implemented HTTP response reception using the STM32F410RB and Wemos ESP8266.

Received the HTTP response from the server through the ESP8266 UART interface, processed the incoming characters, and forwarded the response to the PC terminal for verification.

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

- HTTP response reception implementation.
- UART receive functionality.
- Response buffer implementation.
- HTTP response forwarding.
- PC terminal output.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
