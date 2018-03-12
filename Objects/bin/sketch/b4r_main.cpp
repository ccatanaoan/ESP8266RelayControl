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
 //BA.debugLineNum = 50;BA.debugLine="ConnectToWifi";
_connecttowifi();
 //BA.debugLineNum = 53;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'creat";
_clientid = B4R::B4RString::fromNumber((Long)(Common_Rnd((Long) (0),(Long) (999999999))));
 //BA.debugLineNum = 54;BA.debugLine="MQTT.Initialize2(WiFiStr.stream, MQTTHostName, MQ";
b4r_main::_mqtt->Initialize2(b4r_main::_wifistr->getStream(),b4r_main::_mqtthostname,(UInt) (b4r_main::_mqttport),_clientid,_mqtt_messagearrived,_mqtt_disconnected);
 //BA.debugLineNum = 55;BA.debugLine="MQTTOpt.Initialize(MQTTUser, MQTTPassword)";
b4r_main::_mqttopt->Initialize(b4r_main::_mqttuser,b4r_main::_mqttpassword);
 //BA.debugLineNum = 56;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 59;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 //BA.debugLineNum = 60;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_connecttowifi(){
const UInt cp = B4R::StackMemory::cp;
Byte _numberofnetworks = 0;
Int _c = 0;
B4R::B4RString be_ann107_8;
B4R::B4RString be_ann109_4;
B4R::B4RString be_ann109_6;
B4R::B4RString be_ann111_8;
B4R::B4RString be_ann113_4;
B4R::B4RString be_ann113_6;
 //BA.debugLineNum = 139;BA.debugLine="Sub ConnectToWifi";
 //BA.debugLineNum = 140;BA.debugLine="Dim numberOfNetworks As Byte = WiFi.Scan";
_numberofnetworks = b4r_main::_wifi->Scan();
 //BA.debugLineNum = 141;BA.debugLine="Dim c As Int";
_c = 0;
 //BA.debugLineNum = 142;BA.debugLine="Log(\"Found \", numberOfNetworks, \" networks\")";
B4R::Common::LogHelper(3,102,F("Found "),1,_numberofnetworks,102,F(" networks"));
 //BA.debugLineNum = 143;BA.debugLine="For c = 0 To numberOfNetworks - 1";
{
const int step4 = 1;
const int limit4 = (Int) (_numberofnetworks-1);
_c = 0 ;
for (;(step4 > 0 && _c <= limit4) || (step4 < 0 && _c >= limit4) ;_c = ((Int)(0 + _c + step4))  ) {
 //BA.debugLineNum = 144;BA.debugLine="Log(\"SSID: \", WiFi.ScannedSSID(c), \"|RSSI: \", Wi";
B4R::Common::LogHelper(4,102,F("SSID: "),101,b4r_main::_wifi->ScannedSSID((Byte) (_c))->data,102,F("|RSSI: "),5,b4r_main::_wifi->ScannedRSSI((Byte) (_c)));
 //BA.debugLineNum = 145;BA.debugLine="If WiFi.ScannedSSID(c) = \"CloydNote8\" Then";
if ((b4r_main::_wifi->ScannedSSID((Byte) (_c)))->equals(be_ann107_8.wrap("CloydNote8"))) { 
 //BA.debugLineNum = 146;BA.debugLine="Log(\"Connecting to CloydNote8 WiFi\")";
B4R::Common::LogHelper(1,102,F("Connecting to CloydNote8 WiFi"));
 //BA.debugLineNum = 147;BA.debugLine="WiFi.Connect2(\"CloydNote8\", \"adjj6347\")";
b4r_main::_wifi->Connect2(be_ann109_4.wrap("CloydNote8"),be_ann109_6.wrap("adjj6347"));
 //BA.debugLineNum = 148;BA.debugLine="Exit";
if (true) break;
 }else if((b4r_main::_wifi->ScannedSSID((Byte) (_c)))->equals(be_ann111_8.wrap("Rise Above This Home"))) { 
 //BA.debugLineNum = 150;BA.debugLine="Log(\"Connecting to Rise Above This Home WiFi\")";
B4R::Common::LogHelper(1,102,F("Connecting to Rise Above This Home WiFi"));
 //BA.debugLineNum = 151;BA.debugLine="WiFi.Connect2(\"Rise Above This Home\", \"SteelRes";
b4r_main::_wifi->Connect2(be_ann113_4.wrap("Rise Above This Home"),be_ann113_6.wrap("SteelReserve"));
 //BA.debugLineNum = 152;BA.debugLine="Exit";
if (true) break;
 }else {
 };
 }
};
 //BA.debugLineNum = 157;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 158;BA.debugLine="Log(\"Connected to WiFi, Local IP \", WiFi.LocalIp";
