//-----------------------------------------------------------------------------
#ifndef __Pandora_EngineCore_Math_inl__
#define __Pandora_EngineCore_Math_inl__
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace Pandora { namespace EngineCore
//-----------------------------------------------------------------------------
{

    //-------------------------------------------------------------------------

    inline bool Math::SupportSSE ( )
    {
        #if PANDORA_PROCESSOR_SUPPORT_SSE
        #   if (PANDORA_PLATFORM == PANDORA_PLATFORM_MACOS)
                return true ; // Always true on Intel Macs
        #   elif defined(PANDORA_ENGINECORE_EXPORTS)
                return bSupportSSE ; // When called from the DLL
        #   else
                return SupportSSE_NotInline ( ) ; // When called from another DLL
        #   endif
        #else
            return false ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline bool Math::SupportVFP ( )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFP
        #   if defined(PANDORA_ENGINECORE_EXPORTS)
                return bSupportVFP ; // When called from the DLL
        #   else
                return SupportVFP_NotInline ( ) ; // When called from another DLL
        #   endif
        #else
            return false ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline bool Math::SupportVFPU ( )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        #   if defined(PANDORA_ENGINECORE_EXPORTS)
                return bSupportVFPU ; // When called from the DLL
        #   else
                return SupportVFPU_NotInline ( ) ; // When called from another DLL
        #   endif
        #else
            return false ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline bool Math::SupportNEON ( )
    {
        #if PANDORA_PROCESSOR_SUPPORT_NEON
        #   if defined(PANDORA_ENGINECORE_EXPORTS)
                return bSupportNEON ; // When called from the DLL
        #   else
                return SupportNEON_NotInline ( ) ; // When called from another DLL
        #   endif
        #else
            return false ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Cos ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_Cos ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::cosf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return cosf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------
    
    inline float Math::Sin ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_Sin ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::sinf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return sinf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Tan ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_Tan ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::tanf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return tanf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline void Math::SinCos ( float _fValue, float *_fSin, float *_fCos )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)
        XMScalarSinCos ( _fSin, _fCos, _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        Vectormath::floatInVec x ( _fValue ) ; 
        Vectormath::floatInVec s ; 
        Vectormath::floatInVec c ; 
        Vectormath::sincosf  ( x, &s, &c ) ;
        *_fSin = s.getAsFloat ( ) ;
        *_fCos = c.getAsFloat ( ) ;
        #else
        *_fSin = sinf ( _fValue ) ;
        *_fCos = cosf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::ACos ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_ACos ( _fValue ) ;
        #else
        return acosf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------
    
    inline float Math::ASin ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_ASin ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::asinf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return asinf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::ATan ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_ATan ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::atanf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return atanf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::ATan2 ( float _fValue1, float _fValue2 )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_ATan2 ( _fValue1, _fValue2 ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::atan2f ( Vectormath::floatInVec( _fValue1 ), Vectormath::floatInVec( _fValue2 ) ).getAsFloat ( ) ;
        #else
        return atan2f ( _fValue1, _fValue2 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Sqr ( float _fValue )
    {
        return _fValue * _fValue ;
    }
    
    //-------------------------------------------------------------------------

    inline float Math::Sqrt ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_Sqrt ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::sqrtf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return sqrtf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::RSqrt ( float _fValue )
    {
        #if PANDORA_PROCESSOR_SUPPORT_VFPU
        return VFPU_RSqrt ( _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return ( _fValue > +0.0f ) ? Vectormath::rsqrtf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) : 0.0f ; // FIXME: in case (_fValue <= 0), we should return +Inf to be mathematically correct...
        #else
        const float s = sqrtf ( _fValue ) ;
        return    ( s > +0.0f ) ? ( 1.0f / s ) : 0.0f ; // FIXME: in case (s <= 0), we should return +Inf to be mathematically correct...
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::FastSqrt ( float _fValue )
    {
        // TODO : does it work on other processors ?
        //
        #if (PANDORA_PROCESSOR == PANDORA_PROCESSOR_X86)
            // Newton based method
            //
            float xhalf = 0.5f *  _fValue ;                                 // compute half value
            int   i     = *(int*)&_fValue ;                                 // get bits for floating value 
            i           = 0x5f375a86 - ( i >> 1 ) ;                         // gives initial guess y0 
            _fValue     = *(float*)&i ;                                     // convert bits back to float 
            _fValue     = _fValue * ( 1.5f - xhalf * _fValue * _fValue ) ;  // Newton step, repeating increases accuracy 
            return      ( 1.0f / _fValue ) ;
        #else
            return Sqrt ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::FastRSqrt ( float _fValue )
    {
        // TODO : does it work on other processors ?
        //
        #if (PANDORA_PROCESSOR == PANDORA_PROCESSOR_X86)
            // Newton based method
            //
            float xhalf = 0.5f *  _fValue ;                                 // compute half value
            int   i     = *(int*)&_fValue ;                                 // get bits for floating value 
            i           = 0x5f375a86 - ( i >> 1 ) ;                         // gives initial guess y0 
            _fValue     = *(float*)&i ;                                     // convert bits back to float 
            _fValue     = _fValue * ( 1.5f - xhalf * _fValue * _fValue ) ;  // Newton step, repeating increases accuracy 
            return        _fValue ;
        #else
            return RSqrt ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Abs ( float _fValue )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)    \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return ( _fValue > 0.0f ) ? _fValue : ( - _fValue ) ;
        #else
        return fabsf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------
    
    inline float Math::Inv ( float _fValue )
    {
        assert ( _fValue != 0 ) ;

        return 1.0f / _fValue ;
    }

    //-------------------------------------------------------------------------

    inline bool Math::IsEqualEps ( float _fValue1, float _fValue2, float _fEpsilon )
    {
        return Abs( _fValue1 - _fValue2 ) < _fEpsilon ;
    }

    //-------------------------------------------------------------------------

    inline bool Math::IsNullEps ( float _fValue, float _fEpsilon )
    {
        return IsEqualEps ( _fValue, 0.0f, _fEpsilon ) ;
    }

    //-------------------------------------------------------------------------
    
    inline float Math::InvIfNotNull ( float _fValue )
    {
        return IsNullEps ( _fValue ) ? 0.0f : ( 1.0f / _fValue ) ;
    }

    //-------------------------------------------------------------------------

    inline float Math::DegToRad ( float _fValue )
    {
        return _fValue * 0.017453292519943295769236907684886f ;
    }

    //-------------------------------------------------------------------------
    
    inline float Math::RadToDeg ( float _fValue )
    {
        return _fValue * 57.295779513082320876798154814105f ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Rand ( float _fMax )
    {
        return ( Rand ( ) * _fMax ) ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Rand ( float _fMin, float _fMax )
    {
        return Math::IsEqualEps( _fMax, _fMin ) ? _fMin : ( _fMin + ( Rand ( ) * ( _fMax - _fMin ) ) ) ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Min ( float _fValue1, float _fValue2 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return ( _fValue1 < _fValue2 ) ? _fValue1 : _fValue2 ;
        #else
        return fminf ( _fValue1, _fValue2 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Max ( float _fValue1, float _fValue2 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return ( _fValue1 > _fValue2 ) ? _fValue1 : _fValue2 ;
        #else
        return fmaxf ( _fValue1, _fValue2 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Avg ( float _fValue1, float _fValue2 )
    {
        return ( _fValue1 + _fValue2 ) * 0.5f ;
    }  

    //-------------------------------------------------------------------------

    inline float Math::Min ( float _fValue1, float _fValue2, float _fValue3 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)
        return ( _fValue1 < _fValue2 ) ? Min ( _fValue1, _fValue3 ) : Min ( _fValue2, _fValue3 ) ;
        #else
        return fminf ( fminf ( _fValue1, _fValue2 ), _fValue3 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Max ( float _fValue1, float _fValue2, float _fValue3 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return ( _fValue1 > _fValue2 ) ? Max ( _fValue1, _fValue3 ) : Max ( _fValue2, _fValue3 ) ;
        #else
        return fmaxf ( fmaxf ( _fValue1, _fValue2 ), _fValue3 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Avg ( float _fValue1, float _fValue2, float _fValue3 )
    {
        return ( _fValue1 + _fValue2 + _fValue3 ) * Math_k_f1By3 ;
    }        

    //-------------------------------------------------------------------------

    inline float Math::Min ( float _fValue1, float _fValue2, float _fValue3, float _fValue4 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return Min ( Min ( _fValue1, _fValue2 ), Min ( _fValue3, _fValue4 ) ) ;
        #else
        return fminf ( fminf ( fminf ( _fValue1, _fValue2 ), _fValue3 ), _fValue4 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Max ( float _fValue1, float _fValue2, float _fValue3, float _fValue4 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return Max ( Max ( _fValue1, _fValue2 ), Max ( _fValue3, _fValue4 ) ) ;
        #else
        return fmaxf ( fmaxf ( fmaxf ( _fValue1, _fValue2 ), _fValue3 ), _fValue4 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Avg ( float _fValue1, float _fValue2, float _fValue3, float _fValue4 )
    {
        return ( _fValue1 + _fValue2 + _fValue3 + _fValue4 ) * Math_k_f1By4 ;
    }        

    //-------------------------------------------------------------------------
     
    inline float Math::Clamp ( float _fValue, float _fMin, float _fMax )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_WIN32)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WINRT)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_XB1)          \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_AIRPLAY)      \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_BLACKBERRY)   \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_FLASH)        \
        ||  (PANDORA_PLATFORM == PANDORA_PLATFORM_WP7)
        return ( _fValue > _fMin ) ? ( ( _fValue < _fMax ) ? _fValue : _fMax ) : _fMin ;
        #else
        return fminf ( fmaxf ( _fValue, _fMin ), _fMax ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Sgn ( float _fValue )
    {
        return (_fValue > 0.0f ) ? 1.0f : ( (_fValue < 0.0f ) ? -1.0f : 0.0f ) ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Mad ( float _fValue1, float _fValue2, float _fValue3 )
    {
        #if defined(FP_FAST_FMAF)
        return fmaf ( _fValue1, _fValue2, _fValue3 ) ;
        #else
        return _fValue1 * _fValue2 + _fValue3 ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline bool Math::IsPowerOf2 ( uint32 _iValue )
    {
        if ( _iValue  < 1 ) return false ;
        if ( _iValue == 1 ) return true  ;

        if ( _iValue & ( _iValue - 1 ) ) 
        {
            return false ;
        }

        return true ;
    }

    //-------------------------------------------------------------------------

    inline bool Math::IsInteger ( float _fValue )
    {
        return ( _fValue > 0 ) ? ( Math::Abs ( _fValue - Math::Floor ( _fValue ) ) < Math_k_fEps ) 
                               : ( Math::Abs ( _fValue - Math::Ceil  ( _fValue ) ) < Math_k_fEps ) ;
    }

    //-------------------------------------------------------------------------

    inline uint32 Math::GetNextPowerOf2 ( uint32 _iValue )
    {
        uint32 i = 2 ;

        while ( ( i > 0 ) && ( i <= _iValue ) )
        {
            i <<= 1 ;
        }

        return i ;
    }

    //-------------------------------------------------------------------------

    inline uint32 Math::GetPrevPowerOf2 ( uint32 _iValue )
    {
        uint32 i = 2 ;

        while ( ( i > 0 ) && ( i < _iValue )) 
        {
            i <<= 1 ;
        }

        return i >> 1 ;
    }

    //-------------------------------------------------------------------------

    inline uint32 Math::GetNearestPowerOf2 ( uint32 _iValue, bool _bPreferBiggest )
    {
        if ( IsPowerOf2 ( _iValue ) ) return _iValue ;
        
        uint32 iPrev = GetPrevPowerOf2 ( _iValue ) ;
        uint32 iNext = GetNextPowerOf2 ( _iValue ) ;

        if ( _bPreferBiggest )  return ( _iValue - iPrev >= iNext - _iValue ) ? iNext : iPrev ;
        else                    return ( _iValue - iPrev >  iNext - _iValue ) ? iNext : iPrev ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Ceil ( float _fValue )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::ceilf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return ceilf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Floor ( float _fValue )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::floorf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return floorf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::GetNearestInteger ( float _fValue )
    {
        const float fFloor = Floor ( _fValue ) ;

        return ( _fValue - fFloor > 0.5f ) ? ( fFloor + 1.0f ) : fFloor ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Log ( float _fValue )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::logf ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return logf ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------
    
    inline float Math::Log10 ( float _fValue )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::log10f ( Vectormath::floatInVec( _fValue ) ).getAsFloat ( ) ;
        #else
        return log10f ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Power ( float _fValue, float _fExposant )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::powf ( Vectormath::floatInVec( _fValue ), Vectormath::floatInVec( _fExposant ) ).getAsFloat ( ) ;
        #else
        return powf ( _fValue, _fExposant ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Mod ( float _fValue1, float _fValue2 )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        return Vectormath::fmodf ( Vectormath::floatInVec( _fValue1 ), Vectormath::floatInVec( _fValue2 ) ).getAsFloat ( ) ;
        #else
        return fmodf ( _fValue1, _fValue2 ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::Round ( float _fValue, uint32 _iDecimals )
    {
        if ( _iDecimals > 0 )
        {
            const float fShifter = Power( 10.0f, (float)_iDecimals ) ;

            return GetNearestInteger ( _fValue * fShifter ) / fShifter ;
        }
        return GetNearestInteger ( _fValue ) ;
    }

    //-------------------------------------------------------------------------

    inline float Math::Trunc ( float _fValue, uint32 _iDecimals )
    {
        if ( _iDecimals > 0 )
        {
            const float fShifter = Power( 10.0f, (float)_iDecimals ) ;

            return ( _fValue >= 0.0f ) ? ( Floor ( _fValue * fShifter ) / fShifter ) : ( Ceil ( _fValue * fShifter ) / fShifter ) ;
        }
        return ( _fValue >= 0.0f ) ? Floor ( _fValue ) : Ceil ( _fValue ) ;
    }

    //-----------------------------------------------------------------------------

    inline float Math::WrapBetweenMinusPiAndPi ( float _fValue )
    {
        //??? Des fois retourne des valeurs hors du range (de peu, mais du coup ça assert, dans leurs propres fonctions, bravo Microsoft)
        //???#if (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)
        //???return XMScalarModAngle ( _fValue ) ;
        //???#else
        _fValue = Mod ( _fValue, Math_k_f2Pi ) ;
        return ( _fValue < -Math_k_fPi ) ? ( _fValue + Math_k_f2Pi ) : ( ( _fValue > Math_k_fPi ) ? ( _fValue - Math_k_f2Pi ) : _fValue ) ;
        //???#endif
    }

    //-----------------------------------------------------------------------------

    inline float Math::FastSin ( float _fValue )
    {
        assert ( _fValue >= -Math_k_fPi ) ;
        assert ( _fValue <=  Math_k_fPi ) ;

        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)
        return XMScalarSinEst ( _fValue ) ;
        #else
        const float B =  4.0f * Math_k_f1ByPi ;
        const float C = -B    * Math_k_f1ByPi ;
        const float y = B * _fValue + C * _fValue * Abs( _fValue ) ;
        return 0.225f * (y * Abs(y) - y) + y ;
        #endif
    }

    //-----------------------------------------------------------------------------

    inline float Math::FastCos ( float _fValue )
    {
        assert ( _fValue >= -Math_k_fPi ) ;
        assert ( _fValue <=  Math_k_fPi ) ;

        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)
        return XMScalarCosEst ( _fValue ) ;
        #else
        float x = _fValue + Math_k_fPiBy2 ; // Wrap: cos(x) = cos(x - 2 pi)
        return FastSin ( ( x > Math_k_fPi ) ? ( x - Math_k_f2Pi ) : x ) ; 
        #endif
    }

    //-------------------------------------------------------------------------

    inline void Math::FastSinCos ( float _fValue, float *_fSin, float *_fCos )
    {
        #if (PANDORA_PLATFORM == PANDORA_PLATFORM_XB360)
        XMScalarSinCosEst ( _fSin, _fCos, _fValue ) ;
        #elif (PANDORA_PLATFORM == PANDORA_PLATFORM_PS3)
        // On PS3 the "accurate" function is faster
        Vectormath::floatInVec x ( _fValue ) ; 
        Vectormath::floatInVec s ; 
        Vectormath::floatInVec c ; 
        Vectormath::sincosf  ( x, &s, &c ) ;
        *_fSin = s.getAsFloat ( ) ;
        *_fCos = c.getAsFloat ( ) ;
        #else
        *_fSin = FastSin ( _fValue ) ;
        *_fCos = FastCos ( _fValue ) ;
        #endif
    }

    //-------------------------------------------------------------------------

    inline float Math::EvaluateBSpline ( float _fPoint0, float _fPoint1, float _fPoint2, float _fPoint3, float _fFactor )
    {
        const float f   = Clamp ( _fFactor, 0.0f, 1.0f ) ;
        const float p0  = (          _fPoint0 + 4.0f * _fPoint1 +        _fPoint2            ) * Math_k_f1By6 ;
        const float p1  = ( - 3.0f * _fPoint0 +                   3.0f * _fPoint2            ) * Math_k_f1By6 ;
        const float p2  = (   3.0f * _fPoint0 - 6.0f * _fPoint1 + 3.0f * _fPoint2            ) * Math_k_f1By6 ;
        const float p3  = (        - _fPoint0 + 3.0f * _fPoint1 - 3.0f * _fPoint2 + _fPoint3 ) * Math_k_f1By6 ;

        return p0 + f * ( p1 + f * ( p2 + f * p3 ) ) ;
    }

    //-------------------------------------------------------------------------

    inline float Math::EvaluateBezier ( float _fPoint0, float _fPoint1, float _fPoint2, float _fPoint3, float _fFactor )
    {                     
        float f     = Clamp ( _fFactor, 0.0f, 1.0f ) ;
        float p0 ( -        _fPoint0 + 3.0f * _fPoint1 - 3.0f * _fPoint2 + _fPoint3 ) ;
        float p1 (   3.0f * _fPoint0 - 6.0f * _fPoint1 + 3.0f * _fPoint2            ) ;
        float p2 ( - 3.0f * _fPoint0 + 3.0f * _fPoint1                              ) ;

        p0 *= ( f * f * f ) ;
        p1 *= ( f * f     ) ;
        p2 *= ( f         ) ;

        return _fPoint0 + p0 + p1 + p2 ;
    }

    //-------------------------------------------------------------------------

    inline float Math::EvaluateCatmullRom ( float _fPoint0, float _fPoint1, float _fPoint2, float _fPoint3, float _fFactor )
    {
        const float f  = Clamp ( _fFactor, 0.0f, 1.0f ) ;
        const float p0 = 2.0f * _fPoint1 ;
        const float p1 =      - _fPoint0 + _fPoint2 ;
        const float p2 = 2.0f * _fPoint0 - 5.0f * _fPoint1 + 4.0f * _fPoint2 - _fPoint3 ;
        const float p3 =      - _fPoint0 + 3.0f * _fPoint1 - 3.0f * _fPoint2 + _fPoint3 ;

        return 0.5f * ( p0 + f * ( p1 + f * ( p2 + f * p3 ) ) ) ;
    }

//-----------------------------------------------------------------------------
} } // Namespace End
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
#endif //__Pandora_EngineCore_Math_inl__
//-----------------------------------------------------------------------------
