//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "leapmotion.h"
//-----------------------------------------------------------------------------
#include <memory>
//-----------------------------------------------------------------------------
#include "C_Leap.h"

using namespace std;

unique_ptr<C_Leap> SLM (new C_Leap);


#ifdef S3DX_DLL
	leapmotionAPI leapmotion ;
#endif

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

int Callback_leapmotion_setFingerPitchLimit ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setFingerPitchLimit" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nDegrees = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;


#   pragma TODO( write the code for bOK = leapmotion.setFingerPitchLimit ( nDegrees ) )


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_setFingerYawLimit ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setFingerYawLimit" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nDegrees = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;


#   pragma TODO( write the code for bOK = leapmotion.setFingerYawLimit ( nDegrees ) )


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_setConfidenceLimit ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setConfidenceLimit" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable n0to1 = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->confLimit(n0to1.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_setScreenTapOptions ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setScreenTapOptions" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nMinForwardVelocity = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nHistorySeconds     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nMinDistance        = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->setOptGestureScreentap(nMinForwardVelocity.GetNumberValue(), nHistorySeconds.GetNumberValue(), nMinDistance.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_setSwipeOptions ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setSwipeOptions" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nMinLength   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nMinVelocity = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->setOptGestureSwipe(nMinLength.GetNumberValue(), nMinVelocity.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_setCircleOptions ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setCircleOptions" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nMinRadius = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nMinArc    = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->setOptGestureCircle(nMinRadius.GetNumberValue(), nMinArc.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_setKeyTapOptions ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.setKeyTapOptions" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nMinDownVelocity = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nHistorySeconds  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nMinDistance     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->setOptGestureKeytap(nMinDownVelocity.GetNumberValue(), nHistorySeconds.GetNumberValue(), nMinDistance.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_isInitialized ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.isInitialized" ) ;

    // Output Parameters 
    S3DX::AIVariable bInitialized ;

	bInitialized.SetBooleanValue(SLM->isInit());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bInitialized ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_getDeviceString ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.getDeviceString" ) ;

    // Output Parameters 
    S3DX::AIVariable sDeviceString ;

	sDeviceString.SetStringValue(SLM->getDeviceString());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = sDeviceString ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_allowGestures ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.allowGestures" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
	S3DX::AIVariable bSwipe = (iInputCount < _iInCount) ? _pIn[iInputCount++] : S3DX::AIVariable();
    S3DX::AIVariable bCircle    = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable bScreentap = (iInputCount < _iInCount) ? _pIn[iInputCount++] : S3DX::AIVariable();
    S3DX::AIVariable bKeytap    = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->allowGestures(bSwipe.GetBooleanValue(), bCircle.GetBooleanValue(), bScreentap.GetBooleanValue(), bKeytap.GetBooleanValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_isGestureEnabled ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.isGestureEnabled" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable kGesture = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->isGestureAllowed((int)kGesture.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_shutdown ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.shutdown" ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->shutdown());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_enableGestures ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.enableGestures" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable bEnable = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->enableGestures(bEnable.GetBooleanValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_loop ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.loop" ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->loop());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_init ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.init" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAIName = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->init(sAIName.GetStringValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_leapmotion_useVRMode ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "leapmotion.useVRMode" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable bUseVR = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SLM->useVR(bUseVR.GetBooleanValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

leapmotionPackage::leapmotionPackage ( )
{
#ifdef S3DX_DLL
    leapmotion.pfn_leapmotion_setFingerPitchLimit = Callback_leapmotion_setFingerPitchLimit ;
    leapmotion.pfn_leapmotion_setFingerYawLimit   = Callback_leapmotion_setFingerYawLimit   ;
    leapmotion.pfn_leapmotion_setConfidenceLimit  = Callback_leapmotion_setConfidenceLimit  ;
    leapmotion.pfn_leapmotion_setScreenTapOptions = Callback_leapmotion_setScreenTapOptions ;
    leapmotion.pfn_leapmotion_setSwipeOptions     = Callback_leapmotion_setSwipeOptions     ;
    leapmotion.pfn_leapmotion_setCircleOptions    = Callback_leapmotion_setCircleOptions    ;
    leapmotion.pfn_leapmotion_setKeyTapOptions    = Callback_leapmotion_setKeyTapOptions    ;
    leapmotion.kGestureStateInvalid = -1 ; 
    leapmotion.kGestureStateStart   = 1 ; 
    leapmotion.kGestureStateUpdate  = 2 ; 
    leapmotion.kGestureStateStop    = 3 ; 
    leapmotion.pfn_leapmotion_isInitialized    = Callback_leapmotion_isInitialized    ;
    leapmotion.kBoneMetacarpal   = 0 ; 
    leapmotion.kBoneProximal     = 1 ; 
    leapmotion.kBoneIntermedial  = 2 ; 
    leapmotion.kBoneDistal        = 3 ; 
    leapmotion.kFingerThumb      = 0 ; 
    leapmotion.kFingerIndex      = 1 ; 
    leapmotion.kFingerMiddle     = 2 ; 
    leapmotion.kFingerRing       = 3 ; 
    leapmotion.kFingerPinky      = 4 ; 
    leapmotion.pfn_leapmotion_getDeviceString  = Callback_leapmotion_getDeviceString  ;
    leapmotion.pfn_leapmotion_allowGestures    = Callback_leapmotion_allowGestures    ;
    leapmotion.pfn_leapmotion_isGestureEnabled = Callback_leapmotion_isGestureEnabled ;
    leapmotion.pfn_leapmotion_shutdown       = Callback_leapmotion_shutdown       ;
    leapmotion.pfn_leapmotion_enableGestures = Callback_leapmotion_enableGestures ;
	leapmotion.kGestureSwipe = 1;
	leapmotion.kGestureCircle = 4 ; 
	leapmotion.kGestureScreentap = 5;
    leapmotion.kGestureKeytap = 6 ; 
    leapmotion.pfn_leapmotion_loop      = Callback_leapmotion_loop      ;
    leapmotion.pfn_leapmotion_init      = Callback_leapmotion_init      ;
    leapmotion.pfn_leapmotion_useVRMode = Callback_leapmotion_useVRMode ;
	
#endif
}

