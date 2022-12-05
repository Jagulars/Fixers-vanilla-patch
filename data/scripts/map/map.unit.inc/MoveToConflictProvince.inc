section.begin
   Name = MoveToConflictProvince
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\MOVETOCONFLICTPROVINCE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pConflict : Integer = _misc_GetCurrentConflict();
      [*] = ;var confType : Integer = ParserGetIntValueByKeyByHandle(pConflict, 'Type');
      [*] = ;
      [*] = ;var curUID : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(curUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(curUID);
      [*] = ;var queryID : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(confType)+','+IntToStr(gIntRegister_ConflictHeroUID1)+','+IntToStr(gIntRegister_ConflictHeroUID2)+']',_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;if (confType = gc_LanConflictProvAttack) or (confType = gc_LanConflictCancelSiege) then
      [*] = ;begin
      [*] = ;   var siegePlHandle,plIndex : Integer;
      [*] = ;   var isSiege : Boolean;
      [*] = ;
      [*] = ;   // enemy player province attack
      [*] = ;   // check for attack dialog
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'IsUnderSiege');
      [*] = ;
      [*] = ;   isSiege := BoolRegister0;
      [*] = ;   if isSiege then
      [*] = ;   begin
      [*] = ;      if IntRegister0 <> 0 then
      [*] = ;         plIndex := GetPlayerIndexByHandle( IntRegister0 )
      [*] = ;      else
      [*] = ;         plIndex := -1;
      [*] = ;      if plIndex = myPlIndex then // my different hero is besieging enemy
      [*] = ;      begin
      [*] = ;         IntRegister0 := myPlIndex;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetPlayerIndex');
      [*] = ;         plIndex := IntRegister1;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := myPlIndex;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetPlayerIndex');
      [*] = ;      plIndex := IntRegister1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   queryID := -1;
      [*] = ;   if plIndex <> -1 then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;
      [*] = ;      if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;      begin
      [*] = ;         ExecuteState('SetupEnemyRegisters');
      [*] = ;         if isSiege then
      [*] = ;            queryID := gc_gui_query_heroEnemyAttackSiegeHero
      [*] = ;         else
      [*] = ;            queryID := gc_gui_query_heroEnemyAttackProvince;
      [*] = ;         StringRegister0 := IntToStr(queryID);
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'CheckRequestQuery');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if queryID = -1 then
      [*] = ;      ExecuteState('AttackTargetProvince');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   // simultaneous attack
      [*] = ;   var enUID : Integer = 0;
      [*] = ;   case myUID of
      [*] = ;      gIntRegister_ConflictHeroUID1 : enUID := gIntRegister_ConflictHeroUID2;
      [*] = ;      gIntRegister_ConflictHeroUID2 : enUID := gIntRegister_ConflictHeroUID1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   queryID := -1;
      [*] = ;   if enUID > 0 then
      [*] = ;   begin
      [*] = ;      //if myPlIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;      Assert(SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPlayer'),_log_name+' called for AI player.');
      [*] = ;      //if SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPlayer') then
      [*] = ;      begin
      [*] = ;         var enGOHandle : Integer = GetGameObjectHandleByUniqueId(enUID);
      [*] = ;         _hero_GetName(myGOHandle, gStringRegister_MyHeroName);
      [*] = ;         _hero_GetName(enGOHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;         var enPlHandle : Integer = GetGameObjectPlayerHandleByHandle(enGOHandle);
      [*] = ;         PlayerExecuteStateByHandle(enPlHandle, 'GetName');
      [*] = ;         gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;         var pEnParser : Integer = ParserSelectGameObject(enGOHandle);
      [*] = ;         var pEnUnits : Integer = ParserSelectByHandleByKey(pEnParser, 'Units');
      [*] = ;
      [*] = ;         IntRegister0 := pEnUnits;
      [*] = ;         MapExecuteState('map.GetArmyUnitsCount');
      [*] = ;         gIntRegister_GuardEnemyCount := IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := pEnUnits;
      [*] = ;         MapExecuteState('map.GetArmyUnitsList');
      [*] = ;         gStringRegister_GuardEnemyList := StringRegister0;
      [*] = ;
      [*] = ;         gIntRegister_MapCurHeroIndex := GetGameObjectIndexByHandle(myGOHandle);
      [*] = ;
      [*] = ;         IntRegister0 := 12;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CheckRitualEffect');
      [*] = ;         if BoolRegister0 then
      [*] = ;            queryID := gc_gui_query_heroProvinceMagicBarrier
      [*] = ;         else
      [*] = ;            queryID := gc_gui_query_heroSimultaneousAttack;
      [*] = ;         StringRegister0 := IntToStr(queryID);
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(myPlHandle,'CheckRequestQuery');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(queryID)+']',$1000000 or _log_trace);
   struct.end
section.end

