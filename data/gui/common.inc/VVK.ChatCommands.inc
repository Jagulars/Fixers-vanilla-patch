section.begin
   Name = VVK.ChatCommands
   UsedFileName =
   Description : struct.begin
      [*] = ;IntRegister0 - execution mode (0-execute, 1-return status)
      [*] = ;IntRegister1 - command id
      [*] = ;IntRegister3 - (!) window handle to which this one attached
      [*] = ;StringRegister0 - command name
      [*] = ;StringRegister1 - command parameters (from cfg file)
      [*] = ;StringRegister2 - state parameters (passed in RegisterWindowState)
      [*] = ;StringRegister3 - extra state parameters (passed in PostCommand)
      [*] = ;RETURNS:
      [*] = ;   IntRegister2 - (&0xff: 1 - command available, stop execution, 2 - command unavailable, stop execution, 0 - not supported, continue execution)
      [*] = ;                  high 24 bits are for user defined check availability attributes!
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;function IsChatActive() : Boolean;
      [*] = ;begin
      [*] = ;   if (_gui_GetLayerExt(cChatLayer,0) <> 0) and (GetGUIElementVisible(_gui_GetLayerExt(cChatLayer,0))) then
      [*] = ;      Result := true
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;var attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var res : Integer;
      [*] = ;
      [*] = ;if (cmd = '.generalconsole') then
      [*] = ;begin
      [*] = ;   if (not IsChatActive()) then
      [*] = ;      res := 1
      [*] = ;   else
      [*] = ;      res := 0;
      [*] = ;   if (mode = 0) and (res = 1) then
      [*] = ;   begin
      [*] = ;      GUIExecuteState('SwitchToChat');
      [*] = ;   end;
      [*] = ;   IntRegister2 := res;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if cmd = 'generalconsoleclose' then
      [*] = ;begin
      [*] = ;   if IsChatActive() then
      [*] = ;   begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         SetValueByName('Status','shortcut');
      [*] = ;         SetValueByName('Key','escape');
      [*] = ;         GUIExecuteState(attr);
      [*] = ;      end;
      [*] = ;      IntRegister2 := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      IntRegister2 := 0;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if cmd = '.generalconsoleexitgame' then
      [*] = ;begin
      [*] = ;   if mode = 0 then
      [*] = ;   begin
      [*] = ;      if user_attr <> '' then
      [*] = ;         _run_ExitGame()
      [*] = ;      else
      [*] = ;         _gui_ShowQuestionDialog('menu|57', '#.generalconsoleexitgame||1', 0, '', 0, True, False);
      [*] = ;   end;
      [*] = ;   IntRegister2 := 1;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (cmd = '.generalconsolesnapshot') then
      [*] = ;begin
      [*] = ;   if mode = 0 then
      [*] = ;   begin
      [*] = ;      var v : Boolean;
      [*] = ;
      [*] = ;      if StrToInt(StringRegister1) = 0 then
      [*] = ;         v := true
      [*] = ;      else
      [*] = ;         v := false;
      [*] = ;
      [*] = ;      CreateSnapShot(v);
      [*] = ;   end;
      [*] = ;   IntRegister2 := 1;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (cmd = '.generalconsolesteamupdate') then
      [*] = ;begin
      [*] = ;   var r : Integer;
      [*] = ;
      [*] = ;   if not _achievement_IsSteamAvailable() then
      [*] = ;      r := 2
      [*] = ;   else
      [*] = ;      r := 1;
      [*] = ;
      [*] = ;   if (mode = 0) and (r <> 2) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 4;
      [*] = ;      GUIExecuteState('VVK.AchievementsCore');
      [*] = ;   end;
      [*] = ;   IntRegister2 := r;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if IsChatActive() then
      [*] = ;begin
      [*] = ;   if cmd = 'generalconsolereturn' then
      [*] = ;   begin
      [*] = ;      if mode = 0 then
      [*] = ;      begin
      [*] = ;         SetValueByName('Status','shortcut');
      [*] = ;         SetValueByName('Key','return');
      [*] = ;         GUIExecuteState(attr);
      [*] = ;      end;
      [*] = ;      IntRegister2 := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if ((_cmd_GetAttributes(cmd) and gc_gui_command_attr_system) <> 0) then
      [*] = ;         IntRegister2 := 0
      [*] = ;      else
      [*] = ;         IntRegister2 := 2;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;   IntRegister2 := 0;
   struct.end
section.end
