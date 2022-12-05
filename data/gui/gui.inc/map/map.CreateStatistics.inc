section.begin
   Name = map.CreateStatistics
   Description : struct.begin
      [*] = ;IntRegister0 - (0-display window, 1-return final score only in IR0 -- no render)
      [*] = ;BoolRegister0 - true - end game screen
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATESTATISTICS';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;const cWindowNameS = 'statistics';
      [*] = ;const cTemplateNameS = 'statistics_window';
      [*] = ;const cEventStateS ='map.EventStatistics';
      [*] = ;
      [*] = ;//const cWindowNameE = 'statistics';
      [*] = ;const cWindowNameE = 'shardendgamestatistics';
      [*] = ;const cTemplateNameE = 'endgame_window';
      [*] = ;//const cEventStateE ='map.EventStatistics';
      [*] = ;const cEventStateE ='map.EventEndGameStatistics';
      [*] = ;
      [*] = ;const cBtnAcceptTag = 101;
      [*] = ;
      [*] = ;const cMastersRecordsNo = 10;
      [*] = ;
      [*] = ;// common part
      [*] = ;const cPlayerName = $1e;
      [*] = ;const cEconomicsHeader = $1d;
      [*] = ;const cOpponentsHeader = $1c;
      [*] = ;const cPlayerPortrait = $1b;
      [*] = ;const cStatsTable = $1a;             // stats
      [*] = ;const cEndGameSummary = $1a;         // eog
      [*] = ;const cEconomicsTable = $19;         // stats
      [*] = ;const cEndGameStatsTable = $19;      // eog
      [*] = ;const cOpponentsTable = $18;         // stats
      [*] = ;const cRewardsTable = $18;           // eog
      [*] = ;const cOKButton = $17;
      [*] = ;const cPlayerDifficulty = $16;
      [*] = ;
      [*] = ;// stats
      [*] = ;const cOpponentsElement = $15;
      [*] = ;const cOpponentsPortrait = $14;
      [*] = ;const cOpponentsFrame = $13;
      [*] = ;const cOpponentsBanner = $12;
      [*] = ;const cOpponentsName = $11;
      [*] = ;const cOpponentsLevel = $10;
      [*] = ;
      [*] = ;// end game
      [*] = ;const cRewardIcon = $14;
      [*] = ;const cRewardName = $13;
      [*] = ;const cRewardPoints = $12;
      [*] = ;
      [*] = ;//common part
      [*] = ;const cEconomicsTableHeader1 = $6;   // stats
      [*] = ;const cEndGameTableHeader1 = $6;     // eog
      [*] = ;const cOpponentsHeaderText = $5;
      [*] = ;const cEconomicsHeaderText = $4;
      [*] = ;const cPlayerDifficultyText = $3;
      [*] = ;const cPlayerPortraitFrame = $2;
      [*] = ;const cPlayerNameText = $1;
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;var text : array [0..$40] of String;
      [*] = ;var font : array [0..$40] of String;
      [*] = ;var font_color : array [0..$40] of TColorRGBA;
      [*] = ;var max_w : array [0..$10] of Integer;
      [*] = ;var default_text_color : TColorRGBA;
      [*] = ;
      [*] = ;procedure CopyRGBColor(src : TColorRGBA; var dst : TColorRGBA);
      [*] = ;begin
      [*] = ;   dst.r := src.r;
      [*] = ;   dst.g := src.g;
      [*] = ;   dst.b := src.b;
      [*] = ;   dst.a := src.a;
      [*] = ;end;
      [*] = ;
      [*] = ;function AddString(var dst : String; text : String; fh : String) : Integer;
      [*] = ;begin
      [*] = ;   var w,h : Integer;
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   if _sa_GetNumSafe(text) = 2 then
      [*] = ;   begin
      [*] = ;      var t1,t2 : String;
      [*] = ;
      [*] = ;      _sa_Get(text,0,t1);
      [*] = ;      _sa_Get(text,1,t2);
      [*] = ;      temp_str := GetLocaleTableListItemByID(t1,t2);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      temp_str := text;
      [*] = ;
      [*] = ;   _sa_AddWithQuotes(dst,temp_str);
      [*] = ;   GetGUIElementFontTextFormatRect(fh,temp_str,w,h);
      [*] = ;   Result := w;
      [*] = ;end;
      [*] = ;
      [*] = ;// &1 - no header, &2 - no footer, &4 - no center lines, &8 - no top line y additions, &0x20 - no center and bottom lines y additions
      [*] = ;// &0x100 - use left corner
      [*] = ;function DisplayTable(whd : Integer;columns_no : Integer;rows_no : Integer;fh : String;start_y : Integer; flags : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var columns,temp_str : String;
      [*] = ;   var pos : TRectangle;
      [*] = ;   var i,xhd,idx : Integer;
      [*] = ;
      [*] = ;   i := $3f;
      [*] = ;   font[i] := fh;
      [*] = ;   CopyRGBColor(default_text_color,font_color[i]);
      [*] = ;
      [*] = ;   columns := '';
      [*] = ;   xhd := 0;
      [*] = ;   for i:=0 to columns_no-1 do
      [*] = ;   begin
      [*] = ;      _sa_AddAsInt(columns,max_w[i]);
      [*] = ;      xhd := xhd+max_w[i];
      [*] = ;   end;
      [*] = ;   _sys_FillRect(pos,0,start_y,0,0);
      [*] = ;   if ((flags and $100) = 0) then
      [*] = ;      pos.pos.x := -1*((xhd+_gui_TableGetFrameWidth(gc_gui_TableStyleBorder)*(columns_no+1)) div 2)
      [*] = ;   else
      [*] = ;      pos.pos.x := 0;
      [*] = ;
      [*] = ;   if ((flags and 1) = 0) then
      [*] = ;   begin
      [*] = ;      _gui_TableGetFrameString(columns,gc_gui_TableFrameTop,temp_str);
      [*] = ;      xhd:=_gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;      pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if ((flags and $8) = 0) then
      [*] = ;         pos.pos.y := pos.pos.y+_gui_TableGetFrameHeight(gc_gui_TableStyleBorder);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i:=0 to rows_no-1 do
      [*] = ;   begin
      [*] = ;      if font[i] = '' then
      [*] = ;         idx := $3f
      [*] = ;      else
      [*] = ;         idx := i;
      [*] = ;      _gui_TableFormatTextLine(font[idx],columns,text[i],temp_str);
      [*] = ;      //if (_log) and (columns_no>3) then _log_Gui(text[i]);
      [*] = ;      xhd:=_gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,font[idx],font_color[idx]);
      [*] = ;      pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;      temp_str := '';
      [*] = ;      if (i = (rows_no-1)) then
      [*] = ;      begin
      [*] = ;         if ((flags and 2) = 0) then
      [*] = ;            _gui_TableGetFrameString(columns,gc_gui_TableFrameBottom,temp_str);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((flags and 4) = 0) then
      [*] = ;            _gui_TableGetFrameString(columns,gc_gui_TableFrameCenter,temp_str);
      [*] = ;      end;
      [*] = ;      if temp_str <> '' then
      [*] = ;      begin
      [*] = ;         xhd:=_gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,gc_gui_table_font_handle,gc_gui_fontcolor_NormalWhite);
      [*] = ;         pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((flags and $20) = 0) then
      [*] = ;            pos.pos.y := pos.pos.y+_gui_TableGetFrameHeight(gc_gui_TableStyleBorder);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := pos.pos.y;
      [*] = ;end;
      [*] = ;
      [*] = ;var eg_text : array [0..$40] of String;
      [*] = ;var eg_rewards : array [0..$20] of Integer;
      [*] = ;var eg_rewards_txt : array [0..$20] of String;
      [*] = ;var eg_rewards_scores : array [0..$20] of Integer;
      [*] = ;var eg_text2_start,eg_game_score,eg_rewards_no,eg_text_idx,eg_ruler_nick : Integer;
      [*] = ;var eg_ruler_name : String;
      [*] = ;
      [*] = ;//if blank then calculate final score only
      [*] = ;function FillEndGameStats(font_handle : String) : Integer;
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;   //var timeShift : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iTimeShift);
      [*] = ;   var bGameWin : Boolean = gBoolRegister_MapWin;
      [*] = ;   var bGameLose : Boolean = gBoolRegister_MapLose;
      [*] = ;   var i,j,k,n,dummyHandle,tmpPlHandle,difficulty,plIndex,r_score,work1,work2,max_diff : Integer;
      [*] = ;   var tmp_bool : Boolean;
      [*] = ;   var temp_str : String;
      [*] = ;
      [*] = ;   eg_rewards_no := 0;
      [*] = ;   eg_game_score := 0;
      [*] = ;   eg_text_idx := 0;
      [*] = ;   r_score := 0;
      [*] = ;   for i:=0 to 2 do
      [*] = ;      max_w[i] := 0;
      [*] = ;
      [*] = ;   // achievements
      [*] = ;   if not gGame.sandbox then
      [*] = ;   begin
      [*] = ;      if bGameWin then
      [*] = ;      begin
      [*] = ;         if GetPlayerBoolValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_bNoLoss) then
      [*] = ;            i := 1
      [*] = ;         else
      [*] = ;            i := 0;
      [*] = ;
      [*] = ;         //��� ������ (2) Zero losses
      [*] = ;         if (i=1) {and (timeShift=0)} then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 2;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '287');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := (200*(gGame.map.x-2)) div 8;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_tactician,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //��� ��������� (8) No battles lost
      [*] = ;         i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLoseCount);
      [*] = ;         if (i=0) {and (timeShift=0)} then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 8;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '288');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := (100*(gGame.map.x-2)) div 8;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_strategist,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //������� ����� (15) Arena Champion
      [*] = ;         i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iArenaWinCount);
      [*] = ;         if (i>=10) then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 15;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '526');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := 50;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_arena_champion,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //����������� ����� ������ (3) Explorer
      [*] = ;         i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iExplore);
      [*] = ;         if (i>1000) then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 3;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '289');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := 30;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_explorer,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //������� ��� ����� (10) Uncovered whole map
      [*] = ;         n := 1;
      [*] = ;         for i := 0 to ParserGetCountByHandle(gStratHexCells.handle)-1 do
      [*] = ;         begin
      [*] = ;            var pProvFog : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gStratHexCells.handle, i),'Fog');
      [*] = ;            var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog,gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;            if fog > 1 then // half fog is ok
      [*] = ;            begin
      [*] = ;               n := 0;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (n<>0) and gGame.fog then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 10;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '290');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := (40*(gGame.map.x-2)) div 8;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_cartographer,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //����� ��������� �������� (13) Fully built stronghold
      [*] = ;         n := 1;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;         dummyHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(IntRegister0, 'DummyUID'));
      [*] = ;         for i:=1 to gPrototypeData.innerBuildings.number-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := i;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;            tmp_bool := BoolRegister0;
      [*] = ;            IntRegister0 := i;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'IsBuildingAvailable');
      [*] = ;            var isAvailable : Boolean = BoolRegister0;
      [*] = ;            var isOutGroup : Boolean = not BoolRegister1;
      [*] = ;            var isEverBuildable : Boolean = BoolRegister3;
      [*] = ;            //if (not tmp_bool) and (not BoolRegister1) and (BoolRegister0) and (BoolRegister3) then // BUG in logic ((not isOutGroup) not the same as (not BoolRegister1))
      [*] = ;            if (not tmp_bool) and (not isOutGroup) and (isAvailable) and (isEverBuildable) then
      [*] = ;            begin
      [*] = ;               n := 0;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (n <> 0) then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 13;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '291');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := 25;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_architect,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //����� ����� �������� (1) Dragons killed
      [*] = ;         i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDragonHunt);
      [*] = ;         if (i>=10) then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 1;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '292');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := 40;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_dragon_slayer,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //���������� ����� ������ (4) Gold looted
      [*] = ;         i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iPillage);
      [*] = ;         if (i>1000) then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 4;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '293');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := 25;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_looter,'');
      [*] = ;         end;
      [*] = ;
      [*] = ;         //������ ��� (5) Item sets
      [*] = ;         if (GetPlayerBoolValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_bSet)) then
      [*] = ;         begin
      [*] = ;            eg_rewards[eg_rewards_no] := 5;
      [*] = ;            eg_rewards_txt[eg_rewards_no] := GetLocaleTableListItemByID('gui', '294');
      [*] = ;            eg_rewards_scores[eg_rewards_no] := 20;
      [*] = ;            r_score := r_score+eg_rewards_scores[eg_rewards_no];
      [*] = ;            eg_rewards_no := eg_rewards_no+1;
      [*] = ;            _achievement_Trigger(gc_achiev_items_collector,'');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      eg_game_score := eg_game_score+r_score;
      [*] = ;
      [*] = ;      //���������� ���������� Number of opponents
      [*] = ;      work1 := 0;
      [*] = ;      max_diff := 0;
      [*] = ;      for i:=0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         tmpPlHandle := GetPlayerHandleByIndex(i);
      [*] = ;         if (plHandle<>tmpPlHandle) then
      [*] = ;         begin
      [*] = ;            difficulty := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(tmpPlHandle)].basediff;
      [*] = ;            max_diff:=Max(max_diff,difficulty);
      [*] = ;            work1 := work1+4+difficulty;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      work1 := work1+max_diff*5;
      [*] = ;      eg_game_score := eg_game_score+work1;
      [*] = ;
      [*] = ;      if font_handle <> '' then
      [*] = ;      begin
      [*] = ;         eg_text[eg_text_idx] := '';
      [*] = ;         max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|58',font_handle));
      [*] = ;         max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(gGame.map.players-1),font_handle));
      [*] = ;         max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;         eg_text_idx := eg_text_idx+1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      //��������� ����������� Defeated opponents
      [*] = ;      work1 := 0;
      [*] = ;      work2 := 0;
      [*] = ;      n := ParserSelectByHandleByKey(ParserSelectPlayer(plHandle), 'KilledPlayers');
      [*] = ;      for i:=0 to ParserGetCountByHandle(n)-1 do
      [*] = ;      begin
      [*] = ;         work1 := work1+1;
      [*] = ;         plIndex := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(n, i), 'Index');
      [*] = ;         tmpPlHandle := GetPlayerHandleByIndex(plIndex);
      [*] = ;         difficulty := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(tmpPlHandle)].basediff;
      [*] = ;         work2 := work2+5+(difficulty)*4;
      [*] = ;      end;
      [*] = ;      eg_game_score := eg_game_score+work2;
      [*] = ;
      [*] = ;      if font_handle <> '' then
      [*] = ;      begin
      [*] = ;         eg_text[eg_text_idx] := '';
      [*] = ;         max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|273',font_handle));
      [*] = ;         max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;         max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work2),font_handle));
      [*] = ;         eg_text_idx := eg_text_idx+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //����� Battles Won
      [*] = ;   i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iWinCount);
      [*] = ;   eg_game_score := eg_game_score+(i div 2);
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|267',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i div 2),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //��������� Battles Lost
      [*] = ;   i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLoseCount);
      [*] = ;   eg_game_score := eg_game_score-(i div 2);
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|268',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(-1*(i div 2)),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //��������� Provinces
      [*] = ;   work1 := 0;
      [*] = ;   work2 := 0;
      [*] = ;   for i:=0 to ParserGetCountByHandle(gStratHexCells.handle)-1 do
      [*] = ;   begin
      [*] = ;      n := ParserSelectByHandleByIndex(gStratHexCells.handle, i);
      [*] = ;      if SameText(ParserGetValueByKeyByHandle(n, 'Player'), GetPlayerNameInterfaceIO()) then
      [*] = ;      begin
      [*] = ;         work1 := work1+1;
      [*] = ;         work2 := work2+2+ParserGetIntValueByKeyByHandle(n, 'ProvinceLevel');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   work2 := work2 div 2;
      [*] = ;   eg_game_score := eg_game_score+work2;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|269',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work2),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //������ Heroes
      [*] = ;   work1 := 0;
      [*] = ;   work2 := 0;
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;      begin
      [*] = ;         work1 := work1+1;
      [*] = ;         work2 := work2+3+GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   eg_game_score := eg_game_score+work2;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|270',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work2),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //������-��������� Veteran Warriors
      [*] = ;   work1 := 0;
      [*] = ;   work2 := 0;
      [*] = ;   for i:=GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHero : Integer = ParserSelectGameObject(GetGameObjectHandleByIndex(i, plHandle));
      [*] = ;      var pUnits : Integer = ParserSelectByHandleByKey(pHero, 'Units');
      [*] = ;
      [*] = ;      for j:=0 to ParserGetCountByHandle(pUnits)-1 do
      [*] = ;      begin
      [*] = ;         var pUnit : Integer = ParserSelectByHandleByIndex(pUnits, j);
      [*] = ;         var level : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Level');
      [*] = ;         var isHero : Boolean = ParserGetBoolValueByKeyByHandle(pUnit, 'IsHero');
      [*] = ;
      [*] = ;         var unitID : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitID');
      [*] = ;         var pPrototypeUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle,unitID);
      [*] = ;         var unitType : Integer = ParserGetIntValueByKeyByHandle(pPrototypeUnit, 'UnitType');
      [*] = ;
      [*] = ;         if (not IsHero) and (level>=10) and (unitType<>2) then
      [*] = ;         begin
      [*] = ;            work1 := work1+1;
      [*] = ;            work2 := work2+((level-7) div 3);
      [*] = ;
      [*] = ;            var pMedals : Integer = ParserSelectByHandleByKey(pUnit, 'Medals');
      [*] = ;
      [*] = ;            for k:=0 to ParserGetCountByHandle(pMedals)-1 do
      [*] = ;            begin
      [*] = ;               var pMedal : Integer = ParserSelectByHandleByIndex(pMedals, k);
      [*] = ;               var medalID : Integer = ParserGetIntValueByKeyByHandle(pMedal, 'MedalID');
      [*] = ;               if (medalID<>0) and (medalID<>6) then
      [*] = ;                  work2 := work2+2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   for i:=0 to ParserGetCountByHandle(gStratHexCells.handle)-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, i);
      [*] = ;      if SameText(ParserGetValueByKeyByHandle(pHexCell, 'Player'), GetPlayerNameInterfaceIO()) then
      [*] = ;      begin
      [*] = ;         var pGarrison : Integer =  ParserSelectByHandleByKey(pHexCell, 'Garrison');
      [*] = ;         var pGarrisonUnits : Integer = ParserSelectByHandleByKey(pGarrison, 'Units');
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pGarrisonUnits)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pGarrisonUnit : Integer = ParserSelectByHandleByIndex(pGarrisonUnits, j);
      [*] = ;            var level : Integer = ParserGetIntValueByKeyByHandle(pGarrisonUnits, 'Level');
      [*] = ;            if (level>=10) then
      [*] = ;            begin
      [*] = ;               work1 := work1+1;
      [*] = ;               work2 := work2+((level-7) div 3);
      [*] = ;               var pMedals : Integer = ParserSelectByHandleByKey(pGarrisonUnit, 'Medals');
      [*] = ;
      [*] = ;               for k:=0 to ParserGetCountByHandle(pMedals)-1 do
      [*] = ;               begin
      [*] = ;                  var pMedal : Integer = ParserSelectByHandleByIndex(pMedals, k);
      [*] = ;                  var medalID : Integer = ParserGetIntValueByKeyByHandle(pMedal, 'MedalID');
      [*] = ;                  if (medalID<>0) and (medalID<>6) then
      [*] = ;                     work2 := work2+2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   eg_game_score := eg_game_score+work2;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|283',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work2),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //�������� � ����� Stronghold buildings
      [*] = ;   work1 := 0;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;   n := ParserSelectByHandleByKey(IntRegister0, 'InnerBuildings');
      [*] = ;   for i := ParserGetCountByHandle(n)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      j := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(n, i), 'BuildingID');
      [*] = ;      if j<>0 then
      [*] = ;         work1 := work1+1;
      [*] = ;   end;
      [*] = ;   eg_game_score := eg_game_score+(work1 div 4);
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|284',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1 div 4),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //�������� ������� Treasures found
      [*] = ;   work1 := 0;
      [*] = ;   work2 := 0;
      [*] = ;   n := ParserSelectByHandleByKey(ParserSelectByHandleByKey(ParserSelectPlayer(plHandle), 'Stats'), 'RareItems');
      [*] = ;   for i:=0 to ParserGetCountByHandle(n)-1 do
      [*] = ;   begin
      [*] = ;      j := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(n, i), 'Count');
      [*] = ;      work1 := work1+j;
      [*] = ;      work2 := work2+j*(i+1);
      [*] = ;   end;
      [*] = ;   eg_game_score := eg_game_score+work2;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|274',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work2),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //������� ��������� Quests completed
      [*] = ;   i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iQuestDone);
      [*] = ;   eg_game_score := eg_game_score+i*10;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|278',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i*10),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //������� Awards
      [*] = ;   if (font_handle <> '') and (not gGame.sandbox) then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|280',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(eg_rewards_no),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(r_score),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //������ �� ������� Reloads
      [*] = ;   {eg_game_score := eg_game_score-timeShift*20;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|396',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(timeShift),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(-timeShift*20),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   //�������� Personality
      [*] = ;   i := (round(abs(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma))) div 10);
      [*] = ;   eg_game_score := eg_game_score+i;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|285',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c ',font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i),font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   eg_text2_start := eg_text_idx;
      [*] = ;
      [*] = ;   //����� Time
      [*] = ;   i := gGame.currentturn+(150-((gGame.map.x+gGame.map.y-12) div 4)*25);
      [*] = ;   if (i<200) then
      [*] = ;      work1 := 150-(i div 4)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (i<400) then
      [*] = ;         work1 := 100-((i-200) div 4)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (i<600) then
      [*] = ;         work1 := 50-((i-400) div 8)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (i<800) then
      [*] = ;               work1 := 25-((i-600) div 20)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (i<1000) then
      [*] = ;                  work1 := 15-((i-800) div 40)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if (i<2000) then
      [*] = ;                     work1 := 10-((i-1000) div 200)
      [*] = ;                  else
      [*] = ;                     work1 := 4;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   eg_game_score := (eg_game_score*work1) div 100;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      if (work1>100) then
      [*] = ;         temp_str := '+'+IntToStr(work1-100)+'%'
      [*] = ;      else
      [*] = ;         temp_str := IntToStr(work1-100)+'%';
      [*] = ;
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|51',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c'+IntToStr(gGame.currentturn),font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+temp_str,font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //��������� Difficulty
      [*] = ;   if (gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].custom) then
      [*] = ;      work1 := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].score
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      n := ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].basediff);
      [*] = ;      work1 := ParserGetIntValueByKeyByHandle(n, 'Score');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _log_Values('SCORE|GAME_SCORE|M_DIFF|P',work1,eg_game_score,max_diff+2,(work1*max_diff) div 4,0,0);
      [*] = ;   if (not gGame.fog) then
      [*] = ;      work1 := round(work1*4/5);
      [*] = ;   work1 := (work1*(max_diff+2)) div 4;
      [*] = ;
      [*] = ;   eg_game_score := (eg_game_score*work1) div 100;
      [*] = ;
      [*] = ;   if font_handle <> '' then
      [*] = ;   begin
      [*] = ;      eg_text[eg_text_idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|218',font_handle));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c ',font_handle));
      [*] = ;      max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(work1)+'%',font_handle));
      [*] = ;      eg_text_idx := eg_text_idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (eg_game_score<0) then
      [*] = ;      eg_game_score := 0;
      [*] = ;
      [*] = ;   //������/��������� Victory / Defeat
      [*] = ;   if gGame.sandbox then
      [*] = ;   begin
      [*] = ;      eg_game_score := (eg_game_score) div 2;
      [*] = ;      i := -50;
      [*] = ;
      [*] = ;      if font_handle <> '' then
      [*] = ;      begin
      [*] = ;         eg_text[eg_text_idx] := '';
      [*] = ;         max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'menu|sandbox',font_handle));
      [*] = ;         max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c ',font_handle));
      [*] = ;         max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i)+'%',font_handle));
      [*] = ;         eg_text_idx := eg_text_idx+1;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if bGameWin then
      [*] = ;      begin
      [*] = ;         temp_str := '22';
      [*] = ;         i := 100;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         temp_str := '23';
      [*] = ;         eg_game_score := (eg_game_score) div 5;
      [*] = ;         i := -80;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if font_handle <> '' then
      [*] = ;      begin
      [*] = ;         eg_text[eg_text_idx] := '';
      [*] = ;         max_w[0] := Max(max_w[0],AddString(eg_text[eg_text_idx],'gui|'+temp_str,font_handle));
      [*] = ;         max_w[1] := Max(max_w[1],AddString(eg_text[eg_text_idx],'^c ',font_handle));
      [*] = ;         max_w[2] := Max(max_w[2],AddString(eg_text[eg_text_idx],'^c'+IntToStr(i)+'%',font_handle));
      [*] = ;         eg_text_idx := eg_text_idx+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //eg_game_score := 200;
      [*] = ;   Result := eg_game_score;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetSummaryText(score : Integer;nick_id : Integer;var dst_txt : String);
      [*] = ;begin
      [*] = ;   var text,bm_fname : String;
      [*] = ;
      [*] = ;   if (score>0) then
      [*] = ;   begin
      [*] = ;      var yearTextIndex : Integer = 298;
      [*] = ;      var i,n,pBookMasters,place : Integer;
      [*] = ;
      [*] = ;      if ((score mod 100)<11) or ((score mod 100)>15) then
      [*] = ;      begin
      [*] = ;         case (score mod 10) of
      [*] = ;            1 : yearTextIndex := 296;
      [*] = ;            4 : yearTextIndex := 297;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      place := -1;
      [*] = ;
      [*] = ;      text := GetLocaleTableListItemByID('message', '22.description');
      [*] = ;      if (place>-1) and (place<10) then
      [*] = ;      begin
      [*] = ;         gIntRegister_RecordPlace := place+1;
      [*] = ;         text := text+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('message', '23.description');
      [*] = ;      end;
      [*] = ;
      [*] = ;      gStringRegister_StrYears := GetLocaleTableListItemByID('gui', IntToStr(yearTextIndex));
      [*] = ;   end
      [*] = ;   else
      [*] = ;      text := GetLocaleTableListItemByID('message', '29.description');
      [*] = ;
      [*] = ;   dst_txt := text;
      [*] = ;end;
      [*] = ;
      [*] = ;const cTextCustom = 'gui|767';
      [*] = ;
      [*] = ;var temp_str,txt,plName : String;
      [*] = ;var i,whd,ehd,xhd,windowHandle,if_handle,karma,pRulerNick,idx,plIndex : Integer;
      [*] = ;var plHandle,n,j : Integer;
      [*] = ;var elem_d,elem2_d : TInterfaceElementData;
      [*] = ;var pos,tmp_pos : TRectangle;
      [*] = ;var stats_str : array [0..$10] of String;
      [*] = ;var ti : array [0..4] of Integer;
      [*] = ;var wnd_name,event_name,tpl_name : String;
      [*] = ;var end_game : Boolean = BoolRegister0;
      [*] = ;var stats_mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(end_game)+']',_log_trace);
      [*] = ;if (end_game) and (stats_mode<>0) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   IntRegister0 := FillEndGameStats('');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if end_game then
      [*] = ;begin
      [*] = ;   wnd_name := cWindowNameE;
      [*] = ;   event_name := cEventStateE;
      [*] = ;   tpl_name := cTemplateNameE;
      [*] = ;   _gv_SetMapLock(1,_log_name);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   wnd_name := cWindowNameS;
      [*] = ;   event_name := cEventStateS;
      [*] = ;   tpl_name := cTemplateNameS;
      [*] = ;end;
      [*] = ;
      [*] = ;if_handle := _gui_GetInterfaceWindowHandle(tpl_name);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,gc_gui_if_base_window_id,elem_d);
      [*] = ;
      [*] = ;windowHandle := _gui_GetWindow(wnd_name);
      [*] = ;if windowHandle <> 0 then
      [*] = ;   RemoveGUIElement(windowHandle);
      [*] = ;_sys_FillRect(pos,0,0,elem_d.p.size.w,elem_d.p.size.h);
      [*] = ;windowHandle := _gui_CreateScalableWindow_VVK(wnd_name,_gui_GetLayerI(),gc_gui_align_parent_m,pos,'common_window');
      [*] = ;
      [*] = ;plHandle := GetPlayerHandleInterfaceIO();
      [*] = ;plIndex := GetPlayerIndexByHandle(plHandle);
      [*] = ;
      [*] = ;// player portrait
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerPortrait,elem_d);
      [*] = ;if (gGame.gametype=gc_GameTypeCampaign) then
      [*] = ;begin
      [*] = ;   if (gTutorial.map) then
      [*] = ;      temp_str := 'astral.players.icon.big.17'
      [*] = ;   else
      [*] = ;      temp_str := 'astral.players.icon.big.player';
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;      temp_str := 'astral.players.icon.big.'+IntToStr(gLanShardGame.arrLanPlayers[plIndex].profile.avatar)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (gGame.gameType = gc_GameTypeHotseat) and (plIndex > 0) then
      [*] = ;         temp_str := 'astral.players.icon.big.'+IntToStr(gArrHotseatProfiles[plIndex].avatar)
      [*] = ;      else
      [*] = ;         temp_str := 'astral.players.icon.big.'+IntToStr(gProfile.avatar);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;_sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;_gui_CreateImage_VVK('',windowHandle,temp_str,elem_d.align,pos);
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerPortraitFrame,elem_d);
      [*] = ;_sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;_gui_CreateImage_VVK('',windowHandle,'gamepanel03.portrait.frame.big',elem_d.align,pos);
      [*] = ;
      [*] = ;// player name
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerName,elem_d);
      [*] = ;temp_str := '';
      [*] = ;if end_game then
      [*] = ;begin
      [*] = ;   var pRulerTitle : Integer;
      [*] = ;
      [*] = ;   _gui_CreateImage_VVK('',windowHandle,'element.header.strip.875',elem_d.align,elem_d.p);
      [*] = ;
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEndGameStatsTable,elem2_d);
      [*] = ;   eg_game_score := FillEndGameStats(elem2_d.font_handle);
      [*] = ;
      [*] = ;   for i:=0 to gPrototypeData.rulerTitles.number-1 do
      [*] = ;   begin
      [*] = ;      pRulerTitle := ParserSelectByHandleByIndex(gPrototypeData.rulerTitles.handle,i);
      [*] = ;      if (eg_game_score>=(ParserGetIntValueByKeyByHandle(pRulerTitle, 'Min'))) and (eg_game_score<(ParserGetIntValueByKeyByHandle(pRulerTitle, 'Max'))) then
      [*] = ;      begin
      [*] = ;         temp_str := GetLocaleTableListItemByID('ruler_title', IntToStr(ParserGetIntValueByKeyByHandle(pRulerTitle,'RulerTitleID')))+' ';
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;   _gui_CreateImage_VVK('',windowHandle,'element.header.strip.620',elem_d.align,elem_d.p);
      [*] = ;
      [*] = ;karma := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;case gGame.gameType of
      [*] = ;   gc_GameTypeHotseat : plName := gArrHotseatProfiles[plIndex].name;
      [*] = ;   gc_GameTypeLanShard : plName := gLanShardGame.arrLanPlayers[plIndex].profile.name;
      [*] = ;   else plName := gProfile.name;
      [*] = ;end;
      [*] = ;
      [*] = ;temp_str := temp_str+plName;
      [*] = ;
      [*] = ;for i:=0 to gPrototypeData.rulerNicks.number-1 do
      [*] = ;begin
      [*] = ;   pRulerNick := ParserSelectByHandleByIndex(gPrototypeData.rulerNicks.handle, i);
      [*] = ;   if (karma>=ParserGetIntValueByKeyByHandle(pRulerNick, 'Min')) and (karma<ParserGetIntValueByKeyByHandle(pRulerNick, 'Max')) then
      [*] = ;   begin
      [*] = ;      eg_ruler_nick := ParserGetIntValueByKeyByHandle(pRulerNick, 'RulerNickID');
      [*] = ;      temp_str := temp_str+' '+GetLocaleTableListItemByID('ruler_nick',IntToStr(eg_ruler_nick));
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if end_game then
      [*] = ;   eg_ruler_name := temp_str;
      [*] = ;
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerNameText,elem_d);
      [*] = ;_gui_CreateText_VVK('',windowHandle,temp_str,elem_d.align,elem_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;// player difficulty
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerDifficulty,elem_d);
      [*] = ;_gui_CreateImage_VVK('',windowHandle,'element.strip.148',elem_d.align,elem_d.p);
      [*] = ;_gui_GetInterfaceElement(if_handle,cPlayerDifficultyText,elem_d);
      [*] = ;i := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].basediff;
      [*] = ;if (gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].custom) then
      [*] = ;   txt := cTextCustom
      [*] = ;else
      [*] = ;   txt := 'difficulty|'+IntToStr(i);
      [*] = ;_gui_CreateText_VVK('',windowHandle,txt,elem_d.align,elem_d.p,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;// economics header
      [*] = ;_gui_GetInterfaceElement(if_handle,cEconomicsHeader,elem_d);
      [*] = ;temp_str := 'element.strip.240';
      [*] = ;_sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;i := GetGUITextureWidth(temp_str);
      [*] = ;pos.pos.x := pos.pos.x+(elem_d.p.size.w div 2) - (i div 2);
      [*] = ;_gui_CreateImage_VVK('',windowHandle,temp_str,elem_d.align,pos);
      [*] = ;_gui_GetInterfaceElement(if_handle,cEconomicsHeaderText,elem_d);
      [*] = ;pos.pos.y := elem_d.p.pos.y;
      [*] = ;pos.size.w := i;
      [*] = ;if end_game then txt := 'gui|279'
      [*] = ;else txt := 'gui|264';
      [*] = ;_gui_CreateText_VVK('',windowHandle,txt,elem_d.align,pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;// opponents / awards header (right panel)
      [*] = ;if (not gGame.sandbox) or (not end_game) then
      [*] = ;begin
      [*] = ;   _gui_GetInterfaceElement(if_handle,cOpponentsHeader,elem_d);
      [*] = ;   _sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;   pos.pos.x := pos.pos.x+(elem_d.p.size.w div 2) - (i div 2);
      [*] = ;   _gui_CreateImage_VVK('',windowHandle,temp_str,elem_d.align,pos);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cOpponentsHeaderText,elem_d);
      [*] = ;   pos.pos.y := elem_d.p.pos.y;
      [*] = ;   pos.size.w := i;
      [*] = ;   if end_game then txt := 'gui|280'
      [*] = ;   else txt := 'gui|58';
      [*] = ;   _gui_CreateText_VVK('',windowHandle,txt,elem_d.align,pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;end;
      [*] = ;
      [*] = ;// dismiss button
      [*] = ;_gui_GetInterfaceElement(if_handle,cOKButton,elem_d);
      [*] = ;_sys_FillRect(pos,elem_d.p.pos.x,elem_d.p.pos.y,0,0);
      [*] = ;//i := _gui_CreateImage_VVK('',windowHandle,'mainpanel.btnplace.with.frame',elem_d.align,pos);
      [*] = ;//_sys_FillRect(pos,0,0,0,0);
      [*] = ;//_gui_CreateButton_VVK('', i,'','mainpanel.btn.accept',gc_gui_align_parent_m,pos,event_name,'menu|47',cBtnAcceptTag);
      [*] = ;i := _gui_CreateImage_VVK('',windowHandle,'gamepanel03.close.btn.placer',elem_d.align,pos);
      [*] = ;_sys_FillRect(pos,0,0,0,0);
      [*] = ;_gui_CreateButton_VVK('', i,'','map.heropanel.btn.closewindow',gc_gui_align_parent_m,pos,event_name,'menu|47',cBtnAcceptTag);
      [*] = ;
      [*] = ;IntRegister0 := GetPlayerHandleInterfaceIO();
      [*] = ;GUIExecuteState('VVK.map.GetGoldAndGemStats');
      [*] = ;stats_str[0] := StringRegister0;
      [*] = ;stats_str[1] := StringRegister1;
      [*] = ;stats_str[2] := StringRegister2;
      [*] = ;stats_str[3] := StringRegister3;
      [*] = ;
      [*] = ;if (not end_game) then
      [*] = ;begin
      [*] = ;   // stats data
      [*] = ;   _gui_GetInterfaceElement(if_handle,cStatsTable,elem_d);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEconomicsTableHeader1,elem2_d);
      [*] = ;   CopyRGBColor(elem_d.color,default_text_color);
      [*] = ;
      [*] = ;   _sys_FillRect(pos,elem_d.p.pos.x+(elem_d.p.size.w div 2),elem_d.p.pos.y,1,1);
      [*] = ;   whd := _gui_CreateImage_VVK('stats',windowHandle,gc_gui_material_blank_0,elem_d.align,pos);
      [*] = ;
      [*] = ;   _sys_FillRect(pos,0,0,0,0);
      [*] = ;
      [*] = ;   idx := 0;
      [*] = ;   // turns, heroes, etc
      [*] = ;   max_w[0] := 0;
      [*] = ;   max_w[1] := 0;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|51',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(gGame.currentturn),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // unions if any
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|186',elem_d.font_handle));
      [*] = ;   i := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;   if (i>0) then
      [*] = ;   begin
      [*] = ;      i := GetPlayerIntValueIndByHandle(GetPlayerHandleByIndex(i), gc_map_PLStack_MapUnit_iProfile);
      [*] = ;      max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+GetLocaleTableListItemByID('players',IntToStr(i)),elem_d.font_handle));
      [*] = ;   end
      [*] = ;   else
      [*] = ;      max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','40'),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // karma
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],GetLocaleTableListItemByID('gui','karma'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma) div 10),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // corruption
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],GetLocaleTableListItemByID('gui','263')+',%',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[2],6)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // victories
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|267',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iWinCount)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // defeats
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|268',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLoseCount)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // provinces
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|269',elem_d.font_handle));
      [*] = ;   n := 0;
      [*] = ;   for i:=0 to ParserGetCountByHandle(gStratHexCells.handle)-1 do
      [*] = ;   begin
      [*] = ;      j := ParserSelectByHandleByIndex(gStratHexCells.handle, i);
      [*] = ;      if SameText(ParserGetValueByKeyByHandle(j,'Player'),GetPlayerNameInterfaceIO()) then
      [*] = ;         n := n+1;
      [*] = ;   end;
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(n),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // heroes
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|270',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(_plr_GetNonBuriedHeroCount(plHandle)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // enemies killed
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|273',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(ParserGetCountByHandle(ParserSelectByHandleByKey(ParserSelectPlayer(plHandle),'KilledPlayers'))),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   // quests completed
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'gui|278',elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iQuestDone)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   pos.pos.y := DisplayTable(whd,2,idx,elem_d.font_handle,0,0) + GetGUIElementFontHeight(elem_d.font_handle);
      [*] = ;
      [*] = ;   // treasures found - header
      [*] = ;   temp_str := '';
      [*] = ;   text[0] := 'gui|274';
      [*] = ;   i := AddString(temp_str,text[0],elem2_d.font_handle);
      [*] = ;   pos.pos.x := -1*(i div 2);
      [*] = ;   if _log then _log_Gui(temp_str);
      [*] = ;   if _log then _log_Values('X|Y|DX|DY',pos.pos.x,pos.pos.y,pos.size.w,pos.size.h,0,0);
      [*] = ;   xhd:=_gui_CreateText_VVK('',whd,text[0],gc_gui_align_parent_lt,pos,gc_gui_align_lt,elem2_d.font_handle,elem2_d.color);
      [*] = ;   pos.pos.y := pos.pos.y+GetGUIElementHeight(xhd);
      [*] = ;
      [*] = ;   n := ParserSelectByHandleByKey(ParserSelectByHandleByKey(ParserSelectPlayer(plHandle),'Stats'),'RareItems');
      [*] = ;   idx := 0;
      [*] = ;   max_w[0] := 0;
      [*] = ;   max_w[1] := 0;
      [*] = ;   for i:=0 to ParserGetCountByHandle(n)-1 do
      [*] = ;   begin
      [*] = ;      if i < 3 then
      [*] = ;      begin
      [*] = ;         text[idx] := '';font[idx] := '';
      [*] = ;         max_w[0] := Max(max_w[0],AddString(text[idx],'gui|'+IntToStr(275+i),elem_d.font_handle));
      [*] = ;         max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+IntToStr(ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(n,i),'Count')),elem_d.font_handle));
      [*] = ;         idx := idx+1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   DisplayTable(whd,2,idx,elem_d.font_handle,pos.pos.y,0);
      [*] = ;
      [*] = ;   // load attempts
      [*] = ;   //text := text+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('gui', '396')+': '+IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iTimeShift));
      [*] = ;
      [*] = ;   // economics
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEconomicsTable,elem_d);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEconomicsTableHeader1,elem2_d);
      [*] = ;   CopyRGBColor(elem_d.color,default_text_color);
      [*] = ;   _sys_FillRect(pos,elem_d.p.pos.x+(elem_d.p.size.w div 2),elem_d.p.pos.y,1,1);
      [*] = ;   whd := _gui_CreateImage_VVK('economics',windowHandle,gc_gui_material_blank_0,elem_d.align,pos);
      [*] = ;
      [*] = ;   idx := 0;
      [*] = ;   max_w[0] := 0;
      [*] = ;   max_w[1] := 0;
      [*] = ;   max_w[2] := 0;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[idx]);
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','53'),elem2_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(ignore)%'+gc_gui_GoldIconChar,elem2_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c%color(ignore)%'+gc_gui_GemIconChar,elem2_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','55'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(info)%'+IntToStr(_sa_GetAsInt(stats_str[0],1)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[1],1)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','56'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(info)%'+IntToStr(_sa_GetAsInt(stats_str[0],2)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[1],2)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','57'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(info)%'+IntToStr(_sa_GetAsInt(stats_str[0],3)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[1],3)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','58'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(info)%'+IntToStr(_sa_GetAsInt(stats_str[0],4)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[1],4)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','61'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(info)%'+IntToStr(_sa_GetAsInt(stats_str[0],0)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[1],0)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[idx]);
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','54'),elem2_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(ignore)%'+gc_gui_GoldIconChar,elem2_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c%color(ignore)%'+gc_gui_GemIconChar,elem2_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','266'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(attention)%'+IntToStr(_sa_GetAsInt(stats_str[2],1)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[3],1)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','59'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(attention)%'+IntToStr(_sa_GetAsInt(stats_str[2],2)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[3],2)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','60'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(attention)%'+IntToStr(_sa_GetAsInt(stats_str[2],3)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[3],3)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','58'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(attention)%'+IntToStr(_sa_GetAsInt(stats_str[2],4)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[3],4)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','263'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(attention)%'+IntToStr(_sa_GetAsInt(stats_str[2],5)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[3],5)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := '';
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','61'),elem_d.font_handle));
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c%color(attention)%'+IntToStr(_sa_GetAsInt(stats_str[2],0)),elem_d.font_handle));
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+IntToStr(_sa_GetAsInt(stats_str[3],0)),elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[idx]);
      [*] = ;   max_w[0] := Max(max_w[0],AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','62'),elem_d.font_handle));
      [*] = ;   i := _sa_GetAsInt(stats_str[0],0)-_sa_GetAsInt(stats_str[2],0);
      [*] = ;   if i > 0 then
      [*] = ;      temp_str := '%color(info)%+'+IntToStr(i)
      [*] = ;   else
      [*] = ;      temp_str := '%color(attention)%'+IntToStr(i); // removed '-' in '%color(attention)%-', to prevent string like '--33'
      [*] = ;   max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+temp_str,elem_d.font_handle));
      [*] = ;   i := _sa_GetAsInt(stats_str[1],0)-_sa_GetAsInt(stats_str[3],0);
      [*] = ;   if i > 0 then
      [*] = ;      temp_str := '%color(info)%+'+IntToStr(i)
      [*] = ;   else
      [*] = ;      temp_str := '%color(attention)%'+IntToStr(i); // removed '-' in '%color(attention)%-', to prevent string like '--33'
      [*] = ;   max_w[2] := Max(max_w[2],AddString(text[idx],'^c'+temp_str,elem_d.font_handle));
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   _sys_FillRect(pos,0,0,0,0);
      [*] = ;   pos.pos.y := DisplayTable(whd,3,idx,elem_d.font_handle,0,0)+(GetGUIElementFontHeight(elem2_d.font_handle) div 3);
      [*] = ;
      [*] = ;   idx := 0;
      [*] = ;   for i:=0 to 5 do
      [*] = ;      max_w[i] := 0;
      [*] = ;
      [*] = ;   temp_str := 'ABCDEFGHI';
      [*] = ;
      [*] = ;   for i := 0 to 8 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := i+1;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetResPriceStat');
      [*] = ;      ti[1] := IntRegister1;
      [*] = ;      ti[2] := IntRegister2;
      [*] = ;      IntRegister0 := i+1;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetResCount');
      [*] = ;      ti[0] := IntRegister1;
      [*] = ;
      [*] = ;      text[idx] := '';font[idx] := '';
      [*] = ;      max_w[0] := Max(max_w[0],AddString(text[idx],'^c%color(ignore)%%style(Symbols)%'+SubStr(temp_str,i+1,1)+'%style(default)%%color(restore)%',elem_d.font_handle));
      [*] = ;      //if _log then _log_Gui(GetLocaleTableListItemByID('resource',IntToStr(i+1)));
      [*] = ;      max_w[1] := Max(max_w[1],AddString(text[idx],'^c'+GetLocaleTableListItemByID('resource',IntToStr(i+1)),elem_d.font_handle));
      [*] = ;      for j:=0 to 2 do
      [*] = ;         max_w[j+2] := Max(max_w[j+2],AddString(text[idx],'^c'+IntToStr(ti[j]),elem_d.font_handle));
      [*] = ;
      [*] = ;      idx := idx+1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   DisplayTable(whd,5,idx,elem_d.font_handle,pos.pos.y+_gui_TableGetFrameHeight(gc_gui_TableStyleBorder)+GetGUIElementFontHeight(elem2_d.font_handle),0);
      [*] = ;
      [*] = ;   idx := 0;
      [*] = ;   j := _gui_TableGetFrameWidth(gc_gui_TableStyleBorder)*2;
      [*] = ;   for i:=0 to 2 do
      [*] = ;      j := j+max_w[i];
      [*] = ;
      [*] = ;   max_w[0] := j;
      [*] = ;   max_w[1] := max_w[3];
      [*] = ;   max_w[2] := max_w[4];
      [*] = ;
      [*] = ;   text[idx] := '';font[idx] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[idx]);
      [*] = ;   AddString(text[idx],'^c'+GetLocaleTableListItemByID('gui','63'),elem2_d.font_handle);
      [*] = ;   AddString(text[idx],'^c%color(ignore)%'+gc_gui_GoldIconChar,elem2_d.font_handle);
      [*] = ;   AddString(text[idx],'^c%color(ignore)%'+gc_gui_GemIconChar,elem2_d.font_handle);
      [*] = ;   idx := idx+1;
      [*] = ;
      [*] = ;   DisplayTable(whd,3,idx,elem_d.font_handle,pos.pos.y,2);
      [*] = ;
      [*] = ;   // opponents
      [*] = ;   begin
      [*] = ;      var name,portrait : String;
      [*] = ;      var sign,color1,color2,ipprofile,difficulty,treaty : Integer;
      [*] = ;      var bInGame : Boolean;
      [*] = ;      var p_d,f_d,b_d,n_d,l_d : TInterfaceElementData;
      [*] = ;
      [*] = ;      n := gGame.map.players-1;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsTable,elem_d);
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsElement,elem2_d);
      [*] = ;      _sys_FillRect(pos,0,0,elem_d.p.size.w,(n-1)*elem2_d.p.size.h);
      [*] = ;      whd := _gui_CreateScrollableCanvas_VVK('opponents',windowHandle,elem_d.align,elem_d.p,pos.size,'map.dialog',true);
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsPortrait,p_d);
      [*] = ;      p_d.p.pos.x := p_d.p_raw.pos.x-elem2_d.p_raw.pos.x;
      [*] = ;      p_d.p.pos.y := p_d.p_raw.pos.y-elem2_d.p_raw.pos.y;
      [*] = ;      p_d.p.size.w := 0;p_d.p.size.h := 0;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsFrame,f_d);
      [*] = ;      f_d.p.pos.x := f_d.p_raw.pos.x-elem2_d.p_raw.pos.x;
      [*] = ;      f_d.p.pos.y := f_d.p_raw.pos.y-elem2_d.p_raw.pos.y;
      [*] = ;      f_d.p.size.w := 0;f_d.p.size.h := 0;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsBanner,b_d);
      [*] = ;      b_d.p.pos.x := b_d.p_raw.pos.x-elem2_d.p_raw.pos.x;
      [*] = ;      b_d.p.pos.y := b_d.p_raw.pos.y-elem2_d.p_raw.pos.y;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsName,n_d);
      [*] = ;      n_d.p.pos.x := n_d.p_raw.pos.x-elem2_d.p_raw.pos.x;
      [*] = ;      n_d.p.pos.y := n_d.p_raw.pos.y-elem2_d.p_raw.pos.y;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cOpponentsLevel,l_d);
      [*] = ;      l_d.p.pos.x := l_d.p_raw.pos.x-elem2_d.p_raw.pos.x;
      [*] = ;      l_d.p.pos.y := l_d.p_raw.pos.y-elem2_d.p_raw.pos.y;
      [*] = ;
      [*] = ;      _sys_FillRect(pos,0,0,1,1);
      [*] = ;      for i:=0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         var enPlHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         var enCMode : String = GetPlayerControlModeByHandle(enPlHandle);
      [*] = ;
      [*] = ;         if plHandle <> enPlHandle then
      [*] = ;         begin
      [*] = ;            ipprofile := GetPlayerIntValueIndByHandle(enPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;            difficulty := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(enPlHandle)].basediff;
      [*] = ;            bInGame := _plr_IsInGame(enPlHandle);
      [*] = ;            treaty := gArrDiplomacy[i][gIntRegister_MapMyPlayerIndex].treaty; // 0 - never seen before on this shard
      [*] = ;
      [*] = ;            if (i > 0) and SameText(enCMode, 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               case gGame.gameType of
      [*] = ;                  gc_GameTypeHotseat : ipProfile := gArrHotseatProfiles[i].avatar;
      [*] = ;                  gc_GameTypeLanShard : ipProfile := gLanShardGame.arrLanPlayers[i].profile.avatar;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if SameText(enCMode, 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               case gGame.gameType of
      [*] = ;                  gc_GameTypeHotseat : begin
      [*] = ;                     ipprofile := gArrHotseatProfiles[i].avatar;
      [*] = ;                     sign := gArrHotseatProfiles[i].sign;
      [*] = ;                     color1 := gArrHotseatProfiles[i].color1;
      [*] = ;                     color2 := gArrHotseatProfiles[i].color2;
      [*] = ;                     name := gArrHotseatProfiles[i].name;
      [*] = ;                     portrait := 'astral.players.icon.small.'+IntToStr(ipprofile);
      [*] = ;                  end;
      [*] = ;                  gc_GameTypeLanShard : begin
      [*] = ;                     ipprofile := gLanShardGame.arrLanPlayers[i].profile.avatar;
      [*] = ;                     sign := gLanShardGame.arrLanPlayers[i].profile.sign;
      [*] = ;                     color1 := gLanShardGame.arrLanPlayers[i].profile.color1;
      [*] = ;                     color2 := gLanShardGame.arrLanPlayers[i].profile.color2;
      [*] = ;                     name := gLanShardGame.arrLanPlayers[i].profile.name;
      [*] = ;                     portrait := 'astral.players.icon.small.'+IntToStr(ipprofile);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gGame.arrplayerset[i]=0) and (treaty=0) and (bInGame) and (not SameText(enCMode, 'cmPlayer')) then
      [*] = ;               begin
      [*] = ;                  sign := -1;
      [*] = ;                  color1 := -1;
      [*] = ;                  color2 := -1;
      [*] = ;                  name := 'gui|271';
	  
      [*] = ;                  portrait := 'astral.players.icon.small.0';
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if ipProfile > 0 then
      [*] = ;                  begin
      [*] = ;                     var pPlayer : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, ipprofile);
      [*] = ;
      [*] = ;                     sign := ParserGetIntValueByKeyByHandle(pPlayer, 'Herb');
      [*] = ;                     color1 := ParserGetIntValueByKeyByHandle(pPlayer, 'Color1');
      [*] = ;                     color2 := ParserGetIntValueByKeyByHandle(pPlayer, 'Color2');
      [*] = ;                     name := GetLocaleTableListItemByID('players', IntToStr(ipprofile));
      [*] = ;                     portrait := 'astral.players.icon.small.'+IntToStr(ipprofile);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     // local lord
      [*] = ;                     j := GetPlayerIntValueIndByHandle(enPlHandle, gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;                     sign := -2; // no sign
      [*] = ;                     color1 := j-1;
      [*] = ;                     color2 := j-1;
      [*] = ;                     name := 'gui|323';
      [*] = ;                     portrait := 'astral.players.icon.small.0';
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            xhd := _gui_CreateImage_VVK('',whd,gc_gui_material_blank_0,gc_gui_align_parent_lt,pos);
      [*] = ;
      [*] = ;            _gui_CreateImage_VVK('',xhd,portrait,gc_gui_align_parent_lt,p_d.p);
      [*] = ;            _gui_CreateHerb('',xhd,sign,color1,color2,gc_gui_align_parent_lt.h,gc_gui_align_parent_lt.v,b_d.p.pos.x,b_d.p.pos.y);
      [*] = ;            _gui_CreateImage_VVK('',xhd,'gamepanel03.round.frame.79x69',gc_gui_align_parent_lt,f_d.p);
      [*] = ;            _gui_CreateText_VVK('',xhd,name,gc_gui_align_parent_lt,n_d.p,gc_gui_align_middle,n_d.font_handle,n_d.color);
      [*] = ;
      [*] = ;            if (bInGame) then
      [*] = ;               temp_str := 'difficulty|'+IntToStr(difficulty)
      [*] = ;            else
      [*] = ;               temp_str := 'gui|159';
      [*] = ;            _gui_CreateText_VVK('',xhd,temp_str,gc_gui_align_parent_lt,l_d.p,gc_gui_align_middle,l_d.font_handle,l_d.color);
      [*] = ;            pos.pos.y := pos.pos.y+elem2_d.p.size.h;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var th,w,h : Integer;
      [*] = ;   var eg_max_w : array [0..4] of Integer;
      [*] = ;
      [*] = ;   for i:=0 to 3 do
      [*] = ;      eg_max_w[i]:=max_w[i];
      [*] = ;
      [*] = ;   // summary
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEndGameSummary,elem_d);
      [*] = ;   CopyRGBColor(elem_d.color,default_text_color);
      [*] = ;   _sys_FillRect(pos,elem_d.p.pos.x+(elem_d.p.size.w div 2),elem_d.p.pos.y,1,1);
      [*] = ;   whd := _gui_CreateImage_VVK('summary',windowHandle,gc_gui_material_blank_0,elem_d.align,pos);
      [*] = ;
      [*] = ;   n := _gui_TableGetFrameWidth(gc_gui_TableStyleBorder);
      [*] = ;   th := _gui_TableGetFrameHeight(gc_gui_TableStyleBorder);
      [*] = ;
      [*] = ;   GetSummaryText(eg_game_score,eg_ruler_nick,temp_str);
      [*] = ;   gStringRegister_RulerTitle := eg_ruler_name;
      [*] = ;   gIntRegister_NumYears := eg_game_score;
      [*] = ;   StringRegister0 := temp_str;
      [*] = ;   MapExecuteState('StringReplaceParams');
      [*] = ;
      [*] = ;   temp_str := GetGUIWrappedTextFormatByFont(elem_d.font_handle,StringRegister1,elem_d.p.size.w);
      [*] = ;   GetGUIElementFontTextFormatRect(elem_d.font_handle,temp_str,w,h);
      [*] = ;   _sys_FillRect(pos,-1*(elem_d.p.size.w div 2),th,0,0);
      [*] = ;   _gui_CreateText_VVK('',whd,temp_str,gc_gui_align_parent_lt,pos,gc_gui_align_lt,elem_d.font_handle,elem_d.color);
      [*] = ;   max_w[0] := w+(n*2);
      [*] = ;   n := GetGUIElementFontHeight(elem_d.font_handle);
      [*] = ;   n := (h+n-1) div n;
      [*] = ;   n := min($40,n);
      [*] = ;
      [*] = ;   for i := 0 to n-1 do
      [*] = ;   begin
      [*] = ;      text[i] := '';font[i] := '';
      [*] = ;      AddString(text[i],' ',elem_d.font_handle);
      [*] = ;   end;
      [*] = ;   DisplayTable(whd,1,n,elem_d.font_handle,0,$24);
      [*] = ;
      [*] = ;   // stats text
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEndGameStatsTable,elem_d);
      [*] = ;   _gui_GetInterfaceElement(if_handle,cEndGameTableHeader1,elem2_d);
      [*] = ;   CopyRGBColor(elem_d.color,default_text_color);
      [*] = ;   _sys_FillRect(pos,elem_d.p.pos.x+(elem_d.p.size.w div 2),elem_d.p.pos.y,1,1);
      [*] = ;   whd := _gui_CreateImage_VVK('stats',windowHandle,gc_gui_material_blank_0,elem_d.align,pos);
      [*] = ;   SetGUIElementTag(whd,eg_game_score);
      [*] = ;
      [*] = ;   n := _gui_TableGetFrameWidth(gc_gui_TableStyleBorder);
      [*] = ;   max_w[0] := eg_max_w[0]+eg_max_w[1]+eg_max_w[2]+(n*2);
      [*] = ;   text[0] := '';font[0] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[0]);
      [*] = ;   AddString(text[0],'^c'+GetLocaleTableListItemByID('gui','281'),elem_d.font_handle);
      [*] = ;   th := DisplayTable(whd,1,1,elem_d.font_handle,0,$22);
      [*] = ;
      [*] = ;   for i:=0 to 3 do
      [*] = ;      max_w[i]:=eg_max_w[i];
      [*] = ;
      [*] = ;   for i:=0 to eg_text2_start-1 do
      [*] = ;   begin
      [*] = ;      text[i] := eg_text[i];
      [*] = ;      font[i] := '';
      [*] = ;   end;
      [*] = ;   th := DisplayTable(whd,3,eg_text2_start,elem_d.font_handle,th,0);
      [*] = ;
      [*] = ;   max_w[0] := eg_max_w[0]+eg_max_w[1]+eg_max_w[2]+(n*2);
      [*] = ;   text[0] := '';font[0] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[0]);
      [*] = ;   AddString(text[0],'^c'+GetLocaleTableListItemByID('gui','282'),elem_d.font_handle);
      [*] = ;   th := DisplayTable(whd,1,1,elem_d.font_handle,th,$2b);
      [*] = ;   max_w[0] := eg_max_w[0];
      [*] = ;
      [*] = ;   for i:=eg_text2_start to eg_text_idx-1 do
      [*] = ;   begin
      [*] = ;      text[i-eg_text2_start] := eg_text[i];
      [*] = ;      font[i-eg_text2_start] := '';
      [*] = ;   end;
      [*] = ;   th := DisplayTable(whd,3,eg_text_idx-eg_text2_start,elem_d.font_handle,th,0);
      [*] = ;
      [*] = ;   max_w[0] := eg_max_w[0]+eg_max_w[1]+n;
      [*] = ;   max_w[1] := eg_max_w[2];
      [*] = ;   text[0] := '';font[0] := elem2_d.font_handle;CopyRGBColor(elem2_d.color,font_color[0]);
      [*] = ;   AddString(text[0],'^c'+GetLocaleTableListItemByID('gui','61'),elem_d.font_handle);
      [*] = ;   AddString(text[0],'^c'+IntToStr(eg_game_score),elem_d.font_handle);
      [*] = ;   th := DisplayTable(whd,2,1,elem_d.font_handle,th,$9);
      [*] = ;
      [*] = ;   // rewards
      [*] = ;   if eg_rewards_no > 0 then
      [*] = ;   begin
      [*] = ;      var n_d,p_d : TInterfaceElementData;
      [*] = ;      var icon_pos : TRectangle;
      [*] = ;      var r_no : Integer;
      [*] = ;
      [*] = ;      _gui_GetInterfaceElement(if_handle,cRewardsTable,elem_d);
      [*] = ;      CopyRGBColor(elem_d.color,default_text_color);
      [*] = ;      _gui_GetInterfaceElement(if_handle,cRewardIcon,elem2_d);
      [*] = ;      _gui_GetInterfaceElement(if_handle,cRewardName,n_d);
      [*] = ;      _gui_GetInterfaceElement(if_handle,cRewardPoints,p_d);
      [*] = ;      w := _gui_TableGetFrameWidth(gc_gui_TableStyleBorder);
      [*] = ;      h := GetGUIElementFontHeight(elem_d.font_handle);
      [*] = ;      th := _gui_TableGetFrameHeight(gc_gui_TableStyleBorder);
      [*] = ;      n := ((elem2_d.p.size.h+(h-1)) div h);
      [*] = ;      r_no := eg_rewards_no;
      [*] = ;      //r_no := $20;
      [*] = ;      _sys_FillRect(pos,0,0,elem_d.p.size.w,r_no*(n*h+th)+th);
      [*] = ;      whd := _gui_CreateScrollableCanvas_VVK('rewards',windowHandle,elem_d.align,elem_d.p,pos.size,'map.dialog',true);
      [*] = ;
      [*] = ;      _sys_FillRect(pos,0,0,1,1);
      [*] = ;      _sys_FillRect(icon_pos,((elem2_d.p.size.w-GetGUITextureWidth('icon.medal.1')) div 2)+w,((elem2_d.p.size.h-GetGUITextureHeight('icon.medal.1')) div 2)+th,0,0);
      [*] = ;      n_d.p.pos.x := n_d.p_raw.pos.x-elem2_d.p_raw.pos.x+w;n_d.p.pos.y := n_d.p_raw.pos.y-elem2_d.p_raw.pos.y+th;
      [*] = ;      p_d.p.pos.x := p_d.p_raw.pos.x-elem2_d.p_raw.pos.x+w;p_d.p.pos.y := p_d.p_raw.pos.y-elem2_d.p_raw.pos.y+th;
      [*] = ;      max_w[0] := elem2_d.p.size.w;
      [*] = ;      max_w[1] := elem_d.p.size.w-max_w[0]-(w*3);
      [*] = ;      for i:=0 to r_no-1 do
      [*] = ;      begin
      [*] = ;         if i >= eg_rewards_no then
      [*] = ;            idx := 0
      [*] = ;         else
      [*] = ;            idx := i;
      [*] = ;         xhd := _gui_CreateImage_VVK('',whd,gc_gui_material_blank_0,gc_gui_align_parent_lt,pos);
      [*] = ;         for j:=0 to n-1 do
      [*] = ;         begin
      [*] = ;            text[j]:='';font[j]:='';
      [*] = ;            AddString(text[j],'^c ',elem_d.font_handle);
      [*] = ;            AddString(text[j],'^c ',elem_d.font_handle);
      [*] = ;         end;
      [*] = ;         if (i <> (r_no-1)) then
      [*] = ;            DisplayTable(xhd,2,n,elem_d.font_handle,0,$126)
      [*] = ;         else
      [*] = ;            DisplayTable(xhd,2,n,elem_d.font_handle,0,$124);
      [*] = ;         _gui_CreateImage_VVK('',xhd,'icon.medal.'+IntToStr(eg_rewards[idx]),gc_gui_align_parent_lt,icon_pos);
      [*] = ;         _gui_CreateText_VVK('',xhd,eg_rewards_txt[idx],gc_gui_align_parent_lt,n_d.p,gc_gui_align_middle,n_d.font_handle,n_d.color);
      [*] = ;         _gui_CreateText_VVK('',xhd,'+'+IntToStr(eg_rewards_scores[idx])+' '+GetLocaleTableListItemByID('gui', '295'),gc_gui_align_parent_lt,p_d.p,gc_gui_align_middle,p_d.font_handle,p_d.color);
      [*] = ;         pos.pos.y := pos.pos.y+n*h+th;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_FadeWindow_VVK(windowHandle,gc_gui_FadeTime0_2,0);
      [*] = ;_gui_RootWindowAddM(windowHandle);
      [*] = ;SetGUIElementPressState(windowHandle,event_name);
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

