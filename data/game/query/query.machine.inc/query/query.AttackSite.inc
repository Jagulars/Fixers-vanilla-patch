section.begin
   Name = query.AttackSite
   Code : struct.begin
      [*] = ;var _log_name : String = 'QUERY\QUERY.ATTACKSITE';
      [*] = ;var _log_trace : Integer = $80001;
      [*] = ;
      [*] = ;if gGame.quickgame and (not gBoolRegister_IsDefenderAutoBattle) then
      [*] = ;begin
      [*] = ;   ExecuteState('query.AttackSiteAuto');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var plHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, plHandle);
      [*] = ;
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;var site_idx : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, site_idx);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[P:'+IntToStr(_gv_GetCurrentPlayer)+',SI:'+IntToStr(site_idx)+']',_log_trace);
      [*] = ;// achievements
      [*] = ;var af : Integer = GetPlayerIntValueByHandle(plHandle, gc_map_PLStack_MapUnit_nAchievemntsFlags);
      [*] = ;if ParserSelectByHandleByKey(pProvSite,'Shop') <> 0 then
      [*] = ;   af := (af or 1)
      [*] = ;else
      [*] = ;   af := (af and $fffffffe);
      [*] = ;SetPlayerIntValueByHandle(plHandle, gc_map_PLStack_MapUnit_nAchievemntsFlags, af);
      [*] = ;//
      [*] = ;
      [*] = ;IntRegister0 := ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;IntRegister1 := 0;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'SetupBattleRegisters');
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'CheckAttackMode');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

