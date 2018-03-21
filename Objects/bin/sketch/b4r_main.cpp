#include "B4RDefines.h"

B4R::Serial* b4r_main::_serial1;
B4R::D1Pins* b4r_main::_d1pins;
B4R::Pin* b4r_main::_pin16;
B4R::Pin* b4r_main::_d6;
B4R::Pin* b4r_main::_d3;
B4R::B4RESPWiFi* b4r_main::_wifi;
B4R::B4RESP8266* b4r_main::_esp;
B4R::B4RString* b4r_main::_relayopenhydroponicdelay;
B4R::B4RString* b4r_main::_relayclosehydroponicdelay;
B4R::B4RString* b4r_main::_relayopengrowlightdelay;
B4R::B4RString* b4r_main::_relayclosegrowlightdelay;
B4R::B4REEPROM* b4r_main::_eeprom;
static B4R::Serial be_gann1_3;
static B4R::D1Pins be_gann2_3;
static B4R::Pin be_gann3_3;
static B4R::Pin be_gann4_3;
static B4R::Pin be_gann5_3;
static B4R::B4RESPWiFi be_gann6_3;
static B4R::B4RESP8266 be_gann7_3;
static B4R::B4RString be_gann8_5;
static B4R::B4RString be_gann9_5;
static B4R::B4RString be_gann10_5;
static B4R::B4RString be_gann11_5;
static B4R::B4REEPROM be_gann12_3;


void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
b4r_main::_serial1->Initialize((ULong) (115200));
Common_Delay((ULong) (3000));
B4R::Common::LogHelper(1,102,F("AppStart"));
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
b4r_main::_d3->Initialize(b4r_main::_d1pins->D3,Pin_MODE_OUTPUT);
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
b4r_main::_pin16->DigitalWrite(Common_True);
_relayopenhydroponic((Byte) (0));
_relayopengrowlight((Byte) (0));
B4R::StackMemory::cp = cp;
}

void b4r_main::initializeProcessGlobals() {
     B4R::StackMemory::buffer = (byte*)malloc(STACK_BUFFER_SIZE);
     b4r_main::_process_globals();  
}
void b4r_main::_process_globals(){
const UInt cp = B4R::StackMemory::cp;
b4r_main::_serial1 = &be_gann1_3;
b4r_main::_d1pins = &be_gann2_3;
b4r_main::_pin16 = &be_gann3_3;
b4r_main::_d6 = &be_gann4_3;
b4r_main::_d3 = &be_gann5_3;
b4r_main::_wifi = &be_gann6_3;
b4r_main::_esp = &be_gann7_3;

// ****************************************************************
// ************ START - ANDY'S CONFIGURATION **********************
// ****************************************************************

// ************** HYDROPONIC OPEN DURATION ************************
b4r_main::_relayopenhydroponicdelay = be_gann8_5.wrap("2000"); 

// ************** HYDROPONIC CLOSED DURATION **********************
b4r_main::_relayclosehydroponicdelay = be_gann9_5.wrap("10000");

// ************** GROW LIGHT OPEN DURATION ************************
b4r_main::_relayopengrowlightdelay = be_gann10_5.wrap("3000"); 

// ************** GROW LIGHT CLOSED DURATION **********************
b4r_main::_relayclosegrowlightdelay = be_gann11_5.wrap("9000"); 

// ****************************************************************
// ************ END - ANDY'S CONFIGURATION ************************
// ****************************************************************

b4r_main::_eeprom = &be_gann12_3;
}
void b4r_main::_relayclosegrowlight(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::Common::LogHelper(2,102,F("Relay grow light closed. Duration: "),101,b4r_main::_relayclosegrowlightdelay->data);
b4r_main::_d3->DigitalWrite(Common_True);
B4R::__c->CallSubPlus(_relayopengrowlight,(ULong)(atof(b4r_main::_relayclosegrowlightdelay->data)),(Byte) (0));
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayclosehydroponic(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::Common::LogHelper(2,102,F("Relay hydroponic closed. Duration: "),101,b4r_main::_relayclosehydroponicdelay->data);
b4r_main::_d6->DigitalWrite(Common_True);
B4R::__c->CallSubPlus(_relayopenhydroponic,(ULong)(atof(b4r_main::_relayclosehydroponicdelay->data)),(Byte) (0));
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopengrowlight(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::Common::LogHelper(2,102,F("Relay grow light opened. Duration: "),101,b4r_main::_relayopengrowlightdelay->data);
b4r_main::_d3->DigitalWrite(Common_False);
B4R::__c->CallSubPlus(_relayclosegrowlight,(ULong)(atof(b4r_main::_relayopengrowlightdelay->data)),(Byte) (0));
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopenhydroponic(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::Common::LogHelper(2,102,F("Relay hydroponic opened. Duration: "),101,b4r_main::_relayopenhydroponicdelay->data);
b4r_main::_d6->DigitalWrite(Common_False);
B4R::__c->CallSubPlus(_relayclosehydroponic,(ULong)(atof(b4r_main::_relayopenhydroponicdelay->data)),(Byte) (0));
B4R::StackMemory::cp = cp;
}
