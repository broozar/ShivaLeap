//-----------------------------------------------------------------------------
#ifndef __Pandora_EngineCore_Quaternion_h__
#define __Pandora_EngineCore_Quaternion_h__
//-----------------------------------------------------------------------------
#include "Leap.h"

typedef Leap::Vector Vector3;
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
class Quaternion
	//-------------------------------------------------------------------------
{
public:

	//---------------------------------------------------------------------
	//  Construction
	//---------------------------------------------------------------------
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(const float *_pValues);

	//---------------------------------------------------------------------
	//  Opérateurs de cast
	//---------------------------------------------------------------------
	inline              operator float * ();
	inline              operator const float * () const;

	//---------------------------------------------------------------------
	//  Opérateurs binaires
	//---------------------------------------------------------------------
	inline  Quaternion  operator *      (const Quaternion &_qQuaternion) const;
	inline  Quaternion  operator +      (const Quaternion &_qQuaternion) const;
	inline  Quaternion  operator -      (const Quaternion &_qQuaternion) const;
	inline  Quaternion  operator *      (float       _fScalar) const;
	inline  Quaternion  operator /      (float       _fScalar) const;

	//---------------------------------------------------------------------
	//  Opérateurs d'assignation
	//---------------------------------------------------------------------
	inline  Quaternion &operator *=     (const Quaternion &_qQuaternion);
	inline  Quaternion &operator *=     (float       _fScalar);
	inline  Quaternion &operator /=     (float       _fScalar);

	//---------------------------------------------------------------------
	//  Methods
	//---------------------------------------------------------------------
	inline  Quaternion &Normalize();
	inline  Quaternion &Neg();
	inline  Quaternion &Invert();
	inline  float       Magnitude() const;
	inline  float       SqrMagnitude() const;
	inline  Quaternion  GetInverse() const;
	inline  Quaternion  GetConjugate() const;
	inline  Quaternion &SetNeutral();
	inline  Quaternion &Set(float _x, float _y, float _z, float _w);
	Quaternion &SetAxisAngle(const Vector3 &_vAxis, float  _fAngle);
	bool        GetAxisAngle(Vector3 &_vAxis, float &_fAngle) const;
	Quaternion &SetAxis(const Vector3 &_vXAxis, const Vector3 &_vYAxis, const Vector3 &_vZAxis);
	Quaternion &SetAngles(float _x, float _y, float _z);
	inline  Quaternion &SetAngles(const Vector3 &_vAngles);
	bool        GetAngles(Vector3 &_vAngles) const;
	//Quaternion &SetVector       ( const Vector3 &_vVector ) ;
	Quaternion &SetYawPitchRoll(float  _fYaw, float  _fPitch, float  _fRoll);
	bool        GetYawPitchRoll(float &_fYaw, float &_fPitch, float &_fRoll) const;
	inline  Vector3     GetXAxis() const;
	inline  Vector3     GetYAxis() const;
	inline  Vector3     GetZAxis() const;
	inline  bool        IsNeutral() const;
	inline  bool        IsNeutralEps() const;
	inline  bool        IsNormalizedEps() const;
	inline  Vector3     TransformVector(const Vector3 &_vVector) const;
	inline  Quaternion &Lerp(const Quaternion &_qSrcQuaternion,
		const Quaternion &_qDstQuaternion,
		float       _fFactor);
	inline  Quaternion &Slerp(const Quaternion &_qSrcQuaternion,
		const Quaternion &_qDstQuaternion,
		float       _fFactor);
	inline  void        Scale(float       _fFactor);
	inline  bool        IsEqualTo(const Quaternion &_qQuaternion, float _fEpsilon = Math_k_fEps) const;
	inline  Quaternion &Round(uint32 _iDecimals);

	void        Compress(int16 &_x, int16 &_y, int16 &_z, bool _bAdaptative) const;
	void        Uncompress(int16  _x, int16  _y, int16  _z, bool _bAdaptative);

	//---------------------------------------------------------------------
	//  Debug
	//---------------------------------------------------------------------
	void        DebugPrint() const;


	//---------------------------------------------------------------------
	//  Variables
	//---------------------------------------------------------------------
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};

		float xyzw[4];
	};


	//-------------------------------------------------------------------------
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Structure version, for unions...
//-------------------------------------------------------------------------
struct SQuaternion {
	inline          Quaternion &AsQuaternion() { return (Quaternion &)*this; }
	inline  const   Quaternion &AsQuaternion() const { return (const Quaternion &)*this; }

	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};

		float xyzw[4];
	};
};

//-----------------------------------------------------------------------------
#include "Quaternion.inl"
//-----------------------------------------------------------------------------
#endif //__Pandora_EngineCore_Quaternion_h__
//-----------------------------------------------------------------------------
