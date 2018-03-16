#include "B4RDefines.h"

B4R::ByteConverter* b4r_wifiserver::_bc;
B4R::AsyncStreams* b4r_wifiserver::_astream;
B4R::WiFiServerSocket* b4r_wifiserver::_server;
b4r_main* b4r_wifiserver::_main;
b4r_globalstore* b4r_wifiserver::_globalstore;
static B4R::ByteConverter be_gann1_3;
static B4R::AsyncStreams be_gann2_3;
static B4R::WiFiServerSocket be_gann3_3;


 void b4r_wifiserver::_astream_error(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 77;BA.debugLine="Private Sub AStream_Error";
 //BA.debugLineNum = 78;BA.debugLine="Log(\"Disconnected\")";
B4R::Common::LogHelper(1,102,F("Disconnected"));
 //BA.debugLineNum = 79;BA.debugLine="server.Listen";
b4r_wifiserver::_server->Listen();
 //BA.debugLineNum = 80;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_astream_newdata(B4R::Array* _buffer){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann15_4;
B4R::B4RString be_ann16_7;
B4R::B4RString be_ann17_7;
B4R::B4RString be_ann18_5;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString be_ann18_11;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
Int _i1 = 0;
Int _i2 = 0;
B4R::Array* _b1 = NULL;
B4R::B4RString be_ann21_13;
B4R::Array* _b2 = NULL;
B4R::B4RString be_ann23_13;
B4R::B4RString be_ann36_4;
B4R::B4RString be_ann36_11;
B4R::B4RString be_ann37_4;
B4R::B4RString be_ann37_11;
B4R::B4RString be_ann37_18;
B4R::B4RString be_ann38_4;
B4R::B4RString be_ann39_4;
B4R::B4RString be_ann39_14;
B4R::B4RString be_ann39_24;
B4R::B4RString be_ann42_7;
B4R::B4RString be_ann43_4;
B4R::B4RString be_ann43_11;
B4R::B4RString be_ann43_18;
B4R::B4RString be_ann45_4;
B4R::B4RString be_ann45_11;
B4R::B4RString be_ann46_4;
B4R::B4RString be_ann48_4;
B4R::B4RString be_ann51_4;
B4R::B4RString be_ann51_11;
 //BA.debugLineNum = 20;BA.debugLine="Private Sub Astream_NewData (Buffer() As Byte)";
 //BA.debugLineNum = 21;BA.debugLine="Log(\"Buffer: \",Buffer)";
B4R::Common::LogHelper(2,102,F("Buffer: "),100,be_ann15_4.wrapPointer(_buffer));
 //BA.debugLineNum = 22;BA.debugLine="If bc.IndexOf(Buffer, \"GET\") <> -1 Then";
if (b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann16_7.wrap("GET"))->GetBytes())!=-1) { 
 //BA.debugLineNum = 23;BA.debugLine="If bc.IndexOf(Buffer, \"/set\") <> -1 Then";
if (b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann17_7.wrap("/set"))->GetBytes())!=-1) { 
 //BA.debugLineNum = 25;BA.debugLine="Dim ssid = \"\", password  = \"\" As String";
_ssid = be_ann18_5.wrap("");
_password = be_ann18_11.wrap("");
 //BA.debugLineNum = 26;BA.debugLine="Dim i1 As Int = 0";
_i1 = 0;
 //BA.debugLineNum = 27;BA.debugLine="Dim i2 As Int = 0";
_i2 = 0;
 //BA.debugLineNum = 28;BA.debugLine="For Each b1() As Byte In bc.Split(Buffer, \" \")";
B4R::Iterator* group7 = b4r_wifiserver::_bc->Split(_buffer,(be_ann21_13.wrap(" "))->GetBytes());
while (group7->MoveNext()) {
_b1 = (B4R::Array*)B4R::Object::toPointer(group7->Get());
 //BA.debugLineNum = 29;BA.debugLine="If i1 = 1 Then";
if (_i1==1) { 
 //BA.debugLineNum = 30;BA.debugLine="For Each b2() As Byte In bc.Split(b1, \"/\")";
B4R::Iterator* group9 = b4r_wifiserver::_bc->Split(_b1,(be_ann23_13.wrap("/"))->GetBytes());
while (group9->MoveNext()) {
_b2 = (B4R::Array*)B4R::Object::toPointer(group9->Get());
 //BA.debugLineNum = 31;BA.debugLine="Select i2";
switch (_i2) {
case 2: {
 //BA.debugLineNum = 33;BA.debugLine="ssid = bc.StringFromBytes(b2)";
_ssid = b4r_wifiserver::_bc->StringFromBytes(_b2);
 break; }
case 3: {
 //BA.debugLineNum = 35;BA.debugLine="password = bc.StringFromBytes(b2)";
_password = b4r_wifiserver::_bc->StringFromBytes(_b2);
 break; }
}
;
 //BA.debugLineNum = 37;BA.debugLine="i2 = i2 + 1";
_i2 = (Int) (_i2+1);
 }
;
 };
 //BA.debugLineNum = 41;BA.debugLine="i1 = i1 + 1";
_i1 = (Int) (_i1+1);
 }
;
 //BA.debugLineNum = 43;BA.debugLine="Log(StackBufferUsage)";
B4R::Common::LogHelper(1,4,B4R::__c->StackBufferUsage());
 //BA.debugLineNum = 44;BA.debugLine="Astream.Write(\"HTTP/1.1 200\").Write(CRLF)";
b4r_wifiserver::_astream->Write((be_ann36_4.wrap("HTTP/1.1 200"))->GetBytes())->Write((be_ann36_11.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 45;BA.debugLine="Astream.Write(\"Content-Type: text/html\").Write(";
b4r_wifiserver::_astream->Write((be_ann37_4.wrap("Content-Type: text/html"))->GetBytes())->Write((be_ann37_11.wrap(Common_CRLF))->GetBytes())->Write((be_ann37_18.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 46;BA.debugLine="Astream.Write(\"<script>setTimeout(function(){lo";
b4r_wifiserver::_astream->Write((be_ann38_4.wrap("<script>setTimeout(function(){location.href=\"http://192.168.4.1\"} , 20000);</script>"))->GetBytes());
 //BA.debugLineNum = 47;BA.debugLine="Astream.Write(\"WiFi set to: \").Write(ssid).Writ";
b4r_wifiserver::_astream->Write((be_ann39_4.wrap("WiFi set to: "))->GetBytes())->Write((_ssid)->GetBytes())->Write((be_ann39_14.wrap(", password: "))->GetBytes())->Write((_password)->GetBytes())->Write((be_ann39_24.wrap("<br><br/>Please wait..."))->GetBytes());
 //BA.debugLineNum = 48;BA.debugLine="Main.SaveNetworkDetails(ssid, password)";
b4r_wifiserver::_main->_savenetworkdetails(_ssid,_password);
 //BA.debugLineNum = 49;BA.debugLine="CallSubPlus(\"ConnectWifi\", 500, 0)";
B4R::__c->CallSubPlus(_connectwifi,(ULong) (500),(Byte) (0));
 }else if(b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann42_7.wrap(" / "))->GetBytes())!=-1) { 
 //BA.debugLineNum = 51;BA.debugLine="Astream.Write(\"HTTP/1.1 200\").Write(CRLF).Write";
b4r_wifiserver::_astream->Write((be_ann43_4.wrap("HTTP/1.1 200"))->GetBytes())->Write((be_ann43_11.wrap(Common_CRLF))->GetBytes())->Write((be_ann43_18.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 52;BA.debugLine="If Main.WiFi.IsConnected Then";
if (b4r_wifiserver::_main->_wifi->getIsConnected()) { 
 //BA.debugLineNum = 53;BA.debugLine="Astream.Write(\"Connected to network.\").Write(C";
b4r_wifiserver::_astream->Write((be_ann45_4.wrap("Connected to network."))->GetBytes())->Write((be_ann45_11.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 54;BA.debugLine="Astream.Write(\"ESP8266 IP address: \").Write(Ma";
b4r_wifiserver::_astream->Write((be_ann46_4.wrap("ESP8266 IP address: "))->GetBytes())->Write((b4r_wifiserver::_main->_wifi->getLocalIp())->GetBytes());
 }else {
 //BA.debugLineNum = 56;BA.debugLine="Astream.Write(\"Not connected!\")";
b4r_wifiserver::_astream->Write((be_ann48_4.wrap("Not connected!"))->GetBytes());
 };
 }else {
 //BA.debugLineNum = 59;BA.debugLine="Astream.Write(\"HTTP/1.1 404\").Write(CRLF)";
b4r_wifiserver::_astream->Write((be_ann51_4.wrap("HTTP/1.1 404"))->GetBytes())->Write((be_ann51_11.wrap(Common_CRLF))->GetBytes());
 };
 //BA.debugLineNum = 61;BA.debugLine="CallSubPlus(\"CloseConnection\", 200, 0)";
B4R::__c->CallSubPlus(_closeconnection,(ULong) (200),(Byte) (0));
 };
 //BA.debugLineNum = 63;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_closeconnection(Byte _u){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 69;BA.debugLine="Private Sub CloseConnection(u As Byte)";
 //BA.debugLineNum = 70;BA.debugLine="Log(\"close connection\")";
B4R::Common::LogHelper(1,102,F("close connection"));
 //BA.debugLineNum = 71;BA.debugLine="If server.Socket.Connected Then";
if (b4r_wifiserver::_server->getSocket()->getConnected()) { 
 //BA.debugLineNum = 72;BA.debugLine="server.Socket.Stream.Flush";
b4r_wifiserver::_server->getSocket()->getStream()->Flush();
 //BA.debugLineNum = 73;BA.debugLine="server.Socket.Close";
b4r_wifiserver::_server->getSocket()->Close();
 };
 //BA.debugLineNum = 75;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_connectwifi(Byte _u){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 65;BA.debugLine="Private Sub ConnectWifi(u As Byte)";
 //BA.debugLineNum = 66;BA.debugLine="Main.ConnectToNetwork";
b4r_wifiserver::_main->_connecttonetwork();
 //BA.debugLineNum = 67;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_process_globals(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 3;BA.debugLine="Sub Process_Globals";
 //BA.debugLineNum = 4;BA.debugLine="Private bc As ByteConverter";
b4r_wifiserver::_bc = &be_gann1_3;
 //BA.debugLineNum = 5;BA.debugLine="Private Astream As AsyncStreams";
b4r_wifiserver::_astream = &be_gann2_3;
 //BA.debugLineNum = 6;BA.debugLine="Private server As WiFiServerSocket";
b4r_wifiserver::_server = &be_gann3_3;
 //BA.debugLineNum = 7;BA.debugLine="End Sub";
}
B4R::Array* b4r_wifiserver::_replacestring(B4R::Array* _original,B4R::Array* _searchfor,B4R::Array* _replacewith){
const UInt cp = B4R::StackMemory::cp;
B4R::ByteConverter be_ann71_3;
B4R::ByteConverter* _bc2 = NULL;
Int _c = 0;
Int _i = 0;
B4R::Array be_ann81_18e2;
B4R::Array* _result = NULL;
Int _previndex = 0;
Int _targetindex = 0;
 //BA.debugLineNum = 82;BA.debugLine="Public Sub ReplaceString(Original() As Byte, Searc";
 //BA.debugLineNum = 84;BA.debugLine="Dim bc2 As ByteConverter";
_bc2 = &be_ann71_3;
 //BA.debugLineNum = 85;BA.debugLine="Dim c As Int = 0";
_c = 0;
 //BA.debugLineNum = 86;BA.debugLine="Dim i As Int";
_i = 0;
 //BA.debugLineNum = 87;BA.debugLine="If SearchFor.Length <> ReplaceWith.Length Then";
if (_searchfor->length!=_replacewith->length) { 
 //BA.debugLineNum = 88;BA.debugLine="i = bc2.IndexOf(Original, SearchFor)";
_i = _bc2->IndexOf(_original,_searchfor);
 //BA.debugLineNum = 89;BA.debugLine="Do While i > -1";
while (_i>-1) {
 //BA.debugLineNum = 90;BA.debugLine="c = c + 1";
_c = (Int) (_c+1);
 //BA.debugLineNum = 91;BA.debugLine="i = bc2.IndexOf2(Original, SearchFor, i + Searc";
_i = _bc2->IndexOf2(_original,_searchfor,(UInt) (_i+_searchfor->length));
 }
;
 };
 //BA.debugLineNum = 94;BA.debugLine="Dim result(Original.Length + c * (ReplaceWith.Len";
_result =be_ann81_18e2.wrapDynamic((Int) (_original->length+_c*(_replacewith->length-_searchfor->length)), sizeof(Byte));
 //BA.debugLineNum = 95;BA.debugLine="Dim prevIndex As Int = 0";
_previndex = 0;
 //BA.debugLineNum = 96;BA.debugLine="Dim targetIndex As Int = 0";
_targetindex = 0;
 //BA.debugLineNum = 97;BA.debugLine="i = bc2.IndexOf(Original, SearchFor)";
_i = _bc2->IndexOf(_original,_searchfor);
 //BA.debugLineNum = 98;BA.debugLine="Do While i > -1";
while (_i>-1) {
 //BA.debugLineNum = 99;BA.debugLine="bc2.ArrayCopy2(Original, prevIndex, result, targ";
_bc2->ArrayCopy2(_original,(UInt) (_previndex),_result,(UInt) (_targetindex),(UInt) (_i-_previndex));
 //BA.debugLineNum = 100;BA.debugLine="targetIndex = targetIndex + i - prevIndex";
_targetindex = (Int) (_targetindex+_i-_previndex);
 //BA.debugLineNum = 101;BA.debugLine="bc2.ArrayCopy2(ReplaceWith, 0, result, targetInd";
_bc2->ArrayCopy2(_replacewith,(UInt) (0),_result,(UInt) (_targetindex),(UInt) (_replacewith->length));
 //BA.debugLineNum = 102;BA.debugLine="targetIndex = targetIndex + ReplaceWith.Length";
_targetindex = (Int) (_targetindex+_replacewith->length);
 //BA.debugLineNum = 103;BA.debugLine="prevIndex = i + SearchFor.Length";
_previndex = (Int) (_i+_searchfor->length);
 //BA.debugLineNum = 104;BA.debugLine="i = bc2.IndexOf2(Original, SearchFor, prevIndex)";
_i = _bc2->IndexOf2(_original,_searchfor,(UInt) (_previndex));
 }
;
 //BA.debugLineNum = 106;BA.debugLine="If prevIndex < Original.Length Then";
if (_previndex<_original->length) { 
 //BA.debugLineNum = 107;BA.debugLine="bc2.ArrayCopy2(Original, prevIndex, result, targ";
_bc2->ArrayCopy2(_original,(UInt) (_previndex),_result,(UInt) (_targetindex),(UInt) (_original->length-_previndex));
 };
 //BA.debugLineNum = 109;BA.debugLine="Return result";
B4R::StackMemory::cp = cp;
if (true) return B4R::StackMemory::ReturnArrayOnStack(_result, sizeof(Byte));
 //BA.debugLineNum = 110;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
return NULL;
}
void b4r_wifiserver::_server_newconnection(B4R::WiFiSocket* _newsocket){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 16;BA.debugLine="Private Sub Server_NewConnection (NewSocket As WiF";
 //BA.debugLineNum = 17;BA.debugLine="Astream.Initialize(NewSocket.Stream, \"astream_New";
b4r_wifiserver::_astream->Initialize(_newsocket->getStream(),_astream_newdata,_astream_error);
 //BA.debugLineNum = 18;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_start(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann6_10;
 //BA.debugLineNum = 9;BA.debugLine="Public Sub Start";
 //BA.debugLineNum = 10;BA.debugLine="Log(\"StartAP: \", Main.WiFi.StartAccessPoint(\"Andy";
B4R::Common::LogHelper(2,102,F("StartAP: "),8,b4r_wifiserver::_main->_wifi->StartAccessPoint(be_ann6_10.wrap("AndyRelayAP")));
 //BA.debugLineNum = 11;BA.debugLine="Log(\"My AP ip: \", Main.WiFi.AccessPointIp)";
B4R::Common::LogHelper(2,102,F("My AP ip: "),101,b4r_wifiserver::_main->_wifi->getAccessPointIp()->data);
 //BA.debugLineNum = 12;BA.debugLine="server.Initialize(80, \"server_NewConnection\")";
b4r_wifiserver::_server->Initialize((UInt) (80),_server_newconnection);
 //BA.debugLineNum = 13;BA.debugLine="server.Listen";
b4r_wifiserver::_server->Listen();
 //BA.debugLineNum = 14;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
