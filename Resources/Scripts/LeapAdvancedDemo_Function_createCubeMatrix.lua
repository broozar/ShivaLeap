--------------------------------------------------------------------------------
--  Function......... : createCubeMatrix
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.createCubeMatrix ( nCubeDimension, nScale, nSpacingFactor )
--------------------------------------------------------------------------------
	
    --
    -- Create an N x N x N matrix of cubes
    --
    
    local hScene = application.getCurrentUserScene ( )
        
    -- These offsets are simply to make the cube matrix be centered at 0,0,0
    local nXoffset = -nSpacingFactor - (nCubeDimension - 3) * nScale * 0.5
    local nYoffset = 2
    local nZoffset = -nSpacingFactor - (nCubeDimension - 3) * nScale * 0.5
    local nTableSize = table.getSize ( this.tMaterials ( ) ) - 1
    
    local dimensionSquared = math.pow ( nCubeDimension, 2 )
    local dimensionCubed = math.pow ( nCubeDimension, 3 )
    
    for blockIndex = 1, dimensionCubed
    do
        local hObject = scene.createRuntimeObject ( hScene, "cube" )
        
        -- Size
        object.setUniformScale ( hObject, nScale )
        
        -- Translation
        local x = nXoffset + math.mod ( blockIndex, nCubeDimension ) * nSpacingFactor
        local y = nYoffset + math.mod ( math.floor((blockIndex - 1) / dimensionSquared), nCubeDimension) * nSpacingFactor
        local z = nZoffset + math.mod ( math.floor((blockIndex - 1) / nCubeDimension), nCubeDimension ) * nSpacingFactor
        object.setTranslation ( hObject, x, y, z, object.kGlobalSpace )
                
        -- Material
        shape.setMeshSubsetMaterial ( hObject, 0, table.getAt ( this.tMaterials ( ), math.random ( 0, nTableSize ) ) )
        
        -- Sensor & dynamics
        this.objectAddSensor ( hObject, false )
        
        -- Init
        object.sendEvent ( hObject, "shapeAI", "onCaptureOrigin" )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
