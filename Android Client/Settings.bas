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
	Private astream As AsyncStreams
	Type Record (SSID As String, Password As String, OpenDelay As String, ClosedDelay As String)
	Private rec As Record
	Private ser As B4RSerializator
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
	Private tglConnection As ToggleButton
	Dim CheckInternetJob As HttpJob
	Dim IsInternetConnected As Boolean
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
	
	tglConnection.Checked = True
	
	ser.Initialize
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
	
	If tglConnection.Checked Then
		' Online
		ProgressDialogShow("Attempting to set settings...")
		Sleep(100)
		Try
			CheckIfOnline
			If IsInternetConnected Then
				If MQTT.IsInitialized = False Or MQTT.Connected = False Then
					MQTT_Connect
				End If
				Log(txtSSID.Text & "|" & txtPassword.Text & "|" & txtOpenDelay.Text & "|" & txtClosedDelay.Text)
				MQTT.Publish("Andy", BC.StringToBytes(txtSSID.Text & "|" & txtPassword.Text & "|" & txtOpenDelay.Text & "|" & txtClosedDelay.Text, "utf8"))
			Else
				ProgressDialogHide
				ToastMessageShow("No internet connection", False)
			End If
		Catch
			Log(LastException)
			ProgressDialogHide
		End Try
	Else
		' Access Point
		Try
			Sleep(100)
			ProgressDialogHide
			Sleep(100)
			ProgressDialogShow("Connecting to AndyRelayAccessPoint...")
			Sleep(100)
			Disconnect
			Dim sock As Socket
			sock.Initialize("sock")
			sock.Connect("192.168.4.1", 51042, 10000)
			Wait For sock_Connected (Successful As Boolean)
			If Successful Then
				astream.InitializePrefix(sock.InputStream, False, sock.OutputStream, "astream")
				astream.Write(ser.ConvertArrayToBytes(RecordToObjects(rec)))
				Sleep(2000)
				ToastMessageShow("Successfully saved the settings", False)
			End If
			Disconnect
		Catch
			Log(LastException)
			ProgressDialogHide
		End Try
	End If
	ProgressDialogHide
End Sub

Sub btnGet_Click
	'ToastMessageShow("Attempting to retrieve settings", False)

	Dim x As String = ""
	txtSSID.Text = x
	txtPassword.Text = x
	txtOpenDelay.Text = x
	txtClosedDelay.Text = x

	If tglConnection.Checked Then
		' Online
		ProgressDialogShow("Attempting to retrieve settings...")
		Sleep(100)
		Try
			CheckIfOnline
			If IsInternetConnected Then
				If MQTT.IsInitialized = False Or MQTT.Connected = False Then
					MQTT_Connect
				End If
				MQTT.Publish("Andy", BC.StringToBytes("Get settings", "utf8"))
			Else
				ProgressDialogHide
				ToastMessageShow("No internet connection", False)
			End If
		Catch
			Log(LastException)
			ProgressDialogHide
		End Try
	Else
		Try
			Sleep(100)
			ProgressDialogHide
			Sleep(100)
			ProgressDialogShow("Connecting to AndyRelayAccessPoint...")
			Sleep(100)
			Dim forceWiFiConnect As WiFiConnect
			For i = 1 To 40
				If forceWiFiConnect.IsWiFiEnabled Then
					If WiFi.SSID <> "AndyRelayAccessPoint" Then
						forceWiFiConnect.connectToSSID(forceWiFiConnect.WIFI_OPEN,"AndyRelayAccessPoint","")
					Else
						Exit
					End If
				End If
			Next
			ProgressDialogShow("Attempting to retrieve settings...")
			Sleep(100)
			Disconnect
			Dim sock As Socket
			sock.Initialize("sock")
			sock.Connect("192.168.4.1", 51042, 10000)
			Wait For sock_Connected (Successful As Boolean)
			If Successful Then
				astream.InitializePrefix(sock.InputStream, False, sock.OutputStream, "astream")
				Wait For astream_NewData (Buffer() As Byte)
				If Buffer(0) = 0 Then
					txtSSID.Text = x
					txtPassword.Text = x
					txtOpenDelay.Text = x
					txtClosedDelay.Text = x
					ProgressDialogHide
					ToastMessageShow("No settings found", False)
				Else
					Wait For astream_NewData (Buffer() As Byte)
					rec = ObjectsToRecord(ser.ConvertBytesToArray(Buffer))
					txtSSID.Text = rec.SSID
					txtPassword.Text = rec.Password
					txtOpenDelay.Text = rec.OpenDelay
					txtClosedDelay.Text = rec.ClosedDelay
					ProgressDialogHide
					ToastMessageShow("Successfully retrieved the settings", False)
				End If
			Else
			End If
			Disconnect
		Catch
			Log(LastException)
			ProgressDialogHide
		End Try
	End If
	ProgressDialogHide
End Sub

Sub JobDone(job As HttpJob)
	If job.JobName="CheckInternetJob" And job.Success=False Then
		IsInternetConnected = False
	Else
		IsInternetConnected = True
	End If
	job.Release
End Sub

Sub CheckIfOnline
	CheckInternetJob.Initialize("CheckInternetJob", Me)
	CheckInternetJob.Download("http://www.google.com")
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
		End If
	Catch
		Log(LastException)
	End Try
End Sub

Sub RecordToObjects (Record As Record) As Object()
	Record.SSID = txtSSID.Text
	Record.Password = txtPassword.Text
	Record.OpenDelay = txtOpenDelay.Text
	Record.ClosedDelay = txtClosedDelay.Text
	Return Array(Record.SSID, Record.Password, Record.OpenDelay, Record.ClosedDelay)
End Sub

Sub ObjectsToRecord(Objects() As Object) As Record
	Dim r As Record
	r.Initialize
	r.SSID = Objects(0)
	r.Password = Objects(1)
	r.OpenDelay = Objects(2)
	r.ClosedDelay = Objects(3)
	Return r
End Sub

Sub AStream_Error
	Log("Error")
End Sub

Sub AStream_Terminated
	Log("Terminated")
End Sub

Sub Disconnect
	Log("Disconnect")
	If astream.IsInitialized Then astream.Close
	ProgressDialogHide
End Sub

'Return true to allow the default exceptions handler to handle the uncaught exception.
Sub Application_Error (Error As Exception, StackTrace As String) As Boolean
	Return True
End Sub

Sub IsConnectedToInternet As Boolean 'ignore
	Dim P As Phone
	Dim WF As ServerSocket 'ignore
	Dim B As Boolean=False

	If P.GetDataState="CONNECTED" Then B=True
	If WF.GetMyWiFiIP<>"127.0.0.1" Then B=True  'ignore
	If WF.GetMyIP<>"127.0.0.1" Then B=True

	Return B
End Sub