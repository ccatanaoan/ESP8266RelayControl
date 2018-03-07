
#ifndef b4r_main_h
#define b4r_main_h

class b4r_main {
public:

static void initializeProcessGlobals();
static void _appstart();
static void _process_globals();
static B4R::Serial* _serial1;
static B4R::D1Pins* _d1pins;
static B4R::Timer* _timer1;
static B4R::Pin* _pin16;
static B4R::Pin* _pin2;
static B4R::Pin* _d6;
static void _timer1_tick();
};

#endif