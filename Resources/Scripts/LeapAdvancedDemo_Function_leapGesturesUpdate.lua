--------------------------------------------------------------------------------
--  Function......... : leapGesturesUpdate
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapGesturesUpdate ( nNumGestures )
--------------------------------------------------------------------------------
	
	local hScene = application.getCurrentUserScene ( )
    
    -- Prevent multiple fingers from triggering a swipe gesture
    local bSwipeGate = false
    
	for gestureIndex = 0, nNumGestures - 1
    do
        local nGestureID, kGestureType, nDuration, kGesturesState = sbLeap.getGesture ( gestureIndex )
        --log.message ( "ID: ", nGestureID, " T: ", kGestureType, " D: ", nDuration, " S: ", kGesturesState )
        
        if(nGestureID > 0)
        then
            if(kGestureType == sbLeap.kGestureTypeSwipe and not bSwipeGate)
            then
                if(not this.hSelectedObject ( ))
                then
                    this.leapGestureSwipe ( nGestureID, kGesturesState )
                    bSwipeGate = true
                end
            elseif(kGestureType == sbLeap.kGestureTypeCircle)
            then
                if(kGesturesState == sbLeap.kGestureStateStart or kGesturesState == sbLeap.kGestureStateUpdate)
                then
                    this.Rewind ( )
                end
                --local nPointable, nNormX, nNormY, nNormZ, nCenterX, nCenterY, nCenterZ, nTraces, nRadius = sbLeap.getGestureCircle ( nGestureID )
                --log.message ( "Circle | ID: ", nPointable, " Normal (", nNormX, ", ", nNormY, ", ", nNormZ, ") Center(", nCenterX, ", ", nCenterY, ", ", nCenterZ, ") Traces: ", nTraces, " Radius: ", nRadius )
            elseif(kGestureType == sbLeap.kGestureTypeKeyTap)
            then
                local nPointable, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ = sbLeap.getGestureKeyTap ( nGestureID )
                nPosX, nPosY, nPosZ = math.vectorScale ( nPosX, nPosY, nPosZ, this.nScaleFactor ( ) )
                this.objectSelect ( nPosX, nPosY, nPosZ, nDirX, nDirY, nDirZ )
                --log.message ( "KeyTap | ID: ", nPointable, " Direction(", nDirX, ", ", nDirY, ", ", nDirZ, ") Position(", nPosX, ", ", nPosY, ", ", nPosZ, ")" )
            elseif(kGestureType == sbLeap.kGestureTypeScreenTap)
            then
                local nPointable, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ = sbLeap.getGestureScreenTap( nGestureID )
                --log.message ( "ScreenTap | ID: ", nPointable, " Direction(", nDirX, ", ", nDirY, ", ", nDirZ, ") Position(", nPosX, ", ", nPosY, ", ", nPosZ, ")" )
            end
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
