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
B4R::B4RString* b4r_main::_wifissid;
B4R::B4RString* b4r_main::_wifipassword;
B4R::B4RString* b4r_main::_relayopendelay;
B4R::B4RString* b4r_main::_relaycloseddelay;
B4R::B4REEPROM* b4r_main::_eeprom;
B4R::ByteConverter* b4r_main::_bc;
Byte b4r_main::_magic_eeprom;
b4r_globalstore* b4r_main::_globalstore;
b4r_wifiserver* b4r_main::_wifiserver;
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
static B4R::B4RString be_gann15_5;
static B4R::B4RString be_gann16_5;
static B4R::B4RString be_gann17_5;
static B4R::B4RString be_gann18_5;
static B4R::B4REEPROM be_gann19_3;
static B4R::ByteConverter be_gann20_3;


 void SetSTA(B4R::Object* o) {
   WiFi.mode(WIFI_STA);
}
void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 34;BA.debugLine="Private Sub AppStart";
 //BA.debugLineNum = 35;BA.debugLine="Serial1.Initialize(115200)";
b4r_main::_serial1->Initialize((ULong) (115200));
 //BA.debugLineNum = 36;BA.debugLine="Delay(3000)";
Common_Delay((ULong) (3000));
 //BA.debugLineNum = 37;BA.debugLine="Log(\"AppStart\")";
B4R::Common::LogHelper(1,102,F("AppStart"));
 //BA.debugLineNum = 42;BA.debugLine="pin16.Initialize(16, pin16.MODE_OUTPUT)";
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
 //BA.debugLineNum = 43;BA.debugLine="d6.Initialize(d1pins.D6, d6.MODE_OUTPUT)";
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
 //BA.debugLineNum = 44;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 47;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 //BA.debugLineNum = 48;BA.debugLine="ReadFromEEPROM";
_readfromeeprom();
 //BA.debugLineNum = 51;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 //BA.debugLineNum = 52;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_cleareeprom(){
const UInt cp = B4R::StackMemory::cp;
UInt _i = 0;
Byte be_ann193_9e1[1];
B4R::Array be_ann193_9e2;
 //BA.debugLineNum = 227;BA.debugLine="Sub ClearEEPROM";
 //BA.debugLineNum = 228;BA.debugLine="Dim i As UInt";
_i = 0;
 //BA.debugLineNum = 230;BA.debugLine="Log(\"Size: \", eeprom.Size, \" bytes\")";
B4R::Common::LogHelper(3,102,F("Size: "),4,b4r_main::_eeprom->getSize(),102,F(" bytes"));
 //BA.debugLineNum = 231;BA.debugLine="For i = 0 To eeprom.Size";
{
const int step3 = 1;
const int limit3 = b4r_main::_eeprom->getSize();
_i = (UInt) (0) ;
for (;(step3 > 0 && _i <= limit3) || (step3 < 0 && _i >= limit3) ;_i = ((UInt)(0 + _i + step3))  ) {
 //BA.debugLineNum = 232;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), i)";
b4r_main::_eeprom->WriteBytes(be_ann193_9e2.create(be_ann193_9e1,1,1,(Byte) (0)),_i);
 //BA.debugLineNum = 233;BA.debugLine="Log(i)";
B4R::Common::LogHelper(1,4,_i);
 }
};
 //BA.debugLineNum = 235;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_connecttonetwork(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 243;BA.debugLine="Public Sub ConnectToNetwork";
 //BA.debugLineNum = 244;BA.debugLine="WiFi.Disconnect";
b4r_main::_wifi->Disconnect();
 //BA.debugLineNum = 246;BA.debugLine="ReadFromEEPROM";
_readfromeeprom();
 //BA.debugLineNum = 248;BA.debugLine="ConnectToWifi";
_connecttowifi();
 //BA.debugLineNum = 249;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_connecttowifi(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
B4R::B4RString* _clientid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 141;BA.debugLine="Sub ConnectToWifi";
 //BA.debugLineNum = 142;BA.debugLine="Dim SSID As String";
_ssid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 143;BA.debugLine="Dim password As String";
_password = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 145;BA.debugLine="SSID = bc.StringFromBytes(GlobalStore.Slot0)";
_ssid = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot0);
 //BA.debugLineNum = 146;BA.debugLine="If SSID.Length = 0 Then";
