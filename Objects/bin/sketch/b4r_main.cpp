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
B4R::B4RSerializator* b4r_main::_ser;
B4R::Array* b4r_main::_objectsbuffer;
bool b4r_main::_iswificonnectingappstart;
B4R::Timer* b4r_main::_timer1;
ULong b4r_main::_counter;
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
static B4R::B4RSerializator be_gann22_3;
static B4R::Object be_gann23_4e1[10];
static B4R::Array be_gann23_4e2;
static B4R::Object* be_gann23_4e3[10];
static B4R::Timer be_gann25_3;


 void SetSTA(B4R::Object* o) {
   WiFi.mode(WIFI_STA);
}
void b4r_main::_appstart(){
const UInt cp = B4R::StackMemory::cp;
Int _attempts = 0;
 //BA.debugLineNum = 39;BA.debugLine="Private Sub AppStart";
 //BA.debugLineNum = 40;BA.debugLine="Serial1.Initialize(115200)";
b4r_main::_serial1->Initialize((ULong) (115200));
 //BA.debugLineNum = 41;BA.debugLine="Delay(3000)";
Common_Delay((ULong) (3000));
 //BA.debugLineNum = 42;BA.debugLine="Log(\"AppStart\")";
B4R::Common::LogHelper(1,102,F("AppStart"));
 //BA.debugLineNum = 47;BA.debugLine="d6.Initialize(d1pins.D6, d6.MODE_OUTPUT)";
b4r_main::_d6->Initialize(b4r_main::_d1pins->D6,Pin_MODE_OUTPUT);
 //BA.debugLineNum = 48;BA.debugLine="pin16.Initialize(16, pin16.MODE_OUTPUT)";
b4r_main::_pin16->Initialize((Byte) (16),Pin_MODE_OUTPUT);
 //BA.debugLineNum = 49;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 52;BA.debugLine="ReadFromEEPROM";
_readfromeeprom();
 //BA.debugLineNum = 54;BA.debugLine="IsWiFIConnectingAppStart = True";
b4r_main::_iswificonnectingappstart = Common_True;
 //BA.debugLineNum = 56;BA.debugLine="Log(\"Stopping access point\")";
B4R::Common::LogHelper(1,102,F("Stopping access point"));
 //BA.debugLineNum = 57;BA.debugLine="RunNative(\"SetSTA\", Null)";
Common_RunNative(SetSTA,Common_Null);
 //BA.debugLineNum = 60;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 //BA.debugLineNum = 62;BA.debugLine="Dim attempts As Int = 0";
_attempts = 0;
 //BA.debugLineNum = 63;BA.debugLine="Do Until attempts = 3";
while (!(_attempts==3)) {
 //BA.debugLineNum = 64;BA.debugLine="ConnectToWifi";
_connecttowifi();
 //BA.debugLineNum = 65;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 66;BA.debugLine="Timer1.Enabled = False";
b4r_main::_timer1->setEnabled(Common_False);
 //BA.debugLineNum = 67;BA.debugLine="IsWiFIConnectingAppStart = False";
b4r_main::_iswificonnectingappstart = Common_False;
 //BA.debugLineNum = 68;BA.debugLine="Exit";
if (true) break;
 };
 //BA.debugLineNum = 70;BA.debugLine="attempts = attempts + 1";
_attempts = (Int) (_attempts+1);
 }
;
 //BA.debugLineNum = 72;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 73;BA.debugLine="Timer1.Enabled = False";
b4r_main::_timer1->setEnabled(Common_False);
 //BA.debugLineNum = 74;BA.debugLine="IsWiFIConnectingAppStart = False";
b4r_main::_iswificonnectingappstart = Common_False;
 }else {
 //BA.debugLineNum = 76;BA.debugLine="Log(\"Starting as an access point.\")";
B4R::Common::LogHelper(1,102,F("Starting as an access point."));
 //BA.debugLineNum = 77;BA.debugLine="Timer1.Initialize(\"Timer1_Tick\", 1000) '1000ms =";
b4r_main::_timer1->Initialize(_timer1_tick,(ULong) (1000));
 //BA.debugLineNum = 78;BA.debugLine="Timer1.Enabled = True";
b4r_main::_timer1->setEnabled(Common_True);
 //BA.debugLineNum = 79;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 };
 //BA.debugLineNum = 81;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_cleareeprom(){
const UInt cp = B4R::StackMemory::cp;
UInt _i = 0;
Byte be_ann228_9e1[1];
B4R::Array be_ann228_9e2;
 //BA.debugLineNum = 269;BA.debugLine="Sub ClearEEPROM 'ignore";
 //BA.debugLineNum = 270;BA.debugLine="Dim i As UInt";
_i = 0;
 //BA.debugLineNum = 272;BA.debugLine="Log(\"Size: \", eeprom.Size, \" bytes\")";
B4R::Common::LogHelper(3,102,F("Size: "),4,b4r_main::_eeprom->getSize(),102,F(" bytes"));
 //BA.debugLineNum = 273;BA.debugLine="For i = 0 To eeprom.Size";
{
const int step3 = 1;
const int limit3 = b4r_main::_eeprom->getSize();
_i = (UInt) (0) ;
for (;(step3 > 0 && _i <= limit3) || (step3 < 0 && _i >= limit3) ;_i = ((UInt)(0 + _i + step3))  ) {
 //BA.debugLineNum = 274;BA.debugLine="eeprom.WriteBytes(Array As Byte(0), i)";
b4r_main::_eeprom->WriteBytes(be_ann228_9e2.create(be_ann228_9e1,1,1,(Byte) (0)),_i);
 //BA.debugLineNum = 275;BA.debugLine="Log(i)";
B4R::Common::LogHelper(1,4,_i);
 }
};
 //BA.debugLineNum = 277;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_connecttonetwork(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 285;BA.debugLine="Public Sub ConnectToNetwork";
 //BA.debugLineNum = 291;BA.debugLine="Log(\"Restarting controller\")";
B4R::Common::LogHelper(1,102,F("Restarting controller"));
 //BA.debugLineNum = 292;BA.debugLine="ESP.Restart";
b4r_main::_esp->Restart();
 //BA.debugLineNum = 293;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_connecttowifi(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
B4R::B4RString* _clientid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 180;BA.debugLine="Sub ConnectToWifi";
 //BA.debugLineNum = 181;BA.debugLine="Dim SSID As String";
_ssid = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 182;BA.debugLine="Dim password As String";
_password = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 184;BA.debugLine="SSID = bc.StringFromBytes(GlobalStore.Slot0)";
_ssid = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot0);
 //BA.debugLineNum = 185;BA.debugLine="If SSID.Length = 0 Then";
