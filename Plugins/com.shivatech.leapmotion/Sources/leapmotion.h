//-----------------------------------------------------------------------------
#ifndef __leapmotion_h__
#define __leapmotion_h__
//-----------------------------------------------------------------------------
#include "S3DXAIPackage.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Package declaration
//-----------------------------------------------------------------------------
class leapmotionPackage : public S3DX::AIPackage
{
public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
	//-------------------------------------------------------------------------

	leapmotionPackage         ( ) ;
                               ~leapmotionPackage         ( ) ;

	//-------------------------------------------------------------------------
    //  Accessors
	//-------------------------------------------------------------------------

    const   char               *GetName             ( ) const ;
            S3DX::uint32        GetFunctionCount    ( ) const ;
            S3DX::uint32        GetConstantCount    ( ) const ;
    const   S3DX::AIFunction   *GetFunctionAt       ( S3DX::uint32 _iIndex ) const ;
    const   S3DX::AIConstant   *GetConstantAt       ( S3DX::uint32 _iIndex ) const ;

} ;

//-----------------------------------------------------------------------------
// Package API declaration
//-----------------------------------------------------------------------------
class leapmotionAPI
{
public :

    //-------------------------------------------------------------------------
    //  API Constructor
	//-------------------------------------------------------------------------
                                leapmotionAPI       ( ) 
                                {
                                    pfn_leapmotion_setFingerPitchLimit = NULL ;
                                    pfn_leapmotion_setFingerYawLimit   = NULL ;
                                    pfn_leapmotion_setConfidenceLimit  = NULL ;
                                    pfn_leapmotion_setScreenTapOptions = NULL ;
                                    pfn_leapmotion_setSwipeOptions     = NULL ;
                                    pfn_leapmotion_setCircleOptions    = NULL ;
                                    pfn_leapmotion_setKeyTapOptions    = NULL ;
                                    pfn_leapmotion_isInitialized    = NULL ;
                                    pfn_leapmotion_getDeviceString  = NULL ;
                                    pfn_leapmotion_allowGestures    = NULL ;
                                    pfn_leapmotion_isGestureEnabled = NULL ;
                                    pfn_leapmotion_shutdown       = NULL ;
                                    pfn_leapmotion_enableGestures = NULL ;
                                    pfn_leapmotion_loop      = NULL ;
                                    pfn_leapmotion_init      = NULL ;
                                    pfn_leapmotion_useVRMode = NULL ;

                                }

	//-------------------------------------------------------------------------
	//  API Callbacks 
	//-------------------------------------------------------------------------

    S3DX::AICallback        pfn_leapmotion_setFingerPitchLimit ;
    S3DX::AICallback        pfn_leapmotion_setFingerYawLimit ;
    S3DX::AICallback        pfn_leapmotion_setConfidenceLimit ;
    S3DX::AICallback        pfn_leapmotion_setScreenTapOptions ;
    S3DX::AICallback        pfn_leapmotion_setSwipeOptions ;
    S3DX::AICallback        pfn_leapmotion_setCircleOptions ;
    S3DX::AICallback        pfn_leapmotion_setKeyTapOptions ;
    S3DX::AICallback        pfn_leapmotion_isInitialized ;
    S3DX::AICallback        pfn_leapmotion_getDeviceString ;
    S3DX::AICallback        pfn_leapmotion_allowGestures ;
    S3DX::AICallback        pfn_leapmotion_isGestureEnabled ;
    S3DX::AICallback        pfn_leapmotion_shutdown ;
    S3DX::AICallback        pfn_leapmotion_enableGestures ;
    S3DX::AICallback        pfn_leapmotion_loop ;
    S3DX::AICallback        pfn_leapmotion_init ;
    S3DX::AICallback        pfn_leapmotion_useVRMode ;

	//-------------------------------------------------------------------------
	//  API Functions 
	//-------------------------------------------------------------------------

