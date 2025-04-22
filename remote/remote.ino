#include "IRremote.hpp"

// pin locations
const byte SEGMENT_PIN[] = { 2, 3, 4, 5, 6, 7, 8, 13 };  // A B C D E F G DP
const byte DIGIT_PIN[] = { 9, 10, 11, 12 };
#define IR_RECEIVE_PIN 21

#define SEGMENTS 8
#define DIGITS 4

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
#define TIMER_INTERVAL 1000

#define SS0 0b11111100
#define SS1 0b01100000
#define SS2 0b11011010
#define SS3 0b11110010
#define SS4 0b01100110
#define SS5 0b10110110
#define SS6 0b10111110
#define SS7 0b11100000
#define SS8 0b11111110
#define SS9 0b11100110

#define INCREMENT 10

int timer = 0;
bool on = true;
bool play = false;

unsigned long last_update;

void ss_write_digit(byte display, byte num) {
  byte digit;
  switch (num) {
    case 0: digit = SS0; break;
    case 1: digit = SS1; break;
    case 2: digit = SS2; break;
    case 3: digit = SS3; break;
    case 4: digit = SS4; break;
    case 5: digit = SS5; break;
    case 6: digit = SS6; break;
    case 7: digit = SS7; break;
    case 8: digit = SS8; break;
    case 9: digit = SS9; break;
    default: 
      Serial.print(timer);
      Serial.print(" ss_write_digit unrecognized digit: ");
      Serial.println(num); 
      return;
  }

  for (int i=0; i<SEGMENTS; i++)
    digitalWrite(SEGMENT_PIN[SEGMENTS-i-1], on ? digit & (1 << i) : LOW);
  digitalWrite(DIGIT_PIN[display], LOW);
  delay(1);
  digitalWrite(DIGIT_PIN[display], HIGH);
}

void ss_write() {
  int write = timer;
  for (int i=DIGITS-1; i>=0; i--) {
    if (write == 0 && i != DIGITS-1) break;
    ss_write_digit(i, write % 10);
    write /= 10;
  }
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  for (int i=0; i<SEGMENTS; i++)
    pinMode(SEGMENT_PIN[i], OUTPUT);
  for (int i=0; i<DIGITS; i++) {
    pinMode(DIGIT_PIN[i], OUTPUT);
    digitalWrite(DIGIT_PIN[i], HIGH);
  }

  last_update = millis();
}

void loop() {
  unsigned long time = millis();

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
            break;
          }
          case NEXT: {
            break;
          }
          case PLAY: {
            play = !play;
            Serial.println(play ? "PLAY" : "PAUSE");
            break;
          }
          case UP: {
            timer += INCREMENT;
            break;
          }
          case DOWN: {
            timer -= INCREMENT;
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
            timer = timer * 10;
            Serial.println(timer);
            break;
          }
          case ONE: {
            timer = timer * 10 + 1;
            Serial.println(timer);
            break;
          }
          case TWO: {
            timer = timer * 10 + 2;
            Serial.println(timer);
            break;
          }
          case THREE: {
            timer = timer * 10 + 3;
            Serial.println(timer);
            break;
          }
          case FOUR: {
            timer = timer * 10 + 4;
            Serial.println(timer);
            break;
          }
          case FIVE: {
            timer = timer * 10 + 5;
            Serial.println(timer);
            break;
          }
          case SIX: {
            timer = timer * 10 + 6;
            Serial.println(timer);
            break;
          }
          case SEVEN: {
            timer = timer * 10 + 7;
            Serial.println(timer);
            break;
          }
          case EIGHT: {
            timer = timer * 10 + 8;
            Serial.println(timer);
            break;
          }
          case NINE: {
            timer = timer * 10 + 9;
            Serial.println(timer);
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
  } else if (on && play && time - last_update >= TIMER_INTERVAL && timer > 0) {
    last_update = time;
    timer--;
  }

  timer = min(max(timer, 0), 9999);
  if (timer == 0)
    play = false;
  ss_write();
}