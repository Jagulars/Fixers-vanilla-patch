section.begin
   Name = CheckSabotage
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\GLOBAL.INC\CHECKSABOTAGE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var bProceedTurn : Boolean = true;
      [*] = ;
      [*] = ;ExecuteState('GetHeroHandle');
      [*] = ;var heroHandle : Integer = IntRegister0;
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID));
      [*] = ;
      [*] = ;IntRegister0 := 24;
      [*] = ;GameObjectExecuteStateByHandle(mapHeroHandle, 'GetSkillLevel');
      [*] = ;var skill24 : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := 981;
      [*] = ;GameObjectExecuteStateByHandle(mapHeroHandle, 'CheckAbility');
      [*] = ;var abil981 : Integer = IntRegister1;
      [*] = ;
      [*] = ;if (skill24 > 1) or (abil981 > 0) then
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;   
      [*] = ;   var arPrices : array [0..2] of Integer;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to 2 do
      [*] = ;       arPrices[i] := -1;
      [*] = ;
      [*] = ;   ExecuteState('GetSabotagePrices');
      [*] = ;   arPrices[0] := IntRegister0;
      [*] = ;   arPrices[1] := IntRegister1;
      [*] = ;   arPrices[2] := IntRegister2;
      [*] = ;   //arPrices[0] := 100;
      [*] = ;   //arPrices[1] := 200;
      [*] = ;   //arPrices[2] := 300;
      [*] = ;
      [*] = ;   if (arPrices[0] >= 0) or (arPrices[1] >= 0) or (arPrices[2] >= 0) then
      [*] = ;   begin
      [*] = ;      if (myPlHandle = GetPlayerHandleInterfaceIO) then
      [*] = ;      begin
      [*] = ;         bProceedTurn := false;
      [*] = ;         
      [*] = ;         gIntRegister_FalseAlarmPrice := arPrices[0];
      [*] = ;         gIntRegister_PoisonedWaterPrice := arPrices[1];
      [*] = ;         gIntRegister_PanicPrice := arPrices[2];
      [*] = ;         _hero_GetName(mapHeroHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;         _gv_SetBattleLock($10001,_log_name);
      [*] = ;
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_heroMakeSabotage);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;      end
      [*] = ;      else // AI
      [*] = ;      if SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC') then
      [*] = ;      begin
      [*] = ;         var mapPlHandle : Integer = GetGameObjectPlayerHandleByHandle(mapHeroHandle);
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;
      [*] = ;         ArrayClear();
      [*] = ;         for i := 0 to 2 do
      [*] = ;            if (arPrices[i] >= 0) and ((arPrices[i] <= plGold) or (arPrices[i] = 0)) then
      [*] = ;               ArrayPushValue(i);
      [*] = ;
      [*] = ;         var count : Integer = ArrayGetCount;
      [*] = ;         if count > 0 then
      [*] = ;         begin
      [*] = ;            var ind : Integer = _rand_Random(count);
      [*] = ;            var sabInd : Integer = ArrayGetValueByIndex(ind);
      [*] = ;
      [*] = ;            IntRegister0 := sabInd;
      [*] = ;            ExecuteState('MakeSabotage');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetBoolValueByIndex(gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;
      [*] = ;BoolRegister0 := bProceedTurn;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

