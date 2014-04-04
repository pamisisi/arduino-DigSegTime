#include "DigSegTime.h"



DigSegTime::DigSegTime(boolean mode, uint8_t seg1_pin, uint8_t seg2_pin,
			uint8_t seg3_pin, uint8_t seg4_pin, uint8_t sega_pin,
			uint8_t segb_pin, uint8_t segc_pin, uint8_t segd_pin,
			uint8_t sege_pin, uint8_t segf_pin, uint8_t segg_pin,
		uint8_t segdp_pin){
	mode_ = mode;
	// true 代表共阳, false 代表共阴
  	if (mode_){
	    DigitOn_ = HIGH;
	    DigitOff_ = LOW;
	    SegOn_ = LOW;
	    SegOff_ = HIGH;
  	}else {
	    DigitOn_ = LOW;
	    DigitOff_ = HIGH;
	    SegOn_ = HIGH;
	    SegOff_ = LOW;
  	}

  	DigitPins[0]=seg1_pin;
	DigitPins[1]=seg2_pin;
	DigitPins[2]=seg3_pin;
	DigitPins[3]=seg4_pin;
	SegmentPins[0]=sega_pin;
	SegmentPins[1]=segb_pin;
	SegmentPins[2]=segc_pin;
	SegmentPins[3]=segd_pin;
	SegmentPins[4]=sege_pin;
	SegmentPins[5]=segf_pin;
	SegmentPins[6]=segg_pin;
	SegmentPins[7]=segdp_pin;

	// 配置IO为输出
	for(uint8_t digit=0; digit<4; digit++){
		pinMode(DigitPins[digit],OUTPUT);
	}

	for(uint8_t seg=0; seg<8; seg++){
		pinMode(SegmentPins[seg],OUTPUT);
	}

	clean();

	brightness_ = 1;
}

void DigSegTime::brightness(uint8_t brightness) {
	brightness_ = constrain(brightness, 1, 10);
	brightness_ = map(brightness_,1, 10, 10, 1000);
}

void DigSegTime::scan() {
	for(uint8_t seg=0; seg<8; seg++) {
		digitalWrite(SegmentPins[seg],SegOn_);
		for(uint8_t digit=0; digit<4; digit++){
			if(lights[digit][seg] == true){
				digitalWrite(DigitPins[digit],DigitOn_);
			}
		}
		delayMicroseconds(brightness_);
		for(uint8_t digit=0; digit<4; digit++){
			digitalWrite(DigitPins[digit],DigitOff_);
		}
		digitalWrite(SegmentPins[seg],SegOff_);
	}
}


void DigSegTime::print(char c){
	numberCode_ [0] = c;
	numberCode_ [1] = ' ';
	numberCode_ [2] = ' ';
	numberCode_ [3] = ' ';
	compile();
}

void DigSegTime::print(char c, uint8_t i){
	numberCode_ [0] = ' ';
	numberCode_ [1] = ' ';
	numberCode_ [2] = ' ';
	numberCode_ [3] = ' ';
	numberCode_ [(i-1)] = c;
	compile();
}

void DigSegTime::printChange(char c, uint8_t i){
	numberCode_ [(i-1)] = c;
	compile();
}

void DigSegTime::print(char c, uint8_t i, uint8_t dp){
	numberCode_ [0] = ' ';
	numberCode_ [1] = ' ';
	numberCode_ [2] = ' ';
	numberCode_ [3] = ' ';
	numberCode_ [(i-1)] = c;
	compile();
	printDp(dp);
}

void DigSegTime::print(const String &s){
	numberCode_ [0] = s[0];
	numberCode_ [1] = s[1];
	numberCode_ [2] = s[2];
	numberCode_ [3] = s[3];
	compile();
}

void DigSegTime::print(const String &s, uint8_t dp){
	numberCode_ [0] = s[0];
	numberCode_ [1] = s[1];
	numberCode_ [2] = s[2];
	numberCode_ [3] = s[3];
	compile();
	printDp(dp);
}

void DigSegTime::print(int number) {
	String str = String(number);
	numberCode_ [0] = str[0];
	numberCode_ [1] = str[1];
	numberCode_ [2] = str[2];
	numberCode_ [3] = str[3];
	compile();
}

void DigSegTime::print(unsigned int number) {
	String str = String(number);
	numberCode_ [0] = str[0];
	numberCode_ [1] = str[1];
	numberCode_ [2] = str[2];
	numberCode_ [3] = str[3];
	compile();
}

void DigSegTime::printHr(const String &s) {
	numberCode_ [0] = s[0];
	numberCode_ [1] = s[1];
	compile();
}

void DigSegTime::printMin(const String &s) {
	numberCode_ [2] = s[0];
	numberCode_ [3] = s[1];
	compile();
}

void DigSegTime::printHr(uint8_t hr) {
	numberCode_ [0] = (hr / 10) + '0';
	numberCode_ [1] = (hr % 10) + '0';
	compile();
}

void DigSegTime::printMin(uint8_t min) {
	numberCode_ [2] = (min / 10) + '0';
	numberCode_ [3] = (min % 10) + '0';
	compile();
}

