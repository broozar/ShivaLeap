--------------------------------------------------------------------------------
--  State............ : Selected
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function shapeAI.Selected_onLoop ( )
--------------------------------------------------------------------------------
	
    local x, y, z = object.transformPoint ( application.getCurrentUserActiveCamera ( ), 0, 0, -8, object.kLocalSpace, object.kGlobalSpace )
    
	object.translateTo ( this.getObject ( ), x, y, z, object.kGlobalSpace, application.getLastFrameTime ( ) )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
