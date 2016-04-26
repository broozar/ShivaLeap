--------------------------------------------------------------------------------
--  Function......... : init
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapMotionUser.init ( bUseVR )
--------------------------------------------------------------------------------
	
    if leapmotion.init ("LeapMotionUser") == true then
    
        -- set VR mode (or not)
        this._bUseVRmode ( bUseVR )
        
        -- define allowed gestures
        leapmotion.allowGestures ( true, true, true, true )
        
        -- set confidence limit for poses
        leapmotion.setConfidenceLimit ( 0.1 )
        
        -- define gesture options: uncomment if needed. units are given
        --leapmotion.setCircleOptions ( mm, rad )
        --leapmotion.setKeyTapOptions ( mm/s, s, mm )
        --leapmotion.setScreenTapOptions ( mm/s, s, mm )
        --leapmotion.setSwipeOptions ( mm, mm/s )
        
        -- reserve space in tracking data tables
        local tL = this._trackDataL ( )
        local tR = this._trackDataR ( )
        for i=0, 126 do
            table.add ( tL, 0 )
            table.add ( tR, 0 )
        end
        
        -- now switch to tracking state
        this.Track ( )
        
    else
        -- optional: tell user that init went wrong
        log.warning ( "leapinit wrong!" )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
