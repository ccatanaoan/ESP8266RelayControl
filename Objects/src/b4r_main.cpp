#include "B4RDefines.h"

B4R::Serial* b4r_main::_serial1;
B4R::D1Pins* b4r_main::_d1pins;
B4R::Pin* b4r_main::_pin16;
B4R::Pin* b4r_main::_d6;
B4R::B4RESPWiFi* b4r_main::_wifi;
B4R::WiFiSocket* b4r_main::_wifistr;
B4R::MqttClient* b4r_main::_mqtt;
B4R::MqttConnectOptions* b4r_main::_mqttopt;
B4R::B4RString* b4r_main::_mqttuser;
B4R::B4RString* b4r_main::_mqttpassword;
B4R::B4RString* b4r_main::_mqtthostname;
Int b4r_main::_mqttport;
bool b4r_main::_stoprelay;
B4R::B4RESP8266* b4r_main::_esp;
static B4R::Serial be_gann1_3;
static B4R::D1Pins be_gann2_3;
static B4R::Pin be_gann3_3;
static B4R::Pin be_gann4_3;
static B4R::B4RESPWiFi be_gann5_3;
static B4R::WiFiSocket be_gann6_3;
static B4R::MqttClient be_gann7_3;
static B4R::MqttConnectOptions be_gann8_3;
static B4R::B4RString be_gann9_5;
static B4R::B4RString be_gann10_5;
static B4R::B4RString be_gann11_5;
static B4R::B4RESP8266 be_gann14_3;


 void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
Byte _numberofnetworks = 0;
Int _c = 0;
B4R::B4RString be_ann27_8;
B4R::B4RString be_ann29_4;
B4R::B4RString be_ann29_6;
B4R::B4RString be_ann31_8;
B4R::B4RString be_ann33_4;
B4R::B4RString be_ann33_6;
B4R::B4RString* _clientid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 38;BA.debugLine="Private Sub AppStart";
 //BA.debugLineNum = 39;BA.debugLine="Serial1.Initialize(115200)";
b4r_main::_serial1->Initialize((ULong) (115200));
 //BA.debugLineNum = 40;BA.debugLine="Delay(3000)";
Common_Delay((ULong) (3000));
 //BA.debugLineNum = 41;BA.debugLine="Log(\"AppStart\")";
B4R::Common::LogHelper(1,102,F("AppStart"));
 //BA.debugLineNum = 46;BA.debugLine="pin16.Initialize(16, pin16.MODE_OUTPUT)";
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
 //BA.debugLineNum = 47;BA.debugLine="d6.Initialize(d1pins.D6, d6.MODE_OUTPUT)";
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
 //BA.debugLineNum = 50;BA.debugLine="Dim numberOfNetworks As Byte = WiFi.Scan";
_numberofnetworks = b4r_main::_wifi->Scan();
 //BA.debugLineNum = 51;BA.debugLine="Dim c As Int";
_c = 0;
 //BA.debugLineNum = 52;BA.debugLine="Log(\"Found \", numberOfNetworks, \" networks\")";
