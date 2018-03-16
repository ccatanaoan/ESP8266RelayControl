
#ifndef b4r_globalstore_h
#define b4r_globalstore_h
class b4r_main;
class b4r_wifiserver;

class b4r_globalstore {
public:

static void _process_globals();
static B4R::Array* _globalbuffer;
static B4R::ByteConverter* _bc;
static UInt _mmsrcoffset;
static UInt _mmdestoffset;
static UInt _mmcount;
static B4R::Array* _slot0;
static B4R::Array* _slot1;
static B4R::Array* _slot2;
static B4R::Array* _slot3;
static B4R::Array* _slot4;
static B4R::Array* _slots;
static B4R::Array* _lengths;
static b4r_main* _main;
static b4r_wifiserver* _wifiserver;
static void _put(Int _slot,B4R::Array* _value);
};

#endif