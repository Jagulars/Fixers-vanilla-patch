section.begin
   Name = DataBanReplacement
   Description : struct.begin
      [*] = ;IntRegister0 - replacement parser
   struct.end
   Code : struct.begin
      [*] = ;var pReplacementData : Integer = IntRegister0;
      [*] = ;var bLoad : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var pBanData : Integer = _misc_ParserGetOrCreateByKey('ban_data', false);
      [*] = ;var pBannedUnits : Integer = _pars_SelectOrCreateByKey(pBanData, 'Units');
      [*] = ;var pBannedSites : Integer = _pars_SelectOrCreateByKey(pBanData, 'Sites');
      [*] = ;var pBannedSpells : Integer = _pars_SelectOrCreateByKey(pBanData, 'Spells');
      [*] = ;var pBannedGuardTypes : Integer = _pars_SelectOrCreateByKey(pBanData, 'GuardTypes');
      [*] = ;var pBannedGuards : Integer = _pars_SelectOrCreateByKey(pBanData, 'Guards');
      [*] = ;var pBannedNeutralUnits : Integer = _pars_SelectOrCreateByKey(pBanData, 'GuardUnits');
      [*] = ;var pBannedUpgrades : Integer = _pars_SelectOrCreateByKey(pBanData, 'Upgrades');
      [*] = ;var pBannedAbilities : Integer = _pars_SelectOrCreateByKey(pBanData, 'Abilities');
      [*] = ;var pBannedItems : Integer = _pars_SelectOrCreateByKey(pBanData, 'Items');
      [*] = ;
      [*] = ;var i, j, k, h, id, pProto, pParser, pChild, pGuards, pItems, pUpgrades : Integer;
      [*] = ;var bReplacement : Boolean;
      [*] = ;
      [*] = ;procedure Ban(pParser, id : Integer);
      [*] = ;begin
      [*] = ;   if not _pars_ExistsByID(pParser, id) then
      [*] = ;   begin
      [*] = ;      pParser := ParserAddChildByIndex(pParser, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pParser, 'ID', id);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// ban unavailable data
      [*] = ;pParser := gPrototypeData.units.handle;
      [*] = ;for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;begin
      [*] = ;   id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pParser, i), 'UnitID');
      [*] = ;   if id < 0 then
      [*] = ;   begin
      [*] = ;      Ban(pBannedUnits, -id);
      [*] = ;      Ban(pBannedNeutralUnits, -id);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;pParser := gPrototypeData.spells.handle;
      [*] = ;for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;begin
      [*] = ;   id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pParser, i), 'SpellID');
      [*] = ;   if id < 0 then
      [*] = ;   begin
      [*] = ;      Ban(pBannedSpells, -id);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;pParser := gPrototypeData.items.handle;
      [*] = ;for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;begin
      [*] = ;   id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pParser, i), 'ItemID');
      [*] = ;   if id < 0 then
      [*] = ;   begin
      [*] = ;      Ban(pBannedItems, -id);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// ban items that allow recruitment of banned units.
      [*] = ;for i := 1 to gPrototypeData.items.number-1 do
      [*] = ;begin
      [*] = ;   id := _misc_GetParserAbilityPower(ParserSelectByHandleByIndex(gPrototypeData.items.handle, i), 84);
      [*] = ;   if (id > 0) and _pars_ExistsByID(pBannedUnits, id) then
      [*] = ;      Ban(pBannedItems, i);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// ban spell scrolls
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedSpells)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedSpells, i);
      [*] = ;   Ban(pBannedItems, ParserGetIntValueByKeyByHandle(pChild, 'ID') + gPrototypeData.items.number); // spell scroll indices start after normal items 
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// replace units based on banned abilities
      [*] = ;pParser := ParserSelectByHandleByKey(pReplacementData, 'Units'); 
      [*] = ;for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;   if _pars_ExistsByID(pBannedAbilities, ParserGetIntValueByKeyByHandle(pChild, 'TriggerAbilityID')) then
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.units.handle, ParserGetIntValueByKeyByHandle(pChild, 'UnitID'));
      [*] = ;      ParserCopyFromByHandle(pChild);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// replace items based on banned abilities
      [*] = ;pParser := ParserSelectByHandleByKey(pReplacementData, 'Items'); 
      [*] = ;for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;   if _pars_ExistsByID(pBannedAbilities, ParserGetIntValueByKeyByHandle(pChild, 'TriggerAbilityID')) then
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.items.handle, ParserGetIntValueByKeyByHandle(pChild, 'ItemID'));
      [*] = ;      ParserCopyFromByHandle(pChild);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedAbilities)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedAbilities, i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(pChild, 'ID');
      [*] = ;   
      [*] = ;   // ban items that grant a banned ability
      [*] = ;   for j := 1 to gPrototypeData.items.number-1 do
      [*] = ;   begin
      [*] = ;      pParser := ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gPrototypeData.items.handle, j), 'Abilities');
      [*] = ;      for k := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;      if ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pParser, k), 'AbilityID') = id then
      [*] = ;         Ban(pBannedItems, j);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // ban upgrades that grant a banned ability
      [*] = ;   for j := 1 to gPrototypeData.unitupgrades.number-1 do
      [*] = ;   begin
      [*] = ;      pParser := ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gPrototypeData.unitupgrades.handle, j), 'Upgrades');
      [*] = ;      for k := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;      if ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pParser, k), 'AbilityID') = id then
      [*] = ;         Ban(pBannedUpgrades, j);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// delete banned upgrades from unit data
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedUpgrades)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedUpgrades, i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(pChild, 'ID');
      [*] = ;   
      [*] = ;   for j := 1 to gPrototypeData.units.number-1 do
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.units.handle, j);
      [*] = ;      
      [*] = ;      pUpgrades := ParserSelectByHandleByKey(pProto, 'StartUpgrades');
      [*] = ;      for k := ParserGetCountByHandle(pUpgrades)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pChild := ParserSelectByHandleByIndex(pUpgrades, k);
      [*] = ;         if ParserGetIntValueByKeyByHandle(pChild, 'UpgradeID') = id then
      [*] = ;         begin
      [*] = ;            ParserFreeByHandle(pChild);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      pUpgrades := ParserSelectByHandleByKey(pProto, 'UnitUpgrades');
      [*] = ;      for k := 0 to ParserGetCountByHandle(pUpgrades)-1 do
      [*] = ;      begin
      [*] = ;         pParser := ParserSelectByHandleByKey(ParserSelectByHandleByIndex(pUpgrades, k), 'Upgrades');
      [*] = ;         for h := ParserGetCountByHandle(pParser)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            pChild := ParserSelectByHandleByIndex(pParser, h);
      [*] = ;            if ParserGetIntValueByKeyByHandle(pChild, 'UpgradeID') = id then
      [*] = ;            begin
      [*] = ;               ParserFreeByHandle(pChild);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// delete banned items from unit loot data
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedItems)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedItems, i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(pChild, 'ID');
      [*] = ;   
      [*] = ;   for j := 1 to gPrototypeData.units.number-1 do
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.units.handle, j);
      [*] = ;      
      [*] = ;      pParser := ParserSelectByHandleByKey(pProto, 'UnitLoots');
      [*] = ;      for k := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;      begin
      [*] = ;         pItems := ParserSelectByHandleByKey(ParserSelectByHandleByIndex(pParser, k), 'Items');
      [*] = ;         for h := 0 to ParserGetCountByHandle(pItems)-1 do
      [*] = ;         begin
      [*] = ;            pChild := ParserSelectByHandleByIndex(pItems, h);
      [*] = ;            if ParserGetIntValueByKeyByHandle(pChild, 'ItemID') = id then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pChild, 'ItemID', 0);
      [*] = ;               ParserSetIntValueByKeyByHandle(pChild, 'Possibility', 0);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// ban or replace guards
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedGuardTypes)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedGuardTypes, i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(pChild, 'ID');
      [*] = ;   
      [*] = ;   bReplacement := false;
      [*] = ;   
      [*] = ;   pParser := ParserSelectByHandleByKey(pReplacementData, 'Guards');
      [*] = ;   pGuards := ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gPrototypeData.guardTypes.handle, id), 'GuardID');
      [*] = ;   for [MAIN]j := 0 to ParserGetCountByHandle(pGuards)-1 do
      [*] = ;   begin
      [*] = ;      id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGuards, j), 'GuardID');
      [*] = ;      for k := 0 to ParserGetCountByHandle(pParser)-1 do // check replacement data for guard replacement
      [*] = ;      begin
      [*] = ;         pChild := ParserSelectByHandleByIndex(pParser, k);
      [*] = ;         if ParserGetIntValueByKeyByHandle(pChild, 'GuardID') = id then
      [*] = ;         begin
      [*] = ;            pProto := ParserSelectByHandleByIndex(gPrototypeData.guards.handle, id);
      [*] = ;            ParserCopyFromByHandle(pChild);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;            bReplacement := true;
      [*] = ;            continue(Main);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // if replacement is not found for any of the 4 tiers, then ban all of them. If even one is found, then only replace what can be replaced and ban nothing.
      [*] = ;   if (not bReplacement) then
      [*] = ;   for j := 0 to ParserGetCountByHandle(pGuards)-1 do
      [*] = ;      Ban(pBannedGuards, ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGuards, j), 'GuardID'));
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedGuardTypes)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedGuardTypes, i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(pChild, 'ID'); 
      [*] = ;   
      [*] = ;   // delete banned guards from site data
      [*] = ;   for [MAIN]j := 1 to gPrototypeData.sites.number-1 do
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.sites.handle, j);
      [*] = ;      
      [*] = ;      pGuards := ParserSelectByHandleByKey(pProto, 'Guards');
      [*] = ;      for k := ParserGetCountByHandle(pGuards)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pChild := ParserSelectByHandleByIndex(pGuards, k);
      [*] = ;         if (ParserGetIntValueByKeyByHandle(pChild, 'Guard') = id) and (ParserGetCountByHandle(pGuards) > 1) then // we don't want to delete all guards. Ensure at least one remains.
      [*] = ;         begin
      [*] = ;            ParserFreeByHandle(pChild);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;            continue(Main);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // delete banned guards from province type data
      [*] = ;   for [MAIN]j := 1 to gPrototypeData.provincetypes.number-1 do
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, j);
      [*] = ;      
      [*] = ;      pGuards := ParserSelectByHandleByKey(pProto, 'GuardTypes');
      [*] = ;      for k := ParserGetCountByHandle(pGuards)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pChild := ParserSelectByHandleByIndex(pGuards, k);
      [*] = ;         if (ParserGetIntValueByKeyByHandle(pChild, 'GuardType') = id) and (ParserGetCountByHandle(pGuards) > 1) then // we don't want to delete all guards. Ensure at least one remains.
      [*] = ;         begin
      [*] = ;            ParserFreeByHandle(pChild);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;            continue(Main);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure DeleteOrReplaceUnit(pParser, unitID : Integer);
      [*] = ;begin
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;   var replacementID : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'ReplacementID');
      [*] = ;            
      [*] = ;   if replacementID <> 0 then
      [*] = ;      ParserSetIntValueByKeyByHandle(pParser, 'UnitID', replacementID)
      [*] = ;   else
      [*] = ;      ParserFreeByHandle(pParser);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure CheckUnits(pParser, pCheck : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var pUnits : Integer = ParserSelectByHandleByKey(pParser, 'Units');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pUnits)-1 do
      [*] = ;   begin
      [*] = ;      pParser := ParserSelectByHandleByIndex(pUnits, i);
      [*] = ;      id := ParserGetIntValueByKeyByHandle(pParser, 'UnitID');
      [*] = ;      if _pars_ExistsByID(pCheck, id) then
      [*] = ;         DeleteOrReplaceUnit(pParser, id);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// delete or replace individual units in guards data
      [*] = ;for i := 0 to ParserGetCountByHandle(pBannedNeutralUnits)-1 do
      [*] = ;begin
      [*] = ;   pChild := ParserSelectByHandleByIndex(pBannedNeutralUnits, i);
      [*] = ;   id := ParserGetIntValueByKeyByHandle(pChild, 'ID'); 
      [*] = ;   
      [*] = ;   for j := 0 to gPrototypeData.guards.number-1 do
      [*] = ;   begin
      [*] = ;      pProto := ParserSelectByHandleByIndex(gPrototypeData.guards.handle, j);
      [*] = ;      pGuards := ParserSelectByHandleByKey(pGuards, 'Units');
      [*] = ;      
      [*] = ;      for k := 0 to ParserGetCountByHandle(pGuards)-1 do
      [*] = ;      begin
      [*] = ;         pChild := ParserSelectByHandleByIndex(pGuards, k);
      [*] = ;         
      [*] = ;         if ParserGetIntValueByKeyByHandle(pChild, 'UnitID') = id then
      [*] = ;         begin
      [*] = ;            DeleteOrReplaceUnit(pParser, id);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pProto, 'Customised', True);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// replace or delete unavailable units on a loaded shard.
      [*] = ;if bLoad then
      [*] = ;begin
      [*] = ;   var pProvince, pProvSites, pUnits, plHandle, heroHandle : Integer;
      [*] = ;   var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;            
      [*] = ;   for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;   begin
      [*] = ;      pProvince := ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;         
      [*] = ;      CheckUnits(ParserSelectByHandleByKey(pProvince, 'Garrison'), pBannedUnits);
      [*] = ;      CheckUnits(ParserSelectByHandleByKey(pProvince, 'Defender'), pBannedNeutralUnits);
      [*] = ;      CheckUnits(ParserSelectByHandleByKey(pProvince, 'Guard'), pBannedNeutralUnits);
      [*] = ;         
      [*] = ;      pProvSites := ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;      begin
      [*] = ;         CheckUnits(ParserSelectByHandleByKey(ParserSelectByHandleByIndex(pProvSites, j), 'Guard'), pBannedNeutralUnits);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;            
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      plHandle := GetPlayerHandleByIndex(i);
      [*] = ;            
      [*] = ;      for j := 0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;      begin
      [*] = ;         heroHandle := GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         CheckUnits(ParserSelectGameObject(heroHandle), pBannedUnits);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end
