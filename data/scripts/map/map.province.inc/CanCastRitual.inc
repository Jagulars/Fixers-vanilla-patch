section.begin
   Name = CanCastRitual
   Description : struct.begin
      [*] = ;IntRegister0 - ritual ID
      [*] = ;IntRegister1 - player handle
      [*] = ;OUT: BoolRegister0 - is ritual available
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var ritualID : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = IntRegister1;
      [*] = ;var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var provUID : Integer = GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle);
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var provAlly : Boolean = SameText(plName, provPlName);
      [*] = ;var provPopulation : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Population');
      [*] = ;var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;IntRegister0 := ritualID;
      [*] = ;StateMachineExecuteState(initMachine, 'GetRitualParserByID', 0);
      [*] = ;var pRitual : Integer = IntRegister1;
      [*] = ;var onAlly : Boolean = ParserGetBoolValueByKeyByHandle(pRitual, 'OnAlly');
      [*] = ;var onEnemy : Boolean = ParserGetBoolValueByKeyByHandle(pRitual, 'OnEnemy');
      [*] = ;var onHero : Boolean = ParserGetBoolValueByKeyByHandle(pRitual, 'OnHero');
      [*] = ;
      [*] = ;var available : Boolean = true;
      [*] = ;var isNeutral : Boolean = _misc_IsProvinceNeutral(pProvince);
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;
      [*] = ;if (ritualID = 14) and (provPlName = '') then // no mass insanity (rebellion) on non-player provinces
      [*] = ;   available := false
      [*] = ;else
      [*] = ;if isNeutral then
      [*] = ;begin
      [*] = ;   available := false;
      [*] = ;
      [*] = ;   if onAlly and onHero then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plHandle;
      [*] = ;      ExecuteState('GetHeroesData');
      [*] = ;      if IntRegister2 > 0 then
      [*] = ;      available := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if onEnemy then
      [*] = ;   begin
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         var aPlHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         if aPlHandle <> plHandle then
      [*] = ;         begin
      [*] = ;            IntRegister0 := aPlHandle;
      [*] = ;            ExecuteState('GetHeroesData');
      [*] = ;            if IntRegister2 > 0 then
      [*] = ;            begin
      [*] = ;               available := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if not onHero then
      [*] = ;      begin
      [*] = ;         var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;         var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         if ParserGetCountByHandle(pGuardUnits) > 0 then
      [*] = ;         available := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if provAlly then
      [*] = ;   begin
      [*] = ;      if (not onAlly) then
      [*] = ;      available := false;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (not onEnemy) then
      [*] = ;      available := false;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if available and onHero then
      [*] = ;   begin
      [*] = ;      var isHero : Boolean = false;
      [*] = ;      for i := GetPlayerGameObjectsCountByHandle(provPlHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, provPlHandle);
      [*] = ;         if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;         begin
      [*] = ;            var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;            if curUID = provUID then
      [*] = ;            begin
      [*] = ;               isHero := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      available := isHero;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if available then
      [*] = ;begin
      [*] = ;   var pRitualEffects : Integer = ParserSelectByHandleByKey(pRitual, 'Effects');
      [*] = ;   for [MAIN]i := ParserGetCountByHandle(pRitualEffects)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pRitualEffect : Integer = ParserSelectByHandleByIndex(pRitualEffects, i);
      [*] = ;      var effectID : Integer = ParserGetIntValueByKeyByHandle(pRitualEffect, 'EffectID');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pRitualEffect, 'Param1');
      [*] = ;
      [*] = ;      case effectID of
      [*] = ;         18 :
      [*] = ;         begin
      [*] = ;            if isCastle then
      [*] = ;            available := false;
      [*] = ;         end;
      [*] = ;         19 :
      [*] = ;         begin
      [*] = ;            for j := GetCountOfPlayers-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var plHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;               if GetPlayerRaceTagByHandle(plHandle) = gc_map_PlayerRaceTag then
      [*] = ;               begin
      [*] = ;                  for k := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByIndex(k, plHandle);
      [*] = ;                     var action : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;                     var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;                     if (action = 5) and (curUID = provUID) then
      [*] = ;                     begin
      [*] = ;                        available := false;
      [*] = ;                        break(MAIN);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         20 :
      [*] = ;         begin
      [*] = ;            var isHero : Boolean = false;
      [*] = ;
      [*] = ;            for [PLAYER]j := GetCountOfPlayers-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var plHandle : Integer = GetPlayerHandleByIndex(j);
      [*] = ;               if GetPlayerRaceTagByHandle(plHandle) = gc_map_PlayerRaceTag then
      [*] = ;               begin
      [*] = ;                  for k := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByIndex(k, plHandle);
      [*] = ;                     if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;                     begin
      [*] = ;                        var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;                        if curUID = provUID then
      [*] = ;                        begin
      [*] = ;                           isHero := true;
      [*] = ;                           break(PLAYER);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if not isHero then
      [*] = ;            available := false;
      [*] = ;         end;
      [*] = ;         22 :
      [*] = ;         begin
      [*] = ;            ExecuteState('GetFreeOuterBuildSlot');
      [*] = ;            var slotInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;            if slotInd = -1 then
      [*] = ;            available := false;
      [*] = ;         end;
      [*] = ;         23 :
      [*] = ;         begin
      [*] = ;            IntRegister0 := param1;
      [*] = ;            ExecuteState('CheckOuterBuilding');
      [*] = ;            var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            if isBuilt then
      [*] = ;            available := false;
      [*] = ;         end;
      [*] = ;         24 :
      [*] = ;         begin
      [*] = ;            if provPopulation <= 0 then
      [*] = ;            available := false;
      [*] = ;         end;
      [*] = ;         25 :
      [*] = ;         begin
      [*] = ;            j := ParserSelectByHandleByKey(pProvince,'Defender');
      [*] = ;            var provDefID : Integer = ParserGetIntValueByKeyByHandle(j, 'DefenderID');
      [*] = ;            IntRegister0 := provDefID;
      [*] = ;            StateMachineExecuteState(initMachine, 'GetDefenderParserByID', 0);
      [*] = ;            var pDefender : Integer = IntRegister1;
      [*] = ;
      [*] = ;            var canDismiss : Boolean = ParserGetBoolValueByKeyByHandle(pDefender, 'CanDismiss');
      [*] = ;            if canDismiss then
      [*] = ;            available := false;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := available;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

