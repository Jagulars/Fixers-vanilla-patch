section.begin
   Name = EventGameplaySettings
   UsedFileName =
   Code : struct.begin
      [*] = ;const cBtnAcceptTag = 1;
      [*] = ;const cBtnCancelTag = 2;
      [*] = ;const cBtnSetDefaultTag = 3;
      [*] = ;const cBtnGenesisMode = 4;
      [*] = ;const cCheckBoxFog = 10;
      [*] = ;const cCheckBoxDiplomacy = 11;
      [*] = ;const cCheckBoxQuickGame = 12;
      [*] = ;const cCheckBoxSandbox = 13;
      [*] = ;const cCheckBoxImprovedAI = 14;
      [*] = ;const cAllowHeroesFlagsBaseTag = 100;
      [*] = ;const cCheckBoxEndTag = 200;
      [*] = ;
      [*] = ;var pBaseWindow : Integer = _gui_GetWindowParserByName('Gameplay Settings');
      [*] = ;var pBaseChildren : Integer = ParserSelectByHandleByKey(pBaseWindow, 'Children');
      [*] = ;
      [*] = ;
      [*] = ;function GetElementHandleByName(pParent : Integer; name : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var i, pElement, pChildren : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParent)-1 do
      [*] = ;   begin
      [*] = ;      pElement := ParserSelectByHandleByIndex(pParent, i);
      [*] = ;      if SameText(ParserGetValueByKeyByHandle(pElement, 'Name'), name) then
      [*] = ;      begin
      [*] = ;         Result := ParserGetIntValueByKeyByHandle(pElement, 'Handle');
      [*] = ;         break;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if Result = 0 then
      [*] = ;      begin
      [*] = ;         pChildren := ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;         if pChildren <> 0 then
      [*] = ;            Result := GetElementHandleByName(pChildren, name);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetSectionByTag(tag : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if (tag >= cAllowHeroesFlagsBaseTag) and (tag < cCheckBoxEndTag) then
      [*] = ;   begin
      [*] = ;      Result := 0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := -1;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetCheckBoxOptionIndexByTag(pParser, searchTag : Integer; var count : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   
      [*] = ;   var section : Integer = GetSectionByTag(searchTag);
      [*] = ;   if section >= 0 then
      [*] = ;   begin
      [*] = ;      var i, pElement, tag, pChildren : Integer;
      [*] = ;      for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;      begin
      [*] = ;         pElement := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;         if ParserGetValueByKeyByHandle(pElement, 'ElementType') = 'Checkbox' then
      [*] = ;         begin
      [*] = ;            tag := ParserGetIntValueByKeyByHandle(pElement, 'Tag');
      [*] = ;            
      [*] = ;            if GetSectionByTag(tag) = section then
      [*] = ;            begin
      [*] = ;               if tag = searchTag then
      [*] = ;               begin
      [*] = ;                  Result := count;
      [*] = ;                  break;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  count := count + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      
      [*] = ;         if Result = -1 then
      [*] = ;         begin
      [*] = ;            pChildren := ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;            if pChildren <> 0 then
      [*] = ;               Result := GetCheckBoxOptionIndexByTag(pChildren, searchTag, count);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure VerifyCheckboxes(pParser : Integer);
      [*] = ;begin
      [*] = ;   var i, pElement, tag, index, count, pChildren, elmHandle, bitFlag : Integer;
      [*] = ;      
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;   begin
      [*] = ;      pElement := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;      elmHandle := ParserGetIntValueByKeyByHandle(pElement, 'Handle');
      [*] = ;      if (elmHandle <> 0) and (ParserGetValueByKeyByHandle(pElement, 'ElementType') = 'Checkbox') then
      [*] = ;      begin
      [*] = ;         tag := ParserGetIntValueByKeyByHandle(pElement, 'Tag');
      [*] = ;         case tag of
      [*] = ;            cCheckBoxFog : SetGUIElementChecked(elmHandle, gMapSettingsTmp.fog);
      [*] = ;            cCheckBoxDiplomacy : SetGUIElementChecked(elmHandle, gMapSettingsTmp.diplomacy);
      [*] = ;            cCheckBoxQuickGame : SetGUIElementChecked(elmHandle, gMapSettingsTmp.quickgame);
      [*] = ;            cCheckBoxSandbox : SetGUIElementChecked(elmHandle, gMapSettingsTmp.sandbox);
      [*] = ;            cCheckBoxImprovedAI : SetGUIElementChecked(elmHandle, gMapSettingsTmp.improvedai);
      [*] = ;            else // allowed heroes
      [*] = ;            begin
      [*] = ;               count := 0;
      [*] = ;               index := GetCheckBoxOptionIndexByTag(pBaseChildren, tag, count);
      [*] = ;               if index >= 0 then
      [*] = ;               begin
      [*] = ;                  bitFlag := _misc_GetBitFlagByIndex(index);
      [*] = ;                  SetGUIElementChecked(elmHandle, (gMapSettingsTmp.allowedheroes and bitFlag) = 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      pChildren := ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;      if pChildren <> 0 then
      [*] = ;         VerifyCheckboxes(pChildren);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String = GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;
      [*] = ;if status = 'Initialize' then
      [*] = ;begin
      [*] = ;   if (elmName='sandbox') then
      [*] = ;   begin
      [*] = ;      if (gGame.gameType <> gc_GameTypeCustom) and (gGame.gameType <> gc_GameTypeHotseat) then
      [*] = ;      begin
      [*] = ;         SetGUIElementVisible(elmHandle, False);
      [*] = ;         SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (elmName='improvedai') then
      [*] = ;   begin
      [*] = ;      if (gGame.gameType <> gc_GameTypeLanShard) then
      [*] = ;      begin
      [*] = ;         SetGUIElementVisible(elmHandle, False);
      [*] = ;         SetGUIAllowEvents(elmHandle, False, False, False);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      VerifyCheckboxes(pBaseChildren);
      [*] = ;      
      [*] = ;      // close in empty space left by invisible checkbox
      [*] = ;      if (not GetGUIElementVisible(GetElementHandleByName(pBaseChildren, 'sandbox'))) and (not GetGUIElementVisible(GetElementHandleByName(pBaseChildren, 'improvedai'))) then
      [*] = ;      begin
      [*] = ;         var elmAllowedHeroes : Integer = GetElementHandleByName(pBaseChildren, 'allowed_heroes');
      [*] = ;         SetGUIElementPositionY(elmAllowedHeroes, GetGUIElementPositionY(elmAllowedHeroes) - 20);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   var bChecked : Boolean = (not GetGUIElementChecked(elmHandle));
      [*] = ;   
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         if gMapSettingsTmp.allowedheroes >= $ffff then
      [*] = ;         begin
      [*] = ;            gMapSettingsTmp.allowedheroes := 0;
      [*] = ;            VerifyCheckboxes(pBaseChildren);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _misc_AssignGlobalVars('gMapSettingsTmp', 'gMapSettings');
      [*] = ;            _gui_FadeElement(GetGUIElementIndexByNameParent('Gameplay Settings', _gui_GetLayerI()), gc_gui_FadeTime0_4, false, true, true);
      [*] = ;            
      [*] = ;            if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;               _inet_SendShardGameSettings();
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _misc_AssignGlobalVars('gMapSettings', 'gMapSettingsTmp');
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('Gameplay Settings', _gui_GetLayerI()),gc_gui_FadeTime0_4);
      [*] = ;      end;
      [*] = ;      cBtnSetDefaultTag : begin
      [*] = ;         gMapSettingsTmp.allowedheroes := 0;
      [*] = ;         gMapSettingsTmp.fog := true;
      [*] = ;         gMapSettingsTmp.diplomacy := true;
      [*] = ;         gMapSettingsTmp.quickgame := false;
      [*] = ;         gMapSettingsTmp.sandbox := false;
      [*] = ;         gMapSettingsTmp.improvedai := false;
      [*] = ;         VerifyCheckboxes(pBaseChildren);
      [*] = ;      end;
      [*] = ;      cBtnGenesisMode : begin
      [*] = ;         gMapSettingsTmp.genesismode := gMapSettings.genesismode;
      [*] = ;         StringRegister0 := 'Genesis Mode';
      [*] = ;         GUIExecuteState('CreateWindowFromParser');
      [*] = ;      end;
      [*] = ;      cCheckBoxFog : begin
      [*] = ;         gMapSettingsTmp.fog := bChecked;
      [*] = ;         if (not bChecked) then
      [*] = ;            gMapSettingsTmp.diplomacy := False;
      [*] = ;         VerifyCheckboxes(pBaseChildren);
      [*] = ;      end;
      [*] = ;      cCheckBoxDiplomacy : begin
      [*] = ;         gMapSettingsTmp.diplomacy := bChecked;
      [*] = ;         if (bChecked) then
      [*] = ;            gMapSettingsTmp.fog := True;
      [*] = ;         VerifyCheckboxes(pBaseChildren);
      [*] = ;      end;
      [*] = ;      cCheckBoxQuickGame : begin
      [*] = ;         gMapSettingsTmp.quickgame := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cCheckBoxSandbox : begin
      [*] = ;         gMapSettingsTmp.sandbox := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      cCheckBoxImprovedAI : begin
      [*] = ;         gMapSettingsTmp.improvedai := bChecked;
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (tag >= cAllowHeroesFlagsBaseTag) and (tag < cCheckBoxEndTag) then
      [*] = ;         begin
      [*] = ;            var count : Integer = 0;
      [*] = ;            var ind : Integer = GetCheckBoxOptionIndexByTag(pBaseChildren, tag, count);
      [*] = ;            gMapSettingsTmp.allowedheroes := _misc_GetBitFlagByIndex(ind) xor gMapSettingsTmp.allowedheroes;
      [*] = ;            
      [*] = ;            SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

