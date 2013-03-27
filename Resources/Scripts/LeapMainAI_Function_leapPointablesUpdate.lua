--------------------------------------------------------------------------------
--  Function......... : leapPointablesUpdate
--  Author........... : 
--  Description...... : Update the size, position and rotation of each pointable
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMainAI.leapPointablesUpdate ( nNumPointables )
--------------------------------------------------------------------------------
	
    local hScene = application.getCurrentUserScene ( )
    
	for pointableIndex = 0, nNumPointables - 1
    do
        if(pointableIndex > (this.nHandsMaximum ( ) * 5) - 1) then return end
        
        local pointableID = sbLeap.getFramePointable ( pointableIndex )
        --local length = sbLeap.getPointableLength ( pointableID )
        --local width = sbLeap.getPointableWidth ( pointableID )
        local x, y, z = sbLeap.getPointableTipPosition ( pointableID )
        local dirX, dirY, dirZ = sbLeap.getPointableDirection ( pointableID )
        
        local hPointable = scene.getTaggedObject ( hScene, "pointable" .. pointableIndex )
        
        --
        -- Scale the Leap axis
        --
        x, y, z = math.vectorScale ( x, y, z, this.nScaleFactor ( ) )
        --length = length * this.nScaleFactor ( )
        --width = width * this.nScaleFactor ( )
        
        object.setTranslation ( hPointable, x, y, z, object.kGlobalSpace )
        local nx, ny, nz = math.vectorAdd ( x, y, z, dirX, dirY, dirZ )
        object.lookAt ( hPointable, nx, ny, nz, object.kGlobalSpace, 1 )
        object.setVisible ( hPointable, true )
    end
    
    --
    -- Hide un-used pointables
    --
    for pointableIndex = nNumPointables, (this.nHandsMaximum ( ) * 5) - 1
    do
        local hPointable = scene.getTaggedObject ( hScene, "pointable" .. pointableIndex )
        object.setVisible ( hPointable, false )    
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