if (_ssid->getLength()==0) { 
 //BA.debugLineNum = 186;BA.debugLine="SSID = WiFiSSID";
_ssid = b4r_main::_wifissid;
 //BA.debugLineNum = 187;BA.debugLine="GlobalStore.Put(0,SSID)";
b4r_main::_globalstore->_put(0,(_ssid)->GetBytes());
 //BA.debugLineNum = 188;BA.debugLine="WriteToEEPROM(bc.StringFromBytes(GlobalStore.Slo";
_writetoeeprom(b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot0),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot1),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3));
 };
 //BA.debugLineNum = 191;BA.debugLine="password = bc.StringFromBytes(GlobalStore.Slot1)";
_password = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot1);
 //BA.debugLineNum = 192;BA.debugLine="If password.Length = 0 Then";
if (_password->getLength()==0) { 
 //BA.debugLineNum = 193;BA.debugLine="password = WiFiPassword";
_password = b4r_main::_wifipassword;
 //BA.debugLineNum = 194;BA.debugLine="GlobalStore.Put(1,password)";
b4r_main::_globalstore->_put(1,(_password)->GetBytes());
 //BA.debugLineNum = 195;BA.debugLine="WriteToEEPROM(bc.StringFromBytes(GlobalStore.Slo";
_writetoeeprom(b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot0),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot1),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3));
 };
 //BA.debugLineNum = 198;BA.debugLine="WiFi.Connect2(SSID, password)";
b4r_main::_wifi->Connect2(_ssid,_password);
 //BA.debugLineNum = 200;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 202;BA.debugLine="Log(\"Stopping access point\")";
B4R::Common::LogHelper(1,102,F("Stopping access point"));
 //BA.debugLineNum = 203;BA.debugLine="Timer1.Enabled = False";
b4r_main::_timer1->setEnabled(Common_False);
 //BA.debugLineNum = 204;BA.debugLine="RunNative(\"SetSTA\", Null)";
Common_RunNative(SetSTA,Common_Null);
 //BA.debugLineNum = 205;BA.debugLine="counter = 0";
b4r_main::_counter = (ULong) (0);
 //BA.debugLineNum = 206;BA.debugLine="Log(\"Connected to WiFi = \",SSID,\", Local IP = \",";
B4R::Common::LogHelper(6,102,F("Connected to WiFi = "),101,_ssid->data,102,F(", Local IP = "),101,b4r_main::_wifi->getLocalIp()->data,102,F(", Password = "),101,_password->data);
 //BA.debugLineNum = 208;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'crea";
_clientid = B4R::B4RString::fromNumber((Long)(Common_Rnd((Long) (0),(Long) (999999999))));
 //BA.debugLineNum = 209;BA.debugLine="MQTT.Initialize2(WiFiStr.stream, MQTTHostName, M";
b4r_main::_mqtt->Initialize2(b4r_main::_wifistr->getStream(),b4r_main::_mqtthostname,(UInt) (b4r_main::_mqttport),_clientid,_mqtt_messagearrived,_mqtt_disconnected);
 //BA.debugLineNum = 210;BA.debugLine="MQTTOpt.Initialize(MQTTUser, MQTTPassword)";
b4r_main::_mqttopt->Initialize(b4r_main::_mqttuser,b4r_main::_mqttpassword);
 //BA.debugLineNum = 211;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 }else {
 //BA.debugLineNum = 213;BA.debugLine="Log(\"Failed to connect to \",SSID, \" WiFi\")";
B4R::Common::LogHelper(3,102,F("Failed to connect to "),101,_ssid->data,102,F(" WiFi"));
 };
 //BA.debugLineNum = 216;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_connect(Byte _unused){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann72_4;
 //BA.debugLineNum = 83;BA.debugLine="Sub MQTT_Connect(Unused As Byte)";
 //BA.debugLineNum = 84;BA.debugLine="If WiFi.IsConnected = False And IsWiFIConnectingA";
