section.begin
   Name = KillHero
   Description : struct.begin
      [*] = ;IntRegister0 - hero handle
      [*] = ;BoolRegister0 - check current hero index
      [*] = ;BoolRegister1 - instantly destroy
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\KILLHERO';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure ResetQuests(goHandle : Integer);
      [*] = ;begin
      [*] = ;   var pGOQuests : Integer = ParserSelectByHandleByKey(ParserSelectGameObject(goHandle), 'Quests');
      [*] = ;   var i,p,ps,prov,idx,qid : Integer;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pGOQuests)-1 do
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByIndex(pGOQuests,i);
      [*] = ;      idx := ParserGetIntValueByKeyByHandle(p,'SiteIndex');
      [*] = ;      if idx >= 0 then
      [*] = ;      begin
      [*] = ;         prov := ParserSelectByHandleByIndex(gStratHexCells.handle,ParserGetIntValueByKeyByHandle(p,'ProvIndex'));
      [*] = ;         if prov <> 0 then
      [*] = ;         begin
      [*] = ;            ps := ParserSelectByHandleByIndex(ParserSelectByHandleByKey(prov,'Sites'),idx);
      [*] = ;            qid := ParserGetIntValueByKeyByHandle(ps,'Quest');
      [*] = ;            if _log then _Log_valuesM('Clearing_quest_for_killed_hero.ProvIdx|SiteIdx|QuestID',ParserGetIntValueByKeyByHandle(p,'ProvIndex'),idx,-1*qid,0,0,0);
      [*] = ;            if qid < 0 then
      [*] = ;               ParserSetIntValueByKeyByHandle(ps,'Quest',-1*qid);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var checkIndex : Boolean = BoolRegister0;
      [*] = ;var isDestroy : Boolean = BoolRegister1;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;//var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'CancelOrders');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iBeforeTargetUID, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iReachUID, 0);
      [*] = ;
      [*] = ;ResetQuests(goHandle);
      [*] = ;ParserClearByHandle(ParserSelectGameObject(goHandle));
      [*] = ;
      [*] = ;SetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead, true);
      [*] = ;SetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried, true);
      [*] = ;SetGameObjectVisibleByHandle(goHandle, false);
      [*] = ;
      [*] = ;if gIntRegister_MapSelectedUID = GetGameObjectUniqueIdByHandle(goHandle) then
      [*] = ;   gIntRegister_MapSelectedUID := 0;
      [*] = ;
      [*] = ;if _log then _Log_map(_log_name+' Hero bury, handle: '+IntToStr(goHandle));
      [*] = ;if goHandle = gIntRegister_MapActiveHeroHandle then
      [*] = ;   gIntRegister_MapActiveHeroHandle := 0;
      [*] = ;
      [*] = ;{if isDestroy or (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   GameObjectDestroyByHandle(goHandle)
      [*] = ;else
      [*] = ;   AddObjectToDestroyList(goHandle);}
      [*] = ;
      [*] = ;if checkIndex and (_gv_GetCurrentPlayer() = myPlIndex) and (gIntRegister_MapCurHeroIndex >= 0) then
      [*] = ;   gIntRegister_MapCurHeroIndex := gIntRegister_MapCurHeroIndex - 1;
      [*] = ;
      [*] = ;if goHandle = gIntRegister_BattleAttackHeroHandle then
      [*] = ;   gIntRegister_BattleAttackHeroHandle := 0;
      [*] = ;
      [*] = ;if goHandle = gIntRegister_BattleDefendHeroHandle then
      [*] = ;   gIntRegister_BattleDefendHeroHandle := 0;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

