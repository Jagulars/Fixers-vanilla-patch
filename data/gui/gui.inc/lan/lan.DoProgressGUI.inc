section.begin
   Name = lan.DoProgressGUI
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\LAN\LAN.DOPROGRESSGUI';
      [*] = ;var _log_trace : Integer = $1;
      [*] = ;// lan tactical battle between humans ONLY!! (_misc_IsLanBattle() == true)
      [*] = ;
      [*] = ;var lastLanPing : Float = GetFloatValueByName('LastLanPing');
      [*] = ;var i,j : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if (lastLanPing <> 0) and ((lastLanPing+gc_PingInterval)<GetCurrentTime()) then
      [*] = ;begin
      [*] = ;   _lan_LanSendParserToEnemy( gc_LAN_DUMP, _pars_ParserEmpty());
      [*] = ;   SetFloatValueByName('LastLanPing', GetCurrentTime());
      [*] = ;end;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'CheckLose');
      [*] = ;var lose : Boolean = BoolRegister0;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;PlayerExecuteStateByHandle(enPlHandle, 'CheckLose');
      [*] = ;var enLose : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;if (not Lose) and (not enLose) and (not gBoolRegister_BattleEndBattle) and (gIntRegister_QuerySpellUsage=0) then
      [*] = ;begin
      [*] = ;   var curBattlePlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_BattleCurPlIndex);
      [*] = ;   if (myPlHandle=curBattlePlHandle) then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'IsAllActionsDone');
      [*] = ;      if BoolRegister0 and (_gv_GetBattleLock() = 0) then
      [*] = ;      begin
      [*] = ;         if (not gBoolRegister_GUIEndTurn) then
      [*] = ;            logi('lan.DoProgressGUI : IsAllActionsDone : gBoolRegister_GUIEndTurn := true');
      [*] = ;
      [*] = ;         if (LanMyInfoID = gIntRegsiter_LanBatClientID)then
      [*] = ;            gBoolRegister_LanClientEndTurn := True;
      [*] = ;         gBoolRegister_GUIEndTurn := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (_gv_GetBattleLock() = 0) then
      [*] = ;begin
      [*] = ;   var bError : Boolean = _inet_ExecuteLanSyncParser();
      [*] = ;   if (bError) then
      [*] = ;      ErrorLogI(_log_name+': bError : _inet_ExecuteLanSyncParser=True');
      [*] = ;
      [*] = ;   for i := GetCountOfPlayers()-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      if (GetPlayerRaceTagByHandle(plHandle)=gc_player_Units_RaceTag) then
      [*] = ;      begin
      [*] = ;         var goHandle : Integer;
      [*] = ;         for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            goHandle := GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;            if GetGameObjectVisibleByHandle(goHandle) then
      [*] = ;            begin
      [*] = ;               var bError : Boolean = _inet_ExecuteUnitLanSyncParser(goHandle);
      [*] = ;               if (bError) then
      [*] = ;                  ErrorLogI(_log_name+': bError : _inet_ExecuteUnitLanSyncParser=True');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (_gv_GetBattleLock() = 0) and (gIntRegister_LanSwitchToMasterTurn=gIntRegister_InetLanActionSyncEnum+1) then // sync enums pile up with each action as the battle progresses, gIntRegister_LanSwitchToMasterTurn is the sync enum when turn was passed
      [*] = ;begin
      [*] = ;   gIntRegister_InetLanActionSyncEnum := gIntRegister_InetLanActionSyncEnum+1;
      [*] = ;   gIntRegister_LanSwitchToMasterTurn := 0;
      [*] = ;   GUIExecuteState('lan.SwitchToMasterTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;if (_gv_GetBattleLock() = 0) and (gIntRegister_LanSwitchToClientTurn=gIntRegister_InetLanActionSyncEnum+1) then
      [*] = ;begin
      [*] = ;   gIntRegister_InetLanActionSyncEnum := gIntRegister_InetLanActionSyncEnum+1;
      [*] = ;   gIntRegister_LanSwitchToClientTurn := 0;
      [*] = ;   GUIExecuteState('lan.SwitchToClientTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end