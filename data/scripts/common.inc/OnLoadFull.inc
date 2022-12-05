section.begin
   Name = OnLoadFull
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\ONLOADFULL';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;TimeLog('OnLoadFull start');
      [*] = ;
      [*] = ;var pMachineParser : Integer = ParserSelectCurrentStateMachine();
      [*] = ;
      [*] = ;var activeDLC : Boolean = false;
      [*] = ;var versionChanged : Boolean = false;//(gIntRegister_GVLogging = gc_gvlog_log_all);
      [*] = ;
      [*] = ;var curVersion : String;
      [*] = ;_misc_GetBuildVersionExt(curVersion);
      [*] = ;var oldVersion : String = ParserGetValueByKeyByHandle(pMachineParser, 'Version');
      [*] = ;if not SameText(curVersion, oldVersion) then
      [*] = ;begin
      [*] = ;   versionChanged := true;
      [*] = ;   if oldVersion <> '' then
      [*] = ;      Log('Version changed: Old Version: '+oldVersion)
      [*] = ;   else
      [*] = ;      Log('Version changed: Old Version: ???');
      [*] = ;end;
      [*] = ;
      [*] = ;function SaveObjectToFile(idx,tag,p : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(idx);
      [*] = ;
      [*] = ;   if (tag = -1) or (GetPlayerRaceTagByHandle(plHandle) = tag) then
      [*] = ;   begin
      [*] = ;      var i,n,po,ps,h,ph,j,k : Integer;
      [*] = ;      var nm : String;
      [*] = ;
      [*] = ;      IntRegister0 := p;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'SaveInfoToParser');
      [*] = ;
      [*] = ;      nm := GetPlayerNameByIndex(idx);
      [*] = ;      LogI(_log_name+'. Object: '+nm);
      [*] = ;      ParserSetValueByKeyByHandle(p, 'PlayerName', nm);
      [*] = ;      ParserSetValueByKeyByHandle(p, 'PlayerControlMode', GetPlayerControlModeByHandle(plHandle));
      [*] = ;      n := GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'GameObjectsNo', n);
      [*] = ;      po := ParserAddChildByIndex(p, 'GameObjects');
      [*] = ;
      [*] = ;      for i := 0 to n-1 do
      [*] = ;      begin
      [*] = ;         h := GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;         ph := ParserAddChildByIndex(po, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(ph, 'Idx', i);
      [*] = ;         nm := GetGameObjectBaseNameByHandle(h);
      [*] = ;         ParserSetValueByKeyByHandle(ph, 'Name', nm);
      [*] = ;      end;
      [*] = ;      Result := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FixItemParser(pItemParser : Integer);
      [*] = ;begin
      [*] = ;   var itemID : Integer = ParserGetIntValueByKeyByHandle(pItemParser, 'ItemID');
      [*] = ;   var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.items.handle, itemID);
      [*] = ;   if not ParserGetBoolValueByKeyByHandle(pItem, 'Breakable') then
      [*] = ;      ParserSetIntValueByKeyByHandle(pItemParser, 'Durability', -1);
      [*] = ;end;
      [*] = ;
      [*] = ;function FixUpgradesParser(var pMyUpgrades : Integer; unitID, level : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var myUpgCount : Integer = ParserGetCountByHandle(pMyUpgrades);
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   // add missing upgrades
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;   var pStartUpgrades : Integer = ParserSelectByHandleByKey(pUnit, 'StartUpgrades');
      [*] = ;   var stUpgCount : Integer = ParserGetCountByHandle(pStartUpgrades);
      [*] = ;
      [*] = ;   for i := 0 to stUpgCount-1 do
      [*] = ;   begin
      [*] = ;      var pStartUpgrade : Integer = ParserSelectByHandleByIndex(pStartUpgrades, i);
      [*] = ;      var stId : Integer = ParserGetIntValueByKeyByHandle(pStartUpgrade, 'UpgradeID');
      [*] = ;
      [*] = ;      var pMyUpgrade : Integer = ParserSelectByHandleByIndex(pMyUpgrades, i);
      [*] = ;      var myID : Integer = ParserGetIntValueByKeyByHandle(pMyUpgrade, 'UpgradeID');
      [*] = ;
      [*] = ;      if stId <> myID then
      [*] = ;      begin
      [*] = ;         for j := myUpgCount-level-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pMyUpgrade : Integer = ParserSelectByHandleByIndex(pMyUpgrades, j);
      [*] = ;            ParserFreeByHandle(pMyUpgrade);
      [*] = ;         end;
      [*] = ;
      [*] = ;         for j := 0 to stUpgCount-1 do
      [*] = ;            ParserAddChildByIndex(pMyUpgrades, '*');
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pMyUpgrades)-1 downto stUpgCount do
      [*] = ;         begin
      [*] = ;            var pUpgrade1 : Integer = ParserSelectByHandleByIndex(pMyUpgrades, j);
      [*] = ;            var pUpgrade2 : Integer = ParserSelectByHandleByIndex(pMyUpgrades, j-stUpgCount);
      [*] = ;            var id2 : Integer = ParserGetIntValueByKeyByHandle(pUpgrade2, 'UpgradeID');
      [*] = ;            ParserSetIntValueByKeyByHandle(pUpgrade1, 'UpgradeID', id2);
      [*] = ;         end;
      [*] = ;
      [*] = ;         for j := 0 to stUpgCount-1 do
      [*] = ;         begin
      [*] = ;            var pStartUpgrade : Integer = ParserSelectByHandleByIndex(pStartUpgrades, j);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pStartUpgrade, 'UpgradeID');
      [*] = ;
      [*] = ;            var pMyUpgrade : Integer = ParserSelectByHandleByIndex(pMyUpgrades, j);
      [*] = ;            ParserSetIntValueByKeyByHandle(pMyUpgrade, 'UpgradeID', id);
      [*] = ;         end;
      [*] = ;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FixUnitsParser(pParser : Integer;armyType : String;provinceUID : Integer);
      [*] = ;begin
      [*] = ;   var pParserUnits : Integer = ParserSelectByHandleByKey(pParser, 'Units');
      [*] = ;   var i, j, k, no, p : Integer;
      [*] = ;
      [*] = ;   no := ParserGetCountByHandle(pParserUnits);
      [*] = ;   if no > gc_MaxArmyCount then
      [*] = ;   begin
      [*] = ;      for i := no-1 downto gc_MaxArmyCount do
      [*] = ;      begin
      [*] = ;         p := ParserSelectByHandleByIndex(pParserUnits, i);
      [*] = ;         ParserFreeByHandle(p);
      [*] = ;      end;
      [*] = ;      ErrorLogI('Army units number fixed from '+IntToStr(no)+' down to '+IntToStr(gc_MaxArmyCount)+'. Entity: '+armyType+', ProvinceUID: '+IntToStr(provinceUID));
      [*] = ;      no := gc_MaxArmyCount;
      [*] = ;   end;
      [*] = ;   for i := no-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pParserUnit : Integer = ParserSelectByHandleByIndex(pParserUnits, i);
      [*] = ;      var unitID : Integer = ParserGetIntValueByKeyByHandle(pParserUnit, 'UnitID');
      [*] = ;
      [*] = ;      {if not activeDLC then
      [*] = ;      begin
      [*] = ;         var curLife : Integer = ParserGetIntValueByKeyByHandle(pParserUnit, 'CurLife');
      [*] = ;         case unitID of
      [*] = ;            72, 73 : unitID := 34; //centaur
      [*] = ;            74, 75 : unitID := 16; //dwarf
      [*] = ;            76, 77 : unitID := 15; //elf
      [*] = ;            78, 79 : unitID := 13; //goblin
      [*] = ;            80, 81 : unitID := 18; //halfling
      [*] = ;            82, 83 : unitID := 69; //lizardman
      [*] = ;            84, 85 : unitID := 14; //goblin
      [*] = ;         end;
      [*] = ;         ParserSetIntValueByKeyByHandle(pParserUnit, 'UnitID', unitID);
      [*] = ;      end;}
      [*] = ;   
      [*] = ;      var level : Integer = ParserGetIntValueByKeyByHandle(pParserUnit, 'Level');
      [*] = ;      var pMyUpgrades : Integer = ParserSelectByHandleByKey(pParserUnit, 'Upgrades');
      [*] = ;      FixUpgradesParser(pMyUpgrades, unitID, level);
      [*] = ;
      [*] = ;      if ParserGetBoolValueByKeyByHandle(pParserUnit, 'IsHero') then
      [*] = ;      begin
      [*] = ;         var maphero_handle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pParserUnit, 'HeroUID'));
      [*] = ;         if maphero_handle <> 0 then
      [*] = ;            GameObjectExecuteStateByHandle(maphero_handle, 'RecalcCurrentHP');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := pParserUnit;
      [*] = ;         IntRegister1 := pParserUnits;
      [*] = ;         IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;         ExecuteState('GetUnitPropertyByParser');
      [*] = ;         var maxLife : Integer = IntRegister3;
      [*] = ;         var curLife : Integer = ParserGetIntValueByKeyByHandle(pParserUnit, 'CurLife');
      [*] = ;         var lifeRatio : Float = 0;
      [*] = ;
      [*] = ;         if ParserIsValueExistsByKeyByHandle(pParserUnit, 'LifeRatio') then
      [*] = ;         begin
      [*] = ;            if (curLife > 0) then
      [*] = ;            begin
      [*] = ;               lifeRatio := ParserGetFloatValueByKeyByHandle(pParserUnit, 'LifeRatio');
      [*] = ;               curLife := Round(Clamp(maxLife * lifeRatio, 1, maxLife));
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            lifeRatio := Clamp(curLife / maxLife, 0, 1);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pParserUnit, 'LifeRatio', lifeRatio);
      [*] = ;            curLife := Round(Clamp(maxLife * lifeRatio, 0, maxLife));
      [*] = ;         end;
      [*] = ;         ParserSetIntValueByKeyByHandle(pParserUnit, 'CurLife', curLife);
      [*] = ;         ParserSetFloatValueByKeyByHandle(pParserUnit, 'FCurLife', curLife);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var cBuildEnabled : Boolean = true;
      [*] = ;
      [*] = ;procedure AddUnknownRegisters(pParser : Integer);
      [*] = ;begin
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_ArenaBattle', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_ArenaWatcher', false);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ArenaLeague', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ArenaReward', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ArenaChosenSide', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ArenaBet', 0);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_UpdateHeroPath', false);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_MoveMapHeroHandle', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_QuerySpellUsage', 0);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_RealAIBattle', false);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_CurBattleLogElement', 0);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_ShowBattleLog', false);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_GUIDrawPathUID', 0);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_IsAutoBattle', false);
      [*] = ;
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnEndTurnEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnCastleEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnDiplomacyEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnStatisticsEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRitualEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnExploreEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnPillageEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnEnterSiteEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRitualEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnLibraryEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnGarrisonEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnOuterBuildEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnDefenderEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnShopEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnHeroCloseEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnBatEndTurnEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnCastleCloseEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnAttackShardEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnNextHeroEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnInnerBuildEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnQuarterEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnAdvBuildEnabled', true);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnMenuEnabled', true);
      [*] = ;   cBuildEnabled := _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnCastleBuildEnabled', true);
      [*] = ;
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnEndTurnBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnCastleBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnDiplomacyBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnStatisticsBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRitualBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnExploreBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnPillageBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnEnterSiteBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRitualBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnLibraryBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnGarrisonBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnOuterBuildBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnDefenderBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnShopBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnHeroCloseBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnBatEndTurnBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnNextHeroBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRepairBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRepairAllBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnCastleCloseBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnRecruitHeroBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnAttackShardBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnZarrTalkBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnAstralStatsBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnBattleSettingsBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnSwitchWeaponBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnQuarterBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnAdvBuildBlink', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BtnCastleBuildBlink', false);
      [*] = ;
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_InBattle', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_GUISaveAstral', false);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_TutorialHistoryIndex', 0);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_CheckLevelUp', false);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_VirtualBattleResult', 0);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_VirtualBattleHeroDied', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_DiplomacyInited', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_BrokenWeapon', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_MapResolveConflicts', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_WaitLanQueryResult', false);
      [*] = ;   _pars_CheckBoolValue(pParser, 'gBoolRegister_AfterEndTurn', false); 
      [*] = ;
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_MoodDummyUID', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ConflictHeroUID1', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ConflictHeroUID2', 0);
      [*] = ;   _pars_CheckValue(pParser, 'gStringRegister_ClientQueryID', '');
      [*] = ;
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegsiter_LanReadyPlayersCount', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegsiter_LanShardBatReadyCount', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegsiter_LanBatServerID', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegsiter_LanBatClientID', 0);
      [*] = ;
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_ScenarioEventFlags', 0);
      [*] = ;   _pars_CheckIntValue(pParser, 'gIntRegister_LanMapUID', 0);
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;   var pTutHistory : Integer = ParserSelectByHandleByKey(pParser, 'gArrTutorialHistory');
      [*] = ;   if pTutHistory = 0 then
      [*] = ;   begin
      [*] = ;      for i := 0 to gc_MaxTutorialHistory-1 do
      [*] = ;         gArrTutorialHistory[i] := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pTutorial : Integer = ParserSelectByHandleByKey(pParser, 'gTutorial');
      [*] = ;   if pTutorial <> 0 then
      [*] = ;   begin
      [*] = ;      _pars_CheckIntValue(pTutorial, 'advancedmode', 0);
      [*] = ;      _pars_CheckIntValue(pTutorial, 'buildrank', 0);
      [*] = ;      _pars_CheckBoolValue(pTutorial, 'buyUnit', false);
      [*] = ;      _pars_CheckBoolValue(pTutorial, 'learnSpell', false);
      [*] = ;      _pars_CheckBoolValue(pTutorial, 'buyItem', false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pCampaign : Integer = ParserSelectByHandleByKey(pParser, 'gCampaign');
      [*] = ;   if pCampaign <> 0 then
      [*] = ;   begin
      [*] = ;      var pCampPlayers : Integer = ParserSelectByHandleByKey(pCampaign, 'arrCampPlayers');
      [*] = ;      for i := 0 to ParserGetCountByHandle(pCampPlayers)-1 do
      [*] = ;      begin
      [*] = ;         var pCampPlayer : Integer = ParserSelectByHandleByIndex(pCampPlayers, i);
      [*] = ;         _pars_CheckBoolValue(pCampPlayer, 'buildadded', false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;                  
      [*] = ;   var pArrDiplomacy : Integer = ParserSelectByHandleByKey(pParser, 'gArrDiplomacy');
      [*] = ;   if pArrDiplomacy <> 0 then
      [*] = ;   begin
      [*] = ;      for i := 0 to ParserGetCountByHandle(pArrDiplomacy)-1 do
      [*] = ;      begin
      [*] = ;         var pArDiplomacy : Integer = ParserSelectByHandleByIndex(pArrDiplomacy, i);
      [*] = ;         for j := 0 to ParserGetCountByHandle(pArDiplomacy)-1 do
      [*] = ;         begin
      [*] = ;            var pDiplomacy : Integer = ParserSelectByHandleByIndex(pArDiplomacy, j);
      [*] = ;            _pars_CheckIntValue(pDiplomacy, 'meet', -1);
      [*] = ;            _pars_CheckIntValue(pDiplomacy, 'displayPriority', 0); // this function is pointless, the value is there even if the game was never saved with it. Gives 0 unlike "deal" below for some reason.
      [*] = ;            //_pars_CheckBoolValue(pDiplomacy, 'lanAnswer', false); // this is no longer used
      [*] = ;            var pMessage : Integer = ParserSelectByHandleByKey(pDiplomacy, 'message');
      [*] = ;            if pMessage <> 0 then
      [*] = ;            begin
      [*] = ;               _pars_CheckIntValue(pMessage, 'deal', 0); // this function is also pointless, even if the value is zero in the parser struct, it will load to the game as -1
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var plCount : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByKey(pParser, 'gGame.map'), 'players');
      [*] = ;
      [*] = ;   var pGameArrPlayerDiffiuclty : Integer = ParserSelectByHandleByKey(pParser, 'gGame.arrplayerdifficulty');
      [*] = ;   if (pGameArrPlayerDiffiuclty=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to plCount-1 do
      [*] = ;      begin
      [*] = ;         gGame.arrplayerdifficulty[i].custom := False;
      [*] = ;         var diff : Integer = GetPlayerIntValueIndByHandle(GetPlayerHandleByIndex(i), gc_map_PLStack_MapUnit_iDifficulty);
      [*] = ;         _map_SetGameCustomDifficultyOptionsDefault(gGame.arrplayerdifficulty[i], False, diff);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pGameArrPlayerControl : Integer = ParserSelectByHandleByKey(pParser, 'gGame.arrplayercontrol');
      [*] = ;   if (pGameArrPlayerControl=0) then
      [*] = ;   begin
      [*] = ;      for i:=0 to plCount-1 do
      [*] = ;         gGame.arrplayercontrol[i] := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   i := ParserSelectByHandleByKey(pParser, 'gCampMapHero');
      [*] = ;   if i = 0 then
      [*] = ;      gCampMapHero.units_no := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;var isAstral : Boolean;
      [*] = ;var i, j, k, p, c : Integer;
      [*] = ;
      [*] = ;c := RefreshFileList(gc_dlc_path + gc_dlc_ext);
      [*] = ;for i:=0 to c-1 do
      [*] = ;begin
      [*] = ;   var fnm : String = GetFileListNameByIndex(i);
      [*] = ;   IntRegister0 := 2;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister2 := -1;
      [*] = ;   EvaluateFile(gc_dlc_path + fnm);
      [*] = ;   if IntRegister1 = 1 then
      [*] = ;      activeDLC := true;
      [*] = ;end;
      [*] = ;
      [*] = ;var pCurRegisters : Integer = ParserSelectByHandleByKey(pMachineParser, 'Registers');
      [*] = ;Assert((pCurRegisters<>0),'OnLoadFull : Registers not found');
      [*] = ;if (pCurRegisters<>0) then
      [*] = ;begin
      [*] = ;   if versionChanged then
      [*] = ;      AddUnknownRegisters(pCurRegisters);
      [*] = ;   
      [*] = ;   StateMachineGlobalVariablesLoadFromParser(pCurRegisters, '', true, true);
      [*] = ;end;
      [*] = ;
      [*] = ;//ParserSelectByHandle(pCurRegisters);
      [*] = ;//ParserSaveToFile('OnLoadFullpCurRegisters');
      [*] = ;//ParserClearByHandle(pCurRegisters);
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;   isAstral := false
      [*] = ;else
      [*] = ;   isAstral := true;
      [*] = ;
      [*] = ;if ParserSelectByHandleByKey(pCurRegisters, 'gTutorial') = 0 then
      [*] = ;begin
      [*] = ;   _camp_tutorial_Init();
      [*] = ;   gTutorial.map := false;
      [*] = ;   gTutorial.move := 50;
      [*] = ;end;
      [*] = ;
      [*] = ;if not isAstral then
      [*] = ;begin
      [*] = ;   // restore handles by indices
      [*] = ;   IntRegister0 := pMachineParser;
      [*] = ;   ExecuteState('LoadConvertBatRegisters');
      [*] = ;   
      [*] = ;   // modify custom game data
      [*] = ;   gBoolRegister_ConvertGenesisMode := True;
      [*] = ;   GUIExecuteState('EventGenesisMode');
      [*] = ;   
      [*] = ;   const cDataPath = '.\data\game\var\genesismode.cfg';
      [*] = ;   var pReplacementData : Integer = _misc_ParserGetOrCreateByKey('replacement_data', true);
      [*] = ;   ParserLoadFromFile(cDataPath);
      [*] = ;   
      [*] = ;   IntRegister0 := pReplacementData;
      [*] = ;   BoolRegister0 := True;
      [*] = ;   MapExecuteState('DataBanReplacement');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   gMapSettings.genesismode := gProfile.genesismode;
      [*] = ;end;
      [*] = ;
      [*] = ;// restore players control mode for lan shard game
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;begin
      [*] = ;   var override_mode, plHandle : Integer;
      [*] = ;   var cMode : String;
      [*] = ;
      [*] = ;   // check if we need to override ids for saves
      [*] = ;   p := _misc_GetSaveGameDescriptionParser('');
      [*] = ;   override_mode := ParserGetIntValueByKeyByHandle(p,'OverrideLAN');
      [*] = ;   if override_mode > 1 then
      [*] = ;   begin
      [*] = ;      _log_map('Converting lan game to single/hotseat player game');
      [*] = ;      if override_mode = 2 then
      [*] = ;      begin
      [*] = ;         for i := 1 to gGame.map.players-1 do
      [*] = ;            gGame.arrPlayerControl[i] := 0;
      [*] = ;
      [*] = ;         gGame.gameType := gc_GameTypeCustom;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         gGame.gameType := gc_GameTypeHotseat;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if override_mode = 1 then
      [*] = ;   begin
      [*] = ;      _log_map('Using OVERRIDE for lan load.');
      [*] = ;      j := ParserGetIntValueByKeyByHandle(p,'OverrideLAN_'+IntToStr(gLanShardGame.masterid));
      [*] = ;      if j <> 0 then
      [*] = ;      begin
      [*] = ;         _log_map('Master ID('+IntToStr(gLanShardGame.masterid)+') replaced with ID('+IntToStr(j)+')');
      [*] = ;         gLanShardGame.masterid := j;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         j := ParserGetIntValueByKeyByHandle(p,'OverrideLAN_'+IntToStr(gLanShardGame.arrLanPlayers[i].lanID));
      [*] = ;         if j <> 0 then
      [*] = ;         begin
      [*] = ;            _log_map('Player ID('+IntToStr(gLanShardGame.arrLanPlayers[i].lanID)+') replaced with ID('+IntToStr(j)+')');
      [*] = ;            gLanShardGame.arrLanPlayers[i].lanID := j;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      plHandle := GetPlayerHandleByIndex(i);
      [*] = ;      cMode := GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;      if (SameText(cMode, 'cmNone')) or ((override_mode=2) and (i>0)) then
      [*] = ;      begin
      [*] = ;         if gGame.arrPlayerControl[i] = 0 then
      [*] = ;            cMode := 'cmPC'
      [*] = ;         else
      [*] = ;            cMode := 'cmPlayer';
      [*] = ;
      [*] = ;         SetPlayerControlModeByHandle(plHandle, cMode);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if SameText(cMode, 'cmPlayer') and _plr_IsInGame(plHandle) then
      [*] = ;         SetPlayerBoolValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_bTurnFinished,false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;   begin
      [*] = ;      if gIntRegister_BattleAttackPlayer <> 0 then
      [*] = ;      begin
      [*] = ;         plHandle := GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;         cMode := GetPlayerControlModeByHandle(gIntRegister_BattleAttackPlayer);
      [*] = ;         SetPlayerControlModeByHandle(plHandle, cMode);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gIntRegister_BattleDefendPlayer <> 0 then
      [*] = ;      begin
      [*] = ;         plHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;         cMode := GetPlayerControlModeByHandle(gIntRegister_BattleDefendPlayer);
      [*] = ;         SetPlayerControlModeByHandle(plHandle, cMode);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var plInd : Integer = -1;
      [*] = ;
      [*] = ;   if override_mode < 2 then
      [*] = ;   begin
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         if gLanShardGame.arrLanPlayers[i].lanID = LanMyInfoID() then
      [*] = ;         begin
      [*] = ;            plInd := i;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      plInd := 0;
      [*] = ;
      [*] = ;   if plInd < 0 then
      [*] = ;   begin
      [*] = ;      if GetLanMode() >= 2 then
      [*] = ;         plInd := 0
      [*] = ;      else
      [*] = ;         plInd := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // setup master ID
      [*] = ;   var isMaster : Boolean = false;
      [*] = ;   if override_mode < 2 then
      [*] = ;   begin
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         if gLanShardGame.arrLanPlayers[i].lanID = gLanShardGame.masterID then
      [*] = ;         begin
      [*] = ;            isMaster := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      isMaster := true;
      [*] = ;
      [*] = ;   if not isMaster then
      [*] = ;   begin
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         plHandle := GetPlayerHandleByIndex(i);
      [*] = ;         cMode := GetPlayerControlModeByHandle(plHandle);
      [*] = ;         if _plr_IsInGame(plHandle) and SameText(cMode, 'cmPlayer') then
      [*] = ;         begin
      [*] = ;            gLanShardGame.masterID := gLanShardGame.arrLanPlayers[i].lanID;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   gIntRegister_MapMyPlayerIndex := plInd;
      [*] = ;
      [*] = ;   if GetPlayerHandleInterfaceIO() = 0 then
      [*] = ;   begin
      [*] = ;      case gIntRegister_CurGameMode of
      [*] = ;         gc_GameModeStrategy : begin
      [*] = ;            _gv_SetIOHandle(GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex),_log_name);
      [*] = ;         end;
      [*] = ;         gc_GameModeTactics : begin
      [*] = ;            plHandle := 0;
      [*] = ;
      [*] = ;            if GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer) = gIntRegister_MapMyPlayerIndex then
      [*] = ;               plHandle := GetPlayerHandleByName(gc_battle_attackPlayerName)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer) = gIntRegister_MapMyPlayerIndex then
      [*] = ;                  plHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;            end;
      [*] = ;
      [*] = ;            _gv_SetIOHandle(plHandle,_log_name);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not isAstral) then
      [*] = ;begin
      [*] = ;   if versionChanged then
      [*] = ;   begin
      [*] = ;      var battleDecalPlayer : Integer = GetPlayerHandleByName('battle.decal');
      [*] = ;      if battleDecalPlayer <> 0 then
      [*] = ;      begin
      [*] = ;         ClearPlayerGameObjectsByHandle(battleDecalPlayer);
	   [*] = ;         DeletePlayerByHandle(battleDecalPlayer);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var pProvinces : Integer = _map_GetStratHexCells();
      [*] = ;   var pInitHexCells : Integer = _map_GetHexCells();
      [*] = ;   var mapSizeX : Integer = gGame.map.x;
      [*] = ;   var mapSizeY : Integer = gGame.map.y;
      [*] = ;
      [*] = ;   if versionChanged then
      [*] = ;   for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'X', i div mapSizeY); //for some reason on shard map, Y is horizontal while X is vertical from bird-perspective, unlike in battles. This treats them same as in battles though.
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'Y', i mod mapSizeX);
      [*] = ;      
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;
      [*] = ;      FixUnitsParser(ParserSelectByHandleByKey(pProvince,'Guard'),'Guard',dummyUID);
      [*] = ;      FixUnitsParser(ParserSelectByHandleByKey(pProvince,'Defender'),'Defender',dummyUID);
      [*] = ;      FixUnitsParser(ParserSelectByHandleByKey(pProvince,'Garrison'),'Garrison',dummyUID);
      [*] = ;      FixUnitsParser(ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'EncounterGuard'), 'Guard'),'EncounterGuard',dummyUID);
      [*] = ;      FixUnitsParser(ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Rebel'), 'Guard'),'Rebel',dummyUID);
      [*] = ;      // fixing redunant encounters in provinces
      [*] = ;      if (ParserGetIntValueByKeyByHandle(pProvince, 'EventWin') <> 0) then _Log_Map('Win/lose events exists for province '+IntToStr(dummyUID)+': '+IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'EventWin')));
      [*] = ;      if (gIntRegister_CurrentEncounterID = 0) and (gIntRegister_CurrentEventID = 0) then
      [*] = ;      begin
      [*] = ;        ParserSetIntValueByKeyByHandle(pProvince, 'EventWin', 0);
      [*] = ;        ParserSetIntValueByKeyByHandle(pProvince, 'EventDraw', 0);
      [*] = ;        ParserSetIntValueByKeyByHandle(pProvince, 'EventLose', 0);
      [*] = ;      end;
      [*] = ;      //
      [*] = ;
      [*] = ;      // add shop modifiers
      [*] = ;      var pProvShop : Integer = ParserSelectByHandleByKey(pProvince, 'Shop');
      [*] = ;      if pProvShop <> 0 then
      [*] = ;      begin
      [*] = ;         var pPriceModifiers : Integer = ParserSelectByHandleByKey(pProvShop, 'PriceModifiers');
      [*] = ;         if pPriceModifiers = 0 then
      [*] = ;         begin
      [*] = ;            pPriceModifiers :=  ParserAddChildByIndex(pProvShop, 'PriceModifiers');
      [*] = ;
      [*] = ;            for j := 0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               var pPriceModifier : Integer = ParserAddChildByIndex(pPriceModifiers, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pPriceModifier, 'PlayerIndex', j);
      [*] = ;               ParserSetIntValueByKeyByHandle(pPriceModifier, 'PriceModifier', 100);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // add restore flag for sites
      [*] = ;      var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;      for j := ParserGetCountByHandle(pProvSites)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;         var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;         if pSiteGuard <> 0 then
      [*] = ;         begin
      [*] = ;            FixUnitsParser(pSiteGuard,'SiteGuard',dummyUID);
      [*] = ;            _pars_CheckBoolValue(pSiteGuard, 'NeedRestore', true);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var activeUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ActiveHUDHeroUID');
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(activeUID);
      [*] = ;      var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;
      [*] = ;      if GetPlayerRaceTagByHandle(plHandle) <> gc_map_PlayerRaceTag then
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'ActiveHUDHeroUID', 0)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         if curUID <> dummyUID then
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'ActiveHUDHeroUID', 0)
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;      var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;      var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;      var pProvRebel : Integer = ParserSelectByHandleByKey(pProvince, 'Rebel');
      [*] = ;
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;      var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;      var provLastPlayer : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;      var provType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceType');
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(provPlHandle);
      [*] = ;
      [*] = ;      var pProvHeroes : Integer = ParserSelectByHandleByKey(pProvince, 'MoveHeroes');
      [*] = ;      if pProvHeroes = 0 then
      [*] = ;         pProvHeroes := ParserAddChildByIndex(pProvince, 'MoveHeroes');
      [*] = ;
      [*] = ;      _pars_CheckIntValue(pProvince, 'UpdatePlayer', -1);
      [*] = ;      ParserSetValueByKeyByHandle(pProvince, 'UpdateLevel', '');
      [*] = ;      _pars_CheckIntValue(pProvince, 'UpdateFlags', 0);
      [*] = ;
      [*] = ;      var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;
      [*] = ;      // refresh player's province flags
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;
      [*] = ;      if dummyUID <> 0 then
      [*] = ;      begin
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         if (provPlHandle <> 0) then
      [*] = ;         begin
      [*] = ;            if provLastPlayer = provPlIndex then
      [*] = ;            begin
      [*] = ;               IntRegister0 := provPlHandle;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'SetupPlayerFlag');
      [*] = ;            end;
      [*] = ;
      [*] = ;            // change too strong defenders
      [*] = ;            if (gGame.gameType = gc_GameTypeCampaign) and SameText(cMode, 'cmPC') then
      [*] = ;            begin
      [*] = ;               var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;               if defID > 0 then
      [*] = ;               begin
      [*] = ;                  var pDefender : Integer = ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, defID);
      [*] = ;                  var defPower : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Power');
      [*] = ;
      [*] = ;                  if defPower >= 4 + gCampaign.currentTurn div 10 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := 1;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'PlaceDefender');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if not gTutorial.map then
      [*] = ;         begin
      [*] = ;            var lastPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;            if SameText(lastPlayer, '') or SameText(lastPlayer, '-1') then
      [*] = ;            begin
      [*] = ;               if provPlName = '' then
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvince, 'LastPlayer', -1)
      [*] = ;               else
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvince, 'LastPlayer', provPlIndex);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // setup province guard encounters
      [*] = ;         var exist : Boolean = ParserIsValueExistsByKeyByHandle(pProvGuard, 'Encounter');
      [*] = ;         if (provPlName = '') and (not exist) then
      [*] = ;         begin
      [*] = ;            var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provinceTypes.handle, provType);
      [*] = ;            var pGuardTypes : Integer = ParserSelectByHandleByKey(pProvinceType, 'GuardTypes');
      [*] = ;            if ParserGetCountByHandle(pGuardTypes) > 0 then
      [*] = ;            begin
      [*] = ;               var pGuardType : Integer = ParserSelectByHandleByIndex(pGuardTypes, 0);
      [*] = ;               var enc : Integer = ParserGetIntValueByKeyByHandle(pGuardType, 'Enconter');
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvGuard, 'Encounter', enc);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetStable');
      [*] = ;         var stable : Integer = IntRegister0;
      [*] = ;         ParserSetIntValueByKeyByHandle(dummyHandle, 'Stable', stable);
      [*] = ;
      [*] = ;         // check incorrect rebel guards
      [*] = ;         var pRebelGuard : Integer = ParserSelectByHandleByKey(pProvRebel, 'Guard');
      [*] = ;         var pRebelUnits : Integer = ParserSelectByHandleByKey(pRebelGuard, 'Units');
      [*] = ;
      [*] = ;         if ParserGetCountByHandle(pRebelUnits) > 0 then
      [*] = ;         begin
      [*] = ;            var pGarrUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;            if ParserGetCountByHandle(pGarrUnits) = 0 then
      [*] = ;               ParserClearByHandle(pRebelGuard);
      [*] = ;         end;
      [*] = ;
      [*] = ;         // check empty guard dialogs
      [*] = ;         var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         if (provPlName = '') and (ParserGetCountByHandle(pGuardUnits) > 0) then
      [*] = ;         begin
      [*] = ;            var guardDialog : Integer = ParserGetIntValueByKeyByHandle(pProvGuard, 'Dialog');
      [*] = ;            if guardDialog = 0 then
      [*] = ;            begin
      [*] = ;               var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provinceTypes.handle, provType);
      [*] = ;               var pGuardTypes : Integer = ParserSelectByHandleByKey(pProvinceType, 'GuardTypes');
      [*] = ;               if ParserGetCountByHandle(pGuardTypes) > 0 then
      [*] = ;               begin
      [*] = ;                  var pGuardType0 : Integer = ParserSelectByHandleByIndex(pGuardTypes, 0);
      [*] = ;                  var dialog : Integer = ParserGetIntValueByKeyByHandle(pGuardType0, 'Dialog');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvGuard, 'Dialog', dialog);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if provPlName <> '' then
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'UpdatePlayer', provPlIndex);
      [*] = ;      
      [*] = ;         // destroy stuck ritual FX
      [*] = ;         for j := 1 to gPrototypeData.rituals.number-1 do
      [*] = ;         begin
      [*] = ;            if (_fx_FindFXHandleByID(dummyHandle, true, 1000+j)<>0) then
      [*] = ;            begin
      [*] = ;               Log('ritual FX exists, ritual ID: '+IntToStr(j));
      [*] = ;               var bDestroy : Boolean = true;
      [*] = ;               var pProvRituals : Integer = ParserSelectByHandleByKey(pProvince, 'Rituals');
      [*] = ;               for k := ParserGetCountByHandle(pProvRituals)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pProvRitual : Integer = ParserSelectByHandleByIndex(pProvRituals, k);
      [*] = ;
      [*] = ;                  if (ParserGetIntValueByKeyByHandle(pProvRitual, 'RitualID') = j) and (ParserGetIntValueByKeyByHandle(pProvRitual, 'Time') > 0) then
      [*] = ;                  begin
      [*] = ;                     bDestroy := false;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            
      [*] = ;               if bDestroy then
      [*] = ;               begin
      [*] = ;                  Log('destroy ritual FX');
      [*] = ;                 _fx_GetOrCreateFXByID(dummyHandle, 'fxritual_'+IntToStr(j)+'_destroy', 0, 0, 0, 0, 0, 1000+j);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;   for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      if GetPlayerHandleByName(provPlName) = GetPlayerHandleInterfaceIO then
      [*] = ;         ParserClearByHandle(ParserSelectByHandleByKey(pProvince, 'CastedRituals')); // no casted rituals are supposed to be stored on your own provinces during your manual turn.
      [*] = ;   end;
      [*] = ;   
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      var goldInc, gemInc : Integer = 0;
      [*] = ;      for j := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, j);
      [*] = ;         var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;         if SameText(plName, GetPlayerNameByIndex(i)) then
      [*] = ;         begin
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'IsUnderSiege');
      [*] = ;            var siegePlHandle : Integer = IntRegister0;
      [*] = ;            var underSiege : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            if not underSiege then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 3;
      [*] = ;               IntRegister1 := -1;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;               goldInc := goldInc + IntRegister0;
      [*] = ;               gemInc := gemInc + IntRegister1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   // update heroes
      [*] = ;   if versionChanged then
      [*] = ;   begin
      [*] = ;      var goHandle, heroParser, heroInventory, heroLevel, class1, class2, heroClass, bonusType, bonusValue, leader, magic, health, bonusLife, pHealthLevel, oldHealth, oldBonusLife, lifeChange, stamChange, moralChange : Integer;
      [*] = ;      var pUnitLevels : Integer = gPrototypeData.unitLevels.handle;
      [*] = ;      var pHealthLevels : Integer = ParserSelectByHandleByKey(pUnitLevels, 'Health');
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         
      [*] = ;         var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(plHandle), 'Treasury');
      [*] = ;         for j := 0 to ParserGetCountByHandle(pTreasury)-1 do
      [*] = ;            FixItemParser(ParserSelectByHandleByIndex(pTreasury, j));
      [*] = ;         
      [*] = ;         for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            goHandle := GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;            heroLevel := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;            leader := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLeader);
      [*] = ;            magic := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iMagic);
      [*] = ;            health := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iHealth);
      [*] = ;            bonusLife := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLife);
      [*] = ;            
      [*] = ;            if (bonusLife < heroLevel - 20) or ((heroLevel > 10) and (leader + magic + health < heroLevel) and (heroLevel <= 20)) then // incorrect stats, reset to a fixed default
      [*] = ;            begin
      [*] = ;               class1 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;               class2 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd2);
      [*] = ;               heroClass := class1; 
      [*] = ;               if class2 > 0 then
      [*] = ;               begin
      [*] = ;                  heroClass := class1 * 4 + class2;
      [*] = ;                  if heroLevel >= 20 then
      [*] = ;                     heroClass := heroClass + 16;
      [*] = ;               end;
      [*] = ;            
      [*] = ;               // update hero params
      [*] = ;               leader := 0;
      [*] = ;               magic := 0;
      [*] = ;               health := 0;
      [*] = ;               bonusLife := 0;
      [*] = ;               lifeChange := 0;
      [*] = ;               stamChange := 0;
      [*] = ;               moralChange := 0;
      [*] = ;            
      [*] = ;               oldHealth := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iHealth);
      [*] = ;               oldBonusLife := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLife);
      [*] = ;            
      [*] = ;               for k := 0 to heroLevel do
      [*] = ;               begin
      [*] = ;                  bonusValue := 0;
      [*] = ;                  bonusType := 0;
      [*] = ;                  if k < 10 then
      [*] = ;                     _unit_GetFixedHeroBonus(class1, k, bonusType, bonusValue)
      [*] = ;                  else
      [*] = ;                     _unit_GetFixedHeroBonus(heroClass, k, bonusType, bonusValue);
      [*] = ;               
      [*] = ;                  if bonusValue <> 0 then
      [*] = ;                  case bonusType of
      [*] = ;                     0 : leader := leader + bonusValue;
      [*] = ;                     1 : magic := magic + bonusValue;
      [*] = ;                     2 : health := health + bonusValue;
      [*] = ;                     3 : bonusLife := bonusLife + bonusValue;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLeader, leader);
      [*] = ;               SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iMagic, magic);
      [*] = ;               SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iHealth, health);
      [*] = ;               SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLife, bonusLife);
      [*] = ;            
      [*] = ;               if oldBonusLife <> bonusLife then
      [*] = ;                  lifeChange := bonusLife - oldBonusLife;
      [*] = ;            
      [*] = ;               if health < oldHealth then
      [*] = ;               for k := health+1 to oldHealth do
      [*] = ;               begin
      [*] = ;                  pHealthLevel := ParserSelectByHandleByIndex(pHealthLevels, k-1);
      [*] = ;                  lifeChange := lifeChange - ParserGetIntValueByKeyByHandle(pHealthLevel, 'Life');
      [*] = ;                  stamChange := stamChange - ParserGetIntValueByKeyByHandle(pHealthLevel, 'Stamina');
      [*] = ;                  moralChange := moralChange - ParserGetIntValueByKeyByHandle(pHealthLevel, 'Moral');
      [*] = ;               end;
      [*] = ;               if oldHealth < health then
      [*] = ;               for k := oldHealth+1 to health do
      [*] = ;               begin
      [*] = ;                  pHealthLevel := ParserSelectByHandleByIndex(pHealthLevels, k-1);
      [*] = ;                  lifeChange := lifeChange + ParserGetIntValueByKeyByHandle(pHealthLevel, 'Life');
      [*] = ;                  stamChange := stamChange + ParserGetIntValueByKeyByHandle(pHealthLevel, 'Stamina');
      [*] = ;                  moralChange := moralChange + ParserGetIntValueByKeyByHandle(pHealthLevel, 'Moral');
      [*] = ;               end;
      [*] = ;               _unit_ModifyHeroAttributes(goHandle, lifeChange, stamChange, moralChange);
      [*] = ;            end;
      [*] = ;         
      [*] = ;            var heroAIPower : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;            if (heroAIPower > 25) then
      [*] = ;            begin
      [*] = ;               heroAIPower := heroLevel div 3;
      [*] = ;               SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAIPower, heroAIPower);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            heroParser := ParserSelectGameObject(goHandle);
      [*] = ;            if ParserGetCountByHandle(heroParser) > 0 then
      [*] = ;            begin
      [*] = ;               FixUnitsParser(heroParser,'HeroArmy',i*256+j);
      [*] = ;            
      [*] = ;               heroInventory := ParserSelectByHandleByKey(heroParser, 'Doll');
      [*] = ;               for k := 0 to gc_HeroInventoryCount-1 do
      [*] = ;                  FixItemParser(ParserSelectByHandleByIndex(heroInventory, k));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // deal value type used to be boolean so when loading such save file, it will be -1 as integer. This will be the trigger.
      [*] = ;   var bResetNewValues : Boolean = (gArrDiplomacy[0][0].message.deal = -1);  // player 0 to player 0 deal should never be anything else than 0.
      [*] = ;
      [*] = ;   for i := 0 to gc_MaxMapPlayers-1 do
      [*] = ;   begin
      [*] = ;      var profile : Integer = GetPlayerIntValueIndByHandle(GetPlayerHandleByIndex(i), gc_map_PLStack_MapUnit_iProfile);
      [*] = ;      
      [*] = ;      for j := 0 to gc_MaxMapPlayers-1 do
      [*] = ;      begin
      [*] = ;         if (gArrDiplomacy[i][j].treaty > 0) and (gArrDiplomacy[i][j].meet < 0) then
      [*] = ;            gArrDiplomacy[i][j].meet := 0;
      [*] = ;      
      [*] = ;         if (gArrDiplomacy[i][j].treaty = gc_TreatyWar) then
      [*] = ;         begin
      [*] = ;            gArrDiplomacy[j][i].treaty := gc_TreatyWar;
      [*] = ;         
      [*] = ;            for k := 0 to gc_MaxMapPlayers-1 do
      [*] = ;            begin
      [*] = ;               if (gArrDiplomacy[i][k].treaty = gc_TreatyUnion) then
      [*] = ;               begin
      [*] = ;                  gArrDiplomacy[j][k].treaty := gc_TreatyWar;
      [*] = ;                  gArrDiplomacy[k][j].treaty := gc_TreatyWar;
      [*] = ;               end;
      [*] = ;               if (gArrDiplomacy[j][k].treaty = gc_TreatyUnion) then
      [*] = ;               begin
      [*] = ;                  gArrDiplomacy[i][k].treaty := gc_TreatyWar;
      [*] = ;                  gArrDiplomacy[k][i].treaty := gc_TreatyWar;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      
      [*] = ;         if bResetNewValues then
      [*] = ;         begin
      [*] = ;            gArrDiplomacy[i][j].message.deal := 0;
      [*] = ;         
      [*] = ;            if gGame.diplomacy and (gArrDiplomacy[i][j].treaty > 0) and (profile > 0) and (i <> j) then
      [*] = ;            begin
      [*] = ;               var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;               _diplomacy_ShuffleRandom(i, j, ParserGetIntValueByKeyByHandle(pProfile, 'Random'));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      
      [*] = ;         if (gArrDiplomacy[i][j].message.mType > 0) and (gArrDiplomacy[i][j].message.mType <> gArrDiplomacy[i][j].queryWindowMessage.mType) then
      [*] = ;            _diplomacy_AssignMessage(gArrDiplomacy[i][j].queryWindowMessage, gArrDiplomacy[i][j].message);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeTactics) and versionChanged then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGOUpgrades : Integer = ParserSelectByHandleByKey(pGOParser 'Upgrades');
      [*] = ;      var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;      var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;      FixUpgradesParser(pGOUpgrades, unitID, level);
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;   end;
      [*] = ;
      [*] = ;   plHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGOUpgrades : Integer = ParserSelectByHandleByKey(pGOParser 'Upgrades');
      [*] = ;      var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;      var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;      FixUpgradesParser(pGOUpgrades, unitID, level);
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pCurParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle());
      [*] = ;var pBattleLog : Integer = ParserSelectByHandleByKey(pCurParser, 'BattleLog');
      [*] = ;if pBattleLog = 0 then
      [*] = ;   pBattleLog := ParserAddChildByIndex(pCurParser, 'BattleLog');
      [*] = ;
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(pCurParser, 'Queries');
      [*] = ;if pQueries = 0 then pQueries := ParserAddChildByIndex(pCurParser, 'Queries');
      [*] = ;
      [*] = ;
      [*] = ;// nulling registers
      [*] = ;gIntRegister_EndHexCell := 0;
      [*] = ;gIntRegister_EndHexUID := 0;
      [*] = ;//gIntRegister_InfoUnitUID := 0;
      [*] = ;gIntRegister_StartTrackNode := 0;
      [*] = ;gIntRegister_EndTrackNode := 0;
      [*] = ;gIntRegister_BeforeEndTrackNode := 0;
      [*] = ;
      [*] = ;gIntRegister_MapSelectedHex := 0;
      [*] = ;gIntRegister_MapUnderCursorHex := 0;
      [*] = ;gIntRegister_DeadHeroHandle := 0;
      [*] = ;gIntRegister_MapActiveHeroHandle := 0;
      [*] = ;gIntRegister_MoveMapHeroHandle := 0;
      [*] = ;gIntRegister_GUINoSpaceForItemHeroUID := 0;
      [*] = ;gBoolRegister_Loading := false;
	   [*] = ;gBoolRegister_LanMapTurnPassed := false;
      [*] = ;gBoolRegister_HaltLanProgress := False;
      [*] = ;
      [*] = ;// pfx smart tree registers
      [*] = ;gIntRegister_fxTree_RootHandle := 0;
      [*] = ;gStringRegister_fxTree_NodeName := '';
      [*] = ;gIntRegister_fxTree_NodeHandle := 0;
      [*] = ;gIntRegister_fxTree_NodeTarget := 0;
      [*] = ;gFloatRegister_fxTree_CoordTargetX := 0;
      [*] = ;gFloatRegister_fxTree_CoordTargetY := 0;
      [*] = ;gFloatRegister_fxTree_CoordTargetZ := 0;
      [*] = ;gFloatRegister_fxTree_SleepTime := 0;
      [*] = ;gBoolRegister_fxTree_Loaded := false;
      [*] = ;
      [*] = ;// debug registers
      [*] = ;gFloatRegister_gDbgFloat0PrevValue := 0;
      [*] = ;gFloatRegister_gDbgFloat1PrevValue := 0;
      [*] = ;gFloatRegister_gDbgFloat2PrevValue := 0;
      [*] = ;gFloatRegister_gDbgFloat3PrevValue := 0;
      [*] = ;gIntRegister_DbgMapSelectedHex := 0;
      [*] = ;gIntRegister_dbgX := 0;
      [*] = ;gIntRegister_dbgY := 0;
      [*] = ;gIntRegister_dbgZ := 0;
      [*] = ;
      [*] = ;if not isAstral then
      [*] = ;begin
      [*] = ;   var pProvinces : Integer = _map_GetStratHexCells();
      [*] = ;
      [*] = ;   //IntRegister0 := 3;
      [*] = ;   //ExecuteState('AstralBorders');
      [*] = ;
      [*] = ;   if not gTutorial.map then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := true;
      [*] = ;      MapExecuteState('SetButtonsEnabled');
      [*] = ;   end
      [*] = ;   else
      [*] = ;      gGame.diplomacy := false;
      [*] = ;      
      [*] = ;   // check allowed heroes
      [*] = ;   var flags : Integer = gGame.allowedheroes;
      [*] = ;   var oldVersionNumber : String;
      [*] = ;   _misc_ExtractModVersionFromExtendedVersion(oldVersion, oldVersionNumber);
      [*] = ;   if StrExists(oldVersion, 'Fixers_Vanilla_Patch') and (not _misc_IsUpdatedVersion('0.9.365', oldVersionNumber)) then // in earlier versions, allowedheroes bitflag 0 was nothing allowed. Later, it means everything is allowed.
      [*] = ;   begin
      [*] = ;      gGame.allowedheroes := (flags xor $ffff);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if (flags >= $ffff) or ((flags > 0) and (gGame.gameType = gc_GameTypeCampaign)) then // for some reason everything is banned, or something is banned in campaign.
      [*] = ;   begin
      [*] = ;      gGame.allowedheroes := 0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if ((flags and $f) = $f) or ((flags and $f0) = $f0) or ((flags and $f00) = $f00) or ((flags and $f000) = $f000) then // check completely banned primary classes
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         var class1 : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;         // if a banned primary class exists in the game, something fishy is going on. Allow the class in full.
      [*] = ;         case class1 of
      [*] = ;            1 : if ((gGame.allowedheroes and $f) = $f) then gGame.allowedheroes := gGame.allowedheroes and $fff0;
      [*] = ;            2 : if ((gGame.allowedheroes and $f0) = $f0) then gGame.allowedheroes := gGame.allowedheroes and $ff0f;
      [*] = ;            3 : if ((gGame.allowedheroes and $f00) = $f00) then gGame.allowedheroes := gGame.allowedheroes and $f0ff;
      [*] = ;            4 : if ((gGame.allowedheroes and $f000) = $f000) then gGame.allowedheroes := gGame.allowedheroes and $0fff;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if (oldVersion = '') or (StrExists(oldVersion, 'Fixers_Vanilla_Patch') and (not _misc_IsUpdatedVersion('0.9.4145', oldVersionNumber))) then
      [*] = ;   begin
      [*] = ;      ExecuteState('map.InitGrid');
      [*] = ;   end;
      [*] = ;         
      [*] = ;   if gTutorial.init and (gTutorial.move = 0) then
      [*] = ;      gTutorial.init := false;
      [*] = ;
      [*] = ;   if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;   begin
      [*] = ;      gBoolRegister_InBattle := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var ph : Integer;
      [*] = ;
      [*] = ;      // reset battle hex grid to make sure to get rid of polymorph bug
      [*] = ;      ExecuteState('bat.InitGrid');
      [*] = ;      // clear all temp player objects if any
      [*] = ;      for i := 0 to 3 do
      [*] = ;      begin
      [*] = ;         case i of
      [*] = ;            0 : ph := GetPlayerHandleByName(gc_battle_virtAttackPlayerName);
      [*] = ;            1 : ph := GetPlayerHandleByName(gc_battle_virtDefendPlayerName);
      [*] = ;            2 : ph := GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;            3 : ph := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;         end;
      [*] = ;         if ph <> 0 then
      [*] = ;         begin
      [*] = ;            ClearPlayerGameObjectsByHandle(ph);
      [*] = ;            SetPlayerControlModeByHandle(ph, 'cmNone');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      SetActiveTrackNodeList(0);
      [*] = ;   end;
      [*] = ;
      [*] = ;
      [*] = ;   if (not gBoolRegister_DiplomacyInited) then
      [*] = ;   begin
      [*] = ;      // set diplomacy war
      [*] = ;      _diplomacy_InitAllDiplomacy();
      [*] = ;
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;            if i <> j then
      [*] = ;               gArrDiplomacy[i][j].treaty := 1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;   
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, 0);
      [*] = ;   var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;   if pProvFog = 0 then
      [*] = ;   begin
      [*] = ;      for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;         var pProvFog : Integer = ParserAddChildByIndex(pProvince, 'Fog'); // province fog type: 0 - no fog, 1 - half fog, 2 - full fog
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvFog, IntToStr(j), 2);
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'CalcFogMap');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var no,provPlHandle,plParser : Integer;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      plParser := ParserSelectPlayer(GetPlayerHandleByIndex(i));
      [*] = ;      if not ParserIsValueExistsByKeyByHandle(plParser, 'CapturedProvincesNo') then
      [*] = ;      begin
      [*] = ;         no := 0;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;         begin
      [*] = ;            p := ParserSelectByHandleByIndex(pProvinces, j);
      [*] = ;            provPlHandle := GetPlayerHandleByName(ParserGetValueByKeyByHandle(p, 'Player'));
      [*] = ;            if (provPlHandle <> 0) and (GetPlayerIndexByHandle(provPlHandle) = i) then
      [*] = ;               no := no + 1;
      [*] = ;         end;
      [*] = ;         ParserSetIntValueByKeyByHandle(plParser, 'CapturedProvincesNo', no-1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if gTutorial.map then
      [*] = ;   begin
      [*] = ;      if (not cBuildEnabled) and (gTutorial.build = 0) then
      [*] = ;         gBoolRegister_BtnCastleBuildEnabled := false;
      [*] = ;
      [*] = ;      if gTutorial.hire >= 8 then
      [*] = ;         gTutorial.buyUnit := true;
      [*] = ;
      [*] = ;      if gTutorial.library >= 7 then
      [*] = ;         gTutorial.learnSpell := true;
      [*] = ;
      [*] = ;      if gTutorial.trade >= 9 then
      [*] = ;         gTutorial.buyItem := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Fix 1 tiles at left side, after new tiles added to alpha_null_2
      [*] = ;   if (GetTileIndex(0, 0)=48) then
      [*] = ;   begin
      [*] = ;      for i:=0 to (GetMapHeight) do
      [*] = ;         PaintTerrain(-(GetMapWidth div 2), i, MapGetTileIndexByTileBlock('alpha_null_2'), 0, 0, false, 6, 0, 1, true, true);
      [*] = ;   end;
      [*] = ;   LoadPatterns(true, true);
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   GUIExecuteState('vvk.map.UpdateProvinceHUD');
      [*] = ;
      [*] = ;   gIntRegister_MapBattleProvince := 0;
      [*] = ;   gIntRegister_BattleAttackArmy := 0;
      [*] = ;   gIntRegister_BattleAttackHeroHandle := 0;
      [*] = ;   gIntRegister_BattleAttackPlayer := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var plShards : Integer = GetPlayerHandleByName(gc_astral_shardsPlayerName);
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(plShards)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var shHandle : Integer = GetGameObjectHandleByIndex(i, plShards);
      [*] = ;      var uid : Integer = GetGameObjectUniqueIdByHandle(shHandle);
      [*] = ;      var shInd : Integer = _shard_GetShardByUID(uid);
      [*] = ;      if shInd < 0 then
      [*] = ;         GameObjectDestroyByHandle(shHandle)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var isMain : Boolean = _shard_IsMain(gShards[shInd]);
      [*] = ;         if (gShards[shInd].ipPlayer > 0) and (not isMain) then
      [*] = ;            GameObjectDestroyByHandle(shHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;begin
      [*] = ;   // ensure default data
      [*] = ;   gGame.allowedheroes := 0;
      [*] = ;   gGame.quickgame := false;
      [*] = ;   gGame.sandbox := false;
      [*] = ;   
      [*] = ;   // add camp player buildings
      [*] = ;   for i := 1 to gc_MaxCampPlayer-1 do
      [*] = ;   begin
      [*] = ;      if (not gCampaign.arrCampPlayers[i].buildAdded) and gCampaign.arrCampPlayers[i].inGame and gCampaign.arrCampPlayers[i].firstMeet then
      [*] = ;      begin
      [*] = ;         var pPlayer : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, i);
      [*] = ;         var y : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Y');
      [*] = ;
      [*] = ;         var buildCount : Integer = 7 * (y - gCampaign.arrCampPlayers[0].sizeBonus - 1);
      [*] = ;         for j := 0 to buildCount-1 do
      [*] = ;            _camp_player_AddBuild(gCampaign.arrCampPlayers[i]);
      [*] = ;
      [*] = ;         gCampaign.arrCampPlayers[i].buildAdded := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var objectFlags : Integer = _pars_GetIntValueByKeyByHandleDef(pMachineParser, 'ObjectFlags', $ff);
      [*] = ;var shardScenery : Integer = _pars_GetIntValueByKeyByHandleDef(pMachineParser, 'ShardScenery', $ff);
      [*] = ;var townScenery : Integer = _pars_GetIntValueByKeyByHandleDef(pMachineParser, 'TownScenery', $ff);
      [*] = ;var provinceScenery : Integer = _pars_GetIntValueByKeyByHandleDef(pMachineParser, 'ProvinceScenery', $ff);
      [*] = ;var battleScenery : Integer = _pars_GetIntValueByKeyByHandleDef(pMachineParser, 'BattleScenery', $ff);
      [*] = ;IntRegister0 := _obj_GetCheckSceneryFlags(objectFlags, shardScenery, townScenery, provinceScenery, battleScenery);
      [*] = ;GUIExecuteState('CheckScenery');
      [*] = ;
      [*] = ;gBoolRegister_GUIProgressOnceOnGUIDoCreate := True;
      [*] = ;//if gProfile.simplegraphics then
      [*] = ;//   _actor_CheckSimplifiedGraphics();
      [*] = ;
      [*] = ;// update music lists in case new songs are added since previous version, also create new threads if not yet exist. Creating new threads in DoInitSound would cause Access Violations.
      [*] = ;if versionChanged then
      [*] = ;begin
      [*] = ;         //AmbientThreadListImportFile('.\data\sounds\ambient\old.cfg');
      [*] = ;   {if isAstral then
      [*] = ;   begin
      [*] = ;      var threadHandle : Integer = SndGetOrCreateAmbientThread('astral');
      [*] = ;      if threadHandle <> 0 then
      [*] = ;         AmbientThreadListImportFile('.\data\sounds\ambient\astral.cfg');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics) then
      [*] = ;   begin
      [*] = ;      var threadHandle : Integer = SndGetOrCreateAmbientThread('shard');
      [*] = ;      if threadHandle <> 0 then
      [*] = ;         AmbientThreadListImportFile('.\data\sounds\ambient\shard.cfg');}
      [*] = ;   
      [*] = ;      {threadHandle := SndGetOrCreateAmbientThread('battle');
      [*] = ;      if threadHandle <> 0 then
      [*] = ;         AmbientThreadListImportFile('.\data\sounds\ambient\battle.cfg');}
      [*] = ;   //end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;{for i := 1 to 1 do
      [*] = ;begin
      [*] = ;   var threadName : String;
      [*] = ;   case i of
      [*] = ;      gc_GameModeAstral : 
      [*] = ;      begin
      [*] = ;         threadName := 'astral';
      [*] = ;      end;
      [*] = ;      gc_GameModeStrategy : 
      [*] = ;      begin
      [*] = ;         threadName := 'shard';
      [*] = ;      end;
      [*] = ;      gc_GameModeTactics : 
      [*] = ;      begin
      [*] = ;         threadName := 'battle';
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var threadHandle : Integer = SndGetOrCreateAmbientThread(threadName);
      [*] = ;   if threadHandle <> 0 then
      [*] = ;      AmbientThreadListImportFile('.\data\sounds\ambient\'+threadName+'.cfg');
      [*] = ;end;}
      [*] = ;
      [*] = ;//_gui_RecalcSettingsLowest(gProfile.settingslowest);
      [*] = ;
      [*] = ;SetRandomExtKey64(gIntRegister_RandomExtKey0, gIntRegister_RandomExtKey1);
      [*] = ;SetMapGeneratorRandomKey(gIntRegister_MapGeneratorKey0, gIntRegister_MapGeneratorKey1);
      [*] = ;SetGlobalMapGeneratorRandomKey(gIntRegister_GlobalMapGeneratorKey0, gIntRegister_GlobalMapGeneratorKey1);
      [*] = ;
      [*] = ;var bRecyclerExists : Boolean = false;
      [*] = ;for i := GetCountOfPlayers-1 downto 0 do
      [*] = ;begin
      [*] = ;   var plName : String = GetPlayerNameByIndex(i);
      [*] = ;   Log(plName);
      [*] = ;   var playerHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   var raceTag : Integer = GetPlayerRaceTagByHandle(playerHandle);
      [*] = ;   var goCount : Integer = GetPlayerGameObjectsCountByHandle(playerHandle);
      [*] = ;   Log('   Racetag: '+IntToStr(raceTag));
      [*] = ;   Log('   Handle: '+IntToStr(playerHandle));
      [*] = ;   Log('   GO Count: '+IntToStr(goCount)); 
      [*] = ;   if SameText(plName, 'recycle') then
      [*] = ;   begin
      [*] = ;      for j := 0 to GetPlayerGameObjectsCountByHandle(playerHandle)-1 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, playerHandle);
      [*] = ;         Log('      '+IntToStr(goHandle)+' '+GetGameObjectBaseNameByHandle(goHandle));
      [*] = ;      end;
      [*] = ;      ClearPlayerGameObjectsByHandle(playerHandle);
      [*] = ;      if bRecyclerExists then
      [*] = ;         DeletePlayerByHandle(playerHandle);
      [*] = ;      
      [*] = ;      bRecyclerExists := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if SameText(plName, 'particles') then
      [*] = ;   begin
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(playerHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, playerHandle);
      [*] = ;         var baseName : String = GetGameObjectBaseNameByHandle(goHandle);
      [*] = ;         if SameText(baseName, 'creation') or SameText(baseName, 'bowloflife') or SameText(baseName, 'pentagramm') or SameText(baseName, 'shield') or SameText(baseName, 'shield_2') 
      [*] = ;         or SameText(baseName, 'spellboundbox') or SameText(baseName, 'sword') or SameText(baseName, 'waveplane') or SameText(baseName, 'waveplane_hypno') then
      [*] = ;         begin
      [*] = ;            Log('      '+IntToStr(goHandle)+' '+baseName+', non-recycleable, deleting...');
      [*] = ;            AddObjectToDestroyList(goHandle);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if SameText(plName, 'projectiles') or SameText(plName, 'PlTrack') or SameText(plName, 'PlTrackBattle') or SameText(plName, 'battle.remains') then
      [*] = ;      ClearPlayerGameObjectsByHandle(playerHandle);
      [*] = ;   Log('  ');
      [*] = ;end;
      [*] = ;
      [*] = ;var decalHandle : Integer;
      [*] = ;//var w, h, x, z, texOff0, texOff1, scale0, scale1, texScale0, texScale1, texAng, eps : Float;
      [*] = ;//var texRot, texScale, texOff, texOffRot : Boolean;
      [*] = ;//var libMat, decName : String;
      [*] = ;var decalCount : Integer = DecalManagerGetDecalCount;
      [*] = ;Log('DecalManager DecalCount: '+IntToStr(decalCount));
      [*] = ;//for i := 0 to decalCount-1 do
      [*] = ;//begin  
      [*] = ;   //decalHandle := DecalManagerGetDecalHandleByIndex(i);
      [*] = ;   //GetDecalDataByHandle(decalHandle, w, h, x, z, texOff0, texOff1, scale0, scale1, texScale0, texScale1, texAng, eps, texRot, texScale, texOff, texOffRot, libMat, decName);
      [*] = ;   //Log('  '+GetDecalMaterialNameByHandle(decalHandle));  
      [*] = ;//end;
      [*] = ;Log('  ');
      [*] = ;
      [*] = ;
      [*] = ;if _log then
      [*] = ;begin
      [*] = ;   var p,n,pc : Integer;
      [*] = ;   var fnm : String;
      [*] = ;
      [*] = ;   p := _misc_ParserGetOrCreateByKey('dumpglobals_tmp', True);
      [*] = ;   fnm := 'log\load_globals_'+IntToStr(LanMyInfoID())+'.dat';
      [*] = ;   StateMachineGlobalVariablesSaveToParser(p,'',false,true);
      [*] = ;   ParserSelectByHandle(p);
      [*] = ;   ParserSaveToFile(fnm);
      [*] = ;   _misc_ParserGetOrCreateByKey('dumpglobals_tmp', True);
      [*] = ;   fnm := 'log\load_mapparser_'+IntToStr(LanMyInfoID())+'.dat';
      [*] = ;   p := ParserSelectStateMachineByHandle(GetMapInitMachineHandle());
      [*] = ;   if p <> 0 then ParserSaveToFile(fnm);
      [*] = ;
      [*] = ;   p := _misc_ParserGetOrCreateByKey('dumpobjects_tmp', True);
      [*] = ;   n := 0;
      [*] = ;   pc := 0;
      [*] = ;   for i := 0 to GetCountOfPlayers()-1 do
      [*] = ;   begin
      [*] = ;      if pc = 0 then
      [*] = ;         pc := ParserAddChildByIndex(p, '*');;
      [*] = ;      if SaveObjectToFile(i,-1,pc) then
      [*] = ;      begin
      [*] = ;         pc := 0;
      [*] = ;         n := n + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   ParserSetIntValueByKeyByHandle(p, 'TotalObjects', n);
      [*] = ;   ParserSaveToFileByHandle(p,'log\load_objects_'+IntToStr(LanMyInfoID())+'.dat');
      [*] = ;   _misc_ParserGetOrCreateByKey('dumpobjects_tmp', True);
      [*] = ;end;
      [*] = ;
      [*] = ;TimeLog('OnLoadFull end');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

