--------------------------------------------------------------------------------
--  Function......... : leapGestureSwipe
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapGestureSwipe ( nGestureID, kGestureState )
--------------------------------------------------------------------------------
	
	local nPointable, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ, nSpeed, nStartX, nStartY, nStartZ = sbLeap.getGestureSwipe ( nGestureID )
    
    if(kGestureState == sbLeap.kGestureStateStart or kGestureState == sbLeap.kGestureStateUpdate)
    then
        local absX = math.abs ( nDirX )
        local absY = math.abs ( nDirY )
        local absZ = math.abs ( nDirZ )
        
        --
        -- Swipe up to unselect
        --
        if(nDirY > 0 and nDirY > absX)
        then
            if(this.hSelectedObject ( ))
            then
                object.sendEvent ( this.hSelectedObject ( ), "shapeAI", "onUnselected" )
                this.hSelectedObject ( nil )
            end
        --
        -- Swipe left/right to rotate camera
        --
        elseif(absX > 0 and absX > absY and absX > absZ)
        then
            -- origin of camera is 0, 5, 20
            local destX, destY, destZ
            local x, y, z = object.getTranslation ( application.getCurrentUserActiveCamera ( ), object.kGlobalSpace )
            local quadrant = 0
            
            --
            -- Determine Quadrant
            --  0 (0, -20)
            -- 1+3
            --  2 (0, 20)
            x = math.roundToNearestInteger ( x )
            z = math.roundToNearestInteger ( z )
            
            if(x < 0 and z == 0) then quadrant = 1 end
            if(x == 0 and z < 0) then quadrant = 0 end
            if(x > 0 and z == 0) then quadrant = 3 end
            if(x == 0 and z > 0) then quadrant = 2 end
            
            --log.message ( "you are in quadrant: " .. quadrant )
            -- rotate CCW
            if(nDirX > 0)
            then    
                quadrant = quadrant + 1
                if(quadrant > 3) then quadrant = 0 end
            else
                quadrant = quadrant - 1
                if(quadrant < 0) then quadrant = 3 end
            end
           
            --log.message ( "destination: " .. quadrant )
            if(quadrant == 0)
            then
                destX = 0
                destY = 5
                destZ = -20
            elseif(quadrant == 1)
            then
                destX = -20
                destY = 5
                destZ = 0
            elseif(quadrant == 2)
            then
                destX = 0
                destY = 5
                destZ = 20
            elseif(quadrant == 3)
            then
                destX = 20
                destY = 5
                destZ = 0
            end
            
            local t = this.tCameraDestination ( )
            table.empty ( t )
            table.add ( t, destX )
            table.add ( t, destY )
            table.add ( t, destZ )
            this.RotateCamera ( )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
