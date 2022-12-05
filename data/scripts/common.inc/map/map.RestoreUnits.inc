section.begin
   Name = map.RestoreUnits
   Description : struct.begin
      [*] = ;IntRegister0 - army parser
      [*] = ;IntRegister1 - hero handle
      [*] = ;IntRegister2 - province bonus
	   [*] = ;IntRegister3 - original army
	   [*] = ;IntRegister4 - province dummy UID
      [*] = ;BoolRegister0 - is home land
      [*] = ;BoolRegister1 - is raise units
      [*] = ;OUT: BoolRegister2 - need restore // for heroes won't work properly
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var pArmyUnits : Integer = IntRegister0;
      [*] = ;var heroHandle : Integer = IntRegister1;
      [*] = ;var provBonus : Integer = IntRegister2;
	   [*] = ;var pOrigArmy : Integer = IntRegister3;
      [*] = ;var bHomeLand : Boolean = BoolRegister0;
      [*] = ;var bRaise : Boolean = BoolRegister1;
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;	  
      [*] = ;function GetSquadHealBonus : Integer;
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pArmyUnits)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pArmyUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;
      [*] = ;      if (i = 0) and (heroHandle <> 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 24;
      [*] = ;         GameObjectExecuteStateByHandle(heroHandle, 'CheckAbility');
      [*] = ;         if IntRegister1 > 0 then
      [*] = ;            Result := Result + 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         IntRegister1 := pArmyUnit;
      [*] = ;         IntRegister2 := heroHandle;
      [*] = ;         IntRegister3 := 24;
      [*] = ;         ExecuteState('CheckUnitAbility');
      [*] = ;         if IntRegister4 > 0 then
      [*] = ;            Result := Result + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if pArmyUnits = 0 then
      [*] = ;   exit;
      [*] = ;
      [*] = ;
      [*] = ;var squadHeal : Integer = GetSquadHealBonus();
	  [*] = ;//var curArmyIDs : array [0..gc_MaxArmyCount] of Integer;
	  [*] = ;var curArmyIDs : array [0..gc_MaxArmyCount] of Integer;
      [*] = ;for i := 0 to gc_MaxArmyCount-1 do
      [*] = ;   curArmyIDs[i] := 0;
      [*] = ;
      [*] = ;var armyCount : Integer = ParserGetCountByHandle(pArmyUnits);
	  [*] = ;
      [*] = ;// doesn't work for heroes
      [*] = ;var needRestore : Boolean = false;
      [*] = ;
      [*] = ;_rand_ClearRoll();
      [*] = ;
      [*] = ;for i := armyCount-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pArmyUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'UnitID');
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife');
      [*] = ;   var moralMod : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'MoralMod');
      [*] = ;
      [*] = ;   IntRegister0 := pArmyUnit;
      [*] = ;   IntRegister1 := pArmyUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetUnitPropertyByParser');
      [*] = ;   var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;   if armyCount < gc_MaxArmyCount then
	  [*] = ;	   curArmyIDs[i] := unitID;
      [*] = ;
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;   var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;   if curLife > 0 then
      [*] = ;   begin
      [*] = ;      var oldCurLife : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife');
      [*] = ;      var oldMoralMod : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'MoralMod');
      [*] = ;
      [*] = ;      // heal necromants
      [*] = ;      if (not bRaise) and (unitType = 2) then
      [*] = ;      begin
      [*] = ;         if heroHandle <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 21;
      [*] = ;            GameObjectExecuteStateByHandle(heroHandle, 'GetSkillLevel');
      [*] = ;            var skillLevel : Integer = IntRegister1;
      [*] = ;
      [*] = ;            if skillLevel > 0 then
      [*] = ;            begin
      [*] = ;               curLife := curLife + Max(1, Floor(maxLife * skillLevel / 10));
      [*] = ;               if curLife > maxLife then
      [*] = ;                  curLife := maxLife;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var healBonus : Integer = 0;
      [*] = ;
      [*] = ;         if (heroHandle = 0) or (i > 0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := pArmyUnit;
      [*] = ;            IntRegister2 := heroHandle;
      [*] = ;            IntRegister3 := 35;
      [*] = ;            ExecuteState('CheckUnitAbility');
      [*] = ;            healBonus := IntRegister4;
      [*] = ;
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := pArmyUnit;
      [*] = ;            IntRegister2 := heroHandle;
      [*] = ;            IntRegister3 := 48;
      [*] = ;            ExecuteState('CheckUnitAbility');
      [*] = ;            healBonus := healBonus + 2 * IntRegister4;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            healBonus := GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iHealth);
      [*] = ;
      [*] = ;            IntRegister0 := 35;
      [*] = ;            GameObjectExecuteStateByHandle(heroHandle, 'CheckAbility');
      [*] = ;            healBonus := healBonus + IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := 48;
      [*] = ;            GameObjectExecuteStateByHandle(heroHandle, 'CheckAbility');
      [*] = ;            healBonus := healBonus + 2 * IntRegister1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if bHomeLand then
      [*] = ;         begin
      [*] = ;            if curLife < maxLife then
      [*] = ;            begin
      [*] = ;               var lifeAdd : Integer = Floor(maxLife * (10 + provBonus) / 100);
      [*] = ;               if lifeAdd < 1 then
      [*] = ;                  lifeAdd := 1;
      [*] = ;
      [*] = ;               lifeAdd := lifeAdd + healBonus;
      [*] = ;
      [*] = ;               if (unitType <> 2) and (unitType <> 4) then
      [*] = ;                  lifeAdd := lifeAdd + squadHeal;
      [*] = ;
      [*] = ;               curLife := curLife + lifeAdd;
      [*] = ;               if curLife > maxLife then
      [*] = ;                  curLife := maxLife;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if moralMod < 0 then
      [*] = ;               moralMod := moralMod + 1;
      [*] = ;            if moralMod > 0 then
      [*] = ;               moralMod := moralMod - 1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if curLife < maxLife then
      [*] = ;            begin
      [*] = ;               var lifeAdd : Integer = healBonus;
      [*] = ;               if (unitType <> 2) and (unitType <> 4) then
      [*] = ;                  lifeAdd := lifeAdd + squadHeal;
      [*] = ;
      [*] = ;               curLife := curLife + lifeAdd;
      [*] = ;               if curLife > maxLife then
      [*] = ;                  curLife := maxLife;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if moralmod > -15 then
      [*] = ;               moralMod := moralMod - 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pArmyUnit, 'CurLife', curLife);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pArmyUnit, 'FCurLife', curLife);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pArmyUnit, 'LifeRatio', curLife / maxLife);
      [*] = ;      ParserSetIntValueByKeyByHandle(pArmyUnit, 'MoralMod', moralMod);
      [*] = ;
      [*] = ;      if (curLife < maxLife) or (moralMod <> 0) then
      [*] = ;         needRestore := true;
      [*] = ;
      [*] = ;      if (i = 0) and (heroHandle <> 0) then
      [*] = ;      begin
      [*] = ;         SetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iCurHP, curLife);
      [*] = ;
      [*] = ;         IntRegister0 := gc_map_hero_iLife;
      [*] = ;         GameObjectExecuteStateByHandle(heroHandle, 'GetProperty');
      [*] = ;         var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var fCurToMax : Float = curLife / maxLife;
      [*] = ;         SetGameObjectFloatValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_fCurToMaxLife, fCurToMax);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// make list of missing units and possibly pick one to be readded.
      [*] = ;if bRaise and (gGame.currentTurn mod gc_GuardRessTime = 0) and (armyCount < gc_MaxArmyCount) then
      [*] = ;begin
      [*] = ;   var resRouletteCount : Integer = 0;
	  [*] = ;	var origArmyCount : Integer = 0;
	  [*] = ;	origArmyCount := ParserGetIntValueByKeyByHandle(pOrigArmy, 'Quantity'); 
	  [*] = ;	if (origArmyCount > 0) or (pOrigArmy = 0) then //Hireable Defenders don't have "Quantity" -value so should be zero at this point, only resurrect such squads, so exit
	  [*] = ;      exit;
	  [*] = ;
	  [*] = ;	var pOrigArmyUnits : Integer = ParserSelectByHandleByKey(pOrigArmy, 'Units');
      [*] = ;	for i := 0 to ParserGetCountByHandle(pOrigArmyUnits)-1 do
	  [*] = ;   begin
      [*] = ;   	var pOrigArmyUnit : Integer = ParserSelectByHandleByIndex(pOrigArmyUnits, i);
	  [*] = ;   	var unitID : Integer = ParserGetIntValueByKeyByHandle(pOrigArmyUnit, 'UnitID');
	  [*] = ;		var count : Integer = ParserGetIntValueByKeyByHandle(pOrigArmyUnit, 'Count');
	  [*] = ;
	  [*] = ;		origArmyCount := origArmyCount + count;
	  [*] = ;
      [*] = ;		for j := 0 to count-1 do //match-check existing units with original units
	  [*] = ;		begin
	  [*] = ;			for k := 0 to armyCount-1 do
	  [*] = ;			begin
	  [*] = ;				if (curArmyIDs[k] = unitID) then
	  [*] = ;				begin
	  [*] = ;   		 		curArmyIDs[k] := 0;//match found, take it out the check
	  [*] = ; 					break;
	  [*] = ;				end;
	  [*] = ;
	  [*] = ;				if (k = armyCount-1) then //if no match is found after going through current units
	  [*] = ;				begin
	  [*] = ;					//var pUnit : Integer = _unit_GetUnitParserByID(unitID);
	  [*] = ;					//var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;					gArrRollerN[resRouletteCount] := pOrigArmyUnit; //include unit in resurrection roulette
      [*] = ;					gArrRollerP[resRouletteCount] := 10;
      [*] = ;					resRouletteCount := resRouletteCount + 1;
	  [*] = ; 					break;
	  [*] = ;				end;
	  [*] = ;			end;		
	  [*] = ;		end;
	  [*] = ;	end;
      [*] = ;	if resRouletteCount > 0 then // resurrection
      [*] = ;	begin
	  [*] = ;		//if origArmyCount = 0 then //ensure no zero division
	  [*] = ;		//	origArmyCount := 1;
	  [*] = ;		//var resChance : Float = 1.1 - armyCount / origArmyCount; //the more troops are missing relative to full army the higher the chance for resurrection.
	  [*] = ;		//if resYes > 0.85 then
	  [*] = ;		//	resYes := 0.85; //minimum resurrection chance 15%
	  [*] = ;
	  [*] = ;		//if RandomExt() < resChance then
	  [*] = ;		begin
      [*] = ;			var pNewUnit : Integer = _rand_Roll(false); //sum ranks of all dead units, gArrRoller, and pick unit, the lower the rank the higher the probability.
      [*] = ;		
      [*] = ;			if pNewUnit <> 0 then
      [*] = ;			begin
      [*] = ;				var unitID : Integer = ParserGetIntValueByKeyByHandle(pNewUnit, 'UnitID');
	  [*] = ;				var level : Integer = ParserGetIntValueByKeyByHandle(pNewUnit, 'Level');
	  [*] = ;
      [*] = ;				if level < 0 then
      [*] = ;					level := 0
      [*] = ;				else if level > gc_battle_Unit_Level_Cap then
      [*] = ;					level := gc_battle_Unit_Level_Cap;
      [*] = ;
      [*] = ;				IntRegister0 := unitID;
      [*] = ;				IntRegister1 := level;
      [*] = ;				ExecuteState('GetUnitExpByLevel');
      [*] = ;				IntRegister0 := pArmyUnits;
      [*] = ;				IntRegister1 := unitID;
      [*] = ;				//IntRegister2 := exp;  // already calculated in previous call
      [*] = ;				IntRegister3 := 0; //no hero handle
      [*] = ;				ExecuteState('AddUnitToParser');
      [*] = ;               var pArmyUnit : Integer = IntRegister4;
      [*] = ;               
      [*] = ;				IntRegister0 := pArmyUnit;
      [*] = ;				IntRegister1 := pArmyUnits;
      [*] = ;				IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;				ExecuteState('GetUnitPropertyByParser');
      [*] = ;				var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;				var newLife : Integer = maxLife div 2 + 1;
      [*] = ;				ParserSetIntValueByKeyByHandle(pArmyUnit, 'CurLife', newLife);
      [*] = ;				ParserSetFloatValueByKeyByHandle(pArmyUnit, 'FCurLife', newLife);
	  [*] = ;			end;
      [*] = ;		end;
      [*] = ;	end;
	  [*] = ;	if (origArmyCount - armyCount >= 2) then //if still missing units
      [*] = ;	   needRestore := true;
	  [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;_misc_AntiFreeze();
      [*] = ;
      [*] = ;BoolRegister2 := needRestore;
   struct.end
section.end

