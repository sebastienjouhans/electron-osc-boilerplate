#include <Ethernet2.h>
#include <EthernetUdp2.h>
#include <SPI.h>
#include <OSCBundle.h>

EthernetUDP Udp;

#define encoder0PinA 2
#define encoder0PinB 3
volatile  int encoder0Pos = 4323;
int encoderPosOld = 0;
int sensitivity = 2;
int vidLength = (1024 * sensitivity); 
float scrub = 0;
int encoderTick = 0;
boolean tick = false;




//the Arduino's IP
IPAddress ip(169, 254, 227, 190);
//destination IP
IPAddress outIp(169, 254, 227, 11);
const unsigned int outPort = 57121;

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0xEB, 0xE4
}; // you can find this written on the board of some Arduino Ethernets or shields

void setup() {
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Ethernet.begin(mac, ip);
  Udp.begin(8888);
  Serial.begin (115200);
}

void loop() {
  rangeCheck();
  oscSend();
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;
    }         // CW
    else {
      encoder0Pos = encoder0Pos - 1;  // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos - 1;
    }         // CW
    else {
      encoder0Pos = encoder0Pos + 1;   // CCW
    }
  }

  tick = true;
  //Serial.println(encoder0Pos);
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;
    }       // CW
    else {
      encoder0Pos = encoder0Pos - 1;    // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;
    }        // CW
    else {
      encoder0Pos = encoder0Pos - 1;   // CCW
    }
  }

  tick = true;
  //Serial.println(encoder0Pos);
}

void oscSend() {
  if (tick == true) {
    //declare the bundle
    OSCBundle bndl;

    //BOSCBundle's add' returns the OSCMessage so the message's 'add' can be composed together
    bndl.add("/scrub").add((float)scrub);
    Udp.beginPacket(outIp, outPort);
    bndl.send(Udp); // send the bytes to the SLIP stream
    Udp.endPacket(); // mark the end of the OSC Packet
    bndl.empty(); // empty the bundle to free room for a new one
    tick = false;
    Serial.println(encoder0Pos);
    Serial.println(scrub);
    Serial.println(scrub * 1000);
    Serial.println(encoderTick);
    Serial.println("------");
  }
}

void rangeCheck() {
  if (encoder0Pos < 0) {
    scrub = 1 + (float(encoder0Pos % vidLength) / float (vidLength)) ;
  }
  else {
    scrub = float(encoder0Pos % vidLength) / float (vidLength);
  }
  
  encoderTick = int((vidLength * scrub));
}