B4R::Common::LogHelper(2,102,F("Connected to WiFi, Local IP "),101,b4r_main::_wifi->getLocalIp()->data);
 }else {
 //BA.debugLineNum = 160;BA.debugLine="Log(\"Not Connected to WiFi\")";
B4R::Common::LogHelper(1,102,F("Not Connected to WiFi"));
 };
 //BA.debugLineNum = 162;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_connect(Byte _unused){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann40_4;
 //BA.debugLineNum = 62;BA.debugLine="Sub MQTT_Connect(Unused As Byte)";
 //BA.debugLineNum = 63;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 64;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 66;BA.debugLine="If MQTT.Connect = False Then";
if (b4r_main::_mqtt->Connect()==Common_False) { 
 //BA.debugLineNum = 67;BA.debugLine="Log(\"Connecting to broker\")";
B4R::Common::LogHelper(1,102,F("Connecting to broker"));
 //BA.debugLineNum = 68;BA.debugLine="MQTT.Connect2(MQTTOpt)";
b4r_main::_mqtt->Connect2(b4r_main::_mqttopt);
 //BA.debugLineNum = 69;BA.debugLine="CallSubPlus(\"MQTT_Connect\", 1000, 0)";
B4R::__c->CallSubPlus(_mqtt_connect,(ULong) (1000),(Byte) (0));
 }else {
 //BA.debugLineNum = 71;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 72;BA.debugLine="Log(\"Connected to broker\")";
B4R::Common::LogHelper(1,102,F("Connected to broker"));
 //BA.debugLineNum = 73;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
b4r_main::_mqtt->Subscribe(be_ann40_4.wrap("Andy"),(Byte) (0));
 };
 //BA.debugLineNum = 75;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_disconnected(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 129;BA.debugLine="Sub mqtt_Disconnected";
 //BA.debugLineNum = 130;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 131;BA.debugLine="Log(\"Disconnected from broker\")";
B4R::Common::LogHelper(1,102,F("Disconnected from broker"));
 //BA.debugLineNum = 132;BA.debugLine="MQTT.Close";
b4r_main::_mqtt->Close();
 //BA.debugLineNum = 133;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 134;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 136;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 137;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_messagearrived(B4R::B4RString* _topic,B4R::Array* _payload){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann70_8;
B4R::B4RString be_ann71_3;
B4R::B4RString be_ann72_4;
B4R::B4RString be_ann72_6;
B4R::B4RString be_ann75_3;
B4R::B4RString be_ann76_4;
B4R::B4RString be_ann76_6;
B4R::B4RString be_ann79_3;
B4R::B4RString be_ann80_4;
B4R::B4RString be_ann80_6;
B4R::B4RString be_ann82_3;
B4R::B4RString be_ann84_4;
B4R::B4RString be_ann84_6;
B4R::B4RString be_ann86_4;
B4R::B4RString be_ann86_6;
B4R::B4RString be_ann88_4;
B4R::B4RString be_ann88_6;
 //BA.debugLineNum = 104;BA.debugLine="Sub mqtt_MessageArrived (Topic As String, Payload(";
 //BA.debugLineNum = 105;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 106;BA.debugLine="Log(\"Message arrived. Topic=\", Topic, \" Payload=\"";
B4R::Common::LogHelper(4,102,F("Message arrived. Topic="),101,_topic->data,102,F(" Payload="),100,be_ann70_8.wrapPointer(_payload));
 //BA.debugLineNum = 107;BA.debugLine="If Payload=\"Remotely close relay\" Then";
