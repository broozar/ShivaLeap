//-----------------------------------------------------------------------------
#include "Pch.h"
#include "Math.h"
//-----------------------------------------------------------------------------
#include <time.h>
//-----------------------------------------------------------------------------
bool Math::bSupportSSE  = false ;
bool Math::bSupportVFP  = false ;
bool Math::bSupportVFPU = false ;
bool Math::bSupportNEON = false ;
//-----------------------------------------------------------------------------

uint32 time_seed ( )
{
    uint32 now = (uint32)time ( NULL ) ;
    return now & 0x7fffffff ; // Generate int32 friendly uint32 ;)
}

//-----------------------------------------------------------------------------
//  Initialisation
//-----------------------------------------------------------------------------

bool Math::Init ( )
{
    // Connect SSE functions if possible.
    //
    if ( DetectSSE ( ) ) 
    {
        bSupportSSE     = true ;
        Log::Message    ( eLogCategory_None, "SSE Processor detected. Using fast math function" ) ;
    }

    // Connect VFP functions if possible.
    //
    if ( DetectVFP ( ) ) 
    {
        bSupportVFP     = true ;
        Log::Message    ( eLogCategory_None, "VFP Processor detected. Using fast math function" ) ;
    }

    // Connect VFPU functions if possible.
    //
    if ( DetectVFPU ( ) ) 
    {
        bSupportVFPU    = true ;
        Log::Message    ( eLogCategory_None, "VFPU Processor detected. Using fast math function" ) ;
    }

    // Connect NEON functions if possible.
    //
    if ( DetectNEON ( ) ) 
    {
        bSupportNEON    = true ;
        Log::Message    ( eLogCategory_None, "NEON Processor detected. Using fast math function" ) ;
    }

    // Initialize random generator
    //
    SetRandomSeed           ( time_seed ( ) ) ;
    SetGaussianRandomSeed   ( time_seed ( ) ) ;

    // Make some fake randoms
    //
    for ( uint32 i = 0 ; i < 8 ; i++ )
    {
        Rand ( ) ;
    }

    return true ;
}

//-------------------------------------------------------------------------
//  Fonctions d'évaluation de courbes
//-------------------------------------------------------------------------

float Math::EvaluateBSpline ( float *_pPointList, uint32 _iPointCount, float _fFactor )
{
    return 0.0f ;
}

//-------------------------------------------------------------------------

float Math::EvaluateBezier ( float *_pPointList, uint32 _iPointCount, float _fFactor )
{
    return 0.0f ;
}

//-------------------------------------------------------------------------

float Math::EvaluateCatmullRom ( float *_pPointList, uint32 _iPointCount, float _fFactor )
{
    return 0.0f ;
}

//-------------------------------------------------------------------------
//  Fonctions diverses
//-------------------------------------------------------------------------

float Math::Calculate3DPolygonArea ( float *_pPointList, uint32 _iPointCount )
{
    // Works with convex and concave polygons :)
    //
    float xyArea = 0.0f ;
	float yzArea = 0.0f ;
	float zxArea = 0.0f ;

	uint32 v0 = _iPointCount - 1 ;

	for ( uint32 v1 = 0 ; v1 < _iPointCount ; v0 = v1, ++v1 )
	{
        const float *p0 = &_pPointList[ v0 * 3 ] ;
		const float *p1 = &_pPointList[ v1 * 3 ] ;

        xyArea += (p0[1] + p1[1]) * (p1[0] - p0[0]) * 0.5f ;
		yzArea += (p0[2] + p1[2]) * (p1[1] - p0[1]) * 0.5f ;
		zxArea += (p0[0] + p1[0]) * (p1[2] - p0[2]) * 0.5f ;
	}

	return Sqrt( xyArea * xyArea + yzArea * yzArea + zxArea * zxArea ) ;
}


