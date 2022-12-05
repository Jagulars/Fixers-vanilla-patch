section.begin
   Name = bat.BackgroundScenery
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.BACKGROUNDSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = False;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'battle.pattern';
      [*] = ;const cRaceName = 'nature';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var uPlHandle : Integer = _plr_GetOrCreatePlayer(cPlayerName, cRaceName, cCMode, False);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   const cPatternFileName = '.\data\gen\backgroundpatterns.cfg';
      [*] = ;   var pPatternCovers : Integer = _misc_ParserGetOrCreateByKey('background_patterns', False);
      [*] = ;   if ParserGetCountByHandle(pPatternCovers) = 0 then
      [*] = ;      ParserLoadFromFile(cPatternFileName);
      [*] = ;   
      [*] = ;   var curVisualID : Integer = 0;
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;      curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;   
      [*] = ;   var bSmoothTerrain : Boolean = ParserGetBoolValueByKeyByHandle(pPatternCovers, 'SmoothTerrain');
      [*] = ;   
      [*] = ;   var curSiteID : Integer = 0;
      [*] = ;   var debugCurSiteID : Integer = ParserGetIntValueByKeyByHandle(pPatternCovers, 'DebugCurSiteID');
      [*] = ;   if (debugCurSiteID<>0) then
      [*] = ;      curSiteID := debugCurSiteID
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, _gv_GetCurrentPlayerHandle());
      [*] = ;      var action : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;      if (action=gc_UnitTaskExplore) or (action=gc_UnitTaskAttackSite) then
      [*] = ;      begin
      [*] = ;         var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;         IntRegister0 := curUID;
      [*] = ;         MapExecuteState('GetProvinceParserByUID');
      [*] = ;         var pProvince : Integer = IntRegister1;
      [*] = ;         var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;         curSiteID := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pProvSites, siteInd), 'SiteID');
      [*] = ;      end;
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
      [*] = ;   var pPruner : Integer = _obj_GetPrunerByStateName('BattleScenery', 'bat.BackgroundScenery');
      [*] = ;   var pPlayer : Integer = _obj_GetPlayerPruner(pPruner, cPlayerName);
      [*] = ;   
      [*] = ;   procedure HideObjectsInRadius(const posX, posZ, radius : Float);
      [*] = ;   begin
      [*] = ;      GetGameObjectsInRadius(posX, posZ, radius, false, true, uPlHandle, -1, 0, false, false, false, false, false, false);
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to GetGameObjectListCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(i);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         if (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<radius) then
      [*] = ;         AddObjectToDestroyList(goHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure HideObjectsInRectangle(const posX, posZ, sizeX, sizeY : Float);
      [*] = ;   begin
      [*] = ;      var radius : Float = Sqrt(Sqr(sizeX) + Sqr(sizeY));
      [*] = ;      GetGameObjectsInRadius(posX, posZ, radius, false, true, uPlHandle, -1, 0, false, false, false, false, false, false);
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to GetGameObjectListCount-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(i);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;         if ((goPosX)>posX) and ((goPosX)<(posX+sizeX)) and ((goPosZ)>posZ) and ((goPosZ)<(posZ+sizeY)) then
      [*] = ;            AddObjectToDestroyList(goHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure FillBackgroundPatterns(const bStandLast, bStandAfterSmooth : Boolean);
      [*] = ;   begin
      [*] = ;      var i, j, k, pPatternCover, pIgnoreOnSites, posX, posY : Integer;
      [*] = ;      var patternName : String;
      [*] = ;      var debug, unique, standLast, standAfterSmooth, bIgnore : Boolean;
      [*] = ;      
      [*] = ;      for i := 0 to ParserGetCountByHandle(pPatternCovers)-1 do
      [*] = ;      begin
      [*] = ;         pPatternCover := ParserSelectByHandleByIndex(pPatternCovers, i);
      [*] = ;   
      [*] = ;         patternName := ParserGetValueByKeyByHandle(pPatternCover, 'PatternName');
      [*] = ;      
      [*] = ;         if _obj_PatternEnabled(patternName, pPlayer, gProfile.battlescenery) then
      [*] = ;         begin
      [*] = ;            posX := ParserGetIntValueByKeyByHandle(pPatternCover, 'PosX');
      [*] = ;            posY := ParserGetIntValueByKeyByHandle(pPatternCover, 'PosY');
      [*] = ;            debug := ParserGetBoolValueByKeyByHandle(pPatternCover, 'Debug');
      [*] = ;            unique := ParserGetBoolValueByKeyByHandle(pPatternCover, 'Unique');
      [*] = ;            standLast := ParserGetBoolValueByKeyByHandle(pPatternCover, 'StandLast');
      [*] = ;            standAfterSmooth := ParserGetBoolValueByKeyByHandle(pPatternCover, 'StandAfterSmooth');
      [*] = ;   
      [*] = ;            pIgnoreOnSites := ParserSelectByHandleByKey(pPatternCover, 'IgnoreOnSites');
      [*] = ;            bIgnore := False;
      [*] = ;            if (pIgnoreOnSites<>0) then
      [*] = ;            begin
      [*] = ;               for j:=0 to ParserGetCountByHandle(pIgnoreOnSites)-1 do
      [*] = ;               begin
      [*] = ;                  var ignoreOnSite : Integer = ParserGetIntValueByIndexByHandle(pIgnoreOnSites, j);
      [*] = ;                  if (ignoreOnSite=curSiteID) then
      [*] = ;                  begin
      [*] = ;                     bIgnore := True;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            if (not bIgnore) and ((standLast=bStandLast) or bStandAfterSmooth) and (standAfterSmooth=bStandAfterSmooth) then
      [*] = ;            begin
      [*] = ;               if debug then
      [*] = ;               begin
      [*] = ;                  posX := posX+gIntRegister_dbgX;
      [*] = ;                  posY := posY+gIntRegister_dbgY;
      [*] = ;               end;
      [*] = ;   
      [*] = ;               if (unique) then
      [*] = ;               begin
      [*] = ;                  var pSites : Integer = ParserSelectByHandleByKey(pPatternCover, 'Sites');
      [*] = ;   
      [*] = ;                  for j:=0 to ParserGetCountByHandle(pSites)-1 do
      [*] = ;                  begin
      [*] = ;                     var site : Integer = ParserGetIntValueByIndexByHandle(pSites, j);
      [*] = ;                     if (site=curSiteID) then
      [*] = ;                     begin
      [*] = ;                        var pTerrainTypes : Integer = ParserSelectByHandleByKey(pPatternCover, 'TerrainTypes');
      [*] = ;                        
      [*] = ;                        for k:=0 to ParserGetCountByHandle(pTerrainTypes)-1 do
      [*] = ;                        begin
      [*] = ;                           var terrainType : Integer = ParserGetIntValueByIndexByHandle(pTerrainTypes, k);
      [*] = ;                           var sTerrainType : String = '';
      [*] = ;                           case terrainType of
      [*] = ;                              1 : sTerrainType := 'Plain';
      [*] = ;                              2 : sTerrainType := 'Forest';
      [*] = ;                              3 : sTerrainType := 'Hill';
      [*] = ;                              4 : sTerrainType := 'Swamp';
      [*] = ;                              5 : sTerrainType := 'Desert';
      [*] = ;                              6 : sTerrainType := 'DeadLand';
      [*] = ;                           end;
      [*] = ;   
      [*] = ;                           if (not SameText(rightTType, sTerrainType)) then
      [*] = ;                           begin
      [*] = ;                              bIgnore := True;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              bIgnore := False;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if (not bIgnore) then
      [*] = ;                        begin
      [*] = ;                           var pClearObjects : Integer = ParserSelectByHandleByKey(pPatternCover, 'ClearObjects');
      [*] = ;                           if (pClearObjects<>0) then
      [*] = ;                           begin
      [*] = ;                              for k:=0 to ParserGetCountByHandle(pClearObjects)-1 do
      [*] = ;                              begin
      [*] = ;                                 var pClearObject : Integer = ParserSelectByHandleByIndex(pClearObjects, k);
      [*] = ;                                 var sizeX : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'SizeX');
      [*] = ;                                 var sizeY : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'SizeY');
      [*] = ;                                 if (sizeX>0) and (sizeY>0) then
      [*] = ;                                 begin
      [*] = ;                                    var offX : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffX');
      [*] = ;                                    var offY : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffY');
      [*] = ;                                    var clearX : Float = floor(gFloatRegister_GridXCoord+gc_HexSize*4+posX)+offX;
      [*] = ;                                    var clearY : Float = floor(gFloatRegister_GridYCoord+gc_HexSize*4+posY)+offY;
      [*] = ;                                    HideObjectsInRectangle(clearX, clearY, sizeX, sizeY);
      [*] = ;                                 end;
      [*] = ;   
      [*] = ;                                 var radius : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'Radius');
      [*] = ;                                 if (radius>0) then
      [*] = ;                                 begin
      [*] = ;                                    var offX : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffX');
      [*] = ;                                    var offY : Float = ParserGetFloatValueByKeyByHandle(pClearObject, 'OffY');
      [*] = ;                                    var clearX : Float = floor(gFloatRegister_GridXCoord+gc_HexSize*4+posX)+offX;
      [*] = ;                                    var clearY : Float = floor(gFloatRegister_GridYCoord+gc_HexSize*4+posY)+offY;
      [*] = ;                                    HideObjectsInRadius(clearX, clearY, radius);
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;   
      [*] = ;                           StandPattern(uPlHandle, patternName, gFloatRegister_GridXCoord + gc_HexSize*4 + posX, gFloatRegister_GridYCoord + gc_HexSize*4 + posY, 0);
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (not bIgnore) then
      [*] = ;                  begin
      [*] = ;                     var pTerrainTypes : Integer = ParserSelectByHandleByKey(pPatternCover, 'TerrainTypes');
      [*] = ;                     var sideLeft : Boolean = ParserGetBoolValueByKeyByHandle(pPatternCover, 'SideLeft');
      [*] = ;                     var sideRight : Boolean = ParserGetBoolValueByKeyByHandle(pPatternCover, 'SideRight');
      [*] = ;                     
      [*] = ;                     for j:=0 to ParserGetCountByHandle(pTerrainTypes)-1 do
      [*] = ;                     begin
      [*] = ;                        var terrainType : Integer = ParserGetIntValueByIndexByHandle(pTerrainTypes, j);
      [*] = ;                        var sTerrainType : String = '';
      [*] = ;                        case terrainType of
      [*] = ;                           1 : sTerrainType := 'Plain';
      [*] = ;                           2 : sTerrainType := 'Forest';
      [*] = ;                           3 : sTerrainType := 'Hill';
      [*] = ;                           4 : sTerrainType := 'Swamp';
      [*] = ;                           5 : sTerrainType := 'Desert';
      [*] = ;                           6 : sTerrainType := 'DeadLand';
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if (sideLeft) then
      [*] = ;                        begin
      [*] = ;                           bIgnore := (not SameText(leftTType, sTerrainType));
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if (sideRight) then
      [*] = ;                        begin
      [*] = ;                           bIgnore := (not SameText(rightTType, sTerrainType));
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if (not bIgnore) then
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;   
      [*] = ;                     if (not bIgnore) then
      [*] = ;                     begin
      [*] = ;                        var pWorldRuleVisuals : Integer = ParserSelectByHandleByKey(pPatternCover, 'WorldRuleVisuals');
      [*] = ;                        if (pWorldRuleVisuals<>0) then
      [*] = ;                        begin
      [*] = ;                           var count : Integer = ParserGetCountByHandle(pWorldRuleVisuals);
      [*] = ;                           if (count>0) then
      [*] = ;                           begin
      [*] = ;                              bIgnore := True;
      [*] = ;                              for j:=0 to count-1 do
      [*] = ;                              begin
      [*] = ;                                 var visualID : Integer = ParserGetIntValueByIndexByHandle(pWorldRuleVisuals, j);
      [*] = ;                                 if (visualID=curVisualID) then
      [*] = ;                                 begin
      [*] = ;                                    bIgnore := False;
      [*] = ;                                    break;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;   
      [*] = ;                     if (not bIgnore) and (not gBoolRegister_BattleIsSiege) or (gBoolRegister_BattleIsSiege and ParserGetBoolValueByKeyByHandle(pPatternCover, 'UseOnSiege')) then
      [*] = ;                        StandPattern(uPlHandle, patternName, gFloatRegister_GridXCoord + gc_HexSize*4 + posX, gFloatRegister_GridYCoord + gc_HexSize*4 + posY, 0);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            //log('x = ' + IntToStr(posX) + '; y = ' + IntToStr(posY) + '; patName = ' + patternName);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   FillBackgroundPatterns(False, False);
      [*] = ;
      [*] = ;   var siegeLevel : Integer = 0;
      [*] = ;   if (gBoolRegister_BattleIsSiege) then
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;      var bCastle : Boolean =  ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;      var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;      var pGarrisonSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;      
      [*] = ;      if (bCastle) then
      [*] = ;         siegeLevel := 5
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i := 3 downto 0 do
      [*] = ;         begin
      [*] = ;            var pGarrisonSlot : Integer = ParserSelectByHandleByIndex(pGarrisonSlots, i);
      [*] = ;            var count : Integer = ParserGetIntValueByKeyByHandle(pGarrisonSlot, 'Count');
      [*] = ;            if (count>0) then
      [*] = ;            begin
      [*] = ;               siegeLevel := i+1;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      StandPattern(uPlHandle, 'battle-siege-ground-6', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;      case siegeLevel of
      [*] = ;         1 : StandPattern(uPlHandle, 'battle-siege-outpost-ground-6-onlywalls', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;         2 : StandPattern(uPlHandle, 'battle-siege-fort-ground-6-onlywalls', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;         else StandPattern(uPlHandle, 'battle-siege-ground-6-onlywalls', gFloatRegister_GridXCoord + gc_HexSize*4+27, gFloatRegister_GridYCoord + gc_HexSize*8-10, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   FillBackgroundPatterns(True, False);
      [*] = ;
      [*] = ;   if (bSmoothTerrain) then
      [*] = ;      MapGeneratorSmoothTiles;
      [*] = ;
      [*] = ;   FillBackgroundPatterns(True, True);
      [*] = ;
      [*] = ;   //TerrainUpdate(true, true); // this in bat.FieldScenery, son't know what it does though.
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then Clear();
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;sTrace := _log_name;
      [*] = ;if (runFlags and 2) > 0 then sTrace := sTrace + '['+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle))+']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace, $1000000 or _log_trace);
   struct.end
section.end

