section.begin
   Name = InitialFly
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'PROJECTILE\PROJECTILE.INC\INITIALFLY';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure SetupBehaviour(goHandle : Integer; startX, startY, startZ, endX, endY, endZ, speed, parabolaFactor : Float; useRotate : Boolean; pitchStart, pitchMid, pitchEnd : Float);
      [*] = ;begin
      [*] = ;   var pathLenght : Float = VectorDistance(startX, startY, startZ, endX, endY, endZ);
      [*] = ;   SetGameObjectPositionByHandle(goHandle, startX, startY, startZ);
      [*] = ;   //SetGameObjectPitchAngleByHandle(goHandle, pitchStart);
      [*] = ;
      [*] = ;   var behHnd : Integer = BehaviourCreate(goHandle, 'TXMoveRotateWaveBehaviour', true, false);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'OffsetTime', 0);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosX', 'wscNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosY', 'wscNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'WaveSinCosZ', 'wscNone');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'ClearPaths', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathPosition', 'mppUse');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathScale', 'mpsNone');
      [*] = ;   if (useRotate) then
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprUse')
      [*] = ;   else
      [*] = ;   SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprNone');
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,0]', startX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,0]', startY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,0]', startZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesPitchAngle[0,0]', pitchStart);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,0]', speed);
      [*] = ;
      [*] = ;   var midX : Float = (startX+endX)/2;
      [*] = ;   var midY : Float = (startY+endY)/2 + pathLenght*parabolaFactor;
      [*] = ;   var midZ : Float = (startZ+endZ)/2;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,1]', midX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,1]', midY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,1]', midZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesPitchAngle[0,1]', pitchMid);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,1]', speed);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,2]', endX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,2]', endY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,2]', endZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesPitchAngle[0,2]', pitchEnd);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,2]', speed*0.02);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'OnStatePathTravelStop', 'OnPathTravelStop');
      [*] = ;
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;   var estimateTime : Float = GetBehaviourFloatProperty(behHnd, 'EstimateTime[0]');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'StartTime[0]', GetCurrentTime-(Random*estimateTime));
      [*] = ;   SetBehaviourStringProperty(behHnd, 'StartPathTravel', '');
      [*] = ;end;
      [*] = ;
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle();
      [*] = ;if not gc_RecycleProjectiles then
      [*] = ;begin
      [*] = ;   _fx_ClearFX(myHnd, true, true);
      [*] = ;   BehaviourClear(myHnd);
      [*] = ;end
      [*] = ;else
      [*] = ;   SetGameObjectMyVisible(true);
      [*] = ;
      [*] = ;var targetGOUID : Integer = GetIntValueByIndex(gc_stack_projectile_iTarget);
      [*] = ;var targetGOHandle : Integer = GetGameObjectHandleByUniqueId(targetGOUID);
      [*] = ;if (targetGOHandle<>0) then
      [*] = ;begin
      [*] = ;   var bbX, bbY, bbZ : Float;
      [*] = ;   GetGameObjectAxisAlignedDimensionsByHandle(targetGOHandle, bbX, bbY, bbZ);
      [*] = ;
      [*] = ;   var ownerGOHnd : Integer = GetGameObjectHandleByUniqueId(GetIntValueByIndex(gc_stack_projectile_iOwner));
      [*] = ;   var startX, startY, startZ : Float;
      [*] = ;   if (ownerGOHnd<>0) then
      [*] = ;   begin
      [*] = ;      if _log then _Log_map(_log_name+' Owner: '+GetGameObjectBaseNameByHandle(ownerGOHnd));
      [*] = ;      startX := GetGameObjectPositionXByHandle(ownerGOHnd);
      [*] = ;      startY := GetGameObjectPositionYByHandle(ownerGOHnd);
      [*] = ;      startZ := GetGameObjectPositionZByHandle(ownerGOHnd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      startX := GetGameObjectMyPositionX;
      [*] = ;      startY := GetGameObjectMyPositionY;
      [*] = ;      startZ := GetGameObjectMyPositionZ;
      [*] = ;   end;
      [*] = ;   var endX : Float = GetGameObjectPositionXByHandle(targetGOHandle);
      [*] = ;   var endY : Float = GetGameObjectPositionYByHandle(targetGOHandle);
      [*] = ;   var endZ : Float = GetGameObjectPositionZByHandle(targetGOHandle);
      [*] = ;
      [*] = ;   var dirX : Float = endX - startX;
      [*] = ;   var dirY : Float = 0;
      [*] = ;   var dirZ : Float = endZ - startZ;
      [*] = ;   var angle : Float = 0;
      [*] = ;   if VectorLength(dirX, dirY, dirZ) > 0.0001 then
      [*] = ;   begin
      [*] = ;      angle := VectorAngle(dirX, dirY, dirZ, -1, 0, 0);
      [*] = ;      if dirZ < 0 then
      [*] = ;      angle := -angle;
      [*] = ;   end;
      [*] = ;   const cEmptyProjDefaultScale = 0.08;
      [*] = ;   const cTypicalProjDefaultScale = 1.948717;
      [*] = ;
      [*] = ;   var scale, defaultScale : Float = 1;
      [*] = ;   var targetH : Float = 0.5; // Target point height in percent of target unit bounding box. 0.5 - means fire at unit center. 0.9 - means fire at head.
      [*] = ;   var speed : Float = 30;
      [*] = ;   var projX, projY, projZ, parabola : Float = 0;
      [*] = ;   var pitchStart, pitchMid, pitchEnd : Float = 0;
      [*] = ;   var useRotate : Boolean = False;
      [*] = ;   if (ownerGOHnd<>0) then
      [*] = ;   begin
      [*] = ;      case GetGameObjectBaseNameByHandle(ownerGOHnd) of
      [*] = ;         'slinger' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 1.25;
      [*] = ;            speed := 32;
      [*] = ;            parabola := 0.125;
      [*] = ;            projX := -3.555;
      [*] = ;            projY := 2.8;
      [*] = ;            projZ := 0.22;
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailstone', 'trailstone');
      [*] = ;         end;
      [*] = ;         'halfling', 'halflingforager', 'halflingspy' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 1.25;
      [*] = ;            speed := 32;
      [*] = ;            parabola := 0.125;
      [*] = ;            projX := -1.8616+0.2;
      [*] = ;            projY := 0.9613+0.8;
      [*] = ;            projZ := -0.6454+0.55;
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailstone', 'trailstone');
      [*] = ;         end;
      [*] = ;         'crossbowman' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 40;
      [*] = ;            parabola := 0.0625;
      [*] = ;            projX := -1.8665;
      [*] = ;            projY := 2.6455;
      [*] = ;            projZ := -0.0625;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.bolt.crossbowman');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'crossbowman');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'archer' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 35;
      [*] = ;            //targetH := 0.6;
      [*] = ;            //parabola := 0.085;
      [*] = ;            targetH := 0.75;
      [*] = ;            parabola := 0.025;
      [*] = ;            projX := -0.7567;
      [*] = ;            projY := 2.9554;
      [*] = ;            projZ := -0.0272;
      [*] = ;            {useRotate := True;
      [*] = ;            pitchStart := 10+180;
      [*] = ;            pitchMid := 20+180;
      [*] = ;            pitchEnd := 45+180;}
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'scout' : begin
      [*] = ;            if _unit_CheckAbility(ownerGOHnd, gc_ability_magic_shot) > 0 then
      [*] = ;            begin
      [*] = ;               defaultScale := cEmptyProjDefaultScale;
      [*] = ;               scale := 0.6;
      [*] = ;               speed := 12;
      [*] = ;               targetH := 0.5;
      [*] = ;               parabola := 0.1;
      [*] = ;               projX := -4.8222;
      [*] = ;               projY := 4.2874;
      [*] = ;               projZ := 0.2604;
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;               GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               defaultScale := cTypicalProjDefaultScale;
      [*] = ;               speed := 35;
      [*] = ;               targetH := 0.85;
      [*] = ;               parabola := 0.025;
      [*] = ;               projX := -1.3092;
      [*] = ;               projY := 3.9894;
      [*] = ;               projZ := 0.2772;
      [*] = ;               SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;               SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;               MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'elf', 'elfdruid', 'elfranger' : begin
      [*] = ;            defaultScale := 2.204;
      [*] = ;            speed := 35;
      [*] = ;            targetH := 0.85;
      [*] = ;            parabola := 0.025;
      [*] = ;            projX := -0.8814;
      [*] = ;            projY := 3.8515;
      [*] = ;            projZ := 0.1325;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.elf');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'elf');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'horsearcher' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 35;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.025;
      [*] = ;            projX := -1.3031-0.75;
      [*] = ;            projY := 4.2650;
      [*] = ;            projZ := -0.1477;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'cataphract' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 35;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.025;
      [*] = ;            projX := -1.3031-0.75;
      [*] = ;            projY := 4.2650;
      [*] = ;            projZ := -0.1477;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'centaur' : begin
      [*] = ;            defaultScale := 2.204;
      [*] = ;            scale := 1.1;
      [*] = ;            speed := 35;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.025;
      [*] = ;            projX := -1.3031-0.75;
      [*] = ;            projY := 4.4650;
      [*] = ;            projZ := 0.4;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.elf');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'elf');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'assassin' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            targetH := 0.7;
      [*] = ;            scale := 1.1;
      [*] = ;            speed := 25;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -2.5395;
      [*] = ;            projY := 2.9775;
      [*] = ;            projZ := -0.0879;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.sword.assassin');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'assassin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailsword', 'trailsword');
      [*] = ;         end;
      [*] = ;         'spearman' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            targetH := 0.9;
      [*] = ;            scale := 1;
      [*] = ;            speed := 35;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := 0.9526;
      [*] = ;            projY := 4.2090;
      [*] = ;            projZ := -0.8509;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.pike.spearman');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'spearman');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailspear', 'trailspear');
      [*] = ;         end;
      [*] = ;         'barbarian' : begin
      [*] = ;            defaultScale := 0.044289;
      [*] = ;            targetH := 0.9;
      [*] = ;            scale := 1.16;
      [*] = ;            speed := 20;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -2.3446;
      [*] = ;            projY := 3.2617;
      [*] = ;            projZ := -0.1779;
      [*] = ;            useRotate := True;
      [*] = ;            pitchStart := 450;
      [*] = ;            pitchMid := 225;
      [*] = ;            pitchEnd := 5;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.axe.barbarian');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'barbarian');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailaxe', 'trailaxe');
      [*] = ;         end;
      [*] = ;         'thief' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            targetH := 0.5;
      [*] = ;            scale := 1.1;
      [*] = ;            speed := 25;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -3.1066;
      [*] = ;            projY := 2.5861;
      [*] = ;            projZ := 0.3714;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.knife.thief');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'thief');
      [*] = ;            MyGameObjectPFXSrcLibCreate('traildagger', 'traildagger');
      [*] = ;         end;
      [*] = ;         'wizard' : begin
      [*] = ;            if _unit_CheckAbility(ownerGOHnd, gc_ability_magic_shot) > 0 then
      [*] = ;            begin
      [*] = ;               defaultScale := cEmptyProjDefaultScale;
      [*] = ;               scale := 0.6;
      [*] = ;               speed := 12;
      [*] = ;               targetH := 0.5;
      [*] = ;               parabola := 0.1;
      [*] = ;               projX := -4.8222;
      [*] = ;               projY := 4.2874;
      [*] = ;               projZ := 0.2604;
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;               GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               defaultScale := cTypicalProjDefaultScale;
      [*] = ;               speed := 35;
      [*] = ;               targetH := 0.85;
      [*] = ;               parabola := 0.025;
      [*] = ;               projX := -1.3092;
      [*] = ;               projY := 3.9894;
      [*] = ;               projZ := 0.2772;
      [*] = ;               SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;               SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;               MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'mage', 'magewhite' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.6;
      [*] = ;            speed := 12;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -1.3810;
      [*] = ;            projY := 2.5760;
      [*] = ;            projZ := 0.1469;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         'mageblack' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.6;
      [*] = ;            speed := 12;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -1.3810;
      [*] = ;            projY := 2.5760;
      [*] = ;            projZ := 0.1469;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0_dark', 'shotvioletball0_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1_dark', 'shotvioletball1_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2_dark', 'shotvioletball2_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin_dark', 'shotvioletball0perlin_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2_dark', 'shotvioletballtrail2_dark');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin_dark', 'shotvioletball0perlin_dark', scale);
      [*] = ;         end;
      [*] = ;         'priest' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.6;
      [*] = ;            speed := 12;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3.3810;
      [*] = ;            projY := 3.0;
      [*] = ;            projZ := 0.1469;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         'warlock' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.6;
      [*] = ;            speed := 12;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3.3810;
      [*] = ;            projY := 3.0;
      [*] = ;            projZ := 0.1469;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0_dark', 'shotvioletball0_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1_dark', 'shotvioletball1_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2_dark', 'shotvioletball2_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin_dark', 'shotvioletball0perlin_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2_dark', 'shotvioletballtrail2_dark');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin_dark', 'shotvioletball0perlin_dark', scale);
      [*] = ;         end;
      [*] = ;         'devil' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 1.6;
      [*] = ;            speed := 12;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3;
      [*] = ;            projY := 11.0;
      [*] = ;            projZ := 0.5;
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'fireball_ball', 'fireball_ball');
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'fireball_trail', 'fireball_trail');
      [*] = ;            {MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);}
      [*] = ;         end;
      [*] = ;         'monk' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -1.5;
      [*] = ;            projY := 3.0;
      [*] = ;            projZ := 0.0;
      [*] = ;            //MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            //MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         'slug' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            speed := 13;
      [*] = ;            targetH := 0.25;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := 0;
      [*] = ;            projY := 0;
      [*] = ;            projZ := 0;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotslug', 'shotslug');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotslugperlin', 'shotslugperlin');
      [*] = ;         end;
      [*] = ;         'chimera' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            speed := 13;
      [*] = ;            targetH := 0.25;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3.5;
      [*] = ;            projY := 2.32;
      [*] = ;            projZ := 0.555;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotslug', 'shotslug');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotslugperlin', 'shotslugperlin');
      [*] = ;         end;
      [*] = ;         'shaman' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -1.7418;
      [*] = ;            projY := 2.3194;
      [*] = ;            projZ := 0.6259;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0_dark', 'shotvioletball0_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1_dark', 'shotvioletball1_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2_dark', 'shotvioletball2_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin_dark', 'shotvioletball0perlin_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2_dark', 'shotvioletballtrail2_dark');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin_dark', 'shotvioletball0perlin_dark', scale);
      [*] = ;         end;
      [*] = ;         'fairy', 'succubus' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -1.7418;
      [*] = ;            projY := 4.3194;
      [*] = ;            projZ := 0.6259;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball0', 'shotdarkball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball1', 'shotdarkball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball2', 'shotdarkball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball0perlin', 'shotdarkball0perlin');
      [*] = ;            //MyGameObjectPFXSrcLibCreate('shotdarkballtrail', 'shotdarkballtrail');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         'imp' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -1.7418;
      [*] = ;            projY := 2.3194;
      [*] = ;            projZ := 0.6259;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball0', 'shotdarkball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball1', 'shotdarkball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball2', 'shotdarkball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball0perlin', 'shotdarkball0perlin');
      [*] = ;            //MyGameObjectPFXSrcLibCreate('shotdarkballtrail', 'shotdarkballtrail');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         'lizardmanpriest' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.6;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.3;
      [*] = ;            projY := 2.5;
      [*] = ;            projZ := -1;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball0', 'shotdarkball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball1', 'shotdarkball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball2', 'shotdarkball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotdarkball0perlin', 'shotdarkball0perlin');
      [*] = ;            //MyGameObjectPFXSrcLibCreate('shotdarkballtrail', 'shotdarkballtrail');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         'sorcerer' : begin
      [*] = ;            //speed := 10;
      [*] = ;            //MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3.7139;
      [*] = ;            projY := 3.0644;
      [*] = ;            projZ := -0.1695;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0_dark', 'shotvioletball0_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1_dark', 'shotvioletball1_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2_dark', 'shotvioletball2_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin_dark', 'shotvioletball0perlin_dark');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2_dark', 'shotvioletballtrail2_dark');
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin_dark', 'shotvioletball0perlin_dark', scale);
      [*] = ;         end;
      [*] = ;         'spider', 'spiderblackwidow' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 1.25;
      [*] = ;            speed := 10;
      [*] = ;            parabola := 0.225;
      [*] = ;            projX := +5;
      [*] = ;            projY := 0;
      [*] = ;            projZ := -1;
      [*] = ;            _fx_GetOrCreateFXByID(myHnd, 'fxspiderfire', 0, 0, 0, 0, 0.5, 2);
      [*] = ;         end;
      [*] = ;         'basilisk' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 10;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -1.5;
      [*] = ;            projY := 3.0;
      [*] = ;            projZ := -1.25;
      [*] = ;            _fx_GetOrCreateFXByID(myHnd, 'fxstonetrail', 0, 0, 0, 0, 0.1, 7);
      [*] = ;         end;
      [*] = ;         'medusa' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 7;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -1.5;
      [*] = ;            projY := 3.0;
      [*] = ;            projZ := 0.0;
      [*] = ;            _fx_GetOrCreateFXByID(myHnd, 'fxstonetrail', 0, 0, 0, 0, 0.1, 7);
      [*] = ;         end;
      [*] = ;         'giant' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            scale := 1.25;
      [*] = ;            speed := 35;
      [*] = ;            projX := -7.5;
      [*] = ;            projY := 6.0;
      [*] = ;            useRotate := True;
      [*] = ;            pitchStart := -540;
      [*] = ;            pitchMid := -405;
      [*] = ;            pitchEnd := -180;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.stone.giant');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'giant_stone');
      [*] = ;         end;
      [*] = ;         'giantfire' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            scale := 1.25;
      [*] = ;            speed := 35;
      [*] = ;            projX := -7.5;
      [*] = ;            projY := 6.0;
      [*] = ;            useRotate := True;
      [*] = ;            pitchStart := -540;
      [*] = ;            pitchMid := -405;
      [*] = ;            pitchEnd := -180;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.stone.giant');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'giantfire_stone');
      [*] = ;         end;
      [*] = ;         'catapult' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            scale := 1.1;
      [*] = ;            speed := 30;
      [*] = ;            parabola := 0.15;
      [*] = ;            projX := -0.155; //5;
      [*] = ;            projY := 4.48; //6.0;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.stone.giant');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'giant_stone');
      [*] = ;         end;
      [*] = ;         'ballista' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 30;
      [*] = ;            scale := 2;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -2;
      [*] = ;            projY := 2.6455;
      [*] = ;            projZ := 0;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.bolt.crossbowman');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'crossbowman');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'warrior' : begin
      [*] = ;            if _unit_CheckAbility(ownerGOHnd, gc_ability_magic_shot) > 0 then
      [*] = ;            begin
      [*] = ;               defaultScale := cEmptyProjDefaultScale;
      [*] = ;               scale := 0.6;
      [*] = ;               speed := 12;
      [*] = ;               targetH := 0.5;
      [*] = ;               parabola := 0.1;
      [*] = ;               projX := -4.8222;
      [*] = ;               projY := 4.2874;
      [*] = ;               projZ := 0.2604;
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;               GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               defaultScale := cTypicalProjDefaultScale;
      [*] = ;               speed := 35;
      [*] = ;               targetH := 0.85;
      [*] = ;               parabola := 0.025;
      [*] = ;               projX := -1.3092;
      [*] = ;               projY := 3.9894;
      [*] = ;               projZ := 0.2772;
      [*] = ;               SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;               SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;               MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'commander' : begin
      [*] = ;            if _unit_CheckAbility(ownerGOHnd, gc_ability_magic_shot) > 0 then
      [*] = ;            begin
      [*] = ;               defaultScale := cEmptyProjDefaultScale;
      [*] = ;               scale := 0.6;
      [*] = ;               speed := 12;
      [*] = ;               targetH := 0.5;
      [*] = ;               parabola := 0.1;
      [*] = ;               projX := -4.8222;
      [*] = ;               projY := 4.2874;
      [*] = ;               projZ := 0.2604;
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;               MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;               GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               defaultScale := cTypicalProjDefaultScale;
      [*] = ;               speed := 35;
      [*] = ;               targetH := 0.85;
      [*] = ;               parabola := 0.025;
      [*] = ;               projX := -1.3092;
      [*] = ;               projY := 3.9894;
      [*] = ;               projZ := 0.2972;
      [*] = ;               SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.bolt.crossbowman');
      [*] = ;               SetGameObjectMaterialNameByHandle(myHnd, 'crossbowman');
      [*] = ;               MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;               //SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.arrow.archer');
      [*] = ;               //SetGameObjectMaterialNameByHandle(myHnd, 'archer');
      [*] = ;               //MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'lich' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.6;
      [*] = ;            speed := 12;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.8222;
      [*] = ;            projY := 4.2874;
      [*] = ;            projZ := 0.2604;
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'fxspheregreen0', 'fxspheregreen0');
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'acid_trail', 'acid_trail');
      [*] = ;         end;
      [*] = ;         'centaurchief' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            targetH := 0.9;
      [*] = ;            scale := 1;
      [*] = ;            speed := 35;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -2.8;
      [*] = ;            projY := 5.2090;
      [*] = ;            projZ := -1;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.pike.spearman');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'spearman');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailspear', 'trailspear');
      [*] = ;         end;
      [*] = ;         'centaurhuntsman' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            scale := 1.25;
      [*] = ;            speed := 14;
      [*] = ;            parabola := 0.125;
      [*] = ;            projX := -4.25;
      [*] = ;            projY := 3.8;
      [*] = ;            projZ := -0.2;
      [*] = ;            useRotate := True;
      [*] = ;            pitchStart := -450/2+180;
      [*] = ;            pitchMid := -225/2+180;
      [*] = ;            pitchEnd := -5+180;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.bolo.centaurhuntsman');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'centaurhuntsman');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailstone', 'trailstone');
      [*] = ;         end;
      [*] = ;         'dwarfmechanic' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 40;
      [*] = ;            parabola := 0.0625;
      [*] = ;            projX := -1.8665;
      [*] = ;            projY := 1.8455;
      [*] = ;            projZ := 0.30625;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.bolt.crossbowman');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'crossbowman');
      [*] = ;            //SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.bolt.dwarfmechanic');
      [*] = ;            //SetGameObjectMaterialNameByHandle(myHnd, 'dwarfmechanic');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         'goblinalchemist' : begin
      [*] = ;         end;
      [*] = ;         'goblinpoisonspit' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            targetH := 0.6;
      [*] = ;            scale := 0.025;
      [*] = ;            speed := 30;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -2;
      [*] = ;            projY := 2;
      [*] = ;            projZ := 0;
      [*] = ;            useRotate := True;
      [*] = ;            pitchStart := 90;
      [*] = ;            pitchMid := 90;
      [*] = ;            pitchEnd := 90;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.thorn.goblinpoisonspit');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'goblinpoisonspit');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailspear', 'trailspear');
      [*] = ;         end;
      [*] = ;         'orcthrower' : begin
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            targetH := 0.9;
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 20;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -3.3648;
      [*] = ;            projY := 3.0703-0.6;
      [*] = ;            projZ := 1.0251;
      [*] = ;            useRotate := True;
      [*] = ;            pitchStart := -160;
      [*] = ;            pitchMid := -80;
      [*] = ;            pitchEnd := -30;
      [*] = ;            //pitchStart := -180;
      [*] = ;            //pitchMid := -40;
      [*] = ;            //pitchEnd := -260;
      [*] = ;            SetGameObjectVisualPropertiesByHandle(myHnd, 'misc', 'weapon.club.orcthrower');
      [*] = ;            SetGameObjectMaterialNameByHandle(myHnd, 'orcthrower');
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailaxe', 'trailaxe');
      [*] = ;         end;
      [*] = ;         'dragon', 'dragonfire' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            targetH := 0.3;
      [*] = ;            scale := 7.2;
      [*] = ;            speed := 25;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -5.7;
      [*] = ;            projY := 4.4;
      [*] = ;            projZ := 0;
      [*] = ;            MyGameObjectPFXSrcLibCreate('dragonfire', 'dragonfire');
      [*] = ;            MyGameObjectPFXSrcLibCreate('dragonfiretrail0', 'dragonfiretrail0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('dragonfiretrail1', 'dragonfiretrail1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('dragonfiretrail2', 'dragonfiretrail2');
	  [*] = ;            _gui_PlaySound('spells', 'spell23'); //fireball sound
      [*] = ;         end;
      [*] = ;         'dragonunholy' : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            targetH := 0.3;
      [*] = ;            scale := 0.8;
      [*] = ;            speed := 20;
      [*] = ;            parabola := 0.0;
      [*] = ;            projX := -5.7;
      [*] = ;            projY := 4.4;
      [*] = ;            projZ := 0;
      [*] = ;            MyGameObjectPFXSrcLibCreate('fireball_ball', 'fireball_ball');
      [*] = ;            MyGameObjectPFXSrcLibCreate('fireball_trail', 'fireball_trail');
      [*] = ;            MyGameObjectPFXSrcLibCreate('fxspheregreen0', 'fxspheregreen0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('acid_trail', 'acid_trail');
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         if (GetIntValueByIndex(gc_stack_projectile_iType)=gc_projectile_iEmpty) then
      [*] = ;         begin
      [*] = ;            speed := 100;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   //if (ownerGOHnd=0) then
      [*] = ;   begin
      [*] = ;      case GetIntValueByIndex(gc_stack_projectile_iType) of
      [*] = ;         gc_projectile_iTower : begin  
      [*] = ;            defaultScale := cTypicalProjDefaultScale;
      [*] = ;            speed := 35;
      [*] = ;            targetH := 0.75;
      [*] = ;            parabola := 0.025;
      [*] = ;            MyGameObjectPFXSrcLibCreate('trailarrow', 'trailarrow');
      [*] = ;         end;
      [*] = ;         gc_projectile_iMagicTower1 : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.3;
      [*] = ;            speed := 20;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.8222;
      [*] = ;            projY := 4.2874;
      [*] = ;            projZ := 0.2604;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         gc_projectile_iMagicTower2 : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.3;
      [*] = ;            speed := 20;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.8222;
      [*] = ;            projY := 4.2874;
      [*] = ;            projZ := 0.2604;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         gc_projectile_iMagicTower3 : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.3;
      [*] = ;            speed := 20;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.8222;
      [*] = ;            projY := 4.2874;
      [*] = ;            projZ := 0.2604;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         gc_projectile_iMagicTower4 : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.3;
      [*] = ;            speed := 20;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.8222;
      [*] = ;            projY := 4.2874;
      [*] = ;            projZ := 0.2604;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         gc_projectile_iMagicTower5 : begin
      [*] = ;            defaultScale := cEmptyProjDefaultScale;
      [*] = ;            scale := 0.3;
      [*] = ;            speed := 20;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -4.8222;
      [*] = ;            projY := 4.2874;
      [*] = ;            projZ := 0.2604;
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0', 'shotvioletball0');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball1', 'shotvioletball1');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball2', 'shotvioletball2');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            MyGameObjectPFXSrcLibCreate('shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         ErrorLog('projectile.aix : unknown projectile');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (scale<>1) or gc_RecycleProjectiles then
      [*] = ;   SetGameObjectMyScale(defaultScale*scale, defaultScale*scale, defaultScale*scale);
      [*] = ;   endY := endY+bbZ*targetH;
      [*] = ;
      [*] = ;   speed := speed*_misc_CalcBattleSpeedModified(gc_battle_projectilespeedmod);
      [*] = ;
      [*] = ;   VectorRotateY(projX, projY, projZ, angle);
      [*] = ;   startX := startX+projX;
      [*] = ;   startY := startY+projY;
      [*] = ;   startZ := startZ+projZ;
      [*] = ;   SetupBehaviour(myHnd, startX, startY, startZ, endX, endY, endZ, speed, parabola, useRotate, pitchStart, pitchMid, pitchEnd);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

