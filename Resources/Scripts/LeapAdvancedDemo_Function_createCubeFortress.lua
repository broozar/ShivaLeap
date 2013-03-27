--------------------------------------------------------------------------------
--  Function......... : createCubeFortress
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.createCubeFortress ( nScale, nHeight, centerX, centerY, centerZ, nRadius)
--------------------------------------------------------------------------------
	
	--
    -- Create a fortress with walls at radius nRadius from the center and a height of nHeight blocks
    --
    
    local hScene = application.getCurrentUserScene ( )
        
    local nTableSize = table.getSize ( this.tMaterials ( ) ) - 1
    
    -- calculate number of cubes that will fit in a row at radius nRadius
    local numberOfCubes = math.floor ( nRadius * 2 / nScale )
    
    log.message ( "Creating fortress of: " .. (numberOfCubes * 4 * nHeight) .. " cubes" )
    -- starting coordinates
    local startCoordinateX = centerX - (numberOfCubes * 0.5) * nScale
    local startCoordinateY = nScale * 0.5
    local startCoordinateZ = centerZ - (numberOfCubes * 0.5) * nScale
    
    for wallIndex = 1, 4
    do
        for heightIndex = 1, nHeight
        do
            for blockIndex = 1, numberOfCubes
            do
                local hObject = scene.createRuntimeObject ( hScene, "cube" )
                
                -- Size
                object.setUniformScale ( hObject, nScale )
                
                -- Translation
                local x = startCoordinateX + nScale * blockIndex
                local y = startCoordinateY + (heightIndex - 1) * nScale
                local z = startCoordinateZ
                object.setTranslation ( hObject, x, y, z, object.kGlobalSpace )
                
                -- Rotate the object around the origin based on which wall we're creating
                if(wallIndex == 2)
                then
                    object.rotateAround ( hObject, centerX, centerY, centerZ, 0, 90, 0, object.kGlobalSpace )
                elseif(wallIndex == 3)
                then
                    object.rotateAround ( hObject, centerX, centerY, centerZ, 0, 180, 0, object.kGlobalSpace )
                elseif(wallIndex == 4)
                then
                    object.rotateAround ( hObject, centerX, centerY, centerZ, 0, -90, 0, object.kGlobalSpace )
                end
                        
                -- Material
                shape.setMeshSubsetMaterial ( hObject, 0, table.getAt ( this.tMaterials ( ), 3 ) )
                
                -- Sensor & dynamics
                this.objectAddSensor ( hObject, true )
                
                -- Init
                object.sendEvent ( hObject, "shapeAI", "onCaptureOrigin" )
            end
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
