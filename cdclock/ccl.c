#include <stdio.h>
#include <wiringPi.h>

/* So here's how it seems to work.
 * set a bit, kick the clock it sends the bit
 * once you have sent all the bits for all 8 digits
 * you kick the latch to present it.
 */

// array to activate particular digit on the 8x7segment module
// it is the common anode of 7 segment
//int anode[] =
//  { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

// array for decimal number, it is the cathode, please refer to the datasheet.
// therefore a logic low will activate the particular segment
// PGFEDCBA, segment on 7 segment, P is the dot

#define b10000000 0x80
#define b01000000 0x40
#define b00100000 0x20
#define b00010000 0x10
#define b00001000 0x08
#define b00000100 0x04
#define b00000010 0x02
#define b00000001 0x01

#define b11000000 192
#define b11111001 249
#define b10100100 164
#define b10110000 176
#define b10011001 153
#define b10010010 146
#define b10000010 130
#define b11111000 248
//#define b10000000 128
#define b10010000 144
#define b01111111 127
#define b11111111 255

int anode[] =
  {
  b10000000, // digit 1 from right
      b01000000, // digit 2 from right
      b00100000, // digit 3 from right
      b00010000, // digit 4 from right
      b00001000, // digit 5 from right
      b00000100, // digit 6 from right
      b00000010, // digit 7 from right
      b00000001 // digit 8 from right
    };

// array for decimal number, it is the cathode, please refer to the datasheet.
// therefore a logic low will activate the particular segment
// PGFEDCBA, segment on 7 segment, P is the dot

int cathode[] =
  {
  b11000000, // 0
      b11111001, // 1
      b10100100, // 2
      b10110000, // 3
      b10011001, // 4
      b10010010, // 5
      b10000010, // 6
      b11111000, // 7
      b10000000, // 8
      b10010000, // 9
      b01111111, // dot
      b11111111  // blank
    };

//int cathode[] =
//  { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67 };

int LATCH = 4; // RCK of 8x7segment module pin 16

int CLOCK = 16; // SCK of 8x7segment module pin 10

int DATA = 15; // DIO of 8x7segment module,  pin 8

typedef int bool;
typedef int boolean;
#define false 0
#define true (!false)

void init(void)
  {

    wiringPiSetup();
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, OUTPUT);
  }

boolean lastval = false;
void shift(boolean val)
  {
    if (lastval != val)
      {
        int state = val ? HIGH : LOW;
        digitalWrite(DATA, state);
      }
    lastval = val;
    digitalWrite(CLOCK, HIGH);
    digitalWrite(CLOCK, LOW);
  }

void latch()
  {
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
  }

void write(int val)
  {
    // write each bit of val to register
    int i;
    for (i = 0; i < 8; i++)
      shift(((val << i) & b10000000) != 0);
  }

void displaynumber(int position, int value)
  {
    int p = anode[position];
    int v = cathode[value];
    write(p);
    write(v);
  }

void go()
  {
    init();

    int ary[8];
    int lp;
    for (lp = 0; lp < 8; lp++)
      ary[lp] = 0;
    while (true)
      {
        int highdigit = 7;
        int carry = 1;
        for (lp = 7; lp >= 0; lp--)
          {
            ary[lp] += carry;
            if ((ary[lp] == 10) && (carry == 1))
              {
                carry = 1;
                ary[lp] = 0;
              }
            else
              carry = 0;
            if (ary[lp] > 0)
              highdigit = lp;
          }
        int rp;
        for (rp = 7; rp >= highdigit; rp--)
          {
            displaynumber(7 - rp, ary[rp]);
            latch();
            delay(1);
          }
      }
  }

int invert(int v)
  {
    int lp;
    int out = 0;
    for (lp = 0; lp < 8; lp++)
      {
        int b = v % 2;
        v = v / 2;
        out *= 2;
        out += b;
      }
    return out;
  }

int main(int num, char *opts[])
  {
    go();
    return 0;
  }

#define LED 0
int blink_main(void)
  {
    printf("Raspberry Pi blink\n");

    wiringPiSetup();
    pinMode(LED, OUTPUT);

    for (;;)
      {
        digitalWrite(LED, HIGH);  // On
        delay(500);   // mS
        digitalWrite(LED, LOW); // Off
        delay(500);
      }
    return 0;
  }

