/*  Andy's Hydroponic Pump Relay Controller
 *  
 *  Periodically turns on and off the relay to power on and off the hydroponic pump.
 *  
 *  Created 2018
 *  by Cloyd Nino Catanaoan and Andy Pierson
 */
 
#include "B4RDefines.h"

B4R::Serial* b4r_main::_serial1;
B4R::D1Pins* b4r_main::_d1pins;
B4R::Pin* b4r_main::_pin16;
B4R::Pin* b4r_main::_d6;
static B4R::Serial be_gann1_3;
static B4R::D1Pins be_gann2_3;
static B4R::Pin be_gann3_3;
static B4R::Pin be_gann4_3;


 void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
 
b4r_main::_serial1->Initialize((ULong) (115200));
B4R::Common::LogHelper(1,102,F("AppStart"));
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
_relayopen((Byte) (0));
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
}
void b4r_main::_relayclose(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::Common::LogHelper(1,102,F("Relay Close"));
b4r_main::_d6->DigitalWrite(Common_True);
b4r_main::_pin16->DigitalWrite(Common_True);
//******************************************* CHANGE THE DELAY HERE *********************************************************************
// Andy, change the (XXXX) value to how long you want the relay to stay close. For two hours, 1000 ms * 60 sec * 60 min * 2 hr = 7200000.
B4R::__c->CallSubPlus(_relayopen,(ULong) (15000),(Byte) (0));
//***************************************************************************************************************************************
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopen(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::Common::LogHelper(1,102,F("Relay Open"));
b4r_main::_d6->DigitalWrite(Common_False);
b4r_main::_pin16->DigitalWrite(Common_False);
//******************************************* CHANGE THE DELAY HERE *********************************************************************
// Andy, change the (XXXX) value to how long you want the relay to stay open. For 20 minutes, 1000 ms * 60 sec * 20 min = 1200000.
B4R::__c->CallSubPlus(_relayclose,(ULong) (5000),(Byte) (0));
//***************************************************************************************************************************************
B4R::StackMemory::cp = cp;
}
