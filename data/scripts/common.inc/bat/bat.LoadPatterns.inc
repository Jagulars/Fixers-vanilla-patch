section.begin
   Name = bat.LoadPatterns
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.LOADPATTERNS';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;procedure HideObjectsInRadius(posX, posZ, radius : Float);
      [*] = ;begin
      [*] = ;   const cBattlePatternPlName = 'battle.pattern';
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cBattlePatternPlName);
      [*] = ;   GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, -1, 0, false, false, false, false, false, false);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectListCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectListByIndex(i);
      [*] = ;      var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;      if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;      AddObjectToDestroyList(goHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure HideObjectsInRectangle(posX, posZ, sizeX, sizeY : Float);
      [*] = ;begin
      [*] = ;   const cBattlePatternPlName = 'battle.pattern';
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cBattlePatternPlName);
      [*] = ;   var radius : Float = sqrt(sqr(sizeX)+sqr(sizeY));
      [*] = ;   GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, -1, 0, false, false, false, false, false, false);
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetGameObjectListCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectListByIndex(i);
      [*] = ;      var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;      var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;      if ((goPosX)>posX) and ((goPosX)<(posX+sizeX)) and ((goPosZ)>posZ) and ((goPosZ)<(posZ+sizeY)) then
      [*] = ;      AddObjectToDestroyList(goHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pointerPlayer : Integer = GetPlayerHandleByName('PlTrackBattle');
      [*] = ;if gc_RecyclePointers then
      [*] = ;   _plr_RecycleGameObjects(pointerPlayer)
      [*] = ;else
      [*] = ;   ClearPlayerGameObjectsByHandle(pointerPlayer);
      [*] = ;
      [*] = ;var posX, posY : integer;
      [*] = ;var xOff, yOff : integer;
      [*] = ;var backgroundPatName : String;
      [*] = ;
      [*] = ;var bSmoothTerrain : Boolean = True;
      [*] = ;
      [*] = ;// getting currentSiteID start
      [*] = ;var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, _gv_GetCurrentPlayerHandle());
      [*] = ;var action : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;var curSiteID : Integer = 0;
      [*] = ;if (action=gc_UnitTaskExplore) or (action=gc_UnitTaskAttackSite) then
      [*] = ;begin
      [*] = ;   var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;   IntRegister0 := curUID;
      [*] = ;   MapExecuteState('GetProvinceParserByUID');
      [*] = ;   var pProvince : Integer = IntRegister1;
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;   curSiteID := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pProvSites, siteInd), 'SiteID');
      [*] = ;end;
      [*] = ;// getting currentSiteID finish
      [*] = ;
      [*] = ;const cPatternPlName = 'battle.pattern';
      [*] = ;const cPatternRaceName = 'nature';
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var patPlHandle : Integer = GetPlayerHandleByName(cPatternPlName);
      [*] = ;if patPlHandle = 0 then
      [*] = ;   patPlHandle := CreatePlayer(cPatternPlName, cPatternRaceName, 'cmNone')
      [*] = ;else
      [*] = ;   ClearPlayerGameObjectsByHandle(patPlHandle);
      [*] = ;
      [*] = ;var curVisualID : Integer = 0;
      [*] = ;if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;   curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;
      [*] = ;procedure ClearDecalsOnBattleField();
      [*] = ;begin
      [*] = ;   const hexDecalPrefix = 'battlehex_';
      [*] = ;   var prefixLen : Integer = StrLength(hexDecalPrefix);
      [*] = ;   
      [*] = ;   ArrayClear();
      [*] = ;   var rad : Float = 24;
      [*] = ;   var x, z : Float;
      [*] = ;   var i, j : Integer;
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
      [*] = ;      var decalCount : Integer = ArrayGetCount;
      [*] = ;      for j := 0 to decalCount-1 do
      [*] = ;      begin
      [*] = ;         var dHnd : Integer = ArrayGetValueByIndex(j);
      [*] = ;         if (not SameText(SubStr(GetDecalNameByHandle(dHnd), 0, prefixLen), hexDecalPrefix)) then // reuse battlehexes over battles, destroy others
      [*] = ;            DestroyDecalByHandle(dHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillBackgroundPatterns(const bSiege, bStandLast, bStandAfterSmooth : Boolean);
      [*] = ;begin
      [*] = ;   var pPatternCovers  : Integer = _misc_ParserGetOrCreateByKey('pBackgroundPat',true);
      [*] = ;   const cPatternFileName = '.\data\gen\backgroundpatterns.cfg';
      [*] = ;   ParserLoadFromFile(cPatternFileName);
      [*] = ;
      [*] = ;   bSmoothTerrain := ParserGetBoolValueByKeyByHandle(pPatternCovers, 'SmoothTerrain');
      [*] = ;
      [*] = ;   // loading parsers
      [*] = ;   var debugCurSiteID : Integer = ParserGetIntValueByKeyByHandle(pPatternCovers, 'DebugCurSiteID');
      [*] = ;   if (debugCurSiteID<>0) then
      [*] = ;   curSiteID := debugCurSiteID;
      [*] = ;
      [*] = ;   if (gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;   begin
      [*] = ;      var index, pTerrain : Integer;
      [*] = ;      if (gInetBattle.map.lefttype<>0) then
      [*] = ;      index := gInetBattle.map.lefttype
      [*] = ;      else
      [*] = ;      index := 1+floor(random*6);
      [*] = ;      pTerrain := ParserSelectByHandleByIndex(gPrototypeData.terrainTypes.handle, index);
      [*] = ;      gStringRegister_Battle_LeftTType := ParserGetValueByKeyByHandle(pTerrain, 'Name');
      [*] = ;
      [*] = ;      if (gInetBattle.map.righttype<>0) then
      [*] = ;      index := gInetBattle.map.righttype
      [*] = ;      else
      [*] = ;      index := 1+floor(random*6);
      [*] = ;      pTerrain := ParserSelectByHandleByIndex(gPrototypeData.terrainTypes.handle, index);
      [*] = ;      gStringRegister_Battle_RightTType := ParserGetValueByKeyByHandle(pTerrain, 'Name');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gIntRegister_CurDemoMode=2) then
      [*] = ;   begin
      [*] = ;      var pDemoGame : Integer = _misc_ParserGetOrCreateByKey('DemoGame',false);
      [*] = ;      var leftTType : String = ParserGetValueByKeyByHandle(pDemoGame, 'LeftTType');
      [*] = ;      if (leftTType<>'') then
      [*] = ;         gStringRegister_Battle_LeftTType := leftTType;
      [*] = ;
      [*] = ;      var rightTType : String = ParserGetValueByKeyByHandle(pDemoGame, 'RightTType');
      [*] = ;      if (rightTType<>'') then
      [*] = ;         gStringRegister_Battle_RightTType := rightTType;
      [*] = ;
      [*] = ;      curSiteID := ParserGetIntValueByKeyByHandle(pDemoGame, 'CurSiteID');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var leftTType : String = gStringRegister_Battle_LeftTType;
      [*] = ;   var rightTType : String = gStringRegister_Battle_RightTType;
      [*] = ;
      [*] = ;   case curVisualID of
      [*] = ;      2 : begin
      [*] = ;         leftTType := 'Desert';
      [*] = ;         rightTType := 'Desert';
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         leftTType := 'DeadLand';
      [*] = ;         rightTType := 'DeadLand';
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         //leftTType := 'Autumn';
      [*] = ;         //rightTType := 'Autumn';
      [*] = ;      end;
      [*] = ;      5 : begin
      [*] = ;         leftTType := 'DeadLand';
      [*] = ;         rightTType := 'DeadLand';
      [*] = ;         //leftTType := 'Vulcan';
      [*] = ;         //rightTType := 'Vulcan';
      [*] = ;      end;
      [*] = ;      //6 : begin
      [*] = ;         //   leftTType := 'Ice';
      [*] = ;         //   rightTType := 'Ice';
      [*] = ;      //end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var debugLeftTType : String = ParserGetValueByKeyByHandle(pPatternCovers, 'DebugLeftTType');
      [*] = ;   var debugRightTType : String = ParserGetValueByKeyByHandle(pPatternCovers, 'DebugRightTType');
      [*] = ;   if (debugLeftTType<>'') then
      [*] = ;      leftTType := debugLeftTType;
      [*] = ;   if (debugRightTType<>'') then
      [*] = ;      rightTType := debugRightTType;
      [*] = ;
      [*] = ;   pPatternCovers := ParserSelectByHandleByKey(pPatternCovers, 'BackgroundPatterns');
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pPatternCovers)-1 do
      [*] = ;   begin
      [*] = ;      var pPatternCover : Integer = ParserSelectByHandleByIndex(pPatternCovers, i);
      [*] = ;
      [*] = ;      var patternName : String;
      [*] = ;      var posX, posY : Integer;
      [*] = ;      var debug, unique, standLast, standAfterSmooth : Boolean;
      [*] = ;      patternName := ParserGetValueByKeyByHandle(pPatternCover, 'PatternName');
      [*] = ;      posX := ParserGetIntValueByKeyByHandle(pPatternCover, 'PosX');
      [*] = ;      posY := ParserGetIntValueByKeyByHandle(pPatternCover, 'PosY');
      [*] = ;      debug := ParserGetBoolValueByKeyByHandle(pPatternCover, 'Debug');
      [*] = ;      unique := ParserGetBoolValueByKeyByHandle(pPatternCover, 'Unique');
      [*] = ;      standLast := ParserGetBoolValueByKeyByHandle(pPatternCover, 'StandLast');
      [*] = ;      standAfterSmooth := ParserGetBoolValueByKeyByHandle(pPatternCover, 'StandAfterSmooth');
      [*] = ;
      [*] = ;      var pIgnoreOnSites : Integer = ParserSelectByHandleByKey(pPatternCover, 'IgnoreOnSites');
      [*] = ;      var bIgnore : Boolean = False;
      [*] = ;      if (pIgnoreOnSites<>0) then
      [*] = ;      begin
      [*] = ;         var j : Integer;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pIgnoreOnSites)-1 do
      [*] = ;         begin
      [*] = ;            var ignoreOnSite : Integer = ParserGetIntValueByIndexByHandle(pIgnoreOnSites, j);
      [*] = ;            if (ignoreOnSite=curSiteID) then
      [*] = ;            begin
      [*] = ;               bIgnore := True;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not bIgnore) and ((standLast=bStandLast) or bStandAfterSmooth) and (standAfterSmooth=bStandAfterSmooth) then
      [*] = ;      begin
      [*] = ;         if debug then
      [*] = ;         begin
      [*] = ;            posX := posX+gIntRegister_dbgX;
      [*] = ;            posY := posY+gIntRegister_dbgY;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (unique) then
      [*] = ;         begin
      [*] = ;            var pSites : Integer = ParserSelectByHandleByKey(pPatternCover, 'Sites');
      [*] = ;
      [*] = ;            var j : Integer;
      [*] = ;            for j:=0 to ParserGetCountByHandle(pSites)-1 do
      [*] = ;            begin
      [*] = ;               var site : Integer = ParserGetIntValueByIndexByHandle(pSites, j);
      [*] = ;               if (site=curSiteID) then
      [*] = ;               begin
      [*] = ;                  var pTerrainTypes : Integer = ParserSelectByHandleByKey(pPatternCover, 'TerrainTypes');
      [*] = ;                  var j : Integer;
      [*] = ;                  for j:=0 to ParserGetCountByHandle(pTerrainTypes)-1 do
      [*] = ;                  begin
      [*] = ;                     var terrainType : Integer = ParserGetIntValueByIndexByHandle(pTerrainTypes, j);
      [*] = ;                     var sTerrainType : String = '';
      [*] = ;                     case terrainType of
      [*] = ;                        1 : sTerrainType := 'Plain';
      [*] = ;                        2 : sTerrainType := 'Forest';
      [*] = ;                        3 : sTerrainType := 'Hill';
      [*] = ;                        4 : sTerrainType := 'Swamp';
      [*] = ;                        5 : sTerrainType := 'Desert';
      [*] = ;                        6 : sTerrainType := 'DeadLand';
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (not SameText(rightTType, sTerrainType)) then
      [*] = ;                     begin
      [*] = ;                        bIgnore := True
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        bIgnore := False;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (not bIgnore) then
      [*] = ;                  begin
      [*] = ;                     var pClearObjects : Integer = ParserSelectByHandleByKey(pPatternCover, 'ClearObjects');
      [*] = ;                     if (pClearObjects<>0) then
      [*] = ;                     begin
      [*] = ;                        var k : Integer;
      [*] = ;                        for k:=0 to ParserGetCountByHandle(pClearObjects)-1 do
      [*] = ;                        begin
      [*] = ;                           var pClearObject : Integer = ParserSelectByHandleByIndex(pClearObjects, k);
      [*] = ;                           var sizeX : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'SizeX');
      [*] = ;                           var sizeY : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'SizeY');
      [*] = ;                           if (sizeX>0) and (sizeY>0) then
      [*] = ;                           begin
      [*] = ;                              var offX : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffX');
      [*] = ;                              var offY : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffY');
      [*] = ;                              var clearX : Float = floor(gFloatRegister_GridXCoord+gc_HexSize*4+posX)+offX;
      [*] = ;                              var clearY : Float = floor(gFloatRegister_GridYCoord+gc_HexSize*4+posY)+offY;
      [*] = ;                              HideObjectsInRectangle(clearX, clearY, sizeX, sizeY);
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           var radius : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'Radius');
      [*] = ;                           if (radius>0) then
      [*] = ;                           begin
      [*] = ;                              var offX : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffX');
      [*] = ;                              var offY : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffY');
      [*] = ;                              var clearX : Float = floor(gFloatRegister_GridXCoord+gc_HexSize*4+posX)+offX;
      [*] = ;                              var clearY : Float = floor(gFloatRegister_GridYCoord+gc_HexSize*4+posY)+offY;
      [*] = ;                              HideObjectsInRadius(clearX, clearY, radius);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     StandPattern(patPlHandle, patternName, gFloatRegister_GridXCoord + gc_HexSize*4 + posX, gFloatRegister_GridYCoord + gc_HexSize*4 + posY, 0);
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (not bIgnore) then
      [*] = ;            begin
      [*] = ;               var pTerrainTypes : Integer = ParserSelectByHandleByKey(pPatternCover, 'TerrainTypes');
      [*] = ;               var sideLeft : Boolean = ParserGetBoolValueByKeyByHandle(pPatternCover, 'SideLeft');
      [*] = ;               var sideRight : Boolean = ParserGetBoolValueByKeyByHandle(pPatternCover, 'SideRight');
      [*] = ;               var j : Integer;
      [*] = ;               for j:=0 to ParserGetCountByHandle(pTerrainTypes)-1 do
      [*] = ;               begin
      [*] = ;                  var terrainType : Integer = ParserGetIntValueByIndexByHandle(pTerrainTypes, j);
      [*] = ;                  var sTerrainType : String = '';
      [*] = ;                  case terrainType of
      [*] = ;                     1 : sTerrainType := 'Plain';
      [*] = ;                     2 : sTerrainType := 'Forest';
      [*] = ;                     3 : sTerrainType := 'Hill';
      [*] = ;                     4 : sTerrainType := 'Swamp';
      [*] = ;                     5 : sTerrainType := 'Desert';
      [*] = ;                     6 : sTerrainType := 'DeadLand';
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (sideLeft) then
      [*] = ;                  begin
      [*] = ;                     if (not SameText(leftTType, sTerrainType)) then
      [*] = ;                     begin
      [*] = ;                        bIgnore := True
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     bIgnore := False;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (sideRight) then
      [*] = ;                  begin
      [*] = ;                     if (not SameText(rightTType, sTerrainType)) then
      [*] = ;                     begin
      [*] = ;                        bIgnore := True
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     bIgnore := False;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (not bIgnore) then
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (not bIgnore) then
      [*] = ;               begin
      [*] = ;                  var pWorldRuleVisuals : Integer = ParserSelectByHandleByKey(pPatternCover, 'WorldRuleVisuals');
      [*] = ;                  if (pWorldRuleVisuals<>0) then
      [*] = ;                  begin
      [*] = ;                     var count : Integer = ParserGetCountByHandle(pWorldRuleVisuals);
      [*] = ;                     if (count>0) then
      [*] = ;                     begin
      [*] = ;                        bIgnore := True;
      [*] = ;                        for j:=0 to count-1 do
      [*] = ;                        begin
      [*] = ;                           var visualID : Integer = ParserGetIntValueByIndexByHandle(pWorldRuleVisuals, j);
      [*] = ;                           if (visualID=curVisualID) then
      [*] = ;                           begin
      [*] = ;                              bIgnore := False;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var useOnSiege : Boolean = ParserGetBoolValueByKeyByHandle(pPatternCover, 'UseOnSiege');
      [*] = ;               if (not bIgnore) and (not bSiege) or ((bSiege) and (UseOnSiege)) then
      [*] = ;               StandPattern(patPlHandle, patternName, gFloatRegister_GridXCoord + gc_HexSize*4 + posX, gFloatRegister_GridYCoord + gc_HexSize*4 + posY, 0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //log('x = ' + IntToStr(posX) + '; y = ' + IntToStr(posY) + '; patName = ' + backgroundPatName);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearObjectsAround(goHandle : Integer; radius : Float);
      [*] = ;begin
      [*] = ;   var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;   var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;   var radius : Float = 2.5;
      [*] = ;   const cBattlePatternPlName = 'battle.pattern';
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cBattlePatternPlName);
      [*] = ;   GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, -1, 0, false, false, false, false, false, false);
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to GetGameObjectListCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;      if (goHnd<>goHandle) then
      [*] = ;      begin
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;
      [*] = ;         if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;         SetGameObjectVisibleByHandle(goHnd, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FadeObjectsInRadiusByBaseName(posX, posZ, radius : Float; baseName : String; alpha : Float);
      [*] = ;begin
      [*] = ;   const cBattlePatternPlName = 'battle.pattern';
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cBattlePatternPlName);
      [*] = ;   GetGameObjectsInRadius(posX, posZ, radius, false, true, plHnd, -1, 0, false, false, false, false, false, false);
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to GetGameObjectListCount-1 do
      [*] = ;   begin
      [*] = ;      var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;      var goBaseName : String = GetGameObjectBaseNameByHandle(goHnd);
      [*] = ;      if (SameText(goBaseName, baseName)) then
      [*] = ;      begin
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;
      [*] = ;         if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;         begin
      [*] = ;            _fx_CreateAlphaFadeEffect(goHnd, 0, alpha, alpha, 'alphaeffect');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pPatterns : Integer = gBattleData.patternList.handle;
      [*] = ;
      [*] = ;LoadPatterns(true, true);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;var arrGlobalPattern : array[0..2] of String;
      [*] = ;arrGlobalPattern[0] := 'clear-hex-grid-randomheight-4';
      [*] = ;arrGlobalPattern[1] := 'clear-hex-grid-randomheight-5';
      [*] = ;arrGlobalPattern[2] := 'clear-hex-grid-randomheight-7';
      [*] = ;var indGlobalPattern : integer = Floor(3*RandomExt);
      [*] = ;
      [*] = ;StandPattern(patPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4-8, gFloatRegister_GridYCoord + gc_HexSize*1, 0);
      [*] = ;StandPattern(patPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4+22, gFloatRegister_GridYCoord + gc_HexSize*1, 0);
      [*] = ;
      [*] = ;StandPattern(patPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4-8, gFloatRegister_GridYCoord + gc_HexSize*12, 0);
      [*] = ;StandPattern(patPlHandle, 'clear-hex-grid', gFloatRegister_GridXCoord + gc_HexSize*4+22, gFloatRegister_GridYCoord + gc_HexSize*12, 0);
      [*] = ;//StandPattern(patPlHandle, 'clear-hex-grid-randomheight-4', gc_HexSize*4, gc_HexSize*4, 0);
      [*] = ;
      [*] = ;StandPattern(patPlHandle, arrGlobalPattern[indGlobalPattern], gFloatRegister_GridXCoord + gc_HexSize*4, gFloatRegister_GridYCoord + gc_HexSize*4, 0);
      [*] = ;
      [*] = ;ClearDecalsOnBattleField;
      [*] = ;
      [*] = ;var siegeLevel : Integer = 0;
      [*] = ;if (gBoolRegister_BattleIsSiege) then
      [*] = ;begin
      [*] = ;   var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;   var bCastle : Boolean =  ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;   var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;   var pGarrisonSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;   if (bCastle) then
      [*] = ;   siegeLevel := 5
      [*] = ;   else
      [*] = ;   for i:=3 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGarrisonSlot : Integer = ParserSelectByHandleByIndex(pGarrisonSlots, i);
      [*] = ;      var count : Integer = ParserGetIntValueByKeyByHandle(pGarrisonSlot, 'Count');
      [*] = ;      if (count>0) then
      [*] = ;      begin
      [*] = ;         siegeLevel := i+1;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if _obj_EnabledByFlag(gc_ObjectFlagBattleDecor) then // unfortunately, the fortification ground and the surrounding scenery is clumped into one pattern, so we can't have just the ground texture unless the pattern is tampered with.
      [*] = ;   begin
      [*] = ;      StandPattern(patPlHandle, 'battle-siege-ground-6', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;      case siegeLevel of
      [*] = ;         1 : StandPattern(patPlHandle, 'battle-siege-outpost-ground-6-onlywalls', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;         2 : StandPattern(patPlHandle, 'battle-siege-fort-ground-6-onlywalls', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;         else
      [*] = ;         StandPattern(patPlHandle, 'battle-siege-ground-6-onlywalls', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _obj_EnabledByFlag(gc_ObjectFlagBattleDecor) then
      [*] = ;FillBackgroundPatterns(gBoolRegister_BattleIsSiege, False, False);
      [*] = ;
      [*] = ;var arrHexType : array[0..15] of Integer;
      [*] = ;{arrHexType[0] := 1;//'PlainPass';
      [*] = ;arrHexType[1] := 9;//'DesertPass';
      [*] = ;arrHexType[2] := 11;//'DeadLandPass';
      [*] = ;arrHexType[3] := 6;//'HillImpass';
      [*] = ;arrHexType[4] := 5;//'HillPass';
      [*] = ;arrHexType[5] := 3;//'ForestPass';
      [*] = ;arrHexType[6] := 7;//'SwampPass';
      [*] = ;arrHexType[7] := 2;//'PlainImpass';
      [*] = ;arrHexType[8] := 4;//'ForestImpass';
      [*] = ;arrHexType[9] := 8;//'SwampImpass';
      [*] = ;arrHexType[10] := 10;//'DesertImpass';
      [*] = ;arrHexType[11] := 12;//'DeadLandImpass';
      [*] = ;arrHexType[12] := 13;//'CastleWallPass';
      [*] = ;arrHexType[13] := 14;//'CastleWallImpass';
      [*] = ;arrHexType[14] := 15;//'CastlePass';
      [*] = ;arrHexType[15] := 16;//'CastleImpass';}
      [*] = ;// new pattern stand order, to fix water kill hills
      [*] = ;arrHexType[0] := 1;//'PlainPass';
      [*] = ;arrHexType[1] := 9;//'DesertPass';
      [*] = ;arrHexType[2] := 11;//'DeadLandPass';
      [*] = ;arrHexType[3] := 6;//'HillImpass';
      [*] = ;arrHexType[4] := 3;//'ForestPass';
      [*] = ;arrHexType[5] := 7;//'SwampPass';
      [*] = ;arrHexType[6] := 2;//'PlainImpass';
      [*] = ;arrHexType[7] := 4;//'ForestImpass';
      [*] = ;arrHexType[8] := 8;//'SwampImpass';
      [*] = ;arrHexType[9] := 5;//'HillPass';
      [*] = ;arrHexType[10] := 10;//'DesertImpass';
      [*] = ;arrHexType[11] := 12;//'DeadLandImpass';
      [*] = ;arrHexType[12] := 13;//'CastleWallPass';
      [*] = ;arrHexType[13] := 14;//'CastleWallImpass';
      [*] = ;arrHexType[14] := 15;//'CastlePass';
      [*] = ;arrHexType[15] := 16;//'CastleImpass';
      [*] = ;var indHexType : integer;
      [*] = ;
      [*] = ;const cRaceName = 'misc';
      [*] = ;const cPlayerName = 'particles.battle';
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;if (plHandle<>0) then
      [*] = ;   DeletePlayerByHandle(plHandle);
      [*] = ;plHandle := CreatePlayer(cPlayerName, cRaceName, 'cmPC'); //to progress state machine
      [*] = ;
      [*] = ;for indHexType := 0 to 15 do
      [*] = ;begin
      [*] = ;   for i := 0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;   //for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;      var hexType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;
      [*] = ;      var posX, posY, posZ : Float;
      [*] = ;      posX := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;      posZ := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;      posY := RayCastHeight(posX, posZ);
      [*] = ;
      [*] = ;      var pLeftHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i+8);
      [*] = ;      var leftHexType : Integer = ParserGetIntValueByKeyByHandle(pLeftHexCell, 'Type');
      [*] = ;
      [*] = ;      var pRightHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i-8);
      [*] = ;      var rightHexType : Integer = ParserGetIntValueByKeyByHandle(pRightHexCell, 'Type');
      [*] = ;
      [*] = ;      if hexType = arrHexType[indHexType] then
      [*] = ;      begin
      [*] = ;         if (hexType = 7) and _obj_EnabledByFlag(gc_ObjectFlagBattleDecor) then // 7 - SwampPass
      [*] = ;         begin
      [*] = ;            const cBaseName = 'swampfogbattle';
      [*] = ;            var goHnd : Integer;
      [*] = ;
      [*] = ;            goHnd := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, cBaseName, posX-0.25, posY+1, posZ+0.5);
      [*] = ;         end;
      [*] = ;
      [*] = ;         var x, y, z : Float;
      [*] = ;         //GetTrackNodePositionByIndex(i, x, y, z);
      [*] = ;         x := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;         z := ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;
      [*] = ;         // GEC
      [*] = ;         // fill castle patterns
      [*] = ;         var leftCorner : Boolean = false;
      [*] = ;         var rightCorner : Boolean = false;
      [*] = ;
      [*] = ;         if (hexType = 13) or (hexType = 14) or (hexType = 15) then
      [*] = ;         begin
      [*] = ;            var tmpX, tmpY, tmpZ : Float;
      [*] = ;            GetTrackNodePositionByIndex(0, tmpX, tmpY, tmpZ);
      [*] = ;            z := tmpZ+4.5*(i div 8);
      [*] = ;
      [*] = ;            var xShift : Float = Sqrt(3) / 4 * gc_HexSize;
      [*] = ;
      [*] = ;            if (i div gc_battle_GridSize) mod 2 = 0 then
      [*] = ;            x := x + xShift
      [*] = ;            else
      [*] = ;            x := x - xShift;
      [*] = ;
      [*] = ;            if (hexType = 13) and (leftHexType = 14) then
      [*] = ;            leftCorner := true;
      [*] = ;
      [*] = ;            if (hexType = 13) and (rightHexType = 14) then
      [*] = ;            rightCorner := true;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pPatterns)-1 do
      [*] = ;         begin
      [*] = ;            var pPatternZone : Integer = ParserSelectByHandleByIndex(pPatterns, j);
      [*] = ;
      [*] = ;            var zoneType : Integer = ParserGetIntValueByKeyByHandle(pPatternZone, 'Type');
      [*] = ;            if hexType = zoneType then
      [*] = ;            begin
      [*] = ;               var pPatterns : Integer = ParserSelectByHandleByKey(pPatternZone, 'Patterns');
      [*] = ;               var sum : Float = 0;
      [*] = ;               var g : Integer;
      [*] = ;               for g := 0 to ParserGetCountByHandle(pPatterns)-1 do
      [*] = ;               begin
      [*] = ;                  var pPattern : Integer = ParserSelectByHandleByIndex(pPatterns, g);
      [*] = ;                  var pWorldRuleVisualFreqs : Integer = ParserSelectByHandleByKey(pPattern, 'WorldRuleVisualFreqs');
      [*] = ;                  var siegeLevelMin : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMin');
      [*] = ;                  var siegeLevelMax : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMax');
      [*] = ;                  if (siegeLevelMin=0) or (siegeLevel=0) or ((siegeLevel<>0) and (siegeLevel>=siegeLevelMin) and (siegeLevel<=siegeLevelMax)) then
      [*] = ;                  begin
      [*] = ;                     var k : Integer;
      [*] = ;                     for k:=0 to ParserGetCountByHandle(pWorldRuleVisualFreqs)-1 do
      [*] = ;                     begin
      [*] = ;                        var pWorldRuleVisualFreq : Integer = ParserSelectByHandleByIndex(pWorldRuleVisualFreqs, k);
      [*] = ;                        if (curVisualID=ParserGetIntValueByKeyByHandle(pWorldRuleVisualFreq, 'VisualID')) then
      [*] = ;                        begin
      [*] = ;                           var freq : Float = ParserGetFloatValueByKeyByHandle(pWorldRuleVisualFreq, 'Frequency');
      [*] = ;                           sum := sum + freq;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var ind : Float = RandomExt * sum;
      [*] = ;               sum := 0;
      [*] = ;
      [*] = ;               for g := 0 to ParserGetCountByHandle(pPatterns)-1 do
      [*] = ;               begin
      [*] = ;                  var pPattern : Integer = ParserSelectByHandleByIndex(pPatterns, g);
      [*] = ;                  var isWater : Boolean = false;
      [*] = ;                  isWater := ParserGetBoolValueByKeyByHandle(pPattern, 'Water');
      [*] = ;
      [*] = ;                  var pWorldRuleVisualFreqs : Integer = ParserSelectByHandleByKey(pPattern, 'WorldRuleVisualFreqs');
      [*] = ;                  var siegeLevelMin : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMin');
      [*] = ;                  var siegeLevelMax : Integer = ParserGetIntValueByKeyByHandle(pPattern, 'SiegeLevelMax');
      [*] = ;                  if (siegeLevelMin=0) or (siegeLevel=0) or ((siegeLevel<>0) and (siegeLevel>=siegeLevelMin) and (siegeLevel<=siegeLevelMax)) then
      [*] = ;                  begin
      [*] = ;                     var k : Integer;
      [*] = ;                     for k:=0 to ParserGetCountByHandle(pWorldRuleVisualFreqs)-1 do
      [*] = ;                     begin
      [*] = ;                        var pWorldRuleVisualFreq : Integer = ParserSelectByHandleByIndex(pWorldRuleVisualFreqs, k);
      [*] = ;                        if (curVisualID=ParserGetIntValueByKeyByHandle(pWorldRuleVisualFreq, 'VisualID')) then
      [*] = ;                        begin
      [*] = ;                           var freq : Float = ParserGetFloatValueByKeyByHandle(pWorldRuleVisualFreq, 'Frequency');
      [*] = ;                           sum := sum + freq;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if sum >= ind then
      [*] = ;                     begin
      [*] = ;                        var patName : String = ParserGetValueByKeyByHandle(pPattern, 'Name');
      [*] = ;                        var isRandRotate : Boolean = false;
      [*] = ;                        isRandRotate := ParserGetBoolValueByKeyByHandle(pPattern, 'RandRotate');
      [*] = ;
      [*] = ;                        var angle : Float = 0;
      [*] = ;                        if isRandRotate then angle := Floor(4*RandomExt) * 90;
      [*] = ;
      [*] = ;                        angle := angle / 180 * pi;
      [*] = ;                        // stand pattern
      [*] = ;                        StandPattern(patPlHandle, patName, x, z, angle);
      [*] = ;                        if isWater then
      [*] = ;                        var wfHandle : integer = WaterFieldAdd('battle', x - gc_HexSize*1, z - gc_HexSize*1, x + gc_HexSize*1, z + gc_HexSize*1, -0.85);
      [*] = ;
      [*] = ;                        var pLayers : Integer = ParserSelectByHandleByKey(pPattern, 'Layers');
      [*] = ;                        if ParserGetCountByHandle(pLayers)>0 then
      [*] = ;                        begin
      [*] = ;                           var indLayer : Integer = Floor(RandomExt*ParserGetCountByHandle(pLayers));
      [*] = ;                           patName := ParserGetValueByIndexByHandle(pLayers, indLayer);
      [*] = ;                           angle := 0;
      [*] = ;                           StandPattern(patPlHandle, patName, x, z, angle);
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        var leftPatternName : String = 'battle-siege-outpost-garbage-left';
      [*] = ;                        var rightPatternName : String = 'battle-siege-outpost-garbage-right';
      [*] = ;                        case siegeLevel of
      [*] = ;                           1 : begin
      [*] = ;                              leftPatternName := 'battle-siege-outpost-garbage-left';
      [*] = ;                              rightPatternName := 'battle-siege-outpost-garbage-right';
      [*] = ;                           end;
      [*] = ;                           2 : begin
      [*] = ;                              leftPatternName := 'battle-siege-fort-garbage-left';
      [*] = ;                              rightPatternName := 'battle-siege-fort-garbage-right';
      [*] = ;                           end;
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              leftPatternName := 'battle-siege-garbage-left';
      [*] = ;                              rightPatternName := 'battle-siege-garbage-right';
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                        if (leftCorner) then
      [*] = ;                        StandPattern(patPlHandle, leftPatternName, x, z, angle);
      [*] = ;                        if (rightCorner) then
      [*] = ;                        StandPattern(patPlHandle, rightPatternName, x, z, angle);
      [*] = ;
      [*] = ;                        if (leftCorner) then // (hexType=13)
      [*] = ;                        begin
      [*] = ;                           var leftHexPosZ : Float = ParserGetFloatValueByKeyByHandle(pLeftHexCell, 'CenterY');
      [*] = ;                           FadeObjectsInRadiusByBaseName(x, leftHexPosZ-2, 2.5, 'wall_crash_left', 0.3);
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if hexType = 14 then
      [*] = ;         begin
      [*] = ;            if ParserGetBoolValueByKeyByHandle(pHexCell, 'Tower') then
      [*] = ;            begin
      [*] = ;               var bnTower : String;
      [*] = ;               if (siegeLevel>0) and (siegeLevel<3) then
      [*] = ;               bnTower := 'fort_tower'
      [*] = ;               else
      [*] = ;               bnTower := 'tower';
      [*] = ;               var goHandle : Integer = CreatePlayerGameObjectHandleByHandle(patPlHandle, 'buildings', bnTower, posX, 0, posZ);
      [*] = ;               var ind : Integer = i - gc_battle_GridSize;
      [*] = ;
      [*] = ;               if ind >= 0 then
      [*] = ;               begin
      [*] = ;                  var pHexCell1 : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                  var hexType : Integer = ParserGetIntValueByKeyByHandle(pHexCell1, 'Type');
      [*] = ;                  if (hexType=13) then
      [*] = ;                  begin
      [*] = ;                     FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'tower', 0.5);
      [*] = ;                     FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'fort_tower', 0.5);
      [*] = ;                     FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'wall01', 0.99);
      [*] = ;                     FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'outpost_wall', 0.99);
      [*] = ;                     FadeObjectsInRadiusByBaseName(posX, posZ, 2.5, 'fort_wall', 0.99);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _obj_EnabledByFlag(gc_ObjectFlagBattleDecor) then
      [*] = ;FillBackgroundPatterns(gBoolRegister_BattleIsSiege, True, False);
      [*] = ;
      [*] = ;if (bSmoothTerrain) then
      [*] = ;MapGeneratorSmoothTiles;
      [*] = ;
      [*] = ;if _obj_EnabledByFlag(gc_ObjectFlagBattleDecor) then
      [*] = ;FillBackgroundPatterns(gBoolRegister_BattleIsSiege, True, True);
      [*] = ;
      [*] = ;if gBoolRegister_BattleIsSiege then
      [*] = ;begin
      [*] = ;   var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   var pTmp : Integer = _misc_ParserGetOrCreateByKey('bat_lp_tmp',true);
      [*] = ;   IntRegister0 := pTmp;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetTowersData');
      [*] = ;   var towerCount : Integer = IntRegister1;
      [*] = ;   var mTowerCount : Integer = IntRegister2;
      [*] = ;
      [*] = ;   for i := towerCount to towerCount+mTowerCount-1 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := i-towerCount;
      [*] = ;      ExecuteState('bat.GetMageTowerPosition');
      [*] = ;      var posX : Float = FloatRegister0;
      [*] = ;      var posY : Float = FloatRegister1;
      [*] = ;      var posZ : Float = FloatRegister2;
      [*] = ;
      [*] = ;      var pTower : Integer = ParserSelectByHandleByIndex(pTmp, i);
      [*] = ;      var towerType : Integer = ParserGetIntValueByKeyByHandle(pTower, 'Type');
      [*] = ;      var baseName : String = '';
      [*] = ;      var scale : Float = 1;
      [*] = ;      var rotate : Float = 0;
      [*] = ;      case towerType of
      [*] = ;         1 : begin
      [*] = ;            baseName := 'sorcererscircle2';
      [*] = ;            scale := 1.3449;
      [*] = ;            rotate := -50;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            baseName := 'library5';
      [*] = ;            scale := 1.4845;
      [*] = ;            rotate := -60;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            baseName := 'magetower2';
      [*] = ;            scale := 0.6412;
      [*] = ;            rotate := -40;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            baseName := 'magictower';
      [*] = ;            scale := 1.3785;
      [*] = ;            rotate := -230;
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            baseName := 'bf_magictower'; //must be 'lightningtower', but it is too low quality for large siege size.
      [*] = ;            scale := 0.5667;
      [*] = ;            rotate := -60;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            baseName := 'bf_magictower';
      [*] = ;            ErrorLog('unknown magic tower type = '+IntToStr(towerType));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var goHandle : Integer = CreatePlayerGameObjectHandleByHandle(patPlHandle, 'buildings', baseName, posX, 0, posZ);
      [*] = ;      SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;      GameObjectRollByHandle(goHandle, rotate);
      [*] = ;      ClearObjectsAround(goHandle, 2.5);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;TerrainUpdate(true, true);
      [*] = ;_misc_NormalizeWaterFieldByName('battle', 0.05, false, true);
      [*] = ;
      [*] = ;if (curVisualID=4) or (curVisualID=5) or (curVisualID=6) then
      [*] = ;begin
      [*] = ;   gBoolRegister_NeedSeasonChangeBattle := True;
      [*] = ;   ExecuteState('CreateSeasons');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

