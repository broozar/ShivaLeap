--------------------------------------------------------------------------------
--  Function......... : leapGesturesUpdate
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMainAI.leapGesturesUpdate ( nNumGestures )
--------------------------------------------------------------------------------
	
	local hScene = application.getCurrentUserScene ( )
    
	for gestureIndex = 0, nNumGestures - 1
    do
        local nGestureID, kGestureType, nDuration, kGesturesState = sbLeap.getGesture ( gestureIndex )
        --log.message ( "ID: ", nGestureID, " T: ", kGestureType, " D: ", nDuration, " S: ", kGesturesState )
        
        if(nGestureID > 0)
        then
            if(kGestureType == sbLeap.kGestureTypeSwipe)
            then
                local nPointable, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ, nSpeed, nStartX, nStartY, nStartZ = sbLeap.getGestureSwipe ( nGestureID )
                --log.message ( "Swipe | ID: ", nPointable, " Direction(", nDirX, ", ", nDirY, ", ", nDirZ, ") Position(", nPosX, ", ", nPosY, ", ", nPosZ, ") Speed: ", nSpeed, " Start(", nStartX, ", ", nStartY, ", ", nStartZ, ")" )
            elseif(kGestureType == sbLeap.kGestureTypeCircle)
            then
                local nPointable, nNormX, nNormY, nNormZ, nCenterX, nCenterY, nCenterZ, nTraces, nRadius = sbLeap.getGestureCircle ( nGestureID )
                --log.message ( "Circle | ID: ", nPointable, " Normal (", nNormX, ", ", nNormY, ", ", nNormZ, ") Center(", nCenterX, ", ", nCenterY, ", ", nCenterZ, ") Traces: ", nTraces, " Radius: ", nRadius )
            elseif(kGestureType == sbLeap.kGestureTypeKeyTap)
            then
                local nPointable, nDirX, nDirY, nDirZ, nPosX, nPosY, nPosZ = sbLeap.getGestureKeyTap ( nGestureID )
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
