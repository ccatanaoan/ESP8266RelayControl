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
 //BA.debugLineNum = 94;BA.debugLine="Private Sub AStream_Error";
 //BA.debugLineNum = 95;BA.debugLine="server.Listen";
b4r_wifiserver::_server->Listen();
 //BA.debugLineNum = 96;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_astream_newdata(B4R::Array* _buffer){
const UInt cp = B4R::StackMemory::cp;
B4R::Object be_ann14_2;
B4R::B4RString be_ann15_7;
B4R::B4RString be_ann16_7;
B4R::B4RString be_ann17_5;
B4R::B4RString* _ssid = B4R::B4RString::EMPTY;
B4R::B4RString be_ann17_11;
B4R::B4RString* _password = B4R::B4RString::EMPTY;
B4R::B4RString be_ann17_17;
B4R::B4RString* _opendelay = B4R::B4RString::EMPTY;
B4R::B4RString be_ann17_23;
B4R::B4RString* _closeddelay = B4R::B4RString::EMPTY;
Int _i1 = 0;
Int _i2 = 0;
B4R::Array* _b1 = NULL;
B4R::B4RString be_ann20_13;
B4R::Array* _b2 = NULL;
B4R::B4RString be_ann22_13;
B4R::B4RString be_ann39_4;
B4R::B4RString be_ann39_11;
B4R::B4RString be_ann44_4;
B4R::B4RString be_ann44_11;
B4R::B4RString be_ann48_4;
B4R::B4RString be_ann48_11;
B4R::B4RString be_ann49_4;
B4R::B4RString be_ann49_11;
B4R::B4RString be_ann49_18;
B4R::B4RString be_ann50_4;
B4R::B4RString be_ann51_4;
B4R::B4RString be_ann51_14;
B4R::B4RString be_ann51_24;
B4R::B4RString be_ann51_34;
B4R::B4RString be_ann51_44;
B4R::B4RString be_ann54_7;
B4R::B4RString be_ann55_4;
B4R::B4RString be_ann55_11;
B4R::B4RString be_ann55_18;
B4R::B4RString be_ann56_22;
B4R::B4RString be_ann56_33;
B4R::B4RString be_ann56_44;
B4R::B4RString* be_ann56_54e1[7];
B4R::Array be_ann56_54e2;
B4R::B4RString* _c = B4R::B4RString::EMPTY;
B4R::B4RString be_ann58_7;
B4R::B4RString be_ann59_4;
B4R::B4RString be_ann59_11;
B4R::B4RString be_ann59_18;
B4R::B4RString be_ann61_4;
B4R::B4RString be_ann61_11;
B4R::B4RString be_ann62_4;
B4R::B4RString be_ann64_4;
B4R::B4RString be_ann67_4;
B4R::B4RString be_ann67_11;
B4R::B4RString be_ann67_18;
B4R::B4RString be_ann68_4;
B4R::B4RString be_ann68_11;
 //BA.debugLineNum = 19;BA.debugLine="Private Sub Astream_NewData (Buffer() As Byte)";
 //BA.debugLineNum = 20;BA.debugLine="Log(Buffer)";
B4R::Common::LogHelper(1,100,be_ann14_2.wrapPointer(_buffer));
 //BA.debugLineNum = 21;BA.debugLine="If bc.IndexOf(Buffer, \"GET\") <> -1 Then";
