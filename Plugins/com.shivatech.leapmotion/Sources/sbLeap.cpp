//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "sbLeap.h"
#include "Leap_SDK\include\Leap.h"
#include <list>
using namespace std;
using namespace Leap;
//-----------------------------------------------------------------------------

#ifdef S3DX_DLL
	sbLeapAPI sbLeap ;
#endif

//
// GLOBALS
//



class ShivaListener : public Listener {
  public:
	S3DX::AIVariable AIModel;
	S3DX::AIVariable EventPrefix;
	int	EventReceiverType;
	int ListenerID;
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);

	ShivaListener(S3DX::AIVariable pAIModel, S3DX::AIVariable pEventPrefix, int pEventReceiverType);

	private:
		static int m_ClassID;
};

int ShivaListener::m_ClassID = 1;

ShivaListener::ShivaListener(S3DX::AIVariable pAIModel, S3DX::AIVariable pEventPrefix, int pEventReceiverType) {
	AIModel = pAIModel;
	EventPrefix = pEventPrefix;
	int EventReceiverType = pEventReceiverType;
	ListenerID = m_ClassID++;
}

void ShivaListener::onInit(const Controller& controller) {
  S3DX::AIVariable currentScene = S3DX::application.getCurrentUserScene();
  S3DX::AIVariable eventName = S3DX::string.format ( "%s%s", EventPrefix, "LeapListenerInit" );

  if ((EventReceiverType == 0) || (EventReceiverType == 1)) { // all or user event
	S3DX::scene.sendEventToAllUsers(currentScene, AIModel, eventName, ListenerID);
  }

  if ((EventReceiverType == 0) || (EventReceiverType == 2)) { // all or object event
	S3DX::scene.sendEventToAllObjects(currentScene, AIModel, eventName, ListenerID);
  }
}

void ShivaListener::onConnect(const Controller& controller) {
  S3DX::AIVariable currentScene = S3DX::application.getCurrentUserScene();
  S3DX::AIVariable eventName = S3DX::string.format ( "%s%s", EventPrefix, "LeapConnected" );

  if ((EventReceiverType == 0) || (EventReceiverType == 1)) { // all or user event
	S3DX::scene.sendEventToAllUsers(currentScene, AIModel, eventName, ListenerID);
  }

  if ((EventReceiverType == 0) || (EventReceiverType == 2)) { // all or object event
	S3DX::scene.sendEventToAllObjects(currentScene, AIModel, eventName, ListenerID);
  }
}

void ShivaListener::onDisconnect(const Controller& controller) {
  S3DX::AIVariable currentScene = S3DX::application.getCurrentUserScene();
  S3DX::AIVariable eventName = S3DX::string.format ( "%s%s", EventPrefix, "LeapDisconnected" );

  if ((EventReceiverType == 0) || (EventReceiverType == 1)) { // all or user event
	S3DX::scene.sendEventToAllUsers(currentScene, AIModel, eventName, ListenerID);
  }

  if ((EventReceiverType == 0) || (EventReceiverType == 2)) { // all or object event
	S3DX::scene.sendEventToAllObjects(currentScene, AIModel, eventName, ListenerID);
  }
}

void ShivaListener::onExit(const Controller& controller) {
  S3DX::AIVariable currentScene = S3DX::application.getCurrentUserScene();
  S3DX::AIVariable eventName = S3DX::string.format ( "%s%s", EventPrefix, "LeapListenerExit" );

  if ((EventReceiverType == 0) || (EventReceiverType == 1)) { // all or user event
	S3DX::scene.sendEventToAllUsers(currentScene, AIModel, eventName, ListenerID);
  }

  if ((EventReceiverType == 0) || (EventReceiverType == 2)) { // all or object event
	S3DX::scene.sendEventToAllObjects(currentScene, AIModel, eventName, ListenerID);
  }
}

void ShivaListener::onFrame(const Controller& controller) {
  S3DX::AIVariable currentScene = S3DX::application.getCurrentUserScene();
  S3DX::AIVariable eventName = S3DX::string.format ( "%s%s", EventPrefix, "LeapFrameReceived" );

  if ((EventReceiverType == 0) || (EventReceiverType == 1)) { // all or user event
	S3DX::scene.sendEventToAllUsers(currentScene, AIModel, eventName, ListenerID, (S3DX::float32)controller.frame().id(), controller.frame().hands().count(), controller.frame().pointables().count(), controller.frame().fingers().count(), controller.frame().tools().count(), (S3DX::float32)controller.frame().timestamp());
  }

  if ((EventReceiverType == 0) || (EventReceiverType == 2)) { // all or object event
	S3DX::scene.sendEventToAllObjects(currentScene, AIModel, eventName, ListenerID, (S3DX::float32)controller.frame().id(), controller.frame().hands().count(), controller.frame().pointables().count(), controller.frame().fingers().count(), controller.frame().tools().count(), (S3DX::float32)controller.frame().timestamp());
  }
}

Controller *LeapController;

Frame currentFrame, workingFrame;
vector<Frame> frameArray;
vector<ShivaListener *> Listeners;


//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

