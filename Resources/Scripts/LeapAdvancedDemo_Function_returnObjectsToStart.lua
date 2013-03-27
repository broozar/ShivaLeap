--------------------------------------------------------------------------------
--  Function......... : returnObjectsToStart
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.returnObjectsToStart ( nFactor )
--------------------------------------------------------------------------------
	
    local hScene = application.getCurrentUserScene ( )
    
    local dt = application.getLastFrameTime ( ) * nFactor * 0.3
    
	for sceneObjectIndex = 0, scene.getObjectCount ( hScene ) - 1
    do
        local hObject = scene.getObjectAt ( hScene, sceneObjectIndex )
        if(object.getModelName ( hObject ) == "cube")
        then
            local tOrigin = object.getAIVariable ( hObject, "shapeAI", "tOriginalLocation" )
            local x, y, z = table.getRangeAt ( tOrigin, 0, 3 )
            object.translateTo ( hObject, x, y, z, object.kGlobalSpace, dt )
            object.rotateTo ( hObject, 0, 0, 0, object.kGlobalSpace, dt )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
