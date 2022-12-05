section.begin
   Name = GetAllySpellTaste
   Description : struct.begin
      [*] = ;IntRegister0 - spell ID
      [*] = ;IntRegister1 - target unit UID
      [*] = ;OUT: IntRegister2 - result
      [*] = ;OUT: IntRegister3 - gain spell damage
   struct.end
   UsedFileName =
   Code : struct.begin
      [*] = ;var spellID : Integer = IntRegister0;
      [*] = ;var tUID : Integer = IntRegister1;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;var pTGOParser : Integer = ParserSelectGameObject(tGOHandle);
      [*] = ;var pTGOActions : Integer = ParserSelectByHandleByKey(pTGOParser, 'Actions');
      [*] = ;var pTGOEffects : Integer = ParserSelectByHandleByKey(pTGOParser, 'Effects');
      [*] = ;
      [*] = ;var tUnitID : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iUnitID);
      [*] = ;var pTarUnit : Integer = _unit_GetUnitParserByID(tUnitID);
      [*] = ;var tRank : Integer =  ParserGetIntValueByKeyByHandle(pTarUnit, 'Rank');
      [*] = ;
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;var tIsHero : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bIsHero);
      [*] = ;var tCanAct : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle,  gc_stack_unit_bCanAct);
      [*] = ;
      [*] = ;var gainSpDamage : Integer = 0;
      [*] = ;var antiSkill : Integer = 0;
      [*] = ;
      [*] = ;IntRegister0 := spellID;
      [*] = ;StateMachineExecuteState(initMachine, 'GetSpellParserByID', 0);
      [*] = ;var pSpell : Integer = IntRegister1;
      [*] = ;
      [*] = ;var spNegative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Negative');
      [*] = ;
      [*] = ;var spPowerMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'PowerMod');
      [*] = ;var spDurationMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'DurationMod');
      [*] = ;
      [*] = ;var spResistPower : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'ResistPower');
      [*] = ;var spResistDuration : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'ResistDuration');
      [*] = ;var spDefencePower : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'DefencePower');
      [*] = ;
      [*] = ;var spResistMod : Integer = 0;
      [*] = ;if spResistPower > 0 then
      [*] = ;spResistMod := spResistPower
      [*] = ;else
      [*] = ;spResistMod := spResistDuration;
      [*] = ;
      [*] = ;var pSpAntiEffects : Integer = ParserSelectByHandleByKey(pSpell, 'AntiEffects');
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;function GetTarAction(ind : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pTGOAction : Integer =  ParserSelectByHandleByIndex(pTGOActions, ind);
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(pTGOAction, 'Value');
      [*] = ;end;
      [*] = ;
      [*] = ;var curLife : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var maxLife : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;
      [*] = ;var tCurAmmo : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurAmmo);
      [*] = ;var tCurStamina : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;var tCurMoral : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurMoral);
      [*] = ;var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;var tAttack : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iAttack);
      [*] = ;var tCounterAttack : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iCounterAttack);
      [*] = ;var tRangedAttack : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iRangedAttack);
      [*] = ;var tDefence : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iDefence);
      [*] = ;var tRangedDefence : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iRangedDefence);
      [*] = ;var tResist : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iResist);
      [*] = ;var tSpeed : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iSpeed);
      [*] = ;var tMaxAmmo : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iMaxAmmo);
      [*] = ;var tMaxStamina : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iMaxStamina);
      [*] = ;var tMaxMoral : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iMaxMoral);
      [*] = ;var tMaxLife : Integer = _unit_GetProperty(tGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pSpAntiEffects)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pSpAntiEffect : Integer = ParserSelectByHandleByIndex(pSpAntiEffects, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpAntiEffect, 'AbilityID');
      [*] = ;
      [*] = ;   IntRegister0 := abilID;
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'CheckAbility');
      [*] = ;   antiSkill := antiSkill + IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;var tUnitType : Integer = ParserGetIntValueByKeyByHandle(pTarUnit, 'UnitType');
      [*] = ;
      [*] = ;var pSpUnitTypes : Integer = ParserSelectByHandleByKey(pSpell, 'UnitTypes');
      [*] = ;for i := ParserGetCountByHandle(pSpUnitTypes)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pSpUnitType : Integer = ParserSelectByHandleByIndex(pSpUnitTypes, i);
      [*] = ;   var spUnitType : Integer = ParserGetIntValueByKeyByHandle(pSpUnitType, 'UnitType');
      [*] = ;
      [*] = ;   if spUnitType = tUnitType then
      [*] = ;   begin
      [*] = ;      antiSkill := 1;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var res : Integer = 0;
      [*] = ;
      [*] = ;if antiSkill > 0 then
      [*] = ;res := 0
      [*] = ;else
      [*] = ;begin
      [*] = ;   var buff : Integer = 0;
      [*] = ;   var resist : Integer = 0;
      [*] = ;   var duration : Integer = 0;
      [*] = ;   var attBuff : Integer = 0;
      [*] = ;   var baseDamage : Integer = 0;
      [*] = ;   var hit : Integer = 0;
      [*] = ;   var selfHeal : Integer = 0;
      [*] = ;   var bFriendlyFire : Boolean = false;
      [*] = ;
      [*] = ;   resist := tResist;
      [*] = ;
      [*] = ;   if isHero then
      [*] = ;   resist := resist - _unit_CheckAbility(myGOHandle, 908);
      [*] = ;
      [*] = ;   resist := (resist * spResistMod) div 100;
      [*] = ;
      [*] = ;   if resist < 0 then
      [*] = ;   resist := 0;
      [*] = ;
      [*] = ;   var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pSpellEffects)-1 do
      [*] = ;   begin
      [*] = ;      var pSpellEffect : Integer = ParserSelectByHandleByIndex(pSpellEffects, i);
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'AbilityID');
      [*] = ;      var effPower : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'Power');
      [*] = ;
      [*] = ;      if (effPower <> 0) and isHero then
      [*] = ;      begin
      [*] = ;         if effPower > 0 then
      [*] = ;         effPower := effPower + (_unit_CheckAbilityExt(myGOHandle, 905) * spPowerMod) div 100
      [*] = ;         else
      [*] = ;         effPower := effPower - (_unit_CheckAbilityExt(myGOHandle, 905) * spPowerMod) div 100
      [*] = ;      end;
      [*] = ;
      [*] = ;      var effDuration : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'Duration');
      [*] = ;      duration := effDuration;
      [*] = ;
      [*] = ;      if duration > 0 then
      [*] = ;      begin
      [*] = ;         if isHero then
      [*] = ;         duration := duration + (_unit_CheckAbilityExt(myGOHandle, 906) * spDurationMod) div 100;
      [*] = ;
      [*] = ;         if abilID = 1 then
      [*] = ;         abilID := -1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      case abilID of
      [*] = ;         1 :
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               if spNegative and (not bFriendlyFire) then
      [*] = ;               begin
      [*] = ;                  // damage
      [*] = ;                  var def : Integer = 0;
      [*] = ;                  if spResistPower > 0 then
      [*] = ;                  def := def + resist;
      [*] = ;                  if spDefencePower > 0 then
      [*] = ;                  def := def + tDefence;
      [*] = ;
      [*] = ;                  IntRegister0 := effPower;
      [*] = ;                  IntRegister1 := def;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  MapExecuteState('bat.GetHit');
      [*] = ;                  hit := IntRegister2;
      [*] = ;
      [*] = ;                  gainSpDamage := gainSpDamage - hit;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  // healing
      [*] = ;                  gainSpDamage := effPower;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         10 :
      [*] = ;         // increasing ammo
      [*] = ;         begin
      [*] = ;            if not spNegative then
      [*] = ;            begin
      [*] = ;               if effDuration = -1 then
      [*] = ;               begin
      [*] = ;                  if (GetTarAction(0) > 0) or (GetTarAction(1) > 0) then
      [*] = ;                  begin
      [*] = ;                     if tMaxAmmo - tCurAmmo > effPower then
      [*] = ;                     begin
      [*] = ;                        buff := buff + effPower * (tRangedAttack + _unit_CheckAbility(tGOHandle, 24));
      [*] = ;                        if tCurAmmo = 0 then
      [*] = ;                        gainSpDamage := gainSpDamage + tRangedAttack + _unit_CheckAbility(tGOHandle, 24);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        buff := buff + (tMaxAmmo - tCurAmmo) * (tRangedAttack + _unit_CheckAbility(tGOHandle, 24));
      [*] = ;                        if tCurAmmo = 0 then
      [*] = ;                        gainSpDamage := gainSpDamage + tRangedAttack + _unit_CheckAbility(tGOHandle, 24);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  // regular effect
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         11 :
      [*] = ;         // increasing stamina
      [*] = ;         begin
      [*] = ;            if (_unit_CheckAbility(tGOHandle, 18) = 0) and (not spNegative) then
      [*] = ;            begin
      [*] = ;               if effDuration = -1 then
      [*] = ;               begin
      [*] = ;                  if tMaxStamina - tCurStamina > effPower then
      [*] = ;                  hit := effPower
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if tCurStamina >= 5 then
      [*] = ;                     hit := 0
      [*] = ;                     else
      [*] = ;                     hit := tMaxStamina - tCurStamina;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if hit > 0 then
      [*] = ;                  begin
      [*] = ;                     buff := buff + hit;
      [*] = ;                     if tCurStamina = 0 then
      [*] = ;                     buff := buff + hit * tAttack
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if tCurStamina < 5 then
      [*] = ;                        begin
      [*] = ;                           buff := buff + (hit * tAttack) div 5;
      [*] = ;                           if myGOHandle = tGOHandle then
      [*] = ;                           gainSpDamage := gainSpDamage + tAttack;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  // regular effect
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         12 :
      [*] = ;         // increasing moral
      [*] = ;         begin
      [*] = ;            if (_unit_CheckAbility(tGOHandle, 19) = 0) and (not spNegative) then
      [*] = ;            begin
      [*] = ;               if effDuration = -1 then
      [*] = ;               begin
      [*] = ;                  if effPower > tMaxMoral - tCurMoral then
      [*] = ;                  effPower := tMaxMoral - tCurMoral;
      [*] = ;                  if effPower < 0 then
      [*] = ;                  effPower := 0;
      [*] = ;
      [*] = ;                  buff := buff + effPower;
      [*] = ;
      [*] = ;                  if tCurMoral = 0 then
      [*] = ;                  gainSpDamage := gainSpDamage + tAttack * effPower;
      [*] = ;
      [*] = ;                  if tCurMoral < 5 then
      [*] = ;                  buff := buff + effPower;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  // regular effect
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         31 :
      [*] = ;         // disable spells
      [*] = ;         begin
      [*] = ;            if isHero then
      [*] = ;            effPower := effPower + _unit_CheckAbility(myGOHandle, 908);
      [*] = ;
      [*] = ;            for j := ParserGetCountByHandle(pTGOEffects)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pTGOEffect : Integer =  ParserSelectByHandleByIndex(pTGOEffects, j);
      [*] = ;
      [*] = ;               var tEffDuration : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'Duration');
      [*] = ;               var tEffPower : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'Power');
      [*] = ;               var tEffSpellID : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'SpellID');
      [*] = ;
      [*] = ;               IntRegister0 := tEffSpellID;
      [*] = ;               StateMachineExecuteState(initMachine, 'GetSpellParserByID', 0);
      [*] = ;               var pEffSpell : Integer = IntRegister1;
      [*] = ;               var negative : Boolean = ParserGetBoolValueByKeyByHandle(pEffSpell, 'Negative');
      [*] = ;
      [*] = ;               if (tEffSpellID > 0) and negative then
      [*] = ;               begin
      [*] = ;                  if tEffDuration > effPower then
      [*] = ;                  buff := buff + effPower * tEffPower
      [*] = ;                  else
      [*] = ;                  buff := buff + tEffDuration * tEffPower;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         72 : bFriendlyFire := true;
      [*] = ;         75 :
      [*] = ;         // extra turn
      [*] = ;         begin
      [*] = ;            if (_unit_CheckAbility(tGOHandle, 36) = 0) and (tCurMoral > 0) and (not tCanAct) then
      [*] = ;            begin
      [*] = ;               if GetTarAction(0) = 2 then
      [*] = ;               gainSpDamage := gainSpDamage + _unit_CheckAbility(tGOHandle, 24);
      [*] = ;               if GetTarAction(1) = 2 then
      [*] = ;               gainSpDamage := gainSpDamage + tRangedAttack;
      [*] = ;               if GetTarAction(2) = 2 then
      [*] = ;               gainSpDamage := gainSpDamage + tAttack;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         89 :
      [*] = ;         // teleport
      [*] = ;         begin
      [*] = ;            if (tAttack > 5) and (tCurAmmo = 0) and (GetTarAction(2) < 2) and tCanAct then
      [*] = ;            begin
      [*] = ;               var maxHit : Integer = 0;
      [*] = ;
      [*] = ;               for j := 0 to gc_battle_GridSize-1 do
      [*] = ;               for k := 0 to gc_battle_GridSize-1 do
      [*] = ;               begin
      [*] = ;                  IntRegister0 := j;
      [*] = ;                  IntRegister1 := k;
      [*] = ;                  GameObjectExecuteStateByHandle(tGOHandle, 'GetTeleportTaste');
      [*] = ;                  var hit : Integer = IntRegister2;
      [*] = ;
      [*] = ;                  if hit > maxHit then
      [*] = ;                  maxHit := hit;
      [*] = ;               end;
      [*] = ;
      [*] = ;               gainSpDamage := maxHit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         91 :
      [*] = ;         // dark pact
      [*] = ;         begin
      [*] = ;            if (tCurLife <= tMaxLife div 4) and ((GetTarAction(5) > 0) or (GetTarAction(6) > 0)) then
      [*] = ;            begin
      [*] = ;               gainSpDamage := 5 + (tRank - 1) * 10;
      [*] = ;               buff := buff + tRank * 50;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if spResistDuration > 0 then
      [*] = ;            duration := duration - resist;
      [*] = ;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserBySpellID');
      [*] = ;            if IntRegister1 <> 0 then
      [*] = ;            duration := 0;
      [*] = ;
      [*] = ;            if duration > 1 then
      [*] = ;            begin
      [*] = ;               if abilID > 1000 then
      [*] = ;               begin
      [*] = ;                  if GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanAct) = false then
      [*] = ;                  duration := duration - 1;
      [*] = ;
      [*] = ;                  var spUnitID : Integer = abilID - 1000;
      [*] = ;                  var pSpUnit : Integer = _unit_GetUnitParserByID(spUnitID);
      [*] = ;                  var spUnitAttack : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Attack');
      [*] = ;
      [*] = ;                  gainSpDamage := spUnitAttack - tAttack;
      [*] = ;                  if tCurAmmo >= 2 then
      [*] = ;                  gainSpDamage := gainSpDamage - 2 * tRangedAttack;
      [*] = ;
      [*] = ;                  gainSpDamage := (gainSpDamage * tAttack) div (tAttack + 1) * duration;
      [*] = ;
      [*] = ;                  if tIsHero then
      [*] = ;                  gainSpDamage := (gainSpDamage * 2) div 3;
      [*] = ;               end;
      [*] = ;
      [*] = ;               case abilID of
      [*] = ;                  -1 :
      [*] = ;                  // regeneration
      [*] = ;                  begin
      [*] = ;                     if tCurLife < tMaxLife then
      [*] = ;                     begin
      [*] = ;                        buff := buff + (tRangedAttack * tCurAmmo) div 20;
      [*] = ;                        buff := buff + tAttack div 2;
      [*] = ;                        if (GetTarAction(3) > 0) or (GetTarAction(4) > 0) or (GetTarAction(5) > 0) or (GetTarAction(6) > 0) then
      [*] = ;                        buff := buff + duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  2 :
      [*] = ;                  // increasing attack
      [*] = ;                  begin
      [*] = ;                     if GetTarAction(2) = 2 then
      [*] = ;                     buff := buff + duration * effPower;
      [*] = ;                  end;
      [*] = ;                  3 :
      [*] = ;                  // increasing counter attack
      [*] = ;                  begin
      [*] = ;                     if (GetTarAction(5) > 0) or (GetTarAction(6) > 0) then
      [*] = ;                     buff := buff + duration * effPower;
      [*] = ;                  end;
      [*] = ;                  4 :
      [*] = ;                  // increasing defence
      [*] = ;                  begin
      [*] = ;                     if GetTarAction(6) > 0 then
      [*] = ;                     buff := buff + duration * effPower;
      [*] = ;                  end;
      [*] = ;                  5 :
      [*] = ;                  // increasing ranged defence
      [*] = ;                  begin
      [*] = ;                     if GetTarAction(4) > 0 then
      [*] = ;                     buff := buff + duration * effPower;
      [*] = ;                  end;
      [*] = ;                  6 :
      [*] = ;                  // increasing resistance
      [*] = ;                  begin
      [*] = ;                     if (GetTarAction(3) > 0) or (GetTarAction(5) > 0) then
      [*] = ;                     buff := buff + duration * effPower;
      [*] = ;                  end;
      [*] = ;                  7 :
      [*] = ;                  // increasing speed
      [*] = ;                  begin
      [*] = ;                     if (GetTarAction(0) = 0) or (GetTarAction(1) = 0) or (GetTarAction(2) = 0) then
      [*] = ;                     buff := buff + duration * (effPower + tAttack div 5);
      [*] = ;                  end;
      [*] = ;                  8 :
      [*] = ;                  // increasing ranged attack
      [*] = ;                  begin
      [*] = ;                     if (GetTarAction(0) = 0) or (GetTarAction(1) = 0) or (GetTarAction(2) = 0) then
      [*] = ;                     buff := buff + duration * effPower;
      [*] = ;                  end;
      [*] = ;                  68 :
      [*] = ;                  begin
      [*] = ;                     if (tCurLife < tMaxLife) and (GetTarAction(2) = 2) then
      [*] = ;                     begin
      [*] = ;                        buff := buff + (tAttack * effPower) div 100 * duration;
      [*] = ;                        gainSpDamage := gainSpDamage + (tAttack * effPower) div 100;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var myTaste : Integer = buff;
      [*] = ;   if gainSpDamage < 0 then
      [*] = ;   begin
      [*] = ;      if Abs(gainSpDamage) >= tCurLife then
      [*] = ;      begin
      [*] = ;         gainSpDamage := gainSpDamage - tCurLife;
      [*] = ;         myTaste := myTaste + gainSpDamage * 6;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := 70;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'IsAbilityInEffects');
      [*] = ;         if BoolRegister0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 70;
      [*] = ;            GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectDuration');
      [*] = ;            var tEffDur70 : Integer = IntRegister1;
      [*] = ;
      [*] = ;            gainSpDamage := gainSpDamage + (tEffDur70 - 1);
      [*] = ;            myTaste := myTaste + 3 * (tEffDur70 - 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         myTaste := myTaste + 3 * gainSpDamage;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var pSpellEffect0 : Integer = ParserSelectByHandleByIndex(pSpellEffects, 0);
      [*] = ;      var abilID0 : Integer =  ParserGetIntValueByKeyByHandle(pSpellEffect0, 'AbilityID');
      [*] = ;      if (abilID0 = 1) and (gainSpDamage > tMaxLife - tCurLife) then
      [*] = ;      gainSpDamage := tMaxLife - tCurLife;
      [*] = ;
      [*] = ;      myTaste := myTaste + gainSpDamage * 3;
      [*] = ;      myTaste := myTaste + gainSpDamage * tRank div 2;
      [*] = ;
      [*] = ;      if tIsHero then
      [*] = ;      myTaste := myTaste + gainSpDamage;
      [*] = ;   end;
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'GetMyTaste');
      [*] = ;   myTaste := myTaste + (myTaste * IntRegister0) div 50;
      [*] = ;   res := myTaste;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;IntRegister3 := gainSpDamage;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

