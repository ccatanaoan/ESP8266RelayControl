#include "B4RDefines.h"

B4R::AsyncStreams* b4r_wifiserver::_astream;
B4R::WiFiServerSocket* b4r_wifiserver::_server;
b4r_main* b4r_wifiserver::_main;
b4r_globalstore* b4r_wifiserver::_globalstore;
static B4R::AsyncStreams be_gann1_3;
static B4R::WiFiServerSocket be_gann2_3;


 void b4r_wifiserver::_astream_error(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 32;BA.debugLine="Private Sub AStream_Error";
 //BA.debugLineNum = 33;BA.debugLine="Log(\"Disconnected\")";
B4R::Common::LogHelper(1,102,F("Disconnected"));
 //BA.debugLineNum = 34;BA.debugLine="server.Socket.Close";
b4r_wifiserver::_server->getSocket()->Close();
 //BA.debugLineNum = 35;BA.debugLine="server.Listen";
b4r_wifiserver::_server->Listen();
 //BA.debugLineNum = 36;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_astream_newdata(B4R::Array* _buffer){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 27;BA.debugLine="Private Sub Astream_NewData (Buffer() As Byte)";
 //BA.debugLineNum = 28;BA.debugLine="Main.SaveNetworkDetails(Buffer)";
b4r_wifiserver::_main->_savenetworkdetails(_buffer);
 //BA.debugLineNum = 30;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_process_globals(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 2;BA.debugLine="Sub Process_Globals";
 //BA.debugLineNum = 3;BA.debugLine="Private Astream As AsyncStreams";
b4r_wifiserver::_astream = &be_gann1_3;
 //BA.debugLineNum = 4;BA.debugLine="Private server As WiFiServerSocket";
b4r_wifiserver::_server = &be_gann2_3;
 //BA.debugLineNum = 5;BA.debugLine="End Sub";
}
void b4r_wifiserver::_server_newconnection(B4R::WiFiSocket* _newsocket){
const UInt cp = B4R::StackMemory::cp;
Byte _storedlength = 0;
Byte be_ann16_9e1[1];
B4R::Array be_ann16_9e2;
Byte be_ann19_9e1[1];
B4R::Array be_ann19_9e2;
 //BA.debugLineNum = 15;BA.debugLine="Private Sub Server_NewConnection (NewSocket As WiF";
 //BA.debugLineNum = 16;BA.debugLine="Log(\"New connection\")";
B4R::Common::LogHelper(1,102,F("New connection"));
 //BA.debugLineNum = 17;BA.debugLine="Astream.InitializePrefix(NewSocket.Stream, False,";
b4r_wifiserver::_astream->InitializePrefix(_newsocket->getStream(),Common_False,_astream_newdata,_astream_error);
 //BA.debugLineNum = 18;BA.debugLine="Dim StoredLength As Byte = Main.GetStoredDataLeng";
_storedlength = b4r_wifiserver::_main->_getstoreddatalength();
 //BA.debugLineNum = 19;BA.debugLine="If StoredLength > 0 Then";
if (_storedlength>0) { 
 //BA.debugLineNum = 20;BA.debugLine="Astream.Write(Array As Byte(1))";
b4r_wifiserver::_astream->Write(be_ann16_9e2.create(be_ann16_9e1,1,1,(Byte) (1)));
 //BA.debugLineNum = 21;BA.debugLine="Astream.Write(Main.eeprom.ReadBytes(2, StoredLen";
b4r_wifiserver::_astream->Write(b4r_wifiserver::_main->_eeprom->ReadBytes((UInt) (2),(UInt) (_storedlength)));
 }else {
 //BA.debugLineNum = 23;BA.debugLine="Astream.Write(Array As Byte(0))";
b4r_wifiserver::_astream->Write(be_ann19_9e2.create(be_ann19_9e1,1,1,(Byte) (0)));
 };
 //BA.debugLineNum = 25;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_start(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann5_10;
 //BA.debugLineNum = 7;BA.debugLine="Public Sub Start";
 //BA.debugLineNum = 8;BA.debugLine="Log(\"StartAP: \", Main.WiFi.StartAccessPoint(\"Andy";
B4R::Common::LogHelper(2,102,F("StartAP: "),8,b4r_wifiserver::_main->_wifi->StartAccessPoint(be_ann5_10.wrap("AndyRelayAccessPoint")));
 //BA.debugLineNum = 9;BA.debugLine="Log(\"My AP ip: \", Main.WiFi.AccessPointIp)";
B4R::Common::LogHelper(2,102,F("My AP ip: "),101,b4r_wifiserver::_main->_wifi->getAccessPointIp()->data);
 //BA.debugLineNum = 10;BA.debugLine="Log(\"My local ip: \", Main.WiFi.LocalIp)";
B4R::Common::LogHelper(2,102,F("My local ip: "),101,b4r_wifiserver::_main->_wifi->getLocalIp()->data);
 //BA.debugLineNum = 11;BA.debugLine="server.Initialize(51042, \"server_NewConnection\")";
b4r_wifiserver::_server->Initialize((UInt) (51042),_server_newconnection);
 //BA.debugLineNum = 12;BA.debugLine="server.Listen";
b4r_wifiserver::_server->Listen();
 //BA.debugLineNum = 13;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
