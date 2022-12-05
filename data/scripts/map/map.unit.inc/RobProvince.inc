section.begin
   Name = RobProvince
   UsedFileName =
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyQuests : Integer = ParserSelectByHandleByKey(pMyParser, 'Quests');
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var pMachineParser : Integer = ParserSelectStateMachineByHandle(initMachine);
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(pMachineParser, 'Queries');
      [*] = ;
      [*] = ;var pQuests : Integer = gPrototypeData.quests.handle;
      [*] = ;var uid : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;
      [*] = ;IntRegister0 := uid;
      [*] = ;StateMachineExecuteState(initMachine, 'GetProvinceParserByUID', 0);
      [*] = ;var pProvince : Integer = IntRegister1;
      [*] = ;var population : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Population');
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;var provName : String = StringRegister0;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerAttitude');
      [*] = ;var attitude : Integer = IntRegister0;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;if population > 0 then
      [*] = ;begin
      [*] = ;   var power : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth);
      [*] = ;   var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pMyUnits)-1 downto 1 do
      [*] = ;   begin
      [*] = ;      var pMyUnit : Integer = ParserSelectByHandleByIndex(pMyUnits, i);
      [*] = ;      var unitID : Integer = ParserGetIntValueByKeyByHandle(pMyUnit, 'UnitID');
      [*] = ;      var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;      power := power + ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      IntRegister1 := pMyUnit;
      [*] = ;      IntRegister2 := myGOHandle;
      [*] = ;      IntRegister3 := 58;
      [*] = ;      MapExecuteState('CheckUnitAbility');
      [*] = ;      if IntRegister4 > 0 then
      [*] = ;      power := power + 1;
      [*] = ;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      IntRegister1 := pMyUnit;
      [*] = ;      IntRegister2 := myGOHandle;
      [*] = ;      IntRegister3 := 50;
      [*] = ;      MapExecuteState('CheckUnitAbility');
      [*] = ;      if IntRegister4 > 0 then
      [*] = ;      power := power + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var killed : Integer = Floor(5 + power + population * (power + 1) / 100);
      [*] = ;   if killed > population then
      [*] = ;   killed := population;
      [*] = ;
      [*] = ;   var loot: Integer = Floor((killed + RandomExt * killed) / 7 + 20 + RandomExt*50);
      [*] = ;
      [*] = ;   IntRegister0 := 982;
      [*] = ;   GameObjectExecuteStateByHandle(myGOHandle, 'CheckAbility');
      [*] = ;   var robAbility : Integer = IntRegister1;
      [*] = ;
      [*] = ;   loot := loot + Floor(loot * robAbility / 100);
      [*] = ;
      [*] = ;   IntRegister0 := 41;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'CheckInnerBuildAbility');
      [*] = ;   var param1 : Integer = IntRegister1;
      [*] = ;
      [*] = ;   loot := loot + (loot * param1) div 100;
      [*] = ;
      [*] = ;   var karma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;   karma := karma - 5;
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma, karma);
      [*] = ;
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold + loot);
      [*] = ;
      [*] = ;   plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + loot);
      [*] = ;      
      [*] = ;   if _stats_IsEligible(myPlHandle) then _stats_SimpleUpdate('Gold', 'PlunderGold', loot);
      [*] = ;
      [*] = ;   population := population - killed;
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvince, 'Population', population);
      [*] = ;
      [*] = ;   if attitude > -10 then
      [*] = ;   begin
      [*] = ;      var change : Integer = 1 + killed div 200;
      [*] = ;      if change > 3 then
      [*] = ;      change := 3;
      [*] = ;
      [*] = ;      attitude := attitude - change;
      [*] = ;      if attitude < -10 then
      [*] = ;      attitude := -10;
      [*] = ;
      [*] = ;      //IntRegister0 := attitude;
      [*] = ;      //GameObjectExecuteStateByHandle(dummyHandle, 'SetOwnerAttitude');
      [*] = ;      IntRegister0 := myPlHandle;
      [*] = ;      IntRegister1 := -change;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'ChangeAttitude');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if GetPlayerIndexByHandle(myPlHandle) = gIntRegister_MapMyPlayerIndex then
      [*] = ;   begin
      [*] = ;      _hero_GetName(myGOHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;      gStringRegister_ProvinceName := provName;
      [*] = ;      gIntRegister_GoldReward := loot;
      [*] = ;
      [*] = ;      var queryID : String;
      [*] = ;      if population > 0 then
      [*] = ;      queryID := IntToStr(gc_gui_query_heroRobProvince)
      [*] = ;      else
      [*] = ;      queryID := IntToStr(gc_gui_query_heroFinalRobProvince);
      [*] = ;
      [*] = ;      StringRegister0 := queryID;
      [*] = ;      GUIExecuteState('map.RequestQueryWindow');
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pMyQuests)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMyQuest : Integer = ParserSelectByHandleByIndex(pMyQuests, i);
      [*] = ;      var questID : Integer = ParserGetIntValueByKeyByHandle(pMyQuest, 'Index');
      [*] = ;      var complete : Boolean = ParserGetBoolValueByKeyByHandle(pMyQuest, 'Complete');
      [*] = ;
      [*] = ;      var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;      var qType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;
      [*] = ;      if (qType = 6) and (not complete) then
      [*] = ;      begin
      [*] = ;         var pMyArProgress : Integer = ParserSelectByHandleByKey(pMyQuest, 'ArProgress');
      [*] = ;         var pMyProgress : Integer = ParserSelectByHandleByIndex(pMyArProgress, 0);
      [*] = ;         var progress : Integer = ParserGetIntValueByKeyByHandle(pMyProgress, 'Progress');
      [*] = ;         progress := progress + loot;
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyProgress, 'Progress', progress);
      [*] = ;
      [*] = ;         IntRegister0 := i;
      [*] = ;         ExecuteState('CheckQuestDone');
      [*] = ;
      [*] = ;         var complete : Boolean = ParserGetBoolValueByKeyByHandle(pMyQuest, 'Complete');
      [*] = ;         var encFound : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncFound');
      [*] = ;         var encDone : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncDone');
      [*] = ;
      [*] = ;         if (not complete) and (encFound > 0) then
      [*] = ;         begin
      [*] = ;            var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encFound);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', myUID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', i);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pillage : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iPillage);
      [*] = ;   pillage := pillage + loot;
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iPillage, pillage);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iActionType, 0);
      [*] = ;   SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

