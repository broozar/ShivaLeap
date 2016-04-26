--------------------------------------------------------------------------------
--  Function......... : setupBones
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapHandsForSceneDummy.setupBones ( )
--------------------------------------------------------------------------------
	
    local hO = this._oHands ( )
    local tr = this._htBonesRight ( )
    local tl = this._htBonesLeft ( )
    
	if ( (hO ~= nil) and (object.getChildCount ( hO ) >= 2) ) then
    
        -- get first child object - right arm
        local ra = object.getChildAt ( hO, 0 )
        this._oArmRight ( ra )

        hashtable.empty ( tr )
        for i=0, shape.getSkeletonJointCount ( ra ) do
            local name = shape.getSkeletonJointNameAt ( ra, i )
            if string.isEmpty ( name ) == false then
                local x,y,z = shape.getSkeletonJointRotation ( ra, name, object.kParentSpace )
                hashtable.add ( tr, name, x..","..y..","..z )
            end
        end
    
        -- get second child object - left arm
        local la = object.getChildAt ( hO, 1 )
        this._oArmLeft ( la )

        hashtable.empty ( tl )
        for i=0, shape.getSkeletonJointCount ( la ) do
            local name = shape.getSkeletonJointNameAt ( la, i )
            if string.isEmpty ( name ) == false then
                local x,y,z = shape.getSkeletonJointRotation ( la, name, object.kParentSpace )
                hashtable.add ( tl, name, x..","..y..","..z )
            end
        end
        
        this.Tracking ( )
        
        
        --[[ INFO: BONE NAMES IN THE SAMPLE MODEL
        
        1 base 2 middle 3 tip		
        ------------------ LEFT
        ID211688224 - pinky3
        ID211571904 - pinky2
		ID211455488 - pinky1
		ID55555520  - ring3
		ID55439200  - ring2
		ID55322784  - ring1 
		ID209841328 - middle3
		ID209724976 - middle2
		ID53354800  - middle1
		ID211224672 - index3
		ID211108288 - index2
		ID210991872 - index1
		ID54860064  - thumb1
		ID54975568  - thumb2
		ID55091936  - thumb3
		ID53238816  - wrist/palm
		ID53122928  - root/elbow
		------------------ RIGHT
		ID209226016 - pinky3
		ID209110128 - pinky2
		ID208994112 - pinky1
		ID208764048 - ring3
		ID208631904 - ring2
		ID208515888 - ring1
		ID208285888 - middle3
		ID208170000 - middle2
		ID208053936 - middle1
		ID207824000 - index3
		ID207708048 - index2
		ID207575792 - index1
		ID207333616 - thumb3
		ID207217632 - thumb2
		ID207101600 - thumb1
		ID206996304 - wrist/palm
		ID206742352 - root/elbow

        ]]--
        
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
