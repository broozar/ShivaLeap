#pragma once
//-----------------------------------------------------------------------------
#include "Leap.h"
//-----------------------------------------------------------------------------
#include "eigen\Eigen\Dense"
#include "eigen\Eigen\StdVector"
//-----------------------------------------------------------------------------
using namespace std;
using namespace Leap;
//-----------------------------------------------------------------------------
#include <memory>

typedef vector<float> fingerSegmentTRS;
typedef vector<fingerSegmentTRS> fingerSegmentStore;
typedef vector<fingerSegmentStore> fingerStore;
typedef vector<Eigen::Quaternionf, Eigen::aligned_allocator<Eigen::Vector2f> > QuaternionFingers;


class C_Leap {
private:
	// AI stuff
	const char* _sAI = "LeapMotionUser";
	S3DX::AIVariable _hU;
	// target tables for tracking
	float _trackDataL[128];
	float _trackDataR[128];
	// init stuff
	bool _bUseVR = false;
	bool _bUseGestures = false;
	bool _bInitialized = false;
	
	// LEAP stuff
	unique_ptr<Controller> _LeapCon;
	Frame _curFrame;
	GestureList _gestList;
	float _confidence = 0.5f;

	// EIGEN calc
	QuaternionFingers _getFingerQ(Leap::Finger const & finger, float roll);

public:
	C_Leap();
	~C_Leap();
	bool init(const char* ainame);
	bool shutdown();
	bool isInit() const;

	bool loop();

	bool enableGestures(bool bEnable);
	bool allowGestures(bool allowCircle, bool allowSwipe, bool allowScreentap, bool allowKeytap);
	bool isGestureAllowed(int gestureID) const;
	
	bool useVR(bool bEnable);
	const char* getDeviceString() const;

	bool setOptGestureCircle(float nMinRadius, float nMinArc);
	bool setOptGestureSwipe(float nMinLength, float nMinVelocity);
	bool setOptGestureScreentap(float nMinForwardVelocity, float nHistorySeconds, float nMinDistance);
	bool setOptGestureKeytap(float nMinDownVelocity, float nHistorySeconds, float nMinDistance);

	bool confLimit(float nLimit);

};

