# 1 "C:\\Users\\Cloyd\\Desktop\\ESP826~1\\Objects\\src\\src.ino"
# 1 "C:\\Users\\Cloyd\\Desktop\\ESP826~1\\Objects\\src\\src.ino"
# 2 "C:\\Users\\Cloyd\\Desktop\\ESP826~1\\Objects\\src\\src.ino" 2

void setup() {
 b4r_main::initializeProcessGlobals();
 b4r_main::_appstart();
}

void loop() {
 while (true) {
  B4R::scheduler.loop();
 }
}
