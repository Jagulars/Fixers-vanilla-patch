section.begin
   Name = VVK.ProcessCommandsShortcuts
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;//var ret_str : String;
      [*] = ;
      [*] = ;if (GetIntValueByName('VVK_RT') and $40) <> 0 then
      [*] = ;   _log := true;
      [*] = ;if (tag >= gc_gui_command_hotkey_start_uid) and (tag < (gc_gui_command_hotkey_start_uid+gc_gui_game_commands_max)) then
      [*] = ;begin
      [*] = ;   tag := tag - gc_gui_command_hotkey_start_uid;
      [*] = ;   if _log then _log_Values('CMD_TAG|NO',tag,gArr_gui_game_commands_hotkeys[tag].cmd_no,0,0,0,0);
      [*] = ;   if _log then _log_Gui('KEY: '+gArr_gui_game_commands_hotkeys[tag].hotkey);
      [*] = ;   
      [*] = ;   // always override hotkeys if writing a chat message, 
      [*] = ;   var focusedHnd : Integer = GetGUIFocusedElementHandle();
      [*] = ;   if (focusedHnd <> 0) and (focusedHnd = _gui_GetWindow('internetshell.rightpanel.chat.chatinput.text')) then 
      [*] = ;   begin
      [*] = ;      SetValueByName('Status','shortcut');
      [*] = ;      var hotkey : String = gArr_gui_game_commands_hotkeys[tag].hotkey;
      [*] = ;      if (hotkey = 'Return') or (hotkey = 'Escape') then
      [*] = ;         GUIExecuteState('EvLanShellChat');
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if gArr_gui_game_commands_hotkeys[tag].cmd_no = 1 then
      [*] = ;   begin
      [*] = ;      tag := gArr_gui_game_commands_hotkeys[tag].cmd[0];
      [*] = ;      if _log then _log_Gui('REAL CMD NAME: '+gArr_gui_game_commands[tag].name);
      [*] = ;      _cmd_Process(gArr_gui_game_commands[tag].name,gArr_gui_game_commands[tag].attr,'');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var no,i,j,cmd_idx,fnd,whd,res,cmd_no1,cmd_no2 : Integer;
      [*] = ;      var temp_str,wnd_str,state_name,cmd_attr : String;
      [*] = ;      var cmd_idx1 : array [0..gc_gui_game_commands_max_per_hotkey] of Integer;
      [*] = ;      var cmd_idx2 : array [0..gc_gui_game_commands_max_per_hotkey] of Integer;
      [*] = ;
      [*] = ;      IntRegister2 := _gui_GetLayerI();
      [*] = ;      IntRegister0 := $101;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister3 := $ff;
      [*] = ;      GUIExecuteState('VVK.RootWindowOperations');
      [*] = ;      wnd_str := StringRegister0;
      [*] = ;
      [*] = ;      for j := 0 to gArr_gui_game_commands_hotkeys[tag].cmd_no-1 do
      [*] = ;         cmd_idx1[j] := gArr_gui_game_commands_hotkeys[tag].cmd[j];
      [*] = ;      cmd_no1 := gArr_gui_game_commands_hotkeys[tag].cmd_no;
      [*] = ;      no := _sa_GetNum(wnd_str);
      [*] = ;      if _log then _log_Values('WND_NO|TAG',no,tag,0,0,0,0);
      [*] = ;      for i := 0 to no-1 do
      [*] = ;      begin
      [*] = ;         if _log then _log_Gui(IntToStr(i)+' Name: '+GetGUIElementNameByIndex(GetGUIElementParentByIndex(_sa_GetAsInt(wnd_str,i)))+', CmdNo: '+IntToStr(gArr_gui_game_commands_hotkeys[tag].cmd_no));
      [*] = ;         whd := _sa_GetAsInt(wnd_str,i);
      [*] = ;         temp_str := GetGUIElementStringTag(whd);
      [*] = ;         whd := GetGUIElementParentByIndex(whd);
      [*] = ;         _sa_Get_D(temp_str,0,$23,state_name);
      [*] = ;         _sa_Get_D(temp_str,1,$23,cmd_attr);
      [*] = ;         fnd := 0;
      [*] = ;         cmd_no2 := 0;
      [*] = ;         for j := 0 to cmd_no1-1 do
      [*] = ;         begin
      [*] = ;            cmd_idx := cmd_idx1[j];
      [*] = ;            if _log then _log_Gui('   '+gArr_gui_game_commands[cmd_idx].name+', A: '+cmd_attr);
      [*] = ;            StringRegister0 := gArr_gui_game_commands[cmd_idx].name;
      [*] = ;            StringRegister1 := gArr_gui_game_commands[cmd_idx].attr;
      [*] = ;            StringRegister2 := cmd_attr;
      [*] = ;            StringRegister3 := '';
      [*] = ;            IntRegister0 := 1;
      [*] = ;            IntRegister1 := gArr_gui_game_commands[cmd_idx].id;
      [*] = ;            IntRegister2 := 0;
      [*] = ;            IntRegister3 := whd;
      [*] = ;            GUIExecuteState(state_name);
      [*] = ;            if _log then _log_Values('____R',IntRegister2,0,0,0,0,0);
      [*] = ;            res := (IntRegister2 and $ff);
      [*] = ;            if (res <> 0)  then
      [*] = ;            begin
      [*] = ;               if res = 1 then
      [*] = ;               begin
      [*] = ;                  fnd := 1;
      [*] = ;                  StringRegister0 := gArr_gui_game_commands[cmd_idx].name;
      [*] = ;                  StringRegister1 := gArr_gui_game_commands[cmd_idx].attr;
      [*] = ;                  StringRegister2 := cmd_attr;
      [*] = ;                  StringRegister3 := '';
      [*] = ;                  IntRegister0 := 0;
      [*] = ;                  IntRegister1 := gArr_gui_game_commands[cmd_idx].id;
      [*] = ;                  IntRegister2 := 0;
      [*] = ;                  IntRegister3 := whd;
      [*] = ;                  GUIExecuteState(state_name);
      [*] = ;                  GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               cmd_idx2[cmd_no2] := cmd_idx;
      [*] = ;               cmd_no2 := cmd_no2 + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (fnd = 1) or (cmd_no2 = 0) then
      [*] = ;            break;
      [*] = ;         for j := 0 to cmd_no2-1 do
      [*] = ;            cmd_idx1[j] := cmd_idx2[j];
      [*] = ;         cmd_no1 := cmd_no2;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

