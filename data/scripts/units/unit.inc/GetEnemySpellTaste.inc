section.begin
   Name = GetEnemySpellTaste
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
      [*] = ;
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd( gc_stack_unit_bIsHero);
      [*] = ;var tIsHero : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;var gainSpDamage : Integer = 0;
      [*] = ;var bPossessed : Boolean = true;
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
      [*] = ;var i, j : Integer;
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
      [*] = ;
      [*] = ;IntRegister0 := 24;
      [*] = ;GameObjectExecuteStateByHandle(tGOHandle, 'CheckAbility');
      [*] = ;var tAbil24 : Integer = _unit_CheckAbility(tGOHandle, 24);
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
      [*] = ;for i := 0 to ParserGetCountByHandle(pSpUnitTypes)-1 do
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
      [*] = ;   var bLifeDrain : Boolean = false;
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
      [*] = ;         // damage
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               baseDamage := baseDamage + effPower;
      [*] = ;
      [*] = ;               var def : Integer = 0;
      [*] = ;               if spResistPower > 0 then
      [*] = ;               def := def + resist;
      [*] = ;               if spDefencePower > 0 then
      [*] = ;               def := def + tDefence;
      [*] = ;
      [*] = ;               IntRegister0 := effPower;
      [*] = ;               IntRegister1 := def;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               MapExecuteState('bat.GetHit');
      [*] = ;               hit := IntRegister2;
      [*] = ;
      [*] = ;               gainSpDamage := gainSpDamage + hit;
      [*] = ;
      [*] = ;               if ((GetTarAction(0) = 2) or (GetTarAction(1) = 2)) and (GetTarAction(3) = 0) and (GetTarAction(4) = 0) and (GetTarAction(5) = 0) and (GetTarAction(6) = 0) then
      [*] = ;               begin
      [*] = ;                  attBuff := attBuff + (tRangedAttack * tCurAmmo) div 4;
      [*] = ;                  attBuff := attBuff + (tAbil24 * tCurAmmo) div 4;
      [*] = ;               end;
      [*] = ;
      [*] = ;               attBuff := attBuff + (tRangedAttack * tCurAmmo) div 5 + (tAttack + tDefence + tRangedDefence) div 2;
      [*] = ;
      [*] = ;               if bLifeDrain then
      [*] = ;               begin
      [*] = ;                  selfHeal := selfHeal + hit;
      [*] = ;                  if selfHeal > maxLife - curLife then
      [*] = ;                  selfHeal := maxLife - curLife;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         10 :
      [*] = ;         // burning ammo
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               baseDamage := baseDamage + effPower;
      [*] = ;
      [*] = ;               var def : Integer = 0;
      [*] = ;               if spResistPower > 0 then
      [*] = ;               def := resist;
      [*] = ;
      [*] = ;               IntRegister0 := effPower;
      [*] = ;               IntRegister1 := def;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               MapExecuteState('bat.GetHit');
      [*] = ;               hit := IntRegister2;
      [*] = ;
      [*] = ;               if tCurAmmo < hit then
      [*] = ;                  hit := tCurAmmo;
      [*] = ;
      [*] = ;               if hit > 0 then
      [*] = ;               begin
      [*] = ;                  gainSpDamage := gainSpDamage + hit;
      [*] = ;                  buff := buff + (hit * (tRangedAttack + tAbil24)) div 2;
      [*] = ;
      [*] = ;                  if ((GetTarAction(0) = 2) or (GetTarAction(1) = 2)) and (GetTarAction(3) = 0) and (GetTarAction(4) = 0) and (GetTarAction(5) = 0) and (GetTarAction(6) = 0) then
      [*] = ;                  begin
      [*] = ;                     attBuff := attBuff + (tRangedAttack * tCurAmmo) div 4;
      [*] = ;                     attBuff := attBuff + (tAbil24 * tCurAmmo) div 4;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  attBuff := attBuff + (tRangedAttack * tCurAmmo) div 5 + (tAttack + tDefence + tRangedDefence) div 2;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               // regular effect
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         11 :
      [*] = ;         // lowering energy
      [*] = ;         begin
      [*] = ;            if _unit_CheckAbility(tGOHandle, 18) = 0 then
      [*] = ;            begin
      [*] = ;               if spNegative then
      [*] = ;               begin
      [*] = ;                  if effDuration = -1 then
      [*] = ;                  begin
      [*] = ;                     hit := hit + effPower;
      [*] = ;                     if spResistPower > 0 then
      [*] = ;                     hit := hit - resist;
      [*] = ;
      [*] = ;                     if hit > 0 then
      [*] = ;                     begin
      [*] = ;                        if tCurStamina < hit then
      [*] = ;                        hit := tCurStamina * 2;
      [*] = ;
      [*] = ;                        if GetTarAction(0) = 2 then
      [*] = ;                        hit := hit + hit * (_unit_CheckAbility(tGOHandle, 24) div 7);
      [*] = ;
      [*] = ;                        if GetTarAction(1) = 2 then
      [*] = ;                        hit := hit + hit * (tRangedAttack div 7);
      [*] = ;
      [*] = ;                        if GetTarAction(2) = 2 then
      [*] = ;                        hit := hit + hit * (tAttack div 7);
      [*] = ;
      [*] = ;                        buff := buff + hit;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     // regular effect
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         12 :
      [*] = ;         // fear
      [*] = ;         begin
      [*] = ;            if (_unit_CheckAbility(tGOHandle, 19) = 0) and spNegative then
      [*] = ;            begin
      [*] = ;               if effDuration = -1 then
      [*] = ;               begin
      [*] = ;                  hit := hit + effPower;
      [*] = ;                  if spResistPower > 0 then
      [*] = ;                  hit := hit - resist;
      [*] = ;
      [*] = ;                  if (hit > 0) and (tCurMoral > 0) then
      [*] = ;                  begin
      [*] = ;                     if tCurMoral < hit then
      [*] = ;                     hit := 20 + tCurMoral div 4
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if tCurMoral < hit + 5 then
      [*] = ;                        hit := (hit * 3) div 2;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if GetTarAction(0) = 2 then
      [*] = ;                     hit := hit + hit * (_unit_CheckAbility(tGOHandle, 24) div 7);
      [*] = ;
      [*] = ;                     if GetTarAction(1) = 2 then
      [*] = ;                     hit := hit + hit * (tRangedAttack div 7);
      [*] = ;
      [*] = ;                     if GetTarAction(2) = 2 then
      [*] = ;                     hit := hit + hit * (tAttack div 7);
      [*] = ;
      [*] = ;                     buff := buff + hit;
      [*] = ;                  end;
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
      [*] = ;            if tIsHero then
      [*] = ;            effPower := effPower + _unit_CheckAbility(tGOHandle, 908);
      [*] = ;
      [*] = ;            for j := ParserGetCountByHandle(pTGOEffects)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pTGOEffect : Integer =  ParserSelectByHandleByIndex(pTGOEffects, j);
      [*] = ;
      [*] = ;               var tEffDuration : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'Duration');
      [*] = ;               var tEffPower : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'Power');
      [*] = ;               var tEffSpellID : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'SpellID');
      [*] = ;               var tEffID : Integer = ParserGetIntValueByKeyByHandle(pTGOEffect, 'EffectID');
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
      [*] = ;                  buff := buff + tEffDuration * tEffPower
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (tEffID = 73) or (tEffID = 90) then
      [*] = ;               begin
      [*] = ;                  buff := buff + 50;
      [*] = ;                  gainSpDamage := gainSpDamage + tAttack * (tEffDuration - 1);
      [*] = ;
      [*] = ;                  if tEffID = 73 then
      [*] = ;                  bPossessed := false;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // damage from summoned unit
      [*] = ;            if GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bSummoned) and (effPower > resist) then
      [*] = ;            begin
      [*] = ;               baseDamage := baseDamage + effPower;
      [*] = ;
      [*] = ;               IntRegister0 := effPower + effPower * 2;
      [*] = ;               IntRegister1 := resist;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               MapExecuteState('bat.GetHit');
      [*] = ;               hit := IntRegister2;
      [*] = ;
      [*] = ;               gainSpDamage := gainSpDamage + hit;
      [*] = ;
      [*] = ;               if ((GetTarAction(0) = 2) or (GetTarAction(1) = 2)) and (GetTarAction(3) = 0) and (GetTarAction(4) = 0) and (GetTarAction(5) = 0) and (GetTarAction(6) = 0) then
      [*] = ;               begin
      [*] = ;                  attBuff := attBuff + (tRangedAttack * tCurAmmo) div 4;
      [*] = ;                  attBuff := attBuff + (tAbil24 * tCurAmmo) div 4;
      [*] = ;               end;
      [*] = ;
      [*] = ;               attBuff := attBuff + (tRangedAttack * tCurAmmo) div 5 + (tAttack + tDefence + tRangedDefence) div 2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         47 :
      [*] = ;         // web
      [*] = ;         begin
      [*] = ;            if (resist < 4) and (_unit_CheckAbility(tGOHandle, 36) = 0) then
      [*] = ;            begin
      [*] = ;               if duration > tAttack then
      [*] = ;               duration := 2
      [*] = ;               else
      [*] = ;               duration := 1;
      [*] = ;
      [*] = ;               if (GetTarAction(5) <> 0) and (GetTarAction(6) <> 0) then
      [*] = ;               begin
      [*] = ;                  buff := buff + tCounterAttack * duration;
      [*] = ;                  if tIsHero then
      [*] = ;                  buff := buff + 10;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         71 :
      [*] = ;         begin
      [*] = ;            bLifeDrain := true;
      [*] = ;         end;
      [*] = ;         73 :
      [*] = ;         // submission
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               if (effPower > resist) and (_unit_CheckAbility(tGOHandle, 36) = 0) and ((GetTarAction(0) = 2) or (GetTarAction(1) = 2) or (GetTarAction(2) = 2)) then
      [*] = ;               begin
      [*] = ;                  gainSpDamage := gainSpDamage + tAttack + tRangedAttack;
      [*] = ;                  buff := buff + tAttack + tRangedAttack;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if spResistDuration > 0 then
      [*] = ;               duration := duration - resist;
      [*] = ;
      [*] = ;               if (duration > 0) and (_unit_CheckAbility(tGOHandle, 36) = 0) and ((GetTarAction(0) = 2) or (GetTarAction(1) = 2) or (GetTarAction(2) = 2)) then
      [*] = ;               begin
      [*] = ;                  gainSpDamage := gainSpDamage + (tAttack + tRangedAttack) * duration;
      [*] = ;                  buff := buff + tAttack + tRangedAttack + tCurLife;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         92 :
      [*] = ;         // suicide
      [*] = ;         begin
      [*] = ;            if (spResistPower = 0) or (resist <= effPower) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := myGOHandle;
      [*] = ;               IntRegister1 := -1;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               BoolRegister1 := false;
      [*] = ;               BoolRegister2 := false;
      [*] = ;               BoolRegister3 := true;
      [*] = ;               ExecuteState('GetMeleeHit');
      [*] = ;               gainSpDamage := IntRegister2;
      [*] = ;
      [*] = ;               if ((GetTarAction(0) = 2) or (GetTarAction(1) = 2)) and (GetTarAction(3) = 0) and (GetTarAction(4) = 0) and (GetTarAction(5) = 0) and (GetTarAction(6) = 0) then
      [*] = ;               begin
      [*] = ;                  attBuff := attBuff + (tRangedAttack * tCurAmmo) div 4;
      [*] = ;                  attBuff := attBuff + (tAbil24 * tCurAmmo) div 4;
      [*] = ;               end;
      [*] = ;
      [*] = ;               attBuff := attBuff + (tRangedAttack * tCurAmmo) div 5 + (tAttack + tDefence + tRangedDefence) div 2;
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
      [*] = ;               var rank : Integer = ParserGetIntValueByKeyByHandle(pTarUnit, 'Rank');
      [*] = ;
      [*] = ;               if (abilID > 1000) and ((rank <> 2) or tIsHero) then
      [*] = ;               begin
      [*] = ;                  var spUnitID : Integer = abilID - 1000;
      [*] = ;                  var pSpUnit : Integer = _unit_GetUnitParserByID(spUnitID);
      [*] = ;                  var spUnitAttack : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Attack');
      [*] = ;                  var spUnitLife : Integer = ParserGetIntValueByKeyByHandle(pSpUnit, 'Life');
      [*] = ;
      [*] = ;                  // polymorph
      [*] = ;                  if GetTarAction(2) = 2 then
      [*] = ;                  buff := buff + (tAttack - spUnitAttack) * duration;
      [*] = ;
      [*] = ;                  buff := buff + tRangedAttack * tCurAmmo;
      [*] = ;                  if (GetTarAction(5) > 0) or (GetTarAction(6) > 0) then
      [*] = ;                  begin
      [*] = ;                     gainSpDamage := gainSpDamage + tCurLife;
      [*] = ;                     buff := buff + (tCurLife - spUnitLife) * duration;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               case abilID of
      [*] = ;                  -1 :
      [*] = ;                  begin
      [*] = ;                     // poisoning
      [*] = ;                     buff := buff - duration * effPower;
      [*] = ;                     gainSpDamage := gainSpDamage - duration * effPower;
      [*] = ;
      [*] = ;                     if ((GetTarAction(0) = 2) or (GetTarAction(1) = 2)) and (GetTarAction(3) = 0) and (GetTarAction(4) = 0) and (GetTarAction(5) = 0) and (GetTarAction(6) = 0) then
      [*] = ;                     begin
      [*] = ;                        buff := buff + (tRangedAttack * tCurAmmo) div 4;
      [*] = ;                        buff := buff + (tAbil24 * tCurAmmo) div 4;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  2 :
      [*] = ;                  begin
      [*] = ;                     // lowering attack
      [*] = ;                     if GetTarAction(2) = 2 then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tAttack) and (effPower < 0) then
      [*] = ;                        buff := buff + (tAttack - 1) * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  3 :
      [*] = ;                  begin
      [*] = ;                     // lowering counterattack
      [*] = ;                     if (GetTarAction(5) > 0) or (GetTarAction(6) > 0) then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tCounterAttack) and (effPower < 0) then
      [*] = ;                        buff := buff + (tCounterAttack - 1) * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  4 :
      [*] = ;                  begin
      [*] = ;                     // lowering defence
      [*] = ;                     if GetTarAction(6) > 0 then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tDefence) and (effPower < 0) then
      [*] = ;                        buff := buff + tDefence * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  5 :
      [*] = ;                  begin
      [*] = ;                     // lowering ranged defence
      [*] = ;                     if GetTarAction(4) > 0 then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tRangedDefence) and (effPower < 0) then
      [*] = ;                        buff := buff + tRangedDefence * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  6 :
      [*] = ;                  begin
      [*] = ;                     // lowering resistance
      [*] = ;                     if (GetTarAction(3) > 0) or (GetTarAction(5) > 0) then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tResist) and (effPower < 0) then
      [*] = ;                        buff := buff + tResist * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  7 :
      [*] = ;                  begin
      [*] = ;                     // slow
      [*] = ;                     if (tSpeed > 1) and (GetTarAction(0) = 0) and (GetTarAction(1) = 0) and (GetTarAction(2) = 0) then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tSpeed) and (effPower < 0) then
      [*] = ;                        buff := buff + (tResist + tAttack div 5) * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * (effPower - tAttack div 5);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  8 :
      [*] = ;                  begin
      [*] = ;                     // lowering ranged attack
      [*] = ;                     if GetTarAction(1) = 2 then
      [*] = ;                     begin
      [*] = ;                        if (Abs(effPower) > tRangedAttack) and (effPower < 0) then
      [*] = ;                        buff := buff + (tRangedAttack - 1) * duration
      [*] = ;                        else
      [*] = ;                        buff := buff - duration * effPower;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  36, 38 :
      [*] = ;                  begin
      [*] = ;                     if (GetTarAction(1) = 2) or (GetTarAction(2) = 2) then
      [*] = ;                     begin
      [*] = ;                        gainSpDamage := gainSpDamage + tAttack + tRangedAttack;
      [*] = ;                        buff := buff + tCurLife * duration;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     buff := buff + 2 * duration;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var myTaste : Integer = buff;
      [*] = ;
      [*] = ;   IntRegister0 := 73;
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectDuration');
      [*] = ;   var tEffDur73 : Integer = IntRegister1;
      [*] = ;
      [*] = ;   if (gainSpDamage > 0) and bPossessed and (tEffDur73 > 0) and (tEffDur73 < 3) then
      [*] = ;   gainSpDamage := -gainSpDamage;
      [*] = ;
      [*] = ;   if gainSpDamage >= tCurLife then
      [*] = ;   begin
      [*] = ;      gainSpDamage := tCurLife;
      [*] = ;
      [*] = ;      if selfHeal > tCurLife then
      [*] = ;      gainSpDamage := gainSpDamage * 2
      [*] = ;      else
      [*] = ;      gainSpDamage := gainSpDamage + selfHeal;
      [*] = ;
      [*] = ;      myTaste := myTaste + gainSpDamage * 6;
      [*] = ;      myTaste := myTaste + attBuff;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gainSpDamage := gainSpDamage + selfHeal;
      [*] = ;
      [*] = ;      // decreasing damage effect for sleeping target
      [*] = ;      IntRegister0 := 70;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectDuration');
      [*] = ;      var tEffDur70 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if tEffDur70 > 1 then
      [*] = ;      myTaste := myTaste + gainSpDamage div tEffDur70
      [*] = ;      else
      [*] = ;      myTaste := myTaste + gainSpDamage * 3;
      [*] = ;
      [*] = ;      if (gainSpDamage > 5) or (gainSpDamage >= baseDamage div 2) then
      [*] = ;      myTaste := myTaste + attBuff;
      [*] = ;   end;
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'GetMyTaste');
      [*] = ;   myTaste := myTaste + (myTaste * IntRegister0) div 50;
      [*] = ;
      [*] = ;   res := myTaste;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;IntRegister3 := gainSpDamage;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