//-----------------------------------------------------------------------------

leapmotionPackage::~leapmotionPackage ( )
{

}

//-----------------------------------------------------------------------------
//  Functions table
//-----------------------------------------------------------------------------

static S3DX::AIFunction aMyFunctions [ ] =
{
    { "setFingerPitchLimit", Callback_leapmotion_setFingerPitchLimit, "bOK"          , "nDegrees"                                          , "sets finger pitch range in degrees"         , 0 }, 
    { "setFingerYawLimit"  , Callback_leapmotion_setFingerYawLimit  , "bOK"          , "nDegrees"                                          , "sets finger yaw range in degrees"           , 0 }, 
    { "setConfidenceLimit" , Callback_leapmotion_setConfidenceLimit , "bOK"          , "n0to1"                                             , "hand pose confidence limiter"               , 0 }, 
    { "setScreenTapOptions", Callback_leapmotion_setScreenTapOptions, "bOK"          , "nMinForwardVelocity, nHistorySeconds, nMinDistance", "configures ScreenTap gesture"               , 0 }, 
    { "setSwipeOptions"    , Callback_leapmotion_setSwipeOptions    , "bOK"          , "nMinLength, nMinVelocity"                          , "configures Swipe gesture"                   , 0 }, 
    { "setCircleOptions"   , Callback_leapmotion_setCircleOptions   , "bOK"          , "nMinRadius, nMinArc"                               , "configures Cirlce gesture"                  , 0 }, 
    { "setKeyTapOptions"   , Callback_leapmotion_setKeyTapOptions   , "bOK"          , "nMinDownVelocity, nHistorySeconds, nMinDistance"   , "configures KeyTap gesture"                  , 0 }, 
    { "isInitialized"   , Callback_leapmotion_isInitialized   , "bInitialized" , ""                                    , "checks if the plugins is ready"             , 0 }, 
    { "getDeviceString" , Callback_leapmotion_getDeviceString , "sDeviceString", ""                                    , "Returns the identifier of Leap device 0"    , 0 }, 
    { "allowGestures"   , Callback_leapmotion_allowGestures   , "bOK", "bSwipe, bCircle, bScreentap, bKeytap", "dis/allow certain gestures only"            , 0 }, 
    { "isGestureEnabled", Callback_leapmotion_isGestureEnabled, "bAllowed", "kGesture"                            , "check if a certain gesture is enabled"      , 0 }, 
    { "shutdown"      , Callback_leapmotion_shutdown      , "bOK", ""       , "disconnect Leap device"                     , 0 }, 
    { "enableGestures", Callback_leapmotion_enableGestures, "bOK", "bEnable", "toggle gesture handlers"                    , 0 }, 
    { "loop"     , Callback_leapmotion_loop     , "bOK", ""       , "call every frame to feed tracking events"   , 0 }, 
    { "init"     , Callback_leapmotion_init     , "bOK", "sAIName", "init Leap plugin with communication AI name", 0 }, 
    { "useVRMode", Callback_leapmotion_useVRMode, "bOK", "bUseVR" , "switches between regular and VR modes"      , 0 }    
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
    { "kGestureStateInvalid", -1, "Gesture status"              , 0 }, 
    { "kGestureStateStart"  , 1 , "Gesture status"              , 0 }, 
    { "kGestureStateUpdate" , 2 , "Gesture status"              , 0 }, 
    { "kGestureStateStop"   , 3 , "Gesture status"              , 0 }, 
    { "kBoneMetacarpal"  , 0, "finger bone constant"        , 0 }, 
    { "kBoneProximal"    , 1, "finger bone constant"        , 0 }, 
    { "kBoneIntermedial" , 2, "finger bone constant"        , 0 }, 
    { "kBoneDistal"       , 3, "finger bone constant"        , 0 }, 
    { "kFingerThumb"     , 0, "finger constant"             , 0 }, 
    { "kFingerIndex"     , 1, "finger constant"             , 0 }, 
    { "kFingerMiddle"    , 2, "finger constant"             , 0 }, 
    { "kFingerRing"      , 3, "finger constant"             , 0 }, 
    { "kFingerPinky"     , 4, "finger constant"             , 0 }, 
	{ "kGestureSwipe", 1, "Gesture recognition constant", 0 },
	{ "kGestureCircle", 4, "Gesture recognition constant", 0 }, 
	{ "kGestureScreentap", 5, "Gesture recognition constant", 0 },
	{ "kGestureKeytap", 6, "Gesture recognition constant", 0 }
    //{ NULL, 0, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Accessors
//-----------------------------------------------------------------------------

const char *leapmotionPackage::GetName ( ) const
{
    return "leapmotion" ;
}

//-----------------------------------------------------------------------------

S3DX::uint32 leapmotionPackage::GetFunctionCount ( ) const
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

S3DX::uint32 leapmotionPackage::GetConstantCount ( ) const
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

const S3DX::AIFunction *leapmotionPackage::GetFunctionAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyFunctions[ _iIndex ] ;
}

//-----------------------------------------------------------------------------

const S3DX::AIConstant *leapmotionPackage::GetConstantAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyConstants[ _iIndex ] ;
}
