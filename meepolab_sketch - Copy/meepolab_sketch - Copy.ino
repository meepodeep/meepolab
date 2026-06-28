// Include the library
#include <Control_Surface.h>

#include <Keypad.h>
// Instantiate a MIDI Interface to use
USBMIDI_Interface midi;

Transposer<-12, +12> transposer;
uint8_t KeyVelocity = 0;
int octave = 0;
uint8_t KeysVelocity[25];
unsigned long firstPressTime[25];
unsigned long lastPressTime[25];

// Instantiate an analog multiplexer
CD74HC4067 mux {
  23,       // Analog input pin
  {0, 1, 2, 3} // Address pins 0 1 2 3
};
CD74HC4067 mux_1 {
  22,       // Analog input pin
  {4, 5, 6, 7} // Address pins 0 1 2 3
};
SPIShiftRegisterOut<32> sreg {
  SPI,      // SPI interface to use
  10,       // Latch pin (ST_CP)
  MSBFIRST, // Byte order
};

using namespace MIDI_Notes;

// Create an array of potentiometers that send out
// MIDI Control Change messages when you turn the
// potentiometers connected to the eight input pins of
// the multiplexer
NoteLED leds[] {
  {sreg.pin(0), 0},  // LED pin, address (note number, channel, cable)
  {sreg.pin(1), 1},  //
  {sreg.pin(2), 2},  //
  {sreg.pin(3), 3},  //
  {sreg.pin(4), 4},  //
  {sreg.pin(5), 5},  //
  {sreg.pin(6), 6},  //
  {sreg.pin(7), 7},  //
  {sreg.pin(8), 8},  //
  {sreg.pin(9), 9},  //
  {sreg.pin(10), 10},  //
  {sreg.pin(11), 11},  //
  {sreg.pin(12), 12},  //
  {sreg.pin(13), 13},  //
  {sreg.pin(14), 14},  //
  {sreg.pin(15), 15},  //
  {sreg.pin(16), 16},  //
  {sreg.pin(17), 17},  //
  {sreg.pin(18), 18},  //
  {sreg.pin(19), 19},  //
  {sreg.pin(20), 20},  //
  {sreg.pin(21), 21},  //
  {sreg.pin(22), 22},  //
  {sreg.pin(23), 23},  //
  {sreg.pin(24), 24},  //
  {sreg.pin(25), 25},  //
  {sreg.pin(26), 26},  //
  {sreg.pin(27), 27},  //
  {sreg.pin(28), 28},  //
  {sreg.pin(29), 29},  //
  {sreg.pin(30), 30},  //
  {sreg.pin(31), 31},  //
  {sreg.pin(32), 32},  //
};
CCPotentiometer volumePotentiometers[] {
  {mux.pin(0), {MIDI_CC::Channel_Volume, Channel_1}},
  {mux.pin(1), {MIDI_CC::Channel_Volume, Channel_2}},
  {mux.pin(2), {MIDI_CC::Channel_Volume, Channel_3}},
  {mux.pin(3), {MIDI_CC::Channel_Volume, Channel_4}},
  {mux.pin(4), {MIDI_CC::Channel_Volume, Channel_5}},
  {mux.pin(5), {MIDI_CC::Channel_Volume, Channel_6}},
  {mux.pin(6), {MIDI_CC::Channel_Volume, Channel_7}},
  {mux.pin(7), {MIDI_CC::Channel_Volume, Channel_8}},
  {mux.pin(8), {MIDI_CC::Channel_Volume, Channel_9}},
  {mux.pin(9), {MIDI_CC::Channel_Volume, Channel_10}},
  {mux.pin(10), {MIDI_CC::Channel_Volume, Channel_11}},
  {mux.pin(11), {MIDI_CC::Channel_Volume, Channel_12}},
};

Bankable::NoteButton buttons[] = {
  {transposer, mux.pin(12), {25, Channel_13}},
  {transposer, mux.pin(13), {26, Channel_13}},
  {transposer, mux.pin(14), {27, Channel_13}},
  {transposer, mux.pin(15), {28, Channel_13}},
  {transposer, mux_1.pin(0), {29, Channel_13}},
  {transposer, mux_1.pin(1), {30, Channel_13}},
  {transposer, mux_1.pin(2), {31, Channel_13}},
  {transposer, mux_1.pin(3), {32, Channel_13}},
};
// The note numbers corresponding to the buttons in the matrix
const AddressMatrix<5, 5> addresses {{
  {0, 1, 2, 3, 4},
  {5,6,7,8,9 },
  {10,11,12,13,14 },
  {15,16,17,18,19},
  {20,21,22,23,24}
}};
 const AddressMatrix<5, 1> addressbutton {{
  {0},
  {1},
  {2},
  {3},
  {4}
}};
Bankable::NoteButtonMatrix<5, 5> buttonmatrix {
  transposer,
  {12, 24, 25, 26, 27}, // row pins
  {37,28,29,30,35},    // column pins
  addresses,    // address matrix
  Channel_14,   // channel and cable number
  KeyVelocity,
};
CCButtonMatrix<5, 1> buttonmatrix_1 {
  {12, 24, 25, 26, 27}, // row pins
  {34},    // column pins
  addressbutton,    // address matrix
  Channel_15,    // channel and cable number
};


