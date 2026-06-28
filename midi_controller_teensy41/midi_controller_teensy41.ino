// ============================================================
// MIDI Controller — Teensy 4.1
// Tools > Board: Teensy 4.1
// Tools > USB Type: Serial + MIDI
//   (use Serial+MIDI during debug so you can see Serial.print output)
// ============================================================

#include <Control_Surface.h>
#include <Keypad.h>

USBMIDI_Interface midi;
Transposer<-12, +12> transposer;

uint8_t KeyVelocity = 64;
uint8_t KeysVelocity[25]         = {};
unsigned long firstPressTime[25] = {};
unsigned long lastPressTime[25]  = {};
int octave = 0;

CD74HC4067 mux {
  23,
  {0, 1, 2, 3}
};
CD74HC4067 mux_1 {
  22,
  {4, 5, 6, 7}
};

SPIShiftRegisterOut<32> sreg {
  SPI2,
  10,
  MSBFIRST,
};

using namespace MIDI_Notes;

NoteLED leds[] {
  {sreg.pin(0),  0},  {sreg.pin(1),  1},  {sreg.pin(2),  2},  {sreg.pin(3),  3},
  {sreg.pin(4),  4},  {sreg.pin(5),  5},  {sreg.pin(6),  6},  {sreg.pin(7),  7},
  {sreg.pin(8),  8},  {sreg.pin(9),  9},  {sreg.pin(10),10},  {sreg.pin(11),11},
  {sreg.pin(12),12},  {sreg.pin(13),13},  {sreg.pin(14),14},  {sreg.pin(15),15},
  {sreg.pin(16),16},  {sreg.pin(17),17},  {sreg.pin(18),18},  {sreg.pin(19),19},
  {sreg.pin(20),20},  {sreg.pin(21),21},  {sreg.pin(22),22},  {sreg.pin(23),23},
  {sreg.pin(24),24},  {sreg.pin(25),25},  {sreg.pin(26),26},  {sreg.pin(27),27},
  {sreg.pin(28),28},  {sreg.pin(29),29},  {sreg.pin(30),30},  {sreg.pin(31),31},
};

CCPotentiometer volumePotentiometers[] {
  {mux.pin(0),  {MIDI_CC::Channel_Volume, Channel_1}},
  {mux.pin(1),  {MIDI_CC::Channel_Volume, Channel_2}},
  {mux.pin(2),  {MIDI_CC::Channel_Volume, Channel_3}},
  {mux.pin(3),  {MIDI_CC::Channel_Volume, Channel_4}},
  {mux.pin(4),  {MIDI_CC::Channel_Volume, Channel_5}},
  {mux.pin(5),  {MIDI_CC::Channel_Volume, Channel_6}},
  {mux.pin(6),  {MIDI_CC::Channel_Volume, Channel_7}},
  {mux.pin(7),  {MIDI_CC::Channel_Volume, Channel_8}},
  {mux.pin(8),  {MIDI_CC::Channel_Volume, Channel_9}},
  {mux.pin(9),  {MIDI_CC::Channel_Volume, Channel_10}},
  {mux.pin(10), {MIDI_CC::Channel_Volume, Channel_11}},
  {mux.pin(11), {MIDI_CC::Channel_Volume, Channel_12}},
};

Bankable::NoteButton transposeButtons[] {
  {transposer, mux.pin(12),  {25, Channel_13}},
  {transposer, mux.pin(13),  {26, Channel_13}},
  {transposer, mux.pin(14),  {27, Channel_13}},
  {transposer, mux.pin(15),  {28, Channel_13}},
  {transposer, mux_1.pin(0), {29, Channel_13}},
  {transposer, mux_1.pin(1), {30, Channel_13}},
  {transposer, mux_1.pin(2), {31, Channel_13}},
  {transposer, mux_1.pin(3), {32, Channel_13}},
};

const AddressMatrix<5, 1> addressbutton {{
  {0}, {1}, {2}, {3}, {4},
}};
CCButtonMatrix<5, 1> buttonmatrix_1 {
  {12, 24, 25, 26, 27},
  {33},
  addressbutton,
  Channel_15,
};