if (b4r_main::_wifi->getIsConnected()==Common_False && b4r_main::_iswificonnectingappstart==Common_False) { 
 //BA.debugLineNum = 85;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 87;BA.debugLine="If MQTT.Connect = False Then";
if (b4r_main::_mqtt->Connect()==Common_False) { 
 //BA.debugLineNum = 88;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 89;BA.debugLine="Log(\"Connecting to broker\")";
B4R::Common::LogHelper(1,102,F("Connecting to broker"));
 //BA.debugLineNum = 90;BA.debugLine="MQTT.Connect2(MQTTOpt)";
b4r_main::_mqtt->Connect2(b4r_main::_mqttopt);
 //BA.debugLineNum = 91;BA.debugLine="CallSubPlus(\"MQTT_Connect\", 1000, 0)";
B4R::__c->CallSubPlus(_mqtt_connect,(ULong) (1000),(Byte) (0));
 }else {
 //BA.debugLineNum = 93;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 94;BA.debugLine="Log(\"Connected to broker\")";
B4R::Common::LogHelper(1,102,F("Connected to broker"));
 //BA.debugLineNum = 95;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
b4r_main::_mqtt->Subscribe(be_ann72_4.wrap("Andy"),(Byte) (0));
 };
 //BA.debugLineNum = 97;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_disconnected(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 173;BA.debugLine="Sub mqtt_Disconnected";
 //BA.debugLineNum = 174;BA.debugLine="Log(\"Disconnected from broker\")";
B4R::Common::LogHelper(1,102,F("Disconnected from broker"));
 //BA.debugLineNum = 175;BA.debugLine="pin16.DigitalWrite(True)";
b4r_main::_pin16->DigitalWrite(Common_True);
 //BA.debugLineNum = 176;BA.debugLine="MQTT.Close";
b4r_main::_mqtt->Close();
 //BA.debugLineNum = 177;BA.debugLine="MQTT_Connect(0)";
_mqtt_connect((Byte) (0));
 //BA.debugLineNum = 178;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqtt_messagearrived(B4R::B4RString* _topic,B4R::Array* _payload){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann117_8;
B4R::B4RString be_ann118_3;
B4R::B4RString be_ann119_4;
B4R::B4RString be_ann119_6;
B4R::B4RString be_ann122_3;
B4R::B4RString be_ann123_4;
B4R::B4RString be_ann123_6;
B4R::B4RString be_ann126_3;
B4R::B4RString be_ann127_4;
B4R::B4RString be_ann127_6;
B4R::B4RString be_ann129_3;
B4R::B4RString be_ann130_13;
B4R::B4RString be_ann130_24;
B4R::B4RString be_ann130_35;
B4R::B4RString be_ann130_46;
B4R::B4RString* be_ann130_56e1[8];
B4R::Array be_ann130_56e2;
B4R::B4RString* _c = B4R::B4RString::EMPTY;
B4R::B4RString be_ann131_4;
B4R::B4RString be_ann132_3;
B4R::B4RString be_ann134_4;
B4R::B4RString be_ann134_6;
B4R::B4RString be_ann136_4;
B4R::B4RString be_ann136_6;
B4R::B4RString be_ann138_4;
B4R::B4RString be_ann138_6;
B4R::B4RString be_ann141_7;
 //BA.debugLineNum = 141;BA.debugLine="Sub mqtt_MessageArrived (Topic As String, Payload(";
 //BA.debugLineNum = 142;BA.debugLine="pin16.DigitalWrite(False)";
b4r_main::_pin16->DigitalWrite(Common_False);
 //BA.debugLineNum = 143;BA.debugLine="Log(\"Message arrived. Topic=\", Topic, \" Payload=\"";
B4R::Common::LogHelper(4,102,F("Message arrived. Topic="),101,_topic->data,102,F(" Payload="),100,be_ann117_8.wrapPointer(_payload));
 //BA.debugLineNum = 144;BA.debugLine="If Payload=\"Remotely close relay\" Then";
if ((_payload)->equals((be_ann118_3.wrap("Remotely close relay"))->GetBytes())) { 
 //BA.debugLineNum = 145;BA.debugLine="MQTT.Publish(\"Andy\",\"*Closing relay by remote\")";
b4r_main::_mqtt->Publish(be_ann119_4.wrap("Andy"),(be_ann119_6.wrap("*Closing relay by remote"))->GetBytes());
 //BA.debugLineNum = 146;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 147;BA.debugLine="StopRelay = True";
b4r_main::_stoprelay = Common_True;
 }else if((_payload)->equals((be_ann122_3.wrap("Remotely open relay"))->GetBytes())) { 
 //BA.debugLineNum = 149;BA.debugLine="MQTT.Publish(\"Andy\",\"*Opening relay by remote\")";
b4r_main::_mqtt->Publish(be_ann123_4.wrap("Andy"),(be_ann123_6.wrap("*Opening relay by remote"))->GetBytes());
 //BA.debugLineNum = 150;BA.debugLine="StopRelay = False";
b4r_main::_stoprelay = Common_False;
 //BA.debugLineNum = 151;BA.debugLine="RelayOpen(0)";
_relayopen((Byte) (0));
 }else if((_payload)->equals((be_ann126_3.wrap("Restart controller"))->GetBytes())) { 
 //BA.debugLineNum = 153;BA.debugLine="MQTT.Publish(\"Andy\",\"*Restarting relay by remote";
b4r_main::_mqtt->Publish(be_ann127_4.wrap("Andy"),(be_ann127_6.wrap("*Restarting relay by remote"))->GetBytes());
 //BA.debugLineNum = 154;BA.debugLine="ESP.Restart";
b4r_main::_esp->Restart();
 }else if((_payload)->equals((be_ann129_3.wrap("Get settings"))->GetBytes())) { 
 //BA.debugLineNum = 156;BA.debugLine="Dim c As String = JoinStrings(Array As String(\"*";
_c = B4R::__c->JoinStrings(be_ann130_56e2.create(be_ann130_56e1,8,100,be_ann130_13.wrap("*Get settings: "),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot0),be_ann130_24.wrap(","),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot1),be_ann130_35.wrap(","),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2),be_ann130_46.wrap(","),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3)));
 //BA.debugLineNum = 157;BA.debugLine="MQTT.Publish(\"Andy\",c)";
