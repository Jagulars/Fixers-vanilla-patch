section.begin
   Name = VVK.ToolsMenuCommands
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
      [*] = ;   'menutoolsbutton' : begin
      [*] = ;      case cmd_attr of
      [*] = ;         'mapeditor': begin
      [*] = ;            if (gBoolRegister_EditorAllowed) then
      [*] = ;            begin
      [*] = ;               tag := $20000+210;
      [*] = ;               if mode = 0 then
      [*] = ;               begin
      [*] = ;                  FadeMenu(0);
      [*] = ;                  _gui_DelayExecuteStateOneInstance('ShowMapEditorMenu',gc_gui_FadeTime0_2);
      [*] = ;               end
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := 0;
      [*] = ;         end;
      [*] = ;         'windowdesigner': begin
      [*] = ;            if gc_WindowDesignerEnabled then
      [*] = ;            begin
      [*] = ;               tag := $20000+237;
      [*] = ;               if mode = 0 then
      [*] = ;                  res := _cmd_Post('menuaction','windowdesigner',user_attr)
      [*] = ;               else
      [*] = ;                  res := _cmd_Check('menuaction','windowdesigner',user_attr);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               res := 0;
      [*] = ;         end;
      [*] = ;         'back': begin
      [*] = ;            tag := $20000+11;
      [*] = ;            if mode = 0 then
      [*] = ;            begin
      [*] = ;               FadeMenu(0);
      [*] = ;               GUIExecuteState('ShowMenu');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else begin
      [*] = ;            res := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'menumainbutton' : begin
      [*] = ;      if cmd_attr = 'back' then
      [*] = ;      begin
      [*] = ;         tag := $20000+11;
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            FadeMenu(0);
      [*] = ;            GUIExecuteState('ShowMenu');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         res := 0;
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
