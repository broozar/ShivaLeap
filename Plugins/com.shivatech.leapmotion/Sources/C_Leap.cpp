#include "PrecompiledHeader.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
//-----------------------------------------------------------------------------
#include "eigen\Eigen\Dense"
//-----------------------------------------------------------------------------
#include "C_Leap.h"
//-----------------------------------------------------------------------------
#include "Leap.h"

using namespace std;
using namespace Leap;

const float Math_k_fPiBy2 = 1.5707963267948966192313216916398f;
const float Math_k_fPi = 3.141592654f;

//-----------------------------------------------------------------------------
// helpers

QuaternionFingers C_Leap::_getFingerQ(Leap::Finger const & finger, float roll) {
	Eigen::Quaternionf tempMeta;
	Eigen::Quaternionf tempProx;
	Eigen::Quaternionf tempMedi;
	Eigen::Quaternionf tempDist;

	for (int b = 0; b < 4; ++b) {
		auto boneType = static_cast<Bone::Type>(b);
		auto bone = finger.bone(boneType);

		auto bdirL = bone.direction();
		auto bdirZL = bdirL.zAxis();
		
		Eigen::Vector3f bdir(bdirL.x, bdirL.y, bdirL.z);
		Eigen::Vector3f bdirZ(bdirZL.x, bdirZL.y, bdirZL.z);

		Eigen::Quaternionf q, q1;

		Eigen::Matrix3f m;
		m = Eigen::AngleAxisf(roll, Eigen::Vector3f::UnitZ());
		
		q1.setFromTwoVectors(bdirZ, bdir);
		Eigen::Quaternionf q2(m);

		//q = q1;
		q = q1 * q2;
		//q = q2;

		switch (boneType) {
		case Leap::Bone::TYPE_METACARPAL:
			tempMeta = q;
			break;
		case Leap::Bone::TYPE_PROXIMAL:
			tempProx = q;
			break;
		case Leap::Bone::TYPE_INTERMEDIATE:
			tempMedi = q;
			break;
		case Leap::Bone::TYPE_DISTAL:
			tempDist = q;
			break;
		default:
			break;
		}

	}

	return { tempMeta, tempProx, tempMedi, tempDist };
}

//-----------------------------------------------------------------------------
// constructor destructor

C_Leap::C_Leap() {
}

C_Leap::~C_Leap() {
}

//-----------------------------------------------------------------------------
// init shutdown

bool C_Leap::init(const char* ainame) {

	if ((ainame != nullptr) && (ainame != '\0')) _sAI = ainame;
	// default already defined in .h

	_LeapCon = unique_ptr<Controller> (new Controller);
	if (_LeapCon == nullptr) {
		S3DX::log.warning("LEAP: Could not create controller interface.");
		this->shutdown();
		return false;
	}

	// get current ShiVa user
	_hU = S3DX::application.getCurrentUser();
	if (_hU.IsNil()) return false;

	_bInitialized = true;
	return true;
}

bool C_Leap::shutdown() {
	if (_bInitialized) {
		_bInitialized = false;
		_LeapCon = nullptr; // destroy Controller
	}
	return true;
}

bool C_Leap::isInit() const {
	return _bInitialized;
}

const char* C_Leap::getDeviceString() const {
	if (_LeapCon == nullptr) {
		S3DX::log.warning("LEAP: Interface must be initialized first.");
		return "";
	}

	auto dev = (*_LeapCon).devices()[0];

	if (dev.isValid()) return (dev.toString()).c_str();
	return "";
}

//-----------------------------------------------------------------------------
// loop

