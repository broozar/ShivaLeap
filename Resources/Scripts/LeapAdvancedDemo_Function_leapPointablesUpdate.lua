--------------------------------------------------------------------------------
--  Function......... : leapPointablesUpdate
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapPointablesUpdate ( nNumPointables )
--------------------------------------------------------------------------------
	
    local hScene = application.getCurrentUserScene ( )
    
	for pointableIndex = 0, nNumPointables - 1
    do
        if(pointableIndex > this.nMaxPointables ( ) - 1) then return end
        
        local pointableID = sbLeap.getFramePointable ( pointableIndex )
        local x, y, z = sbLeap.getPointableTipPosition ( pointableID )
        local dirX, dirY, dirZ = sbLeap.getPointableDirection ( pointableID )
        
        local hPointable = scene.getTaggedObject ( hScene, "pointable" .. pointableIndex )
        
        x, y, z = this.leapCoordinateToCameraSpace ( x, y, z )

        object.setTranslation ( hPointable, x, y, z, object.kGlobalSpace )
        local nx, ny, nz = math.vectorAdd ( x, y, z, dirX, dirY, dirZ )
        object.lookAt ( hPointable, nx, ny, nz, object.kGlobalSpace, 1 )
        object.setVisible ( hPointable, true )
    end
    
    --
    -- Hide un-used pointables
    --
    for pointableIndex = nNumPointables, this.nMaxPointables ( ) - 1
    do
        local hPointable = scene.getTaggedObject ( hScene, "pointable" .. pointableIndex )
        object.setVisible ( hPointable, false )    
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
