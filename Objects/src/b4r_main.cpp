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
B4R::Array* b4r_main::_settings;
b4r_globalstore* b4r_main::_globalstore;
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
static Byte be_gann19_4e1[4];
static B4R::Array be_gann19_4e2;


 void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann27_6;
B4R::B4RString* _clientid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 32;BA.debugLine="Private Sub AppStart";
 //BA.debugLineNum = 33;BA.debugLine="Serial1.Initialize(115200)";
b4r_main::_serial1->Initialize((ULong) (115200));
 //BA.debugLineNum = 34;BA.debugLine="Delay(3000)";
Common_Delay((ULong) (3000));
 //BA.debugLineNum = 35;BA.debugLine="Log(\"AppStart\")";
B4R::Common::LogHelper(1,102,F("AppStart"));
 //BA.debugLineNum = 40;BA.debugLine="pin16.Initialize(16, pin16.MODE_OUTPUT)";
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
 //BA.debugLineNum = 41;BA.debugLine="d6.Initialize(d1pins.D6, d6.MODE_OUTPUT)";
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
 //BA.debugLineNum = 44;BA.debugLine="GlobalStore.Put(4,\"1\")";
b4r_main::_globalstore->_put(4,(be_ann27_6.wrap("1"))->GetBytes());
 //BA.debugLineNum = 45;BA.debugLine="ReadFromEEPROM";
_readfromeeprom();
 //BA.debugLineNum = 46;BA.debugLine="ConnectToWifi";
_connecttowifi();
 //BA.debugLineNum = 49;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'creat";
_clientid = B4R::B4RString::fromNumber((Long)(Common_Rnd((Long) (0),(Long) (999999999))));
 //BA.debugLineNum = 50;BA.debugLine="MQTT.Initialize2(WiFiStr.stream, MQTTHostName, MQ";
b4r_main::_mqtt->Initialize2(b4r_main::_wifistr->getStream(),b4r_main::_mqtthostname,(UInt) (b4r_main::_mqttport),_clientid,_mqtt_messagearrived,_mqtt_disconnected);
 //BA.debugLineNum = 51;BA.debugLine="MQTTOpt.Initialize(MQTTUser, MQTTPassword)";
b4r_main::_mqttopt->Initialize(b4r_main::_mqttuser,b4r_main::_mqttpassword);
 //BA.debugLineNum = 52;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 55;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 //BA.debugLineNum = 56;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_cleareeprom(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4REEPROM be_ann246_3;
B4R::B4REEPROM* _eeprom = NULL;
UInt _i = 0;
Byte be_ann250_9e1[1];
B4R::Array be_ann250_9e2;
 //BA.debugLineNum = 313;BA.debugLine="Sub ClearEEPROM";
 //BA.debugLineNum = 314;BA.debugLine="Dim eeprom As EEPROM";
_eeprom = &be_ann246_3;
 //BA.debugLineNum = 315;BA.debugLine="Dim i As UInt";
_i = 0;
 //BA.debugLineNum = 317;BA.debugLine="Log(\"Size: \", eeprom.Size, \" bytes\")";
B4R::Common::LogHelper(3,102,F("Size: "),4,_eeprom->getSize(),102,F(" bytes"));
 //BA.debugLineNum = 318;BA.debugLine="For i = 0 To eeprom.Size";
{
const int step4 = 1;
const int limit4 = _eeprom->getSize();
_i = (UInt) (0) ;
for (;(step4 > 0 && _i <= limit4) || (step4 < 0 && _i >= limit4) ;_i = ((UInt)(0 + _i + step4))  ) {
 //BA.debugLineNum = 319;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), i)";
_eeprom->WriteBytes(be_ann250_9e2.create(be_ann250_9e1,1,1,(Byte) (0)),_i);
 //BA.debugLineNum = 320;BA.debugLine="Log(i)";
B4R::Common::LogHelper(1,4,_i);
 }
};
 //BA.debugLineNum = 322;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_connecttowifi(){
const UInt cp = B4R::StackMemory::cp;
B4R::ByteConverter be_ann151_3;
B4R::ByteConverter* _bc = NULL;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
B4R::ByteConverter be_ann171_3;
B4R::B4RString* _count = B4R::B4RString::EMPTY;
B4R::Object be_ann178_6;
B4R::Object be_ann180_6;
B4R::Object be_ann182_6;
B4R::Object be_ann184_6;
B4R::B4RString be_ann185_6;
 //BA.debugLineNum = 177;BA.debugLine="Sub ConnectToWifi";
 //BA.debugLineNum = 178;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann151_3;
 //BA.debugLineNum = 179;BA.debugLine="Dim SSID As String";
_ssid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 180;BA.debugLine="Dim password As String";
_password = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 182;BA.debugLine="SSID = bc.StringFromBytes(GlobalStore.Slot0)";
_ssid = _bc->StringFromBytes(b4r_main::_globalstore->_slot0);
 //BA.debugLineNum = 183;BA.debugLine="If SSID.Length = 0 Then";
