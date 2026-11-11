# Magnetic-Mystery-Puzzle
Code and CAD and stuff for the Magnetic Mystery Puzzle Game
# Magnetic Mystery Puzzle Box

An interactive puzzle project featuring an Arduino-controlled enclosure with hidden digital Hall effect sensors. Players must wave a magnet over four hidden sensors in the correct non-repeating sequence to unlock the win condition. Each successful solve automatically generates a new randomized pattern.

Developed by **Juniper Tech Labs**.

---

## Repository Contents

### 3D CAD Models & Drawings
* **`Assembly, Cardboard Box.step`** — Complete top-level assembly containing the cardboard enclosure, Arduino Nano R4, mini breadboard mount, and 4 sensor modules.
* **`Assembly, Digital Hall Effects Sensor.step`** — Sub-assembly for the digital Hall effect sensor module with right-angle headers.
* **`Digital Hall Effects Sensor - Short.step`** — Compact lead variant of the Hall effect sensor module.
* **`Top, Cardboard Box.step`** / **`Bottom, Cardboard Box.step`** — Individual solid models for enclosure fabrication.
* **`Top, Carboard Box, Flat Pattern.pdf`** — 1:1 scale flat fold template for the box lid (185 mm base with 35 mm wall folds).
* **`Bottom, Carboard Box, Flat Pattern.pdf`** — 1:1 scale flat fold template for the box base (175 mm base with 50 mm wall folds).

### Firmware
* **`Magnetic_Mystery_Puzzle.ino`** — Arduino sketch controlling sensor debounce, pattern randomization, validation logic, and LED status feedback.

---

## Hardware & Wiring

### Components
* 1x Arduino Uno or Nano (compatible with Nano R4 / Uno R3 / standard ATmega328P boards)
* 4x Digital Hall Effect Sensor Modules (e.g., A3144 / KY-003)
* 1x Green LED (Success / Detection indicator)
* 1x Red LED (Error / Reset indicator)
* 2x 220Ω Current-Limiting Resistors
* Neodymium magnet (wand or handheld)
* Enclosure material (cardboard or 3D printed sheet)

### Pin Configuration

| Component | Arduino Pin | Configuration / Notes |
| :--- | :--- | :--- |
| **Sensor 0** | Digital Pin `2` | `INPUT_PULLUP` (Active LOW) |
| **Sensor 1** | Digital Pin `3` | `INPUT_PULLUP` (Active LOW) |
| **Sensor 2** | Digital Pin `4` | `INPUT_PULLUP` (Active LOW) |
| **Sensor 3** | Digital Pin `5` | `INPUT_PULLUP` (Active LOW) |
| **Green LED** | Digital Pin `6` | Active HIGH via 220Ω resistor |
| **Red LED** | Digital Pin `7` | Active HIGH via 220Ω resistor |
| **Random Seed**| Analog Pin `A0` | **Leave floating / unconnected** |

---

## How It Works

1. **Startup & Randomization:** On boot, the Arduino reads ambient analog noise on unconnected pin `A0` to seed the random number generator. It shuffles the indices `[0, 1, 2, 3]` using a Fisher-Yates swap, ensuring each sensor appears exactly once in the target sequence.
2. **Player Input:** Moving a magnet across any sensor pulls its corresponding pin LOW. The green LED pulses once for 250 ms to confirm receipt, and state-latch flags prevent rapid multi-triggering.
3. **Validation:**
   * **Win:** Entering all 4 sensors in the correct sequence flashes the Green LED 5 times and generates a brand-new target sequence.
   * **Fail:** Entering an incorrect sequence flashes the Red LED 5 times. The secret pattern remains unchanged so the player can retry.
4. **Debug Monitoring:** Open the Serial Monitor at **9600 baud** to see real-time sensor detections and reveal the current winning sequence.

---

## Getting Started

1. **Enclosure:** Print the flat pattern PDFs at 100% scale (no scaling / actual size), trace onto cardboard or cardstock, cut along solid outer lines, and score along inner dash-dot fold lines.
2. **Assembly:** Mount the 4 Hall effect sensors underneath the box lid in your desired layout (refer to `Assembly, Cardboard Box.step`).
3. **Upload Code:**
   * Open `Magnetic_Mystery_Puzzle.ino` in the Arduino IDE.
   * Select your board under **Tools > Board** and your serial port under **Tools > Port**.
   * Click **Upload**.
4. **Play:** Power the Arduino via USB or external 5V/VIN and test with a handheld magnet.

---

## License

This project is released under the [MIT License](LICENSE). You are free to modify, adapt, and build upon both the code and physical design.

This README was AI generated
