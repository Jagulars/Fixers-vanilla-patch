section.begin
   Name = GetAttitude
   Description : struct.begin
      [*] = ;IntRegister0 - player index
      [*] = ;OUT: IntRegister1 - attitude
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\GETATTITUDE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = (gIntRegister_DiplomacyWindowMode <= 0);
      [*] = ;
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pPlayers : Integer = gPrototypeData.players.handle;
      [*] = ;var pMyProfile : Integer = ParserSelectByHandleByIndex(pPlayers, myPlProfile);
      [*] = ;var pAttitudes : Integer = ParserSelectByHandleByKey(pMyProfile, 'Attitude');
      [*] = ;var profSensitivity : Integer = ParserGetIntValueByKeyByHandle(pMyProfile, 'Sensitivity');
      [*] = ;
      [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;if _log then _gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', PlIndex: '+IntToStr(plIndex)+', Profile: '+IntToStr(myPlProfile)+']',_log_trace);
      [*] = ;
      [*] = ;if SameText(myCMode, 'cmPlayer') and SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   IntRegister0 := gArrDiplomacy[myPlIndex][plIndex].attitude;
      [*] = ;   exit;
      [*] = ;end
      [*] = ;else
      [*] = ;if not bImprovedAI then
      [*] = ;begin
      [*] = ;   profSensitivity := 100;
      [*] = ;end
      [*] = ;else
      [*] = ;if SameText(myCMode, 'cmPC') and SameText(cMode, 'cmPC') then
      [*] = ;begin
      [*] = ;   var pAttitude : Integer = ParserSelectByHandleByIndex(pAttitudes, plProfile);
      [*] = ;   IntRegister1 := ParserGetIntValueByKeyByHandle(pAttitude, 'Value');
      [*] = ;   
      [*] = ;   if _log then _gv_traceState(_log_name+'[Both Players AI, Predefined Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var att : Integer = gArrDiplomacy[myPlIndex][plIndex].attitude;
      [*] = ;if _log then _log_Map('Base Attitude '+IntToStr(att));
      [*] = ;
      [*] = ;if profSensitivity > 0 then
      [*] = ;   att := att * profSensitivity div 100
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister1 := 0;
      [*] = ;   if _log then _gv_traceState(_log_name+'[Sensitivity = 0, Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;if _log then _log_Map('Attitude after sensitivity '+IntToStr(att));
      [*] = ;
      [*] = ;function GetKarmaAttitude(plHnd, plHnd2 : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var karma : Integer = _map_GetPlayerKarma(plHnd);
      [*] = ;   var karma2 : Integer = _map_GetPlayerKarma(plHnd2);
      [*] = ;   if karma >= 20 then
      [*] = ;      Result := Result + ((karma2 div 10) * (karma div 10)) div 5;
      [*] = ;
      [*] = ;   if karma <= -20 then
      [*] = ;      Result := Result + ((karma2 div 10) * (karma div 10)) div 10;
      [*] = ;
      [*] = ;   if (Abs(karma) < 20) and (Abs(karma2) < 20) then
      [*] = ;      Result := Result + 5 - Round(Abs(karma2 - karma)) div 10;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetBuildingAttitude(plHnd, plHnd2 : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   IntRegister0 := 43;
      [*] = ;   PlayerExecuteStateByHandle(plHnd2, 'CheckInnerBuildAbility');
      [*] = ;   Result := Result + IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetPersonalityAttitude(plHnd, plHnd2, pProfile : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var treachery : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Deception');
      [*] = ;   var respectPower : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'RespectPower');
      [*] = ;   
      [*] = ;   if (treachery > 0) or (respectPower > 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetPlayerIndexByHandle(plHnd2);
      [*] = ;      PlayerExecuteStateByHandle(plHnd, 'GetPoliticalPower');
      [*] = ;   
      [*] = ;      if (respectPower > 0) then
      [*] = ;      begin
      [*] = ;         Result := Result + IntRegister1 * respectPower div 100;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      if (treachery > 0) and (IntRegister1 > ParserGetIntValueByKeyByHandle(pProfile, 'TreacheryThreshold')) then // pretend to be friendly when the enemy is powerful
      [*] = ;      begin
      [*] = ;         Result := Result + treachery;
      [*] = ;      end;
      [*] =    ;end;
      [*] = ;end;
      [*] = ;
      [*] = ;att := att + GetKarmaAttitude(myPlHandle, plHandle);
      [*] = ;if _log then _log_Map('Attitude after karma '+IntToStr(att));
      [*] = ;
      [*] = ;// check relations
      [*] = ;var i, thirdPlHnd, thirdPlAtt, thirdPlProfile, pThirdProfile, pThirdAttitudes, myAtt : Integer;
      [*] = ;var thirdPlCMode : String;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if (i <> plIndex) and (i <> myPlIndex) then
      [*] = ;begin
      [*] = ;   thirdPlHnd := GetPlayerHandleByIndex(i);
      [*] = ;   if _plr_IsInGame(thirdPlHnd) then
      [*] = ;   begin
      [*] = ;      if bImprovedAI then
      [*] = ;      begin
      [*] = ;         thirdPlCMode := GetPlayerControlModeByHandle(thirdPlHnd);
      [*] = ;         thirdPlProfile := GetPlayerIntValueIndByHandle(thirdPlHnd, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;         pThirdProfile := ParserSelectByHandleByIndex(pPlayers, thirdPlProfile);
      [*] = ;         pThirdAttitudes := ParserSelectByHandleByKey(pThirdProfile, 'Attitude');
      [*] = ;         
      [*] = ;         if SameText(myCMode, 'cmPC') and SameText(thirdPlCMode, 'cmPC') then
      [*] = ;            myAtt := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pAttitudes, thirdPlProfile), 'Value')
      [*] = ;         else
      [*] = ;         if SameText(myCMode, 'cmPC') then
      [*] = ;         begin
      [*] = ;            myAtt := gArrDiplomacy[myPlIndex][i].attitude * profSensitivity div 100;
      [*] = ;            myAtt := myAtt + GetKarmaAttitude(myPlHandle, thirdPlHnd);
      [*] = ;            myAtt := myAtt + GetBuildingAttitude(myPlHandle, thirdPlHnd);
      [*] = ;            myAtt := myAtt + GetPersonalityAttitude(myPlHandle, thirdPlHnd, pMyProfile);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            myAtt := gArrDiplomacy[myPlIndex][i].attitude;
      [*] = ;         
      [*] = ;         if SameText(thirdPlCMode, 'cmPC') and SameText(cMode, 'cmPC') then
      [*] = ;            thirdPlAtt := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pThirdAttitudes, plProfile), 'Value')
      [*] = ;         else
      [*] = ;         if SameText(thirdPlCMode, 'cmPC') then
      [*] = ;         begin
      [*] = ;            var thirdSensitivity : Integer = ParserGetIntValueByKeyByHandle(pThirdProfile, 'Sensitivity');
      [*] = ;            if thirdSensitivity <= 0 then
      [*] = ;               thirdPlAtt := 0
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               thirdPlAtt := gArrDiplomacy[i][plIndex].attitude * thirdSensitivity div 100;
      [*] = ;               thirdPlAtt := thirdPlAtt + GetKarmaAttitude(thirdPlHnd, plHandle);
      [*] = ;               thirdPlAtt := thirdPlAtt + GetBuildingAttitude(thirdPlHnd, plHandle);
      [*] = ;               thirdPlAtt := thirdPlAtt + GetPersonalityAttitude(thirdPlHnd, plHandle, pThirdProfile);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            thirdPlAtt := gArrDiplomacy[i][plIndex].attitude;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         thirdPlAtt := gArrDiplomacy[i][plIndex].attitude;
      [*] = ;         myAtt := gArrDiplomacy[myPlIndex][i].attitude;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      att := att + (thirdPlAtt div 10) * (myAtt div 50); // popularity among masters I like/dislike
      [*] = ;
      [*] = ;      case gArrDiplomacy[i][plIndex].treaty of
      [*] = ;         gc_TreatyWar : att := att - myAtt div 5;
      [*] = ;         gc_TreatyUnion : att := att + myAtt div 5;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if _log then _log_Map('Attitude after relations '+IntToStr(att));
      [*] = ;
      [*] = ;att := att + GetBuildingAttitude(myPlHandle, plHandle);
      [*] = ;if _log then _log_Map('Attitude after buildings '+IntToStr(att));
      [*] = ;
      [*] = ;if bImprovedAI then
      [*] = ;begin
      [*] = ;   att := att + GetPersonalityAttitude(myPlHandle, plHandle, pMyProfile);
      [*] = ;   if _log then _log_Map('Attitude after personality '+IntToStr(att));
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := att;
      [*] = ;if _log then _gv_traceState(_log_name+'[Result: '+IntToStr(att)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

