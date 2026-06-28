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
  {4, 5, 6, 7} // Address pins 4 5 6 7
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

 const AddressMatrix<5, 1> addressbutton {{
  {0},
  {1},
  {2},
  {3},
  {4}
}};
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

void setup() {
  Control_Surface.begin();
  mux.begin();
  for (auto &button : buttons) // for each button in the buttons array
   	button.invert();
}

// Update the Control Surface
void loop() {
  Control_Surface.loop();


  
}
}