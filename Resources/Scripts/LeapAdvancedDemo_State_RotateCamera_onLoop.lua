--------------------------------------------------------------------------------
--  State............ : RotateCamera
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.RotateCamera_onLoop ( )
--------------------------------------------------------------------------------
	
    if (sbLeap.isConnected() == true) then
        local FrameID, numHands, numPointables, numFingers, numTools, numGestures = sbLeap.getFrame ( 0 )
        sbLeap.setWorkingFrame ( )
        
        --
        -- Draw the pointables
        --
        this.leapPointablesUpdate ( numPointables )
    end
    
    local hCamera = application.getCurrentUserActiveCamera ( )
    
	local xo, yo, zo = table.getRangeAt ( this.tCameraDestination ( ), 0, 3 )    

    object.translateTo ( hCamera, xo, yo, zo, object.kGlobalSpace, application.getLastFrameTime ( ) * 2)
    object.lookAt ( hCamera, 0, 4, 0, object.kGlobalSpace, 1 )
    
    local x, y, z = object.getTranslation ( hCamera, object.kGlobalSpace )
    x, y, z = math.roundToNearestInteger ( x ), math.roundToNearestInteger ( y ), math.roundToNearestInteger ( z )
    
    if(x == xo and y == yo and z == zo)
    then
        this.Interact ( )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
