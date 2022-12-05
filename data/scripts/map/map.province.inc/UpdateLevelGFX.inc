section.begin
   Name = UpdateLevelGFX
   Description : struct.begin
      [*] = ;update development level graphics
      [*] = ;IntRegister0 - phase ID (0-add objects to remove list, 1-add objects, 2-remove objects)
   struct.end
   Code : struct.begin
      [*] = ;var phase : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\UPDATELEVELGFX';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var i,n : Integer;
      [*] = ;
      [*] = ;var lo : String = ParserGetValueByKeyByHandle(pProvince, 'UpdateLevel');
      [*] = ;
      [*] = ;if (lo <> '') and (_sa_GetAsInt(lo, 0) <> 0) and (gProfile.provincescenery < gc_ProvincePopulationSceneryLimit) then
      [*] = ;begin
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var myPatPlName : String = ParserGetValueByKeyByHandle(pProvince, 'PatternPlayer');
      [*] = ;   var myPatPlHandle : Integer = GetPlayerHandleByName(myPatPlName); // prov.pattern
      [*] = ;   var patGroupName : String = 'group.prov.' + IntToStr(dummyUID);
      [*] = ;   var patGrHandle : Integer = GetPlayerGrHandleByHandle(myPatPlHandle, patGroupName);
      [*] = ;   if patGrHandle = 0 then
      [*] = ;      patGrHandle := CreateGroup(myPatPlName, patGroupName);
      [*] = ;
      [*] = ;   case phase of
      [*] = ;      0 : begin
      [*] = ;         if _log then _Log_map('Objects in group: '+IntToStr(GetGroupCountGameObjectsByHandle(patGrHandle)));
      [*] = ;         for i := 0 to GetGroupCountGameObjectsByHandle(patGrHandle)-1 do
      [*] = ;         begin
      [*] = ;            n := GetGroupGOHandleByGOIndexByHandle(patGrHandle, i);
      [*] = ;            if n <> 0 then
      [*] = ;               _sa_AddAsInt(lo,n);
      [*] = ;         end;
      [*] = ;         if _log then _Log_map('Removed UIDs[1]: '+lo);
      [*] = ;         ParserSetValueByKeyByHandle(pProvince, 'UpdateLevel', lo);
      [*] = ;         GroupClearGameObjectsByHandle(patGrHandle);
      [*] = ;      end;
      [*] = ;      1 : begin
      [*] = ;         var pRaceList,pRace,pPatternList,pPattern,oldGOCount,j : Integer;
      [*] = ;         var patName : String;
      [*] = ;         var raceID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;         IntRegister0 := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;         MapExecuteState('GetProvLevelParserByID');
      [*] = ;         pRaceList := ParserSelectByHandleByKey( IntRegister1, 'RaceList');
      [*] = ;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         FloatRegister0 := 0;
      [*] = ;         ExecuteState('HideShowObjects');
      [*] = ;
      [*] = ;         for i := 0 to ParserGetCountByHandle(pRaceList)-1 do
      [*] = ;         begin
      [*] = ;            pRace := ParserSelectByHandleByIndex(pRaceList, i);
      [*] = ;            if ParserGetIntValueByKeyByHandle(pRace,'RaceID') = raceID then
      [*] = ;            begin
      [*] = ;               pPatternList := ParserSelectByHandleByKey(pRace, 'PatternList');
      [*] = ;               var patternCount : Integer = ParserGetCountByHandle(pPatternList);
      [*] = ;               if patternCount > 0 then
      [*] = ;               begin
      [*] = ;                  pPattern := ParserSelectByHandleByIndex(pPatternList, Floor(Random * patternCount));
      [*] = ;                  patName := ParserGetValueByKeyByHandle(pPattern, 'PatternName');
      [*] = ;
      [*] = ;                  var pPruner : Integer = _obj_GetPrunerByStateName('ProvinceScenery', 'ProvinceScenery');
      [*] = ;                  var pPlayer : Integer = _obj_GetPlayerPruner(pPruner, myPatPlName);
      [*] = ;
      [*] = ;                  if _obj_PatternEnabled(patName, pPlayer, gProfile.provincescenery) then
      [*] = ;                  begin
      [*] = ;                     oldGOCount := GetPlayerGameObjectsCountByHandle(myPatPlHandle);
      [*] = ;                     StandPattern(myPatPlHandle, patName, ParserGetFloatValueByKeyByHandle(pProvince, 'CenterX'), ParserGetFloatValueByKeyByHandle(pProvince, 'CenterY'), 0);
      [*] = ;
      [*] = ;                     for j := 0 to gc_MaxPrunerObjects-1 do // get stored province pruning data so we get the universal frequencies
      [*] = ;                     begin
      [*] = ;                        gSceneryPruner[j].baseName := gProvinceSceneryPruner[j].baseName;
      [*] = ;                        gSceneryPruner[j].frequency := gProvinceSceneryPruner[j].frequency;
      [*] = ;                        gSceneryPruner[j].count := gProvinceSceneryPruner[j].count;
      [*] = ;                     end;
      [*] = ;                     _obj_PrunePlayer(pPlayer, gProfile.provincescenery, oldGOCount);
      [*] = ;                     for j := 0 to gc_MaxPrunerObjects-1 do
      [*] = ;                     begin
      [*] = ;                        gProvinceSceneryPruner[j].baseName := gSceneryPruner[j].baseName;
      [*] = ;                        gProvinceSceneryPruner[j].frequency := gSceneryPruner[j].frequency;
      [*] = ;                        gProvinceSceneryPruner[j].count := gSceneryPruner[j].count;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     for j := GetPlayerGameObjectsCountByHandle(myPatPlHandle)-1 downto oldGOCount do // get every new object just added in StandPattern
      [*] = ;                        GroupAddGameObjectByHandle(patGrHandle, GetGameObjectHandleByIndex(j, myPatPlHandle));
      [*] = ;                     if _log then _Log_valuesM('OBJ|GO', GetPlayerGameObjectsCountByHandle(myPatPlHandle), oldGOCount, 0,0,0,0);
      [*] = ;
      [*] = ;                     BoolRegister0 := False;
      [*] = ;                     FloatRegister0 := 0;
      [*] = ;                     ExecuteState('HideShowObjects');
      [*] = ;
      [*] = ;                     ParserSetValueByKeyByHandle(pProvince, 'PatternGroup', patGroupName);
      [*] = ;                     gBoolRegister_NeedSeasonChangeObjects := True;
      [*] = ;                  end;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         if _log then _Log_map('Removing objects: '+lo);
      [*] = ;         for i := (_sa_GetNum(lo)-1) downto 1 do
      [*] = ;         begin
      [*] = ;            //n := GetGameObjectHandleByUniqueId(_sa_GetAsInt(lo,i));
      [*] = ;            n := _sa_GetAsInt(lo,i);
      [*] = ;            _map_ProvDoFadeGameObject(n, GetGameObjectMyHandle(), 0, '', False, True);
      [*] = ;            SetGameObjectVisibleByHandle(n, false);
      [*] = ;            //GameObjectDestroyByHandle(n);
      [*] = ;         end;
      [*] = ;         ParserSetValueByKeyByHandle(pProvince, 'UpdateLevel', '');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
