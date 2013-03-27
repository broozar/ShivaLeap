--------------------------------------------------------------------------------
--  State............ : Rewind
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.Rewind_onLoop ( )
--------------------------------------------------------------------------------
	        
    local FrameID, numHands, numPointables, numFingers, numTools, numGestures = sbLeap.getFrame ( 0 )
    sbLeap.setWorkingFrame ( )
    
    --
    -- Draw the pointables
    --
    this.leapPointablesUpdate ( numPointables )
    
    --
    -- If there aren't any gestures in the frame, bail out
    --
    if(numGestures == 0)
    then
        this.Interact ( )
    else
        for gestureIndex = 0, numGestures - 1
        do
            local nGestureID, kGestureType, nDuration, kGesturesState = sbLeap.getGesture ( gestureIndex )
            --log.message ( "ID: ", nGestureID, " T: ", kGestureType, " D: ", nDuration, " S: ", kGesturesState )
            
            if(nGestureID > 0)
            then
                if(kGestureType == sbLeap.kGestureTypeCircle)
                then    
                    if( kGesturesState == sbLeap.kGestureStateStart or kGesturesState == sbLeap.kGestureStateUpdate)
                    then
                        local nPointable, nNormX, nNormY, nNormZ, nCenterX, nCenterY, nCenterZ, nTraces, nRadius = sbLeap.getGestureCircle ( nGestureID )
                        this.returnObjectsToStart ( nTraces )
                    else
                        this.Interact ( )
                    end
                end
            end
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
