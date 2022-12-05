section.begin
   Name = GetSiteTrophies
   Description : struct.begin
      [*] = ;IntRegister0 - site index
      [*] = ;IntRegister1- site level
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var siteIndex : Integer = IntRegister0;
      [*] = ;var siteLevel : Integer = IntRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\GETSITETROPHIES';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var heroClass : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;var myGOParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pSiteLootItems : Integer = ParserSelectByHandleByKey(myGOParser, 'SiteLootItems');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[HeroUID: '+IntToStr(GetGameObjectUniqueIdByHandle(myGOHandle))+']',_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(myPlHandle)].basediff;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pMyPlParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pMyPlayerStats : Integer = ParserSelectByHandleByKey(pMyPlParser, 'Stats');
      [*] = ;var pMyRareItems : Integer = ParserSelectByHandleByKey(pMyPlayerStats, 'RareItems');
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var pMyDefenders : Integer = ParserSelectByHandleByKey(pCastle, 'Defenders');
      [*] = ;var pMyAvOuterBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'AvOuterBuildings');
      [*] = ;var pMyRituals : Integer = ParserSelectByHandleByKey(pCastle, 'AvailableRituals');
      [*] = ;
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(myGOParser, 'Units');
      [*] = ;var pMyHero : Integer = ParserSelectByHandleByIndex(pMyUnits, 0);
      [*] = ;
      [*] = ;var curUID : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;IntRegister0 := curUID;
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;var pProvince : Integer = IntRegister1;
      [*] = ;var provIndex : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;
      [*] = ;var curShard : Integer = gCampaign.activeshard;
      [*] = ;
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteIndex);
      [*] = ;var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;
      [*] = ;var pSite : Integer = ParserSelectByHandleByIndex(gPrototypeData.sites.handle, siteID);
      [*] = ;var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;
      [*] = ;var dropped : Integer = 0;
      [*] = ;var dropLevel : Integer = 0;
      [*] = ;var siteGold : Integer = 0; //50 * siteLevel + Floor(RandomExt * (1 + 50 * siteLevel));
      [*] = ;var siteGem : Integer = 0; //5 * (siteLevel - 1) + Floor(RandomExt * (10 + siteLevel));
      [*] = ;var shop : Integer = 0;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;var pExtItems : Integer = gPrototypeData.extitems.handle;
      [*] = ;
      [*] = ;ExecuteState('ClearSiteLoot');
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;
      [*] = ;   case abilID of
      [*] = ;      13 : shop := 1;
      [*] = ;      22 : shop := 2;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gTutorial.Map and (gTutorial.Site >= 0) then
      [*] = ;begin
      [*] = ;   case gTutorial.site of
      [*] = ;      0 : begin
      [*] = ;         siteGold := 10 + _rand_Random(20);
      [*] = ;         siteGem := _rand_Random(10);
      [*] = ;      end;
      [*] = ;      1 : begin
      [*] = ;         siteGold := 20 + _rand_Random(20);
      [*] = ;         siteGem := 3 + _rand_Random(10);
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         siteGold := 50 + _rand_Random(50);
      [*] = ;         siteGem := 5 + _rand_Random(10);
      [*] = ;
      [*] = ;         dropped := 1;
      [*] = ;         var itemID : Integer = 0;
      [*] = ;         case heroClass of
      [*] = ;            1 : itemID := 168;
      [*] = ;            2 : itemID := 191;
      [*] = ;            3 : itemID := 146;
      [*] = ;            4 : itemID := 237;
      [*] = ;         end;
      [*] = ;         var pItem : Integer = ParserSelectByHandleByIndex(pItems, itemID);
      [*] = ;         var durability : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;         var itemDur : Integer = _rand_Random(1 + durability div 3) + 1;
      [*] = ;
      [*] = ;         var pNewLoot : Integer = ParserAddChildByIndex(pSiteLootItems, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewLoot, 'ItemID', itemID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewLoot, 'Durability', itemDur);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pNewLoot, 'Picked', false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if shop > 0 then
      [*] = ;   begin
      [*] = ;      var pSiteShop : Integer = 0;
      [*] = ;      if shop = 1 then
      [*] = ;         pSiteShop := ParserSelectByHandleByKey(pProvSite, 'Shop')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         pSiteShop := _misc_ParserGetOrCreateByKey('Shop',true);
      [*] = ;         var pShopItems : Integer = ParserAddChildByIndex(pSiteShop, 'Items');
      [*] = ;
      [*] = ;         var stuff : Integer = 8 + _rand_Random(5);
      [*] = ;         _rand_ClearRoll();
      [*] = ;         var count : Integer = 0;
      [*] = ;
      [*] = ;         for i := ParserGetCountByHandle(pItems)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pItem : Integer = ParserSelectByHandleByIndex(pItems, i);
      [*] = ;            var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;            var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;
      [*] = ;            if (rarity > 1) and (shopLevel < 5) then
      [*] = ;            begin
      [*] = ;               gArrRollerN[count] := i;
      [*] = ;               gArrRollerP[count] := 8 - rarity;
      [*] = ;               count := count + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i := 0 to stuff-1 do
      [*] = ;         begin
      [*] = ;            var pSiteShopItem : Integer = ParserAddChildByIndex(pShopItems, '*');
      [*] = ;            var itemID : Integer = _rand_Roll(true);
      [*] = ;            var itemCount : Integer = 1 + _rand_Random(3);
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pSiteShopItem, 'ItemID', itemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pSiteShopItem, 'Count', itemCount);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gc_StaticLoot then
      [*] = ;      begin
      [*] = ;         siteGold := 400 + _rand_RandomSeed2(400, siteIndex, provIndex);
      [*] = ;         siteGem := 80 + _rand_RandomSeed2(80, provIndex, siteIndex);
      [*] = ;         dropped := 3 + _rand_RandomSeed2(3, siteIndex, provIndex)
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         siteGold := 400 + _rand_Random(400);
      [*] = ;         siteGem := 80 + _rand_Random(80);
      [*] = ;         dropped := 3 + _rand_Random(3);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pShopItems : Integer = ParserAddChildByIndex(pSiteShop, 'Items');
      [*] = ;      var count : Integer = 0;
      [*] = ;      _rand_ClearRoll();
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pShopItems)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pShopItem : Integer = ParserSelectByHandleByIndex(pShopItems, i);
      [*] = ;
      [*] = ;         gArrRollerN[count] := ParserGetIntValueByKeyByHandle(pShopItem, 'ItemID');
      [*] = ;         gArrRollerP[count] := 10;
      [*] = ;         count := count + 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if dropped > count then
      [*] = ;         dropped := count;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gc_StaticLoot then
      [*] = ;      begin
      [*] = ;         siteGold := 50 * siteLevel + _rand_RandomSeed2(1 + 50 * siteLevel, provIndex, siteIndex);
      [*] = ;         siteGem := 5 * (siteLevel - 1) + _rand_RandomSeed3(10 + siteLevel, gGame.seed, provIndex, siteIndex);
      [*] = ;
      [*] = ;         case siteLevel of
      [*] = ;            1 :
      [*] = ;            begin
      [*] = ;               dropped := _rand_RandomSeed2(2, siteIndex, provIndex);
      [*] = ;               dropLevel := 1;
      [*] = ;            end;
      [*] = ;            2 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 4 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            3 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            4 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            5 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            6 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            7 :
      [*] = ;            begin
      [*] = ;               dropped := 1;
      [*] = ;               dropLevel := 4;
      [*] = ;            end;
      [*] = ;            8 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            9 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 4 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            10 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 4;
      [*] = ;                  siteGold := siteGold + 200;
      [*] = ;                  siteGem := siteGem + 25;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            11 :
      [*] = ;            begin
      [*] = ;               dropped := 1;
      [*] = ;               dropLevel := 5;
      [*] = ;            end;
      [*] = ;            12 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;                  siteGold := siteGold + 400;
      [*] = ;                  siteGem := siteGem + 50;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 6;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            13 :
      [*] = ;            begin
      [*] = ;               if _rand_RandomSeed2(10, siteIndex, provIndex) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 6;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               dropped := dropped + 1 + (siteLevel - 13) div 2 + _rand_RandomSeed2((siteLevel - 12) div 2, siteIndex, provIndex);
      [*] = ;               dropLevel := 6;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         siteGold := 50 * siteLevel + _rand_Random(1 + 50 * siteLevel);
      [*] = ;         siteGem := 5 * (siteLevel - 1) + _rand_Random(10 + siteLevel);
      [*] = ;
      [*] = ;         case siteLevel of
      [*] = ;            1 :
      [*] = ;            begin
      [*] = ;               dropped := _rand_Random(2);
      [*] = ;               dropLevel := 1;
      [*] = ;            end;
      [*] = ;            2 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 4 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 2;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            3 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            4 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            5 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            6 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 3;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            7 :
      [*] = ;            begin
      [*] = ;               dropped := 1;
      [*] = ;               dropLevel := 4;
      [*] = ;            end;
      [*] = ;            8 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            9 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 4 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 4;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            10 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 4;
      [*] = ;                  siteGold := siteGold + 200;
      [*] = ;                  siteGem := siteGem + 25;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            11 :
      [*] = ;            begin
      [*] = ;               dropped := 1;
      [*] = ;               dropLevel := 5;
      [*] = ;            end;
      [*] = ;            12 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 2 then
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 5;
      [*] = ;                  siteGold := siteGold + 400;
      [*] = ;                  siteGem := siteGem + 50;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 6;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            13 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(10) > 6 then
      [*] = ;               begin
      [*] = ;                  dropped := 2;
      [*] = ;                  dropLevel := 5;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  dropped := 1;
      [*] = ;                  dropLevel := 6;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               dropped := dropped + 1 + (siteLevel - 13) div 2 + _rand_Random((siteLevel - 12) div 2);
      [*] = ;               dropLevel := 6;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if dropped > gc_MaxLootCount then
      [*] = ;         dropped := gc_MaxLootCount;
      [*] = ;
      [*] = ;      _rand_ClearRoll();
      [*] = ;      var count : Integer = 0;
      [*] = ;
      [*] = ;      if ParserGetIntValueByKeyByHandle(pMyHero, 'CurLife') > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 987;
      [*] = ;         GameObjectExecuteStateByHandle(myGOHandle, 'CheckAbility');
      [*] = ;         var robSites : Integer = IntRegister1;
      [*] = ;
      [*] = ;         siteGold := siteGold + Floor(siteGold * robSites / 100);
      [*] = ;         siteGem := siteGem + Floor(siteGem * robSites / 100);
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pExtItems)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pItem : Integer = ParserSelectByHandleByIndex(pExtItems, i);
      [*] = ;         var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;
      [*] = ;         if (shopLevel = dropLevel) and _map_IsItemEnabled(i) then
      [*] = ;         begin
      [*] = ;            var pItemAbilities : Integer = ParserSelectByHandleByKey(pItem, 'Abilities');
      [*] = ;            var pItemAbility0 : Integer = ParserSelectByHandleByIndex(pItemAbilities, 0);
      [*] = ;            var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;            var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;
      [*] = ;            var bAdd : Boolean = true;
      [*] = ;
      [*] = ;            case itemType of
      [*] = ;               10 : begin // spell scroll
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pItem, 'ItemID') <= 0 then
      [*] = ;                     bAdd := false;
      [*] = ;               end;
      [*] = ;               11 : begin // defender agreement
      [*] = ;                  var defID : Integer = ParserGetIntValueByKeyByHandle(pItemAbility0, 'Power');
      [*] = ;                  var pMyDefender : Integer = ParserSelectByHandleByIndex(pMyDefenders, defID);
      [*] = ;
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pMyDefender, 'Count') < 0 then
      [*] = ;                     bAdd := false
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;                     begin
      [*] = ;                        var worldSize : Integer = _camp_player_GetWorldSize(gCampaign.arrCampPlayers[0]);
      [*] = ;                        var pDefender : Integer = ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, defID);
      [*] = ;                        var defPower : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Power');
      [*] = ;
      [*] = ;                        if ((worldSize < 12) and (defPower >= 4)) or ((worldSize < 16) and (defPower >= 5)) or
      [*] = ;                        ((worldSize < 20) and (defPower >= 6)) then
      [*] = ;                           bAdd := false;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               12 :
      [*] = ;               // building plan
      [*] = ;               begin
      [*] = ;                  var buildID : Integer = ParserGetIntValueByKeyByHandle(pItemAbility0, 'Power');
      [*] = ;                  var pMyAvOuterBuilding : Integer = ParserSelectByHandleByIndex(pMyAvOuterBuildings, buildID);
      [*] = ;
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pMyAvOuterBuilding, 'Count') < 0 then
      [*] = ;                     bAdd := false;
      [*] = ;               end;
      [*] = ;               13 :
      [*] = ;               // ritual scroll
      [*] = ;               begin
      [*] = ;                  var ritualID : Integer = ParserGetIntValueByKeyByHandle(pItemAbility0, 'Power');
      [*] = ;                  var pMyRitual : Integer = ParserSelectByHandleByIndex(pMyRituals, ritualID);
      [*] = ;
      [*] = ;                  if ParserGetIntValueByKeyByHandle(pMyRitual, 'Count') < 0 then
      [*] = ;                     bAdd := false;
      [*] = ;               end;
      [*] = ;               14 :
      [*] = ;               // inner building
      [*] = ;               begin
      [*] = ;                  bAdd := false;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if bAdd then
      [*] = ;            begin
      [*] = ;               gArrRollerN[count] := i;
      [*] = ;               gArrRollerP[count] := (7 - rarity);
      [*] = ;               count := count + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to dropped-1 do
      [*] = ;   begin
      [*] = ;      var itemID : Integer;
      [*] = ;      if gc_StaticLoot then
      [*] = ;         itemID := _rand_RollSeed3(true, i, siteIndex * 5, provIndex)
      [*] = ;      else
      [*] = ;         itemID := _rand_Roll(true);
      [*] = ;
      [*] = ;      var pItem : Integer = ParserSelectByHandleByIndex(pExtItems, itemID);
      [*] = ;      var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;      var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;      var breakable : Boolean = ParserGetBoolValueByKeyByHandle(pItem, 'Breakable');
      [*] = ;      var lootItemDur : Integer;
      [*] = ;
      [*] = ;      if breakable and (_rand_Random(30) > 10) then
      [*] = ;         lootItemDur := itemDur div 2 + _rand_Random(1 + itemDur div 2)
      [*] = ;      else
      [*] = ;         lootItemDur := itemDur;
      [*] = ;
      [*] = ;      var pNewLoot : Integer = ParserAddChildByIndex(pSiteLootItems, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewLoot, 'ItemID', itemID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewLoot, 'Durability', lootItemDur);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pNewLoot, 'Picked', false);
      [*] = ;
      [*] = ;      case rarity of
      [*] = ;         4, 5, 6 :
      [*] = ;         begin
      [*] = ;            var pMyRareItem : Integer = ParserSelectByHandleByIndex(pMyRareItems, rarity - 4);
      [*] = ;            var rareCount : Integer = ParserGetIntValueByKeyByHandle(pMyRareItem, 'Count');
      [*] = ;            ParserSetIntValueByKeyByHandle(pMyRareItem, 'Count', rareCount + 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (cMode = 'cmPlayer') and (dropped < gc_MaxLootCount) and (gGame.gameType = gc_GameTypeCampaign) and (curShard >= 0) and (shop = 0) and (siteLevel > 1) and
      [*] = ;   ((siteLevel > 14) or (_rand_Random(30 - siteLevel * 2) = 0)) then
      [*] = ;   begin
      [*] = ;      _rand_ClearRoll();
      [*] = ;      var count : Integer = 0;
      [*] = ;      var activePlayer : Integer = gCampaign.activePlayer;
      [*] = ;
      [*] = ;      for i := 0 to gc_MaxShardBuild-1 do
      [*] = ;      begin
      [*] = ;         var buildID : Integer = gShards[gCampaign.activeshard].arBuilding[i];
      [*] = ;         if (buildID > 0) and (gCampaign.arrCampPlayers[activePlayer].arrBuilds[buildID] = 0) then
      [*] = ;         begin
      [*] = ;            gArrRollerN[count] := buildID;
      [*] = ;            gArrRollerP[count] := 10;
      [*] = ;            count := count + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if count > 0 then
      [*] = ;      begin
      [*] = ;         var buildID : Integer = _rand_Roll(false);
      [*] = ;         gCampaign.arrCampPlayers[activePlayer].arrBuilds[buildID] := 1;
      [*] = ;
      [*] = ;         //var itemID : Integer = gPrototypeData.items.number + gPrototypeData.spells.number + gPrototypeData.defenders.number +
      [*] = ;         //gPrototypeData.outerBuildings.number + gPrototypeData.rituals.number + buildID;
      [*] = ;         IntRegister0 := buildID;
      [*] = ;         IntRegister1 := 14;
      [*] = ;         MapExecuteState('GetExtItemIDByType');
      [*] = ;         var itemID : Integer = IntRegister2;
      [*] = ;
      [*] = ;         var pNewLoot : Integer = ParserAddChildByIndex(pSiteLootItems, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewLoot, 'ItemID', itemID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewLoot, 'Durability', 0);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pNewLoot, 'Picked', true);
      [*] = ;
      [*] = ;         dropped := dropped + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if cMode = 'cmPlayer' then
      [*] = ;begin
      [*] = ;   var pDifficulty : Integer = ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, plDiff);
      [*] = ;   var lootMod : Integer = ParserGetIntValueByKeyByHandle(pDifficulty, 'LootMod');
      [*] = ;
      [*] = ;   siteGold := (siteGold * lootMod) div 100;
      [*] = ;   siteGem := (siteGem * lootMod) div 100;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;
      [*] = ;   if (abilID = 3) and (param1 = 2) then
      [*] = ;   begin
      [*] = ;      siteGem := siteGem + (siteGold * 2) div 5;
      [*] = ;      siteGold := 0;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(myGOParser, 'SiteGold', siteGold);
      [*] = ;ParserSetIntValueByKeyByHandle(myGOParser, 'SiteGem', siteGem);
      [*] = ;
      [*] = ;var p : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;if p <> 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_province_uf_sites_updated;
      [*] = ;   StringRegister0 := _log_name;
      [*] = ;   GameObjectExecuteStateByHandle(p, 'MergeUpdateFlags');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[SiteGold: '+IntToStr(siteGold)+', SiteGem: '+IntToStr(SiteGem)+']',$1000000 or _log_trace);
   struct.end
section.end

