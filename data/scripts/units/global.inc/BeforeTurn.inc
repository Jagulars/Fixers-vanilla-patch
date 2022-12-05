section.begin
   Name = BeforeTurn
   Description : struct.begin
      [*] = ;BoolRegister0 - make turn
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\GLOBAL.INC\BEFORETURN';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var makeTurn : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var plHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var autoBattle : Boolean = GetBoolValueByIndex(gc_battle_PLStack_bAutoBattle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;ExecuteState('GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;if (plHandle = GetPlayerHandleInterfaceIO) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle)) and _misc_IsLanBattle() then
      [*] = ;begin
      [*] = ;   if (gIntRegister_PlayBell > 0) and (not autoBattle) and (not gBoolRegister_QuickBattle) then
      [*] = ;      _gui_PlaySound('interface','end_turn');
      [*] = ;   
      [*] = ;   gIntRegister_PlayBell := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   var abil : Integer = _unit_CheckAbility(goHandle, gc_ability_heal_aura);
      [*] = ;   if GetGameObjectPlayableObjectByHandle(goHandle) and (abil > 0) then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := true;
      [*] = ;      IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;      IntRegister1 := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'FindNeighbour');
      [*] = ;
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGONeighbours : Integer = ParserSelectByHandleByKey(pGOParser, 'Neighbours');
      [*] = ;      for j := ParserGetCountByHandle(pGONeighbours)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pGONeighbour : Integer = ParserSelectByHandleByIndex(pGONeighbours, j);
      [*] = ;         var uid : Integer = ParserGetIntValueByKeyByHandle(pGONeighbour, 'UID');
      [*] = ;         var nGOHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;         var unitID : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iUnitID);
      [*] = ;         var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;         var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;         if (unitType <> 2) and (unitType <> 4) then
      [*] = ;         begin
      [*] = ;            var aHeal : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iAddHealPoints);
      [*] = ;            aHeal := aHeal + abil;
      [*] = ;            SetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iAddHealPoints, aHeal);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'BeforeTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;if SameText(cMode, 'cmPC') or gBoolRegister_QuickBattle or autoBattle then
      [*] = ;begin
      [*] = ;   IntRegister0 := plHandle;
      [*] = ;   IntRegister1 := enPlHandle;
      [*] = ;   MapExecuteState('bat.CalcActions');
      [*] = ;end;
      [*] = ;
      [*] = ;if not gBoolRegister_BattleSimulate then
      [*] = ;   PlayerExecuteStateByHandle(enPlHandle, 'CalcDangerMap')
      [*] = ;else
      [*] = ;   PlayerExecuteStateByHandle(enPlHandle, 'CalcSimDangerMap');
      [*] = ;
      [*] = ;if (not gBoolRegister_BattlePlaceMode) and makeTurn then
      [*] = ;begin
      [*] = ;   ExecuteState('SetupTowersTarget');
      [*] = ;   ExecuteState('MakeTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

