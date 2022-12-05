section.begin
   Name = VVK.MainMenuCommands
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
      [*] = ;   StringRegister0 - string array
      [*] = ;      int: element tag
      [*] = ;      int: button extra status (1 - show as checked)
      [*] = ;      str: text reource section and name split by # sign, or empty string if old scheme (menu#(tag&0x7fff)) should be used
   struct.end
   Code : struct.begin
      [*] = ;procedure FadeMenu(hdr : Integer);
      [*] = ;begin
      [*] = ;   _misc_FadeMenu('astral_menu',hdr);
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var cmd_attr : String = StringRegister1;
      [*] = ;var reg_attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var res,tag,tag_attr,i : Integer;
      [*] = ;var ret_str, lng_str: String;
      [*] = ;
      [*] = ;res := 1;
      [*] = ;ret_str := '';
      [*] = ;tag := 0;
      [*] = ;tag_attr := 0;
      [*] = ;lng_str := '';
      [*] = ;
      [*] = ;if ((mode = 0) and (not _misc_IsMenuVisible('astral_menu'))) or ((_cmd_GetAttributes(cmd) and gc_gui_command_attr_system) <> 0) or (SubStr(cmd,1,5) = 'debug') then
      [*] = ;begin
      [*] = ;   IntRegister2 := 0;
      [*] = ;   StringRegister0 := '';
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;case cmd of
      [*] = ;   'menumainbutton' : begin
      [*] = ;      case cmd_attr of
      [*] = ;         'continue': begin
      [*] = ;            tag := $20000+16;
      [*] = ;            if mode = 0 then
      [*] = ;               FadeMenu(1);
      [*] = ;         end;
      [*] = ;         'load': begin
      [*] = ;            tag := $20000+39;
      [*] = ;            if UserGetProfileSavesCount() = 0 then
      [*] = ;               res := 2;
      [*] = ;            if (mode = 0) and (res <> 2) then
      [*] = ;            begin
      [*] = ;               //FadeMenu(1);
      [*] = ;               _prof_SyncCustomsFolder(-1);
      [*] = ;               SetIntValueByName('loadMapMode', 0);
      [*] = ;               SetBoolValueByName('bLoadMapSkipApproval', False);
      [*] = ;               GUIExecuteState('ShowLoadMap');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'save': begin
      [*] = ;            tag := $20000+54;
      [*] = ;            if _cmd_CheckNF('menuisactionpossible','',cmd_attr) = 2 then
      [*] = ;               res := 2;
      [*] = ;            if (mode = 0) and (res = 1) then
      [*] = ;            begin
      [*] = ;               //FadeMenu(1);
      [*] = ;               _prof_SyncCustomsFolder(-1);
      [*] = ;               SetIntValueByName('saveMapMode',0);
      [*] = ;               SetBoolValueByName('bActiveSave',false);
      [*] = ;               GUIExecuteState('ShowSaveMap');
      [*] = ;               SetGUIElementFocusedHandle(_gui_GetWindow('SaveMap.filename.text'));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'settings': begin
      [*] = ;            tag := $20000+6;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               //FadeMenu(1);
      [*] = ;               _gui_ShowSettingsDialog();
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'achievements': begin
      [*] = ;            tag := $20000+9;
      [*] = ;            lng_str := 'gui#achievements_plural';
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 0;
      [*] = ;               IntRegister1 := 1;
      [*] = ;               GUIExecuteState('vvk.ShowAchievListModal');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'exit': begin
      [*] = ;            tag := $20000+18;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               FadeMenu(0);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowExit',gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'difficulty': begin
      [*] = ;            tag := $20000+104;
      [*] = ;            if _cmd_CheckNF('menuisactionpossible','',cmd_attr) = 2 then
      [*] = ;               res := 2;
      [*] = ;            if (mode = 0) and (res = 1) then
      [*] = ;            begin
      [*] = ;               FadeMenu(0);
      [*] = ;               gIntRegister_GUITutorialChooseDifficultyMode := 0;
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowChangeDifficulty',gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'genesismode': begin
      [*] = ;            tag := $20000+238;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               gMapSettingsTmp.genesismode := gMapSettings.genesismode;
      [*] = ;               StringRegister0 := 'Genesis Mode';
      [*] = ;               GUIExecuteState('CreateWindowFromParser');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else begin
      [*] = ;            res := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   else begin
      [*] = ;      res := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (res <> 0) and (tag <> 0) then
      [*] = ;begin
      [*] = ;   _sa_AddAsInt(ret_str,tag);
      [*] = ;   _sa_AddAsInt(ret_str,tag_attr);
      [*] = ;   _sa_Add(ret_str,lng_str);
      [*] = ;end;
      [*] = ;
      [*] = ;if (reg_attr <> '') and (res = 0) and (not StrExists(cmd,'mbdown')) and (not StrExists(cmd,'mbup')) then
      [*] = ;   res := 2;
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_str;
   struct.end
section.end
