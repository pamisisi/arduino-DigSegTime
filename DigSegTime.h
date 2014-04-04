#ifndef DigSegTime_h
#define DigSegTime_h

#include <Arduino.h>
/**		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F , 无		*/
const static unsigned char segCode[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00};

class DigSegTime {
	public:
		DigSegTime(boolean mode, uint8_t seg1_pin, uint8_t seg2_pin, 
			uint8_t seg3_pin, uint8_t seg4_pin, uint8_t sega_pin,
			uint8_t segb_pin, uint8_t segc_pin, uint8_t segd_pin,
			uint8_t sege_pin, uint8_t segf_pin, uint8_t segg_pin,
		uint8_t segdp_pin);

		void brightness(uint8_t brightness);
		void scan (void);
		
		void print(char c);
		void print(char c, uint8_t i);
		void print(char c, uint8_t i, uint8_t dp);
		void print(const String &s);
		void print(const String &s, uint8_t dp);
		void print(int number);
		void print(unsigned int number);
		void printHr(const String &s);
		void printMin(const String &s);
		void printHr(uint8_t hr);
		void printMin(uint8_t min);
		void printTime(uint8_t hr, uint8_t min);
		void printTime(const String &s1, const String &s2);
		void printTime(const String &s, uint8_t min);
		void printTime(uint8_t hr, const String &s);

		void printChange(char c, uint8_t i);
		
		void printDp(uint8_t dpNumber);

	private:
		boolean mode_, DigitOn_, DigitOff_, SegOn_, SegOff_;
		int brightness_;
		char numberCode_ [4];
		boolean lights[4][8];
		uint8_t DigitPins[4];
  		uint8_t SegmentPins[8];

  		void clean();
  		void compile();
};

#endif