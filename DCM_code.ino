//code for Nano Aetherphone 2 - MIDI controller
//by "Chi ha ucciso Il Conte?" - https://chihauccisoilconte.eu/

// library needed:
// MIDI - https://github.com/FortySevenEffects/arduino_midi_library
// This machine kills fascists

//released under CC BY-NC license
//this machine kills fascists


#include <SPI.h>
#include <Wire.h>
#include <MIDI.h>
#define MPU 0x68  // I2C address of the MPU-6050

const byte input = 11;   // digital input to arduino from mux
const byte c=10;
const byte b=9;
const byte a=8;

const int button1Pin = 4;
const int button2Pin = 5;
const int button3Pin = 2;
const int button4Pin = 7;

const int DEFAULT_MIDI_CHANNEL = 1;
MIDI_CREATE_DEFAULT_INSTANCE();


int button1State = 0; 
int button2State = 0; 
int button3State = 0; 
int button4State = 0; 


int note1 = 0;
int note2 = 0;
int note3 = 0;
int note4 = 0;
int note5 = 0;
int note6 = 0;
int note7 = 0;
int note8 = 0;
int note9 = 0;
int note10 = 0;
int note11 = 0;
int note12 = 0;

int led1 = 3;
int led2 = 6;
int led3 = A1; // bush button LED
int led4 = A2; // on off LED



int brightness1 = 0; 
int brightness2 = 0; 

// to store the values from mux
// bool val[] = {0,0,0,0,0,0,0,0};  
byte numero;


const int MPU_ADDR=0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
 
void setup() {
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
   Serial.begin(31250);


   
  pinMode(c, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);

  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);


  
  pinMode(button1Pin, INPUT); 
  pinMode(button2Pin, INPUT); 
  pinMode(button3Pin, INPUT); 
  pinMode(button4Pin, INPUT); 
  pinMode(input, INPUT);    

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

}
 
