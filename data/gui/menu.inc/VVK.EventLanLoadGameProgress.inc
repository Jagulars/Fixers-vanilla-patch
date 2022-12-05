section.begin
   Name = VVK.EventLanLoadGameProgress
   UsedFileName =
   Code : struct.begin
      [*] = ;const cBtnOK = 101;
      [*] = ;const cBtnClose = 102;
      [*] = ;const cBtnRefresh = 103;
      [*] = ;
      [*] = ;const cWindowTemplateName = 'lan_load_game_progress';
      [*] = ;const cBadgeHeaderTexName = 'element.strip.240';
      [*] = ;
      [*] = ;const cPlayerIcon = $18;
      [*] = ;const cPlayerNameStrip = $17;
      [*] = ;const cPlayerCOA = $16;
      [*] = ;const cPlayerBadge = $8;
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;if (GetValueByName('Press')='c') then
      [*] = ;begin
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;   case tag of
      [*] = ;      cBtnClose, gc_gui_hotkey_btnEscape, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var whd : Integer = _gui_RootWindowGetBase(GetIntValueByName('ElementHandle'));
      [*] = ;         LanTerminateGame();
      [*] = ;         _gui_RootWindowRemoveWithFade(whd,gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;      cBtnOK, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var whd : Integer = _gui_RootWindowGetBase(GetIntValueByName('ElementHandle'));
      [*] = ;         var pLanGame,pTmp : Integer;
      [*] = ;         var mapname : String;
      [*] = ;
      [*] = ;         pTmp := _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;         LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(),pTmp);
      [*] = ;         mapname := ParserGetValueByKeyByHandle(pTmp,'MapName');
      [*] = ;
      [*] = ;         pLanGame := _misc_ParserGetOrCreateByKey('ellgp_langame', True);
      [*] = ;         if (_inet_IsSaveGameMapName(mapname)) and (GetLanMode() > 1) then
      [*] = ;         begin
      [*] = ;            ParserSetValueByKeyByHandle(pLanGame, 'SaveGame', mapname);
      [*] = ;
      [*] = ;            _lan_LanSendParser(gc_LAN_START, pLanGame);
      [*] = ;            LanLockServer();
      [*] = ;            IntRegister0 := pLanGame;
      [*] = ;            GUIExecuteState('DoInetShardGame');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            LanTerminateGame();
      [*] = ;         _gui_RootWindowRemoveWithFade(whd,gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;      cBtnRefresh : begin
      [*] = ;         var whd : Integer = _gui_GetWindow(cLanLoadGameSyncName);
      [*] = ;         var mapname : String;
      [*] = ;         var p,i,j,badges_no,total_players,id,bhd,thd : Integer;
      [*] = ;         var if_handle : Integer = _gui_GetInterfaceWindowHandle(cWindowTemplateName);
      [*] = ;         var elem_d : TInterfaceElementData;
      [*] = ;         var badge : TElementSize;
      [*] = ;         var icon_pos,name_pos,coa_pos : TelementPos;
      [*] = ;         var info : String;
      [*] = ;         var txt_pos : TRectangle;
      [*] = ;         var d_client_id : Integer = GetIntValueByName('DisconnectedClientID');
      [*] = ;
      [*] = ;         icon_pos.x := _gui_ie_GetOffsetX(if_handle,cPlayerIcon,cPlayerBadge,false);
      [*] = ;         icon_pos.y := _gui_ie_GetOffsetY(if_handle,cPlayerIcon,cPlayerBadge,false);
      [*] = ;
      [*] = ;         name_pos.x := _gui_ie_GetOffsetX(if_handle,cPlayerNameStrip,cPlayerBadge,false);
      [*] = ;         name_pos.y := _gui_ie_GetOffsetY(if_handle,cPlayerNameStrip,cPlayerBadge,false);
      [*] = ;
      [*] = ;         coa_pos.x := _gui_ie_GetOffsetX(if_handle,cPlayerCOA,cPlayerBadge,false);
      [*] = ;         coa_pos.y := _gui_ie_GetOffsetY(if_handle,cPlayerCOA,cPlayerBadge,false);
      [*] = ;
      [*] = ;         thd := GetGUIElementIndexByNameParent('badge_0',whd);
      [*] = ;         if thd > 0 then
      [*] = ;         begin
      [*] = ;            badge.w := GetGUIElementWidth(thd);
      [*] = ;            badge.h := GetGUIElementHeight(thd);
      [*] = ;         end;
      [*] = ;         
      [*] = ;         var modVersion : String; 
      [*] = ;         var myModVersion : String = gc_DataModName + '_' + gc_DataModVersion;
      [*] = ;         var sameGameVersion : Boolean = true;
      [*] = ;
      [*] = ;         p := _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;         LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(),p);
      [*] = ;         mapname := ParserGetValueByKeyByHandle(p,'MapName');
      [*] = ;
      [*] = ;         p := _misc_ParserGetOrCreateByKey('client_info', True);
      [*] = ;         _gui_GetInterfaceElement(if_handle,cPlayerNameStrip,elem_d);
      [*] = ;         badges_no := _sa_GetAsInt(GetGUIElementStringTag(whd),0);
      [*] = ;         if _log then _log_values('BADGES_NO',badges_no,0,0,0,0,0);
      [*] = ;         for i:=0 to badges_no-1 do
      [*] = ;         begin
      [*] = ;            thd := GetGUIElementIndexByNameParent('badge_'+IntToStr(i),whd);
      [*] = ;            if thd <> 0 then
      [*] = ;            begin
      [*] = ;               id := GetGUIElementTag(thd);
      [*] = ;               RemoveGUIChildren(thd);
      [*] = ;               ParserClearByHandle(p);
      [*] = ;               if id <> d_client_id then
      [*] = ;                  LanPublicServerGetClientInfoToParserByClientID(id,p);
      [*] = ;
      [*] = ;               _sys_FillRect(txt_pos,name_pos.x,name_pos.y,0,0);
      [*] = ;               bhd := _gui_CreateImage_VVK('',thd,cBadgeHeaderTexName,gc_gui_align_parent_lt,txt_pos);
      [*] = ;               _sys_FillRect(txt_pos,0,0,0,0);
      [*] = ;               var nick : String = ParserGetValueByKeyByHandle(p, 'Nick');
      [*] = ;               if nick = '' then
      [*] = ;                  nick := '????'; // not logged in yet
      [*] = ;               _gui_CreateText_VVK('',bhd,nick,gc_gui_align_parent_m,txt_pos,gc_gui_align_middle,elem_d.font_handle,elem_d.color);
      [*] = ;
      [*] = ;               info := ParserGetValueByKeyByHandle(p, 'Info');
      [*] = ;               if _log then _log_gui('LanLoadProgress player id: '+IntToStr(id)+' , Nick: '+ParserGetValueByKeyByHandle(p, 'Nick')+', Info: '+info);
      [*] = ;
      [*] = ;               _sys_FillRect(txt_pos,icon_pos.x,icon_pos.y,0,0);
      [*] = ;               _gui_CreateImage_VVK('',thd,'astral.players.icon.small.'+IntToStr(_sa_GetAsInt(info,3)),gc_gui_align_parent_lt,txt_pos);
      [*] = ;               _gui_CreateHerb('', thd, _sa_GetAsInt(info, 2), _sa_GetAsInt(info, 0), _sa_GetAsInt(info, 1), 'halParentLeft', 'valParentTop', coa_pos.x, coa_pos.y);
      [*] = ;
      [*] = ;               if (nick <> '????') and (_sa_GetAsInt(info, 6) = 1) then
      [*] = ;               begin
      [*] = ;                  modVersion := '';
      [*] = ;                  _inet_GetClientModVersion(info, modVersion);
      [*] = ;                  if not SameText(modVersion, myModVersion) then
      [*] = ;                     sameGameVersion := false;
      [*] = ;               end;
      [*] = ;
      [*] = ;               _sys_FillRect(txt_pos,0,0,badge.w,badge.h);
      [*] = ;               bhd := _gui_CreateImage_VVK('fade',thd,'misc.blank.black.alpha.1',gc_gui_align_parent_lt,txt_pos);
      [*] = ;               SetGUIElementUserBlend(bhd,0.7);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         total_players := 0;
      [*] = ;         for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;         begin
      [*] = ;            id := LanGetClientIDByIndex(i);
      [*] = ;            if (id<>0) then
      [*] = ;            begin
      [*] = ;               for j := 0 to badges_no-1 do
      [*] = ;               begin
      [*] = ;                  bhd := GetGUIElementIndexByNameParent('badge_'+IntToStr(j),whd);
      [*] = ;                  if (GetGUIElementTag(bhd) = id) and (id <> d_client_id) then
      [*] = ;                  begin
      [*] = ;                     total_players := total_players + 1;
      [*] = ;                     RemoveGUIElement(GetGUIElementIndexByNameParent('fade',bhd));
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         bhd := GetGUIElementIndexByNameParent('accept_placeholder.frame.button',whd);
      [*] = ;         if bhd <> 0 then
      [*] = ;         begin
      [*] = ;            if not sameGameVersion then
      [*] = ;            begin
      [*] = ;               SetGUIElementEnabled(bhd,false);
      [*] = ;               SetGUIElementHint(bhd, 'menu|multiplayer_version_reminder');
      [*] = ;            end    
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               SetGUIElementHint(bhd, 'map.event|28.1');
      [*] = ;               if total_players <> badges_no then
      [*] = ;                  SetGUIElementEnabled(bhd,false)
      [*] = ;               else
      [*] = ;                  SetGUIElementEnabled(bhd,true);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end