b4r_main::_mqtt->Publish(be_ann131_4.wrap("Andy"),(_c)->GetBytes());
 }else if((_payload)->equals((be_ann132_3.wrap("Check relay status"))->GetBytes())) { 
 //BA.debugLineNum = 159;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 160;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is permanently clos";
b4r_main::_mqtt->Publish(be_ann134_4.wrap("Andy"),(be_ann134_6.wrap("*Relay is permanently closed"))->GetBytes());
 }else if(b4r_main::_d6->DigitalRead()) { 
 //BA.debugLineNum = 162;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is closed\")";
b4r_main::_mqtt->Publish(be_ann136_4.wrap("Andy"),(be_ann136_6.wrap("*Relay is closed"))->GetBytes());
 }else {
 //BA.debugLineNum = 164;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay is open\")";
b4r_main::_mqtt->Publish(be_ann138_4.wrap("Andy"),(be_ann138_6.wrap("*Relay is open"))->GetBytes());
 };
 }else {
 //BA.debugLineNum = 167;BA.debugLine="If bc.IndexOf(Payload,\"|\") > 0 Then";
if (b4r_main::_bc->IndexOf(_payload,(be_ann141_7.wrap("|"))->GetBytes())>0) { 
 //BA.debugLineNum = 168;BA.debugLine="MQTTChangeSetting(Payload)";
_mqttchangesetting(_payload);
 };
 };
 //BA.debugLineNum = 171;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_mqttchangesetting(B4R::Array* _message){
const UInt cp = B4R::StackMemory::cp;
Int _c = 0;
B4R::Array* _s = NULL;
B4R::B4RString be_ann265_13;
B4R::B4RString be_ann281_4;
B4R::B4RString be_ann281_6;
B4R::B4RString be_ann285_4;
B4R::B4RString be_ann285_6;
B4R::Object be_ann288_6;
B4R::Object be_ann288_12;
B4R::Object be_ann288_18;
B4R::Object be_ann288_24;
 //BA.debugLineNum = 319;BA.debugLine="Private Sub MQTTChangeSetting(message() As Byte)";
 //BA.debugLineNum = 320;BA.debugLine="Dim c As Int";
_c = 0;
 //BA.debugLineNum = 321;BA.debugLine="For Each s() As Byte In bc.Split(message, \"|\")";
B4R::Iterator* group2 = b4r_main::_bc->Split(_message,(be_ann265_13.wrap("|"))->GetBytes());
while (group2->MoveNext()) {
_s = (B4R::Array*)B4R::Object::toPointer(group2->Get());
 //BA.debugLineNum = 322;BA.debugLine="If c = 0 Then";
if (_c==0) { 
 //BA.debugLineNum = 323;BA.debugLine="GlobalStore.Put(0,s) ' SSID";
b4r_main::_globalstore->_put(0,_s);
 };
 //BA.debugLineNum = 325;BA.debugLine="If c = 1 Then";
if (_c==1) { 
 //BA.debugLineNum = 326;BA.debugLine="GlobalStore.Put(1,s) ' Password";
b4r_main::_globalstore->_put(1,_s);
 };
 //BA.debugLineNum = 328;BA.debugLine="If c = 2 Then";
if (_c==2) { 
 //BA.debugLineNum = 329;BA.debugLine="GlobalStore.Put(2,s) ' Open delay";
b4r_main::_globalstore->_put(2,_s);
 };
 //BA.debugLineNum = 331;BA.debugLine="If c = 3 Then";
if (_c==3) { 
 //BA.debugLineNum = 332;BA.debugLine="GlobalStore.Put(3,s) ' Closed delay";
b4r_main::_globalstore->_put(3,_s);
 };
 //BA.debugLineNum = 334;BA.debugLine="c = c + 1";
_c = (Int) (_c+1);
 }
;
 //BA.debugLineNum = 336;BA.debugLine="If IsNumber(bc.StringFromBytes(GlobalStore.Slot2)";