void DigSegTime::printTime(uint8_t hr, uint8_t min) {
	numberCode_ [0] = (hr / 10) + '0';
	numberCode_ [1] = (hr % 10) + '0';

	numberCode_ [2] = (min / 10) + '0';
	numberCode_ [3] = (min % 10) + '0';
	compile();
}


void DigSegTime::printTime(const String &s, uint8_t min) {
	numberCode_ [0] = s[0];
	numberCode_ [1] = s[1];

	numberCode_ [2] = (min / 10) + '0';
	numberCode_ [3] = (min % 10) + '0';
	compile();
}

void DigSegTime::printTime(uint8_t hr, const String &s) {
	numberCode_ [2] = s[0];
	numberCode_ [3] = s[1];
	numberCode_ [0] = (hr / 10) + '0';
	numberCode_ [1] = (hr % 10) + '0';
	compile();
}

void DigSegTime::printTime(const String &s1, const String &s2) {
	numberCode_ [0] = s1[0];
	numberCode_ [1] = s1[1];

	numberCode_ [2] = s2[0];
	numberCode_ [3] = s2[1];
	compile();
}



/**
*	显示几个点数
*	dpNumber 点数 0 ~ 3;

void DigSegTime::printDp(uint8_t dpNumber) {
	switch(dpNumber){
		case 1:	//显示一个点
			lights[0][7] = true;
			lights[1][7] = false;
			break;
		case 2: //显示两个点
			lights[0][7] = false;
			lights[1][7] = true;
			break;
		case 3: //显示三个点
			lights[0][7] = true;
			lights[1][7] = true;
			break;
		default:
			lights[0][7] = false;
			lights[1][7] = false;
	}
}
*/

/** 某某产的4位数码管得用这个才能正确显示几个点*/
void DigSegTime::printDp(uint8_t dpNumber) {
	switch(dpNumber){
		case 1:
			lights[2][7] = false;
			lights[3][7] = true;
			break;
		case 2:
			lights[2][7] = true;
			lights[3][7] = true;
			break;
		case 3:
			lights[2][7] = true;
			lights[3][7] = true;
			break;
		default:
			lights[2][7] = false;
			lights[3][7] = false;
	}
}

/**
*	把 numberCode_ 字符数组 转换成须显示的高低电平状态  lights[][];
*   想要显示其它的字符请在此函数内增加对应的代码
*/
void DigSegTime::compile() {
	for(uint8_t len=0; len<4; len++){
		switch(numberCode_ [len]){
			case ' ':
				lights[len][0] = false;
				lights[len][1] = false;
				lights[len][2] = false;
				lights[len][3] = false;
				lights[len][4] = false;
				lights[len][5] = false;
				lights[len][6] = false;
				break;
			case '0':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = false;
				break;
			case '1':
				lights[len][0] = false;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = false;
				lights[len][4] = false;
				lights[len][5] = false;
				lights[len][6] = false;
				break;
			case '2':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = false;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = false;
				lights[len][6] = true;
				break;
			case '3':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = false;
				lights[len][5] = false;
				lights[len][6] = true;
				break;
			case '4':
				lights[len][0] = false;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = false;
				lights[len][4] = false;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case '5':
				lights[len][0] = true;
				lights[len][1] = false;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = false;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case '6':
				lights[len][0] = true;
				lights[len][1] = false;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case '7':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = false;
				lights[len][4] = false;
				lights[len][5] = false;
				lights[len][6] = false;
				break;
			case '8':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case '9':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = false;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case 'A':
				lights[len][0] = true;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = false;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case 'B':
				lights[len][0] = false;
				lights[len][1] = false;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case 'C':
				lights[len][0] = true;
				lights[len][1] = false;
				lights[len][2] = false;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = false;
				break;
			case 'D':
				lights[len][0] = false;
				lights[len][1] = true;
				lights[len][2] = true;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = false;
				lights[len][6] = true;
				break;
			case 'E':
				lights[len][0] = true;
				lights[len][1] = false;
				lights[len][2] = false;
				lights[len][3] = true;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case 'F':
				lights[len][0] = true;
				lights[len][1] = false;
				lights[len][2] = false;
				lights[len][3] = false;
				lights[len][4] = true;
				lights[len][5] = true;
				lights[len][6] = true;
				break;
			case '-':
				lights[len][0] = false;
				lights[len][1] = false;
				lights[len][2] = false;
				lights[len][3] = false;
				lights[len][4] = false;
				lights[len][5] = false;
				lights[len][6] = true;
				break;
			default:
				lights[len][0] = false;
				lights[len][1] = false;
				lights[len][2] = false;
				lights[len][3] = false;
				lights[len][4] = false;
				lights[len][5] = false;
				lights[len][6] = false;
		}
	}
	
}

// 清屏无显示
void DigSegTime::clean() {
	for(uint8_t digit=0; digit<4; digit++){
		digitalWrite(DigitPins[digit], DigitOff_);
	}

	for(uint8_t seg=0; seg<8; seg++){
		digitalWrite(SegmentPins[seg], SegOff_);
	}
}