if (_ssid->getLength()==0) { 
 //BA.debugLineNum = 147;BA.debugLine="SSID = WiFiSSID";
_ssid = b4r_main::_wifissid;
 //BA.debugLineNum = 148;BA.debugLine="GlobalStore.Put(0,SSID)";
b4r_main::_globalstore->_put(0,(_ssid)->GetBytes());
 };
 //BA.debugLineNum = 151;BA.debugLine="password = bc.StringFromBytes(GlobalStore.Slot1)";
_password = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot1);
 //BA.debugLineNum = 152;BA.debugLine="If password.Length = 0 Then";
if (_password->getLength()==0) { 
 //BA.debugLineNum = 153;BA.debugLine="password = WiFiPassword";
_password = b4r_main::_wifipassword;
 //BA.debugLineNum = 154;BA.debugLine="GlobalStore.Put(1,password)";
b4r_main::_globalstore->_put(1,(_password)->GetBytes());
 };
 //BA.debugLineNum = 157;BA.debugLine="WiFi.Connect2(SSID, password)";
b4r_main::_wifi->Connect2(_ssid,_password);
 //BA.debugLineNum = 159;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 161;BA.debugLine="Log(\"Stopping access point\")";
B4R::Common::LogHelper(1,102,F("Stopping access point"));
 //BA.debugLineNum = 162;BA.debugLine="RunNative(\"SetSTA\", Null)";
Common_RunNative(SetSTA,Common_Null);
 //BA.debugLineNum = 163;BA.debugLine="Log(\"Connected to WiFi = \",SSID,\" Local IP = \",";
B4R::Common::LogHelper(6,102,F("Connected to WiFi = "),101,_ssid->data,102,F(" Local IP = "),101,b4r_main::_wifi->getLocalIp()->data,102,F(" Password = "),101,_password->data);
 //BA.debugLineNum = 165;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'cre";
_clientid = B4R::B4RString::fromNumber((Long)(Common_Rnd((Long) (0),(Long) (999999999))));
 //BA.debugLineNum = 166;BA.debugLine="MQTT.Initialize2(WiFiStr.stream, MQTTHostName,";
b4r_main::_mqtt->Initialize2(b4r_main::_wifistr->getStream(),b4r_main::_mqtthostname,(UInt) (b4r_main::_mqttport),_clientid,_mqtt_messagearrived,_mqtt_disconnected);
 //BA.debugLineNum = 167;BA.debugLine="MQTTOpt.Initialize(MQTTUser, MQTTPassword)";
b4r_main::_mqttopt->Initialize(b4r_main::_mqttuser,b4r_main::_mqttpassword);
 //BA.debugLineNum = 168;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 }else {
 //BA.debugLineNum = 170;BA.debugLine="Log(\"Failed to connect to WiFi\")";
B4R::Common::LogHelper(1,102,F("Failed to connect to WiFi"));
 };
 //BA.debugLineNum = 173;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_connect(Byte _unused){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann46_4;
 //BA.debugLineNum = 54;BA.debugLine="Sub MQTT_Connect(Unused As Byte)";
 //BA.debugLineNum = 55;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 56;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 58;BA.debugLine="If MQTT.Connect = False Then";
if (b4r_main::_mqtt->Connect()==Common_False) { 
 //BA.debugLineNum = 59;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 60;BA.debugLine="Log(\"Connecting to broker\")";
B4R::Common::LogHelper(1,102,F("Connecting to broker"));
 //BA.debugLineNum = 61;BA.debugLine="MQTT.Connect2(MQTTOpt)";
b4r_main::_mqtt->Connect2(b4r_main::_mqttopt);
 //BA.debugLineNum = 62;BA.debugLine="CallSubPlus(\"MQTT_Connect\", 1000, 0)";
B4R::__c->CallSubPlus(_mqtt_connect,(ULong) (1000),(Byte) (0));
 }else {
 //BA.debugLineNum = 64;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 65;BA.debugLine="Log(\"Connected to broker\")";
B4R::Common::LogHelper(1,102,F("Connected to broker"));
 //BA.debugLineNum = 66;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
b4r_main::_mqtt->Subscribe(be_ann46_4.wrap("Andy"),(Byte) (0));
 };
 //BA.debugLineNum = 68;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_disconnected(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 133;BA.debugLine="Sub mqtt_Disconnected";
 //BA.debugLineNum = 134;BA.debugLine="Log(\"Disconnected from broker\")";
