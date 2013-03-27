--------------------------------------------------------------------------------
--  Function......... : leapCoordinateToCameraSpace
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapCoordinateToCameraSpace ( x, y, z )
--------------------------------------------------------------------------------
	
    --
    -- Scale the Leap axis
    --
    x, y, z = math.vectorScale ( x, y, z, this.nScaleFactor ( ) )
    
    --
    -- Convert the Leap axis to the camera coordinate system
    -- 
    x, y, z = object.transformPoint ( application.getCurrentUserActiveCamera ( ), x, this.nLeapOriginY ( ) + y, this.nLeapOriginZ ( ) + z, object.kLocalSpace, object.kGlobalSpace )
    
    return x, y, z
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
