section.begin
   Name = bat.FieldScenery
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.FIELDSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = False;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'battlefield';
      [*] = ;const cRaceName = 'nature';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;const cParticlePlName = 'particles.battle';
      [*] = ;const cParticlePlRace = 'misc';
      [*] = ;const cParticlePlCMode = 'cmPC';
      [*] = ;
      [*] = ;var uPlHandle : Integer = _plr_GetOrCreatePlayer(cPlayerName, cRaceName, cCMode, False);
      [*] = ;   
      [*] = ;var particlePlHandle : Integer = _plr_GetOrCreatePlayer(cParticlePlName, cParticlePlRace, cParticlePlCMode, False);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle))+', '+cParticlePlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(particlePlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   var pHexCells : Integer = gHexCells.handle;
      [*] = ;   
      [*] = ;   var curVisualID : Integer = 0;
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;      curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;   
      [*] = ;   procedure ClearObjectsAround(goHandle : Integer; radius : Float);
      [*] = ;   begin
      [*] = ;      const cBattlePatternPlName = 'battle.pattern';
      [*] = ;      var plHnd : Integer = GetPlayerHandleByName(cBattlePatternPlName);
      [*] = ;      
      [*] = ;      var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;      
      [*] = ;      GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, -1, 0, false, false, false, false, false, false);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to GetGameObjectListCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;         if (goHnd<>goHandle) then
      [*] = ;         begin
      [*] = ;            var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;            var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;   
      [*] = ;            if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;            AddObjectToDestroyList(goHnd);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure FadeObjectsInRadiusByBaseName(posX, posZ, radius : Float; baseName : String; alpha : Float);
      [*] = ;   begin
      [*] = ;      GetGameObjectsInRadius(posX, posZ, radius, false, true, uPlHandle, -1, 0, false, false, false, false, false, false);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to GetGameObjectListCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;         var goBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;         if (SameText(goBaseName, baseName)) then
      [*] = ;         begin
      [*] = ;            var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;            var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;   
      [*] = ;            if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;            begin
      [*] = ;               _fx_CreateAlphaFadeEffect(goHnd, 0, alpha, alpha, 'alphaeffect');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var pPatterns : Integer = gBattleData.patternList.handle;
      [*] = ;   
      [*] = ;   var i, j : Integer;
      [*] = ;   
      [*] = ;   var siegeLevel : Integer = 0;
      [*] = ;   if (gBoolRegister_BattleIsSiege) then
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;      var bCastle : Boolean =  ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;      var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;      var pGarrisonSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;      if (bCastle) then
      [*] = ;         siegeLevel := 5
      [*] = ;      else
      [*] = ;      for i:=3 downto 0 do
      [*] = ;      begin
      [*] = ;         var pGarrisonSlot : Integer = ParserSelectByHandleByIndex(pGarrisonSlots, i);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pGarrisonSlot, 'Count');
      [*] = ;         if (count>0) then
      [*] = ;         begin
      [*] = ;            siegeLevel := i+1;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var arrHexType : array[0..15] of Integer;
      [*] = ;   {arrHexType[0] := 1;//'PlainPass';
      [*] = ;   arrHexType[1] := 9;//'DesertPass';
      [*] = ;   arrHexType[2] := 11;//'DeadLandPass';
      [*] = ;   arrHexType[3] := 6;//'HillImpass';
      [*] = ;   arrHexType[4] := 5;//'HillPass';
      [*] = ;   arrHexType[5] := 3;//'ForestPass';
      [*] = ;   arrHexType[6] := 7;//'SwampPass';
      [*] = ;   arrHexType[7] := 2;//'PlainImpass';
      [*] = ;   arrHexType[8] := 4;//'ForestImpass';
      [*] = ;   arrHexType[9] := 8;//'SwampImpass';
      [*] = ;   arrHexType[10] := 10;//'DesertImpass';
      [*] = ;   arrHexType[11] := 12;//'DeadLandImpass';
      [*] = ;   arrHexType[12] := 13;//'CastleWallPass';
      [*] = ;   arrHexType[13] := 14;//'CastleWallImpass';
      [*] = ;   arrHexType[14] := 15;//'CastlePass';
      [*] = ;   arrHexType[15] := 16;//'CastleImpass';}
      [*] = ;   // new pattern stand order, to fix water kill hills
      [*] = ;   arrHexType[0] := 1;//'PlainPass';
      [*] = ;   arrHexType[1] := 9;//'DesertPass';
      [*] = ;   arrHexType[2] := 11;//'DeadLandPass';
      [*] = ;   arrHexType[3] := 6;//'HillImpass';
      [*] = ;   arrHexType[4] := 3;//'ForestPass';
      [*] = ;   arrHexType[5] := 7;//'SwampPass';
      [*] = ;   arrHexType[6] := 2;//'PlainImpass';
      [*] = ;   arrHexType[7] := 4;//'ForestImpass';
      [*] = ;   arrHexType[8] := 8;//'SwampImpass';
      [*] = ;   arrHexType[9] := 5;//'HillPass';
      [*] = ;   arrHexType[10] := 10;//'DesertImpass';
      [*] = ;   arrHexType[11] := 12;//'DeadLandImpass';
      [*] = ;   arrHexType[12] := 13;//'CastleWallPass';
      [*] = ;   arrHexType[13] := 14;//'CastleWallImpass';
      [*] = ;   arrHexType[14] := 15;//'CastlePass';
      [*] = ;   arrHexType[15] := 16;//'CastleImpass';
      [*] = ;   
      [*] = ;   var indHexType : integer;
      [*] = ;   for indHexType := 0 to 15 do
      [*] = ;   begin
      [*] = ;      for i := 0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;      //for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;         var hexType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;   
      [*] = ;         var posX, posY, posZ : Float;
      [*] = ;         posX := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;         posZ := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;         posY := RayCastHeight(posX, posZ);
      [*] = ;   
      [*] = ;         var pLeftHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i+8);
      [*] = ;         var leftHexType : Integer = ParserGetIntValueByKeyByHandle(pLeftHexCell, 'Type');
      [*] = ;   
      [*] = ;         var pRightHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i-8);
      [*] = ;         var rightHexType : Integer = ParserGetIntValueByKeyByHandle(pRightHexCell, 'Type');
      [*] = ;   
      [*] = ;         if hexType = arrHexType[indHexType] then
      [*] = ;         begin
      [*] = ;            if (hexType = 7) then // 7 - SwampPass
      [*] = ;            begin
      [*] = ;               const cBaseName = 'swampfogbattle';
      [*] = ;               var goHnd : Integer = CreatePlayerGameObjectHandle(cParticlePlName, cParticlePlRace, cBaseName, posX-0.25, posY+1, posZ+0.5);
      [*] = ;            end;
      [*] = ;   
      [*] = ;            var x, y, z : Float;
      [*] = ;            //GetTrackNodePositionByIndex(i, x, y, z);
      [*] = ;            x := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;            z := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;   
      [*] = ;            // GEC
      [*] = ;            // fill castle patterns
      [*] = ;            var leftCorner : Boolean = false;
      [*] = ;            var rightCorner : Boolean = false;
      [*] = ;   
      [*] = ;            if (hexType = 13) or (hexType = 14) or (hexType = 15) then
      [*] = ;            begin
      [*] = ;               var tmpX, tmpY, tmpZ : Float;
      [*] = ;               GetTrackNodePositionByIndex(0, tmpX, tmpY, tmpZ);
      [*] = ;               z := tmpZ+4.5*(i div 8);
      [*] = ;   
      [*] = ;               var xShift : Float = Sqrt(3) / 4 * gc_HexSize;
      [*] = ;   
      [*] = ;               if (i div gc_battle_GridSize) mod 2 = 0 then
      [*] = ;               x := x + xShift
      [*] = ;               else
      [*] = ;               x := x - xShift;
      [*] = ;   
      [*] = ;               if (hexType = 13) and (leftHexType = 14) then
      [*] = ;               leftCorner := true;
      [*] = ;   
      [*] = ;               if (hexType = 13) and (rightHexType = 14) then
      [*] = ;               rightCorner := true;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            for j := 0 to ParserGetCountByHandle(pPatterns)-1 do
      [*] = ;            begin
      [*] = ;               var pPatternZone : Integer = ParserSelectByHandleByIndex(pPatterns, j);
      [*] = ;   
      [*] = ;               var zoneType : Integer = ParserGetIntValueByKeyByHandle(pPatternZone, 'Type');
      [*] = ;               if hexType = zoneType then
      [*] = ;               begin
      [*] = ;                  var pPatterns : Integer = ParserSelectByHandleByKey(pPatternZone, 'Patterns');
      [*] = ;                  var sum : Float = 0;
      [*] = ;                  var g : Integer;
      [*] = ;                  for g := 0 to ParserGetCountByHandle(pPatterns)-1 do
      [*] = ;                  begin
      [*] = ;                     var pPattern : Integer = ParserSelectByHandleByIndex(pPatterns, g);
      [*] = ;                     var pWorldRuleVisualFreqs : Integer = ParserSelectByHandleByKey(pPattern, 'WorldRuleVisualFreqs');
      [*] = ;                     var siegeLevelMin : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMin');
      [*] = ;                     var siegeLevelMax : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMax');
      [*] = ;                     if (siegeLevelMin=0) or (siegeLevel=0) or ((siegeLevel<>0) and (siegeLevel>=siegeLevelMin) and (siegeLevel<=siegeLevelMax)) then
      [*] = ;                     begin
      [*] = ;                        var k : Integer;
      [*] = ;                        for k:=0 to ParserGetCountByHandle(pWorldRuleVisualFreqs)-1 do
      [*] = ;                        begin
      [*] = ;                           var pWorldRuleVisualFreq : Integer = ParserSelectByHandleByIndex(pWorldRuleVisualFreqs, k);
      [*] = ;                           if (curVisualID=ParserGetIntValueByKeyByHandle(pWorldRuleVisualFreq, 'VisualID')) then
      [*] = ;                           begin
      [*] = ;                              var freq : Float = ParserGetFloatValueByKeyByHandle(pWorldRuleVisualFreq, 'Frequency');
      [*] = ;                              sum := sum + freq;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;   
      [*] = ;                  var ind : Float = Random * sum;
      [*] = ;                  sum := 0;
      [*] = ;   
      [*] = ;                  for g := 0 to ParserGetCountByHandle(pPatterns)-1 do
      [*] = ;                  begin
      [*] = ;                     var pPattern : Integer = ParserSelectByHandleByIndex(pPatterns, g);
      [*] = ;                     var isWater : Boolean = false;
      [*] = ;                     isWater := ParserGetBoolValueByKeyByHandle(pPattern, 'Water');
      [*] = ;   
      [*] = ;                     var pWorldRuleVisualFreqs : Integer = ParserSelectByHandleByKey(pPattern, 'WorldRuleVisualFreqs');
      [*] = ;                     var siegeLevelMin : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMin');
      [*] = ;                     var siegeLevelMax : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMax');
      [*] = ;                     if (siegeLevelMin=0) or (siegeLevel=0) or ((siegeLevel<>0) and (siegeLevel>=siegeLevelMin) and (siegeLevel<=siegeLevelMax)) then
      [*] = ;                     begin
      [*] = ;                        var k : Integer;
      [*] = ;                        for k:=0 to ParserGetCountByHandle(pWorldRuleVisualFreqs)-1 do
      [*] = ;                        begin
      [*] = ;                           var pWorldRuleVisualFreq : Integer = ParserSelectByHandleByIndex(pWorldRuleVisualFreqs, k);
      [*] = ;                           if (curVisualID=ParserGetIntValueByKeyByHandle(pWorldRuleVisualFreq, 'VisualID')) then
      [*] = ;                           begin
      [*] = ;                              var freq : Float = ParserGetFloatValueByKeyByHandle(pWorldRuleVisualFreq, 'Frequency');
      [*] = ;                              sum := sum + freq;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if sum >= ind then
      [*] = ;                        begin
      [*] = ;                           var patName : String = ParserGetValueByKeyByHandle(pPattern, 'Name');
      [*] = ;                           var isRandRotate : Boolean = false;
      [*] = ;                           isRandRotate := ParserGetBoolValueByKeyByHandle(pPattern, 'RandRotate');
      [*] = ;   
      [*] = ;                           var angle : Float = 0;
      [*] = ;                           if isRandRotate then angle := Floor(4*Random) * 90;
      [*] = ;   
      [*] = ;                           angle := angle / 180 * pi;
      [*] = ;                           // stand pattern
      [*] = ;                           StandPattern(uPlHandle, patName, x, z, angle);
      [*] = ;   
      [*] = ;                           if isWater then WaterFieldAdd(gc_WaterNameBattle, x - gc_HexSize*1, z - gc_HexSize*1, x + gc_HexSize*1, z + gc_HexSize*1, -0.85);
      [*] = ;   
      [*] = ;                           var pLayers : Integer = ParserSelectByHandleByKey(pPattern, 'Layers');
      [*] = ;                           if ParserGetCountByHandle(pLayers)>0 then
      [*] = ;                           begin
      [*] = ;                              var indLayer : Integer = Floor(Random*ParserGetCountByHandle(pLayers));
      [*] = ;                              patName := ParserGetValueByIndexByHandle(pLayers, indLayer);
      [*] = ;                              angle := 0;
      [*] = ;                              StandPattern(uPlHandle, patName, x, z, angle);
      [*] = ;                           end;
      [*] = ;   
      [*] = ;                           var leftPatternName : String = 'battle-siege-outpost-garbage-left';
      [*] = ;                           var rightPatternName : String = 'battle-siege-outpost-garbage-right';
      [*] = ;                           case siegeLevel of
      [*] = ;                              1 : begin
      [*] = ;                                 leftPatternName := 'battle-siege-outpost-garbage-left';
      [*] = ;                                 rightPatternName := 'battle-siege-outpost-garbage-right';
      [*] = ;                              end;
      [*] = ;                              2 : begin
      [*] = ;                                 leftPatternName := 'battle-siege-fort-garbage-left';
      [*] = ;                                 rightPatternName := 'battle-siege-fort-garbage-right';
      [*] = ;                              end;
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 leftPatternName := 'battle-siege-garbage-left';
      [*] = ;                                 rightPatternName := 'battle-siege-garbage-right';
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                           
      [*] = ;                           if (leftCorner) then
      [*] = ;                              StandPattern(uPlHandle, leftPatternName, x, z, angle);
      [*] = ;                           if (rightCorner) then
      [*] = ;                              StandPattern(uPlHandle, rightPatternName, x, z, angle);
      [*] = ;   
      [*] = ;                           if (leftCorner) then // (hexType=13)
      [*] = ;                           begin
      [*] = ;                              var leftHexPosZ : Float = ParserGetFloatValueByKeyByHandle(pLeftHexCell, 'CenterY');
      [*] = ;                              FadeObjectsInRadiusByBaseName(x, leftHexPosZ-2, 2.5, 'wall_crash_left', 0.3);
      [*] = ;                           end;
      [*] = ;   
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            if hexType = 14 then
      [*] = ;            begin
      [*] = ;               if ParserGetBoolValueByKeyByHandle(pHexCell, 'Tower') then
      [*] = ;               begin
      [*] = ;                  var bnTower : String;
      [*] = ;                  if (siegeLevel>0) and (siegeLevel<3) then
      [*] = ;                     bnTower := 'fort_tower'
      [*] = ;                  else
      [*] = ;                     bnTower := 'tower';
      [*] = ;                  var goHandle : Integer = CreatePlayerGameObjectHandleByHandle(uPlHandle, 'buildings', bnTower, posX, 0, posZ);
      [*] = ;                  var ind : Integer = i - gc_battle_GridSize;
      [*] = ;   
      [*] = ;                  if ind >= 0 then
      [*] = ;                  begin
      [*] = ;                     var pHexCell1 : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                     var hexType : Integer = ParserGetIntValueByKeyByHandle(pHexCell1, 'Type');
      [*] = ;                     if (hexType=13) then
      [*] = ;                     begin
      [*] = ;                        FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'tower', 0.5);
      [*] = ;                        FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'fort_tower', 0.5);
      [*] = ;                        FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'wall01', 0.99);
      [*] = ;                        FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'outpost_wall', 0.99);
      [*] = ;                        FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'fort_wall', 0.99);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if gBoolRegister_BattleIsSiege then
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;   
      [*] = ;      var pTowers : Integer = _misc_ParserGetOrCreateByKey('towers_data', True);
      [*] = ;      IntRegister0 := pTowers;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetTowersData');
      [*] = ;      var towerCount : Integer = IntRegister1;
      [*] = ;      var mTowerCount : Integer = IntRegister2;
      [*] = ;   
      [*] = ;      for i := towerCount to towerCount+mTowerCount-1 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := i-towerCount;
      [*] = ;         ExecuteState('bat.GetMageTowerPosition');
      [*] = ;         var posX : Float = FloatRegister0;
      [*] = ;         var posY : Float = FloatRegister1;
      [*] = ;         var posZ : Float = FloatRegister2;
      [*] = ;   
      [*] = ;         var pTower : Integer = ParserSelectByHandleByIndex(pTowers, i);
      [*] = ;         var towerType : Integer = ParserGetIntValueByKeyByHandle(pTower, 'Type');
      [*] = ;         var baseName : String = '';
      [*] = ;         var scale : Float = 1;
      [*] = ;         var rotate : Float = 0;
      [*] = ;         case towerType of
      [*] = ;            1 : begin
      [*] = ;               baseName := 'sorcererscircle2';
      [*] = ;               scale := 1.3449;
      [*] = ;               rotate := -50;
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               baseName := 'library5';
      [*] = ;               scale := 1.4845;
      [*] = ;               rotate := -60;
      [*] = ;            end;
      [*] = ;            3 : begin
      [*] = ;               baseName := 'magetower2';
      [*] = ;               scale := 0.6412;
      [*] = ;               rotate := -40;
      [*] = ;            end;
      [*] = ;            4 : begin
      [*] = ;               baseName := 'magictower';
      [*] = ;               scale := 1.3785;
      [*] = ;               rotate := -230;
      [*] = ;            end;
      [*] = ;            5 : begin
      [*] = ;               baseName := 'bf_magictower'; //must be 'lightningtower', but it is too low quality for large siege size.
      [*] = ;               scale := 0.5667;
      [*] = ;               rotate := -60;
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               baseName := 'bf_magictower';
      [*] = ;               ErrorLog('unknown magic tower type = '+IntToStr(towerType));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         var goHandle : Integer = CreatePlayerGameObjectHandleByHandle(uPlHandle, 'buildings', baseName, posX, 0, posZ);
      [*] = ;         SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;         GameObjectRollByHandle(goHandle, rotate);
      [*] = ;         ClearObjectsAround(goHandle, 2.5);
      [*] = ;      end;
      [*] = ;      ParserClearByHandle(pTowers);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   TerrainUpdate(true, true);
      [*] = ;   _misc_NormalizeWaterFieldByName(gc_WaterNameBattle, 0.05, false, true);
      [*] = ;end;
      [*] = ;   
      [*] = ;procedure ClearDecalsOnBattleField();
      [*] = ;begin
      [*] = ;   const hexDecalPrefix = 'battlehex_';
      [*] = ;   var prefixLen : Integer = StrLength(hexDecalPrefix);
      [*] = ;      
      [*] = ;   ArrayClear();
      [*] = ;   var rad : Float = 24;
      [*] = ;   var x, z : Float;
      [*] = ;   var i, j, dHnd, decalCount : Integer;
      [*] = ;   for i:=0 to 2 do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         0 : begin
      [*] = ;            x := gFloatRegister_GridXCoord + gc_HexSize*12;
      [*] = ;            z := gFloatRegister_GridYCoord + gc_HexSize*0;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            x := gFloatRegister_GridXCoord + gc_HexSize*12;
      [*] = ;            z := gFloatRegister_GridYCoord + gc_HexSize*4;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            x := gFloatRegister_GridXCoord + gc_HexSize*12;
      [*] = ;            z := gFloatRegister_GridYCoord + gc_HexSize*8;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      GetDecalsInArea(round(x), round(z), rad);
      [*] = ;      decalCount := ArrayGetCount;
      [*] = ;      for j := 0 to decalCount-1 do
      [*] = ;      begin
      [*] = ;         dHnd := ArrayGetValueByIndex(j);
      [*] = ;         if (not SameText(SubStr(GetDecalNameByHandle(dHnd), 0, prefixLen), hexDecalPrefix)) then // reuse battlehexes over battles, destroy others
      [*] = ;            DestroyDecalByHandle(dHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   //if GetPlayerGameObjectsCountByHandle(uPlHandle) > 0 then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
      [*] = ;      ClearPlayerGameObjectsByHandle(GetPlayerHandleByName(cParticlePlName));
      [*] = ;      _map_ClearWaterFieldsByName(gc_WaterNameBattle);
      [*] = ;      ClearDecalsOnBattleField;
      [*] = ;   
      [*] = ;      var arrGlobalPattern : array[0..2] of String;
      [*] = ;      arrGlobalPattern[0] := 'clear-hex-grid-randomheight-4';
      [*] = ;      arrGlobalPattern[1] := 'clear-hex-grid-randomheight-5';
      [*] = ;      arrGlobalPattern[2] := 'clear-hex-grid-randomheight-7';
      [*] = ;      var indGlobalPattern : Integer = Floor(3*Random);
      [*] = ;
      [*] = ;      StandPattern(uPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4-8, gFloatRegister_GridYCoord + gc_HexSize*1, 0);
      [*] = ;      StandPattern(uPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4+22, gFloatRegister_GridYCoord + gc_HexSize*1, 0);
      [*] = ;
      [*] = ;      StandPattern(uPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4-8, gFloatRegister_GridYCoord + gc_HexSize*12, 0);
      [*] = ;      StandPattern(uPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4+22, gFloatRegister_GridYCoord + gc_HexSize*12, 0);
      [*] = ;      //StandPattern(uPlHandle, 'clear-hex-grid-randomheight-4', gc_HexSize*4, gc_HexSize*4, 0);
      [*] = ;
      [*] = ;      StandPattern(uPlHandle, arrGlobalPattern[indGlobalPattern], gFloatRegister_GridXCoord + gc_HexSize*4, gFloatRegister_GridYCoord + gc_HexSize*4, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then Clear();
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;sTrace := _log_name;
      [*] = ;if (runFlags and 2) > 0 then sTrace := sTrace + '['+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle))+', '+cParticlePlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(particlePlHandle))+']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace, $1000000 or _log_trace);
   struct.end
section.end

