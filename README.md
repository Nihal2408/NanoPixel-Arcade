<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 27 09 AM" src="https://github.com/user-attachments/assets/59a867bb-cdea-40ce-b1fa-18be04f1086a" />
<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 34 04 AM" src="https://github.com/user-attachments/assets/175fc6e6-6440-420b-8902-7f9a991bc988" />
<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 34 10 AM" src="https://github.com/user-attachments/assets/25cbe201-ce90-45d1-b519-f632ecca16ae" />
<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 34 12 AM" src="https://github.com/user-attachments/assets/2a6e6ade-6ed9-4bb4-86ef-6b5db53fdc12" />

# NanoPixel Arcade 🕹️👾

An ultra-compact, dual-button 8-bit handheld gaming console powered by an Arduino Nano and a 0.96-inch monochrome I2C OLED display. Designed from scratch with custom PCB routing, tactile physical controls, and onboard audio feedback for on-the-go retro gaming.

---

## 📸 Media & Showcase

<!-- Add your build photos here -->
![Console Front View](docs/images/console_front.png)  
*Figure 1: Fully assembled NanoPixel Arcade handheld console.*

![PCB & Action](docs/images/pcb_routing.png)  
*Figure 2: Custom board layout showing ergonomic button placement and I2C display header.*

---

## 📌 Project Overview

**NanoPixel Arcade** reimagines vintage arcade gaming inside a pocket-sized form factor. Running a custom-built, hardware-optimized obstacle-dodging runner game in C++, the console challenges your reflexes by spawning randomized ground cacti (to jump over) and overhead flying hazards (to duck beneath). 

The hardware avoids unnecessary complexity: it relies on the internal pull-up resistors of the ATmega328P microcontroller to register button inputs with zero passive debounce components, while a direct I2C interface pushes clean 60 FPS bitmap frames to the high-contrast SSD1306 OLED screen.

### ✨ Key Features
- **Crisp 128×64 Display:** High-contrast 0.96" monochrome I2C OLED screen rendering smooth sprite physics and HUD score counters.
- **Ergonomic Dual-Button Input:** Dedicated tactile switches for Jump (`D2`) and Duck/Crouch (`D3`) designed for natural thumb play.
- **8-Bit Chiptune Audio:** Onboard passive magnetic buzzer (`D8`) producing instantaneous sound cues on jump, score milestones, and game over.
- **Minimalist Hardware:** Leverages microcontroller internal pull-ups to minimize component count and keep assembly beginner-friendly.
- **Standalone Portability:** Flexible power routing compatible with 5V USB power banks or regulated Li-ion battery packs.

---

## 🛒 Bill of Materials (BOM)

