section.begin
   Name = MakeDiplomacy
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\MAKEDIPLOMACY';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pProfiles : Integer = gPrototypeData.players.handle;
      [*] = ;var myPlDiff : Integer = gGame.arrplayerdifficulty[myPlIndex].basediff;
      [*] = ;var profile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var pProfile : Integer = ParserSelectByHandleByIndex(pProfiles, profile);
      [*] = ;var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
	  [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pMyTreasury : Integer = ParserSelectByHandleByKey(pMyParser, 'Treasury');
      [*] = ;
      [*] = ;var profAggro : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Aggro');
      [*] = ;var profDiplTimer : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'DiplomacyTimer');
      [*] = ;var profGreed : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Greed');
      [*] = ;var profSensitivity : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Sensitivity');
      [*] = ;var profRespectPower : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'RespectPower');
      [*] = ;var profRandom : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Random');
      [*] = ;
      [*] = ;if (not bImprovedAI) then
      [*] = ;begin
      [*] = ;   profGreed := 0; 
      [*] = ;   profSensitivity := 100;
      [*] = ;   profRespectPower := 0;
      [*] = ;   profRandom := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', Profile: '+IntToStr(profile)+']',_log_trace);
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;IntRegister0 := pCastle;
      [*] = ;IntRegister1 := -1;
      [*] = ;MapExecuteState('map.MakeMoveMap');
      [*] = ;
      [*] = ;var warInd : Integer = -1;
      [*] = ;var exchange : Boolean = true;
      [*] = ;var treaty : Boolean = true;
      [*] = ;var union : Boolean = true;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var curTurn : Integer = gGame.currentTurn;
      [*] = ;var resCount : Integer = gPrototypeData.resources.number;
      [*] = ;
      [*] = ;ExecuteState('GetGoldAndGemTaste');
      [*] = ;var goldTaste : Float = FloatRegister0;
      [*] = ;var gemTaste : Float = FloatRegister1;
      [*] = ;_log_Map('GoldTaste: '+FloatToStr(goldTaste)+', GemTaste: '+FloatToStr(gemTaste));
      [*] = ;
      [*] = ;ExecuteState('GetWars');
      [*] = ;var wars : Integer = IntRegister0;
      [*] = ;if wars = 0 then
      [*] = ;begin
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if i <> myPlIndex then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;
      [*] = ;      if _plr_IsInGame(plHandle) and (gArrDiplomacy[myPlIndex][i].treaty = gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][i].canKill > 0) then
      [*] = ;      begin
      [*] = ;         if warInd < 0 then
      [*] = ;            warInd := i
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := warInd;
      [*] = ;            ExecuteState('GetAttitude');
      [*] = ;            var warAtt : Integer = IntRegister1;
      [*] = ;            IntRegister0 := warInd;
      [*] = ;            ExecuteState('GetPoliticalPower');
      [*] = ;            var warPower : Integer = IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := i;
      [*] = ;            ExecuteState('GetAttitude');
      [*] = ;            var plAtt : Integer = IntRegister1;
      [*] = ;            IntRegister0 := i;
      [*] = ;            ExecuteState('GetPoliticalPower');
      [*] = ;            var plPower : Integer = IntRegister1;
      [*] = ;
      [*] = ;            var iOld : Integer = warAtt - gArrDiplomacy[myPlIndex][warInd].canKill div 5 - warPower div 5;
      [*] = ;            var iNew : Integer = plAtt - gArrDiplomacy[myPlIndex][i].canKill div 5 - plPower div 5;
      [*] = ;
      [*] = ;            if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;               iNew := iNew - myPlDiff * 2;
      [*] = ;            var warPlHandle : Integer = GetPlayerHandleByIndex(warInd);
      [*] = ;            if SameText(GetPlayerControlModeByHandle(warPlHandle), 'cmPlayer') then
      [*] = ;               iOld := iOld - myPlDiff * 2;
      [*] = ;
      [*] = ;            if iNew < iOld then
      [*] = ;               warInd := i;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_log_Map('Wars: '+IntToStr(wars)+', NewWarInd: '+IntToStr(warInd));
      [*] = ;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if (i <> myPlIndex) and (gArrDiplomacy[myPlIndex][i].message.treaty = 0) and (gArrDiplomacy[myPlIndex][i].message.mType = 0) and
      [*] = ;((gArrDiplomacy[i][myPlIndex].message.mType <> gc_MessageTreaty) or (gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyWar)) then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;
      [*] = ;   if _plr_IsInGame(plHandle) and (gArrDiplomacy[myPlIndex][i].treaty > 0) and (gArrDiplomacy[myPlIndex][i].message.mType = 0) and (GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex) = 0) then
      [*] = ;   begin
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;      if gArrDiplomacy[i][myPlIndex].message.mType > 0 then
      [*] = ;         treaty := false
      [*] = ;      else
      [*] = ;         treaty := true;
      [*] = ;
      [*] = ;      var bOppMessage : Boolean = (gArrDiplomacy[i][myPlIndex].message.mType > 0) and (gArrDiplomacy[i][myPlIndex].message.deal >= 0);
      [*] = ;
      [*] = ;      var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;      IntRegister0 := i;
      [*] = ;      ExecuteState('GetAttitude');
      [*] = ;      var attitude : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := i;
      [*] = ;      ExecuteState('GetPoliticalPower');
      [*] = ;      var polPower : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var canKill : Integer = gArrDiplomacy[myPlIndex][i].canKill;
      [*] = ;      var messPlInd : Integer = -1;
      [*] = ;
      [*] = ;      _log_Map('DiplPlayerIndex: '+IntToStr(i)+', DiplPlayerProfile: '+IntToStr(plProfile)+', Political Power: '+IntToStr(polPower)+', Attitude: '+IntToStr(attitude)+', CanKill: '+IntToStr(canKill));
      [*] = ;
      [*] = ;      MapExecuteState('map.GetActivePlayers');
      [*] = ;      if IntRegister0 = 2 then
      [*] = ;      begin
      [*] = ;         case gArrDiplomacy[myPlIndex][i].treaty of
      [*] = ;            gc_TreatyUnion : begin
      [*] = ;               ExecuteState('GetProvinceCount');
      [*] = ;               var myProvCount : Integer = IntRegister0;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetProvinceCount');
      [*] = ;               var plProvCount : Integer = IntRegister0;
      [*] = ;
      [*] = ;               if SameText(cMode, 'cmPlayer') then
      [*] = ;               begin
      [*] = ;                  if (gGame.gameType = gc_GameTypeCampaign) and (gCampaign.arrDialogs[103] > 0) and (profile = 3) then
      [*] = ;                  begin
      [*] = ;                     // Beleth in campaign
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageDemandSurrender;
      [*] = ;                     _misc_PlMakeDiplomacyText(myPlIndex, i, 31, 0);
      [*] = ;                     messPlInd := i;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     gArrDiplomacy[myPlIndex][i].answer := 0;
      [*] = ;                     
      [*] = ;                     var bDemandSurrender, bSurrender : Boolean;
      [*] = ;                     
      [*] = ;                     if bImprovedAI then
      [*] = ;                     begin
      [*] = ;                        var surrenderPower : Integer = polPower + attitude div 2 - profGreed;
      [*] = ;                        _log_Map('SurrenderPower: '+IntToStr(surrenderPower));
      [*] = ;                        bDemandSurrender := (surrenderPower < 40);
      [*] = ;                        bSurrender := (surrenderPower > 100);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        bDemandSurrender := (myProvCount >= plProvCount * 3); // demand surrender if I have three times more provinces
      [*] = ;                        bSurrender := (plProvCount >= myProvCount * 3); // surrender if my ally has three times more provinces
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     if bDemandSurrender then
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageDemandSurrender;
      [*] = ;                        _misc_PlMakeDiplomacyText(myPlIndex, i, 21, 0);
      [*] = ;                        messPlInd := i;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if bSurrender then
      [*] = ;                        begin
      [*] = ;                           gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageSurrender;
      [*] = ;                           _misc_PlMakeDiplomacyText(myPlIndex, i, 22, 0);
      [*] = ;                           messPlInd := i;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           // offer to randomize victory
      [*] = ;                           gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageThrowDice;
      [*] = ;                           _misc_PlMakeDiplomacyText(myPlIndex, i, 20, 0);
      [*] = ;                           messPlInd := i;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else // if two AI players in union win, the one with more provinces gains the shard (or with more political power if improved ai)
      [*] = ;               begin
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  if ((not bImprovedAI) and (myProvCount > plProvCount)) or (bImprovedAI and (polPower <= 0)) then
      [*] = ;                     PlayerExecuteStateByHandle(plHandle,'SetInGameStatus')
      [*] = ;                  else
      [*] = ;                     ExecuteState('SetInGameStatus');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_TreatyPeace : begin
      [*] = ;               // declare war if remaining two players are not in union
      [*] = ;               if SameText(cMode, 'cmPlayer') then
      [*] = ;               begin
      [*] = ;                  gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyWar;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].answer := 0;
      [*] = ;                  _misc_PlMakeDiplomacyText(myPlIndex, i, 30, 0);
      [*] = ;                  messPlInd := i;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := i;
      [*] = ;                  ExecuteState('DeclareWar');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var bExpandHalt : Boolean = GetBoolValueByIndex(gc_map_PLStack_MapUnit_bExpandHalted);
      [*] = ;         var randomFactor : Integer = 0;
      [*] = ;         if profRandom > 0 then
      [*] = ;            randomFactor := gArrDiplomacy[myPlIndex][i].random;
      [*] = ;   
      [*] = ;         case gArrDiplomacy[myPlIndex][i].treaty of
      [*] = ;            gc_TreatyWar : begin
      [*] = ;               // offer peace
      [*] = ;               if (not bOppMessage) and ((polPower > 0) or (canKill <= 0) or bImprovedAI) then
      [*] = ;               begin
      [*] = ;                  var ally1 : Integer = -1; // my ally
      [*] = ;                  var ally2 : Integer = -1; // ally of my enemy
      [*] = ;
      [*] = ;                  for j := 0 to gGame.map.players-1 do
      [*] = ;                  if (j <> myPlIndex) and (j <> i) and _plr_IsInGame(GetPlayerHandleByIndex(j)) then
      [*] = ;                  begin
      [*] = ;                     if (gArrDiplomacy[j][myPlIndex].treaty = gc_TreatyUnion) and (gArrDiplomacy[j][i].treaty = gc_TreatyWar) then
      [*] = ;                        ally1 := j
      [*] = ;                     else
      [*] = ;                     if (gArrDiplomacy[j][i].treaty = gc_TreatyUnion) and (gArrDiplomacy[j][myPlIndex].treaty = gc_TreatyWar) then
      [*] = ;                        ally2 := j;
      [*] = ;                  end;
      [*] = ;                        
      [*] = ;                  var plHandle1 : Integer = GetPlayerHandleByIndex(ally1);
      [*] = ;                  var plHandle2 : Integer = GetPlayerHandleByIndex(ally2);
      [*] = ;                  var cMode1 : String = GetPlayerControlModeByHandle(plHandle1);
      [*] = ;                  var cMode2 : String = GetPlayerControlModeByHandle(plHandle2);
      [*] = ;                  
      [*] = ;                  // don't bombard peace offers every turn
      [*] = ;                  var time : Integer = Max(gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyWar][1], gArrDiplomacy[i][myPlIndex].arrTalk[gc_TreatyWar][1]); // when war was declared,
      [*] = ;                  time := Max(time, gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyPeace][1]); // or when I have last offered peace
      [*] = ;
      [*] = ;                  var readyForPeace : Boolean = (curTurn - time > profDiplTimer);
      [*] = ;                  
      [*] = ;                  if readyForPeace and (ally1 >= 0) and SameText(cMode1, 'cmPC') then // ensure that ally has not sent a peace offer lately either
      [*] = ;                  begin
      [*] = ;                     var pProfile1 : Integer = ParserSelectByHandleByIndex(pProfiles, GetPlayerIntValueIndByHandle(plHandle1, gc_map_PLStack_MapUnit_iProfile));
      [*] = ;                     
      [*] = ;                     var time1 : Integer = Max(gArrDiplomacy[ally1][i].arrTalk[gc_TreatyWar][1], gArrDiplomacy[i][ally1].arrTalk[gc_TreatyWar][1]);
      [*] = ;                     time1 := Max(time1, gArrDiplomacy[ally1][i].arrTalk[gc_TreatyPeace][1]);
      [*] = ;                     
      [*] = ;                     readyForPeace := (curTurn - time1 > ParserGetIntValueByKeyByHandle(pProfile1, 'DiplomacyTimer'));
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if readyForPeace then
      [*] = ;                  begin
      [*] = ;                     GameObjectExecuteStateByHandle(cDummyHandle, 'IsUnderSiege');
      [*] = ;                     var siegePlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;                     var bAskPeace : Boolean = (plHandle = siegePlHandle) or ((ally2 >= 0) and (plHandle2 = siegePlHandle));  // always ask for peace if the enemy or his ally is besieging stronghold.
      [*] = ;                     var peacePower : Integer = 0;
      [*] = ;                     if not bAskPeace then 
      [*] = ;                     begin
      [*] = ;                        if bImprovedAI then
      [*] = ;                        begin
      [*] = ;                           peacePower := polPower + attitude + randomFactor - profAggro div 3 - canKill;
      [*] = ;                        
      [*] = ;                           if bExpandHalt then
      [*] = ;                              peacePower := peacePower - 20;//Max(0, profAggro div 3 + profGreed);
      [*] = ;                  
      [*] = ;                           if (profSensitivity > 0) then
      [*] = ;                           begin
      [*] = ;                              if gArrDiplomacy[myPlIndex][i].arrTraitor[0] > 0 then // attacks without declaration of war
      [*] = ;                                 peacePower := peacePower - 500 * profSensitivity div 100;
      [*] = ;                     
      [*] = ;                              if gArrDiplomacy[myPlIndex][i].arrTraitor[1] > 0 then // attack on ally
      [*] = ;                                 peacePower := peacePower - 1000 * profSensitivity div 100;
      [*] = ;                           end;
      [*] = ;                        
      [*] = ;                           _log_Map('MakePeacePower: '+IntToStr(peacePower));
      [*] = ;                           bAskPeace := (peacePower >= 10);
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                           bAskPeace := (_rand_Random(50 + curTurn - time) > profAggro div 2);
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     if bAskPeace then
      [*] = ;                     begin
      [*] = ;                        var executePeace : Boolean = true;
      [*] = ;                        
      [*] = ;                        // check if I want peace also with the ally of the enemy, must be checked first
      [*] = ;                        if (ally2 >= 0) and (gArrDiplomacy[myPlIndex][ally2].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[ally2][myPlIndex].message.treaty <> gc_TreatyPeace) then
      [*] = ;                        begin
      [*] = ;                           bAskPeace := (plHandle = siegePlHandle) or ((ally2 >= 0) and (plHandle2 = siegePlHandle)); // always ask for peace if the enemy or his ally is besieging stronghold.
      [*] = ;                           
      [*] = ;                           if not bAskPeace then
      [*] = ;                           begin
      [*] = ;                              if bImprovedAI then
      [*] = ;                              begin
      [*] = ;                                 IntRegister0 := ally2;
      [*] = ;                                 ExecuteState('GetPoliticalPower');
      [*] = ;                                 var polPower2 : Integer = IntRegister1;
      [*] = ;                                 
      [*] = ;                                 IntRegister0 := ally2;
      [*] = ;                                 ExecuteState('Attitude');
      [*] = ;                                 var attitude2 : Integer = IntRegister1;
      [*] = ;                                 
      [*] = ;                                 var randomFactor2 : Integer = 0;
      [*] = ;                                 if profRandom > 0 then
      [*] = ;                                    randomFactor := gArrDiplomacy[myPlIndex][ally2].random;
      [*] = ;                                 
      [*] = ;                                 var peacePower2 : Integer = polPower2 + attitude2 + randomFactor2 - profAggro div 3 - gArrDiplomacy[myPlIndex][ally2].canKill;
      [*] = ;                        
      [*] = ;                                 if bExpandHalt then
      [*] = ;                                    peacePower2 := peacePower2 - 20;
      [*] = ;                  
      [*] = ;                                 if (profSensitivity > 0) then
      [*] = ;                                 begin
      [*] = ;                                    if gArrDiplomacy[myPlIndex][ally2].arrTraitor[0] > 0 then // attacks without declaration of war
      [*] = ;                                       peacePower2 := peacePower2 - 500 * profSensitivity div 100;
      [*] = ;                     
      [*] = ;                                    if gArrDiplomacy[myPlIndex][ally2].arrTraitor[1] > 0 then // attack on ally
      [*] = ;                                       peacePower2 := peacePower2 - 1000 * profSensitivity div 100;
      [*] = ;                                 end;
      [*] = ;                                 _log_Map('MakePeacePower AllyIndex('+IntToStr(ally2)+'): '+IntToStr(peacePower2));
      [*] = ;                                 
      [*] = ;                                 peacePower := peacePower + peacePower2 div 2;
      [*] = ;                                 _log_Map('Merged MakePeacePower: '+IntToStr(peacePower));
      [*] = ;                                 
      [*] = ;                                 bAskPeace := (peacePower >= 10);
      [*] = ;                              end
      [*] = ;                              else
      [*] = ;                              if (gArrDiplomacy[myPlIndex][ally2].canKill < 1) then
      [*] = ;                                  bAskPeace := true
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 IntRegister0 := ally2;
      [*] = ;                                 ExecuteState('GetPoliticalPower');
      [*] = ;                                 bAskPeace := (IntRegister1 > 0);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                           
      [*] = ;                           if bAskPeace then // ask peace
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][ally2].message.mType := gc_MessageTreaty;
      [*] = ;                              gArrDiplomacy[myPlIndex][ally2].message.treaty := gc_TreatyPeace;
      [*] = ;                              
      [*] = ;                              if SameText(cMode2, 'cmPlayer') and ((gGame.gameType <> gc_GameTypeLanShard) or (ally2 = gIntRegister_MapMyPlayerIndex)) then 
      [*] = ;                              begin
      [*] = ;                                 _misc_PlMakeDiplomacyText(myPlIndex, ally2, 5, 0);
      [*] = ;                                 var queryID : String = gArrDiplomacy[myPlIndex][ally2].message.text;
      [*] = ;                                 if (queryID <> '') then
      [*] = ;                                 begin
      [*] = ;                                    var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(plHandle2), 'Queries'), '*');
      [*] = ;                                    ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;                                    ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', myPlIndex);
      [*] = ;                                    ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;            
      [*] = ;                                   _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][ally2].queryWindowMessage, gArrDiplomacy[myPlIndex][ally2].message);
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                              executePeace := false;
      [*] = ;                        end;
      [*] = ;                        
      [*] = ;                        if executePeace then
      [*] = ;                        begin
      [*] = ;                           if SameText(cMode, 'cmPlayer') then // send peace proposal to human enemy
      [*] = ;                           begin
      [*] = ;                              executePeace := false;
      [*] = ;                           
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;                              _misc_PlMakeDiplomacyText(myPlIndex, i, 5, 0);
      [*] = ;                              messPlInd := i;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           if (ally1 >= 0) or (ally2 >= 0) then // union peace offer, cannot execute immediately
      [*] = ;                           begin
      [*] = ;                              executePeace := false;
      [*] = ;                           
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;                           end;
      [*] = ;                         
      [*] = ;                           //Determine if my AI ally wants peace and send messages. 
      [*] = ;                           //Here instead of DiplomacyReceiveMessages (unlike human players) because otherwise there's a risk that the peace will be executed in GetDiploAnswerAI, which we don't want, but just to determine if a message should be sent.
      [*] = ;                           if (ally1 >= 0) and SameText(cMode1, 'cmPC') then
      [*] = ;                           begin
      [*] = ;                              var sendToI : Boolean = (gArrDiplomacy[ally1][i].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[i][ally1].message.treaty <> gc_TreatyPeace);
      [*] = ;                              var sendToAlly2 : Boolean = (ally2 >= 0) and (gArrDiplomacy[ally1][ally2].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[ally2][ally1].message.treaty <> gc_TreatyPeace);
      [*] = ;                        
      [*] = ;                              var checkPlInd : Integer = -1;
      [*] = ;                              if sendToI then checkPlInd := i
      [*] = ;                              else 
      [*] = ;                              if sendToAlly2 then checkPlInd := ally2;
      [*] = ;                              
      [*] = ;                              if checkPlInd >= 0 then
      [*] = ;                              begin
      [*] = ;                                 // use pseudo offer from the enemy player to get willingness of AI to form peace.
      [*] = ;                                 gArrDiplomacy[checkPlInd][ally1].message.mType := gc_MessageTreaty;
      [*] = ;                                 gArrDiplomacy[checkPlInd][ally1].message.treaty := gc_TreatyPeace;
      [*] = ;                           
      [*] = ;                                 IntRegister0 := checkPlInd;
      [*] = ;                                 PlayerExecuteStateByHandle(plHandle1, 'GetDiploAnswerAI');
      [*] = ;                                 var bAgree : Boolean = (gArrDiplomacy[checkPlInd][ally1].message.deal > 0);
      [*] = ;                                 _diplomacy_ClearMessage(gArrDiplomacy[checkPlInd][ally1].message);
      [*] = ;                           
      [*] = ;                                 // send the actual message(s)
      [*] = ;                                 if sendToI then
      [*] = ;                                 begin
      [*] = ;                                    gArrDiplomacy[ally1][i].message.mType := gc_MessageTreaty;
      [*] = ;                                    gArrDiplomacy[ally1][i].message.treaty := gc_TreatyPeace;
      [*] = ;                                    if not bAgree then 
      [*] = ;                                    begin
      [*] = ;                                       gArrDiplomacy[ally1][i].message.deal := -3;
      [*] = ;                                       gArrDiplomacy[ally1][i].arrTalk[gc_TreatyPeace][0] := 0;
      [*] = ;                                       gArrDiplomacy[ally1][i].arrTalk[gc_TreatyPeace][1] := curTurn;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                           
      [*] = ;                                 if sendToAlly2 then
      [*] = ;                                 begin
      [*] = ;                                    gArrDiplomacy[ally1][ally2].message.mType := gc_MessageTreaty;
      [*] = ;                                    gArrDiplomacy[ally1][ally2].message.treaty := gc_TreatyPeace;
      [*] = ;                                    if not bAgree then 
      [*] = ;                                    begin
      [*] = ;                                       gArrDiplomacy[ally1][ally2].message.deal := -3;
      [*] = ;                                       gArrDiplomacy[ally1][ally2].arrTalk[gc_TreatyPeace][0] := 0;
      [*] = ;                                       gArrDiplomacy[ally1][ally2].arrTalk[gc_TreatyPeace][1] := curTurn;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           // no peace if the AI player is about to destroy me. Otherwise, they could never destroy each other. Only when 1 AI vs 1 AI.
      [*] = ;                           if (siegePlHandle = plHandle) or (gArrDiplomacy[i][myPlIndex].canKill >= 20) then
      [*] = ;                              executePeace := false;
      [*] = ;
      [*] = ;                           if executePeace then
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][i].treaty := gc_TreatyPeace;
      [*] = ;                              gArrDiplomacy[i][myPlIndex].treaty := gc_TreatyPeace;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyPeace][1] := curTurn;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_TreatyPeace : begin
      [*] = ;               if (warInd = i) and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[2][1] >= Min(10, curTurn)) and
      [*] = ;               (curTurn - gArrDiplomacy[i][myPlIndex].arrTalk[2][1] >= Min(10, curTurn)) then
      [*] = ;               begin
      [*] = ;                  if ((curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[6][1] >= Min(20, curTurn)) or
      [*] = ;                  (gArrDiplomacy[myPlIndex][i].arrTalk[6][0] = 0)) and
      [*] = ;                  (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[7][1] >= Min(10, curTurn)) then
      [*] = ;                  begin
      [*] = ;                     treaty := false;
      [*] = ;                     var bSendMessage, bDemand : Boolean = false;
      [*] = ;
      [*] = ;                     var demandAmount : Integer;
      [*] = ;                     var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;                     var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;                     if bImprovedAI then
      [*] = ;                     begin
      [*] = ;                        var peacePower : Integer = polPower + attitude + randomFactor - profAggro div 3 - canKill;
      [*] = ;
      [*] = ;                        if (gArrDiplomacy[myPlIndex][i].arrTalk[6][1] > 0) and (gArrDiplomacy[myPlIndex][i].arrTalk[6][0] = 0) then // more angry when demands were refused
      [*] = ;                           peacePower := peacePower - profSensitivity div (10 + curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[6][1]);
      [*] = ;                        
      [*] = ;                        if bExpandHalt then
      [*] = ;                           peacePower := peacePower - 20;
      [*] = ;                        
      [*] = ;                        _log_Map('KeepPeacePower: '+IntToStr(peacePower));
      [*] = ;                        
      [*] = ;                        if (peacePower <= -10) then
      [*] = ;                           bSendMessage := true;
      [*] = ;                        
      [*] = ;                        if bSendMessage then
      [*] = ;                        begin
      [*] = ;                           demandAmount := 100 + curTurn + curTurn * profGreed div 5;
      [*] = ;
      [*] = ;                           // ask for buyout
      [*] = ;                           if (not bOppMessage) and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[6][1] >= Min(profDiplTimer, curTurn)) // if enough turns have passed since previous demand
      [*] = ;                           and (plGem * 3 + plGold > demandAmount) and (demandAmount > 100) then
      [*] = ;                              bDemand := true;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        var aggression : Integer = profAggro;
      [*] = ;                        var bloodThirst : Integer = 1000 - polPower - attitude + profAggro + gArrDiplomacy[myPlIndex][i].canKill;
      [*] = ;                        
      [*] = ;                        if SameText(cMode, 'cmPlayer') then
      [*] = ;                           bloodThirst := bloodThirst + myPlDiff * 20;
      [*] = ;
      [*] = ;                        if (gArrDiplomacy[myPlIndex][i].arrTalk[6][1] > 0) and (gArrDiplomacy[myPlIndex][i].arrTalk[6][0] = 0) then // more angry when demands were refused
      [*] = ;                           aggression := aggression + 10 + _rand_Random(30);
      [*] = ;                        
      [*] = ;                        if (bExpandHalt and (_rand_Random(5) <= aggression div 20)) or
      [*] = ;                        ((_rand_Random(50 + profAggro div 2) > attitude) and (_rand_Random(100) < aggression) and
      [*] = ;                        (_rand_Random(50) < gArrDiplomacy[myPlIndex][i].canKill)) then
      [*] = ;                           bSendMessage := true;
      [*] = ;                        
      [*] = ;                        if bSendMessage then
      [*] = ;                        begin
      [*] = ;                           demandAmount := 100 + (bloodThirst - 500) div 3 + curTurn;
      [*] = ;
      [*] = ;                           // ask for buyout
      [*] = ;                           if (not bOppMessage) and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[6][1] >= Min(20, curTurn)) and // if at least 20 turns have passed since previous demand
      [*] = ;                           (_rand_Random(bloodThirst) < 500 + profGreed * 10) and (plGem * 3 + plGold > demandAmount) then
      [*] = ;                              bDemand := true;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     if bSendMessage then
      [*] = ;                     begin
      [*] = ;                        if bDemand then
      [*] = ;                        begin
      [*] = ;                           var gold : Integer = 0;
      [*] = ;                           var gem : Integer = 0;
      [*] = ;
      [*] = ;                           var myGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;                           var myGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;                           if myGem * 4 > myGold then
      [*] = ;                           begin
      [*] = ;                              if plGold >= demandAmount then
      [*] = ;                                 gold := demandAmount
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 gold := plGold;
      [*] = ;                                 gem := (demandAmount - plGold) div 3;
      [*] = ;                              end;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              if plGem >= demandAmount div 3 then
      [*] = ;                                 gem := demandAmount div 3
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 gem := plGem;
      [*] = ;                                 gold := demandAmount - plGem * 3;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           if SameText(cMode, 'cmPlayer') then
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageExchange;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.tradeTake.trade := true;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.tradeTake.gold := gold;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.tradeTake.gem := gem;
      [*] = ;                              _misc_PlMakeDiplomacyText(myPlIndex, i, 12, 0);
      [*] = ;                              messPlInd := i;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][i].arrTalk[6][1] := curTurn;
      [*] = ;                              if polPower < 0 then // if enemy AI player is weaker, agree to demands
      [*] = ;                              begin
      [*] = ;                                 var myGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;                                 var myGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;                                 myGold := myGold + gold;
      [*] = ;                                 myGem := myGem + gem;
      [*] = ;                                 SetIntValueByIndex(gc_map_PLStack_MapUnit_iGold, myGold);
      [*] = ;                                 SetIntValueByIndex(gc_map_PLStack_MapUnit_iGem, myGem);
      [*] = ;
      [*] = ;                                 var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;                                 var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;                                 plGold := plGold - gold;
      [*] = ;                                 plGem := plGem - gem;
      [*] = ;                                 SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;                                 SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;                                 // war demands are so rare that probably they shouldn't count towards irregular income
      [*] = ;                                 //plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;                                 //SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;
      [*] = ;                                 //plGem := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;                                 //SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gem);
      [*] = ;
      [*] = ;                                 gArrDiplomacy[myPlIndex][i].arrTalk[6][0] := 1;
      [*] = ;                              end
      [*] = ;                              else // enemy AI player does not agree to demands
      [*] = ;                                 gArrDiplomacy[myPlIndex][i].arrTalk[6][0] := 0;
      [*] = ;                           end;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           // declare war
      [*] = ;                           if SameText(cMode, 'cmPlayer') then
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyWar;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].answer := 0;
      [*] = ;                              _misc_PlMakeDiplomacyText(myPlIndex, i, 4, 0);
      [*] = ;                              messPlInd := i;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              IntRegister0 := i;
      [*] = ;                              ExecuteState('DeclareWar');
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyWar][1] := curTurn;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               // offer union
      [*] = ;               if treaty and (not bOppMessage) and union and (attitude >= 50) and (polPower > 100) and
      [*] = ;               (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[3][1] > profDiplTimer) then
      [*] = ;               begin
      [*] = ;                  ExecuteState('GetUnionCount');
      [*] = ;                  var myUnionCount : Integer = IntRegister0;
      [*] = ;
      [*] = ;                  PlayerExecuteStateByHandle(plHandle, 'GetUnionCount');
      [*] = ;                  var plUnionCount : Integer = IntRegister0;
      [*] = ;
      [*] = ;                  if (myUnionCount = 0) and (plUnionCount = 0) then
      [*] = ;                  begin
      [*] = ;                     if (gGame.gameType = gc_GameTypeCampaign) and (gCampaign.arrDialogs[103] > 0) and ((profile = 3) or (plProfile = 3)) then
      [*] = ;                     begin
      [*] = ;                        // don't offer union if player has union with Beleth
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        var poss : Integer = 900 + profDiplTimer * 10 - attitude * 3;
      [*] = ;                        var plDiff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle)].basediff;
      [*] = ;
      [*] = ;                        if SameText(cMode, 'cmPlayer') then
      [*] = ;                        poss := poss + plDiff * 20
      [*] = ;                        else
      [*] = ;                        poss := poss - plDiff * 20;
      [*] = ;
      [*] = ;                        if (poss < 20) or (_rand_Random(poss) < 20) then
      [*] = ;                        begin
      [*] = ;                           union := false;
      [*] = ;                           treaty := false;
      [*] = ;
      [*] = ;                           // offer union
      [*] = ;                           if SameText(cMode, 'cmPlayer') then
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyUnion;
      [*] = ;                              _misc_PlMakeDiplomacyText(myPlIndex, i, 6, 0);
      [*] = ;                              messPlInd := i;
      [*] = ;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyUnion][1] := curTurn;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyUnion][0] := 0;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              gArrDiplomacy[myPlIndex][i].treaty := gc_TreatyUnion;
      [*] = ;                              gArrDiplomacy[i][myPlIndex].treaty := gc_TreatyUnion;
      [*] = ;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyUnion][1] := curTurn;
      [*] = ;                              gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyUnion][0] := 1;
      [*] = ;                              gArrDiplomacy[i][myPlIndex].arrTalk[gc_TreatyUnion][1] := curTurn;
      [*] = ;                              gArrDiplomacy[i][myPlIndex].arrTalk[gc_TreatyUnion][0] := 1;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_TreatyUnion : begin
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetUnionCount');
      [*] = ;               var plUnionCount : Integer = IntRegister0;
      [*] = ;
      [*] = ;               // cancel union
      [*] = ;               if (not bOppMessage) and (curTurn - gArrDiplomacy[i][myPlIndex].arrTalk[3][1] > 10) and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[3][1] > 10) and
      [*] = ;                 ((plUnionCount > 1) or (attitude < 30)) then
      [*] = ;               begin
      [*] = ;                  if (gGame.gameType = gc_GameTypeCampaign) and (gCampaign.arrDialogs[103] > 0) and (profile = 3) and (i = gIntRegister_MapMyPlayerIndex) then
      [*] = ;                  begin
      [*] = ;                     // don't cancel union with Beleth in campaign
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     treaty := false;
      [*] = ;                     if SameText(cMode, 'cmPlayer') then
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyCancelUnion;
      [*] = ;                        _misc_PlMakeDiplomacyText(myPlIndex, i, 11, 0);
      [*] = ;                        messPlInd := i;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].treaty := gc_TreatyPeace;
      [*] = ;                        gArrDiplomacy[i][myPlIndex].treaty := gc_TreatyPeace;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if gArrDiplomacy[myPlIndex][i].answer <> 0 then
      [*] = ;         treaty := false;
      [*] = ;
      [*] = ;         if (not bOppMessage) and (gArrDiplomacy[myPlIndex][i].treaty > 1) then
      [*] = ;         begin
      [*] = ;            // cancel trade deal
      [*] = ;            if treaty and gArrDiplomacy[myPlIndex][i].trade.trade then
      [*] = ;            begin
      [*] = ;               var cancel : Boolean = false;
      [*] = ;               var cantTrade : Boolean = false;
      [*] = ;
      [*] = ;               // if refuse to review the deal
      [*] = ;               if (gArrDiplomacy[myPlIndex][i].arrTalk[5][0] = 0) and (gArrDiplomacy[myPlIndex][i].arrTalk[5][1] > 0) and
      [*] = ;               ((gArrDiplomacy[myPlIndex][i].arrTalk[5][1] > gArrDiplomacy[i][myPlIndex].arrTalk[5][1]) or
      [*] = ;               (gArrDiplomacy[i][myPlIndex].arrTalk[5][0] = 0)) then
      [*] = ;               cancel := true;
      [*] = ;
      [*] = ;               // no resource or unnecessary resource
      [*] = ;               for j := 1 to resCount-1 do
      [*] = ;               begin
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  ExecuteState('GetResCount');
      [*] = ;                  var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  if resCount <= 0 then
      [*] = ;                  begin
      [*] = ;                     if gArrDiplomacy[myPlIndex][i].trade.arrResources[j-1] then
      [*] = ;                     begin
      [*] = ;                        cancel := true;
      [*] = ;                        if resCount < 0 then
      [*] = ;                        cantTrade := true;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if resCount > 1 then
      [*] = ;                  begin
      [*] = ;                     if gArrDiplomacy[i][myPlIndex].trade.arrResources[j-1] then
      [*] = ;                     cancel := true;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               // negative income
      [*] = ;               var goldInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;               if (goldInc < 0) and (gArrDiplomacy[myPlIndex][i].trade.gold > 0) then
      [*] = ;               cancel := true;
      [*] = ;
      [*] = ;               var gemInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;               if (gemInc < 0) and (gArrDiplomacy[myPlIndex][i].trade.gem > 0) then
      [*] = ;               cancel := true;
      [*] = ;
      [*] = ;               if cantTrade or (cancel and
      [*] = ;               ((curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[5][1] > 10) or (gArrDiplomacy[myPlIndex][i].arrTalk[5][0] = 0)) and
      [*] = ;               ((curTurn - gArrDiplomacy[i][myPlIndex].arrTalk[5][1] > 10) or (gArrDiplomacy[i][myPlIndex].arrTalk[5][0] = 0))) then
      [*] = ;               begin
      [*] = ;                  treaty := false;
      [*] = ;
      [*] = ;                  if SameText(cMode, 'cmPlayer') then
      [*] = ;                  begin
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := 4;
      [*] = ;                     _misc_PlMakeDiplomacyText(myPlIndex, i, 10, 0);
      [*] = ;                     messPlInd := i;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     _diplomacy_ClearTrade(gArrDiplomacy[myPlIndex][i].trade);
      [*] = ;                     _diplomacy_ClearTrade(gArrDiplomacy[i][myPlIndex].trade);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // review trade deal
      [*] = ;            if treaty and gArrDiplomacy[myPlIndex][i].trade.trade and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[5][1] > 10) and
      [*] = ;            ((curTurn - gArrDiplomacy[i][myPlIndex].arrTalk[5][1] > 10) or (gArrDiplomacy[i][myPlIndex].arrTalk[5][0] = 0)) then
      [*] = ;            begin
      [*] = ;               var give : Integer = gArrDiplomacy[myPlIndex][i].trade.gold + (gArrDiplomacy[myPlIndex][i].trade.gem * 5) div 2;
      [*] = ;               var take : Integer = gArrDiplomacy[i][myPlIndex].trade.gold + (gArrDiplomacy[i][myPlIndex].trade.gem * 5) div 2;
      [*] = ;
      [*] = ;               for j := 1 to resCount-1 do
      [*] = ;               if gArrDiplomacy[myPlIndex][i].trade.arrResources[j-1] then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  MapExecuteState('map.GetResPriceValue');
      [*] = ;                  give := give + IntRegister1;
      [*] = ;               end;
      [*] = ;               for j := 1 to resCount-1 do
      [*] = ;               if gArrDiplomacy[i][myPlIndex].trade.arrResources[j-1] then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  MapExecuteState('map.GetResPriceValue');
      [*] = ;                  take := take + IntRegister1;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if give > take + 10 then
      [*] = ;               begin
      [*] = ;                  treaty := false;
      [*] = ;                  var gold1 : Integer = gArrDiplomacy[myPlIndex][i].trade.gold;
      [*] = ;                  var gold2 : Integer = gArrDiplomacy[i][myPlIndex].trade.gold;
      [*] = ;                  var gem1 : Integer = gArrDiplomacy[myPlIndex][i].trade.gem;
      [*] = ;                  var gem2 : Integer = gArrDiplomacy[i][myPlIndex].trade.gem;
      [*] = ;                  var debt : Integer = give - take;
      [*] = ;
      [*] = ;                  if gold1 > 0 then
      [*] = ;                  begin
      [*] = ;                     gold1 := gold1 - debt;
      [*] = ;                     if gold1 < 0 then
      [*] = ;                     begin
      [*] = ;                        debt := -gold1;
      [*] = ;                        gold1 := 0;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     debt := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (debt > 0) and (gem1 > 0) then
      [*] = ;                  begin
      [*] = ;                     gem1 := gem1 - (debt * 2) div 5;
      [*] = ;                     if gem1 < 0 then
      [*] = ;                     begin
      [*] = ;                        debt := -(gem1 * 5) div 2;
      [*] = ;                        gem1 := 0;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     debt := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (debt > 0) and (gold2 > 0) then
      [*] = ;                  begin
      [*] = ;                     gold2 := gold2 + debt;
      [*] = ;                     debt := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (debt > 0) and (gem2 > 0) then
      [*] = ;                  begin
      [*] = ;                     gem2 := gem2 + (debt * 2) div 5;
      [*] = ;                     debt := 0;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if SameText(cMode, 'cmPlayer') then
      [*] = ;                  begin
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := 2;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeGive.gold := gold1;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeGive.gem := gem1;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeTake.gold := gold2;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeTake.gem := gem2;
      [*] = ;
      [*] = ;                     for j := 0 to gc_MaxTradeResCount-1 do
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.tradeGive.arrResources[j] := gArrDiplomacy[myPlIndex][i].trade.arrResources[j];
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.tradeTake.arrResources[j] := gArrDiplomacy[i][myPlIndex].trade.arrResources[j];
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     _misc_PlMakeDiplomacyText(myPlIndex, i, 9, 0);
      [*] = ;                     messPlInd := i;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].arrTalk[5][0] := 0;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var plGoldInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;                     var plGemInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;
      [*] = ;                     if (plGoldInc > gold2) and (plGemInc > gem2) then
      [*] = ;                     begin
      [*] = ;                        // accept
      [*] = ;                        gArrDiplomacy[myPlIndex][i].trade.gold := gold1;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].trade.gem := gem1;
      [*] = ;                        gArrDiplomacy[i][myPlIndex].trade.gold := gold2;
      [*] = ;                        gArrDiplomacy[i][myPlIndex].trade.gem := gem2;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].arrTalk[5][0] := 1;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        // refuse
      [*] = ;                        gArrDiplomacy[myPlIndex][i].arrTalk[5][0] := 0;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].arrTalk[5][1] := curTurn;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // offer trade
      [*] = ;            if treaty and (attitude >= 10) and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[5][1] > profDiplTimer) and
      [*] = ;            (not gArrDiplomacy[myPlIndex][i].trade.trade) then
      [*] = ;            begin
      [*] = ;               var give : Integer = 0;
      [*] = ;               var take : Integer = 0;
      [*] = ;
      [*] = ;               for j := 1 to resCount-1 do
      [*] = ;               begin
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  ExecuteState('GetResCount');
      [*] = ;                  var myResCount : Integer = IntRegister1;
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  PlayerExecuteStateByHandle(plHandle, 'GetResCount');
      [*] = ;                  var plResCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  if (myResCount > 1) and (plResCount <= 0) then
      [*] = ;                  give := j;
      [*] = ;
      [*] = ;                  if (myResCount <= 0) and (plResCount > 1) then
      [*] = ;                  take := j;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (take > 0) or (give > 0) then
      [*] = ;               begin
      [*] = ;                  treaty := false;
      [*] = ;                  var pay : Integer = 0;
      [*] = ;                  if take > 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := take;
      [*] = ;                     MapExecuteState('map.GetResPriceValue');
      [*] = ;                     pay := pay + IntRegister1;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if give > 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := give;
      [*] = ;                     MapExecuteState('map.GetResPriceValue');
      [*] = ;                     pay := pay - IntRegister1;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var gold : Integer = 0;
      [*] = ;                  var gem : Integer = 0;
      [*] = ;                  var willTrade : Boolean = true;
      [*] = ;
      [*] = ;                  var goldInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;                  var gemInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;
      [*] = ;                  if (pay > 0) then
      [*] = ;                  begin
      [*] = ;                     if goldInc > 20 then
      [*] = ;                     begin
      [*] = ;                        gold := goldInc - 20;
      [*] = ;                        if gold > pay then
      [*] = ;                        gold := pay;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if gold < pay then
      [*] = ;                     begin
      [*] = ;                        if gemInc > 10 then
      [*] = ;                        begin
      [*] = ;                           gem := gemInc - 10;
      [*] = ;                           if gem * 5 > (pay - gold) * 2 then
      [*] = ;                           gem := ((pay - gold) * 2) div 5;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (give = 0) and (gold = 0) and (gem = 0) then
      [*] = ;                     willTrade := false;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if pay < 0 then
      [*] = ;                  begin
      [*] = ;                     if goldInc < gemInc * 5 then
      [*] = ;                     gold := pay
      [*] = ;                     else
      [*] = ;                     gem := (pay * 2) div 5;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if willTrade then
      [*] = ;                  begin
      [*] = ;                     if SameText(cMode, 'cmPlayer') then
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.mType := 2;
      [*] = ;                        if gold > 0 then gArrDiplomacy[myPlIndex][i].message.tradeGive.gold := gold;
      [*] = ;                        if gem > 0 then gArrDiplomacy[myPlIndex][i].message.tradeGive.gem := gem;
      [*] = ;                        if gold < 0 then gArrDiplomacy[myPlIndex][i].message.tradeTake.gold := -gold;
      [*] = ;                        if gem < 0 then gArrDiplomacy[myPlIndex][i].message.tradeTake.gem := -gem;
      [*] = ;
      [*] = ;                        if give > 0 then gArrDiplomacy[myPlIndex][i].message.tradeGive.arrResources[give-1] := true;
      [*] = ;                        if take > 0 then gArrDiplomacy[myPlIndex][i].message.tradeTake.arrResources[take-1] := true;
      [*] = ;
      [*] = ;                        _misc_PlMakeDiplomacyText(myPlIndex, i, 7, 0);
      [*] = ;                        messPlInd := i;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].arrTalk[5][0] := 0;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        var plGoldInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;                        var plGemInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;
      [*] = ;                        if ((gold > 0) or (plGoldInc > Abs(gold))) and ((gem > 0) or (plGemInc > Abs(gem))) then
      [*] = ;                        begin
      [*] = ;                           // accept
      [*] = ;                           gArrDiplomacy[myPlIndex][i].trade.trade := true;
      [*] = ;                           gArrDiplomacy[i][myPlIndex].trade.trade := true;
      [*] = ;
      [*] = ;                           if gold > 0 then gArrDiplomacy[myPlIndex][i].trade.gold := gold;
      [*] = ;                           if gem > 0 then gArrDiplomacy[myPlIndex][i].trade.gem := gem;
      [*] = ;                           if gold < 0 then gArrDiplomacy[myPlIndex][i].trade.gold := -gold;
      [*] = ;                           if gem < 0 then gArrDiplomacy[myPlIndex][i].trade.gem := -gem;
      [*] = ;
      [*] = ;                           if give > 0 then gArrDiplomacy[myPlIndex][i].trade.arrResources[give-1] := true;
      [*] = ;                           if take > 0 then gArrDiplomacy[i][myPlIndex].trade.arrResources[take-1] := true;
      [*] = ;
      [*] = ;                           gArrDiplomacy[myPlIndex][i].arrTalk[5][0] := 1;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        gArrDiplomacy[myPlIndex][i].arrTalk[5][0] := 0;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // offer exchange
      [*] = ;            _rand_ClearRoll;
      [*] = ;            var count : Integer = 0;
      [*] = ;            var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;            var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;            for j := gc_TreasurySize-1 downto gc_TreasurySize-gc_HeroDiplomacyItemsCount do
      [*] = ;            begin
      [*] = ;               var pTreasurySlot : Integer = ParserSelectByHandleByIndex(pMyTreasury, j);
      [*] = ;               var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'ItemID');
      [*] = ;               var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extItems.handle, itemID);
      [*] = ;               var goldCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GoldCost');
      [*] = ;               var gemCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GemCost');
      [*] = ;
      [*] = ;               if (itemID > 0) and ((goldCost = 0) or (goldCost <= plGold)) and ((gemCost = 0) or (gemCost <= plGem)) then
      [*] = ;               begin
      [*] = ;                  gArrRollerN[count] := j;
      [*] = ;                  gArrRollerP[count] := 10;
      [*] = ;                  count := count + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if count > 0 then // sell items to other player
      [*] = ;            begin
      [*] = ;               var trInd : Integer = _rand_Roll(false);
      [*] = ;               var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pMyTreasury, trInd);
      [*] = ;               var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;               var itemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;               if treaty and (attitude >= 0) and exchange and (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[4][1] > profDiplTimer) and
      [*] = ;               (gArrDiplomacy[myPlIndex][i].arrTalk[4][0] <> itemID) then
      [*] = ;               begin
      [*] = ;                  var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extItems.handle, itemID);
      [*] = ;                  var goldCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GoldCost');
      [*] = ;                  var gemCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GemCost');
      [*] = ;
      [*] = ;                  treaty := false;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].arrTalk[4][0] := itemID;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].arrTalk[4][1] := curTurn;
      [*] = ;
      [*] = ;                  if SameText(cMode, 'cmPlayer') then
      [*] = ;                  begin
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := 3;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeTake.gold := goldCost;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeTake.gem := gemCost;
      [*] = ;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeGive.arrItems[0][0] := itemID;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeGive.arrItems[0][1] := itemDur;
      [*] = ;
      [*] = ;                     _misc_PlMakeDiplomacyText(myPlIndex, i, 8, 0);
      [*] = ;                     messPlInd := i;
      [*] = ;                     exchange := false;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := itemID;
      [*] = ;                     PlayerExecuteStateByHandle(plHandle, 'CanSellItem'); // is it worth keeping to the other AI player
      [*] = ;                     var canSell : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                     var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;                     var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;                     if (not canSell) and ((goldCost = 0) or (plGold >= goldCost)) and ((gemCost = 0) or (plGem >= gemCost)) then
      [*] = ;                     begin
      [*] = ;                        // accept
      [*] = ;                        IntRegister0 := itemID;
      [*] = ;                        IntRegister1 := itemDur;
      [*] = ;                        PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;                        if BoolRegister0 then
      [*] = ;                        begin
      [*] = ;                           var myGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;                           var myGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;                           
      [*] = ;                           myGold := myGold + goldCost;
      [*] = ;                           myGem := myGem + gemCost;
      [*] = ;                           SetIntValueByIndex(gc_map_PLStack_MapUnit_iGold, myGold);
      [*] = ;                           SetIntValueByIndex(gc_map_PLStack_MapUnit_iGem, myGem);
      [*] = ;
      [*] = ;                           plGold := plGold - goldCost;
      [*] = ;                           plGem := plGem - gemCost;
      [*] = ;                           SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;                           SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;                           myGold := GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;                           SetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldGain, myGold + goldCost);
      [*] = ;
      [*] = ;                           myGem := GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;                           SetIntValueByIndex(gc_map_PLStack_MapUnit_iGemGain, myGem + gemCost);
      [*] = ;
      [*] = ;                           ParserSetIntValueByKeyByHandle(pTreasuryItem, 'ItemID', 0);
      [*] = ;                           ParserSetIntValueByKeyByHandle(pTreasuryItem, 'ItemDur', 0);
      [*] = ;                           ParserSetBoolValueByKeyByHandle(pTreasuryItem, 'Picked', false);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            var politic : Integer = _rand_Random(profAggro div 2) + _rand_Random(profAggro div 2) + _rand_Random(profAggro div 2);
      [*] = ;            politic := politic + _rand_Random((profDiplTimer-5) * 3) + _rand_Random(20);
      [*] = ;
      [*] = ;            if (politic > 0) and (gArrDiplomacy[myPlIndex][i].treaty = gc_TreatyUnion) then
      [*] = ;            politic := politic div 2;
      [*] = ;
      [*] = ;            if attitude < 0 then
      [*] = ;            politic := politic + _rand_Random(-attitude)
      [*] = ;            else
      [*] = ;            politic := politic - _rand_Random(attitude);
      [*] = ;
      [*] = ;            // offer gift
      [*] = ;            if (i <> warInd) and treaty and (attitude > -10) and exchange and (polPower > politic) and
      [*] = ;            (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[7][1] > profDiplTimer) and
      [*] = ;            (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[6][1] > 10) then
      [*] = ;            begin
      [*] = ;               var gold : Integer = 0;
      [*] = ;               var gem : Integer = 0;
      [*] = ;               var trInd : Integer = -1;
      [*] = ;
      [*] = ;               _rand_ClearRoll;
      [*] = ;               var count : Integer = 0;
      [*] = ;
      [*] = ;               for j := gc_TreasurySize-1 downto gc_TreasurySize-gc_HeroDiplomacyItemsCount do
      [*] = ;               begin
      [*] = ;                  var pTreasurySlot : Integer = ParserSelectByHandleByIndex(pMyTreasury, j);
      [*] = ;                  var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasurySlot, 'ItemID');
      [*] = ;                  var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extItems.handle, itemID);
      [*] = ;                  var goldCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GoldCost');
      [*] = ;                  var gemCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GemCost');
      [*] = ;
      [*] = ;                  if (itemID > 0) and ((goldCost = 0) or (goldCost <= plGold)) and ((gemCost = 0) or (gemCost <= plGem)) then
      [*] = ;                  begin
      [*] = ;                     gArrRollerN[count] := j;
      [*] = ;                     gArrRollerP[count] := 10;
      [*] = ;                     count := count + 1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if count > 0 then
      [*] = ;               trInd := _rand_Roll(false);
      [*] = ;
      [*] = ;               var myGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;               var myGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;               var myGoldLimit : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;               var myGemLimit : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;
      [*] = ;               if myGold > myGoldLimit then
      [*] = ;               gold := Min(100 + curTurn * 2 + _rand_Random(50), myGold - myGoldLimit);
      [*] = ;
      [*] = ;               if myGem > myGemLimit then
      [*] = ;               gem := Min(20 + curTurn div 5 + _rand_Random(10), myGem - myGemLimit);
      [*] = ;
      [*] = ;               if (trInd >= 0) or (gold > 0) or (gem > 0) then
      [*] = ;               begin
      [*] = ;                  var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pMyTreasury, trInd);
      [*] = ;                  var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;                  var itemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].arrTalk[7][1] := curTurn;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].arrTalk[7][0] := itemID;
      [*] = ;
      [*] = ;                  treaty := false;
      [*] = ;                  exchange := false;
      [*] = ;
      [*] = ;                  if SameText(cMode, 'cmPlayer') then
      [*] = ;                  begin
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := 3;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeGive.gold := gold;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.tradeGive.gem := gem;
      [*] = ;
      [*] = ;                     if itemID > 0 then
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.tradeGive.arrItems[0][0] := itemID;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.tradeGive.arrItems[0][1] := itemDur;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     _misc_PlMakeDiplomacyText(myPlIndex, i, 13, 0);
      [*] = ;                     messPlInd := i;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var myGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;                     var myGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;                     myGold := myGold - gold;
      [*] = ;                     myGem := myGem - gem;
      [*] = ;                     SetIntValueByIndex(gc_map_PLStack_MapUnit_iGold, myGold);
      [*] = ;                     SetIntValueByIndex(gc_map_PLStack_MapUnit_iGem, myGem);
      [*] = ;
      [*] = ;                     var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;                     var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;                     plGold := plGold + gold;
      [*] = ;                     plGem := plGem + gem;
      [*] = ;                     SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;                     SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;                     plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;                     SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;
      [*] = ;                     plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;                     SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gem);
      [*] = ;
      [*] = ;                     if itemID > 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := itemID;
      [*] = ;                        IntRegister1 := itemDur;
      [*] = ;                        PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;                        if BoolRegister0 then
      [*] = ;                        begin
      [*] = ;                           ParserSetIntValueByKeyByHandle(pTreasuryItem, 'ItemID', 0);
      [*] = ;                           ParserSetIntValueByKeyByHandle(pTreasuryItem, 'ItemDur', 0);
      [*] = ;                           ParserSetBoolValueByKeyByHandle(pTreasuryItem, 'Picked', false);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if messPlInd >= 0 then
      [*] = ;      begin
      [*] = ;         _diplomacy_Escrow(myPlIndex, i, true);
      [*] = ;         
      [*] = ;         var messPlHandle : Integer = GetPlayerHandleByIndex(messPlInd);
      [*] = ;         var queryID : String = gArrDiplomacy[myPlIndex][messPlInd].message.text;
      [*] = ;         if (queryID <> '') and SameText(GetPlayerControlModeByHandle(messPlHandle), 'cmPlayer') and ((gGame.gameType <> gc_GameTypeLanShard) or (messPlInd = gIntRegister_MapMyPlayerIndex)) then
      [*] = ;         begin
      [*] = ;            var pPlParser : Integer = ParserSelectPlayer(messPlHandle);
      [*] = ;            var pQueries : Integer = ParserSelectByHandleByKey(pPlParser, 'Queries');
      [*] = ;            var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;            ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', myPlIndex);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;            
      [*] = ;            _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][messPlInd].queryWindowMessage, gArrDiplomacy[myPlIndex][messPlInd].message);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