const byte ROWS = 5; // five rows
const byte COLS = 1; // 1 column
char keys[ROWS][COLS] = {
  {1},
  {2},
  {3},
  {4},
  {5}
};
byte rowPins[ROWS] = {12, 24, 25, 26, 27}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {34}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const byte ROWS_1 = 5; // five rows
const byte COLS_1 = 10; // 10 column
char keys_1[ROWS_1][COLS_1] = {
  {6,7,8,9,10,11,12,13,14,15},
  {16,17,18,19,20,21,22,23,24,25},
  {26,27,28,29,30,31,32,33,34,35},
  {36,37,38,39,40,41,42,43,44,45},
  {46,47,48,49,50,51,52,53,54,55}
};
byte rowPins_1[ROWS_1] = {12, 24, 25, 26, 27}; // connect to the row pinouts of the keypad
byte colPins_1[COLS_1] = {8,9,21,20,38,37,28,29,30,35}; // connect to the column pinouts of the keypad

Keypad keypad_1 = Keypad(makeKeymap(keys_1), rowPins_1, colPins_1, ROWS_1, COLS_1);


// 7-bit filtered analog input for velocity control
FilteredAnalog<7> velocityInput = 35;
// Initialize the Control Surface
void setup() {
  Control_Surface.begin();
  mux.begin();
  for (auto &button : buttons) // for each button in the buttons array
   	button.invert();
}

