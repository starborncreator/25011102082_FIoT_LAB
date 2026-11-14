
# **README**

# 8051 – 4×4 Keypad-Based Character Movement on LCD

## Experiment Details

**Experiment:** 4×4 Keypad-Based Character Movement

**Microcontroller:** 8051 (AT89S52)

**Development Environment:** Keil µVision

**Display Interface:** 16×2 LCD

**Input Interface:** 4×4 Matrix Keypad

---

## TASK 7C – 4×4 Keypad-Based Character Movement

### 1. Objective

To develop an interactive LCD application using a 4×4 matrix keypad, in which a character can be moved across the 16×2 LCD display using directional keys.

The keypad acts as the input device, allowing the user to control the character's movement in four directions: up, down, left, and right.

### 2. Working Principle

The 4×4 matrix keypad is interfaced with the 8051 microcontroller to detect user inputs.

Four keys are assigned as directional controls. Whenever a valid directional key is pressed, the microcontroller identifies the key and updates the character's position on the LCD.

The character moves dynamically across the 16×2 display according to the pressed key.

The LCD cursor-positioning function developed in Task 7B can be reused to update the character's position.

### 3. Key Mapping and Functional Requirements

The following keys are assigned as directional controls:

| Key Press | Action | Movement |
|:---:|---|:---:|
| 2 | Move Up | ↑ |
| 8 | Move Down | ↓ |
| 4 | Move Left | ← |
| 6 | Move Right | → |

### 4. Character Movement Operations

#### 4.1 Move Up – Key 2

When key 2 is pressed, the character moves one position upward on the LCD.

#### 4.2 Move Down – Key 8

When key 8 is pressed, the character moves one position downward on the LCD.

#### 4.3 Move Left – Key 4

When key 4 is pressed, the character moves one column towards the left.

#### 4.4 Move Right – Key 6

When key 6 is pressed, the character moves one column towards the right.

### 5. LCD Display Configuration

The application uses a 16×2 LCD consisting of:

- 2 rows.
- 16 columns per row.
- 32 character positions in total.

The character position is updated dynamically based on the keypad input.

### 6. Implementation Steps

1. Initialize the 16×2 LCD.
2. Initialize the 4×4 matrix keypad.
3. Define variables to store the current row and column positions of the character.
4. Display the character at the initial LCD position.
5. Continuously scan the matrix keypad for key presses.
6. Identify the pressed directional key.
7. Update the row position when moving up or down.
8. Update the column position when moving left or right.
9. Clear the previous character position.
10. Move the LCD cursor to the updated position.
11. Display the character at the new position.
12. Repeat the process continuously.

### 7. Expected Behaviour

The character should move across the LCD based on the directional key pressed.

| Key | Expected Behaviour |
|:---:|---|
| 2 | Character moves one row upward |
| 8 | Character moves one row downward |
| 4 | Character moves one column left |
| 6 | Character moves one column right |

### 8. Concepts Covered

- 8051 GPIO programming.
- 4×4 matrix keypad interfacing.
- Row-column keypad scanning.
- LCD interfacing.
- LCD cursor positioning.
- Dynamic character movement.
- Directional input handling.
- Row and column indexing.
- Embedded C programming.
- Modular programming using functions.

### 9. Expected Results

1. Successfully interface a 4×4 matrix keypad with the 8051 microcontroller.
2. Detect the directional keys 2, 4, 6 and 8.
3. Move a character upward and downward across the LCD.
4. Move a character left and right across the LCD.
5. Update the character position dynamically based on keypad input.

### 10. Result

Successfully implemented an interactive LCD character movement application using a 4×4 matrix keypad and the 8051 microcontroller.

The character position is dynamically updated on the 16×2 LCD based on the directional keys pressed by the user.

---

## Hardware Requirements

- AT89S52 Microcontroller
- 8051 Development Board
- 16×2 LCD Module
- 4×4 Matrix Keypad
- Connecting Wires
- 5V Power Supply

## Software Requirements

- Keil µVision IDE
- 8051 C Compiler
- Embedded C

---

## Deliverables

- Complete Embedded C source code.
- LCD interfacing implementation.
- Matrix keypad scanning implementation.
- Directional character movement logic.
- README documentation.
- GitHub repository containing the implementation.