bool C_Leap::loop() {
	if (!_bInitialized) return false;
	if (_LeapCon == nullptr) return false;
	if (!(*_LeapCon).isConnected()) {
		S3DX::log.warning("LEAP: Device not connected.");
		return false;
	}
	if (!(*_LeapCon).isServiceConnected()) {
		S3DX::log.warning("LEAP: Service not connected.");
		return false;
	}

	// get current ShiVa user
	_hU = S3DX::application.getCurrentUser();
	if (_hU.IsNil()) return false;

	// tracking data snapshot
	_curFrame = (*_LeapCon).frame();

	//-------------------------------------------------------------------------
	// hand handling

	HandList hands = _curFrame.hands();
	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {

		// Get the first hand
		auto hand = *hl;
		//skip if confidence too low
		if (hand.confidence() < _confidence) continue;

		// Get the hand's position, normal vector and direction
		auto ppos = hand.palmPosition();
		auto pnorm = hand.palmNormal();
		auto proll = pnorm.roll();
		auto pdir = hand.direction();
		auto pdirZL = pdir.forward();

		Eigen::Vector3f dir(pdir.x, pdir.y, pdir.z);
		Eigen::Vector3f dirZ(pdirZL.x, pdirZL.y, pdirZL.z);
		
		Eigen::Quaternionf hq;
		hq.setFromTwoVectors(dirZ, dir);

		Eigen::Matrix3f m;
		m = Eigen::AngleAxisf(proll, Eigen::Vector3f::UnitZ());
		Eigen::Quaternionf q2(m);
		hq = hq*q2;

		// Get the Arm bone
		Arm arm = hand.arm();
		auto wpos = arm.wristPosition();
		auto epos = arm.elbowPosition();

		// Get fingers
		auto fingers = hand.fingers();
		QuaternionFingers tempThumb, tempIndex, tempMiddle, tempRing, tempPinky;
		float tempThumbID, tempIndexID, tempMiddleID, tempRingID, tempPinkyID;

		if (hand.isLeft()) {

			// palm
			_trackDataL[0] = (float)hand.id();
			_trackDataL[1] = ppos.x / 1000;
			_trackDataL[2] = ppos.y / 1000;
			_trackDataL[3] = ppos.z / 1000;
			_trackDataL[4] = hq.x();
			_trackDataL[5] = hq.y();
			_trackDataL[6] = hq.z();
			_trackDataL[7] = hq.w();

			_trackDataL[8] = proll;
			_trackDataL[9] = 0;

			// arm
			//_trackDataL[7] = wpos.x / 1000;
			//_trackDataL[8] = wpos.y / 1000;
			//_trackDataL[9] = wpos.z / 1000;
			_trackDataL[10] = epos.x / 1000;
			_trackDataL[11] = epos.y / 1000;
			_trackDataL[12] = epos.z / 1000;

			// fingers
			for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
				auto finger = *fl;
				auto fid = (float) finger.id();
				auto fname = finger.type();

				// Get finger bones
				switch (fname) {
				case Leap::Finger::TYPE_THUMB:
					tempThumb = _getFingerQ(finger, proll);
					tempThumbID = fid;
					break;
				case Leap::Finger::TYPE_INDEX:
					tempIndex = _getFingerQ(finger, proll);
					tempIndexID = fid;
					break;
				case Leap::Finger::TYPE_MIDDLE:
					tempMiddle = _getFingerQ(finger, proll);
					tempMiddleID = fid;
					break;
				case Leap::Finger::TYPE_RING:
					tempRing = _getFingerQ(finger, proll);
					tempRingID = fid;
					break;
				case Leap::Finger::TYPE_PINKY:
					tempPinky = _getFingerQ(finger, proll);
					tempPinkyID = fid;
					break;
				default:
					break;
				}
			} // FOR fingers end

			_trackDataL[13] = tempThumbID;
			_trackDataL[14] = tempThumb[0].w();
			_trackDataL[15] = tempThumb[0].y();
			_trackDataL[16] = tempThumb[0].z();
			_trackDataL[17] = tempThumb[0].w();
			_trackDataL[18] = tempThumb[1].x();
			_trackDataL[19] = tempThumb[1].y();
			_trackDataL[20] = tempThumb[1].z();
			_trackDataL[21] = tempThumb[1].w();
			_trackDataL[22] = tempThumb[2].x();
			_trackDataL[23] = tempThumb[2].y();
			_trackDataL[24] = tempThumb[2].z();
			_trackDataL[25] = tempThumb[2].w();
			_trackDataL[26] = tempThumb[3].x();
			_trackDataL[27] = tempThumb[3].y();
			_trackDataL[28] = tempThumb[3].z();
			_trackDataL[29] = tempThumb[3].w();
			_trackDataL[30] = tempIndexID;
			_trackDataL[31] = tempIndex[0].x();
			_trackDataL[32] = tempIndex[0].y();
			_trackDataL[33] = tempIndex[0].z();
			_trackDataL[34] = tempIndex[0].w();
			_trackDataL[35] = tempIndex[1].x();
			_trackDataL[36] = tempIndex[1].y();
			_trackDataL[37] = tempIndex[1].z();
			_trackDataL[38] = tempIndex[1].w();
			_trackDataL[39] = tempIndex[2].x();
			_trackDataL[40] = tempIndex[2].y();
			_trackDataL[41] = tempIndex[2].z();
			_trackDataL[42] = tempIndex[2].w();
			_trackDataL[43] = tempIndex[3].x();
			_trackDataL[44] = tempIndex[3].y();
			_trackDataL[45] = tempIndex[3].z();
			_trackDataL[46] = tempIndex[3].w();
			_trackDataL[47] = tempMiddleID;
			_trackDataL[48] = tempMiddle[0].x();
			_trackDataL[49] = tempMiddle[0].y();
			_trackDataL[50] = tempMiddle[0].z();
			_trackDataL[51] = tempMiddle[0].w();
			_trackDataL[52] = tempMiddle[1].x();
			_trackDataL[53] = tempMiddle[1].y();
			_trackDataL[54] = tempMiddle[1].z();
			_trackDataL[55] = tempMiddle[1].w();
			_trackDataL[56] = tempMiddle[2].x();
			_trackDataL[57] = tempMiddle[2].y();
			_trackDataL[58] = tempMiddle[2].z();
			_trackDataL[59] = tempMiddle[2].w();
			_trackDataL[60] = tempMiddle[3].x();
			_trackDataL[61] = tempMiddle[3].y();
			_trackDataL[62] = tempMiddle[3].z();
			_trackDataL[63] = tempMiddle[3].w();
			_trackDataL[64] = tempRingID;
			_trackDataL[65] = tempRing[0].x();
			_trackDataL[66] = tempRing[0].y();
			_trackDataL[67] = tempRing[0].z();
			_trackDataL[68] = tempRing[0].w();
			_trackDataL[69] = tempRing[1].x();
			_trackDataL[70] = tempRing[1].y();
			_trackDataL[71] = tempRing[1].z();
			_trackDataL[72] = tempRing[1].w();
			_trackDataL[73] = tempRing[2].x();
			_trackDataL[74] = tempRing[2].y();
			_trackDataL[75] = tempRing[2].z();
			_trackDataL[76] = tempRing[2].w();
			_trackDataL[77] = tempRing[3].x();
			_trackDataL[78] = tempRing[3].y();
			_trackDataL[79] = tempRing[3].z();
			_trackDataL[80] = tempRing[3].w();
			_trackDataL[81] = tempPinkyID;
			_trackDataL[82] = tempPinky[0].x();
			_trackDataL[83] = tempPinky[0].y();
			_trackDataL[84] = tempPinky[0].z();
			_trackDataL[85] = tempPinky[0].w();
			_trackDataL[86] = tempPinky[1].x();
			_trackDataL[87] = tempPinky[1].y();
			_trackDataL[88] = tempPinky[1].z();
			_trackDataL[89] = tempPinky[1].w();
			_trackDataL[90] = tempPinky[2].x();
			_trackDataL[91] = tempPinky[2].y();
			_trackDataL[92] = tempPinky[2].z();
			_trackDataL[93] = tempPinky[2].w();
			_trackDataL[94] = tempPinky[3].x();
			_trackDataL[95] = tempPinky[3].y();
			_trackDataL[96] = tempPinky[3].z();
			_trackDataL[97] = tempPinky[3].w();

			// fill table and send
			auto _trackDataLS = S3DX::table.newInstance();
			for (auto i : _trackDataL) {
				S3DX::table.add(_trackDataLS, i);
			}
			S3DX::user.setAIVariable(_hU, _sAI, "_trackDataL", _trackDataLS);

		}  else {

			// palm
			_trackDataR[0] = (float)hand.id();
			_trackDataR[1] = ppos.x / 1000;
			_trackDataR[2] = ppos.y / 1000;
			_trackDataR[3] = ppos.z / 1000;
			_trackDataR[4] = hq.x();
			_trackDataR[5] = hq.y();
			_trackDataR[6] = hq.z();
			_trackDataR[7] = hq.w();
			_trackDataR[8] = proll;
			_trackDataR[9] = 0;
			// arm
			//_trackDataR[7] = wpos.x / 1000;
			//_trackDataR[8] = wpos.y / 1000;
			//_trackDataR[9] = wpos.z / 1000;
			_trackDataR[10] = epos.x / 1000;
			_trackDataR[11] = epos.y / 1000;
			_trackDataR[12] = epos.z / 1000;

			// fingers
			for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
				auto finger = *fl;
				auto fid = (float) finger.id();
				auto fname = finger.type();

				// Get finger bones
				switch (fname) {
				case Leap::Finger::TYPE_THUMB:
					tempThumb = _getFingerQ(finger, proll);
					tempThumbID = fid;
					break;
				case Leap::Finger::TYPE_INDEX:
					tempIndex = _getFingerQ(finger, proll);
					tempIndexID = fid;
					break;
				case Leap::Finger::TYPE_MIDDLE:
					tempMiddle = _getFingerQ(finger, proll);
					tempMiddleID = fid;
					break;
				case Leap::Finger::TYPE_RING:
					tempRing = _getFingerQ(finger, proll);
					tempRingID = fid;
					break;
				case Leap::Finger::TYPE_PINKY:
					tempPinky = _getFingerQ(finger, proll);
					tempPinkyID = fid;
					break;
				default:
					break;
				}
			} // FOR fingers end

			_trackDataR[13] = tempThumbID;
			_trackDataR[14] = tempThumb[0].x();
			_trackDataR[15] = tempThumb[0].y();
			_trackDataR[16] = tempThumb[0].z();
			_trackDataR[17] = tempThumb[0].w();
			_trackDataR[18] = tempThumb[1].x();
			_trackDataR[19] = tempThumb[1].y();
			_trackDataR[20] = tempThumb[1].z();
			_trackDataR[21] = tempThumb[1].w();
			_trackDataR[22] = tempThumb[2].x();
			_trackDataR[23] = tempThumb[2].y();
			_trackDataR[24] = tempThumb[2].z();
			_trackDataR[25] = tempThumb[2].w();
			_trackDataR[26] = tempThumb[3].x();
			_trackDataR[27] = tempThumb[3].y();
			_trackDataR[28] = tempThumb[3].z();
			_trackDataR[29] = tempThumb[3].w();
			_trackDataR[30] = tempIndexID;
			_trackDataR[31] = tempIndex[0].x();
			_trackDataR[32] = tempIndex[0].y();
			_trackDataR[33] = tempIndex[0].z();
			_trackDataR[34] = tempIndex[0].w();
			_trackDataR[35] = tempIndex[1].x();
			_trackDataR[36] = tempIndex[1].y();
			_trackDataR[37] = tempIndex[1].z();
			_trackDataR[38] = tempIndex[1].w();
			_trackDataR[39] = tempIndex[2].x();
			_trackDataR[40] = tempIndex[2].y();
			_trackDataR[41] = tempIndex[2].z();
			_trackDataR[42] = tempIndex[2].w();
			_trackDataR[43] = tempIndex[3].x();
			_trackDataR[44] = tempIndex[3].y();
			_trackDataR[45] = tempIndex[3].z();
			_trackDataR[46] = tempIndex[3].w();
			_trackDataR[47] = tempMiddleID;
			_trackDataR[48] = tempMiddle[0].x();
			_trackDataR[49] = tempMiddle[0].y();
			_trackDataR[50] = tempMiddle[0].z();
			_trackDataR[51] = tempMiddle[0].w();
			_trackDataR[52] = tempMiddle[1].x();
			_trackDataR[53] = tempMiddle[1].y();
			_trackDataR[54] = tempMiddle[1].z();
			_trackDataR[55] = tempMiddle[1].w();
			_trackDataR[56] = tempMiddle[2].x();
			_trackDataR[57] = tempMiddle[2].y();
			_trackDataR[58] = tempMiddle[2].z();
			_trackDataR[59] = tempMiddle[2].w();
			_trackDataR[60] = tempMiddle[3].x();
			_trackDataR[61] = tempMiddle[3].y();
			_trackDataR[62] = tempMiddle[3].z();
			_trackDataR[63] = tempMiddle[3].w();
			_trackDataR[64] = tempRingID;
			_trackDataR[65] = tempRing[0].x();
			_trackDataR[66] = tempRing[0].y();
			_trackDataR[67] = tempRing[0].z();
			_trackDataR[68] = tempRing[0].w();
			_trackDataR[69] = tempRing[1].x();
			_trackDataR[70] = tempRing[1].y();
			_trackDataR[71] = tempRing[1].z();
			_trackDataR[72] = tempRing[1].w();
			_trackDataR[73] = tempRing[2].x();
			_trackDataR[74] = tempRing[2].y();
			_trackDataR[75] = tempRing[2].z();
			_trackDataR[76] = tempRing[2].w();
			_trackDataR[77] = tempRing[3].x();
			_trackDataR[78] = tempRing[3].y();
			_trackDataR[79] = tempRing[3].z();
			_trackDataR[80] = tempRing[3].w();
			_trackDataR[81] = tempPinkyID;
			_trackDataR[82] = tempPinky[0].x();
			_trackDataR[83] = tempPinky[0].y();
			_trackDataR[84] = tempPinky[0].z();
			_trackDataR[85] = tempPinky[0].w();
			_trackDataR[86] = tempPinky[1].x();
			_trackDataR[87] = tempPinky[1].y();
			_trackDataR[88] = tempPinky[1].z();
			_trackDataR[89] = tempPinky[1].w();
			_trackDataR[90] = tempPinky[2].x();
			_trackDataR[91] = tempPinky[2].y();
			_trackDataR[92] = tempPinky[2].z();
			_trackDataR[93] = tempPinky[2].w();
			_trackDataR[94] = tempPinky[3].x();
			_trackDataR[95] = tempPinky[3].y();
			_trackDataR[96] = tempPinky[3].z();
			_trackDataR[97] = tempPinky[3].w();

			// fill table and send
			auto _trackDataRS = S3DX::table.newInstance();
			for (auto i : _trackDataR) {
				S3DX::table.add(_trackDataRS, i);
			}
			S3DX::user.setAIVariable(_hU, _sAI, "_trackDataR", _trackDataRS);
		}

	} // for HANDS end


	//-------------------------------------------------------------------------
	// tool handling
	auto tools = _curFrame.tools();

	for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
		auto tool = *tl;
		auto tpos = tool.tipPosition();
		auto tdir = tool.direction();

		S3DX::user.sendEventImmediate(
			_hU,
			_sAI,
			"onTool",
			(float)tool.id(),
			tpos.x / 1000,
			tpos.y / 1000,
			tpos.z / 1000,
			tdir.x,
			tdir.y,
			tdir.z
			);
	} // for TOOLS end

	//-------------------------------------------------------------------------
	// gesture handling
	_gestList = _curFrame.gestures();

	for (int g = 0; g < _gestList.count(); ++g) {

		Gesture gesture = _gestList[g];
		switch (gesture.type()) {

		case Gesture::TYPE_CIRCLE: {
			CircleGesture circle = gesture;

			// Calculate angle swept since last frame
			float sweptAngle = 0;
			if (circle.state() != Gesture::STATE_START) {
				CircleGesture previousUpdate = CircleGesture((*_LeapCon).frame(1).gesture(circle.id()));
				sweptAngle = ((circle.progress() - previousUpdate.progress()) * 2 * PI) * RAD_TO_DEG;
			}

			// Calculate counter/clockwiseness
			bool cw = false;
			if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) cw = true;

			S3DX::user.sendEventImmediate(
				_hU,
				_sAI,
				"onGestureCircle",
				(float)gesture.id(),
				(float)gesture.state(),
				circle.progress(),
				circle.radius(),
				sweptAngle,
				cw
				);
			break;
		}

		case Gesture::TYPE_SWIPE: {
			SwipeGesture swipe = gesture;
			S3DX::user.sendEventImmediate(
				_hU,
				_sAI,
				"onGestureSwipe",
				(float)gesture.id(),
				(float)gesture.state(),
				(float)swipe.direction().x,
				(float)swipe.direction().y,
				(float)swipe.direction().z,
				swipe.speed()
				);
			break;
		}

		case Gesture::TYPE_KEY_TAP: {
			KeyTapGesture tap = gesture;
			S3DX::user.sendEventImmediate(
				_hU,
				_sAI,
				"onGestureKeytap",
				(float)gesture.id(),
				(float)gesture.state(),
				(float)tap.position().x,
				(float)tap.position().y,
				(float)tap.position().z,
				(float)tap.direction().x,
				(float)tap.direction().y,
				(float)tap.direction().z
				);
			break;
		}

		case Gesture::TYPE_SCREEN_TAP: {
			ScreenTapGesture screentap = gesture;
			S3DX::user.sendEventImmediate(
				_hU,
				_sAI,
				"onGestureScreentap",
				(float)gesture.id(),
				(float)gesture.state(),
				(float)screentap.position().x,
				(float)screentap.position().y,
				(float)screentap.position().z,
				(float)screentap.direction().x,
				(float)screentap.direction().y,
				(float)screentap.direction().z
				);
			break;
		}

		} // switch end
	} // for GESTURE end

	return true;
}

