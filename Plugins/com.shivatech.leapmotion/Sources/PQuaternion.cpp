//-----------------------------------------------------------------------------
#include "Quaternion.h"

Quaternion &Quaternion::SetAxis ( const Vector3 &_vXAxis, const Vector3 &_vYAxis, const Vector3 &_vZAxis )
{
    // FIXME : code piqué de Maya, à optimiser et vérifier...
    float m[3][3] ;

    m[0][0] = _vXAxis.x ;
    m[1][0] = _vXAxis.y ;
    m[2][0] = _vXAxis.z ;
    m[0][1] = _vYAxis.x ;
    m[1][1] = _vYAxis.y ;
    m[2][1] = _vYAxis.z ;
    m[0][2] = _vZAxis.x ;
    m[1][2] = _vZAxis.y ;
    m[2][2] = _vZAxis.z ;


    float trace, s ;
    int i, j, k ;
    
    // vectors are multiplied on the left (pre-multipy).
    //
    trace = m[0][0] + m[1][1] + m[2][2] ;

    if ( trace > 0.0f ) 
    {
        s = Math::Sqrt ( trace + 1.0f ) ;
        w = s * 0.5f ;
        s = 0.5f / s ;
        x = ( m[1][2] - m[2][1] ) * s ;
        y = ( m[2][0] - m[0][2] ) * s ;
        z = ( m[0][1] - m[1][0] ) * s ;
    } 
    else 
    {        
        float *q[3] = { &x, &y, &z } ;

        i = 0 ;

        if ( m[1][1] > m[0][0] ) i = 1 ;
        if ( m[2][2] > m[i][i] ) i = 2 ;

        j = ( i + 1 ) % 3 ;
        k = ( j + 1 ) % 3 ;

        s = Math::Sqrt ( m[i][i] - ( m[j][j] + m[k][k] ) + 1.0f ) ;

        *q[i] = s * 0.5f ;

        s = 0.5f / s ;

        w     = ( m[j][k] - m[k][j] ) * s ;
        *q[j] = ( m[j][i] + m[i][j] ) * s ;
        *q[k] = ( m[k][i] + m[i][k] ) * s ;
    }


    return *this ;
}

//-----------------------------------------------------------------------------

Quaternion &Quaternion::SetAxisAngle ( const Vector3 &_vAxis, float _fAngle )
{
    float fSum = _vAxis.SqrLength ( ) ;

    if ( fSum <= 0.000001f ) 
    {
        SetNeutral ( ) ;
    } 
    else 
    {
        _fAngle *= 0.5f ;

        float s = Math::Sin( _fAngle ) ;

        if ( ! Math::IsEqualEps ( fSum, 1.0f ) ) 
        {
            s /= Math::Sqrt ( fSum ) ;
        }

        x = s * _vAxis.x ;
        y = s * _vAxis.y ;
        z = s * _vAxis.z ;

        w = Math::Cos ( _fAngle ) ;

        //Normalize ( ) ; //???
    }

    return *this ;        
}

//-----------------------------------------------------------------------------

Quaternion &Quaternion::SetAngles ( float _x, float _y, float _z )
{
    //*
    float c1    ;
    float s1    ; Math::SinCos ( _y * 0.5f, &s1, &c1 ) ;
    float c2    ;
    float s2    ; Math::SinCos ( _z * 0.5f, &s2, &c2 ) ;
    float c3    ;
    float s3    ; Math::SinCos ( _x * 0.5f, &s3, &c3 ) ;
    float c1c2  = c1 * c2 ;    
    float s1s2  = s1 * s2 ;    

    w = c1c2 * c3 - s1s2 * s3 ;
    x = c1c2 * s3 + s1s2 * c3 ;
    y = s1 * c2 * c3 + c1 * s2 * s3 ;
    z = c1 * s2 * c3 - s1 * c2 * s3 ;
    
    return *this ; // No need to normalize.
}

//-----------------------------------------------------------------------------

