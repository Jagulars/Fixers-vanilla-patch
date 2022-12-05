section.begin
   Name = MakeTurn
   Code : struct.begin
      [*] = ;function CheckMeleeHit(tGOHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := tGOHandle;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   BoolRegister1 := false;
      [*] = ;   BoolRegister2 := false;
      [*] = ;   BoolRegister3 := true;
      [*] = ;   ExecuteState('GetMeleeHit');
      [*] = ;   Result := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckRangedHit(tGOHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := tGOHandle;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('GetRangedHit');
      [*] = ;   Result := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\MAKETURN';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName();
      [*] = ;var moveType : Integer = _unit_GetMoveType(myGOHandle);
      [*] = ;var HexDist : Float = Sqrt(3) * gc_HexSize;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;var castMode : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iCastMode);
      [*] = ;var mapPlHandle : Integer = 0;
      [*] = ;
      [*] = ;if GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode) = 1 then
      [*] = ;   mapPlHandle := gIntRegister_BattleAttackPlayer
      [*] = ;else
      [*] = ;   mapPlHandle := gIntRegister_BattleDefendPlayer;
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyNeighbours : Integer = ParserSelectByHandleByKey(pMyParser, 'Neighbours');
      [*] = ;var pMyActions : Integer = ParserSelectByHandleByKey(pMyParser, 'Actions');
      [*] = ;
      [*] = ;var bMarch : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bCanMarch);
      [*] = ;var movePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;var curLife : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurLife);
      [*] = ;var curStamina : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurStamina);
      [*] = ;var actAbility : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iActiveAbility);
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myGridX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * myGridY + myGridX;
      [*] = ;var myTNHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;var pMyHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;var randKey1, randKey0 : Integer;
      [*] = ;GetRandomExtKey64(randKey0, randKey1);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+',X:'+IntToStr(myGridX)+',Y:'+IntToStr(myGridY)+',RandKey0:'+IntToStr(randKey0)+',RandKey1:'+IntToStr(randKey1)+']',_log_trace);
      [*] = ;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iAttack;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var attack : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iShootingRange;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var range : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var rangedAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iResist;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var resist : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iDefence;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var defence : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;var abil46 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_stoned);
      [*] = ;var abil47 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_web);
      [*] = ;var abil57 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_soul_stealer);
      [*] = ;var abil68 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_vampire);
      [*] = ;
      [*] = ;var myUnitID : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iUnitID);
      [*] = ;
      [*] = ;var pUnit : Integer = _unit_GetUnitParserByID(myUnitID);
      [*] = ;var myUnitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;var i, j, x, y, x1, y1 : Integer;
      [*] = ;var bAct : Boolean = false;
      [*] = ;var bCanAct : Boolean = GetBoolValueByIndex(gc_stack_unit_bCanAct);
      [*] = ;var bCanMelee : Boolean = GetBoolValueByIndex(gc_stack_unit_bCanMelee);
      [*] = ;var bCanShoot : Boolean = GetBoolValueByIndex(gc_stack_unit_bCanShoot);
      [*] = ;var bCanCast : Boolean = GetBoolValueByIndex(gc_stack_unit_bCanCast);
      [*] = ;
      [*] = ;var curAmmo : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo);
      [*] = ;
      [*] = ;procedure FillMoveMap();
      [*] = ;begin
      [*] = ;   var i,pHexCell,uid,land,pass,moveMap : Integer;
      [*] = ;   var node_enabled : Boolean;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pHexCell := ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;      uid := ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;
      [*] = ;      land := ParserGetIntValueByKeyByHandle(pHexCell, 'Land');
      [*] = ;      pass := ParserGetIntValueByKeyByHandle(pHexCell, 'Pass');
      [*] = ;
      [*] = ;      moveMap := 0;
      [*] = ;      node_enabled := GetTrackNodeEnabledByHandle(GetTrackNodeHandleByIndex(i));
      [*] = ;      if (land > 0) and (land <= movePoints) and (pass > 0) and (node_enabled) and (uid = 0) then
      [*] = ;      begin
      [*] = ;         if (land = movePoints) and bMarch then
      [*] = ;            moveMap := 1
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if land < movePoints then
      [*] = ;               moveMap := 2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'MoveMap', moveMap);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function AIInMeleeRange(x, y : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;   var pass : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Pass');
      [*] = ;   var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;   var land : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Land');
      [*] = ;
      [*] = ;   var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;   var tnEnable : Boolean = GetTrackNodeEnabledByHandle(tnHandle);
      [*] = ;   var neighbour_node: Boolean;
      [*] = ;
      [*] = ;   Result := 0;
      [*] = ;   if (x >= 0) and (x < gc_battle_GridSize) and (y >= 0) and (y < gc_battle_GridSize) then
      [*] = ;   begin
      [*] = ;      if (x = myGridX) and (y = myGridY) then
      [*] = ;         Result := 3
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if tnEnable and (pass > 0) and (uid = 0) then
      [*] = ;         begin
      [*] = ;            neighbour_node := GetTrackNodesConnectedByHandle(myTNHandle, tnHandle);
      [*] = ;            if (land > movePoints) and bMarch and (not neighbour_node) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := gc_ability_march;
      [*] = ;               ExecuteState('CheckAbility');
      [*] = ;               if ((curStamina - IntRegister1) >= 5) then
      [*] = ;                  Result := 1
      [*] = ;               else
      [*] = ;                  Result := 0;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               Result := 2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckMeleeTarget(x, y, pMeleeTarget : Integer);
      [*] = ;begin
      [*] = ;   var meleeRange : Integer = AIInMeleeRange(x, y);
      [*] = ;   if meleeRange > 0 then
      [*] = ;   begin
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', meleeRange);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridX', x);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridY', y);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function AIBetterPlace(x, y, x1, y1, mov, mov1 : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;   var terType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;   var terInd : Integer = (terType + 1) div 2;
      [*] = ;
      [*] = ;   var ind1 : Integer = gc_battle_GridSize * y1 + x1;
      [*] = ;   var pHexCell1 : Integer = ParserSelectByHandleByIndex(pHexCells, ind1);
      [*] = ;   var terType1 : Integer = ParserGetIntValueByKeyByHandle(pHexCell1, 'Type');
      [*] = ;   var terInd1 : Integer = (terType1 + 1) div 2;
      [*] = ;
      [*] = ;   IntRegister0 := gc_ability_common_attack;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   var abil65 : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_ability_round_attack;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   var abil66 : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var isExit : Boolean = false;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   // round attack
      [*] = ;   if (abil65 > 0) or ((abil66 > 0) and (curStamina > abil66)) then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := false;
      [*] = ;      IntRegister0 := x;
      [*] = ;      IntRegister1 := y;
      [*] = ;      ExecuteState('FindNeighbour');
      [*] = ;      var neigh : Integer = IntRegister2;
      [*] = ;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      IntRegister0 := x1;
      [*] = ;      IntRegister1 := y1;
      [*] = ;      ExecuteState('FindNeighbour');
      [*] = ;      var neigh1 : Integer = IntRegister2;
      [*] = ;
      [*] = ;      if neigh > neigh1 then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         isExit := true;
      [*] = ;      end;
      [*] = ;      if neigh < neigh1 then
      [*] = ;      begin
      [*] = ;         Result := false;
      [*] = ;         isExit := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not isExit then
      [*] = ;   begin
      [*] = ;      // check terrain types knowledge
      [*] = ;      var abilID : Integer = 0;
      [*] = ;      case terInd of
      [*] = ;         gc_ForestTerrainType : abilID := gc_ability_forests_knowledge;
      [*] = ;         gc_HillTerrainType : abilID := gc_ability_hills_knowledge;
      [*] = ;         gc_SwampTerrainType : abilID := gc_ability_swamps_knowledge;
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := abilID;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if ( IntRegister1 > 3) and (terInd = gc_ForestTerrainType) and (terInd1 <> gc_ForestTerrainType) then
      [*] = ;         Result := true;
      [*] = ;      if ( IntRegister1 > 3) and (terInd = gc_HillTerrainType) and (terInd1 <> gc_HillTerrainType) then
      [*] = ;         Result := true;
      [*] = ;      if ( IntRegister1 > 3) and (terInd = gc_SwampTerrainType) and (terInd1 <> gc_SwampTerrainType) then
      [*] = ;         Result := true;
      [*] = ;
      [*] = ;      isExit := Result;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // check move cost
      [*] = ;   if not isExit then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_ability_tireless;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if IntRegister1 = 0 then
      [*] = ;      begin
      [*] = ;         if mov1 > mov then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            isExit := true;
      [*] = ;         end;
      [*] = ;         if mov1 < mov then
      [*] = ;         begin
      [*] = ;            Result := false;
      [*] = ;            isExit := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // check hills
      [*] = ;   if (not isExit) and (terInd = gc_HillTerrainType) and (terInd1 <> gc_HillTerrainType) then
      [*] = ;   begin
      [*] = ;      Result := true;
      [*] = ;      isExit := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // check distance to borders
      [*] = ;   if not isExit then
      [*] = ;   begin
      [*] = ;      var plAttack : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;
      [*] = ;      if (plAttack = 1) and (x > x1) then
      [*] = ;         Result := true;
      [*] = ;      if (plAttack = 0) and (x < x1) then
      [*] = ;         Result := true;
      [*] = ;   end;
      [*] = ;   //Result := true;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckBetterPlace(x, y, pMeleeTarget : Integer);
      [*] = ;begin
      [*] = ;   var canMelee : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee');
      [*] = ;   var meleeGridX : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridX');
      [*] = ;   var meleeGridY : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridY');
      [*] = ;
      [*] = ;   var meleeRange : Integer= AIInMeleeRange(x, y);
      [*] = ;
      [*] = ;   if (meleeRange > 0) and ((canMelee = 0) or AIBetterPlace(x, y, meleeGridX, meleeGridY, canMelee, meleeRange)) then
      [*] = ;   begin
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', meleeRange);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridX', x);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridY', y);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetMyAction(ind : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pMyActions, ind), 'Value');
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckCorpse(plHandle : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var movePoints : Integer = GetIntValueByIndex(gc_stack_unit_iMovePoints);
      [*] = ;   var i : Integer;
      [*] = ;   var minDist : Integer = 100;
      [*] = ;
      [*] = ;   Result := 0;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;      var gridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var gridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;      var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID));
      [*] = ;      var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;      if (curLife = 0) and (unitType <> 2) and (unitType <> 4) and (gridX >= 0) and (gridX < gc_battle_GridSize) and (gridY >= 0) and (gridY < gc_battle_GridSize) then
      [*] = ;      begin
      [*] = ;         var land : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pHexCells, gc_battle_GridSize * gridY + gridX), 'Land');
      [*] = ;
      [*] = ;         if (land < movePoints) and (land > 0) and (land < minDist) then
      [*] = ;         begin
      [*] = ;            Result := goHandle;
      [*] = ;            minDist := land;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// making list of available spells
      [*] = ;var arCast : array [0..500] of Integer;
      [*] = ;var spellCount : Integer = 0;
      [*] = ;var pMySpells : Integer = ParserSelectByHandleByKey(pMyParser, 'Spells');
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;IntRegister0 := gc_ability_low_spells_cost;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var abil983 : Integer = IntRegister1;
      [*] = ;
      [*] = ;if bCanCast then
      [*] = ;for i := 0 to ParserGetCountByHandle(pMySpells)-1 do
      [*] = ;begin
      [*] = ;   var pMySpell : Integer = ParserSelectByHandleByIndex(pMySpells, i);
      [*] = ;   var spellID : Integer = ParserGetIntValueByKeyByHandle(pMySpell, 'SpellID');
      [*] = ;
      [*] = ;   if isHero then
      [*] = ;   begin
      [*] = ;      var used : Boolean = ParserGetBoolValueByKeyByHandle(pMySpell, 'Used');
      [*] = ;      if (castMode > 0) and (not used) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         MapExecuteState('GetSpellParserByID');
      [*] = ;         var pSpell : Integer = IntRegister1;
      [*] = ;         var gemCost : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Cost');
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleAbilityExistByID(8)) then
      [*] = ;         begin
      [*] = ;            var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(8);
      [*] = ;            gemCost := _misc_RoundUp((gemCost*param1)/100);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (mapPlHandle = 0) or (plGem >= (gemCost * (100 - abil983)) div 100) then
      [*] = ;         begin
      [*] = ;            arCast[spellCount] := spellID;
      [*] = ;            spellCount := spellCount + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var spAmmo : Integer = ParserGetIntValueByKeyByHandle(pMySpell, 'Ammo');
      [*] = ;      if curAmmo >= spAmmo then
      [*] = ;      begin
      [*] = ;         arCast[spellCount] := spellID;
      [*] = ;         spellCount := spellCount + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// choosing spell
      [*] = ;var chosenSpell : Integer = -1;
      [*] = ;var spellTaste : Integer = 0;
      [*] = ;var spellTargetUID : Integer = 0;
      [*] = ;var spellTargetX : Integer = 0;
      [*] = ;var spellTargetY : Integer = 0;
      [*] = ;var spellHit : Integer = 0;
      [*] = ;
      [*] = ;if bCanCast then
      [*] = ;for i := 0 to spellCount-1 do
      [*] = ;begin
      [*] = ;   var spellID : Integer = arCast[i];
      [*] = ;   if spellID > 0 then
      [*] = ;   begin
      [*] = ;      var damage : Integer = 0;
      [*] = ;      var buff : Integer = 0;
      [*] = ;      var summon : Integer = 0;
      [*] = ;
      [*] = ;      IntRegister0 := spellID;
      [*] = ;      MapExecuteState('GetSpellParserByID');
      [*] = ;      var pSpell : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;
      [*] = ;      var spSacrifice : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Sacrifice');
      [*] = ;      var spTarget : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Target');
      [*] = ;      var spArea : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;      var spRadius : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Radius');
      [*] = ;      var spOnEnemy : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnEnemy');
      [*] = ;      var spOnAlly : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnAlly');
      [*] = ;
      [*] = ;      if (not spSacrifice) or (castMode > 1) then
      [*] = ;      begin
      [*] = ;         var spellPower : Integer;
      [*] = ;         // spell with unit target
      [*] = ;         if spTarget = 1 then
      [*] = ;         begin
      [*] = ;            if spOnEnemy then
      [*] = ;            begin
      [*] = ;               for j := 0 to GetPlayerGameObjectsCountByHandle(enPlHandle)-1 do
      [*] = ;               begin
      [*] = ;                  var enGOHandle : Integer = GetGameObjectHandleByIndex(j, enPlHandle);
      [*] = ;                  var stealthMode : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not stealthMode) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     IntRegister1 := GetGameObjectUniqueIdByHandle(enGOHandle);
      [*] = ;                     ExecuteState('GetEnemySpellTaste');
      [*] = ;                     var myTaste : Integer = IntRegister2;
      [*] = ;                     var spDamage : Integer = IntRegister3;
      [*] = ;
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     ExecuteState('CalcSpellPenalty');
      [*] = ;                     myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;                     if (myTaste > spellTaste) and ((spDamage > 0) or (myTaste > 0)) then
      [*] = ;                     begin
      [*] = ;                        spellTaste := myTaste;
      [*] = ;                        spellHit := spDamage;
      [*] = ;                        chosenSpell := i;
      [*] = ;                        spellTargetUID := GetGameObjectUniqueIdByHandle(enGOHandle);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if spOnAlly then
      [*] = ;            begin
      [*] = ;               for j := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(j, myPlHandle);
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     IntRegister1 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                     ExecuteState('GetAllySpellTaste');
      [*] = ;                     var myTaste : Integer = IntRegister2;
      [*] = ;                     var spDamage : Integer = IntRegister3;
      [*] = ;
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     ExecuteState('CalcSpellPenalty');
      [*] = ;                     myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;                     if (myTaste > spellTaste) and ((spDamage > 0) or (myTaste > 0)) then
      [*] = ;                     begin
      [*] = ;                        spellTaste := myTaste;
      [*] = ;                        spellHit := spDamage;
      [*] = ;                        chosenSpell := i;
      [*] = ;                        spellTargetUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // spell with whole battlefield target
      [*] = ;         if (spTarget = 0) and (spArea = 2) then
      [*] = ;         begin
      [*] = ;            var myTaste : Integer = 0;
      [*] = ;            var myDamage : Integer = 0;
      [*] = ;
      [*] = ;            if spOnAlly then
      [*] = ;            begin
      [*] = ;               for j := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(j, myPlHandle);
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     IntRegister1 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                     ExecuteState('GetAllySpellTaste');
      [*] = ;                     myTaste := myTaste + IntRegister2;
      [*] = ;                     myDamage := myDamage + IntRegister3;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if spOnEnemy then
      [*] = ;            begin
      [*] = ;               for j := 0 to GetPlayerGameObjectsCountByHandle(enPlHandle)-1 do
      [*] = ;               begin
      [*] = ;                  var enGOHandle : Integer = GetGameObjectHandleByIndex(j, enPlHandle);
      [*] = ;                  var stealthMode : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not stealthMode) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := spellID;
      [*] = ;                     IntRegister1 := GetGameObjectUniqueIdByHandle(enGOHandle);
      [*] = ;                     ExecuteState('GetEnemySpellTaste');
      [*] = ;                     myTaste := myTaste + IntRegister2;
      [*] = ;                     myDamage := myDamage + IntRegister3;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            ExecuteState('CalcSpellPenalty');
      [*] = ;            myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;            if (myTaste > spellTaste) and ((myDamage > 0) or (myTaste > 0)) then
      [*] = ;            begin
      [*] = ;               spellTaste := myTaste;
      [*] = ;               spellHit := myDamage;
      [*] = ;               chosenSpell := i;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // spell on unit corpse
      [*] = ;         if (spTarget = 2) or (spTarget = 4) then
      [*] = ;         begin
      [*] = ;            if spOnEnemy then
      [*] = ;            begin
      [*] = ;               for j := 0 to GetPlayerGameObjectsCountByHandle(enPlHandle)-1 do
      [*] = ;               begin
      [*] = ;                  var enGOHandle : Integer = GetGameObjectHandleByIndex(j, enPlHandle);
      [*] = ;                  var playable : Boolean = GetGameObjectPlayableObjectByHandle(enGOHandle);
      [*] = ;
      [*] = ;                  var gridX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var gridY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;                  if (gridX >= 0) and (gridX < gc_battle_GridSize) and (gridY >= 0) and (gridY < gc_battle_GridSize) then
      [*] = ;                  begin
      [*] = ;                     var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;                     var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                     var cellUID : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;                     var dangerZone : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'DangerZone');
      [*] = ;
      [*] = ;                     if (not playable) and ((spTarget = 2) or (cellUID = 0)) then
      [*] = ;                     begin
      [*] = ;                        var buff : Integer = 0;
      [*] = ;                        var damage : Integer = 0;
      [*] = ;
      [*] = ;                        var pSpellEffect0 : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;                        var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'AbilityID');
      [*] = ;
      [*] = ;                        if abilID > 1000 then
      [*] = ;                        begin
      [*] = ;                           spellPower := ParserGetIntValueByKeyByHandle(pSpellEffect0, 'Power');
      [*] = ;                           var spUnitID : Integer = abilID - 1000;
      [*] = ;
      [*] = ;                           var pSpUnit : Integer = _unit_GetUnitParserByID(spUnitID);
      [*] = ;
      [*] = ;                           var rank : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Rank');
      [*] = ;                           var speed : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Speed');
      [*] = ;                           var attack : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Attack');
      [*] = ;                           var life : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Life');
      [*] = ;
      [*] = ;                           var abil907 : Integer = _unit_CheckAbilityExt(myGOHandle, gc_ability_summoning_power);
      [*] = ;                           var abil909 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_necro_summoning_power);
      [*] = ;
      [*] = ;                           spellPower := spellPower + abil907 + abil909;
      [*] = ;
      [*] = ;                           buff := (rank + 1) * 10 + spellPower * 3 - dangerZone + life;
      [*] = ;
      [*] = ;                           damage := attack + spellPower div 2;
      [*] = ;                           if dangerZone >= 2 then
      [*] = ;                           begin
      [*] = ;                              damage := damage - dangerZone - 1 + speed;
      [*] = ;                              if damage < 1 then
      [*] = ;                                 damage := 1;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        var myTaste : Integer = buff;
      [*] = ;                        myTaste := myTaste + damage * 3;
      [*] = ;
      [*] = ;                        IntRegister0 := spellID;
      [*] = ;                        ExecuteState('CalcSpellPenalty');
      [*] = ;                        myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;                        if (myTaste > spellTaste) and ((damage > 0) or (buff > 0)) then
      [*] = ;                        begin
      [*] = ;                           spellTaste := myTaste;
      [*] = ;                           spellHit := damage;
      [*] = ;                           chosenSpell := i;
      [*] = ;                           spellTargetUID := GetGameObjectUniqueIdByHandle(enGOHandle);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if spOnAlly then
      [*] = ;            begin
      [*] = ;               for j := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(j, myPlHandle);
      [*] = ;                  var playable : Boolean = GetGameObjectPlayableObjectByHandle(goHandle);
      [*] = ;
      [*] = ;                  var gridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var gridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;                  if (gridX >= 0) and (gridX < gc_battle_GridSize) and (gridY >= 0) and (gridY < gc_battle_GridSize) then
      [*] = ;                  begin
      [*] = ;                     var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;                     var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                     var cellUID : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;                     var dangerZone : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'DangerZone');
      [*] = ;
      [*] = ;                     if (not playable) and ((spTarget = 2) or (cellUID = 0)) then
      [*] = ;                     begin
      [*] = ;                        var buff : Integer = 0;
      [*] = ;                        var damage : Integer = 0;
      [*] = ;
      [*] = ;                        var pSpellEffect0 : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;                        var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'AbilityID');
      [*] = ;
      [*] = ;                        if abilID > 1000 then
      [*] = ;                        begin
      [*] = ;                           spellPower := ParserGetIntValueByKeyByHandle(pSpellEffect0, 'Power');
      [*] = ;                           var spUnitID : Integer = abilID - 1000;
      [*] = ;
      [*] = ;                           var pSpUnit : Integer = _unit_GetUnitParserByID(spUnitID);
      [*] = ;
      [*] = ;                           var rank : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Rank');
      [*] = ;                           var speed : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Speed');
      [*] = ;                           var attack : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Attack');
      [*] = ;                           var life : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Life');
      [*] = ;
      [*] = ;                           var abil907 : Integer = _unit_CheckAbilityExt(myGOHandle, gc_ability_summoning_power);
      [*] = ;                           var abil909 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_necro_summoning_power);
      [*] = ;
      [*] = ;                           spellPower := spellPower + abil907 + abil909;
      [*] = ;
      [*] = ;                           buff := (rank + 1) * 10 + spellPower * 3 - 1 + dangerZone + life;
      [*] = ;
      [*] = ;                           damage := attack + spellPower div 2;
      [*] = ;                           if dangerZone >= 2 then
      [*] = ;                           begin
      [*] = ;                              damage := damage - dangerZone - 1 + speed;
      [*] = ;                              if damage < 1 then
      [*] = ;                                 damage := 1;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        // resurrect
      [*] = ;                        if abilID = 1 then
      [*] = ;                        begin
      [*] = ;                           var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;                           var pUnit : Integer = _unit_GetUnitParserByID(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID));
      [*] = ;                           var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;                           var attack : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Attack');
      [*] = ;
      [*] = ;                           buff := rank * 15 + level * 2;
      [*] = ;                           damage := attack;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        var myTaste : Integer = buff;
      [*] = ;                        myTaste := myTaste + damage * 3;
      [*] = ;
      [*] = ;                        IntRegister0 := spellID;
      [*] = ;                        ExecuteState('CalcSpellPenalty');
      [*] = ;                        myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;                        if (myTaste > spellTaste) and ((damage > 0) or (buff > 0)) then
      [*] = ;                        begin
      [*] = ;                           spellTaste := myTaste;
      [*] = ;                           spellHit := damage;
      [*] = ;                           chosenSpell := i;
      [*] = ;                           spellTargetUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // spell on free hex
      [*] = ;         if (spTarget = 5) then
      [*] = ;         begin
      [*] = ;            var abil907 : Integer = _unit_CheckAbilityExt(myGOHandle, gc_ability_summoning_power);
      [*] = ;            var spRange : Integer = abil907 div 2 + 1;
      [*] = ;
      [*] = ;            IntRegister0 := myGridX;
      [*] = ;            IntRegister1 := myGridY;
      [*] = ;            IntRegister2 := spRange;
      [*] = ;            ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;            for x := 0 to gc_battle_GridSize-1 do
      [*] = ;            begin
      [*] = ;               for y := 0 to gc_battle_GridSize-1 do
      [*] = ;               begin
      [*] = ;                  var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;                  var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;                  var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;                  var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;                  var shoot : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Shoot');
      [*] = ;                  var dangerZone : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'DangerZone');
      [*] = ;
      [*] = ;                  IntRegister0 := spellID;
      [*] = ;                  IntRegister1 := pHexCell;
      [*] = ;                  ExecuteState('CanCastSpell');
      [*] = ;                  var canCast : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                  if (shoot > 0) and (uid = 0) and (GetTrackNodeEnabledByHandle(tnHandle)) then
      [*] = ;                  begin
      [*] = ;                     var pSpellEffect0 : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;                     var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'AbilityID');
      [*] = ;
      [*] = ;                     if abilID > 1000 then
      [*] = ;                     begin
      [*] = ;                        var buff : Integer = 0;
      [*] = ;                        var damage : Integer = 0;
      [*] = ;
      [*] = ;                        spellPower := ParserGetIntValueByKeyByHandle(pSpellEffect0, 'Power');
      [*] = ;                        var spUnitID : Integer = abilID - 1000;
      [*] = ;
      [*] = ;                        var pSpUnit : Integer = _unit_GetUnitParserByID(spUnitID);
      [*] = ;
      [*] = ;                        var rank : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Rank');
      [*] = ;                        var speed : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Speed');
      [*] = ;                        var attack : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Attack');
      [*] = ;                        var life : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Life');
      [*] = ;
      [*] = ;                        spellPower := spellPower + _unit_CheckAbilityExt(myGOHandle, gc_ability_summoning_power);
      [*] = ;
      [*] = ;                        buff := (rank + 1) * 10 + spellPower * 3 - dangerZone * 2 + life;
      [*] = ;
      [*] = ;                        damage := attack + spellPower div 2;
      [*] = ;                        if dangerZone >= 2 then
      [*] = ;                        begin
      [*] = ;                           damage := damage - dangerZone + speed;
      [*] = ;                           if damage < 1 then
      [*] = ;                              damage := 1;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        var myTaste : Integer = buff;
      [*] = ;                        myTaste := myTaste + damage * 3;
      [*] = ;
      [*] = ;                        IntRegister0 := spellID;
      [*] = ;                        ExecuteState('CalcSpellPenalty');
      [*] = ;                        myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;                        if (myTaste > spellTaste) and ((damage > 0) or (buff > 0)) then
      [*] = ;                        begin
      [*] = ;                           spellTaste := myTaste;
      [*] = ;                           spellHit := damage;
      [*] = ;                           chosenSpell := i;
      [*] = ;                           spellTargetX := x;
      [*] = ;                           spellTargetY := y;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if spTarget = 3 then
      [*] = ;         begin
      [*] = ;            for x := 0 to gc_battle_GridSize-1 do
      [*] = ;            for y := 0 to gc_battle_GridSize-1 do
      [*] = ;            begin
      [*] = ;               var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;               var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;               var myTaste : Integer = 0;
      [*] = ;               var myDamage : Integer = 0;
      [*] = ;
      [*] = ;               IntRegister0 := x;
      [*] = ;               IntRegister1 := y;
      [*] = ;               IntRegister2 := spRadius;
      [*] = ;               ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;               if spOnAlly or spOnEnemy then
      [*] = ;               begin
      [*] = ;                  for x1 := 0 to gc_battle_GridSize-1 do
      [*] = ;                  for y1 := 0 to gc_battle_GridSize-1 do
      [*] = ;                  begin
      [*] = ;                     var ind1 : Integer = gc_battle_GridSize * y1 + x1;
      [*] = ;                     var pHexCell1 : Integer = ParserSelectByHandleByIndex(pHexCells, ind1);
      [*] = ;                     var shoot1 : Integer = ParserGetIntValueByKeyByHandle(pHexCell1, 'Shoot');
      [*] = ;                     var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell1, 'UID');
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;                     var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;                     var playable : Boolean = GetGameObjectPlayableObjectByHandle(goHandle);
      [*] = ;
      [*] = ;                     if (goHandle <> 0) and playable and ((shoot1 > 0) or ((x = x1) and (y = y1))) then
      [*] = ;                     begin
      [*] = ;                        if spOnAlly and (plHandle = myPlHandle) then
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := spellID;
      [*] = ;                           IntRegister1 := uid;
      [*] = ;                           ExecuteState('GetAllySpellTaste');
      [*] = ;                           myTaste := myTaste + IntRegister2;
      [*] = ;                           myDamage := myDamage + IntRegister3;
      [*] = ;                        end;
      [*] = ;                        if spOnEnemy and (plHandle <> myPlHandle) then
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := spellID;
      [*] = ;                           IntRegister1 := uid;
      [*] = ;                           ExecuteState('GetEnemySpellTaste');
      [*] = ;                           myTaste := myTaste + IntRegister2;
      [*] = ;                           myDamage := myDamage + IntRegister3;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  for x1 := 0 to gc_battle_GridSize-1 do
      [*] = ;                  for y1 := 0 to gc_battle_GridSize-1 do
      [*] = ;                  begin
      [*] = ;                     var ind1 : Integer = gc_battle_GridSize * y1 + x1;
      [*] = ;                     var pHexCell1 : Integer = ParserSelectByHandleByIndex(pHexCells, ind1);
      [*] = ;                     var shoot1 : Integer = ParserGetIntValueByKeyByHandle(pHexCell1, 'Shoot');
      [*] = ;
      [*] = ;                     if (shoot1 > 0) or ((x = x1) and (y = y1)) then
      [*] = ;                     begin
      [*] = ;                        // tile for spell
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               IntRegister0 := spellID;
      [*] = ;               ExecuteState('CalcSpellPenalty');
      [*] = ;               myTaste := myTaste + IntRegister1;
      [*] = ;
      [*] = ;               if (myTaste > spellTaste) and ((myDamage > 0) or (myTaste > 0)) then
      [*] = ;               begin
      [*] = ;                  spellTaste := myTaste;
      [*] = ;                  spellHit := myDamage;
      [*] = ;                  chosenSpell := i;
      [*] = ;                  spellTargetX := x;
      [*] = ;                  spellTargetY := y;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if spellHit = 0 then
      [*] = ;   spellHit := spellTaste div 10;
      [*] = ;
      [*] = ;var pHealTargets : Integer = _misc_ParserGetOrCreateByKey('ui_mt_HealTargets',true);
      [*] = ;// CanHeal : Integer; 0 - not available, 1 - available with walk and march, 2 - available with march, 3 - available from current position
      [*] = ;var pShootTargets : Integer = _misc_ParserGetOrCreateByKey('ui_mt_ShootTargets',true);
      [*] = ;// CanRange : Integer; 0 - not available, 1 - available with walk and march, 2 - available with march, 3 - available from current position
      [*] = ;var pMeleeTargets : Integer = _misc_ParserGetOrCreateByKey('ui_mt_MeleeTargets',true);
      [*] = ;// CanMelee : Integer; 0 - not available, 1 - available with walk and march, 2 - available with march, 3 - available from current position
      [*] = ;// GridX, GridY - grid position for attack
      [*] = ;
      [*] = ;case moveType of
      [*] = ;   0 : ExecuteState('MakeStepMap');
      [*] = ;   else begin
      [*] = ;      BoolRegister0 := (moveType = 2);
      [*] = ;      ExecuteState('MakeFlyMap');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// heal targets
      [*] = ;IntRegister0 := gc_ability_healing;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var healAbility : Integer = IntRegister1;
      [*] = ;
      [*] = ;if (healAbility > 0) and (curAmmo > 0) and bCanShoot then
      [*] = ;begin
      [*] = ;   ExecuteState('Select');
      [*] = ;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      //var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;      var pHealTarget : Integer = ParserAddChildByIndex(pHealTargets, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pHealTarget, 'CanHeal', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHealTarget, 'GridX', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHealTarget, 'GridY', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // heal targets from current position
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;      var goGridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var goGridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;      var pHealTarget : Integer = ParserSelectByHandleByIndex(pHealTargets, i);
      [*] = ;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'IsHealTarget');
      [*] = ;      if (IntRegister1 > 0) and GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;      begin
      [*] = ;         if gBoolRegister_BattleSimulate then
      [*] = ;         begin
      [*] = ;            if Abs(goGridX - myGridX) < movePoints + range then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pHealTarget, 'CanHeal', 3);
      [*] = ;               ParserSetIntValueByKeyByHandle(pHealTarget, 'GridX', myGridX);
      [*] = ;
      [*] = ;               if Abs(goGridX - myGridX) > range then
      [*] = ;               begin
      [*] = ;                  var dist : Integer = Round(Abs(goGridX - myGridX) - range);
      [*] = ;                  if goGridX < myGridX then
      [*] = ;                     dist := -dist;
      [*] = ;
      [*] = ;                  var healX : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'GridX');
      [*] = ;                  healX := healX + dist;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHealTarget, 'GridX', healX);
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHealTarget, 'CanHeal', 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var gridInd : Integer = gc_battle_GridSize * goGridY + goGridX;
      [*] = ;
      [*] = ;            var pGOHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, gridInd);
      [*] = ;            var shoot : Integer = ParserGetIntValueByKeyByHandle(pGOHexCell, 'Shoot');
      [*] = ;
      [*] = ;            if shoot > 0 then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pHealTarget, 'CanHeal', 3);
      [*] = ;               ParserSetIntValueByKeyByHandle(pHealTarget, 'GridX', myGridX);
      [*] = ;               ParserSetIntValueByKeyByHandle(pHealTarget, 'GridY', myGridY);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // heal targets not from current position
      [*] = ;   if not gBoolRegister_BattleSimulate then
      [*] = ;   begin
      [*] = ;      FillMoveMap();
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;         var moveMap : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'MoveMap');
      [*] = ;
      [*] = ;         if moveMap > 0 then
      [*] = ;         begin
      [*] = ;            var gridX : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'X');
      [*] = ;            var gridY : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Y');
      [*] = ;
      [*] = ;            IntRegister0 := gridX;
      [*] = ;            IntRegister1 := gridY;
      [*] = ;            ExecuteState('GetUpdShootingRange');
      [*] = ;            var uShootRange : Integer = IntRegister2;
      [*] = ;
      [*] = ;            IntRegister0 := gridX;
      [*] = ;            IntRegister1 := gridY;
      [*] = ;            IntRegister2 := uShootRange;
      [*] = ;            ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;            for j := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(j, myPlHandle);
      [*] = ;               if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;               begin
      [*] = ;                  var pHealTarget : Integer = ParserSelectByHandleByIndex(pHealTargets, j);
      [*] = ;                  var canHeal : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'CanHeal');
      [*] = ;
      [*] = ;                  var goGridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var goGridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;                  var gridInd : Integer = gc_battle_GridSize * goGridY + goGridX;
      [*] = ;
      [*] = ;                  var pEnHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, gridInd);
      [*] = ;                  var shoot : Integer = ParserGetIntValueByKeyByHandle(pEnHexCell, 'Shoot');
      [*] = ;
      [*] = ;                  IntRegister0 := 0;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'IsHealTarget');
      [*] = ;                  var isHealTarget : Boolean = (IntRegister1 > 0);
      [*] = ;
      [*] = ;                  if (canHeal < moveMap) and (shoot > 0) and isHealTarget then
      [*] = ;                  begin
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHealTarget, 'CanHeal', moveMap);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHealTarget, 'GridX', gridX);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHealTarget, 'GridY', gridY);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // DEBUG
      [*] = ;   {if gBoolRegister_IsHumanPlayer then
      [*] = ;   begin
      [*] = ;      Log('Heal targets for ' + myCustomName);
      [*] = ;      for i := ParserGetCountByHandle(pHealTargets)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pHealTarget : Integer = ParserSelectByHandleByIndex(pHealTargets, i);
      [*] = ;         var canHeal : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'CanHeal');
      [*] = ;         var gridX : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'GridX');
      [*] = ;         var gridY : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'GridY');
      [*] = ;
      [*] = ;         if canHeal > 0 then
      [*] = ;         begin
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;            var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;            var goY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;            Log('____________________________');
      [*] = ;            Log('CanHeal = ' + IntToStr(canHeal));
      [*] = ;            Log('HealGridX = ' + IntToStr(gridX));
      [*] = ;            Log('HealGridY = ' + IntToStr(gridY));
      [*] = ;            Log('TargetGridX = ' + IntToStr(goX));
      [*] = ;            Log('TargetGridY = ' + IntToStr(goY));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;{}
      [*] = ;   // DEBUG
      [*] = ;end;
      [*] = ;
      [*] = ;// shoot targets
      [*] = ;if (rangedAttack > 0) and (curAmmo > 0) and bCanShoot then
      [*] = ;begin
      [*] = ;   ExecuteState('Select');
      [*] = ;
      [*] = ;   // shoot targets from current position
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;
      [*] = ;      var pShootTarget : Integer = ParserAddChildByIndex(pShootTargets, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pShootTarget, 'CanRange', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pShootTarget, 'GridX', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pShootTarget, 'GridY', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;      var stealthMode : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;      var pShootTarget : Integer = ParserSelectByHandleByIndex(pShootTargets, i);
      [*] = ;
      [*] = ;      if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not stealthMode) then
      [*] = ;      begin
      [*] = ;         var enGridX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;         var enGridY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;         if gBoolRegister_BattleSimulate then
      [*] = ;         begin
      [*] = ;            if Abs(enGridX - myGridX) < movePoints + range then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pShootTarget, 'CanRange', 3);
      [*] = ;               ParserSetIntValueByKeyByHandle(pShootTarget, 'GridX', myGridX);
      [*] = ;
      [*] = ;               if Abs(enGridX - myGridX) > range then
      [*] = ;               begin
      [*] = ;                  var dist : Integer = Round(Abs(enGridX - myGridX) - range);
      [*] = ;                  if enGridX < myGridX then
      [*] = ;                  dist := -dist;
      [*] = ;
      [*] = ;                  var shootX : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'GridX');
      [*] = ;                  shootX := shootX + dist;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pShootTarget, 'GridX', shootX);
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pShootTarget, 'CanRange', 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var gridInd : Integer = gc_battle_GridSize * enGridY + enGridX;
      [*] = ;
      [*] = ;            var pEnHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, gridInd);
      [*] = ;            var shootMap : Integer = ParserGetIntValueByKeyByHandle(pEnHexCell, 'Shoot');
      [*] = ;
      [*] = ;            if shootMap = 2 then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pShootTarget, 'CanRange', 3);
      [*] = ;               ParserSetIntValueByKeyByHandle(pShootTarget, 'GridX', myGridX);
      [*] = ;               ParserSetIntValueByKeyByHandle(pShootTarget, 'GridY', myGridY);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // shoot targets not from current position
      [*] = ;   if not gBoolRegister_BattleSimulate then
      [*] = ;   begin
      [*] = ;      FillMoveMap();
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;         var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;         var moveMap : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'MoveMap');
      [*] = ;
      [*] = ;         if (moveMap > 0) and (uid = 0) then
      [*] = ;         begin
      [*] = ;            var gridX : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'X');
      [*] = ;            var gridY : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Y');
      [*] = ;
      [*] = ;            IntRegister0 := gridX;
      [*] = ;            IntRegister1 := gridY;
      [*] = ;            ExecuteState('GetUpdShootingRange');
      [*] = ;            var uShootRange : Integer = IntRegister2;
      [*] = ;
      [*] = ;            IntRegister0 := gridX;
      [*] = ;            IntRegister1 := gridY;
      [*] = ;            IntRegister2 := uShootRange;
      [*] = ;            ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;            for j := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var enGOHandle : Integer = GetGameObjectHandleByIndex(j, enPlHandle);
      [*] = ;               var stealthMode : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;               if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not stealthMode) then
      [*] = ;               begin
      [*] = ;                  var pShootTarget : Integer = ParserSelectByHandleByIndex(pShootTargets, j);
      [*] = ;                  var canRange : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'CanRange');
      [*] = ;
      [*] = ;                  var enGridX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var enGridY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;                  var gridInd : Integer = gc_battle_GridSize * enGridY + enGridX;
      [*] = ;
      [*] = ;                  var pEnHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, gridInd);
      [*] = ;                  var shoot : Integer = ParserGetIntValueByKeyByHandle(pEnHexCell, 'Shoot');
      [*] = ;
      [*] = ;                  if (canRange < moveMap) and (shoot > 1) then
      [*] = ;                  begin
      [*] = ;                     ParserSetIntValueByKeyByHandle(pShootTarget, 'CanRange', moveMap);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pShootTarget, 'GridX', gridX);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pShootTarget, 'GridY', gridY);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // DEBUG
      [*] = ;   {if gBoolRegister_IsHumanPlayer then
      [*] = ;   begin
      [*] = ;      Log('Shoot targets for ' + myCustomName);
      [*] = ;      for i := ParserGetCountByHandle(pShootTargets)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pShootTarget : Integer = ParserSelectByHandleByIndex(pShootTargets, i);
      [*] = ;         var canRange : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'CanRange');
      [*] = ;         var gridX : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'GridX');
      [*] = ;         var gridY : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'GridY');
      [*] = ;
      [*] = ;         if canRange > 0 then
      [*] = ;         begin
      [*] = ;            var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;            var goX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;            var goY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;            Log('____________________________');
      [*] = ;            Log('CanRange = ' + IntToStr(canRange));
      [*] = ;            Log('ShootGridX = ' + IntToStr(gridX));
      [*] = ;            Log('ShootGridY = ' + IntToStr(gridY));
      [*] = ;            Log('TargetGridX = ' + IntToStr(goX));
      [*] = ;            Log('TargetGridY = ' + IntToStr(goY));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   // DEBUG{}
      [*] = ;end;
      [*] = ;
      [*] = ;// melee targets
      [*] = ;if bCanMelee then
      [*] = ;begin
      [*] = ;   ExecuteState('Select');
      [*] = ;   for i := 0 to GetPlayerGameObjectsCountByHandle(enPlHandle)-1 do
      [*] = ;   begin
      [*] = ;      var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;      var stealthMode : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;      var pMeleeTarget : Integer = ParserAddChildByIndex(pMeleeTargets, '*');
      [*] = ;   
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridX', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridY', 0);
      [*] = ;   
      [*] = ;      if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not stealthMode) then
      [*] = ;      begin
      [*] = ;         var enGridX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;         var enGridY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;   
      [*] = ;         if not gBoolRegister_BattleSimulate then
      [*] = ;         begin
      [*] = ;            var x : Integer = enGridX - 1 + enGridY mod 2;
      [*] = ;            var y : Integer = enGridY - 1;
      [*] = ;   
      [*] = ;            var meleeRange : Integer = AIInMeleeRange(x, y);
      [*] = ;            if meleeRange > 0 then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', meleeRange);
      [*] = ;               ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridX', x);
      [*] = ;               ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridY', y);
      [*] = ;            end;
      [*] = ;   
      [*] = ;            CheckBetterPlace(enGridX + enGridY mod 2, enGridY - 1, pMeleeTarget);
      [*] = ;            CheckBetterPlace(enGridX + 1, enGridY, pMeleeTarget);
      [*] = ;            CheckBetterPlace(enGridX + enGridY mod 2, enGridY + 1, pMeleeTarget);
      [*] = ;            CheckBetterPlace(enGridX - 1 + enGridY mod 2, enGridY + 1, pMeleeTarget);
      [*] = ;            CheckBetterPlace(enGridX - 1 , enGridY, pMeleeTarget);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if Abs(enGridX - myGridX) <= movePoints + 1 then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', 3);
      [*] = ;               ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridX', myGridX);
      [*] = ;   
      [*] = ;               if Abs(enGridX - myGridX) > 1 then
      [*] = ;               begin
      [*] = ;                  var dist : Integer = Round(Abs(enGridX - myGridX) - 1);
      [*] = ;                  if enGridX < myGridX then
      [*] = ;                     dist := -dist;
      [*] = ;   
      [*] = ;                  var meleeX : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridX');
      [*] = ;                  meleeX := meleeX + dist;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pMeleeTarget, 'GridX', meleeX);
      [*] = ;   
      [*] = ;                  ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// DEBUG
      [*] = ;{if gBoolRegister_IsHumanPlayer then
      [*] = ;begin
      [*] = ;   Log('Melee targets for ' + myCustomName);
      [*] = ;   for i := 0 to ParserGetCountByHandle(pMeleeTargets)-1 do
      [*] = ;   begin
      [*] = ;      var pMeleeTarget : Integer = ParserSelectByHandleByIndex(pMeleeTargets, i);
      [*] = ;      var canMelee : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee');
      [*] = ;      var gridX : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridX');
      [*] = ;      var gridY : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridY');
      [*] = ;
      [*] = ;      if canMelee > 0 then
      [*] = ;      begin
      [*] = ;         var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;         var goX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;         var goY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;         Log('____________________________');
      [*] = ;         Log('CanMelee = ' + IntToStr(canMelee));
      [*] = ;         Log('MeleeGridX = ' + IntToStr(gridX));
      [*] = ;         Log('MeleeGridY = ' + IntToStr(gridY));
      [*] = ;         Log('TargetGridX = ' + IntToStr(goX));
      [*] = ;         Log('TargetGridY = ' + IntToStr(goY));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;// DEBUG{}
      [*] = ;
      [*] = ;// estimate targets
      [*] = ;
      [*] = ;var willStrike : Integer = -1;
      [*] = ;var meleeHit : Integer = 0;
      [*] = ;var willShoot : Integer = -1;
      [*] = ;var shootHit : Integer = 0;
      [*] = ;var willHeal : Integer = -1;
      [*] = ;var healHit : Integer = 0;
      [*] = ;var taste : Integer = -1000;
      [*] = ;var taste1 : Integer;
      [*] = ;var killShoot : Boolean = false;
      [*] = ;var killMelee : Boolean = false;
      [*] = ;var antiHit : Integer;
      [*] = ;
      [*] = ;var enemyArmy : Integer = 0;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;   if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;   begin
      [*] = ;      if CheckRangedHit(goHandle) <= 0 then
      [*] = ;      begin
      [*] = ;         if CheckMeleeHit(goHandle) > 0 then
      [*] = ;            enemyArmy := enemyArmy + 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         enemyArmy := enemyArmy + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var ourArmy : Integer = 0;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   if GetGameObjectPlayableObjectByHandle(GetGameObjectHandleByIndex(i, myPlHandle)) then
      [*] = ;      ourArmy := ourArmy + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;// estimate heal targets
      [*] = ;if (healAbility > 0) and (curAmmo > 0) and bCanShoot then
      [*] = ;begin
      [*] = ;   for i := ParserGetCountByHandle(pHealTargets)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHealTarget : Integer = ParserSelectByHandleByIndex(pHealTargets, i);
      [*] = ;      var canHeal : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'CanHeal');
      [*] = ;
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iDefence;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      var goDefence : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iRangedDefence;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      var goRangedDefence : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iResist;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      var goResist : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var isHero : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;      if canHeal > 0 then
      [*] = ;      begin
      [*] = ;         var hit : Integer = healAbility;
      [*] = ;
      [*] = ;         var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;         var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if maxLife - curLife < hit then
      [*] = ;            hit := maxLife - curLife;
      [*] = ;
      [*] = ;         taste1 := hit * 5 + goDefence + goRangedDefence + goResist + (canHeal - 1) * 2;
      [*] = ;         if isHero then
      [*] = ;         begin
      [*] = ;            var uid : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iHeroUID);
      [*] = ;            var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;            var class1 : Integer = GetGameObjectIntValueIndByHandle(mapHeroHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;            taste1 := taste1 + hit * (class1 div 2);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if canHeal = 1 then
      [*] = ;            taste1 := taste1 div 2;
      [*] = ;
      [*] = ;         IntRegister0 := 73;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         if IntRegister1 > 0 then
      [*] = ;            taste1 := -2000;
      [*] = ;
      [*] = ;         if taste1 > taste then
      [*] = ;         begin
      [*] = ;            taste := taste1;
      [*] = ;            willHeal := i;
      [*] = ;            healHit := hit;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// estimate shoot targets
      [*] = ;if (rangedAttack > 0) and (curAmmo > 0) and bCanShoot then
      [*] = ;begin
      [*] = ;   taste := -1000;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pShootTargets)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pShootTarget : Integer = ParserSelectByHandleByIndex(pShootTargets, i);
      [*] = ;      var canRange : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'CanRange');
      [*] = ;
      [*] = ;      if canRange > 0 then
      [*] = ;      begin
      [*] = ;         var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;         var enCurLife : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurLife);
      [*] = ;         var enCurAmmo : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurAmmo);
      [*] = ;         var enIsHero : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bIsHero);
      [*] = ;         var enIsSummoned : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bSummoned);
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iAttack;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iCounterAttack;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enCounterAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enRangedAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iResist;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enResist : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_immobilized;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;         var enAbil36 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var myTaste : Integer = 0;
      [*] = ;         var myHit : Integer = 0;
      [*] = ;
      [*] = ;         // web
      [*] = ;         if abil47 > 0 then
      [*] = ;         begin
      [*] = ;            var enAbil109 : Integer = _unit_CheckAbility(enGOHandle, gc_ability_web_immunity);
      [*] = ;
      [*] = ;            if (ourArmy > 2) and (enAbil109 = 0) then
      [*] = ;            begin
      [*] = ;               myTaste := enCurLife div 2;
      [*] = ;               myHit := enCurLife div 4;
      [*] = ;
      [*] = ;               if enIsHero then
      [*] = ;               begin
      [*] = ;                  myTaste := myTaste * 2;
      [*] = ;                  myHit := myHit * 2;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if abil47 > enAttack then
      [*] = ;                  myTaste := myTaste * 2;
      [*] = ;
      [*] = ;               if enAbil36 > 0 then
      [*] = ;               begin
      [*] = ;                  myTaste := myTaste div 3;
      [*] = ;                  myHit := myHit div 3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            // stone spell
      [*] = ;            if abil46 > 0 then
      [*] = ;            begin
      [*] = ;               if (enAbil36 = 0) and (ourArmy > 2) and (abil46 > enResist) then
      [*] = ;               begin
      [*] = ;                  myTaste := (abil46 - enResist - 1) * (enCurLife div 2 + enAttack);
      [*] = ;                  myHit := (abil46 - enResist - 1) * (enCurLife div 4 + enAttack);
      [*] = ;
      [*] = ;                  if enIsHero then
      [*] = ;                  begin
      [*] = ;                     myTaste := myTaste * 2;
      [*] = ;                     myHit := myHit * 2;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var enAbil108 : Integer = _unit_CheckAbility(enGOHandle, 108);
      [*] = ;
      [*] = ;               if (abil46 <= enResist) or (enAbil108 > 0) then
      [*] = ;               begin
      [*] = ;                  myTaste := -2000;
      [*] = ;                  myHit := -3;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               // normal shot
      [*] = ;               IntRegister0 := enGOHandle;
      [*] = ;               ExecuteState('AI_CalcRangedHit');
      [*] = ;               myHit := IntRegister1;
      [*] = ;
      [*] = ;               IntRegister0 := gc_battle_unit_iCurAmmo;
      [*] = ;               ExecuteState('GetProperty');
      [*] = ;               if IntRegister1 > 1 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gc_ability_double_shot;
      [*] = ;                  ExecuteState('CheckAbility');
      [*] = ;                  var abil20 : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  // double shot
      [*] = ;                  if (myHit < enCurLife) and (canRange = 3) and (abil20 > 0) and (curStamina >= abil20) then
      [*] = ;                  begin
      [*] = ;                     myHit := myHit * 2;
      [*] = ;                     ParserSetIntValueByKeyByHandle(pShootTarget, 'CanRange', 4);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               IntRegister0 := gc_ability_poison_immunity;
      [*] = ;               GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;               var enAbil42 : Integer = IntRegister1;
      [*] = ;
      [*] = ;               IntRegister0 := gc_ability_poison_shot;
      [*] = ;               ExecuteState('CheckAbility');
      [*] = ;               var abil78 : Integer = IntRegister1;
      [*] = ;
      [*] = ;               // poison shot
      [*] = ;               if (enAbil42 = 0) and (myHit < enCurLife) then
      [*] = ;                  myHit := myHit + abil78 * 2;
      [*] = ;
      [*] = ;               myTaste := Round(myHit * 2 - Abs(myHit - enCurLife - 1));
      [*] = ;               var adder : Integer = (enAttack + enCounterAttack) div 5;
      [*] = ;               adder := adder + (enRangedAttack * enCurAmmo) div 5;
      [*] = ;
      [*] = ;               if enIsSummoned then
      [*] = ;                  adder := adder - 3;
      [*] = ;
      [*] = ;               if enIsHero then
      [*] = ;               begin
      [*] = ;                  var uid : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iHeroUID);
      [*] = ;                  var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;                  var enClass1 : Integer = GetGameObjectIntValueIndByHandle(mapHeroHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;                  adder := adder + myHit * (enClass1 div 2);
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (myHit >= shootHit div 2) or (myHit >= enCurLife) then
      [*] = ;                  myTaste := myTaste + adder;
      [*] = ;
      [*] = ;               if (adder > 0) and (myHit >= enCurLife) then
      [*] = ;                  myTaste := myTaste + adder;
      [*] = ;
      [*] = ;               if ParserGetIntValueByKeyByHandle(pShootTarget, 'CanRange') = 1 then
      [*] = ;                  myTaste := myTaste div 2;
      [*] = ;
      [*] = ;               // don't damage my units under spell
      [*] = ;               IntRegister0 := 73;
      [*] = ;               GameObjectExecuteStateByHandle(enGOHandle, 'GetEffectDurationByAbility');
      [*] = ;               var dur73 : Integer = IntRegister1;
      [*] = ;
      [*] = ;               if (dur73 > 0) and (dur73 < 3) then
      [*] = ;                  myTaste := -2000;
      [*] = ;
      [*] = ;               if (myTaste > 0) and (dur73 > 0)  then
      [*] = ;                  myTaste := myTaste div 10;
      [*] = ;
      [*] = ;               IntRegister0 := 70;
      [*] = ;               GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;               var enAbil70 : Integer = IntRegister1;
      [*] = ;
      [*] = ;               if (myTaste > 0) and (enAbil70 > 0) then
      [*] = ;                  myTaste := myTaste div 2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ((willShoot < 0) and (enemyArmy = 0)) or ((myHit > 0) and (myTaste > taste)) then
      [*] = ;         begin
      [*] = ;            taste := myTaste;
      [*] = ;            willShoot := i;
      [*] = ;            shootHit := myHit;
      [*] = ;            killShoot := (myHit >= enCurLife);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// estimate melee targets
      [*] = ;IntRegister0 := gc_ability_does_not_fight;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;if (IntRegister1 = 0) and bCanMelee then
      [*] = ;begin
      [*] = ;   taste := -1000;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pMeleeTargets)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMeleeTarget : Integer = ParserSelectByHandleByIndex(pMeleeTargets, i);
      [*] = ;      var canMelee : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee');
      [*] = ;
      [*] = ;      if canMelee > 0 then
      [*] = ;      begin
      [*] = ;         var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;         var enCurLife : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurLife);
      [*] = ;         var enCurStamina : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;         var enCurAmmo : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurAmmo);
      [*] = ;         var enResting : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bResting);
      [*] = ;         var enIsHero : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bIsHero);
      [*] = ;         var enIsSummoned : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bSummoned);
      [*] = ;
      [*] = ;         var enUnitID : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iUnitID);
      [*] = ;         var pEnUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, enUnitID);
      [*] = ;         var enUnitType : Integer = ParserGetIntValueByKeyByHandle(pEnUnit, 'UnitType');
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iAttack;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iCounterAttack;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enCounterAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;         var enRangedAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_magic_strike;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;         var enAbil27 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := enGOHandle;
      [*] = ;         ExecuteState('AI_CalcMeleeHit');
      [*] = ;         var hit : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_crushing_blow;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         var abil59 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if (hit < enCurLife) and (abil59 > 0) and (curStamina > abil59) and (canMelee > 1) then
      [*] = ;         begin
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCrush, true);
      [*] = ;            IntRegister0 := enGOHandle;
      [*] = ;            ExecuteState('AI_CalcMeleeHit');
      [*] = ;            hit := IntRegister1;
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCrush, false);
      [*] = ;            ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', 5);
      [*] = ;         end;
      [*] = ;
      [*] = ;         // check vampire on counter attack
      [*] = ;         IntRegister0 := gc_ability_first_strike;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;         var enAbil16 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_vampire;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;         var enAbil68 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_cunning;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         var abil26 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if ((hit < enCurLife) or (enAbil16 > 0)) and (enAbil68 > 0) and (abil26 = 0) and (myUnitType <> 2) and (myUnitType <> 4) and (enCurStamina > 0) and (not enResting) then
      [*] = ;         begin
      [*] = ;            if enAbil27 > 0 then
      [*] = ;               antiHit := enCounterAttack - resist
      [*] = ;            else
      [*] = ;               antiHit := enCounterAttack - defence;
      [*] = ;
      [*] = ;            if antiHit > curLife then
      [*] = ;               antiHit := curLife;
      [*] = ;
      [*] = ;            antiHit := (antiHit * enAbil68) div 100;
      [*] = ;
      [*] = ;            if antiHit > 0 then
      [*] = ;               hit := hit - antiHit;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var myTaste : Integer = Round(hit * 2 - Abs(hit - enCurLife - 1));
      [*] = ;
      [*] = ;         // don't damage my units under spell
      [*] = ;         IntRegister0 := 73;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetEffectDurationByAbility');
      [*] = ;         var dur73 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if (dur73 > 0) and (dur73 < 3) then
      [*] = ;            myTaste := -2000;
      [*] = ;
      [*] = ;         if hit < enCurLife then
      [*] = ;         begin
      [*] = ;            // check poison
      [*] = ;            IntRegister0 := gc_ability_poison_attack;
      [*] = ;            ExecuteState('CheckAbility');
      [*] = ;            var abil41 : Integer = IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := gc_ability_poison_immunity;
      [*] = ;            GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;            if IntRegister1 = 0 then
      [*] = ;               myTaste := myTaste + abil41 * 3;
      [*] = ;
      [*] = ;            // TODO: don't hit transformed into dragons
      [*] = ;            //if ((Squad[1-AA][i].pUnit->GetUnitType()==60)&&(Squad[1-AA][i].pUnit!=Squad[1-AA][i].pTrueForm)&&(Hit<20))
      [*] = ;            //MyTaste=-2000;;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // check trample
      [*] = ;         IntRegister0 := gc_ability_trumpling;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         var abil63 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if (hit < enCurLife) and (abil63 >= enCurLife - hit) then
      [*] = ;         begin
      [*] = ;            hit := enCurLife;
      [*] = ;            myTaste := hit * 2;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // check life drain
      [*] = ;         if (hit > 0) and (enUnitType <> 2) and (enUnitType <> 4) and (curLife < maxLife) then
      [*] = ;         begin
      [*] = ;            if abil68 > 0 then
      [*] = ;               myTaste := myTaste + 2 * Min((hit * abil68) div 100, maxLife - curLife);
      [*] = ;            if (abil57 > 0) and (hit >= enCurLife) then
      [*] = ;               myTaste := myTaste + 2 * Min(abil57, maxLife - curLife);
      [*] = ;         end;
      [*] = ;
      [*] = ;         // round attack
      [*] = ;         IntRegister0 := gc_ability_common_attack;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         var abil65 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_round_attack;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         var abil66 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if (abil65 > 0) or ((abil66 > 0) and (curStamina > abil66)) then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := false;
      [*] = ;            IntRegister0 := ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridX');
      [*] = ;            IntRegister1 := ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridY');
      [*] = ;            ExecuteState('FindNeighbour');
      [*] = ;            var neigh : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if neigh > 1 then
      [*] = ;            begin
      [*] = ;               if (abil66 > 0) and (curStamina > abil66) then
      [*] = ;                  ParserSetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee', canMelee + 100);
      [*] = ;
      [*] = ;               for j := ParserGetCountByHandle(pMyNeighbours)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pMyNeighbour : Integer = ParserSelectByHandleByIndex(pMyNeighbours, j);
      [*] = ;                  var uid : Integer = ParserGetIntValueByKeyByHandle(pMyNeighbour, 'UID');
      [*] = ;                  var nGOHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;
      [*] = ;                  if nGOHandle <> enGOHandle then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := nGOHandle;
      [*] = ;                     ExecuteState('AI_CalcMeleeHit');
      [*] = ;                     var neighHit : Integer = IntRegister1;
      [*] = ;
      [*] = ;                     hit := hit + neighHit;
      [*] = ;                     myTaste := myTaste + neighHit * 2;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_immobilized;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;         var enAbil36 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var adder : Integer = enAbil36 * 5;
      [*] = ;         adder := adder + enAttack div 2;
      [*] = ;
      [*] = ;         if enIsSummoned then
      [*] = ;            adder := adder - 3;
      [*] = ;
      [*] = ;         // check counter attack
      [*] = ;         if (hit < enCurLife) and (abil26 = 0) and (enCurStamina > 0) and (not enResting) then
      [*] = ;         begin
      [*] = ;            if enAbil27 > 0 then
      [*] = ;               antiHit := enCounterAttack - resist
      [*] = ;            else
      [*] = ;               antiHit := enCounterAttack - defence;
      [*] = ;
      [*] = ;            if antiHit > curLife then
      [*] = ;               antiHit := curLife;
      [*] = ;
      [*] = ;            adder := adder - antiHit;
      [*] = ;         end;
      [*] = ;
      [*] = ;         adder := adder + (enRangedAttack * enCurAmmo) div 5;
      [*] = ;
      [*] = ;         if enIsHero then
      [*] = ;         begin
      [*] = ;            var uid : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iHeroUID);
      [*] = ;            var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;            var enClass1 : Integer = GetGameObjectIntValueIndByHandle(mapHeroHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;            adder := adder + hit * (enClass1 div 2);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (hit >= meleeHit div 2) or (hit >= enCurLife) then
      [*] = ;            myTaste := myTaste + adder;
      [*] = ;
      [*] = ;         if (adder > 0) and (hit >= enCurLife) then
      [*] = ;            myTaste := myTaste + adder;
      [*] = ;
      [*] = ;         if (myTaste > 0) and (dur73 > 0) then
      [*] = ;            myTaste := myTaste div 10;
      [*] = ;
      [*] = ;         IntRegister0 := 70;
      [*] = ;         GameObjectExecuteStateByHandle(enGOHandle, 'GetEffectDurationByAbility');
      [*] = ;         var dur70 : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if (myTaste > 0) and (dur70 > 1) then
      [*] = ;            myTaste := myTaste div dur70;
      [*] = ;
      [*] = ;         if (ParserGetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee') = 1) and (myTaste > 0) then
      [*] = ;            myTaste := myTaste div 2;
      [*] = ;
      [*] = ;         if ((willStrike < 0) and (enemyArmy = 0)) or ((hit > 0) and (myTaste > taste)) then
      [*] = ;         begin
      [*] = ;            taste := myTaste;
      [*] = ;            willStrike := i;
      [*] = ;            meleeHit := hit;
      [*] = ;            killMelee := (hit >= enCurLife);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// choose action
      [*] = ;var indexAI : Integer;
      [*] = ;ExecuteState('Select');
      [*] = ;
      [*] = ;// choose spell
      [*] = ;if (chosenSpell >= 0) and (spellHit >= shootHit) and (spellHit >= meleeHit) and (spellHit >= healHit) then
      [*] = ;begin
      [*] = ;   var indexAI : Integer = -1;
      [*] = ;   var spellID : Integer = arCast[chosenSpell];
      [*] = ;
      [*] = ;   IntRegister0 := spellID;
      [*] = ;   MapExecuteState('GetSpellParserByID');
      [*] = ;   var pSpell : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var spTarget : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Target');
      [*] = ;   var spArea : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;   var spRadius : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Radius');
      [*] = ;   var spOnAlly : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnAlly');
      [*] = ;   var spOnEnemy : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'OnEnemy');
      [*] = ;   var spSacrifice : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Sacrifice');
      [*] = ;   var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;
      [*] = ;   var pSpellEffect0 : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect0, 'AbilityID');
      [*] = ;
      [*] = ;   if spSacrifice then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'GetSpellVictimUID');
      [*] = ;      gIntRegister_SacrificeUID := IntRegister0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   case spTarget of
      [*] = ;      1 : begin
      [*] = ;         var tGOHandle : Integer = GetGameObjectHandleByUniqueId(spellTargetUID);
      [*] = ;
      [*] = ;         if abilID = gc_ability_teleport then
      [*] = ;         begin
      [*] = ;            // teleport
      [*] = ;            var bigHit : Integer = 0;
      [*] = ;            var spX : Integer = 0;
      [*] = ;            var spY : Integer = 0;
      [*] = ;
      [*] = ;            for x := 0 to gc_battle_GridSize-1 do
      [*] = ;            begin
      [*] = ;               for y := 0 to gc_battle_GridSize-1 do
      [*] = ;               begin
      [*] = ;                  IntRegister0 := x;
      [*] = ;                  IntRegister1 := y;
      [*] = ;                  GameObjectExecuteStateByHandle(tGOHandle, 'GetTeleportTaste');
      [*] = ;                  var hit : Integer = IntRegister2;
      [*] = ;
      [*] = ;                  if hit > bigHit then
      [*] = ;                  begin
      [*] = ;                     bigHit := hit;
      [*] = ;                     spX := x;
      [*] = ;                     spY := y;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            gIntRegister_TeleportUID := spellTargetUID;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            IntRegister1 := ParserSelectByHandleByIndex(pHexCells, gc_battle_GridSize * spY + spX);
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('CastSpell');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var gridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;            var gridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;            var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;            var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;            var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;
      [*] = ;            //Squad[SpellTarget1][SpellTarget2].UnderSpell(SP,ActiveUnit,AA);
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            IntRegister1 := pHexCell;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('CastSpell');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      2, 4 : begin
      [*] = ;         var tGOHandle : Integer = GetGameObjectHandleByUniqueId(spellTargetUID);
      [*] = ;
      [*] = ;         var gridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;         var gridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;         var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;         //CorpseSpell(SP,&Squad[SpellTarget1][SpellTarget2]);
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         IntRegister1 := pHexCell;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         ExecuteState('CastSpell');
      [*] = ;      end;
      [*] = ;      5 : begin
      [*] = ;         var ind : Integer = gc_battle_GridSize * spellTargetY + spellTargetX;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;         //TileSpell(SP,SpellTarget1,SpellTarget2);
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         IntRegister1 := pHexCell;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         ExecuteState('CastSpell');
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         //IntRegister0 := spellTargetX;
      [*] = ;         //IntRegister1 := spellTargetY;
      [*] = ;         //IntRegister2 := spRadius;
      [*] = ;         //ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;         var ind : Integer = gc_battle_GridSize * spellTargetY + spellTargetX;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         IntRegister1 := pHexCell;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         ExecuteState('CastSpell');
      [*] = ;      end;
      [*] = ;      0 : begin
      [*] = ;         if spArea = 2 then
      [*] = ;         begin
      [*] = ;            var ind : Integer = gc_battle_GridSize * spellTargetY + spellTargetX;
      [*] = ;            var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            IntRegister1 := pHexCell;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('CastSpell');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //IntRegister0 := spellID;
      [*] = ;   //ExecuteState('AfterAISpellCast');
      [*] = ;   //if spellTargetUID <> 0 then
      [*] = ;   {if (not gBoolRegister_BattleSimulate) and (not gBoolRegister_QuickBattle) then
      [*] = ;   begin
      [*] = ;      if spTarget = 1 then
      [*] = ;      begin
      [*] = ;         var tGOHandle : Integer = GetGameObjectHandleByUniqueId(spellTargetUID);
      [*] = ;         var tCustomName : String = GetGameObjectCustomNameByHandle(tGOHandle);
      [*] = ;         //Log(myCustomName + ' cast spell ' + IntToStr(spellID) + ' on ' + tCustomName);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         //Log(myCustomName + ' cast spell ' + IntToStr(spellID) + ' on (' + IntToStr(spellTargetX) + ', ' + IntToStr(spellTargetY) + ')');
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   bAct := true;
      [*] = ;end;
      [*] = ;
      [*] = ;// choose heal target
      [*] = ;if not bAct then
      [*] = ;begin
      [*] = ;   if (willHeal >= 0) and (healHit >= shootHit) and (healHit >= meleeHit) then
      [*] = ;   begin
      [*] = ;      indexAI := -1;
      [*] = ;
      [*] = ;      var pHealTarget : Integer = ParserSelectByHandleByIndex(pHealTargets, willHeal);
      [*] = ;      var tGOHandle : Integer = GetGameObjectHandleByIndex(willHeal, myPlHandle);
      [*] = ;
      [*] = ;      var canHeal : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'CanHeal');
      [*] = ;      var tGridX : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'GridX');
      [*] = ;      var tGridY : Integer = ParserGetIntValueByKeyByHandle(pHealTarget, 'GridY');
      [*] = ;      var tInd : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;      var tTnHandle : Integer = GetTrackNodeHandleByIndex(tInd);
      [*] = ;
      [*] = ;      bAct := true;
      [*] = ;
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;      begin
      [*] = ;         if (myGridX = tGridX) and (myGridY = tGridY) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := tGOHandle;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('HealUnit');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if canHeal = 1 then
      [*] = ;               ExecuteState('GoMarch');
      [*] = ;
      [*] = ;            IntRegister0 := tTnHandle;
      [*] = ;            IntRegister1 := GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;            IntRegister2 := 3;
      [*] = ;            ExecuteState('Position');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               if _log then ErrorLogI(_log_name+' Warning(heal): unit positioning to '+IntToStr(tGridX)+','+IntToStr(tGridY)+'failed');
      [*] = ;               bAct := false;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := tGridX;
      [*] = ;         IntRegister1 := myGridY;
      [*] = ;         IntRegister2 := GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;         IntRegister3 := 3;
      [*] = ;         ExecuteState('DoPositionByCoords');
      [*] = ;      end;
      [*] = ;      //Log(myCustomName + ' heals ' + GetGameObjectCustomNameByHandle(tGOHandle));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// choose shoot target
      [*] = ;if not bAct then
      [*] = ;begin
      [*] = ;   if (willShoot >= 0) and ((shootHit >= meleeHit) or killShoot or ((curAmmo > 3) and (attack < rangedAttack) and (shootHit >= meleeHit div 2))) and ((not killMelee) or killShoot) then
      [*] = ;   begin
      [*] = ;      indexAI := -1;
      [*] = ;
      [*] = ;      var pShootTarget : Integer = ParserSelectByHandleByIndex(pShootTargets, willShoot);
      [*] = ;      var tGOHandle : Integer = GetGameObjectHandleByIndex(willShoot, enPlHandle);
      [*] = ;
      [*] = ;      var canRange : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'CanRange');
      [*] = ;      var tGridX : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'GridX');
      [*] = ;      var tGridY : Integer = ParserGetIntValueByKeyByHandle(pShootTarget, 'GridY');
      [*] = ;      var tInd : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;      var tTnHandle : Integer = GetTrackNodeHandleByIndex(tInd);
      [*] = ;
      [*] = ;      bAct := true;
      [*] = ;
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;      begin
      [*] = ;         if (myGridX = tGridX) and (myGridY = tGridY) then
      [*] = ;         begin
      [*] = ;            // double shot
      [*] = ;            if canRange = 4 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := gc_ability_double_shot;
      [*] = ;               ExecuteState('ActivateAbility');
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, GetGameObjectUniqueIdByHandle(tGOHandle));
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('FireAttack');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if canRange = 1 then
      [*] = ;               ExecuteState('GoMarch');
      [*] = ;
      [*] = ;            IntRegister0 := tTnHandle;
      [*] = ;            IntRegister1 := GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;            IntRegister2 := 2;
      [*] = ;            ExecuteState('Position');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               if _log then ErrorLogI(_log_name+' Warning(shoot): unit positioning to '+IntToStr(tGridX)+','+IntToStr(tGridY)+'failed');
      [*] = ;               bAct := false;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := tGridX;
      [*] = ;         IntRegister1 := myGridY;
      [*] = ;         IntRegister2 := GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;         IntRegister3 := 2;
      [*] = ;         ExecuteState('DoPositionByCoords');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// choose melee target
      [*] = ;if not bAct then
      [*] = ;begin
      [*] = ;   if willStrike >= 0 then
      [*] = ;   begin
      [*] = ;      indexAI := -1;
      [*] = ;
      [*] = ;      var pMeleeTarget : Integer = ParserSelectByHandleByIndex(pMeleeTargets, willStrike);
      [*] = ;      var tGOHandle : Integer = GetGameObjectHandleByIndex(willStrike, enPlHandle);
      [*] = ;
      [*] = ;      var canMelee : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'CanMelee');
      [*] = ;      var tGridX : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridX');
      [*] = ;      var tGridY : Integer = ParserGetIntValueByKeyByHandle(pMeleeTarget, 'GridY');
      [*] = ;      var tInd : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;      var tTnHandle : Integer = GetTrackNodeHandleByIndex(tInd);
      [*] = ;
      [*] = ;      bAct := true;
      [*] = ;
      [*] = ;      if canMelee mod 100 = 1 then
      [*] = ;         ExecuteState('GoMarch');
      [*] = ;
      [*] = ;      if canMelee mod 100 = 5 then
      [*] = ;         SetGameObjectMyBoolValueInd(gc_stack_unit_bCrush, true);
      [*] = ;
      [*] = ;      if canMelee >= 100 then
      [*] = ;         SetGameObjectMyBoolValueInd(gc_stack_unit_bRoundAttack, true);
      [*] = ;
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;      begin
      [*] = ;         if (myGridX = tGridX) and (myGridY = tGridY) then
      [*] = ;         begin
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, GetGameObjectUniqueIdByHandle(tGOHandle));
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('Attack');
      [*] = ;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            ExecuteState('CheckAttackAnimation');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := tTnHandle;
      [*] = ;            IntRegister1 := GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;            IntRegister2 := 1;
      [*] = ;            ExecuteState('Position');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               if _log then ErrorLogI(_log_name+' Warning(melee): unit positioning to '+IntToStr(tGridX)+','+IntToStr(tGridY)+'failed');
      [*] = ;               //SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, false); // something is wrong and we cant reach destination point. Exiting from dead loop.
      [*] = ;               bAct := false;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := tGridX;
      [*] = ;         IntRegister1 := myGridY;
      [*] = ;         IntRegister2 := GetGameObjectUniqueIdByHandle(tGOHandle);
      [*] = ;         IntRegister3 := 1;
      [*] = ;         ExecuteState('DoPositionByCoords');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bTurnDone, true);
      [*] = ;
      [*] = ;if bAct then
      [*] = ;begin
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;      if GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct) then
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bTurnDone, false);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var checkNearest : Boolean = true;
      [*] = ;   if not gBoolRegister_BattleSimulate then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'IsAllActionsDone');
      [*] = ;      checkNearest := BoolRegister0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if checkNearest then
      [*] = ;   begin
      [*] = ;      var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;      var movePoints : Integer = GetIntValueByIndex(gc_stack_unit_iMovePoints);
      [*] = ;      var speed : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed);
      [*] = ;
      [*] = ;      // gather ammo
      [*] = ;      if (_unit_CheckAbility(myGOHandle, gc_ability_ammo_gather) > 0) and (curAmmo = 0) then
      [*] = ;      begin
      [*] = ;         ExecuteState('GatherAmmo');
      [*] = ;         SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;         bAct := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // meditation
      [*] = ;      if not bAct then
      [*] = ;      begin
      [*] = ;         if (_unit_CheckAbility(myGOHandle, gc_ability_meditation) > 0) and (curAmmo = 0) then
      [*] = ;         begin
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bResting, true);
      [*] = ;            bAct := true;
      [*] = ;            //Log(myCustomName + ' meditates');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // resting
      [*] = ;      if not bAct then
      [*] = ;      begin
      [*] = ;         var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;         var maxStamina : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxStamina);
      [*] = ;
      [*] = ;         if (curStamina <= maxStamina div 2) and (movePoints = speed) and (GetMyAction(3) = 0) and (GetMyAction(4) = 0) then
      [*] = ;         begin
      [*] = ;            ExecuteState('SetRestMode');
      [*] = ;            bAct := true;
      [*] = ;            //Log(myCustomName + ' rests');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // first aid
      [*] = ;      if not bAct then
      [*] = ;      begin
      [*] = ;         var abil35 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_first_aid);
      [*] = ;
      [*] = ;         if (curLife < maxLife) and (movePoints = speed) and (abil35 > 0) and (GetMyAction(3) = 0) and (GetMyAction(4) = 0) then
      [*] = ;         begin
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bResting, true);
      [*] = ;            bAct := true;
      [*] = ;            //Log(myCustomName + ' makes first aid');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // flesh eater
      [*] = ;      if not bAct then
      [*] = ;      begin
      [*] = ;         var abil49 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_flesh_eater);
      [*] = ;
      [*] = ;         if (abil49 > 0) and (curLife <= maxLife div 2) then
      [*] = ;         begin
      [*] = ;            var myGridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;            var myGridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;            IntRegister0 := myGridX;
      [*] = ;            IntRegister1 := myGridY;
      [*] = ;            PlayerExecuteStateByHandle(enPlHandle, 'GetDeadUnitInHex');
      [*] = ;            var goHandle : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if goHandle = 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := myGridX;
      [*] = ;               IntRegister1 := myGridY;
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'GetDeadUnitInHex');
      [*] = ;               goHandle := IntRegister2;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if goHandle <> 0 then
      [*] = ;            begin
      [*] = ;               BoolRegister0 := true;
      [*] = ;               ExecuteState('EatCorpse');
      [*] = ;
      [*] = ;               bAct := true;
      [*] = ;               //Log(myCustomName + ' eats corpse');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ExecuteState('Select');
      [*] = ;
      [*] = ;               var goHandle : Integer = CheckCorpse(enPlHandle);
      [*] = ;               if goHandle = 0 then
      [*] = ;                  goHandle := CheckCorpse(myPlHandle);
      [*] = ;
      [*] = ;               if goHandle <> 0 then
      [*] = ;               begin
      [*] = ;                  var tGridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var tGridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;                  var tInd : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;
      [*] = ;                  bAct := true;
      [*] = ;                  if not gBoolRegister_BattleSimulate then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := GetTrackNodeHandleByIndex(tInd);
      [*] = ;                     IntRegister1 := 0;
      [*] = ;                     IntRegister2 := 4;
      [*] = ;                     ExecuteState('Position');
      [*] = ;                     if not BoolRegister0 then
      [*] = ;                     begin
      [*] = ;                        if _log then ErrorLogI(_log_name+' Warning(eat corpse): unit positioning to '+IntToStr(tGridX)+','+IntToStr(tGridY)+'failed');
      [*] = ;                        bAct := false;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     //Log(myCustomName + ' eats corpse');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := tGridX;
      [*] = ;                     IntRegister1 := myGridY;
      [*] = ;                     IntRegister2 := 0;
      [*] = ;                     IntRegister3 := 4;
      [*] = ;                     ExecuteState('DoPositionByCoords');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // choose nearest target
      [*] = ;      if not bAct then
      [*] = ;      begin
      [*] = ;         if movePoints > 0 then
      [*] = ;         begin
      [*] = ;            if not gBoolRegister_BattleSimulate then
      [*] = ;            begin
      [*] = ;               if (range > 0) and (curAmmo > 0) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := myGridX;
      [*] = ;                  IntRegister1 := myGridY;
      [*] = ;                  IntRegister2 := range;
      [*] = ;                  ExecuteState('MakeShootMap');
      [*] = ;               end;
      [*] = ;
      [*] = ;               case moveType of
      [*] = ;                  0 : begin
      [*] = ;                     ExecuteState('MakeAIStepMap');
      [*] = ;                  end;
      [*] = ;                  else begin
      [*] = ;                     BoolRegister0 := (moveType = 2);
      [*] = ;                     ExecuteState('MakeFlyMap');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;                  var pass : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Pass');
      [*] = ;                  var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;
      [*] = ;                  if (pass > 0) and (uid = 0) then
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHexCell, 'GoMap', ParserGetIntValueByKeyByHandle(pHexCell, 'Land'))
      [*] = ;                  else
      [*] = ;                     ParserSetIntValueByKeyByHandle(pHexCell, 'GoMap', 0);
      [*] = ;               end;
      [*] = ;
      [*] = ;               var way : Integer = 1000;
      [*] = ;               var x1 : Integer = gc_battle_GridSize;
      [*] = ;               var y1 : Integer = gc_battle_GridSize;
      [*] = ;               var army : Integer = 0;
      [*] = ;               var bNeedGo : Boolean = true;
      [*] = ;
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;                  if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gc_battle_unit_iAttack;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;                     var goAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;                     IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;                     var goRangedAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;                     var curAmmo : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurAmmo);
      [*] = ;
      [*] = ;                     if (goAttack + goRangedAttack * curAmmo > _unit_CheckAbility(goHandle, gc_ability_healing) * curAmmo) then
      [*] = ;                        army := army + 1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var gridX, gridY : Integer;
      [*] = ;               for gridX := 0 to gc_battle_GridSize-1 do
      [*] = ;               begin
      [*] = ;                  for gridY := 0 to gc_battle_GridSize-1 do
      [*] = ;                  begin
      [*] = ;                     var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, gc_battle_GridSize * gridY + gridX);
      [*] = ;                     var goMap : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'GoMap');
      [*] = ;
      [*] = ;                     if (goMap > 0) and (goMap < way) then
      [*] = ;                     begin
      [*] = ;                        if (healAbility * curAmmo = 0) or (attack + rangedAttack * curAmmo > healAbility * curAmmo) or (army <= 1) then
      [*] = ;                        begin
      [*] = ;                           if rangedAttack * curAmmo > 0 then
      [*] = ;                           begin
      [*] = ;                              // find shoot target
      [*] = ;                              IntRegister0 := gridX;
      [*] = ;                              IntRegister1 := gridY;
      [*] = ;                              ExecuteState('GetUpdShootingRange');
      [*] = ;                              var uShootRange : Integer = IntRegister2;
      [*] = ;
      [*] = ;                              IntRegister0 := gridX;
      [*] = ;                              IntRegister1 := gridY;
      [*] = ;                              IntRegister2 := uShootRange;
      [*] = ;                              ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;                              for j := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;                              begin
      [*] = ;                                 var enGOHandle : Integer = GetGameObjectHandleByIndex(j, enPlHandle);
      [*] = ;                                 if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode)) then
      [*] = ;                                 begin
      [*] = ;                                    var ind : Integer = gc_battle_GridSize * GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY) + GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                                    var shoot : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pHexCells, ind), 'Shoot');
      [*] = ;
      [*] = ;                                    if shoot = 2 then
      [*] = ;                                    begin
      [*] = ;                                       if ((enemyArmy = 0) or ( CheckRangedHit(enGOHandle) > 0)) then
      [*] = ;                                       begin
      [*] = ;                                          x1 := gridX;
      [*] = ;                                          y1 := gridY;
      [*] = ;                                          way := goMap;
      [*] = ;                                       end;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           // find melee target
      [*] = ;                           BoolRegister0 := false;
      [*] = ;                           BoolRegister1 := false;
      [*] = ;                           IntRegister0 := gridX;
      [*] = ;                           IntRegister1 := gridY;
      [*] = ;                           ExecuteState('FindNeighbourEx');
      [*] = ;
      [*] = ;                           for j := ParserGetCountByHandle(pMyNeighbours)-1 downto 0 do
      [*] = ;                           begin
      [*] = ;                              var pMyNeighbour : Integer = ParserSelectByHandleByIndex(pMyNeighbours, j);
      [*] = ;                              var nGOHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pMyNeighbour, 'UID'));
      [*] = ;
      [*] = ;                              //if GetGameObjectPlayableObjectByHandle(nGOHandle) and (not GetGameObjectBoolValueIndByHandle(nGOHandle, gc_stack_unit_bStealthMode)) then
      [*] = ;                              if GetGameObjectPlayableObjectByHandle(nGOHandle) then
      [*] = ;                              begin
      [*] = ;                                 if (enemyArmy = 0) or (CheckMeleeHit(nGOHandle) > 0) then
      [*] = ;                                 begin
      [*] = ;                                    x1 := gridX;
      [*] = ;                                    y1 := gridY;
      [*] = ;                                    way := goMap;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           // find heal targets
      [*] = ;                           bNeedGo := false;
      [*] = ;
      [*] = ;                           IntRegister0 := gridX;
      [*] = ;                           IntRegister1 := gridY;
      [*] = ;                           ExecuteState('GetUpdShootingRange');
      [*] = ;                           //var uShootRange : Integer = IntRegister2;
      [*] = ;
      [*] = ;                           IntRegister0 := gridX;
      [*] = ;                           IntRegister1 := gridY;
      [*] = ;                           //IntRegister2 := uShootRange; // set in prev state call
      [*] = ;                           ExecuteState('MakeShootMap');
      [*] = ;
      [*] = ;                           for j := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;                           begin
      [*] = ;                              var goHandle : Integer = GetGameObjectHandleByIndex(j, myPlHandle);
      [*] = ;                              if GetGameObjectPlayableObjectByHandle(goHandle) then
      [*] = ;                              begin
      [*] = ;                                 var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;                                 var unitType : Integer = ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(unitID), 'UnitType');
      [*] = ;
      [*] = ;                                 if (unitType <> 2) and (unitType <> 4) then
      [*] = ;                                 begin
      [*] = ;                                    var goX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                                    var goY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;                                    var shoot : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pHexCells, gc_battle_GridSize * goY + goX), 'Shoot');
      [*] = ;
      [*] = ;                                    if shoot > 0 then
      [*] = ;                                    begin
      [*] = ;                                       var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;                                       IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;                                       GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;                                       if (curLife < IntRegister1) then
      [*] = ;                                       begin
      [*] = ;                                          x1 := gridX;
      [*] = ;                                          y1 := gridY;
      [*] = ;                                          way := goMap;
      [*] = ;                                       end;
      [*] = ;                                    end;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (x1 = gc_battle_GridSize) and bNeedGo then
      [*] = ;               begin
      [*] = ;                  var dist : Integer = 50;
      [*] = ;                  var tGOHandle : Integer = 0;
      [*] = ;
      [*] = ;                  for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;                     if GetGameObjectPlayableObjectByHandle(enGOHandle) and (not GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bStealthMode)) then
      [*] = ;                     begin
      [*] = ;                        var goX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                        var goY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;                        var dist1 : Integer = Round(Abs(goX - myGridX) + Abs(goY - myGridY));
      [*] = ;
      [*] = ;                        if (dist1 < dist) then
      [*] = ;                        begin
      [*] = ;                           dist := dist1;
      [*] = ;                           // NEW
      [*] = ;                           //x1 := goX;
      [*] = ;                           //y1 := goY;
      [*] = ;                           // NEW
      [*] = ;                           tGOHandle := enGOHandle;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if dist < 50 then
      [*] = ;                  begin
      [*] = ;                     var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                     var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;                     for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;                     begin
      [*] = ;                        var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;                        var gridX : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'X');
      [*] = ;                        var gridY : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Y');
      [*] = ;                        var goMap : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'GoMap');
      [*] = ;
      [*] = ;                        var dist1 : Integer = Round(Abs(tGridX - gridX) + Abs(tGridY - gridY));
      [*] = ;                        if (goMap > 0) and (dist1 < dist) then
      [*] = ;                        begin
      [*] = ;                           dist := dist1;
      [*] = ;                           x1 := gridX;
      [*] = ;                           y1 := gridY;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if x1 < gc_battle_GridSize then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := GetTrackNodeHandleByIndex(gc_battle_GridSize * y1 + x1);
      [*] = ;                  ExecuteState('GoToPosition');
      [*] = ;
      [*] = ;                  bAct := true;
      [*] = ;                  //SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  //SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;                  //SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;
      [*] = ;                  // commented to fix healers going to attack
      [*] = ;                  // maybe this code is needed?
      [*] = ;                  {var minDanger : Integer = 1000;
      [*] = ;                  var goInd : Integer = -1;
      [*] = ;
      [*] = ;                  for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;                     var land : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'GoMap');
      [*] = ;                     var uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;
      [*] = ;                     if (land = 1) and (uid = 0) then
      [*] = ;                     begin
      [*] = ;                        var danger : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'DangerZone');
      [*] = ;                        if danger < minDanger then
      [*] = ;                        begin
      [*] = ;                           minDanger := danger;
      [*] = ;                           goInd := i;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var myDanger : Integer = ParserGetIntValueByKeyByHandle(pMyHexCell, 'DangerZone');
      [*] = ;
      [*] = ;                  if (goInd >= 0) and (minDanger < myDanger) then
      [*] = ;                  begin
      [*] = ;                     var tnHandle : Integer = GetTrackNodeHandleByIndex(goInd);
      [*] = ;
      [*] = ;                     IntRegister0 := tnHandle;
      [*] = ;                     ExecuteState('GoToPosition');
      [*] = ;
      [*] = ;                     if GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints) = 0 then
      [*] = ;                     SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;
      [*] = ;                     bAct := true;
      [*] = ;                  end
      [*] = ;                  else}
      [*] = ;                  begin
      [*] = ;                     //SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;                     //SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;                     SetBoolValueByIndex(gc_stack_unit_bBlocked, true);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               // battle simulate
      [*] = ;               var add : Integer = 0;
      [*] = ;               var dist : Integer = 10;
      [*] = ;
      [*] = ;               for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;                  var playable : Boolean = GetGameObjectPlayableObjectByHandle(enGOHandle);
      [*] = ;
      [*] = ;                  var goX : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                  var goY : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;                  var dist1 : Integer = Round(Abs(goX - myGridX));
      [*] = ;                  if playable and (dist1 < dist) then
      [*] = ;                  begin
      [*] = ;                     dist := dist1;
      [*] = ;                     if goX > myGridX then
      [*] = ;                        add := movePoints
      [*] = ;                     else
      [*] = ;                        add := -movePoints;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if add <> 0 then
      [*] = ;               begin
      [*] = ;                  var gridX : Integer = 0;
      [*] = ;                  if Abs(add) > dist then
      [*] = ;                     gridX := Round(myGridX + dist * add / Abs(add))
      [*] = ;                  else
      [*] = ;                     gridX := myGridX + add;
      [*] = ;
      [*] = ;                  gridX := Round(Clamp(gridX, 0, 7));
      [*] = ;
      [*] = ;                  IntRegister0 := gridX;
      [*] = ;                  IntRegister1 := myGridY;
      [*] = ;                  IntRegister2 := 0;
      [*] = ;                  IntRegister3 := 0;
      [*] = ;                  ExecuteState('DoPositionByCoords');
      [*] = ;
      [*] = ;                  SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;                  bAct := true;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  ErrorLogI('For some reason, there is no possible target to move towards');
      [*] = ;                  SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;if bAct and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;      if GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct) then
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bBlocked, false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _Log_Map(_log_name+' Unit name: '+myCustomName+', Act='+BoolToStr(bAct));
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;if not gBoolRegister_IsHumanPlayer then
      [*] = ;   _misc_AntiFreeze();
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

