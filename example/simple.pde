#include <DigSegTime.h>

// 第1个参数 0 代表共阴 ,1代表共阳 1~4脚, a~g+dp脚
DigSegTime dst(1, 4,7,8,A0, 5,9,A2,A4,A5,6,A1,A3);

unsigned long times;
unsigned int ms;

boolean sect;

void setup() {

	dst.brightness(20);
	times = millis();
	//dst.print("ABCD");
	//dst.printTime(23,12);
	dst.printHr("AB");
	dst.printMin(12);

	// 更详细的printXX 方法请查看 DigSegTime.h 文件
}

void loop() {
	dst.scan();     //扫描 loop 内不能有延时函数不然无法正常工作
	/*
	unsigned long mill = millis();
	if(mill - times >= 10){
		times = mill;
		
		sect = !sect;
		if(sect){
			dst.printDp(1);
		}else{
			dst.printDp(0);
		}

		ms++;
		dst.print(ms);
	}
	*/
}
