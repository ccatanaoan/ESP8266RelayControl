Type=StaticCode
Version=2.2
ModulesStructureVersion=1
B4R=true
@EndOfDesignText@


Sub Process_Globals
	Private bc As ByteConverter
	Private Astream As AsyncStreams	
	Private server As WiFiServerSocket
End Sub

Public Sub Start
	Log("StartAP: ", Main.WiFi.StartAccessPoint("AndyRelayAP"))
	Log("My AP ip: ", Main.WiFi.AccessPointIp)
	server.Initialize(80, "server_NewConnection")
	server.Listen
End Sub

Private Sub Server_NewConnection (NewSocket As WiFiSocket)
	Astream.Initialize(NewSocket.Stream, "astream_NewData", "astream_Error")
End Sub

Private Sub Astream_NewData (Buffer() As Byte)
    Log("Buffer: ",Buffer)
	If bc.IndexOf(Buffer, "GET") <> -1 Then
		If bc.IndexOf(Buffer, "/set") <> -1 Then
			
			Dim ssid = "", password  = "" As String
			Dim i1 As Int = 0
			Dim i2 As Int = 0
			For Each b1() As Byte In bc.Split(Buffer, " ")
				If i1 = 1 Then
					For Each b2() As Byte In bc.Split(b1, "/")
						Select i2
							Case 2
								ssid = bc.StringFromBytes(b2)
							Case 3
								password = bc.StringFromBytes(b2)
						End Select
						i2 = i2 + 1
					Next
					
				End If
				i1 = i1 + 1
			Next
			Log(StackBufferUsage)
			Astream.Write("HTTP/1.1 200").Write(CRLF)
			Astream.Write("Content-Type: text/html").Write(CRLF).Write(CRLF)
			Astream.Write("<script>setTimeout(function(){location.href=""http://192.168.4.1""} , 20000);</script>")
			Astream.Write("WiFi set to: ").Write(ssid).Write(", password: ").Write(password).Write("<br><br/>Please wait...")
			Main.SaveNetworkDetails(ssid, password)
			CallSubPlus("ConnectWifi", 500, 0)
		Else If bc.IndexOf(Buffer, " / ") <> -1 Then
			Astream.Write("HTTP/1.1 200").Write(CRLF).Write(CRLF)
			If Main.WiFi.IsConnected Then
				Astream.Write("Connected to network.").Write(CRLF)
				Astream.Write("ESP8266 IP address: ").Write(Main.WiFi.LocalIp)
			Else
				Astream.Write("Not connected!")
			End If
    	Else
			Astream.Write("HTTP/1.1 404").Write(CRLF)
		End If
		CallSubPlus("CloseConnection", 200, 0)
	End If
End Sub

Private Sub ConnectWifi(u As Byte)
	Main.ConnectToNetwork
End Sub

Private Sub CloseConnection(u As Byte)
	Log("close connection")
	If server.Socket.Connected Then
		server.Socket.Stream.Flush
		server.Socket.Close
	End If
End Sub

Private Sub AStream_Error
	Log("Disconnected")
	server.Listen
End Sub

Public Sub ReplaceString(Original() As Byte, SearchFor() As Byte, ReplaceWith() As Byte) As Byte()
	'count number of occurrences
	Dim bc2 As ByteConverter
	Dim c As Int = 0
	Dim i As Int
	If SearchFor.Length <> ReplaceWith.Length Then
		i = bc2.IndexOf(Original, SearchFor)
		Do While i > -1 
			c = c + 1
			i = bc2.IndexOf2(Original, SearchFor, i + SearchFor.Length)
		Loop
	End If
	Dim result(Original.Length + c * (ReplaceWith.Length - SearchFor.Length)) As Byte
	Dim prevIndex As Int = 0
	Dim targetIndex As Int = 0
	i = bc2.IndexOf(Original, SearchFor)
	Do While i > -1 
		bc2.ArrayCopy2(Original, prevIndex, result, targetIndex, i - prevIndex)
		targetIndex = targetIndex + i - prevIndex
		bc2.ArrayCopy2(ReplaceWith, 0, result, targetIndex, ReplaceWith.Length)
		targetIndex = targetIndex + ReplaceWith.Length
		prevIndex = i + SearchFor.Length
		i = bc2.IndexOf2(Original, SearchFor, prevIndex)
	Loop
	If prevIndex < Original.Length Then
		bc2.ArrayCopy2(Original, prevIndex, result, targetIndex, Original.Length - prevIndex)
	End If
	Return result
End Sub