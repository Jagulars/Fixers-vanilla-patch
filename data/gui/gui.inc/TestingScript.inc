section.begin
   Name = TestingScript
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\TESTINGSCRIPT';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;         
      [*] = ;         var proposePlayerInd : Integer = 0;
      [*] = ;         var answerPlayerInd : Integer = 5;
	  [*] = ;            var messagePlInd : Integer = -1;
      [*] = ;      
      [*] = ;         var proposePlHandle : Integer = GetPlayerHandleByIndex(proposePlayerInd);
      [*] = ;         var answerPlHandle : Integer = GetPlayerHandleByIndex(answerPlayerInd);
      [*] = ;         
      [*] = ;         var myPlIndex : Integer = gIntRegister_MapMyPlayerIndex;
      [*] = ;         var IAmInvolved : Boolean = (proposePlayerInd = myPlIndex) or (answerPlayerInd = myPlIndex);
      [*] = ;gArrDiplomacy[answerPlayerInd][proposePlayerInd].displaypriority := $100;
      [*] = ;//gArrDiplomacy[proposePlayerInd][answerPlayerInd].displaypriority := 1;
      [*] = ;//gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.mtype := 2;
      [*] = ;gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal := 1;
      [*] = ;//gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.treaty := 0;
      [*] = ;//gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.tradeGive.gold := 160;
      [*] = ;//gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.tradeTake.gem := 120;
      [*] = ;         var deal : Integer = gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal;
      [*] = ;         case deal of
      [*] = ;            -3 : begin // proposal withdrawn
      [*] = ;               if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal < 1) then // ensure that already sealed deal cannot be withdrawn because of internet lag
      [*] = ;               begin
      [*] = ;                  gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal := -1;
      [*] = ;               
      [*] = ;                  if answerPlayerInd = myPlIndex then
      [*] = ;                  begin
      [*] = ;                     if ((gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ff) = 0) then // if their proposal has been viewed
      [*] = ;                     begin
      [*] = ;                        _diplomacy_UpdateDisplayPriority(myPlIndex, 1);
      [*] = ;                        gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority := (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ffff00) + 1;
      [*] = ;                     end
      [*] = ;                     else // no need to inform of their withdrawn offer if the offer was never viewed in the first place.
      [*] = ;                        gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority := gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ffff00;
      [*] = ;                     
      [*] = ;                     gArrDiplomacy[answerPlayerInd][proposePlayerInd].answer := 0;
      [*] = ;                     
      [*] = ;                     if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;                     begin
      [*] = ;                        if (gIntRegister_DiplomacyActivePlayerID = proposePlayerInd) then
      [*] = ;                        begin
      [*] = ;                           if (gIntRegister_DiplomacyWindowMode = 4) then // when currently viewing the offer that is now withdrawn
      [*] = ;                           begin
      [*] = ;                              _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                              gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;                           end;
      [*] = ;                           GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;                        end
      [*] = ;                        else // instant blink
      [*] = ;                        if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority > 0) then
      [*] = ;                        begin
      [*] = ;                           var elmPortrait : Integer = GetGUIElementIndexByNameParent('dip_background.round_portrait_'+IntToStr(proposePlayerInd)+'_border', _gui_GetWindow('diplomacy'));
      [*] = ;                           _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(proposePlayerInd), elmPortrait, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;                        end
      [*] = ;                        else // remove blink
      [*] = ;                        if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority = 0) then
      [*] = ;                        begin
      [*] = ;                           var placeHolder : Boolean;
      [*] = ;                           _gui_RemoveBlinkElement('btnDiplomacyPlayer_'+IntToStr(proposePlayerInd), placeHolder);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            -2 : begin // ally peace refused
	  [*] = ;               //var messagePlInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'MessagePlayer');
	  [*] = ;               if messagePlInd >= 0 then
	  [*] = ;               begin
      [*] = ;                  IntRegister0 := proposePlayerInd;
      [*] = ;                  IntRegister1 := answerPlayerInd;
      [*] = ;                  PlayerExecuteStateByHandle(GetPlayerHandleByIndex(messagePlInd), 'RefusePeaceFromUnion');
	  [*] = ;               end;
      [*] = ;            end;
      [*] = ;            -1 : begin // proposal refused
      [*] = ;               IntRegister0 := proposePlayerInd;
      [*] = ;               PlayerExecuteStateByHandle(answerPlHandle, 'HumanCancelDeal');
      [*] = ;            end;
      [*] = ;            0 : begin //receive proposal
      [*] = ;               if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal < 1) and (gArrDiplomacy[answerPlayerInd][proposePlayerInd].message.deal < 1) then // ensure that no new messages are delivered because of internet lag if a deal has already been sealed
      [*] = ;               begin
      [*] = ;                  {var pMessage : Integer = ParserSelectByHandleByKey(pLan, 'Message');
      [*] = ;                  IntRegister0 := 3; // unpack a message
      [*] = ;                  IntRegister1 := pMessage;
      [*] = ;                  IntRegister2 := proposePlayerInd;
      [*] = ;                  IntRegister3 := answerPlayerInd;
      [*] = ;                  GUIExecuteState('VVK.DiplomacyHelper');}
      [*] = ;               
      [*] = ;                  gArrDiplomacy[answerPlayerInd][proposePlayerInd].answer := 0;
      [*] = ;               
      [*] = ;                  if answerPlayerInd = myPlIndex then
      [*] = ;                  begin
      [*] = ;                     _diplomacy_UpdateDisplayPriority(myPlIndex, 1);
      [*] = ;                     gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority := (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ffff00) + 1;
      [*] = ;                  
      [*] = ;                     if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;                     begin
      [*] = ;                        if (gIntRegister_DiplomacyActivePlayerID = proposePlayerInd) then
      [*] = ;                        begin
      [*] = ;                           if (gIntRegister_DiplomacyWindowMode = 4) then // when already viewing their previous offer that is now replaced by a new one
      [*] = ;                           begin
      [*] = ;                              _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                              _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message);
      [*] = ;                              _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.tradeGive);
      [*] = ;                              _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.tradeTake);
      [*] = ;                              //gIntRegister_DiplomacyWindowMode := 4;
      [*] = ;                           end;
      [*] = ;                           GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           var elmPortrait : Integer = GetGUIElementIndexByNameParent('dip_background.round_portrait_'+IntToStr(proposePlayerInd)+'_border', _gui_GetWindow('diplomacy'));
      [*] = ;                           _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(proposePlayerInd), elmPortrait, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  {else
      [*] = ;                  if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.treaty = gc_TreatyPeace) then // If offering peace to a union war ask me if I agree.
      [*] = ;                  begin
      [*] = ;                     var allyPlIndex, enemyPlIndex : Integer = -1;
      [*] = ;                     if (gArrDiplomacy[myPlIndex][proposePlayerInd].treaty = gc_TreatyUnion) then
      [*] = ;                     begin
      [*] = ;                        allyPlIndex := proposePlayerInd;
      [*] = ;                        enemyPlIndex := answerPlayerInd;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (gArrDiplomacy[myPlIndex][answerPlayerInd].treaty = gc_TreatyUnion) then
      [*] = ;                     begin
      [*] = ;                        allyPlIndex := answerPlayerInd;
      [*] = ;                        enemyPlIndex := proposePlayerInd;
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     if (allyPlIndex >= 0) then
      [*] = ;                     begin
      [*] = ;                        _diplomacy_UpdateDisplayPriority(myPlIndex, $10000);
      [*] = ;                        gArrDiplomacy[proposePlayerInd][myPlIndex].displayPriority := (gArrDiplomacy[proposePlayerInd][myPlIndex].displayPriority and $ffff) + $10000;
      [*] = ;                  
      [*] = ;                        if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;                        if (gArrDiplomacy[enemyPlIndex][myPlIndex].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][enemyPlIndex].message.treaty <> gc_TreatyPeace) then
      [*] = ;                        begin
      [*] = ;                           PlayerExecuteStateByHandle(proposePlHandle, 'GetName');
      [*] = ;                           gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;                           gIntRegister_QueryPlayerIndex := proposePlayerInd;
      [*] = ;
      [*] = ;                           PlayerExecuteStateByHandle(answerPlHandle, 'GetName');
      [*] = ;                           gStringRegister_EnemyPlayerNameDiplomacy := StringRegister0;
      [*] = ;                           gIntRegister_QueryPlayerIndex1 := answerPlayerInd;
      [*] = ;              
      [*] = ;                           StringRegister0 := IntToStr(gc_gui_query_diplAskPeaceFromUnion);
      [*] = ;                           GUIExecuteState('map.RequestQueryWindow');
      [*] = ;                        else;
      [*] = ;                     end;
      [*] = ;                  end;}
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            1 : begin // proposal accepted, the deal will be processed when the turn is passed
      [*] = ;               IntRegister0 := proposePlayerInd;
      [*] = ;               PlayerExecuteStateByHandle(answerPlHandle, 'HumanAcceptDeal');
      [*] = ;            end;
      [*] = ;            2 : begin // ally peace accept
	  [*] = ;               //var messagePlInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'MessagePlayer');
	  [*] = ;               if messagePlInd >= 0 then
	  [*] = ;               begin
      [*] = ;                  IntRegister0 := proposePlayerInd;
      [*] = ;                  IntRegister1 := answerPlayerInd;
      [*] = ;                  PlayerExecuteStateByHandle(GetPlayerHandleByIndex(messagePlInd), 'AcceptPeaceFromUnion');
	  [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

