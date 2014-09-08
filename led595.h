#ifndef LED595_H
#define LED595_H

/*
 * Led595
 *
 * Uses a 74HC595 shift register to print text on a 7seg display
 *
 * 2014 rccursach
 * rccursach.blogspot.com
 */

#include <Arduino.h>

//fonts has the form:

//  aaa
// f   b
// f   b
//  ggg
// e   c
// e   c
//  ddd  xx

 PROGMEM const prog_char fonts[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
    0b11101110, // 10  "A"
    0b00111110, // 11  "B"
    0b10011100, // 12  "C"
    0b01111010, // 13  "D"
    0b10011110, // 14  "E"
    0b10001110, // 15  "F"
    0b00000000, // 16  NO DISPLAY
    0b00000000, // 17  NO DISPLAY
    0b00000000, // 18  NO DISPLAY
    0b00000000, // 19  NO DISPLAY
    0b00000000, // 20  NO DISPLAY
    0b00000000, // 21  NO DISPLAY
    0b00000000, // 22  NO DISPLAY
    0b00000000, // 23  NO DISPLAY
    0b00000000, // 24  NO DISPLAY
    0b00000000, // 25  NO DISPLAY
    0b00000000, // 26  NO DISPLAY
    0b00000000, // 27  NO DISPLAY
    0b00000000, // 28  NO DISPLAY
    0b00000000, // 29  NO DISPLAY
    0b00000000, // 30  NO DISPLAY
    0b00000000, // 31  NO DISPLAY
    0b00000000, // 32 ' '
    0b01100001, // 33 '!'
    0b01000100, // 34 '"'
    0b00000000, // 35 '#'  NO DISPLAY
    0b00000000, // 36 '$'  NO DISPLAY
    0b00000000, // 37 '%'  NO DISPLAY
    0b00000000, // 38 '&'  NO DISPLAY
    0b01000000, // 39 '''
    0b10011100, // 40 '('
    0b11110000, // 41 ')'
    0b00000000, // 42 '*'  NO DISPLAY
    0b00000000, // 43 '+'  NO DISPLAY
    0b00000001, // 44 ','
    0b00000010, // 45 '-'
    0b00000001, // 46 '.'
    0b00000000, // 47 '/'  NO DISPLAY
    0b11111100, // 48 '0'
    0b01100000, // 49 '1'
    0b11011010, // 50 '2'
    0b11110010, // 51 '3'
    0b01100110, // 52 '4'
    0b10110110, // 53 '5'
    0b10111110, // 54 '6'
    0b11100000, // 55 '7'
    0b11111110, // 56 '8'
    0b11110110, // 57 '9'
    0b00000000, // 58 ':'  NO DISPLAY
    0b00000000, // 59 ';'  NO DISPLAY
    0b00000000, // 60 '<'  NO DISPLAY
    0b00010010, // 61 '='
    0b00000000, // 62 '>'  NO DISPLAY
    0b00000000, // 63 '?'  NO DISPLAY
    0b00000000, // 64 '@'  NO DISPLAY
    0b11101110, // 65 'A'
    0b00111110, // 66 'B'
    0b10011100, // 67 'C'
    0b01111010, // 68 'D'
    0b10011110, // 69 'E'
    0b10001110, // 70 'F'
    0b10111100, // 71 'G'
    0b01101110, // 72 'H'
    0b01100000, // 73 'I'
    0b01110000, // 74 'J'
    0b00000000, // 75 'K'  NO DISPLAY
    0b00011100, // 76 'L'
    0b00000000, // 77 'M'  NO DISPLAY
    0b00101010, // 78 'N'
    0b11111100, // 79 'O'
    0b11001110, // 80 'P'
    0b11100110, // 81 'Q'
    0b00001010, // 82 'R'
    0b10110110, // 83 'S'
    0b00011110, // 84 'T'
    0b01111100, // 85 'U'
    0b00000000, // 86 'V'  NO DISPLAY
    0b00000000, // 87 'W'  NO DISPLAY
    0b00000000, // 88 'X'  NO DISPLAY
    0b01110110, // 89 'Y'
    0b11011010, // 90 'Z'
    0b10011100, // 91 '['
    0b00000000, // 92 '\'  NO DISPLAY
    0b11110000, // 93 ']'
    0b00000000, // 94 '^'  NO DISPLAY
    0b00010000, // 95 '_'
    0b00000100, // 96 '`'
    0b11101110, // 97 'a' SAME AS CAP
    0b00111110, // 98 'b' SAME AS CAP
    0b00011010, // 99 'c'
    0b01111010, // 100 'd' SAME AS CAP
    0b11011110, // 101 'e'
    0b10001110, // 102 'f' SAME AS CAP
    0b10111100, // 103 'g' SAME AS CAP
    0b00101110, // 104 'h'
    0b00100000, // 105 'i'
    0b01110000, // 106 'j' SAME AS CAP
    0b00000000, // 107 'k'  NO DISPLAY
    0b01100000, // 108 'l'
    0b00000000, // 109 'm'  NO DISPLAY
    0b00101010, // 110 'n' SAME AS CAP
    0b00111010, // 111 'o'
    0b11001110, // 112 'p' SAME AS CAP
    0b11100110, // 113 'q' SAME AS CAP
    0b00001010, // 114 'r' SAME AS CAP
    0b10110110, // 115 's' SAME AS CAP
    0b00011110, // 116 't' SAME AS CAP
    0b00111000, // 117 'u'
    0b00000000, // 118 'b'  NO DISPLAY
    0b00000000, // 119 'w'  NO DISPLAY
    0b00000000, // 120 'x'  NO DISPLAY
    0b01110110, // 121 'y'
    0b11011010, // 122 'z'
    0b00000000, // 123 '0b'  NO DISPLAY
    0b00001100, // 124 '|'
    0b00000001, // 125 ','
    0b00000000, // 126 '~'  NO DISPLAY
    0b00000000, // 127 'DEL'  NO DISPLAY
  };

class Led595{
public:
  Led595(int* digitPins, int dp_size, int clock, int latch, int data);
  ~Led595();
  
  void printString(char* str);
  void rotateText(boolean rotate);
  
  void start(void(*fun)());

  void refreshInterrupt(); //callback function for automatic timed screen refreshing

private:
  
  int* dp;         //Digit pins
  int digitsCount; //How much digits are
  
  int cl;          //595's Clock, Latch and Data pins
  int la;
  int da;
  
  char* text;
  
  boolean lockDisplay;  //lock display to avoid refresInterrupt() to use "char* text" if a call to printString() is on course.
  boolean rotate;
  
  int led_on;
  int led_off;

};

#endif
