section.begin
   Name = InitialFlySpell
   Code : struct.begin
      [*] = ;const cSpellCastHeightK = 1.2;
      [*] = ;
      [*] = ;var _log_name : String = 'PROJECTILE\PROJECTILE.INC\INITIALFLYSPELL';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure SetupBehaviour(goHandle : Integer; startX, startY, startZ, endX, endY, endZ, speed, parabolaFactor : Float; useRotate : Boolean; pitchStart, pitchMid, pitchEnd : Float);
      [*] = ;begin
      [*] = ;   var pathLength : Float = VectorDistance(startX, startY, startZ, endX, endY, endZ);
      [*] = ;   var s : Float = speed;
      [*] = ;
      [*] = ;   SetGameObjectPositionByHandle(goHandle, startX, startY, startZ);
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
      [*] = ;      SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprUse')
      [*] = ;   else
      [*] = ;      SetBehaviourStringProperty(behHnd, 'MovementPathRotate', 'mprNone');
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'AddPath', '');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,0]', startX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,0]', startY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,0]', startZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesPitchAngle[0,0]', pitchStart);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,0]', s);
      [*] = ;
      [*] = ;   var midX : Float = (startX+endX)/2;
      [*] = ;   var midY : Float = (startY+endY)/2 + pathLength*parabolaFactor;
      [*] = ;   var midZ : Float = (startZ+endZ)/2;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,1]', midX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,1]', midY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,1]', midZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesPitchAngle[0,1]', pitchMid);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,1]', s);
      [*] = ;
      [*] = ;   SetBehaviourStringProperty(behHnd, 'PathsAddNode[0]', '');
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesX[0,2]', endX);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesY[0,2]', endY);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesZ[0,2]', endZ);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesPitchAngle[0,2]', pitchEnd);
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,2]', s*0.02);
      [*] = ;   //SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,2]', s);
      [*] = ;
      [*] = ;   if _log then _Log_map(_log_name+' Speed: '+FloatToStr(speed)+', PathLen: '+FloatToStr(pathLength));
      [*] = ;   if _log then _Log_map(_log_name+' ['+FloatToStr(startX)+','+FloatToStr(startZ)+','+FloatToStr(startY)+'] ,['+FloatToStr(midX)+','+FloatToStr(midZ)+','+FloatToStr(midY)+'] ,['+FloatToStr(endX)+','+FloatToStr(endZ)+','+FloatToStr(endY)+']');
      [*] = ;   SetBehaviourStringProperty(behHnd, 'OnStatePathTravelStop', 'OnPathTravelStopSpell');
      [*] = ;   //SetBehaviourStringProperty(behHnd, 'OnStateAllPathTravelledOver', 'OnPathTravelStopSpell');
      [*] = ;
      [*] = ;   SetBehaviourIntProperty(behHnd, 'ActivePathIndex', 0);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'PathsLooped[0]', false);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;   var estimateTime : Float = GetBehaviourFloatProperty(behHnd, 'EstimateTime[0]');
      [*] = ;   midX := GetCurrentTime()-(Random*estimateTime);
      [*] = ;   //midX := GetCurrentTime()-1;
      [*] = ;   if _log then _Log_map(_log_name+' Time: '+FloatToStr(estimateTime)+', StartTime: '+FloatToStr(midX));
      [*] = ;   SetBehaviourFloatProperty(behHnd, 'StartTime[0]', midX);
      [*] = ;   //SetBehaviourBoolProperty(behHnd, 'PathsShowPath[0]', True);
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
      [*] = ;var ownerGOHnd : Integer = GetGameObjectHandleByUniqueId(GetIntValueByIndex(gc_stack_projectile_iOwner));
      [*] = ;if (ownerGOHnd<>0) then
      [*] = ;begin
      [*] = ;   if _log then _Log_map(_log_name+' Owner: '+GetGameObjectBaseNameByHandle(ownerGOHnd));
      [*] = ;   var pHexCells : Integer = gHexCells.handle;
      [*] = ;   var ind : Integer = gc_battle_GridSize * GetIntValueByIndex(gc_stack_projectile_iTPosY) + GetIntValueByIndex(gc_stack_projectile_iTPosX);
      [*] = ;   if _log then _Log_map(_log_name+' Target Y: '+IntToStr(GetIntValueByIndex(gc_stack_projectile_iTPosY))+', Target X: '+IntToStr(GetIntValueByIndex(gc_stack_projectile_iTPosX)));
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;   var targetGOUID : Integer = GetIntValueByIndex(gc_stack_projectile_iTarget);
      [*] = ;   if _log then _Log_map(_log_name+' TargetGOUID: '+IntToStr(targetGOUID));
      [*] = ;   var targetGOHandle : Integer = 0;
      [*] = ;   var endX, endY, endZ : Float;
      [*] = ;   var bbX, bbY, bbZ : Float;
      [*] = ;   var yOff : Float;
      [*] = ;
      [*] = ;   if (targetGOUID<>0) then
      [*] = ;      targetGOHandle := GetGameObjectHandleByUniqueId(targetGOUID);
      [*] = ;   if (targetGOHandle<>0) then
      [*] = ;   begin
      [*] = ;      GetGameObjectAxisAlignedDimensionsByHandle(targetGOHandle, bbX, bbY, bbZ);
      [*] = ;      yOff := bbZ;
      [*] = ;      endX := GetGameObjectPositionXByHandle(targetGOHandle);
      [*] = ;      endY := GetGameObjectPositionYByHandle(targetGOHandle);
      [*] = ;      endZ := GetGameObjectPositionZByHandle(targetGOHandle);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      yOff := 2.5;
      [*] = ;      endX := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;      endZ := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;      endY := RayCastHeight(round(endX), round(endZ));
      [*] = ;   end;
      [*] = ;
      [*] = ;   var startX : Float = GetGameObjectPositionXByHandle(ownerGOHnd);
      [*] = ;   var startY : Float = GetGameObjectPositionYByHandle(ownerGOHnd);
      [*] = ;   var startZ : Float = GetGameObjectPositionZByHandle(ownerGOHnd);
      [*] = ;
      [*] = ;   var dirX : Float = endX - startX;
      [*] = ;   var dirY : Float = 0;
      [*] = ;   var dirZ : Float = endZ - startZ;
      [*] = ;   var angle : Float = 0;
      [*] = ;   if VectorLength(dirX, dirY, dirZ) > 0.0001 then
      [*] = ;   begin
      [*] = ;      angle := VectorAngle(dirX, dirY, dirZ, -1, 0, 0);
      [*] = ;      if dirZ < 0 then
      [*] = ;         angle := -angle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var scale : Float = 1;
      [*] = ;   var targetH : Float = 0.5; // Target point height in percent of target unit bounding box. 0.5 - means fire at unit center. 0.9 - means fire at head.
      [*] = ;   var speed : Float = 100;
      [*] = ;   var projX, projY, projZ, parabola : Float = 0;
      [*] = ;   var pitchStart, pitchMid, pitchEnd : Float = 0;
      [*] = ;   var useRotate : Boolean = False;
      [*] = ;   var startAtTarget : Boolean = False;
      [*] = ;   var projEndX, projEndZ : Float = 0;
      [*] = ;   var projEndY : Float = 10;
      [*] = ;
      [*] = ;   // setup start
      [*] = ;   //speed := 100;
      [*] = ;
      [*] = ;   var spellID : Integer = GetIntValueByIndex(gc_stack_projectile_iType)-gc_projectile_iSpell;
      [*] = ;   if (spellID>0) then
      [*] = ;   begin
      [*] = ;      case spellID of
      [*] = ;         4 : begin //magic arrow
      [*] = ;            scale := 0.6;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3.7139;
      [*] = ;            projY := 0.0644;
      [*] = ;            projZ := -0.1695;
      [*] = ;            startAtTarget := false;
      [*] = ;            projEndX := -20;
      [*] = ;            projEndY := 15;
      [*] = ;            projEndZ := 0;
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball0', 'shotvioletball0');
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball1', 'shotvioletball1');
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball2', 'shotvioletball2');
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         23 : begin //fireball
      [*] = ;            scale := 2;
      [*] = ;            speed := 15;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0.1;
      [*] = ;            projX := -3.7139;
      [*] = ;            projY := 0.0644;
      [*] = ;            projZ := -0.1695;
      [*] = ;            startAtTarget := false;
      [*] = ;            projEndX := -20;
      [*] = ;            projEndY := 15;
      [*] = ;            projEndZ := 0;
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'fireball_ball', 'fireball_ball');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball1', 'shotvioletball1');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball2', 'shotvioletball2');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'fireball_trail', 'fireball_trail');
      [*] = ;            //GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;
      [*] = ;         {41 : begin //acid
      [*] = ;            scale := 1;
      [*] = ;            speed := 25;
      [*] = ;            targetH := 0.7;
      [*] = ;            parabola := 0;
      [*] = ;            projX := -3.7139;
      [*] = ;            projY := 0.0644;
      [*] = ;            projZ := -0.1695;
      [*] = ;            startAtTarget := false;
      [*] = ;            projEndX := -20;
      [*] = ;            projEndY := 15;
      [*] = ;            projEndZ := 0;
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'fxspheregreen0', 'fxspheregreen0');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball1', 'shotvioletball1');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball2', 'shotvioletball2');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin');
      [*] = ;            //GameObjectPFXSrcLibCreateByHandle(myHnd, 'shotvioletballtrail2', 'shotvioletballtrail2'); // shotvioletballtrail
      [*] = ;            GameObjectPFXSrcLibCreateByHandle(myHnd, 'acid_trail', 'acid_trail');
      [*] = ;            //GameObjectPFXEffectScaleByHandle(myHnd, 'acid_trail', 'acid_trail', scale);
      [*] = ;            //GameObjectPFXEffectScaleByHandle(myHnd, 'shotvioletball0perlin', 'shotvioletball0perlin', scale);
      [*] = ;         end;}
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            scale := 0.45;
      [*] = ;            speed := 10;
      [*] = ;            targetH := 0.5;
      [*] = ;            parabola := 0;
      [*] = ;            projX := 0;
      [*] = ;            projY := 0;
      [*] = ;            projZ := 0;
      [*] = ;            startAtTarget := true;
      [*] = ;            projEndX := 0;
      [*] = ;            projEndY := 2;
      [*] = ;            projEndZ := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if (targetGOHandle<>0) then
      [*] = ;         yOff := yOff*targetH;
      [*] = ;      
      [*] = ;      if  gc_RecycleProjectiles then
      [*] = ;      begin
      [*] = ;         // 0.08 is the default scale of "weapon.empty" object. This works only as long as all spell projectiles are "weapon.empty" objects.
      [*] = ;         SetGameObjectMyScale(0.08*scale, 0.08*scale, 0.08*scale);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (scale<>1) then
      [*] = ;         SetGameObjectMyScale(GetGameObjectMyScaleX()*scale, GetGameObjectMyScaleY()*scale, GetGameObjectMyScaleZ()*scale); // this would not work unless projectile game objects are recreated each time.
      [*] = ;      
      [*] = ;      endY := endY+yOff;
      [*] = ;
      [*] = ;      if (startAtTarget) then
      [*] = ;      begin
      [*] = ;         startX := endX+projEndX;
      [*] = ;         startY := endY+projEndY;
      [*] = ;         startZ := endZ+projEndZ;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         //VectorRotateY(projX, projY, projZ, angle);
      [*] = ;         //startX := startX+projX;
      [*] = ;         //startY := startY+projY;
      [*] = ;         //startZ := startZ+projZ;
      [*] = ;         GetGameObjectAxisAlignedDimensionsByHandle(ownerGOHnd, bbX, bbY, bbZ);
      [*] = ;         if _log then _Log_map('Src dimensions: ['+FloatToStr(bbX)+','+FloatToStr(bbZ)+','+FloatToStr(bbY)+']');
      [*] = ;         startY := startY+(bbZ*cSpellCastHeightK);
      [*] = ;      end;
      [*] = ;
      [*] = ;      speed := speed*_misc_CalcBattleSpeedModified(gc_battle_projectilespeedmod);
      [*] = ;      SetupBehaviour(myHnd, startX, startY, startZ, endX, endY, endZ, speed, parabola, useRotate, pitchStart, pitchMid, pitchEnd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      ErrorLog(_log_name+'. SpellID=0');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

