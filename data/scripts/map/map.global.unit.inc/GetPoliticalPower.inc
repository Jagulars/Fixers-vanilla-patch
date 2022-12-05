section.begin
   Name = GetPoliticalPower
   Description : struct.begin
      [*] = ;IntRegister0 - player index
      [*] = ;OUT: IntRegister1 - political power
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\GETPOLITICALPOWER';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = (gIntRegister_DiplomacyWindowMode <= 0);
      [*] = ;
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[plIndex].basediff;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(plHandle);
	  [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;var pPlCastle : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pPlCastle, 'DummyUID');
      [*] = ;var plDummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlDiff : Integer = gGame.arrplayerdifficulty[myPlIndex].basediff;
      [*] = ;var myPlProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, myPlProfile);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', PlIndex: '+IntToStr(plIndex)+', Profile: '+IntToStr(myPlProfile)+']',_log_trace);
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pMyCastle : Integer = IntRegister0;
      [*] = ;dummyUID := ParserGetIntValueByKeyByHandle(pPlCastle, 'DummyUID');
      [*] = ;var myDummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var power : Integer = 0;
      [*] = ;//var power : Integer = gArrDiplomacy[myPlIndex][plIndex].power;
      [*] = ;//if _log then _log_Map('Base power '+IntToStr(power));
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;var myGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var myGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;var myGoldLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;var myGemLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;var plGoldInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;var plGemInc : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;
      [*] = ;// political situation
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if (i <> myPlIndex) and (i <> plIndex) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then
      [*] = ;begin
      [*] = ;   case gArrDiplomacy[myPlIndex][i].treaty of
      [*] = ;      gc_TreatyWar : power := power + 20;
      [*] = ;      gc_TreatyUnion : power := power - 30;
      [*] = ;   end;
      [*] = ;
      [*] = ;   case gArrDiplomacy[plIndex][i].treaty of
      [*] = ;      gc_TreatyWar : power := power - 20;
      [*] = ;      gc_TreatyUnion : power := power + 30;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if _log then _log_Map('Power after political situation '+IntToStr(power));
      [*] = ;
      [*] = ;
      [*] = ;// difficulty level
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;   power := power - myPlDiff * 3
      [*] = ;else
      [*] = ;   power := power + (plDiff - myPlDiff) * 3;
      [*] = ;if _log then _log_Map('Power after difficulty '+IntToStr(power));
      [*] = ;
      [*] = ;// attitudes (better to have this script get pure power separate from personal opinion)
      [*] = ;if (not bImprovedAI) then
      [*] = ;begin
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('GetAttitude');
      [*] = ;   power := power + IntRegister1 div 3;
      [*] = ;   if _log then _log_Map('Power after attitude '+IntToStr(power));
      [*] = ;end;
      [*] = ;
      [*] = ;// province count
      [*] = ;ExecuteState('GetProvinceCount');
      [*] = ;power := power - IntRegister0;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetProvinceCount');
      [*] = ;power := power + IntRegister0;
      [*] = ;if _log then _log_Map('Power after provinces '+IntToStr(power));
      [*] = ;
      [*] = ;// siege of the castle
      [*] = ;GameObjectExecuteStateByHandle(myDummyHandle, 'IsUnderSiege');
      [*] = ;var bUnderSiege : Boolean = BoolRegister0;
      [*] = ;if IntRegister0 = plHandle then
      [*] = ;   power := power + 50;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(plDummyHandle, 'IsUnderSiege');
      [*] = ;var bPlUnderSiege : Boolean = BoolRegister0;
      [*] = ;if IntRegister0 = myPlHandle then
      [*] = ;   power := power - 250;
      [*] = ;if _log then _log_Map('Power after siege situation '+IntToStr(power));
      [*] = ;
      [*] = ;// distance to the castle
      [*] = ;var plBorder : Boolean = false;
      [*] = ;var myBorder : Boolean = false;
      [*] = ;for i := 0 to 5 do
      [*] = ;begin
      [*] = ;   IntRegister0 := pPlCastle;
      [*] = ;   IntRegister1 := i;
      [*] = ;   MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;   var pProvince : Integer = IntRegister2;
      [*] = ;
      [*] = ;   if pProvince <> 0 then
      [*] = ;   begin
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      if SameText(provPlName, myPlName) then
      [*] = ;         plBorder := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := pMyCastle;
      [*] = ;   IntRegister1 := i;
      [*] = ;   MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;   pProvince := IntRegister2;
      [*] = ;
      [*] = ;   if pProvince <> 0 then
      [*] = ;   begin
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      if SameText(provPlName, plName) then
      [*] = ;         myBorder := true;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if myBorder then
      [*] = ;   power := power + 30;
      [*] = ;if plBorder then
      [*] = ;   power := power - 100;
      [*] = ;if _log then _log_Map('Power after border check '+IntToStr(power));
      [*] = ;
      [*] = ;// available heroes
      [*] = ;var myHighestPowerHero, enHighestPowerHero : Integer = 0;
      [*] = ;var goHandle, AIPower, level : Integer;
      [*] = ;var bDead : Boolean;
      [*] = ;for i := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;begin
      [*] = ;   goHandle := GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   begin
      [*] = ;      AIPower := 0;
      [*] = ;      bDead := GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;
      [*] = ;      if bImprovedAI then
      [*] = ;      begin
      [*] = ;         if (not bDead) or ((not bUnderSiege) and (not myBorder)) then
      [*] = ;         begin
      [*] = ;            AIPower := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;         
      [*] = ;            if (myGold < myGoldLimit) then
      [*] = ;               AIPower := Max(0, Round(AIPower * (myGold / myGoldLimit)));
      [*] = ;         
      [*] = ;            if (myGem < myGemLimit) and ((GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd1) = 4) 
      [*] = ;            or ((GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iClassInd2) = 4) and (GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iMagic) >= 4))) then
      [*] = ;               AIPower := Max(0, Min(AIPower, Round(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAIPower) * (myGem / myGemLimit))));
      [*] = ;         
      [*] = ;            power := power - 1 - AIPower;
      [*] = ;            if AIPower > myHighestPowerHero then
      [*] = ;               myHighestPowerHero := AIPower;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if not bDead then
      [*] = ;      begin
      [*] = ;         AIPower := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel) div 2;
      [*] = ;         power := power - 1 - AIPower;
      [*] = ;      end;
      [*] = ;      if _log then _log_Map('My Hero, index: '+IntToStr(i)+', AIPower: '+IntToStr(AIPower)+', Available: '+BoolToStr(not bDead));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;begin
      [*] = ;   goHandle := GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;   begin
      [*] = ;      AIPower := 0;
      [*] = ;      bDead := GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;
      [*] = ;      if bImprovedAI then
      [*] = ;      begin
      [*] = ;         if (not bDead) or ((not bPlUnderSiege) and (not plBorder)) then
      [*] = ;         begin
      [*] = ;            if bDead then
      [*] = ;            begin
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetResurrectPrice');
      [*] = ;               if (plGold >= IntRegister0) and (plGem >= IntRegister1) and (((plGoldInc > 0) or (plGold >= IntRegister0 * 3)) and ((plGemInc > 0) or (plGem >= IntRegister1 * 3))) then
      [*] = ;               begin
      [*] = ;                  bDead := false;  // consider the hero alive if there's buffer zone and resources to resurrect it.
      [*] = ;                  plGold := plGold - IntRegister0;
      [*] = ;                  plGem := plGem - IntRegister1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         
      [*] = ;            if not bDead then
      [*] = ;            begin
      [*] = ;               AIPower := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;               power := power + 1 + AIPower;
      [*] = ;               if AIPower > enHighestPowerHero then
      [*] = ;                  enHighestPowerHero := AIPower;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if not bDead then
      [*] = ;      begin
      [*] = ;         AIPower := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel) div 2;
      [*] = ;         power := power + 1 + AIPower;
      [*] = ;      end;
      [*] = ;      if _log then _log_Map('Enemy Hero, index: '+IntToStr(i)+', AIPower: '+IntToStr(AIPower)+', Available: '+BoolToStr(not bDead));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if bImprovedAI then
      [*] = ;begin
      [*] = ;   var bestHeroDisparity : Integer = enHighestPowerHero - myHighestPowerHero;
      [*] = ;   if bestHeroDisparity > 0 then // my hero is weaker
      [*] = ;      power := power + (bestHeroDisparity * bestHeroDisparity) div 2
      [*] = ;   else
      [*] = ;   if bestHeroDisparity < 0 then // enemy hero is weaker
      [*] = ;      power := power - (bestHeroDisparity * bestHeroDisparity) div 2;
      [*] = ;   if _log then _log_Map('Power after hero disparity '+IntToStr(power));
      [*] = ;   
      [*] = ;   var pride : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Pride');
      [*] = ;   if (pride <> 0) then
      [*] = ;   begin
      [*] = ;      power := power - pride; // Prideful masters always consider you to be weaker than you are. Negative value can be used for submissiveness.
      [*] = ;      if _log then _log_Map('Power after pride '+IntToStr(power));
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var deception : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Deception');
      [*] = ;   if (deception > 0) and (power <= ParserGetIntValueByKeyByHandle(pProfile, 'TreacheryThreshold')) then
      [*] = ;   begin
      [*] = ;      power := power - deception;
      [*] = ;      if _log then _log_Map('Power after treachery '+IntToStr(power));
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if _log then _log_Map('Power after hero disparity '+IntToStr(power));
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Result: '+IntToStr(power)+']',$1000000 or _log_trace);
      [*] = ;IntRegister1 := power;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

