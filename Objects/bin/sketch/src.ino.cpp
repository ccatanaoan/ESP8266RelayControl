#include <Arduino.h>
#line 1 "C:\\Users\\ccatanaoan\\Desktop\\IoT\\Relay Control\\Relay Control for Andy\\src\\src.ino"
#line 1 "C:\\Users\\ccatanaoan\\Desktop\\IoT\\Relay Control\\Relay Control for Andy\\src\\src.ino"
#include "B4RDefines.h"

#line 3 "C:\\Users\\ccatanaoan\\Desktop\\IoT\\Relay Control\\Relay Control for Andy\\src\\src.ino"
void setup();
#line 8 "C:\\Users\\ccatanaoan\\Desktop\\IoT\\Relay Control\\Relay Control for Andy\\src\\src.ino"
void loop();
#line 3 "C:\\Users\\ccatanaoan\\Desktop\\IoT\\Relay Control\\Relay Control for Andy\\src\\src.ino"
void setup() {
	b4r_main::initializeProcessGlobals();
	b4r_main::_appstart();
}

void loop() {
	while (true) {
		B4R::scheduler.loop();
	}
}







