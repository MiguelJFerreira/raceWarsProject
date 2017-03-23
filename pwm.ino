/*
mySerial-bluetooth
Serial-bluetooth
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8); // RX, TX


//PWM pins para os motores
int Motor1A = 15;
int Motor1B = 14;
int Motor2A = 16;
int Motor2B = 10;

//EN_1 come pwm
int EN_1 =3;
int EN_2 =4;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

//motor 1 dá a tração, motor 2 vira  
  pinMode( Motor1A, OUTPUT );
  pinMode( Motor1B, OUTPUT );
  pinMode( Motor2A, OUTPUT );
  pinMode( Motor2B, OUTPUT );
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, LOW );
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
  digitalWrite( EN_1, LOW );
  digitalWrite( EN_2, LOW );
}

//para que serve a flag??
int flag1 = -1;
int flag2 = -1;

volatile int velocity;

void loop() { // run over and over
  if (mySerial.available()) {
    
    char toSend = (char)mySerial.read();
    Serial.println(toSend);
    switch(toSend){
      case 0:
        velocity=0;
      case 1:
        velocity=26;
       case 2:
         velocity=51;
       case 3:
          velocity=77;
       case 4:
          velocity=102;
       case 5:
         velocity=127;
       case 6:
          velocity=154;
       case 7:
          velocity=179;
       case 8:
          velocity=205;
       case 9:
          velocity=230;
       case 'q':
          velocity=255;
    }
    analogWrite(EN_1, velocity);
    
    if(toSend == 'S')
    {
        flag1 = 0;
        flag2 = 0;
        digitalWrite( Motor1A, LOW );
        digitalWrite( Motor1B, LOW );
        
        digitalWrite( Motor2A, LOW );
        digitalWrite( Motor2B, LOW );
    }
    if(toSend == 'F' || toSend == 'G' || toSend == 'I')
    {
        if(flag1 != 1)
        {
          flag1 = 1;
          digitalWrite( Motor1A, HIGH );
          digitalWrite(Motor1B, LOW);
        }
    }
    if(toSend == 'B' || toSend == 'H' || toSend == 'J')
    {
        if(flag1 != 2)
        {
          flag1 = 2;
          digitalWrite( Motor1B, HIGH );
          digitalWrite(Motor1A, LOW);
        }
    }

    if(toSend == 'L' || toSend == 'G' || toSend == 'H')
    {
        if(flag2 != 1)
        {
          flag2 = 1;
          digitalWrite( Motor2B, HIGH );
          digitalWrite(Motor2A,LOW);
        }
    }
    else
    if(toSend == 'R' || toSend == 'I' || toSend == 'J')
    {
        if(flag2 != 2)
        {
          flag2 = 2;
          digitalWrite( Motor2A, HIGH );
          digitalWrite(Motor2B, LOW);
        }
    }
    else
    {
        if(flag2 != 3)
        {
          flag2 = 3;
          digitalWrite( Motor2A, LOW );
          digitalWrite( Motor2B, LOW );
        }
    }
  }
 
}