| Item | Component / Part | Designator | Footprint | Qty | Unit Price (USD) | Sourcing / Buying Link |
| :---: | :--- | :--- | :--- | :---: | :---: | :--- |
| 1 | **Arduino Nano V3.0** (ATmega328P) | `U1` | DIP-30 / Module Socket | 1 | $2.80 | [AliExpress / Amazon](https://www.aliexpress.com/item/32868739265.html) |
| 2 | **0.96" I2C OLED Display** (SSD1306, 128×64) | `DISP1` | 4-Pin 2.54mm Header | 1 | $1.85 | [AliExpress / Amazon](https://www.aliexpress.com/item/32896971385.html) |
| 3 | **6×6mm THT Tactile Switch** (Jump, Duck) | `SW1, SW2` | `SW-TH_4P-L6.0-W6.0-P4.50` | 2 | $0.08 | [LCSC Electronics (C78923)](https://www.lcsc.com/product-detail/C78923.html) |
| 4 | **Passive Buzzer** (5V, 12mm THT) | `BZ1` | `BUZZER-TH_D12.0` | 1 | $0.25 | [LCSC Electronics (C2943265)](https://www.lcsc.com/product-detail/C2943265.html) |
| 5 | **2.54mm Female Pin Header** (1×4 for OLED) | `J1` | `HDR-F-2.54_1X4` | 1 | $0.05 | [LCSC Electronics (C224344)](https://www.lcsc.com/product-detail/C224344.html) |
| 6 | **2.54mm Female Pin Header** (1×15 for Nano) | `J2, J3` | `HDR-F-2.54_1X15` | 2 | $0.15 | [LCSC Electronics (C224346)](https://www.lcsc.com/product-detail/C224346.html) |
| 7 | **Mini SPST Power Slide Switch** | `SW_PWR` | `SW-TH_3P-SS12D00` | 1 | $0.10 | [LCSC Electronics (C136657)](https://www.lcsc.com/product-detail/C136657.html) |

---

## ⚡ Schematic & Hardware Pinout

```
                           +-------------------+
                           |   Arduino Nano    |
                           |    ATmega328P     |
                           +---------+---------+
                                     |
       +-----------------------------+-----------------------------+
       |                  |                    |                   |
       v [I2C Bus]        v [Digital In]       v [Digital In]      v [Audio Out]
+-------------+    +---------------+    +---------------+    +------------+
| 0.96" OLED  |    | Button 1: JUMP|    | Button 2: DUCK|    |  Passive   |
|   SSD1306   |    |  (Tact Switch)|    |  (Tact Switch)|    |   Buzzer   |
| SCL -> A5   |    |  Pin 1 -> D2  |    |  Pin 1 -> D3  |    |  (+) -> D8 |
| SDA -> A4   |    |  Pin 2 -> GND |    |  Pin 2 -> GND |    |  (-) -> GND|
| VCC -> 5V   |    +---------------+    +---------------+    +------------+
| GND -> GND  |
+-------------+
```

### Complete Pin Table

| Component | Pin Label | Arduino Nano Pin | Function / Configuration |
| :--- | :--- | :--- | :--- |
| **0.96" I2C OLED** | `GND` | `GND` | Ground reference |
| | `VCC` | `5V` (or `3.3V`) | Logic and display power |
| | `SCL` | `A5` | Hardware I2C Clock line |
| | `SDA` | `A4` | Hardware I2C Data line |
| **Jump Button (`SW1`)** | Terminal 1 / 2 | `D2` to `GND` | Active LOW (`INPUT_PULLUP`) |
| **Duck Button (`SW2`)** | Terminal 1 / 2 | `D3` to `GND` | Active LOW (`INPUT_PULLUP`) |
| **Audio Buzzer (`BZ1`)** | `+` / `-` | `D8` to `GND` | PWM tone generation (`tone()`) |

---

## 🎮 How to Play

1. **Power On:** Slide the power switch on or plug in the Mini/Type-C USB cable to power the Nano.
2. **Start Screen:** Press the **Jump** (`D2`) or **Duck** (`D3`) button to start the game loop.
3. **Controls:**
   - **Jump Button (`D2`):** Tap to leap over incoming ground cacti.
   - **Duck Button (`D3`):** Press and hold to crouch beneath high-flying aerial obstacles.
4. **Scoring:** Surviving each obstacle awards 1 point. As your score climbs, the scrolling speed ramps up automatically!
5. **Game Over:** Crashing into any hazard plays a game-over tone and displays your final score. Press Jump to immediately restart.

---

## 💻 Software & Installation

### Prerequisites
Install the following open-source libraries via the **Arduino Library Manager** (`Ctrl + Shift + I` / `Cmd + Shift + I`):
- **Adafruit SSD1306**
- **Adafruit GFX Library**

### Flashing the Firmware
1. Clone this repository:
   ```bash
   git clone https://github.com/<your-username>/NanoPixel-Arcade.git
   ```
2. Open `src/NanoPixel_Arcade.ino` inside the Arduino IDE.
3. Under **Tools > Board**, select **Arduino Nano**.
4. Under **Tools > Processor**, select **ATmega328P** (or *ATmega328P (Old Bootloader)* depending on your board clone).
5. Select your active serial port and hit **Upload** (`Ctrl + U`).

---

## 🛠️ File Structure

```
├── docs/                   # Assembly photos, schematics, and pinout diagrams
│   ├── images/
│   └── NanoPixel_Schematic.pdf
├── hardware/               # EasyEDA Gerber files, BOM CSV, and PCB layout
│   ├── BOM_NanoPixel-Arcade.csv
│   └── Gerbers_NanoPixel_Arcade.zip
├── src/                    # Arduino C++ source code
│   └── NanoPixel_Arcade.ino
├── LICENSE                 # MIT License
└── README.md               # Project documentation
```

---

## 📄 License

This project is open-source hardware and software released under the [MIT License](LICENSE).
