
#ifndef b4r_wifiserver_h
#define b4r_wifiserver_h
class b4r_main;
class b4r_globalstore;

class b4r_wifiserver {
public:

static void _astream_error();
static void _astream_newdata(B4R::Array* _buffer);
static void _process_globals();
static B4R::AsyncStreams* _astream;
static B4R::WiFiServerSocket* _server;
static b4r_main* _main;
static b4r_globalstore* _globalstore;
static void _server_newconnection(B4R::WiFiSocket* _newsocket);
static void _start();
};

#endif