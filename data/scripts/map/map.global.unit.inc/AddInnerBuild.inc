section.begin
   Name = AddInnerBuild
   Description : struct.begin
      [*] = ;IntRegister0 - inner building ID
   struct.end
   Code : struct.begin
      [*] = ;var buildID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\ADDINNERBUILD';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pSpells : Integer = gPrototypeData.spells.handle;
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;
      [*] = ;IntRegister0 := buildID;
      [*] = ;MapExecuteState('GetInnerBuildParserByID');
      [*] = ;var pBuilding : Integer = IntRegister1;
      [*] = ;var pBuildAbilities : Integer = ParserSelectByHandleByKey(pBuilding, 'Abilities');
      [*] = ;var buildGroup : Integer = ParserGetIntValueByKeyByHandle(pBuilding, 'Group');
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pPlProvince : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pPlProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pPlProvince, 'AvOuterBuildings');
      [*] = ;var pInnerBuildings : Integer = ParserSelectByHandleByKey(pPlProvince, 'InnerBuildings');
      [*] = ;var pInnerBuilding : Integer = ParserAddChildByIndex(pInnerBuildings, '*');
      [*] = ;ParserSetIntValueByKeyByHandle(pInnerBuilding, 'BuildingID', buildID);
      [*] = ;ParserSetIntValueByKeyByHandle(pInnerBuilding, 'Group', buildGroup);
      [*] = ;
      [*] = ;// change resource prices
      [*] = ;var pBuildResources : Integer = ParserSelectByHandleByKey(pBuilding, 'Resources');
      [*] = ;for i := ParserGetCountByHandle(pBuildResources)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pBuildResource : Integer = ParserSelectByHandleByIndex(pBuildResources, i);
      [*] = ;   var resID : Integer = ParserGetIntValueByKeyByHandle(pBuildResource, 'ResourceID');
      [*] = ;   var resCount : Integer = ParserGetIntValueByKeyByHandle(pBuildResource, 'Count');
      [*] = ;
      [*] = ;   IntRegister0 := resID;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'GetResCount');
      [*] = ;
      [*] = ;   if IntRegister1 <= 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := resID;
      [*] = ;      IntRegister1 := resCount;
      [*] = ;      MapExecuteState('map.ChangeResPrice');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// check for spells available in this building
      [*] = ;for i := 0 to ParserGetCountByHandle(pSpells)-1 do
      [*] = ;begin
      [*] = ;   var pSpell : Integer = ParserSelectByHandleByIndex(pSpells, i);
      [*] = ;   var spellID : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'SpellID');
      [*] = ;   var id : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'BuildingID');
      [*] = ;
      [*] = ;   if (id = buildID) and (SpellID > 0) then
      [*] = ;   begin
      [*] = ;      var level : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Level');
      [*] = ;      var pProvSpells : Integer = ParserSelectByHandleByKey(pPlProvince, 'SpellLevels');
      [*] = ;      var pProvLevelSpells : Integer = ParserSelectByHandleByIndex(pProvSpells, level);
      [*] = ;      pProvLevelSpells := ParserSelectByHandleByKey(pProvLevelSpells, 'Spells');
      [*] = ;
      [*] = ;      var pProvSpell : Integer = ParserAddChildByIndex(pProvLevelSpells, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvSpell, 'SpellID', spellID);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// check for defenders, rituals, walls in abilities
      [*] = ;var pMyDefenders : Integer = ParserSelectByHandleByKey(pPlProvince, 'Defenders');
      [*] = ;var pProvRituals : Integer = ParserSelectByHandleByKey(pPlProvince, 'AvailableRituals');
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pBuildAbilities)-1 do
      [*] = ;begin
      [*] = ;   var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, i);
      [*] = ;   var abilityID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param2');
      [*] = ;
      [*] = ;   case abilityID of
      [*] = ;      1 :
      [*] = ;      begin
      [*] = ;         // check for items that allow this building
      [*] = ;         var pProvShop : Integer = ParserSelectByHandleByKey(pPlProvince, 'Shop');
      [*] = ;         var pProvItems : Integer = ParserSelectByHandleByKey(pProvShop, 'Items');
      [*] = ;
      [*] = ;         if param1 < 2 then
      [*] = ;         begin
      [*] = ;            for j := 0 to ParserGetCountByHandle(pItems)-1 do
      [*] = ;            begin
      [*] = ;               var pItem : Integer = ParserSelectByHandleByIndex(pItems, j);
      [*] = ;               var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;               var itemBuildID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'BuildingID');
      [*] = ;
      [*] = ;               if itemBuildID = buildID then
      [*] = ;               begin
      [*] = ;                  var pNewItem : Integer = ParserAddChildByIndex(pProvItems, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewItem, 'ItemID', itemID);
      [*] = ;
      [*] = ;                  if param1 = 0 then
      [*] = ;                     ParserSetIntValueByKeyByHandle(pNewItem, 'Count', 0)
      [*] = ;                  else
      [*] = ;                     ParserSetIntValueByKeyByHandle(pNewItem, 'Count', 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _rand_ClearRoll;
      [*] = ;            var count : Integer = 0;
      [*] = ;            for j := 0 to ParserGetCountByHandle(pItems)-1 do
      [*] = ;            begin
      [*] = ;               var pItem : Integer = ParserSelectByHandleByIndex(pItems, j);
      [*] = ;               var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;               var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;               var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;
      [*] = ;               if (shopLevel = param2) and (rarity > 1) and (rarity <= param2) then
      [*] = ;               begin
      [*] = ;                  gArrRollerN[count] := itemID;
      [*] = ;                  gArrRollerP[count] := 7 - rarity;
      [*] = ;                  count := count + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            for j := 0 to 7-param2-1 do
      [*] = ;            begin
      [*] = ;               var itemID : Integer = _rand_Roll(true);
      [*] = ;               if itemID > 0 then
      [*] = ;               begin
      [*] = ;                  var pNewItem : Integer = ParserAddChildByIndex(pProvItems, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewItem, 'ItemID', itemID);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewItem, 'Count', 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      4 :
      [*] = ;      begin
      [*] = ;         // open garrison slots
      [*] = ;         var pProvGarrison : Integer = ParserSelectByHandleByKey(pPlProvince, 'Garrison');
      [*] = ;         var pGarrisonSlots : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Slots');
      [*] = ;         var pGarrisonSlot : Integer = ParserSelectByHandleByIndex(pGarrisonSlots, param1-1);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pGarrisonSlot, 'Count');
      [*] = ;         count := count + param2;
      [*] = ;         ParserSetIntValueByKeyByHandle(pGarrisonSlot, 'Count', count);
      [*] = ;      end;
      [*] = ;      6 :
      [*] = ;      begin
      [*] = ;         var pProvMercenary : Integer = ParserSelectByHandleByKey(pPlProvince, 'Mercenary');
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pProvMercenary, 'UnitID');
      [*] = ;
      [*] = ;         if unitID = 0 then
      [*] = ;         ExecuteState('AddMercenary');
      [*] = ;      end;
      [*] = ;      8 :
      [*] = ;      begin
      [*] = ;         // recruit units
      [*] = ;         var pProvRecruitUnits : Integer = ParserSelectByHandleByKey(pPlProvince, 'RecruitUnits');
      [*] = ;         var pNewRecruitUnit : Integer = ParserAddChildByIndex(pProvRecruitUnits, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewRecruitUnit, 'UnitID', param1);
      [*] = ;      end;
      [*] = ;      10 :
      [*] = ;      begin
      [*] = ;         var stable : Integer = ParserGetIntValueByKeyByHandle(pPlProvince, 'Stable');
      [*] = ;         stable := stable + param1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pPlProvince, 'Stable', stable);
      [*] = ;      end;
      [*] = ;      11 :
      [*] = ;      begin
      [*] = ;         // outer building
      [*] = ;         var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, param1);
      [*] = ;
      [*] = ;         if param2 > 0 then
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvOuterBuilding, 'Count', param2)
      [*] = ;         else
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvOuterBuilding, 'Count', -1);
      [*] = ;      end;
      [*] = ;      15 :
      [*] = ;      begin
      [*] = ;         // add defenders
      [*] = ;         var defenderID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;         var pMyDefender : Integer = ParserSelectByHandleByIndex(pMyDefenders, defenderID);
      [*] = ;         var defCount : Integer = ParserGetIntValueByKeyByHandle(pMyDefender, 'Count');
      [*] = ;
      [*] = ;         if param2 > 0 then
      [*] = ;            ParserSetIntValueByKeyByHandle(pMyDefender, 'Count', defCount+param2)
      [*] = ;         else
      [*] = ;            ParserSetIntValueByKeyByHandle(pMyDefender, 'Count', -1);
      [*] = ;      end;
      [*] = ;      27 :
      [*] = ;      begin
      [*] = ;         // add rituals
      [*] = ;         var ritualID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;
      [*] = ;         var pProvRitual : Integer = ParserSelectByHandleByIndex(pProvRituals, ritualID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvRitual, 'Count', -1);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvRitual, 'Cooldown', 0);
      [*] = ;      end;
      [*] = ;      35 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetMaxFortValue');
      [*] = ;         var maxFort : Integer = IntRegister0;
      [*] = ;
      [*] = ;         // increase wall strength
      [*] = ;         var fort : Integer = ParserGetIntValueByKeyByHandle(pPlProvince, 'Fort');
      [*] = ;         var r : Float = fort / maxFort;
      [*] = ;
      [*] = ;         maxFort := maxFort + param1;
      [*] = ;         var newFort : Integer = Floor(maxFort * r);
      [*] = ;         ParserSetIntValueByKeyByHandle(pPlProvince, 'Fort', newFort);
      [*] = ;      end;
      [*] = ;      39 :
      [*] = ;      begin
      [*] = ;         var canHire : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iCanHire);
      [*] = ;         canHire := canHire + param1;
      [*] = ;         SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanHire, canHire);
      [*] = ;      end;
      [*] = ;      40 :
      [*] = ;      begin
      [*] = ;         var canOuterBuild : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iCanOuterBuild);
      [*] = ;         canOuterBuild := canOuterBuild + param1;
      [*] = ;         SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanOuterBuild, canOuterBuild);
      [*] = ;      end;
      [*] = ;      46 :
      [*] = ;      begin
      [*] = ;         var karma : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iKarma);
      [*] = ;         karma := karma + param1;
      [*] = ;         SetIntValueByIndex(gc_map_PLStack_MapUnit_iKarma, karma);
      [*] = ;      end;
      [*] = ;      48 :
      [*] = ;      begin
      [*] = ;         // event timer
      [*] = ;         if cMode = 'cmPlayer' then
      [*] = ;         begin
      [*] = ;            var pEventTimers : Integer = ParserSelectByHandleByKey(pPlParser, 'EventTimers');
      [*] = ;            var pEventTimer : Integer = ParserAddChildByIndex(pEventTimers, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventTimer, 'EventID', param1);
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventTimer, 'Timer', param2);
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventTimer, 'DummyUID', dummyUID);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      50 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := pPlProvince;
      [*] = ;         IntRegister1 := param1;
      [*] = ;         IntRegister2 := param2;
      [*] = ;         IntRegister3 := 0;
      [*] = ;         IntRegister4 := -1;
      [*] = ;         IntRegister5 := 0;
      [*] = ;         MapExecuteState('AddSite');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//visualization
      [*] = ;if (myPlHandle = GetPlayerHandleInterfaceIO) then
      [*] = ;begin
      [*] = ;   if _obj_CreationStateEnabled('InnerBuildScenery') and ((gGame.gameType <> gc_GameTypeHotseat) or (GetPlayerIndexByHandle(myPlHandle) = 0)) then // graphics are implemented only for one town, so in hotseat games, apply only the host.
      [*] = ;   begin
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      ExecuteState('CreateInnerBuildModel');
      [*] = ;   end;
      [*] = ;
      [*] = ;   _map_RefreshProvinceHUD(dummyUID);
      [*] = ;
      [*] = ;   IntRegister0 := -3;
      [*] = ;   MapExecuteState('CheckTutorialProgress');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

