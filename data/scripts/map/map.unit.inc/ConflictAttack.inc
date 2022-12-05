section.begin
   Name = ConflictAttack
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\CONFLICTATTACK';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[UID:'+IntToStr(myUID)+',UID1:'+IntToStr(gIntRegister_ConflictHeroUID1)+',UID2:'+IntToStr(gIntRegister_ConflictHeroUID2)+']',_log_trace);
      [*] = ;if myUID = gIntRegister_ConflictHeroUID2 then // no progressing until both conflict heroes processed.
      [*] = ;begin
      [*] = ;   // start battle
      [*] = ;   var enGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_ConflictHeroUID1);
      [*] = ;   var pEnParser : Integer = ParserSelectGameObject(enGOHandle);
      [*] = ;   var enPlHandle : Integer = GetGameObjectPlayerHandleByHandle(enGOHandle);
      [*] = ;   var enPlIndex : Integer = GetPlayerIndexByHandle(enPlHandle);
      [*] = ;   var cMode1 : String = GetPlayerControlModeByHandle(enPlHandle);
      [*] = ;
      [*] = ;   if gGame.gameType = gc_GameTypeHotseat then
      [*] = ;   begin
      [*] = ;      _gv_SetIOHandle(enPlHandle,_log_name);
      [*] = ;      gIntRegister_MapMyPlayerIndex := enPlIndex;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gv_SetCurrentPlayer(enPlIndex,_log_name);
      [*] = ;   gIntRegister_MapCurHeroIndex := GetGameObjectIndexByHandle(enGOHandle);
      [*] = ;
      [*] = ;   gIntRegister_BattleAttackArmy := pEnParser;
      [*] = ;   gIntRegister_BattleAttackHeroHandle := enGOHandle;
      [*] = ;   gIntRegister_BattleAttackPlayer := enPlHandle;
      [*] = ;
      [*] = ;   gIntRegister_BattleDefendArmy := pMyParser;
      [*] = ;   gIntRegister_BattleDefendHeroHandle := myGOHandle;
      [*] = ;   gIntRegister_BattleDefendPlayer := myPlHandle;
      [*] = ;   
      [*] = ;   var do_lan_attack : Integer;
      [*] = ;   var idxa, idxd : Integer;
      [*] = ;
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) and gBoolRegister_MapResolveConflicts then
      [*] = ;   begin
      [*] = ;      MapExecuteState('map.LanSetupBattleIDs');
      [*] = ;      do_lan_attack := IntRegister0;
      [*] = ;      idxa := IntRegister1;
      [*] = ;      idxd := IntRegister2;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      do_lan_attack := 0;
      [*] = ;
      [*] = ;   var pProvince : Integer = _misc_GetProvinceParserByUID(GetIntValueByIndex(gc_map_GOStack_MapUnit_iTargetUID));
      [*] = ;
      [*] = ;   gIntRegister_MapBattleProvince := pProvince;
      [*] = ;   gIntRegister_BattleProvIndex1 := ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;   gIntRegister_BattleProvIndex2 := ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;
      [*] = ;   var terType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
      [*] = ;   var pTerrainType : Integer = ParserSelectByHandleByIndex(gPrototypeData.terrainTypes.handle, terType);
      [*] = ;   var sTerType : String = ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;
      [*] = ;   gStringRegister_Battle_RightTType := sTerType;
      [*] = ;   gStringRegister_Battle_LeftTType := sTerType;
      [*] = ;
      [*] = ;   gBoolRegister_BattleSimulate := false;
      [*] = ;
      [*] = ;   gIntRegister_BattleSiteID := 0;
      [*] = ;   gIntRegister_BattleSiteLevel := 0;
      [*] = ;   gIntRegister_BattleSiteIndex := -1;
      [*] = ;   gBoolRegister_BattleSiteIsGuarded := false;
      [*] = ;
      [*] = ;   if do_lan_attack <> 0 then
      [*] = ;   begin
      [*] = ;      var pParser : Integer = _misc_ParserGetOrCreateByKey('mat_ftb_FadeToBattle',true);
      [*] = ;      var pRegisters : Integer = ParserAddChildByIndex(pParser, 'Registers');
      [*] = ;      var randKey0, randKey1 : Integer;
      [*] = ;
      [*] = ;      IntRegister0 := pRegisters;
      [*] = ;      MapExecuteState('SaveBattleRegisters');
      [*] = ;
      [*] = ;      GetRandomExtKey64(randKey0, randKey1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pParser, 'RandKey0', randKey0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pParser, 'RandKey1', randKey1);
      [*] = ;
      [*] = ;      if do_lan_attack <> 3 then
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(pParser, 'LanFlags', do_lan_attack);
      [*] = ;         if ((do_lan_attack and 1) <> 0) then
      [*] = ;            ParserSetIntValueByKeyByHandle(pParser, 'LanID', gLanShardGame.arrLanPlayers[idxa].lanID)
      [*] = ;         else
      [*] = ;            ParserSetIntValueByKeyByHandle(pParser, 'LanID', gLanShardGame.arrLanPlayers[idxd].lanID);
      [*] = ;      end;
      [*] = ;
      [*] = ;      Assert((GetLanMode() > 1),'Conflict Attack, Fade to battle called for client.');
      [*] = ;      _inet_LanSendBattleParser(gc_LAN_SHARD_FADETOBATTLE, pParser);
      [*] = ;     // if GetPlayerIndexByHandle(myPlHandle) = gIntRegister_ConflictPlayerIndex then
      [*] = ;         _gv_SetMapLock($10002,_log_name); // it will be decreased by one in gc_LAN_SHARD_CHOOSERESULT
      [*] = ;      //else
      [*] = ;      //   _gv_SetMapLock($10001,_log_name);
      [*] = ;      if _log then _log_valuesM('HumanAttack|HumanDefense|ProvinceIdx|LanFlags|IdxA|IdxD',gIntRegsiter_LanBatServerID,gIntRegsiter_LanBatClientID,gIntRegister_CurProvinceIndex,do_lan_attack,idxa,idxd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      Assert((SameText(cMode, 'cmPlayer') or SameText(cMode1, 'cmPlayer')),_log_name+' Some of the players should be human!');
      [*] = ;
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      MapExecuteState('CheckHumanPlayer');
      [*] = ;      if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;      begin
      [*] = ;         if (not gBoolRegister_InBattle) and (gBoolRegister_IsHumanPlayer or gBoolRegister_IsAutoBattle) then
      [*] = ;           GUIExecuteState('VVK.map.StartTacticalBattle')
      [*] = ;         else
      [*] = ;            MapExecuteState('bat.AddPlayers');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         Assert((gIntRegister_CurGameMode = gc_GameModeTactics),_log_name+' Unknown game mode');
      [*] = ;         MapExecuteState('bat.AddPlayers');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //IntRegister0 := gIntRegister_BattleDefendArmy;
      [*] = ;   //IntRegister1 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;   //ExecuteState('StartBattleWithArmy');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

