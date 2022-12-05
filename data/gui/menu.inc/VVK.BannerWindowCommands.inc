section.begin
   Name = VVK.BannerWindowCommands
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
      [*] = ;      str: text resource section and name split by # sign, or empty string if old scheme (menu#(tag&0x7fff)) should be used
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\VVK.BANNERWINDOWCOMMANDS';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var cmd_attr : String = StringRegister1;
      [*] = ;var reg_attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var res,i,whd,bhd,thd,posx : Integer;
      [*] = ;var ret_str,temp_str : String;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;res := 0;
      [*] = ;ret_str := '';
      [*] = ;
      [*] = ;case cmd of
      [*] = ;   '.menushowbanner' : begin
      [*] = ;      if _log then _log_gui('UA: '+user_attr);
      [*] = ;      whd := _gui_GetWindow(cBaseAdsWindowName);
      [*] = ;      if whd <> 0 then
      [*] = ;      begin
      [*] = ;         if cmd_attr <> '' then
      [*] = ;         begin
      [*] = ;            case cmd_attr of
      [*] = ;               'next' : user_attr := IntToStr($10000);
      [*] = ;               'prev' : user_attr := IntToStr(-$10000);
      [*] = ;               'action' : user_attr := IntToStr(-$ffff);
      [*] = ;               else user_attr := IntToStr($ffff);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         res := 1;
      [*] = ;         if mode = 0 then
      [*] = ;         begin
      [*] = ;            var no,prev_no,new_no : Integer;
      [*] = ;
      [*] = ;            temp_str := GetGUIElementStringTag(whd);
      [*] = ;            no := GetGUIElementTag(whd);
      [*] = ;            prev_no := _sa_GetAsInt(temp_str,0);
      [*] = ;            new_no := StrToInt(user_attr);
      [*] = ;            case new_no of
      [*] = ;               $ffff : begin // random
      [*] = ;                  if no > 1 then
      [*] = ;                  begin
      [*] = ;                     new_no := Round(RandomExt()*(no-1));
      [*] = ;                     while (new_no = prev_no) do
      [*] = ;                        new_no := Round(RandomExt()*(no-1));
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     new_no := 0;
      [*] = ;               end;
      [*] = ;               -$10000 : begin
      [*] = ;                  new_no := prev_no - 1;
      [*] = ;                  if new_no < 0 then
      [*] = ;                     new_no := no-1;
      [*] = ;               end;
      [*] = ;               $10000 : begin
      [*] = ;                  new_no := prev_no + 1;
      [*] = ;                  if new_no >= no then
      [*] = ;                     new_no := 0;
      [*] = ;               end;
      [*] = ;               -$ffff : begin
      [*] = ;               end;
      [*] = ;               else begin
      [*] = ;                  if new_no < 0 then
      [*] = ;                     new_no := 0
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if new_no >= no then
      [*] = ;                        new_no := no-1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if new_no = -$ffff then
      [*] = ;            begin
      [*] = ;               bhd := GetGUIElementIndexByNameParent('banner_'+IntToStr(prev_no),whd);
      [*] = ;               if _log then _log_values('CBANNER',prev_no,0,0,0,0,0);
      [*] = ;               if bhd <> 0 then
      [*] = ;               begin
      [*] = ;                  var tag : String = GetGUIElementStringTag(bhd);
      [*] = ;
      [*] = ;                  i := _sa_GetAsInt(tag,1);
      [*] = ;                  _sa_Get(tag,3,temp_str);
      [*] = ;                  if _log then _log_gui('EXT_URL['+IntToStr(i)+','+IntToStr(_sa_GetAsInt(tag,2))+']: '+temp_str);
      [*] = ;                  if _sa_GetAsInt(tag,2) = 1 then
      [*] = ;                     _achievement_Trigger(gc_achiev_two_years,'');
      [*] = ;                  //_gui_ShowQuestionDialog('IDX: '+IntToStr(i)+gc_gui_BreakLine+temp_str, '#menumainbutton|exit|1', 0, '', 0, true, false);
      [*] = ;                  temp_str := '-1|'+IntToStr(i);
      [*] = ;                  i := SteamAPPTriggerAchievements(temp_str,gc_gui_DelimiterChar,gc_gui_QuoteChar);
      [*] = ;                  _log_values('RESULT',i,0,0,0,0,0);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               bhd := GetGUIElementIndexByNameParent('banner_'+IntToStr(new_no),whd);
      [*] = ;               SetGUIElementVisible(bhd,true);
      [*] = ;               if (prev_no >= 0) and (prev_no<>new_no) then
      [*] = ;               begin
      [*] = ;                  thd := GetGUIElementIndexByNameParent('banner_'+IntToStr(prev_no),whd);
      [*] = ;                  SetGUIElementVisible(thd,false);
      [*] = ;               end;
      [*] = ;               //thd := _gui_GetWindow('main_menu');
      [*] = ;               //if thd <> 0 then
      [*] = ;               //   posx := GetGUIElementPositionX(thd)
      [*] = ;               //else
      [*] = ;                  posx := GetViewerWidth div 4;//GetGUIElementWidth(whd);
      [*] = ;               posx := (posx-GetGUIElementWidth(bhd)) div 2;
      [*] = ;               if _log then _log_Values('POSX|WHD|BHD|WHDY',posx,GetGUIElementWidth(whd),GetGUIElementWidth(bhd),GetGUIElementPositionY(whd),0,0);
      [*] = ;               SetGUIElementPositionX(bhd,posx);
      [*] = ;               thd := GetGUIElementIndexByNameParent('banner_goto',whd);
      [*] = ;               SetGUIElementPositionX(thd,posx);
      [*] = ;               thd := GetGUIElementIndexByNameParent('button_prev',whd);
      [*] = ;               SetGUIElementPosition(thd,StrToInt(GetGUIElementStringTag(thd))+posx,(GetGUIElementHeight(bhd)-GetGUIElementHeight(thd)) div 2);
      [*] = ;               thd := GetGUIElementIndexByNameParent('button_next',whd);
      [*] = ;               SetGUIElementPosition(thd,(GetGUIElementWidth(bhd)+StrToInt(GetGUIElementStringTag(thd)))+posx,(GetGUIElementHeight(bhd)-GetGUIElementHeight(thd)) div 2);
      [*] = ;               thd := GetGUIElementIndexByNameParent('button_goto',whd);
      [*] = ;               SetGUIElementPosition(thd,((GetGUIElementWidth(bhd)-GetGUIElementWidth(thd)) div 2)+posx,(GetGUIElementHeight(bhd)+StrToInt(GetGUIElementStringTag(thd))));
      [*] = ;               temp_str := GetGUIElementStringTag(bhd);
      [*] = ;               thd := _sa_GetAsInt(temp_str,0);
      [*] = ;               temp_str := '';
      [*] = ;               _sa_AddAsInt(temp_str,new_no);
      [*] = ;               _sa_AddAsFloat(temp_str,GetGameTime()+(thd/1000));
      [*] = ;               SetGUIElementStringTag(whd,temp_str);
      [*] = ;               if _log then _log_values('CBANNER|PBANNER',new_no,prev_no,0,0,0,0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   '.generalshowachievements' : begin
      [*] = ;      if (not _achievement_IsPending()) then
      [*] = ;         res := 2
      [*] = ;      else
      [*] = ;         res := 1;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         _achievement_Process('VVK.ShowAchievement');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_str;
   struct.end
section.end

