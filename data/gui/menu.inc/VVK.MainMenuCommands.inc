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
      [*] = ;   _misc_FadeMenu('main_menu',hdr);
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
      [*] = ;if (mode = 0) and (not _misc_IsMenuVisible('main_menu')) and (user_attr = '') then
      [*] = ;begin
      [*] = ;   IntRegister2 := 0;
      [*] = ;   StringRegister0 := '';
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;case cmd of
      [*] = ;   'menumainbutton' : begin
      [*] = ;      case cmd_attr of
      [*] = ;         'campaign': begin
      [*] = ;            tag := $20000+1;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               FadeMenu(0);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowCampaign',gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'demo': begin
      [*] = ;            i := Max(gc_DemoVersion, gc_expoVersion);
      [*] = ;            if i <> 0 then
      [*] = ;            begin
      [*] = ;               tag := $20000+2;
      [*] = ;               if mode = 0 then
      [*] = ;               begin
      [*] = ;                  FadeMenu(0);
      [*] = ;                  _gui_DelayExecuteStateOneInstance('ShowDemo',gc_gui_FadeTime0_2);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := 0;
      [*] = ;         end;
      [*] = ;         'custom': begin
      [*] = ;            tag := $20000+3;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               FadeMenu(0);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowCustomGame',gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'multiplayer': begin
      [*] = ;            tag := $20000+4;
      [*] = ;            if mode = 0 then
      [*] = ;               res := _cmd_Post('menuaction','multiplayer',user_attr)
      [*] = ;            else
      [*] = ;               res := _cmd_Check('menuaction','multiplayer',user_attr);
      [*] = ;         end;
      [*] = ;         'profile': begin
      [*] = ;            tag := $20000+5;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _misc_AssignGlobalVars('gProfile', 'gProfileTmp');
      [*] = ;               _misc_FadeMenuExt('main_menu',4);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowProfile', gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'achievements': begin
      [*] = ;            tag := $20000+9;
      [*] = ;            lng_str := 'gui#achievements_plural';
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _misc_FadeMenuExt('main_menu',4);
      [*] = ;               IntRegister0 := 0;
      [*] = ;               IntRegister1 := 1;
      [*] = ;               GUIExecuteState('vvk.ShowAchievListModal');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'settings': begin
      [*] = ;            tag := $20000+6;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               _misc_FadeMenuExt('main_menu',4);
      [*] = ;               _gui_ShowSettingsDialog();
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'credits': begin
      [*] = ;            tag := $20000+7;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               FadeMenu(1);
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowCredits', gc_gui_FadeTime0_2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         'editor': begin
      [*] = ;            if (gBoolRegister_EditorAllowed) then
      [*] = ;            begin
      [*] = ;               tag := $20000+210;
      [*] = ;               if mode = 0 then
      [*] = ;               begin
      [*] = ;                  _editor_Init(gMapEditor);
      [*] = ;                  _editor_InitGUIEditor(gGUIEditor);
      [*] = ;                  _editor_InitEmptyMapEditor(gMapEditor.map);
      [*] = ;                  var bRun : Boolean = (GetGUIShiftStateCtrl);
      [*] = ;                  if (bRun) then
      [*] = ;                  _editor_LoadMapDataFromFile('');
      [*] = ;                  _editor_GenerateMap('', False, False, bRun);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := 0;
      [*] = ;         end;
      [*] = ;         'tools': begin
      [*] = ;            if gc_InGameModdingToolsEnabled then
      [*] = ;            begin
      [*] = ;               tag := $20000+236;
      [*] = ;               if mode = 0 then
      [*] = ;               begin
      [*] = ;                  FadeMenu(0);
      [*] = ;                  _gui_DelayExecuteStateOneInstance('ShowTools',gc_gui_FadeTime0_2);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := 0;
      [*] = ;         end;
      [*] = ;         'exit': begin
      [*] = ;            tag := $20000+8;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               if user_attr <> '' then
      [*] = ;               begin
      [*] = ;                  FadeMenu(1);
      [*] = ;                  StringRegister0 := 'guiDoRunExitGame';
      [*] = ;                  FloatRegister0 := gc_gui_FadeTime0_6;
      [*] = ;                  GUIExecuteState('FadeIn');
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  _gui_ShowQuestionDialog('menu|57', '#menumainbutton|exit|1', 0, '', 0, true, false);
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
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_str;
   struct.end
section.end

