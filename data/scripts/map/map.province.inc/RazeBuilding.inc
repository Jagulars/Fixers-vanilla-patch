section.begin
   Name = RazeBuilding
   Description : struct.begin
      [*] = ;IntRegister0 - slot index
      [*] = ;BoolRegister0 - update garrison info
   struct.end
   Code : struct.begin
      [*] = ;var index : Integer = IntRegister0;
      [*] = ;var updGarrison : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\RAZEBUILDING';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;if index >= 0 then
      [*] = ;begin
      [*] = ;   var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, index);
      [*] = ;   var outerBuildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;   var pOuterBuilding : Integer = ParserSelectByHandleByIndex(gPrototypeData.outerBuildings.handle, outerBuildID);
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID', 0);
      [*] = ;
      [*] = ;   ExecuteState('IsGarrison');
      [*] = ;   if (not BoolRegister0) and updGarrison then
      [*] = ;   begin
      [*] = ;      var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;      ParserClearByHandle(ParserSelectByHandleByKey(pProvGarrison, 'Units'));
      [*] = ;
      [*] = ;      var pGarrSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;      for i := ParserGetCountByHandle(pGarrSlots)-1 downto 0 do
      [*] = ;         ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGarrSlots, i), 'Count', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // change wall strength
      [*] = ;   var buildWall : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Wall');
      [*] = ;   if buildWall > 0 then
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'Fort', ParserGetIntValueByKeyByHandle(pProvince, 'Fort')- buildWall);
      [*] = ;
      [*] = ;   if plHandle <> 0 then
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma)-ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Karma'));
      [*] = ;
      [*] = ;   // destroy object
      [*] = ;   if (gProfile.provincescenery < gc_OuterBuildSceneryLimit) then
      [*] = ;   begin
      [*] = ;      var patPlName : String = 'pattern';
      [*] = ;      var patPlHandle : Integer = GetPlayerHandleByName(patPlName);
      [*] = ;      var posX : Float = ParserGetFloatValueByKeyByHandle(pProvOuterBuilding, 'X');
      [*] = ;      var posZ : Float = ParserGetFloatValueByKeyByHandle(pProvOuterBuilding, 'Y');
      [*] = ;      var plName : String = ParserGetValueByKeyByHandle(pProvOuterBuilding, 'PatternPlayer');
      [*] = ;      var grName : String = ParserGetValueByKeyByHandle(pProvOuterBuilding, 'PatternGroup');
      [*] = ;      var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;      var grHandle : Integer = GetPlayerGrHandleByHandle(plHandle, grName);
      [*] = ;      if (grHandle=0) then
      [*] = ;         grHandle := CreateGroupByPlHandle(plHandle, grName);
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      for i := GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, i);
      [*] = ;
      [*] = ;         if gBoolRegister_MapTurnFinished then
      [*] = ;            _map_ProvDoFadeGameObject(goHandle, 0, 1, '', False, True)
      [*] = ;         else
      [*] = ;            AddObjectToDestroyList(goHandle);
      [*] = ;      end;
      [*] = ;      GroupClearGameObjectsByHandle(grHandle);
      [*] = ;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      FloatRegister0 := 1;
      [*] = ;      ExecuteState('HideShowObjects');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pBuildAbilities : Integer = ParserSelectByHandleByKey(pOuterBuilding, 'Abilities');
      [*] = ;   var calcFog : Boolean = false;
      [*] = ;   var stable : Boolean = false;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pBuildAbilities)-1 do
      [*] = ;   begin
      [*] = ;      var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, i);
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;      //var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;      //var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;      case abilityID of
      [*] = ;         2 : stable := true;
      [*] = ;         11 : calcFog := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Port') > 0) or stable then
      [*] = ;   begin
      [*] = ;      calcFog := true;
      [*] = ;      i := gIntRegister_MapSelectedUID;
      [*] = ;      if i <> 0 then
      [*] = ;         i := GetGameObjectHandleByUniqueId(i);
      [*] = ;      if i<> 0 then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(i, 'UpdatePath');
      [*] = ;         gBoolRegister_GUIUpdateMapDrawPath := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ExecuteState('GetStable');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'Stable', IntRegister0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if calcFog then
      [*] = ;   begin
      [*] = ;      if plIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;         MapExecuteState('map.DoShowFog')
      [*] = ;      else
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'CalcFogMap');
      [*] = ;      gBoolRegister_GUIUpdateMapHexGrid := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gMapEditor.enabled) then
      [*] = ;   begin
      [*] = ;      gMapEditor.grid[ParserGetIntValueByKeyByHandle(pProvince, 'Index')].outerbuild[index] := 0;
      [*] = ;      //_editor_UpdateGridOuterBuildings(gMapEditor.grid[ind]);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