bool Quaternion::GetAngles ( Vector3 &_vAngles ) const
{
    //
    float sqw   = w * w ;   
    float sqx   = x * x ;    
    float sqy   = y * y ;    
    float sqz   = z * z ;
    float unit  = sqx + sqy + sqz + sqw ; // if normalized is one, otherwise is correction factor
    float test  = x * y + z * w ;
    
    if ( test > 0.49999f * unit )
    { 
        // singularity at north pole
        //
        _vAngles.y = 2.0f * Math::ATan2 ( x, w ) ;
        _vAngles.z = Math_k_fPiBy2 ;
        _vAngles.x = 0.0f ;
        return true ;
    }    

    if ( test < -0.49999f * unit ) 
    { 
        // singularity at south pole
        //
        _vAngles.y = - 2.0f * Math::ATan2 ( x, w ) ;
        _vAngles.z = - Math_k_fPiBy2 ;
        _vAngles.x = 0.0f ;
        return true ;
    } 
    
    float numx  =   2.0f * ( x * w - y * z ) ;
    float numy  =   2.0f * ( y * w - x * z ) ;
    float numz  =   2.0f * test / unit ;

    _vAngles.x = Math::ATan2 ( numx, - sqx + sqy - sqz + sqw ) ;
    _vAngles.y = Math::ATan2 ( numy,   sqx - sqy - sqz + sqw ) ;
    _vAngles.z = Math::ASin  ( numz ) ;
   
    return true ;
}

//-----------------------------------------------------------------------------

bool Quaternion::GetAxisAngle ( Vector3 &_vAxis, float &_fAngle ) const
{
    bool    bResult ;
    float   fInverseOfSinThetaByTwo, fThetaExtended ;
    
    if ( Math::IsEqualEps ( w, 1.0f ) )
    {
        _fAngle = 0.0f ;

        if ( _vAxis.Length ( ) < Math_k_fEps ) 
        {
            //
            //  Passed in axis invalid, choose an arbitrary axis.
            //
            _vAxis.Set ( 0.0f, 1.0f, 0.0f ) ;
        }
        
        bResult = false ;
    }
    else 
    {
        fThetaExtended = Math::ACos ( Math::Clamp ( w, -1.0f, 1.0f ) ) ;

        _fAngle = fThetaExtended * 2.0f ;
        
        fInverseOfSinThetaByTwo = 1.0f / Math::Sin ( fThetaExtended ) ;

        _vAxis.x = x * fInverseOfSinThetaByTwo ;
        _vAxis.y = y * fInverseOfSinThetaByTwo ;
        _vAxis.z = z * fInverseOfSinThetaByTwo ;

        bResult = true ;
    }

    return bResult ;

}

//-----------------------------------------------------------------------------

Quaternion &Quaternion::SetYawPitchRoll ( float _fYaw, float _fPitch, float _fRoll )
{
    // Apply Yaw first
    //
    SetAngles ( 0, _fYaw, 0 ) ;

    // Apply Pitch
    //
    if ( ! Math::IsNullEps ( _fPitch ) )
    {
        Quaternion qPitch ; 
        *this  *=  qPitch .SetAngles ( _fPitch, 0, 0 ) ;
    }

    // Apply Roll
    //
    if ( ! Math::IsNullEps ( _fRoll ) )
    {
        Quaternion qRoll  ; 
        *this  *=  qRoll  .SetAngles ( 0, 0, _fRoll ) ;
    }

    return *this ;
}

//-----------------------------------------------------------------------------

bool Quaternion::GetYawPitchRoll ( float &_fYaw, float &_fPitch, float &_fRoll ) const
{
    // TEST... FIXME...
    //
    const Vector3 vQX = GetXAxis ( ) ;
    const Vector3 vQY = GetYAxis ( ) ;
    const Vector3 vQZ = GetZAxis ( ) ;

    if ( vQY.DotProduct ( Vector3( 0, 1, 0 ) ) >= 0.0f )
    {
        // Yaw TODO : Yaw has a singularity at +/-90 !!!
        //
        const Vector3 vQZProjOnXZ = Vector3( vQZ.x, 0, vQZ.z ).Normalize ( ) ;

        _fYaw   = Math::ACos ( vQZProjOnXZ.DotProduct ( Vector3( 1, 0, 0 ) ) ) - Math_k_fPiBy2 ;

        if ( vQZProjOnXZ.DotProduct ( Vector3( 0, 0, 1 ) ) <= 0.0f )
        {
            if ( _fYaw > 0 ) _fYaw =   Math_k_fPi - _fYaw ;
            else             _fYaw = - Math_k_fPi - _fYaw ;
        }

        // Pitch
        //
        _fPitch = Math_k_fPiBy2 - Math::ACos ( vQZ.DotProduct ( Vector3( 0, 1, 0 ) ) ) ;

        // Roll
        //
        Quaternion qUnRolled ; 
        qUnRolled.SetYawPitchRoll ( _fYaw, _fPitch, 0 ) ;

        _fRoll  = Math::ACos ( vQX.DotProduct ( qUnRolled.GetYAxis ( ) ) ) - Math_k_fPiBy2 ;
    }
    else
    {
        // TODO
        //
        _fYaw   = 0 ;
        _fPitch = 0 ;
        _fRoll  = 0 ;
    }

    return true ;
}

