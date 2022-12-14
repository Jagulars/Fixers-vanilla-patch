section.begin
   Name = ExploreSite
   Description : struct.begin
      [*] = ;IntRegister0 - province handle
      [*] = ;IntRegister1 - site index
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var siteInd : Integer = IntRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\EXPLORESITE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myGOParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteInd);
      [*] = ;var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;var level : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Level');
      [*] = ;
      [*] = ;var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;gIntRegister_BattleDefendArmy := pSiteGuard;
      [*] = ;
      [*] = ;IntRegister0 := siteID;
      [*] = ;MapExecuteState('GetSiteParserByID');
      [*] = ;var pSiteAbilities : Integer = ParserSelectByHandleByKey( IntRegister1, 'Abilities');
      [*] = ;var i : Integer;
      [*] = ;var checkLevel : Boolean = false;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param2');
      [*] = ;
      [*] = ;   case abilID of
      [*] = ;      // 1 ????????????? ??????? Param 1
      [*] = ;      1 :
      [*] = ;      begin
      [*] = ;         _map_RefreshProvinceHUD(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;      end;
      [*] = ;      // +2 ????? ?????? Param 1 ?????????? Param 2
      [*] = ;      // 3 ?????????
      [*] = ;      // +4 ?????????? ??????? Param1 ? ???????????? Param2
      [*] = ;      // +5 ??????????? ?????????? ? ????????? ? ????? Param1
      [*] = ;      // +6 ???????? ????? ?????? ?? Param1%
      [*] = ;      // +7 ???????? ??????? ????????? ?? Param1
      [*] = ;      // +8 ??????? ?????? ?????? ????? Param1
      [*] = ;      // 9 ???? ????????? Param1+Level*Param2 ?????
      [*] = ;      9 :
      [*] = ;      begin
      [*] = ;         var heroExp : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;         var exp : Integer = param1 + level * param2;
      [*] = ;         heroExp := heroExp + exp;
      [*] = ;         SetGameObjectIntValueIndByHandle(myGOHandle, gc_map_GOStack_MapUnit_iExp, heroExp);
      [*] = ;         checkLevel := true;
      [*] = ;      end;
      [*] = ;      // 10 ???? ????????? Param1+Level*Param2 ??????
      [*] = ;      10 :
      [*] = ;      begin
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         var gold : Integer = param1 + level * param2;
      [*] = ;         gIntRegister_GoldReward := gold;
      [*] = ;
      [*] = ;         plGold := plGold + gold;
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;
      [*] = ;         plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;      
      [*] = ;         if _stats_IsEligible(myPlHandle) then _stats_SimpleUpdate('Gold', 'EncounterGold', gold);
      [*] = ;      end;
      [*] = ;      // 11 ???? ????????? Param1+Level*Param2 ??????????
      [*] = ;      11 :
      [*] = ;      begin
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         var gem : Integer = param1 + level * param2;
      [*] = ;         gIntRegister_GemReward := gem;
      [*] = ;
      [*] = ;         plGem := plGem + gem;
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;         plGem := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gem);
      [*] = ;      
      [*] = ;         if _stats_IsEligible(myPlHandle) then _stats_SimpleUpdate('Gem', 'EncounterGem', gem);
      [*] = ;      end;
      [*] = ;      // 12 ???? ????????? ??????????? ?????????
      [*] = ;      12 :
      [*] = ;      begin
      [*] = ;         if level < 2 then
      [*] = ;            level := 2;
      [*] = ;
      [*] = ;         if level > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := siteInd;
      [*] = ;            IntRegister1 := level;
      [*] = ;            ExecuteState('GetSiteTrophies');
      [*] = ;         end;
      [*] = ;
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         var gold : Integer = ParserGetIntValueByKeyByHandle(myGOParser, 'SiteGold');
      [*] = ;         var gem : Integer = ParserGetIntValueByKeyByHandle(myGOParser, 'SiteGem');
      [*] = ;
      [*] = ;         plGold := plGold + gold;
      [*] = ;         plGem := plGem + gem;
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;         plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;
      [*] = ;         plGem := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gem);
      [*] = ;      
      [*] = ;         if _stats_IsEligible(myPlHandle) then
      [*] = ;         begin
      [*] = ;            _stats_SimpleUpdate('Gold', 'EncounterGold', gold);
      [*] = ;            _stats_SimpleUpdate('Gem', 'EncounterGem', gem);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if SameText(cMode, 'cmPC') then
      [*] = ;         begin
      [*] = ;            var pMyLoot : Integer = ParserSelectByHandleByKey(myGOParser, 'SiteLootItems');
      [*] = ;            IntRegister0 := pMyLoot;
      [*] = ;            ExecuteState('TakeLootByParser');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      // +13 ???????, ????????? ?????????? ???? Param1, ? ??????? ?? Param2
      [*] = ;      // +14 (????????? ???????? ??? ?????????) Param1 - ?????????? ?????????, Param2 - ??????? ???????????
      [*] = ;      // +15 ????? ????????? ????? Param1 ? ???????????? Param2
      [*] = ;      // 16 ?????
      [*] = ;      16 :
      [*] = ;      begin
      [*] = ;         if cMode = 'cmPC' then
      [*] = ;         begin
      [*] = ;            var exp : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iExp);
      [*] = ;            var level : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iLevel);
      [*] = ;            exp := exp + 20 + level * 5;
      [*] = ;            SetIntValueByIndex(gc_map_GOStack_MapUnit_iExp, exp);
      [*] = ;
      [*] = ;            checkLevel := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      // +17 ????? ?????? ?????????? Encounter Param1
      [*] = ;      // 18 ????????????? ?????
      [*] = ;      // +19 ???????? ?????????? ??????? ?? Param1
      [*] = ;      // +20 ???????? ????????? ? ????????? ?? Param1
      [*] = ;      // +21 ?????? ???????????? ??????? ???????? ?????? Param1. ???? ????????? ????? ???????????. ??? ???????? ?????? ???? ??????.
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (cMode = 'cmPC') and checkLevel then
      [*] = ;begin
      [*] = ;   var levelUp : Boolean = true;
      [*] = ;   while levelUp do
      [*] = ;   begin
      [*] = ;      ExecuteState('IsLevelUp');
      [*] = ;      levelUp := BoolRegister0;
      [*] = ;
      [*] = ;      if levelUp then
      [*] = ;         ExecuteState('AIHeroLevelUp');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

