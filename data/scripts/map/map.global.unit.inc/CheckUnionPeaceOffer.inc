section.begin
   Name = CheckUnionPeaceOffer
   Description : struct.begin
      [*] = ;IntRegister0 - message writer
      [*] = ;IntRegister1 - peace player index
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CHECKUNIONPEACEOFFER';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var proposePlInd : Integer = IntRegister0;
      [*] = ;var answerPlInd : Integer = IntRegister1;
      [*] = ;var checkAllyAgree : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', ProposePlayer: '+IntToStr(proposePlInd)+', AnswerPlayer: '+IntToStr(answerPlInd)+']',_log_trace);
      [*] = ;
      [*] = ;var isUnionPeaceOffer : Boolean = false;
      [*] = ;var queryAnotherPlayer : Boolean = false;
      [*] = ;var bObstructed : Boolean = false;
      [*] = ;var allyPlIndex, enPlIndex : Integer = -1;
      [*] = ;
      [*] = ;
      [*] = ;if (gArrDiplomacy[proposePlInd][answerPlInd].message.treaty = gc_TreatyPeace) then
      [*] = ;begin
      [*] = ;   MapExecuteState('map.GetActivePlayers');
      [*] = ;   if IntRegister0 > 2 then
      [*] = ;   begin
      [*] = ;      // ensure there is a union
      [*] = ;      var i : Integer;
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      if (gArrDiplomacy[i][proposePlInd].treaty = gc_TreatyUnion) or (gArrDiplomacy[i][answerPlInd].treaty = gc_TreatyUnion) then 
      [*] = ;      begin
      [*] = ;         isUnionPeaceOffer := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;         
      [*] = ;      if isUnionPeaceOffer then
      [*] = ;      begin
      [*] = ;         var waitPlayerPairs, resolvedPlayers : String = '';   
      [*] = ;         var j, otherPlayerInd : Integer;
      [*] = ;   
      [*] = ;         for i := 0 to gGame.map.players-1 do
      [*] = ;         begin
      [*] = ;            otherPlayerInd := -1;
      [*] = ;         
      [*] = ;            if (i = proposePlInd) or (gArrDiplomacy[i][proposePlInd].treaty = gc_TreatyUnion) then
      [*] = ;               otherPlayerInd := answerPlInd
      [*] = ;            else       
      [*] = ;            if (i = answerPlInd) or (gArrDiplomacy[i][answerPlInd].treaty = gc_TreatyUnion) then
      [*] = ;               otherPlayerInd := proposePlInd;
      [*] = ;         
      [*] = ;            if (otherPlayerInd >= 0) then
      [*] = ;            begin
      [*] = ;               var plHandlei : Integer = GetPlayerHandleByIndex(i);
      [*] = ;		       
      [*] = ;               if _plr_IsInGame(plHandlei) then
      [*] = ;               for j := i+1 to gGame.map.players-1 do
      [*] = ;               if (gArrDiplomacy[j][i].treaty = gc_TreatyWar) and ((gArrDiplomacy[j][otherPlayerInd].treaty = gc_TreatyUnion) or (j = otherPlayerInd)) then // i & j are enemies in this particular union war
      [*] = ;               begin
      [*] = ;                  var plHandlej : Integer = GetPlayerHandleByIndex(j);
      [*] = ;                  if _plr_IsInGame(plHandlej) then
      [*] = ;                  begin
      [*] = ;                     var iDealJ : Integer = gArrDiplomacy[i][j].message.deal;
      [*] = ;                     var jDealI : Integer = gArrDiplomacy[j][i].message.deal;
      [*] = ;                     
      [*] = ;                     PlayerExecuteStateByHandle(plHandlei, 'GetName');
      [*] = ;                     var plNamei : String = StringRegister0;
      [*] = ;                     
      [*] = ;                     PlayerExecuteStateByHandle(plHandlej, 'GetName');
      [*] = ;                     var plNamej : String = StringRegister0;
      [*] = ;                     
      [*] = ;                     // check if there is an unanswered peace proposal or no direct proposal at all
	  [*] = ;                     if ((jDealI = 0) or ((jDealI < 0) and (gArrDiplomacy[i][j].message.treaty = gc_TreatyPeace) and (iDealJ = 0))) and
	  [*] = ;                        ((iDealJ = 0) or ((iDealJ < 0) and (gArrDiplomacy[j][i].message.treaty = gc_TreatyPeace) and (jDealI = 0))) then
      [*] = ;                     begin
      [*] = ;                        queryAnotherPlayer := true;
      [*] = ;                        waitPlayerPairs := waitPlayerPairs + gc_gui_BreakLine + plNamei + '  >  <  ' + plNamej;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (jDealI <= 0) and (iDealJ <= 0) then
      [*] = ;                     begin
      [*] = ;                        bObstructed := true;
      [*] = ;                        
      [*] = ;                        resolvedPlayers := resolvedPlayers + gc_gui_BreakLine;
      [*] = ;                        if (jDealI = -1) or (iDealJ = -3) then
      [*] = ;                           resolvedPlayers := resolvedPlayers + '%color(attention)%' + plNamei + '  > %color(default)%'
      [*] = ;                        else
      [*] = ;                           resolvedPlayers := resolvedPlayers + plNamei + '  < ';
      [*] = ;                        
      [*] = ;                        if (iDealJ = -1) or (jDealI = -3) then
      [*] = ;                           resolvedPlayers := resolvedPlayers + '%color(attention)% <  ' + plNamej + '%color(default)%'
      [*] = ;                        else
      [*] = ;                           resolvedPlayers := resolvedPlayers +' >  '+ plNamej;
      [*] = ;                        
      [*] = ;                        
      [*] = ;                        {var agreeStr : String = GetLocaleTableListItemByID('player15','19');
      [*] = ;                        agreeStr := SubStr(agreeStr, 0, StrLength(agreeStr)-1); // remove the dot at the end of the string for neater formatting
      [*] = ;                        var refuseStr : String = GetLocaleTableListItemByID('player15','16'); 
      [*] = ;                        refuseStr := SubStr(refuseStr, 0, StrLength(refuseStr)-1);
      [*] = ;                        
      [*] = ;                        resolvedPlayers := resolvedPlayers + gc_gui_BreakLine + '(';
      [*] = ;                           
      [*] = ;                        if (jDealI = -1) or (iDealJ = -3) then
      [*] = ;                           resolvedPlayers := resolvedPlayers + refuseStr  // i refused
      [*] = ;                        else
      [*] = ;                           resolvedPlayers := resolvedPlayers + agreeStr; // i agrees
      [*] = ;                           
      [*] = ;                        resolvedPlayers := resolvedPlayers + ') ' +plNamei + '  > <  ' + plNamej + ' (';
      [*] = ;                        
      [*] = ;                        if (iDealJ = -1) or (jDealI = -3) then
      [*] = ;                           resolvedPlayers := resolvedPlayers + refuseStr  // j refused
      [*] = ;                        else
      [*] = ;                           resolvedPlayers := resolvedPlayers + agreeStr; // j agrees
      [*] = ;                           
      [*] = ;                        resolvedPlayers := resolvedPlayers + ')';}
      [*] = ;                        
      [*] = ;                        if (not checkAllyAgree) then
      [*] = ;                        begin
      [*] = ;                           if (gArrDiplomacy[j][myPlIndex].treaty = gc_TreatyUnion) and ((iDealJ = -1) or (jDealI = -3)) then  // my ally j has refused
      [*] = ;                           begin
      [*] = ;                              allyPlIndex := j;
      [*] = ;                              enPlIndex := i;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           if (gArrDiplomacy[i][myPlIndex].treaty = gc_TreatyUnion) and ((jDealI = -1) or (iDealJ = -3)) then // my ally i has refused
      [*] = ;                           begin
      [*] = ;                              allyPlIndex := i;
      [*] = ;                              enPlIndex := j;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (jDealI > 0) or (iDealJ > 0) then
      [*] = ;                     begin
      [*] = ;                        resolvedPlayers := resolvedPlayers + gc_gui_BreakLine + plNamei + '  < '+GetLocaleTableListItemByID('gui','160')+' >  ' + plNamej;
      [*] = ;                        
      [*] = ;                        if checkAllyAgree then
      [*] = ;                        begin
      [*] = ;                           if (gArrDiplomacy[j][myPlIndex].treaty = gc_TreatyUnion) then  // my ally j has agreed
      [*] = ;                           begin
      [*] = ;                              allyPlIndex := j;
      [*] = ;                              enPlIndex := i;
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           if (gArrDiplomacy[i][myPlIndex].treaty = gc_TreatyUnion) then // my ally i has agreed
      [*] = ;                           begin
      [*] = ;                              allyPlIndex := i;
      [*] = ;                              enPlIndex := j;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gStringRegister_PlayersList := '';
      [*] = ;         
      [*] = ;         if waitPlayerPairs <> '' then
      [*] = ;            gStringRegister_PlayersList := gc_gui_BreakLine + waitPlayerPairs
      [*] = ;         else
      [*] = ;            gStringRegister_PlayersList := gc_gui_BreakLine + resolvedPlayers;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;{var i, plInd : Integer;
      [*] = ;var flip : Integer = 0;
      [*] = ;if myPlIndex > proposePlInd then
      [*] = ;   flip := gGame.map.players;
      [*] = ;   
      [*] = ;for i := myPlIndex+1 to proposePlInd-1 + flip do // iterate each player starting from proposer and ending at proposer
      [*] = ;begin
      [*] = ;   if i > gGame.map.players-1 then
      [*] = ;      plInd := i - gGame.map.players
      [*] = ;   else
      [*] = ;      plInd := i;
      [*] = ;   
      [*] = ;   _log_Map(_log_name+' Checking Player '+IntToStr(plInd));
      [*] = ;end;}
      [*] = ;   
      [*] = ;BoolRegister1 := isUnionPeaceOffer;
      [*] = ;BoolRegister2 := queryAnotherPlayer;
      [*] = ;BoolRegister3 := bObstructed;
      [*] = ;IntRegister0 := allyPlIndex;
      [*] = ;IntRegister1 := enPlIndex;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name+'[Union: '+BoolToStr(isUnionPeaceOffer)+', QAP: '+BoolToStr(queryAnotherPlayer)+', Rejected: '+BoolToStr(bObstructed)+', Ally: '+IntToStr(allyPlIndex)+', Enemy: '+IntToStr(enPlIndex)+']',$1000000 or _log_trace);
   struct.end
section.end

