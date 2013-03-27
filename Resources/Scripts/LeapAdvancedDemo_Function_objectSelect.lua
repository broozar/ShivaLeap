--------------------------------------------------------------------------------
--  Function......... : objectSelect
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.objectSelect ( nPosX, nPosY, nPosZ, nDirX, nDirY, nDirZ )
--------------------------------------------------------------------------------
	
    local hScene = application.getCurrentUserScene ( )
    nPosX, nPosY, nPosZ = object.transformPoint ( application.getCurrentUserActiveCamera ( ), nPosX, this.nLeapOriginY ( ) + nPosY, this.nLeapOriginZ ( ) + nPosZ, object.kLocalSpace, object.kGlobalSpace )
	local hObject = scene.getFirstHitSensor ( hScene, nPosX, nPosY, nPosZ, nDirX, nDirY, nDirZ, 10 )
    if(hObject)
    then
        if(this.hSelectedObject ( ))
        then
            object.sendEvent ( this.hSelectedObject ( ), "shapeAI", "onUnselected" )
        end
        
        this.hSelectedObject ( hObject )
        object.sendEvent ( hObject, "shapeAI", "onSelected"  )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
