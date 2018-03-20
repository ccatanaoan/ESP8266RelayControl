package andy.home.system;


import anywheresoftware.b4a.B4AMenuItem;
import android.app.Activity;
import android.os.Bundle;
import anywheresoftware.b4a.BA;
import anywheresoftware.b4a.BALayout;
import anywheresoftware.b4a.B4AActivity;
import anywheresoftware.b4a.ObjectWrapper;
import anywheresoftware.b4a.objects.ActivityWrapper;
import java.lang.reflect.InvocationTargetException;
import anywheresoftware.b4a.B4AUncaughtException;
import anywheresoftware.b4a.debug.*;
import java.lang.ref.WeakReference;

public class settings extends android.support.v7.app.AppCompatActivity implements B4AActivity{
	public static settings mostCurrent;
	static boolean afterFirstLayout;
	static boolean isFirst = true;
    private static boolean processGlobalsRun = false;
	BALayout layout;
	public static BA processBA;
	BA activityBA;
    ActivityWrapper _activity;
    java.util.ArrayList<B4AMenuItem> menuItems;
	public static final boolean fullScreen = false;
	public static final boolean includeTitle = true;
    public static WeakReference<Activity> previousOne;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        mostCurrent = this;
		if (processBA == null) {
			processBA = new BA(this.getApplicationContext(), null, null, "andy.home.system", "andy.home.system.settings");
			processBA.loadHtSubs(this.getClass());
	        float deviceScale = getApplicationContext().getResources().getDisplayMetrics().density;
	        BALayout.setDeviceScale(deviceScale);
            
		}
		else if (previousOne != null) {
			Activity p = previousOne.get();
			if (p != null && p != this) {
                BA.LogInfo("Killing previous instance (settings).");
				p.finish();
			}
		}
        processBA.setActivityPaused(true);
        processBA.runHook("oncreate", this, null);
		if (!includeTitle) {
        	this.getWindow().requestFeature(android.view.Window.FEATURE_NO_TITLE);
        }
        if (fullScreen) {
        	getWindow().setFlags(android.view.WindowManager.LayoutParams.FLAG_FULLSCREEN,   
        			android.view.WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
		
        processBA.sharedProcessBA.activityBA = null;
		layout = new BALayout(this);
		setContentView(layout);
		afterFirstLayout = false;
        WaitForLayout wl = new WaitForLayout();
        if (anywheresoftware.b4a.objects.ServiceHelper.StarterHelper.startFromActivity(processBA, wl, false))
		    BA.handler.postDelayed(wl, 5);

	}
	static class WaitForLayout implements Runnable {
		public void run() {
			if (afterFirstLayout)
				return;
			if (mostCurrent == null)
				return;
            
			if (mostCurrent.layout.getWidth() == 0) {
				BA.handler.postDelayed(this, 5);
				return;
			}
			mostCurrent.layout.getLayoutParams().height = mostCurrent.layout.getHeight();
			mostCurrent.layout.getLayoutParams().width = mostCurrent.layout.getWidth();
			afterFirstLayout = true;
			mostCurrent.afterFirstLayout();
		}
	}
	private void afterFirstLayout() {
        if (this != mostCurrent)
			return;
		activityBA = new BA(this, layout, processBA, "andy.home.system", "andy.home.system.settings");
        
        processBA.sharedProcessBA.activityBA = new java.lang.ref.WeakReference<BA>(activityBA);
        anywheresoftware.b4a.objects.ViewWrapper.lastId = 0;
        _activity = new ActivityWrapper(activityBA, "activity");
        anywheresoftware.b4a.Msgbox.isDismissing = false;
        if (BA.isShellModeRuntimeCheck(processBA)) {
			if (isFirst)
				processBA.raiseEvent2(null, true, "SHELL", false);
			processBA.raiseEvent2(null, true, "CREATE", true, "andy.home.system.settings", processBA, activityBA, _activity, anywheresoftware.b4a.keywords.Common.Density, mostCurrent);
			_activity.reinitializeForShell(activityBA, "activity");
		}
        initializeProcessGlobals();		
        initializeGlobals();
        
        BA.LogInfo("** Activity (settings) Create, isFirst = " + isFirst + " **");
        processBA.raiseEvent2(null, true, "activity_create", false, isFirst);
		isFirst = false;
		if (this != mostCurrent)
			return;
        processBA.setActivityPaused(false);
        BA.LogInfo("** Activity (settings) Resume **");
        processBA.raiseEvent(null, "activity_resume");
        if (android.os.Build.VERSION.SDK_INT >= 11) {
			try {
				android.app.Activity.class.getMethod("invalidateOptionsMenu").invoke(this,(Object[]) null);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}
	public void addMenuItem(B4AMenuItem item) {
		if (menuItems == null)
			menuItems = new java.util.ArrayList<B4AMenuItem>();
		menuItems.add(item);
	}
	@Override
	public boolean onCreateOptionsMenu(android.view.Menu menu) {
		super.onCreateOptionsMenu(menu);
        try {
            if (processBA.subExists("activity_actionbarhomeclick")) {
                Class.forName("android.app.ActionBar").getMethod("setHomeButtonEnabled", boolean.class).invoke(
                    getClass().getMethod("getActionBar").invoke(this), true);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        if (processBA.runHook("oncreateoptionsmenu", this, new Object[] {menu}))
            return true;
		if (menuItems == null)
			return false;
		for (B4AMenuItem bmi : menuItems) {
			android.view.MenuItem mi = menu.add(bmi.title);
			if (bmi.drawable != null)
				mi.setIcon(bmi.drawable);
            if (android.os.Build.VERSION.SDK_INT >= 11) {
				try {
                    if (bmi.addToBar) {
				        android.view.MenuItem.class.getMethod("setShowAsAction", int.class).invoke(mi, 1);
                    }
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
			mi.setOnMenuItemClickListener(new B4AMenuItemsClickListener(bmi.eventName.toLowerCase(BA.cul)));
		}
        
		return true;
	}   
 @Override
 public boolean onOptionsItemSelected(android.view.MenuItem item) {
    if (item.getItemId() == 16908332) {
        processBA.raiseEvent(null, "activity_actionbarhomeclick");
        return true;
    }
    else
        return super.onOptionsItemSelected(item); 
}
@Override
 public boolean onPrepareOptionsMenu(android.view.Menu menu) {
    super.onPrepareOptionsMenu(menu);
    processBA.runHook("onprepareoptionsmenu", this, new Object[] {menu});
    return true;
    
 }
 protected void onStart() {
    super.onStart();
    processBA.runHook("onstart", this, null);
}
 protected void onStop() {
    super.onStop();
    processBA.runHook("onstop", this, null);
}
    public void onWindowFocusChanged(boolean hasFocus) {
       super.onWindowFocusChanged(hasFocus);
       if (processBA.subExists("activity_windowfocuschanged"))
           processBA.raiseEvent2(null, true, "activity_windowfocuschanged", false, hasFocus);
    }
	private class B4AMenuItemsClickListener implements android.view.MenuItem.OnMenuItemClickListener {
		private final String eventName;
		public B4AMenuItemsClickListener(String eventName) {
			this.eventName = eventName;
		}
		public boolean onMenuItemClick(android.view.MenuItem item) {
			processBA.raiseEventFromUI(item.getTitle(), eventName + "_click");
			return true;
		}
	}
    public static Class<?> getObject() {
		return settings.class;
	}
    private Boolean onKeySubExist = null;
    private Boolean onKeyUpSubExist = null;
	@Override
	public boolean onKeyDown(int keyCode, android.view.KeyEvent event) {
        if (processBA.runHook("onkeydown", this, new Object[] {keyCode, event}))
            return true;
		if (onKeySubExist == null)
			onKeySubExist = processBA.subExists("activity_keypress");
		if (onKeySubExist) {
			if (keyCode == anywheresoftware.b4a.keywords.constants.KeyCodes.KEYCODE_BACK &&
					android.os.Build.VERSION.SDK_INT >= 18) {
				HandleKeyDelayed hk = new HandleKeyDelayed();
				hk.kc = keyCode;
				BA.handler.post(hk);
				return true;
			}
			else {
				boolean res = new HandleKeyDelayed().runDirectly(keyCode);
				if (res)
					return true;
			}
		}
		return super.onKeyDown(keyCode, event);
	}
	private class HandleKeyDelayed implements Runnable {
		int kc;
		public void run() {
			runDirectly(kc);
		}
		public boolean runDirectly(int keyCode) {
			Boolean res =  (Boolean)processBA.raiseEvent2(_activity, false, "activity_keypress", false, keyCode);
			if (res == null || res == true) {
                return true;
            }
            else if (keyCode == anywheresoftware.b4a.keywords.constants.KeyCodes.KEYCODE_BACK) {
				finish();
				return true;
			}
            return false;
		}
		
	}
    @Override
	public boolean onKeyUp(int keyCode, android.view.KeyEvent event) {
        if (processBA.runHook("onkeyup", this, new Object[] {keyCode, event}))
            return true;
		if (onKeyUpSubExist == null)
			onKeyUpSubExist = processBA.subExists("activity_keyup");
		if (onKeyUpSubExist) {
			Boolean res =  (Boolean)processBA.raiseEvent2(_activity, false, "activity_keyup", false, keyCode);
			if (res == null || res == true)
				return true;
		}
		return super.onKeyUp(keyCode, event);
	}
	@Override
	public void onNewIntent(android.content.Intent intent) {
        super.onNewIntent(intent);
		this.setIntent(intent);
        processBA.runHook("onnewintent", this, new Object[] {intent});
	}
    @Override 
	public void onPause() {
		super.onPause();
        if (_activity == null)
            return;
        if (this != mostCurrent)
			return;
		anywheresoftware.b4a.Msgbox.dismiss(true);
        BA.LogInfo("** Activity (settings) Pause, UserClosed = " + activityBA.activity.isFinishing() + " **");
        if (mostCurrent != null)
            processBA.raiseEvent2(_activity, true, "activity_pause", false, activityBA.activity.isFinishing());		
        processBA.setActivityPaused(true);
        mostCurrent = null;
        if (!activityBA.activity.isFinishing())
			previousOne = new WeakReference<Activity>(this);
        anywheresoftware.b4a.Msgbox.isDismissing = false;
        processBA.runHook("onpause", this, null);
	}

	@Override
	public void onDestroy() {
        super.onDestroy();
		previousOne = null;
        processBA.runHook("ondestroy", this, null);
	}
    @Override 
	public void onResume() {
		super.onResume();
        mostCurrent = this;
        anywheresoftware.b4a.Msgbox.isDismissing = false;
        if (activityBA != null) { //will be null during activity create (which waits for AfterLayout).
        	ResumeMessage rm = new ResumeMessage(mostCurrent);
        	BA.handler.post(rm);
        }
        processBA.runHook("onresume", this, null);
	}
    private static class ResumeMessage implements Runnable {
    	private final WeakReference<Activity> activity;
    	public ResumeMessage(Activity activity) {
    		this.activity = new WeakReference<Activity>(activity);
    	}
		public void run() {
			if (mostCurrent == null || mostCurrent != activity.get())
				return;
			processBA.setActivityPaused(false);
            BA.LogInfo("** Activity (settings) Resume **");
		    processBA.raiseEvent(mostCurrent._activity, "activity_resume", (Object[])null);
		}
    }
	@Override
	protected void onActivityResult(int requestCode, int resultCode,
	      android.content.Intent data) {
		processBA.onActivityResult(requestCode, resultCode, data);
        processBA.runHook("onactivityresult", this, new Object[] {requestCode, resultCode});
	}
	private static void initializeGlobals() {
		processBA.raiseEvent2(null, true, "globals", false, (Object[])null);
	}
    public void onRequestPermissionsResult(int requestCode,
        String permissions[], int[] grantResults) {
        for (int i = 0;i < permissions.length;i++) {
            Object[] o = new Object[] {permissions[i], grantResults[i] == 0};
            processBA.raiseEventFromDifferentThread(null,null, 0, "activity_permissionresult", true, o);
        }
            
    }

public anywheresoftware.b4a.keywords.Common __c = null;
public static anywheresoftware.b4j.objects.MqttAsyncClientWrapper _mqtt = null;
public static String _mqttuser = "";
public static String _mqttpassword = "";
public static String _mqttserveruri = "";
public static anywheresoftware.b4a.agraham.byteconverter.ByteConverter _bc = null;
public static anywheresoftware.b4a.randomaccessfile.AsyncStreams _astream = null;
public static andy.home.system.settings._record _rec = null;
public static andy.home.system.b4rserializator _ser = null;
public de.amberhome.objects.appcompat.ACToolbarLightWrapper _actoolbarlight1 = null;
public de.amberhome.objects.appcompat.ACActionBar _toolbarhelper = null;
public wifi.MLwifi _wifi = null;
public anywheresoftware.b4a.objects.ButtonWrapper _btnget = null;
public anywheresoftware.b4a.objects.ButtonWrapper _btnset = null;
public anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper _txtpassword = null;
public anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper _txtssid = null;
public anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper _txtcloseddelay = null;
public anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper _txtopendelay = null;
public anywheresoftware.b4a.objects.CompoundButtonWrapper.ToggleButtonWrapper _tglconnection = null;
public anywheresoftware.b4a.samples.httputils2.httpjob _checkinternetjob = null;
public static boolean _isinternetconnected = false;
public anywheresoftware.b4a.samples.httputils2.httputils2service _httputils2service = null;
public andy.home.system.main _main = null;
public andy.home.system.starter _starter = null;

public static void initializeProcessGlobals() {
             try {
                Class.forName(BA.applicationContext.getPackageName() + ".main").getMethod("initializeProcessGlobals").invoke(null, null);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
}
public static class _record{
public boolean IsInitialized;
public String SSID;
public String Password;
public String OpenDelay;
public String ClosedDelay;
public void Initialize() {
IsInitialized = true;
SSID = "";
Password = "";
OpenDelay = "";
ClosedDelay = "";
}
@Override
		public String toString() {
			return BA.TypeToString(this, false);
		}}
public static String  _activity_create(boolean _firsttime) throws Exception{
anywheresoftware.b4a.objects.CSBuilder _cs = null;
 //BA.debugLineNum = 38;BA.debugLine="Sub Activity_Create(FirstTime As Boolean)";
 //BA.debugLineNum = 39;BA.debugLine="If FirstTime Then";
if (_firsttime) { 
 //BA.debugLineNum = 41;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 };
 //BA.debugLineNum = 43;BA.debugLine="Activity.LoadLayout(\"Settings\")";
mostCurrent._activity.LoadLayout("Settings",mostCurrent.activityBA);
 //BA.debugLineNum = 44;BA.debugLine="ToolbarHelper.Initialize";
mostCurrent._toolbarhelper.Initialize(mostCurrent.activityBA);
 //BA.debugLineNum = 45;BA.debugLine="Dim cs As CSBuilder";
_cs = new anywheresoftware.b4a.objects.CSBuilder();
 //BA.debugLineNum = 46;BA.debugLine="ToolbarHelper.Title= cs.Initialize.Size(20).Appen";
mostCurrent._toolbarhelper.setTitle(BA.ObjectToCharSequence(_cs.Initialize().Size((int) (20)).Append(BA.ObjectToCharSequence("Settings")).PopAll().getObject()));
 //BA.debugLineNum = 47;BA.debugLine="ToolbarHelper.Subtitle=\"\"";
mostCurrent._toolbarhelper.setSubtitle(BA.ObjectToCharSequence(""));
 //BA.debugLineNum = 48;BA.debugLine="ToolbarHelper.ShowUpIndicator = False 'set to tru";
mostCurrent._toolbarhelper.setShowUpIndicator(anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 49;BA.debugLine="ACToolBarLight1.InitMenuListener";
mostCurrent._actoolbarlight1.InitMenuListener();
 //BA.debugLineNum = 51;BA.debugLine="txtOpenDelay.EditText.InputType = txtOpenDelay.Ed";
mostCurrent._txtopendelay.getEditText().setInputType(mostCurrent._txtopendelay.getEditText().INPUT_TYPE_NUMBERS);
 //BA.debugLineNum = 52;BA.debugLine="txtClosedDelay.EditText.InputType = txtClosedDela";
mostCurrent._txtcloseddelay.getEditText().setInputType(mostCurrent._txtcloseddelay.getEditText().INPUT_TYPE_NUMBERS);
 //BA.debugLineNum = 54;BA.debugLine="tglConnection.Checked = True";
mostCurrent._tglconnection.setChecked(anywheresoftware.b4a.keywords.Common.True);
 //BA.debugLineNum = 56;BA.debugLine="ser.Initialize";
_ser._initialize(processBA);
 //BA.debugLineNum = 57;BA.debugLine="End Sub";
return "";
}
public static String  _activity_pause(boolean _userclosed) throws Exception{
 //BA.debugLineNum = 69;BA.debugLine="Sub Activity_Pause (UserClosed As Boolean)";
 //BA.debugLineNum = 71;BA.debugLine="End Sub";
return "";
}
public static String  _activity_resume() throws Exception{
 //BA.debugLineNum = 59;BA.debugLine="Sub Activity_Resume";
 //BA.debugLineNum = 60;BA.debugLine="Try";
try { //BA.debugLineNum = 61;BA.debugLine="If MQTT.IsInitialized = False Or MQTT.Connected";
if (_mqtt.IsInitialized()==anywheresoftware.b4a.keywords.Common.False || _mqtt.getConnected()==anywheresoftware.b4a.keywords.Common.False) { 
 //BA.debugLineNum = 62;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 };
 } 
       catch (Exception e6) {
			processBA.setLastException(e6); //BA.debugLineNum = 65;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 67;BA.debugLine="End Sub";
return "";
}
public static boolean  _application_error(anywheresoftware.b4a.objects.B4AException _error,String _stacktrace) throws Exception{
 //BA.debugLineNum = 333;BA.debugLine="Sub Application_Error (Error As Exception, StackTr";
 //BA.debugLineNum = 334;BA.debugLine="Return True";
if (true) return anywheresoftware.b4a.keywords.Common.True;
 //BA.debugLineNum = 335;BA.debugLine="End Sub";
return false;
}
public static String  _astream_error() throws Exception{
 //BA.debugLineNum = 318;BA.debugLine="Sub AStream_Error";
 //BA.debugLineNum = 319;BA.debugLine="Log(\"Error\")";
anywheresoftware.b4a.keywords.Common.Log("Error");
 //BA.debugLineNum = 320;BA.debugLine="End Sub";
return "";
}
public static String  _astream_terminated() throws Exception{
 //BA.debugLineNum = 322;BA.debugLine="Sub AStream_Terminated";
 //BA.debugLineNum = 323;BA.debugLine="Log(\"Terminated\")";
anywheresoftware.b4a.keywords.Common.Log("Terminated");
 //BA.debugLineNum = 324;BA.debugLine="End Sub";
return "";
}
public static void  _btnget_click() throws Exception{
ResumableSub_btnGet_Click rsub = new ResumableSub_btnGet_Click(null);
rsub.resume(processBA, null);
}
public static class ResumableSub_btnGet_Click extends BA.ResumableSub {
public ResumableSub_btnGet_Click(andy.home.system.settings parent) {
this.parent = parent;
}
andy.home.system.settings parent;
String _x = "";
anywheresoftware.b4a.jalle007.wificonnect.WiFiConnect _forcewificonnect = null;
int _i = 0;
anywheresoftware.b4a.objects.SocketWrapper _sock = null;
boolean _successful = false;
byte[] _buffer = null;
int step32;
int limit32;

@Override
public void resume(BA ba, Object[] result) throws Exception{

    while (true) {
try {

        switch (state) {
            case -1:
return;

case 0:
//C
this.state = 1;
 //BA.debugLineNum = 152;BA.debugLine="Dim x As String = \"\"";
_x = "";
 //BA.debugLineNum = 153;BA.debugLine="txtSSID.Text = x";
parent.mostCurrent._txtssid.setText((Object)(_x));
 //BA.debugLineNum = 154;BA.debugLine="txtPassword.Text = x";
parent.mostCurrent._txtpassword.setText((Object)(_x));
 //BA.debugLineNum = 155;BA.debugLine="txtOpenDelay.Text = x";
parent.mostCurrent._txtopendelay.setText((Object)(_x));
 //BA.debugLineNum = 156;BA.debugLine="txtClosedDelay.Text = x";
parent.mostCurrent._txtcloseddelay.setText((Object)(_x));
 //BA.debugLineNum = 158;BA.debugLine="If tglConnection.Checked Then";
if (true) break;

case 1:
//if
this.state = 54;
if (parent.mostCurrent._tglconnection.getChecked()) { 
this.state = 3;
}else {
this.state = 21;
}if (true) break;

case 3:
//C
this.state = 4;
 //BA.debugLineNum = 160;BA.debugLine="ProgressDialogShow(\"Attempting to retrieve setti";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Attempting to retrieve settings..."));
 //BA.debugLineNum = 161;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 55;
return;
case 55:
//C
this.state = 4;
;
 //BA.debugLineNum = 162;BA.debugLine="Try";
if (true) break;

case 4:
//try
this.state = 19;
this.catchState = 18;
this.state = 6;
if (true) break;

case 6:
//C
this.state = 7;
this.catchState = 18;
 //BA.debugLineNum = 163;BA.debugLine="CheckIfOnline";
_checkifonline();
 //BA.debugLineNum = 164;BA.debugLine="If IsInternetConnected Then";
if (true) break;

case 7:
//if
this.state = 16;
if (parent._isinternetconnected) { 
this.state = 9;
}else {
this.state = 15;
}if (true) break;

case 9:
//C
this.state = 10;
 //BA.debugLineNum = 165;BA.debugLine="If MQTT.IsInitialized = False Or MQTT.Connecte";
if (true) break;

case 10:
//if
this.state = 13;
if (parent._mqtt.IsInitialized()==anywheresoftware.b4a.keywords.Common.False || parent._mqtt.getConnected()==anywheresoftware.b4a.keywords.Common.False) { 
this.state = 12;
}if (true) break;

case 12:
//C
this.state = 13;
 //BA.debugLineNum = 166;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 if (true) break;

case 13:
//C
this.state = 16;
;
 //BA.debugLineNum = 168;BA.debugLine="MQTT.Publish(\"Andy\", BC.StringToBytes(\"Get set";
parent._mqtt.Publish("Andy",parent._bc.StringToBytes("Get settings","utf8"));
 if (true) break;

case 15:
//C
this.state = 16;
 //BA.debugLineNum = 170;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 171;BA.debugLine="ToastMessageShow(\"No internet connection\", Fal";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("No internet connection"),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 16:
//C
this.state = 19;
;
 if (true) break;

case 18:
//C
this.state = 19;
this.catchState = 0;
 //BA.debugLineNum = 174;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 //BA.debugLineNum = 175;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 if (true) break;
if (true) break;

case 19:
//C
this.state = 54;
this.catchState = 0;
;
 if (true) break;

case 21:
//C
this.state = 22;
 //BA.debugLineNum = 178;BA.debugLine="Try";
if (true) break;

case 22:
//try
this.state = 53;
this.catchState = 52;
this.state = 24;
if (true) break;

case 24:
//C
this.state = 25;
this.catchState = 52;
 //BA.debugLineNum = 179;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 56;
return;
case 56:
//C
this.state = 25;
;
 //BA.debugLineNum = 180;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 181;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 57;
return;
case 57:
//C
this.state = 25;
;
 //BA.debugLineNum = 182;BA.debugLine="ProgressDialogShow(\"Connecting to AndyRelayAcce";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Connecting to AndyRelayAccessPoint..."));
 //BA.debugLineNum = 183;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 58;
return;
case 58:
//C
this.state = 25;
;
 //BA.debugLineNum = 184;BA.debugLine="Dim forceWiFiConnect As WiFiConnect";
_forcewificonnect = new anywheresoftware.b4a.jalle007.wificonnect.WiFiConnect();
 //BA.debugLineNum = 185;BA.debugLine="For i = 1 To 40";
if (true) break;

case 25:
//for
this.state = 38;
step32 = 1;
limit32 = (int) (40);
_i = (int) (1) ;
this.state = 59;
if (true) break;

case 59:
//C
this.state = 38;
if ((step32 > 0 && _i <= limit32) || (step32 < 0 && _i >= limit32)) this.state = 27;
if (true) break;

case 60:
//C
this.state = 59;
_i = ((int)(0 + _i + step32)) ;
if (true) break;

case 27:
//C
this.state = 28;
 //BA.debugLineNum = 186;BA.debugLine="If forceWiFiConnect.IsWiFiEnabled Then";
if (true) break;

case 28:
//if
this.state = 37;
if (_forcewificonnect.IsWiFiEnabled(processBA)) { 
this.state = 30;
}if (true) break;

case 30:
//C
this.state = 31;
 //BA.debugLineNum = 187;BA.debugLine="If WiFi.SSID <> \"AndyRelayAccessPoint\" Then";
if (true) break;

case 31:
//if
this.state = 36;
if ((parent.mostCurrent._wifi.SSID()).equals("AndyRelayAccessPoint") == false) { 
this.state = 33;
}else {
this.state = 35;
}if (true) break;

case 33:
//C
this.state = 36;
 //BA.debugLineNum = 188;BA.debugLine="forceWiFiConnect.connectToSSID(forceWiFiConn";
_forcewificonnect.connectToSSID(processBA,_forcewificonnect.WIFI_OPEN,"AndyRelayAccessPoint","");
 if (true) break;

case 35:
//C
this.state = 36;
 //BA.debugLineNum = 190;BA.debugLine="Exit";
this.state = 38;
if (true) break;
 if (true) break;

case 36:
//C
this.state = 37;
;
 if (true) break;

case 37:
//C
this.state = 60;
;
 if (true) break;
if (true) break;

case 38:
//C
this.state = 39;
;
 //BA.debugLineNum = 194;BA.debugLine="ProgressDialogShow(\"Attempting to retrieve sett";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Attempting to retrieve settings..."));
 //BA.debugLineNum = 195;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 61;
return;
case 61:
//C
this.state = 39;
;
 //BA.debugLineNum = 196;BA.debugLine="Disconnect";
_disconnect();
 //BA.debugLineNum = 197;BA.debugLine="Dim sock As Socket";
_sock = new anywheresoftware.b4a.objects.SocketWrapper();
 //BA.debugLineNum = 198;BA.debugLine="sock.Initialize(\"sock\")";
_sock.Initialize("sock");
 //BA.debugLineNum = 199;BA.debugLine="sock.Connect(\"192.168.4.1\", 51042, 10000)";
_sock.Connect(processBA,"192.168.4.1",(int) (51042),(int) (10000));
 //BA.debugLineNum = 200;BA.debugLine="Wait For sock_Connected (Successful As Boolean)";
anywheresoftware.b4a.keywords.Common.WaitFor("sock_connected", processBA, this, null);
this.state = 62;
return;
case 62:
//C
this.state = 39;
_successful = (Boolean) result[0];
;
 //BA.debugLineNum = 201;BA.debugLine="If Successful Then";
if (true) break;

case 39:
//if
this.state = 50;
if (_successful) { 
this.state = 41;
}else {
this.state = 49;
}if (true) break;

case 41:
//C
this.state = 42;
 //BA.debugLineNum = 202;BA.debugLine="astream.InitializePrefix(sock.InputStream, Fal";
parent._astream.InitializePrefix(processBA,_sock.getInputStream(),anywheresoftware.b4a.keywords.Common.False,_sock.getOutputStream(),"astream");
 //BA.debugLineNum = 203;BA.debugLine="Wait For astream_NewData (Buffer() As Byte)";
anywheresoftware.b4a.keywords.Common.WaitFor("astream_newdata", processBA, this, null);
this.state = 63;
return;
case 63:
//C
this.state = 42;
_buffer = (byte[]) result[0];
;
 //BA.debugLineNum = 204;BA.debugLine="If Buffer(0) = 0 Then";
if (true) break;

case 42:
//if
this.state = 47;
if (_buffer[(int) (0)]==0) { 
this.state = 44;
}else {
this.state = 46;
}if (true) break;

case 44:
//C
this.state = 47;
 //BA.debugLineNum = 205;BA.debugLine="txtSSID.Text = x";
parent.mostCurrent._txtssid.setText((Object)(_x));
 //BA.debugLineNum = 206;BA.debugLine="txtPassword.Text = x";
parent.mostCurrent._txtpassword.setText((Object)(_x));
 //BA.debugLineNum = 207;BA.debugLine="txtOpenDelay.Text = x";
parent.mostCurrent._txtopendelay.setText((Object)(_x));
 //BA.debugLineNum = 208;BA.debugLine="txtClosedDelay.Text = x";
parent.mostCurrent._txtcloseddelay.setText((Object)(_x));
 //BA.debugLineNum = 209;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 210;BA.debugLine="ToastMessageShow(\"No settings found\", False)";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("No settings found"),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 46:
//C
this.state = 47;
 //BA.debugLineNum = 212;BA.debugLine="Wait For astream_NewData (Buffer() As Byte)";
anywheresoftware.b4a.keywords.Common.WaitFor("astream_newdata", processBA, this, null);
this.state = 64;
return;
case 64:
//C
this.state = 47;
_buffer = (byte[]) result[0];
;
 //BA.debugLineNum = 213;BA.debugLine="rec = ObjectsToRecord(ser.ConvertBytesToArray";
parent._rec = _objectstorecord(parent._ser._convertbytestoarray(_buffer));
 //BA.debugLineNum = 214;BA.debugLine="txtSSID.Text = rec.SSID";
parent.mostCurrent._txtssid.setText((Object)(parent._rec.SSID));
 //BA.debugLineNum = 215;BA.debugLine="txtPassword.Text = rec.Password";
parent.mostCurrent._txtpassword.setText((Object)(parent._rec.Password));
 //BA.debugLineNum = 216;BA.debugLine="txtOpenDelay.Text = rec.OpenDelay";
parent.mostCurrent._txtopendelay.setText((Object)(parent._rec.OpenDelay));
 //BA.debugLineNum = 217;BA.debugLine="txtClosedDelay.Text = rec.ClosedDelay";
parent.mostCurrent._txtcloseddelay.setText((Object)(parent._rec.ClosedDelay));
 //BA.debugLineNum = 218;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 219;BA.debugLine="ToastMessageShow(\"Successfully retrieved the";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Successfully retrieved the settings"),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 47:
//C
this.state = 50;
;
 if (true) break;

case 49:
//C
this.state = 50;
 if (true) break;

case 50:
//C
this.state = 53;
;
 //BA.debugLineNum = 223;BA.debugLine="Disconnect";
_disconnect();
 if (true) break;

case 52:
//C
this.state = 53;
this.catchState = 0;
 //BA.debugLineNum = 225;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 //BA.debugLineNum = 226;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 if (true) break;
if (true) break;

case 53:
//C
this.state = 54;
this.catchState = 0;
;
 if (true) break;

case 54:
//C
this.state = -1;
;
 //BA.debugLineNum = 229;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 230;BA.debugLine="End Sub";
if (true) break;
}} 
       catch (Exception e0) {
			
if (catchState == 0)
    throw e0;
else {
    state = catchState;
processBA.setLastException(e0);}
            }
        }
    }
}
public static void  _sock_connected(boolean _successful) throws Exception{
}
public static void  _astream_newdata(byte[] _buffer) throws Exception{
}
public static void  _btnset_click() throws Exception{
ResumableSub_btnSet_Click rsub = new ResumableSub_btnSet_Click(null);
rsub.resume(processBA, null);
}
public static class ResumableSub_btnSet_Click extends BA.ResumableSub {
public ResumableSub_btnSet_Click(andy.home.system.settings parent) {
this.parent = parent;
}
andy.home.system.settings parent;
anywheresoftware.b4a.objects.SocketWrapper _sock = null;
boolean _successful = false;

@Override
public void resume(BA ba, Object[] result) throws Exception{

    while (true) {
try {

        switch (state) {
            case -1:
return;

case 0:
//C
this.state = 1;
 //BA.debugLineNum = 76;BA.debugLine="If txtSSID.Text.Trim = \"\" Then";
if (true) break;

case 1:
//if
this.state = 4;
if ((parent.mostCurrent._txtssid.getText().trim()).equals("")) { 
this.state = 3;
}if (true) break;

case 3:
//C
this.state = 4;
 //BA.debugLineNum = 77;BA.debugLine="ToastMessageShow(\"Please enter a valid WiFi SSID";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid WiFi SSID (network name)"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 78;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 81;BA.debugLine="If txtPassword.Text.Trim = \"\" Then";

case 4:
//if
this.state = 7;
if ((parent.mostCurrent._txtpassword.getText().trim()).equals("")) { 
this.state = 6;
}if (true) break;

case 6:
//C
this.state = 7;
 //BA.debugLineNum = 82;BA.debugLine="ToastMessageShow(\"Please enter a valid WiFi pass";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid WiFi password"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 83;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 86;BA.debugLine="If txtPassword.Text.IndexOf(\" \") <> -1 Then";

case 7:
//if
this.state = 10;
if (parent.mostCurrent._txtpassword.getText().indexOf(" ")!=-1) { 
this.state = 9;
}if (true) break;

case 9:
//C
this.state = 10;
 //BA.debugLineNum = 87;BA.debugLine="ToastMessageShow(\"Space is not allowed in the Wi";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Space is not allowed in the WiFi password"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 88;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 91;BA.debugLine="If IsNumber(txtOpenDelay.Text) = False Or txtOpen";

case 10:
//if
this.state = 13;
if (anywheresoftware.b4a.keywords.Common.IsNumber(parent.mostCurrent._txtopendelay.getText())==anywheresoftware.b4a.keywords.Common.False || (parent.mostCurrent._txtopendelay.getText()).equals("0")) { 
this.state = 12;
}if (true) break;

case 12:
//C
this.state = 13;
 //BA.debugLineNum = 92;BA.debugLine="ToastMessageShow(\"Please enter a valid Open Dela";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid Open Delay value"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 93;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 96;BA.debugLine="If IsNumber(txtClosedDelay.Text) = False Or txtCl";

case 13:
//if
this.state = 16;
if (anywheresoftware.b4a.keywords.Common.IsNumber(parent.mostCurrent._txtcloseddelay.getText())==anywheresoftware.b4a.keywords.Common.False || (parent.mostCurrent._txtcloseddelay.getText()).equals("0")) { 
this.state = 15;
}if (true) break;

case 15:
//C
this.state = 16;
 //BA.debugLineNum = 97;BA.debugLine="ToastMessageShow(\"Please enter a valid Closed De";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid Closed Delay value"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 98;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 101;BA.debugLine="If tglConnection.Checked Then";

case 16:
//if
this.state = 47;
if (parent.mostCurrent._tglconnection.getChecked()) { 
this.state = 18;
}else {
this.state = 36;
}if (true) break;

case 18:
//C
this.state = 19;
 //BA.debugLineNum = 103;BA.debugLine="ProgressDialogShow(\"Attempting to set settings..";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Attempting to set settings..."));
 //BA.debugLineNum = 104;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 48;
return;
case 48:
//C
this.state = 19;
;
 //BA.debugLineNum = 105;BA.debugLine="Try";
if (true) break;

case 19:
//try
this.state = 34;
this.catchState = 33;
this.state = 21;
if (true) break;

case 21:
//C
this.state = 22;
this.catchState = 33;
 //BA.debugLineNum = 106;BA.debugLine="CheckIfOnline";
_checkifonline();
 //BA.debugLineNum = 107;BA.debugLine="If IsInternetConnected Then";
if (true) break;

case 22:
//if
this.state = 31;
if (parent._isinternetconnected) { 
this.state = 24;
}else {
this.state = 30;
}if (true) break;

case 24:
//C
this.state = 25;
 //BA.debugLineNum = 108;BA.debugLine="If MQTT.IsInitialized = False Or MQTT.Connecte";
if (true) break;

case 25:
//if
this.state = 28;
if (parent._mqtt.IsInitialized()==anywheresoftware.b4a.keywords.Common.False || parent._mqtt.getConnected()==anywheresoftware.b4a.keywords.Common.False) { 
this.state = 27;
}if (true) break;

case 27:
//C
this.state = 28;
 //BA.debugLineNum = 109;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 if (true) break;

case 28:
//C
this.state = 31;
;
 //BA.debugLineNum = 111;BA.debugLine="Log(txtSSID.Text & \"|\" & txtPassword.Text & \"|";
anywheresoftware.b4a.keywords.Common.Log(parent.mostCurrent._txtssid.getText()+"|"+parent.mostCurrent._txtpassword.getText()+"|"+parent.mostCurrent._txtopendelay.getText()+"|"+parent.mostCurrent._txtcloseddelay.getText());
 //BA.debugLineNum = 112;BA.debugLine="MQTT.Publish(\"Andy\", BC.StringToBytes(txtSSID.";
parent._mqtt.Publish("Andy",parent._bc.StringToBytes(parent.mostCurrent._txtssid.getText()+"|"+parent.mostCurrent._txtpassword.getText()+"|"+parent.mostCurrent._txtopendelay.getText()+"|"+parent.mostCurrent._txtcloseddelay.getText(),"utf8"));
 if (true) break;

case 30:
//C
this.state = 31;
 //BA.debugLineNum = 114;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 115;BA.debugLine="ToastMessageShow(\"No internet connection\", Fal";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("No internet connection"),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 31:
//C
this.state = 34;
;
 if (true) break;

case 33:
//C
this.state = 34;
this.catchState = 0;
 //BA.debugLineNum = 118;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 //BA.debugLineNum = 119;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 if (true) break;
if (true) break;

case 34:
//C
this.state = 47;
this.catchState = 0;
;
 if (true) break;

case 36:
//C
this.state = 37;
 //BA.debugLineNum = 123;BA.debugLine="Try";
if (true) break;

case 37:
//try
this.state = 46;
this.catchState = 45;
this.state = 39;
if (true) break;

case 39:
//C
this.state = 40;
this.catchState = 45;
 //BA.debugLineNum = 124;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 49;
return;
case 49:
//C
this.state = 40;
;
 //BA.debugLineNum = 125;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 126;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 50;
return;
case 50:
//C
this.state = 40;
;
 //BA.debugLineNum = 127;BA.debugLine="ProgressDialogShow(\"Connecting to AndyRelayAcce";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Connecting to AndyRelayAccessPoint..."));
 //BA.debugLineNum = 128;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 51;
return;
case 51:
//C
this.state = 40;
;
 //BA.debugLineNum = 129;BA.debugLine="Disconnect";
_disconnect();
 //BA.debugLineNum = 130;BA.debugLine="Dim sock As Socket";
_sock = new anywheresoftware.b4a.objects.SocketWrapper();
 //BA.debugLineNum = 131;BA.debugLine="sock.Initialize(\"sock\")";
_sock.Initialize("sock");
 //BA.debugLineNum = 132;BA.debugLine="sock.Connect(\"192.168.4.1\", 51042, 10000)";
_sock.Connect(processBA,"192.168.4.1",(int) (51042),(int) (10000));
 //BA.debugLineNum = 133;BA.debugLine="Wait For sock_Connected (Successful As Boolean)";
anywheresoftware.b4a.keywords.Common.WaitFor("sock_connected", processBA, this, null);
this.state = 52;
return;
case 52:
//C
this.state = 40;
_successful = (Boolean) result[0];
;
 //BA.debugLineNum = 134;BA.debugLine="If Successful Then";
if (true) break;

case 40:
//if
this.state = 43;
if (_successful) { 
this.state = 42;
}if (true) break;

case 42:
//C
this.state = 43;
 //BA.debugLineNum = 135;BA.debugLine="astream.InitializePrefix(sock.InputStream, Fal";
parent._astream.InitializePrefix(processBA,_sock.getInputStream(),anywheresoftware.b4a.keywords.Common.False,_sock.getOutputStream(),"astream");
 //BA.debugLineNum = 136;BA.debugLine="astream.Write(ser.ConvertArrayToBytes(RecordTo";
parent._astream.Write(parent._ser._convertarraytobytes(_recordtoobjects(parent._rec)));
 //BA.debugLineNum = 137;BA.debugLine="Sleep(2000)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (2000));
this.state = 53;
return;
case 53:
//C
this.state = 43;
;
 //BA.debugLineNum = 138;BA.debugLine="ToastMessageShow(\"Successfully saved the setti";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Successfully saved the settings"),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 43:
//C
this.state = 46;
;
 //BA.debugLineNum = 140;BA.debugLine="Disconnect";
_disconnect();
 if (true) break;

case 45:
//C
this.state = 46;
this.catchState = 0;
 //BA.debugLineNum = 142;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 //BA.debugLineNum = 143;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 if (true) break;
if (true) break;

case 46:
//C
this.state = 47;
this.catchState = 0;
;
 if (true) break;

case 47:
//C
this.state = -1;
;
 //BA.debugLineNum = 146;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 147;BA.debugLine="End Sub";
if (true) break;
}} 
       catch (Exception e0) {
			
if (catchState == 0)
    throw e0;
else {
    state = catchState;
processBA.setLastException(e0);}
            }
        }
    }
}
public static String  _checkifonline() throws Exception{
 //BA.debugLineNum = 241;BA.debugLine="Sub CheckIfOnline";
 //BA.debugLineNum = 242;BA.debugLine="CheckInternetJob.Initialize(\"CheckInternetJob\", M";
mostCurrent._checkinternetjob._initialize(processBA,"CheckInternetJob",settings.getObject());
 //BA.debugLineNum = 243;BA.debugLine="CheckInternetJob.Download(\"http://www.google.com\"";
mostCurrent._checkinternetjob._download("http://www.google.com");
 //BA.debugLineNum = 244;BA.debugLine="End Sub";
return "";
}
public static String  _disconnect() throws Exception{
 //BA.debugLineNum = 326;BA.debugLine="Sub Disconnect";
 //BA.debugLineNum = 327;BA.debugLine="Log(\"Disconnect\")";
anywheresoftware.b4a.keywords.Common.Log("Disconnect");
 //BA.debugLineNum = 328;BA.debugLine="If astream.IsInitialized Then astream.Close";
if (_astream.IsInitialized()) { 
_astream.Close();};
 //BA.debugLineNum = 329;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 330;BA.debugLine="End Sub";
return "";
}
public static String  _globals() throws Exception{
 //BA.debugLineNum = 21;BA.debugLine="Sub Globals";
 //BA.debugLineNum = 24;BA.debugLine="Private ACToolBarLight1 As ACToolBarLight";
mostCurrent._actoolbarlight1 = new de.amberhome.objects.appcompat.ACToolbarLightWrapper();
 //BA.debugLineNum = 25;BA.debugLine="Private ToolbarHelper As ACActionBar";
mostCurrent._toolbarhelper = new de.amberhome.objects.appcompat.ACActionBar();
 //BA.debugLineNum = 26;BA.debugLine="Private WiFi As MLwifi";
mostCurrent._wifi = new wifi.MLwifi();
 //BA.debugLineNum = 27;BA.debugLine="Private btnGet As Button";
mostCurrent._btnget = new anywheresoftware.b4a.objects.ButtonWrapper();
 //BA.debugLineNum = 28;BA.debugLine="Private btnSet As Button";
mostCurrent._btnset = new anywheresoftware.b4a.objects.ButtonWrapper();
 //BA.debugLineNum = 29;BA.debugLine="Private txtPassword As FloatLabeledEditText";
mostCurrent._txtpassword = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 30;BA.debugLine="Private txtSSID As FloatLabeledEditText";
mostCurrent._txtssid = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 31;BA.debugLine="Private txtClosedDelay As FloatLabeledEditText";
mostCurrent._txtcloseddelay = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 32;BA.debugLine="Private txtOpenDelay As FloatLabeledEditText";
mostCurrent._txtopendelay = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 33;BA.debugLine="Private tglConnection As ToggleButton";
mostCurrent._tglconnection = new anywheresoftware.b4a.objects.CompoundButtonWrapper.ToggleButtonWrapper();
 //BA.debugLineNum = 34;BA.debugLine="Dim CheckInternetJob As HttpJob";
mostCurrent._checkinternetjob = new anywheresoftware.b4a.samples.httputils2.httpjob();
 //BA.debugLineNum = 35;BA.debugLine="Dim IsInternetConnected As Boolean";
_isinternetconnected = false;
 //BA.debugLineNum = 36;BA.debugLine="End Sub";
return "";
}
public static boolean  _isconnectedtointernet() throws Exception{
anywheresoftware.b4a.phone.Phone _p = null;
anywheresoftware.b4a.objects.SocketWrapper.ServerSocketWrapper _wf = null;
boolean _b = false;
 //BA.debugLineNum = 337;BA.debugLine="Sub IsConnectedToInternet As Boolean 'ignore";
 //BA.debugLineNum = 338;BA.debugLine="Dim P As Phone";
_p = new anywheresoftware.b4a.phone.Phone();
 //BA.debugLineNum = 339;BA.debugLine="Dim WF As ServerSocket 'ignore";
_wf = new anywheresoftware.b4a.objects.SocketWrapper.ServerSocketWrapper();
 //BA.debugLineNum = 340;BA.debugLine="Dim B As Boolean=False";
_b = anywheresoftware.b4a.keywords.Common.False;
 //BA.debugLineNum = 342;BA.debugLine="If P.GetDataState=\"CONNECTED\" Then B=True";
if ((_p.GetDataState()).equals("CONNECTED")) { 
_b = anywheresoftware.b4a.keywords.Common.True;};
 //BA.debugLineNum = 343;BA.debugLine="If WF.GetMyWiFiIP<>\"127.0.0.1\" Then B=True  'igno";
if ((_wf.GetMyWifiIP()).equals("127.0.0.1") == false) { 
_b = anywheresoftware.b4a.keywords.Common.True;};
 //BA.debugLineNum = 344;BA.debugLine="If WF.GetMyIP<>\"127.0.0.1\" Then B=True";
if ((_wf.GetMyIP()).equals("127.0.0.1") == false) { 
_b = anywheresoftware.b4a.keywords.Common.True;};
 //BA.debugLineNum = 346;BA.debugLine="Return B";
if (true) return _b;
 //BA.debugLineNum = 347;BA.debugLine="End Sub";
return false;
}
public static String  _jobdone(anywheresoftware.b4a.samples.httputils2.httpjob _job) throws Exception{
 //BA.debugLineNum = 232;BA.debugLine="Sub JobDone(job As HttpJob)";
 //BA.debugLineNum = 233;BA.debugLine="If job.JobName=\"CheckInternetJob\" And job.Success";
if ((_job._jobname).equals("CheckInternetJob") && _job._success==anywheresoftware.b4a.keywords.Common.False) { 
 //BA.debugLineNum = 234;BA.debugLine="IsInternetConnected = False";
_isinternetconnected = anywheresoftware.b4a.keywords.Common.False;
 }else {
 //BA.debugLineNum = 236;BA.debugLine="IsInternetConnected = True";
_isinternetconnected = anywheresoftware.b4a.keywords.Common.True;
 };
 //BA.debugLineNum = 238;BA.debugLine="job.Release";
_job._release();
 //BA.debugLineNum = 239;BA.debugLine="End Sub";
return "";
}
public static String  _mqtt_connect() throws Exception{
String _clientid = "";
anywheresoftware.b4j.objects.MqttAsyncClientWrapper.MqttConnectOptionsWrapper _connopt = null;
 //BA.debugLineNum = 247;BA.debugLine="Sub MQTT_Connect";
 //BA.debugLineNum = 248;BA.debugLine="Try";
try { //BA.debugLineNum = 249;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'crea";
_clientid = BA.NumberToString(anywheresoftware.b4a.keywords.Common.Rnd((int) (0),(int) (999999999)));
 //BA.debugLineNum = 250;BA.debugLine="MQTT.Initialize(\"MQTT\", MQTTServerURI, ClientId)";
_mqtt.Initialize(processBA,"MQTT",_mqttserveruri,_clientid);
 //BA.debugLineNum = 251;BA.debugLine="Dim ConnOpt As MqttConnectOptions";
_connopt = new anywheresoftware.b4j.objects.MqttAsyncClientWrapper.MqttConnectOptionsWrapper();
 //BA.debugLineNum = 252;BA.debugLine="ConnOpt.Initialize(MQTTUser, MQTTPassword)";
_connopt.Initialize(_mqttuser,_mqttpassword);
 //BA.debugLineNum = 253;BA.debugLine="MQTT.Connect2(ConnOpt)";
_mqtt.Connect2((org.eclipse.paho.client.mqttv3.MqttConnectOptions)(_connopt.getObject()));
 } 
       catch (Exception e8) {
			processBA.setLastException(e8); //BA.debugLineNum = 255;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 257;BA.debugLine="End Sub";
return "";
}
public static String  _mqtt_connected(boolean _success) throws Exception{
 //BA.debugLineNum = 259;BA.debugLine="Sub MQTT_Connected (Success As Boolean)";
 //BA.debugLineNum = 260;BA.debugLine="Try";
try { //BA.debugLineNum = 261;BA.debugLine="If Success = False Then";
if (_success==anywheresoftware.b4a.keywords.Common.False) { 
 //BA.debugLineNum = 262;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 }else {
 //BA.debugLineNum = 264;BA.debugLine="Log(\"Connected to MQTT broker\")";
anywheresoftware.b4a.keywords.Common.Log("Connected to MQTT broker");
 //BA.debugLineNum = 265;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
_mqtt.Subscribe("Andy",(int) (0));
 };
 } 
       catch (Exception e9) {
			processBA.setLastException(e9); //BA.debugLineNum = 268;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 271;BA.debugLine="End Sub";
return "";
}
public static String  _mqtt_disconnected() throws Exception{
 //BA.debugLineNum = 273;BA.debugLine="Private Sub MQTT_Disconnected";
 //BA.debugLineNum = 274;BA.debugLine="Try";
try { //BA.debugLineNum = 275;BA.debugLine="Log(\"Disconnected from MQTT broker\")";
anywheresoftware.b4a.keywords.Common.Log("Disconnected from MQTT broker");
 //BA.debugLineNum = 276;BA.debugLine="MQTT.Close";
_mqtt.Close();
 } 
       catch (Exception e5) {
			processBA.setLastException(e5); //BA.debugLineNum = 278;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 280;BA.debugLine="End Sub";
return "";
}
public static void  _mqtt_messagearrived(String _topic,byte[] _payload) throws Exception{
ResumableSub_MQTT_MessageArrived rsub = new ResumableSub_MQTT_MessageArrived(null,_topic,_payload);
rsub.resume(processBA, null);
}
public static class ResumableSub_MQTT_MessageArrived extends BA.ResumableSub {
public ResumableSub_MQTT_MessageArrived(andy.home.system.settings parent,String _topic,byte[] _payload) {
this.parent = parent;
this._topic = _topic;
this._payload = _payload;
}
andy.home.system.settings parent;
String _topic;
byte[] _payload;
String _status = "";
String[] _s = null;

@Override
public void resume(BA ba, Object[] result) throws Exception{

    while (true) {
try {

        switch (state) {
            case -1:
return;

case 0:
//C
this.state = 1;
 //BA.debugLineNum = 283;BA.debugLine="Try";
if (true) break;

case 1:
//try
this.state = 10;
this.catchState = 9;
this.state = 3;
if (true) break;

case 3:
//C
this.state = 4;
this.catchState = 9;
 //BA.debugLineNum = 284;BA.debugLine="Dim status As String";
_status = "";
 //BA.debugLineNum = 285;BA.debugLine="status = BytesToString(Payload, 0, Payload.Lengt";
_status = anywheresoftware.b4a.keywords.Common.BytesToString(_payload,(int) (0),_payload.length,"UTF8");
 //BA.debugLineNum = 286;BA.debugLine="Log(\"MQTT_MessageArrived: \" & status )";
anywheresoftware.b4a.keywords.Common.Log("MQTT_MessageArrived: "+_status);
 //BA.debugLineNum = 287;BA.debugLine="If status.IndexOf(\"*Get settings:\") <> -1 Then";
if (true) break;

case 4:
//if
this.state = 7;
if (_status.indexOf("*Get settings:")!=-1) { 
this.state = 6;
}if (true) break;

case 6:
//C
this.state = 7;
 //BA.debugLineNum = 288;BA.debugLine="Dim s() As String = Regex.Split(\",\", status.Rep";
_s = anywheresoftware.b4a.keywords.Common.Regex.Split(",",_status.replace("*Get settings: ",""));
 //BA.debugLineNum = 289;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 11;
return;
case 11:
//C
this.state = 7;
;
 //BA.debugLineNum = 290;BA.debugLine="txtSSID.Text = s(0).Trim";
parent.mostCurrent._txtssid.setText((Object)(_s[(int) (0)].trim()));
 //BA.debugLineNum = 291;BA.debugLine="txtPassword.Text = s(1).Trim";
parent.mostCurrent._txtpassword.setText((Object)(_s[(int) (1)].trim()));
 //BA.debugLineNum = 292;BA.debugLine="txtOpenDelay.Text = s(2).Trim";
parent.mostCurrent._txtopendelay.setText((Object)(_s[(int) (2)].trim()));
 //BA.debugLineNum = 293;BA.debugLine="txtClosedDelay.Text = s(3).Trim";
parent.mostCurrent._txtcloseddelay.setText((Object)(_s[(int) (3)].trim()));
 if (true) break;

case 7:
//C
this.state = 10;
;
 if (true) break;

case 9:
//C
this.state = 10;
this.catchState = 0;
 //BA.debugLineNum = 296;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 if (true) break;
if (true) break;

case 10:
//C
this.state = -1;
this.catchState = 0;
;
 //BA.debugLineNum = 298;BA.debugLine="End Sub";
if (true) break;
}} 
       catch (Exception e0) {
			
if (catchState == 0)
    throw e0;
else {
    state = catchState;
processBA.setLastException(e0);}
            }
        }
    }
}
public static andy.home.system.settings._record  _objectstorecord(Object[] _objects) throws Exception{
andy.home.system.settings._record _r = null;
 //BA.debugLineNum = 308;BA.debugLine="Sub ObjectsToRecord(Objects() As Object) As Record";
 //BA.debugLineNum = 309;BA.debugLine="Dim r As Record";
_r = new andy.home.system.settings._record();
 //BA.debugLineNum = 310;BA.debugLine="r.Initialize";
_r.Initialize();
 //BA.debugLineNum = 311;BA.debugLine="r.SSID = Objects(0)";
_r.SSID = BA.ObjectToString(_objects[(int) (0)]);
 //BA.debugLineNum = 312;BA.debugLine="r.Password = Objects(1)";
_r.Password = BA.ObjectToString(_objects[(int) (1)]);
 //BA.debugLineNum = 313;BA.debugLine="r.OpenDelay = Objects(2)";
_r.OpenDelay = BA.ObjectToString(_objects[(int) (2)]);
 //BA.debugLineNum = 314;BA.debugLine="r.ClosedDelay = Objects(3)";
_r.ClosedDelay = BA.ObjectToString(_objects[(int) (3)]);
 //BA.debugLineNum = 315;BA.debugLine="Return r";
if (true) return _r;
 //BA.debugLineNum = 316;BA.debugLine="End Sub";
return null;
}
public static String  _process_globals() throws Exception{
 //BA.debugLineNum = 7;BA.debugLine="Sub Process_Globals";
 //BA.debugLineNum = 10;BA.debugLine="Private MQTT As MqttClient";
_mqtt = new anywheresoftware.b4j.objects.MqttAsyncClientWrapper();
 //BA.debugLineNum = 11;BA.debugLine="Private MQTTUser As String = \"dbgdbcqw\"";
_mqttuser = "dbgdbcqw";
 //BA.debugLineNum = 12;BA.debugLine="Private MQTTPassword As String = \"Nc3F4APoO801\"";
_mqttpassword = "Nc3F4APoO801";
 //BA.debugLineNum = 13;BA.debugLine="Private MQTTServerURI As String = \"tcp://m14.clou";
_mqttserveruri = "tcp://m14.cloudmqtt.com:15093";
 //BA.debugLineNum = 14;BA.debugLine="Private BC As ByteConverter";
_bc = new anywheresoftware.b4a.agraham.byteconverter.ByteConverter();
 //BA.debugLineNum = 15;BA.debugLine="Private astream As AsyncStreams";
_astream = new anywheresoftware.b4a.randomaccessfile.AsyncStreams();
 //BA.debugLineNum = 16;BA.debugLine="Type Record (SSID As String, Password As String,";
;
 //BA.debugLineNum = 17;BA.debugLine="Private rec As Record";
_rec = new andy.home.system.settings._record();
 //BA.debugLineNum = 18;BA.debugLine="Private ser As B4RSerializator";
_ser = new andy.home.system.b4rserializator();
 //BA.debugLineNum = 19;BA.debugLine="End Sub";
return "";
}
public static Object[]  _recordtoobjects(andy.home.system.settings._record _record) throws Exception{
 //BA.debugLineNum = 300;BA.debugLine="Sub RecordToObjects (Record As Record) As Object()";
 //BA.debugLineNum = 301;BA.debugLine="Record.SSID = txtSSID.Text";
_record.SSID = mostCurrent._txtssid.getText();
 //BA.debugLineNum = 302;BA.debugLine="Record.Password = txtPassword.Text";
_record.Password = mostCurrent._txtpassword.getText();
 //BA.debugLineNum = 303;BA.debugLine="Record.OpenDelay = txtOpenDelay.Text";
_record.OpenDelay = mostCurrent._txtopendelay.getText();
 //BA.debugLineNum = 304;BA.debugLine="Record.ClosedDelay = txtClosedDelay.Text";
_record.ClosedDelay = mostCurrent._txtcloseddelay.getText();
 //BA.debugLineNum = 305;BA.debugLine="Return Array(Record.SSID, Record.Password, Record";
if (true) return new Object[]{(Object)(_record.SSID),(Object)(_record.Password),(Object)(_record.OpenDelay),(Object)(_record.ClosedDelay)};
 //BA.debugLineNum = 306;BA.debugLine="End Sub";
return null;
}
}