//-------------------------------------------------------------------------
// rndlcg            Linear Congruential Method, the "minimal standard generator"
//                   Park & Miller, 1988, Comm of the ACM, 31(10), pp. 1192-1201
//
//-------------------------------------------------------------------------
static const int32 iQuotient    = Math_k_iMaxInt32 / 16807L ;
static const int32 iRemainder   = Math_k_iMaxInt32 % 16807L ;
static       int32 seed_val    = 1L ;
//-------------------------------------------------------------------------

void Math::SetRandomSeed ( int32 _iSeed )
{
    seed_val = ( _iSeed != 0 ) ? _iSeed : 1 ;
}

//-------------------------------------------------------------------------

int32 Math::GetRandomSeed ( )
{
    return seed_val ;
}

//-------------------------------------------------------------------------

uint32 randlcg ( )       /* returns a random unsigned integer */
{
    if ( seed_val <= iQuotient )
    {
        seed_val = (seed_val * 16807L) % Math_k_iMaxInt32 ;
    }
    else
    {
        const int32 high_part = seed_val / iQuotient ;
        const int32 low_part  = seed_val % iQuotient ;
        const int32 test      = 16807L * low_part - iRemainder * high_part ;

        seed_val = ( test > 0 ) ? test : ( test + Math_k_iMaxInt32 ) ;
    }

    return seed_val ;
}


float Math::Rand ( )
{
    return float( randlcg ( ) ) / float( Math_k_iMaxInt32 ) ;
}

//-------------------------------------------------------------------------
static uint32 iGaussianRandomSeed = 61829450 ;

void Math::SetGaussianRandomSeed ( int32 _iSeed )
{
    iGaussianRandomSeed = ( _iSeed != 0 ) ? _iSeed : 1 ;
}

//-------------------------------------------------------------------------

int32 Math::GetGaussianRandomSeed ( )
{
    return iGaussianRandomSeed ;
}

//-------------------------------------------------------------------------

float Math::GaussianRand ( float _fCenter, float _fRadius )
{
    double fSum = 0.0f ;

    for ( register uint32 i = 0 ; i < 3 ; i++ )
    {
        uint32 iHold         =   iGaussianRandomSeed ;
        iGaussianRandomSeed ^= ( iGaussianRandomSeed << 13 ) ;
        iGaussianRandomSeed ^= ( iGaussianRandomSeed >> 17 ) ;
        iGaussianRandomSeed ^= ( iGaussianRandomSeed <<  5 ) ;

        int32 r = iHold + iGaussianRandomSeed ;
        fSum   += (double)r * (1.0 / 0x7fffffff ) ;
    }

    // fSum is between [-3..3]
    //
    return _fRadius * (float)fSum / 3.0f + _fCenter ;
}

