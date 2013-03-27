--------------------------------------------------------------------------------
--  Function......... : leapInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapAdvancedDemo.leapInit ( )
--------------------------------------------------------------------------------
	
	local nResult = sbLeap.connect ( )
    log.message ( "Leap Connect result: ", nResult )
    local time = system.getUnixTimestampString ( )
    local startTime = string.toNumber (string.getSubString ( time, string.getLength ( time ) - 5, 5))
    local timer = 0
    
    while ((sbLeap.isConnected ( ) == false) and (timer < 3)) do
        local strTime = system.getUnixTimestampString ( )
        local nowTime = string.toNumber (string.getSubString ( strTime, string.getLength ( strTime ) - 5, 5))
        timer = nowTime - startTime
        log.message ( "Start Time: ", startTime, " Timer: ", timer )
    end
    
    if (timer > 2 ) then
        log.message ( "Connection failed" )
        sbLeap.disconnect()
        application.quit ( )
    else
        log.message ( "Device connected" )
        
        --
        -- Gestures
        --        
        sbLeap.enableGesture ( sbLeap.kGestureTypeSwipe, true )
        sbLeap.enableGesture ( sbLeap.kGestureTypeCircle, true )
        --sbLeap.enableGesture ( sbLeap.kGestureTypeScreenTap, true )
        --sbLeap.enableGesture ( sbLeap.kGestureTypeKeyTap, true )
        
        log.message ( "\n------Gestures------" )
        if(sbLeap.isGestureEnabled ( sbLeap.kGestureTypeSwipe ))     then log.message ( "  Swipe enabled" ) end
        if(sbLeap.isGestureEnabled ( sbLeap.kGestureTypeCircle ))    then log.message ( "  Circle enabled" ) end
        if(sbLeap.isGestureEnabled ( sbLeap.kGestureTypeScreenTap )) then log.message ( "  Screen Tap enabled" ) end
        if(sbLeap.isGestureEnabled ( sbLeap.kGestureTypeKeyTap ))    then log.message ( "  Key Tap enabled" ) end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
