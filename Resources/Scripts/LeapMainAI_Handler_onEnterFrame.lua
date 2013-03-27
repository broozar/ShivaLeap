--------------------------------------------------------------------------------
--  Handler.......... : onEnterFrame
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMainAI.onEnterFrame (  )
--------------------------------------------------------------------------------
	if (sbLeap.isConnected() == true) then
        
        local FrameID, numHands, numPointables, numFingers, numTools, numGestures = sbLeap.getFrame ( 0 )
        --log.message ( "Hands: ", numHands, " P: ", numPointables, " F: ", numFingers, " T: ", numTools, " G: ", numGestures )
        sbLeap.setWorkingFrame ( )
        
        if(this.bShowPalm ( ))
        then
            this.leapHandsUpdate ( numHands, true )
        end
        
        if(this.bShowFingers ( ))
        then
            this.leapPointablesUpdate ( numPointables )
        end
        
        this.leapGesturesUpdate ( numGestures )
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
