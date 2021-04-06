

#include "ofxHeartbeat.h"

ofxHeartbeat::ofxHeartbeat()
{
}

ofxHeartbeat::~ofxHeartbeat() {

}

void ofxHeartbeat::setup( const string &serverIp, const string &appId, int txPort, const string &devIp )
{
    mCountdown = 0;
    mServerIp = devIp;
    mServerIp = serverIp;
    mTxPort = txPort;

    if( !mIsSetup ) {
        oscHeartbeatTx.setup( mServerIp, mTxPort );
        mIsSetup = true;
    }
    mRunning = true;

    ofLogNotice( "ofxHeartbeat" ) << "setup & start heartbeat at " << mServerIp << " " << ofGetElapsedTimef();
}

void ofxHeartbeat::resetCountdown()
{
    mCountdown = mHeartBeatInterval; 
}

void ofxHeartbeat::stop()
{
    mRunning = false;
    ofLogNotice( "ofxHeartbeat" ) << "stop heartbeat!";
}

void ofxHeartbeat::start()
{
    mRunning = true;
    resetCountdown();
    ofLogNotice( "ofxHeartbeat" ) << "start heartbeat!";
}


void ofxHeartbeat::update( float dt )
{

    if( mRunning ) {
        mCountdown -= dt;
        if( mCountdown < 0 ) {
            const ofxOscMessage m = encodeOsc();
            oscHeartbeatTx.sendMessage( m, false );
            // ofLogNotice("ofxHeartbeat") << "sent heartbeat at " << ofToString(ofGetElapsedTimef());

            resetCountdown();
        }
    }
}

ofxOscMessage ofxHeartbeat::encodeOsc() const
{
    ofxOscMessage m;
    m.setAddress( "/heart" );
    //m.addStringArg( mAppId ); //[1] device ID

    return m;
}
