--------------------------------------------------------------------------------
--  Handler.......... : onInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function LeapHandsForSceneDummy.onInit (  )
--------------------------------------------------------------------------------

    local hS = application.getCurrentUserScene ( )
    local o = this.getObject ( )
    local mn = this.HandModelName ( )
    local hH = nil
    
    -- make sure hands model is available
    if application.isModelReferenced ( mn ) == true then
        -- create hand model
        hH = scene.createRuntimeObject ( hS, mn )
        -- store object
        this._oHands ( hH )
        
        -- parent hands to LEAPdummy
        object.setTransformOption ( hH, object.kTransformOptionInheritsParentScale, false )
        object.setParent ( hH, o, false )
        
        -- loop through objects and fill bone name tables
        this.setupBones ( )
        
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