if (_ssid->getLength()==0) { 
 //BA.debugLineNum = 184;BA.debugLine="SSID = WiFiSSID";
_ssid = b4r_main::_wifissid;
 //BA.debugLineNum = 185;BA.debugLine="GlobalStore.Put(0,SSID)";
b4r_main::_globalstore->_put(0,(_ssid)->GetBytes());
 };
 //BA.debugLineNum = 188;BA.debugLine="Log(\"SSID: \",SSID)";
B4R::Common::LogHelper(2,102,F("SSID: "),101,_ssid->data);
 //BA.debugLineNum = 189;BA.debugLine="password = bc.StringFromBytes(GlobalStore.Slot1)";
_password = _bc->StringFromBytes(b4r_main::_globalstore->_slot1);
 //BA.debugLineNum = 190;BA.debugLine="If password.Length = 0 Then";
if (_password->getLength()==0) { 
 //BA.debugLineNum = 191;BA.debugLine="password = WiFiPassword";
_password = b4r_main::_wifipassword;
 //BA.debugLineNum = 192;BA.debugLine="GlobalStore.Put(1,password)";
b4r_main::_globalstore->_put(1,(_password)->GetBytes());
 };
 //BA.debugLineNum = 194;BA.debugLine="Log(\"Password: \",password)";
B4R::Common::LogHelper(2,102,F("Password: "),101,_password->data);
 //BA.debugLineNum = 196;BA.debugLine="WiFi.Connect2(SSID, password)";
b4r_main::_wifi->Connect2(_ssid,_password);
 //BA.debugLineNum = 198;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 199;BA.debugLine="Log(\"Connected to WiFi = \",SSID,\" Local IP = \",";
B4R::Common::LogHelper(4,102,F("Connected to WiFi = "),101,_ssid->data,102,F(" Local IP = "),101,b4r_main::_wifi->getLocalIp()->data);
 }else {
 //BA.debugLineNum = 201;BA.debugLine="Log(\"Not Connected to WiFi\")";
B4R::Common::LogHelper(1,102,F("Not Connected to WiFi"));
 //BA.debugLineNum = 202;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann171_3;
 //BA.debugLineNum = 203;BA.debugLine="Dim count As String = bc.StringFromBytes(GlobalS";
_count = _bc->StringFromBytes(b4r_main::_globalstore->_slot4);
 //BA.debugLineNum = 204;BA.debugLine="count = NumberFormat(count,1,0)";
_count = B4R::__c->NumberFormat((Double)(atof(_count->data)),(Byte) (1),(Byte) (0));
 //BA.debugLineNum = 205;BA.debugLine="Log(\"WiFi connection attempts: \",count)";
B4R::Common::LogHelper(2,102,F("WiFi connection attempts: "),101,_count->data);
 //BA.debugLineNum = 206;BA.debugLine="If count > 3 Then";
if ((Double)(atof(_count->data))>3) { 
 //BA.debugLineNum = 207;BA.debugLine="Log(\"Temporarily reverting to CloydNote8 networ";
B4R::Common::LogHelper(1,102,F("Temporarily reverting to CloydNote8 network"));
 //BA.debugLineNum = 208;BA.debugLine="GlobalStore.Put(0,WiFiSSID) ' SSID";
b4r_main::_globalstore->_put(0,(b4r_main::_wifissid)->GetBytes());
 //BA.debugLineNum = 209;BA.debugLine="Log(\"GlobalStore.Slot0: \",GlobalStore.Slot0)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot0: "),100,be_ann178_6.wrapPointer(b4r_main::_globalstore->_slot0));
 //BA.debugLineNum = 211;BA.debugLine="GlobalStore.Put(1,WiFiPassword) ' Password";
b4r_main::_globalstore->_put(1,(b4r_main::_wifipassword)->GetBytes());
 //BA.debugLineNum = 212;BA.debugLine="Log(\"GlobalStore.Slot1: \",GlobalStore.Slot1)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot1: "),100,be_ann180_6.wrapPointer(b4r_main::_globalstore->_slot1));
 //BA.debugLineNum = 214;BA.debugLine="GlobalStore.Put(2,RelayOpenDelay) ' Open delay";
b4r_main::_globalstore->_put(2,(b4r_main::_relayopendelay)->GetBytes());
 //BA.debugLineNum = 215;BA.debugLine="Log(\"GlobalStore.Slot2: \",GlobalStore.Slot2)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot2: "),100,be_ann182_6.wrapPointer(b4r_main::_globalstore->_slot2));
 //BA.debugLineNum = 217;BA.debugLine="GlobalStore.Put(3,RelayClosedDelay) ' Closed de";
b4r_main::_globalstore->_put(3,(b4r_main::_relaycloseddelay)->GetBytes());
 //BA.debugLineNum = 218;BA.debugLine="Log(\"GlobalStore.Slot3: \",GlobalStore.Slot3)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot3: "),100,be_ann184_6.wrapPointer(b4r_main::_globalstore->_slot3));
 //BA.debugLineNum = 220;BA.debugLine="GlobalStore.Put(4,\"1\")";
b4r_main::_globalstore->_put(4,(be_ann185_6.wrap("1"))->GetBytes());
 }else {
 //BA.debugLineNum = 223;BA.debugLine="GlobalStore.Put(4,bc.StringToBytes(count + 1))";
b4r_main::_globalstore->_put(4,_bc->StringToBytes(B4R::B4RString::fromNumber((Double)((Double)(atof(_count->data))+1))));
 };
 };
 //BA.debugLineNum = 226;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_connect(Byte _unused){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann47_4;
 //BA.debugLineNum = 58;BA.debugLine="Sub MQTT_Connect(Unused As Byte)";
 //BA.debugLineNum = 59;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 60;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 62;BA.debugLine="If MQTT.Connect = False Then";