// Update the Control Surface
void loop() {
  Control_Surface.loop();
  for (auto &button : buttons)
    button.setVelocity(velocityInput.getValue());

    char button = keypad.getKey(); // Check if a key is pressed
    
  if (button == 2) { // Replace 'A' with your target button
    octave +=1; 
  }
  if (button == 3) { // Replace 'A' with your target button
    octave -= 1;
  }
  transposer.select(0+octave);

  switch (button) {
  case 6:
    firstPressTime[0] = millis();
    break;
  case 7:
    firstPressTime[1] = millis();
    break;
  case 8:
    firstPressTime[2] = millis();
    break;
  case 9:
    firstPressTime[3] = millis();
    break;
  case 10:
    firstPressTime[4] = millis();
    break;
  case 16:
    firstPressTime[5] = millis();
    break;
  case 17:
    firstPressTime[6] = millis();
    break;
  case 18:
    firstPressTime[7] = millis();
    break;
  case 19:
    firstPressTime[8] = millis();
    break;
  case 20:
    firstPressTime[9] = millis();
    break;
  case 26:
    firstPressTime[10] = millis();
    break;
  case 27:
    firstPressTime[11] = millis();
    break;
  case 28:
    firstPressTime[12] = millis();
    break;
  case 29:
    firstPressTime[13] = millis();
    break;
  case 30:
    firstPressTime[14] = millis();
    break;
  case 36:
    firstPressTime[15] = millis();
    break;
  case 37:
    firstPressTime[16] = millis();
    break;
  case 38:
    firstPressTime[17] = millis();
    break;
  case 39:
    firstPressTime[18] = millis();
    break;
  case 40:
    firstPressTime[19] = millis();
    break;
  case 46:
    firstPressTime[20] = millis();
    break;
  case 47:
    firstPressTime[21] = millis();
    break;
  case 48:
    firstPressTime[22] = millis();
    break;
  case 49:
    firstPressTime[23] = millis();
    break;
  case 50:
    firstPressTime[24] = millis();
    break;
  default:
    // statements to run if nothing matches
    break;
}
switch (button) {
  case 11:
    lastPressTime[0] = millis();
    KeysVelocity[0]=(uint8_t)(lastPressTime[0]-firstPressTime[0]);
    KeyVelocity = KeysVelocity[0];
    break;
  case 12:
    lastPressTime[1] = millis();
    KeysVelocity[1]=(uint8_t)(lastPressTime[1]-firstPressTime[1]);
    KeyVelocity = KeysVelocity[1];
    break;
  case 13:
    lastPressTime[2] = millis();
    KeysVelocity[2]=(uint8_t)(lastPressTime[2]-firstPressTime[2]);
    KeyVelocity = KeysVelocity[2];
    break;
  case 14:
    lastPressTime[3] = millis();
    KeysVelocity[3]=(uint8_t)(lastPressTime[3]-firstPressTime[3]);
    KeyVelocity = KeysVelocity[3];
    break;
  case 15:
    lastPressTime[4] = millis();
    KeysVelocity[4]=(uint8_t)(lastPressTime[4]-firstPressTime[4]);
    KeyVelocity = KeysVelocity[4];
    break;
  case 21:
    lastPressTime[5] = millis();
    KeysVelocity[5]=(uint8_t)(lastPressTime[5]-firstPressTime[5]);
    KeyVelocity = KeysVelocity[5];
    break;
  case 22:
    lastPressTime[6] = millis();
    KeysVelocity[6]=(uint8_t)(lastPressTime[6]-firstPressTime[6]);
    KeyVelocity = KeysVelocity[6];
    break;
  case 23:
    lastPressTime[7] = millis();
    KeysVelocity[7]=(uint8_t)(lastPressTime[7]-firstPressTime[7]);
    KeyVelocity = KeysVelocity[7];
    break;
  case 24:
    lastPressTime[8] = millis();
    KeysVelocity[8]=(uint8_t)(lastPressTime[8]-firstPressTime[8]);
    KeyVelocity = KeysVelocity[8];
    break;
  case 25:
    lastPressTime[9] = millis();
    KeysVelocity[9]=(uint8_t)(lastPressTime[9]-firstPressTime[9]);
    KeyVelocity = KeysVelocity[9];
    break;
  case 31:
    lastPressTime[10] = millis();
    KeysVelocity[10]=(uint8_t)(lastPressTime[10]-firstPressTime[10]);
    KeyVelocity = KeysVelocity[10];
    break;
  case 32:
    lastPressTime[11] = millis();
    KeysVelocity[11]=(uint8_t)(lastPressTime[11]-firstPressTime[11]);
    KeyVelocity = KeysVelocity[11];
    break;
  case 33:
    lastPressTime[12] = millis();
    KeysVelocity[12]=(uint8_t)(lastPressTime[12]-firstPressTime[12]);
    KeyVelocity = KeysVelocity[12];
    break;
  case 34:
    lastPressTime[13] = millis();
    KeysVelocity[13]=(uint8_t)(lastPressTime[13]-firstPressTime[13]);
    KeyVelocity = KeysVelocity[13];
    break;
  case 35:
    lastPressTime[14] = millis();
    KeysVelocity[14]=(uint8_t)(lastPressTime[14]-firstPressTime[14]);
    KeyVelocity = KeysVelocity[14];
    break;
  case 41:
    lastPressTime[15] = millis();
    KeysVelocity[15]=(uint8_t)(lastPressTime[15]-firstPressTime[15]);
    KeyVelocity = KeysVelocity[15];
    break;
  case 42:
    lastPressTime[16] = millis();
    KeysVelocity[16]=(uint8_t)(lastPressTime[16]-firstPressTime[16]);
    KeyVelocity = KeysVelocity[16];
    break;
  case 43:
    lastPressTime[17] = millis();
    KeysVelocity[17]=(uint8_t)(lastPressTime[17]-firstPressTime[17]);
    KeyVelocity = KeysVelocity[17];
    break;
  case 44:
    lastPressTime[18] = millis();
    KeysVelocity[18]=(uint8_t)(lastPressTime[18]-firstPressTime[18]);
    KeyVelocity = KeysVelocity[18];
    break;
  case 45:
    lastPressTime[19] = millis();
    KeysVelocity[19]=(uint8_t)(lastPressTime[19]-firstPressTime[19]);
    KeyVelocity = KeysVelocity[19];
    break;
  case 51:
    lastPressTime[20] = millis();
    KeysVelocity[20]=(uint8_t)(lastPressTime[20]-firstPressTime[20]);
    KeyVelocity = KeysVelocity[20];
    break;
  case 52:
    lastPressTime[21] = millis();
    KeysVelocity[21]=(uint8_t)(lastPressTime[21]-firstPressTime[21]);
    KeyVelocity = KeysVelocity[21];
    break;
  case 53:
    lastPressTime[22] = millis();
    KeysVelocity[22]=(uint8_t)(lastPressTime[22]-firstPressTime[22]);
    KeyVelocity = KeysVelocity[22];
    break;
  case 54:
    lastPressTime[23] = millis();
    KeysVelocity[23]=(uint8_t)(lastPressTime[23]-firstPressTime[23]);
    KeyVelocity = KeysVelocity[23];
    break;
  case 55:
    lastPressTime[24] = millis();
    KeysVelocity[24]=(uint8_t)(lastPressTime[24]-firstPressTime[24]);
    KeyVelocity = KeysVelocity[24];
    break;
  default:
    // statements to run if nothing matches
    break;
}
}