if (b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann15_7.wrap("GET"))->GetBytes())!=-1) { 
 //BA.debugLineNum = 22;BA.debugLine="If bc.IndexOf(Buffer, \"/set\") <> -1 Then";
if (b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann16_7.wrap("/set"))->GetBytes())!=-1) { 
 //BA.debugLineNum = 23;BA.debugLine="Dim ssid = \"\", password  = \"\", OpenDelay = \"\",";
_ssid = be_ann17_5.wrap("");
_password = be_ann17_11.wrap("");
_opendelay = be_ann17_17.wrap("");
_closeddelay = be_ann17_23.wrap("");
 //BA.debugLineNum = 24;BA.debugLine="Dim i1 As Int = 0";
_i1 = 0;
 //BA.debugLineNum = 25;BA.debugLine="Dim i2 As Int = 0";
_i2 = 0;
 //BA.debugLineNum = 26;BA.debugLine="For Each b1() As Byte In bc.Split(Buffer, \" \")";
B4R::Iterator* group7 = b4r_wifiserver::_bc->Split(_buffer,(be_ann20_13.wrap(" "))->GetBytes());
while (group7->MoveNext()) {
_b1 = (B4R::Array*)B4R::Object::toPointer(group7->Get());
 //BA.debugLineNum = 27;BA.debugLine="If i1 = 1 Then";
if (_i1==1) { 
 //BA.debugLineNum = 28;BA.debugLine="For Each b2() As Byte In bc.Split(b1, \"/\")";
B4R::Iterator* group9 = b4r_wifiserver::_bc->Split(_b1,(be_ann22_13.wrap("/"))->GetBytes());
while (group9->MoveNext()) {
_b2 = (B4R::Array*)B4R::Object::toPointer(group9->Get());
 //BA.debugLineNum = 29;BA.debugLine="Select i2";
switch (_i2) {
case 2: {
 //BA.debugLineNum = 31;BA.debugLine="ssid = bc.StringFromBytes(b2)";
_ssid = b4r_wifiserver::_bc->StringFromBytes(_b2);
 break; }
case 3: {
 //BA.debugLineNum = 33;BA.debugLine="password = bc.StringFromBytes(b2)";
_password = b4r_wifiserver::_bc->StringFromBytes(_b2);
 break; }
case 4: {
 //BA.debugLineNum = 35;BA.debugLine="OpenDelay = bc.StringFromBytes(b2)";
_opendelay = b4r_wifiserver::_bc->StringFromBytes(_b2);
 break; }
case 5: {
 //BA.debugLineNum = 37;BA.debugLine="ClosedDelay = bc.StringFromBytes(b2)";
_closeddelay = b4r_wifiserver::_bc->StringFromBytes(_b2);
 break; }
}
;
 //BA.debugLineNum = 39;BA.debugLine="i2 = i2 + 1";
_i2 = (Int) (_i2+1);
 }
;
 };
 //BA.debugLineNum = 43;BA.debugLine="i1 = i1 + 1";
_i1 = (Int) (_i1+1);
 }
;
 //BA.debugLineNum = 47;BA.debugLine="If IsNumber(OpenDelay) = False Or OpenDelay.Len";
if (B4R::__c->IsNumber(_opendelay)==Common_False || _opendelay->getLength()==0) { 
 //BA.debugLineNum = 48;BA.debugLine="Astream.Write(\"Open delay value is invalid!\").";
b4r_wifiserver::_astream->Write((be_ann39_4.wrap("Open delay value is invalid!"))->GetBytes())->Write((be_ann39_11.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 49;BA.debugLine="CallSubPlus(\"CloseConnection\", 200, 0)";
B4R::__c->CallSubPlus(_closeconnection,(ULong) (200),(Byte) (0));
 //BA.debugLineNum = 50;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 52;BA.debugLine="If IsNumber(ClosedDelay) = False Or ClosedDelay";
if (B4R::__c->IsNumber(_closeddelay)==Common_False || _closeddelay->getLength()==0) { 
 //BA.debugLineNum = 53;BA.debugLine="Astream.Write(\"Closed delay value is invalid!\"";
b4r_wifiserver::_astream->Write((be_ann44_4.wrap("Closed delay value is invalid!"))->GetBytes())->Write((be_ann44_11.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 54;BA.debugLine="CallSubPlus(\"CloseConnection\", 200, 0)";
B4R::__c->CallSubPlus(_closeconnection,(ULong) (200),(Byte) (0));
 //BA.debugLineNum = 55;BA.debugLine="Return";
B4R::StackMemory::cp = cp;
if (true) return ;
 };
 //BA.debugLineNum = 57;BA.debugLine="Astream.Write(\"HTTP/1.1 200\").Write(CRLF)";
b4r_wifiserver::_astream->Write((be_ann48_4.wrap("HTTP/1.1 200"))->GetBytes())->Write((be_ann48_11.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 58;BA.debugLine="Astream.Write(\"Content-Type: text/html\").Write(";
b4r_wifiserver::_astream->Write((be_ann49_4.wrap("Content-Type: text/html"))->GetBytes())->Write((be_ann49_11.wrap(Common_CRLF))->GetBytes())->Write((be_ann49_18.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 59;BA.debugLine="Astream.Write(\"<script>setTimeout(function(){lo";
b4r_wifiserver::_astream->Write((be_ann50_4.wrap("<script>setTimeout(function(){location.href=\"http://192.168.4.1\"} , 20000);</script>"))->GetBytes());
 //BA.debugLineNum = 60;BA.debugLine="Astream.Write(\"WiFi set to: \").Write(ssid).Writ";
b4r_wifiserver::_astream->Write((be_ann51_4.wrap("WiFi set to: "))->GetBytes())->Write((_ssid)->GetBytes())->Write((be_ann51_14.wrap("<br>Password: "))->GetBytes())->Write((_password)->GetBytes())->Write((be_ann51_24.wrap("<br>Open Delay: "))->GetBytes())->Write((_opendelay)->GetBytes())->Write((be_ann51_34.wrap("<br>Closed Delay: "))->GetBytes())->Write((_closeddelay)->GetBytes())->Write((be_ann51_44.wrap("<br><br/>Applying the new settings. Please wait..."))->GetBytes());
 //BA.debugLineNum = 61;BA.debugLine="Main.SaveNetworkDetails(ssid, password, OpenDel";
b4r_wifiserver::_main->_savenetworkdetails(_ssid,_password,_opendelay,_closeddelay);
 //BA.debugLineNum = 62;BA.debugLine="CallSubPlus(\"ConnectWifi\", 500, 0)";
B4R::__c->CallSubPlus(_connectwifi,(ULong) (500),(Byte) (0));
 }else if(b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann54_7.wrap("/getsettings"))->GetBytes())!=-1) { 
 //BA.debugLineNum = 64;BA.debugLine="Astream.Write(\"HTTP/1.1 200\").Write(CRLF).Write";
b4r_wifiserver::_astream->Write((be_ann55_4.wrap("HTTP/1.1 200"))->GetBytes())->Write((be_ann55_11.wrap(Common_CRLF))->GetBytes())->Write((be_ann55_18.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 65;BA.debugLine="Dim c As String = JoinStrings(Array As String(b";
_c = B4R::__c->JoinStrings(be_ann56_54e2.create(be_ann56_54e1,7,100,b4r_wifiserver::_bc->StringFromBytes(b4r_wifiserver::_globalstore->_slot0),be_ann56_22.wrap(","),b4r_wifiserver::_bc->StringFromBytes(b4r_wifiserver::_globalstore->_slot1),be_ann56_33.wrap(","),b4r_wifiserver::_bc->StringFromBytes(b4r_wifiserver::_globalstore->_slot2),be_ann56_44.wrap(","),b4r_wifiserver::_bc->StringFromBytes(b4r_wifiserver::_globalstore->_slot3)));
 //BA.debugLineNum = 66;BA.debugLine="Astream.Write(c)";
b4r_wifiserver::_astream->Write((_c)->GetBytes());
 }else if(b4r_wifiserver::_bc->IndexOf(_buffer,(be_ann58_7.wrap(" / "))->GetBytes())!=-1) { 
 //BA.debugLineNum = 68;BA.debugLine="Astream.Write(\"HTTP/1.1 200\").Write(CRLF).Write";
b4r_wifiserver::_astream->Write((be_ann59_4.wrap("HTTP/1.1 200"))->GetBytes())->Write((be_ann59_11.wrap(Common_CRLF))->GetBytes())->Write((be_ann59_18.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 69;BA.debugLine="If Main.WiFi.IsConnected Then";
if (b4r_wifiserver::_main->_wifi->getIsConnected()) { 
 //BA.debugLineNum = 70;BA.debugLine="Astream.Write(\"Connected to AndyRelayAccessPoi";
b4r_wifiserver::_astream->Write((be_ann61_4.wrap("Connected to AndyRelayAccessPoint WiFi network."))->GetBytes())->Write((be_ann61_11.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 71;BA.debugLine="Astream.Write(\"<br><br/>ESP8266 IP address: \")";
b4r_wifiserver::_astream->Write((be_ann62_4.wrap("<br><br/>ESP8266 IP address: "))->GetBytes())->Write((b4r_wifiserver::_main->_wifi->getLocalIp())->GetBytes());
 }else {
 //BA.debugLineNum = 73;BA.debugLine="Astream.Write(\"Not connected to WiFi network!\"";
b4r_wifiserver::_astream->Write((be_ann64_4.wrap("Not connected to WiFi network!"))->GetBytes());
 };
 }else {
 //BA.debugLineNum = 76;BA.debugLine="Astream.Write(\"HTTP/1.1 200\").Write(CRLF).Write";
b4r_wifiserver::_astream->Write((be_ann67_4.wrap("HTTP/1.1 200"))->GetBytes())->Write((be_ann67_11.wrap(Common_CRLF))->GetBytes())->Write((be_ann67_18.wrap(Common_CRLF))->GetBytes());
 //BA.debugLineNum = 77;BA.debugLine="Astream.Write(\"Remote command unrecognized!\").W";
b4r_wifiserver::_astream->Write((be_ann68_4.wrap("Remote command unrecognized!"))->GetBytes())->Write((be_ann68_11.wrap(Common_CRLF))->GetBytes());
 };
 //BA.debugLineNum = 79;BA.debugLine="CallSubPlus(\"CloseConnection\", 200, 0)";
B4R::__c->CallSubPlus(_closeconnection,(ULong) (200),(Byte) (0));
 };
 //BA.debugLineNum = 81;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_closeconnection(Byte _u){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 87;BA.debugLine="Private Sub CloseConnection(u As Byte)";
 //BA.debugLineNum = 88;BA.debugLine="If server.Socket.Connected Then";
if (b4r_wifiserver::_server->getSocket()->getConnected()) { 
 //BA.debugLineNum = 89;BA.debugLine="server.Socket.Stream.Flush";
b4r_wifiserver::_server->getSocket()->getStream()->Flush();
 //BA.debugLineNum = 90;BA.debugLine="server.Socket.Close";
b4r_wifiserver::_server->getSocket()->Close();
 };
 //BA.debugLineNum = 92;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_connectwifi(Byte _u){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 83;BA.debugLine="Private Sub ConnectWifi(u As Byte)";
 //BA.debugLineNum = 84;BA.debugLine="Main.ConnectToNetwork";
b4r_wifiserver::_main->_connecttonetwork();
 //BA.debugLineNum = 85;BA.debugLine="End Sub";
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
B4R::ByteConverter be_ann86_3;
B4R::ByteConverter* _bc2 = NULL;
Int _c = 0;
Int _i = 0;
B4R::Array be_ann96_18e2;
B4R::Array* _result = NULL;
Int _previndex = 0;
Int _targetindex = 0;
 //BA.debugLineNum = 98;BA.debugLine="Public Sub ReplaceString(Original() As Byte, Searc";
 //BA.debugLineNum = 100;BA.debugLine="Dim bc2 As ByteConverter";
_bc2 = &be_ann86_3;
 //BA.debugLineNum = 101;BA.debugLine="Dim c As Int = 0";
_c = 0;
 //BA.debugLineNum = 102;BA.debugLine="Dim i As Int";
_i = 0;
 //BA.debugLineNum = 103;BA.debugLine="If SearchFor.Length <> ReplaceWith.Length Then";
if (_searchfor->length!=_replacewith->length) { 
 //BA.debugLineNum = 104;BA.debugLine="i = bc2.IndexOf(Original, SearchFor)";
_i = _bc2->IndexOf(_original,_searchfor);
 //BA.debugLineNum = 105;BA.debugLine="Do While i > -1";
while (_i>-1) {
 //BA.debugLineNum = 106;BA.debugLine="c = c + 1";
_c = (Int) (_c+1);
 //BA.debugLineNum = 107;BA.debugLine="i = bc2.IndexOf2(Original, SearchFor, i + Searc";
_i = _bc2->IndexOf2(_original,_searchfor,(UInt) (_i+_searchfor->length));
 }
;
 };
 //BA.debugLineNum = 110;BA.debugLine="Dim result(Original.Length + c * (ReplaceWith.Len";
_result =be_ann96_18e2.wrapDynamic((Int) (_original->length+_c*(_replacewith->length-_searchfor->length)), sizeof(Byte));
 //BA.debugLineNum = 111;BA.debugLine="Dim prevIndex As Int = 0";
_previndex = 0;
 //BA.debugLineNum = 112;BA.debugLine="Dim targetIndex As Int = 0";
_targetindex = 0;
 //BA.debugLineNum = 113;BA.debugLine="i = bc2.IndexOf(Original, SearchFor)";
_i = _bc2->IndexOf(_original,_searchfor);
 //BA.debugLineNum = 114;BA.debugLine="Do While i > -1";
while (_i>-1) {
 //BA.debugLineNum = 115;BA.debugLine="bc2.ArrayCopy2(Original, prevIndex, result, targ";
_bc2->ArrayCopy2(_original,(UInt) (_previndex),_result,(UInt) (_targetindex),(UInt) (_i-_previndex));
 //BA.debugLineNum = 116;BA.debugLine="targetIndex = targetIndex + i - prevIndex";
_targetindex = (Int) (_targetindex+_i-_previndex);
 //BA.debugLineNum = 117;BA.debugLine="bc2.ArrayCopy2(ReplaceWith, 0, result, targetInd";
_bc2->ArrayCopy2(_replacewith,(UInt) (0),_result,(UInt) (_targetindex),(UInt) (_replacewith->length));
 //BA.debugLineNum = 118;BA.debugLine="targetIndex = targetIndex + ReplaceWith.Length";
_targetindex = (Int) (_targetindex+_replacewith->length);
 //BA.debugLineNum = 119;BA.debugLine="prevIndex = i + SearchFor.Length";
_previndex = (Int) (_i+_searchfor->length);
 //BA.debugLineNum = 120;BA.debugLine="i = bc2.IndexOf2(Original, SearchFor, prevIndex)";
_i = _bc2->IndexOf2(_original,_searchfor,(UInt) (_previndex));
 }
;
 //BA.debugLineNum = 122;BA.debugLine="If prevIndex < Original.Length Then";
if (_previndex<_original->length) { 
 //BA.debugLineNum = 123;BA.debugLine="bc2.ArrayCopy2(Original, prevIndex, result, targ";
_bc2->ArrayCopy2(_original,(UInt) (_previndex),_result,(UInt) (_targetindex),(UInt) (_original->length-_previndex));
 };
 //BA.debugLineNum = 125;BA.debugLine="Return result";
B4R::StackMemory::cp = cp;
if (true) return B4R::StackMemory::ReturnArrayOnStack(_result, sizeof(Byte));
 //BA.debugLineNum = 126;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
return NULL;
}
void b4r_wifiserver::_server_newconnection(B4R::WiFiSocket* _newsocket){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 15;BA.debugLine="Private Sub Server_NewConnection (NewSocket As WiF";
 //BA.debugLineNum = 16;BA.debugLine="Astream.Initialize(NewSocket.Stream, \"astream_New";
b4r_wifiserver::_astream->Initialize(_newsocket->getStream(),_astream_newdata,_astream_error);
 //BA.debugLineNum = 17;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
void b4r_wifiserver::_start(){
const UInt cp = B4R::StackMemory::cp;
B4R::B4RString be_ann6_10;
 //BA.debugLineNum = 9;BA.debugLine="Public Sub Start";
 //BA.debugLineNum = 10;BA.debugLine="Log(\"Start AP: \", Main.WiFi.StartAccessPoint(\"And";
B4R::Common::LogHelper(4,102,F("Start AP: "),8,b4r_wifiserver::_main->_wifi->StartAccessPoint(be_ann6_10.wrap("AndyRelayAccessPoint")),102,F(" IP: "),101,b4r_wifiserver::_main->_wifi->getAccessPointIp()->data);
 //BA.debugLineNum = 11;BA.debugLine="server.Initialize(80, \"server_NewConnection\")";
b4r_wifiserver::_server->Initialize((UInt) (80),_server_newconnection);
 //BA.debugLineNum = 12;BA.debugLine="server.Listen";
b4r_wifiserver::_server->Listen();
 //BA.debugLineNum = 13;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
