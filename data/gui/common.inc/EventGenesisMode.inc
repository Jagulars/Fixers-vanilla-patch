section.begin
   Name = EventGenesisMode
   Code : struct.begin
      [*] = ;const cAcceptBtnTag = 1;
      [*] = ;const cCancelBtnTag = 2;
      [*] = ;const cResetBtnTag = 3;
      [*] = ;const cEmptyBtnTag = 4;
      [*] = ;const cCheckBoxStartTag = 10;
      [*] = ;const cDifficultyTag = 10;
      [*] = ;const cProvinceDetailsTag = 11;
      [*] = ;const cRearAttackTag = 12;
      [*] = ;const cAstralEnergySpellTag = 13;
      [*] = ;//const cTwoWeaponsTag = 14;
      [*] = ;const cUnitsBaseTag = 100;
      [*] = ;const cSitesBaseTag = 200;
      [*] = ;const cSpellsBaseTag = 300;
      [*] = ;const cGuardTypesBaseTag = 400;
      [*] = ;const cGuardTypes2BaseTag = 500;
      [*] = ;const cUpgradesBaseTag = 600;
      [*] = ;const cAbilitiesBaseTag = 900;
      [*] = ;const cCheckBoxEndTag = 1100;
      [*] = ;
      [*] = ;var pBaseWindow : Integer = ParserSelectByHandleByKey(_gui_GetWindowParserByName('Genesis Mode'), 'Children');
      [*] = ;
      [*] = ;function GetSectionStartTag(section : Integer) : Integer;
      [*] = ;begin
      [*] = ;   case section of
      [*] = ;      0 : Result := cCheckBoxStartTag;
      [*] = ;      1 : Result := cUnitsBaseTag;
      [*] = ;      2 : Result := cSitesBaseTag;
      [*] = ;      3 : Result := cSpellsBaseTag;
      [*] = ;      4 : Result := cGuardTypesBaseTag;
      [*] = ;      5 : Result := cGuardTypes2BaseTag; // too many options to fit in one bitflag
      [*] = ;      6 : Result := cUpgradesBaseTag;
      [*] = ;      7 : Result := cAbilitiesBaseTag;
      [*] = ;      else Result := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetSectionByTag(tag : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   
      [*] = ;   if (tag >= cCheckBoxStartTag) and (tag < cCheckBoxEndTag) then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      for i := 7 downto 0 do
      [*] = ;      if tag >= GetSectionStartTag(i) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetCheckBoxOptionCount(pParser, section : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var i, pElement, pChildren : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;   begin
      [*] = ;      pElement := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pElement, 'ElementType') = 'Checkbox' then
      [*] = ;      begin
      [*] = ;         if GetSectionByTag(ParserGetIntValueByKeyByHandle(pElement, 'Tag')) = section then
      [*] = ;            Result := Result + 1;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      pChildren := ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;      if pChildren <> 0 then
      [*] = ;         Result := Result + GetCheckBoxOptionCount(pChildren, section);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetCheckBoxOptionTagByIndex(pParser, index, section : Integer; var count : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var i, pElement, tag, pChildren : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;   begin
      [*] = ;      pElement := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pElement, 'ElementType') = 'Checkbox' then
      [*] = ;      begin
      [*] = ;         tag := ParserGetIntValueByKeyByHandle(pElement, 'Tag');
      [*] = ;         if GetSectionByTag(tag) = section then
      [*] = ;         begin
      [*] = ;            if count = index then
      [*] = ;            begin
      [*] = ;               Result := tag;
      [*] = ;               break;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               count := count + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if Result = 0 then
      [*] = ;      begin
      [*] = ;         pChildren := ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;         if pChildren <> 0 then
      [*] = ;            Result := GetCheckBoxOptionTagByIndex(pChildren, index, section, count);
      [*] = ;      end;
      [*] = ;   end;
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
      [*] = ;            if GetSectionByTag(tag) = section then
      [*] = ;            begin
      [*] = ;               if tag = searchTag then
      [*] = ;               begin
      [*] = ;                  Result := count;
      [*] = ;                  break;
      [*] = ;               end
      [*] = ;              else
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
      [*] = ;   var i, pElement, tag, section, index, count, pChildren, elmHandle, bitFlag : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;   begin
      [*] = ;      pElement := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;      elmHandle := ParserGetIntValueByKeyByHandle(pElement, 'Handle');
      [*] = ;      if (elmHandle <> 0) and (ParserGetValueByKeyByHandle(pElement, 'ElementType') = 'Checkbox') then
      [*] = ;      begin
      [*] = ;         tag := ParserGetIntValueByKeyByHandle(pElement, 'Tag');
      [*] = ;         section := GetSectionByTag(tag);
      [*] = ;         count := 0;
      [*] = ;         index := GetCheckBoxOptionIndexByTag(pBaseWindow, tag, count);
      [*] = ;         if index >= 0 then
      [*] = ;         begin
      [*] = ;            bitFlag := _misc_GetBitFlagByIndex(index);
      [*] = ;            SetGUIElementChecked(elmHandle, (_sa_GetAsInt(gMapSettingsTmp.genesismode, section) and bitFlag) = 0);
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
      [*] = ;procedure ConvertBitFlagToIDs(section, pParser : Integer); 
      [*] = ;begin
      [*] = ;   var i, tag, workInd, pChild : Integer;
      [*] = ;   var flags : Integer = _sa_GetAsInt(gGame.genesismode, section);
      [*] = ;   var count : Integer = GetCheckBoxOptionCount(pBaseWindow, section);
      [*] = ;   for i := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      if (flags and _misc_GetBitFlagByIndex(i)) > 0 then
      [*] = ;      begin
      [*] = ;         workInd := 0;
      [*] = ;         tag := GetCheckBoxOptionTagByIndex(pBaseWindow, i, section, workInd);
      [*] = ;         if tag > 0 then
      [*] = ;         begin
      [*] = ;            pChild := ParserAddChildByIndex(pParser, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pChild, 'ID', tag - GetSectionStartTag(section));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;if gBoolRegister_ConvertGenesisMode then
      [*] = ;begin
      [*] = ;   gBoolRegister_ConvertGenesisMode := False;
      [*] = ;   
      [*] = ;   var pBanData : Integer = _misc_ParserGetOrCreateByKey('ban_data', false);
      [*] = ;   var pUnits : Integer = _pars_SelectOrCreateByKey(pBanData, 'Units');
      [*] = ;   var pSites : Integer = _pars_SelectOrCreateByKey(pBanData, 'Sites');
      [*] = ;   var pSpells : Integer = _pars_SelectOrCreateByKey(pBanData, 'Spells');
      [*] = ;   var pGuardTypes : Integer = _pars_SelectOrCreateByKey(pBanData, 'GuardTypes');
      [*] = ;   var pUpgrades : Integer = _pars_SelectOrCreateByKey(pBanData, 'Upgrades');
      [*] = ;   var pAbilities : Integer = _pars_SelectOrCreateByKey(pBanData, 'Abilities');
      [*] = ;   
      [*] = ;   ConvertBitFlagToIDs(1, pUnits);
      [*] = ;   ConvertBitFlagToIDs(2, pSites);
      [*] = ;   ConvertBitFlagToIDs(3, pSpells);
      [*] = ;   ConvertBitFlagToIDs(4, pGuardTypes);
      [*] = ;   ConvertBitFlagToIDs(5, pGuardTypes);
      [*] = ;   ConvertBitFlagToIDs(6, pUpgrades);
      [*] = ;   ConvertBitFlagToIDs(7, pAbilities);
      [*] = ;end
      [*] = ;else
      [*] = ;if (GetValueByName('Status') = 'Initialize') then
      [*] = ;begin
      [*] = ;   if tag = 0 then
      [*] = ;      VerifyCheckboxes(pBaseWindow)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      procedure Deactivate(elmHandle : Integer); // this doesn't really deactivate anything, just makes it visually clear that they are unavailable. In actuality, they are banned in DataBanReplacement.inc
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;         SetGUIElementHint(elmHandle, 'menu|dlc_required');
      [*] = ;      end;
      [*] = ;      
      [*] = ;      var section : Integer = GetSectionByTag(tag);
      [*] = ;      var id : Integer = tag - GetSectionStartTag(section);
      [*] = ;      var key : String = '';
      [*] = ;      
      [*] = ;      var pParser : Integer;
      [*] = ;      case section of
      [*] = ;         1 : begin 
      [*] = ;            pParser := gPrototypeData.units.handle;
      [*] = ;            key := 'UnitID';
      [*] = ;         end;
      [*] = ;         2 : begin 
      [*] = ;            pParser := gPrototypeData.sites.handle;
      [*] = ;            key := 'SiteID';
      [*] = ;         end;
      [*] = ;         3 : begin 
      [*] = ;            pParser := gPrototypeData.spells.handle;
      [*] = ;            key := 'SpellID';
      [*] = ;         end;
      [*] = ;         4,5 : begin 
      [*] = ;            pParser := gPrototypeData.guardtypes.handle;
      [*] = ;            key := 'GuardType';
      [*] = ;         end;
      [*] = ;         6 : begin 
      [*] = ;            pParser := gPrototypeData.unitupgrades.handle;
      [*] = ;            key := 'UpgradeID';
      [*] = ;         end;
      [*] = ;         7 : begin 
      [*] = ;            pParser := gPrototypeData.abilities.handle;
      [*] = ;            key := 'AbilityID';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if pParser <> 0 then
      [*] = ;      begin
      [*] = ;         var i, pThing, tid : Integer;
      [*] = ;         for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;         begin
      [*] = ;            pThing := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;            tid := ParserGetIntValueByKeyByHandle(pThing, key);
      [*] = ;            if (tid < 0) and (Round(Abs(tid)) = id) then
      [*] = ;            begin
      [*] = ;               Deactivate(elmHandle);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         // deactivate unit upgrades that upgrade to unavailable units
      [*] = ;         if key = 'UpgradeID' then
      [*] = ;         begin
      [*] = ;            pParser := ParserSelectByHandleByIndex(gPrototypeData.unitupgrades.handle, id);
      [*] = ;            pParser := ParserSelectByHandleByKey(pParser, 'Upgrades');
      [*] = ;            for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;            begin
      [*] = ;               pThing := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;               if ParserGetIntValueByKeyByHandle(pThing, 'AbilityID') = 62 then
      [*] = ;               begin
      [*] = ;                  pThing := ParserSelectByHandleByIndex(gPrototypeData.units.handle, ParserGetIntValueByKeyByHandle(pThing, 'Quantity'));
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pThing, 'UnitID') < 0 then
      [*] = ;                  begin
      [*] = ;                     Deactivate(elmHandle);
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (GetValueByName('Press') = 'c') then
      [*] = ;begin
      [*] = ;   var section : Integer = GetSectionByTag(tag);
      [*] = ;   if section >= 0 then
      [*] = ;   begin
      [*] = ;      var workInd : Integer = 0;
      [*] = ;      var index : Integer = GetCheckBoxOptionIndexByTag(pBaseWindow, tag, workInd);
      [*] = ;      
      [*] = ;      if index >= 0 then
      [*] = ;      begin
      [*] = ;         var bitFlag : Integer = _misc_GetBitFlagByIndex(index);
      [*] = ;         _sa_SetIntAtIndex(gMapSettingsTmp.genesismode, section, _sa_GetAsInt(gMapSettingsTmp.genesismode, section) xor bitFlag);
      [*] = ;            
      [*] = ;         var bChecked : Boolean = not GetGUIElementChecked(elmHandle);
      [*] = ;         SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case tag of
      [*] = ;         cAcceptBtnTag : begin
      [*] = ;            gMapSettings.genesismode := gMapSettingsTmp.genesismode;
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('Genesis Mode'), gc_gui_FadeTime0_2);
      [*] = ;         end;
      [*] = ;         cCancelBtnTag : 
      [*] = ;         begin
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('Genesis Mode'), gc_gui_FadeTime0_2);
      [*] = ;         end;
      [*] = ;         cResetBtnTag : 
      [*] = ;         begin
      [*] = ;            gMapSettingsTmp.genesismode := '0|0|0|0|0|0|0|0';
      [*] = ;            VerifyCheckboxes(pBaseWindow);
      [*] = ;         end;
      [*] = ;         cEmptyBtnTag : 
      [*] = ;         begin
      [*] = ;            var i, bitFlag : Integer;
      [*] = ;            for i := 0 to 7 do
      [*] = ;            begin
      [*] = ;               bitFlag := _misc_GetBitFlagByIndex(GetCheckBoxOptionCount(pBaseWindow, i)+1) - 1;
      [*] = ;               _sa_SetIntAtIndex(gMapSettingsTmp.genesismode, i, bitFlag);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            VerifyCheckboxes(pBaseWindow);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
   struct.end
section.end

