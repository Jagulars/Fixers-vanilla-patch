section.begin
   Name = VVK.GameCommandsCore
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;   [0] - reload commands
      [*] = ;   [1] - register shortcuts (SR0 - list of modes, RET: IR0 - number of shortcuts registered)
      [*] = ;   [2] - register window state (IR1 - handle, SR0 - state, SR1 - attr, RET: BR0 - true if was already registered)
      [*] = ;   [3] - unregister window state (IR1 - handle, RET: BR0 - true if was already registered)
      [*] = ;   [4] - post command (SR0 - name, SR1 - cmd attr, SR2 - user attr, RET: IR0 - state)
      [*] = ;   [5] - check command (SR0 - name, SR1 - cmd attr, SR2 - user attr, RET: IR0 - state)
      [*] = ;   [6] - process command (SR0 - name, SR1 - cmd attr, SR2 - user attr, RET: IR0 - state)
      [*] = ;   [7] - get command hotkey (SR0 - name, SR1 - cmd attr, RET: SR0 - hotkey)
      [*] = ;   [8] - get command attributes (gc_gui_command_attr_ ) from command name (SR0)
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure ReloadCommands();
      [*] = ;begin
      [*] = ;   const cCommandsFileName = '.\data\gui\commands.cfg';
      [*] = ;
      [*] = ;   var pExtraData, pElems, pElem, i : Integer;
      [*] = ;
      [*] = ;   pExtraData := _misc_ParserGetOrCreateByKey('commands_cfg',true);
      [*] = ;   ParserLoadFromFile(cCommandsFileName);
      [*] = ;
      [*] = ;   pElems := ParserSelectByHandleByKey(pExtraData, 'Commands');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pElems)-1 do
      [*] = ;   begin
      [*] = ;      if i >= gc_gui_game_commands_max then
      [*] = ;         break;
      [*] = ;
      [*] = ;      pElem := ParserSelectByHandleByIndex(pElems, i);
      [*] = ;      gArr_gui_game_commands[i].id := ParserGetIntValueByKeyByHandle(pElem, 'ID');
      [*] = ;      gArr_gui_game_commands[i].scope := ParserGetValueByKeyByHandle(pElem, 'Scope');
      [*] = ;      gArr_gui_game_commands[i].name := StrToLowerCase(ParserGetValueByKeyByHandle(pElem,'Name'));
      [*] = ;      gArr_gui_game_commands[i].attr := ParserGetValueByKeyByHandle(pElem, 'Attr');
      [*] = ;      gArr_gui_game_commands[i].hotkey := ParserGetValueByKeyByHandle(pElem, 'Hotkey');
      [*] = ;   end;
      [*] = ;   gArr_gui_game_commands[i].id := -1;
      [*] = ;
      [*] = ;   Log('Commands reloaded. Total active commands: '+IntToStr(i));
      [*] = ;   _misc_ParserGetOrCreateByKey('commands_cfg',true);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RegisterShortcuts(modes : String);
      [*] = ;begin
      [*] = ;   var i,j,k,l,fnd,modes_no,no,hno,cmd_no : Integer;
      [*] = ;   var mode_names : array [0..$20] of String;
      [*] = ;   var temp_str,modes_i,temp_str2,temp_str3 : String;
      [*] = ;   var cmd_idx : array [0..gc_gui_game_commands_max] of Integer;
      [*] = ;
      [*] = ;   modes_no := _sa_GetNum(modes);
      [*] = ;   for i := 0 to modes_no-1 do
      [*] = ;   begin
      [*] = ;      _sa_Get(modes,i,mode_names[i]);
      [*] = ;   end;
      [*] = ;
      [*] = ;   cmd_no := 0;
      [*] = ;   i := 0;
      [*] = ;   while gArr_gui_game_commands[i].id > 0 do
      [*] = ;   begin
      [*] = ;      if gArr_gui_game_commands[i].hotkey <> '' then
      [*] = ;      begin
      [*] = ;         modes_i := gArr_gui_game_commands[i].scope;
      [*] = ;         no := _sa_GetNum_D(modes_i,$2c);
      [*] = ;         fnd := 0;
      [*] = ;         for [MAIN]j := 0 to no-1 do
      [*] = ;         begin
      [*] = ;            _sa_Get_D(modes_i,j,$2c,temp_str);
      [*] = ;            for k := 0 to modes_no-1 do
      [*] = ;            begin
      [*] = ;               if temp_str = mode_names[k] then
      [*] = ;               begin
      [*] = ;                  fnd := 1;
      [*] = ;                  break(MAIN);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if fnd <> 0 then
      [*] = ;         begin
      [*] = ;            cmd_idx[cmd_no] := i;
      [*] = ;            cmd_no := cmd_no + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      i := i + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   hno := 0;
      [*] = ;   for i := 0 to cmd_no-1 do
      [*] = ;   begin
      [*] = ;      no := _sa_GetNum_D(gArr_gui_game_commands[cmd_idx[i]].hotkey,$2c);
      [*] = ;      for j := 0 to no-1 do
      [*] = ;      begin
      [*] = ;         fnd := 0;
      [*] = ;         _sa_Get_D(gArr_gui_game_commands[cmd_idx[i]].hotkey,j,$2c,temp_str);
      [*] = ;         for k := 0 to hno-1 do
      [*] = ;         begin
      [*] = ;            if SameText(gArr_gui_game_commands_hotkeys[k].hotkey,temp_str) then
      [*] = ;            begin
      [*] = ;               l := gArr_gui_game_commands_hotkeys[k].cmd_no;
      [*] = ;               if l < gc_gui_game_commands_max_per_hotkey then
      [*] = ;               begin
      [*] = ;                  gArr_gui_game_commands_hotkeys[k].cmd[l] := cmd_idx[i];
      [*] = ;                  gArr_gui_game_commands_hotkeys[k].cmd_no := l + 1;
      [*] = ;               end;
      [*] = ;               fnd := 1;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if fnd = 0 then
      [*] = ;         begin
      [*] = ;            gArr_gui_game_commands_hotkeys[hno].id := gc_gui_command_hotkey_start_uid + hno;
      [*] = ;            gArr_gui_game_commands_hotkeys[hno].cmd[0] := cmd_idx[i];
      [*] = ;            gArr_gui_game_commands_hotkeys[hno].cmd_no := 1;
      [*] = ;            gArr_gui_game_commands_hotkeys[hno].hotkey := temp_str;
      [*] = ;            hno := hno + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gArr_gui_game_commands_hotkeys[hno].id := -1;
      [*] = ;
      [*] = ;   for i := 0 to hno-1 do
      [*] = ;   begin
      [*] = ;      _sa_Get(gArr_gui_game_commands_hotkeys[i].hotkey,0,temp_str);
      [*] = ;      temp_str2 := '';
      [*] = ;      _sa_Get(gArr_gui_game_commands_hotkeys[i].hotkey,1,temp_str2);
      [*] = ;      if temp_str2 = '' then
      [*] = ;         temp_str2 := 'spiUp';
      [*] = ;      temp_str3 := '';
      [*] = ;      for j := 0 to gArr_gui_game_commands_hotkeys[i].cmd_no-1 do
      [*] = ;      begin
      [*] = ;         temp_str3 := temp_str3 + gArr_gui_game_commands[gArr_gui_game_commands_hotkeys[i].cmd[j]].name+',';
      [*] = ;      end;
      [*] = ;      //Log('Shortcut keys: '+temp_str+', State: '+temp_str2+', ID: '+IntToStr(gArr_gui_game_commands_hotkeys[i].id-gc_gui_command_hotkey_start_uid)+', Cmd: '+temp_str3);
      [*] = ;      RegisterGUIShortcutIgnoreShift(True, 'CmdHotkey_'+IntToStr(i), temp_str, 'Shift+Ctrl+Alt', temp_str2, 'VVK.ProcessCommandsShortcuts', gArr_gui_game_commands_hotkeys[i].id);
      [*] = ;   end;
      [*] = ;   Log('Shortcuts for modes '+modes+' registered. Total shortcuts: '+IntToStr(hno));
      [*] = ;end;
      [*] = ;
      [*] = ;function RegisterWindowState(windowHandle : Integer;cmd_state : String;cmd_attr : String) : Boolean;
      [*] = ;begin
      [*] = ;   var whd : Integer;
      [*] = ;   var exists : Boolean;
      [*] = ;
      [*] = ;   if GetGUIElementParentByIndex(windowHandle) <> _gui_GetLayerI() then
      [*] = ;   begin
      [*] = ;      ErrorLog('Can attach command handler only to root windows.');
      [*] = ;      Result := false;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      whd := GetGUIElementIndexByNameParent(cRootWindowCommandName,windowHandle);
      [*] = ;      if whd = 0 then
      [*] = ;      begin
      [*] = ;         exists := false;
      [*] = ;         whd := AddNewElementByClassNameParent(cRootWindowCommandName, 'TOSWImageGuiControl', 0, windowHandle);
      [*] = ;         SetGUIElementMaterial(whd,gc_gui_material_blank_0);
      [*] = ;         SetGUIElementAlign(whd, gc_gui_align_parent_m.h,gc_gui_align_parent_m.v);
      [*] = ;         SetGUIElementAllPositionRect(whd,0,0,1,1);
      [*] = ;         SetGUIElementVisible(whd,false);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         exists := true;
      [*] = ;
      [*] = ;      SetGUIElementStringTag(whd,cmd_state+'#'+cmd_attr);
      [*] = ;      Result := exists;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function UnRegisterWindowState(windowHandle : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var whd : Integer;
      [*] = ;   var exists : Boolean;
      [*] = ;
      [*] = ;   if GetGUIElementParentByIndex(windowHandle) <> _gui_GetLayerI() then
      [*] = ;   begin
      [*] = ;      ErrorLog('Can remove command handler only from root windows.');
      [*] = ;      Result := false;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      whd := GetGUIElementIndexByNameParent(cRootWindowCommandName,windowHandle);
      [*] = ;      if whd <> 0 then
      [*] = ;      begin
      [*] = ;         RemoveGUIElement(whd);
      [*] = ;         exists := false;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         exists := true;
      [*] = ;
      [*] = ;      Result := exists;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function FindCommandIndex(cmd_name : String; cmd_attr : String) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var nm : String;
      [*] = ;   var attr : String;
      [*] = ;
      [*] = ;   nm := StrToLowerCase(cmd_name);
      [*] = ;   attr := StrToLowerCase(cmd_attr);
      [*] = ;   Result := -1;
      [*] = ;   i := 0;
      [*] = ;   while gArr_gui_game_commands[i].id > 0 do
      [*] = ;   begin
      [*] = ;      if ((gArr_gui_game_commands[i].name = nm) and (gArr_gui_game_commands[i].attr = attr))  then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;      i := i + 1;
      [*] = ;   end;
      [*] = ;   if Result = -1 then
      [*] = ;      ErrorLog('[GUI] Command '+cmd_name+', attr '+cmd_attr+' not found.');
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessCommandByIndex(cmd_idx : Integer; cmd_attr_ext : String; post_mode : Integer;var ret_str : String) : Integer;
      [*] = ;begin
      [*] = ;   var no,i,whd : Integer;
      [*] = ;   var temp_str,wnd_str,state_name,cmd_attr : String;
      [*] = ;
      [*] = ;   IntRegister2 := _gui_GetLayerI();
      [*] = ;   IntRegister0 := $101;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister3 := $ff;
      [*] = ;   GUIExecuteState('VVK.RootWindowOperations');
      [*] = ;   wnd_str := StringRegister0;
      [*] = ;   //if post_mode = 0 then
      [*] = ;   //   if _log then Log('Cmd: '+gArr_gui_game_commands[cmd_idx].name+', Wnd: '+wnd_str);
      [*] = ;
      [*] = ;   if _log then Log('NAME: '+gArr_gui_game_commands[cmd_idx].name+', CA: '+gArr_gui_game_commands[cmd_idx].attr);
      [*] = ;   Result := 0;
      [*] = ;   no := _sa_GetNum(wnd_str);
      [*] = ;   for i := 0 to no-1 do
      [*] = ;   begin
      [*] = ;      whd := _sa_GetAsInt(wnd_str,i);
      [*] = ;      temp_str := GetGUIElementStringTag(whd);
      [*] = ;      whd := GetGUIElementParentByIndex(whd);
      [*] = ;      _sa_Get_D(temp_str,0,$23,state_name);
      [*] = ;      _sa_Get_D(temp_str,1,$23,cmd_attr);
      [*] = ;      if post_mode = 0 then
      [*] = ;         if _log then Log(IntToStr(i)+' NAME: '+GetGUIElementNameByIndex(whd)+', STATE: '+state_name+', SA: '+cmd_attr+', UA: '+cmd_attr_ext);
      [*] = ;      StringRegister0 := gArr_gui_game_commands[cmd_idx].name;
      [*] = ;      StringRegister1 := gArr_gui_game_commands[cmd_idx].attr;
      [*] = ;      StringRegister2 := cmd_attr;
      [*] = ;      StringRegister3 := cmd_attr_ext;
      [*] = ;      IntRegister0 := post_mode;
      [*] = ;      IntRegister1 := gArr_gui_game_commands[cmd_idx].id;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := whd;
      [*] = ;      GUIExecuteState(state_name);
      [*] = ;      if ((IntRegister2 and $ff) <> 0)  then
      [*] = ;      begin
      [*] = ;         ret_str := StringRegister0;
      [*] = ;         Result := IntRegister2;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckCommandAvailability(cmd_name : String; cmd_attr : String; user_attr : String;var ret_str : String) : Integer;
      [*] = ;begin
      [*] = ;   var idx : Integer;
      [*] = ;
      [*] = ;   idx := FindCommandIndex(cmd_name,cmd_attr);
      [*] = ;   if idx <> -1 then
      [*] = ;      Result := ProcessCommandByIndex(idx,user_attr,1,ret_str)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if _log then Log('Command '+cmd_name+' A: '+cmd_attr+' not found.');
      [*] = ;      ret_str := '';
      [*] = ;      Result := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessCommand(cmd_name : String; cmd_attr : String; user_attr : String;var ret_str : String) : Integer;
      [*] = ;begin
      [*] = ;   var idx : Integer;
      [*] = ;
      [*] = ;   idx := FindCommandIndex(cmd_name,cmd_attr);
      [*] = ;   if idx <> -1 then
      [*] = ;      Result := ProcessCommandByIndex(idx,user_attr,0,ret_str)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ret_str := '';
      [*] = ;      Result := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetCommandAttributes( cmd : String ) : Integer ;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   if SubStr(cmd,1,1) = '.' then Result := Result or gc_gui_command_attr_system;
      [*] = ;   if SubStr(cmd,1,1) = '_' then Result := Result or gc_gui_command_attr_top;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var ret_str : String = '';
      [*] = ;
      [*] = ;if (GetIntValueByName('VVK_RT') and $20) <> 0 then
      [*] = ;   _log := true;
      [*] = ;case mode of
      [*] = ;   0 : ReloadCommands();
      [*] = ;   1 : RegisterShortcuts(StringRegister0);
      [*] = ;   2 : BoolRegister0 := RegisterWindowState(IntRegister1,StringRegister0,StringRegister1);
      [*] = ;   3 : BoolRegister0 := UnRegisterWindowState(IntRegister1);
      [*] = ;   4,6 : IntRegister0 := ProcessCommand(StringRegister0,StringRegister1,StringRegister2,ret_str);
      [*] = ;   5 : IntRegister0 := CheckCommandAvailability(StringRegister0,StringRegister1,StringRegister2,ret_str);
      [*] = ;   7 : begin
      [*] = ;      var idx : Integer;
      [*] = ;
      [*] = ;      idx := FindCommandIndex(StringRegister0,StringRegister1);
      [*] = ;      if idx <> -1 then
      [*] = ;      begin
      [*] = ;         var temp_str,temp_str2,temp_str3,temp_str4 : String;
      [*] = ;         var i : Integer;
      [*] = ;         temp_str := gArr_gui_game_commands[idx].hotkey;
      [*] = ;         if temp_str <> '' then
      [*] = ;         begin
      [*] = ;            idx := _sa_GetNum_D(temp_str,$2c);
      [*] = ;            temp_str2 := '';
      [*] = ;            for i := 0 to idx-1 do
      [*] = ;            begin
      [*] = ;               _sa_Get_D(temp_str,i,$2c,temp_str3);
      [*] = ;               if temp_str2 <> '' then
      [*] = ;                  temp_str2 := temp_str2 + ', ';
      [*] = ;               _sa_Get(temp_str3,0,temp_str4);
      [*] = ;               temp_str2 := temp_str2 + temp_str4;
      [*] = ;            end;
      [*] = ;            ret_str := temp_str2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   8 : begin
      [*] = ;      IntRegister0 := GetCommandAttributes( StringRegister0 );
      [*] = ;   end;
      [*] = ;end;
      [*] = ;StringRegister0 := ret_str;
   struct.end
section.end

