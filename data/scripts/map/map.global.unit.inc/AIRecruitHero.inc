section.begin
   Name = AIRecruitHero
   Description[*] = ;OUT: BoolRegister0 - can player spend money
   UsedFileName =
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;var plGoldInc : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;var plGemInc : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var hire : Boolean = false;
      [*] = ;var canSpend : Boolean = true;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(cDummyHandle, 'IsUnderSiege');
      [*] = ;var underSiege : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;if (not underSiege) and (not gGame.sandbox) then
      [*] = ;begin
      [*] = ;   var allowedHeroes : Integer = gGame.allowedHeroes;
      [*] = ;   var aliveHeroes : Boolean = false;
      [*] = ;   var heroCount : Integer = GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;   for i := heroCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;      if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;      begin
      [*] = ;         aliveHeroes := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _rand_ClearRoll;
      [*] = ;   for i := 0 to 3 do
      [*] = ;      gArrRollerN[i] := i+1;
      [*] = ;
      [*] = ;   // first hero
      [*] = ;   if (_plr_GetNonBuriedHeroCount(myPlHandle)=0) and (not ((gScenario.enabled) and (not GetBoolValueByIndex(gc_map_PLStack_MapUnit_bAllowHireHero)))) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 1;
      [*] = ;      ExecuteState('GetHeroPrice');
      [*] = ;      var goldPrice : Integer = IntRegister1;
      [*] = ;      var gemPrice : Integer = IntRegister2;
      [*] = ;      if ((plGold >= goldPrice) or (goldPrice=0)) and ((plGem >= gemPrice) or (gemPrice=0)) then
      [*] = ;      begin
      [*] = ;         hire := true;
      [*] = ;
      [*] = ;         IntRegister0 := 3;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         GameObjectExecuteStateByHandle(cDummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;         var gold : Integer = IntRegister0;
      [*] = ;         var gem : Integer = IntRegister1;
      [*] = ;
      [*] = ;         for i := 0 to 5 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := pCastle;
      [*] = ;            IntRegister1 := i;
      [*] = ;            StateMachineExecuteState(initMachine, 'map.GetNeighbourHexByIndex', 0);
      [*] = ;            var pProvince : Integer = IntRegister2;
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            if dummyHandle <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 3;
      [*] = ;               IntRegister1 := -1;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;               gold := gold + IntRegister0;
      [*] = ;               gem := gem + IntRegister1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         for i := 0 to 3 do
      [*] = ;         case i of
      [*] = ;            0 : begin
      [*] = ;               if ((allowedHeroes and $f) < $f) then
      [*] = ;               begin
      [*] = ;                  gArrRollerP[i] := 15;
      [*] = ;               end;
      [*] = ;            end; 
      [*] = ;            1 : begin
      [*] = ;               if ((allowedHeroes and $f0) < $f0) then
      [*] = ;               begin
      [*] = ;                  gArrRollerP[i] := 20;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               if ((allowedHeroes and $f00) < $f00) then
      [*] = ;               begin
      [*] = ;                  var probability : Integer = 1;
      [*] = ;                  if gold > 40 then
      [*] = ;                     probability := gold div 10;
      [*] = ;                  
      [*] = ;                  gArrRollerP[i] := probability;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            3 : begin
      [*] = ;               if ((allowedHeroes and $f000) < $f000) then
      [*] = ;               begin
      [*] = ;                  var probability : Integer = 1;
      [*] = ;                  if gem > 10 then
      [*] = ;                     probability := gem div 2;
      [*] = ;                  
      [*] = ;                  gArrRollerP[i] := probability;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      canSpend := false;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   // not first hero
      [*] = ;   begin
      [*] = ;      var needRes : Boolean = false;
      [*] = ;      for i := heroCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;         var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;         var buried : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried);
      [*] = ;         var dist : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCastleDist);
      [*] = ;
      [*] = ;         if dead and (not buried) and (dist = 0) then
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetResurrectPrice');
      [*] = ;            var resGold : Integer = IntRegister0;
      [*] = ;            var resGem : Integer = IntRegister1;
      [*] = ;
      [*] = ;            if ((plGold >= resGold) or (resGold=0)) and ((plGem >= resGem) or (resGem=0)) then
      [*] = ;            begin
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'Resurrect');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var willRes : Boolean = aliveHeroes;
      [*] = ;               if (plGold < 50) or (plGem < 10) or (plGoldInc < 7) or (plGemInc < 3) then
      [*] = ;               willRes := true;
      [*] = ;
      [*] = ;               if willRes and (_rand_Random(1 + gGame.currentTurn div 10) = 0) then
      [*] = ;               begin
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'Resurrect')
      [*] = ;               end
      [*] = ;               else
      [*] = ;               needRes := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (needRes) or ((gScenario.enabled) and (not GetBoolValueByIndex(gc_map_PLStack_MapUnit_bAllowHireHero))) then
      [*] = ;      canSpend := false
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         // choose hero
      [*] = ;         if gGame.currentTurn > 10 then
      [*] = ;         begin
      [*] = ;            for i := 0 to 3 do
      [*] = ;            begin
      [*] = ;               IntRegister0 := i+1;
      [*] = ;               ExecuteState('GetHeroPrice');
      [*] = ;               var goldPrice : Integer = IntRegister1;
      [*] = ;               var gemPrice : Integer = IntRegister2;
      [*] = ;
      [*] = ;               var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;               var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;               var plGoldLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;               var plGemLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;
      [*] = ;               if (plGold>=goldPrice+plGoldLimit) and (plGem>=gemPrice+plGemLimit) then
      [*] = ;               begin
      [*] = ;                  hire := true;
      [*] = ;                  case i of
      [*] = ;                     0 : begin
      [*] = ;                        if ((allowedHeroes and $f) < $f) then
      [*] = ;                        begin
      [*] = ;                           gArrRollerP[i] := max(1, plGold div 10);
      [*] = ;                        end;
      [*] = ;                     end; 
      [*] = ;                     1 : begin
      [*] = ;                        if ((allowedHeroes and $f0) < $f0) then
      [*] = ;                        begin
      [*] = ;                           gArrRollerP[i] := max(1, plGold div 10);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     2 : begin
      [*] = ;                        if ((allowedHeroes and $f00) < $f00) then
      [*] = ;                        begin
      [*] = ;                           gArrRollerP[i] := max(1, plGold div 2);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     3 : begin
      [*] = ;                        if ((allowedHeroes and $f000) < $f000) then
      [*] = ;                        begin
      [*] = ;                           gArrRollerP[i] := max(1, plGem);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if canSpend and hire then
      [*] = ;   begin
      [*] = ;      var classInd : Integer = _rand_Roll(false);
      [*] = ;
      [*] = ;      IntRegister0 := classInd;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      ExecuteState('RecruitHero');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := canSpend;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

