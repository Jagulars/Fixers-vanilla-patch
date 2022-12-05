section.begin
   Name = GatherAmmo
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\GATHERAMMO';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var abil23 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_ammo_gather);
      [*] = ;var curAmmo : Integer = GetIntValueByIndex(gc_stack_unit_iCurAmmo);
      [*] = ;var maxAmmo : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxAmmo);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[A: '+IntToStr(abil23)+', Max Ammo: '+IntToStr(maxAmmo)+', Cur Ammo: '+IntToStr(curAmmo)+']',_log_trace);
      [*] = ;
      [*] = ;if (abil23 > 0) and (curAmmo < maxAmmo) then
      [*] = ;begin
      [*] = ;   var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;   GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;   var addAmmo : Integer = 1 + _rand_Random(abil23);
      [*] = ;
      [*] = ;   if curAmmo + addAmmo > maxAmmo then
      [*] = ;      addAmmo := maxAmmo - curAmmo;
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurAmmo, curAmmo + addAmmo);
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var pElmLog : Integer = _log_battle_AddNewElement();
      [*] = ;      ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 7);
      [*] = ;
      [*] = ;      var pSrcUnit : Integer = ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;      ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;
      [*] = ;      var pChangedParams : Integer = ParserGetIntValueByKeyByHandle(pSrcUnit, 'ChangedParams');
      [*] = ;      var pChangedParam : Integer = _log_battle_AddChangedParamToParser(pChangedParams);
      [*] = ;      ParserSetIntValueByKeyByHandle(pChangedParam, 'ParamID', 4);
      [*] = ;      ParserSetIntValueByKeyByHandle(pChangedParam, 'Value', addAmmo);
      [*] = ;
      [*] = ;      _log_battle_Show();
      [*] = ;
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_ammo_gather, addAmmo);
      [*] = ;
      [*] = ;      if _obj_EnabledByFlag(gc_ObjectFlagBattleFX) and (_fx_FindFXHandleByID(myGOHandle, true, 8) = 0) then
      [*] = ;         _fx_GetOrCreateFXByID(myGOHandle, 'fxammo', 0, 0, 0, 0, Random, 8);
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('ActionDone');
      [*] = ;
      [*] = ;   _inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_activateability, 0, gc_ability_ammo_gather, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'GatherAmmo');
      [*] = ;end
      [*] = ;else
      [*] = ;   ErrorLogI('Cannot gather ammo, unit does not have the ability or has maximum ammo');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

