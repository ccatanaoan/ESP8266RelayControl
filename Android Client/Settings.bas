B4A=true
Group=Default Group
ModulesStructureVersion=1
Type=Activity
Version=7.8
@EndOfDesignText@
#Region  Activity Attributes 
	#FullScreen: False
	#IncludeTitle: True
#End Region
#Extends: android.support.v7.app.AppCompatActivity

Sub Process_Globals
	'These global variables will be declared once when the application starts.
	'These variables can be accessed from all modules.
	Private MQTT As MqttClient
	Private MQTTUser As String = "dbgdbcqw"
	Private MQTTPassword As String = "Nc3F4APoO801"
	Private MQTTServerURI As String = "tcp://m14.cloudmqtt.com:15093"
	Private BC As ByteConverter
End Sub

Sub Globals
	'These global variables will be redeclared each time the activity is created.
	'These variables can only be accessed from this module.
	Private txtClosedDelay As EditText
	Private txtOpenDelay As EditText
	Private txtPassword As EditText
	Private txtSSID As EditText
	Private ACToolBarLight1 As ACToolBarLight
	Private ToolbarHelper As ACActionBar
	Private WiFi As MLwifi
	Private btnGet As Button
	Private btnSet As Button
End Sub

Sub Activity_Create(FirstTime As Boolean)
	If FirstTime Then
		'CallSub(Me, MQTT_Connect)
		MQTT_Connect
	End If
	Activity.LoadLayout("Settings")
	ToolbarHelper.Initialize
	Dim cs As CSBuilder
	ToolbarHelper.Title= "Settings" 'cs.Initialize.Size(20).Append("Settings").PopAll
	ToolbarHelper.Subtitle=""
	ToolbarHelper.ShowUpIndicator = False 'set to true to show the up arrow
	ACToolBarLight1.InitMenuListener

End Sub

Sub Activity_Resume
	Try
		If MQTT.IsInitialized = False Or MQTT.Connected = False Then
			MQTT_Connect
		End If
	Catch
		Log(LastException)
	End Try
End Sub

Sub Activity_Pause (UserClosed As Boolean)

End Sub


Sub btnSet_Click
	If WiFi.isWifiConnected = True And WiFi.SSID = "AndyRelayAccessPoint" Then
	
	Else
		If WiFi.isOnLine Then
			Log(txtSSID.Text & "|" & txtPassword.Text & "|" & txtOpenDelay.Text & "|" & txtClosedDelay.Text)
			MQTT.Publish("Andy", BC.StringToBytes(txtSSID.Text & "|" & txtPassword.Text & "|" & txtOpenDelay.Text & "|" & txtClosedDelay.Text, "utf8"))
		End If
	End If
End Sub

Sub btnGet_Click
	If WiFi.isWifiConnected = True And WiFi.SSID = "AndyRelayAccessPoint" Then
	
	Else
		If WiFi.isOnLine Then
			MQTT.Publish("Andy", BC.StringToBytes("Get settings", "utf8"))
		End If
	End If
End Sub

'Connect to CloudMQTT broker
Sub MQTT_Connect
	Try
		Dim ClientId As String = Rnd(0, 999999999) 'create a unique id
		MQTT.Initialize("MQTT", MQTTServerURI, ClientId)
		Dim ConnOpt As MqttConnectOptions
		ConnOpt.Initialize(MQTTUser, MQTTPassword)
		MQTT.Connect2(ConnOpt)
	Catch
		Log(LastException)
	End Try
End Sub

Sub MQTT_Connected (Success As Boolean)
	Try
		If Success = False Then
			Log(LastException)
		Else
			Log("Connected to MQTT broker")
			MQTT.Subscribe("Andy", 0)
		End If
	Catch
		Log(LastException)
	End Try
    
End Sub

Private Sub MQTT_Disconnected
	Try
		Log("Disconnected from MQTT broker")
		MQTT.Close
	Catch
		Log(LastException)
	End Try
End Sub

Private Sub MQTT_MessageArrived (Topic As String, Payload() As Byte)
	Try
		Dim status As String
		status = BytesToString(Payload, 0, Payload.Length, "UTF8")
		Log("MQTT_MessageArrived: " & status )
		If status.IndexOf("*Get settings:") <> -1 Then
			Dim s() As String = Regex.Split(",", status.Replace("*Get settings: ",""))
			txtSSID.Text = s(0).Trim
			txtPassword.Text = s(1).Trim
			txtOpenDelay.Text = s(2).Trim
			txtClosedDelay.Text = s(3).Trim
		End If
	Catch
		Log(LastException)
	End Try
End Sub