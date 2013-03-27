--------------------------------------------------------------------------------
--  Function......... : sceneInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.sceneInit ( )
--------------------------------------------------------------------------------
	
	application.setCurrentUserScene ( "LeapMotion_AdvancedScene" )
    local hScene = application.getCurrentUserScene ( )
    
    --
    -- Create Cubes
    --
    this.createCubeMatrix ( 3, 2, 2.5 )
    this.createCubeFortress ( 6, 4, 0, 0, 0, 25 )
    
    --
    -- Create Pointables
    --
	for pointableIndex = 0, this.nMaxPointables ( ) - 1
    do
        local hPointable = scene.createRuntimeObject ( hScene, "fingerTip" )
        scene.setObjectTag ( hScene, hPointable, "pointable" .. pointableIndex )
        object.setVisible ( hPointable, false )
    end
    
    --
    -- Dynamics
    --
	scene.setDynamicsGravity ( hScene, 0, -16, 0 )
    --scene.setDynamicsIterationsPerStep ( hScene, 3 )
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