void loop() {

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable

  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

int mc1 =0;
int mc2  =0;
int mc3  =0;
int mc4  =0;

    


 

  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  int button4State = digitalRead(button4Pin);

  analogWrite(led1, brightness1);
  analogWrite(led2, brightness2);

  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);



 
  numero = 0;
  for(byte i=0;i<8;i++) {

         numero = numero | ( digitalRead(input) << i) ;

    //select mux input
    digitalWrite(a, bitRead(i, 0));
    digitalWrite(b, bitRead(i, 1));
    digitalWrite(c, bitRead(i, 2));
 
 
 button1State = digitalRead(button1Pin);
 button2State = digitalRead(button2Pin);
 button3State = digitalRead(button3Pin);
 button4State = digitalRead(button4Pin);




    
  }
 

 if (button1State == HIGH) { 
    // if note not playing

    
    if (note1 == 0) {
      // play note (note number, velocity, channel)
      // more info: http://arduinomidilib.sourceforge.net/a00001.html
      // MIDI notes chart http://www.phys.unsw.edu.au/jw/notes.html
      // 55 = G3, 127 = trigger note with max volume
    
   MIDI.sendNoteOn(43, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note1 = 1;
    }
  // when button released
         digitalWrite(led3, HIGH);
 } else {


    // if note playing
    if (note1 == 1) {
      // if playing - stop
      
      MIDI.sendNoteOff(43, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note1 = 0;

  }

   
     if (button2State == HIGH) {
       

    // if note not playing
    if (note2 == 0) { 
            

   MIDI.sendNoteOn(45, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing 
      note2 = 1;
    }
  // when button released
          digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note2 == 1) {
      // if playing - stop
     
      MIDI.sendNoteOff(45, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note2 = 0;

  }
   
     if (button3State == HIGH) {
    // if note not playing
    if (note3 == 0) {
  
   MIDI.sendNoteOn(42, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note3 = 1;
    }
  // when button released
            digitalWrite(led3, HIGH);
} else {
    // if note playing
    if (note3 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(42, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note3 = 0;
  }

     if (button4State == HIGH) {
    // if note not playing
    if (note4 == 0) {
 
   MIDI.sendNoteOn(44, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note4 = 1;
    }
  // when button released
             digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note4 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(44, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note4 = 0;
  }

  if (numero == 1) {
    // if note not playing
    if (note5 == 0) {
 
   MIDI.sendNoteOn(46, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note5 = 1;
    }
  // when button released
              digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note5 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(46, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note5 = 0;
  }

    if (numero == 2) {
    // if note not playing
    if (note6 == 0) {
 
   MIDI.sendNoteOn(53, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note6 = 1;
    }
  // when button released
              digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note6 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(53, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note6 = 0;
  }

      if (numero == 4) {
    // if note not playing
    if (note7 == 0) {
 
   MIDI.sendNoteOn(52, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note7 = 1;
    }
  // when button released
              digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note7 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(52, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note7 = 0;
  }

        if (numero == 8) {
    // if note not playing
    if (note8 == 0) {
 
   MIDI.sendNoteOn(50, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note8 = 1;
    }
  // when button released
               digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note8 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(50, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note8 = 0;
  }

          if (numero == 16) {
    // if note not playing
    if (note9 == 0) {
 
   MIDI.sendNoteOn(51, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note9 = 1;
    }
  // when button released
               digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note9 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(51, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note9 = 0;
  }

            if (numero == 32) {
    // if note not playing
    if (note10 == 0) {
 
   MIDI.sendNoteOn(49, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note10 = 1;
    }
  // when button released
                digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note10 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(49, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note10 = 0;
  }

              if (numero == 64) {
    // if note not playing
    if (note11 == 0) {
 
   MIDI.sendNoteOn(48, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note11 = 1;
    }
  // when button released
                digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note11 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(48, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note11 = 0;
  }

                if (numero == 128) {
    // if note not playing
    if (note12 == 0) {
 
   MIDI.sendNoteOn(47, 127, DEFAULT_MIDI_CHANNEL);
      // note is playing
      note12 = 1;
    }
  // when button released
                digitalWrite(led3, HIGH);
 } else {
    // if note playing
    if (note12 == 1) {
      // if playing - stop
      MIDI.sendNoteOff(47, 0, DEFAULT_MIDI_CHANNEL);
    }
    // if button released note is off
    note12 = 0;
  }

  //serial printing
  //Serial.print("Numero: ");
  //Serial.println(numero);




 
if (gyro_x < 3000 && gyro_x > 10000) {

int xf = gyro_x;
 brightness1 = map(xf, 3000, 10000, 0, 255);

  mc1 = map(xf, 3000, 10000, 0, 127);
   MIDI.sendControlChange(1, mc1, DEFAULT_MIDI_CHANNEL);

} else {
    // if note playing
mc1 = 0;
  }

if (gyro_x < -3000 && gyro_x > -10000  ) {

int xb = gyro_x;

 brightness1 = map(xb, -3000, -10000, 0, 255);

  mc2 = map(xb, -3000, -10000, 0, 127);
   MIDI.sendControlChange(2, mc2, DEFAULT_MIDI_CHANNEL);


}else {
    // if note playing

mc2 = 0;
  }

if (gyro_y > 9000 && gyro_y < 13000 ) {

int xf = gyro_y;

 brightness2 = map(xf, 13000, 9000, 0, 255);


  mc3 = map(xf, 13000, 9000, 0, 127);
  MIDI.sendControlChange(3, mc3, DEFAULT_MIDI_CHANNEL);


}else {
    // if note playing
mc3 = 0;
  }

if (gyro_y < 12000 && gyro_y > 8000) {

int yb = gyro_y;

 brightness2 = map(yb, 12000, 8000, 0, 255);

  mc4 = map(yb, 12000, 8000, 0, 127);
   MIDI.sendControlChange(4, mc4, DEFAULT_MIDI_CHANNEL);


}else {
    // if note playing
mc4 = 0;
  }
 
}