if (B4R::__c->IsNumber(b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2))==Common_False || b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2)->getLength()==0) { 
 //BA.debugLineNum = 337;BA.debugLine="MQTT.Publish(\"Andy\",\"*Open delay value is invali";
b4r_main::_mqtt->Publish(be_ann281_4.wrap("Andy"),(be_ann281_6.wrap("*Open delay value is invalid!"))->GetBytes());
 //BA.debugLineNum = 338;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 340;BA.debugLine="If IsNumber(bc.StringFromBytes(GlobalStore.Slot3)";
if (B4R::__c->IsNumber(b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3))==Common_False || b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3)->getLength()==0) { 
 //BA.debugLineNum = 341;BA.debugLine="MQTT.Publish(\"Andy\",\"*Closed delay value is inva";
b4r_main::_mqtt->Publish(be_ann285_4.wrap("Andy"),(be_ann285_6.wrap("*Closed delay value is invalid!"))->GetBytes());
 //BA.debugLineNum = 342;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 344;BA.debugLine="Log(\"MQTTChangeSetting.Slot0: \",GlobalStore.Slot0";
B4R::Common::LogHelper(8,102,F("MQTTChangeSetting.Slot0: "),100,be_ann288_6.wrapPointer(b4r_main::_globalstore->_slot0),102,F(" GlobalStore.Slot1: "),100,be_ann288_12.wrapPointer(b4r_main::_globalstore->_slot1),102,F(" GlobalStore.Slot2: "),100,be_ann288_18.wrapPointer(b4r_main::_globalstore->_slot2),102,F(" GlobalStore.Slot3: "),100,be_ann288_24.wrapPointer(b4r_main::_globalstore->_slot3));
 //BA.debugLineNum = 345;BA.debugLine="WriteToEEPROM(bc.StringFromBytes(GlobalStore.Slot";
_writetoeeprom(b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot0),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot1),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2),b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3));
 //BA.debugLineNum = 346;BA.debugLine="ConnectToNetwork";
_connecttonetwork();
 //BA.debugLineNum = 347;BA.debugLine="End Sub";
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
 //BA.debugLineNum = 32;BA.debugLine="Private ser As B4RSerializator";
b4r_main::_ser = &be_gann22_3;
 //BA.debugLineNum = 33;BA.debugLine="Private ObjectsBuffer(10) As Object";
b4r_main::_objectsbuffer =be_gann23_4e2.wrapObjects((void**)be_gann23_4e3,be_gann23_4e1,10, sizeof(B4R::Object));
 //BA.debugLineNum = 34;BA.debugLine="Private IsWiFIConnectingAppStart As Boolean";
b4r_main::_iswificonnectingappstart = false;
 //BA.debugLineNum = 35;BA.debugLine="Private Timer1 As Timer";
b4r_main::_timer1 = &be_gann25_3;
 //BA.debugLineNum = 36;BA.debugLine="Private counter As ULong";
