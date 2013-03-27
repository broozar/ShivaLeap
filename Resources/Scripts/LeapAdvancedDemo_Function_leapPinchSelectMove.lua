--------------------------------------------------------------------------------
--  Function......... : leapPinchSelectMove
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapPinchSelectMove ( numPointables )
--------------------------------------------------------------------------------
	    
    --
    -- Look at first 2 fingers and get their distance from each other and whether they're pinching
    --
    local pointableID1 = sbLeap.getFramePointable ( 0 )
    local pointableID2 = sbLeap.getFramePointable ( 1 )    
    
    local x, y, z = sbLeap.getPointableTipPosition ( pointableID1 )
    local x2, y2, z2 = sbLeap.getPointableTipPosition ( pointableID2 )
    
    x, y, z = this.leapCoordinateToCameraSpace ( x, y, z )
    x2, y2, z2 = this.leapCoordinateToCameraSpace ( x2, y2, z2 )
    
    local distance = math.vectorLength ( math.vectorSubtract ( x, y, z, x2, y2, z2 ) )
    local bPinching = this.nLastPinchDistance ( ) > distance
    this.nLastPinchDistance ( distance )
    
    --
    -- An object isn't selected
    --
    if(not this.hSelectedObject ( ))
    then
        if(numPointables == 2 and distance < 4 and bPinching)
        then
            --try to select an object        
            local hScene = application.getCurrentUserScene ( )

            local vx, vy, vz = sbLeap.getPointableTipVelocity ( pointableID1 )
            local vx2, vy2, vz2 = sbLeap.getPointableTipVelocity ( pointableID2 )
            
            local hObject = scene.getFirstHitSensor ( hScene, x, y, z, vx, vy, vz, 4 )
            local hObject2 = scene.getFirstHitSensor ( hScene, x2, y2, z2, vx2, vy2, vz2, 4 )
            
            if(hObject and hObject2 and object.isEqualTo ( hObject, hObject2 ))
            then
                this.hSelectedObject ( hObject )
                dynamics.enableDynamics ( hObject, false )
            end
        end
    else
    --
    -- An object is selected
    --
        if((distance > 5 and not bPinching) or numPointables < 2)
        then
            -- Apply the average velocity of the 2 fingers to the object
            local vx, vy, vz
            if(numPointables < 2)
            then
                -- If the # fingers goes from 2 to 1, launch block in -z
                vx, vy, vz = this.leapCoordinateToCameraSpace ( 0, 0, -5000 )
            else
                -- drop the block
                --[[
                vx, vy, vz = sbLeap.getPointableTipVelocity ( pointableID1 )
                local vx2, vy2, vz2 = sbLeap.getPointableTipVelocity ( pointableID2 )
                local fx, fy, fz = (vx + vx2) * 0.5, (vy + vy2) * 0.5, (vz + vz2) * 0.5
                vx, vy, vz = this.leapCoordinateToCameraSpace ( fx, fy, fz )
                ]]
                vx, vy, vz = 0, 0, 0
            end
            dynamics.enableDynamics ( this.hSelectedObject ( ), true )
            dynamics.setLinearVelocity ( this.hSelectedObject ( ), vx, vy, vz, object.kGlobalSpace )
            this.hSelectedObject ( nil )
            
        else            
            -- Move the object to the midway point between the 2 fingers
            local dx, dy, dz = math.vectorSubtract ( x, y, z, x2, y2, z2 )
            dx, dy, dz = math.vectorSetLength ( dx, dy, dz, distance * 0.5 )
            
            object.setTranslation ( this.hSelectedObject ( ), x - dx, y - dy, z - dz, object.kGlobalSpace )
        end
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
