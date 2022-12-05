section.begin
   Name = AddSite
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
      [*] = ;IntRegister1 - site ID
      [*] = ;IntRegister2 - site level
      [*] = ;IntRegister3 - quest
      [*] = ;IntRegister4 - hidden
      [*] = ;IntRegister5 - guard
      [*] = ;OUT: IntRegister6 - site parser
   struct.end
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var siteID : Integer = IntRegister1;
      [*] = ;var siteLevel : Integer = IntRegister2;
      [*] = ;var quest : Integer = IntRegister3;
      [*] = ;var hidden : Integer = IntRegister4;
      [*] = ;var guard : Integer = IntRegister5;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\ADDSITE';
      [*] = ;var _log_trace : Integer = $20000;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(siteID)+']',_log_trace);
      [*] = ;
      [*] = ;if siteLevel < 0 then
      [*] = ;   siteLevel := 0;
      [*] = ;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;if (dummyHandle <> 0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_province_uf_sites_updated;
      [*] = ;   StringRegister0 := _log_name;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'MergeUpdateFlags');
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := siteID;
      [*] = ;ExecuteState('GetSiteParserByID');
      [*] = ;var pSite : Integer = IntRegister1;
      [*] = ;var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;
      [*] = ;var pGuardTypes : Integer = gPrototypeData.guardTypes.handle;
      [*] = ;var pGuards : Integer = gPrototypeData.guards.handle;
      [*] = ;
      [*] = ;function GetGuardLevelByGuardPower(siteGuardType, guardPower : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var pGuardIDs : Integer = ParserSelectByHandleByKey(siteGuardType, 'GuardID');
      [*] = ;   var curPower : Integer = 1000;
      [*] = ;
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pGuardIDs)-1 do
      [*] = ;   begin
      [*] = ;      var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, i);
      [*] = ;      var guardID : Integer = ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;
      [*] = ;      var pGuard : Integer = ParserSelectByHandleByIndex(pGuards, guardID);
      [*] = ;      var aGuardPower : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;      if Abs(aGuardPower - guardPower) < Abs(curPower - guardPower) then
      [*] = ;      begin
      [*] = ;         curPower := aGuardPower;
      [*] = ;         Result := i;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;var guarded : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Guarded');
      [*] = ;var siteName : String = ParserGetValueByKeyByHandle(pSite, 'Name');
      [*] = ;var siteTreasure : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Treasure');
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;var pProvSite : Integer = 0;
      [*] = ;
      [*] = ;if ParserGetCountByHandle(pProvSites) < gc_MaxProvinceSite then
      [*] = ;begin
      [*] = ;   if hidden = 0 then
      [*] = ;      hidden := ParserGetIntValueByKeyByHandle(pSite, 'Place') - 1;
      [*] = ;
      [*] = ;   IntRegister0 := hidden;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetNewSiteExplore');
      [*] = ;   var explore : Integer = IntRegister1;
      [*] = ;   //var explore : Integer = GetSiteExplore(pProvince, hidden);
      [*] = ;
      [*] = ;   if explore > 0 then
      [*] = ;   begin
      [*] = ;      pProvSite := ParserAddChildByIndex(pProvSites, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvSite, 'Explore', explore);
      [*] = ;      ParserSetValueByKeyByHandle(pProvSite, 'Name', siteName);
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvSite, 'SiteID', siteID);
      [*] = ;
      [*] = ;      var level : Integer = siteLevel * 2 + Floor(2 * RandomExt);
      [*] = ;      if explore > 60 + RandomExt * 40 then
      [*] = ;         level := level + Floor(RandomExt * ((explore - 60) div 11));
      [*] = ;
      [*] = ;      level := level + siteTreasure;
      [*] = ;      if level > 10 then
      [*] = ;         level := 10;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvSite, 'Level', level);
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvSite, 'Quest', quest);
      [*] = ;
      [*] = ;      // add and setup guard
      [*] = ;      if ((guard > 0) and (guarded > 0)) or ((RandomExt * 100 < guarded) and (guard >= 0)) then
      [*] = ;      begin
      [*] = ;         var pSiteGuards : Integer = ParserSelectByHandleByKey(pSite, 'Guards');
      [*] = ;         var sum : Integer = 0;
      [*] = ;
      [*] = ;         for i := ParserGetCountByHandle(pSiteGuards)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSiteGuard : Integer = ParserSelectByHandleByIndex(pSiteGuards, i);
      [*] = ;            var poss : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'Possibility');
      [*] = ;            // world rule
      [*] = ;            if (_worldrule_GetWorldRuleAbilityExistByID(14)) then
      [*] = ;            begin
      [*] = ;               var pWorldRule : Integer = _worldrule_GetWorldRuleParser();
      [*] = ;               var pWorldRuleAbilities : Integer = ParserSelectByHandleByKey(pWorldRule, 'Abilities');
      [*] = ;               var j : Integer;
      [*] = ;               for j:=0 to ParserGetCountByHandle(pWorldRuleAbilities)-1 do
      [*] = ;               begin
      [*] = ;                  var pWorldRuleAbility : Integer = ParserSelectByHandleByIndex(pWorldRuleAbilities, j);
      [*] = ;                  var abilityID : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'AbilityID');
      [*] = ;                  if (abilityID=14) then
      [*] = ;                  begin
      [*] = ;                     var param1 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param1');
      [*] = ;                     var param2 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param2');
      [*] = ;
      [*] = ;                     var guardID : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'Guard');
      [*] = ;                     if (param1=guardID) then
      [*] = ;                        poss := (poss*param2) div 100;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            sum := sum + poss;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var randSum : Float = RandomExt() * sum;
      [*] = ;         var siteGuardType : Integer = -1;
      [*] = ;
      [*] = ;         for i := ParserGetCountByHandle(pSiteGuards)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSiteGuard : Integer = ParserSelectByHandleByIndex(pSiteGuards, i);
      [*] = ;            var poss : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'Possibility');
      [*] = ;            // world rule
      [*] = ;            if (_worldrule_GetWorldRuleAbilityExistByID(14)) then
      [*] = ;            begin
      [*] = ;               var pWorldRule : Integer = _worldrule_GetWorldRuleParser();
      [*] = ;               var pWorldRuleAbilities : Integer = ParserSelectByHandleByKey(pWorldRule, 'Abilities');
      [*] = ;               var j : Integer;
      [*] = ;               for j:=0 to ParserGetCountByHandle(pWorldRuleAbilities)-1 do
      [*] = ;               begin
      [*] = ;                  var pWorldRuleAbility : Integer = ParserSelectByHandleByIndex(pWorldRuleAbilities, j);
      [*] = ;                  var abilityID : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'AbilityID');
      [*] = ;                  if (abilityID=14) then
      [*] = ;                  begin
      [*] = ;                     var param1 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param1');
      [*] = ;                     var param2 : Integer = ParserGetIntValueByKeyByHandle(pWorldRuleAbility, 'Param2');
      [*] = ;
      [*] = ;                     var guardID : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'Guard');
      [*] = ;                     if (param1=guardID) then
      [*] = ;                        poss := (poss*param2) div 100;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            randSum := randSum - poss;
      [*] = ;
      [*] = ;            if randSum <= 0 then
      [*] = ;            begin
      [*] = ;               siteGuardType := ParserGetIntValueByKeyByHandle(pSiteGuard, 'Guard');
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pSiteGuardType : Integer = ParserSelectByHandleByIndex(pGuardTypes, siteGuardType);
      [*] = ;         var guardKarma : Integer = ParserGetIntValueByKeyByHandle(pSiteGuardType, 'Karma');
      [*] = ;
      [*] = ;         var guardLevel : Integer = -1;
      [*] = ;
      [*] = ;         for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;            var ability : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;            if ability = 8 then
      [*] = ;            begin
      [*] = ;               guardLevel := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var guardPower : Integer;
      [*] = ;
      [*] = ;         if guardLevel = -1 then
      [*] = ;         begin
      [*] = ;            guardPower := 1 + siteLevel * 3 + Floor(RandomExt * (siteLevel + 1)) - Floor(RandomExt * (siteLevel + 1));
      [*] = ;            if explore > 60 + RandomExt * 30 then
      [*] = ;               guardPower := Floor(guardPower + RandomExt * (siteLevel + 4));
      [*] = ;
      [*] = ;            if guardPower > gGame.map.neutrals then
      [*] = ;               guardPower := gGame.map.neutrals;
      [*] = ;
      [*] = ;            guardLevel := GetGuardLevelByGuardPower(pSiteGuardType, guardPower);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if guardLevel > 3 then
      [*] = ;            guardLevel := 3;
      [*] = ;
      [*] = ;         var pGuardIDs : Integer = ParserSelectByHandleByKey(pSiteGuardType, 'GuardID');
      [*] = ;         var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, guardLevel);
      [*] = ;         var guardID : Integer = ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;
      [*] = ;         IntRegister0 := guardID;
      [*] = ;         ExecuteState('GetGuardParserByID');
      [*] = ;         var pGuard : Integer = IntRegister1;
      [*] = ;         guardPower := ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;
      [*] = ;         var treasure : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Treasure');
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvSite, 'Level', guardPower + treasure);
      [*] = ;
      [*] = ;         IntRegister0 := pProvSite;
      [*] = ;         IntRegister1 := siteGuardType;
      [*] = ;         IntRegister2 := guardID;
      [*] = ;         IntRegister3 := guardKarma;
      [*] = ;         ExecuteState('map.AddGuard');
      [*] = ;         ParserSetBoolValueByKeyByHandle( IntRegister4, 'NeedRestore', false);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // setup random quest
      [*] = ;      if quest = 0 then
      [*] = ;      begin
      [*] = ;         var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;
      [*] = ;         for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;            var ability : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;            if (ability = 15) and (_rand_Random(100) < ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param2')) then
      [*] = ;            begin
      [*] = ;               quest := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if quest > 0 then
      [*] = ;         begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvSite, 'Quest', quest);
      [*] = ;            var quests : Integer = gPrototypeData.quests.handle;
      [*] = ;            var questHnd : Integer = ParserSelectByHandleByIndex(quests, quest);
      [*] = ;            var questType : Integer = ParserGetIntValueByKeyByHandle(questHnd, 'Type');
      [*] = ;            if questType = 7 then
      [*] = ;            begin
      [*] = ;               var pQuestObjectives : Integer = ParserSelectByHandleByKey(questHnd, 'Objectives');
      [*] = ;               var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;               var questIndex : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Index');
      [*] = ;               if questIndex = 1 then
      [*] = ;               begin
      [*] = ;                  var ps : array [0..gc_max_spells] of Integer;
      [*] = ;                  var ps_no,p,i,id : Integer;
      [*] = ;
      [*] = ;                  ps_no := 0;
      [*] = ;                  for i := 3 to (gPrototypeData.spells.number)-1 do
      [*] = ;                  begin
      [*] = ;                     p := ParserSelectByHandleByIndex(gPrototypeData.extItems.handle, gPrototypeData.items.number+i);
      [*] = ;                     id := ParserGetIntValueByKeyByHandle(p,'ItemID');
      [*] = ;                     if (id > 0) and (ParserGetIntValueByKeyByHandle(p, 'ShopLevel') > 0) then
      [*] = ;                     begin
      [*] = ;                        ps[ps_no] := id;
      [*] = ;                        ps_no := ps_no + 1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  id := ps[_rand_Random(ps_no)];
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvSite, 'QuestData', id);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var quests : Integer = gPrototypeData.quests.handle;
      [*] = ;            var questsCount : Integer = ParserGetCountByHandle(quests);
      [*] = ;            for i := questsCount downto 1 do
      [*] = ;            begin
      [*] = ;               var questHnd : Integer = ParserSelectByHandleByIndex(quests, i);
      [*] = ;               var questType : Integer = ParserGetIntValueByKeyByHandle(questHnd, 'Type');
      [*] = ;               var questGiver : Integer = ParserGetIntValueByKeyByHandle(questHnd, 'Giver');
      [*] = ;               if (questGiver = siteID) and (questType = 8) then
      [*] = ;               begin
      [*] = ;                  //ParserSetIntValueByKeyByHandle(pProvSite, 'Quest', 9999);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pProvSite, 'RandomQuest', true);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // setup shop
      [*] = ;      var isShop : Boolean = false;
      [*] = ;      var itemType : Integer = 0;
      [*] = ;      var shopLevel : Integer = 0;
      [*] = ;      var itemCount : Integer = 8;
      [*] = ;      var priceMod : Integer = 300;
      [*] = ;
      [*] = ;      for i := 0 to ParserGetCountByHandle(pSiteAbilities)-1 do
      [*] = ;      begin
      [*] = ;         var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;         var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;
      [*] = ;         case abilID of
      [*] = ;            13 :
      [*] = ;            begin
      [*] = ;               isShop := true;
      [*] = ;               itemType := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;               shopLevel := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param2');
      [*] = ;
      [*] = ;               if Floor(randomExt * 10) = 0 then
      [*] = ;               begin
      [*] = ;                  shopLevel := shopLevel + 1;
      [*] = ;
      [*] = ;                  if Floor(randomExt * 10) = 0 then
      [*] = ;                  shopLevel := shopLevel + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            14 :
      [*] = ;            begin
      [*] = ;               itemCount := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;               priceMod := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param2');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if isShop then
      [*] = ;      begin
      [*] = ;         //Log('Shop in province ' + IntToStr(dummyUID));
      [*] = ;         var pSiteShop : Integer = ParserAddChildByIndex(pProvSite, 'Shop');
      [*] = ;         var pShopItems : Integer = ParserAddChildByIndex(pSiteShop, 'Items');
      [*] = ;         ParserSetIntValueByKeyByHandle(pSiteShop, 'ItemType', itemType);
      [*] = ;
      [*] = ;         IntRegister0 := itemType;
      [*] = ;         IntRegister1 := shopLevel;
      [*] = ;         IntRegister2 := 0;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         ExecuteState('map.ShopRoller');
      [*] = ;         var randCount : Integer = IntRegister3;
      [*] = ;
      [*] = ;         // fill shop items
      [*] = ;         if randCount > 0 then
      [*] = ;         begin
      [*] = ;            if itemCount > randCount then
      [*] = ;            itemCount := randCount;
      [*] = ;
      [*] = ;            for i := 0 to itemCount-1 do
      [*] = ;            begin
      [*] = ;               var pShopItem : Integer = ParserAddChildByIndex(pShopItems, '*');
      [*] = ;               var itemID : Integer = _rand_Roll(true);
      [*] = ;               var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extItems.handle, itemID);
      [*] = ;               var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;
      [*] = ;               var count : Integer = 0;
      [*] = ;               if rarity = 1 then
      [*] = ;               count := 0
      [*] = ;               else
      [*] = ;               count := 1 + Floor(randomExt * (6 - rarity));
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pShopItem, 'ItemID', itemID);
      [*] = ;               ParserSetIntValueByKeyByHandle(pShopItem, 'Count', count);
      [*] = ;            end;
      [*] = ;
      [*] = ;            // setup price modifiers
      [*] = ;            var pPriceModifiers : Integer = ParserAddChildByIndex(pSiteShop, 'PriceModifiers');
      [*] = ;            for i := 0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               var pPriceModifier : Integer = ParserAddChildByIndex(pPriceModifiers, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pPriceModifier, 'PlayerIndex', i);
      [*] = ;               ParserSetIntValueByKeyByHandle(pPriceModifier, 'PriceModifier', priceMod);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister6 := pProvSite;
   struct.end
section.end

