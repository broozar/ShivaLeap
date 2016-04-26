--------------------------------------------------------------------------------
--  Handler.......... : onGestureScreentap
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMotionUser.onGestureScreentap ( nID, kState, nPosX, nPosY, nPosZ, nDirX, nDirY, nDirZ )
--------------------------------------------------------------------------------
	
    -- DEBUG
	-- log.message ( "SCREENTAP" .. nID .. " " .. kState .. " " .. nPosX .. " " .. nPosY .. " " .. nPosZ .. " " .. nDirX .. " " .. nDirY .. " " .. nDirZ )
	
    -- DEMO only!
    local c = hud.getComponent ( application.getCurrentUser ( ), "g.gesture" )
    if c ~= nil and kState == leapmotion.kGestureStateStop then -- taps are always discrete, meaning StateStop
        hud.setLabelText ( c, "Gesture #"..nID.." SCREENTAP" )
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