//-----------------------------------------------------------------------------

void Quaternion::Compress ( int16 &_x, int16 &_y, int16 &_z, bool _bAdaptative ) const
{
    // Compresses the quaternion from traditional 4*4 = 16 bytes to 6 bytes.
    // This is a lossy compression based on article "Quaternion, Compression" by Zarb-Adami in GPG3.
    //
    if ( _bAdaptative )
    {
        // Cal3D implementation, fixed by NiCoX, looks ok according to the automated test
        //
        const float fScale = 1.41421f ;

        if ( ( Math::Abs( w ) > Math::Abs( x ) ) && 
             ( Math::Abs( w ) > Math::Abs( y ) ) && 
             ( Math::Abs( w ) > Math::Abs( z ) ) ) 
        {
            float rx = x * fScale ;
            float ry = y * fScale ;
            float rz = z * fScale ;

            // w is the biggest element, make sure it's also positive, if not, negate the quaternion
            //
            if ( w < 0.0f ) 
            {
                rx = -rx ;
                ry = -ry ;
                rz = -rz ;
            }
            if      ( rx < -1.0f ) rx = -1.0f ;
            else if ( rx >  1.0f ) rx =  1.0f ;
            if      ( ry < -1.0f ) ry = -1.0f ;
            else if ( ry >  1.0f ) ry =  1.0f ;
            if      ( rz < -1.0f ) rz = -1.0f ;
            else if ( rz >  1.0f ) rz =  1.0f ;

            _x = int16(          rx * 32767.0f ) ;
            _y = int16( ( int32( ry * 32767.0f ) & 0xfffe ) | 1 ) ;
            _z = int16( ( int32( rz * 32767.0f ) & 0xfffe ) | 1 ) ;
        }
        else if ( ( Math::Abs( z ) > Math::Abs( x ) ) && 
                  ( Math::Abs( z ) > Math::Abs( y ) ) ) 
        {
            float rx = x * fScale ;
            float ry = y * fScale ;
            float rw = w * fScale ;

            // z is the biggest element, make sure it's also positive, if not, negate the quaternion
            //
            if ( z < 0.0f ) 
            {
                rx = -rx ;
                ry = -ry ;
                rw = -rw ;
            }
            if      ( rx < -1.0f ) rx = -1.0f ;
            else if ( rx >  1.0f ) rx =  1.0f ;
            if      ( ry < -1.0f ) ry = -1.0f ;
            else if ( ry >  1.0f ) ry =  1.0f ;
            if      ( rw < -1.0f ) rw = -1.0f ;
            else if ( rw >  1.0f ) rw =  1.0f ;

            _x = int16(          rx * 32767.0f ) ;
            _y = int16( ( int32( ry * 32767.0f ) & 0xfffe ) | 1 ) ;
            _z = int16( ( int32( rw * 32767.0f ) & 0xfffe ) | 0 ) ;
        }
        else if ( Math::Abs( y ) > Math::Abs( x ) )
        {
            float rx = x * fScale ;
            float rz = z * fScale ;
            float rw = w * fScale ;

            // y is the biggest element, make sure it's also positive, if not, negate the quaternion
            //
            if ( y < 0.0f ) 
            {
                rx = -rx ;
                rz = -rz ;
                rw = -rw ;
            }
            if      ( rx < -1.0f ) rx = -1.0f ;
            else if ( rx >  1.0f ) rx =  1.0f ;
            if      ( rz < -1.0f ) rz = -1.0f ;
            else if ( rz >  1.0f ) rz =  1.0f ;
            if      ( rw < -1.0f ) rw = -1.0f ;
            else if ( rw >  1.0f ) rw =  1.0f ;

            _x = int16(          rx * 32767.0f ) ;
            _y = int16( ( int32( rz * 32767.0f ) & 0xfffe) | 0 ) ;
            _z = int16( ( int32( rw * 32767.0f ) & 0xfffe) | 1 ) ;
        }
        else 
        {
            float ry = y * fScale ;
            float rz = z * fScale ;
            float rw = w * fScale ;

            // x is the biggest element, make sure it's also positive, if not, negate the quaternion
            //
            if ( x < 0.0f ) 
            {
                ry = -ry ;
                rz = -rz ;
                rw = -rw ;
            }
            if      ( ry < -1.0f ) ry = -1.0f ;
            else if ( ry >  1.0f ) ry =  1.0f ;
            if      ( rz < -1.0f ) rz = -1.0f ;
            else if ( rz >  1.0f ) rz =  1.0f ;
            if      ( rw < -1.0f ) rw = -1.0f ;
            else if ( rw >  1.0f ) rw =  1.0f ;

            _x = int16(          ry * 32767.0f ) ;
            _y = int16( ( int32( rz * 32767.0f ) & 0xfffe ) | 0 ) ;
            _z = int16( ( int32( rw * 32767.0f ) & 0xfffe ) | 0 ) ;
        }
    }
    else
    {
        // Naive method: less accurate
        //
        if ( w < 0.0f )
        {
            _x = - int16( x * 32767.0f ) ;
            _y = - int16( y * 32767.0f ) ;
            _z = - int16( z * 32767.0f ) ;
        }
        else
        {
            _x =   int16( x * 32767.0f ) ;
            _y =   int16( y * 32767.0f ) ;
            _z =   int16( z * 32767.0f ) ;
        }
    }
}