B4R::Common::LogHelper(1,102,F("Disconnected from broker"));
 //BA.debugLineNum = 135;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 //BA.debugLineNum = 136;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 137;BA.debugLine="MQTT.Close";
b4r_main::_mqtt->Close();
 //BA.debugLineNum = 138;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 139;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_messagearrived(B4R::B4RString* _topic,B4R::Array* _payload){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann87_8;
B4R::B4RString be_ann88_3;
B4R::B4RString be_ann89_4;
B4R::B4RString be_ann89_6;
B4R::B4RString be_ann92_3;
B4R::B4RString be_ann93_4;
B4R::B4RString be_ann93_6;
B4R::B4RString be_ann96_3;
B4R::B4RString be_ann97_4;
B4R::B4RString be_ann97_6;
B4R::B4RString be_ann99_3;
B4R::B4RString be_ann101_4;
B4R::B4RString be_ann101_6;
B4R::B4RString be_ann103_4;
B4R::B4RString be_ann103_6;
B4R::B4RString be_ann105_4;
B4R::B4RString be_ann105_6;
 //BA.debugLineNum = 108;BA.debugLine="Sub mqtt_MessageArrived (Topic As String, Payload(";
 //BA.debugLineNum = 109;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 110;BA.debugLine="Log(\"Message arrived. Topic=\", Topic, \" Payload=\"";
B4R::Common::LogHelper(4,102,F("Message arrived. Topic="),101,_topic->data,102,F(" Payload="),100,be_ann87_8.wrapPointer(_payload));
 //BA.debugLineNum = 111;BA.debugLine="If Payload=\"Remotely close relay\" Then";
if ((_payload)->equals((be_ann88_3.wrap("Remotely close relay"))->GetBytes())) { 
 //BA.debugLineNum = 112;BA.debugLine="MQTT.Publish(\"Andy\",\"*Closing relay by remote\")";
b4r_main::_mqtt->Publish(be_ann89_4.wrap("Andy"),(be_ann89_6.wrap("*Closing relay by remote"))->GetBytes());
 //BA.debugLineNum = 113;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 114;BA.debugLine="StopRelay = True";
b4r_main::_stoprelay = Common_True;
 }else if((_payload)->equals((be_ann92_3.wrap("Remotely open relay"))->GetBytes())) { 
 //BA.debugLineNum = 116;BA.debugLine="MQTT.Publish(\"Andy\",\"*Opening relay by remote\")";
b4r_main::_mqtt->Publish(be_ann93_4.wrap("Andy"),(be_ann93_6.wrap("*Opening relay by remote"))->GetBytes());
 //BA.debugLineNum = 117;BA.debugLine="StopRelay = False";
b4r_main::_stoprelay = Common_False;
 //BA.debugLineNum = 118;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 }else if((_payload)->equals((be_ann96_3.wrap("Restart controller"))->GetBytes())) { 
 //BA.debugLineNum = 120;BA.debugLine="MQTT.Publish(\"Andy\",\"*Restarting relay by remote";
b4r_main::_mqtt->Publish(be_ann97_4.wrap("Andy"),(be_ann97_6.wrap("*Restarting relay by remote"))->GetBytes());
 //BA.debugLineNum = 121;BA.debugLine="ESP.Restart";
b4r_main::_esp->Restart();
 }else if((_payload)->equals((be_ann99_3.wrap("Check relay status"))->GetBytes())) { 
 //BA.debugLineNum = 123;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 124;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is permanently clos";
b4r_main::_mqtt->Publish(be_ann101_4.wrap("Andy"),(be_ann101_6.wrap("*Relay is permanently closed"))->GetBytes());
 }else if(b4r_main::_d6->DigitalRead()) { 
 //BA.debugLineNum = 126;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is closed\")";
b4r_main::_mqtt->Publish(be_ann103_4.wrap("Andy"),(be_ann103_6.wrap("*Relay is closed"))->GetBytes());
 }else {
 //BA.debugLineNum = 128;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is open\")";
b4r_main::_mqtt->Publish(be_ann105_4.wrap("Andy"),(be_ann105_6.wrap("*Relay is open"))->GetBytes());
 };
 };
 //BA.debugLineNum = 131;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}

