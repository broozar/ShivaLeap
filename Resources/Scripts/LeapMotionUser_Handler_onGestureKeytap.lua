--------------------------------------------------------------------------------
--  Handler.......... : onGestureKeytap
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMotionUser.onGestureKeytap ( nID, kState, nPosX, nPosY, nPosZ, nDirX, nDirY, nDirZ )
--------------------------------------------------------------------------------
	
	-- DEBUG
	-- log.message ( "KEYTAP" .. nID .. " " .. kState .. " ".. nPosX .. " " .. nPosY .. " " .. nPosZ .. " ".. nDirX .. " " .. nDirY .. " " .. nDirZ )
	
    -- DEMO only!
    local c = hud.getComponent ( application.getCurrentUser ( ), "g.gesture" )
    if c ~= nil and kState == leapmotion.kGestureStateStop then  -- taps are always discrete, meaning StateStop
        hud.setLabelText ( c, "Gesture #"..nID.." KEYTAP" )
    end
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
