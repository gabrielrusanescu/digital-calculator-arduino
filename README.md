# Arduino Matrix Keypad and LCD Calculator

This repository contains the firmware for an Arduino-based calculator that utilizes a 16x2 Liquid Crystal Display (LCD) and a 4x4 matrix keypad to perform basic mathematical operations. 

---

## Features

* **Standard Arithmetic Operations**: Supports basic calculations including addition, subtraction, multiplication, and division.
* **Division-by-Zero Protection**: Features error-handling logic that intercepts divisions by zero and outputs a warning message on the screen.
* **Negative Number Configuration**: Allows the processing and initiation of negative values directly via the keypad layout.
* **Synchronized Display Cursor**: Implements a non-blocking blinking cursor effect to show active user input placement.

---

## Hardware Configuration

The system requires an Arduino board, a standard 16x2 LCD module, and a 4x4 matrix keypad. The hardware pins are mapped as follows:

### LCD Pin Mapping
The LCD is initialized using the standard `LiquidCrystal` library with the designated digital pins:

| LCD Pin | Arduino Pin |
| :--- | :--- |
| **RS** | 12 |
| **Enable** | 11 |
| **D4** | 10 |
| **D5** | 9 |
| **D6** | 8 |
| **D7** | 7 |

### Keypad Pin Mapping
The 4x4 matrix keypad uses the following row and column pin setup:

| Keypad Line | Arduino Pin |
| :--- | :--- |
| **Row 1, 2, 3, 4** | 5, 4, 3, 2 |
| **Column 1, 2, 3, 4** | A3, A2, A1, A0 |

### Keypad Layout Matrix
The layout mapping array correlates keys to their respective characters:

| | Col 1 | Col 2 | Col 3 | Col 4 |
| :--- | :---: | :---: | :---: | :---: |
| **Row 1** | 1 | 2 | 3 | + |
| **Row 2** | 4 | 5 | 6 | - |
| **Row 3** | 7 | 8 | 9 | * |
| **Row 4** | . | 0 | = | / |

---

## Software Dependencies

To compile and upload this project, ensure you have the following libraries installed in your Arduino IDE:
* `LiquidCrystal.h`
* `Keypad.h`

---

## Operational Logic

1. **Initialization**: The system sets up the serial communication interface at a baud rate of 115200, initializes the 16x2 layout, runs the introductory screen, and sets the cursor configuration.
2. **Key Processing**: 
   * Mathematical operators (`+`, `-`, `*`, `/`) segment inputs into distinct string variables.
   * The `=` key converts the captured string segments into double-precision floating-point numbers, processes the operation, and displays the outcome on the screen.
   * The decimal point key (`.`) includes input filtering to prevent duplicate decimal formatting within a single numeric string.
3. **Error Management**: If a user attempts to divide an operand by zero, the LCD screen clears, prints a temporary error notification ("S-a incercat impartirea la 0"), and resets the evaluation state safely to 0.
