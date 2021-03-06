//-----------------------------------------------------------------------------
#ifndef __sbLeap_Plugin_h__
#define __sbLeap_Plugin_h__
//-----------------------------------------------------------------------------
#include "S3DXPlugin.h"
//-----------------------------------------------------------------------------

#define PLUGIN_AIPACKAGES_COUNT 1

//-----------------------------------------------------------------------------
// Class declaration
//-----------------------------------------------------------------------------

S3DX_DECLARE_PLUGIN ( sbLeap )
{
    S3DX_DECLARE_AIENGINEAPI        ( ) ;
    S3DX_DECLARE_PLUGIN_INSTANCE    ( sbLeap ) ;

public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
    //-------------------------------------------------------------------------
                                    sbLeap                    ( ) ;
                                   ~sbLeap                    ( ) ;

    //-------------------------------------------------------------------------
    //  Plugin content directory
    //-------------------------------------------------------------------------
            void                    SetContentsDirectory        ( const char *_pDirectory ) ;

    //-------------------------------------------------------------------------
    //  AI packages
    //-------------------------------------------------------------------------
            S3DX::uint32            GetAIPackageCount           ( ) const ;
    const   S3DX::AIPackage        *GetAIPackageAt              ( S3DX::uint32 _iIndex ) const ;


    //-------------------------------------------------------------------------
    //  User functions
    //-------------------------------------------------------------------------
    inline  const char             *GetContentsDirectory        ( ) const { return aContentsDirectory ; }

private :

    //-------------------------------------------------------------------------
    //  Variables
    //-------------------------------------------------------------------------
	S3DX::AIPackage *   aAIPackages			[PLUGIN_AIPACKAGES_COUNT] ;
    char                aContentsDirectory  [ 1024 ] ;
} ;


//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
