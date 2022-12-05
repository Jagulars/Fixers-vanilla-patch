section.begin
   Name = CastRitual
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
      [*] = ;IntRegister1 - ritual ID
      [*] = ;IntRegister2 - hero UID
   struct.end
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var ritualID : Integer = IntRegister1;
      [*] = ;var heroUID : Integer = IntRegister2;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CASTRITUAL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var tHeroHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;if tHeroHandle <> 0 then
      [*] = ;   gIntRegister_MapCurHeroIndex := GetGameObjectIndexByHandle(tHeroHandle);
      [*] = ;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var provPlInd : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlInd : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;var plKarma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;var plCanCast : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanCast);
      [*] = ;
      [*] = ;var enemyProvince : Boolean = (provPlHandle <> myPlHandle);
      [*] = ;
      [*] = ;IntRegister0 := ritualID;
      [*] = ;MapExecuteState('GetRitualParserByID');
      [*] = ;var pRitual : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := ritualID;
      [*] = ;ExecuteState('GetRitualPrice');
      [*] = ;var gold : Integer = IntRegister1;
      [*] = ;var gem : Integer = IntRegister2;
      [*] = ;
      [*] = ;var ritKarma : Integer = ParserGetIntValueByKeyByHandle(pRitual, 'Karma');
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;var canCast : Boolean = true;
      [*] = ;var pProvRituals : Integer = ParserSelectByHandleByKey(pProvince, 'Rituals');
      [*] = ;
      [*] = ;if (plCanCast > 0) and ((plGold >= gold) or (gold=0)) and ((plGem >= gem) or (gem=0)) then
      [*] = ;begin
      [*] = ;   plGold := plGold - gold;
      [*] = ;   plGem := plGem - gem;
      [*] = ;   plKarma := plKarma + ritKarma;
      [*] = ;   plCanCast := plCanCast - 1;
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma, plKarma);
      [*] = ;
      [*] = ;   // change resource prices
      [*] = ;   var pRitResources : Integer = ParserSelectByHandleByKey(pRitual, 'Resources');
      [*] = ;   for i := ParserGetCountByHandle(pRitResources)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pRitResource : Integer = ParserSelectByHandleByIndex(pRitResources, i);
      [*] = ;      var resID : Integer = ParserGetIntValueByKeyByHandle(pRitResource, 'ResourceID');
      [*] = ;
      [*] = ;      IntRegister0 := resID;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'GetResCount');
      [*] = ;
      [*] = ;      if IntRegister1 <= 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := resID;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         MapExecuteState('map.ChangeResPrice');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := 12;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetRitualBonus');
      [*] = ;
      [*] = ;   if IntRegister1 > 0 then
      [*] = ;   begin
      [*] = ;      // province with magic barrier
      [*] = ;      if myPlHandle = GetPlayerHandleInterfaceIO() then
      [*] = ;      begin
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_playerRitualMagicBarrier);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      // set cooldown
      [*] = ;      ExecuteState('GetCastleParser');
      [*] = ;      var pPlCastle : Integer = IntRegister0;
      [*] = ;      var pPlRituals : Integer = ParserSelectByHandleByKey(pPlCastle, 'AvailableRituals');
      [*] = ;
      [*] = ;      var pPlRitual : Integer = ParserSelectByHandleByIndex(pPlRituals, ritualID);
      [*] = ;
      [*] = ;      // VVK: support for buildings which support cooldown decrease
      [*] = ;      IntRegister0 := ritualID;
      [*] = ;      ExecuteState('GetRitualCooldown');
      [*] = ;      ParserSetIntValueByKeyByHandle(pPlRitual, 'Cooldown', IntRegister1);
      [*] = ;
      [*] = ;      var ritCount : Integer = ParserGetIntValueByKeyByHandle(pPlRitual, 'Count');
      [*] = ;      if ritCount > 0 then
      [*] = ;         ParserSetIntValueByKeyByHandle(pPlRitual, 'Count', ritCount-1);
      [*] = ;
      [*] = ;      var pRitEffects : Integer = ParserSelectByHandleByKey(pRitual, 'Effects');
      [*] = ;      var time : Integer = ParserGetIntValueByKeyByHandle(pRitual, 'Time');
      [*] = ;      var event : Integer = ParserGetIntValueByKeyByHandle(pRitual, 'Event');
      [*] = ;
      [*] = ;      if enemyProvince then
      [*] = ;         pProvRituals := ParserSelectByHandleByKey(pProvince, 'CastedRituals')
      [*] = ;      else
      [*] = ;         pProvRituals := ParserSelectByHandleByKey(pProvince, 'Rituals');
      [*] = ;
      [*] = ;      if (time > 0) or (event > 0) then
      [*] = ;      begin
      [*] = ;         var pNewRitual : Integer = ParserAddChildByIndex(pProvRituals, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewRitual, 'RitualID', ritualID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewRitual, 'Time', time);
      [*] = ;         ParserSetValueByKeyByHandle(pNewRitual, 'Player', myPlName);
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pRitEffects)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pRitEffect : Integer = ParserSelectByHandleByIndex(pRitEffects, i);
      [*] = ;         var effectID : Integer = ParserGetIntValueByKeyByHandle(pRitEffect, 'EffectID');
      [*] = ;         var param1 : Integer = ParserGetIntValueByKeyByHandle(pRitEffect, 'Param1');
      [*] = ;
      [*] = ;         case effectID of
      [*] = ;            3 : begin
      [*] = ;               gIntRegister_CurProvinceIndex := GetGameObjectIndexByHandle(dummyHandle);
      [*] = ;               IntRegister0 := param1;
      [*] = ;               //IntRegister1 := myPlHandle;
      [*] = ;               //BoolRegister0 := true;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'ProceedEvent');
      [*] = ;            end;
      [*] = ;            5 : begin
      [*] = ;               if tHeroHandle = 0 then
      [*] = ;               begin
      [*] = ;                  for j := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;                  begin
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByIndex(j, myPlHandle);
      [*] = ;                     if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;                     begin
      [*] = ;                        var uid : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;                        if uid = dummyUID then
      [*] = ;                        begin
      [*] = ;                           tHeroHandle := goHandle;
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if tHeroHandle <> 0 then
      [*] = ;               begin
      [*] = ;                  if myPlInd = gIntRegister_MapMyPlayerIndex then
      [*] = ;                     gIntRegister_MapActiveHeroHandle := tHeroHandle;
      [*] = ;
      [*] = ;                  IntRegister0 := param1;
      [*] = ;                  GameObjectExecuteStateByHandle(tHeroHandle, 'ProceedEncounter');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := ritualID;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'CreateRitualFX');
      [*] = ;   end;
      [*] = ;
      [*] = ;   gIntRegister_MapPickedRitualID := 0;
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iCanCast, plCanCast);
      [*] = ;
      [*] = ;   if (myPlHandle=GetPlayerHandleInterfaceIO()) then
      [*] = ;      _map_RefreshProvinceHUD(dummyUID);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

