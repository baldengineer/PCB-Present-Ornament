// Bald Engineer's Live PCB Present Ornament
// James Lewis (C) 2021
// MIT License

// Arduino Pro: 328p 3v3 @ 8 MHz
// We're going to run with internal RC oscillator


#include<EEPROM.h>

// Define the pinouts
// Rows
// PCB: Pin9, Pin10, Pin11, Pin12, Pin13
// AVR: PC1,  PD0,   PD1,   PD2,   PD3
// Uno: A1,    0,     1,     2,     3
const byte top_row_pin = A1;
const byte row_count = 5;
const byte rows[row_count] = {A1,0,1,2,3};

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


uint32_t default_wait_time = 2;  // have to re-think this...

uint8_t mode = 0;

void drive_col(int row, unsigned long led_wait_time) {
  pinMode(row, OUTPUT);
  digitalWrite(row, LOW); // enable the row
  for (int col=0; col < (col_count/2); col++) {
      pinMode(cols[col], OUTPUT);
      digitalWrite(cols[col], HIGH); // enable colA
      pinMode(cols[col+4], OUTPUT);
      digitalWrite(cols[col+4], HIGH); // enable colB
      delay(led_wait_time);
      digitalWrite(cols[col], LOW); // disable colA
      pinMode(cols[col], INPUT);
      digitalWrite(cols[col+4], LOW); // disable colB
      pinMode(cols[col+4], INPUT);
    //  delay(led_wait_time);
  }
  digitalWrite(row, HIGH); // disable the row
  pinMode(row, INPUT);
}

// NONE OF THIS IS RIGHT
void drive_matrix(bool pattern, uint32_t led_wait_time) {
  // cycle through the rows
  for (int row=0; row < row_count; row++) {
    // operate two columns at the same time
    pinMode(row, OUTPUT);
    digitalWrite(row, LOW); // enable the row
    for (int col=0; col < (col_count/2); col++) {
      drive_col(col, led_wait_time);
    }
    digitalWrite(row, HIGH); // disable the row
    pinMode(row, INPUT);
  }
}

void setup() {
  mode = -1; // eventually replace with EEPROM code
//  EEPROM.write(0, 0); // let's wear it out
}

void loop() {
 // drive_col(top_row_pin, 1);

  // cycle through the rows
 for (int row=0; row < row_count; row++) {
    // operate two columns at the same time
    drive_col(rows[row], 1);
  }
// drive_col(A1, 1);
// drive_col(0, 1);
/*
  switch(mode) {
    case 0: // all on
      bool boxes[] = {
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
        1,1,1,1, 1,1,1,1,
      };
      drive_matrix(boxes, default_wait_time);
    break;
  }
*/

}
