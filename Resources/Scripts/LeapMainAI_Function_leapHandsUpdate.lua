--------------------------------------------------------------------------------
--  Function......... : leapHandsUpdate
--  Author........... : Zachary Burke
--  Description...... : Update the translation and rotation of all hands.
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMainAI.leapHandsUpdate ( nNumHands, bDrawSpheres )
--------------------------------------------------------------------------------
	
    local hScene = application.getCurrentUserScene()
    
	for handIndex = 0, nNumHands - 1
    do
        -- Only allow nHandsMAximum hands
        if(handIndex > this.nHandsMaximum ( ) - 1) then return end
        
        -- Get the tagged hand based on this hand index
        -- Note that leap does not distinguish between left/right hand
        local hHand = scene.getTaggedObject ( hScene, "hand" .. handIndex )
        
        --
        -- Get hand ID and number of fingers & tools
        --
        local handID, fcount, tcount = sbLeap.getHand ( handIndex )
        
        --
        -- Get the position of the palm, the palm normal and the direction the
        -- hand is facing.
        --
        local handX, handY, handZ = sbLeap.getPalmPosition ( handID )
        local normX, normY, normZ = sbLeap.getPalmNormal( handID )
        local dirX, dirY, dirZ = sbLeap.getHandDirection ( handID )
        
        --
        -- Scale the Leap axis
        --
        handX, handY, handZ = math.vectorScale ( handX, handY, handZ, this.nScaleFactor ( ) )        
                
        --
        -- Position the hand and point it in the direction we're looking at 
        -- using the negative palm normal as up.  If you instead use the positive
        -- palm normal, the hand will flip and look like a left hand.
        --
        object.setTranslation ( hHand, handX, handY, handZ, object.kGlobalSpace )
        local nx, ny, nz = math.vectorAdd ( handX, handY, handZ, dirX, dirY, dirZ )            
        object.lookAtWithUp ( hHand, nx, ny, nz, -normX, -normY, -normZ, object.kGlobalSpace, 1 )
        object.setVisible ( hHand, true )
        
        if(bDrawSpheres)
        then
            local hSphere = scene.getTaggedObject ( hScene, "sphere" .. handIndex )
            local sphereX, sphereY, sphereZ = sbLeap.getHandSphereCentre ( handID )
            local sphereR = sbLeap.getHandSphereRadius ( handID )
            
            sphereX, sphereY, sphereZ = math.vectorScale ( sphereX, sphereY, sphereZ, this.nScaleFactor ( ) )
            sphereR = sphereR * this.nScaleFactor ( )
            
            object.setTranslation ( hSphere, sphereX, sphereY, sphereZ, object.kGlobalSpace )
            object.setUniformScale ( hSphere, sphereR * 0.5)
            object.setVisible ( hSphere, true )
        end
    end
    
    --
    -- Hide any hands and spheres that aren't around anymore
    --
    for handIndex = nNumHands, this.nHandsMaximum ( ) - 1
    do
        local hHand = scene.getTaggedObject ( hScene, "hand" .. handIndex )
        local hSphere = scene.getTaggedObject ( hScene, "sphere" .. handIndex )
        object.setVisible ( hHand, false )
        object.setVisible ( hSphere, false )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
