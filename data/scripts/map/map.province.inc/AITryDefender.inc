section.begin
   Name = AITryDefender
   Description[*] = ;BoolRegister0 - is player smart
   UsedFileName =
   Code : struct.begin
      [*] = ;var bigGuy : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;var pDefenders : Integer = gPrototypeData.defenders.handle;
      [*] = ;
      [*] = ;var pInitParser : Integer = ParserSelectStateMachineByHandle(initMachine);
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].basediff;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;var plGoldLimit : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;var plGemLimit : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;var plKarma : Integer = _map_GetPlayerKarma(plHandle);
      [*] = ;
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;var pDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;var isDefender : Boolean = (ParserGetCountByHandle(pDefUnits) > 0);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var pPlDefenders : Integer = ParserSelectByHandleByKey(pCastle, 'Defenders');
      [*] = ;
      [*] = ;var pRollDefenders : Integer = _misc_ParserGetOrCreateByKey('aitd_Defenders',true);
      [*] = ;
      [*] = ;function GetRandomDefender : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var sum : Integer = 0;
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pRollDefenders)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pRollDefender : Integer = ParserSelectByHandleByIndex(pRollDefenders, i);
      [*] = ;      sum := sum + ParserGetIntValueByKeyByHandle(pRollDefender, 'Freq');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sum > 0 then
      [*] = ;   begin
      [*] = ;      var randSum : Float = RandomExt * sum;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pRollDefenders)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pRollDefender : Integer = ParserSelectByHandleByIndex(pRollDefenders, i);
      [*] = ;         randSum := randSum - ParserGetIntValueByKeyByHandle(pRollDefender, 'Freq');
      [*] = ;
      [*] = ;         if randSum <= 0 then
      [*] = ;         begin
      [*] = ;            Result := ParserGetIntValueByKeyByHandle(pRollDefender, 'DefenderID');
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var taste, curDefPower : Integer = 0;
      [*] = ;var chDefID : Integer = 0;
      [*] = ;
      [*] = ;if plDiff = 0 then
      [*] = ;bigGuy := false;
      [*] = ;
      [*] = ;if isDefender then
      [*] = ;begin
      [*] = ;   var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;   
      [*] = ;   IntRegister0 := defID;
      [*] = ;   IntRegister1 := pDefUnits;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetDefenderPower', 0);
      [*] = ;   if bImprovedAI then
      [*] = ;   curDefPower := IntRegister2
      [*] = ;   else
      [*] = ;   taste := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;if pProvince = pCastle then // everything is expendable when stronghold is threatened
      [*] = ;begin
      [*] = ;   StringRegister0 := plName;
      [*] = ;   ExecuteState('IsEnemyNeighbour');
      [*] = ;   if BoolRegister0 then
      [*] = ;   begin
      [*] = ;      plGoldLimit := 0;
      [*] = ;      plGemLimit := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if bImprovedAI then
      [*] = ;begin
      [*] = ;   for i := ParserGetCountByHandle(pDefenders)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, i);
      [*] = ;      var defCount : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;      if (defCount <> 0) then
      [*] = ;      begin
      [*] = ;         var pDefender : Integer = ParserSelectByHandleByIndex(pDefenders, i);
      [*] = ;         var defPower : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Power');
      [*] = ;
      [*] = ;         // Ensure that early on in the campaign, not too powerful defenders (can be gained from site raiding) are picked since the player won't have necessary units to defeat them.
      [*] = ;         if (defCount < 0) or ((defCount > 0) and (bigGuy or (defPower < 3)) and ((gGame.gameType <> gc_GameTypeCampaign) or (defPower < 4 + gCampaign.currentTurn div 10))) and (defPower > curDefPower) then
      [*] = ;         begin
      [*] = ;            var defID : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'DefenderID');
      [*] = ;            IntRegister0 := defID;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GetDefenderPrice');
      [*] = ;            var goldPrice : Integer = IntRegister1;
      [*] = ;            var gemPrice : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if (plGold >= plGoldLimit + goldPrice) and ((gemPrice = 0) or (plGem >= plGemLimit + gemPrice)) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := defID;
      [*] = ;               ExecuteState('CanHireDefender');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := defID;
      [*] = ;                  StateMachineExecuteState(initMachine, 'GetDefenderPowerByID', 0);
      [*] = ;                  var power : Integer = IntRegister1;
      [*] = ;                  
      [*] = ;                  var defKarma : Integer =  Min(Max(ParserGetIntValueByKeyByHandle(pDefender, 'Karma'), -1), 1);
      [*] = ;                  power := power + Max(0, power) * defKarma * plKarma div 100;
      [*] = ;                  
      [*] = ;                  if (power > taste) then
      [*] = ;                  begin
      [*] = ;                     taste := power;
      [*] = ;                     chDefID := defID;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if chDefID > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := chDefID;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'BuyDefender');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var bHire : Boolean = false;
      [*] = ;   
      [*] = ;   // first compare defenders by their simple "Power" value, ranging from 1 to 6. 
      [*] = ;   for i := ParserGetCountByHandle(pDefenders)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, i);
      [*] = ;      var defCount : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;      if (defCount <> 0) then
      [*] = ;      begin
      [*] = ;         var pDefender : Integer = ParserSelectByHandleByIndex(pDefenders, i);
      [*] = ;         var defPower : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Power');
      [*] = ;
      [*] = ;         // use some random variance so not always the highest power defender is picked. Also ensure that early on in the campaign, not too powerful defenders are nto picked since the player won't have necessary units to defeat them.
      [*] = ;         if ((defCount < 0) or ((defCount > 0) and (bigGuy or (defPower < 3)) and ((gGame.gameType <> gc_GameTypeCampaign) or (defPower < 4 + gCampaign.currentTurn div 10)))) and (defPower > taste + RandomExt * taste / 2) then
      [*] = ;         begin
      [*] = ;            var defID : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'DefenderID');
      [*] = ;            IntRegister0 := defID;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'GetDefenderPrice');
      [*] = ;            var goldPrice : Integer = IntRegister1;
      [*] = ;            var gemPrice : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if (plGold >= plGoldLimit + goldPrice) and ((gemPrice = 0) or (plGem >= plGemLimit + gemPrice)) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := defID;
      [*] = ;               ExecuteState('CanHireDefender');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  taste := defPower;
      [*] = ;                  bHire := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if bHire then
      [*] = ;   begin
      [*] = ;      // now randomly choose the defender based on calculated power from GetDefenderPowerByID. Higher value results in higher chance to be chosen.
      [*] = ;      for i := ParserGetCountByHandle(pDefenders)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, i);
      [*] = ;         var defCount : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;         if (defCount <> 0) then
      [*] = ;         begin
      [*] = ;            var pDefender : Integer = ParserSelectByHandleByIndex(pDefenders, i);
      [*] = ;            var defPower : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Power');
      [*] = ;
      [*] = ;            if (defPower = taste) and ((defCount < 0) or ((defCount > 0) and (bigGuy or (defPower < 3)))) then
      [*] = ;            begin
      [*] = ;               var defID : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'DefenderID');
      [*] = ;               
      [*] = ;               IntRegister0 := defID;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetDefenderPrice');
      [*] = ;               var goldPrice : Integer = IntRegister1;
      [*] = ;               var gemPrice : Integer = IntRegister2;
      [*] = ;
      [*] = ;               if (plGold >= plGoldLimit + goldPrice) and ((gemPrice = 0) or (plGem >= plGemLimit + gemPrice)) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := defID;
      [*] = ;                  ExecuteState('CanHireDefender');
      [*] = ;                  if BoolRegister0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := defID;
      [*] = ;                     StateMachineExecuteState(initMachine, 'GetDefenderPowerByID', 0);
      [*] = ;                     var power : Integer = IntRegister1;
      [*] = ;                     
      [*] = ;                     // for some reason, cut the power value based on how many defenders are already hired by the player.
      [*] = ;                     var used : Integer = 0;
      [*] = ;                     
      [*] = ;                     IntRegister0 := defID;
      [*] = ;                     PlayerExecuteStateByHandle(plHandle, 'IsDefenderAvailable');
      [*] = ;                     if BoolRegister0 then
      [*] = ;                     for j := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;                     begin
      [*] = ;                        var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, j);
      [*] = ;
      [*] = ;                        if SameText(plName, ParserGetValueByKeyByHandle(pProvince, 'Player')) then
      [*] = ;                        begin
      [*] = ;                           var pProvDefender1 : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;                           var id : Integer = ParserGetIntValueByKeyByHandle(pProvDefender1, 'DefenderID');
      [*] = ;                           if (id > 0) then
      [*] = ;                              used := used + 1;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if used > 0 then
      [*] = ;                     begin
      [*] = ;                        power := power div used;
      [*] = ;                        if power < 1 then
      [*] = ;                          power := 1;
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     var pRollDefender : Integer = ParserAddChildByIndex(pRollDefenders, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pRollDefender, 'DefenderID', defID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pRollDefender, 'Freq', power);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // choose defender to hire
      [*] = ;      var chDefID : Integer = GetRandomDefender;
      [*] = ;
      [*] = ;      if chDefID > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := chDefID;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'BuyDefender');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

