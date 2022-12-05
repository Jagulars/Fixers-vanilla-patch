section.begin
   Name = battle.DrawPath
   Code : struct.begin
      [*] = ;procedure EffectZTest(goHnd : Integer; bState : Boolean);
      [*] = ;begin
      [*] = ;   const className = 'TXZBufferEffect';
      [*] = ;   var effHnd : Integer = EffectCreate(goHnd, className, true, false);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'ZWrite', True);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'ZTest', bState);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'ColorBuffer', True);
      [*] = ;   SetBehaviourBoolProperty(effHnd, 'NoColorBuffer', True);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Setup3DGUIMovePoints(xStart, yStart, xEnd, yEnd, height : Float; Step : Integer; IsStartPoint, IsEndPoint : Boolean; pointType : Integer);
      [*] = ;begin
      [*] = ;   const cGUIPlName = 'PlTrackBattle';
      [*] = ;   const cGUIPlRace = 'misc';
      [*] = ;   var cGUICrossBaseName, cGUIPointBaseName : String;
      [*] = ;   if gc_RecyclePointers then
      [*] = ;   begin
      [*] = ;      cGUICrossBaseName := 'pointer_cross_R';
      [*] = ;      cGUIPointBaseName := 'pointer_point_R';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      cGUICrossBaseName := 'pointer_cross';
      [*] = ;      cGUIPointBaseName := 'pointer_point';
      [*] = ;   end;
      [*] = ;   
      [*] = ;   const cGUICrossYOff = 0.0; //1.25
      [*] = ;   var plHandle : Integer = _plr_GetOrCreatePlayer(cGUIPlName, cGUIPlRace, 'cmPlayer', false);
      [*] = ;
      [*] = ;   var goMidPoint : Integer;
      [*] = ;
      [*] = ;   var scaleCross : Float = 0.36; //0.56
      [*] = ;   var scalePoint : Float = 0.425;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var midPosX, midPosY : Float;
      [*] = ;   for i := 0 to Step-1 do
      [*] = ;   begin
      [*] = ;      midPosX := xStart + (i + 1) * (xEnd - xStart) / (Step + 1);
      [*] = ;      midPosY := yStart + (i + 1) * (yEnd - yStart) / (Step + 1);
      [*] = ;      if ({(i=0) and }(IsStartPoint)) or ((i<Step{-1}) and (IsEndPoint)) or ((not IsStartPoint) and (not IsEndPoint)) then
      [*] = ;      begin
      [*] = ;         goMidPoint := _obj_GetInvisibleOrCreate(plHandle, cGUIPlRace, cGUIPointBaseName, midPosX, 0, midPosY);
      [*] = ;         EffectZTest(goMidPoint, False);
      [*] = ;         //SetGameObjectAutoOffsetByHandle(goMidPoint, false);
      [*] = ;         SetGameObjectPositionByHandle(goMidPoint, GetGameObjectPositionXByHandle(goMidPoint), height + cGUICrossYOff, GetGameObjectPositionZByHandle(goMidPoint));
      [*] = ;         SetGameObjectScaleByHandle(goMidPoint, GetGameObjectScaleXByHandle(goMidPoint) * scalePoint, GetGameObjectScaleYByHandle(goMidPoint) * scalePoint, GetGameObjectScaleZByHandle(goMidPoint) * scalePoint);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if IsEndPoint then
      [*] = ;   begin
      [*] = ;      var goEndPoint : Integer;
      [*] = ;      goEndPoint := _obj_GetInvisibleOrCreate(plHandle, cGUIPlRace, cGUICrossBaseName, xEnd, 0, yEnd);
      [*] = ;      EffectZTest(goEndPoint, False);
      [*] = ;
      [*] = ;      //SetGameObjectAutoOffsetByHandle(goEndPoint, false);
      [*] = ;      SetGameObjectPositionByHandle(goEndPoint, GetGameObjectPositionXByHandle(goEndPoint), height + cGUICrossYOff, GetGameObjectPositionZByHandle(goEndPoint));
      [*] = ;      SetGameObjectScaleByHandle(goEndPoint, GetGameObjectScaleXByHandle(goEndPoint) * scaleCross, GetGameObjectScaleYByHandle(goEndPoint) * scaleCross, GetGameObjectScaleZByHandle(goEndPoint) * scaleCross);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      goMidPoint := _obj_GetInvisibleOrCreate(plHandle, cGUIPlRace, cGUIPointBaseName, xEnd, 0, yEnd);
      [*] = ;      EffectZTest(goMidPoint, False);
      [*] = ;      //SetGameObjectAutoOffsetByHandle(goMidPoint, false);
      [*] = ;      SetGameObjectPositionByHandle(goMidPoint, GetGameObjectPositionXByHandle(goMidPoint), height + cGUICrossYOff, GetGameObjectPositionZByHandle(goMidPoint));
      [*] = ;      SetGameObjectScaleByHandle(goMidPoint, GetGameObjectScaleXByHandle(goMidPoint) * scalePoint, GetGameObjectScaleYByHandle(goMidPoint) * scalePoint, GetGameObjectScaleZByHandle(goMidPoint) * scalePoint);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pointerPlayer : Integer = GetPlayerHandleByName('PlTrackBattle');
      [*] = ;if gc_RecyclePointers then
      [*] = ;   _plr_RecycleGameObjects(pointerPlayer)
      [*] = ;else
      [*] = ;   ClearPlayerGameObjectsByHandle(pointerPlayer);
      [*] = ;
      [*] = ;var selGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;{var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;var isShoot : Boolean = false;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_battle_unit_iShootingRange;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;   var range : Integer = IntRegister1;
      [*] = ;   IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;   var rangedAttack : Integer = IntRegister1;
      [*] = ;   IntRegister0 := gc_battle_unit_iCurAmmo;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;   var ammo : Integer = IntRegister1;
      [*] = ;   
      [*] = ;   var isShootable : Boolean;
      [*] = ;   _unit_IsShootEndPoint(goHandle, gIntRegister_BeforeEndTrackNode, range, rangedAttack, ammo, gBoolRegister_BattlePlaceMode, isShoot, isShootable);
      [*] = ;end;}
      [*] = ;
      [*] = ;if {(isShoot) or} (gIntRegister_CurSpell>0) then
      [*] = ;exit;
      [*] = ;var lunge : Boolean = GetGameObjectBoolValueIndByHandle(selGOHandle, gc_stack_unit_bLunge);
      [*] = ;var endPointValid : Boolean;
      [*] = ;var goEnemyUID : Integer;
      [*] = ;if lunge then
      [*] = ;begin
      [*] = ;   _unit_IsValidEndPoint(selGOHandle, gIntRegister_EndTrackNode, true, false, endPointValid, goEnemyUID);
      [*] = ;   if (endPointValid) and (goEnemyUID <>0) then exit;
      [*] = ;end;
      [*] = ;_unit_IsValidEndPoint(selGOHandle, gIntRegister_BeforeEndTrackNode, true, false, endPointValid, goEnemyUID);
      [*] = ;
      [*] = ;if (selGOHandle<>0) and (GetGameObjectTrackPointMovementModeByHandle(selGOHandle) = 'mmNone') and
      [*] = ;endPointValid then
      [*] = ;begin
      [*] = ;   if (gIntRegister_StartTrackNode <> 0) and (gIntRegister_BeforeEndTrackNode <> 0) then
      [*] = ;   begin
      [*] = ;      //if GetTrackNodePathByHandle(gIntRegister_StartTrackNode, gIntRegister_BeforeEndTrackNode) then
      [*] = ;      begin
      [*] = ;         var endIndex : Integer = GetTrackNodeTPCount-1;
      [*] = ;         if goEnemyUID <> 0 then
      [*] = ;         endIndex := endIndex - 1;
      [*] = ;
      [*] = ;         var IsEndPoint : Boolean = false;
      [*] = ;         var IsStartPoint : Boolean = false;
      [*] = ;         var guiTrackStep : Integer = 2;
      [*] = ;         var pointType : Integer;
      [*] = ;         var height : Float = GetGameObjectPositionYByHandle(selGOHandle);
      [*] = ;         var i : Integer;
      [*] = ;         for i := 1 to endIndex do
      [*] = ;         begin
      [*] = ;            var x1, y1 : Float;
      [*] = ;            GetTrackNodeTPByIndex(i, x1, y1);
      [*] = ;            height := height+GetHeightData(round(x1), round(y1));
      [*] = ;         end;
      [*] = ;         height := height/(endIndex+1);
      [*] = ;
      [*] = ;         for i := 1 to endIndex do
      [*] = ;         begin
      [*] = ;            var x1, y1 : Float;
      [*] = ;            var x2, y2 : Float;
      [*] = ;            GetTrackNodeTPByIndex(i, x1, y1);
      [*] = ;            GetTrackNodeTPByIndex(i-1, x2, y2);
      [*] = ;
      [*] = ;            pointType := 0;
      [*] = ;            if (i=1) then
      [*] = ;            IsStartPoint := True
      [*] = ;            else
      [*] = ;            IsStartPoint := False;
      [*] = ;
      [*] = ;            if (i=endIndex) then
      [*] = ;            IsEndPoint := True
      [*] = ;            else
      [*] = ;            IsEndPoint := False;
      [*] = ;            Setup3DGUIMovePoints(x2, y2, x1, y1, height, guiTrackStep, IsStartPoint, IsEndPoint, pointType);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

