section.begin
   Name = ChooseInnerBuild
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CHOOSEINNERBUILD';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pPlProvince : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pPlProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var pInnerBuildings : Integer = gPrototypeData.innerBuildings.handle;
      [*] = ;var pSpells : Integer = gPrototypeData.spells.handle;
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;var pResources : Integer = gPrototypeData.resources.handle;
      [*] = ;
      [*] = ;var i, j, k, l : Integer;
      [*] = ;
      [*] = ;var goHandle : Integer = 0;
      [*] = ;if GetPlayerGameObjectsCountByHandle(myPlHandle) > 0 then
      [*] = ;goHandle := GetGameObjectHandleByIndex(0, myPlHandle);
      [*] = ;
      [*] = ;var class1 : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;var count : Integer = 0;
      [*] = ;
      [*] = ;procedure MakeBuildTaste(buildID, taste, parserTastes : Integer);
      [*] = ;begin
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   IntRegister1 := taste;
      [*] = ;   IntRegister2 := parserTastes;
      [*] = ;   ExecuteState('MakeBuildTaste');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddBuild(buildID : Integer);
      [*] = ;begin
      [*] = ;   gArrRollerN[count] := buildID;
      [*] = ;   gArrRollerP[count] := 1;
      [*] = ;   count := count + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;var profile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var karma : Integer = 0;
      [*] = ;if profile > 0 then
      [*] = ;begin
      [*] = ;   var pPlayer : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;   karma := ParserGetIntValueByKeyByHandle(pPlayer, 'Karma');
      [*] = ;end;
      [*] = ;
      [*] = ;// build in first turns
      [*] = ;case gGame.currentTurn of
      [*] = ;   2 : begin
      [*] = ;      case class1 of
      [*] = ;         1 : begin
      [*] = ;            IntRegister0 := 2; // forge
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 2;
      [*] = ;               ExecuteState('BuyInnerBuild');
      [*] = ;               _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            IntRegister0 := 1; // workshop
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 1;
      [*] = ;               ExecuteState('BuyInnerBuild');
      [*] = ;               _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := 3; // library
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 3;
      [*] = ;               ExecuteState('BuyInnerBuild');
      [*] = ;               _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   3 : begin
      [*] = ;      _rand_ClearRoll;
      [*] = ;      case class1 of
      [*] = ;         1 : begin
      [*] = ;            if karma < 0 then
      [*] = ;            begin
      [*] = ;               AddBuild(16); // thieves
      [*] = ;               AddBuild(17); // brigands
      [*] = ;               AddBuild(8); // slingers
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if karma > 0 then
      [*] = ;            begin
      [*] = ;               AddBuild(9); // spearmen
      [*] = ;               AddBuild(8);
      [*] = ;               //AddBuild(14);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               AddBuild(16);
      [*] = ;               AddBuild(17);
      [*] = ;               AddBuild(8);
      [*] = ;               AddBuild(9); 
      [*] = ;               //AddBuild(14);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         2, 4 : begin
      [*] = ;            if karma < 0 then
      [*] = ;            begin
      [*] = ;               AddBuild(17);
      [*] = ;               AddBuild(9);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if karma > 0 then
      [*] = ;            begin
      [*] = ;               AddBuild(9);
      [*] = ;               AddBuild(12); // pikemen
      [*] = ;               AddBuild(11); // swordsmen
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               AddBuild(9);
      [*] = ;               AddBuild(17);
      [*] = ;               AddBuild(12);
      [*] = ;               AddBuild(11);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            //Злой - воры, разбойники
      [*] = ;            //Добрый - копейщики, мечники
      [*] = ;
      [*] = ;            if karma < 0 then
      [*] = ;            begin
      [*] = ;               AddBuild(16);
      [*] = ;               AddBuild(17);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if karma > 0 then
      [*] = ;            begin
      [*] = ;               AddBuild(9);
      [*] = ;               AddBuild(11);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               AddBuild(16);
      [*] = ;               AddBuild(17);
      [*] = ;               AddBuild(9);
      [*] = ;               AddBuild(11);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var buildID : Integer = _rand_Roll(false);
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      ExecuteState('IsBuildingAvailable');
      [*] = ;      var available : Boolean = BoolRegister0;
      [*] = ;      var fullGroup : Boolean = not BoolRegister1;
      [*] = ;      var isBuilt : Boolean = BoolRegister2;
      [*] = ;      var everBuildable : Boolean = BoolRegister3;
      [*] = ;
      [*] = ;      if (not isBuilt) and (not fullGroup) then
      [*] = ;      begin
      [*] = ;         if available then
      [*] = ;         begin
      [*] = ;            IntRegister0 := buildID;
      [*] = ;            ExecuteState('BuyInnerBuild');
      [*] = ;            _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;            exit;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := buildID;
      [*] = ;            ExecuteState('GetRequiredBuilding');
      [*] = ;            var reqID : Integer = IntRegister1;
      [*] = ;            var allBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            if reqID > 0 then
      [*] = ;            begin
      [*] = ;               SetIntValueByIndex(gc_map_PLStack_MapUnit_iPlanned, buildID);
      [*] = ;               IntRegister0 := reqID;
      [*] = ;               ExecuteState('BuyInnerBuild');
      [*] = ;               _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var planID : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iPlanned);
      [*] = ;if planID > 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := planID;
      [*] = ;   ExecuteState('GetRequiredBuilding');
      [*] = ;   var reqID : Integer = IntRegister1;
      [*] = ;   var allBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if allBuilt then
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iPlanned, 0);
      [*] = ;
      [*] = ;      IntRegister0 := planID;
      [*] = ;      ExecuteState('BuyInnerBuild');
      [*] = ;      _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;      exit;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if reqID > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := reqID;
      [*] = ;         ExecuteState('BuyInnerBuild');
      [*] = ;         var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;         if not isBuilt then
      [*] = ;           SetIntValueByIndex(gc_map_PLStack_MapUnit_iPlanned, 0)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         SetIntValueByIndex(gc_map_PLStack_MapUnit_iPlanned, 0)
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// init buildings tastes array
      [*] = ;var pBuildTastes : Integer = _misc_ParserGetOrCreateByKey('cib_BuildTastes',true);
      [*] = ;for i := 0 to ParserGetCountByHandle(pInnerBuildings)-1 do
      [*] = ;begin
      [*] = ;   var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;   var buildID : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'BuildingID');
      [*] = ;
      [*] = ;   var pBuildTaste : Integer = ParserAddChildByIndex(pBuildTastes, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pBuildTaste, 'BuildID', buildID);
      [*] = ;   ParserSetIntValueByKeyByHandle(pBuildTaste, 'Taste', 1);
      [*] = ;end;
      [*] = ;
      [*] = ;// unit buildings
      [*] = ;var pLevelsInfo : Integer = _misc_ParserGetOrCreateByKey('cib_LevelsInfo',true);
      [*] = ;for i := 0 to 4 do
      [*] = ;begin
      [*] = ;   var pLevelInfo : Integer = ParserAddChildByIndex(pLevelsInfo, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pLevelInfo, 'SlotCount', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pLevelInfo, 'HeroCount', 0);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pLevelInfo, 'IsBuilt', false);
      [*] = ;   ParserAddChildByIndex(pLevelInfo, 'Buildings');
      [*] = ;end;
      [*] = ;
      [*] = ;// calculate hero slots count
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   for j := 1 to 4 do
      [*] = ;   begin
      [*] = ;      var pLevelInfo : Integer = ParserSelectByHandleByIndex(pLevelsInfo, j);
      [*] = ;      IntRegister0 := j;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle,'GetUnitSlots');
      [*] = ;
      [*] = ;      if IntRegister1 > 0 then
      [*] = ;      begin
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pLevelInfo, 'SlotCount');
      [*] = ;         value := value + IntRegister1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pLevelInfo, 'SlotCount', value);
      [*] = ;
      [*] = ;         var heroCount : Integer = ParserGetIntValueByKeyByHandle(pLevelInfo, 'HeroCount');
      [*] = ;         ParserSetIntValueByKeyByHandle(pLevelInfo, 'HeroCount', heroCount+1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// unit buildings tastes
      [*] = ;for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;   var buildID : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'BuildingID');
      [*] = ;   var buildGroup : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Group');
      [*] = ;   var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;   var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   var fullGroup : Boolean = false;
      [*] = ;   if buildGroup > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := buildGroup;
      [*] = ;      ExecuteState('IsFullBuildGroup');
      [*] = ;      fullGroup := BoolRegister0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;
      [*] = ;      if abilID = 8 then
      [*] = ;      begin
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;         var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;         var pLevelInfo : Integer = ParserSelectByHandleByIndex(pLevelsInfo, rank);
      [*] = ;
      [*] = ;         if fullGroup then
      [*] = ;         ParserSetBoolValueByKeyByHandle(pLevelInfo, 'IsBuilt', true)
      [*] = ;         else
      [*] = ;         if not isBuilt then
      [*] = ;         begin
      [*] = ;            var pLevelBuildings : Integer = ParserSelectByHandleByKey(pLevelInfo, 'Buildings');
      [*] = ;            var pLevelBuilding : Integer = ParserAddChildByIndex(pLevelBuildings, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pLevelBuilding, 'BuildingID', buildID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pLevelBuilding, 'UnitID', unitID);
      [*] = ;         end;
      [*] = ;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 1 to 4 do
      [*] = ;begin
      [*] = ;   var pLevelInfo : Integer = ParserSelectByHandleByIndex(pLevelsInfo, i);
      [*] = ;   var isBuilt : Boolean = ParserGetBoolValueByKeyByHandle(pLevelInfo, 'IsBuilt');
      [*] = ;   var heroCount : Integer = ParserGetIntValueByKeyByHandle(pLevelInfo, 'HeroCount');
      [*] = ;
      [*] = ;   var taste : Integer = ParserGetIntValueByKeyByHandle(pLevelInfo, 'SlotCount');
      [*] = ;   if not isBuilt then
      [*] = ;   taste := taste * 5;
      [*] = ;
      [*] = ;   var pLevelBuildings : Integer = ParserSelectByHandleByKey(pLevelInfo, 'Buildings');
      [*] = ;   for j := ParserGetCountByHandle(pLevelBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pLevelBuilding : Integer = ParserSelectByHandleByIndex(pLevelBuildings, j);
      [*] = ;      var buildID : Integer = ParserGetIntValueByKeyByHandle(pLevelBuilding, 'BuildingID');
      [*] = ;      var unitID : Integer = ParserGetIntValueByKeyByHandle(pLevelBuilding, 'UnitID');
      [*] = ;
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;      var unitKarma : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Karma');
      [*] = ;
      [*] = ;      IntRegister0 := unitID;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetUnitPowerByID', 0);
      [*] = ;      var power : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var taste1 : Integer = taste + power * heroCount;
      [*] = ;      if unitID < 3 then
      [*] = ;      taste1 := taste1 div 2;
      [*] = ;
      [*] = ;      var pPlayer : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;
      [*] = ;      var plKarma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;      if pPlayer <> 0 then
      [*] = ;      plKarma := ParserGetIntValueByKeyByHandle(pPlayer, 'Karma');
      [*] = ;
      [*] = ;      if (plKarma <> 0) and (unitKarma <> 0) then
      [*] = ;      begin
      [*] = ;         if plKarma * unitKarma > 0 then
      [*] = ;         taste1 := taste1 * 2
      [*] = ;         else
      [*] = ;         taste1 := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      MakeBuildTaste(buildID, taste1, pBuildTastes);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// spell buildings
      [*] = ;ParserClearByHandle(pLevelsInfo);
      [*] = ;for i := 0 to 4 do
      [*] = ;begin
      [*] = ;   var pLevelInfo : Integer = ParserAddChildByIndex(pLevelsInfo, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pLevelInfo, 'SlotCount', 0);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pLevelInfo, 'IsBuilt', false);
      [*] = ;   ParserAddChildByIndex(pLevelInfo, 'Heroes');
      [*] = ;   ParserAddChildByIndex(pLevelInfo, 'Buildings');
      [*] = ;end;
      [*] = ;
      [*] = ;// calculate hero slots count
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   var goUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   for j := 1 to 4 do
      [*] = ;   begin
      [*] = ;      var pLevelInfo : Integer = ParserSelectByHandleByIndex(pLevelsInfo, j);
      [*] = ;      IntRegister0 := j;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle 'GetSpellSlots');
      [*] = ;
      [*] = ;      if IntRegister1 > 0 then
      [*] = ;      begin
      [*] = ;         var value : Integer = ParserGetIntValueByKeyByHandle(pLevelInfo, 'SlotCount');
      [*] = ;         value := value + IntRegister1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pLevelInfo, 'SlotCount', value);
      [*] = ;
      [*] = ;         var pLevelHeroes : Integer = ParserSelectByHandleByKey(pLevelInfo, 'Heroes');
      [*] = ;         var pLevelHero : Integer = ParserAddChildByIndex(pLevelHeroes, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pLevelHero, 'UID', goUID);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// spell buildings tastes
      [*] = ;for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;   var buildID : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'BuildingID');
      [*] = ;   var buildGroup : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Group');
      [*] = ;   var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;   var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   var fullGroup : Boolean = false;
      [*] = ;   if buildGroup > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := buildGroup;
      [*] = ;      ExecuteState('IsFullBuildGroup');
      [*] = ;      fullGroup := BoolRegister0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for j := ParserGetCountByHandle(pSpells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pSpell : Integer = ParserSelectByHandleByIndex(pSpells, j);
      [*] = ;      var spellID : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'SpellID');
      [*] = ;      var spBuildID : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'BuildingID');
      [*] = ;      var spLevel : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Level');
      [*] = ;
      [*] = ;      if (spBuildID = buildID) and (spLevel > 0) and (spellID > 0) then
      [*] = ;      begin
      [*] = ;         var pLevelInfo : Integer = ParserSelectByHandleByIndex(pLevelsInfo, spLevel);
      [*] = ;         var pLevelBuildings : Integer = ParserSelectByHandleByKey(pLevelInfo, 'Buildings');
      [*] = ;
      [*] = ;         var inList : Boolean = false;
      [*] = ;         var pLevelBuilding : Integer;
      [*] = ;         for k := ParserGetCountByHandle(pLevelBuildings)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            pLevelBuilding := ParserSelectByHandleByIndex(pLevelBuildings, k);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pLevelBuilding, 'BuildingID');
      [*] = ;
      [*] = ;            if id = buildID then
      [*] = ;            begin
      [*] = ;               inList := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pLevelSpells : Integer;
      [*] = ;         if not inList then
      [*] = ;         begin
      [*] = ;            if isBuilt or fullGroup then
      [*] = ;            ParserSetBoolValueByKeyByHandle(pLevelInfo, 'IsBuilt', true)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               pLevelBuilding := ParserAddChildByIndex(pLevelBuildings, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pLevelBuilding, 'BuildingID', buildID);
      [*] = ;               pLevelSpells := ParserAddChildByIndex(pLevelBuilding, 'Spells');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         pLevelSpells := ParserSelectByHandleByKey(pLevelBuilding, 'Spells');
      [*] = ;
      [*] = ;         var pLevelSpell : Integer = ParserAddChildByIndex(pLevelSpells, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pLevelSpell, 'SpellID', spellID);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 1 to 4 do
      [*] = ;begin
      [*] = ;   var pLevelInfo : Integer = ParserSelectByHandleByIndex(pLevelsInfo, i);
      [*] = ;   var isBuilt : Boolean = ParserGetBoolValueByKeyByHandle(pLevelInfo, 'IsBuilt');
      [*] = ;
      [*] = ;   var taste : Integer = 2 * ParserGetIntValueByKeyByHandle(pLevelInfo, 'SlotCount');
      [*] = ;   if not isBuilt then
      [*] = ;   taste := taste * 4;
      [*] = ;
      [*] = ;   var pLevelBuildings : Integer = ParserSelectByHandleByKey(pLevelInfo, 'Buildings');
      [*] = ;   for j := ParserGetCountByHandle(pLevelBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pLevelBuilding : Integer = ParserSelectByHandleByIndex(pLevelBuildings, j);
      [*] = ;      var buildID : Integer = ParserGetIntValueByKeyByHandle(pLevelBuilding, 'BuildingID');
      [*] = ;      var pBuildSpells : Integer = ParserSelectByHandleByKey(pLevelBuilding, 'Spells');
      [*] = ;
      [*] = ;      var taste1 : Integer = 0;
      [*] = ;      for k := ParserGetCountByHandle(pBuildSpells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pBuildSpell : Integer = ParserSelectByHandleByIndex(pBuildSpells, k);
      [*] = ;         var spellID : Integer = ParserGetIntValueByKeyByHandle(pBuildSpell, 'SpellID');
      [*] = ;
      [*] = ;         var pLevelHeroes : Integer = ParserSelectByHandleByKey(pLevelInfo, 'Heroes');
      [*] = ;         for l := ParserGetCountByHandle(pLevelHeroes)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pLevelHero : Integer = ParserSelectByHandleByIndex(pLevelHeroes, l);
      [*] = ;            var goUID : Integer = ParserGetIntValueByKeyByHandle(pLevelHero, 'UID');
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetSpellTaste');
      [*] = ;            taste1 := taste1 + IntRegister1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if taste1 > 0 then
      [*] = ;      MakeBuildTaste(buildID, taste + taste1, pBuildTastes);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;TimeLog('Item buildings start');
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   var class1 : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var pGODoll : Integer = ParserSelectByHandleByKey(pGOParser, 'Doll');
      [*] = ;
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   for j := 0 to gc_HeroDollSlotsCount-1 do
      [*] = ;   begin
      [*] = ;      var pDollSlot : Integer = ParserSelectByHandleByIndex(pGODoll, j);
      [*] = ;      var dollSlot : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemSlot');
      [*] = ;      var dollItemID : Integer = ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemID');
      [*] = ;
      [*] = ;      ArrayClear;
      [*] = ;
      [*] = ;      for k := ParserGetCountByHandle(pItems)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pItem : Integer = ParserSelectByHandleByIndex(pItems, k);
      [*] = ;         var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;         var buildID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'BuildingID');
      [*] = ;         var itemSlot : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;
      [*] = ;         if (dollSlot = itemSlot) and (buildID > 0) and (ArrayGetIndexByValue(buildID) = -1) then
      [*] = ;         begin
      [*] = ;            var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, buildID);
      [*] = ;            var buildGroup : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Group');
      [*] = ;
      [*] = ;            IntRegister0 := buildID;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;            var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            var fullGroup : Boolean = false;
      [*] = ;            if (buildGroup > 0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := buildGroup;
      [*] = ;               ExecuteState('IsFullBuildGroup');
      [*] = ;               fullGroup := BoolRegister0;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (not fullGroup) and (not isBuilt) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := itemID;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;               var canUse : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;               if canUse then
      [*] = ;               begin
      [*] = ;                  var f : Boolean = true;
      [*] = ;                  if dollItemID > 0 then
      [*] = ;                  begin
      [*] = ;                     var pDollItem : Integer = ParserSelectByHandleByIndex(pItems, dollItemID);
      [*] = ;                     var dollShopLevel : Integer = ParserGetIntValueByKeyByHandle(pDollItem, 'ShopLevel');
      [*] = ;
      [*] = ;                     var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;
      [*] = ;                     if dollShopLevel >= shopLevel then
      [*] = ;                     f := false;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if f then
      [*] = ;                  ArrayPushValue(buildID);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _misc_AntiFreeze;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for k := ArrayGetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var buildID : Integer = ArrayGetValueByIndex(k);
      [*] = ;         var taste : Integer;
      [*] = ;
      [*] = ;         if dollItemID = 0 then
      [*] = ;         taste := 5
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := dollItemID;
      [*] = ;            StateMachineExecuteState(initMachine, 'GetItemParserByID', 0);
      [*] = ;            var pItem : Integer = IntRegister1;
      [*] = ;
      [*] = ;            var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;            taste := 5 - shopLevel;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (dollSlot < 9) and (class1 = 1) then
      [*] = ;         taste := taste * 2;
      [*] = ;
      [*] = ;         MakeBuildTaste(buildID, taste, pBuildTastes);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;TimeLog('Item buildings end');
      [*] = ;
      [*] = ;// defender buildings
      [*] = ;// get max defender power
      [*] = ;var pCastleDefenders : Integer = ParserSelectByHandleByKey(pPlProvince, 'Defenders');
      [*] = ;var maxPower : Integer = 0;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pCastleDefenders)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pCastleDefender : Integer = ParserSelectByHandleByIndex(pCastleDefenders, i);
      [*] = ;   var defID : Integer = ParserGetIntValueByKeyByHandle(pCastleDefender, 'DefenderID');
      [*] = ;   var count : Integer = ParserGetIntValueByKeyByHandle(pCastleDefender, 'Count');
      [*] = ;
      [*] = ;   if count < 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := defID;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetDefenderPowerByID', 0);
      [*] = ;      var defPower : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if defPower > maxPower then
      [*] = ;      begin
      [*] = ;         var pDefTerrainTypes : Integer = ParserSelectByHandleByKey(pCastleDefender, 'TerrainType');
      [*] = ;         var allTypes : Boolean = true;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pDefTerrainTypes)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var f : Boolean = ParserGetBoolValueByIndexByHandle(pDefTerrainTypes, j);
      [*] = ;            if not f then
      [*] = ;            begin
      [*] = ;               allTypes := false;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if allTypes then
      [*] = ;         maxPower := defPower;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var buildID : Integer = i;
      [*] = ;   var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;   var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;   var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if not isBuilt then
      [*] = ;   for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;      var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;      var available : Boolean = false;
      [*] = ;
      [*] = ;      if abilID = 15 then
      [*] = ;      begin
      [*] = ;         var taste : Integer = 2;
      [*] = ;         var defID : Integer = param1;
      [*] = ;
      [*] = ;         IntRegister0 := defID;
      [*] = ;         StateMachineExecuteState(initMachine, 'GetDefenderParserById', 0);
      [*] = ;         var pDefender : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var pCastleDefender : Integer = ParserSelectByHandleByIndex(pCastleDefenders, defID);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pCastleDefender, 'Count');
      [*] = ;
      [*] = ;         if count >= 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := defID;
      [*] = ;            StateMachineExecuteState(initMachine, 'GetDefenderPowerByID', 0);
      [*] = ;            var defPower : Integer = IntRegister1;
      [*] = ;
      [*] = ;            if defPower > maxPower then
      [*] = ;            taste := defPower - maxPower;
      [*] = ;
      [*] = ;            if param2 > 0 then
      [*] = ;            begin
      [*] = ;               taste := taste div 10;
      [*] = ;               taste := taste + 1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if j = 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := buildID;
      [*] = ;               ExecuteState('IsBuildingAvailable');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  taste := taste * 2;
      [*] = ;                  if maxPower = 0 then
      [*] = ;                  taste := taste * 3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var pDefTerrainTypes : Integer = ParserSelectByHandleByKey(pDefender, 'TerrainType');
      [*] = ;            var typeCount : Integer = 0;
      [*] = ;
      [*] = ;            for j := ParserGetCountByHandle(pDefTerrainTypes)-3 downto 0 do
      [*] = ;            begin
      [*] = ;               var f : Boolean = ParserGetBoolValueByIndexByHandle(pDefTerrainTypes, j);
      [*] = ;               if f then
      [*] = ;               typeCount := typeCount + 1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            taste := (taste * typeCount) div 4;
      [*] = ;            if taste <= 0 then
      [*] = ;            taste := 1;
      [*] = ;
      [*] = ;            MakeBuildTaste(buildID, taste, pBuildTastes);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// union race buildings
      [*] = ;var plUnion : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;if plUnion > 0 then
      [*] = ;begin
      [*] = ;   for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var buildID : Integer = i;
      [*] = ;      var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;      var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;      var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;      if not isBuilt then
      [*] = ;      begin
      [*] = ;         for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;            var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;            var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;
      [*] = ;            if (abilID = 47) and (param1 = plUnion) then
      [*] = ;            MakeBuildTaste(buildID, 30000, pBuildTastes);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// mood buildings
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;var mood : Integer = IntRegister0;
      [*] = ;if mood < 0 then
      [*] = ;begin
      [*] = ;   for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var buildID : Integer = i;
      [*] = ;      var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;      var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;      var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;      if not isBuilt then
      [*] = ;      begin
      [*] = ;         for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;            var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;            var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;            var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;            if (abilID = 12) then
      [*] = ;            begin
      [*] = ;               var taste : Integer = Round(Abs(mood) * 100);
      [*] = ;
      [*] = ;               if param1 + param2 > 0 then
      [*] = ;               begin
      [*] = ;                  taste := taste * (param1 + param2);
      [*] = ;
      [*] = ;                  IntRegister0 := buildID;
      [*] = ;                  ExecuteState('IsBuildingAvailable');
      [*] = ;                  if BoolRegister0 then
      [*] = ;                  taste := taste * 100;
      [*] = ;
      [*] = ;                  MakeBuildTaste(buildID, taste, pBuildTastes);
      [*] = ;               end;
      [*] = ;               if param1 + param2 < 0 then
      [*] = ;               begin
      [*] = ;                  var pBuildTaste : Integer = ParserSelectByHandleByIndex(pBuildTastes, buildID);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pBuildTaste, 'Taste', 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// all player provinces params
      [*] = ;var coast : Integer = 0;
      [*] = ;mood := 0;
      [*] = ;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   var player : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;   if SameText(player, myPlName) then
      [*] = ;   begin
      [*] = ;      var provCoastal : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Coastal');
      [*] = ;      if provCoastal > 0 then
      [*] = ;      coast := coast + 1;
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;      if (IntRegister0<0) then
      [*] = ;      mood := mood + Round(Abs(IntRegister0));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := 52;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;if not BoolRegister0 then
      [*] = ;MakeBuildTaste(52, coast*10, pBuildTastes);
      [*] = ;
      [*] = ;IntRegister0 := 31;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;if not BoolRegister0 then
      [*] = ;MakeBuildTaste(31, mood*20, pBuildTastes);
      [*] = ;
      [*] = ;IntRegister0 := 44;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;if not BoolRegister0 then
      [*] = ;MakeBuildTaste(44, mood*20, pBuildTastes);
      [*] = ;
      [*] = ;// check inner building abilities
      [*] = ;for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var buildID : Integer = i;
      [*] = ;   var pBuildTaste : Integer = ParserSelectByHandleByIndex(pBuildTastes, i);
      [*] = ;   var taste : Integer = ParserGetIntValueByKeyByHandle(pBuildTaste, 'Taste');
      [*] = ;
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   ExecuteState('IsBuildingAvailable');
      [*] = ;   var available : Boolean = BoolRegister0 and (not BoolRegister2);
      [*] = ;
      [*] = ;   if (taste > 0) and available then
      [*] = ;   begin
      [*] = ;      var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;      var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, j);
      [*] = ;         var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;         var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;         var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;         case abilID of
      [*] = ;            5 :
      [*] = ;            // gold and gem income
      [*] = ;            begin
      [*] = ;               var plGoldInc : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;               var plGemInc : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;
      [*] = ;               if param1 > 0 then
      [*] = ;               begin
      [*] = ;                  var mult : Integer = 1;
      [*] = ;                  if plGoldInc < 40 then
      [*] = ;                  mult := mult + 1;
      [*] = ;                  if plGoldInc < 20 then
      [*] = ;                  mult := mult + 1;
      [*] = ;                  if plGoldInc < 10 then
      [*] = ;                  mult := mult + 1;
      [*] = ;
      [*] = ;                  taste := taste + param1 * mult;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if param2 > 0 then
      [*] = ;               begin
      [*] = ;                  var mult : Integer = 4;
      [*] = ;                  if plGemInc < 20 then
      [*] = ;                  mult := mult + 1;
      [*] = ;                  if plGemInc < 10 then
      [*] = ;                  mult := mult + 1;
      [*] = ;                  if plGemInc < 5 then
      [*] = ;                  mult := mult + 1;
      [*] = ;
      [*] = ;                  taste := taste + param2 * mult;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            9 :
      [*] = ;            // resource income
      [*] = ;            begin
      [*] = ;               IntRegister0 := param1;
      [*] = ;               ExecuteState('GetResCount');
      [*] = ;               var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;               taste := taste + param2 * resCount;
      [*] = ;            end;
      [*] = ;            12 :
      [*] = ;            // mood
      [*] = ;            begin
      [*] = ;               taste := taste + param2 * 50 + param1 * 10;
      [*] = ;            end;
      [*] = ;            16, 22 :
      [*] = ;            // total income, building prices
      [*] = ;            begin
      [*] = ;               taste := taste + param1 * 20;
      [*] = ;            end;
      [*] = ;            37 :
      [*] = ;            // speed
      [*] = ;            begin
      [*] = ;               taste := taste + param1 * 100;
      [*] = ;            end;
      [*] = ;            17 :
      [*] = ;            // res prices
      [*] = ;            begin
      [*] = ;               for k := ParserGetCountByHandle(pResources)-1 downto 1 do
      [*] = ;               begin
      [*] = ;                  IntRegister0 := k;
      [*] = ;                  ExecuteState('GetResCount');
      [*] = ;                  if IntRegister1 <= 0 then
      [*] = ;                  taste := taste + param1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            46 :
      [*] = ;            // karma
      [*] = ;            begin
      [*] = ;               var plKarma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;               // TODO: insert karma value from player's profile
      [*] = ;               if (plKarma * param1 > 0) then
      [*] = ;               taste := taste * 2
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  taste := taste div 3;
      [*] = ;
      [*] = ;                  var pFirstAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, 0);
      [*] = ;                  var id : Integer = ParserGetIntValueByKeyByHandle(pFirstAbility, 'AbilityID');
      [*] = ;
      [*] = ;                  if id = 8 then
      [*] = ;                  taste := 0;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   ParserSetIntValueByKeyByHandle(pBuildTaste, 'Taste', taste);
      [*] = ;end;
      [*] = ;
      [*] = ;// make possible buildings array
      [*] = ;var noTaste : Integer = 0;
      [*] = ;var yesTaste : Integer = 0;
      [*] = ;var wanna : Integer = 0;
      [*] = ;
      [*] = ;var plGoldLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;var plGemLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;
      [*] = ;ArrayClear;
      [*] = ;for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 1 do
      [*] = ;begin
      [*] = ;   var buildID : Integer = i;
      [*] = ;   var pBuildTaste : Integer = ParserSelectByHandleByIndex(pBuildTastes, i);
      [*] = ;   var taste : Integer = ParserGetIntValueByKeyByHandle(pBuildTaste, 'Taste');
      [*] = ;
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   ExecuteState('IsBuildingAvailable');
      [*] = ;   var available : Boolean = BoolRegister0 and BoolRegister1 and (not BoolRegister2);
      [*] = ;
      [*] = ;   if available then
      [*] = ;   begin
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      ExecuteState('GetBuildPrice');
      [*] = ;      var buildGold : Integer = IntRegister1;
      [*] = ;      var buildGem : Integer = IntRegister2;
      [*] = ;
      [*] = ;      if ((plGold>=plGoldLimit+buildGold) or (buildGold=0)) and ((buildGem=0) or (plGem>=plGemLimit+buildGem)) then
      [*] = ;      begin
      [*] = ;         if yesTaste < taste then
      [*] = ;         yesTaste := taste;
      [*] = ;         if taste < 1 then
      [*] = ;         taste := 1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pBuildTaste, 'Taste', taste);
      [*] = ;
      [*] = ;         ArrayPushValue(buildID);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if noTaste < taste then
      [*] = ;         begin
      [*] = ;            noTaste := taste;
      [*] = ;            wanna := buildID;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;Log('ChooseInnerBuild execute');
      [*] = ;//Log('ArrayGetCount = ' + IntToStr(ArrayGetCount));
      [*] = ;// choose building
      [*] = ;if ArrayGetCount > 0 then
      [*] = ;begin
      [*] = ;   var builder : Boolean = true;
      [*] = ;   if noTaste > yesTaste then
      [*] = ;   begin
      [*] = ;      if noTaste - yesTaste - 1000 * RandomExt > 0 then
      [*] = ;      builder := false;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // we build building
      [*] = ;   if builder then
      [*] = ;   begin
      [*] = ;      var sum : Integer = 0;
      [*] = ;      for i := ArrayGetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var buildID : Integer = ArrayGetValueByIndex(i);
      [*] = ;         var pBuildTaste : Integer = ParserSelectByHandleByIndex(pBuildTastes, buildID);
      [*] = ;         sum := sum + ParserGetIntValueByKeyByHandle(pBuildTaste, 'Taste');
      [*] = ;      end;
      [*] = ;
      [*] = ;      var randSum : Float = RandomExt * sum;
      [*] = ;      for i := ArrayGetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var buildID : Integer = ArrayGetValueByIndex(i);
      [*] = ;         var pBuildTaste : Integer = ParserSelectByHandleByIndex(pBuildTastes, buildID);
      [*] = ;         var taste : Integer = ParserGetIntValueByKeyByHandle(pBuildTaste, 'Taste');
      [*] = ;         randSum := randSum - taste;
      [*] = ;
      [*] = ;         if randSum < 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := buildID;
      [*] = ;            ExecuteState('BuyInnerBuild');
      [*] = ;
      [*] = ;            var buildName : String = GetLocaleTableListItemByID('inner_build', IntToStr(BuildID));
      [*] = ;            _gui_ProgressCalculations(_log_name+' Player ' + myPlName + ' builds ' + buildName + '(' + IntToStr(buildID) + ') with taste = ' + IntToStr(taste));
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

