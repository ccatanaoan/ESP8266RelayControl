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
public static String  _activity_create(boolean _firsttime) throws Exception{
anywheresoftware.b4a.objects.CSBuilder _cs = null;
 //BA.debugLineNum = 32;BA.debugLine="Sub Activity_Create(FirstTime As Boolean)";
 //BA.debugLineNum = 33;BA.debugLine="If FirstTime Then";
if (_firsttime) { 
 //BA.debugLineNum = 35;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 };
 //BA.debugLineNum = 37;BA.debugLine="Activity.LoadLayout(\"Settings\")";
mostCurrent._activity.LoadLayout("Settings",mostCurrent.activityBA);
 //BA.debugLineNum = 38;BA.debugLine="ToolbarHelper.Initialize";
mostCurrent._toolbarhelper.Initialize(mostCurrent.activityBA);
 //BA.debugLineNum = 39;BA.debugLine="Dim cs As CSBuilder";
_cs = new anywheresoftware.b4a.objects.CSBuilder();
 //BA.debugLineNum = 40;BA.debugLine="ToolbarHelper.Title= cs.Initialize.Size(20).Appen";
mostCurrent._toolbarhelper.setTitle(BA.ObjectToCharSequence(_cs.Initialize().Size((int) (20)).Append(BA.ObjectToCharSequence("Settings")).PopAll().getObject()));
 //BA.debugLineNum = 41;BA.debugLine="ToolbarHelper.Subtitle=\"\"";
mostCurrent._toolbarhelper.setSubtitle(BA.ObjectToCharSequence(""));
 //BA.debugLineNum = 42;BA.debugLine="ToolbarHelper.ShowUpIndicator = False 'set to tru";
mostCurrent._toolbarhelper.setShowUpIndicator(anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 43;BA.debugLine="ACToolBarLight1.InitMenuListener";
mostCurrent._actoolbarlight1.InitMenuListener();
 //BA.debugLineNum = 45;BA.debugLine="txtOpenDelay.EditText.InputType = txtOpenDelay.Ed";
mostCurrent._txtopendelay.getEditText().setInputType(mostCurrent._txtopendelay.getEditText().INPUT_TYPE_NUMBERS);
 //BA.debugLineNum = 46;BA.debugLine="txtClosedDelay.EditText.InputType = txtClosedDela";
mostCurrent._txtcloseddelay.getEditText().setInputType(mostCurrent._txtcloseddelay.getEditText().INPUT_TYPE_NUMBERS);
 //BA.debugLineNum = 48;BA.debugLine="tglConnection.Checked = True";
mostCurrent._tglconnection.setChecked(anywheresoftware.b4a.keywords.Common.True);
 //BA.debugLineNum = 49;BA.debugLine="End Sub";
return "";
}
public static String  _activity_pause(boolean _userclosed) throws Exception{
 //BA.debugLineNum = 61;BA.debugLine="Sub Activity_Pause (UserClosed As Boolean)";
 //BA.debugLineNum = 63;BA.debugLine="End Sub";
return "";
}
public static String  _activity_resume() throws Exception{
 //BA.debugLineNum = 51;BA.debugLine="Sub Activity_Resume";
 //BA.debugLineNum = 52;BA.debugLine="Try";
try { //BA.debugLineNum = 53;BA.debugLine="If MQTT.IsInitialized = False Or MQTT.Connected";
if (_mqtt.IsInitialized()==anywheresoftware.b4a.keywords.Common.False || _mqtt.getConnected()==anywheresoftware.b4a.keywords.Common.False) { 
 //BA.debugLineNum = 54;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 };
 } 
       catch (Exception e6) {
			processBA.setLastException(e6); //BA.debugLineNum = 57;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 59;BA.debugLine="End Sub";
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
anywheresoftware.b4a.samples.httputils2.httpjob _j = null;
String _htmlstring = "";
String[] _s = null;
int step24;
int limit24;

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
 //BA.debugLineNum = 153;BA.debugLine="ProgressDialogShow(\"Attempting to retrieve settin";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Attempting to retrieve settings..."));
 //BA.debugLineNum = 154;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 52;
return;
case 52:
//C
this.state = 1;
;
 //BA.debugLineNum = 155;BA.debugLine="Dim x As String = \"\"";
_x = "";
 //BA.debugLineNum = 156;BA.debugLine="txtSSID.Text = x";
parent.mostCurrent._txtssid.setText((Object)(_x));
 //BA.debugLineNum = 157;BA.debugLine="txtPassword.Text = x";
parent.mostCurrent._txtpassword.setText((Object)(_x));
 //BA.debugLineNum = 158;BA.debugLine="txtOpenDelay.Text = x";
parent.mostCurrent._txtopendelay.setText((Object)(_x));
 //BA.debugLineNum = 159;BA.debugLine="txtClosedDelay.Text = x";
parent.mostCurrent._txtcloseddelay.setText((Object)(_x));
 //BA.debugLineNum = 161;BA.debugLine="If MQTT.IsInitialized = False Or MQTT.Connected =";
if (true) break;

case 1:
//if
this.state = 4;
if (parent._mqtt.IsInitialized()==anywheresoftware.b4a.keywords.Common.False || parent._mqtt.getConnected()==anywheresoftware.b4a.keywords.Common.False) { 
this.state = 3;
}if (true) break;

case 3:
//C
this.state = 4;
 //BA.debugLineNum = 162;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 if (true) break;
;
 //BA.debugLineNum = 165;BA.debugLine="If tglConnection.Checked Then";

case 4:
//if
this.state = 51;
if (parent.mostCurrent._tglconnection.getChecked()) { 
this.state = 6;
}else {
this.state = 20;
}if (true) break;

case 6:
//C
this.state = 7;
 //BA.debugLineNum = 167;BA.debugLine="Try";
if (true) break;

case 7:
//try
this.state = 18;
this.catchState = 17;
this.state = 9;
if (true) break;

case 9:
//C
this.state = 10;
this.catchState = 17;
 //BA.debugLineNum = 168;BA.debugLine="If WiFi.isOnLine Then";
if (true) break;

case 10:
//if
this.state = 15;
if (parent.mostCurrent._wifi.isOnLine()) { 
this.state = 12;
}else {
this.state = 14;
}if (true) break;

case 12:
//C
this.state = 15;
 //BA.debugLineNum = 169;BA.debugLine="MQTT.Publish(\"Andy\", BC.StringToBytes(\"Get set";
parent._mqtt.Publish("Andy",parent._bc.StringToBytes("Get settings","utf8"));
 if (true) break;

case 14:
//C
this.state = 15;
 //BA.debugLineNum = 171;BA.debugLine="ToastMessageShow(\"No internet connection\", Fal";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("No internet connection"),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 15:
//C
this.state = 18;
;
 if (true) break;

case 17:
//C
this.state = 18;
this.catchState = 0;
 //BA.debugLineNum = 174;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 if (true) break;
if (true) break;

case 18:
//C
this.state = 51;
this.catchState = 0;
;
 if (true) break;

case 20:
//C
this.state = 21;
 //BA.debugLineNum = 178;BA.debugLine="Try";
if (true) break;

case 21:
//try
this.state = 50;
this.catchState = 49;
this.state = 23;
if (true) break;

case 23:
//C
this.state = 24;
this.catchState = 49;
 //BA.debugLineNum = 179;BA.debugLine="Dim forceWiFiConnect As WiFiConnect";
_forcewificonnect = new anywheresoftware.b4a.jalle007.wificonnect.WiFiConnect();
 //BA.debugLineNum = 180;BA.debugLine="For i = 1 To 40";
if (true) break;

case 24:
//for
this.state = 37;
step24 = 1;
limit24 = (int) (40);
_i = (int) (1) ;
this.state = 53;
if (true) break;

case 53:
//C
this.state = 37;
if ((step24 > 0 && _i <= limit24) || (step24 < 0 && _i >= limit24)) this.state = 26;
if (true) break;

case 54:
//C
this.state = 53;
_i = ((int)(0 + _i + step24)) ;
if (true) break;

case 26:
//C
this.state = 27;
 //BA.debugLineNum = 181;BA.debugLine="If forceWiFiConnect.IsWiFiEnabled Then";
if (true) break;

case 27:
//if
this.state = 36;
if (_forcewificonnect.IsWiFiEnabled(processBA)) { 
this.state = 29;
}if (true) break;

case 29:
//C
this.state = 30;
 //BA.debugLineNum = 182;BA.debugLine="If WiFi.SSID <> \"AndyRelayAccessPoint\" Then";
if (true) break;

case 30:
//if
this.state = 35;
if ((parent.mostCurrent._wifi.SSID()).equals("AndyRelayAccessPoint") == false) { 
this.state = 32;
}else {
this.state = 34;
}if (true) break;

case 32:
//C
this.state = 35;
 //BA.debugLineNum = 183;BA.debugLine="forceWiFiConnect.connectToSSID(forceWiFiConn";
_forcewificonnect.connectToSSID(processBA,_forcewificonnect.WIFI_OPEN,"AndyRelayAccessPoint","");
 if (true) break;

case 34:
//C
this.state = 35;
 //BA.debugLineNum = 185;BA.debugLine="Exit";
this.state = 37;
if (true) break;
 if (true) break;

case 35:
//C
this.state = 36;
;
 if (true) break;

case 36:
//C
this.state = 54;
;
 if (true) break;
if (true) break;

case 37:
//C
this.state = 38;
;
 //BA.debugLineNum = 190;BA.debugLine="Dim j As HttpJob";
_j = new anywheresoftware.b4a.samples.httputils2.httpjob();
 //BA.debugLineNum = 191;BA.debugLine="j.Initialize(\"\", Me)";
_j._initialize(processBA,"",settings.getObject());
 //BA.debugLineNum = 192;BA.debugLine="j.Download(\"http://192.168.4.1/getsettings\")";
_j._download("http://192.168.4.1/getsettings");
 //BA.debugLineNum = 193;BA.debugLine="j.GetRequest.SetHeader(\"User-Agent\", \"Mozilla/5";
_j._getrequest().SetHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
 //BA.debugLineNum = 194;BA.debugLine="j.GetRequest.Timeout = 2000";
_j._getrequest().setTimeout((int) (2000));
 //BA.debugLineNum = 195;BA.debugLine="Wait For (j) JobDone(j As HttpJob)";
anywheresoftware.b4a.keywords.Common.WaitFor("jobdone", processBA, this, (Object)(_j));
this.state = 55;
return;
case 55:
//C
this.state = 38;
_j = (anywheresoftware.b4a.samples.httputils2.httpjob) result[0];
;
 //BA.debugLineNum = 196;BA.debugLine="If j.Success Then";
if (true) break;

case 38:
//if
this.state = 47;
if (_j._success) { 
this.state = 40;
}else {
this.state = 46;
}if (true) break;

case 40:
//C
this.state = 41;
 //BA.debugLineNum = 197;BA.debugLine="Log(j.GetString)";
anywheresoftware.b4a.keywords.Common.Log(_j._getstring());
 //BA.debugLineNum = 198;BA.debugLine="Dim htmlstring As String = j.GetString";
_htmlstring = _j._getstring();
 //BA.debugLineNum = 199;BA.debugLine="Dim s() As String = Regex.Split(\",\", htmlstrin";
_s = anywheresoftware.b4a.keywords.Common.Regex.Split(",",_htmlstring);
 //BA.debugLineNum = 200;BA.debugLine="If s.Length = 4 Then";
if (true) break;

case 41:
//if
this.state = 44;
if (_s.length==4) { 
this.state = 43;
}if (true) break;

case 43:
//C
this.state = 44;
 //BA.debugLineNum = 201;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 56;
return;
case 56:
//C
this.state = 44;
;
 //BA.debugLineNum = 202;BA.debugLine="txtSSID.Text = s(0).Trim";
parent.mostCurrent._txtssid.setText((Object)(_s[(int) (0)].trim()));
 //BA.debugLineNum = 203;BA.debugLine="txtPassword.Text = s(1).Trim";
parent.mostCurrent._txtpassword.setText((Object)(_s[(int) (1)].trim()));
 //BA.debugLineNum = 204;BA.debugLine="txtOpenDelay.Text = s(2).Trim";
parent.mostCurrent._txtopendelay.setText((Object)(_s[(int) (2)].trim()));
 //BA.debugLineNum = 205;BA.debugLine="txtClosedDelay.Text = s(3).Trim";
parent.mostCurrent._txtcloseddelay.setText((Object)(_s[(int) (3)].trim()));
 if (true) break;

case 44:
//C
this.state = 47;
;
 if (true) break;

case 46:
//C
this.state = 47;
 //BA.debugLineNum = 209;BA.debugLine="ToastMessageShow(LastException, False)";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA).getObject()),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 47:
//C
this.state = 50;
;
 //BA.debugLineNum = 211;BA.debugLine="j.Release";
_j._release();
 if (true) break;

case 49:
//C
this.state = 50;
this.catchState = 0;
 //BA.debugLineNum = 213;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 if (true) break;
if (true) break;

case 50:
//C
this.state = 51;
this.catchState = 0;
;
 if (true) break;

case 51:
//C
this.state = -1;
;
 //BA.debugLineNum = 216;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 217;BA.debugLine="End Sub";
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
public static void  _jobdone(anywheresoftware.b4a.samples.httputils2.httpjob _j) throws Exception{
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
anywheresoftware.b4a.jalle007.wificonnect.WiFiConnect _forcewificonnect = null;
int _i = 0;
anywheresoftware.b4a.samples.httputils2.httpjob _j = null;
String _a = "";
String _b = "";
String _c = "";
String _d = "";
String _encodedurl = "";
int step40;
int limit40;

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
 //BA.debugLineNum = 68;BA.debugLine="If txtSSID.Text.Trim = \"\" Then";
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
 //BA.debugLineNum = 69;BA.debugLine="ToastMessageShow(\"Please enter a valid WiFi SSID";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid WiFi SSID (network name)"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 70;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 73;BA.debugLine="If txtPassword.Text.Trim = \"\" Then";

case 4:
//if
this.state = 7;
if ((parent.mostCurrent._txtpassword.getText().trim()).equals("")) { 
this.state = 6;
}if (true) break;

case 6:
//C
this.state = 7;
 //BA.debugLineNum = 74;BA.debugLine="ToastMessageShow(\"Please enter a valid WiFi pass";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid WiFi password"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 75;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 78;BA.debugLine="If txtPassword.Text.IndexOf(\" \") <> -1 Then";

case 7:
//if
this.state = 10;
if (parent.mostCurrent._txtpassword.getText().indexOf(" ")!=-1) { 
this.state = 9;
}if (true) break;

case 9:
//C
this.state = 10;
 //BA.debugLineNum = 79;BA.debugLine="ToastMessageShow(\"Space is not allowed in the Wi";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Space is not allowed in the WiFi password"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 80;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 83;BA.debugLine="If IsNumber(txtOpenDelay.Text) = False Or txtOpen";

case 10:
//if
this.state = 13;
if (anywheresoftware.b4a.keywords.Common.IsNumber(parent.mostCurrent._txtopendelay.getText())==anywheresoftware.b4a.keywords.Common.False || (parent.mostCurrent._txtopendelay.getText()).equals("0")) { 
this.state = 12;
}if (true) break;

case 12:
//C
this.state = 13;
 //BA.debugLineNum = 84;BA.debugLine="ToastMessageShow(\"Please enter a valid Open Dela";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid Open Delay value"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 85;BA.debugLine="Return";
if (true) return ;
 if (true) break;
;
 //BA.debugLineNum = 88;BA.debugLine="If IsNumber(txtClosedDelay.Text) = False Or txtCl";

case 13:
//if
this.state = 16;
if (anywheresoftware.b4a.keywords.Common.IsNumber(parent.mostCurrent._txtcloseddelay.getText())==anywheresoftware.b4a.keywords.Common.False || (parent.mostCurrent._txtcloseddelay.getText()).equals("0")) { 
this.state = 15;
}if (true) break;

case 15:
//C
this.state = 16;
 //BA.debugLineNum = 89;BA.debugLine="ToastMessageShow(\"Please enter a valid Closed De";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence("Please enter a valid Closed Delay value"),anywheresoftware.b4a.keywords.Common.False);
 //BA.debugLineNum = 90;BA.debugLine="Return";
if (true) return ;
 if (true) break;

case 16:
//C
this.state = 17;
;
 //BA.debugLineNum = 93;BA.debugLine="ProgressDialogShow(\"Attempting to set settings...";
anywheresoftware.b4a.keywords.Common.ProgressDialogShow(mostCurrent.activityBA,BA.ObjectToCharSequence("Attempting to set settings..."));
 //BA.debugLineNum = 94;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 64;
return;
case 64:
//C
this.state = 17;
;
 //BA.debugLineNum = 96;BA.debugLine="If MQTT.IsInitialized = False Or MQTT.Connected =";
if (true) break;

case 17:
//if
this.state = 20;
if (parent._mqtt.IsInitialized()==anywheresoftware.b4a.keywords.Common.False || parent._mqtt.getConnected()==anywheresoftware.b4a.keywords.Common.False) { 
this.state = 19;
}if (true) break;

case 19:
//C
this.state = 20;
 //BA.debugLineNum = 97;BA.debugLine="MQTT_Connect";
_mqtt_connect();
 if (true) break;
;
 //BA.debugLineNum = 100;BA.debugLine="If tglConnection.Checked Then";

case 20:
//if
this.state = 63;
if (parent.mostCurrent._tglconnection.getChecked()) { 
this.state = 22;
}else {
this.state = 36;
}if (true) break;

case 22:
//C
this.state = 23;
 //BA.debugLineNum = 102;BA.debugLine="Try";
if (true) break;

case 23:
//try
this.state = 34;
this.catchState = 33;
this.state = 25;
if (true) break;

case 25:
//C
this.state = 26;
this.catchState = 33;
 //BA.debugLineNum = 103;BA.debugLine="If WiFi.isOnLine Then";
if (true) break;

case 26:
//if
this.state = 31;
if (parent.mostCurrent._wifi.isOnLine()) { 
this.state = 28;
}else {
this.state = 30;
}if (true) break;

case 28:
//C
this.state = 31;
 //BA.debugLineNum = 104;BA.debugLine="Log(txtSSID.Text & \"|\" & txtPassword.Text & \"|";
anywheresoftware.b4a.keywords.Common.Log(parent.mostCurrent._txtssid.getText()+"|"+parent.mostCurrent._txtpassword.getText()+"|"+parent.mostCurrent._txtopendelay.getText()+"|"+parent.mostCurrent._txtcloseddelay.getText());
 //BA.debugLineNum = 105;BA.debugLine="MQTT.Publish(\"Andy\", BC.StringToBytes(txtSSID.";
parent._mqtt.Publish("Andy",parent._bc.StringToBytes(parent.mostCurrent._txtssid.getText()+"|"+parent.mostCurrent._txtpassword.getText()+"|"+parent.mostCurrent._txtopendelay.getText()+"|"+parent.mostCurrent._txtcloseddelay.getText(),"utf8"));
 if (true) break;

case 30:
//C
this.state = 31;
 //BA.debugLineNum = 107;BA.debugLine="ToastMessageShow(\"No internet connection\", Fal";
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
 //BA.debugLineNum = 110;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 if (true) break;
if (true) break;

case 34:
//C
this.state = 63;
this.catchState = 0;
;
 if (true) break;

case 36:
//C
this.state = 37;
 //BA.debugLineNum = 114;BA.debugLine="Try";
if (true) break;

case 37:
//try
this.state = 62;
this.catchState = 61;
this.state = 39;
if (true) break;

case 39:
//C
this.state = 40;
this.catchState = 61;
 //BA.debugLineNum = 115;BA.debugLine="Dim forceWiFiConnect As WiFiConnect";
_forcewificonnect = new anywheresoftware.b4a.jalle007.wificonnect.WiFiConnect();
 //BA.debugLineNum = 116;BA.debugLine="For i = 1 To 40";
if (true) break;

case 40:
//for
this.state = 53;
step40 = 1;
limit40 = (int) (40);
_i = (int) (1) ;
this.state = 65;
if (true) break;

case 65:
//C
this.state = 53;
if ((step40 > 0 && _i <= limit40) || (step40 < 0 && _i >= limit40)) this.state = 42;
if (true) break;

case 66:
//C
this.state = 65;
_i = ((int)(0 + _i + step40)) ;
if (true) break;

case 42:
//C
this.state = 43;
 //BA.debugLineNum = 117;BA.debugLine="If forceWiFiConnect.IsWiFiEnabled Then";
if (true) break;

case 43:
//if
this.state = 52;
if (_forcewificonnect.IsWiFiEnabled(processBA)) { 
this.state = 45;
}if (true) break;

case 45:
//C
this.state = 46;
 //BA.debugLineNum = 118;BA.debugLine="If WiFi.SSID <> \"AndyRelayAccessPoint\" Then";
if (true) break;

case 46:
//if
this.state = 51;
if ((parent.mostCurrent._wifi.SSID()).equals("AndyRelayAccessPoint") == false) { 
this.state = 48;
}else {
this.state = 50;
}if (true) break;

case 48:
//C
this.state = 51;
 //BA.debugLineNum = 119;BA.debugLine="forceWiFiConnect.connectToSSID(forceWiFiConn";
_forcewificonnect.connectToSSID(processBA,_forcewificonnect.WIFI_OPEN,"AndyRelayAccessPoint","");
 if (true) break;

case 50:
//C
this.state = 51;
 //BA.debugLineNum = 121;BA.debugLine="Exit";
this.state = 53;
if (true) break;
 if (true) break;

case 51:
//C
this.state = 52;
;
 if (true) break;

case 52:
//C
this.state = 66;
;
 if (true) break;
if (true) break;

case 53:
//C
this.state = 54;
;
 //BA.debugLineNum = 126;BA.debugLine="Dim j As HttpJob";
_j = new anywheresoftware.b4a.samples.httputils2.httpjob();
 //BA.debugLineNum = 127;BA.debugLine="j.Initialize(\"\", Me)";
_j._initialize(processBA,"",settings.getObject());
 //BA.debugLineNum = 128;BA.debugLine="Dim a As String = txtSSID.Text.trim";
_a = parent.mostCurrent._txtssid.getText().trim();
 //BA.debugLineNum = 129;BA.debugLine="Dim b As String = txtPassword.Text.trim";
_b = parent.mostCurrent._txtpassword.getText().trim();
 //BA.debugLineNum = 130;BA.debugLine="Dim c As String = txtOpenDelay.Text.trim";
_c = parent.mostCurrent._txtopendelay.getText().trim();
 //BA.debugLineNum = 131;BA.debugLine="Dim d As String = txtClosedDelay.Text.trim";
_d = parent.mostCurrent._txtcloseddelay.getText().trim();
 //BA.debugLineNum = 132;BA.debugLine="Dim encodedURL As String = \"http://192.168.4.1/";
_encodedurl = "http://192.168.4.1/set/"+_a+"/"+_b+"/"+_c+"/"+_d;
 //BA.debugLineNum = 133;BA.debugLine="encodedURL = encodedURL.Replace(\" \", \"%20\")";
_encodedurl = _encodedurl.replace(" ","%20");
 //BA.debugLineNum = 134;BA.debugLine="j.Download(encodedURL)";
_j._download(_encodedurl);
 //BA.debugLineNum = 135;BA.debugLine="j.GetRequest.SetHeader(\"User-Agent\", \"Mozilla/5";
_j._getrequest().SetHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0");
 //BA.debugLineNum = 136;BA.debugLine="j.GetRequest.Timeout = 2000";
_j._getrequest().setTimeout((int) (2000));
 //BA.debugLineNum = 137;BA.debugLine="Wait For (j) JobDone(j As HttpJob)";
anywheresoftware.b4a.keywords.Common.WaitFor("jobdone", processBA, this, (Object)(_j));
this.state = 67;
return;
case 67:
//C
this.state = 54;
_j = (anywheresoftware.b4a.samples.httputils2.httpjob) result[0];
;
 //BA.debugLineNum = 138;BA.debugLine="If j.Success Then";
if (true) break;

case 54:
//if
this.state = 59;
if (_j._success) { 
this.state = 56;
}else {
this.state = 58;
}if (true) break;

case 56:
//C
this.state = 59;
 if (true) break;

case 58:
//C
this.state = 59;
 //BA.debugLineNum = 141;BA.debugLine="ToastMessageShow(LastException,False)";
anywheresoftware.b4a.keywords.Common.ToastMessageShow(BA.ObjectToCharSequence(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA).getObject()),anywheresoftware.b4a.keywords.Common.False);
 if (true) break;

case 59:
//C
this.state = 62;
;
 //BA.debugLineNum = 143;BA.debugLine="j.Release";
_j._release();
 if (true) break;

case 61:
//C
this.state = 62;
this.catchState = 0;
 //BA.debugLineNum = 145;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 if (true) break;
if (true) break;

case 62:
//C
this.state = 63;
this.catchState = 0;
;
 if (true) break;

case 63:
//C
this.state = -1;
;
 //BA.debugLineNum = 148;BA.debugLine="ProgressDialogHide";
anywheresoftware.b4a.keywords.Common.ProgressDialogHide();
 //BA.debugLineNum = 149;BA.debugLine="End Sub";
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
public static String  _globals() throws Exception{
 //BA.debugLineNum = 17;BA.debugLine="Sub Globals";
 //BA.debugLineNum = 20;BA.debugLine="Private ACToolBarLight1 As ACToolBarLight";
mostCurrent._actoolbarlight1 = new de.amberhome.objects.appcompat.ACToolbarLightWrapper();
 //BA.debugLineNum = 21;BA.debugLine="Private ToolbarHelper As ACActionBar";
mostCurrent._toolbarhelper = new de.amberhome.objects.appcompat.ACActionBar();
 //BA.debugLineNum = 22;BA.debugLine="Private WiFi As MLwifi";
mostCurrent._wifi = new wifi.MLwifi();
 //BA.debugLineNum = 23;BA.debugLine="Private btnGet As Button";
mostCurrent._btnget = new anywheresoftware.b4a.objects.ButtonWrapper();
 //BA.debugLineNum = 24;BA.debugLine="Private btnSet As Button";
mostCurrent._btnset = new anywheresoftware.b4a.objects.ButtonWrapper();
 //BA.debugLineNum = 25;BA.debugLine="Private txtPassword As FloatLabeledEditText";
mostCurrent._txtpassword = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 26;BA.debugLine="Private txtSSID As FloatLabeledEditText";
mostCurrent._txtssid = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 27;BA.debugLine="Private txtClosedDelay As FloatLabeledEditText";
mostCurrent._txtcloseddelay = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 28;BA.debugLine="Private txtOpenDelay As FloatLabeledEditText";
mostCurrent._txtopendelay = new anywheresoftware.b4a.objects.FloatLabeledEditTextWrapper();
 //BA.debugLineNum = 29;BA.debugLine="Private tglConnection As ToggleButton";
mostCurrent._tglconnection = new anywheresoftware.b4a.objects.CompoundButtonWrapper.ToggleButtonWrapper();
 //BA.debugLineNum = 30;BA.debugLine="End Sub";
return "";
}
public static String  _mqtt_connect() throws Exception{
String _clientid = "";
anywheresoftware.b4j.objects.MqttAsyncClientWrapper.MqttConnectOptionsWrapper _connopt = null;
 //BA.debugLineNum = 220;BA.debugLine="Sub MQTT_Connect";
 //BA.debugLineNum = 221;BA.debugLine="Try";
try { //BA.debugLineNum = 222;BA.debugLine="Dim ClientId As String = Rnd(0, 999999999) 'crea";
_clientid = BA.NumberToString(anywheresoftware.b4a.keywords.Common.Rnd((int) (0),(int) (999999999)));
 //BA.debugLineNum = 223;BA.debugLine="MQTT.Initialize(\"MQTT\", MQTTServerURI, ClientId)";
_mqtt.Initialize(processBA,"MQTT",_mqttserveruri,_clientid);
 //BA.debugLineNum = 224;BA.debugLine="Dim ConnOpt As MqttConnectOptions";
_connopt = new anywheresoftware.b4j.objects.MqttAsyncClientWrapper.MqttConnectOptionsWrapper();
 //BA.debugLineNum = 225;BA.debugLine="ConnOpt.Initialize(MQTTUser, MQTTPassword)";
_connopt.Initialize(_mqttuser,_mqttpassword);
 //BA.debugLineNum = 226;BA.debugLine="MQTT.Connect2(ConnOpt)";
_mqtt.Connect2((org.eclipse.paho.client.mqttv3.MqttConnectOptions)(_connopt.getObject()));
 } 
       catch (Exception e8) {
			processBA.setLastException(e8); //BA.debugLineNum = 228;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 230;BA.debugLine="End Sub";
return "";
}
public static String  _mqtt_connected(boolean _success) throws Exception{
 //BA.debugLineNum = 232;BA.debugLine="Sub MQTT_Connected (Success As Boolean)";
 //BA.debugLineNum = 233;BA.debugLine="Try";
try { //BA.debugLineNum = 234;BA.debugLine="If Success = False Then";
if (_success==anywheresoftware.b4a.keywords.Common.False) { 
 //BA.debugLineNum = 235;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 }else {
 //BA.debugLineNum = 237;BA.debugLine="Log(\"Connected to MQTT broker\")";
anywheresoftware.b4a.keywords.Common.Log("Connected to MQTT broker");
 //BA.debugLineNum = 238;BA.debugLine="MQTT.Subscribe(\"Andy\", 0)";
_mqtt.Subscribe("Andy",(int) (0));
 };
 } 
       catch (Exception e9) {
			processBA.setLastException(e9); //BA.debugLineNum = 241;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 244;BA.debugLine="End Sub";
return "";
}
public static String  _mqtt_disconnected() throws Exception{
 //BA.debugLineNum = 246;BA.debugLine="Private Sub MQTT_Disconnected";
 //BA.debugLineNum = 247;BA.debugLine="Try";
try { //BA.debugLineNum = 248;BA.debugLine="Log(\"Disconnected from MQTT broker\")";
anywheresoftware.b4a.keywords.Common.Log("Disconnected from MQTT broker");
 //BA.debugLineNum = 249;BA.debugLine="MQTT.Close";
_mqtt.Close();
 } 
       catch (Exception e5) {
			processBA.setLastException(e5); //BA.debugLineNum = 251;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 };
 //BA.debugLineNum = 253;BA.debugLine="End Sub";
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
 //BA.debugLineNum = 256;BA.debugLine="Try";
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
 //BA.debugLineNum = 257;BA.debugLine="Dim status As String";
_status = "";
 //BA.debugLineNum = 258;BA.debugLine="status = BytesToString(Payload, 0, Payload.Lengt";
_status = anywheresoftware.b4a.keywords.Common.BytesToString(_payload,(int) (0),_payload.length,"UTF8");
 //BA.debugLineNum = 259;BA.debugLine="Log(\"MQTT_MessageArrived: \" & status )";
anywheresoftware.b4a.keywords.Common.Log("MQTT_MessageArrived: "+_status);
 //BA.debugLineNum = 260;BA.debugLine="If status.IndexOf(\"*Get settings:\") <> -1 Then";
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
 //BA.debugLineNum = 261;BA.debugLine="Dim s() As String = Regex.Split(\",\", status.Rep";
_s = anywheresoftware.b4a.keywords.Common.Regex.Split(",",_status.replace("*Get settings: ",""));
 //BA.debugLineNum = 262;BA.debugLine="Sleep(100)";
anywheresoftware.b4a.keywords.Common.Sleep(mostCurrent.activityBA,this,(int) (100));
this.state = 11;
return;
case 11:
//C
this.state = 7;
;
 //BA.debugLineNum = 263;BA.debugLine="txtSSID.Text = s(0).Trim";
parent.mostCurrent._txtssid.setText((Object)(_s[(int) (0)].trim()));
 //BA.debugLineNum = 264;BA.debugLine="txtPassword.Text = s(1).Trim";
parent.mostCurrent._txtpassword.setText((Object)(_s[(int) (1)].trim()));
 //BA.debugLineNum = 265;BA.debugLine="txtOpenDelay.Text = s(2).Trim";
parent.mostCurrent._txtopendelay.setText((Object)(_s[(int) (2)].trim()));
 //BA.debugLineNum = 266;BA.debugLine="txtClosedDelay.Text = s(3).Trim";
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
 //BA.debugLineNum = 269;BA.debugLine="Log(LastException)";
anywheresoftware.b4a.keywords.Common.Log(BA.ObjectToString(anywheresoftware.b4a.keywords.Common.LastException(mostCurrent.activityBA)));
 if (true) break;
if (true) break;

case 10:
//C
this.state = -1;
this.catchState = 0;
;
 //BA.debugLineNum = 271;BA.debugLine="End Sub";
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
 //BA.debugLineNum = 15;BA.debugLine="End Sub";
return "";
}
}
