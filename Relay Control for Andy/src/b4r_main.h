
#ifndef b4r_main_h
#define b4r_main_h

class b4r_main {
public:

static void initializeProcessGlobals();
static void _appstart();
static void _process_globals();
static B4R::Serial* _serial1;
static B4R::D1Pins* _d1pins;
static B4R::Pin* _pin16;
static B4R::Pin* _d6;
static B4R::Pin* _d3;
static B4R::B4RESPWiFi* _wifi;
static B4R::B4RESP8266* _esp;
static B4R::B4RString* _relayopenhydroponicdelay;
static B4R::B4RString* _relayclosehydroponicdelay;
static B4R::B4RString* _relayopengrowlightdelay;
static B4R::B4RString* _relayclosegrowlightdelay;
static B4R::B4REEPROM* _eeprom;
static void _relayclosegrowlight(Byte _tag);
static void _relayclosehydroponic(Byte _tag);
static void _relayopengrowlight(Byte _tag);
static void _relayopenhydroponic(Byte _tag);
};

#endif