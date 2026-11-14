
# **README**

# 8051 – LCD Cursor Positioning and Dynamic Value Update

## Experiment Details

**Experiment:** LCD Cursor Positioning and Dynamic Value Update

**Microcontroller:** 8051 (AT89S52)

**Development Environment:** Keil µVision

**Display Interface:** LCD

---

## TASK 7B – Cursor Positioning and Dynamic Value Update

### 1. Objective

To develop LCD cursor-positioning and data-update functions for controlling the display dynamically using the 8051 microcontroller.

The experiment focuses on positioning the LCD cursor at specific row and column locations, displaying strings, and printing numerical values.

### 2. Working Principle

The LCD cursor-positioning functionality allows data to be displayed at specific locations on the LCD instead of always printing from the beginning of the display.

Separate functions are developed to:
- Position the cursor at a specified row and column.
- Display a string on the LCD.
- Display numerical values on the LCD.

These functions improve code modularity and allow dynamic updating of displayed information.

---

### 3. Functions to Be Implemented

The program shall consist of the following functions:

#### 3.1 `lcd_goto(row, column)`

**Objective:** To position the LCD cursor at a specified row and column.

**Working Principle:**

The function accepts the row and column positions as arguments and moves the LCD cursor to the corresponding location.

This allows information to be displayed at different positions on the LCD.

**Function Declaration:**

```c
void lcd_goto(unsigned char row, unsigned char column);
```

#### 3.2 `lcd_puts(string)`

**Objective:** To display a string of characters on the LCD.

**Working Principle:**

The function accepts a string as an argument and displays its characters sequentially starting from the current cursor position.

**Function Declaration:**

```c
void lcd_puts(char *string);
```

#### 3.3 `lcd_print_number(value)`

**Objective:** To display numerical values on the LCD.

**Working Principle:**

The function accepts a numerical value and converts it into individual displayable digits before sending them to the LCD.

This allows numerical data to be displayed dynamically.

**Function Declaration:**

```c
void lcd_print_number(unsigned int value);
```

---

### 4. Implementation Steps

1. Initialize the LCD.
2. Develop the `lcd_goto()` function to control cursor positioning.
3. Develop the `lcd_puts()` function to display strings.
4. Develop the `lcd_print_number()` function to display numerical values.
5. Use the cursor-positioning function to select the required display location.
6. Display strings and numerical values at the specified positions.
7. Verify the LCD output for different cursor positions and values.

---

### 5. Expected Output

The LCD should support:

- Displaying strings at specified row and column positions.
- Positioning the cursor dynamically.
- Displaying numerical values.
- Updating displayed values without restarting the application.

---

### 6. Concepts Covered

- LCD interfacing with 8051.
- LCD cursor positioning.
- Row and column addressing.
- String display functions.
- Integer-to-string conversion.
- Dynamic numerical display.
- Modular programming using functions.
- Embedded C programming.

---

### 7. Expected Results

1. Successfully implement LCD cursor positioning.
2. Display strings using `lcd_puts()`.
3. Display numerical values using `lcd_print_number()`.
4. Update LCD contents dynamically.
5. Verify correct display output at different cursor positions.

---

### 8. Result

Successfully developed LCD cursor-positioning and data-update functions using the 8051 microcontroller. Implemented functions for cursor movement, string display, and numerical value display to enable dynamic LCD interfacing.

---

## Software Requirements

- Keil µVision IDE
- 8051 C Compiler
- Embedded C

## Hardware Requirements

- AT89S52 Microcontroller
- LCD Module
- 8051 Development Board
- Connecting Wires
- Power Supply

---

## Deliverables

- LCD cursor-positioning function.
- String display function.
- Numerical value display function.
- Complete Embedded C source code.
- README documentation.
- GitHub repository containing the implementation.
