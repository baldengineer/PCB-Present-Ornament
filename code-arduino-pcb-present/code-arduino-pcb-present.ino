// Bald Engineer's Live PCB Present Ornament
// James Lewis (C) 2021
// MIT License

// Arduino Pro: 328p 3v3 @ 8 MHz
// We're going to run with internal RC oscillator

// Define the pinouts
// Rows
// PCB: Pin9, Pin10, Pin11, Pin12, Pin13
// AVR: PC1,  PD0,   PD1,   PD2,   PD3
// Uno: A1,    0,     1,     2,     3
const byte top_row_pin = A1;
const byte row_count = 4;
const byte rows[row_count] = {0,1,2,3};

// Cols
// PCB: Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8
// AVR: PB0,  PD7,  PD6,  PC0,  PC5,  PC4,  PC3,  PC2
// Uno:   8,    7,    6,    A0,  A5,   A4,   A3,   A2
const byte col_count = 8;
const byte cols[8] = {8,7,6,A0,A5,A4,A3,A2};


// Pointless Battery Stuff
// Just realized, I tied AREF to ADC6, so why bother?
const byte batt_facepalm = A6; // ADC
const byte batt_pointless = 5; // PD5


unsigned long default_wait_time = 2;  // have to re-think this...

uint8_t mode = 0;

void drive_col(int row, led_wait_time) {
  pinMode(row, OUTPUT);
  digitalWrite(row, LOW); // enable the row
  for (int col=0; col < (col_count/2); col++) {
      pinMode(col, OUTPUT);
      digitalWrite(col, HIGH); // enable colA
      pinMode(col+4, OUTPUT);
      digitalWrite(col+4; HIGH); // enable colB
      delay(led_wait_time);
      digitalWrite(col, LOW); // disable colA
      pinMode(col, INPUT);
      digitalWrite(col+4; LOW); // disable colB
      pinMode(col, INPUT);
      delay(led_wait_time);
  }
}

void drive_matrix(bool pattern, unsigned long led_wait_time) {
  // drive the top row_first

  drive_col(top_row_pin, led_wait_time);
  for (int col=0; col < (col_count/2); col++) {
      drive_col(col, led_wait_time);
  }
  digitalWrite(top_row_pin, HIGH); // disable the row
  pinmode(top_row_pin, INPUT);

  // cycle through the rows
  for (int row=0; row < row_count; row++) {
    // operate two columns at the same time
    pinMode(row, OUTPUT);
    digitalWrite(row, LOW); // enable the row
    for (int col=0; col < (col_count/2); col++) {
      drive_col(col, led_wait_time);
    }
    digitalWrite(row, HIGH); // disable the row
    pinmode(row, INPUT);
  }
}

void setup() {
  mode = 0; // eventually replace with EEPROM code
  EEPROM.write(0, 0); // let's wear it out
}

void loop() {

  switch(mode) {
    case 0: // all on
      bool top_row[8] = {1,1,1,1,1,1,1,1};
      bool boxes[] = {
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
      };
      drive_matrix(top_row, boxes, default_wait_time);
    break;
  }


}
