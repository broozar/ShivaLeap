--------------------------------------------------------------------------------
--  Function......... : objectAddSensor
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.objectAddSensor ( hObject, bSetIdle )
--------------------------------------------------------------------------------
	
    local maxX, maxY, maxZ = object.getBoundingBoxMax ( hObject )
    local minX, minY, minZ = object.getBoundingBoxMin ( hObject )
    
	sensor.add ( hObject, sensor.kShapeTypeBox )
    sensor.setBoxCenterAt ( hObject, 0, 0, 0, 0, object.kLocalSpace )
    sensor.setBoxSizeAt ( hObject, 0, (maxX - minX) * 0.5, (maxY - minY) * 0.5, (maxZ - minZ) * 0.5 )
	
    dynamics.createBoxBody ( hObject, (maxX - minX), (maxY - minY), (maxZ - minZ))
    dynamics.enableDynamics ( hObject, true )
    dynamics.enableCollisions ( hObject, true )
    dynamics.enableGravity ( hObject, true )
    dynamics.setLinearDamping ( hObject, 0.3 )
    dynamics.setBounce ( hObject, 0.01 )
    dynamics.setIdle ( hObject, bSetIdle )
    dynamics.setAutoIdleLinearThreshold ( hObject, 0.1 )
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