void b4r_main::initializeProcessGlobals() {
     B4R::StackMemory::buffer = (byte*)malloc(STACK_BUFFER_SIZE);
     b4r_main::_process_globals();
b4r_globalstore::_process_globals();
b4r_wifiserver::_process_globals();

   
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
 //BA.debugLineNum = 15;BA.debugLine="Public WiFi As ESP8266WiFi";
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
 //BA.debugLineNum = 24;BA.debugLine="Public ESP As ESP8266";
b4r_main::_esp = &be_gann14_3;
 //BA.debugLineNum = 25;BA.debugLine="Private WiFiSSID As String = \"CloydNote8\"";
b4r_main::_wifissid = be_gann15_5.wrap("CloydNote8");
 //BA.debugLineNum = 26;BA.debugLine="Private WiFiPassword As String = \"adjj6347\"";
b4r_main::_wifipassword = be_gann16_5.wrap("adjj6347");
 //BA.debugLineNum = 27;BA.debugLine="Private RelayOpenDelay As String = \"5000\"";
b4r_main::_relayopendelay = be_gann17_5.wrap("5000");
 //BA.debugLineNum = 28;BA.debugLine="Private RelayClosedDelay As String = \"15000\"";
b4r_main::_relaycloseddelay = be_gann18_5.wrap("15000");
 //BA.debugLineNum = 29;BA.debugLine="Private eeprom As EEPROM";
b4r_main::_eeprom = &be_gann19_3;
 //BA.debugLineNum = 30;BA.debugLine="Private bc As ByteConverter";
b4r_main::_bc = &be_gann20_3;
 //BA.debugLineNum = 31;BA.debugLine="Private const MAGIC_EEPROM As Byte = 123";
b4r_main::_magic_eeprom = (Byte) (123);
 //BA.debugLineNum = 32;BA.debugLine="End Sub";
}
void b4r_main::_readfromeeprom(){
const UInt cp = B4R::StackMemory::cp;
B4R::Array* _header = NULL;
B4R::Array* _data = NULL;
Byte be_ann167_16e1[1];
B4R::Array be_ann167_16e2;
Int _i = 0;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
B4R::B4RString* _opendelay = B4R::B4RString::EMPTY;
B4R::B4RString* _closeddelay = B4R::B4RString::EMPTY;
B4R::B4RString* _iswifi = B4R::B4RString::EMPTY;
B4R::Object be_ann183_8;
B4R::Object be_ann183_14;
B4R::Object be_ann183_20;
B4R::Object be_ann183_26;
B4R::Object be_ann183_32;
 //BA.debugLineNum = 197;BA.debugLine="Sub ReadFromEEPROM";
 //BA.debugLineNum = 198;BA.debugLine="Dim header() As Byte = eeprom.ReadBytes(0, 2)";
_header = b4r_main::_eeprom->ReadBytes((UInt) (0),(UInt) (2));
 //BA.debugLineNum = 199;BA.debugLine="If header(0) = MAGIC_EEPROM Then";
if (((Byte*)_header->getData((UInt) (0)))[B4R::Array::staticIndex]==b4r_main::_magic_eeprom) { 
 //BA.debugLineNum = 200;BA.debugLine="Dim data() As Byte = eeprom.ReadBytes(2, header(";
_data = b4r_main::_eeprom->ReadBytes((UInt) (2),(UInt) (((Byte*)_header->getData((UInt) (1)))[B4R::Array::staticIndex]));
 //BA.debugLineNum = 201;BA.debugLine="Dim i As Int = bc.IndexOf(data, Array As Byte(0)";
_i = b4r_main::_bc->IndexOf(_data,be_ann167_16e2.create(be_ann167_16e1,1,1,(Byte) (0)));
 //BA.debugLineNum = 202;BA.debugLine="If i = -1 Then";
if (_i==-1) { 
 //BA.debugLineNum = 203;BA.debugLine="Log(\"Error parsing settings. Starting as an acc";
B4R::Common::LogHelper(1,102,F("Error parsing settings. Starting as an access point."));
 //BA.debugLineNum = 204;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 //BA.debugLineNum = 205;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 208;BA.debugLine="Dim SSID As String = bc.StringFromBytes(bc.SubSt";
_ssid = b4r_main::_bc->StringFromBytes(b4r_main::_bc->SubString2(_data,(UInt) (0),(UInt) (_i)));
 //BA.debugLineNum = 209;BA.debugLine="Dim Password As String = bc.StringFromBytes(bc.S";
_password = b4r_main::_bc->StringFromBytes(b4r_main::_bc->SubString(_data,(UInt) (_i+1)));
 //BA.debugLineNum = 210;BA.debugLine="Dim OpenDelay As String = bc.StringFromBytes(bc.";
_opendelay = b4r_main::_bc->StringFromBytes(b4r_main::_bc->SubString(_data,(UInt) (_i+2+_password->getLength())));
 //BA.debugLineNum = 211;BA.debugLine="Dim ClosedDelay As String = bc.StringFromBytes(b";
_closeddelay = b4r_main::_bc->StringFromBytes(b4r_main::_bc->SubString(_data,(UInt) (_i+3+_opendelay->getLength()+_password->getLength())));
 //BA.debugLineNum = 212;BA.debugLine="Dim IsWifi As String = bc.StringFromBytes(bc.Sub";
_iswifi = b4r_main::_bc->StringFromBytes(b4r_main::_bc->SubString(_data,(UInt) (_i+4+_closeddelay->getLength()+_opendelay->getLength()+_password->getLength())));
 //BA.debugLineNum = 214;BA.debugLine="GlobalStore.Put(0,SSID) ' SSID";
b4r_main::_globalstore->_put(0,(_ssid)->GetBytes());
 //BA.debugLineNum = 215;BA.debugLine="GlobalStore.Put(1,Password) ' Password";
b4r_main::_globalstore->_put(1,(_password)->GetBytes());
 //BA.debugLineNum = 216;BA.debugLine="GlobalStore.Put(2,OpenDelay) ' Open delay";
b4r_main::_globalstore->_put(2,(_opendelay)->GetBytes());
 //BA.debugLineNum = 217;BA.debugLine="GlobalStore.Put(3,ClosedDelay) ' Closed delay";
b4r_main::_globalstore->_put(3,(_closeddelay)->GetBytes());
 //BA.debugLineNum = 218;BA.debugLine="GlobalStore.Put(4,IsWifi) ' Is used as WiFI";
b4r_main::_globalstore->_put(4,(_iswifi)->GetBytes());
 //BA.debugLineNum = 219;BA.debugLine="Log(\"ReadFromEEPROM \",\" Slot0: \",GlobalStore.Slo";
B4R::Common::LogHelper(11,102,F("ReadFromEEPROM "),102,F(" Slot0: "),100,be_ann183_8.wrapPointer(b4r_main::_globalstore->_slot0),102,F(" Slot1: "),100,be_ann183_14.wrapPointer(b4r_main::_globalstore->_slot1),102,F(" Slot2: "),100,be_ann183_20.wrapPointer(b4r_main::_globalstore->_slot2),102,F(" Slot3: "),100,be_ann183_26.wrapPointer(b4r_main::_globalstore->_slot3),102,F(" Slot4: "),100,be_ann183_32.wrapPointer(b4r_main::_globalstore->_slot4));
 }else {
 //BA.debugLineNum = 221;BA.debugLine="Log(\"Settings data not found. Starting as an acc";
B4R::Common::LogHelper(1,102,F("Settings data not found. Starting as an access point."));
 //BA.debugLineNum = 222;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 };
 //BA.debugLineNum = 225;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayclose(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann57_4;
B4R::B4RString be_ann57_6;
B4R::B4RString* _closeddelay = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 70;BA.debugLine="Private Sub RelayClose (tag As Byte)";
 //BA.debugLineNum = 71;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 72;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 74;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 75;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 77;BA.debugLine="Log(\"*Relay has been closed\")";
B4R::Common::LogHelper(1,102,F("*Relay has been closed"));
 //BA.debugLineNum = 78;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been closed\")";
b4r_main::_mqtt->Publish(be_ann57_4.wrap("Andy"),(be_ann57_6.wrap("*Relay has been closed"))->GetBytes());
 //BA.debugLineNum = 79;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 80;BA.debugLine="Dim closedDelay As String = bc.StringFromBytes(Gl";
_closeddelay = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3);
 //BA.debugLineNum = 81;BA.debugLine="If closedDelay.Length = 0 Then";
if (_closeddelay->getLength()==0) { 
 //BA.debugLineNum = 82;BA.debugLine="closedDelay = RelayClosedDelay";
_closeddelay = b4r_main::_relaycloseddelay;
 //BA.debugLineNum = 83;BA.debugLine="GlobalStore.Put(3,RelayClosedDelay)";
b4r_main::_globalstore->_put(3,(b4r_main::_relaycloseddelay)->GetBytes());
 };
 //BA.debugLineNum = 85;BA.debugLine="Log(\"closedDelay: \",closedDelay)";
B4R::Common::LogHelper(2,102,F("closedDelay: "),101,_closeddelay->data);
 //BA.debugLineNum = 86;BA.debugLine="CallSubPlus(\"RelayOpen\", closedDelay, 0)";
B4R::__c->CallSubPlus(_relayopen,(ULong)(atof(_closeddelay->data)),(Byte) (0));
 //BA.debugLineNum = 87;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopen(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann75_4;
B4R::B4RString be_ann75_6;
B4R::B4RString* _opendelay = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 89;BA.debugLine="Private Sub RelayOpen (tag As Byte)";
 //BA.debugLineNum = 90;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 91;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 93;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 94;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 96;BA.debugLine="Log(\"*Relay has been opened\")";
B4R::Common::LogHelper(1,102,F("*Relay has been opened"));
 //BA.debugLineNum = 97;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been opened\")";
b4r_main::_mqtt->Publish(be_ann75_4.wrap("Andy"),(be_ann75_6.wrap("*Relay has been opened"))->GetBytes());
 //BA.debugLineNum = 98;BA.debugLine="d6.DigitalWrite(False)";
b4r_main::_d6->DigitalWrite(Common_False);
 //BA.debugLineNum = 99;BA.debugLine="Dim openDelay As String = bc.StringFromBytes(Glob";
_opendelay = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2);
 //BA.debugLineNum = 100;BA.debugLine="If openDelay.Length = 0  Then";
if (_opendelay->getLength()==0) { 
 //BA.debugLineNum = 101;BA.debugLine="openDelay = RelayOpenDelay";
_opendelay = b4r_main::_relayopendelay;
 //BA.debugLineNum = 102;BA.debugLine="GlobalStore.Put(2,RelayOpenDelay)";
b4r_main::_globalstore->_put(2,(b4r_main::_relayopendelay)->GetBytes());
 };
 //BA.debugLineNum = 104;BA.debugLine="Log(\"openDelay: \",openDelay)";
B4R::Common::LogHelper(2,102,F("openDelay: "),101,_opendelay->data);
 //BA.debugLineNum = 105;BA.debugLine="CallSubPlus(\"RelayClose\", openDelay, 0)";
B4R::__c->CallSubPlus(_relayclose,(ULong)(atof(_opendelay->data)),(Byte) (0));
 //BA.debugLineNum = 106;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_savenetworkdetails(B4R::B4RString* _ssid,B4R::B4RString* _password){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann199_12;
B4R::B4RString be_ann199_14;
B4R::B4RString be_ann200_6;
B4R::B4RString be_ann200_8;
B4R::B4RString be_ann200_10;
 //BA.debugLineNum = 237;BA.debugLine="Public Sub SaveNetworkDetails(SSID As String, Pass";
 //BA.debugLineNum = 238;BA.debugLine="Log(\"Saving settings: \", SSID, \", \", Password, \",";
B4R::Common::LogHelper(8,102,F("Saving settings: "),101,_ssid->data,102,F(", "),101,_password->data,102,F(", "),102,F("56000"),102,F(", "),102,F("60000"));
 //BA.debugLineNum = 239;BA.debugLine="SSID = bc.StringFromBytes(WiFiServer.ReplaceStrin";
_ssid = b4r_main::_bc->StringFromBytes(b4r_main::_wifiserver->_replacestring((_ssid)->GetBytes(),(be_ann199_12.wrap("%20"))->GetBytes(),(be_ann199_14.wrap(" "))->GetBytes()));
 //BA.debugLineNum = 240;BA.debugLine="WriteToEEPROM(SSID,Password,\"56000\",\"60000\",\"True";
_writetoeeprom(_ssid,_password,be_ann200_6.wrap("56000"),be_ann200_8.wrap("60000"),be_ann200_10.wrap("True"));
 //BA.debugLineNum = 241;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_writetoeeprom(B4R::B4RString* _ssid,B4R::B4RString* _password,B4R::B4RString* _opendelay,B4R::B4RString* _closeddelay,B4R::B4RString* _iswifi){
const UInt cp = B4R::StackMemory::cp;
Byte be_ann143_37e1[2];
B4R::Array be_ann143_37e2;
Int _pos = 0;
Byte be_ann147_9e1[1];
B4R::Array be_ann147_9e2;
Byte be_ann151_9e1[1];
B4R::Array be_ann151_9e2;
Byte be_ann155_9e1[1];
B4R::Array be_ann155_9e2;
Byte be_ann159_9e1[1];
B4R::Array be_ann159_9e2;
 //BA.debugLineNum = 175;BA.debugLine="Sub WriteToEEPROM(SSID As String, Password As Stri";
 //BA.debugLineNum = 176;BA.debugLine="eeprom.WriteBytes(Array As Byte(MAGIC_EEPROM, SSI";
b4r_main::_eeprom->WriteBytes(be_ann143_37e2.create(be_ann143_37e1,2,1,b4r_main::_magic_eeprom,(Byte) (_ssid->getLength()+1+_password->getLength()+1+_opendelay->getLength()+1+_closeddelay->getLength()+1+_iswifi->getLength())),(UInt) (0));
 //BA.debugLineNum = 177;BA.debugLine="Dim pos As Int = 2";
_pos = 2;
 //BA.debugLineNum = 178;BA.debugLine="eeprom.WriteBytes(SSID, pos)";
b4r_main::_eeprom->WriteBytes((_ssid)->GetBytes(),(UInt) (_pos));
 //BA.debugLineNum = 179;BA.debugLine="pos = pos + SSID.Length";
_pos = (Int) (_pos+_ssid->getLength());
 //BA.debugLineNum = 180;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), pos)";
b4r_main::_eeprom->WriteBytes(be_ann147_9e2.create(be_ann147_9e1,1,1,(Byte) (0)),(UInt) (_pos));
 //BA.debugLineNum = 181;BA.debugLine="pos = pos + 1";
_pos = (Int) (_pos+1);
 //BA.debugLineNum = 182;BA.debugLine="eeprom.WriteBytes(Password, pos)";
b4r_main::_eeprom->WriteBytes((_password)->GetBytes(),(UInt) (_pos));
 //BA.debugLineNum = 183;BA.debugLine="pos = pos + Password.Length";
_pos = (Int) (_pos+_password->getLength());
 //BA.debugLineNum = 184;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), pos)";
b4r_main::_eeprom->WriteBytes(be_ann151_9e2.create(be_ann151_9e1,1,1,(Byte) (0)),(UInt) (_pos));
 //BA.debugLineNum = 185;BA.debugLine="pos = pos + 1";
_pos = (Int) (_pos+1);
 //BA.debugLineNum = 186;BA.debugLine="eeprom.WriteBytes(OpenDelay, pos)";
b4r_main::_eeprom->WriteBytes((_opendelay)->GetBytes(),(UInt) (_pos));
 //BA.debugLineNum = 187;BA.debugLine="pos = pos + OpenDelay.Length";
_pos = (Int) (_pos+_opendelay->getLength());
 //BA.debugLineNum = 188;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), pos)";
b4r_main::_eeprom->WriteBytes(be_ann155_9e2.create(be_ann155_9e1,1,1,(Byte) (0)),(UInt) (_pos));
 //BA.debugLineNum = 189;BA.debugLine="pos = pos + 1";
_pos = (Int) (_pos+1);
 //BA.debugLineNum = 190;BA.debugLine="eeprom.WriteBytes(ClosedDelay, pos)";
b4r_main::_eeprom->WriteBytes((_closeddelay)->GetBytes(),(UInt) (_pos));
 //BA.debugLineNum = 191;BA.debugLine="pos = pos + ClosedDelay.Length";
_pos = (Int) (_pos+_closeddelay->getLength());
 //BA.debugLineNum = 192;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), pos)";
b4r_main::_eeprom->WriteBytes(be_ann159_9e2.create(be_ann159_9e1,1,1,(Byte) (0)),(UInt) (_pos));
 //BA.debugLineNum = 193;BA.debugLine="pos = pos + 1";
_pos = (Int) (_pos+1);
 //BA.debugLineNum = 194;BA.debugLine="eeprom.WriteBytes(IsWiFi, pos)";
b4r_main::_eeprom->WriteBytes((_iswifi)->GetBytes(),(UInt) (_pos));
 //BA.debugLineNum = 195;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
