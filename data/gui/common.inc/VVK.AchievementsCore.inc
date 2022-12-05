section.begin
   Name = VVK.AchievementsCore
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;[0] - trigger achievement with id in IntRegister1, if StringRegister0 is not empty then calls [1]
      [*] = ;[1] - process achievements queue, StringRegister0 - state name, this state will receive string array of pending achievements in StringRegister0,
      [*] = ;      if state returns IntRegister0 = 1 or original StringRegister0 is empty then steam handler will be called
      [*] = ;[2] - get list IN: BoolRegister0 = true if should use temp profile, RET: StringRegister0 - string array list of achievements, IntRegister0 - number
      [*] = ;[3] - display all received achievements with ids in a dialog window
      [*] = ;[4] - update all achievements on Steam and in profile for current profile
   struct.end
   Code : struct.begin
      [*] = ;const cMaxAchievements = $80;
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure GetProfilesRootPath(var dst_path : String);
      [*] = ;begin
      [*] = ;   var temp_str,temp_str2,temp_str3 : String;
      [*] = ;   var i,n : Integer;
      [*] = ;
      [*] = ;   dst_path := '';
      [*] = ;   temp_str := StrReplace(UserGetProfileFileNameByIndex(0),' ','?');
      [*] = ;   if _log then _log_Gui('Profile root: '+temp_str);
      [*] = ;   if (temp_str <> '') and (_sa_GetNum_D(temp_str,$5c) > 2) then
      [*] = ;   begin
      [*] = ;      n := _sa_GetNum_D(temp_str,$5c);
      [*] = ;      temp_str2 := '';
      [*] = ;      for i := 0 to n-3 do
      [*] = ;      begin
      [*] = ;         _sa_Get_D(temp_str,i,$5c,temp_str3);
      [*] = ;         _sa_Add_D(temp_str2,temp_str3,'\');
      [*] = ;      end;
      [*] = ;      _sa_Add_D(temp_str2,'rand.key','\');
      [*] = ;      if _log then _log_Gui('Rand file: '+temp_str2);
      [*] = ;      dst_path := StrReplace(temp_str2,'?',' ');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckSteam() : Boolean;
      [*] = ;begin
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   temp_str := '-2|0';
      [*] = ;   if SteamAPPTriggerAchievements(temp_str,gc_gui_DelimiterChar,gc_gui_QuoteChar) = 0 then
      [*] = ;      Result := false
      [*] = ;   else
      [*] = ;      Result := true;
      [*] = ;//   _misc_GetGameDataRootPath(temp_str);
      [*] = ;//   temp_str := temp_str+'steam_init.flg';
      [*] = ;//   if IsFileExists(temp_str) then
      [*] = ;//   begin
      [*] = ;//      DeleteFileStream(temp_str);
      [*] = ;//      Result := true;
      [*] = ;//   end
      [*] = ;//   else
      [*] = ;//      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetAchievementsList(use_tmp_profile : Boolean;var dst : String) : Integer;
      [*] = ;begin
      [*] = ;   var temp_str,a_str : String;
      [*] = ;   var i,n,ca : Integer;
      [*] = ;
      [*] = ;   Result := 0;
      [*] = ;   dst := '';
      [*] = ;   if use_tmp_profile then
      [*] = ;      a_str := gProfileTmp.achievements
      [*] = ;   else
      [*] = ;      a_str := gProfile.achievements;
      [*] = ;   n := _sa_GetNum(a_str);
      [*] = ;
      [*] = ;   if (n>0) and (a_str <> '') then
      [*] = ;   begin
      [*] = ;      Result := n;
      [*] = ;      temp_str := '';
      [*] = ;
      [*] = ;      for i := 0 to n-1 do
      [*] = ;      begin
      [*] = ;         ca := (_sa_GetAsInt(a_str,i) and $ffff) xor $EAD2;
      [*] = ;         _sa_AddAsInt(temp_str,ca);
      [*] = ;      end;
      [*] = ;      dst := temp_str;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessAchievements(state : String;force_update_mode : Integer);
      [*] = ;begin
      [*] = ;   var n : Integer;
      [*] = ;   var a_str : String;
      [*] = ;
      [*] = ;   if force_update_mode > 0 then
      [*] = ;      a_str := gProfile.achievements
      [*] = ;   else
      [*] = ;      a_str := gStrRegister_PendingAchievements;
      [*] = ;   n := _sa_GetNum(a_str);
      [*] = ;   if (n > 0) and (a_str <> '') then
      [*] = ;   begin
      [*] = ;      var ca_new : array [0..cMaxAchievements] of Integer;
      [*] = ;      var ca_curr : array [0..cMaxAchievements] of Integer;
      [*] = ;      var ca_no,i,j,f,a : Integer;
      [*] = ;      var temp_str : String;
      [*] = ;
      [*] = ;      ca_no := _sa_GetNum(gProfile.achievements);
      [*] = ;      if (ca_no > 0) and (gProfile.achievements <> '') and (force_update_mode = 0) then
      [*] = ;      begin
      [*] = ;         ca_no := min(ca_no,cMaxAchievements-1);
      [*] = ;         for i := 0 to ca_no-1 do
      [*] = ;            ca_curr[i] := (_sa_GetAsInt(gProfile.achievements,i) and $ffff);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ca_no := 0;
      [*] = ;      ca_curr[ca_no] := -1;
      [*] = ;      ca_no := 0;
      [*] = ;
      [*] = ;      for i := 0 to n-1 do
      [*] = ;      begin
      [*] = ;         a := (_sa_GetAsInt(a_str,i) and $ffff) xor $EAD2;
      [*] = ;         f := 0;
      [*] = ;         for j := 0 to cMaxAchievements-1 do
      [*] = ;         begin
      [*] = ;            if ca_curr[j] = -1 then
      [*] = ;               break;
      [*] = ;            if ca_curr[j] = a then
      [*] = ;            begin
      [*] = ;               f := 1;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if f = 0 then
      [*] = ;         begin
      [*] = ;            ca_new[ca_no] := (a xor $EAD2);
      [*] = ;            if force_update_mode > 0 then ca_new[ca_no] := a;
      [*] = ;            if GetLocaleTableListItemByID('achievements_e2', IntToStr(_achievement_GetTextID(ca_new[ca_no]))+'.name') <> '' then
      [*] = ;               ca_no := ca_no+1
      [*] = ;            else
      [*] = ;            begin
      [*] = ;                if _log then _log_Values('ACH_NOT_FOUND|N',_achievement_GetTextID(ca_new[ca_no]),ca_new[ca_no],0,0,0,0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if force_update_mode = 0 then
      [*] = ;         gStrRegister_PendingAchievements := '';
      [*] = ;
      [*] = ;      if ca_no > 0 then
      [*] = ;      begin
      [*] = ;         if force_update_mode > 0 then
      [*] = ;            temp_str := ''
      [*] = ;         else
      [*] = ;            temp_str := gProfile.achievements;
      [*] = ;         for i := 0 to ca_no-1 do
      [*] = ;            _sa_AddAsInt(temp_str,(ca_new[i] xor $EAD2) or ($CD0000));
      [*] = ;
      [*] = ;         gProfile.achievements := temp_str;
      [*] = ;         _prof_SaveUserProfile();
      [*] = ;         UserSaveProfile();
      [*] = ;         if state <> '' then
      [*] = ;         begin
      [*] = ;            temp_str := '';
      [*] = ;            for i := 0 to ca_no -1 do
      [*] = ;               _sa_AddAsInt(temp_str,ca_new[i]);
      [*] = ;
      [*] = ;            StringRegister0 := temp_str;
      [*] = ;            GUIExecuteState(state);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            IntRegister0 := 1;
      [*] = ;
      [*] = ;         if (IntRegister0 > 0) then
      [*] = ;         begin
      [*] = ;            temp_str := '';
      [*] = ;            for i := 0 to ca_no-1 do
      [*] = ;               _sa_AddAsInt(temp_str,(ca_new[i] xor $EAD2));
      [*] = ;            if CheckSteam() then
      [*] = ;            begin
      [*] = ;               SteamAPPTriggerAchievements(temp_str,gc_gui_DelimiterChar,gc_gui_QuoteChar);
      [*] = ;
      [*] = ;               {GetProfilesRootPath(temp_str);
      [*] = ;               if temp_str <> '' then
      [*] = ;               begin
      [*] = ;                  OpenFileStreamForWrite(temp_str);
      [*] = ;                  for i := 0 to ca_no-1 do
      [*] = ;                     FileStreamWriteInteger(ca_new[i] xor $EAD2);
      [*] = ;                  CloseFileStream();
      [*] = ;               end;}
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if _log then _log_gui('ACHIEV: '+temp_str);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DoTableTest(whd : Integer; font_handle : String; xpos : Integer; ypos : Integer; width : Integer);
      [*] = ;begin
      [*] = ;   var pos : TRectangle;
      [*] = ;   var w,h,i,j,th,fh : Integer;
      [*] = ;   var columns,text,temp_str : String;
      [*] = ;
      [*] = ;   GetGUIElementFontTextFormatRect(gc_gui_table_font_handle,gArrGUIFontSpacers[gc_gui_TableIdx_lc],w,h);
      [*] = ;   width := width-4*w;
      [*] = ;   if _log then _log_Values('WC|WS',w,width,0,0,0,0);
      [*] = ;
      [*] = ;   columns := '';
      [*] = ;   for i :=0 to 3 do
      [*] = ;   begin
      [*] = ;      width := width div 2;
      [*] = ;      _sa_AddAsInt(columns,width);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _sys_FillRect(pos,xpos,ypos,0,0);
      [*] = ;   th := GetGUIElementFontHeight(gc_gui_table_font_handle);
      [*] = ;   fh := GetGUIElementFontHeight(font_handle);
      [*] = ;
      [*] = ;   temp_str := '';
      [*] = ;   for i := 0 to 8 do
      [*] = ;      temp_str := temp_str + gArrGUIFontSpacers[gc_gui_TableIdx_lt+i]+gArrGUIFontSpacers[gc_gui_TableIdx_spacers_start+$10];
      [*] = ;   _gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;   pos.pos.y := pos.pos.y+th*6;
      [*] = ;   temp_str := '';
      [*] = ;   for i := 0 to $1f do
      [*] = ;      temp_str := temp_str + gArrGUIFontSpacers[gc_gui_TableIdx_lines_start+i]+gArrGUIFontSpacers[gc_gui_TableIdx_spacers_start+$10];
      [*] = ;   _gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;   pos.pos.y := pos.pos.y+th*6;
      [*] = ;
      [*] = ;   _gui_TableGetFrameString(columns,gc_gui_TableFrameTop,temp_str);
      [*] = ;   if _log then _log_Gui('F: '+temp_str);
      [*] = ;   _gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;   pos.pos.y := pos.pos.y+th;
      [*] = ;   for i := 0 to 20 do
      [*] = ;   begin
      [*] = ;      text := '';
      [*] = ;      for j := 0 to 3 do
      [*] = ;         _sa_Add(text,'"C'+IntToStr(j)+', R'+IntToStr(i)+'"');
      [*] = ;      _gui_TableFormatTextLine(font_handle,columns,text,temp_str);
      [*] = ;      _gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;      pos.pos.y := pos.pos.y+fh;
      [*] = ;      if (i = 20) then
      [*] = ;         _gui_TableGetFrameString(columns,gc_gui_TableFrameBottom,temp_str)
      [*] = ;      else
      [*] = ;         _gui_TableGetFrameString(columns,gc_gui_TableFrameCenter,temp_str);
      [*] = ;      _gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;      pos.pos.y := pos.pos.y+th;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var id : Integer = IntRegister1;
      [*] = ;var str_attr : String = StringRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   0 : begin
      [*] = ;      if ((gGame.gameType <> gc_GameTypeLanBattle) and (gGame.gameType <> gc_GameTypeLanShard)) and
      [*] = ;         (gGame.gameType <> gc_GameTypeHotseatBattle) and
      [*] = ;         ((gIntRegister_CurGameMode = gc_GameModeAstral) or (not gTutorial.map)) and (not gGame.sandbox) then
      [*] = ;      begin
      [*] = ;         var a_str : String;
      [*] = ;         var ca_curr : array [0..cMaxAchievements] of Integer;
      [*] = ;         var ca_no,i,f : Integer;
      [*] = ;
      [*] = ;         a_str := gStrRegister_PendingAchievements;
      [*] = ;         ca_no := _sa_GetNum(a_str);
      [*] = ;         if (ca_no > 0) and (a_str <> '') then
      [*] = ;         begin
      [*] = ;            ca_no := min(ca_no,cMaxAchievements-1);
      [*] = ;            for i := 0 to ca_no-1 do
      [*] = ;               ca_curr[i] := (_sa_GetAsInt(a_str,i) and $ffff);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            ca_no := 0;
      [*] = ;
      [*] = ;         f := 0;
      [*] = ;         for i := 0 to ca_no-1 do
      [*] = ;         begin
      [*] = ;            if ca_curr[i] = id then
      [*] = ;            begin
      [*] = ;               f := 1;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (f = 0) and (id = gc_achiev_undead_50) then // summons per map special case
      [*] = ;         begin
      [*] = ;            var plHandle : Integer;
      [*] = ;
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;            begin
      [*] = ;               PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(),'GetHeroHandle');
      [*] = ;               plHandle := GetGameObjectPlayerHandleByHandle(GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(IntRegister0,gc_stack_unit_iHeroUID)));
      [*] = ;            end
      [*] = ;            else
      [*] = ;               plHandle := GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;            if (not SameText(GetPlayerControlModeByHandle(plHandle),'cmPC')) then
      [*] = ;            begin
      [*] = ;               var n : Integer;
      [*] = ;               var af : Integer = GetPlayerIntValueByHandle(plHandle, gc_map_PLStack_MapUnit_nAchievemntsFlags);
      [*] = ;
      [*] = ;               n := ((af and $ff00) shr 8) + 1;
      [*] = ;               if n <= 50 then f := 1
      [*] = ;               else n := 50;
      [*] = ;               af := (af and $ffff00ff) or (n shl 8);
      [*] = ;               {if _log then }_log_values('AF|N|F',af,n,f,0,0,0);
      [*] = ;               SetPlayerIntValueByHandle(plHandle, gc_map_PLStack_MapUnit_nAchievemntsFlags, af);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               f := 1;
      [*] = ;         end;
      [*] = ;         if f = 0 then
      [*] = ;            _sa_AddAsInt(gStrRegister_PendingAchievements,id);
      [*] = ;         if _log then _log_Gui('Achievements pending: '+gStrRegister_PendingAchievements);
      [*] = ;
      [*] = ;         if (str_attr <> '') and (f = 0) then
      [*] = ;            ProcessAchievements(str_attr,0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      ProcessAchievements(str_attr,0);
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      var temp_str : String;
      [*] = ;
      [*] = ;      IntRegister0 := GetAchievementsList(BoolRegister0,temp_str);
      [*] = ;      StringRegister0 := temp_str;
      [*] = ;   end;
      [*] = ;   3 : begin
      [*] = ;      if gIntRegister_CurGameMode = gc_GameModeMenu then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         GUIExecuteState('vvk.ShowAchievListModal');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var a_str,temp_str,fh : String;
      [*] = ;         var n,i,whd,id,w,h,i_offs : Integer;
      [*] = ;         var pos,img_pos : TRectangle;
      [*] = ;
      [*] = ;         _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fh);
      [*] = ;         n:= GetAchievementsList(false,a_str);
      [*] = ;         _sys_FillRect(pos,80,80,GetViewerWidth()-160,GetViewerHeight()-160);
      [*] = ;         whd := _gui_CreateScalableWindow_VVK(cQuestionDialogWindowName,_gui_GetLayerI(),gc_gui_align_parent_lt,pos,'common_tooltip_dark');
      [*] = ;         _sys_FillRect(pos,0,0,30,30);
      [*] = ;         _gui_CreateButton_VVK('btnCancel', whd,'', 'mainpanel.btn.cancel', gc_gui_align_parent_lt, pos, 'EventQuestionDialog', '', 102);
      [*] = ;         _sys_FillRect(pos,10,50,1,1);
      [*] = ;         if n > 0 then
      [*] = ;         begin
      [*] = ;            var ehd,xhd : Integer;
      [*] = ;            var text,columns : String;
      [*] = ;
      [*] = ;            ehd := _gui_CreateImage_VVK('table',whd,gc_gui_material_blank_0,gc_gui_align_parent_lt,pos);
      [*] = ;            columns := '';
      [*] = ;            _sys_FillRect(pos,0,0,0,0);
      [*] = ;            h := 56;
      [*] = ;            i_offs := (GetGUIElementFontHeight(fh)*3-h) div 2;
      [*] = ;            w := 70;
      [*] = ;            _sys_FillRect(img_pos,((w-h) div 2)+6,0,0,0);
      [*] = ;            _sa_AddAsInt(columns,w);
      [*] = ;            i := GetGUIElementWidth(whd)-120;
      [*] = ;            _sa_AddAsInt(columns,i div 3);
      [*] = ;            _sa_AddAsInt(columns,i-(i div 3));
      [*] = ;            _gui_TableGetFrameString(columns,gc_gui_TableFrameTop,temp_str);
      [*] = ;            xhd:=_gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;            pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;            for i := 0 to n-1 do
      [*] = ;            begin
      [*] = ;               id := _achievement_GetTextID(_sa_GetAsInt(a_str,i));
      [*] = ;
      [*] = ;               temp_str := 'achievement.icon.'+IntToStr(id);
      [*] = ;               if GetGUITextureWidth(temp_str) = 0 then
      [*] = ;                  temp_str := 'achievement.icon.0';
      [*] = ;               img_pos.pos.y := pos.pos.y+i_offs;
      [*] = ;               _gui_CreateImage_VVK('',ehd,temp_str,gc_gui_align_parent_lt,img_pos);
      [*] = ;
      [*] = ;               text := ' | | ';
      [*] = ;               _gui_TableFormatTextLine(fh,columns,text,temp_str);
      [*] = ;               xhd := _gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,fh,gc_gui_fontcolor_NormalWhite);
      [*] = ;               pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;               text := '';
      [*] = ;               _sa_Add(text,' ');
      [*] = ;               _sa_Add(text,'"^c'+GetLocaleTableListItemByID('achievements_e2', IntToStr(id)+'.name')+'"');
      [*] = ;               _sa_Add(text,'"^r'+GetLocaleTableListItemByID('achievements_e2', IntToStr(id)+'.description')+'"');
      [*] = ;               _gui_TableFormatTextLine(fh,columns,text,temp_str);
      [*] = ;               xhd:=_gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,fh,gc_gui_fontcolor_NormalWhite);
      [*] = ;               pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;               text := ' | | ';
      [*] = ;               _gui_TableFormatTextLine(fh,columns,text,temp_str);
      [*] = ;               xhd := _gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,fh,gc_gui_fontcolor_NormalWhite);
      [*] = ;               pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;               if (i = (n-1)) then
      [*] = ;                  _gui_TableGetFrameString(columns,gc_gui_TableFrameBottom,temp_str)
      [*] = ;               else
      [*] = ;                  _gui_TableGetFrameString(columns,gc_gui_TableFrameCenter,temp_str);
      [*] = ;               xhd:=_gui_CreateText_VVK('',ehd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;               pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //_sys_FillRect(pos,10,10,GetGUIElementWidth(whd)-20,GetGUIElementHeight(whd)-20);
      [*] = ;         //_gui_CreateText_VVK('list',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,fh,gc_gui_fontcolor_NormalWhite);
      [*] = ;         //GetGUIElementFontTextFormatRect(fh,temp_str,w,h);
      [*] = ;         //if _log then _log_Values('H|W',h,GetGUIElementWidth(whd)-20,0,0,0,0);
      [*] = ;         //DoTableTest(whd,fh,10,h,GetGUIElementWidth(whd)-20);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   4 : begin
      [*] = ;      ProcessAchievements('',1);
      [*] = ;   end;
      [*] = ;   $100 : begin
      [*] = ;      BoolRegister0 := CheckSteam();
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

