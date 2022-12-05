section.begin
   Name = DoProgressGUI
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var dc,i: Integer;
      [*] = ;var timer_str : String;
      [*] = ;
      [*] = ;if (not GetProgressingPauseMode())  then
      [*] = ;begin
      [*] = ;   var elmSettingsHandle : Integer = _gui_GetWindow('Settings');
      [*] = ;   if (not ((elmSettingsHandle<>0) and GetGUIElementVisible(elmSettingsHandle))) then
      [*] = ;      GUIExecuteState('DoBlendLighting');
      [*] = ;end;
      [*] = ;  
      [*] = ;GUIExecuteState('DoProgressMusic');
      [*] = ;
      [*] = ;GUIExecuteState('VVK.DoProgressGUI');
      [*] = ;
      [*] = ;timer_str := GetValueByName(cGUISwitchModeTimerName);
      [*] = ;dc := _sa_GetNum(timer_str);
      [*] = ;if dc > 2 then
      [*] = ;begin
      [*] = ;   var mode : Integer;
      [*] = ;   var state_params,temp_str : String;
      [*] = ;   var time1 : Float;
      [*] = ;
      [*] = ;   mode := _sa_GetAsInt(timer_str,0);
      [*] = ;   if mode = gc_gui_ModeNone then
      [*] = ;      SetValueByName(cGUISwitchModeTimerName,'')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      time1 := _sa_GetAsFloat(timer_str,1);
      [*] = ;      if GetGameTime() > time1 then
      [*] = ;      begin
      [*] = ;         state_params := '';
      [*] = ;         for i := 3 to dc-1 do
      [*] = ;         begin
      [*] = ;            _sa_Get(timer_str,i,temp_str);
      [*] = ;            _sa_Add(state_params,temp_str);
      [*] = ;         end;
      [*] = ;
      [*] = ;         time1 := _sa_GetAsFloat(timer_str,2);
      [*] = ;         SetValueByName(cGUISwitchModeTimerName,'');
      [*] = ;         i := gIntRegister_GUIShardGameMode;
      [*] = ;
      [*] = ;         if i <> mode then
      [*] = ;         begin
      [*] = ;            gIntRegister_GUIShardGameMode := mode;
      [*] = ;            IntRegister0 := 1;
      [*] = ;            IntRegister1 := i;
      [*] = ;            IntRegister2 := mode;
      [*] = ;            StringRegister0 := state_params;
      [*] = ;            FloatRegister0 := time1;
      [*] = ;            GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := 2;
      [*] = ;         IntRegister1 := i;
      [*] = ;         IntRegister2 := mode;
      [*] = ;         StringRegister0 := state_params;
      [*] = ;         FloatRegister0 := time1;
      [*] = ;         GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;
      [*] = ;         IntRegister0 := 3;
      [*] = ;         IntRegister1 := i;
      [*] = ;         IntRegister2 := mode;
      [*] = ;         StringRegister0 := state_params;
      [*] = ;         FloatRegister0 := time1;
      [*] = ;         GUIExecuteState('VVK.ControlGameModeChange');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('vvk.lan.OnProgressGUI');
      [*] = ;
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeStrategy then //strategic mode
      [*] = ;   GUIExecuteState('map.DoProgressGUI')
      [*] = ;else
      [*] = ;begin
      [*] = ;   if gIntRegister_CurGameMode = gc_GameModeTactics then //tactic mode
      [*] = ;      GUIExecuteState('battle.DoProgressGUI');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIMapChooseHeroProvince<>0) then
      [*] = ;begin
      [*] = ;   if _log then _log_gui('gIntRegister_GUIMapChooseHeroProvince = ' + IntToStr(gIntRegister_GUIMapChooseHeroProvince));
      [*] = ;   IntRegister0 := gIntRegister_GUIMapChooseHeroProvince;
      [*] = ;   BoolRegister0 := gBoolRegister_GUIMapShowChooseDefender;
      [*] = ;   GUIExecuteState('map.CreateChooseHeroWindow');
      [*] = ;
      [*] = ;   gIntRegister_GUIMapChooseHeroProvince := 0;
      [*] = ;   gBoolRegister_GUIMapShowChooseDefender := false;
      [*] = ;end;
      [*] = ;
      [*] = ;{if (gc_expoVersion=1) and (gIntRegister_CurDemoMode=2) and (gIntRegister_DemoQueryBattle=0) and (_gui_GetWindow('queryWindow')=0) then
      [*] = ;begin
      [*] = ;   var seed : Integer = gGame.seed;
      [*] = ;   case seed of
      [*] = ;      8994, 1000, 1020 : gIntRegister_DemoQueryBattle := 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gc_demoVersion=1) and (gIntRegister_CurDemoMode>0) then
      [*] = ;begin
      [*] = ;   var queryWindow : Integer = _gui_GetWindow('queryWindow');
      [*] = ;
      [*] = ;   if (gIntRegister_CurDemoMode=1) and (gIntRegister_DemoQueryMap=0) and (not GetGUIElementVisible(queryWindow)) then // strategic
      [*] = ;   begin
      [*] = ;      StringRegister0 := '12008';
      [*] = ;      GUIExecuteState('map.RequestQueryWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gIntRegister_CurDemoMode=2) and (gIntRegister_DemoQueryBattle=0) and (not GetGUIElementVisible(queryWindow)) then // battle
      [*] = ;   begin
      [*] = ;      var seed : Integer = gGame.seed;
      [*] = ;      case seed of
      [*] = ;         8994 : begin
      [*] = ;            if (GetUserIntValue('DemoQueryBattle1')=0) then
      [*] = ;            StringRegister0 := '12101'
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               StringRegister0 := '';
      [*] = ;               gIntRegister_DemoQueryBattle := 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         1000 : begin
      [*] = ;            if (GetUserIntValue('DemoQueryBattle2')=0) then
      [*] = ;            StringRegister0 := '12102'
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               StringRegister0 := '';
      [*] = ;               gIntRegister_DemoQueryBattle := 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         1020 : begin
      [*] = ;            if (GetUserIntValue('DemoQueryBattle3')=0) then
      [*] = ;            StringRegister0 := '12103'
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               StringRegister0 := '';
      [*] = ;               gIntRegister_DemoQueryBattle := 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         StringRegister0 := '';
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (StringRegister0<>'') then
      [*] = ;      begin
      [*] = ;         if _log then _log_gui('seed = '+IntToStr(seed) + ' StringRegister0 = '+StringRegister0);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;if (gBoolRegister_GUIBattleResultWindow) and (_gui_GetWindow('battle_results')=0) then
      [*] = ;begin
      [*] = ;   if (GetFloatValueByName('guiBattleResultWindowDelay')=0) then
      [*] = ;   begin
      [*] = ;      SetFloatValueByName('guiBattleResultWindowDelay', GetGameTime());
      [*] = ;      //setting gBoolRegister_GUIBattleResultWindow to NULL in CloseResultWindow
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      const cBattleResultDelay = 1;
      [*] = ;
      [*] = ;      var guiBattleResultWindowDelay : Float = GetFloatValueByName('guiBattleResultWindowDelay');
      [*] = ;
      [*] = ;      if (gBoolRegister_QuickBattle) or ((guiBattleResultWindowDelay+cBattleResultDelay)<GetGameTime()) then
      [*] = ;      begin
      [*] = ;         if _log then _log_gui('guiBattleResultWindowDelay create result window');
      [*] = ;         SetFloatValueByName('guiBattleResultWindowDelay', 0);
      [*] = ;         GUIExecuteState('battle.CreateResultWindow');
      [*] = ;
      [*] = ;         if (_misc_IsLanBattle()) and (LanMyInfoID() = gIntRegsiter_LanBatServerID) then
      [*] = ;         begin
      [*] = ;            var winPlHandle, pid, k : Integer;
      [*] = ;
      [*] = ;            MapExecuteState('bat.GetWinPlayerHandle');
      [*] = ;            winPlHandle := IntRegister0;
      [*] = ;
      [*] = ;            if (winPlHandle=GetPlayerHandleInterfaceIO()) then
      [*] = ;            begin
      [*] = ;               k := 1;
      [*] = ;               pid := gc_LAN_MASTERWIN;
      [*] = ;               // for lan sync and further processing
      [*] = ;               //if (gIntRegister_BattleDefendHeroHandle <> 0) then
      [*] = ;               //   SetGameObjectBoolValueIndByHandle(gIntRegister_BattleDefendHeroHandle, gc_map_GOStack_MapUnit_bIsDead, true);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               k := -1;
      [*] = ;               pid := gc_LAN_CLIENTWIN;
      [*] = ;            end;
      [*] = ;
      [*] = ;            _lan_LanSendParserToEnemy( pid, _pars_ParserEmpty());
      [*] = ;
      [*] = ;            if (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;            begin
      [*] = ;               LanSrvSetClientScore(LanMyInfoID(), k);
      [*] = ;               LanSrvSetClientScore(_inet_GetLanEnemyID(), -1*k);
      [*] = ;               LanPublicServerCloseSession();
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_GUIStartup then
      [*] = ;begin
      [*] = ;   var ph,n,j : Integer;
      [*] = ;   var s : String;
      [*] = ;
      [*] = ;   gBoolRegister_GUIStartup := false;
      [*] = ;   // adding inner buildings now for all players since all gfx init is completed
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      ph := GetPlayerHandleByIndex(i);
      [*] = ;      s := ParserGetValueByKeyByHandle(ParserSelectPlayer(ph),'PendingInnerBuildings');
      [*] = ;      if s <> '' then
      [*] = ;      begin
      [*] = ;         n := _sa_GetNum(s);
      [*] = ;         for j := 0 to n-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := _sa_GetAsInt(s,j);
      [*] = ;            if IntRegister0 <> 0 then
      [*] = ;               PlayerExecuteStateByHandle(ph, 'AddInnerBuild');
      [*] = ;         end;
      [*] = ;         ParserSetValueByKeyByHandle(ParserSelectPlayer(ph),'PendingInnerBuildings','');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIProgressOnceOnGUIDoCreate) then
      [*] = ;begin
      [*] = ;   if gProfile.simplegraphics then
      [*] = ;      _actor_CheckSimplifiedGraphics();
      [*] = ;   //_gui_UpdateSettingsLowest(gProfile.settingslowest);
      [*] = ;   gBoolRegister_GUIProgressOnceOnGUIDoCreate := False;
      [*] = ;end;
      [*] = ;
      [*] = ;//_gui_ClampingMouseToScreen();
   struct.end
section.end

