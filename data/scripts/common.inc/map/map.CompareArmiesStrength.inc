section.begin
   Name = map.CompareArmiesStrength
   Description : struct.begin
      [*] = ;IntRegister0 - first army parser
      [*] = ;IntRegister1 - first hero handle
      [*] = ;IntRegister2 - first player handle
      [*] = ;IntRegister3 - second army parser
      [*] = ;IntRegister4 - second hero handle
      [*] = ;IntRegister5 - second player handle
      [*] = ;OUT: IntRegister6- comparison result
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;// returns 100 if armies strengths are equal, if returns > 100 then first army is stronger
      [*] = ;var pArmyUnits1 : Integer = IntRegister0;
      [*] = ;var heroHandle1 : Integer = IntRegister1;
      [*] = ;var plHandle1 : Integer = IntRegister2;
      [*] = ;var pArmyUnits2 : Integer = IntRegister3;
      [*] = ;var heroHandle2 : Integer = IntRegister4;
      [*] = ;var plHandle2 : Integer = IntRegister5;
      [*] = ;
      [*] = ;// TODO: insert checking bVerySmartAI
      [*] = ;//	if (bVerySmartAI)
      [*] = ;//	{return CompareStrength1(Hero1,Hero2);};
      [*] = ;var value : Float = 0;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;function GetProperty(pUnit, pArmyUnits, propIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := pUnit;
      [*] = ;   IntRegister1 := pArmyUnits;
      [*] = ;   IntRegister2 := propIndex;
      [*] = ;   ExecuteState('GetUnitPropertyByParser');
      [*] = ;   Result := IntRegister3;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckAbility(pArmyUnit, heroHandle, abilID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := 0;
      [*] = ;   IntRegister1 := pArmyUnit;
      [*] = ;   IntRegister2 := heroHandle;
      [*] = ;   IntRegister3 := abilID;
      [*] = ;   ExecuteState('CheckUnitAbility');
      [*] = ;   Result := IntRegister4;
      [*] = ;end;
      [*] = ;
      [*] = ;if ParserGetCountByHandle(pArmyUnits2) = 0 then
      [*] = ;value := 300
      [*] = ;else
      [*] = ;begin
      [*] = ;   var str : array [0..1] of Integer;
      [*] = ;   var def : array [0..1] of Integer;
      [*] = ;   var res : array [0..1] of Integer;
      [*] = ;   var rDef : array [0..1] of Integer;
      [*] = ;   var spd : array [0..1] of Integer;
      [*] = ;   var cAtt : array [0..1] of Integer;
      [*] = ;   var unitsParams : array [0..200] of array [0..11] of Integer;
      [*] = ;   var unitsNum,spellCount1,spellCount2,heroLevel1,heroLevel2 :Integer;
      [*] = ;   var spellCount,heroLevel :Integer;
      [*] = ;   unitsNum:=0;
      [*] = ;   for i := 0 to 1 do
      [*] = ;   begin
      [*] = ;      var pArmyUnits : Integer;
      [*] = ;      var heroHandle : Integer;
      [*] = ;      if i = 0 then
      [*] = ;      begin
      [*] = ;         pArmyUnits := pArmyUnits1;
      [*] = ;         heroHandle := heroHandle1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         pArmyUnits := pArmyUnits2;
      [*] = ;         heroHandle := heroHandle2;
      [*] = ;      end;
      [*] = ;      heroLevel := GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;      spellCount := 0;
      [*] = ;      for k := 1 to 4 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := k;
      [*] = ;         GameObjectExecuteStateByHandle(heroHandle, 'GetSpellSlots');
      [*] = ;         spellCount := spellCount + IntRegister1;
      [*] = ;      end;
      [*] = ;      if i = 0 then
      [*] = ;      begin
      [*] = ;         spellCount1 := spellCount;
      [*] = ;         heroLevel1 := heroLevel;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         spellCount2 := spellCount;
      [*] = ;         heroLevel2 := heroLevel;
      [*] = ;      end;
      [*] = ;
      [*] = ;      str[i] := 0;
      [*] = ;      def[i] := 0;
      [*] = ;      res[i] := 0;
      [*] = ;      rDef[i] := 0;
      [*] = ;      spd[i] := 0;
      [*] = ;      cAtt[i] := 0;
      [*] = ;
      [*] = ;      var armyCount : Integer = 0;
      [*] = ;      for j := 0 to ParserGetCountByHandle(pArmyUnits) - 1 do
      [*] = ;      begin
      [*] = ;         var pArmyUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, j);
      [*] = ;         var isHero : Boolean = ParserGetBoolValueByKeyByHandle(pArmyUnit, 'IsHero');
      [*] = ;         var curLife : Integer;
      [*] = ;         unitsParams[unitsNum,0] := ParserGetIntValueByKeyByHandle(pArmyUnit, 'HeroClass1');
      [*] = ;         unitsParams[unitsNum,1] := GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iShootingRange);
      [*] = ;         unitsParams[unitsNum,2] := GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iRangedAttack);
      [*] = ;         unitsParams[unitsNum,3] := GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iMaxAmmo);
      [*] = ;         unitsParams[unitsNum,4] := GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iAttack);
      [*] = ;         unitsParams[unitsNum,5] := GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iDefence);
      [*] = ;         unitsParams[unitsNum,6] := CheckAbility(pArmyUnit, heroHandle, 17);
      [*] = ;         unitsParams[unitsNum,7] := CheckAbility(pArmyUnit, heroHandle, 28);
      [*] = ;         unitsParams[unitsNum,8] := CheckAbility(pArmyUnit, heroHandle, 24);
      [*] = ;         unitsParams[unitsNum,9] := CheckAbility(pArmyUnit, heroHandle, 39);
      [*] = ;         unitsParams[unitsNum,10] := CheckAbility(pArmyUnit, heroHandle, 27);
      [*] = ;         unitsParams[unitsNum,11] := CheckAbility(pArmyUnit, heroHandle, 26);
      [*] = ;
      [*] = ;         if not isHero then
      [*] = ;         curLife := ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            curLife := GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iCurHP);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (curLife > 0) then
      [*] = ;         begin
      [*] = ;            def[i] := def[i] + GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iDefence);
      [*] = ;            rDef[i] := rDef[i] + GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iRangedDefence);
      [*] = ;            res[i] := res[i] + GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iResist);
      [*] = ;            var tmpSpeed : Integer = GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iSpeed);
      [*] = ;            if tmpSpeed < 1 then
      [*] = ;            tmpSpeed := 1;
      [*] = ;
      [*] = ;            spd[i] := spd[i] + tmpSpeed;
      [*] = ;            cAtt[i] := cAtt[i] + GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iCounterAttack);
      [*] = ;            //str[i] := str[i] + GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iCurLife);
      [*] = ;            str[i] := str[i] + curLife;
      [*] = ;
      [*] = ;            armyCount := armyCount + 1;
      [*] = ;         end;
      [*] = ;         unitsNum:=unitsNum+1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if armyCount > 0 then
      [*] = ;      begin
      [*] = ;         def[i] := def[i] div armyCount;
      [*] = ;         rDef[i] := rDef[i] div armyCount;
      [*] = ;         res[i] := res[i] div armyCount;
      [*] = ;         spd[i] := spd[i] div armyCount;
      [*] = ;         cAtt[i] := Floor(cAtt[i] * 0.8 / armyCount);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // advantage strong AIs beyond weak ones
      [*] = ;   var cMode1 : String = GetPlayerControlModeByHandle(plHandle1);
      [*] = ;   var cMode2 : String = GetPlayerControlModeByHandle(plHandle2);
      [*] = ;
      [*] = ;   if (SameText(cMode1, 'cmPC') or (plHandle1=0)) and (SameText(cMode2, 'cmPC') or (plHandle2=0)) then
      [*] = ;   begin
      [*] = ;      var plDiff1 : Integer = 0;//GetPlayerIntValueIndByHandle(plHandle1, gc_map_PLStack_MapUnit_iDifficulty);
      [*] = ;      if (plHandle1<>0) then
      [*] = ;      plDiff1 := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle1)].basediff;
      [*] = ;      var plDiff2 : Integer = 0;//GetPlayerIntValueIndByHandle(plHandle2, gc_map_PLStack_MapUnit_iDifficulty);
      [*] = ;      if (plHandle2<>0) then
      [*] = ;      plDiff2 := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(plHandle2)].basediff;
      [*] = ;
      [*] = ;      if plDiff1 > plDiff2 then
      [*] = ;      str[1] := Floor(str[1] * (10 - plDiff1 + plDiff2) / 10)
      [*] = ;      else
      [*] = ;      str[0] := Floor(str[0] * (10 - plDiff2 + plDiff1) / 10);
      [*] = ;   end;
      [*] = ;
      [*] = ;   {ErrorLog('str[0] = ' + IntToStr(str[0]));
      [*] = ;   ErrorLog('str[1] = ' + IntToStr(str[1]));
      [*] = ;   ErrorLog('def[0] = ' + IntToStr(def[0]));
      [*] = ;   ErrorLog('def[1] = ' + IntToStr(def[1]));
      [*] = ;   ErrorLog('res[0] = ' + IntToStr(res[0]));
      [*] = ;   ErrorLog('res[1] = ' + IntToStr(res[1]));
      [*] = ;   ErrorLog('rDef[0] = ' + IntToStr(rDef[0]));
      [*] = ;   ErrorLog('rDef[1] = ' + IntToStr(rDef[1]));
      [*] = ;   ErrorLog('spd[0] = ' + IntToStr(spd[0]));
      [*] = ;   ErrorLog('spd[1] = ' + IntToStr(spd[1]));
      [*] = ;   ErrorLog('cAtt[0] = ' + IntToStr(cAtt[0]));
      [*] = ;   ErrorLog('cAtt[1] = ' + IntToStr(cAtt[1]));
      [*] = ;   {}
      [*] = ;   var turn : Integer = 0;
      [*] = ;   while (str[0] > 0) and (str[1] > 0) and (turn < 50) do
      [*] = ;   begin
      [*] = ;      //ErrorLog('str[0] = ' + IntToStr(str[0]));
      [*] = ;      //ErrorLog('str[1] = ' + IntToStr(str[1]));
      [*] = ;      unitsNum:=0;
      [*] = ;      for i := 0 to 1 do
      [*] = ;      begin
      [*] = ;         var pArmyUnits : Integer;
      [*] = ;         var heroHandle : Integer;
      [*] = ;
      [*] = ;         if i = 0 then
      [*] = ;         begin
      [*] = ;            pArmyUnits := pArmyUnits1;
      [*] = ;            heroHandle := heroHandle1;
      [*] = ;            spellCount := spellCount1;
      [*] = ;            heroLevel := heroLevel1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            pArmyUnits := pArmyUnits2;
      [*] = ;            heroHandle := heroHandle2;
      [*] = ;            spellCount := spellCount2;
      [*] = ;            heroLevel := heroLevel2;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for j := 0 to ParserGetCountByHandle(pArmyUnits)-1 do
      [*] = ;         begin
      [*] = ;            //ErrorLog('str[0] = ' + IntToStr(str[0]));
      [*] = ;            //ErrorLog('str[1] = ' + IntToStr(str[1]));
      [*] = ;            var pArmyUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, j);
      [*] = ;            var class1 : Integer = unitsParams[unitsNum,0]; //ParserGetIntValueByKeyByHandle(pArmyUnit, 'HeroClass1');
      [*] = ;
      [*] = ;
      [*] = ;            if (j = 0) and (class1 = 4) and (turn < spellCount) then
      [*] = ;            // simulating healing or spell damage
      [*] = ;            begin
      [*] = ;               heroLevel := heroLevel - 1;
      [*] = ;
      [*] = ;               if turn mod 3 = 0 then
      [*] = ;               str[i] := str[i] + heroLevel + 3
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var damage : Integer = heroLevel + 3 - res[1-i];
      [*] = ;                  if damage > 0 then
      [*] = ;                  str[1-i] := str[1-i] - damage;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var shRange : Integer = unitsParams[unitsNum,1]; //GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iShootingRange);
      [*] = ;               var rAttack : Integer = unitsParams[unitsNum,2]; //GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iRangedAttack);
      [*] = ;               var ammo : Integer = unitsParams[unitsNum,3]; //GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iMaxAmmo);
      [*] = ;
      [*] = ;               if (7 - turn * (spd[0] + spd[1]) <= shRange) and (ammo + (7 - shRange) div (spd[0] + spd[1]) > turn) then
      [*] = ;               // simulating ranged attack
      [*] = ;               begin
      [*] = ;                  var deff : Integer = rDef[1-i];
      [*] = ;
      [*] = ;                  if unitsParams[unitsNum,6] > 0 then //17
      [*] = ;                  deff := deff div 2;
      [*] = ;
      [*] = ;                  if unitsParams[unitsNum,7] > 0 then //28
      [*] = ;                  deff := res[1-i];
      [*] = ;
      [*] = ;                  if rAttack > deff then
      [*] = ;                  str[1-i] := str[1-i] - (rAttack - deff)
      [*] = ;                  else
      [*] = ;                  str[i] := str[i] + unitsParams[unitsNum,8];//24
      [*] = ;               end
      [*] = ;               else
      [*] = ;               // simulating melee attack
      [*] = ;               begin
      [*] = ;                  if turn * (spd[0] + spd[1]) >= 4 then
      [*] = ;                  begin
      [*] = ;                     var deff : Integer = def[1-i];
      [*] = ;
      [*] = ;                     if unitsParams[unitsNum,9] > 0 then //39
      [*] = ;                     deff := deff div 2;
      [*] = ;                     if unitsParams[unitsNum,10] > 0 then //27
      [*] = ;                     deff := res[1-i];
      [*] = ;
      [*] = ;                     var attack : Integer = unitsParams[unitsNum,4]; //GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iAttack);
      [*] = ;                     if attack > deff then
      [*] = ;                     str[1-i] := str[1-i] - (attack - deff);
      [*] = ;
      [*] = ;                     if unitsParams[unitsNum,11] = 0 then //26
      [*] = ;                     begin
      [*] = ;                        deff := unitsParams[unitsNum,5]; //GetProperty(pArmyUnit, pArmyUnits, gc_battle_unit_iDefence);
      [*] = ;                        if cAtt[1-i] > deff then
      [*] = ;                        str[i] := str[i] - (cAtt[1-i] - deff);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            unitsNum:=unitsNum+1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      turn := turn + 1;
      [*] = ;   end;
      [*] = ;   //Log('str[0] = ' + IntToStr(str[0]));
      [*] = ;   //Log('str[1] = ' + IntToStr(str[1]));
      [*] = ;   value := 95 + str[0] - str[1];
      [*] = ;
      [*] = ;   var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;   if bImprovedAI and (gIntRegister_MapCurPlayerIndex = GetPlayerIndexByHandle(plHandle1)) and SameText(cMode1, 'cmPC') then
      [*] = ;   begin
      [*] = ;      var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle1, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;      var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, plProfile);
      [*] = ;      value := value + ParserGetIntValueByKeyByHandle(pProfile, 'Reckless');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if value > 300 then
      [*] = ;   value := 300;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister6 := Round(value);
   struct.end
section.end