if ((_payload)->equals((be_ann71_3.wrap("Remotely close relay"))->GetBytes())) { 
 //BA.debugLineNum = 108;BA.debugLine="MQTT.Publish(\"Andy\",\"*Closing relay by remote\")";
b4r_main::_mqtt->Publish(be_ann72_4.wrap("Andy"),(be_ann72_6.wrap("*Closing relay by remote"))->GetBytes());
 //BA.debugLineNum = 109;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 110;BA.debugLine="StopRelay = True";
b4r_main::_stoprelay = Common_True;
 }else if((_payload)->equals((be_ann75_3.wrap("Remotely open relay"))->GetBytes())) { 
 //BA.debugLineNum = 112;BA.debugLine="MQTT.Publish(\"Andy\",\"*Opening relay by remote\")";
b4r_main::_mqtt->Publish(be_ann76_4.wrap("Andy"),(be_ann76_6.wrap("*Opening relay by remote"))->GetBytes());
 //BA.debugLineNum = 113;BA.debugLine="StopRelay = False";
b4r_main::_stoprelay = Common_False;
 //BA.debugLineNum = 114;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 }else if((_payload)->equals((be_ann79_3.wrap("Restart controller"))->GetBytes())) { 
 //BA.debugLineNum = 116;BA.debugLine="MQTT.Publish(\"Andy\",\"*Restarting relay by remote";
b4r_main::_mqtt->Publish(be_ann80_4.wrap("Andy"),(be_ann80_6.wrap("*Restarting relay by remote"))->GetBytes());
 //BA.debugLineNum = 117;BA.debugLine="ESP.Restart";
b4r_main::_esp->Restart();
 }else if((_payload)->equals((be_ann82_3.wrap("Check relay status"))->GetBytes())) { 
 //BA.debugLineNum = 119;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 120;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is permanently clos";
b4r_main::_mqtt->Publish(be_ann84_4.wrap("Andy"),(be_ann84_6.wrap("*Relay is permanently closed"))->GetBytes());
 }else if(b4r_main::_d6->DigitalRead()) { 
 //BA.debugLineNum = 122;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is closed\")";
b4r_main::_mqtt->Publish(be_ann86_4.wrap("Andy"),(be_ann86_6.wrap("*Relay is closed"))->GetBytes());
 }else {
 //BA.debugLineNum = 124;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is open\")";
b4r_main::_mqtt->Publish(be_ann88_4.wrap("Andy"),(be_ann88_6.wrap("*Relay is open"))->GetBytes());
 };
 };
 //BA.debugLineNum = 127;BA.debugLine="End Sub";
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
void b4r_main::_readfromeeprom(){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann136_4e1[10];
B4R::Array be_ann136_4e2;
B4R::Object* be_ann136_4e3[10];
B4R::Array* _be = NULL;
B4R::ByteConverter be_ann137_3;
B4R::ByteConverter* _bc = NULL;
B4R::B4RSerializator be_ann138_3;
B4R::B4RSerializator* _serializator = NULL;
B4R::B4REEPROM be_ann139_3;
B4R::B4REEPROM* _eeprom = NULL;
Byte be_ann140_4e1[0];
B4R::Array be_ann140_4e2;
B4R::Array* _bytelengthofdataineeprom = NULL;
Int _actuallengthofdataineeprom = 0;
Byte be_ann142_4e1[0];
B4R::Array be_ann142_4e2;
B4R::Array* _bytedataineeprom = NULL;
B4R::Object be_ann143_4e1[0];
B4R::Array be_ann143_4e2;
B4R::Object* be_ann143_4e3[0];
B4R::Array* _objectsineeprom = NULL;
 //BA.debugLineNum = 186;BA.debugLine="Sub ReadFromEEPROM";
 //BA.debugLineNum = 190;BA.debugLine="Dim be(10) As Object 'used as a storage buffer fo";
_be =be_ann136_4e2.wrapObjects((void**)be_ann136_4e3,be_ann136_4e1,10, sizeof(B4R::Object));
 //BA.debugLineNum = 191;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann137_3;
 //BA.debugLineNum = 192;BA.debugLine="Dim serializator As B4RSerializator";
_serializator = &be_ann138_3;
 //BA.debugLineNum = 193;BA.debugLine="Dim eeprom As EEPROM";
_eeprom = &be_ann139_3;
 //BA.debugLineNum = 195;BA.debugLine="Dim ByteLengthOfDataInEEPROM() As Byte";
_bytelengthofdataineeprom =be_ann140_4e2.wrap(be_ann140_4e1,0);
 //BA.debugLineNum = 196;BA.debugLine="Dim ActualLengthOfDataInEEPROM As Int";
_actuallengthofdataineeprom = 0;
 //BA.debugLineNum = 197;BA.debugLine="Dim ByteDataInEEPROM() As Byte";
_bytedataineeprom =be_ann142_4e2.wrap(be_ann142_4e1,0);
 //BA.debugLineNum = 198;BA.debugLine="Dim ObjectsInEEPROM() As Object";
_objectsineeprom =be_ann143_4e2.wrapObjects((void**)be_ann143_4e3,be_ann143_4e1,0, sizeof(B4R::Object));
 //BA.debugLineNum = 199;BA.debugLine="Log(\"Reading data from the EEPROM...\")";
B4R::Common::LogHelper(1,102,F("Reading data from the EEPROM..."));
 //BA.debugLineNum = 201;BA.debugLine="ByteLengthOfDataInEEPROM = eeprom.ReadBytes(700,";
_bytelengthofdataineeprom = _eeprom->ReadBytes((UInt) (700),(UInt) (2));
 //BA.debugLineNum = 203;BA.debugLine="ActualLengthOfDataInEEPROM =  bc.IntsFromBytes(By";
_actuallengthofdataineeprom = ((Int*)ByteConverter_IntsFromBytes(_bytelengthofdataineeprom)->getData((UInt) (0)))[B4R::Array::staticIndex];
 //BA.debugLineNum = 206;BA.debugLine="ByteDataInEEPROM = eeprom.ReadBytes(702, ActualLe";
_bytedataineeprom = _eeprom->ReadBytes((UInt) (702),(UInt) (_actuallengthofdataineeprom));
 //BA.debugLineNum = 209;BA.debugLine="ObjectsInEEPROM = serializator.ConvertBytesToArra";
_objectsineeprom = _serializator->ConvertBytesToArray(_bytedataineeprom,_be);
 //BA.debugLineNum = 216;BA.debugLine="Log(\"WiFiSSID: \",ObjectsInEEPROM(0))";
B4R::Common::LogHelper(2,102,F("WiFiSSID: "),100,((B4R::Object**)_objectsineeprom->getData((UInt) (0)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 217;BA.debugLine="Log(\"WiFiPassword: \",ObjectsInEEPROM(1))";
B4R::Common::LogHelper(2,102,F("WiFiPassword: "),100,((B4R::Object**)_objectsineeprom->getData((UInt) (1)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 218;BA.debugLine="Log(\"MQTTUsername: \",ObjectsInEEPROM(2))";
B4R::Common::LogHelper(2,102,F("MQTTUsername: "),100,((B4R::Object**)_objectsineeprom->getData((UInt) (2)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 219;BA.debugLine="Log(\"MQTT_Password: \",ObjectsInEEPROM(3))";
B4R::Common::LogHelper(2,102,F("MQTT_Password: "),100,((B4R::Object**)_objectsineeprom->getData((UInt) (3)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 220;BA.debugLine="Log(\"MQTTServer: \",ObjectsInEEPROM(4))";
B4R::Common::LogHelper(2,102,F("MQTTServer: "),100,((B4R::Object**)_objectsineeprom->getData((UInt) (4)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 221;BA.debugLine="Log(\"MQTT_Port: \",ObjectsInEEPROM(5))";
B4R::Common::LogHelper(2,102,F("MQTT_Port: "),100,((B4R::Object**)_objectsineeprom->getData((UInt) (5)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 222;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayclose(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann52_4;
B4R::B4RString be_ann52_6;
 //BA.debugLineNum = 77;BA.debugLine="Private Sub RelayClose (tag As Byte)";
 //BA.debugLineNum = 78;BA.debugLine="ReadFromEEPROM";
_readfromeeprom();
 //BA.debugLineNum = 79;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 80;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 82;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 83;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 85;BA.debugLine="Log(\"*Relay has been closed\")";
B4R::Common::LogHelper(1,102,F("*Relay has been closed"));
 //BA.debugLineNum = 86;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been closed\")";
b4r_main::_mqtt->Publish(be_ann52_4.wrap("Andy"),(be_ann52_6.wrap("*Relay has been closed"))->GetBytes());
 //BA.debugLineNum = 87;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 88;BA.debugLine="CallSubPlus(\"RelayOpen\", 15000, 0)";
B4R::__c->CallSubPlus(_relayopen,(ULong) (15000),(Byte) (0));
 //BA.debugLineNum = 89;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopen(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann64_4;
B4R::B4RString be_ann64_6;
 //BA.debugLineNum = 91;BA.debugLine="Private Sub RelayOpen (tag As Byte)";
 //BA.debugLineNum = 92;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 93;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 95;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 96;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 98;BA.debugLine="Log(\"*Relay has been opened\")";
B4R::Common::LogHelper(1,102,F("*Relay has been opened"));
 //BA.debugLineNum = 99;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been opened\")";
b4r_main::_mqtt->Publish(be_ann64_4.wrap("Andy"),(be_ann64_6.wrap("*Relay has been opened"))->GetBytes());
 //BA.debugLineNum = 100;BA.debugLine="d6.DigitalWrite(False)";
b4r_main::_d6->DigitalWrite(Common_False);
 //BA.debugLineNum = 101;BA.debugLine="CallSubPlus(\"RelayClose\", 5000, 0)";
B4R::__c->CallSubPlus(_relayclose,(ULong) (5000),(Byte) (0));
 //BA.debugLineNum = 102;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_writetoeeprom(B4R::B4RString* _wifissid,B4R::B4RString* _wifipassword,B4R::B4RString* _mqttusername,B4R::B4RString* _mqtt_password,B4R::B4RString* _mqttserver,Int _mqtt_port){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann125_10;
B4R::Object be_ann125_12;
B4R::Object be_ann125_14;
B4R::Object be_ann125_16;
B4R::Object be_ann125_18;
B4R::Object be_ann125_20;
B4R::Object* be_ann125_21e1[6];
B4R::Array be_ann125_21e2;
B4R::Array* _listofobjectstostore = NULL;
Byte be_ann126_4e1[0];
B4R::Array be_ann126_4e2;
B4R::Array* _bytedatatostore = NULL;
B4R::ByteConverter be_ann127_3;
B4R::ByteConverter* _bc = NULL;
B4R::B4RSerializator be_ann128_3;
B4R::B4RSerializator* _serializator = NULL;
B4R::B4REEPROM be_ann129_3;
B4R::B4REEPROM* _eeprom = NULL;
Int be_ann132_15e1[1];
B4R::Array be_ann132_15e2;
 //BA.debugLineNum = 164;BA.debugLine="Sub WriteToEEPROM(WiFiSSID As String, WiFiPassword";
 //BA.debugLineNum = 169;BA.debugLine="Dim ListOfObjectsToStore() As Object = Array(WiFi";
_listofobjectstostore = be_ann125_21e2.create(be_ann125_21e1,6,100,be_ann125_10.wrapPointer(_wifissid->data),be_ann125_12.wrapPointer(_wifipassword->data),be_ann125_14.wrapPointer(_mqttusername->data),be_ann125_16.wrapPointer(_mqtt_password->data),be_ann125_18.wrapPointer(_mqttserver->data),be_ann125_20.wrapNumber((Long)_mqtt_port));
 //BA.debugLineNum = 170;BA.debugLine="Dim ByteDataToStore() As Byte";
_bytedatatostore =be_ann126_4e2.wrap(be_ann126_4e1,0);
 //BA.debugLineNum = 171;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann127_3;
 //BA.debugLineNum = 172;BA.debugLine="Dim serializator As B4RSerializator";
_serializator = &be_ann128_3;
 //BA.debugLineNum = 173;BA.debugLine="Dim eeprom As EEPROM";
_eeprom = &be_ann129_3;
 //BA.debugLineNum = 177;BA.debugLine="ByteDataToStore = serializator.ConvertArrayToByte";
_bytedatatostore = _serializator->ConvertArrayToBytes(_listofobjectstostore);
 //BA.debugLineNum = 179;BA.debugLine="Log(\"Writing objects into the EEPROM...\")";
B4R::Common::LogHelper(1,102,F("Writing objects into the EEPROM..."));
 //BA.debugLineNum = 181;BA.debugLine="eeprom.WriteBytes(bc.IntsToBytes(Array As Int(Byt";
_eeprom->WriteBytes(ByteConverter_IntsToBytes(be_ann132_15e2.create(be_ann132_15e1,1,3,_bytedatatostore->length)),(UInt) (700));
 //BA.debugLineNum = 183;BA.debugLine="eeprom.WriteBytes(ByteDataToStore, 702)";
_eeprom->WriteBytes(_bytedatatostore,(UInt) (702));
 //BA.debugLineNum = 184;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