if (b4r_main::_mqtt->Connect()==Common_False) { 
 //BA.debugLineNum = 63;BA.debugLine="Log(\"Connecting to broker\")";
B4R::Common::LogHelper(1,102,F("Connecting to broker"));
 //BA.debugLineNum = 64;BA.debugLine="MQTT.Connect2(MQTTOpt)";
b4r_main::_mqtt->Connect2(b4r_main::_mqttopt);
 //BA.debugLineNum = 65;BA.debugLine="CallSubPlus(\"MQTT_Connect\", 1000, 0)";
B4R::__c->CallSubPlus(_mqtt_connect,(ULong) (1000),(Byte) (0));
 }else {
 //BA.debugLineNum = 67;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 68;BA.debugLine="Log(\"Connected to broker\")";
B4R::Common::LogHelper(1,102,F("Connected to broker"));
 //BA.debugLineNum = 69;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
b4r_main::_mqtt->Subscribe(be_ann47_4.wrap("Andy"),(Byte) (0));
 };
 //BA.debugLineNum = 71;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_disconnected(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 167;BA.debugLine="Sub mqtt_Disconnected";
 //BA.debugLineNum = 168;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 169;BA.debugLine="Log(\"Disconnected from broker\")";
B4R::Common::LogHelper(1,102,F("Disconnected from broker"));
 //BA.debugLineNum = 170;BA.debugLine="MQTT.Close";
b4r_main::_mqtt->Close();
 //BA.debugLineNum = 171;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 172;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 174;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 175;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_messagearrived(B4R::B4RString* _topic,B4R::Array* _payload){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann90_8;
B4R::B4RString be_ann91_3;
B4R::B4RString be_ann92_4;
B4R::B4RString be_ann92_6;
B4R::B4RString be_ann95_3;
B4R::B4RString be_ann96_4;
B4R::B4RString be_ann96_6;
B4R::B4RString be_ann99_3;
B4R::B4RString be_ann100_4;
B4R::B4RString be_ann100_6;
B4R::B4RString be_ann102_3;
B4R::B4RString be_ann104_4;
B4R::B4RString be_ann104_6;
B4R::B4RString be_ann106_4;
B4R::B4RString be_ann106_6;
B4R::B4RString be_ann108_4;
B4R::B4RString be_ann108_6;
B4R::ByteConverter be_ann111_3;
B4R::ByteConverter* _bc = NULL;
Int _c = 0;
B4R::B4RString be_ann113_7;
B4R::Array* _s = NULL;
B4R::B4RString be_ann114_13;
Byte _b = 0;
B4R::Object be_ann119_6;
B4R::Object be_ann123_6;
B4R::Object be_ann127_6;
B4R::Object be_ann131_6;
B4R::ByteConverter be_ann135_3;
 //BA.debugLineNum = 113;BA.debugLine="Sub mqtt_MessageArrived (Topic As String, Payload(";
 //BA.debugLineNum = 114;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 115;BA.debugLine="Log(\"Message arrived. Topic=\", Topic, \" Payload=\"";
B4R::Common::LogHelper(4,102,F("Message arrived. Topic="),101,_topic->data,102,F(" Payload="),100,be_ann90_8.wrapPointer(_payload));
 //BA.debugLineNum = 116;BA.debugLine="If Payload=\"Remotely close relay\" Then";
