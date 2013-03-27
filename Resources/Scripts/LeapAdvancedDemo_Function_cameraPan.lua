--------------------------------------------------------------------------------
--  Function......... : cameraPan
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.cameraPan ( numHands )
--------------------------------------------------------------------------------
	
    if(numHands == 1)
    then
        local nHandID = sbLeap.getHand ( 0 )
        local x, y, z = sbLeap.getPalmPosition ( nHandID )
        x, y, z = math.vectorScale ( x, y, z, this.nScaleFactor ( ) )
        
        local dt = application.getLastFrameTime ( )
        local finalX, finalY, finalZ = 0, 0, 0
        
        if(math.abs ( z ) > 2)
        then
            local dir = z > 1 and 1 or -1
            finalZ = dir * dt * 20
        end
        
        if(math.abs ( x ) > 2)
        then
            local dir = x > 1 and 1 or -1
            finalX = dir * dt * 20
        end
        
        object.translate ( application.getCurrentUserActiveCamera ( ), finalX, 0, finalZ, object.kLocalSpace )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
