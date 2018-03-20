
#ifndef b4r_main_h
#define b4r_main_h
class b4r_globalstore;
class b4r_wifiserver;

class b4r_main {
public:

static void initializeProcessGlobals();
static void _appstart();
static void _cleareeprom();
static void _connecttonetwork();
static void _connecttowifi();
static Byte _getstoreddatalength();
static void _mqtt_connect(Byte _unused);
static void _mqtt_disconnected();
static void _mqtt_messagearrived(B4R::B4RString* _topic,B4R::Array* _payload);
static void _mqttchangesetting(B4R::Array* _message);
static void _process_globals();
static B4R::Serial* _serial1;
static B4R::D1Pins* _d1pins;
static B4R::Pin* _pin16;
static B4R::Pin* _d6;
static B4R::B4RESPWiFi* _wifi;
static B4R::WiFiSocket* _wifistr;
static B4R::MqttClient* _mqtt;
static B4R::MqttConnectOptions* _mqttopt;
static B4R::B4RString* _mqttuser;
static B4R::B4RString* _mqttpassword;
static B4R::B4RString* _mqtthostname;
static Int _mqttport;
static bool _stoprelay;
static B4R::B4RESP8266* _esp;
static B4R::B4RString* _wifissid;
static B4R::B4RString* _wifipassword;
static B4R::B4RString* _relayopendelay;
static B4R::B4RString* _relaycloseddelay;
static B4R::B4REEPROM* _eeprom;
static B4R::ByteConverter* _bc;
static Byte _magic_eeprom;
static B4R::B4RSerializator* _ser;
static B4R::Array* _objectsbuffer;
static bool _iswificonnectingappstart;
static B4R::Timer* _timer1;
static B4R::Timer* _timer2;
static ULong _counter;
static b4r_globalstore* _globalstore;
static b4r_wifiserver* _wifiserver;
static void _readfromeeprom();
static void _relayclose(Byte _tag);
static void _relayopen(Byte _tag);
static void _savenetworkdetails(B4R::Array* _data);
static void _timer1_tick();
static void _timer2_tick();
static void _writetoeeprom(B4R::B4RString* _ssid,B4R::B4RString* _password,B4R::B4RString* _opendelay,B4R::B4RString* _closeddelay);
};

#endif