    inline S3DX::AIVariable     setFingerPitchLimit ( const S3DX::AIVariable& nDegrees ) { S3DX_DECLARE_VIN_01( nDegrees ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setFingerPitchLimit ) pfn_leapmotion_setFingerPitchLimit ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setFingerYawLimit   ( const S3DX::AIVariable& nDegrees ) { S3DX_DECLARE_VIN_01( nDegrees ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setFingerYawLimit ) pfn_leapmotion_setFingerYawLimit ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setConfidenceLimit  ( const S3DX::AIVariable& n0to1 ) { S3DX_DECLARE_VIN_01( n0to1 ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setConfidenceLimit ) pfn_leapmotion_setConfidenceLimit ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setScreenTapOptions ( const S3DX::AIVariable& nMinForwardVelocity, const S3DX::AIVariable& nHistorySeconds, const S3DX::AIVariable& nMinDistance ) { S3DX_DECLARE_VIN_03( nMinForwardVelocity, nHistorySeconds, nMinDistance ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setScreenTapOptions ) pfn_leapmotion_setScreenTapOptions ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setSwipeOptions     ( const S3DX::AIVariable& nMinLength, const S3DX::AIVariable& nMinVelocity ) { S3DX_DECLARE_VIN_02( nMinLength, nMinVelocity ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setSwipeOptions ) pfn_leapmotion_setSwipeOptions ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setCircleOptions    ( const S3DX::AIVariable& nMinRadius, const S3DX::AIVariable& nMinArc ) { S3DX_DECLARE_VIN_02( nMinRadius, nMinArc ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setCircleOptions ) pfn_leapmotion_setCircleOptions ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setKeyTapOptions    ( const S3DX::AIVariable& nMinDownVelocity, const S3DX::AIVariable& nHistorySeconds, const S3DX::AIVariable& nMinDistance ) { S3DX_DECLARE_VIN_03( nMinDownVelocity, nHistorySeconds, nMinDistance ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_setKeyTapOptions ) pfn_leapmotion_setKeyTapOptions ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     isInitialized    (  ) { S3DX::AIVariable vOut ; if ( pfn_leapmotion_isInitialized ) pfn_leapmotion_isInitialized ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getDeviceString  (  ) { S3DX::AIVariable vOut ; if ( pfn_leapmotion_getDeviceString ) pfn_leapmotion_getDeviceString ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     allowGestures    ( const S3DX::AIVariable& bCircle, const S3DX::AIVariable& bSwipe, const S3DX::AIVariable& bKeytap, const S3DX::AIVariable& bScreentap ) { S3DX_DECLARE_VIN_04( bCircle, bSwipe, bKeytap, bScreentap ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_allowGestures ) pfn_leapmotion_allowGestures ( 4, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     isGestureEnabled ( const S3DX::AIVariable& kGesture ) { S3DX_DECLARE_VIN_01( kGesture ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_isGestureEnabled ) pfn_leapmotion_isGestureEnabled ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     shutdown       (  ) { S3DX::AIVariable vOut ; if ( pfn_leapmotion_shutdown ) pfn_leapmotion_shutdown ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     enableGestures ( const S3DX::AIVariable& bEnable ) { S3DX_DECLARE_VIN_01( bEnable ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_enableGestures ) pfn_leapmotion_enableGestures ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     loop      (  ) { S3DX::AIVariable vOut ; if ( pfn_leapmotion_loop ) pfn_leapmotion_loop ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     init      ( const S3DX::AIVariable& nAIName ) { S3DX_DECLARE_VIN_01( nAIName ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_init ) pfn_leapmotion_init ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     useVRMode ( const S3DX::AIVariable& bUseVR ) { S3DX_DECLARE_VIN_01( bUseVR ) ; S3DX::AIVariable vOut ; if ( pfn_leapmotion_useVRMode ) pfn_leapmotion_useVRMode ( 1, vIn, &vOut ); return vOut ; }

 	//-------------------------------------------------------------------------
	//  API Constants 
	//-------------------------------------------------------------------------

    S3DX::AIVariable kGestureStateInvalid ; 
    S3DX::AIVariable kGestureStateStart ; 
    S3DX::AIVariable kGestureStateUpdate ; 
    S3DX::AIVariable kGestureStateStop ; 
    S3DX::AIVariable kBoneMetacarpal ; 
    S3DX::AIVariable kBoneProximal ; 
    S3DX::AIVariable kBoneIntermedial ; 
    S3DX::AIVariable kBoneDistal ; 
    S3DX::AIVariable kFingerThumb ; 
    S3DX::AIVariable kFingerIndex ; 
    S3DX::AIVariable kFingerMiddle ; 
    S3DX::AIVariable kFingerRing ; 
    S3DX::AIVariable kFingerPinky ; 
    S3DX::AIVariable kGestureCircle ; 
    S3DX::AIVariable kGestureSwipe ; 
    S3DX::AIVariable kGestureKeytap ; 
    S3DX::AIVariable kGestureScreentap ; 

} ;

extern leapmotionAPI leapmotion;

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
