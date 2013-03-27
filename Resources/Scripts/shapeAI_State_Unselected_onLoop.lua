--------------------------------------------------------------------------------
--  State............ : Unselected
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function shapeAI.Unselected_onLoop ( )
--------------------------------------------------------------------------------
	
	local xo, yo, zo = table.getRangeAt ( this.tOriginalLocation ( ), 0, 3 )    
    object.translateTo ( this.getObject ( ), xo, yo, zo, object.kGlobalSpace, application.getLastFrameTime ( ) )
    
    local x, y, z = object.getTranslation ( this.getObject ( ), object.kGlobalSpace )
    
    if(x == x0 and y == yo and z == zo)
    then
        this.Idle ( )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
