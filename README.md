<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 27 09 AM" src="https://github.com/user-attachments/assets/59a867bb-cdea-40ce-b1fa-18be04f1086a" />
<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 34 04 AM" src="https://github.com/user-attachments/assets/175fc6e6-6440-420b-8902-7f9a991bc988" />
<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 34 10 AM" src="https://github.com/user-attachments/assets/25cbe201-ce90-45d1-b519-f632ecca16ae" />
<img width="1680" height="1050" alt="Screenshot 2026-11-01 at 11 34 12 AM" src="https://github.com/user-attachments/assets/2a6e6ade-6ed9-4bb4-86ef-6b5db53fdc12" />
# NanoPixel-Arcade
A pocket-sized 8-bit handheld gaming console powered by an Arduino microcontroller
NanoPixel Arcade 🕹️👾An ultra-compact, dual-button 8-bit handheld gaming console powered by an Arduino Nano and a 0.96-inch monochrome I2C OLED display. Designed from scratch with custom PCB routing, tactile physical controls, and onboard audio feedback for on-the-go retro gaming.📸 Media & ShowcaseFigure 1: Fully assembled NanoPixel Arcade handheld console.Figure 2: Custom board layout showing ergonomic button placement and I2C display header.📌 Project OverviewNanoPixel Arcade reimagines vintage arcade gaming inside a pocket-sized form factor. Running a custom-built, hardware-optimized obstacle-dodging runner game in C++, the console challenges your reflexes by spawning randomized ground cacti (to jump over) and overhead flying hazards (to duck beneath).The hardware avoids unnecessary complexity: it relies on the internal pull-up resistors of the ATmega328P microcontroller to register button inputs with zero passive debounce components, while a direct I2C interface pushes clean 60 FPS bitmap frames to the high-contrast SSD1306 OLED screen.✨ Key FeaturesCrisp 128×64 Display: High-contrast 0.96" monochrome I2C OLED screen rendering smooth sprite physics and HUD score counters.Ergonomic Dual-Button Input: Dedicated tactile switches for Jump (D2) and Duck/Crouch (D3) designed for natural thumb play.8-Bit Chiptune Audio: Onboard passive magnetic buzzer (D8) producing instantaneous sound cues on jump, score milestones, and game over.Minimalist Hardware: Leverages microcontroller internal pull-ups to minimize component count and keep assembly beginner-friendly.Standalone Portability: Flexible power routing compatible with 5V USB power banks or regulated Li-ion battery packs.🛒 Bill of Materials (BOM)ItemComponent / PartDesignatorFootprintQtyUnit Price (USD)Sourcing / Buying Link1Arduino Nano V3.0 (ATmega328P)U1DIP-30 / Module Socket1$2.80AliExpress / Amazon20.96" I2C OLED Display (SSD1306, 128×64)DISP14-Pin 2.54mm Header1$1.85AliExpress / Amazon36×6mm THT Tactile Switch (Jump, Duck)SW1, SW2SW-TH_4P-L6.0-W6.0-P4.502$0.08LCSC Electronics (C78923)4Passive Buzzer (5V, 12mm THT)BZ1BUZZER-TH_D12.01$0.25LCSC Electronics (C2943265)52.54mm Female Pin Header (1×4 for OLED)J1HDR-F-2.54_1X41$0.05LCSC Electronics (C224344)62.54mm Female Pin Header (1×15 for Nano)J2, J3HDR-F-2.54_1X152$0.15LCSC Electronics (C224346)7Mini SPST Power Slide SwitchSW_PWRSW-TH_3P-SS12D001$0.10LCSC Electronics (C136657)⚡ Schematic & Hardware Pinout                           +-------------------+
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
Complete Pin TableComponentPin LabelArduino Nano PinFunction / Configuration0.96" I2C OLEDGNDGNDGround referenceVCC5V (or 3.3V)Logic and display powerSCLA5Hardware I2C Clock lineSDAA4Hardware I2C Data lineJump Button (SW1)Terminal 1 / 2D2 to GNDActive LOW (INPUT_PULLUP)Duck Button (SW2)Terminal 1 / 2D3 to GNDActive LOW (INPUT_PULLUP)Audio Buzzer (BZ1)+ / -D8 to GNDPWM tone generation (tone())🎮 How to PlayPower On: Slide the power switch on or plug in the Mini/Type-C USB cable to power the Nano.Start Screen: Press the Jump (D2) or Duck (D3) button to start the game loop.Controls:Jump Button (D2): Tap to leap over incoming ground cacti.Duck Button (D3): Press and hold to crouch beneath high-flying aerial obstacles.Scoring: Surviving each obstacle awards 1 point. As your score climbs, the scrolling speed ramps up automatically!Game Over: Crashing into any hazard plays a game-over tone and displays your final score. Press Jump to immediately restart.💻 Software & InstallationPrerequisitesInstall the following open-source libraries via the Arduino Library Manager (Ctrl + Shift + I / Cmd + Shift + I):Adafruit SSD1306Adafruit GFX LibraryFlashing the FirmwareClone this repository:git clone https://github.com/<your-username>/NanoPixel-Arcade.git
Open src/NanoPixel_Arcade.ino inside the Arduino IDE.Under Tools > Board, select Arduino Nano.Under Tools > Processor, select ATmega328P (or ATmega328P (Old Bootloader) depending on your board clone).Select your active serial port and hit Upload (Ctrl + U).🛠️ File Structure├── docs/                   # Assembly photos, schematics, and pinout diagrams
│   ├── images/
│   └── NanoPixel_Schematic.pdf
├── hardware/               # EasyEDA Gerber files, BOM CSV, and PCB layout
│   ├── BOM_NanoPixel-Arcade.csv
│   └── Gerbers_NanoPixel_Arcade.zip
├── src/                    # Arduino C++ source code
│   └── NanoPixel_Arcade.ino
├── LICENSE                 # MIT License
└── README.md               # Project documentation
📄 LicenseThis project is open-source hardware and software released under the MIT License.
