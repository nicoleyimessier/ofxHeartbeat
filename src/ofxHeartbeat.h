

#pragma once

#include "ofMain.h"
#include "ofxOscMessage.h"
#include "ofxOscSender.h"

class ofxHeartbeat {

public:
	ofxHeartbeat();
	~ofxHeartbeat();
	void setup(const string& serverIp,  // who to send heartbeats to
		const string& appId,     //
		int                   txPort,    //
		const string& devIp = "" //
	);
	void update(float dt);
	void stop();
	void start();
	void resetCountdown();
	bool isRunning() const { return mRunning; }

protected:
	bool   mRunning{ false };
	bool   mIsSetup{ false };
	float  mCountdown{ 0.0f };
	float  mHeartBeatInterval{ 1.0f };
	string mServerIp; // who to send heartbeats to
	string mDeviceIp; // my own IP
	string mAppId{ "APP" };
	int    mTxPort;

	ofxOscSender  oscHeartbeatTx; // to send hearbeats to server
	ofxOscMessage encodeOsc() const;
};
