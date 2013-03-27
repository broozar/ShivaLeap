--------------------------------------------------------------------------------
--  State............ : Rewind
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.Rewind_onEnter ( )
--------------------------------------------------------------------------------
	
    log.message ( "Rewind State" )
    
	local hScene = application.getCurrentUserScene ( )
        
	for sceneObjectIndex = 0, scene.getObjectCount ( hScene ) - 1
    do
        local hObject = scene.getObjectAt ( hScene, sceneObjectIndex )
        if(object.getModelName ( hObject ) == "cube")
        then
            dynamics.setLinearVelocity ( hObject, 0, 0, 0, object.kGlobalSpace )
            dynamics.enableDynamics ( hObject, false )
            dynamics.enableCollisions ( hObject, false )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
