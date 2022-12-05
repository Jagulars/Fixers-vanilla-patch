section.begin
   Name = ProceedDeath
   Description : struct.begin
      [*] = ;IntRegister0 - battle player handle
      [*] = ;BoolRegister0 - my win
      [*] = ;BoolRegister1 - enemy win
      [*] = ;OUT: BoolRegister2 - is hero killed
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var batPlHandle : Integer = IntRegister0;
      [*] = ;var myWin : Boolean = BoolRegister0;
      [*] = ;var enWin : Boolean = BoolRegister1;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myCustomName : String = GetGameObjectCustomNameByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;BoolRegister0 := true;
      [*] = ;BoolRegister1 := false;
      [*] = ;BoolRegister2 := true;
      [*] = ;ExecuteState('MakeMoveMap');
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var batDist : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'MoveMap');
      [*] = ;
      [*] = ;if (batDist < 0) or (batDist > gc_MaxBodyDistance) then
      [*] = ;   batDist := gc_MaxBodyDistance;
      [*] = ;if batDist < 2 then
      [*] = ;   batDist := 2;
      [*] = ;
      [*] = ;ExecuteState('GetResurrectPrice');
      [*] = ;var resGold : Integer = IntRegister0;
      [*] = ;var resGem : Integer = IntRegister1;
      [*] = ;
      [*] = ;gIntRegister_GoldCost := resGold;
      [*] = ;gIntRegister_GemCost := resGem;
      [*] = ;
      [*] = ;gIntRegister_TurnsOnHeroRevive := batDist;
      [*] = ;_hero_GetName(myGOHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;//if myPlIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;   gIntRegister_DeadHeroHandle := myGOHandle;
      [*] = ;
      [*] = ;var myDeath : Boolean = false;
      [*] = ;var queryID : Integer = 0;
      [*] = ;
      [*] = ;if gTutorial.map and SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   queryID := 15038;
      [*] = ;   gTutorial.death := gTutorial.death + 1;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if myWin then
      [*] = ;   begin
      [*] = ;      if ((resGold = 0) or (plGold >= resGold)) and ((resGem = 0) or (plGem >= resGem)) then
      [*] = ;      begin
      [*] = ;         if SameText(cMode, 'cmPlayer') then
      [*] = ;            queryID := gc_gui_query_heroResurrect
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('Resurrect');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if SameText(cMode, 'cmPlayer') then
      [*] = ;            queryID := gc_gui_query_heroResurrectNoMoney
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := batDist;
      [*] = ;            ExecuteState('DeliverToCastle');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if SameText(cMode, 'cmPlayer') then
      [*] = ;         queryID := gc_gui_query_heroDeliverToCastle
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var goCount : Integer = 0;
      [*] = ;
      [*] = ;         for i := GetPlayerGameObjectsCountByHandle(batPlHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(i, batPlHandle);
      [*] = ;            if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;               goCount := goCount + 1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var myExp : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iExp);
      [*] = ;
      [*] = ;         if (myExp > 0) or (goCount > 1) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := batDist;
      [*] = ;            ExecuteState('DeliverToCastle');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            myDeath := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if queryID > 0 then
      [*] = ;begin
      [*] = ;   var resultHandle : Integer = 0;
      [*] = ;
      [*] = ;   if gBoolRegister_MapResolveConflicts then
      [*] = ;      gIntRegister_MapMyPlayerIndex := myPlIndex;
      [*] = ;
      [*] = ;   if gIntRegister_CurQueryHandle <> 0 then
      [*] = ;      resultHandle := _query_GetExecutedHandle();
      [*] = ;
      [*] = ;   if (resultHandle <> 0) and (QueryMachineIsResultHandle(resultHandle)) then
      [*] = ;      QueryMachineResultSetNextQuery(resultHandle, IntToStr(queryID))
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      StringRegister0 := IntToStr(queryID);
      [*] = ;      GUIExecuteState('map.RequestQueryWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gScenario.enabled) then
      [*] = ;begin
      [*] = ;   _scenario_AddTriggerHeroDie(gScenario.evaluate, GetGameObjectIndexByHandle(myGOHandle), myPlIndex);
      [*] = ;   _scenario_EvaluateTriggers(gScenario.evaluate);
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister2 := myDeath;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

