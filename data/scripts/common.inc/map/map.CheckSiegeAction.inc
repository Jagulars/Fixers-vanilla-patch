section.begin
   Name = map.CheckSiegeAction
   Code : struct.begin
      [*] = ;var pArmyUnits : Integer = IntRegister0;
      [*] = ;var heroHandle : Integer = IntRegister1;
      [*] = ;var pProvince : Integer = IntRegister2;
      [*] = ;var owner : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.CHECKSIEGEACTION';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var pHeroParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;var plHandle : Integer = GetGameObjectPlayerHandleByHandle(heroHandle);
      [*] = ;var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;var provCMode : String = GetPlayerControlModeByHandle(provPlHandle);
      [*] = ;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var curFort : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Fort');
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetMaxFortValue');
      [*] = ;var maxFort : Integer = IntRegister0;
      [*] = ;
      [*] = ;IntRegister0 := pArmyUnits;
      [*] = ;IntRegister1 := heroHandle;
      [*] = ;ExecuteState('map.GetSiegePowerByParser');
      [*] = ;var siegePower : Integer = IntRegister2;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetWallRepairValue');
      [*] = ;var repPercent : Integer = IntRegister0;
      [*] = ;var repValue : Integer = (maxFort * repPercent) div 100;
      [*] = ;
      [*] = ;if siegePower - repValue < 10 then
      [*] = ;   siegePower := repValue + 10;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetWallPercent');
      [*] = ;var percent : Integer = IntRegister0;
      [*] = ;var queryID : String = '';
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;ExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;gIntRegister_SiegeTurnsLeft := Floor((curFort - maxFort / 2) / (siegePower - repValue) - 0.0001) + 1;
      [*] = ;
      [*] = ;if heroHandle <> 0 then
      [*] = ;   _hero_GetName(heroHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;gIntRegister_BattleDefendArmy := ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;gIntRegister_BattleDefendHeroHandle := 0;
      [*] = ;
      [*] = ;var checkPlIndex : Integer = -1;
      [*] = ;
      [*] = ;//if plIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;if (not owner) and SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   checkPlIndex := plIndex;
      [*] = ;
      [*] = ;   if (percent = 0) or (maxFort = 0) then
      [*] = ;      queryID := IntToStr(gc_gui_query_heroContinueSiegeAttack)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if percent <= 50 then
      [*] = ;         queryID := IntToStr(gc_gui_query_heroContinueSiegeHole)
      [*] = ;      else
      [*] = ;         queryID := IntToStr(gc_gui_query_heroContinueSiegeNoHole);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   //if provPlIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;   if SameText(provCMode, 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      if gGame.gameType = gc_GameTypeHotseat then
      [*] = ;      begin
      [*] = ;         gIntRegister_MapMyPlayerIndex := provPlIndex;
      [*] = ;         _gv_SetIOHandle(provPlHandle,_log_name);
      [*] = ;      end;
      [*] = ;
      [*] = ;      checkPlIndex := provPlIndex;
      [*] = ;
      [*] = ;      if percent <= 50 then
      [*] = ;         queryID := IntToStr(gc_gui_query_playerEnemySiegeAttack)
      [*] = ;      else
      [*] = ;         queryID := IntToStr(gc_gui_query_playerEnemySiege);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if percent <= 50 then
      [*] = ;      begin
      [*] = ;         if heroHandle <> 0 then
      [*] = ;         begin
      [*] = ;            var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;            var pGarrUnits : Integer = ParserSelectByHandleByKey(pProvGarrison, 'Units');
      [*] = ;
      [*] = ;            if ParserGetCountByHandle(pGarrUnits) > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pProvGarrison;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               GameObjectExecuteStateByHandle(heroHandle, 'StartBattleWithArmy');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := plHandle;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'CaptureProvince');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'RebelSiegeAttack');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if queryID <> '' then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(checkPlIndex);
      [*] = ;   if plHandle <> 0 then
      [*] = ;   begin
      [*] = ;      StringRegister0 := queryID;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'CheckRequestQuery');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

