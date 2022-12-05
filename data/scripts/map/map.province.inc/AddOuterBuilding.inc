section.begin
   Name = AddOuterBuilding
   Description : struct.begin
      [*] = ;IntRegister0 - outer building ID
      [*] = ;IntRegister1 - slot index
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\ADDOUTERBUILDING';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;var buildID : Integer = IntRegister0;
      [*] = ;var slotInd : Integer = IntRegister1;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[ProvUID: '+IntToStr(GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle))+', Build ID: '+IntToStr(buildID)+', Slot Index: '+IntToStr(slotInd)+']',_log_trace);
      [*] = ;
      [*] = ;if (slotInd >= 0) and (slotInd <= 2) then
      [*] = ;begin
      [*] = ;   var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;   var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;   var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, slotInd);
      [*] = ;
      [*] = ;   var pOuterBuilding : Integer = ParserSelectByHandleByIndex(gPrototypeData.outerBuildings.handle, buildID);
      [*] = ;   var pBuildAbilities : Integer = ParserSelectByHandleByKey(pOuterBuilding, 'Abilities');
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   var updateFog : Boolean = false;
      [*] = ;   var stable : Boolean = false;
      [*] = ;   var updGarrison : Boolean = true;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pBuildAbilities)-1 do
      [*] = ;   begin
      [*] = ;      var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, i);
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;      var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;      case abilityID of
      [*] = ;         2 : stable := true;
      [*] = ;         4 : begin
      [*] = ;            // open garrison slots
      [*] = ;            var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;            var pGarrisonSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;            var pGarrisonSlot : Integer = ParserSelectByHandleByIndex(pGarrisonSlots, param1-1);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGarrisonSlot, 'Count', param2);
      [*] = ;
      [*] = ;            updGarrison := false;
      [*] = ;         end;
      [*] = ;         11 : updateFog := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID')>0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := slotInd;
      [*] = ;      BoolRegister0 := updGarrison;
      [*] = ;      ExecuteState('RazeBuilding');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;   var provPlInd : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;
      [*] = ;   // change wall strength
      [*] = ;   var buildWall : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Wall');
      [*] = ;   if buildWall > 0 then
      [*] = ;   begin
      [*] = ;      var fort : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Fort');
      [*] = ;      ExecuteState('GetMaxFortValue');
      [*] = ;      var maxFort : Integer = IntRegister0;
      [*] = ;
      [*] = ;      var r : Float;
      [*] = ;      if maxFort > 0 then
      [*] = ;         r := fort / maxFort
      [*] = ;      else
      [*] = ;         r := 1;
      [*] = ;
      [*] = ;      maxFort := buildWall;
      [*] = ;      fort := Floor(maxFort * r);
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'Fort', fort);
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID', buildID);
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pBuildAbilities)-1 do
      [*] = ;   begin
      [*] = ;      var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, i);
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;      var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;      case abilityID of
      [*] = ;         2 : stable := true;
      [*] = ;         4 : begin
      [*] = ;            // open garrison slots
      [*] = ;            var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;            var pGarrisonSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;            var pGarrisonSlot : Integer = ParserSelectByHandleByIndex(pGarrisonSlots, param1-1);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGarrisonSlot, 'Count', param2);
      [*] = ;         end;
      [*] = ;         11 : updateFog := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var port : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Port');
      [*] = ;   if (port > 0) or stable then
      [*] = ;   begin
      [*] = ;      updateFog := true;
      [*] = ;      if gIntRegister_MapSelectedUID <> 0 then
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'UpdatePath');
      [*] = ;         gBoolRegister_GUIUpdateMapDrawPath := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ExecuteState('GetStable');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'Stable', IntRegister0);
      [*] = ;      
      [*] = ;      if stable and _obj_CreationStateEnabled('Roads') then
      [*] = ;         ExecuteState('CreateRoad');
      [*] = ;   end;
      [*] = ;
      [*] = ;   // create game object
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   IntRegister1 := slotInd;
      [*] = ;   BoolRegister0 := True;
      [*] = ;   ExecuteState('CreateOuterBuildModel');
      [*] = ;
      [*] = ;   if updateFog then
      [*] = ;   begin
      [*] = ;      if provPlInd = gIntRegister_MapMyPlayerIndex then
      [*] = ;         MapExecuteState('map.DoShowFog')
      [*] = ;      else
      [*] = ;         PlayerExecuteStateByHandle(provPlHandle, 'CalcFogMap');
      [*] = ;      gBoolRegister_GUIUpdateMapHexGrid := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gMapEditor.enabled) then
      [*] = ;   begin
      [*] = ;      gMapEditor.grid[ParserGetIntValueByKeyByHandle(pProvince, 'Index')].outerbuild[slotInd] := buildID;
      [*] = ;      //_editor_UpdateGridOuterBuildings(gMapEditor.grid[ind]);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

