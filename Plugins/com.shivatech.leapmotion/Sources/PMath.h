//-----------------------------------------------------------------------------
#ifndef __Pandora_EngineCore_Math_h__
#define __Pandora_EngineCore_Math_h__
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
namespace Pandora { namespace EngineCore
//-----------------------------------------------------------------------------
{
    //-------------------------------------------------------------------------
    //  Constantes (Out of the class because of VC exports problem)
    //-------------------------------------------------------------------------
    const   float   Math_k_fPi              = 3.1415926535897932384626433832795f ;
    const   float   Math_k_f2Pi             = 6.2831853071795864769252867665590f ;
    const   float   Math_k_fPiBy2           = 1.5707963267948966192313216916398f ;
    const   float   Math_k_fPiBy3           = 1.0471975511965977461542144610932f ;
    const   float   Math_k_fPiBy4           = 0.7853981633974483096156608458198f ;
    const   float   Math_k_fPiBy6           = 0.5235987755982988730771072305465f ;
    const   float   Math_k_fPiBy8           = 0.3926990816987241548078304229099f ;

    const   float   Math_k_f1ByPi           = 0.3183098861837906715377675267451f ;
    const   float   Math_k_f1By2            = 0.5f ;
    const   float   Math_k_f1By3            = 0.3333333333333333333333333333333f ;
    const   float   Math_k_f1By4            = 0.25f ;
    const   float   Math_k_f1By6            = 0.1666666666666666666666666666667f ;
    const   float   Math_k_f1By8            = 0.125f ;
    const   float   Math_k_f1By16           = 0.0625f ;
    const   float   Math_k_f1By30           = 0.0333333333333333333333333333333f ;
    const   float   Math_k_f1By32           = 0.03125f ;
    const   float   Math_k_f1By60           = 0.0166666666666666666666666666667f ;
    const   float   Math_k_f1By64           = 0.015625f ;
    const   float   Math_k_f1By127          = 0.0078740157480314960629921259842f ;
    const   float   Math_k_f1By128          = 0.0078125f ;
    const   float   Math_k_f1By255          = 0.0039215686274509803921568627451f ;
    const   float   Math_k_f1By256          = 0.00390625f ;
    const   float   Math_k_f1By511          = 0.0019569471624266f ;
    const   float   Math_k_f1By512          = 0.001953125f ;
    const   float   Math_k_f1By32767        = 0.00003051850947599719f ;
    const   float   Math_k_f1By32768        = 0.000030517578125f ;
    const   float   Math_k_f1By65535        = 0.000015259021897f ;
    const   float   Math_k_f1By65536        = 0.000015258789063f ;

    const   float   Math_k_fEps             = 0.000001f ;
    const   float   Math_k_fSqrEps          = 0.0000000001f ;
    const   float   Math_k_f1MinusEps       = 0.999999f ;
    const   float   Math_k_f1MinusSqrEps    = 0.9999999999f ;

    const   float   Math_k_fMaxFloat        = 3.402823466e+38f ;
    const   float   Math_k_fMinFloat        = 1.175494351e-38f ;
    const   int8    Math_k_iMaxInt8         = 127 ;
    const   int8    Math_k_iMinInt8         = (-128) ;
    const   int16   Math_k_iMaxInt16        = 32767 ;
    const   int16   Math_k_iMinInt16        = (-32767);
    const   int32   Math_k_iMaxInt32        = 2147483647 ;
    const   int32   Math_k_iMinInt32        = (-2147483647 - 1);
    const   int32   Math_k_iMaxUInt8        = 0xff ;
    const   int32   Math_k_iMaxUInt16       = 0xffff ;
    const   int32   Math_k_iMaxUInt32       = 0xffffffff ;

    //-------------------------------------------------------------------------
    class PANDORA_ENGINECORE_API Math
    //-------------------------------------------------------------------------
    {
    public :

        //---------------------------------------------------------------------
        //  Initialisation
        //---------------------------------------------------------------------
                static  bool    Init                        ( ) ;
        inline  static  bool    SupportSSE                  ( ) ;
        inline  static  bool    SupportVFP                  ( ) ;
        inline  static  bool    SupportVFPU                 ( ) ;
        inline  static  bool    SupportNEON                 ( ) ;

        //---------------------------------------------------------------------
        //  Fonctions trigonométriques
        //---------------------------------------------------------------------
        inline  static  float   Cos                         ( float _fValue  ) ;
        inline  static  float   Sin                         ( float _fValue  ) ;
        inline  static  float   Tan                         ( float _fValue  ) ;
        inline  static  void    SinCos                      ( float _fValue, float *_fSin, float *_fCos ) ;
        inline  static  float   ACos                        ( float _fValue  ) ;
        inline  static  float   ASin                        ( float _fValue  ) ;
        inline  static  float   ATan                        ( float _fValue  ) ;
        inline  static  float   ATan2                       ( float _fValue1, float _fValue2 ) ;

        //---------------------------------------------------------------------
        //  Fonctions trigonométriques "rapides" (moindre précision, _fValue compris entre -Pi et Pi)
        //---------------------------------------------------------------------
        inline  static  float   FastCos                     ( float _fValue  ) ; 
        inline  static  float   FastSin                     ( float _fValue  ) ;
        inline  static  void    FastSinCos                  ( float _fValue, float *_fSin, float *_fCos ) ;
        inline  static  float   WrapBetweenMinusPiAndPi     ( float _fValue  ) ;


        //---------------------------------------------------------------------
        //  Fonctions de random
        //---------------------------------------------------------------------
                static  void    SetRandomSeed               ( int32 _iSeed   ) ;
                static  int32   GetRandomSeed               (                ) ;
                static  float   Rand                        (                ) ;
        inline  static  float   Rand                        ( float _fMax    ) ;
        inline  static  float   Rand                        ( float _fMin,
                                                              float _fMax    ) ;

                static  void    SetGaussianRandomSeed       ( int32 _iSeed   ) ;
                static  int32   GetGaussianRandomSeed       (                ) ;
                static  float   GaussianRand                ( float _fCenter,
                                                              float _fRadius ) ;

        //---------------------------------------------------------------------
        //  Fonctions templates
        //---------------------------------------------------------------------
        inline  static  float   Min                         ( float _fValue1, float _fValue2 ) ;
        inline  static  float   Max                         ( float _fValue1, float _fValue2 ) ;
        inline  static  float   Avg                         ( float _fValue1, float _fValue2 ) ;
        inline  static  float   Min                         ( float _fValue1, float _fValue2, float _fValue3 ) ;
        inline  static  float   Max                         ( float _fValue1, float _fValue2, float _fValue3 ) ;
        inline  static  float   Avg                         ( float _fValue1, float _fValue2, float _fValue3 ) ;
        inline  static  float   Min                         ( float _fValue1, float _fValue2, float _fValue3, float _fValue4 ) ;
        inline  static  float   Max                         ( float _fValue1, float _fValue2, float _fValue3, float _fValue4 ) ;
        inline  static  float   Avg                         ( float _fValue1, float _fValue2, float _fValue3, float _fValue4 ) ;
        inline  static  float   Abs                         ( float _fValue ) ;
        inline  static  float   Clamp                       ( float _fValue,  float _fMin,    float _fMax    ) ;
        inline  static  float   Sgn                         ( float _fValue ) ; // returns 1 if > 0, -1 if < 0, 0 if == 0
        inline  static  float   Mad                         ( float _fValue1, float _fValue2, float _fValue3 ) ; // returns _fValue1 x _fValue2 + _fValue3


        //---------------------------------------------------------------------
        //  Fonctions diverses
        //---------------------------------------------------------------------
        inline  static  float   Sqr                         ( float _fValue  ) ;
        inline  static  float   Sqrt                        ( float _fValue  ) ;
        inline  static  float   RSqrt                       ( float _fValue  ) ;
        inline  static  float   Inv                         ( float _fValue  ) ;
        inline  static  float   InvIfNotNull                ( float _fValue  ) ;
        inline  static  bool    IsEqualEps                  ( float _fValue1,
                                                              float _fValue2, float _fEpsilon = Math_k_fEps ) ;
        inline  static  bool    IsNullEps                   ( float _fValue,  float _fEpsilon = Math_k_fEps ) ;
        inline  static  float   DegToRad                    ( float _fValue  ) ;
        inline  static  float   RadToDeg                    ( float _fValue  ) ;
        inline  static  bool    IsPowerOf2                  ( uint32 _iValue ) ;
        inline  static  bool    IsInteger                   ( float _fValue  ) ;
        inline  static  uint32  GetNextPowerOf2             ( uint32 _iValue ) ;
        inline  static  uint32  GetPrevPowerOf2             ( uint32 _iValue ) ;
        inline  static  uint32  GetNearestPowerOf2          ( uint32 _iValue, bool _bPreferBiggest ) ;
        inline  static  float   Ceil                        ( float _fValue  ) ;
        inline  static  float   GetNearestInteger           ( float _fValue  ) ;
        inline  static  float   Round                       ( float _fValue, uint32 _iDecimals ) ;
        inline  static  float   Trunc                       ( float _fValue, uint32 _iDecimals ) ;
        inline  static  float   Floor                       ( float _fValue  ) ;
        inline  static  float   Log                         ( float _fValue  ) ;
        inline  static  float   Log10                       ( float _fValue  ) ;
        inline  static  float   Power                       ( float _fValue, float _fExposant ) ;
        inline  static  float   Mod                         ( float _fValue1,
                                                              float _fValue2 ) ;
        //---------------------------------------------------------------------
        //  Fonctions diverses "rapides"
        //---------------------------------------------------------------------
        inline  static  float   FastSqrt                    ( float _fValue  ) ;
        inline  static  float   FastRSqrt                   ( float _fValue  ) ;

        //---------------------------------------------------------------------
        //  Fonctions d'évaluation de courbes
        //---------------------------------------------------------------------
        inline  static  float   EvaluateBSpline             ( float _fPoint0, float _fPoint1, float _fPoint2, float _fPoint3, float _fFactor ) ;
        inline  static  float   EvaluateBezier              ( float _fPoint0, float _fPoint1, float _fPoint2, float _fPoint3, float _fFactor ) ;
        inline  static  float   EvaluateCatmullRom          ( float _fPoint0, float _fPoint1, float _fPoint2, float _fPoint3, float _fFactor ) ;

                static  float   EvaluateBSpline             ( float *_pPointList, uint32 _iPointCount, float _fFactor ) ; // TODO
                static  float   EvaluateBezier              ( float *_pPointList, uint32 _iPointCount, float _fFactor ) ; // TODO
                static  float   EvaluateCatmullRom          ( float *_pPointList, uint32 _iPointCount, float _fFactor ) ; // TODO

        //---------------------------------------------------------------------
        //  Fonctions diverses
        //---------------------------------------------------------------------
                static  float   Calculate3DPolygonArea      ( float *_pPointList, uint32 _iPointCount ) ;
                static  bool    TestOBBIntersection         ( const float *_pBox0Extents3, const float *_pBox0Position3, const float *_pBox0Basis9, const float *_pBox1Extents3, const float *_pBox1Position3, const float *_pBox1Basis9 ) ;

    private :

        //---------------------------------------------------------------------
        //  Fonctions SIMD
        //---------------------------------------------------------------------
                static  bool    SupportSSE_NotInline        (                ) ; // Fuck VC !!!
                static  bool    SupportVFP_NotInline        (                ) ; // Fuck VC !!!
                static  bool    SupportVFPU_NotInline       (                ) ; // Fuck VC !!!
                static  bool    SupportNEON_NotInline       (                ) ; // Fuck VC !!!
                static  bool    DetectSSE                   (                ) ;
                static  bool    DetectVFP                   (                ) ;
                static  bool    DetectVFPU                  (                ) ;
                static  bool    DetectNEON                  (                ) ;
                //static  float   SqrtSSE                   ( float _fValue  ) ;
                //static  float   RSqrtSSE                  ( float _fValue  ) ;

        //---------------------------------------------------------------------
        //  Fonctions VFPU
        //---------------------------------------------------------------------
            #if PANDORA_PROCESSOR_SUPPORT_VFPU
                static  float   VFPU_Cos                    ( float _fValue  ) ;
                static  float   VFPU_Sin                    ( float _fValue  ) ;
                static  float   VFPU_Tan                    ( float _fValue  ) ;
                static  float   VFPU_ACos                   ( float _fValue  ) ;
                static  float   VFPU_ASin                   ( float _fValue  ) ;
                static  float   VFPU_ATan                   ( float _fValue  ) ;
                static  float   VFPU_ATan2                  ( float _fValue1, float _fValue2 ) ;
                static  float   VFPU_Sqrt                   ( float _fValue  ) ;
                static  float   VFPU_RSqrt                  ( float _fValue  ) ;
            #endif

        //---------------------------------------------------------------------
        //  Variables
        //---------------------------------------------------------------------
                static  bool    bSupportSSE  ; // X86
                static  bool    bSupportVFP  ; // iPhone 3G
                static  bool    bSupportVFPU ; // PSP
                static  bool    bSupportNEON ; // iPhone 3GS

    //-------------------------------------------------------------------------
    } ;
    //-------------------------------------------------------------------------


//-----------------------------------------------------------------------------
} } // Namespace End
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
#include "Math.inl"
//-----------------------------------------------------------------------------
#endif //__Pandora_EngineCore_Math_h__
//-----------------------------------------------------------------------------
