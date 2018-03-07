#include "B4RDefines.h"

B4R::Serial* b4r_main::_serial1;
B4R::D1Pins* b4r_main::_d1pins;
B4R::Timer* b4r_main::_timer1;
B4R::Pin* b4r_main::_pin16;
B4R::Pin* b4r_main::_pin2;
B4R::Pin* b4r_main::_d6;
static B4R::Serial be_gann1_3;
static B4R::D1Pins be_gann2_3;
static B4R::Timer be_gann3_3;
static B4R::Pin be_gann4_3;
static B4R::Pin be_gann5_3;
static B4R::Pin be_gann6_3;


 void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 30;BA.debugLine="Private Sub AppStart";
 //BA.debugLineNum = 31;BA.debugLine="Serial1.Initialize(115200)";
b4r_main::_serial1->Initialize((ULong) (115200));
 //BA.debugLineNum = 32;BA.debugLine="Log(\"AppStart\")";
B4R::Common::LogHelper(1,102,F("AppStart"));
 //BA.debugLineNum = 37;BA.debugLine="pin16.Initialize(16, pin16.MODE_OUTPUT)";
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
 //BA.debugLineNum = 38;BA.debugLine="pin2.Initialize(2, pin2.MODE_OUTPUT)";
b4r_main::_pin2->Initialize((Byte) (2),Pin_MODE_OUTPUT);
 //BA.debugLineNum = 39;BA.debugLine="d6.Initialize(d1pins.D6, d6.MODE_OUTPUT)";
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
 //BA.debugLineNum = 40;BA.debugLine="d6.DigitalWrite(False)";
b4r_main::_d6->DigitalWrite(Common_False);
 //BA.debugLineNum = 41;BA.debugLine="Timer1.Initialize(\"Timer1_Tick\", 5000) 'For Andy:";
b4r_main::_timer1->Initialize(_timer1_tick,(ULong) (5000));
 //BA.debugLineNum = 42;BA.debugLine="Timer1.Enabled = True";
b4r_main::_timer1->setEnabled(Common_True);
 //BA.debugLineNum = 43;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}

void b4r_main::initializeProcessGlobals() {
     B4R::StackMemory::buffer = (byte*)malloc(STACK_BUFFER_SIZE);
     b4r_main::_process_globals();

   
}
void b4r_main::_process_globals(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 8;BA.debugLine="Sub Process_Globals";
 //BA.debugLineNum = 11;BA.debugLine="Public Serial1 As Serial";
b4r_main::_serial1 = &be_gann1_3;
 //BA.debugLineNum = 12;BA.debugLine="Private d1pins As D1Pins";
b4r_main::_d1pins = &be_gann2_3;
 //BA.debugLineNum = 13;BA.debugLine="Private Timer1 As Timer";
b4r_main::_timer1 = &be_gann3_3;
 //BA.debugLineNum = 14;BA.debugLine="Private pin16 As Pin";
b4r_main::_pin16 = &be_gann4_3;
 //BA.debugLineNum = 15;BA.debugLine="Private pin2 As Pin";
b4r_main::_pin2 = &be_gann5_3;
 //BA.debugLineNum = 16;BA.debugLine="Private d6 As Pin";
b4r_main::_d6 = &be_gann6_3;
 //BA.debugLineNum = 17;BA.debugLine="End Sub";
}
void b4r_main::_timer1_tick(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 45;BA.debugLine="Private Sub Timer1_Tick";
 //BA.debugLineNum = 46;BA.debugLine="Log(\"CurrentState: \", d6.DigitalRead)";
B4R::Common::LogHelper(2,102,F("CurrentState: "),8,b4r_main::_d6->DigitalRead());
 //BA.debugLineNum = 47;BA.debugLine="d6.DigitalWrite(Not( d6.DigitalRead))";
b4r_main::_d6->DigitalWrite(Common_Not(b4r_main::_d6->DigitalRead()));
 //BA.debugLineNum = 48;BA.debugLine="Log(\"NewState: \", d6.DigitalRead)";
B4R::Common::LogHelper(2,102,F("NewState: "),8,b4r_main::_d6->DigitalRead());
 //BA.debugLineNum = 50;BA.debugLine="pin16.DigitalWrite(Not(pin16.DigitalRead))";
b4r_main::_pin16->DigitalWrite(Common_Not(b4r_main::_pin16->DigitalRead()));
 //BA.debugLineNum = 51;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