B4R::Common::LogHelper(3,102,F("Found "),1,_numberofnetworks,102,F(" networks"));
 //BA.debugLineNum = 53;BA.debugLine="For c = 0 To numberOfNetworks - 1";
{
const int step9 = 1;
const int limit9 = (Int) (_numberofnetworks-1);
_c = 0 ;
for (;(step9 > 0 && _c <= limit9) || (step9 < 0 && _c >= limit9) ;_c = ((Int)(0 + _c + step9))  ) {
 //BA.debugLineNum = 54;BA.debugLine="Log(\"SSID: \", WiFi.ScannedSSID(c), \"|RSSI: \", Wi";
B4R::Common::LogHelper(4,102,F("SSID: "),101,b4r_main::_wifi->ScannedSSID((Byte) (_c))->data,102,F("|RSSI: "),5,b4r_main::_wifi->ScannedRSSI((Byte) (_c)));
 //BA.debugLineNum = 55;BA.debugLine="If WiFi.ScannedSSID(c) = \"Rise Above This Home\"";
if ((b4r_main::_wifi->ScannedSSID((Byte) (_c)))->equals(be_ann27_8.wrap("Rise Above This Home"))) { 
 //BA.debugLineNum = 56;BA.debugLine="Log(\"Connecting to Rise Above This Home WiFi\")";
B4R::Common::LogHelper(1,102,F("Connecting to Rise Above This Home WiFi"));
 //BA.debugLineNum = 57;BA.debugLine="WiFi.Connect2(\"Rise Above This Home\", \"SteelRes";
b4r_main::_wifi->Connect2(be_ann29_4.wrap("Rise Above This Home"),be_ann29_6.wrap("SteelReserve"));
 //BA.debugLineNum = 58;BA.debugLine="Exit";
if (true) break;
 }else if((b4r_main::_wifi->ScannedSSID((Byte) (_c)))->equals(be_ann31_8.wrap("CloydNote8"))) { 
 //BA.debugLineNum = 60;BA.debugLine="Log(\"Connecting to CloydNote8 WiFi\")";
B4R::Common::LogHelper(1,102,F("Connecting to CloydNote8 WiFi"));
 //BA.debugLineNum = 61;BA.debugLine="WiFi.Connect2(\"CloydNote8\", \"adjj6347\")";
b4r_main::_wifi->Connect2(be_ann33_4.wrap("CloydNote8"),be_ann33_6.wrap("adjj6347"));
 //BA.debugLineNum = 62;BA.debugLine="Exit";
if (true) break;
 };
 }
};
 //BA.debugLineNum = 66;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 67;BA.debugLine="Log(\"Connected to WiFi, Local IP \", WiFi.LocalIp";
B4R::Common::LogHelper(2,102,F("Connected to WiFi, Local IP "),101,b4r_main::_wifi->getLocalIp()->data);
 }else {
 //BA.debugLineNum = 69;BA.debugLine="Log(\"Not Connected to WiFi\")";
B4R::Common::LogHelper(1,102,F("Not Connected to WiFi"));
 };
 //BA.debugLineNum = 73;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'creat";
_clientid = B4R::B4RString::fromNumber((Long)(Common_Rnd((Long) (0),(Long) (999999999))));
 //BA.debugLineNum = 74;BA.debugLine="MQTT.Initialize2(WiFiStr.stream, MQTTHostName, MQ";
b4r_main::_mqtt->Initialize2(b4r_main::_wifistr->getStream(),b4r_main::_mqtthostname,(UInt) (b4r_main::_mqttport),_clientid,_mqtt_messagearrived,_mqtt_disconnected);
 //BA.debugLineNum = 75;BA.debugLine="MQTTOpt.Initialize(MQTTUser, MQTTPassword)";
b4r_main::_mqttopt->Initialize(b4r_main::_mqttuser,b4r_main::_mqttpassword);
 //BA.debugLineNum = 76;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 79;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 //BA.debugLineNum = 80;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_connect(Byte _unused){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann55_4;
 //BA.debugLineNum = 82;BA.debugLine="Sub MQTT_Connect(Unused As Byte)";
 //BA.debugLineNum = 83;BA.debugLine="If MQTT.Connect = False Then";
if (b4r_main::_mqtt->Connect()==Common_False) { 
 //BA.debugLineNum = 84;BA.debugLine="Log(\"Connecting to broker\")";
B4R::Common::LogHelper(1,102,F("Connecting to broker"));
 //BA.debugLineNum = 85;BA.debugLine="MQTT.Connect2(MQTTOpt)";
b4r_main::_mqtt->Connect2(b4r_main::_mqttopt);
 //BA.debugLineNum = 86;BA.debugLine="CallSubPlus(\"MQTT_Connect\", 1000, 0)";
B4R::__c->CallSubPlus(_mqtt_connect,(ULong) (1000),(Byte) (0));
 }else {
 //BA.debugLineNum = 88;BA.debugLine="Log(\"Connected to broker\")";
B4R::Common::LogHelper(1,102,F("Connected to broker"));
 //BA.debugLineNum = 89;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
b4r_main::_mqtt->Subscribe(be_ann55_4.wrap("Andy"),(Byte) (0));
 };
 //BA.debugLineNum = 91;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_disconnected(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 138;BA.debugLine="Sub mqtt_Disconnected";
 //BA.debugLineNum = 139;BA.debugLine="Log(\"Disconnected from broker\")";
