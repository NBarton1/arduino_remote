#include "IRremote.hpp"

// pin locations
#define YELLOW_LED_PIN 6
#define IR_RECEIVE_PIN 5

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

bool on = HIGH;
bool yellow_state = LOW;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pinMode(YELLOW_LED_PIN, OUTPUT);
  digitalWrite(YELLOW_LED_PIN, yellow_state & on);
}

void loop() {
  if (IrReceiver.decode() && IrReceiver.decodedIRData.flags != IRDATA_FLAGS_IS_REPEAT) {
    uint16_t command = IrReceiver.decodedIRData.command;

    if (on || command == POWER) {
      switch (command) {
        case POWER: {
          on = !on;
          break;
        }
        case VOL_UP: {
          break;
        }
        case FUNC: {
          break;
        }
        case PREV: {
          break;
        }
        case PLAY: {
          yellow_state = !yellow_state;
          digitalWrite(YELLOW_LED_PIN, yellow_state);
          break;
        }
        case NEXT: {
          break;
        }
        case DOWN: {
          break;
        }
        case VOL_DOWN: {
          break;
        }
        case UP: {
          break;
        }
        case ZERO: {
          break;
        }
        case EQ: {
          break;
        }
        case ST_REPT: {
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
    
    delay(100);
    IrReceiver.resume();
  }
}