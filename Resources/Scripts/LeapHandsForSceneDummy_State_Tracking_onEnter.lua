--------------------------------------------------------------------------------
--  State............ : Tracking
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapHandsForSceneDummy.Tracking_onEnter ( )
--------------------------------------------------------------------------------
	
    local hU = application.getCurrentUser ( )
    local l = this.LeapMotionUserAIModelName ( )
    
    if user.hasAIModel ( hU, l ) == false then
        log.warning ( "LEAP: User has no <<"..l..">> AIModel" )
        this.Idle ( )
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------