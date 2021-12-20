// Bald Engineer's Live PCB Present Ornament
// James Lewis (C) 2021
// MIT License

// Get the MiniCore Board Definitions! 
// Boards have a 168P or 328PB 3v3 @ 8 MHz
// We're going to run with internal RC oscillator
//
// The PCBs have 40 LEDs configured as a matrix with 
// 8 columns and 5 rows. Code below turns on two LEDs
// at a time. Direct port manipulation limits the flicker.

// #include<EEPROM.h>

// Define the pinouts
// Rows
// PCB: Pin9, Pin10, Pin11, Pin12, Pin13
// AVR: PC1,  PD0,   PD1,   PD2,   PD3
// Uno: A1,    0,     1,     2,     3
const byte row_count = 5;
const byte rows[row_count] = {A1,0,1,2,3};

// Cols
// PCB: Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8
// AVR: PB0,  PD7,  PD6,  PC0,  PC5,  PC4,  PC3,  PC2
// Uno:   8,    7,    6,    A0,  A5,   A4,   A3,   A2
const byte col_count = 8;
const byte cols[8] = {8,7,6,A0,A5,A4,A3,A2};

// Pointless Battery Stuff
// Just realized, I tied AREF to ADC6
// batt_pointless has a LED, so it can be used for debug
const byte batt_facepalm = A6; // ADC
const byte batt_pointless = 5; // PD5

uint8_t mode = 0; // was going to cycle patterns on boot

// Cols    0     1     2     3     4    5      6     7
// PCB: Pin1, Pin2, Pin3, Pin4, Pin5, Pin6, Pin7, Pin8
// AVR: PB0,  PD7,  PD6,  PC0,  PC5,  PC4,  PC3,  PC2
// Uno:   8,    7,    6,    A0,  A5,   A4,   A3,   A2
void drive_col(int row, unsigned long led_wait_time) {
  pinMode(row, OUTPUT);
  digitalWrite(row, LOW);

  // we have plenty of flash memory available

  // DDR = 1 is out, 0 is in  
  // col Pin1 PB0
  DDRB = DDRB | 0x01; // col is out
  PORTB = PORTB | 0x01; // turn it on
  delayMicroseconds(led_wait_time);
  DDRB = DDRB & 0xFE; // col is in

  // col Pin2 PD7
  DDRD = DDRD | 0x80; // col is out
  PORTD = PORTD | 0x80; // turn it on
  delayMicroseconds(led_wait_time);
  DDRD = DDRD & 0x7F; // col is in 

  // col Pin3 PD6
  DDRD = DDRD | 0x40; // col is out
  PORTD = PORTD | 0x40; // turn it on
  delayMicroseconds(led_wait_time);
  DDRD = DDRD & 0xBF; // col is in 

  // col Pin4 PC0
  DDRC = DDRC | 0x01; // col is out
  PORTC = PORTC | 0x01; // turn it on
  delayMicroseconds(led_wait_time);
  DDRC = DDRC & 0xFE; // col is in 

  // col Pin5 PC5
  DDRC = DDRC | 0x20; // col is out
  PORTC = PORTC | 0x20; // turn it on
  delayMicroseconds(led_wait_time);
  DDRC = DDRC & 0xDF; // col is in 

  // col Pin6 PC4
  DDRC = DDRC | 0x10; // col is out
  PORTC = PORTC | 0x10; // turn it on
  delayMicroseconds(led_wait_time);
  DDRC = DDRC & 0xEF; // col is in 

  // col Pin7 PC3
  DDRC = DDRC | 0x08; // col is out
  PORTC = PORTC | 0x08; // turn it on
  delayMicroseconds(led_wait_time);
  DDRC = DDRC & 0xF7; // col is in 
  
  // col Pin8 PC2
  DDRC = DDRC | 0x04; // col is out
  PORTC = PORTC | 0x04; // turn it on
  delayMicroseconds(led_wait_time);
  DDRC = DDRC & 0xFB; // col is in 

  pinMode(row, INPUT);
}

void setup() {
  mode = -1; // eventually replace with EEPROM code
}

void loop() {
 for (int row=0; row < row_count; row++) {
    drive_col(rows[row], 250);
  }
}
