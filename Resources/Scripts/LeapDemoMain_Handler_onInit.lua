--------------------------------------------------------------------------------
--  Handler.......... : onInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapDemoMain.onInit (  )
--------------------------------------------------------------------------------
	
    local hU = this.getUser ( )
    
    -- vsync ON
    application.setOption ( application.kOptionSwapInterval, 1 )
    
    -- load Demo HUD
    hud.newTemplateInstance ( hU, "LeapDemo_Gesture", "g" )
    
    -- load scene
    application.setCurrentUserScene ( "LeapDemo" )
    
    -- start LEAP tracking
    user.sendEvent ( hU, "LeapMotionUser", "onInitLeapStandard" )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
