// Receive infra-red signals and record key encodings
// XiaoCY 2022-05-15

#include <IRremote.hpp>         // 3.x version

int irRevPin = 8;               // PIN number for reveive infra-red signals
uint32_t rawData;               // infra-red raw data

// Key encodings
// uint32_t   CHm   = 0xBA45FF00;        // CH-
// uint32_t   CH    = 0xB946FF00;        // CH
// uint32_t   CHp   = 0xB847FF00;        // CH+
// uint32_t   VOLm  = 0xBB44FF00;        // VOL-
// uint32_t   VOLp  = 0xBF40FF00;        // VOL+
// uint32_t   PLAY  = 0xBC43FF00;        // PLAY/PAUSE
// uint32_t   MINUS = 0xF807FF00;        // MINUS
// uint32_t   PLUS  = 0xEA15FF00;        // PLUS
// uint32_t   EQ    = 0xF609FF00;        // EQ
// uint32_t   NUM0  = 0xE916FF00;        // NUM0
// uint32_t   NUM1h = 0xE619FF00;        // NUM 100+
// uint32_t   NUM2h = 0xF20DFF00;        // NUM 200+
// uint32_t   NUM1  = 0xF30CFF00;        // NUM1
// uint32_t   NUM2  = 0xE718FF00;        // NUM2
// uint32_t   NUM3  = 0xA15EFF00;        // NUM3
// uint32_t   NUM4  = 0xF708FF00;        // NUM4
// uint32_t   NUM5  = 0xE31CFF00;        // NUM5
// uint32_t   NUM6  = 0xA55AFF00;        // NUM6
// uint32_t   NUM7  = 0xBD42FF00;        // NUM7
// uint32_t   NUM8  = 0xAD52FF00;        // NUM8
// uint32_t   NUM9  = 0xB54AFF00;        // NUM9

void setup()
{
  IrReceiver.begin(irRevPin, ENABLE_LED_FEEDBACK);   // Start the receiver
  Serial.begin(9600);
}


void loop() {
  if (IrReceiver.decode()) {
    rawData = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(rawData, HEX);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}