int Callback_sbLeap_getGestureSwipe ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getGestureSwipe" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nGestureID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPointableID ;
    S3DX::AIVariable nDirX ;
    S3DX::AIVariable nDirY ;
    S3DX::AIVariable nDirZ ;
    S3DX::AIVariable nPosX ;
    S3DX::AIVariable nPosY ;
    S3DX::AIVariable nPosZ ;
    S3DX::AIVariable nSpeed ;
    S3DX::AIVariable nStartX ;
    S3DX::AIVariable nStartY ;
    S3DX::AIVariable nStartZ ;

	//TODO these gesture functions are a bit loaded, is it better to do this or break it up into 5 function calls?  going with the easy route for now
	// code for nPointableID, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ, nSpeed, nStartX, nStartY, nStartZ = sbLeap.getGestureSwipe ( nGestureID )

	if (workingFrame.gesture(nGestureID).isValid()) {
		SwipeGesture swipe = (SwipeGesture)workingFrame.gesture(nGestureID);
		
		nPointableID = swipe.pointable().id();
		
		nDirX = swipe.direction().x;
		nDirY = swipe.direction().y;
		nDirZ = swipe.direction().z;
		
		nPosX = swipe.position().x;
		nPosY = swipe.position().y;
		nPosZ = swipe.position().z;

		nSpeed = swipe.speed();
		
		nStartX = swipe.startPosition().x;
		nStartY = swipe.startPosition().y;
		nStartZ = swipe.startPosition().z;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPointableID ;
    _pOut[iReturnCount++] = nDirX ;
    _pOut[iReturnCount++] = nDirY ;
    _pOut[iReturnCount++] = nDirZ ;
    _pOut[iReturnCount++] = nPosX ;
    _pOut[iReturnCount++] = nPosY ;
    _pOut[iReturnCount++] = nPosZ ;
    _pOut[iReturnCount++] = nSpeed ;
    _pOut[iReturnCount++] = nStartX ;
    _pOut[iReturnCount++] = nStartY ;
    _pOut[iReturnCount++] = nStartZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_getGestureCircle ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getGestureCircle" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nGestureID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPointableID ;
    S3DX::AIVariable nNormX ;
    S3DX::AIVariable nNormY ;
    S3DX::AIVariable nNormZ ;
    S3DX::AIVariable nCenterX ;
    S3DX::AIVariable nCenterY ;
    S3DX::AIVariable nCenterZ ;
    S3DX::AIVariable nNumberOfCircleTraces ;
    S3DX::AIVariable nRadiusOfCircle ;


	// code for nPointableID, nNormX, nNormY, nNormZ, nCenterX, nCenterY, nCenterZ, nNumberOfCircleTraces, nRadiusOfCircle = sbLeap.getGestureCircle ( nGestureID )
	if (workingFrame.gesture(nGestureID).isValid()) {
		CircleGesture circle = (CircleGesture)workingFrame.gesture(nGestureID);
		
		nPointableID = circle.pointable().id();
		
		nNormX = circle.normal().x;
		nNormY = circle.normal().y;
		nNormZ = circle.normal().z;
		
		nCenterX = circle.center().x;
		nCenterY = circle.center().y;
		nCenterZ = circle.center().z;

		nNumberOfCircleTraces = circle.progress();

		nRadiusOfCircle = circle.radius();
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPointableID ;
    _pOut[iReturnCount++] = nNormX ;
    _pOut[iReturnCount++] = nNormY ;
    _pOut[iReturnCount++] = nNormZ ;
    _pOut[iReturnCount++] = nCenterX ;
    _pOut[iReturnCount++] = nCenterY ;
    _pOut[iReturnCount++] = nCenterZ ;
    _pOut[iReturnCount++] = nNumberOfCircleTraces ;
    _pOut[iReturnCount++] = nRadiusOfCircle ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_getGestureKeyTap ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getGestureKeyTap" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nGestureID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPointableID ;
    S3DX::AIVariable nDirX ;
    S3DX::AIVariable nDirY ;
    S3DX::AIVariable nDirZ ;
    S3DX::AIVariable nPosX ;
    S3DX::AIVariable nPosY ;
    S3DX::AIVariable nPosZ ;


	// code for nPointableID, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ = sbLeap.getGestureKeyTap ( nGestureID )
	if (workingFrame.gesture(nGestureID).isValid()) {
		KeyTapGesture keytap = (KeyTapGesture)workingFrame.gesture(nGestureID);
		
		nPointableID = keytap.pointable().id();
		
		nDirX = keytap.direction().x;
		nDirY = keytap.direction().y;
		nDirZ = keytap.direction().z;

		nPosX = keytap.position().x;
		nPosY = keytap.position().y;
		nPosZ = keytap.position().z;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPointableID ;
    _pOut[iReturnCount++] = nDirX ;
    _pOut[iReturnCount++] = nDirY ;
    _pOut[iReturnCount++] = nDirZ ;
    _pOut[iReturnCount++] = nPosX ;
    _pOut[iReturnCount++] = nPosY ;
    _pOut[iReturnCount++] = nPosZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_getGestureScreenTap ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getGestureScreenTap" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nGestureID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPointableID ;
    S3DX::AIVariable nDirX ;
    S3DX::AIVariable nDirY ;
    S3DX::AIVariable nDirZ ;
    S3DX::AIVariable nPosX ;
    S3DX::AIVariable nPosY ;
    S3DX::AIVariable nPosZ ;


	// code for nPointableID, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ = sbLeap.getGestureScreenTap ( nGestureID )
	if (workingFrame.gesture(nGestureID).isValid()) {
		ScreenTapGesture screentap = (ScreenTapGesture)workingFrame.gesture(nGestureID);
		
		nPointableID = screentap.pointable().id();
		
		nDirX = screentap.direction().x;
		nDirY = screentap.direction().y;
		nDirZ = screentap.direction().z;

		nPosX = screentap.position().x;
		nPosY = screentap.position().y;
		nPosZ = screentap.position().z;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPointableID ;
    _pOut[iReturnCount++] = nDirX ;
    _pOut[iReturnCount++] = nDirY ;
    _pOut[iReturnCount++] = nDirZ ;
    _pOut[iReturnCount++] = nPosX ;
    _pOut[iReturnCount++] = nPosY ;
    _pOut[iReturnCount++] = nPosZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_getGesture ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getGesture" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nGestureIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nFrameIndex   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nGestureID = 0;
    S3DX::AIVariable kGestureType ;
    S3DX::AIVariable nDurationInSeconds ;
    S3DX::AIVariable kGestureState ;

	// code for nGestureID, kGestureType, nDurationInSeconds, kGestureState = sbLeap.getGesture ( nGestureIndex, nFrameIndex )
	//

	GestureList gestures;

	if (nFrameIndex.IsNil()) {
		gestures = workingFrame.gestures();
	} else {
		//TODO Would it be better to use the gestures(sinceFrame) variant here?
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			gestures = frameArray[nFrameIndex].gestures();
		} else {
			nGestureID = -1; // frame index out of range
		}
	}

	if (nGestureID == 0) {
		int gestureCount = gestures.count();
		if ((nGestureIndex > -1) && (nGestureIndex < gestureCount)) {
			nGestureID = gestures[nGestureIndex].id();
			nDurationInSeconds = gestures[nGestureIndex].durationSeconds();

			// Gesture Type
			switch(gestures[nGestureIndex].type()){
				case Gesture::TYPE_SWIPE:
					kGestureType = 0;
					break;
				case Gesture::TYPE_CIRCLE:
					kGestureType = 1;
					break;
				case Gesture::TYPE_SCREEN_TAP:
					kGestureType = 2;
					break;
				case Gesture::TYPE_KEY_TAP:
					kGestureType = 3;
					break;
				default:
					kGestureType = -1;
			}

			// Gesture State
			switch(gestures[nGestureIndex].state()){
				case Gesture::STATE_START:
					kGestureState = 0;
					break;
				case Gesture::STATE_UPDATE:
					kGestureState = 1;
					break;
				case Gesture::STATE_STOP:
					kGestureState = 2;
					break;
				default:
					kGestureState = -1;
			}
		} else {
			nGestureID = -2; // gesture index out of range
		}
	}

	//////

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nGestureID ;
    _pOut[iReturnCount++] = kGestureType ;
    _pOut[iReturnCount++] = nDurationInSeconds ;
    _pOut[iReturnCount++] = kGestureState ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_isGestureEnabled ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.isGestureEnabled" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable kGestureType = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bEnabled ;
	bool result = false;

	// code for bEnabled = sbLeap.isGestureEnabled ( kGestureType )
	switch((int)kGestureType){
		case 0:
			result = LeapController->isGestureEnabled(Gesture::TYPE_SWIPE);
			break;
		case 1:
			result = LeapController->isGestureEnabled(Gesture::TYPE_CIRCLE);
			break;
		case 2:
			result = LeapController->isGestureEnabled(Gesture::TYPE_SCREEN_TAP);
			break;
		case 3:
			result = LeapController->isGestureEnabled(Gesture::TYPE_KEY_TAP);
			break;
	}

	bEnabled.SetBooleanValue(result);

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bEnabled ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_enableGesture ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.enableGesture" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable kGestureType = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bEnable      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	bool enable = bEnable.GetBooleanValue();

    // code for sbLeap.enableGesture ( kGestureType, bEnable )
	switch((int)kGestureType){
		case 0:
			LeapController->enableGesture(Gesture::TYPE_SWIPE, enable);
			break;
		case 1:
			LeapController->enableGesture(Gesture::TYPE_CIRCLE, enable);
			break;
		case 2:
			LeapController->enableGesture(Gesture::TYPE_SCREEN_TAP, enable);
			break;
		case 3:
			LeapController->enableGesture(Gesture::TYPE_KEY_TAP, enable);
			break;
	}

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_getPointableDirection ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPointableDirection" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nDirX ;
    S3DX::AIVariable nDirY ;
    S3DX::AIVariable nDirZ ;

	Pointable p = workingFrame.pointable((int) nPointableID);

	if(p.isValid()){
		Leap::Vector direction = p.direction();
		nDirX = direction.x;
		nDirY = direction.y;
		nDirZ = direction.z;
	} else{
		nDirX = nDirY = nDirZ = -1;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nDirX ;
    _pOut[iReturnCount++] = nDirY ;
    _pOut[iReturnCount++] = nDirZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_sbLeap_setWorkingFrame ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.setWorkingFrame" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nFrameIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nResult ;

	// code for nResult = sbLeap.setWorkingFrame ( nFrameIndex ) )
	if (nFrameIndex.IsNil()) {
		workingFrame = currentFrame;
		nResult = -1;
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			workingFrame =  frameArray[nFrameIndex];
			nResult = nFrameIndex;
		} else {
			nFrameIndex = -2; // index out of bounds
			// if (dbg.warnings) S3DX::log.warning("");
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nResult ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_storeFrame ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.storeFrame" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nFrameIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nNewFrameIndex ;

	// code for nNewFrameIndex = sbLeap.storeFrame ( nFrameIndex ) )

	if (nNewFrameIndex.IsNil()) {
		nNewFrameIndex = frameArray.size();
		frameArray.push_back(currentFrame); 
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			frameArray[nFrameIndex] = currentFrame;
			nNewFrameIndex = nFrameIndex;
		} else {
			nNewFrameIndex = -1;
			// if (dbg.warnings) S3DX::log.warning("");
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nNewFrameIndex ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPalmNormal ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPalmNormal" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nNormX ;
    S3DX::AIVariable nNormY ;
    S3DX::AIVariable nNormZ ;

	// code for nNormX, nNormY, nNormZ = sbLeap.getPalmNormal ( nHandID ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		Leap::Vector norm = thisHand.palmNormal();
		nNormX = norm.x;
		nNormY = norm.y;
		nNormZ = norm.z;
	} else {
		nNormX = nNormY = nNormZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nNormX ;
    _pOut[iReturnCount++] = nNormY ;
    _pOut[iReturnCount++] = nNormZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPalmPosition ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPalmPosition" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPosX ;
    S3DX::AIVariable nPosY ;
    S3DX::AIVariable nPosZ ;

	// code for nPosX, nPosY, nPosZ = sbLeap.getPalmPosition ( nHandID ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		Leap::Vector position = thisHand.palmPosition();
		nPosX = position.x;
		nPosY = position.y;
		nPosZ = position.z;
	} else {
		nPosX = nPosY = nPosZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPosX ;
    _pOut[iReturnCount++] = nPosY ;
    _pOut[iReturnCount++] = nPosZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPalmVelocity ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPalmVelocity" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nVelX ;
    S3DX::AIVariable nVelY ;
    S3DX::AIVariable nVelZ ;

	// code for nVelX, nVelY, nVelZ = sbLeap.getPalmVelocity ( nHandID ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		Leap::Vector velocity = thisHand.palmVelocity();
		nVelX = velocity.x;
		nVelY = velocity.y;
		nVelZ = velocity.z;
	} else {
		nVelX = nVelY = nVelZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nVelX ;
    _pOut[iReturnCount++] = nVelY ;
    _pOut[iReturnCount++] = nVelZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandDirection ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandDirection" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nDirX ;
    S3DX::AIVariable nDirY ;
    S3DX::AIVariable nDirZ ;

	// code for nDirX, nDirY, nDirZ = sbLeap.getHandDirection ( nHandID ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		Leap::Vector direction = thisHand.direction();
		nDirX = direction.x;
		nDirY = direction.y;
		nDirZ = direction.z;
	} else {
		nDirX = nDirY = nDirZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nDirX ;
    _pOut[iReturnCount++] = nDirY ;
    _pOut[iReturnCount++] = nDirZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandRotationAxis ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandRotationAxis" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nAxisX ;
    S3DX::AIVariable nAxisY ;
    S3DX::AIVariable nAxisZ ;

	// code for nAxisX, nAxisY, nAxisZ = sbLeap.getHandRotationAxis ( nHandID, nSinceFrame ) )
	Hand thisHand = workingFrame.hand((int)nHandID);
	Frame sinceFrame = LeapController->frame(nSinceFrame);

	if (thisHand.isValid()) {
		Leap::Vector axis = thisHand.rotationAxis(sinceFrame);
		nAxisX = axis.x;
		nAxisY = axis.y;
		nAxisZ = axis.z;
	} else {
		nAxisX = nAxisY = nAxisZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nAxisX ;
    _pOut[iReturnCount++] = nAxisY ;
    _pOut[iReturnCount++] = nAxisZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandRotationAngle ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandRotationAngle" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nRefAxisX   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nRefAxisY   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nRefAxisZ   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nRotationAngle ;

	// code for nRotationAngle = sbLeap.getHandRotationAngle ( nHandID, nSinceFrame, nRefAxisX, nRefAxisY, nRefAxisZ ) )
	Hand thisHand = workingFrame.hand((int)nHandID);
	Frame sinceFrame = LeapController->frame(nSinceFrame);

	if (thisHand.isValid()) {
		nRotationAngle = thisHand.rotationAngle(sinceFrame);
	} else {
		nRotationAngle = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nRotationAngle ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandSphereCentre ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandSphereCentre" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nCentreX ;
    S3DX::AIVariable nCentreY ;
    S3DX::AIVariable nCentreZ ;

	// code for nCentreX, nCentreY, nCentreZ = sbLeap.getHandSphereCentre ( nHandID ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		Leap::Vector centre = thisHand.sphereCenter();
		nCentreX = centre.x;
		nCentreY = centre.y;
		nCentreZ = centre.z;
	} else {
		nCentreX = nCentreY = nCentreZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nCentreX ;
    _pOut[iReturnCount++] = nCentreY ;
    _pOut[iReturnCount++] = nCentreZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandSphereRadius ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandSphereRadius" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nRadius ;

	// code for nRadius = sbLeap.getHandSphereRadius ( nHandID ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		nRadius = thisHand.sphereRadius();
	} else {
		nRadius = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nRadius ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandScale ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandScale" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nScaleFactor ;

	// code for nScaleFactor = sbLeap.getHandScale ( nHandID, nSinceFrame ) )
	Hand thisHand = workingFrame.hand((int)nHandID);
	Frame sinceFrame = LeapController->frame(nSinceFrame);

	if (thisHand.isValid()) {
		nScaleFactor = thisHand.scaleFactor(sinceFrame);
	} else {
		nScaleFactor = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nScaleFactor ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandTranslation ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandTranslation" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nTransX ;
    S3DX::AIVariable nTransY ;
    S3DX::AIVariable nTransZ ;

	// code for nTransX, nTransY, nTransZ = sbLeap.getHandTranslation ( nHandID, nSinceFrame ) )
	Hand thisHand = workingFrame.hand((int)nHandID);
	Frame sinceFrame = LeapController->frame(nSinceFrame);

	if (thisHand.isValid()) {
		Leap::Vector trans = thisHand.translation(sinceFrame);
		nTransX = trans.x;
		nTransY = trans.y;
		nTransZ = trans.z;
	} else {
		nTransX = nTransY = nTransZ = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nTransX ;
    _pOut[iReturnCount++] = nTransY ;
    _pOut[iReturnCount++] = nTransZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandTool ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandTool" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID    = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nToolIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nToolID ;

	// code for nToolID = sbLeap.getHandTool ( nHandID, nToolIndex ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		ToolList tools = workingFrame.tools();
		int toolCount = tools.count();
		if (nToolIndex < toolCount) {
			nToolID = tools[nToolIndex].id();
		} else {
			nToolID = -2; // index out of range
		}
	} else {
		nToolID = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nToolID ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandFinger ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandFinger" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nFingerIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFingerID ;

	// code for nFingerID = sbLeap.getHandFinger ( nHandID, nFingerIndex ) )
	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		FingerList fingers = workingFrame.fingers();
		int fingerCount = fingers.count();
		if (nFingerIndex < fingerCount) {
			nFingerID = fingers[nFingerIndex].id();
		} else {
			nFingerID = -2; // index out of range
		}
	} else {
		nFingerID = -1; // hand ID invalid
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFingerID ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHandPointable ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHandPointable" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandID         = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nPointableIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPointableID ;

	// code for nPointableID = sbLeap.getHandPointable ( nHandID, nPointableIndex ) )

	Hand thisHand = workingFrame.hand((int)nHandID);

	if (thisHand.isValid()) {
		PointableList pointables = workingFrame.pointables();
		int pointableCount = pointables.count();
		if (nPointableIndex < pointableCount) {
			nPointableID = pointables[nPointableIndex].id();
		} else {
			nPointableID = -2; // index out of range
		}
	} else {
		nPointableID = -1; // hand ID invalid
	}


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPointableID ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPointableLength ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPointableLength" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nLength ;

	// code for nLength = sbLeap.getPointableLength ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid()) {
		nLength = workingFrame.pointable(nPointableID).length();
	} else {
		nLength = -1;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nLength ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPointableWidth ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPointableWidth" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nWidth ;

	//code for nWidth = sbLeap.getPointableWidth ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid()) {
		nWidth = workingFrame.pointable(nPointableID).width();
	} else {
		nWidth = -1;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nWidth ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPointableTipPosition ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPointableTipPosition" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPosX ;
    S3DX::AIVariable nPosY ;
    S3DX::AIVariable nPosZ ;

	// code for nPosX, nPosY, nPosZ = sbLeap.getPointableTipPosition ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid()) {
		Leap::Vector position = workingFrame.pointable(nPointableID).tipPosition();
		nPosX = position.x;
		nPosY = position.y;
		nPosZ = position.z;
	} else {
		nPosX = nPosY = nPosZ = -1;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPosX ;
    _pOut[iReturnCount++] = nPosY ;
    _pOut[iReturnCount++] = nPosZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getPointableTipVelocity ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getPointableTipVelocity" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nVelX ;
    S3DX::AIVariable nVelY ;
    S3DX::AIVariable nVelZ ;

	// code for nVelX, nVelY, nVelZ = sbLeap.getPointableTipVelocity ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid()) {
		Leap::Vector velocity = workingFrame.pointable(nPointableID).tipVelocity();
		nVelX = velocity.x;
		nVelY = velocity.y;
		nVelZ = velocity.z;
	} else {
		nVelX = nVelY = nVelZ = -1;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nVelX ;
    _pOut[iReturnCount++] = nVelY ;
    _pOut[iReturnCount++] = nVelZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_isFinger ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.isFinger" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bFinger ;

	// code for bFinger = sbLeap.isFinger ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid() && workingFrame.pointable(nPointableID).isFinger()) {
		bFinger = true;
	} else {
		bFinger = false;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bFinger ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_isTool ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.isTool" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bTool ;

	// code for bTool = sbLeap.isTool ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid() && workingFrame.pointable(nPointableID).isTool()) {
		bTool = true;
	} else {
		bTool = false;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bTool ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_isValidPointable ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.isValidPointable" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bPointable ;

	// code for bPointable = sbLeap.isValidPointable ( nPointableID ) )
	if (workingFrame.pointable(nPointableID).isValid()) {
		bPointable = true;
	} else {
		bPointable = false;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bPointable ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getHand ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getHand" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nHandIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable nFrameIndex   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;


    // Output Parameters 
    S3DX::AIVariable nHandID = 0;
    S3DX::AIVariable nNumberOfFingers ;
    S3DX::AIVariable nNumberOfTools ;

	// code for nHandID, nNumberOfFingers, nNumberOfTools = sbLeap.getHand ( nHandIndex, nFrameIndex ) )

	HandList hands;

	if (nFrameIndex.IsNil()) {
		hands = workingFrame.hands();
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			hands = frameArray[nFrameIndex].hands();
		} else {
			nHandID = -1; // frame index out of range
		}
	}

	if (nHandID == 0) {
		int handCount = hands.count();
		if ((nHandIndex > -1) && (nHandIndex < handCount)) {
			nHandID = hands[nHandIndex].id();
			FingerList fingers = hands[nHandIndex].fingers();
			nNumberOfFingers = fingers.count();
			ToolList tools = hands[nHandIndex].tools();
			nNumberOfTools = tools.count();
		} else {
			nHandID = -2; // hand index out of range
		}
	}


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nHandID ;
    _pOut[iReturnCount++] = nNumberOfFingers ;
    _pOut[iReturnCount++] = nNumberOfTools ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}


//
// FRAME FUNCTIONS
//

int Callback_sbLeap_getFrameTimeStamp ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameTimeStamp" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nFrameIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFrameTimestamp ;

	// code for nFrameTimestamp = sbLeap.getFrameTimeStamp ( nFrameIndex ) )
	if (nFrameIndex.IsNil()) {
		nFrameTimestamp = (S3DX::float32)workingFrame.timestamp();
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			nFrameTimestamp = (S3DX::float32) frameArray[nFrameIndex].timestamp();
		} else {
			nFrameTimestamp = -1;
			// if (dbg.warnings) S3DX::log.warning("");
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFrameTimestamp ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrameFinger ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameFinger" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nFingerIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nFrameIndex  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFingerID ;

	// code for nFingerID = sbLeap.getFrameFinger ( nFingerIndex, nFrameIndex ) )
	if (nFrameIndex.IsNil()) {
		FingerList fingers = workingFrame.fingers();
		int fingerCount = fingers.count();
		if (nFingerIndex < fingerCount) {
			nFingerID = fingers[nFingerIndex].id();
		} else {
			nFingerID = -2;
		}
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			FingerList fingers = frameArray[nFrameIndex].fingers();
			int fingerCount = fingers.count();
			if (nFingerIndex < fingerCount) {
				nFingerID = fingers[nFingerIndex].id();
			} else {
				nFingerID = -2;
			}
		} else {
			nFingerID = -1;
			// if (dbg.warnings) S3DX::log.warning("");
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFingerID ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFramePointable ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFramePointable" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nPointableIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nFrameIndex     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPointableID ;

	// code for nPointableID = sbLeap.getFramePointable ( nPointableIndex, nFrameIndex ) )
	if (nFrameIndex.IsNil()) {
		PointableList pointables = workingFrame.pointables();
		int pointableCount = pointables.count();
		if (nPointableIndex < pointableCount) {
			nPointableID = pointables[nPointableIndex].id();
		} else {
			nPointableID = -2;
		}
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			PointableList pointables = frameArray[nFrameIndex].pointables();
			int pointableCount = pointables.count();
			if (nPointableIndex < pointableCount) {
				nPointableID = pointables[nPointableIndex].id();
			} else {
				nPointableID = -2;
			}
		} else {
			nPointableID = -1;
			// if (dbg.warnings) S3DX::log.warning("");
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPointableID ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrameTool ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameTool" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nToolIndex  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nFrameIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nToolID ;

	// code for nToolID = sbLeap.getFrameTool ( nToolIndex, nFrameIndex ) )

	if (nFrameIndex.IsNil()) {
		ToolList tools = workingFrame.tools();
		int toolCount = tools.count();
		if (nToolIndex < toolCount) {
			nToolID = tools[nToolIndex].id();
		} else {
			nToolID = -2;
		}
	} else {
		if ((nFrameIndex > -1) && (nFrameIndex < frameArray.size())) {
			ToolList tools = frameArray[nFrameIndex].tools();
			int toolCount = tools.count();
			if (nToolIndex < toolCount) {
				nToolID = tools[nToolIndex].id();
			} else {
				nToolID = -2;
			}
		} else {
			nToolID = -1;
			// if (dbg.warnings) S3DX::log.warning("");
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nToolID ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrameRotationAngle ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameRotationAngle" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFrameRotAngle ;

	// code for nFrameRotAngle = sbLeap.getFrameRotationAngle ( nSinceFrame ) )
	if (nSinceFrame.IsNil()) {
		nSinceFrame = 0;
	}

	const Frame sinceFrame = LeapController->frame((int)nSinceFrame);

	nFrameRotAngle.SetNumberValue(workingFrame.rotationAngle(sinceFrame));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFrameRotAngle ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrameRotationAxis ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameRotationAxis" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFrameRotAxisX ;
    S3DX::AIVariable nFrameRotAxisY ;
    S3DX::AIVariable nFrameRotAxisZ ;

	// code for nFrameRotAxisX, nFrameRotAxisY, nFrameRotAxisZ = sbLeap.getFrameRotationAxis ( nSinceFrame ) )
	if (nSinceFrame.IsNil()) {
		nSinceFrame = 0;
	}

	const Frame sinceFrame = LeapController->frame((int)nSinceFrame);

	Leap::Vector result = workingFrame.rotationAxis(sinceFrame);

	nFrameRotAxisX = result.x;
	nFrameRotAxisY = result.y;
	nFrameRotAxisZ = result.z;

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFrameRotAxisX ;
    _pOut[iReturnCount++] = nFrameRotAxisY ;
    _pOut[iReturnCount++] = nFrameRotAxisZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrameTranslation ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameTranslation" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFrameTransX ;
    S3DX::AIVariable nFrameTransY ;
    S3DX::AIVariable nFrameTransZ ;

	// code for nFrameTransX, nFrameTransY, nFrameTransZ = sbLeap.getFrameTranslation ( nSinceFrame ) )
	if (nSinceFrame.IsNil()) {
		nSinceFrame = 0;
	}

	const Frame sinceFrame = LeapController->frame((int)nSinceFrame);

	Leap::Vector trans = workingFrame.translation(sinceFrame);

	nFrameTransX = trans.x;
	nFrameTransY = trans.y;
	nFrameTransZ = trans.z;
	
    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFrameTransX ;
    _pOut[iReturnCount++] = nFrameTransY ;
    _pOut[iReturnCount++] = nFrameTransZ ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrameScale ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrameScale" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFrameScale ;

	// code for nFrameScale = sbLeap.getFrameScale ( nSinceFrame ) )
	
	const Frame sinceFrame = LeapController->frame((int)nSinceFrame);
	
	nFrameScale.SetNumberValue(workingFrame.scaleFactor(sinceFrame));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFrameScale ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_getFrame ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.getFrame" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nSinceFrame = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nFrameID ;
    S3DX::AIVariable nNumHands ;
    S3DX::AIVariable nNumPointables ;
    S3DX::AIVariable nNumFingers ;
    S3DX::AIVariable nNumTools ;
	S3DX::AIVariable nNumGestures ;

	// code for nFrameID, nNumHands, nNumPointables, nNumFingers, nNumTools = sbLeap.getFrame ( nSinceFrame ) )

	if (nSinceFrame.IsNil()) {
		nSinceFrame = 0;
	}

	Frame queryFrame = LeapController->frame(nSinceFrame);

	if (queryFrame.isValid()) {
		currentFrame = queryFrame;
		nFrameID.SetNumberValue((S3DX::float32)queryFrame.id());
		nNumHands.SetNumberValue((S3DX::float32)queryFrame.hands().count());
		nNumPointables.SetNumberValue((S3DX::float32)queryFrame.pointables().count());
		nNumFingers.SetNumberValue((S3DX::float32)queryFrame.fingers().count());
		nNumTools.SetNumberValue((S3DX::float32)queryFrame.tools().count());
		nNumGestures.SetNumberValue((S3DX::float32)queryFrame.gestures().count());
	} else {
		nFrameID = -1;
	}


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nFrameID ;
    _pOut[iReturnCount++] = nNumHands ;
    _pOut[iReturnCount++] = nNumPointables ;
    _pOut[iReturnCount++] = nNumFingers ;
    _pOut[iReturnCount++] = nNumTools ;
	_pOut[iReturnCount++] = nNumGestures ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}


//
// Controller Functions
//

int Callback_sbLeap_update ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.update" ) ;

    // Output Parameters 
    S3DX::AIVariable nResult ;


#   pragma TODO( write the code for nResult = sbLeap.update (  ) )


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nResult ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_isConnected ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.isConnected" ) ;

    // Output Parameters 
    S3DX::AIVariable bConnected ;

	// code for bConnected = sbLeap.isConnected (  ) )

	bConnected = LeapController->isConnected();

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bConnected ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_removeListener ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.removeListener" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nListenerID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nResult = 0;

	// code for nResult = sbLeap.removeListener ( nListenerID ) )

	for (unsigned int i = 0; i < Listeners.size(); i++) {
		if (Listeners.at(i)->ListenerID == nListenerID) {
			LeapController->removeListener(*Listeners.at(i));
			Listeners.erase(Listeners.begin() + i);
			break;
		}
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nResult ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_AddListener ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.AddListener" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAIModel           = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sEventPrefix       = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nEventReceiverType = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nResult;

	// code for nResult = sbLeap.AddListener ( sAIModel, sEventPrefix, nEventReceiverType ) )

	ShivaListener newListener(sAIModel, sEventPrefix, nEventReceiverType);
	bool bSuccess = LeapController->addListener(newListener);

	if (bSuccess) {
		Listeners.push_back(&newListener);
		nResult = newListener.ListenerID;
	} else {
		nResult = -1;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nResult ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_disconnect ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.disconnect" ) ;

    // Output Parameters 
    S3DX::AIVariable nResult ;

	// code for nResult = sbLeap.disconnect (  ) )

	delete LeapController;
	Listeners.resize(0);
	frameArray.resize(0);

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nResult ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

int Callback_sbLeap_connect ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "sbLeap.connect" ) ;

    // Output Parameters 
    S3DX::AIVariable nResult = 0;

	// code for nResult = sbLeap.connect (  ) )

	LeapController = new Controller;

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nResult ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}


//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

sbLeapPackage::sbLeapPackage ( )
{
#ifdef S3DX_DLL
    sbLeap.pfn_sbLeap_getGestureSwipe         = Callback_sbLeap_getGestureSwipe         ;
    sbLeap.pfn_sbLeap_getGestureCircle        = Callback_sbLeap_getGestureCircle        ;
    sbLeap.pfn_sbLeap_getGestureKeyTap        = Callback_sbLeap_getGestureKeyTap        ;
    sbLeap.pfn_sbLeap_getGestureScreenTap     = Callback_sbLeap_getGestureScreenTap     ;
    sbLeap.pfn_sbLeap_getGesture              = Callback_sbLeap_getGesture              ;
    sbLeap.kGestureStateInvalid  = -1 ; 
    sbLeap.kGestureStateStart    = 0 ; 
    sbLeap.kGestureStateUpdate   = 1 ; 
    sbLeap.kGestureStateStop     = 2 ; 
    sbLeap.kGestureTypeInvalid   = -1 ; 
    sbLeap.pfn_sbLeap_isGestureEnabled        = Callback_sbLeap_isGestureEnabled        ;
    sbLeap.pfn_sbLeap_enableGesture           = Callback_sbLeap_enableGesture           ;
    sbLeap.kGestureTypeSwipe     = 0 ; 
    sbLeap.kGestureTypeCircle    = 1 ; 
    sbLeap.kGestureTypeScreenTap = 2 ; 
    sbLeap.kGestureTypeKeyTap    = 3 ; 
    sbLeap.pfn_sbLeap_getPointableDirection   = Callback_sbLeap_getPointableDirection   ;
    sbLeap.pfn_sbLeap_getFrameTimeStamp      = Callback_sbLeap_getFrameTimeStamp      ;
    sbLeap.pfn_sbLeap_getHand                = Callback_sbLeap_getHand                ;
    sbLeap.pfn_sbLeap_getFrameTool           = Callback_sbLeap_getFrameTool           ;
    sbLeap.pfn_sbLeap_getFramePointable      = Callback_sbLeap_getFramePointable      ;
    sbLeap.pfn_sbLeap_getFrameFinger         = Callback_sbLeap_getFrameFinger         ;
    sbLeap.pfn_sbLeap_setWorkingFrame         = Callback_sbLeap_setWorkingFrame         ;
    sbLeap.pfn_sbLeap_storeFrame              = Callback_sbLeap_storeFrame              ;
    sbLeap.pfn_sbLeap_removeListener          = Callback_sbLeap_removeListener          ;
    sbLeap.pfn_sbLeap_getHandFinger           = Callback_sbLeap_getHandFinger           ;
    sbLeap.pfn_sbLeap_getPalmNormal           = Callback_sbLeap_getPalmNormal           ;
    sbLeap.pfn_sbLeap_getPalmPosition         = Callback_sbLeap_getPalmPosition         ;
    sbLeap.pfn_sbLeap_getPalmVelocity         = Callback_sbLeap_getPalmVelocity         ;
    sbLeap.pfn_sbLeap_getHandDirection        = Callback_sbLeap_getHandDirection        ;
    sbLeap.pfn_sbLeap_getHandRotationAxis     = Callback_sbLeap_getHandRotationAxis     ;
    sbLeap.pfn_sbLeap_getHandRotationAngle    = Callback_sbLeap_getHandRotationAngle    ;
    sbLeap.pfn_sbLeap_getHandScale            = Callback_sbLeap_getHandScale            ;
    sbLeap.pfn_sbLeap_getHandSphereCentre     = Callback_sbLeap_getHandSphereCentre     ;
    sbLeap.pfn_sbLeap_getHandSphereRadius     = Callback_sbLeap_getHandSphereRadius     ;
    sbLeap.pfn_sbLeap_getHandTranslation      = Callback_sbLeap_getHandTranslation      ;
    sbLeap.pfn_sbLeap_getHandTool             = Callback_sbLeap_getHandTool             ;
    sbLeap.pfn_sbLeap_getHandPointable        = Callback_sbLeap_getHandPointable        ;
    sbLeap.pfn_sbLeap_getFrame            = Callback_sbLeap_getFrame            ;
    sbLeap.pfn_sbLeap_getFrameRotationAngle   = Callback_sbLeap_getFrameRotationAngle   ;
    sbLeap.pfn_sbLeap_getFrameRotationAxis    = Callback_sbLeap_getFrameRotationAxis    ;
    sbLeap.pfn_sbLeap_getFrameScale           = Callback_sbLeap_getFrameScale           ;
    sbLeap.pfn_sbLeap_getFrameTranslation     = Callback_sbLeap_getFrameTranslation     ;
    sbLeap.pfn_sbLeap_getPointableLength      = Callback_sbLeap_getPointableLength      ;
    sbLeap.pfn_sbLeap_getPointableWidth       = Callback_sbLeap_getPointableWidth       ;
    sbLeap.pfn_sbLeap_getPointableTipPosition = Callback_sbLeap_getPointableTipPosition ;
    sbLeap.pfn_sbLeap_getPointableTipVelocity = Callback_sbLeap_getPointableTipVelocity ;
    sbLeap.pfn_sbLeap_isFinger                = Callback_sbLeap_isFinger                ;
    sbLeap.pfn_sbLeap_isTool                  = Callback_sbLeap_isTool                  ;
    sbLeap.pfn_sbLeap_isValidPointable        = Callback_sbLeap_isValidPointable        ;
    sbLeap.pfn_sbLeap_isConnected             = Callback_sbLeap_isConnected             ;
    sbLeap.pfn_sbLeap_AddListener             = Callback_sbLeap_AddListener             ;
    sbLeap.pfn_sbLeap_connect    = Callback_sbLeap_connect    ;
    sbLeap.pfn_sbLeap_disconnect = Callback_sbLeap_disconnect ;
    sbLeap.pfn_sbLeap_update     = Callback_sbLeap_update     ;
	
#endif
}

//-----------------------------------------------------------------------------

sbLeapPackage::~sbLeapPackage ( )
{

}

//-----------------------------------------------------------------------------
//  Functions table
//-----------------------------------------------------------------------------

static S3DX::AIFunction aMyFunctions [ ] =
{
    { "getGestureSwipe"        , Callback_sbLeap_getGestureSwipe        , "nPointableID, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ, nSpeed, nStartX, nStartY, nStartZ"                 , "nGestureID"                                           , "Retrieve swipe gesture data for the given gesture ID"                                                                                                                                                                                                                                                                                           , 0 }, 
    { "getGestureCircle"       , Callback_sbLeap_getGestureCircle       , "nPointableID, nNormX, nNormY, nNormZ, nCenterX, nCenterY, nCenterZ, nNumberOfCircleTraces, nRadiusOfCircle", "nGestureID"                                           , "Retrieve circle gesture data for the given gesture ID."                                                                                                                                                                                                                                                                                         , 0 }, 
    { "getGestureKeyTap"       , Callback_sbLeap_getGestureKeyTap       , "nPointableID, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ"                                                    , "nGestureID"                                           , "Retrieve KeyTap gesture data for the given gesture ID."                                                                                                                                                                                                                                                                                         , 0 }, 
    { "getGestureScreenTap"    , Callback_sbLeap_getGestureScreenTap    , "nPointableID, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ"                                                    , "nGestureID"                                           , "Retrieve ScreenTap gesture data for the given gesture ID."                                                                                                                                                                                                                                                                                      , 0 }, 
    { "getGesture"             , Callback_sbLeap_getGesture             , "nGestureID, kGestureType, nDurationInSeconds, kGestureState"              , "nGestureIndex, nFrameIndex"                           , "Retrieves the Gesture ID, type, duration and state of the specified index"                                                                                                                                                                                                                                                                      , 0 }, 
    { "isGestureEnabled"       , Callback_sbLeap_isGestureEnabled       , "bEnabled"                                                   , "kGestureType"                                         , "Reports whether the specified gesture type is enabled."                                                                                                                                                                                                                                                                                         , 0 }, 
    { "enableGesture"          , Callback_sbLeap_enableGesture          , ""                                                           , "kGestureType, bEnable"                                , "Enables or disables reporting of a specified gesture type.\n\nBy default, all gesture types are disabled. When disabled, gestures of the disabled type are never reported and will not appear in the frame gesture list.\n\nAs a performance optimization, only enable recognition for the types of movements that you use in your application.", 0 }, 
    { "getPointableDirection"  , Callback_sbLeap_getPointableDirection  , "nDirX, nDirY, nDirZ"                                        , "nPointableID"                                         , "Retrieves a unit direction vector pointing in the same direction as the pointable"                                                                     , 0 }, 
    { "getFrameTimeStamp"     , Callback_sbLeap_getFrameTimeStamp     , "nFrameTimestamp"                                            , "nFrameIndex"                                          , "Retrieves the elapsed frame capture time since the controller started"                                                                                 , 0 }, 
    { "getHand"               , Callback_sbLeap_getHand               , "nHandID, nNumberOfFingers, nNumberOfTools"                  , "nHandIndex, nFrameIndex"                              , "Retrieves the Hand ID, number of Fingers and number of Tools for the given frame and hand index"                                                       , 0 }, 
    { "getFrameTool"          , Callback_sbLeap_getFrameTool          , "nToolID"                                                    , "nToolIndex, nFrameIndex"                              , "Retrieves the ToolID for a given Frame/Tool index combination"                                                                                         , 0 }, 
    { "getFramePointable"     , Callback_sbLeap_getFramePointable     , "nPointableID"                                               , "nPointableIndex, nFrameIndex"                         , "Retrieves the PointableID for a given Frame/Pointable index combination"                                                                               , 0 }, 
    { "getFrameFinger"        , Callback_sbLeap_getFrameFinger        , "nFingerID"                                                  , "nFingerIndex, nFrameIndex"                            , "Retrieves the Finger ID for a given Frame/Finger index combination"                                                                                    , 0 }, 
    { "setWorkingFrame"        , Callback_sbLeap_setWorkingFrame        , "nResult"                                                    , "nFrameIndex"                                          , "Sets the working frame for other function to the frame from the frame array, or the current frame if index is nil"                                     , 0 }, 
    { "storeFrame"             , Callback_sbLeap_storeFrame             , "nNewFrameIndex"                                             , "nFrameIndex"                                          , "Stores the last retrieved frame in the frame array. If no nFrameIndex is supplied, a new index is created, otherwise an existing entry is overwritten.", 0 }, 
    { "removeListener"         , Callback_sbLeap_removeListener         , "nResult"                                                    , "nListenerID"                                          , "Removes a previously registered listener"                                                                             , 0 }, 
    { "getHandFinger"          , Callback_sbLeap_getHandFinger          , "nFingerID"                                                  , "nHandID, nFingerIndex"                                , "Retrieves the Finger ID for a given Hand/Finger index combination"                                                    , 0 }, 
    { "getPalmNormal"          , Callback_sbLeap_getPalmNormal          , "nNormX, nNormY, nNormZ"                                     , "nHandID"                                              , "Retrieves the Palm normal for a given Hand"                                                                           , 0 }, 
    { "getPalmPosition"        , Callback_sbLeap_getPalmPosition        , "nPosX, nPosY, nPosZ"                                        , "nHandID"                                              , "Retrieves the Palm position in mm from the leap origin for a given Hand"                                              , 0 }, 
    { "getPalmVelocity"        , Callback_sbLeap_getPalmVelocity        , "nVelX, nVelY, nVelZ"                                        , "nHandID"                                              , "Retrieves the Palm velocity in mm/sec for a given Hand"                                                               , 0 }, 
    { "getHandDirection"       , Callback_sbLeap_getHandDirection       , "nDirX, nDirY, nDirZ"                                        , "nHandID"                                              , "Retrieves the Hand direction from the palm to the finger for a given Hand"                                            , 0 }, 
    { "getHandRotationAxis"    , Callback_sbLeap_getHandRotationAxis    , "nAxisX, nAxisY, nAxisZ"                                     , "nHandID, nSinceFrame"                                 , "Retrieves the Hand rotation axis since the last reference frame, for a given Hand"                                    , 0 }, 
    { "getHandRotationAngle"   , Callback_sbLeap_getHandRotationAngle   , "nRotationAngle"                                             , "nHandID, nSinceFrame, nRefAxisX, nRefAxisY, nRefAxisZ", "Retrieves the Hand rotation angle since the last reference frame, optionally from a reference axis, for a given Hand" , 0 }, 
    { "getHandScale"           , Callback_sbLeap_getHandScale           , "nScaleFactor"                                               , "nHandID, nSinceFrame"                                 , "Retrieves the Hand scale factor since the last reference frame, for a given Hand"                                     , 0 }, 
    { "getHandSphereCentre"    , Callback_sbLeap_getHandSphereCentre    , "nCentreX, nCentreY, nCentreZ"                               , "nHandID"                                              , "Retrieves thecentre of a sphere to fit the hand, for a given Hand"                                                    , 0 }, 
    { "getHandSphereRadius"    , Callback_sbLeap_getHandSphereRadius    , "nRadius"                                                    , "nHandID"                                              , "Retrieves the radius of a sphere to fit the hand, for a given Hand"                                                   , 0 }, 
    { "getHandTranslation"     , Callback_sbLeap_getHandTranslation     , "nTransX, nTransY, nTransZ"                                  , "nHandID, nSinceFrame"                                 , "Retrieves the Hand translation since the last reference frame, for a given Hand"                                      , 0 }, 
    { "getHandTool"            , Callback_sbLeap_getHandTool            , "nToolID"                                                    , "nHandID, nToolIndex"                                  , "Retrieves the ToolID for a given Hand/Tool index combination"                                                         , 0 }, 
    { "getHandPointable"       , Callback_sbLeap_getHandPointable       , "nPointableID"                                               , "nHandID, nPointableIndex"                             , "Retrieves the PointableID for a given Hand/Pointable index combination"                                               , 0 }, 
    { "getFrame"           , Callback_sbLeap_getFrame           , "nFrameID, nNumHands, nNumPointables, nNumFingers, nNumTools, nNumGestures", "nSinceFrame"                                  , "Retrieves the Leap frame ID since the last reference frame and the numbers of object of each object type in the frame", 0 }, 
    { "getFrameRotationAngle"  , Callback_sbLeap_getFrameRotationAngle  , "nFrameRotAngle"                                             , "nSinceFrame"                                          , "Retrieves the rotation angle around the rotation axis since the reference frame"                                      , 0 }, 
    { "getFrameRotationAxis"   , Callback_sbLeap_getFrameRotationAxis   , "nFrameRotAxisX, nFrameRotAxisY, nFrameRotAxisZ"             , "nSinceFrame"                                          , "Retrieves the rotation axis since the reference frame"                                                                , 0 }, 
    { "getFrameScale"          , Callback_sbLeap_getFrameScale          , "nFrameScale"                                                , "nSinceFrame"                                          , "Retrieves the frame scale since the reference frame"                                                                  , 0 }, 
    { "getFrameTranslation"    , Callback_sbLeap_getFrameTranslation    , "nFrameTransX, nFrameTransY, nFrameTransZ"                   , "nSinceFrame"                                          , "Retrieves the frame translation since the reference frame"                                                            , 0 }, 
    { "getPointableLength"     , Callback_sbLeap_getPointableLength     , "nLength"                                                    , "nPointableID"                                         , "Retrieves the estimated length of the pointable in mm"                                                                , 0 }, 
    { "getPointableWidth"      , Callback_sbLeap_getPointableWidth      , "nWidth"                                                     , "nPointableID"                                         , "Retrieves the estimated width of the pointable in mm"                                                                 , 0 }, 
    { "getPointableTipPosition", Callback_sbLeap_getPointableTipPosition, "nPosX, nPosY, nPosZ"                                        , "nPointableID"                                         , "Retrieves the tip posiiton from the leap origin,  in mm"                                                              , 0 }, 
    { "getPointableTipVelocity", Callback_sbLeap_getPointableTipVelocity, "nVelX, nVelY, nVelZ"                                        , "nPointableID"                                         , "Retrieves the tip velocity,  in mm/sec"                                                                               , 0 }, 
    { "isFinger"               , Callback_sbLeap_isFinger               , "bFinger"                                                    , "nPointableID"                                         , "Returns true if the pointable is believed to be a finger"                                                             , 0 }, 
    { "isTool"                 , Callback_sbLeap_isTool                 , "bTool"                                                      , "nPointableID"                                         , "Returns true if the pointable is believed to be a tool"                                                               , 0 }, 
    { "isValidPointable"       , Callback_sbLeap_isValidPointable       , "bPointable"                                                 , "nPointableID"                                         , "Returns true if the pointable isa valid pointable object"                                                             , 0 }, 
    { "isConnected"            , Callback_sbLeap_isConnected            , "bConnected"                                                 , ""                                                     , "Returns true if the leap device is connected"                                                                         , 0 }, 
    { "AddListener"            , Callback_sbLeap_AddListener            , "nResult"                                                    , "sAIModel, sEventPrefix, nEventReceiverType"           , "Registers an event listener for leap events. nEventReciever type specifies user or object events."                    , 0 }, 
    { "connect"   , Callback_sbLeap_connect   , "nResult"                                  , ""                               , "Connects to a Leap device"                                                                      , 0 }, 
    { "disconnect", Callback_sbLeap_disconnect, "nResult"                                  , ""                               , "Disconnects from a Leap device"                                                                 , 0 }, 
    { "update"    , Callback_sbLeap_update    , "nResult"                                  , ""                               , "Polls a leap device and issues update events"                                                   , 0 }, 
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
    { "kGestureStateInvalid" , -1, "An invalid state"                                           , 0 }, 
    { "kGestureStateStart"   , 0 , "The gesture is starting"                                    , 0 }, 
    { "kGestureStateUpdate"  , 1 , "The gesture is in progress"                                 , 0 }, 
    { "kGestureStateStop"    , 2 , "The gesture has completed"                                  , 0 }, 
    { "kGestureTypeInvalid"  , -1, "An invalid type"                                            , 0 }, 
    { "kGestureTypeSwipe"    , 0, "A straight line movement by the hand with fingers extended.", 0 }, 
    { "kGestureTypeCircle"   , 1, "A  circular movement by a finger."                          , 0 }, 
    { "kGestureTypeScreenTap", 2, "A forward tapping movement by a finger."                    , 0 }, 
    { "kGestureTypeKeyTap"   , 3, "A downward tapping movement by a finger."                   , 0 }	
    //{ NULL, 0, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Accessors
//-----------------------------------------------------------------------------

const char *sbLeapPackage::GetName ( ) const
{
    return "sbLeap" ;
}

//-----------------------------------------------------------------------------

S3DX::uint32 sbLeapPackage::GetFunctionCount ( ) const
{
	if ( aMyFunctions[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyFunctions ) / sizeof( S3DX::AIFunction ) ;
	}
}

//-----------------------------------------------------------------------------

S3DX::uint32 sbLeapPackage::GetConstantCount ( ) const
{
	if ( aMyConstants[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyConstants ) / sizeof( S3DX::AIConstant ) ;
	}
}

//-----------------------------------------------------------------------------

const S3DX::AIFunction *sbLeapPackage::GetFunctionAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyFunctions[ _iIndex ] ;
}

//-----------------------------------------------------------------------------

const S3DX::AIConstant *sbLeapPackage::GetConstantAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyConstants[ _iIndex ] ;
}