b4r_main::_counter = 0L;
 //BA.debugLineNum = 37;BA.debugLine="End Sub";
}
void b4r_main::_readfromeeprom(){
const UInt cp = B4R::StackMemory::cp;
B4R::Array* _header = NULL;
B4R::Array* _data = NULL;
Byte be_ann195_16e1[1];
B4R::Array be_ann195_16e2;
Int _i = 0;
B4R::Array* _objects = NULL;
B4R::B4RString be_ann206_8;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString be_ann207_8;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
B4R::B4RString be_ann208_8;
B4R::B4RString* _opendelay = B4R::B4RString::EMPTY;
B4R::B4RString be_ann209_8;
B4R::B4RString* _closeddelay = B4R::B4RString::EMPTY;
B4R::Object be_ann214_8;
B4R::Object be_ann214_14;
B4R::Object be_ann214_20;
B4R::Object be_ann214_26;
 //BA.debugLineNum = 232;BA.debugLine="Sub ReadFromEEPROM";
 //BA.debugLineNum = 233;BA.debugLine="Log(\"Reading settings from the EEPROM\")";
B4R::Common::LogHelper(1,102,F("Reading settings from the EEPROM"));
 //BA.debugLineNum = 235;BA.debugLine="Dim header() As Byte = eeprom.ReadBytes(0, 2)";
_header = b4r_main::_eeprom->ReadBytes((UInt) (0),(UInt) (2));
 //BA.debugLineNum = 236;BA.debugLine="If header(0) = MAGIC_EEPROM Then";
if (((Byte*)_header->getData((UInt) (0)))[B4R::Array::staticIndex]==b4r_main::_magic_eeprom) { 
 //BA.debugLineNum = 237;BA.debugLine="Dim data() As Byte = eeprom.ReadBytes(2, header(";
_data = b4r_main::_eeprom->ReadBytes((UInt) (2),(UInt) (((Byte*)_header->getData((UInt) (1)))[B4R::Array::staticIndex]));
 //BA.debugLineNum = 238;BA.debugLine="Dim i As Int = bc.IndexOf(data, Array As Byte(0)";
_i = b4r_main::_bc->IndexOf(_data,be_ann195_16e2.create(be_ann195_16e1,1,1,(Byte) (0)));
 //BA.debugLineNum = 239;BA.debugLine="If i = -1 Then";
if (_i==-1) { 
 //BA.debugLineNum = 240;BA.debugLine="Log(\"Error parsing settings. Starting as an acc";
B4R::Common::LogHelper(1,102,F("Error parsing settings. Starting as an access point."));
 //BA.debugLineNum = 241;BA.debugLine="WiFi.Disconnect";
b4r_main::_wifi->Disconnect();
 //BA.debugLineNum = 242;BA.debugLine="IsWiFIConnectingAppStart = True";
b4r_main::_iswificonnectingappstart = Common_True;
 //BA.debugLineNum = 243;BA.debugLine="Timer1.Initialize(\"Timer1_Tick\", 1000) '1000ms";
b4r_main::_timer1->Initialize(_timer1_tick,(ULong) (1000));
 //BA.debugLineNum = 244;BA.debugLine="Timer1.Enabled = True";
b4r_main::_timer1->setEnabled(Common_True);
 //BA.debugLineNum = 245;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 //BA.debugLineNum = 246;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 248;BA.debugLine="Dim Objects() As Object = ser.ConvertBytesToArra";
_objects = b4r_main::_ser->ConvertBytesToArray(_data,b4r_main::_objectsbuffer);
 //BA.debugLineNum = 249;BA.debugLine="Dim SSID As String = Objects(0) 'ignore";
_ssid = be_ann206_8.wrap((const char*)B4R::Object::toPointer(((B4R::Object**)_objects->getData((UInt) (0)))[B4R::Array::staticIndex]));
 //BA.debugLineNum = 250;BA.debugLine="Dim Password As String = Objects(1) 'ignore";
_password = be_ann207_8.wrap((const char*)B4R::Object::toPointer(((B4R::Object**)_objects->getData((UInt) (1)))[B4R::Array::staticIndex]));
 //BA.debugLineNum = 251;BA.debugLine="Dim OpenDelay As String = Objects(2) 'ignore";
_opendelay = be_ann208_8.wrap((const char*)B4R::Object::toPointer(((B4R::Object**)_objects->getData((UInt) (2)))[B4R::Array::staticIndex]));
 //BA.debugLineNum = 252;BA.debugLine="Dim ClosedDelay As String = Objects(3) 'ignore";
_closeddelay = be_ann209_8.wrap((const char*)B4R::Object::toPointer(((B4R::Object**)_objects->getData((UInt) (3)))[B4R::Array::staticIndex]));
 //BA.debugLineNum = 253;BA.debugLine="GlobalStore.Put(0,SSID) ' SSID";
b4r_main::_globalstore->_put(0,(_ssid)->GetBytes());
 //BA.debugLineNum = 254;BA.debugLine="GlobalStore.Put(1,Password) ' Password";
b4r_main::_globalstore->_put(1,(_password)->GetBytes());
 //BA.debugLineNum = 255;BA.debugLine="GlobalStore.Put(2,OpenDelay) ' Open delay";
b4r_main::_globalstore->_put(2,(_opendelay)->GetBytes());
 //BA.debugLineNum = 256;BA.debugLine="GlobalStore.Put(3,ClosedDelay) ' Closed delay";
b4r_main::_globalstore->_put(3,(_closeddelay)->GetBytes());
 //BA.debugLineNum = 257;BA.debugLine="Log(\"ReadFromEEPROM \",\" Slot0: \",GlobalStore.Slo";
B4R::Common::LogHelper(9,102,F("ReadFromEEPROM "),102,F(" Slot0: "),100,be_ann214_8.wrapPointer(b4r_main::_globalstore->_slot0),102,F(" Slot1: "),100,be_ann214_14.wrapPointer(b4r_main::_globalstore->_slot1),102,F(" Slot2: "),100,be_ann214_20.wrapPointer(b4r_main::_globalstore->_slot2),102,F(" Slot3: "),100,be_ann214_26.wrapPointer(b4r_main::_globalstore->_slot3));
 }else {
 //BA.debugLineNum = 259;BA.debugLine="Log(\"Settings data not found. Starting as an acc";
B4R::Common::LogHelper(1,102,F("Settings data not found. Starting as an access point."));
 //BA.debugLineNum = 260;BA.debugLine="WiFi.Disconnect";
b4r_main::_wifi->Disconnect();
 //BA.debugLineNum = 261;BA.debugLine="IsWiFIConnectingAppStart = True";
b4r_main::_iswificonnectingappstart = Common_True;
 //BA.debugLineNum = 262;BA.debugLine="Timer1.Initialize(\"Timer1_Tick\", 1000) '1000ms =";
b4r_main::_timer1->Initialize(_timer1_tick,(ULong) (1000));
 //BA.debugLineNum = 263;BA.debugLine="Timer1.Enabled = True";
b4r_main::_timer1->setEnabled(Common_True);
 //BA.debugLineNum = 264;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 };
 //BA.debugLineNum = 267;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayclose(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann84_4;
B4R::B4RString be_ann84_6;
B4R::B4RString* _closeddelay = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 99;BA.debugLine="Private Sub RelayClose (tag As Byte)";
 //BA.debugLineNum = 100;BA.debugLine="If WiFi.IsConnected = False And IsWiFIConnectingA";
if (b4r_main::_wifi->getIsConnected()==Common_False && b4r_main::_iswificonnectingappstart==Common_False) { 
 //BA.debugLineNum = 101;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 103;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 104;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 106;BA.debugLine="Log(\"*Relay has been closed\")";
B4R::Common::LogHelper(1,102,F("*Relay has been closed"));
 //BA.debugLineNum = 107;BA.debugLine="If WiFi.IsConnected  Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 108;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been closed\")";
b4r_main::_mqtt->Publish(be_ann84_4.wrap("Andy"),(be_ann84_6.wrap("*Relay has been closed"))->GetBytes());
 };
 //BA.debugLineNum = 110;BA.debugLine="d6.DigitalWrite(True)";
b4r_main::_d6->DigitalWrite(Common_True);
 //BA.debugLineNum = 111;BA.debugLine="Dim closedDelay As String = bc.StringFromBytes(Gl";
_closeddelay = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot3);
 //BA.debugLineNum = 112;BA.debugLine="If closedDelay.Length = 0 Then";
if (_closeddelay->getLength()==0) { 
 //BA.debugLineNum = 113;BA.debugLine="closedDelay = RelayClosedDelay";
_closeddelay = b4r_main::_relaycloseddelay;
 //BA.debugLineNum = 114;BA.debugLine="GlobalStore.Put(3,RelayClosedDelay)";
b4r_main::_globalstore->_put(3,(b4r_main::_relaycloseddelay)->GetBytes());
 };
 //BA.debugLineNum = 116;BA.debugLine="Log(\"ClosedDelay: \",closedDelay)";
B4R::Common::LogHelper(2,102,F("ClosedDelay: "),101,_closeddelay->data);
 //BA.debugLineNum = 117;BA.debugLine="CallSubPlus(\"RelayOpen\", closedDelay, 0)";
B4R::__c->CallSubPlus(_relayopen,(ULong)(atof(_closeddelay->data)),(Byte) (0));
 //BA.debugLineNum = 118;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_relayopen(Byte _tag){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann104_4;
B4R::B4RString be_ann104_6;
B4R::B4RString* _opendelay = B4R::B4RString::EMPTY;
 //BA.debugLineNum = 120;BA.debugLine="Private Sub RelayOpen (tag As Byte)";
 //BA.debugLineNum = 121;BA.debugLine="If WiFi.IsConnected = False And IsWiFIConnectingA";
if (b4r_main::_wifi->getIsConnected()==Common_False && b4r_main::_iswificonnectingappstart==Common_False) { 
 //BA.debugLineNum = 122;BA.debugLine="ConnectToWifi";
_connecttowifi();
 };
 //BA.debugLineNum = 124;BA.debugLine="If StopRelay Then";
if (b4r_main::_stoprelay) { 
 //BA.debugLineNum = 125;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 127;BA.debugLine="Log(\"*Relay has been opened\")";
B4R::Common::LogHelper(1,102,F("*Relay has been opened"));
 //BA.debugLineNum = 128;BA.debugLine="If WiFi.IsConnected  Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 129;BA.debugLine="MQTT.Publish(\"Andy\",\"*Relay has been opened\")";
b4r_main::_mqtt->Publish(be_ann104_4.wrap("Andy"),(be_ann104_6.wrap("*Relay has been opened"))->GetBytes());
 };
 //BA.debugLineNum = 131;BA.debugLine="d6.DigitalWrite(False)";
b4r_main::_d6->DigitalWrite(Common_False);
 //BA.debugLineNum = 132;BA.debugLine="Dim openDelay As String = bc.StringFromBytes(Glob";
_opendelay = b4r_main::_bc->StringFromBytes(b4r_main::_globalstore->_slot2);
 //BA.debugLineNum = 133;BA.debugLine="If openDelay.Length = 0  Then";
if (_opendelay->getLength()==0) { 
 //BA.debugLineNum = 134;BA.debugLine="openDelay = RelayOpenDelay";
_opendelay = b4r_main::_relayopendelay;
 //BA.debugLineNum = 135;BA.debugLine="GlobalStore.Put(2,RelayOpenDelay)";
b4r_main::_globalstore->_put(2,(b4r_main::_relayopendelay)->GetBytes());
 };
 //BA.debugLineNum = 137;BA.debugLine="Log(\"openDelay: \",openDelay)";
B4R::Common::LogHelper(2,102,F("openDelay: "),101,_opendelay->data);
 //BA.debugLineNum = 138;BA.debugLine="CallSubPlus(\"RelayClose\", openDelay, 0)";
B4R::__c->CallSubPlus(_relayclose,(ULong)(atof(_opendelay->data)),(Byte) (0));
 //BA.debugLineNum = 139;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_savenetworkdetails(B4R::B4RString* _ssid,B4R::B4RString* _password,B4R::B4RString* _opendelay,B4R::B4RString* _closeddelay){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann234_12;
B4R::B4RString be_ann234_14;
 //BA.debugLineNum = 279;BA.debugLine="Public Sub SaveNetworkDetails(SSID As String, Pass";
 //BA.debugLineNum = 280;BA.debugLine="Log(\"Saving settings: \", SSID, \", \", Password, \",";
B4R::Common::LogHelper(8,102,F("Saving settings: "),101,_ssid->data,102,F(", "),101,_password->data,102,F(", "),101,_opendelay->data,102,F(", "),101,_closeddelay->data);
 //BA.debugLineNum = 281;BA.debugLine="SSID = bc.StringFromBytes(WiFiServer.ReplaceStrin";
_ssid = b4r_main::_bc->StringFromBytes(b4r_main::_wifiserver->_replacestring((_ssid)->GetBytes(),(be_ann234_12.wrap("%20"))->GetBytes(),(be_ann234_14.wrap(" "))->GetBytes()));
 //BA.debugLineNum = 282;BA.debugLine="WriteToEEPROM(SSID,Password,OpenDelay,ClosedDelay";
_writetoeeprom(_ssid,_password,_opendelay,_closeddelay);
 //BA.debugLineNum = 283;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_timer1_tick(){
const UInt cp = B4R::StackMemory::cp;
bool _currentstate = false;
bool _newstate = false;
 //BA.debugLineNum = 295;BA.debugLine="Private Sub Timer1_Tick";
 //BA.debugLineNum = 297;BA.debugLine="counter = counter + 1";
b4r_main::_counter = (ULong) (b4r_main::_counter+1);
 //BA.debugLineNum = 298;BA.debugLine="If counter >= 300 Then";
if (b4r_main::_counter>=300) { 
 //BA.debugLineNum = 299;BA.debugLine="Log(\"Stopping access point\")";
B4R::Common::LogHelper(1,102,F("Stopping access point"));
 //BA.debugLineNum = 300;BA.debugLine="RunNative(\"SetSTA\", Null)";
Common_RunNative(SetSTA,Common_Null);
 //BA.debugLineNum = 301;BA.debugLine="IsWiFIConnectingAppStart = True";
b4r_main::_iswificonnectingappstart = Common_True;
 //BA.debugLineNum = 302;BA.debugLine="ConnectToWifi";
_connecttowifi();
 //BA.debugLineNum = 303;BA.debugLine="If WiFi.IsConnected Then";
if (b4r_main::_wifi->getIsConnected()) { 
 //BA.debugLineNum = 304;BA.debugLine="Timer1.Enabled = False";
b4r_main::_timer1->setEnabled(Common_False);
 //BA.debugLineNum = 305;BA.debugLine="IsWiFIConnectingAppStart = False";
b4r_main::_iswificonnectingappstart = Common_False;
 }else {
 //BA.debugLineNum = 307;BA.debugLine="Log(\"Starting as an access point.\")";
B4R::Common::LogHelper(1,102,F("Starting as an access point."));
 //BA.debugLineNum = 308;BA.debugLine="Timer1.Initialize(\"Timer1_Tick\", 1000) '1000ms";
b4r_main::_timer1->Initialize(_timer1_tick,(ULong) (1000));
 //BA.debugLineNum = 309;BA.debugLine="Timer1.Enabled = True";
b4r_main::_timer1->setEnabled(Common_True);
 //BA.debugLineNum = 310;BA.debugLine="WiFiServer.Start";
b4r_main::_wifiserver->_start();
 };
 //BA.debugLineNum = 312;BA.debugLine="counter = 0";
b4r_main::_counter = (ULong) (0);
 };
 //BA.debugLineNum = 314;BA.debugLine="Dim currentState As Boolean = pin16.DigitalRead";
_currentstate = b4r_main::_pin16->DigitalRead();
 //BA.debugLineNum = 315;BA.debugLine="Dim NewState As Boolean = Not(currentState)";
_newstate = Common_Not(_currentstate);
 //BA.debugLineNum = 316;BA.debugLine="pin16.DigitalWrite(NewState)";
b4r_main::_pin16->DigitalWrite(_newstate);
 //BA.debugLineNum = 317;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_main::_writetoeeprom(B4R::B4RString* _ssid,B4R::B4RString* _password,B4R::B4RString* _opendelay,B4R::B4RString* _closeddelay){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann184_10;
B4R::Object be_ann184_12;
B4R::Object be_ann184_14;
B4R::Object be_ann184_16;
B4R::Object* be_ann184_17e1[4];
B4R::Array be_ann184_17e2;
B4R::Array* _listofobjectstostore = NULL;
Byte be_ann185_4e1[0];
B4R::Array be_ann185_4e2;
B4R::Array* _bytedatatostore = NULL;
Byte be_ann187_13e1[2];
B4R::Array be_ann187_13e2;
 //BA.debugLineNum = 218;BA.debugLine="Sub WriteToEEPROM(SSID As String, Password As Stri";
 //BA.debugLineNum = 219;BA.debugLine="Log(\"Writing setiings into the EEPROM\")";
B4R::Common::LogHelper(1,102,F("Writing setiings into the EEPROM"));
 //BA.debugLineNum = 220;BA.debugLine="Dim ListOfObjectsToStore() As Object = Array(SSID";
_listofobjectstostore = be_ann184_17e2.create(be_ann184_17e1,4,100,be_ann184_10.wrapPointer(_ssid->data),be_ann184_12.wrapPointer(_password->data),be_ann184_14.wrapPointer(_opendelay->data),be_ann184_16.wrapPointer(_closeddelay->data));
 //BA.debugLineNum = 221;BA.debugLine="Dim ByteDataToStore() As Byte";
_bytedatatostore =be_ann185_4e2.wrap(be_ann185_4e1,0);
 //BA.debugLineNum = 224;BA.debugLine="ByteDataToStore = ser.ConvertArrayToBytes(ListOfO";
_bytedatatostore = b4r_main::_ser->ConvertArrayToBytes(_listofobjectstostore);
 //BA.debugLineNum = 227;BA.debugLine="eeprom.WriteBytes(Array As Byte(MAGIC_EEPROM, Byt";
b4r_main::_eeprom->WriteBytes(be_ann187_13e2.create(be_ann187_13e1,2,1,b4r_main::_magic_eeprom,(Byte) (_bytedatatostore->length)),(UInt) (0));
 //BA.debugLineNum = 229;BA.debugLine="eeprom.WriteBytes(ByteDataToStore, 2)";
b4r_main::_eeprom->WriteBytes(_bytedatatostore,(UInt) (2));
 //BA.debugLineNum = 230;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
