# **README**

## 8051 – CONTINUOUS ASSESSMENT 2 (CAT2)

### Experiments

This repository contains the implementation of experiments performed using the **8051 Microcontroller (AT89S52)** as part of Continuous Assessment 2. The experiments are developed and simulated/programmed using **Keil µVision IDE**.

### Experiment List

| Task | Experiment Name | Description |
|------|-----------------|-------------|
| TASK 2A | Single LED Blinking | Implements continuous blinking of a single LED connected to Port 1, Pin P1.0 of the 8051 microcontroller using software-generated delays. |

### Task Details

#### [TASK 2A – Single LED Blinking using 8051 Microcontroller](./TASK2A/README.md)

**Hardware Components:**
- 8051 Microcontroller (AT89S52)
- LED
- 220Ω–330Ω current-limiting resistor
- 5V power supply

**Key Concepts Covered:**
- GPIO output configuration
- LED interfacing with 8051
- Active-low LED operation
- Software delay generation using nested loops
- Infinite loop execution for continuous blinking

**Software Requirements:**
- Keil µVision IDE
- 8051 C Compiler

### Repository Structure

```text
8051-CAT2/
│
├── README.md
│
└── TASK2A/
    ├── README.md
    └── main.c
