--------------------------------------------------------------------------------
--  Function......... : cameraScale
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.cameraScale ( numPointables )
--------------------------------------------------------------------------------
	
	--
    -- Move camera forward/back based on scale.
    --
    if(numPointables == 2)
    then
        local nScale = sbLeap.getFrameScale ( 5 )
        if(math.abs ( nScale - 1 ) > 0.1)
        then
            -- check the direction of the 2 pointables
            --[[
            local bMovingIntoScreen = true
            for nPointableIndex = 0, 1
            do
                local nPointableID = sbLeap.getFramePointable ( nPointableIndex )
                local vX, vY, vZ = sbLeap.getPointableTipVelocity ( nPointableID )
                log.message ( vZ )
                -- if the pointable is moving out of the screen, abort 
                if(vZ > 0)
                then
                    bMovingIntoScreen = false
                    break
                end
            end
            ]]
            --if(bMovingIntoScreen)
            --then
                local dt = application.getLastFrameTime ( )
                object.translate ( application.getCurrentUserActiveCamera ( ), 0, 0, (nScale - 1) * -dt * 50, object.kLocalSpace )
            --end
        end
       
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
