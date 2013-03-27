//-----------------------------------------------------------------------------
#ifndef __sbLeap_h__
#define __sbLeap_h__
//-----------------------------------------------------------------------------
#include "S3DXAIPackage.h"
#include "Leap_SDK\include\Leap.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Package declaration
//-----------------------------------------------------------------------------
class sbLeapPackage : public S3DX::AIPackage
{
public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
	//-------------------------------------------------------------------------

	sbLeapPackage         ( ) ;
                               ~sbLeapPackage         ( ) ;

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
class sbLeapAPI
{
public :

    //-------------------------------------------------------------------------
    //  API Constructor
	//-------------------------------------------------------------------------
                                sbLeapAPI       ( ) 
                                {
                                    pfn_sbLeap_getGestureSwipe         = NULL ;
                                    pfn_sbLeap_getGestureCircle        = NULL ;
                                    pfn_sbLeap_getGestureKeyTap        = NULL ;
                                    pfn_sbLeap_getGestureScreenTap     = NULL ;
                                    pfn_sbLeap_getGesture              = NULL ;
                                    pfn_sbLeap_isGestureEnabled        = NULL ;
                                    pfn_sbLeap_enableGesture           = NULL ;
                                    pfn_sbLeap_getPointableDirection   = NULL ;
                                    pfn_sbLeap_getFrameTimeStamp      = NULL ;
                                    pfn_sbLeap_getHand                = NULL ;
                                    pfn_sbLeap_getFrameTool           = NULL ;
                                    pfn_sbLeap_getFramePointable      = NULL ;
                                    pfn_sbLeap_getFrameFinger         = NULL ;
                                    pfn_sbLeap_setWorkingFrame         = NULL ;
                                    pfn_sbLeap_storeFrame              = NULL ;
                                    pfn_sbLeap_removeListener          = NULL ;
                                    pfn_sbLeap_getHandFinger           = NULL ;
                                    pfn_sbLeap_getPalm                 = NULL ;
                                    pfn_sbLeap_getPalmNormal           = NULL ;
                                    pfn_sbLeap_getPalmPosition         = NULL ;
                                    pfn_sbLeap_getPalmVelocity         = NULL ;
                                    pfn_sbLeap_getHandDirection        = NULL ;
                                    pfn_sbLeap_getHandRotationAxis     = NULL ;
                                    pfn_sbLeap_getHandRotationAngle    = NULL ;
                                    pfn_sbLeap_getHandScale            = NULL ;
                                    pfn_sbLeap_getHandSphereCentre     = NULL ;
                                    pfn_sbLeap_getHandSphereRadius     = NULL ;
                                    pfn_sbLeap_getHandTranslation      = NULL ;
                                    pfn_sbLeap_getHandTool             = NULL ;
                                    pfn_sbLeap_getHandPointable        = NULL ;
                                    pfn_sbLeap_getFrame            = NULL ;
                                    pfn_sbLeap_getFrameRotationAngle   = NULL ;
                                    pfn_sbLeap_getFrameRotationAxis    = NULL ;
                                    pfn_sbLeap_getFrameScale           = NULL ;
                                    pfn_sbLeap_getFrameTranslation     = NULL ;
                                    pfn_sbLeap_getPointableLength      = NULL ;
                                    pfn_sbLeap_getPointableWidth       = NULL ;
                                    pfn_sbLeap_getPointableTipPosition = NULL ;
                                    pfn_sbLeap_getPointableTipVelocity = NULL ;
                                    pfn_sbLeap_isFinger                = NULL ;
                                    pfn_sbLeap_isTool                  = NULL ;
                                    pfn_sbLeap_isValidPointable        = NULL ;
                                    pfn_sbLeap_isConnected             = NULL ;
                                    pfn_sbLeap_AddListener             = NULL ;
                                    pfn_sbLeap_connect    = NULL ;
                                    pfn_sbLeap_disconnect = NULL ;
                                    pfn_sbLeap_update     = NULL ;

                                }

	//-------------------------------------------------------------------------
	//  API Callbacks 
	//-------------------------------------------------------------------------

