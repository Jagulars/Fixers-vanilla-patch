section.begin
   Name = Event.ApplyEffects
   Code : struct.begin
      [*] = ;var _log_name : String = 'EVENT\EVENT.APPLYEFFECTS';
      [*] = ;var _log_trace : Integer = $80001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;if _log then _Log_map('Event.ApplyEffects execute');
      [*] = ;
      [*] = ;var pProvinceLevels : Integer = gPrototypeData.provinceLevels.handle;
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;
      [*] = ;// get parser event handle
      [*] = ;var queryHandle : Integer = _query_GetExecutedHandle();
      [*] = ;var queryID : String = QueryMachineQueryGetID(queryHandle);
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;var pInitParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle());
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;IntRegister0 := StrToInt(queryID);
      [*] = ;MapExecuteState('GetEventParserByID');
      [*] = ;var pEvent : Integer = IntRegister1;
      [*] = ;
      [*] = ;if pEvent = 0 then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name+'[Event=NULL]',$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;// get province parser handle
      [*] = ;var dummyHandle : Integer = _map_GetCurrentProvinceHandle();
      [*] = ;var dummyUID : Integer = GetGameObjectUniqueIdByHandle(dummyHandle);
      [*] = ;var pProvince : Integer = GetGameObjectIntValueIndByHandle(dummyHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;if pProvince = 0 then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name+'[Province=NULL]',$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var provUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;var bInterfacePlayer : Boolean = (GetPlayerHandleInterfaceIO = plHandle);
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;var pTreasurySlots : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;
      [*] = ;var provLevel : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;var plKarma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;
      [*] = ;var eventKarma : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Karma');
      [*] = ;plKarma := plKarma + eventKarma;
      [*] = ;SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, plKarma);
      [*] = ;
      [*] = ;var gIntRegister_EventAttackerLevel : Integer = -1;
      [*] = ;var bGuardGold : Boolean = false;
      [*] = ;
      [*] = ;var pEffects : Integer = ParserSelectByHandleByKey(pEvent, 'EffectList');
      [*] = ;
      [*] = ;gIntRegister_TreasureGoldReward := 0;
      [*] = ;gIntRegister_TreasureGemReward := 0;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pEffects)-1 do
      [*] = ;begin
      [*] = ;   var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, i);
      [*] = ;   var index : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;   var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;   var value : Integer = 0;
      [*] = ;
      [*] = ;   case index of
      [*] = ;      // 2 Изменение отношения на Power
      [*] = ;      2 :
      [*] = ;      begin
      [*] = ;         value := power;
      [*] = ;         IntRegister0 := plHandle;
      [*] = ;         IntRegister1 := value;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'ChangeAttitude');
      [*] = ;      end;
      [*] = ;      // 3 Изменение количества населения на Power+Random(Param1)%
      [*] = ;      3 :
      [*] = ;      begin
      [*] = ;         var Population : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Population');
      [*] = ;         value := Power + _rand_Random(param1);
      [*] = ;
      [*] = ;         Population := Floor(Population * (1 + value / 100));
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pProvinceLevels)-1 do
      [*] = ;         begin
      [*] = ;            var pLevel : Integer = ParserSelectByHandleByIndex(pProvinceLevels, j);
      [*] = ;            var lPopulation : Integer = ParserGetIntValueByKeyByHandle(pLevel, 'MaxPopulation');
      [*] = ;
      [*] = ;            if lPopulation > population then
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'Population', Population);
      [*] = ;         //ParserSetIntValueByKeyByHandle(pProvince, 'ProvinceLevel', j);
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CalcLevel');
      [*] = ;
      [*] = ;         if _log then _log_map('Effect: 3 Изменение количества населения на ' + IntToStr(power) + ' + Random(' + IntToStr(Param1) + ') %');
      [*] = ;         if _log then _log_map('Population = ' + IntToStr(Population));
      [*] = ;         if _log then _log_map('ProvinceLevel = ' + IntToStr(j));
      [*] = ;      end;
      [*] = ;      // 5 Доход с провинции + Power+Random(Param1)
      [*] = ;      5 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;         var oldGoldInc : Integer = IntRegister0;
      [*] = ;
      [*] = ;         var GoldInc : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'GoldInc');
      [*] = ;         value := power + _rand_Random(param1);
      [*] = ;
      [*] = ;         GoldInc := GoldInc + value;
      [*] = ;         if GoldInc < 0 then
      [*] = ;            GoldInc := 0;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'GoldInc', GoldInc);
      [*] = ;
      [*] = ;         IntRegister0 := 1;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;         var newGoldInc : Integer = IntRegister0;
      [*] = ;
      [*] = ;         value := newGoldInc - oldGoldInc;
      [*] = ;         if _log then _log_map('Effect: 5 Доход с провинции + ' + IntToStr(power) + ' + Random(' + IntToStr(Param1) + ')');
      [*] = ;         if _log then _log_map('GoldInc = ' + IntToStr(GoldInc));
      [*] = ;      end;
      [*] = ;      // 6 Получить Power+Random(Param1) кристаллов.
      [*] = ;      //
      [*] = ;      //      Если Param2=
      [*] = ;      //      1, величина умножается на уровень провинции
      [*] = ;      //      2 - изменяет количество имеющихся кристаллов на Power+Random(Param1)%
      [*] = ;      //
      [*] = ;      6 :
      [*] = ;      begin
      [*] = ;         value := power + _rand_Random(param1);
      [*] = ;         var provLevel : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;
      [*] = ;         case param2 of
      [*] = ;            1 : value := value * provLevel;
      [*] = ;            2 : value := Floor(value * plGem / 100);
      [*] = ;         end;
      [*] = ;
      [*] = ;         gIntRegister_TreasureGemReward := value;
      [*] = ;         plGem := plGem + value;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;         if _log then _log_map('Effect: 6 Получить ' + IntToStr(power) + ' + Random(' + IntToStr(Param1) + ') кристаллов');
      [*] = ;         if _log then _log_map('Player gem = ' + IntToStr(plGem));
      [*] = ;
      [*] = ;         plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + value);
      [*] = ;
      [*] = ;         gIntRegister_GemReward := value;
      [*] = ;      end;
      [*] = ;      // 7 Карма + Power+Random(Param1)
      [*] = ;      7 :
      [*] = ;      begin
      [*] = ;         value := power + _rand_Random(param1);
      [*] = ;         plKarma := plKarma + value;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, plKarma);
      [*] = ;
      [*] = ;         if _log then _log_map('Effect: 7 Карма + ' + IntToStr(power) + ' + Random(' + IntToStr(Param1) + ')');
      [*] = ;         if _log then _log_map('Player karma = ' + IntToStr(plKarma));
      [*] = ;      end;
      [*] = ;      //9 В провинции появляется новый сайт Power. Если Param1>0 - сайт скрытый, если Param1<0 - открытый. Если Param2=-1 не ставить стражу, 0-по умолчанию, 1-ставить.
      [*] = ;      9 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := power;
      [*] = ;         IntRegister2 := gGame.currentTurn div 20;
      [*] = ;         IntRegister3 := 0;
      [*] = ;         IntRegister4 := param1;
      [*] = ;         IntRegister5 := param2;
      [*] = ;         MapExecuteState('AddSite');
      [*] = ;         var pProvSite : Integer = IntRegister6;
      [*] = ;
      [*] = ;         var pSite : Integer = ParserSelectByHandleByIndex(gPrototypeData.sites.handle, power);
      [*] = ;         var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;         var res : Integer = 0;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, j);
      [*] = ;            var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;            if abilID = 1 then
      [*] = ;            begin
      [*] = ;               res := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if res > 0 then
      [*] = ;         begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvSite, 'Resource', res);
      [*] = ;
      [*] = ;            var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;            var pGuardUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;            var guarded : Boolean = (ParserGetCountByHandle(pGuardUnits) > 0);
      [*] = ;            var explore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'Resource', res);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pProvince, 'ResourceGuarded', guarded);
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'ResourceExplore', explore);
      [*] = ;
      [*] = ;            _map_RefreshProvinceHUD(dummyUID);
      [*] = ;         end;
      [*] = ;         if dummyHandle <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_province_uf_sites_updated;
      [*] = ;            StringRegister0 := _log_name;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'MergeUpdateFlags');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //10 Изменяет накопленное недовольство на Power+Random(Param1)
      [*] = ;      10 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerUnrest');
      [*] = ;         var unrest : Integer = IntRegister0;
      [*] = ;
      [*] = ;         value := _misc_CalcEffect(pEffect, provLevel, unrest);
      [*] = ;         IntRegister0 := unrest + value;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'SetOwnerUnrest');
      [*] = ;      end;
      [*] = ;      //12 Получить Param1 чертежей постройки Power
      [*] = ;      12 :
      [*] = ;      begin
      [*] = ;         var pAvOuterBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'AvOuterBuildings');
      [*] = ;         var pAvOuterBuilding : Integer = ParserSelectByHandleByIndex(pAvOuterBuildings, power);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pAvOuterBuilding, 'Count');
      [*] = ;         if count >= 0 then
      [*] = ;         count := count + param1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pAvOuterBuilding, 'Count', count);
      [*] = ;
      [*] = ;         //var itemID : Integer = gPrototypeData.items.number + gPrototypeData.spells.number + gPrototypeData.defenders.number + power;
      [*] = ;         IntRegister0 := power;
      [*] = ;         IntRegister1 := 12;
      [*] = ;         MapExecuteState('GetExtItemIDByType');
      [*] = ;         var itemID : Integer = IntRegister2;
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;         var pEventItems : Integer = ParserSelectByHandleByKey(pPlParser, 'EventItems');
      [*] = ;         var pEventItem : Integer = ParserAddChildByIndex(pEventItems, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pEventItem, 'ItemID', itemID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pEventItem, 'Durability', itemDur);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pEventItem, 'Picked', false);
      [*] = ;      end;
      [*] = ;      //13 Получить Param1 свитков заклинания Power
      [*] = ;      13 :
      [*] = ;      begin
      [*] = ;         //var itemID : Integer = gPrototypeData.items.number + power;
      [*] = ;         IntRegister0 := power;
      [*] = ;         IntRegister1 := 10;
      [*] = ;         MapExecuteState('GetExtItemIDByType');
      [*] = ;         var itemID : Integer = IntRegister2;
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;         for j := 0 to param1-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            IntRegister1 := itemDur;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;
      [*] = ;            var pEventItems : Integer = ParserSelectByHandleByKey(pPlParser, 'EventItems');
      [*] = ;            var pEventItem : Integer = ParserAddChildByIndex(pEventItems, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'ItemID', itemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'Durability', itemDur);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pEventItem, 'Picked', false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //14 Получить случайный предмет уровня Power, c редкостью не ниже Param1
      [*] = ;      14 :
      [*] = ;      begin
      [*] = ;         var sum : Integer = 0;
      [*] = ;         var pArItems : Integer = _misc_ParserGetOrCreateByKey('query_ArItems',true);
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pItems) do
      [*] = ;         begin
      [*] = ;            var pItem : Integer = ParserSelectByHandleByIndex(pitems, j);
      [*] = ;            var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;            var itemLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;            var itemRarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;//if item matches criteria check rarity and store frequency on the item.
      [*] = ;            if (itemLevel = power) and (itemRarity >= param1) then
      [*] = ;            begin
      [*] = ;               var freq : Integer = 7 - itemRarity;
      [*] = ;               var pArItem : Integer = ParserAddChildByIndex(pArItems, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pArItem, 'ItemID', itemID);
      [*] = ;               ParserSetIntValueByKeyByHandle(pArItem, 'Freq', freq);
      [*] = ;//sum the frequencies of all criteria-meeting items.
      [*] = ;               sum := sum + freq;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;//take a random number from the sum of frequencies.
      [*] = ;         var iWork : Integer = 0;
      [*] = ;         if sum > 0 then
      [*] = ;         begin
      [*] = ;            var randSum : Integer = _rand_Random(sum);
      [*] = ;//iterate through all the items and deduct their individual frequency from the random number one by one.
      [*] = ;            for j := 0 to ParserGetCountByHandle(pArItems)-1 do
      [*] = ;            begin
      [*] = ;               var pArItem : Integer = ParserSelectByHandleByIndex(pArItems, j);
      [*] = ;               randSum := randSum - ParserGetIntValueByKeyByHandle(pArItem, 'Freq');
      [*] = ;//once the number hits below zero, the item currently under iteration is chosen. The higher the frequency, the more likely it is to hit below zero during the iteration of the item in question.
      [*] = ;               if randSum < 0 then
      [*] = ;               begin
      [*] = ;                  iWork := ParserGetIntValueByKeyByHandle(pArItem, 'ItemID');
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if iWork > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := iWork;
      [*] = ;            MapExecuteState('GetItemParserByID');
      [*] = ;            var pItem : Integer = IntRegister1;
      [*] = ;            var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;            IntRegister0 := iWork;
      [*] = ;            IntRegister1 := itemDur;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;
      [*] = ;            var pEventItems : Integer = ParserSelectByHandleByKey(pPlParser, 'EventItems');
      [*] = ;            var pEventItem : Integer = ParserAddChildByIndex(pEventItems, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'ItemID', iWork);
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'Durability', itemDur);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pEventItem, 'Picked', false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //15 Установить уровень атакующего отряда Power. Power is the index of guardID struct in guardtype.
      [*] = ;      15 :
      [*] = ;      begin
      [*] = ;         gIntRegister_EventAttackerLevel := power;
      [*] = ;      end;
      [*] = ;      //16 Получить Param1 предметов Power с прочностью Param2%
      [*] = ;      16 :
      [*] = ;      begin
      [*] = ;         var itemID : Integer = power;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;         itemDur := (itemDur*Param2) div 100;
      [*] = ;
      [*] = ;         var pEventItems : Integer = ParserSelectByHandleByKey(pPlParser, 'EventItems');
      [*] = ;
      [*] = ;         for j := 0 to param1-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            IntRegister1 := itemDur;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;
      [*] = ;            var pEventItem : Integer = ParserAddChildByIndex(pEventItems, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'ItemID', itemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'Durability', itemDur);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pEventItem, 'Picked', false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //17 Установить флаг события Power в значение Param1 + Random(Param2). (-1 включено, 0 - отключено, Х>0 произойдёт через Х ходов и отключится)
      [*] = ;      17 :
      [*] = ;      begin
      [*] = ;         var timer : Integer = param1 + _rand_Random(param2);
      [*] = ;         var eventID : Integer = power;
      [*] = ;         var pEventTimer : Integer = 0;
      [*] = ;
      [*] = ;         var pEventTimers : Integer = ParserSelectByHandleByKey(pPlParser, 'EventTimers');
      [*] = ;         for j := ParserGetCountByHandle(pEventTimers)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pTmpEventTimer : Integer = ParserSelectByHandleByIndex(pEventTimers, j);
      [*] = ;            var id : Integer =  ParserGetIntValueByKeyByHandle(pTmpEventTimer, 'EventID');
      [*] = ;
      [*] = ;            if id = eventID then
      [*] = ;            begin
      [*] = ;               pEventTimer := pTmpEventTimer;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if timer = -1 then
      [*] = ;         begin
      [*] = ;            if pEventTimer <> 0 then
      [*] = ;            ParserFreeByHandle(pEventTimer);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if pEventTimer = 0 then
      [*] = ;            begin
      [*] = ;               pEventTimer := ParserAddChildByIndex(pEventTimers, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pEventTimer, 'EventID', eventID);
      [*] = ;            end;
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventTimer, 'Timer', timer);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //18 Привязать флаг события Power к Param1=0 случайной провинции(по умолчанию), 1 текущей провинции, 2 родовой провинции
      [*] = ;      18 :
      [*] = ;      begin
      [*] = ;         var eventID : Integer = power;
      [*] = ;         var pEventTimer : Integer = 0;
      [*] = ;
      [*] = ;         var pEventTimers : Integer = ParserSelectByHandleByKey(pPlParser, 'EventTimers');
      [*] = ;         for j :=  ParserGetCountByHandle(pEventTimers)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pTmpEventTimer : Integer = ParserSelectByHandleByIndex(pEventTimers, j);
      [*] = ;            var id : Integer =  ParserGetIntValueByKeyByHandle(pTmpEventTimer, 'EventID');
      [*] = ;
      [*] = ;            if id = eventID then
      [*] = ;            begin
      [*] = ;               pEventTimer := pTmpEventTimer;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if pEventTimer = 0 then
      [*] = ;         begin
      [*] = ;            pEventTimer := ParserAddChildByIndex(pEventTimers, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventTimer, 'EventID', eventID);
      [*] = ;         end;
      [*] = ;
      [*] = ;         case param1 of
      [*] = ;            0 : ParserSetIntValueByKeyByHandle(pEventTimer, 'DummyUID', 0);
      [*] = ;            1 : ParserSetIntValueByKeyByHandle(pEventTimer, 'DummyUID', dummyUID);
      [*] = ;            2 : ParserSetIntValueByKeyByHandle(pEventTimer, 'DummyUID', cDummyUID);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //19 Установить в провинции охранника Power, если Power=0 - уволить охранника
      [*] = ;      19 :
      [*] = ;      begin
      [*] = ;         if power = 0 then
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'DismissDefender');
      [*] = ;
      [*] = ;         IntRegister0 := power;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'PlaceDefender');
      [*] = ;
      [*] = ;         value := power;
      [*] = ;      end;
      [*] = ;      //20 Уничтожить постройку Power
      [*] = ;      20 :
      [*] = ;      begin
      [*] = ;         var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;         for j := ParserGetCountByHandle(pProvOuterBuildings)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;            var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;            if buildID = power then
      [*] = ;            begin
      [*] = ;               IntRegister0 := j;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'RazeBuilding');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         value := power;
      [*] = ;      end;
      [*] = ;      //21 Возвести постройку Power
      [*] = ;      21 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;         var slotInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;         IntRegister0 := power;
      [*] = ;         IntRegister1 := slotInd;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;
      [*] = ;         value := power;
      [*] = ;      end;
      [*] = ;      // 22 Изменить коррупцию на Power+Random(Param1)
      [*] = ;      22 :
      [*] = ;      begin
      [*] = ;         var plCorrupt : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCorruption);
      [*] = ;         value := _misc_CalcEffect(pEffect, provLevel, plCorrupt);
      [*] = ;         plCorrupt := plCorrupt + value;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iCorruption, plCorrupt);
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCorruption');
      [*] = ;      end;
      [*] = ;      // 23 Изменить доход кристаллов с провинции на Power+Random(Param1)
      [*] = ;      23 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := 2;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;         var oldGemInc : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var GemInc : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'GemInc');
      [*] = ;         value := power + _rand_Random(param1);
      [*] = ;
      [*] = ;         GemInc := GemInc + value;
      [*] = ;         if GemInc < 0 then
      [*] = ;            GemInc := 0;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'GemInc', GemInc);
      [*] = ;         IntRegister0 := 2;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;         var newGemInc : Integer = IntRegister1;
      [*] = ;
      [*] = ;         value := newGemInc - oldGemInc;
      [*] = ;         if _log then _log_map('Effect: 23 Изменить доход кристаллов с провинции на ' + IntToStr(power) + ' + Random(' + IntToStr(Param1) + ')');
      [*] = ;         if _log then _log_map('GemInc = ' + IntToStr(GemInc));
      [*] = ;      end;
      [*] = ;      //24 Уничтожить в провинции сайт Power
      [*] = ;      24 :
      [*] = ;      begin
      [*] = ;         var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;         var provExplored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;         var siteInd : Integer = -1;
      [*] = ;         value := power;
      [*] = ;
      [*] = ;         for j := 0 to  ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;         begin
      [*] = ;            var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;            var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;            var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;
      [*] = ;            if (siteID = power) and (siteExplore <= provExplored) then
      [*] = ;            begin
      [*] = ;               siteInd := j;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if siteInd = -1 then
      [*] = ;         begin
      [*] = ;            for j := 0 to  ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;            begin
      [*] = ;               var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;               var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;
      [*] = ;               if (siteID = power) then
      [*] = ;               begin
      [*] = ;                  siteInd := j;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if siteInd >= 0 then
      [*] = ;         begin
      [*] = ;            var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteInd);
      [*] = ;            var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvSite, 'SiteID', 0);
      [*] = ;            ParserFreeByHandle(pSiteGuard);
      [*] = ;            if dummyHandle <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := gc_province_uf_sites_updated;
      [*] = ;               StringRegister0 := _log_name;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'MergeUpdateFlags');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //25 Разрушить Power построек в провинции
      [*] = ;      25 :
      [*] = ;      begin
      [*] = ;         var count : Integer = power;
      [*] = ;         var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pProvOuterBuildings)-1 do
      [*] = ;         begin
      [*] = ;            var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;            var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;            if buildID > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := buildID;
      [*] = ;               MapExecuteState('GetOuterBuildParserByID');
      [*] = ;               var pOuterBuilding : Integer = IntRegister1;
      [*] = ;               var wall : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Wall');
      [*] = ;
      [*] = ;               if wall = 0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  GameObjectExecuteStateByHandle(dummyHandle, 'RazeBuilding');
      [*] = ;                  count := count - 1;
      [*] = ;                  if count = 0 then
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         value := power;
      [*] = ;      end;
      [*] = ;      // 26 Изменить отношение к игроку во всех провинциях расы Power на Param1
      [*] = ;      26 :
      [*] = ;      begin
      [*] = ;         var raceID : Integer = power;
      [*] = ;         value := param1;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, j);
      [*] = ;            var dummyUID1 : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle1 : Integer = GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;            var provRaceID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;
      [*] = ;            if provRaceID = raceID then
      [*] = ;            begin
      [*] = ;               IntRegister0 := plHandle;
      [*] = ;               IntRegister1 := value;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle1, 'ChangeAttitude');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //27 Изменить цену на ресурс Power на Param1+Random(Param2)
      [*] = ;      27 :
      [*] = ;      begin
      [*] = ;         var resID : Integer = power;
      [*] = ;         value := param1 + _rand_Random(param2);
      [*] = ;
      [*] = ;         gGame.resPrices[resID] := gGame.resPrices[resID] + value;
      [*] = ;      end;
      [*] = ;      //!!28 Флаг глобального события, сообщение о котором выдаётся сразу всем игрокам. (пока не работает)
      [*] = ;      //29 Изменить состояние здоровья отрядов героев и охранника в провинции на Power, при повреждении будет учтено сопротивление. Param1=0 - абсолютная величина, 1 - в %, Param2=1 - действует только на живых.
      [*] = ;      29 :
      [*] = ;      begin
      [*] = ;         var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;         var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         IntRegister0 := pGuardUnits;
      [*] = ;         IntRegister1 := power;
      [*] = ;         IntRegister2 := param1;
      [*] = ;         IntRegister3 := param2;
      [*] = ;         MapExecuteState( 'map.ChangeArmyLife');
      [*] = ;
      [*] = ;         var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;         var pDefUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         IntRegister0 := pDefUnits;
      [*] = ;         IntRegister1 := power;
      [*] = ;         IntRegister2 := param1;
      [*] = ;         IntRegister3 := param2;
      [*] = ;         MapExecuteState( 'map.ChangeArmyLife');
      [*] = ;
      [*] = ;         var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;         var pGarrUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;         IntRegister0 := pGarrUnits;
      [*] = ;         IntRegister1 := power;
      [*] = ;         IntRegister2 := param1;
      [*] = ;         IntRegister3 := param2;
      [*] = ;         MapExecuteState( 'map.ChangeArmyLife');
      [*] = ;
      [*] = ;         for j := GetCountOfPlayers-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;            if GetPlayerRaceTagByHandle(plHandle) = gc_map_PlayerRaceTag then
      [*] = ;            begin
      [*] = ;               for k := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(k, plHandle);
      [*] = ;                  var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;                  var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;                  if (not dead) and (curUID = provUID) then
      [*] = ;                  begin
      [*] = ;                     var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;                     var pGOUnits : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;
      [*] = ;                     IntRegister0 := pGOUnits;
      [*] = ;                     IntRegister1 := power;
      [*] = ;                     IntRegister2 := param1;
      [*] = ;                     IntRegister3 := param2;
      [*] = ;                     MapExecuteState( 'map.ChangeArmyLife');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //30 Изменить боевой дух отрядов героев и охранника в провинции на Power+Random(Power1). Если Param2>0 значение вычтется у злых воинов, а добрым прибавится, если<0 - наоборот, на нейтралов не подействует.
      [*] = ;      30 :
      [*] = ;      begin
      [*] = ;         value := power + _rand_Random(param1);
      [*] = ;         var sign : Integer = param2;
      [*] = ;
      [*] = ;         var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;         var pGarrUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;
      [*] = ;         IntRegister0 := pGarrUnits;
      [*] = ;         IntRegister1 := value;
      [*] = ;         IntRegister2 := sign;
      [*] = ;         MapExecuteState( 'map.ChangeArmyMoral');
      [*] = ;
      [*] = ;         var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;         var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;
      [*] = ;         IntRegister0 := pGuardUnits;
      [*] = ;         IntRegister1 := value;
      [*] = ;         IntRegister2 := sign;
      [*] = ;         MapExecuteState( 'map.ChangeArmyMoral');
      [*] = ;
      [*] = ;         var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;         var pDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;
      [*] = ;         IntRegister0 := pDefUnits;
      [*] = ;         IntRegister1 := value;
      [*] = ;         IntRegister2 := sign;
      [*] = ;         MapExecuteState( 'map.ChangeArmyMoral');
      [*] = ;
      [*] = ;         for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;            var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;            var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;            if (not isDead) and (curUID = dummyUID) then
      [*] = ;            begin
      [*] = ;               var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;               var pGOUnits : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;
      [*] = ;               IntRegister0 := pGOUnits;
      [*] = ;               IntRegister1 := value;
      [*] = ;               IntRegister2 := sign;
      [*] = ;               MapExecuteState('map.ChangeArmyMoral');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //31 Инициировать восстание в провинции
      [*] = ;      31 :
      [*] = ;      begin
      [*] = ;         gBoolRegister_EventIsRebel := true;
      [*] = ;      end;
      [*] = ;      //32 Починить/повредить укрепления в провинции на Power+Random(Param1)
      [*] = ;      32 :
      [*] = ;      begin
      [*] = ;         var fort : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Fort');
      [*] = ;         value := power + _rand_Random(param1);
      [*] = ;         fort := fort + value;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetMaxFortValue');
      [*] = ;         var maxFortValue : Integer = IntRegister0;
      [*] = ;
      [*] = ;         if fort > maxFortValue then
      [*] = ;         fort := maxFortValue;
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'Fort', fort);
      [*] = ;      end;
      [*] = ;      //33 Установить значение флага кампании Power равным Param1
      [*] = ;      33 :
      [*] = ;      begin
      [*] = ;         gCampaign.arrDialogs[power] := param1;
      [*] = ;      end;
      [*] = ;      //34 Добавить игроку в кампании Power+Random(Param1) энергии.
      [*] = ;      34 :
      [*] = ;      begin
      [*] = ;         var energy : Integer = power + _rand_Random(param1);
      [*] = ;         gCampaign.arrCampPlayers[0].energy := gCampaign.arrCampPlayers[0].energy + energy;
      [*] = ;      end;
      [*] = ;      //35 Открыть доступ к постройке в кампании
      [*] = ;      35 :
      [*] = ;      begin
      [*] = ;         if gGame.gameType = 2 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := 0;
      [*] = ;            IntRegister2 := gCampaign.activeShard;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            MapExecuteState('astral.CreateBuildingList');
      [*] = ;            var buildCount : Integer = IntRegister3;
      [*] = ;
      [*] = ;            if buildCount > 0 then
      [*] = ;            begin
      [*] = ;               var buildID : Integer = _rand_Roll(false);
      [*] = ;               gCampaign.arrCampPlayers[0].arrBuilds[buildID] := 1;
      [*] = ;
      [*] = ;               //var itemID : Integer = gPrototypeData.items.number + gPrototypeData.spells.number + gPrototypeData.defenders.number +
      [*] = ;               //gPrototypeData.outerBuildings.number + gPrototypeData.rituals.number + buildID;
      [*] = ;               IntRegister0 := buildID;
      [*] = ;               IntRegister1 := 14;
      [*] = ;               MapExecuteState('GetExtItemIDByType');
      [*] = ;               var itemID : Integer = IntRegister2;
      [*] = ;
      [*] = ;               var pEventItems : Integer = ParserSelectByHandleByKey(pPlParser, 'EventItems');
      [*] = ;               var pEventItem : Integer = ParserAddChildByIndex(pEventItems, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pEventItem, 'ItemID', itemID);
      [*] = ;               ParserSetIntValueByKeyByHandle(pEventItem, 'Durability', 0);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pEventItem, 'Picked', true);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //36 Добавить в гарнизон Param1 юнитов Power с опытом от 0 до Param2
      [*] = ;      36 :
      [*] = ;      begin
      [*] = ;         var unitID : Integer = power;
      [*] = ;         var unitExp : Integer = _rand_Random(param2);
      [*] = ;
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;         var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;
      [*] = ;         var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;         var pGarrUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;
      [*] = ;         for j := 0 to param1-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := pProvGarrison;
      [*] = ;            IntRegister1 := rank;
      [*] = ;            MapExecuteState('map.GetFreeGarrisonSlot');
      [*] = ;            var slotRank : Integer = IntRegister2;
      [*] = ;            var slotInd : Integer = IntRegister3;
      [*] = ;
      [*] = ;            if (slotRank > 0) and (slotInd >= 0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pProvGarrison;
      [*] = ;               IntRegister1 := unitID;
      [*] = ;               IntRegister2 := unitExp;
      [*] = ;               IntRegister3 := slotRank;
      [*] = ;               IntRegister4 := slotInd;
      [*] = ;               MapExecuteState('map.AddUnitToGarrison');
      [*] = ;            end
      [*] = ;            else
      [*] = ;               break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //37 Перейти к событию кампании Power (в момент обнаружения команды)
      [*] = ;      //38 При потере золота в этом событии будет учтена сокровищница
      [*] = ;      38 :
      [*] = ;      begin
      [*] = ;         bGuardGold := true;
      [*] = ;      end;
      [*] = ;      //39 Сделать провинцию нейтральной
      [*] = ;      39 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'DismissDefender');
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'MakeNeutral');
      [*] = ;
      [*] = ;         if _log then _log_map('Effect: 39 Сделать провинцию нейтральной');
      [*] = ;      end;
      [*] = ;      //40 Получить случайный предмет типа Power уровня Param1, c редкостью не ниже Param2.
      [*] = ;      //(1, 2, 9 Оружие и щиты, 3 Луки и стрелы, 4 Жезлы и сферы, 5 Знамёна, 6 кожа и пояса, 7 Кольчуги, 8 Латы, 10 Свитки, 11 Страж, 12 Чертёж, 13 Ритуал, -1 Одежда, -2 Украшения)
      [*] = ;      40 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := power;
      [*] = ;         IntRegister1 := param1;
      [*] = ;         IntRegister2 := param2;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         MapExecuteState('map.ShopRoller');
      [*] = ;         var extItemID : Integer = _rand_Roll(false);
      [*] = ;
      [*] = ;         // TODO : items array
      [*] = ;         //if (Lootz<6)
      [*] = ;         //{
      [*] = ;         //	Treasurez[Lootz][0]=iWork;
      [*] = ;         //	Treasurez[Lootz][1]=(pFirstItem+iWork)->iDurability;
      [*] = ;         //	Lootz++;
      [*] = ;         //};
      [*] = ;
      [*] = ;         IntRegister0 := extItemID;
      [*] = ;         MapExecuteState('GetExtItemParserByID');
      [*] = ;         var pExtItem : Integer = IntRegister1;
      [*] = ;         var extItemType : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'ItemType');
      [*] = ;         var extItemDur : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'Durability');
      [*] = ;
      [*] = ;         var pItemAbilities : Integer = ParserSelectByHandleByKey(pExtItem, 'Abilities');
      [*] = ;         var pItemAbility : Integer = ParserSelectByHandleByIndex(pItemAbilities, 0);
      [*] = ;         var abilPower : Integer = ParserGetIntValueByKeyByHandle(pItemAbility, 'Power');
      [*] = ;
      [*] = ;         if (extItemID>0) then
      [*] = ;         begin
      [*] = ;            var pEventItems : Integer = ParserSelectByHandleByKey(pPlParser, 'EventItems');
      [*] = ;            var pEventItem : Integer = ParserAddChildByIndex(pEventItems, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'ItemID', extItemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pEventItem, 'Durability', extItemDur);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pEventItem, 'Picked', false);
      [*] = ;         end;
      [*] = ;
      [*] = ;         case extItemType of
      [*] = ;            11 :
      [*] = ;            begin
      [*] = ;               // defender agreement
      [*] = ;               var pPlDefenders : Integer = ParserSelectByHandleByKey(pCastle, 'Defenders');
      [*] = ;               var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, abilPower);
      [*] = ;               var agrCount : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;
      [*] = ;               if agrCount >= 0 then
      [*] = ;               begin
      [*] = ;                  agrCount := agrCount + 1;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pPlDefender, 'Count', agrCount);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            12 :
      [*] = ;            begin
      [*] = ;               var pAvOuterBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'AvOuterBuildings');
      [*] = ;               var pAvOuterBuilding : Integer = ParserSelectByHandleByIndex(pAvOuterBuildings, abilPower);
      [*] = ;               var count : Integer = ParserGetIntValueByKeyByHandle(pAvOuterBuilding, 'Count');
      [*] = ;
      [*] = ;               if count >= 0 then
      [*] = ;               ParserSetIntValueByKeyByHandle(pAvOuterBuilding, 'Count', count+1);
      [*] = ;            end;
      [*] = ;            13 :
      [*] = ;            begin
      [*] = ;               var pAvRituals : Integer = ParserSelectByHandleByKey(pCastle, 'AvailableRituals');
      [*] = ;               var pAvRitual : Integer = ParserSelectByHandleByIndex(pAvRituals, abilPower);
      [*] = ;               var count : Integer = ParserGetIntValueByKeyByHandle(pAvRitual, 'Count');
      [*] = ;
      [*] = ;               if count >= 0 then
      [*] = ;               ParserSetIntValueByKeyByHandle(pAvRitual, 'Count', count + 1);
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := extItemID;
      [*] = ;               IntRegister1 := extItemDur;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //41 Удалить из сокровищницы предмет Power
      [*] = ;      41 :
      [*] = ;      begin
      [*] = ;         for j := 0 to ParserGetCountByHandle(pTreasurySlots)-1 do
      [*] = ;         begin
      [*] = ;            var pTreasurySlot : Integer = ParserSelectByHandleByIndex(pTreasurySlots, j);
      [*] = ;            var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'ItemID');
      [*] = ;
      [*] = ;            if itemID = power then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pTreasurySlot, 'ItemID', 0);
      [*] = ;               ParserSetIntValueByKeyByHandle(pTreasurySlot, 'Durability', 0);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         value := power;
      [*] = ;      end;
      [*] = ;      //42 Получить Param1 договоров со стражем Power
      [*] = ;      42 :
      [*] = ;      begin
      [*] = ;         var pPlDefenders : Integer = ParserSelectByHandleByKey(pCastle, 'Defenders');
      [*] = ;         var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, power);
      [*] = ;         var defCount : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;
      [*] = ;         if defCount >= 0 then
      [*] = ;         begin
      [*] = ;            defCount := defCount + param1;
      [*] = ;            ParserSetIntValueByKeyByHandle(pPlDefender, 'Count', defCount);
      [*] = ;            // TODO: inert code
      [*] = ;            //if (Lootz<6)
      [*] = ;            //{
      [*] = ;            // for (int k=1; k<iMaxItem; k++)
      [*] = ;            // {
      [*] = ;            //    if (((pFirstItem+k)->arEffect[0][0]==86)&&((pFirstItem+k)->arEffect[0][1]==EV->arEffect[Eff][1]))
      [*] = ;            //    Treasurez[Lootz][0]=k;
      [*] = ;            //    Treasurez[Lootz][1]=1;
      [*] = ;            // };
      [*] = ;            // Lootz++;
      [*] = ;            //};
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      50 : begin // set if param1 > 0 or reset if param1 <= 0 flag power
      [*] = ;
      [*] = ;         if ((power<=0) or (power > gc_MaxScenarioEventFlags)) then
      [*] = ;            ErrorLog('Scenario flag index is too big or too small ('+IntToStr(power)+')')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var process : Boolean = true;
      [*] = ;
      [*] = ;            if param2 <> 0 then
      [*] = ;            begin
      [*] = ;               if param2 > 0 then
      [*] = ;               begin
      [*] = ;                  if ((gIntRegister_ScenarioEventFlags and (1 shl (param2-1))) = 0) then
      [*] = ;                     process := false;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if ((gIntRegister_ScenarioEventFlags and (1 shl (-1*(param2-1)))) <> 0) then
      [*] = ;                     process := false;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if process then
      [*] = ;            begin
      [*] = ;               if param1 > 0 then
      [*] = ;                  gIntRegister_ScenarioEventFlags := gIntRegister_ScenarioEventFlags or (1 shl power)
      [*] = ;               else
      [*] = ;                  gIntRegister_ScenarioEventFlags := gIntRegister_ScenarioEventFlags and ($ffffffff xor (1 shl power));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if i = 0 then
      [*] = ;      gIntRegister_EffectValue := Round(Abs(value));
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pEffects)-1 do
      [*] = ;begin
      [*] = ;   var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, i);
      [*] = ;   var index : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;   var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;   var value : Integer = 0;
      [*] = ;
      [*] = ;   case index of
      [*] = ;      // 1 Получить Power+Random(Param1) золота.
      [*] = ;      //
      [*] = ;      //      Если Param2=
      [*] = ;      //      1, величина умножается на уровень провинции
      [*] = ;      //      2 - изменяет количество имеющегося золота на Power+Random(Param1)%
      [*] = ;      //
      [*] = ;      1 :
      [*] = ;      begin
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         value := _misc_CalcEffect(pEffect, provLevel, plGold);
      [*] = ;
      [*] = ;         if (value < 0) and bGuardGold then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 33;
      [*] = ;            GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuildAbility');
      [*] = ;            var abil33 : Integer = IntRegister1;
      [*] = ;
      [*] = ;            value := value - Floor(value * abil33 / 10);
      [*] = ;         end;
      [*] = ;
      [*] = ;         gIntRegister_TreasureGoldReward := value; //used in ToolQueryWindow
      [*] = ;         plGold := plGold + value;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;
      [*] = ;         if (value<>0) and bInterfacePlayer then
      [*] = ;         _gui_PlaySound('interface', 'money_spent');
      [*] = ;
      [*] = ;         if _log then _log_map('Effect: 1 Получить ' + IntToStr(power) + ' + Random(' + IntToStr(Param1) + ') золота');
      [*] = ;         if _log then _log_map('Player gold = ' + IntToStr(plGold));
      [*] = ;
      [*] = ;         plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + value);
      [*] = ;
      [*] = ;         if i = 0 then
      [*] = ;            gIntRegister_EffectValue := Round(Abs(value));
      [*] = ;
      [*] = ;         gIntRegister_GoldReward := value;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;//ParserFreeByHandle(pArItems);
      [*] = ;
      [*] = ;var resultsHandle : Integer = QueryMachineQueryGetResults(queryHandle);
      [*] = ;var countResults : Integer = QueryMachineResultsCount(resultsHandle);
      [*] = ;var guardType : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Attacker');
      [*] = ;
      [*] = ;if (countResults = 0) and (guardType > 0) then
      [*] = ;begin
      [*] = ;   var provHandle : Integer = _map_GetCurrentProvinceHandle();
      [*] = ;
      [*] = ;   _gv_SetMapLock($10001,_log_name);
      [*] = ;
      [*] = ;   IntRegister0 := guardType;
      [*] = ;   GameObjectExecuteStateByHandle(provHandle, 'GuardAttack');
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