B4R::Common::LogHelper(1,102,F("Disconnected from broker"));
 //BA.debugLineNum = 140;BA.debugLine="MQTT.Close";
b4r_main::_mqtt->Close();
 //BA.debugLineNum = 141;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 142;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_messagearrived(B4R::B4RString* _topic,B4R::Array* _payload){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann79_8;
B4R::B4RString be_ann80_3;
B4R::B4RString be_ann81_4;
B4R::B4RString be_ann81_6;
B4R::B4RString be_ann85_3;
B4R::B4RString be_ann86_4;
B4R::B4RString be_ann86_6;
B4R::B4RString be_ann89_3;
B4R::B4RString be_ann90_4;
B4R::B4RString be_ann90_6;
B4R::B4RString be_ann92_3;
B4R::B4RString be_ann94_4;
B4R::B4RString be_ann94_6;
B4R::B4RString be_ann96_4;
B4R::B4RString be_ann96_6;
 //BA.debugLineNum = 115;BA.debugLine="Sub mqtt_MessageArrived (Topic As String, Payload(";
 //BA.debugLineNum = 116;BA.debugLine="Log(\"Message arrived. Topic=\", Topic, \" Payload=\"";
B4R::Common::LogHelper(4,102,F("Message arrived. Topic="),101,_topic->data,102,F(" Payload="),100,be_ann79_8.wrapPointer(_payload));
 //BA.debugLineNum = 117;BA.debugLine="If Payload=\"Remotely close relay\" Then";
if ((_payload)->equals((be_ann80_3.wrap("Remotely close relay"))->GetBytes())) { 
 //BA.debugLineNum = 118;BA.debugLine="MQTT.Publish(\"Andy\",\"Closing the relay remotely\"";
b4r_main::_mqtt->Publish(be_ann81_4.wrap("Andy"),(be_ann81_6.wrap("Closing the relay remotely"))->GetBytes());
 //BA.debugLineNum = 119;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 120;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 121;BA.debugLine="StopRelay = True";
b4r_main::_stoprelay = Common_True;
 }else if((_payload)->equals((be_ann85_3.wrap("Remotely open relay"))->GetBytes())) { 
 //BA.debugLineNum = 123;BA.debugLine="MQTT.Publish(\"Andy\",\"Opening the relay remotely\"";
b4r_main::_mqtt->Publish(be_ann86_4.wrap("Andy"),(be_ann86_6.wrap("Opening the relay remotely"))->GetBytes());
 //BA.debugLineNum = 124;BA.debugLine="StopRelay = False";
b4r_main::_stoprelay = Common_False;
 //BA.debugLineNum = 125;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 }else if((_payload)->equals((be_ann89_3.wrap("Restart controller"))->GetBytes())) { 
 //BA.debugLineNum = 127;BA.debugLine="MQTT.Publish(\"Andy\",\"Restarting the relay remote";
b4r_main::_mqtt->Publish(be_ann90_4.wrap("Andy"),(be_ann90_6.wrap("Restarting the relay remotely"))->GetBytes());
 //BA.debugLineNum = 128;BA.debugLine="ESP.Restart";
b4r_main::_esp->Restart();
 }else if((_payload)->equals((be_ann92_3.wrap("Check relay status"))->GetBytes())) { 
 //BA.debugLineNum = 130;BA.debugLine="If pin16.DigitalRead Then";
if (b4r_main::_pin16->DigitalRead()) { 
 //BA.debugLineNum = 131;BA.debugLine="MQTT.Publish(\"Andy\",\"Relay is closed\")";
b4r_main::_mqtt->Publish(be_ann94_4.wrap("Andy"),(be_ann94_6.wrap("Relay is closed"))->GetBytes());
 }else {
 //BA.debugLineNum = 133;BA.debugLine="MQTT.Publish(\"Andy\",\"Relay is open\")";
b4r_main::_mqtt->Publish(be_ann96_4.wrap("Andy"),(be_ann96_6.wrap("Relay is open"))->GetBytes());
 };
 };
 //BA.debugLineNum = 136;BA.debugLine="End Sub";
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
 //BA.debugLineNum = 13;BA.debugLine="Private pin16 As Pin";
