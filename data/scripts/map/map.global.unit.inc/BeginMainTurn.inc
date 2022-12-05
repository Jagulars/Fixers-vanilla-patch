section.begin
   Name = BeginMainTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\BEGINMAINTURN';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetCurrentPlayerName();
      [*] = ;var myParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(myParser, 'Queries');
      [*] = ;
	  [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;procedure CancelTrade(plIndex : Integer);
      [*] = ;begin
      [*] = ;   if gArrDiplomacy[plIndex][myIndex].message.mType <> gc_MessageCancelTrade then
      [*] = ;   begin
      [*] = ;      _diplomacy_ClearTrade(gArrDiplomacy[myIndex][plIndex].trade);
      [*] = ;      _diplomacy_ClearTrade(gArrDiplomacy[plIndex][myIndex].trade);
      [*] = ;
      [*] = ;      var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplCancelTrade);
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', plIndex);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if (gIntRegister_MapTurnIteration = 10) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   if (gGame.currentTurn <= 1) or ((gGame.currentTurn <= 2) and SameText(GetPlayerControlModeByHandle(myPlHandle),'cmPC')) then // don't process turn changes on first turn
      [*] = ;   begin
      [*] = ;      // switch to next iteration state
      [*] = ;      gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;      gIntRegister_CurProvinceIndex := -1;
      [*] = ;
      [*] = ;      gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;
      [*] = ;      SwitchTo('Nothing');
      [*] = ;
      [*] = ;      _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   ExecuteState('GetCastleParser');
      [*] = ;   var pCastle : Integer = IntRegister0;
      [*] = ;   var cLastPlayer : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'LastPlayer');
      [*] = ;   var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;   var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;
      [*] = ;   var plGold : Integer =       GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer =        GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var plGoldInc : Integer =    GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;   var plGemInc : Integer =     GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;   var campGoldAdd : Integer =  GetIntValueByIndex(gc_map_PLStack_MapUnit_iCampGoldAdd);
      [*] = ;   var campGemAdd : Integer =   GetIntValueByIndex(gc_map_PLStack_MapUnit_iCampGemAdd);
      [*] = ;
      [*] = ;   var isAI : Boolean = SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC');
      [*] = ;
      [*] = ;   var goldInc : Integer = 0;
      [*] = ;   var gemInc : Integer = 0;
      [*] = ;   var goldSpent : Integer = 0;
      [*] = ;   var gemSpent : Integer = 0;
      [*] = ;   var perc : Integer = 0;
      [*] = ;
      [*] = ;   var plCanInnerBuild : Integer = 1;
      [*] = ;   var plCanOuterBuild : Integer = 1;
      [*] = ;   if gBoolRegister_CheatCanBuildInfinite and (myIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   begin
      [*] = ;      plCanInnerBuild := 1000;
      [*] = ;      plCanOuterBuild := 1000;
      [*] = ;   end;
      [*] = ;   var plCanHire : Integer = 1;
      [*] = ;   var plCanCast : Integer = 1;
      [*] = ;
      [*] = ;   var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   //Обработка событий
      [*] = ;
      [*] = ;   //Ритуальные события
      [*] = ;
      [*] = ;   //Дипломатическая переписка
      [*] = ;   //Проверка почты союзников (для игрока-человека)
      [*] = ;
      [*] = ;   //Первая встреча
      [*] = ;   //Получение ответа на сообщение
      [*] = ;   //Сообщение при невыполнимом предложении
      [*] = ;   //Получение сообщения
      [*] = ;   //Объявление войны врагам союзников
      [*] = ;   //(и наоборот для человека)
      [*] = ;
      [*] = ;   //Возврат героев, осаждающих дружественные замки
      [*] = ;
      [*] = ;   //Проверка контакта с другим правителем
      [*] = ;
      [*] = ;   //Обязательные события (по таймеру)
      [*] = ;   //Активизация квеста (кампания)
      [*] = ;
      [*] = ;   //Обязательные события (кампания)
      [*] = ;
      [*] = ;   //События при атаке оппонентов
      [*] = ;
      [*] = ;   //Доход и лечение войска
      [*] = ;
      [*] = ;   //Провинции
      [*] = ;   //Прирост населения
      [*] = ;   //Защитник
      [*] = ;   //Гарнизон
      [*] = ;   //Случайное событие
      [*] = ;   //Изменение шкалы недовольства
      [*] = ;   //Родовой замок
      [*] = ;   //Оппоненты
      [*] = ;   //Герои
      [*] = ;
      [*] = ;   ExecuteState('CheckUnionWars');
      [*] = ;
      [*] = ;   // all provinces
      [*] = ;   for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;      var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;      if SameText(plName, myPlName) and ((not gTutorial.map) or (cLastPlayer = myIndex)) then
      [*] = ;      begin
      [*] = ;         var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         var population : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Population');
      [*] = ;
      [*] = ;         var provRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;         IntRegister0 := provRace;
      [*] = ;         MapExecuteState('GetRaceParserByID');
      [*] = ;         var pProvRace : Integer = IntRegister1;
      [*] = ;         //province heal is all restospeedup modifiers
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetHeal');
      [*] = ;         var provHeal : Integer = IntRegister0;
      [*] = ;
      [*] = ;         var DefFourage : Integer = 0;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'IsUnderSiege');
      [*] = ;         var siegePlHandle : Integer = IntRegister0;
      [*] = ;         var underSiege : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;         if not underSiege then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 3;
      [*] = ;            IntRegister1 := -1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;            goldInc := goldInc + IntRegister0;
      [*] = ;            gemInc := gemInc + IntRegister1;
      [*] = ;
      [*] = ;            var provExplore : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetGrow');
      [*] = ;            var provGrow : Integer = IntRegister0;
      [*] = ;            // world rule
      [*] = ;            if (_worldrule_GetWorldRuleAbilityExistByID(24)) then
      [*] = ;               provGrow := _misc_RoundUp((provGrow*_worldrule_GetWorldRuleAbilityParam1(24))/100);
      [*] = ;
      [*] = ;            // population growth
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetLevel');
      [*] = ;            var oldLevel : Integer = IntRegister0;
      [*] = ;
      [*] = ;            IntRegister0 := oldLevel;
      [*] = ;            MapExecuteState('GetProvLevelParserByID');
      [*] = ;            var pProvLevel : Integer = IntRegister1;
      [*] = ;            var levelExplored : Integer = ParserGetIntValueByKeyByHandle(pProvLevel, 'Explored');
      [*] = ;
      [*] = ;            if oldLevel < gc_MaxProvinceLevel then
      [*] = ;            begin
      [*] = ;               if (provExplore >= levelExplored) or (provGrow <= 0) then
      [*] = ;               begin
      [*] = ;                  if (provGrow > 0) or ((population + provGrow) > 0) then
      [*] = ;                  begin
      [*] = ;                     population := population + provGrow;
      [*] = ;                     ParserSetIntValueByKeyByHandle(pProvince, 'Population', population);
      [*] = ;                  end; // else province is dying
      [*] = ;               end;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'CalcLevel');
      [*] = ;            end;
      [*] = 
      [*] = ;            // defender
      [*] = ;            var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;            var pDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;
      [*] = ;            if ParserGetCountByHandle(pDefUnits) > 0 then
      [*] = ;            begin
      [*] = ;               var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;               IntRegister0 := defID;
      [*] = ;               MapExecuteState('GetDefenderParserByID');
      [*] = ;               var pDefender : Integer = IntRegister1;
      [*] = ;
      [*] = ;               if not isAI then
      [*] = ;               begin
      [*] = ;                  var goldPayment : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'GoldPayment');
      [*] = ;                  var gemPayment : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'GemPayment');
      [*] = ;
      [*] = ;                  if goldPayment < 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := pDefUnits;
      [*] = ;                     MapExecuteState('GetDefArmyPayment');
      [*] = ;                     goldSpent := goldSpent + IntRegister1;
      [*] = ;                     gemSpent := gemSpent + IntRegister2;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     goldSpent := goldSpent + goldPayment;
      [*] = ;                     gemSpent := gemSpent + gemPayment;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               IntRegister0 := defID;
      [*] = ;               IntRegister1 := 4;
      [*] = ;               MapExecuteState('CheckDefenderAbility');
      [*] = ;               defFourage := defFourage + IntRegister2;
      [*] = ;
      [*] = ;               // heal defenders
      [*] = ;               IntRegister0 := pDefUnits;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               IntRegister2 := provHeal;
      [*] = ;               IntRegister3 := pDefender;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               BoolRegister1 := true;
      [*] = ;               MapExecuteState('map.RestoreUnits');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // garrison
      [*] = ;         var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;         var pGarrisonUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;         var payment : Integer = 0;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pGarrisonUnits)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pGarrisonUnit : Integer = ParserSelectByHandleByIndex(pGarrisonUnits, j);
      [*] = ;
      [*] = ;            IntRegister0 := pGarrisonUnit;
      [*] = ;            IntRegister1 := 0;
      [*] = ;            BoolRegister0 := not isAI;
      [*] = ;            MapExecuteState('GetUnitPaymentByParser');
      [*] = ;            payment := payment + IntRegister2;
      [*] = ;            gemSpent := gemSpent + IntRegister3;
      [*] = ;         end;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetHeal');
      [*] = ;         provHeal := IntRegister0;
      [*] = ;
      [*] = ;         IntRegister0 := pGarrisonUnits;
      [*] = ;         IntRegister1 := 0;
      [*] = ;         IntRegister2 := provHeal + 10;
      [*] = ;         IntRegister3 := 0;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         MapExecuteState('map.RestoreUnits');
      [*] = ;
      [*] = ;         IntRegister0 := 28;
      [*] = ;         ExecuteState('CheckInnerBuildAbility');
      [*] = ;         payment := payment - Floor(payment * (defFourage + IntRegister1) / 100);
      [*] = ;
      [*] = ;         if payment > 0 then
      [*] = ;            goldSpent := goldSpent + payment;
      [*] = ;
      [*] = ;         // unrests
      [*] = ;         if (not underSiege) and (population > 0) then
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerUnrest');
      [*] = ;            var provUnrest : Integer = IntRegister0;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;            var provMood : Integer = IntRegister0;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetLevel');
      [*] = ;            var provLevel : Integer = IntRegister0;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetUnRestSlowdown');
      [*] = ;            var provUnrestSlowdown : Integer = IntRegister0;
      [*] = ;
      [*] = ;            if provMood >= 0 then
      [*] = ;            begin
      [*] = ;               if provUnrest >= 0 then
      [*] = ;               begin
      [*] = ;                  provUnrest := provUnrest - (1 + provMood);
      [*] = ;                  if provUnrest < 0 then
      [*] = ;                     provUnrest := 0;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var raceUnrest : Integer = ParserGetIntValueByKeyByHandle(pProvRace, 'Unrest');
      [*] = ;               var unrest : Integer = Floor(provMood * provLevel * raceUnrest / 50) + provUnrestSlowdown;
      [*] = ;
      [*] = ;               if unrest >= 0 then
      [*] = ;                  unrest := -1;
      [*] = ;
      [*] = ;               provUnrest := provUnrest - unrest;
      [*] = ;            end;
      [*] = ;
      [*] = ;            IntRegister0 := provUnrest;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'SetOwnerUnrest');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // castle province
      [*] = ;   ExecuteState('GetCastleStats');
      [*] = ;   goldInc := goldInc + IntRegister0;
      [*] = ;   gemInc := gemInc + IntRegister1;
      [*] = ;   perc := perc + IntRegister2;
      [*] = ;   plCanHire := plCanHire + IntRegister3;
      [*] = ;   plCanOuterBuild := plCanOuterBuild + IntRegister4;
      [*] = ;   plCanCast := plCanCast + IntRegister5;
      [*] = ;   IntRegister0 := 32;
      [*] = ;   ExecuteState('CheckInnerBuildAbility');
      [*] = ;   goldInc := goldInc + campGoldAdd + min(Floor(plGold * IntRegister1 / 100),gc_MaxProfit);
      [*] = ;   gemInc := gemInc + campGemAdd;
      [*] = ;
      [*] = ;   // trade gold and gem income
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      if i <> myIndex then
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         if gArrDiplomacy[myIndex][i].trade.trade and _plr_IsInGame(plHandle) then
      [*] = ;         begin
      [*] = ;            goldInc := goldInc - gArrDiplomacy[myIndex][i].trade.gold;
      [*] = ;            goldInc := goldInc + gArrDiplomacy[i][myIndex].trade.gold;
      [*] = ;            gemInc := gemInc - gArrDiplomacy[myIndex][i].trade.gem;
      [*] = ;            gemInc := gemInc + gArrDiplomacy[i][myIndex].trade.gem;
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := 29;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'CheckInnerBuildAbility');
      [*] = ;         goldInc := goldInc + IntRegister1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // heroes
      [*] = ;   for i := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;      if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;      begin
      [*] = ;         var goUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;         var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;         var action : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;         var dist : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCastleDist);
      [*] = ;         var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(curUID);
      [*] = ;   
      [*] = ;         var pHeroParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   
      [*] = ;         IntRegister0 := curUID;
      [*] = ;         MapExecuteState('GetProvinceParserByUID');
      [*] = ;         var pCurProvince : Integer = IntRegister1;
      [*] = ;   
      [*] = ;         if isDead and (dist > 0) then
      [*] = ;         begin
      [*] = ;            dist := max(0, dist - 1);
      [*] = ;            SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCastleDist, dist);
      [*] = ;            if (dist = 0) and (not isAI) then
      [*] = ;            begin
      [*] = ;               var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_heroBodyDeliveredToCastle);
      [*] = ;               ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', goUID);
      [*] = ;            end
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var provExplore : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Explored');
      [*] = ;            if (action = gc_UnitTaskExplore) and (provExplore >= 100) then
      [*] = ;               SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType, gc_UnitTaskRest);
      [*] = ;         end;
      [*] = ;   
      [*] = ;         // army payment
      [*] = ;         var payment : Integer = 0;
      [*] = ;         var pHeroUnits : Integer = ParserSelectByHandleByKey(pHeroParser, 'Units');
      [*] = ;         for j := ParserGetCountByHandle(pHeroUnits)-1 downto 1 do
      [*] = ;         begin
      [*] = ;            var pHeroUnit : Integer = ParserSelectByHandleByIndex(pHeroUnits, j);
      [*] = ;   
      [*] = ;            IntRegister0 := pHeroUnit;
      [*] = ;            IntRegister1 := goHandle;
      [*] = ;            BoolRegister0 := not isAI;
      [*] = ;            MapExecuteState('GetUnitPaymentByParser');
      [*] = ;            payment := payment + IntRegister2;
      [*] = ;            gemSpent := gemSpent + IntRegister3;
      [*] = ;         end;
      [*] = ;   
      [*] = ;         // heal army
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetHeal');
      [*] = ;         var provHeal : Integer = IntRegister0;
      [*] = ;   
      [*] = ;         var provPlName : String = ParserGetValueByKeyByHandle(pCurProvince, 'Player');
      [*] = ;         var bMyProv : Boolean = SameText(myPlName, provPlName);
      [*] = ;   
      [*] = ;         IntRegister0 := pHeroUnits;
      [*] = ;         IntRegister1 := goHandle;
      [*] = ;         IntRegister2 := provHeal;
      [*] = ;         IntRegister3 := 0;
      [*] = ;         BoolRegister0 := bMyProv;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         MapExecuteState('map.RestoreUnits');
      [*] = ;
      [*] = ;         if not isDead then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_ability_pay_army_less;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;            payment := payment - Floor(payment * IntRegister1 / 100);
      [*] = ;
      [*] = ;            IntRegister0 := gc_ability_gold_income;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;            goldInc := goldInc + IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := gc_ability_gem_income;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;            gemInc := gemInc + IntRegister1;
      [*] = ;
      [*] = ;            // TODO: insert check for fail quests code
      [*] = ;         end;
      [*] = ;         goldSpent := goldSpent + payment;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   goldInc := goldInc + Floor(goldInc * perc / 100);
      [*] = ;
      [*] = ;   // corruption
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('GetCorruption');
      [*] = ;   if (not isAI) and (IntRegister0 > 0) then
      [*] = ;   begin
      [*] = ;      goldSpent := goldSpent + Floor(goldInc * IntRegister0 / 100);
      [*] = ;      gemSpent := gemSpent + Floor(gemInc * IntRegister0 / 100);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not isAI) then
      [*] = ;   begin
      [*] = ;      // cancel resource trades when insufficient means
      [*] = ;      for i := 1 to gPrototypeData.resources.number do
      [*] = ;      begin
      [*] = ;         IntRegister0 := i;
      [*] = ;         ExecuteState('GetResCount');
      [*] = ;         var resCount : Integer = IntRegister1;
      [*] = ;         if resCount < 0 then
      [*] = ;         begin
      [*] = ;            for j := 0 to gGame.map.players-1 do
      [*] = ;            if j <> myIndex then
      [*] = ;            begin
      [*] = ;               if  gArrDiplomacy[myIndex][j].trade.trade and gArrDiplomacy[myIndex][j].trade.arrResources[i-1] and _plr_IsInGame(GetPlayerHandleByIndex(j)) then
      [*] = ;               begin
      [*] = ;                  CancelTrade(j);
      [*] = ;                  resCount := resCount + 1;
      [*] = ;                  if resCount >= 0 then
      [*] = ;                     break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var plGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;      if (plGold < 0) and (goldInc - goldSpent < 0) then
      [*] = ;      begin
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;         begin
      [*] = ;            if j <> myIndex then
      [*] = ;            begin
      [*] = ;               if (gArrDiplomacy[myIndex][j].trade.gold > 0) and _plr_IsInGame(GetPlayerHandleByIndex(j)) then
      [*] = ;                  CancelTrade(j);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var plGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;      if (plGem < 0) and (gemInc - gemSpent < 0) then
      [*] = ;      begin
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;         begin
      [*] = ;            if j <> myIndex then
      [*] = ;            begin
      [*] = ;               if (gArrDiplomacy[myIndex][j].trade.gem > 0) and _plr_IsInGame(GetPlayerHandleByIndex(j)) then
      [*] = ;                  CancelTrade(j);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   plGoldInc := goldInc - goldSpent;
      [*] = ;   plGemInc := gemInc - gemSpent;
      [*] = ;
      [*] = ;   if isAI then
      [*] = ;   begin
      [*] = ;      goldInc := goldInc + 5 + gGame.arrplayerdifficulty[myIndex].basediff * 8;
      [*] = ;      gemInc := gemInc + gGame.currentTurn div 20 + gGame.arrplayerdifficulty[myIndex].basediff * 2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   plGold := plGold + plGoldInc;
      [*] = ;   plGem := plGem + plGemInc;
      [*] = ;
      [*] = ;   if gGame.currentTurn mod gc_CalcIrregIncomeInterval = 0 then
      [*] = ;   begin
      [*] = ;      var goldIncIrreg : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldIncIrreg);
      [*] = ;      var gemIncIrreg : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemIncIrreg);
      [*] = ;      var goldGain : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;      var gemGain : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;      
      [*] = ;      goldIncIrreg := Round(Lerp(goldGain / gc_CalcIrregIncomeInterval, goldIncIrreg, gc_IrregIncomePreserve));
      [*] = ;      gemIncIrreg := Round(Lerp(gemGain / gc_CalcIrregIncomeInterval, gemIncIrreg, gc_IrregIncomePreserve));
      [*] = ;      
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldIncIrreg, goldIncIrreg);
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGemIncIrreg, gemIncIrreg);
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldGain, 0);
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGemGain, 0);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   {if isAI and bImprovedAI then
      [*] = ;   begin
      [*] = ;      var myProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;      if myProfile > 0 then
      [*] = ;      begin
      [*] = ;         var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, myProfile);
      [*] = ;         var profRandom : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Random');
      [*] = ;         if profRandom > 0 then
      [*] = ;         begin
      [*] = ;            var diplTimer : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'DiplomacyTimer');
      [*] = ;            if _rand_Random(diplTimer) < 1 then
      [*] = ;            for i := 0 to gGame.map.players-1 do
      [*] = ;               _diplomacy_ShuffleRandom(myIndex, i, profRandom);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   {_log_Map('PlayerGold '+IntToStr(plGold));
      [*] = ;   _log_Map('PlayerGoldIncome '+IntToStr(goldInc));
      [*] = ;   _log_Map('PlayerGoldExpense '+IntToStr(goldSpent));
      [*] = ;   _log_Map('PlayerIrregGoldIncome '+IntToStr(GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldIncIrreg)));
      [*] = ;   _log_Map('PlayerGem '+IntToStr(plGem));
      [*] = ;   _log_Map('PlayerGemIncome '+IntToStr(plGemInc));
      [*] = ;   _log_Map('PlayerGemExpense '+IntToStr(gemSpent));
      [*] = ;   _log_Map('PlayerIrregGemIncome '+IntToStr(GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemIncIrreg)));}
      [*] = ;
      [*] = ;   {SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldInc, plGoldInc);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemInc, plGemInc);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanInnerBuild, plCanInnerBuild);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanOuterBuild, plCanOuterBuild);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanHire, plCanHire);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanCast, plCanCast);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iLastInnerBuilding, 0);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iLastOuterBuilding, 0);}
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc, plGoldInc);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc, plGemInc);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanInnerBuild, plCanInnerBuild);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanOuterBuild, plCanOuterBuild);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanHire, plCanHire);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanCast, plCanCast);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iLastInnerBuilding, 0);
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iLastOuterBuilding, 0);
      [*] = ;
      [*] = ;   // switch to next iteration state
      [*] = ;   gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;   gIntRegister_CurProvinceIndex := -1;
      [*] = ;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

