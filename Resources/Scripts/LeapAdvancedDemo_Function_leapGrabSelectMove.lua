--------------------------------------------------------------------------------
--  Function......... : leapGrabSelectMove
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapGrabSelectMove ( numHands, numFingers )
--------------------------------------------------------------------------------
	
	if(numHands ~= 1) then return 0 end
    
    --
    -- Get the radius
    --
    local handID = sbLeap.getHand ( 0 )
    local radius = sbLeap.getHandSphereRadius ( handID ) * this.nScaleFactor ( )
    local x, y, z = sbLeap.getHandSphereCentre ( handID )
    x, y, z = this.leapCoordinateToCameraSpace ( x, y, z )
    
    local bGrabbing = this.nLastHandRadius ( ) > radius
    this.nLastHandRadius ( radius )
    
    --
    -- An object isn't selected
    --
    if(not this.hSelectedObject ( ))
    then
        if(bGrabbing and radius < 3.2)
        then
            --try to select an object        
            local hScene = application.getCurrentUserScene ( )
            
            local hIntersection
            local nLargestIntersection = 999999
            for sceneObjectIndex = 0, scene.getObjectCount ( hScene ) - 1
            do
                local hObject = scene.getObjectAt ( hScene, sceneObjectIndex )
                if(object.getModelName ( hObject ) == "cube")
                then
                    local posX, posY, posZ = object.getBoundingSphereCenter ( hObject )
                    local objR = object.getBoundingSphereRadius ( hObject )
                    
                    -- if the distance between the centers is < sum of radii then we intersect
                    local dx, dy, dz = math.vectorSubtract ( x, y, z, posX, posY, posZ )
                    
                    local distanceBetweenCenters = math.vectorLength ( dx, dy, dz )
                    if(distanceBetweenCenters < objR + radius)
                    then
                        -- If multiple objects intersect, pick the one with the largest intersection
                        if(distanceBetweenCenters < nLargestIntersection)
                        then
                            hIntersection = hObject
                            nLargestIntersection = distanceBetweenCenters
                        end
                    end
                end
            end
            
            --Pick the object up
            if(hIntersection)
            then
                this.hSelectedObject ( hIntersection )
                dynamics.enableDynamics ( hIntersection, false )
            end
        end
    else
    --
    -- An object is selected
    --
        if(numFingers > 0)
        then
            -- Throw the object
            local vx, vy, vz = sbLeap.getPalmVelocity ( handID )
            vx, vy, vz = this.leapCoordinateToCameraSpace ( vx, vy, vz )
            
            dynamics.enableDynamics ( this.hSelectedObject ( ), true )
            dynamics.setLinearVelocity ( this.hSelectedObject ( ), vx, vy, vz, object.kGlobalSpace )
            this.hSelectedObject ( nil )
            
        else
            -- Move the object 
            local px, py, pz = sbLeap.getPalmPosition ( handID )
            px, py, pz = this.leapCoordinateToCameraSpace ( px, py, pz )
            
            object.setTranslation ( this.hSelectedObject ( ), px, py, pz, object.kGlobalSpace )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