//-----------------------------------------------------------------------------
// options

bool C_Leap::enableGestures(bool bEnable) {
	if (!_bInitialized) return false;

	return true;
}

bool C_Leap::useVR(bool bEnable) {
	if (!_bInitialized) return false;

	return true;
}

bool C_Leap::allowGestures(bool allowCircle, bool allowSwipe, bool allowScreentap, bool allowKeytap) {
	if (!_bInitialized) return false;
	if (_LeapCon == nullptr) return false;
	
	(*_LeapCon).enableGesture(Gesture::TYPE_SWIPE, allowSwipe);
	(*_LeapCon).enableGesture(Gesture::TYPE_CIRCLE, allowCircle);
	(*_LeapCon).enableGesture(Gesture::TYPE_SCREEN_TAP, allowScreentap);
	(*_LeapCon).enableGesture(Gesture::TYPE_KEY_TAP, allowKeytap);

	return true;
}

bool C_Leap::isGestureAllowed(int gestureID) const {
	if (!_bInitialized) return false;
	if (_LeapCon == nullptr) return false;
	
	return (*_LeapCon).isGestureEnabled((Gesture::Type) gestureID);
}

bool C_Leap::setOptGestureCircle(float nMinRadius, float nMinArc) {
	if (_LeapCon == nullptr) return false;

	(*_LeapCon).config().setFloat("Gesture.Circle.MinRadius", nMinRadius);
	(*_LeapCon).config().setFloat("Gesture.Circle.MinArc", nMinArc);
	(*_LeapCon).config().save();

	return true;
};
bool C_Leap::setOptGestureSwipe(float nMinLength, float nMinVelocity) {
	if (_LeapCon == nullptr) return false;

	(*_LeapCon).config().setFloat("Gesture.Swipe.MinLength", nMinLength);
	(*_LeapCon).config().setFloat("Gesture.Swipe.MinVelocity", nMinVelocity);
	(*_LeapCon).config().save();

	return true;
};
bool C_Leap::setOptGestureScreentap(float nMinForwardVelocity, float nHistorySeconds, float nMinDistance) {
	if (_LeapCon == nullptr) return false;

	(*_LeapCon).config().setFloat("Gesture.ScreenTap.MinForwardVelocity", nMinForwardVelocity);
	(*_LeapCon).config().setFloat("Gesture.ScreenTap.HistorySeconds", nHistorySeconds);
	(*_LeapCon).config().setFloat("Gesture.ScreenTap.MinDistance", nMinDistance);
	(*_LeapCon).config().save();

	return true;
};
bool C_Leap::setOptGestureKeytap(float nMinDownVelocity, float nHistorySeconds, float nMinDistance) {
	if (_LeapCon == nullptr) return false;

	(*_LeapCon).config().setFloat("Gesture.KeyTap.MinDownVelocity", nMinDownVelocity);
	(*_LeapCon).config().setFloat("Gesture.KeyTap.HistorySeconds", nHistorySeconds);
	(*_LeapCon).config().setFloat("Gesture.KeyTap.MinDistance", nMinDistance);
	(*_LeapCon).config().save();

	return true;
};

bool C_Leap::confLimit(float nLimit) {
	if (_LeapCon == nullptr) return false;

	if (nLimit <=1 && nLimit > 0) _confidence = nLimit;

	return true;
}