    S3DX::AICallback        pfn_sbLeap_getGestureSwipe ;
    S3DX::AICallback        pfn_sbLeap_getGestureCircle ;
    S3DX::AICallback        pfn_sbLeap_getGestureKeyTap ;
    S3DX::AICallback        pfn_sbLeap_getGestureScreenTap ;
    S3DX::AICallback        pfn_sbLeap_getGesture ;
    S3DX::AICallback        pfn_sbLeap_isGestureEnabled ;
    S3DX::AICallback        pfn_sbLeap_enableGesture ;
    S3DX::AICallback        pfn_sbLeap_getPointableDirection ;
    S3DX::AICallback        pfn_sbLeap_getFrameTimeStamp ;
    S3DX::AICallback        pfn_sbLeap_getHand ;
    S3DX::AICallback        pfn_sbLeap_getFrameTool ;
    S3DX::AICallback        pfn_sbLeap_getFramePointable ;
    S3DX::AICallback        pfn_sbLeap_getFrameFinger ;
    S3DX::AICallback        pfn_sbLeap_setWorkingFrame ;
    S3DX::AICallback        pfn_sbLeap_storeFrame ;
    S3DX::AICallback        pfn_sbLeap_removeListener ;
    S3DX::AICallback        pfn_sbLeap_getHandFinger ;
    S3DX::AICallback        pfn_sbLeap_getPalm ;
    S3DX::AICallback        pfn_sbLeap_getPalmNormal ;
    S3DX::AICallback        pfn_sbLeap_getPalmPosition ;
    S3DX::AICallback        pfn_sbLeap_getPalmVelocity ;
    S3DX::AICallback        pfn_sbLeap_getHandDirection ;
    S3DX::AICallback        pfn_sbLeap_getHandRotationAxis ;
    S3DX::AICallback        pfn_sbLeap_getHandRotationAngle ;
    S3DX::AICallback        pfn_sbLeap_getHandScale ;
    S3DX::AICallback        pfn_sbLeap_getHandSphereCentre ;
    S3DX::AICallback        pfn_sbLeap_getHandSphereRadius ;
    S3DX::AICallback        pfn_sbLeap_getHandTranslation ;
    S3DX::AICallback        pfn_sbLeap_getHandTool ;
    S3DX::AICallback        pfn_sbLeap_getHandPointable ;
    S3DX::AICallback        pfn_sbLeap_getFrame ;
    S3DX::AICallback        pfn_sbLeap_getFrameRotationAngle ;
    S3DX::AICallback        pfn_sbLeap_getFrameRotationAxis ;
    S3DX::AICallback        pfn_sbLeap_getFrameScale ;
    S3DX::AICallback        pfn_sbLeap_getFrameTranslation ;
    S3DX::AICallback        pfn_sbLeap_getPointableLength ;
    S3DX::AICallback        pfn_sbLeap_getPointableWidth ;
    S3DX::AICallback        pfn_sbLeap_getPointableTipPosition ;
    S3DX::AICallback        pfn_sbLeap_getPointableTipVelocity ;
    S3DX::AICallback        pfn_sbLeap_isFinger ;
    S3DX::AICallback        pfn_sbLeap_isTool ;
    S3DX::AICallback        pfn_sbLeap_isValidPointable ;
    S3DX::AICallback        pfn_sbLeap_isConnected ;
    S3DX::AICallback        pfn_sbLeap_AddListener ;
    S3DX::AICallback        pfn_sbLeap_connect ;
    S3DX::AICallback        pfn_sbLeap_disconnect ;
    S3DX::AICallback        pfn_sbLeap_update ;

	//-------------------------------------------------------------------------
	//  API Functions 
	//-------------------------------------------------------------------------

