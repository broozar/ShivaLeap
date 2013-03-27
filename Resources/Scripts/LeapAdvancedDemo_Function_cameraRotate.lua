--------------------------------------------------------------------------------
--  Function......... : cameraRotate
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.cameraRotate ( )
--------------------------------------------------------------------------------
	
	local nRotX, nRotY, nRotZ = sbLeap.getFrameRotationAxis ( 4 )
    local nRotation = sbLeap.getFrameRotationAngle ( 4 )
    
    local hCamera = application.getCurrentUserActiveCamera ( )
    --local leapX, leapY, leapZ = object.transformPoint ( hCamera, 0, this.nLeapOriginY ( ), this.nLeapOriginZ ( ), object.kLocalSpace, object.kGlobalSpace )
    
	--object.rotateAround ( hCamera, leapX, leapY, leapZ, nRotX * nRotation, nRotY * nRotation, nRotZ * nRotation, object.kGlobalSpace )
	--object.rotateAround ( hCamera, 0, 0, 0, -nRotX * nRotation * 50, -nRotY * nRotation * 50, 0, object.kGlobalSpace )
	object.rotateAround ( hCamera, 0, 0, 0, 0, -nRotY * nRotation * 50, 0, object.kGlobalSpace )
    object.lookAt ( hCamera, 0, 0, 0, object.kGlobalSpace, 1 )
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
