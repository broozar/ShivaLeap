--------------------------------------------------------------------------------
--  Handler.......... : onGestureSwipe
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMotionUser.onGestureSwipe ( nID, kState, nDirX, nDirY, nDirZ, nSpeed )
--------------------------------------------------------------------------------
	
    -- DEBUG
	-- log.message ( "SWIPE" .. nID .. " " .. kState .. " ".. nDirX .. " " .. nDirY .. " " .. nDirZ .. " " .. nSpeed )
    
    -- DEMO only!
    local c = hud.getComponent ( application.getCurrentUser ( ), "g.gesture" )
    if c ~= nil and kState >= leapmotion.kGestureStateStart then -- only catch updates and stops
        hud.setLabelText ( c, "Gesture #"..nID.." SWIPE speed "..nSpeed )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
