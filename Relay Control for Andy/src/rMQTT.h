#pragma once
#include "B4RDefines.h"
#include "PubSubClient.h"
namespace B4R {
	typedef void (*SubVoidStringByteArray)(B4RString* str, Array* barray) ;
	class MqttClient;
	//~shortname: MqttConnectOptions
	class MqttConnectOptions {
		private:
			friend class MqttClient;
			Byte willQOS;
			B4RString* willTopic = NULL;
			B4RString* willPayload;
			bool willRetain;
		public:
			B4RString* Password;
			B4RString* UserName;
			//Sets the user name and password. Pass empty strings to omit a value.
			void Initialize(B4RString* UserName, B4RString* Password);
			//Sets the last will message. This message will be sent if the client is disconnected abruptly.
			void SetLastWill(B4RString* Topic, B4RString* Message, Byte QOS, bool Retained);
	};
	
	//~Version: 1.30
	//~ShortName: MqttClient
	//~Event: MessageArrived (Topic As String, Payload() As Byte)
	//~Event: Disconnected
	class MqttClient {
		private:
			static MqttClient* instance;
			PubSubClient psClient;
			static void callback(char*, uint8_t*, unsigned int);
			static void looper(void* b);
			SubVoidStringByteArray MessageArrivedSub;
			SubVoidVoid DisconnectedSub;
			PollerNode pnode;
			const char* clientId;
			void sharedInit(B4RStream* Stream, B4RString* ClientId, SubVoidStringByteArray MessageArrivedSub, SubVoidVoid DisconnectedSub);
		public:
			/**
			*Initializes the client.
			*Stream - A stream from the network client object. Note that the stream should not be connected before this method.
			*Ip - Server ip address.
			*Port - Server port.
			*ClientId - The client id. Note that the string must be a string literal or a process global string.
			*MessageArrivedSub - The sub that will handle the MessageArrived event.
			*DisconnectedSub - The sub that will handle the Disconnected event.
			*/
			void Initialize(B4RStream* Stream, ArrayByte* Ip, UInt Port, B4RString* ClientId, SubVoidStringByteArray MessageArrivedSub, SubVoidVoid DisconnectedSub);
			//Similar to Initialize. Accepts the server host name instead of the ip address.
			void Initialize2(B4RStream* Stream, B4RString* HostName, UInt Port, B4RString* ClientId, SubVoidStringByteArray MessageArrivedSub, SubVoidVoid DisconnectedSub);
			//Tries to connect to the server. Returns true if connection was successful.
			bool Connect();
			//Similar to Connect. Allows passing connection options with a MqttConnectOptions object.
			bool Connect2(MqttConnectOptions* Options);
			//Subscribes to the given topic. QOS should be 0 or 1. Returns true if operation was successful.
			bool Subscribe(B4RString* Topic, Byte QOS);
			//Unsubscribes from the given topic. Returns true if operation was successful.
			bool Unsubscribe(B4RString* Topic);
			//Publishes a message to the given topic. The QOS is set to 0. 
			bool Publish(B4RString* Topic, ArrayByte* Payload);
			//Similar to Publish. Allows setting the retain flag.
			bool Publish2(B4RString* Topic, ArrayByte* Payload, bool Retained);
			//Closes the client.
			void Close();
	};
	
}