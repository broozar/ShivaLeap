--------------------------------------------------------------------------------
--  State............ : Interact
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.Interact_onLoop ( )
--------------------------------------------------------------------------------
	
	if (sbLeap.isConnected() == true) then
        
        local FrameID, numHands, numPointables, numFingers, numTools, numGestures = sbLeap.getFrame ( 0 )
        --log.message ( "Hands: ", numHands, " P: ", numPointables, " F: ", numFingers, " T: ", numTools, " G: ", numGestures )
        sbLeap.setWorkingFrame ( )
        
        --
        -- Draw the pointables
        --
        this.leapPointablesUpdate ( numPointables )
        
        --
        -- There are 2 ways to select/move objects either by 2 finger pinching or by using the hand radius and finding intersecting objects
        --
        this.leapPinchSelectMove ( numPointables )
        --this.leapGrabSelectMove ( numHands, numFingers )
        
        --
        -- There are a couple different control schemes that you can enable independently
        --
        
        -- MOVEMENT
        -- Move the camera forward/back left/right based on the movements of a single hand
        --
        --this.cameraPan ( numHands )
        
        -- ZOOMING
        -- Zoom in/out based on the scale of 1 or more pointables
        -- 
        --this.cameraScale ( numPointables)        
        
        -- ROTATION
        -- Do a really crappy rotation, not finalized
        --
        --this.cameraRotate ( )
                
        -- SWIPING & TAPPING
        -- Enable swiping to rotate the camera around the matrix and tapping to select a cube
        --
        if(numPointables == 1)
        then
            this.leapGesturesUpdate ( numGestures )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
