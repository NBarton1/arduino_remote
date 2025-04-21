#include "IRremote.hpp"

// pin locations
const byte LED[] = { 2, 3, 4, 5, 6, 7 };
#define IR_RECEIVE_PIN 21

// command numbers for my remote
#define POWER 69
#define VOL_UP 70
#define FUNC 71
#define PREV 68
#define PLAY 64
#define NEXT 67
#define DOWN 7
#define VOL_DOWN 21
#define UP 9
#define ZERO 22
#define EQ 25
#define ST_REPT 13
#define ONE 12
#define TWO 24
#define THREE 94
#define FOUR 8
#define FIVE 28
#define SIX 90
#define SEVEN 66
#define EIGHT 82
#define NINE 74

#define IR_INTERVAL 100
#define COUNT_INTERVAL 500

byte LED_COUNT = sizeof(LED) / sizeof(LED[0]);
int mask = (1 << LED_COUNT) - 1;

int count = 0;
bool on = true;
bool play = true;

void write_LEDs() {
  for (int i=0; i<LED_COUNT; i++)
    digitalWrite(LED[i], on ? count & (1 << i) : LOW);
}

void c(int n) {
  count = n & mask;
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  for (int i=0; i<LED_COUNT; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
  }
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.flags != IRDATA_FLAGS_IS_REPEAT) {
      uint16_t command = IrReceiver.decodedIRData.command;

      if (on || command == POWER) {
        switch (command) {
          case POWER: {
            on = !on;
            Serial.println(on ? "ON" : "OFF");
            break;
          }
          case FUNC: {
            break;
          }
          case PREV: {
            c(count << 1);
            break;
          }
          case NEXT: {
            c(count >> 1);
            break;
          }
          case PLAY: {
            play = !play;
            Serial.println(play ? "PLAY" : "PAUSE");
            break;
          }
          case UP: {
            break;
          }
          case DOWN: {
            break;
          }
          case VOL_UP: {
            break;
          }
          case VOL_DOWN: {
            break;
          }
          case EQ: {
            break;
          }
          case ST_REPT: {
            break;
          }
          case ZERO: {
            break;
          }
          case ONE: {
            break;
          }
          case TWO: {
            break;
          }
          case THREE: {
            break;
          }
          case FOUR: {
            break;
          }
          case FIVE: {
            break;
          }
          case SIX: {
            break;
          }
          case SEVEN: {
            break;
          }
          case EIGHT: {
            break;
          }
          case NINE: {
            break;
          }
          default: {
            Serial.print("unknown button: ");
            Serial.println(command);
          }
        }
      }
    }

    IrReceiver.resume();
    delay(IR_INTERVAL);
  } else if (on && play) {
    c(count+1);
    delay(COUNT_INTERVAL);
  }

  write_LEDs();
}