

// HN61256
//  1 - NC
//  2 - A13 - 44 - PL5 - ~D44
//  3 - A7  - 30 - PC7 - D30
//  4 - A6  - 31 - PC6 - D31
//  5 - A5  - 32 - PC5 - D32
//  6 - A4  - 33 - PC4 - D33
//  7 - A3  - 34 - PC3 - D34
//  8 - A2  - 35 - PC2 - D35
//  9 - A1  - 36 - PC1 - D36
// 10 - A0  - 37 - PC0 - D37
// 11 - D0  - 22 - PA0 - D22
// 12 - D1  - 23 - PA1 - D23
// 13 - D2  - 24 - PA2 - D24
// 14 - GND
// 15 - D3  - 25 - PA3 - D25
// 16 - D4  - 26 - PA4 - D26
// 17 - D5  - 27 - PA5 - D27
// 18 - D6  - 28 - PA6 - D28
// 19 - D7  - 29 - PA7 - D29
// 20 - A11 - 46 - PL3 - ~D46
// 21 - A10 - 47 - PL2 - D47
// 22 - CE  - 40 - PG1 - D40
// 23 - A12 - 45 - PL4 - ~D45
// 24 - A9  - 48 - PL1 - D48
// 25 - A8  - 49 - PL0 - D49
// 26 - CS  - 41 - PG0 - D41
// 27 - A14 - 43 - PL6 - D43
// 28 - Vcc

const int PIN_ADDRESS[15] = 
{
  37, 36, 35, 34, 33, 32, 31, 30,
  49, 48, 47, 46, 45, 44, 43 
};

const int PIN_DATA[8] = 
{
  22, 23, 24, 25, 26, 27, 28, 29
};

const int PIN_CS = 41;
const int PIN_CE = 40;

/////////////////////////////////////////////

const int PIN_CS_ACTIVE = 1;

const int PIN_CE_ACTIVE = 0;
const int PIN_CE_INACTIVE = 1;

// S19 Format writer component
#include "SRecWriter.h"
SRecWriter g_writer;

void setup() {
  pinMode(PIN_CS, OUTPUT);
  pinMode(PIN_CE, OUTPUT);
  
  digitalWrite(PIN_CS, PIN_CS_ACTIVE);
  digitalWrite(PIN_CE, PIN_CE_INACTIVE);

  for(int i=0;i<15;i++) {
    pinMode(PIN_ADDRESS[i], OUTPUT);
    digitalWrite(PIN_ADDRESS[i],0);
  }
  
  for(int i=0;i<8;i++) {
    pinMode(PIN_DATA[i], INPUT);
  }  

  // Enable serial port
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  g_writer.reset();
  g_writer.setSerial(Serial);

}

void loop() {
  g_writer.reset();
  g_writer.setSerial(Serial);
  
  for(uint16_t address=0;address<32768;address++)
  {
    int data = 0;

    for(int i=0;i<15;i++)
      digitalWrite(PIN_ADDRESS[i],(address>>i)&1);
      
    digitalWrite(PIN_CE, PIN_CE_ACTIVE);

    data = 0;
    for(int i=0;i<8;i++)
    {
      if (digitalRead(PIN_DATA[i]) == 1)
        data |= (1 << i);
    }

    digitalWrite(PIN_CE, PIN_CE_INACTIVE);

    g_writer.addData(data);

  }
  g_writer.finish();

  //while(1);
}
