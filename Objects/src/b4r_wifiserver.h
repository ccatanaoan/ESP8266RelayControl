
#ifndef b4r_wifiserver_h
#define b4r_wifiserver_h
class b4r_main;
class b4r_globalstore;

class b4r_wifiserver {
public:

static void _astream_error();
static void _astream_newdata(B4R::Array* _buffer);
static void _closeconnection(Byte _u);
static void _connectwifi(Byte _u);
static void _process_globals();
static B4R::ByteConverter* _bc;
static B4R::AsyncStreams* _astream;
static B4R::WiFiServerSocket* _server;
static b4r_main* _main;
static b4r_globalstore* _globalstore;
static B4R::Array* _replacestring(B4R::Array* _original,B4R::Array* _searchfor,B4R::Array* _replacewith);
static void _server_newconnection(B4R::WiFiSocket* _newsocket);
static void _start();
};

#endif