//-----------------------------------------------------------------------------

void Quaternion::Uncompress ( int16 _x, int16 _y, int16 _z, bool _bAdaptative )
{
    if ( _bAdaptative )
    {
        // Cal3D implementation, fixed by NiCoX, looks ok according to the automated test
        //
        int16 iWhich = ( (_y & 1) << 1 ) | (_z & 1) ;
        _y &= 0xfffe ;
        _z &= 0xfffe ;

        const float fScale = 1.0f / 32767.0f / 1.41421f ;

        if ( iWhich == 3 ) 
        {
            x = _x * fScale ;
            y = _y * fScale ;
            z = _z * fScale ;

            w = 1.0f - ( x * x ) - ( y * y ) - ( z * z ) ;
            
            if ( w > Math_k_fEps )
            {
                w = Math::Sqrt ( w ) ;
            }
        }
        else if ( iWhich == 2 ) 
        {
            x = _x * fScale ;
            y = _y * fScale ;
            w = _z * fScale ;

            z = 1.0f - ( x * x ) - ( y * y ) - ( w * w ) ;
            
            if ( z > Math_k_fEps )
            {
                z = Math::Sqrt ( z ) ;
            }
        }
        else if ( iWhich == 1 ) 
        {
            x = _x * fScale ;
            z = _y * fScale ;
            w = _z * fScale ;

            y = 1.0f - ( x * x ) - ( z * z ) - ( w * w ) ;
            
            if ( y > Math_k_fEps )
            {
                y = Math::Sqrt ( y ) ;
            }
        }
        else 
        {
            y = _x * fScale ;
            z = _y * fScale ;
            w = _z * fScale ;

            x = 1.0f - ( y * y ) - ( z * z ) - ( w * w ) ;
            
            if ( x > Math_k_fEps )
            {
                x = Math::Sqrt ( x ) ;
            }
        }
        //??? if ( w < 0.0f )
        //??? {
        //???     Neg ( ) ;
        //??? }
    }
    else
    {
        // Naive method: less accurate
        //
        x = (float)_x * Math_k_f1By32767 ;
        y = (float)_y * Math_k_f1By32767 ;
        z = (float)_z * Math_k_f1By32767 ;
        w = 1.0f - ( x * x ) - ( y * y ) - ( z * z ) ;

        if ( w > Math_k_fEps )
        {
            w = Math::Sqrt ( w ) ;
        }
    }
}

//-----------------------------------------------------------------------------
//  Debug
//-----------------------------------------------------------------------------

void Quaternion::DebugPrint ( ) const
{
    char s[64] ;

    sprintf ( s, "%f %f %f %f", x, y, z, w ) ;

    Log::Message ( eLogCategory_None, s ) ;
}

//-----------------------------------------------------------------------------
} }
//-----------------------------------------------------------------------------
