//-----------------------------------------------------------------------------
#ifndef __Pandora_EngineCore_Quaternion_inl__
#define __Pandora_EngineCore_Quaternion_inl__
//-----------------------------------------------------------------------------


    //-------------------------------------------------------------------------
    //  Construction
    //-------------------------------------------------------------------------

    inline Quaternion::Quaternion ( )
    {
    }

    //-------------------------------------------------------------------------

    inline Quaternion::Quaternion ( float _x, float _y, float _z, float _w )
    {
        x = _x ;
        y = _y ;
        z = _z ;
        w = _w ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion::Quaternion ( const float *_pValues )
    {
        x = _pValues[0] ;
        y = _pValues[1] ;
        z = _pValues[2] ;
        w = _pValues[3] ;
    }

    //-------------------------------------------------------------------------
    //  Opérateurs de cast
    //-------------------------------------------------------------------------
    inline Quaternion::operator float * ( )
    {
        return xyzw ;
    }

    //-------------------------------------------------------------------------
    
    inline Quaternion::operator const float * ( ) const
    {
        return xyzw ;
    }

    //-------------------------------------------------------------------------
    //  Opérateurs binaires
    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::operator * ( const Quaternion &_qQuaternion ) const
    {
        Quaternion q ;

        //q.x = _qQuaternion.w * x + _qQuaternion.x * w + _qQuaternion.y * z - _qQuaternion.z * y ;
        //q.y = _qQuaternion.w * y + _qQuaternion.y * w + _qQuaternion.z * x - _qQuaternion.x * z ;
        //q.z = _qQuaternion.w * z + _qQuaternion.z * w + _qQuaternion.x * y - _qQuaternion.y * x ;
        //q.w = _qQuaternion.w * w - _qQuaternion.x * x - _qQuaternion.y * y - _qQuaternion.z * z ;
        q.x = Math::Mad ( _qQuaternion.w, x, Math::Mad (   _qQuaternion.x, w, Math::Mad (   _qQuaternion.y, z, - _qQuaternion.z * y ) ) ) ;
        q.y = Math::Mad ( _qQuaternion.w, y, Math::Mad (   _qQuaternion.y, w, Math::Mad (   _qQuaternion.z, x, - _qQuaternion.x * z ) ) ) ;
        q.z = Math::Mad ( _qQuaternion.w, z, Math::Mad (   _qQuaternion.z, w, Math::Mad (   _qQuaternion.x, y, - _qQuaternion.y * x ) ) ) ;
        q.w = Math::Mad ( _qQuaternion.w, w, Math::Mad ( - _qQuaternion.x, x, Math::Mad ( - _qQuaternion.y, y, - _qQuaternion.z * z ) ) ) ;

        return q ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::operator + ( const Quaternion &_qQuaternion ) const
    {
        Quaternion q ;

        q.x = _qQuaternion.x + x ;
        q.y = _qQuaternion.y + y ;
        q.z = _qQuaternion.z + z ;
        q.w = _qQuaternion.w + w ;

        return q ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::operator - ( const Quaternion &_qQuaternion ) const
    {
        Quaternion q ;

        q.x = _qQuaternion.x - x ;
        q.y = _qQuaternion.y - y ;
        q.z = _qQuaternion.z - z ;
        q.w = _qQuaternion.w - w ;

        return q ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::operator * ( float _fScalar ) const
    {
        Quaternion q ;

        q.x = x * _fScalar ;
        q.y = y * _fScalar ;
        q.z = z * _fScalar ;
        q.w = w * _fScalar ;

        return q ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::operator / ( float _fScalar ) const
    {
        return Math::IsNullEps ( _fScalar ) ? *this : *this * Math::Inv ( _fScalar ) ;
    }

    //-------------------------------------------------------------------------
    //  Opérateurs d'assignation
    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::operator *= ( const Quaternion &_qQuaternion )
    {
        Quaternion q ;

        //q.x = _qQuaternion.w * x + _qQuaternion.x * w + _qQuaternion.y * z - _qQuaternion.z * y ;
        //q.y = _qQuaternion.w * y + _qQuaternion.y * w + _qQuaternion.z * x - _qQuaternion.x * z ;
        //q.z = _qQuaternion.w * z + _qQuaternion.z * w + _qQuaternion.x * y - _qQuaternion.y * x ;
        //q.w = _qQuaternion.w * w - _qQuaternion.x * x - _qQuaternion.y * y - _qQuaternion.z * z ;
        q.x = Math::Mad ( _qQuaternion.w, x, Math::Mad (   _qQuaternion.x, w, Math::Mad (   _qQuaternion.y, z, - _qQuaternion.z * y ) ) ) ;
        q.y = Math::Mad ( _qQuaternion.w, y, Math::Mad (   _qQuaternion.y, w, Math::Mad (   _qQuaternion.z, x, - _qQuaternion.x * z ) ) ) ;
        q.z = Math::Mad ( _qQuaternion.w, z, Math::Mad (   _qQuaternion.z, w, Math::Mad (   _qQuaternion.x, y, - _qQuaternion.y * x ) ) ) ;
        q.w = Math::Mad ( _qQuaternion.w, w, Math::Mad ( - _qQuaternion.x, x, Math::Mad ( - _qQuaternion.y, y, - _qQuaternion.z * z ) ) ) ;

        x = q.x ;
        y = q.y ;
        z = q.z ;
        w = q.w ;
        
        return *this ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::operator *= ( float _fScalar )
    {
        x *= _fScalar ;
        y *= _fScalar ;
        z *= _fScalar ;
        w *= _fScalar ;

        return *this ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::operator /= ( float _fScalar )
    {
        if ( ! Math::IsNullEps ( _fScalar ) ) 
        {
            *this *= Math::Inv ( _fScalar ) ;
        }

        return *this ;
    }



    //-------------------------------------------------------------------------
    //  Méthodes
    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::Normalize ( )
    {
        const float fSqrNorm = x * x + y * y + z * z + w * w ;
        if        ( fSqrNorm > Math_k_fEps )
        {
            const float fInvNorm = Math::Inv ( Math::Sqrt( fSqrNorm ) ) ;

            x *= fInvNorm ;
            y *= fInvNorm ;
            z *= fInvNorm ;
            w *= fInvNorm ;
        }

        return *this ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::Neg ( )
    {
        x = -x ;
        y = -y ;
        z = -z ;
        w = -w ;

        return *this ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::Invert ( )
    {
        w = -w ;

        return *this ;
    }

    //-------------------------------------------------------------------------

    inline float Quaternion::SqrMagnitude ( ) const
    {
        return x * x + y * y + z * z + w * w ;
    }

    //-------------------------------------------------------------------------

    inline float Quaternion::Magnitude ( ) const
    {
        return Math::Sqrt ( SqrMagnitude ( ) ) ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::GetInverse ( ) const
    {
        return Quaternion( x, y, z, -w ) ;
    }
    
    //-------------------------------------------------------------------------

    inline Quaternion Quaternion::GetConjugate ( ) const
    {
        return Quaternion( -x, -y, -z, w ) ;
    }

    //-------------------------------------------------------------------------

    inline bool Quaternion::IsNeutral ( ) const
    {
        return ( x == 0.0f ) && ( y == 0.0f ) && ( z == 0.0f ) && ( Math::Abs ( w ) == 1.0f ) ;
    }
    
    //-------------------------------------------------------------------------

    inline bool Quaternion::IsNeutralEps ( ) const
    {
        return ( Math::IsNullEps  ( x ) &&
                 Math::IsNullEps  ( y ) &&
                 Math::IsNullEps  ( z ) &&
                 Math::IsEqualEps ( Math::Abs ( w ), 1.0f ) ) ;
    }
    
    //-------------------------------------------------------------------------

    inline bool Quaternion::IsNormalizedEps ( ) const
    {
        return Math::IsEqualEps ( SqrMagnitude ( ), 1.0f ) ;
    }
    
    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::SetNeutral ( )
    {
        x = y = z = 0.0f ; w = 1.0f ;

        return *this ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::Set ( float _x, float _y, float _z, float _w )
    {
        x = _x ;
        y = _y ;
        z = _z ;
        w = _w ;

        return *this ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::SetAngles ( const Vector3 &_vAngles )
    {
        return SetAngles ( _vAngles.x, _vAngles.y, _vAngles.z ) ;
    }

    //-------------------------------------------------------------------------

    inline Vector3 Quaternion::TransformVector ( const Vector3 &_vVector ) const
    {
        // Formule : result = q.conjugate ( ) * v * q

        //const float rw = - x * _vVector.x - y * _vVector.y - z * _vVector.z ;
        //const float rx =   w * _vVector.x + y * _vVector.z - z * _vVector.y ;
        //const float ry =   w * _vVector.y + z * _vVector.x - x * _vVector.z ;
        //const float rz =   w * _vVector.z + x * _vVector.y - y * _vVector.x ;
        const float rw = Math::Mad ( - x, _vVector.x, Math::Mad ( - y, _vVector.y, - z * _vVector.z ) ) ;
        const float rx = Math::Mad (   w, _vVector.x, Math::Mad (   y, _vVector.z, - z * _vVector.y ) ) ;
        const float ry = Math::Mad (   w, _vVector.y, Math::Mad (   z, _vVector.x, - x * _vVector.z ) ) ;
        const float rz = Math::Mad (   w, _vVector.z, Math::Mad (   x, _vVector.y, - y * _vVector.x ) ) ;

        //return Vector3 ( - rw * x + rx * w - ry * z + rz * y,
        //                 - rw * y + ry * w - rz * x + rx * z,
        //                 - rw * z + rz * w - rx * y + ry * x ) ;
        return Vector3 ( Math::Mad ( - rw, x, Math::Mad ( rx, w, Math::Mad ( - ry, z, rz * y ) ) ),
                         Math::Mad ( - rw, y, Math::Mad ( ry, w, Math::Mad ( - rz, x, rx * z ) ) ),
                         Math::Mad ( - rw, z, Math::Mad ( rz, w, Math::Mad ( - rx, y, ry * x ) ) ) ) ;
    }

    //-------------------------------------------------------------------------

    inline Vector3 Quaternion::GetXAxis ( ) const
    {
        //return Vector3 ( x * x + w * w - z * z - y * y,
        //                 x * y - z * w + y * x - w * z,
        //                 x * z + y * w + w * y + z * x ) ;
        return Vector3 ( Math::Mad ( x, x, Math::Mad (   w, w, Math::Mad ( - z, z, - y * y ) ) ),
                         Math::Mad ( x, y, Math::Mad ( - z, w, Math::Mad (   y, x, - w * z ) ) ),
                         Math::Mad ( x, z, Math::Mad (   y, w, Math::Mad (   w, y,   z * x ) ) ) ) ;
    }

    //-------------------------------------------------------------------------
    
    inline Vector3 Quaternion::GetYAxis ( ) const
    {
        //return Vector3 ( y * x + z * w + w * z + x * y,
        //                 y * y + w * w - x * x - z * z,
        //                 y * z - x * w + z * y - w * x ) ;
        return Vector3 ( Math::Mad ( y, x, Math::Mad (   z, w, Math::Mad (   w, z,   x * y ) ) ),
                         Math::Mad ( y, y, Math::Mad (   w, w, Math::Mad ( - x, x, - z * z ) ) ),
                         Math::Mad ( y, z, Math::Mad ( - x, w, Math::Mad (   z, y, - w * x ) ) ) ) ;
    }

    //-------------------------------------------------------------------------

    inline Vector3 Quaternion::GetZAxis ( ) const
    {
        //return Vector3 ( z * x - y * w + x * z - w * y,
        //                 z * y + x * w + w * x + y * z,
        //                 z * z + w * w - y * y - x * x ) ;
        return Vector3 ( Math::Mad ( z, x, Math::Mad ( - y, w, Math::Mad (   x, z, - w * y ) ) ),
                         Math::Mad ( z, y, Math::Mad (   x, w, Math::Mad (   w, x,   y * z ) ) ),
                         Math::Mad ( z, z, Math::Mad (   w, w, Math::Mad ( - y, y, - x * x ) ) ) ) ;
    }

    //-----------------------------------------------------------------------------

    inline Quaternion &Quaternion::Lerp ( const Quaternion &_qSrcQuaternion, const Quaternion &_qDstQuaternion, float _fFactor )
    {
        assert ( _fFactor >= 0 ) ;
        assert ( _fFactor <= 1 ) ;

        return ( _qSrcQuaternion * ( 1.0f - _fFactor ) + _qDstQuaternion * _fFactor ).Normalize ( ) ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::Slerp ( const Quaternion &_qSrcQuaternion, const Quaternion &_qDstQuaternion, float _fFactor )
    {
        assert ( _fFactor >= 0 ) ;
        assert ( _fFactor <= 1 ) ;

        return *this ;
    }

    //-----------------------------------------------------------------------------

    inline void Quaternion::Scale ( float _fFactor )
    {
        float fCosOmega, fScale0, fScale1 ;

        // On calcule le cosinus.
        //
        fCosOmega = w ;

        // On ajuste les signes ( si nécessaire... ).
        //
        if ( fCosOmega < 0.0f ) 
        {
            fCosOmega   = - fCosOmega ;
            x           = - x ;
            y           = - y ;
            z           = - z ;
            w           = - w ;
        } 

        // On calcule les coefficients.
        //
        if ( ( 1.0f - fCosOmega ) > Math_k_fEps ) 
        {
            // Cas standard ( slerp ).
            //
            float fOmega    = Math::ACos ( fCosOmega ) ;
            float fSinOmega = Math::Sin  ( fOmega    ) ;
            fScale0         = Math::Sin  ( fOmega * ( 1.0f - _fFactor ) ) / fSinOmega ;
            fScale1         = Math::Sin  ( fOmega *          _fFactor   ) / fSinOmega ;

        } 
        else 
        {
            // Les 2 quaternions sont très proches,
            // alors on fait une interpolation linéaire.
            //
            fScale0 = 1.0f - _fFactor ;
            fScale1 =        _fFactor ;
        }

        // On calcule les valeurs finales.
        //
        x = fScale1 * x ;
        y = fScale1 * y ;
        z = fScale1 * z ;
        w = fScale1 * w + fScale0 ;

        //Normalize ( ) ; //???
    }

    //-------------------------------------------------------------------------

    inline bool Quaternion::IsEqualTo ( const Quaternion &_qQuaternion, float _fEpsilon ) const
    {
        return ( Math::Abs ( x - _qQuaternion.x ) < _fEpsilon ) && 
               ( Math::Abs ( y - _qQuaternion.y ) < _fEpsilon ) && 
               ( Math::Abs ( z - _qQuaternion.z ) < _fEpsilon ) && 
               ( Math::Abs ( w - _qQuaternion.w ) < _fEpsilon ) ;
    }

    //-------------------------------------------------------------------------

    inline Quaternion &Quaternion::Round ( uint32 _iDecimals )
    {
        x = Math::Round ( x, _iDecimals ) ;
        y = Math::Round ( y, _iDecimals ) ;
        z = Math::Round ( z, _iDecimals ) ;
        w = Math::Round ( w, _iDecimals ) ;

        return *this ;
    }

//-----------------------------------------------------------------------------
#endif //__Pandora_EngineCore_Quaternion_inl__
//-----------------------------------------------------------------------------