    inline S3DX::AIVariables<11> getGestureSwipe         ( const S3DX::AIVariable& nGestureID ) { S3DX_DECLARE_VIN_01( nGestureID ) ; S3DX::AIVariables<11> vOut ; if ( pfn_sbLeap_getGestureSwipe ) pfn_sbLeap_getGestureSwipe ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<9> getGestureCircle        ( const S3DX::AIVariable& nGestureID ) { S3DX_DECLARE_VIN_01( nGestureID ) ; S3DX::AIVariables<9> vOut ; if ( pfn_sbLeap_getGestureCircle ) pfn_sbLeap_getGestureCircle ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<7> getGestureKeyTap        ( const S3DX::AIVariable& nGestureID ) { S3DX_DECLARE_VIN_01( nGestureID ) ; S3DX::AIVariables<7> vOut ; if ( pfn_sbLeap_getGestureKeyTap ) pfn_sbLeap_getGestureKeyTap ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<7> getGestureScreenTap     ( const S3DX::AIVariable& nGestureID ) { S3DX_DECLARE_VIN_01( nGestureID ) ; S3DX::AIVariables<7> vOut ; if ( pfn_sbLeap_getGestureScreenTap ) pfn_sbLeap_getGestureScreenTap ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<4> getGesture              ( const S3DX::AIVariable& nGestureIndex, const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_02( nGestureIndex, nFrameIndex ) ; S3DX::AIVariables<4> vOut ; if ( pfn_sbLeap_getGesture ) pfn_sbLeap_getGesture ( 2, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     isGestureEnabled        ( const S3DX::AIVariable& kGestureType ) { S3DX_DECLARE_VIN_01( kGestureType ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_isGestureEnabled ) pfn_sbLeap_isGestureEnabled ( 1, vIn, &vOut ); return vOut ; }
    inline void                 enableGesture           ( const S3DX::AIVariable& kGestureType, const S3DX::AIVariable& bEnable ) { S3DX_DECLARE_VIN_02( kGestureType, bEnable ) ; if ( pfn_sbLeap_enableGesture ) pfn_sbLeap_enableGesture ( 2, vIn, NULL );  }
    inline S3DX::AIVariables<3> getPointableDirection   ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getPointableDirection ) pfn_sbLeap_getPointableDirection ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getFrameTimeStamp      ( const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_01( nFrameIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getFrameTimeStamp ) pfn_sbLeap_getFrameTimeStamp ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getHand                ( const S3DX::AIVariable& nHandIndex, const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_02( nHandIndex, nFrameIndex ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getHand ) pfn_sbLeap_getHand ( 2, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getFrameTool           ( const S3DX::AIVariable& nToolIndex, const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_02( nToolIndex, nFrameIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getFrameTool ) pfn_sbLeap_getFrameTool ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getFramePointable      ( const S3DX::AIVariable& nPointableIndex, const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_02( nPointableIndex, nFrameIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getFramePointable ) pfn_sbLeap_getFramePointable ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getFrameFinger         ( const S3DX::AIVariable& nFingerIndex, const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_02( nFingerIndex, nFrameIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getFrameFinger ) pfn_sbLeap_getFrameFinger ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     setWorkingFrame         ( const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_01( nFrameIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_setWorkingFrame ) pfn_sbLeap_setWorkingFrame ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     storeFrame              ( const S3DX::AIVariable& nFrameIndex ) { S3DX_DECLARE_VIN_01( nFrameIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_storeFrame ) pfn_sbLeap_storeFrame ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     removeListener          ( const S3DX::AIVariable& nListenerID ) { S3DX_DECLARE_VIN_01( nListenerID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_removeListener ) pfn_sbLeap_removeListener ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getHandFinger           ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nFingerIndex ) { S3DX_DECLARE_VIN_02( nHandID, nFingerIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getHandFinger ) pfn_sbLeap_getHandFinger ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<5> getPalm                 ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariables<5> vOut ; if ( pfn_sbLeap_getPalm ) pfn_sbLeap_getPalm ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getPalmNormal           ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getPalmNormal ) pfn_sbLeap_getPalmNormal ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getPalmPosition         ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getPalmPosition ) pfn_sbLeap_getPalmPosition ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getPalmVelocity         ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getPalmVelocity ) pfn_sbLeap_getPalmVelocity ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getHandDirection        ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getHandDirection ) pfn_sbLeap_getHandDirection ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getHandRotationAxis     ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_02( nHandID, nSinceFrame ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getHandRotationAxis ) pfn_sbLeap_getHandRotationAxis ( 2, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getHandRotationAngle    ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nSinceFrame, const S3DX::AIVariable& nRefAxisX, const S3DX::AIVariable& nRefAxisY, const S3DX::AIVariable& nRefAxisZ ) { S3DX_DECLARE_VIN_05( nHandID, nSinceFrame, nRefAxisX, nRefAxisY, nRefAxisZ ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getHandRotationAngle ) pfn_sbLeap_getHandRotationAngle ( 5, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getHandScale            ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_02( nHandID, nSinceFrame ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getHandScale ) pfn_sbLeap_getHandScale ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getHandSphereCentre     ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getHandSphereCentre ) pfn_sbLeap_getHandSphereCentre ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getHandSphereRadius     ( const S3DX::AIVariable& nHandID ) { S3DX_DECLARE_VIN_01( nHandID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getHandSphereRadius ) pfn_sbLeap_getHandSphereRadius ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getHandTranslation      ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_02( nHandID, nSinceFrame ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getHandTranslation ) pfn_sbLeap_getHandTranslation ( 2, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getHandTool             ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nToolIndex ) { S3DX_DECLARE_VIN_02( nHandID, nToolIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getHandTool ) pfn_sbLeap_getHandTool ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getHandPointable        ( const S3DX::AIVariable& nHandID, const S3DX::AIVariable& nPointableIndex ) { S3DX_DECLARE_VIN_02( nHandID, nPointableIndex ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getHandPointable ) pfn_sbLeap_getHandPointable ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<6> getFrame            ( const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_01( nSinceFrame ) ; S3DX::AIVariables<6> vOut ; if ( pfn_sbLeap_getFrame ) pfn_sbLeap_getFrame ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getFrameRotationAngle   ( const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_01( nSinceFrame ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getFrameRotationAngle ) pfn_sbLeap_getFrameRotationAngle ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getFrameRotationAxis    ( const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_01( nSinceFrame ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getFrameRotationAxis ) pfn_sbLeap_getFrameRotationAxis ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getFrameScale           ( const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_01( nSinceFrame ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getFrameScale ) pfn_sbLeap_getFrameScale ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getFrameTranslation     ( const S3DX::AIVariable& nSinceFrame ) { S3DX_DECLARE_VIN_01( nSinceFrame ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getFrameTranslation ) pfn_sbLeap_getFrameTranslation ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     getPointableLength      ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getPointableLength ) pfn_sbLeap_getPointableLength ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getPointableWidth       ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_getPointableWidth ) pfn_sbLeap_getPointableWidth ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getPointableTipPosition ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getPointableTipPosition ) pfn_sbLeap_getPointableTipPosition ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<3> getPointableTipVelocity ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariables<3> vOut ; if ( pfn_sbLeap_getPointableTipVelocity ) pfn_sbLeap_getPointableTipVelocity ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     isFinger                ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_isFinger ) pfn_sbLeap_isFinger ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     isTool                  ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_isTool ) pfn_sbLeap_isTool ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     isValidPointable        ( const S3DX::AIVariable& nPointableID ) { S3DX_DECLARE_VIN_01( nPointableID ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_isValidPointable ) pfn_sbLeap_isValidPointable ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     isConnected             (  ) { S3DX::AIVariable vOut ; if ( pfn_sbLeap_isConnected ) pfn_sbLeap_isConnected ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     AddListener             ( const S3DX::AIVariable& sAIModel, const S3DX::AIVariable& sEventPrefix, const S3DX::AIVariable& nEventReceiverType ) { S3DX_DECLARE_VIN_03( sAIModel, sEventPrefix, nEventReceiverType ) ; S3DX::AIVariable vOut ; if ( pfn_sbLeap_AddListener ) pfn_sbLeap_AddListener ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     connect    (  ) { S3DX::AIVariable vOut ; if ( pfn_sbLeap_connect ) pfn_sbLeap_connect ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     disconnect (  ) { S3DX::AIVariable vOut ; if ( pfn_sbLeap_disconnect ) pfn_sbLeap_disconnect ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     update     (  ) { S3DX::AIVariable vOut ; if ( pfn_sbLeap_update ) pfn_sbLeap_update ( 0, NULL, &vOut ); return vOut ; }

 	//-------------------------------------------------------------------------
	//  API Constants 
	//-------------------------------------------------------------------------

    S3DX::AIVariable kGestureStateInvalid ; 
    S3DX::AIVariable kGestureStateStart ; 
    S3DX::AIVariable kGestureStateUpdate ; 
    S3DX::AIVariable kGestureStateStop ; 
    S3DX::AIVariable kGestureTypeInvalid ; 
    S3DX::AIVariable kGestureTypeSwipe ; 
    S3DX::AIVariable kGestureTypeCircle ; 
    S3DX::AIVariable kGestureTypeScreenTap ; 
    S3DX::AIVariable kGestureTypeKeyTap ; 

} ;

extern sbLeapAPI sbLeap;

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
