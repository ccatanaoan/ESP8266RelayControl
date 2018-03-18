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
	Private ACToolBarLight1 As ACToolBarLight
	Private ToolbarHelper As ACActionBar
	Private WiFi As MLwifi
	Private btnGet As Button
	Private btnSet As Button
	Private txtPassword As FloatLabeledEditText
	Private txtSSID As FloatLabeledEditText
	Private txtClosedDelay As FloatLabeledEditText
	Private txtOpenDelay As FloatLabeledEditText
End Sub

Sub Activity_Create(FirstTime As Boolean)
	If FirstTime Then
		'CallSub(Me, MQTT_Connect)
		MQTT_Connect
	End If
	Activity.LoadLayout("Settings")
	ToolbarHelper.Initialize
	Dim cs As CSBuilder
	ToolbarHelper.Title= cs.Initialize.Size(20).Append("Settings").PopAll
	ToolbarHelper.Subtitle=""
	ToolbarHelper.ShowUpIndicator = False 'set to true to show the up arrow
	ACToolBarLight1.InitMenuListener

	txtOpenDelay.EditText.InputType = txtOpenDelay.EditText.INPUT_TYPE_NUMBERS
	txtClosedDelay.EditText.InputType = txtClosedDelay.EditText.INPUT_TYPE_NUMBERS
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

	If txtSSID.Text.Trim = "" Then
		ToastMessageShow("Please enter a valid WiFi SSID (network name)", False)
		Return
	End If
	
	If txtPassword.Text.Trim = "" Then
		ToastMessageShow("Please enter a valid WiFi password", False)
		Return
	End If
	
	If txtPassword.Text.IndexOf(" ") <> -1 Then
		ToastMessageShow("Space is not allowed in the WiFi password", False)
		Return
	End If
	
	If IsNumber(txtOpenDelay.Text) = False Or txtOpenDelay.Text = "0" Then
		ToastMessageShow("Please enter a valid Open Delay value", False)
		Return
	End If
	
	If IsNumber(txtClosedDelay.Text) = False Or txtClosedDelay.Text = "0" Then
		ToastMessageShow("Please enter a valid Closed Delay value", False)
		Return
	End If
	
	ProgressDialogShow("Attempting to set settings...")
	Sleep(100)
	
	' 1. Attempt via MQTT
	Try
		If WiFi.isOnLine Then
			Log(txtSSID.Text & "|" & txtPassword.Text & "|" & txtOpenDelay.Text & "|" & txtClosedDelay.Text)
			MQTT.Publish("Andy", BC.StringToBytes(txtSSID.Text & "|" & txtPassword.Text & "|" & txtOpenDelay.Text & "|" & txtClosedDelay.Text, "utf8"))
		Else
			'ToastMessageShow("No internet connection", False)
		End If
	Catch
		Log(LastException)
	End Try

	
	' 2. Attempt access point first
	Try
			Dim j As HttpJob
			j.Initialize("", Me)
			Dim a As String = txtSSID.Text.trim
			Dim b As String = txtPassword.Text.trim
			Dim c As String = txtOpenDelay.Text.trim
			Dim d As String = txtClosedDelay.Text.trim
			Dim encodedURL As String = "http://192.168.4.1/set/" & a & "/" & b & "/" & c & "/" & d
			encodedURL = encodedURL.Replace(" ", "%20")
			j.Download(encodedURL)
			j.GetRequest.SetHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0")
			j.GetRequest.Timeout = 2000
			Wait For (j) JobDone(j As HttpJob)
			If j.Success Then
			
			Else
				'ToastMessageShow(LastException, False)
			End If
			j.Release
	Catch
		Log(LastException)
	End Try
	ProgressDialogHide
End Sub

Sub btnGet_Click
	'ToastMessageShow("Attempting to retrieve settings", False)
	ProgressDialogShow("Attempting to retrieve settings...")
	Sleep(100)
	Dim x As String = ""
	txtSSID.Text = x
	txtPassword.Text = x
	txtOpenDelay.Text = x
	txtClosedDelay.Text = x
	
	' 1. Attempt via MQTT
	Try
		If WiFi.isOnLine Then
			MQTT.Publish("Andy", BC.StringToBytes("Get settings", "utf8"))
		Else
			ToastMessageShow("No internet connection", False)
		End If
	Catch
		Log(LastException)
	End Try
	
	' 2. Attempt access point first
	Try
		If WiFi.SSID="AndyRelayAccessPoint" Then
			Dim j As HttpJob
			j.Initialize("", Me)
			j.Download("http://192.168.4.1/getsettings")
			j.GetRequest.SetHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0")
			j.GetRequest.Timeout = 2000
			Wait For (j) JobDone(j As HttpJob)
			If j.Success Then
				Log(j.GetString)
				Dim htmlstring As String = j.GetString
				Dim s() As String = Regex.Split(",", htmlstring)
				If s.Length = 4 Then
					Sleep(100)
					txtSSID.Text = s(0).Trim
					txtPassword.Text = s(1).Trim
					txtOpenDelay.Text = s(2).Trim
					txtClosedDelay.Text = s(3).Trim
					'ToastMessageShow("Settings retrieved via access point", False)
				End If
			Else
				ToastMessageShow(LastException, False)
			End If
			j.Release
		End If
	Catch
		Log(LastException)
	End Try
	ProgressDialogHide
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
			Sleep(100)
			txtSSID.Text = s(0).Trim
			txtPassword.Text = s(1).Trim
			txtOpenDelay.Text = s(2).Trim
			txtClosedDelay.Text = s(3).Trim
			'ToastMessageShow("Settings retrieved via internet", False)
		End If
	Catch
		Log(LastException)
	End Try
End Sub