if ((_payload)->equals((be_ann91_3.wrap("Remotely close relay"))->GetBytes())) { 
 //BA.debugLineNum = 117;BA.debugLine="MQTT.Publish(\"Andy\",\"*Closing relay by remote\")";
b4r_main::_mqtt->Publish(be_ann92_4.wrap("Andy"),(be_ann92_6.wrap("*Closing relay by remote"))->GetBytes());
 //BA.debugLineNum = 118;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 119;BA.debugLine="StopRelay = True";
b4r_main::_stoprelay = Common_True;
 }else if((_payload)->equals((be_ann95_3.wrap("Remotely open relay"))->GetBytes())) { 
 //BA.debugLineNum = 121;BA.debugLine="MQTT.Publish(\"Andy\",\"*Opening relay by remote\")";
b4r_main::_mqtt->Publish(be_ann96_4.wrap("Andy"),(be_ann96_6.wrap("*Opening relay by remote"))->GetBytes());
 //BA.debugLineNum = 122;BA.debugLine="StopRelay = False";
b4r_main::_stoprelay = Common_False;
 //BA.debugLineNum = 123;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 }else if((_payload)->equals((be_ann99_3.wrap("Restart controller"))->GetBytes())) { 
 //BA.debugLineNum = 125;BA.debugLine="MQTT.Publish(\"Andy\",\"*Restarting relay by remote";
b4r_main::_mqtt->Publish(be_ann100_4.wrap("Andy"),(be_ann100_6.wrap("*Restarting relay by remote"))->GetBytes());
 //BA.debugLineNum = 126;BA.debugLine="ESP.Restart";
b4r_main::_esp->Restart();
 }else if((_payload)->equals((be_ann102_3.wrap("Check relay status"))->GetBytes())) { 
 //BA.debugLineNum = 128;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 129;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is permanently clos";
b4r_main::_mqtt->Publish(be_ann104_4.wrap("Andy"),(be_ann104_6.wrap("*Relay is permanently closed"))->GetBytes());
 }else if(b4r_main::_d6->DigitalRead()) { 
 //BA.debugLineNum = 131;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is closed\")";
b4r_main::_mqtt->Publish(be_ann106_4.wrap("Andy"),(be_ann106_6.wrap("*Relay is closed"))->GetBytes());
 }else {
 //BA.debugLineNum = 133;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is open\")";
b4r_main::_mqtt->Publish(be_ann108_4.wrap("Andy"),(be_ann108_6.wrap("*Relay is open"))->GetBytes());
 };
 }else {
 //BA.debugLineNum = 136;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann111_3;
 //BA.debugLineNum = 137;BA.debugLine="Dim c As Int = 0";
_c = 0;
 //BA.debugLineNum = 138;BA.debugLine="If bc.IndexOf(Payload,\"|\") > 0 Then";
if (_bc->IndexOf(_payload,(be_ann113_7.wrap("|"))->GetBytes())>0) { 
 //BA.debugLineNum = 139;BA.debugLine="For Each s() As Byte In bc.Split(Payload, \"|\")";
B4R::Iterator* group26 = _bc->Split(_payload,(be_ann114_13.wrap("|"))->GetBytes());
while (group26->MoveNext()) {
_s = (B4R::Array*)B4R::Object::toPointer(group26->Get());
 //BA.debugLineNum = 140;BA.debugLine="Dim b As Byte = bc.StringFromBytes(s)";
_b = (Byte)(atof(_bc->StringFromBytes(_s)->data));
 //BA.debugLineNum = 141;BA.debugLine="settings(c) = b";
((Byte*)b4r_main::_settings->getData((UInt) (_c)))[B4R::Array::staticIndex] = _b;
 //BA.debugLineNum = 142;BA.debugLine="If c = 0 Then";
if (_c==0) { 
 //BA.debugLineNum = 143;BA.debugLine="GlobalStore.Put(0,s) ' SSID";
b4r_main::_globalstore->_put(0,_s);
 //BA.debugLineNum = 144;BA.debugLine="Log(\"GlobalStore.Slot0: \",GlobalStore.Slot0)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot0: "),100,be_ann119_6.wrapPointer(b4r_main::_globalstore->_slot0));
 };
 //BA.debugLineNum = 146;BA.debugLine="If c = 1 Then";
if (_c==1) { 
 //BA.debugLineNum = 147;BA.debugLine="GlobalStore.Put(1,s) ' Password";
b4r_main::_globalstore->_put(1,_s);
 //BA.debugLineNum = 148;BA.debugLine="Log(\"GlobalStore.Slot1: \",GlobalStore.Slot1)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot1: "),100,be_ann123_6.wrapPointer(b4r_main::_globalstore->_slot1));
 };
 //BA.debugLineNum = 150;BA.debugLine="If c = 2 Then";
if (_c==2) { 
 //BA.debugLineNum = 151;BA.debugLine="GlobalStore.Put(2,s) ' Open delay";
b4r_main::_globalstore->_put(2,_s);
 //BA.debugLineNum = 152;BA.debugLine="Log(\"GlobalStore.Slot2: \",GlobalStore.Slot2)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot2: "),100,be_ann127_6.wrapPointer(b4r_main::_globalstore->_slot2));
 };
 //BA.debugLineNum = 154;BA.debugLine="If c = 3 Then";
if (_c==3) { 
 //BA.debugLineNum = 155;BA.debugLine="GlobalStore.Put(3,s) ' Closed delay";
b4r_main::_globalstore->_put(3,_s);
 //BA.debugLineNum = 156;BA.debugLine="Log(\"GlobalStore.Slot3: \",GlobalStore.Slot3)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot3: "),100,be_ann131_6.wrapPointer(b4r_main::_globalstore->_slot3));
 };
 //BA.debugLineNum = 158;BA.debugLine="c = c + 1";
_c = (Int) (_c+1);
 }
;
 //BA.debugLineNum = 160;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann135_3;
 //BA.debugLineNum = 161;BA.debugLine="WriteToEEPROM(bc.StringFromBytes(GlobalStore.Sl";
_writetoeeprom(_bc->StringFromBytes(b4r_main::_globalstore->_slot0),_bc->StringFromBytes(b4r_main::_globalstore->_slot1),_bc->StringFromBytes(b4r_main::_globalstore->_slot2),_bc->StringFromBytes(b4r_main::_globalstore->_slot3));
 //BA.debugLineNum = 162;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 };
 //BA.debugLineNum = 165;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}

void b4r_main::initializeProcessGlobals() {
     B4R::StackMemory::buffer = (byte*)malloc(STACK_BUFFER_SIZE);
     b4r_main::_process_globals();
b4r_globalstore::_process_globals();

   
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
 //BA.debugLineNum = 25;BA.debugLine="Private WiFiSSID As String = \"CloydNote8\"";
b4r_main::_wifissid = be_gann15_5.wrap("CloydNote8");
 //BA.debugLineNum = 26;BA.debugLine="Private WiFiPassword As String = \"adjj6347\"";
b4r_main::_wifipassword = be_gann16_5.wrap("adjj6347");
 //BA.debugLineNum = 27;BA.debugLine="Private RelayOpenDelay As String = \"5000\"";
b4r_main::_relayopendelay = be_gann17_5.wrap("5000");
 //BA.debugLineNum = 28;BA.debugLine="Private RelayClosedDelay As String = \"15000\"";
b4r_main::_relaycloseddelay = be_gann18_5.wrap("15000");
 //BA.debugLineNum = 29;BA.debugLine="Private settings(4) As Byte";
b4r_main::_settings =be_gann19_4e2.wrap(be_gann19_4e1,4);
 //BA.debugLineNum = 30;BA.debugLine="End Sub";
}
void b4r_main::_readfromeeprom(){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann204_4e1[10];
B4R::Array be_ann204_4e2;
B4R::Object* be_ann204_4e3[10];
B4R::Array* _be = NULL;
B4R::ByteConverter be_ann205_3;
B4R::ByteConverter* _bc = NULL;
B4R::B4RSerializator be_ann206_3;
B4R::B4RSerializator* _serializator = NULL;
B4R::B4REEPROM be_ann207_3;
B4R::B4REEPROM* _eeprom = NULL;
Byte be_ann208_4e1[0];
B4R::Array be_ann208_4e2;
B4R::Array* _bytelengthofdataineeprom = NULL;
Int _actuallengthofdataineeprom = 0;
Byte be_ann210_4e1[0];
B4R::Array be_ann210_4e2;
B4R::Array* _bytedataineeprom = NULL;
B4R::Object be_ann211_4e1[0];
B4R::Array be_ann211_4e2;
B4R::Object* be_ann211_4e3[0];
B4R::Array* _objectsineeprom = NULL;
B4R::ByteConverter be_ann223_3;
B4R::Object be_ann224_7;
B4R::Object be_ann226_6;
B4R::Object be_ann228_6;
B4R::Object be_ann230_6;
B4R::Object be_ann232_6;
B4R::Object be_ann235_6;
B4R::Object be_ann237_6;
B4R::Object be_ann239_6;
B4R::Object be_ann241_6;
 //BA.debugLineNum = 248;BA.debugLine="Sub ReadFromEEPROM";
 //BA.debugLineNum = 249;BA.debugLine="Dim be(10) As Object 'used as a storage buffer fo";
_be =be_ann204_4e2.wrapObjects((void**)be_ann204_4e3,be_ann204_4e1,10, sizeof(B4R::Object));
 //BA.debugLineNum = 250;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann205_3;
 //BA.debugLineNum = 251;BA.debugLine="Dim serializator As B4RSerializator";
_serializator = &be_ann206_3;
 //BA.debugLineNum = 252;BA.debugLine="Dim eeprom As EEPROM";
_eeprom = &be_ann207_3;
 //BA.debugLineNum = 254;BA.debugLine="Dim ByteLengthOfDataInEEPROM() As Byte";
_bytelengthofdataineeprom =be_ann208_4e2.wrap(be_ann208_4e1,0);
 //BA.debugLineNum = 255;BA.debugLine="Dim ActualLengthOfDataInEEPROM As Int";
_actuallengthofdataineeprom = 0;
 //BA.debugLineNum = 256;BA.debugLine="Dim ByteDataInEEPROM() As Byte";
_bytedataineeprom =be_ann210_4e2.wrap(be_ann210_4e1,0);
 //BA.debugLineNum = 257;BA.debugLine="Dim ObjectsInEEPROM() As Object";
_objectsineeprom =be_ann211_4e2.wrapObjects((void**)be_ann211_4e3,be_ann211_4e1,0, sizeof(B4R::Object));
 //BA.debugLineNum = 258;BA.debugLine="Log(\"Reading data from the EEPROM...\")";
B4R::Common::LogHelper(1,102,F("Reading data from the EEPROM..."));
 //BA.debugLineNum = 260;BA.debugLine="ByteLengthOfDataInEEPROM = eeprom.ReadBytes(700,";
_bytelengthofdataineeprom = _eeprom->ReadBytes((UInt) (700),(UInt) (2));
 //BA.debugLineNum = 262;BA.debugLine="ActualLengthOfDataInEEPROM =  bc.IntsFromBytes(By";
_actuallengthofdataineeprom = ((Int*)ByteConverter_IntsFromBytes(_bytelengthofdataineeprom)->getData((UInt) (0)))[B4R::Array::staticIndex];
 //BA.debugLineNum = 263;BA.debugLine="Log(\"ActualLengthOfDataInEEPROM: \",ActualLengthOf";
B4R::Common::LogHelper(2,102,F("ActualLengthOfDataInEEPROM: "),3,_actuallengthofdataineeprom);
 //BA.debugLineNum = 264;BA.debugLine="If ActualLengthOfDataInEEPROM = 0 Then";
if (_actuallengthofdataineeprom==0) { 
 //BA.debugLineNum = 265;BA.debugLine="WriteToEEPROM(WiFiSSID,WiFiPassword,5000,15000)";
_writetoeeprom(b4r_main::_wifissid,b4r_main::_wifipassword,B4R::B4RString::fromNumber((Long)(5000)),B4R::B4RString::fromNumber((Long)(15000)));
 //BA.debugLineNum = 267;BA.debugLine="ByteLengthOfDataInEEPROM = eeprom.ReadBytes(700,";
_bytelengthofdataineeprom = _eeprom->ReadBytes((UInt) (700),(UInt) (2));
 //BA.debugLineNum = 269;BA.debugLine="ActualLengthOfDataInEEPROM =  bc.IntsFromBytes(B";
_actuallengthofdataineeprom = ((Int*)ByteConverter_IntsFromBytes(_bytelengthofdataineeprom)->getData((UInt) (0)))[B4R::Array::staticIndex];
 };
 //BA.debugLineNum = 273;BA.debugLine="ByteDataInEEPROM = eeprom.ReadBytes(702, ActualLe";
_bytedataineeprom = _eeprom->ReadBytes((UInt) (702),(UInt) (_actuallengthofdataineeprom));
 //BA.debugLineNum = 276;BA.debugLine="ObjectsInEEPROM = serializator.ConvertBytesToArra";
_objectsineeprom = _serializator->ConvertBytesToArray(_bytedataineeprom,_be);
 //BA.debugLineNum = 282;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann223_3;
 //BA.debugLineNum = 283;BA.debugLine="If ObjectsInEEPROM(0) <> 0 Then";
if ((((B4R::Object**)_objectsineeprom->getData((UInt) (0)))[B4R::Array::staticIndex])->equals(be_ann224_7.wrapNumber((Long)0)) == false) { 
 //BA.debugLineNum = 284;BA.debugLine="GlobalStore.Put(0,bc.StringFromBytes(ObjectsInEE";
b4r_main::_globalstore->_put(0,(_bc->StringFromBytes((B4R::Array*)B4R::Object::toPointer(((B4R::Object**)_objectsineeprom->getData((UInt) (0)))[B4R::Array::staticIndex])))->GetBytes());
 //BA.debugLineNum = 285;BA.debugLine="Log(\"GlobalStore.Slot0: \",GlobalStore.Slot0)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot0: "),100,be_ann226_6.wrapPointer(b4r_main::_globalstore->_slot0));
 //BA.debugLineNum = 287;BA.debugLine="GlobalStore.Put(1,bc.StringFromBytes(ObjectsInEE";
b4r_main::_globalstore->_put(1,(_bc->StringFromBytes((B4R::Array*)B4R::Object::toPointer(((B4R::Object**)_objectsineeprom->getData((UInt) (1)))[B4R::Array::staticIndex])))->GetBytes());
 //BA.debugLineNum = 288;BA.debugLine="Log(\"GlobalStore.Slot1: \",GlobalStore.Slot1)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot1: "),100,be_ann228_6.wrapPointer(b4r_main::_globalstore->_slot1));
 //BA.debugLineNum = 290;BA.debugLine="GlobalStore.Put(2,bc.StringFromBytes(ObjectsInEE";
b4r_main::_globalstore->_put(2,(_bc->StringFromBytes((B4R::Array*)B4R::Object::toPointer(((B4R::Object**)_objectsineeprom->getData((UInt) (2)))[B4R::Array::staticIndex])))->GetBytes());
 //BA.debugLineNum = 291;BA.debugLine="Log(\"GlobalStore.Slot2: \",GlobalStore.Slot2)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot2: "),100,be_ann230_6.wrapPointer(b4r_main::_globalstore->_slot2));
 //BA.debugLineNum = 293;BA.debugLine="GlobalStore.Put(3,bc.StringFromBytes(ObjectsInEE";
b4r_main::_globalstore->_put(3,(_bc->StringFromBytes((B4R::Array*)B4R::Object::toPointer(((B4R::Object**)_objectsineeprom->getData((UInt) (3)))[B4R::Array::staticIndex])))->GetBytes());
 //BA.debugLineNum = 294;BA.debugLine="Log(\"GlobalStore.Slot3: \",GlobalStore.Slot3)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot3: "),100,be_ann232_6.wrapPointer(b4r_main::_globalstore->_slot3));
 }else {
 //BA.debugLineNum = 296;BA.debugLine="GlobalStore.Put(0,WiFiSSID) ' SSID";
b4r_main::_globalstore->_put(0,(b4r_main::_wifissid)->GetBytes());
 //BA.debugLineNum = 297;BA.debugLine="Log(\"GlobalStore.Slot0: \",GlobalStore.Slot0)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot0: "),100,be_ann235_6.wrapPointer(b4r_main::_globalstore->_slot0));
 //BA.debugLineNum = 299;BA.debugLine="GlobalStore.Put(1,WiFiPassword) ' Password";
b4r_main::_globalstore->_put(1,(b4r_main::_wifipassword)->GetBytes());
 //BA.debugLineNum = 300;BA.debugLine="Log(\"GlobalStore.Slot1: \",GlobalStore.Slot1)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot1: "),100,be_ann237_6.wrapPointer(b4r_main::_globalstore->_slot1));
 //BA.debugLineNum = 302;BA.debugLine="GlobalStore.Put(2,RelayOpenDelay) ' Open delay";
b4r_main::_globalstore->_put(2,(b4r_main::_relayopendelay)->GetBytes());
 //BA.debugLineNum = 303;BA.debugLine="Log(\"GlobalStore.Slot2: \",GlobalStore.Slot2)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot2: "),100,be_ann239_6.wrapPointer(b4r_main::_globalstore->_slot2));
 //BA.debugLineNum = 305;BA.debugLine="GlobalStore.Put(3,RelayClosedDelay) ' Closed del";
b4r_main::_globalstore->_put(3,(b4r_main::_relaycloseddelay)->GetBytes());
 //BA.debugLineNum = 306;BA.debugLine="Log(\"GlobalStore.Slot3: \",GlobalStore.Slot3)";
B4R::Common::LogHelper(2,102,F("GlobalStore.Slot3: "),100,be_ann241_6.wrapPointer(b4r_main::_globalstore->_slot3));
 //BA.debugLineNum = 308;BA.debugLine="WriteToEEPROM(WiFiSSID,WiFiPassword,5000,15000)";
_writetoeeprom(b4r_main::_wifissid,b4r_main::_wifipassword,B4R::B4RString::fromNumber((Long)(5000)),B4R::B4RString::fromNumber((Long)(15000)));
 };
 //BA.debugLineNum = 311;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayclose(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann58_4;
B4R::B4RString be_ann58_6;
B4R::ByteConverter be_ann60_3;
B4R::ByteConverter* _bc = NULL;
B4R::B4RString* _closeddelay = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 73;BA.debugLine="Private Sub RelayClose (tag As Byte)";
 //BA.debugLineNum = 74;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 75;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 77;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 78;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 80;BA.debugLine="Log(\"*Relay has been closed\")";
B4R::Common::LogHelper(1,102,F("*Relay has been closed"));
 //BA.debugLineNum = 81;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been closed\")";
b4r_main::_mqtt->Publish(be_ann58_4.wrap("Andy"),(be_ann58_6.wrap("*Relay has been closed"))->GetBytes());
 //BA.debugLineNum = 82;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 83;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann60_3;
 //BA.debugLineNum = 84;BA.debugLine="Dim closedDelay As String = bc.StringFromBytes(Gl";
_closeddelay = _bc->StringFromBytes(b4r_main::_globalstore->_slot3);
 //BA.debugLineNum = 85;BA.debugLine="If closedDelay.Length = 0 Then";
if (_closeddelay->getLength()==0) { 
 //BA.debugLineNum = 86;BA.debugLine="closedDelay = RelayClosedDelay";
_closeddelay = b4r_main::_relaycloseddelay;
 //BA.debugLineNum = 87;BA.debugLine="GlobalStore.Put(3,RelayClosedDelay)";
b4r_main::_globalstore->_put(3,(b4r_main::_relaycloseddelay)->GetBytes());
 };
 //BA.debugLineNum = 89;BA.debugLine="Log(\"closedDelay: \",closedDelay)";
B4R::Common::LogHelper(2,102,F("closedDelay: "),101,_closeddelay->data);
 //BA.debugLineNum = 90;BA.debugLine="CallSubPlus(\"RelayOpen\", closedDelay, 0)";
B4R::__c->CallSubPlus(_relayopen,(ULong)(atof(_closeddelay->data)),(Byte) (0));
 //BA.debugLineNum = 91;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopen(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann77_4;
B4R::B4RString be_ann77_6;
B4R::ByteConverter be_ann79_3;
B4R::ByteConverter* _bc = NULL;
B4R::B4RString* _opendelay = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 93;BA.debugLine="Private Sub RelayOpen (tag As Byte)";
 //BA.debugLineNum = 94;BA.debugLine="If WiFi.IsConnected = False Then";
if (b4r_main::_wifi->getIsConnected()==Common_False) { 
 //BA.debugLineNum = 95;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 97;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 98;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 100;BA.debugLine="Log(\"*Relay has been opened\")";
B4R::Common::LogHelper(1,102,F("*Relay has been opened"));
 //BA.debugLineNum = 101;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been opened\")";
b4r_main::_mqtt->Publish(be_ann77_4.wrap("Andy"),(be_ann77_6.wrap("*Relay has been opened"))->GetBytes());
 //BA.debugLineNum = 102;BA.debugLine="d6.DigitalWrite(False)";
b4r_main::_d6->DigitalWrite(Common_False);
 //BA.debugLineNum = 103;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann79_3;
 //BA.debugLineNum = 104;BA.debugLine="Dim openDelay As String = bc.StringFromBytes(Glob";
_opendelay = _bc->StringFromBytes(b4r_main::_globalstore->_slot2);
 //BA.debugLineNum = 105;BA.debugLine="If openDelay.Length = 0  Then";
if (_opendelay->getLength()==0) { 
 //BA.debugLineNum = 106;BA.debugLine="openDelay = RelayOpenDelay";
_opendelay = b4r_main::_relayopendelay;
 //BA.debugLineNum = 107;BA.debugLine="GlobalStore.Put(2,RelayOpenDelay)";
b4r_main::_globalstore->_put(2,(b4r_main::_relayopendelay)->GetBytes());
 };
 //BA.debugLineNum = 109;BA.debugLine="Log(\"openDelay: \",openDelay)";
B4R::Common::LogHelper(2,102,F("openDelay: "),101,_opendelay->data);
 //BA.debugLineNum = 110;BA.debugLine="CallSubPlus(\"RelayClose\", openDelay, 0)";
B4R::__c->CallSubPlus(_relayclose,(ULong)(atof(_opendelay->data)),(Byte) (0));
 //BA.debugLineNum = 111;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_writetoeeprom(B4R::B4RString* _ssid,B4R::B4RString* _password,B4R::B4RString* _opendelay,B4R::B4RString* _closeddelay){
const UInt cp = B4R::StackMemory::cp;
B4R::ByteConverter be_ann192_3;
B4R::ByteConverter* _bc = NULL;
B4R::Object be_ann193_15;
B4R::Object be_ann193_22;
B4R::Object be_ann193_29;
B4R::Object be_ann193_36;
B4R::Object* be_ann193_37e1[4];
B4R::Array be_ann193_37e2;
B4R::Array* _listofobjectstostore = NULL;
Byte be_ann194_4e1[0];
B4R::Array be_ann194_4e2;
B4R::Array* _bytedatatostore = NULL;
B4R::ByteConverter be_ann195_3;
B4R::B4RSerializator be_ann196_3;
B4R::B4RSerializator* _serializator = NULL;
B4R::B4REEPROM be_ann197_3;
B4R::B4REEPROM* _eeprom = NULL;
Int be_ann200_15e1[1];
B4R::Array be_ann200_15e2;
 //BA.debugLineNum = 228;BA.debugLine="Sub WriteToEEPROM(SSID As String, Password As Stri";
 //BA.debugLineNum = 229;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann192_3;
 //BA.debugLineNum = 230;BA.debugLine="Dim ListOfObjectsToStore() As Object = Array(bc.S";
_listofobjectstostore = be_ann193_37e2.create(be_ann193_37e1,4,100,be_ann193_15.wrapPointer(_bc->StringToBytes(_ssid)),be_ann193_22.wrapPointer(_bc->StringToBytes(_password)),be_ann193_29.wrapPointer(_bc->StringToBytes(_opendelay)),be_ann193_36.wrapPointer(_bc->StringToBytes(_closeddelay)));
 //BA.debugLineNum = 231;BA.debugLine="Dim ByteDataToStore() As Byte";
_bytedatatostore =be_ann194_4e2.wrap(be_ann194_4e1,0);
 //BA.debugLineNum = 232;BA.debugLine="Dim bc As ByteConverter";
_bc = &be_ann195_3;
 //BA.debugLineNum = 233;BA.debugLine="Dim serializator As B4RSerializator";
_serializator = &be_ann196_3;
 //BA.debugLineNum = 234;BA.debugLine="Dim eeprom As EEPROM";
_eeprom = &be_ann197_3;
 //BA.debugLineNum = 237;BA.debugLine="ByteDataToStore = serializator.ConvertArrayToByte";
_bytedatatostore = _serializator->ConvertArrayToBytes(_listofobjectstostore);
 //BA.debugLineNum = 239;BA.debugLine="Log(\"Writing settings into the EEPROM\")";
B4R::Common::LogHelper(1,102,F("Writing settings into the EEPROM"));
 //BA.debugLineNum = 242;BA.debugLine="eeprom.WriteBytes(bc.IntsToBytes(Array As Int(Byt";
_eeprom->WriteBytes(ByteConverter_IntsToBytes(be_ann200_15e2.create(be_ann200_15e1,1,3,_bytedatatostore->length)),(UInt) (700));
 //BA.debugLineNum = 245;BA.debugLine="eeprom.WriteBytes(ByteDataToStore, 702)";
_eeprom->WriteBytes(_bytedatatostore,(UInt) (702));
 //BA.debugLineNum = 246;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
