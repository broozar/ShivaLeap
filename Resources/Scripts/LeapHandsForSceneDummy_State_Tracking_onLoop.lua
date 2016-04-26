--------------------------------------------------------------------------------
--  State............ : Tracking
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapHandsForSceneDummy.Tracking_onLoop ( )
--------------------------------------------------------------------------------
	
    if not leapmotion.isInitialized ( ) then return end
    
    local ar = this._oArmRight ( )
    local al = this._oArmLeft ( )
    
    local br = this._htBonesRight ( )
    local bl = this._htBonesLeft ( )
    
    local hU = application.getCurrentUser ( )
    local un = this.LeapMotionUserAIModelName ( )
    local tr = user.getAIVariable ( hU, un, "_trackDataR" )
    local tl = user.getAIVariable ( hU, un, "_trackDataL" )
    local t = table.newInstance ( )
    
    ------------------------------------------------
    -- right arm

    -- wrist
    shape.overrideSkeletonJointTranslation ( ar, "ID206742352", table.getAt ( tr, 1 ), table.getAt ( tr, 2 ), table.getAt ( tr, 3 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID206742352", table.getAt ( tr, 4 ), table.getAt ( tr, 5 ), table.getAt ( tr, 6 ), table.getAt ( tr, 7 ), object.kParentSpace, 1 )

    -- thumb
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID207101600", table.getAt ( tr, 18 ), table.getAt ( tr, 19 ), table.getAt ( tr, 20 ), table.getAt ( tr, 21 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID207217632", table.getAt ( tr, 22 ), table.getAt ( tr, 23 ), table.getAt ( tr, 24 ), table.getAt ( tr, 25 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID207333616", table.getAt ( tr, 26 ), table.getAt ( tr, 27 ), table.getAt ( tr, 28 ), table.getAt ( tr, 29 ), object.kParentSpace, 1 )

    -- index
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID207575792", table.getAt ( tr, 35 ), table.getAt ( tr, 36 ), table.getAt ( tr, 37 ), table.getAt ( tr, 38 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID207708048", table.getAt ( tr, 39 ), table.getAt ( tr, 40 ), table.getAt ( tr, 41 ), table.getAt ( tr, 42 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID207824000", table.getAt ( tr, 43 ), table.getAt ( tr, 44 ), table.getAt ( tr, 45 ), table.getAt ( tr, 46 ), object.kParentSpace, 1 )

    -- middle
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208053936", table.getAt ( tr, 52 ), table.getAt ( tr, 53 ), table.getAt ( tr, 54 ), table.getAt ( tr, 55 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208170000", table.getAt ( tr, 56 ), table.getAt ( tr, 57 ), table.getAt ( tr, 58 ), table.getAt ( tr, 59 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208285888", table.getAt ( tr, 60 ), table.getAt ( tr, 61 ), table.getAt ( tr, 62 ), table.getAt ( tr, 63 ), object.kParentSpace, 1 )
    
    -- ring
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208515888", table.getAt ( tr, 69 ), table.getAt ( tr, 70 ), table.getAt ( tr, 71 ), table.getAt ( tr, 72 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208631904", table.getAt ( tr, 73 ), table.getAt ( tr, 74 ), table.getAt ( tr, 75 ), table.getAt ( tr, 76 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208764048", table.getAt ( tr, 77 ), table.getAt ( tr, 78 ), table.getAt ( tr, 79 ), table.getAt ( tr, 80 ), object.kParentSpace, 1 )
    
    -- pinky
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID208994112", table.getAt ( tr, 86 ), table.getAt ( tr, 87 ), table.getAt ( tr, 88 ), table.getAt ( tr, 89 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID209110128", table.getAt ( tr, 90 ), table.getAt ( tr, 91 ), table.getAt ( tr, 92 ), table.getAt ( tr, 93 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( ar, "ID209226016", table.getAt ( tr, 94 ), table.getAt ( tr, 95 ), table.getAt ( tr, 96 ), table.getAt ( tr, 97 ), object.kParentSpace, 1 )
    
    
    ------------------------------------------------
    -- left arm
    
    -- wrist
    shape.overrideSkeletonJointTranslation ( al, "ID53122928", table.getAt ( tl, 1 ), table.getAt ( tl, 2 ), table.getAt ( tl, 3 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID53122928", table.getAt ( tl, 4 ), table.getAt ( tl, 5 ), table.getAt ( tl, 6 ), table.getAt ( tl, 7 ), object.kParentSpace, 1 )

    -- thumb
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID54860064", table.getAt ( tl, 18 ), table.getAt ( tl, 19 ), table.getAt ( tl, 20 ), table.getAt ( tl, 21 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID54975568", table.getAt ( tl, 22 ), table.getAt ( tl, 23 ), table.getAt ( tl, 24 ), table.getAt ( tl, 25 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID55091936", table.getAt ( tl, 26 ), table.getAt ( tl, 27 ), table.getAt ( tl, 28 ), table.getAt ( tl, 29 ), object.kParentSpace, 1 )

    -- index
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID210991872", table.getAt ( tl, 35 ), table.getAt ( tl, 36 ), table.getAt ( tl, 37 ), table.getAt ( tl, 38 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID211108288", table.getAt ( tl, 39 ), table.getAt ( tl, 40 ), table.getAt ( tl, 41 ), table.getAt ( tl, 42 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID211224672", table.getAt ( tl, 43 ), table.getAt ( tl, 44 ), table.getAt ( tl, 45 ), table.getAt ( tl, 46 ), object.kParentSpace, 1 )
    
    -- middle
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID53354800", table.getAt ( tl, 52 ), table.getAt ( tl, 53 ), table.getAt ( tl, 54 ), table.getAt ( tl, 55 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID209724976", table.getAt ( tl, 56 ), table.getAt ( tl, 57 ), table.getAt ( tl, 58 ), table.getAt ( tl, 59 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID209841328", table.getAt ( tl, 60 ), table.getAt ( tl, 61 ), table.getAt ( tl, 62 ), table.getAt ( tl, 63 ), object.kParentSpace, 1 )
    
    -- ring
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID55322784", table.getAt ( tl, 69 ), table.getAt ( tl, 70 ), table.getAt ( tl, 71 ), table.getAt ( tl, 72 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID55439200", table.getAt ( tl, 73 ), table.getAt ( tl, 74 ), table.getAt ( tl, 75 ), table.getAt ( tl, 76 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID55555520", table.getAt ( tl, 77 ), table.getAt ( tl, 78 ), table.getAt ( tl, 79 ), table.getAt ( tl, 80 ), object.kParentSpace, 1 )
    
    -- pinky
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID211455488", table.getAt ( tl, 86 ), table.getAt ( tl, 87 ), table.getAt ( tl, 88 ), table.getAt ( tl, 89 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID211571904", table.getAt ( tl, 90 ), table.getAt ( tl, 91 ), table.getAt ( tl, 92 ), table.getAt ( tl, 93 ), object.kParentSpace, 1 )
    shape.overrideSkeletonJointRotationQuaternion ( al, "ID211688224", table.getAt ( tl, 94 ), table.getAt ( tl, 95 ), table.getAt ( tl, 96 ), table.getAt ( tl, 97 ), object.kParentSpace, 1 )

--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------

-- tracking data
-- table data layout
--
-- 0 = hand id
-- 1 = palm x
-- 2 = palm y
-- 3 = palm z
-- 4 = palm yaw
-- 5 = palm pitch
-- 6 = palm roll
-- 
-- 7 = wrist x
-- 8 = wrist y
-- 9 = wrist z
-- 10 = elbow x
-- 11 = elbow y
-- 12 = elbow z
--
--
-- finger segments: 0 meta, 1 prox, 2 mid, 3 dist
--
-- 13 = ThumbID
-- 14 = Thumb[0]yaw
-- 15 = Thumb[0]pitch
-- 16 = Thumb[1]yaw
-- 17 = Thumb[1]pitch
-- 18 = Thumb[2]yaw
-- 19 = Thumb[2]pitch
-- 20 = Thumb[3]yaw
-- 21 = Thumb[3]pitch
-- 22 = IndexID
-- 23 = Index[0]yaw
-- 24 = Index[0]pitch
-- 25 = Index[1]yaw
-- 26 = Index[1]pitch
-- 27 = Index[2]yaw
-- 28 = Index[2]pitch
-- 29 = Index[3]yaw
-- 30 = Index[3]pitch
-- 31 = MiddleID
-- 32 = Middle[0]yaw
-- 33 = Middle[0]pitch
-- 34 = Middle[1]yaw
-- 35 = Middle[1]pitch
-- 36 = Middle[2]yaw
-- 37 = Middle[2]pitch
-- 38 = Middle[3]yaw
-- 39 = Middle[3]pitch
-- 40 = RingID
-- 41 = Ring[0]yaw
-- 42 = Ring[0]pitch
-- 43 = Ring[1]yaw
-- 44 = Ring[1]pitch
-- 45 = Ring[2]yaw
-- 46 = Ring[2]pitch
-- 47 = Ring[3]yaw
-- 48 = Ring[3]pitch
-- 49 = PinkyID
-- 50 = Pinky[0]yaw
-- 51 = Pinky[0]pitch
-- 52 = Pinky[1]yaw
-- 53 = Pinky[1]pitch
-- 54 = Pinky[2]yaw
-- 55 = Pinky[2]pitch
-- 56 = Pinky[3]yaw
-- 57 = Pinky[3]pitch
--
-- for both hands