// Keypad 1 — octave shift
const byte ROWS = 5;
const byte COLS = 1;
char keys[ROWS][COLS] = { {1}, {2}, {3}, {4}, {5} };
byte rowPins[ROWS] = {12, 24, 25, 26, 27};
byte colPins[COLS]  = {34};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Keypad 2 — dual contact velocity keyboard
const byte ROWS_1 = 5;
const byte COLS_1 = 10;
char keys_1[ROWS_1][COLS_1] = {
  { 6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23, 24, 25},
  {26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
  {36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
  {46, 47, 48, 49, 50, 51, 52, 53, 54, 55},
};
byte rowPins_1[ROWS_1] = {12, 24, 25, 26, 27};
byte colPins_1[COLS_1]  = {8, 9, 21, 20, 38, 37, 28, 29, 30, 35};
Keypad keypad_1 = Keypad(makeKeymap(keys_1), rowPins_1, colPins_1, ROWS_1, COLS_1);

FilteredAnalog<7> velocityInput {A12};

static inline uint8_t durationToVelocity(unsigned long delta) {
  long d = constrain((long)delta, 1L, 126L);
  return (uint8_t)(127L - d + 1L);
}

void setup() {
  Serial.begin(115200);
  delay(1000); // give Serial time to connect
  Serial.println("=== MIDI Controller Debug Boot ===");

  Control_Surface.begin();
  mux.begin();
  mux_1.begin();

  for (auto &btn : transposeButtons)
    btn.invert();

  keypad_1.setDebounceTime(5);

  Serial.println("Setup complete.");
}

void loop() {
  Control_Surface.loop();

  velocityInput.update();
  uint8_t analogVel = velocityInput.getValue();
  for (auto &btn : transposeButtons)
    btn.setVelocity(analogVel);

  // Octave shift
  char ctrlKey = keypad.getKey();
  if (ctrlKey == 2) {
    octave = constrain(octave + 1, -12, 12);
    transposer.select(octave);
    Serial.print("Octave UP → "); Serial.println(octave);
  } else if (ctrlKey == 3) {
    octave = constrain(octave - 1, -12, 12);
    transposer.select(octave);
    Serial.print("Octave DN → "); Serial.println(octave);
  }

  // Velocity keyboard
  if (keypad_1.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      Key k = keypad_1.key[i];

      // --- DEBUG: print every active slot so we can see what the keypad sees ---
      if (k.kchar != 0) {
        Serial.print("slot="); Serial.print(i);
        Serial.print(" kchar="); Serial.print((uint8_t)k.kchar);
        Serial.print(" kstate=");
        switch(k.kstate) {
          case PRESSED:  Serial.print("PRESSED");  break;
          case HOLD:     Serial.print("HOLD");     break;
          case RELEASED: Serial.print("RELEASED"); break;
          case IDLE:     Serial.print("IDLE");     break;
        }
        Serial.print(" stateChanged="); Serial.println(k.stateChanged);
      }

      if (!k.stateChanged) continue;

      uint8_t v = (uint8_t)k.kchar;
      if (v < 6 || v > 55) continue;

      int offset     = v - 6;
      int row        = offset / 10;
      int colInRow   = offset % 10;
      bool isSecond  = (colInRow >= 5);
      int colInGroup = colInRow % 5;
      int physKey    = row * 5 + colInGroup;

      int noteNum = constrain(physKey + (octave * 12), 0, 127);
      MIDIAddress addr = {(uint8_t)noteNum, Channel_14};

      Serial.print("  → physKey="); Serial.print(physKey);
      Serial.print(" isSecond="); Serial.print(isSecond);
      Serial.print(" note="); Serial.println(noteNum);

      switch (k.kstate) {
        case PRESSED:
          if (!isSecond) {
            firstPressTime[physKey] = millis();
            Serial.print("  FIRST contact down, physKey="); Serial.println(physKey);
          } else {
            lastPressTime[physKey] = millis();
            unsigned long delta = lastPressTime[physKey] - firstPressTime[physKey];
            KeysVelocity[physKey] = durationToVelocity(delta);
            KeyVelocity = KeysVelocity[physKey];
            midi.sendNoteOn(addr, KeyVelocity);
            Serial.print("  NOTE ON  note="); Serial.print(noteNum);
            Serial.print(" vel="); Serial.print(KeyVelocity);
            Serial.print(" delta="); Serial.print(delta); Serial.println("ms");
          }
          break;

        case RELEASED:
          if (isSecond) {
            midi.sendNoteOff(addr, 0);
            Serial.print("  NOTE OFF note="); Serial.println(noteNum);
          }
          break;

        default:
          break;
      }
    }
  }
}
