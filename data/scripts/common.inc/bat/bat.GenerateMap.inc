section.begin
   Name = bat.GenerateMap
   Code : struct.begin
      [*] = ;var provInd1 : Integer = gIntRegister_BattleProvIndex1;
      [*] = ;var provInd2 : Integer = gIntRegister_BattleProvIndex2;
      [*] = ;var siteInd : Integer = gIntRegister_BattleSiteIndex;
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;function GetHexParserHandleByIndices(posX, posY : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pHexCell, 'Name');
      [*] = ;
      [*] = ;      var x : Integer = StrToInt(SubStr(name, StrPos('.', name)+1, 1));
      [*] = ;      var y : Integer = StrToInt(SubStr(name, StrLength(name), 1));
      [*] = ;      var x1 : Integer =  ParserGetIntValueByKeyByHandle(pHexCell, 'X');
      [*] = ;      var y1 : Integer =  ParserGetIntValueByKeyByHandle(pHexCell, 'Y');
      [*] = ;
      [*] = ;      if (x = posX) and (y = posY) then
      [*] = ;      begin
      [*] = ;         Result := pHexCell;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetActiveTrackNodeList(1);
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;begin
      [*] = ;   var index, pTerrain : Integer;
      [*] = ;   if (gInetBattle.map.lefttype<>0) then
      [*] = ;      index := gInetBattle.map.lefttype
      [*] = ;   else
      [*] = ;      index := 1+Floor(Random*6);
      [*] = ;   pTerrain := ParserSelectByHandleByIndex(gPrototypeData.terrainTypes.handle, index);
      [*] = ;   gStringRegister_Battle_LeftTType := ParserGetValueByKeyByHandle(pTerrain, 'Name');
      [*] = ;
      [*] = ;   if (gInetBattle.map.righttype<>0) then
      [*] = ;      index := gInetBattle.map.righttype
      [*] = ;   else
      [*] = ;      index := 1+Floor(Random*6);
      [*] = ;   pTerrain := ParserSelectByHandleByIndex(gPrototypeData.terrainTypes.handle, index);
      [*] = ;   gStringRegister_Battle_RightTType := ParserGetValueByKeyByHandle(pTerrain, 'Name');
      [*] = ;end
      [*] = ;else
      [*] = ;if (gIntRegister_CurDemoMode=2) then
      [*] = ;begin
      [*] = ;   var pDemoGame : Integer = _misc_ParserGetOrCreateByKey('DemoGame',false);
      [*] = ;   var leftTType : String = ParserGetValueByKeyByHandle(pDemoGame, 'LeftTType');
      [*] = ;   if (leftTType<>'') then
      [*] = ;      gStringRegister_Battle_LeftTType := leftTType;
      [*] = ;
      [*] = ;   var rightTType : String = ParserGetValueByKeyByHandle(pDemoGame, 'RightTType');
      [*] = ;   if (rightTType<>'') then
      [*] = ;      gStringRegister_Battle_RightTType := rightTType;
      [*] = ;end;
      [*] = ;
      [*] = ;var pZoneList : Integer = gBattleData.zoneList.handle;
      [*] = ;var pColZones : Integer = gBattleData.columnZones.handle;
      [*] = ;
      [*] = ;var rZoneLeft : String = gStringRegister_Battle_LeftTType;
      [*] = ;var rZoneRight : String = gStringRegister_Battle_RightTType;
      [*] = ;//log(rZoneLeft + ' vs ' + rZoneRight);
      [*] = ;
      [*] = ;var i, j, g : Integer;
      [*] = ;var pLeftZone, pRightZone : Integer;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pZoneList)-1 do
      [*] = ;begin
      [*] = ;   var pZone : Integer = ParserSelectByHandleByIndex(pZoneList, i);
      [*] = ;   var zoneName : String = ParserGetValueByKeyByHandle(pZone, 'Name');
      [*] = ;
      [*] = ;   if SameText(zoneName, rZoneLeft) then
      [*] = ;      pLeftZone := pZone;
      [*] = ;   if SameText(zoneName, rZoneRight) then
      [*] = ;      pRightZone := pZone;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pColZones) do
      [*] = ;begin
      [*] = ;   var pColZone : Integer = ParserSelectByHandleByIndex(pColZones, i);
      [*] = ;   var pZonesFreq : Integer = ParserSelectByHandleByKey(pColZone, 'ZonesFreq');
      [*] = ;   for j := 0 to ParserGetCountByHandle(pZonesFreq)-1 do
      [*] = ;   begin
      [*] = ;      var pZoneFreq : Integer = ParserSelectByHandleByIndex(pZonesFreq, j);
      [*] = ;
      [*] = ;      var leftPass : Boolean = false;
      [*] = ;      leftPass := ParserGetBoolValueByKeyByHandle(pZoneFreq, 'LeftPass');
      [*] = ;      var leftImpass : Boolean = false;
      [*] = ;      leftImpass := ParserGetBoolValueByKeyByHandle(pZoneFreq, 'LeftImpass');
      [*] = ;      var rightPass : Boolean = false;
      [*] = ;      rightPass := ParserGetBoolValueByKeyByHandle(pZoneFreq, 'RightPass');
      [*] = ;      var rightImpass : Boolean = false;
      [*] = ;      rightImpass := ParserGetBoolValueByKeyByHandle(pZoneFreq, 'RightImpass');
      [*] = ;
      [*] = ;      var zoneID : Integer = 0;
      [*] = ;
      [*] = ;      if leftPass then
      [*] = ;      zoneID := ParserGetIntValueByKeyByHandle(pLeftZone, 'Pass');
      [*] = ;
      [*] = ;      if leftImpass then
      [*] = ;      zoneID := ParserGetIntValueByKeyByHandle(pLeftZone, 'Impass');
      [*] = ;
      [*] = ;      if rightPass then
      [*] = ;      zoneID := ParserGetIntValueByKeyByHandle(pRightZone, 'Pass');
      [*] = ;
      [*] = ;      if rightImpass then
      [*] = ;      zoneID := ParserGetIntValueByKeyByHandle(pRightZone, 'Impass');
      [*] = ;
      [*] = ;      if zoneID > 0 then
      [*] = ;      ParserSetIntValueByKeyByHandle(pZoneFreq, 'Type', zoneID);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var curVisualID : Integer = 0;
      [*] = ;// world rule
      [*] = ;{if (gGame.gametype=2) then
      [*] = ;begin
      [*] = ;   case gShards[gCampaign.activeShard].terrain of
      [*] = ;      6 : curVisualID := 2;
      [*] = ;      7 : curVisualID := 3;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else}
      [*] = ;if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pColZones)-1 do
      [*] = ;begin
      [*] = ;   var pColZone : Integer = ParserSelectByHandleByIndex(pColZones, i);
      [*] = ;   var pZonesFreq : Integer = ParserSelectByHandleByKey(pColZone, 'ZonesFreq');
      [*] = ;   var sum : Float = 0;
      [*] = ;
      [*] = ;   _rand_ClearRoll;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pZonesFreq)-1 do
      [*] = ;   begin
      [*] = ;      var pZoneFreq : Integer = ParserSelectByHandleByIndex(pZonesFreq, j);
      [*] = ;      var terType : Integer = ParserGetIntValueByKeyByHandle(pZoneFreq, 'Type');
      [*] = ;      var freq : Integer = ParserGetIntValueByKeyByHandle(pZoneFreq, 'Freq');
      [*] = ;      gArrRollerN[j] := terType;
      [*] = ;      gArrRollerP[j] := freq;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pColZones)-1 do
      [*] = ;   begin
      [*] = ;      var zoneID : Integer;
      [*] = ;      var rand : Float;
      [*] = ;
      [*] = ;      if provInd1 <> provInd2 then
      [*] = ;      begin
      [*] = ;         zoneID := _rand_RollSeed4(false, i, j, provInd1, provInd2);
      [*] = ;         rand := _rand_RandomSeed4(2, i, j, provInd1, provInd2);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         zoneID := _rand_RollSeed4(false, i, j, provInd1, siteInd);
      [*] = ;         rand := _rand_RandomSeed4(2, i, j, provInd1, siteInd);
      [*] = ;      end;
      [*] = ;      var borderCheckDeadLand : Boolean = ((SameText(rZoneLeft, 'DeadLand') and (i=3) and (rand = 0)) or ((SameText(rZoneRight, 'DeadLand') and (i=4) and (rand = 0))));
      [*] = ;      if (SameText(rZoneLeft, 'DeadLand')) and (SameText(rZoneRight, 'DeadLand')) then
      [*] = ;      borderCheckDeadLand := true;
      [*] = ;
      [*] = ;      if (curVisualID=3) then
      [*] = ;      begin
      [*] = ;         case zoneID of
      [*] = ;            2, 4, 6, 8 : zoneID := 12;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ((i<4) and (not SameText(rZoneLeft, 'Hill'))) or ((i>=4) and (not SameText(rZoneRight, 'Hill'))) or borderCheckDeadLand then
      [*] = ;         begin
      [*] = ;            if (zoneID=5) then
      [*] = ;            zoneID := 7; //11
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ((i<4) and (not SameText(rZoneLeft, 'Swamp'))) or ((i>=4) and (not SameText(rZoneRight, 'Swamp'))) or borderCheckDeadLand then
      [*] = ;         begin
      [*] = ;            if (zoneID=7) then
      [*] = ;            zoneID := 5; //11
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if ((i < 3) and SameText(rZoneLeft, 'DeadLand')) or ((i>4) and SameText(rZoneRight, 'DeadLand')) or borderCheckDeadLand then
      [*] = ;      begin
      [*] = ;         if (zoneID = 9) or (zoneID = 7) or (zoneID = 5) or (zoneID = 3) or (zoneID = 1) then
      [*] = ;         zoneID := 11
      [*] = ;         else
      [*] = ;         if (zoneID = 10) or (zoneID = 8) or (zoneID = 6) or (zoneID = 4) or (zoneID = 2) then
      [*] = ;         zoneID := 12;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var borderCheckDesert : Boolean = ((SameText(rZoneLeft, 'Desert') and (i=3) and (rand = 0)) or ((SameText(rZoneRight, 'Desert') and (i=4) and (rand = 0))));
      [*] = ;      if (SameText(rZoneLeft, 'Desert')) and (SameText(rZoneRight, 'Desert')) then
      [*] = ;      borderCheckDesert := true;
      [*] = ;
      [*] = ;      if (curVisualID=2) then
      [*] = ;      begin
      [*] = ;         if ((i<4) and (not SameText(rZoneLeft, 'Hill'))) or ((i>=4) and (not SameText(rZoneRight, 'Hill'))) or borderCheckDesert then
      [*] = ;         begin
      [*] = ;            if (zoneID=5) then
      [*] = ;            zoneID := 7; //9
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ((i<4) and (not SameText(rZoneLeft, 'Swamp'))) or ((i>=4) and (not SameText(rZoneRight, 'Swamp'))) or borderCheckDesert then
      [*] = ;         begin
      [*] = ;            if (zoneID=7) then
      [*] = ;            zoneID := 5; //9
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((i<3) and (SameText(rZoneLeft, 'Desert'))) or ((i>4) and (SameText(rZoneRight, 'Desert')))
      [*] = ;         or borderCheckDesert then
      [*] = ;         begin
      [*] = ;            if (zoneID = 11) or (zoneID = 7) or (zoneID = 5) or (zoneID = 3) or (zoneID = 1) then
      [*] = ;            zoneID := 9
      [*] = ;            else
      [*] = ;            if (zoneID = 12) or (zoneID = 8) or (zoneID = 6) or (zoneID = 4) or (zoneID = 2) then
      [*] = ;            zoneID := 10;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // world rule
      [*] = ;      if (curVisualID=2) then
      [*] = ;      begin
      [*] = ;         if (zoneID=1) then
      [*] = ;         zoneID := 9;
      [*] = ;         if (zoneID=2) then
      [*] = ;         zoneID := 10;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (curVisualID=3) then
      [*] = ;      begin
      [*] = ;         if (zoneID=1) then
      [*] = ;         zoneID := 11;
      [*] = ;         if (zoneID=2) then
      [*] = ;         zoneID := 12;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //var pHexCell : Integer = GetHexParserHandleByIndices(j, i);
      [*] = ;      var pHexCell : Integer = GetHexParserHandleByIndices(i, j);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Type', zoneID);
      [*] = ;      //ParserSetIntValueByKeyByHandle(pHexCell, 'X', i);
      [*] = ;      //ParserSetIntValueByKeyByHandle(pHexCell, 'Y', j);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// check siege
      [*] = ;var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;ExecuteState('bat.CheckSiege');
      [*] = ;
      [*] = ;if gBoolRegister_BattleIsSiege then
      [*] = ;begin
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetWallPercent');
      [*] = ;   var castleWall : Integer = IntRegister0;
      [*] = ;
      [*] = ;   Log('Castle wall health = ' + FloatToStr(castleWall) + ' %');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pColZones)-2 to ParserGetCountByHandle(pColZones)-1 do
      [*] = ;   begin
      [*] = ;      for j := 0 to ParserGetCountByHandle(pColZones)-1 do
      [*] = ;      begin
      [*] = ;         //var pHexCell : Integer = GetHexParserHandleByIndices(j, i);
      [*] = ;         var pHexCell : Integer = GetHexParserHandleByIndices(i, j);
      [*] = ;         //var x : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'X');
      [*] = ;         //var y : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Y');
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Type', 15);
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Layer', 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetTowersData');
      [*] = ;   var towerCount : Integer = IntRegister1;
      [*] = ;   var mTowerCount : Integer = IntRegister2;
      [*] = ;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pColZones)-1 do
      [*] = ;   begin
      [*] = ;      //var pHexCell : Integer = GetHexParserHandleByIndices(j, ParserGetCountByHandle(pColZones)-3);
      [*] = ;      var pHexCell : Integer = GetHexParserHandleByIndices(ParserGetCountByHandle(pColZones)-3, j);
      [*] = ;
      [*] = ;      IntRegister0 := j;
      [*] = ;      MapExecuteState('vvk.bat.GetWallTowerDataByIndex');
      [*] = ;      if castleWall <= IntRegister0 then
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Type', 13)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (IntRegister1 > 0) and (towerCount >= IntRegister1) then
      [*] = ;            ParserSetBoolValueByKeyByHandle(pHexCell, 'Tower', true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Type', 14);
      [*] = ;         ParserSetIntValueByKeyByHandle(pHexCell, 'Layer', 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pColZones)-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = GetHexParserHandleByIndices(ParserGetCountByHandle(pColZones)-4, j);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Type', 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// make passable tonnel
      [*] = ;var row : Integer = _rand_RandomSeed2(gc_battle_GridSize, provInd1, gGame.seed);
      [*] = ;for i := 0 to gc_battle_GridSize-1 do
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = GetHexParserHandleByIndices(i, row);
      [*] = ;   var hexType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;   if hexType mod 2 = 0 then
      [*] = ;   begin
      [*] = ;      if (ParserGetIntValueByKeyByHandle(pHexCell, 'Type')<>14) then
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Type', 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;begin
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;   var hexType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;
      [*] = ;   var layer : Integer;
      [*] = ;   if hexType mod 2 = 0 then
      [*] = ;      layer := 1
      [*] = ;   else
      [*] = ;      layer := 0;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'Layer', layer);
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_IsHumanPlayer then
      [*] = ;begin
      [*] = ;   //IntRegister0 := _obj_GetCheckSceneryFlags(gProfile.objectflags, gProfile.shardscenery, gProfile.townscenery, gProfile.provincescenery, $ff);
      [*] = ;   //GUIExecuteState('CheckScenery');
      [*] = ;   //ExecuteState('bat.LoadPatterns');
      [*] = ;   // we generate graphics from map.SwitchToBattle
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_InBattle := true;
      [*] = ;
      [*] = ;MapExecuteState('bat.DoAddPlayers');
   struct.end
section.end

