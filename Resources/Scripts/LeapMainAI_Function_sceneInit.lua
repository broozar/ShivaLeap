--------------------------------------------------------------------------------
--  Function......... : sceneInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMainAI.sceneInit ( bShowPalms, bShowFingers )
--------------------------------------------------------------------------------
	
    this.bShowPalm ( bShowPalms )
    this.bShowFingers ( bShowFingers )
    
	application.setCurrentUserScene ( "LeapMotion_Scene1" )
    local hScene = application.getCurrentUserScene ( )
    
    --
    -- Create X hands/spheres, tag them and make them invisible
    --
    for handIndex = 0, this.nHandsMaximum ( ) - 1
    do
        local hHand = scene.createRuntimeObject ( hScene, "hand" )
        local hSphere = scene.createRuntimeObject ( hScene, "sphere" )
        scene.setObjectTag ( hScene, hHand, "hand" .. handIndex )
        scene.setObjectTag ( hScene, hSphere, "sphere" .. handIndex )
        object.setVisible ( hHand, false )
        object.setVisible ( hSphere, false )
    end
    
    --
    -- Create X * 5 pointables
    --
	for pointableIndex = 0, (this.nHandsMaximum ( ) * 5) - 1
    do
        local hPointable = scene.createRuntimeObject ( hScene, "fingerTip" )
        scene.setObjectTag ( hScene, hPointable, "pointable" .. pointableIndex )
        object.setVisible ( hPointable, false )
    end
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