b4r_main::_pin16 = &be_gann3_3;
 //BA.debugLineNum = 14;BA.debugLine="Private d6 As Pin";
b4r_main::_d6 = &be_gann4_3;
 //BA.debugLineNum = 15;BA.debugLine="Private WiFi As ESP8266WiFi";
b4r_main::_wifi = &be_gann5_3;
 //BA.debugLineNum = 16;BA.debugLine="Private WiFiStr As WiFiSocket";
b4r_main::_wifistr = &be_gann6_3;
 //BA.debugLineNum = 17;BA.debugLine="Private MQTT As MqttClient";
b4r_main::_mqtt = &be_gann7_3;
 //BA.debugLineNum = 18;BA.debugLine="Private MQTTOpt As MqttConnectOptions";
b4r_main::_mqttopt = &be_gann8_3;
 //BA.debugLineNum = 19;BA.debugLine="Private MQTTUser As String = \"dbgdbcqw\"";
b4r_main::_mqttuser = be_gann9_5.wrap("dbgdbcqw");
 //BA.debugLineNum = 20;BA.debugLine="Private MQTTPassword As String = \"Nc3F4APoO801\"";
b4r_main::_mqttpassword = be_gann10_5.wrap("Nc3F4APoO801");
 //BA.debugLineNum = 21;BA.debugLine="Private MQTTHostName As String = \"m14.cloudmqtt.c";
b4r_main::_mqtthostname = be_gann11_5.wrap("m14.cloudmqtt.com");
 //BA.debugLineNum = 22;BA.debugLine="Private MQTTPort As Int = 15093";
b4r_main::_mqttport = 15093;
 //BA.debugLineNum = 23;BA.debugLine="Private StopRelay As Boolean = False";
b4r_main::_stoprelay = Common_False;
 //BA.debugLineNum = 24;BA.debugLine="Private ESP As ESP8266";
b4r_main::_esp = &be_gann14_3;
 //BA.debugLineNum = 25;BA.debugLine="End Sub";
}
void b4r_main::_relayclose(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann63_4;
B4R::B4RString be_ann63_6;
 //BA.debugLineNum = 93;BA.debugLine="Private Sub RelayClose (tag As Byte)";
 //BA.debugLineNum = 94;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 95;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 97;BA.debugLine="Log(\"Relay Close\")";
B4R::Common::LogHelper(1,102,F("Relay Close"));
 //BA.debugLineNum = 98;BA.debugLine="MQTT.Publish(\"Andy\",\"Relay Close\")";
b4r_main::_mqtt->Publish(be_ann63_4.wrap("Andy"),(be_ann63_6.wrap("Relay Close"))->GetBytes());
 //BA.debugLineNum = 99;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 100;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 101;BA.debugLine="CallSubPlus(\"RelayOpen\", 15000, 0)";
B4R::__c->CallSubPlus(_relayopen,(ULong) (15000),(Byte) (0));
 //BA.debugLineNum = 102;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopen(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann73_4;
B4R::B4RString be_ann73_6;
 //BA.debugLineNum = 104;BA.debugLine="Private Sub RelayOpen (tag As Byte)";
 //BA.debugLineNum = 105;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 106;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 108;BA.debugLine="Log(\"Relay Open\")";
B4R::Common::LogHelper(1,102,F("Relay Open"));
 //BA.debugLineNum = 109;BA.debugLine="MQTT.Publish(\"Andy\",\"Relay Open\")";
b4r_main::_mqtt->Publish(be_ann73_4.wrap("Andy"),(be_ann73_6.wrap("Relay Open"))->GetBytes());
 //BA.debugLineNum = 110;BA.debugLine="d6.DigitalWrite(False)";
b4r_main::_d6->DigitalWrite(Common_False);
 //BA.debugLineNum = 111;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 112;BA.debugLine="CallSubPlus(\"RelayClose\", 5000, 0)";
B4R::__c->CallSubPlus(_relayclose,(ULong) (5000),(Byte) (0));
 //BA.debugLineNum = 113;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
