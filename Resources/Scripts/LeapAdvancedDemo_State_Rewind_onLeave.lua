--------------------------------------------------------------------------------
--  State............ : Rewind
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.Rewind_onLeave ( )
--------------------------------------------------------------------------------
	
	local hScene = application.getCurrentUserScene ( )
        
	for sceneObjectIndex = 0, scene.getObjectCount ( hScene ) - 1
    do
        local hObject = scene.getObjectAt ( hScene, sceneObjectIndex )
        if(object.getModelName ( hObject ) == "cube")
        then
            dynamics.enableDynamics ( hObject, true)
            dynamics.enableCollisions ( hObject, true )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
