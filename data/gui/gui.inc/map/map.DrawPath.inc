section.begin
   Name = map.DrawPath
   Code : struct.begin
      [*] = ;procedure Clear3DGUIMovePoints();
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName('PlTrack');
      [*] = ;   if plHandle <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_RecyclePointers then
      [*] = ;      begin
      [*] = ;         var i, goHandle : Integer;
      [*] = ;         for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do 
      [*] = ;         begin
      [*] = ;            goHandle := GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;            _obj_Recycle(goHandle);
      [*] = ;            BehaviourClear(goHandle);
      [*] = ;            EffectClear(goHandle); // must be done here to return faded terrain objects to normal
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ClearPlayerGameObjectsByHandle(plHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;{procedure MovePointTestWaterHeight(mpHandle : Integer; mpBaseYOffset : Float);
      [*] = ;begin
      [*] = ;   var minX, minZ, maxX, maxZ, offsetY : Float;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to WaterFieldGetCount-1 do
      [*] = ;   begin
      [*] = ;      WaterFieldGetCoord(i, minX, minZ, maxX, maxZ, offsetY);
      [*] = ;      var posX : Float = GetGameObjectPositionXByHandle(mpHandle);
      [*] = ;      var posY : Float = GetGameObjectPositionYByHandle(mpHandle);
      [*] = ;      var posZ : Float = GetGameObjectPositionZByHandle(mpHandle);
      [*] = ;      if (posX>minX) and (posX<maxX) and (posZ>minZ) and (posZ<maxZ) then
      [*] = ;      SetGameObjectPositionByHandle(mpHandle, posX, RayCastHeight(posX, posZ)+offsetY+1+mpBaseYOffset, posZ);
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
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
      [*] = ;procedure EffectAlphaFadeAround(goHnd : Integer);
      [*] = ;begin
      [*] = ;   var effHnd : Integer = GetEffectByKey(goHnd, 'alphaFadeAroundEffect');
      [*] = ;   if effHnd = 0 then
      [*] = ;   effHnd := EffectCreateWithKey(goHnd, 'TXAlphaFadeAroundEffect', 'alphaFadeAroundEffect', False);
      [*] = ;   var goRad : Float = GetGameObjectBoundingSphereByHandle(goHnd);
      [*] = ;   SetBehaviourIntProperty(effHnd, 'FilterRaceTagAdd', gc_map_PlayerRaceTag);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'FilterBoundMin', goRad);
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'castle4strat');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'castlehill');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'flag_medium');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'volcano1');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'volcano2');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'volcano3');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'volcano4');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'rock1');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'rock2');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'rock3');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'rock4');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'mount01');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'mount02');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'mount03');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'mount04');
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to 8 do
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'shard_edge1_'+IntToStr(i));
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'shard_edge2_1');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'shard_edge2_2');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'shard_edge3_1');
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'shard_edge3_2');
      [*] = ;   for i:=1 to 8 do
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'wellstones'+IntToStr(i));
      [*] = ;   SetBehaviourStringProperty(effHnd, 'FilterBasNameAdd', 'riverwellplane2');
      [*] = ;   //SetBehaviourFloatProperty(effHnd, 'FilterBoundMax', goRad*0.8);
      [*] = ;   SetBehaviourFloatProperty(effHnd, 'LerpTime', 0.25);
      [*] = ;end;
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;procedure Setup3DGUIMovePoints(xStart, yStart, xEnd, yEnd : Float; Step : Integer; IsEndPoint : Boolean; StateColor, pointType : Integer);
      [*] = ;begin
      [*] = ;   const cGUIPlName = 'PlTrack';
      [*] = ;   const cGUIPlRace = 'misc';
      [*] = ;   var cGUICrossBaseName, cGUICrossHoleBaseName, cGUIPointBaseName, cGUIPointHoleBaseName : String;
      [*] = ;   if gc_RecyclePointers then
      [*] = ;   begin
      [*] = ;      cGUICrossBaseName := 'pointer_cross_R';
      [*] = ;      cGUICrossHoleBaseName := 'pointer_cross_hole_R';
      [*] = ;      cGUIPointBaseName := 'pointer_point_R';
      [*] = ;      cGUIPointHoleBaseName := 'pointer_point_hole_R';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      cGUICrossBaseName := 'pointer_cross';
      [*] = ;      cGUICrossHoleBaseName := 'pointer_cross_hole';
      [*] = ;      cGUIPointBaseName := 'pointer_point';
      [*] = ;      cGUIPointHoleBaseName := 'pointer_point_hole';
      [*] = ;   end;
      [*] = ;   const cGUICrossYOff = 0;//0.2; //1.25
      [*] = ;   var plHandle : Integer = _plr_GetOrCreatePlayer(cGUIPlName, cGUIPlRace, 'cmPlayer', false);
      [*] = ;   var goCount : Integer = GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;
      [*] = ;   var goMidPoint : Integer;
      [*] = ;
      [*] = ;   var scaleCross : Float = 0.46; //0.56
      [*] = ;   var scalePoint : Float = 0.6;
      [*] = ;   if IsEndPoint then
      [*] = ;   begin
      [*] = ;      var goEndPoint : Integer;
      [*] = ;      var newBaseName : String = '';
      [*] = ;      if (pointType=0) then
      [*] = ;      newBaseName := cGUICrossBaseName
      [*] = ;      else
      [*] = ;      newBaseName := cGUICrossHoleBaseName;
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      var doPlace : Boolean = True;
      [*] = ;      for j:=(goCount-1) downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         var goBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;         const cMinDist = 0.25;
      [*] = ;         if (VectorDistance(goPosX, 0, goPosZ, xEnd, 0, yEnd)<cMinDist) then
      [*] = ;         begin
      [*] = ;            if (SameText(goBaseName, newBaseName)) then
      [*] = ;            begin
      [*] = ;               doPlace := False;
      [*] = ;               ArrayPushValue(goHnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (doPlace) then
      [*] = ;      begin
      [*] = ;         goEndPoint := _obj_GetInvisibleOrCreate(plHandle, cGUIPlRace, newBaseName, xEnd, 0, yEnd);
      [*] = ;         ArrayPushValue(goEndPoint);
      [*] = ;         //EffectZTest(goEndPoint, False);
      [*] = ;
      [*] = ;         //SetGameObjectAutoOffsetByHandle(goEndPoint, false);
      [*] = ;         SetGameObjectPositionByHandle(goEndPoint, GetGameObjectPositionXByHandle(goEndPoint), GetGameObjectPositionYByHandle(goEndPoint) + cGUICrossYOff, GetGameObjectPositionZByHandle(goEndPoint));
      [*] = ;         SetGameObjectScaleByHandle(goEndPoint, GetGameObjectScaleXByHandle(goEndPoint) * scaleCross, GetGameObjectScaleYByHandle(goEndPoint) * scaleCross, GetGameObjectScaleZByHandle(goEndPoint) * scaleCross);
      [*] = ;
      [*] = ;         EffectAlphaFadeAround(goEndPoint);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var newBaseName : String = '';
      [*] = ;      if (pointType=0) then
      [*] = ;      newBaseName := cGUIPointBaseName
      [*] = ;      else
      [*] = ;      newBaseName := cGUIPointHoleBaseName;
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      var doPlace : Boolean = True;
      [*] = ;      for j:=(goCount-1) downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         var goBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;         const cMinDist = 0.25;
      [*] = ;         if (VectorDistance(goPosX, 0, goPosZ, xEnd, 0, yEnd)<cMinDist) then
      [*] = ;         begin
      [*] = ;            if (SameText(goBaseName, newBaseName)) then
      [*] = ;            begin
      [*] = ;               doPlace := False;
      [*] = ;               ArrayPushValue(goHnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (doPlace) then
      [*] = ;      begin
      [*] = ;         goMidPoint := _obj_GetInvisibleOrCreate(plHandle, cGUIPlRace, newBaseName, xEnd, 0, yEnd);
      [*] = ;         ArrayPushValue(goMidPoint);
      [*] = ;         //EffectZTest(goMidPoint, False);
      [*] = ;
      [*] = ;         //SetGameObjectAutoOffsetByHandle(goMidPoint, false);
      [*] = ;         SetGameObjectPositionByHandle(goMidPoint, GetGameObjectPositionXByHandle(goMidPoint), GetGameObjectPositionYByHandle(goMidPoint) + cGUICrossYOff, GetGameObjectPositionZByHandle(goMidPoint));
      [*] = ;         SetGameObjectScaleByHandle(goMidPoint, GetGameObjectScaleXByHandle(goMidPoint) * scalePoint, GetGameObjectScaleYByHandle(goMidPoint) * scalePoint, GetGameObjectScaleZByHandle(goMidPoint) * scalePoint);
      [*] = ;
      [*] = ;         case StateColor of
      [*] = ;            0 : begin
      [*] = ;            end;
      [*] = ;            1 : begin
      [*] = ;               SetGameObjectMaterialNameByHandle(goMidPoint, 'pointer_alpha');
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               SetGameObjectMaterialNameByHandle(goMidPoint, 'pointer_red');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         EffectAlphaFadeAround(goMidPoint);
      [*] = ;
      [*] = ;         //MovePointTestWaterHeight(goMidPoint, cGUICrossYOff);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var midPosX, midPosY : Float;
      [*] = ;   for i := 0 to Step-1 do
      [*] = ;   begin
      [*] = ;      midPosX := xStart + (i + 1) * (xEnd - xStart) / (Step + 1);
      [*] = ;      midPosY := yStart + (i + 1) * (yEnd - yStart) / (Step + 1);
      [*] = ;
      [*] = ;      var newBaseName : String = '';
      [*] = ;      if (pointType=0) then
      [*] = ;      newBaseName := cGUIPointBaseName
      [*] = ;      else
      [*] = ;      newBaseName := cGUIPointHoleBaseName;
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      var doPlace : Boolean = True;
      [*] = ;      for j:=(goCount-1) downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         var goBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;         const cMinDist = 0.25;
      [*] = ;         if (VectorDistance(goPosX, 0, goPosZ, midPosX, 0, midPosY)<cMinDist) then
      [*] = ;         begin
      [*] = ;            if (SameText(goBaseName, newBaseName)) then
      [*] = ;            begin
      [*] = ;               doPlace := False;
      [*] = ;               ArrayPushValue(goHnd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (doPlace) then
      [*] = ;      begin
      [*] = ;         goMidPoint := _obj_GetInvisibleOrCreate(plHandle, cGUIPlRace, newBaseName, midPosX, 0, midPosY);
      [*] = ;         ArrayPushValue(goMidPoint);
      [*] = ;
      [*] = ;         //EffectZTest(goMidPoint, False);
      [*] = ;
      [*] = ;         //SetGameObjectAutoOffsetByHandle(goMidPoint, false);
      [*] = ;         SetGameObjectPositionByHandle(goMidPoint, GetGameObjectPositionXByHandle(goMidPoint), GetGameObjectPositionYByHandle(goMidPoint) + cGUICrossYOff, GetGameObjectPositionZByHandle(goMidPoint));
      [*] = ;         SetGameObjectScaleByHandle(goMidPoint, GetGameObjectScaleXByHandle(goMidPoint) * scalePoint, GetGameObjectScaleYByHandle(goMidPoint) * scalePoint, GetGameObjectScaleZByHandle(goMidPoint) * scalePoint);
      [*] = ;
      [*] = ;         case StateColor of
      [*] = ;            0 : begin
      [*] = ;            end;
      [*] = ;            1 : begin
      [*] = ;               SetGameObjectMaterialNameByHandle(goMidPoint, 'pointer_alpha');
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               SetGameObjectMaterialNameByHandle(goMidPoint, 'pointer_red');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         EffectAlphaFadeAround(goMidPoint);
      [*] = ;
      [*] = ;         //MovePointTestWaterHeight(goMidPoint, cGUICrossYOff);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_GUIDrawPathUID);
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   var goTPCount : Integer = GetGameObjectTrackPointCountByHandle(goHandle);
      [*] = ;   var reachPoint : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iReachPoint);
      [*] = ;
      [*] = ;   var tUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;   IntRegister0 := tUID;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetProvinceParserByUID', 0);
      [*] = ;   var pTarProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var guiTrackStep : Integer = 2;
      [*] = ;
      [*] = ;   const cGUIPlName = 'PlTrack';
      [*] = ;   const cGUIPlRace = 'misc';
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(cGUIPlName);
      [*] = ;   if plHandle = 0 then
      [*] = ;   plHandle := CreatePlayer(cGUIPlName, cGUIPlRace, 'cmPlayer');
      [*] = ;   var goCount : Integer = GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;   ArrayClear;
      [*] = ;
      [*] = ;   if goTPCount > 0 then
      [*] = ;   begin
      [*] = ;      var stateColor : Integer;
      [*] = ;      var pointType : Integer;
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i := 1 to goTPCount-1 do
      [*] = ;      begin
      [*] = ;         if (i < reachPoint) then
      [*] = ;         stateColor := 0
      [*] = ;         else
      [*] = ;         stateColor := 0;//1
      [*] = ;         if (i <= reachPoint) then
      [*] = ;         pointType := 0
      [*] = ;         else
      [*] = ;         pointType := 1;
      [*] = ;
      [*] = ;         var x, y, z : Float;
      [*] = ;
      [*] = ;         GetGameObjectTrackPointCoordsByIndexByHandle(goHandle, i, x, y, z);
      [*] = ;         FloatRegister0 := x;
      [*] = ;         FloatRegister1 := z;
      [*] = ;         StateMachineExecuteState(initMachine, 'map.GetHexByCoord', 0);
      [*] = ;         var pProvince1 : Integer = IntRegister0;
      [*] = ;         var x1 : Float = ParserGetFloatValueByKeyByHandle(pProvince1, 'CenterX');
      [*] = ;         var y1 : Float = ParserGetFloatValueByKeyByHandle(pProvince1, 'CenterY');
      [*] = ;
      [*] = ;         GetGameObjectTrackPointCoordsByIndexByHandle(goHandle, i-1, x, y, z);
      [*] = ;         FloatRegister0 := x;
      [*] = ;         FloatRegister1 := z;
      [*] = ;         StateMachineExecuteState(initMachine, 'map.GetHexByCoord', 0);
      [*] = ;         var pProvince2 : Integer = IntRegister0;
      [*] = ;         var x2 : Float = ParserGetFloatValueByKeyByHandle(pProvince2, 'CenterX');
      [*] = ;         var y2 : Float = ParserGetFloatValueByKeyByHandle(pProvince2, 'CenterY');
      [*] = ;
      [*] = ;         {var ind1 : Integer = gArrPath[i];
      [*] = ;         var pProvince1 : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, ind1);
      [*] = ;         var x1 : Float = ParserGetFloatValueByKeyByHandle(pProvince1, 'CenterX');
      [*] = ;         var y1 : Float = ParserGetFloatValueByKeyByHandle(pProvince1, 'CenterY');
      [*] = ;
      [*] = ;         var ind2 : Integer = gArrPath[i-1];
      [*] = ;         var pProvince2 : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, ind2);
      [*] = ;         var x2 : Float = ParserGetFloatValueByKeyByHandle(pProvince2, 'CenterX');
      [*] = ;         var y2 : Float = ParserGetFloatValueByKeyByHandle(pProvince2, 'CenterY');}
      [*] = ;
      [*] = ;         if (not gBoolRegister_StandHeroAtProvCenter) then
      [*] = ;         begin
      [*] = ;            FloatRegister0 := x1;
      [*] = ;            FloatRegister1 := y1;
      [*] = ;            StateMachineExecuteState(initMachine, 'map.GetHexByCoord', 0);
      [*] = ;            var pProvince : Integer = IntRegister0;
      [*] = ;
      [*] = ;            var heroPointX : Float = ParserGetFloatValueByKeyByHandle(pProvince, 'HeroPointX');
      [*] = ;            var heroPointY : Float = ParserGetFloatValueByKeyByHandle(pProvince, 'HeroPointY');
      [*] = ;            x1 := heroPointX;
      [*] = ;            y1 := heroPointY;
      [*] = ;
      [*] = ;            FloatRegister0 := x2;
      [*] = ;            FloatRegister1 := y2;
      [*] = ;            StateMachineExecuteState(initMachine, 'map.GetHexByCoord', 0);
      [*] = ;            pProvince := IntRegister0;
      [*] = ;
      [*] = ;            heroPointX := ParserGetFloatValueByKeyByHandle(pProvince, 'HeroPointX');
      [*] = ;            heroPointY := ParserGetFloatValueByKeyByHandle(pProvince, 'HeroPointY');
      [*] = ;            x2 := heroPointX;
      [*] = ;            y2 := heroPointY;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var IsEndPoint : Boolean = (i = goTPCount-1);
      [*] = ;
      [*] = ;         var dist : Float = VectorDistance(x1, 0, y1, x2, 0, y2);
      [*] = ;         if (dist>13) then
      [*] = ;         guiTrackStep := 3
      [*] = ;         else
      [*] = ;         if (dist<5) then
      [*] = ;         guiTrackStep := 0
      [*] = ;         else
      [*] = ;         if (dist<6.25) then
      [*] = ;         guiTrackStep := 1
      [*] = ;         else
      [*] = ;         guiTrackStep := 2;
      [*] = ;         Setup3DGUIMovePoints(x2, y2, x1, y1, guiTrackStep, IsEndPoint, stateColor, pointType);
      [*] = ;
      [*] = ;         //GUIDataViewerZonePointListAdd(DVZone, x1, 0.1, y1)
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   goCount := GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;   var i : Integer;
      [*] = ;   for i := goCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var bExist : Boolean = False;
      [*] = ;      var goHnd1 : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=ArrayGetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHnd2 : Integer = ArrayGetValueByIndex(j);
      [*] = ;         if (goHnd1=goHnd2) then
      [*] = ;         begin
      [*] = ;            bExist := True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (not bExist) then
      [*] = ;      begin
      [*] = ;         if gc_RecyclePointers then
      [*] = ;         begin
      [*] = ;            _obj_Recycle(goHnd1);
      [*] = ;            BehaviourClear(goHnd1);
      [*] = ;            EffectClear(goHnd1);  // must be done here to return faded terrain objects to normal
      [*] = ;         end
      [*] = ;         else
      [*] = ;            GameObjectDestroyByHandle(goHnd1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;Clear3DGUIMovePoints;
   struct.end
section.end