//-------------------------------------------------------------------------
// Check if two oriented bounding boxes overlap
//
bool Math::TestOBBIntersection ( const float *_pBox0Extents3, const float *_pBox0Position3, const float *_pBox0Basis9,
                                 const float *_pBox1Extents3, const float *_pBox1Position3, const float *_pBox1Basis9 )
{
    //A
    const Vector3 &a  = (const Vector3 &)_pBox0Extents3  ;
    const Vector3 &Pa = (const Vector3 &)_pBox0Position3 ;
    const Vector3 *A  = (const Vector3 *)_pBox0Basis9    ;

    //B
    const Vector3 &b  = (const Vector3 &)_pBox1Extents3  ;
    const Vector3 &Pb = (const Vector3 &)_pBox1Position3 ;
    const Vector3 *B  = (const Vector3 *)_pBox1Basis9    ;

    //translation, in parent frame
    Vector3 v = Pb - Pa;
    //translation, in A's frame
    Vector3 T( v.DotProduct(A[0]), v.DotProduct(A[1]), v.DotProduct(A[2]) );

    //B's basis with respect to A's local frame
    float R[3][3];
    float ra, rb, t;
    long i, k;

    //calculate rotation matrix
    for( i=0 ; i<3 ; i++ )
    {
        for( k=0 ; k<3 ; k++ )
        {
            R[i][k] = A[i].DotProduct(B[k]);
        }
    }
    /*ALGORITHM: Use the separating axis test for all 15 potential 
    separating axes. If a separating axis could not be found, the two 
    boxes overlap. */

    //A's basis vectors
    for( i=0 ; i<3 ; i++ )
    {
        ra = a[i];
        rb = b[0]*fabsf(R[i][0]) + b[1]*fabsf(R[i][1]) + b[2]*fabsf(R[i][2]);
        t = fabsf( T[i] );

        if( t > ra + rb ) 
            return false;
    }

    //B's basis vectors
    for( k=0 ; k<3 ; k++ )
    {
        ra = a[0]*fabsf(R[0][k]) + a[1]*fabsf(R[1][k]) + a[2]*fabsf(R[2][k]);
        rb = b[k];
        t = fabsf( T[0]*R[0][k] + T[1]*R[1][k] + T[2]*R[2][k] );

        if( t > ra + rb )
            return false;
    }

    //9 cross products

    //L = A0 x B0
    ra = a[1]*fabsf(R[2][0]) + a[2]*fabsf(R[1][0]);
    rb = b[1]*fabsf(R[0][2]) + b[2]*fabsf(R[0][1]);
    t = fabsf( T[2]*R[1][0] - T[1]*R[2][0] );

    if( t > ra + rb )
        return false;

    //L = A0 x B1
    ra = a[1]*fabsf(R[2][1]) + a[2]*fabsf(R[1][1]);
    rb = b[0]*fabsf(R[0][2]) + b[2]*fabsf(R[0][0]);
    t = fabsf( T[2]*R[1][1] - T[1]*R[2][1] );

    if( t > ra + rb )
        return false;

    //L = A0 x B2
    ra = a[1]*fabsf(R[2][2]) + a[2]*fabsf(R[1][2]);
    rb = b[0]*fabsf(R[0][1]) + b[1]*fabsf(R[0][0]);
    t = fabsf( T[2]*R[1][2] - T[1]*R[2][2] );

    if( t > ra + rb )
        return false;

    //L = A1 x B0
    ra = a[0]*fabsf(R[2][0]) + a[2]*fabsf(R[0][0]);
    rb = b[1]*fabsf(R[1][2]) + b[2]*fabsf(R[1][1]);
    t = fabsf( T[0]*R[2][0] - T[2]*R[0][0] );

    if( t > ra + rb )
        return false;

    //L = A1 x B1
    ra = a[0]*fabsf(R[2][1]) + a[2]*fabsf(R[0][1]);
    rb = b[0]*fabsf(R[1][2]) + b[2]*fabsf(R[1][0]);
    t = fabsf( T[0]*R[2][1] - T[2]*R[0][1] );

    if( t > ra + rb )
        return false;

    //L = A1 x B2
    ra = a[0]*fabsf(R[2][2]) + a[2]*fabsf(R[0][2]);
    rb = b[0]*fabsf(R[1][1]) + b[1]*fabsf(R[1][0]);
    t = fabsf( T[0]*R[2][2] - T[2]*R[0][2] );

    if( t > ra + rb )
        return false;

    //L = A2 x B0
    ra = a[0]*fabsf(R[1][0]) + a[1]*fabsf(R[0][0]);
    rb = b[1]*fabsf(R[2][2]) + b[2]*fabsf(R[2][1]);
    t = fabsf( T[1]*R[0][0] - T[0]*R[1][0] );

    if( t > ra + rb )
        return false;

    //L = A2 x B1
    ra = a[0]*fabsf(R[1][1]) + a[1]*fabsf(R[0][1]);
    rb = b[0] *fabsf(R[2][2]) + b[2]*fabsf(R[2][0]);
    t = fabsf( T[1]*R[0][1] - T[0]*R[1][1] );

    if( t > ra + rb )
        return false;

    //L = A2 x B2
    ra = a[0]*fabsf(R[1][2]) + a[1]*fabsf(R[0][2]);
    rb = b[0]*fabsf(R[2][1]) + b[1]*fabsf(R[2][0]);
    t = fabsf( T[1]*R[0][2] - T[0]*R[1][2] );

    if( t > ra + rb )
        return false;

    // No separating axis found, the two boxes overlap
    // 
    return true;
}
