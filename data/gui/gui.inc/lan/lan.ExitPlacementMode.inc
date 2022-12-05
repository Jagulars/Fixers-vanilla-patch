section.begin
   Name = lan.ExitPlacementMode
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;if _misc_IsLanBattle() then
      [*] = ;begin
      [*] = ;   if (LanMyInfoID() = gIntRegsiter_LanBatServerID) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_InetLanTurn=-2) then
      [*] = ;      begin
      [*] = ;         if _log then _Log_lan('lan.ExitPlacementMode : gIntRegister_InetLanTurn=-2 : master start game');
      [*] = ;         
      [*] = ;         var pLan : Integer = _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;         _lan_LanSendParserToEnemy(gc_LAN_EXITPLACEMENTMODE, pLan);
      [*] = ;         
      [*] = ;         _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.EXITPLACEMENTMODE');
      [*] = ;            
      [*] = ;         SetPlayerBoolValueIndByHandle(GetPlayerHandleByName(gc_battle_attackPlayerName), gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;         SetPlayerBoolValueIndByHandle(GetPlayerHandleByName(gc_battle_defendPlayerName), gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;         
      [*] = ;         MapExecuteState('bat.CheckSabotage');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if _log then _Log_lan('lan.ExitPlacementMode : gIntRegister_InetLanTurn=-1 : master send client placement');
      [*] = ;         _lan_timer_Arm(gc_lt_placement,0,true);
      [*] = ;         
      [*] = ;         var pLan : Integer = _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;         _lan_LanSendParserToEnemy( gc_LAN_CLIENTPLACEMENT, pLan);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      _lan_timer_Arm(gc_lt_placement,0,true);
      [*] = ;         
      [*] = ;      var pLan : Integer = _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;      _lan_LanSendParserToEnemy(gc_LAN_CLIENTPLACEMENTREADY, pLan);
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

