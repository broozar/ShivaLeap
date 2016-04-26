--------------------------------------------------------------------------------
--  Handler.......... : onGestureCircle
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMotionUser.onGestureCircle ( nID, kState, nTurns, nRadiusMM, nAngleDEG, bClockwise )
--------------------------------------------------------------------------------
	
	-- DEBUG
	-- log.message ( "CIRCLE" .. nID .. " " .. kState .. " ".. nTurns .. " " .. nRadiusMM .. " " .. nAngleDEG )

    -- DEMO only!
    local c = hud.getComponent ( application.getCurrentUser ( ), "g.gesture" )
    if c ~= nil and kState >= leapmotion.kGestureStateStart and nTurns > 0 then
        hud.setLabelText ( c, "Gesture #"..nID.." CIRCLE turn "..nTurns )
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
