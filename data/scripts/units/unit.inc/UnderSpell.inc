section.begin
   Name = UnderSpell
   Description : struct.begin
      [*] = ;IntRegister0 - spell ID
      [*] = ;IntRegister1 - caster game object UID
      [*] = ;OUT : IntRegister2 - target UID
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;var spellID : Integer = IntRegister0;
      [*] = ;var castUID : Integer = IntRegister1;
      [*] = ;var castGOHandle : Integer = GetGameObjectHandleByUniqueId(castUID);
      [*] = ;var castPlHandle : Integer = GetGameObjectPlayerHandleByHandle(castGOHandle);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;var pMySpells : Integer = ParserSelectByHandleByKey(pMyParser, 'Spells');
      [*] = ;
      [*] = ;var hit,spellPower,duration : Integer;
      [*] = ;
      [*] = ;var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;var bSummoned : Boolean = GetBoolValueByIndex(gc_stack_unit_bSummoned);
      [*] = ;var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;var maxLife : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;var curAmmo : Integer = GetIntValueByIndex(gc_stack_unit_iCurAmmo);
      [*] = ;var maxAmmo : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxAmmo);
      [*] = ;var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;var maxStamina : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxStamina);
      [*] = ;var curMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;var maxMoral : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxMoral);
      [*] = ;var speed : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed);
      [*] = ;
      [*] = ;// Fly text data
      [*] = ;var oldLife : Integer = curLife;
      [*] = ;var oldStamina : Integer = curStamina;
      [*] = ;var oldMoral : Integer = curMoral;
      [*] = ;
      [*] = ;var castCurLife : Integer = GetGameObjectIntValueIndByHandle(castGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var castMaxLife : Integer = _unit_GetProperty(castGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;
      [*] = ;var bDestroyOnHit : Boolean = false;
      [*] = ;var bLifeDrain : Boolean = false;
      [*] = ;var bFriendlyFire : Boolean = false;
      [*] = ;
      [*] = ;var defence,attack,resist,power_mod,duration_mod : Integer;
      [*] = ;var i, j, k : Integer;
      [*] = ;var targetUID : Integer = myUID;
      [*] = ;var spellCasted : Boolean = true;
      [*] = ;
      [*] = ;IntRegister0 := spellID;
      [*] = ;MapExecuteState('GetSpellParserByID');
      [*] = ;var pSpell : Integer = IntRegister1;
      [*] = ;var spNegative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Negative');
      [*] = ;var spRestoreOnly : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'RestoreOnly');
      [*] = ;var spCumulative : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Cumulative');
      [*] = ;var spLifeCost : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'LifeCost');
      [*] = ;var spResistPower : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'ResistPower');
      [*] = ;var spDefencePower : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'DefencePower');
      [*] = ;var spResistDuration : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'ResistDuration');
      [*] = ;var spPowerMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'PowerMod');
      [*] = ;var spDurationMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'DurationMod');
      [*] = ;var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;
      [*] = ;IntRegister0 := myUID;
      [*] = ;IntRegister1 := spellID;
      [*] = ;GameObjectExecuteStateByHandle(castGOHandle, 'GetSpellRuntimeAttributes');
      [*] = ;resist := IntRegister0;
      [*] = ;attack := IntRegister1;
      [*] = ;defence := IntRegister2;
      [*] = ;power_mod := IntRegister3;
      [*] = ;duration_mod := IntRegister4;
      [*] = ;if _log then _Log_valuesM('ID|Resist|Attack|Defense|PowerMode|DurMod',spellID,resist,attack,defence,power_mod,duration_mod);
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pSpellEffects)-1 do
      [*] = ;begin
      [*] = ;   var pSpellEffect : Integer = ParserSelectByHandleByIndex(pSpellEffects, i);
      [*] = ;
      [*] = ;   var effAbilityID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'AbilityID');
      [*] = ;   var effDuration : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'Duration');
      [*] = ;   var effpower : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'Power');
      [*] = ;   var spellPower : Integer = effPower;
      [*] = ;
      [*] = ;   if _log then _Log_valuesM('Ability|Duration|Power|CurMorale|CurLife',effAbilityID,effDuration,effpower,curMoral,curLife,0);
      [*] = ;   if spellPower > 0 then
      [*] = ;      spellPower := spellPower + power_mod
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if spellPower < 0 then
      [*] = ;         spellPower := spellPower - power_mod;
      [*] = ;   end;
      [*] = ;
      [*] = ;   duration := effDuration;
      [*] = ;   if duration > 0 then
      [*] = ;   begin
      [*] = ;      duration := duration + duration_mod;
      [*] = ;
      [*] = ;      if effAbilityID = gc_ability_life then
      [*] = ;         effAbilityID := -1*gc_ability_life;
      [*] = ;      if effAbilityID = gc_ability_stamina then
      [*] = ;         effAbilityID := -1*gc_ability_stamina;
      [*] = ;   end;
      [*] = ;
      [*] = ;   case effAbilityID of
      [*] = ;      gc_ability_life : begin
      [*] = ;         if spNegative and ((myPlHandle <> castPlHandle) or (not bFriendlyFire)) then
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;               // damage
      [*] = ;               var def : Integer = 0;
      [*] = ;               if spResistPower > 0 then
      [*] = ;                  def := def + resist;
      [*] = ;               if spDefencePower > 0 then
      [*] = ;                  def := def + defence;
      [*] = ;
      [*] = ;               IntRegister0 := spellPower;
      [*] = ;               IntRegister1 := def;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               MapExecuteState('bat.GetHit');
      [*] = ;               var hit : Integer = IntRegister2;
      [*] = ;               if hit > curLife then
      [*] = ;                  hit := curLife;
      [*] = ;
      [*] = ;               if bLifeDrain then
      [*] = ;               begin
      [*] = ;                  var castCurLife : Integer = GetGameObjectIntValueIndByHandle(castGOHandle, gc_stack_unit_iCurLife);
      [*] = ;                  var hp_plus : Integer;
      [*] = ;
      [*] = ;                  hp_plus := min(floor(abs(castMaxLife-castCurLife)),hit);
      [*] = ;                  if hp_plus > 0 then
      [*] = ;                     SetGameObjectIntValueIndByHandle(castGOHandle, gc_stack_unit_iCurLife, castCurLife + hp_plus);
      [*] = ;               end;
      [*] = ;
      [*] = ;               IntRegister0 := hit;
      [*] = ;               IntRegister1 := 2;
      [*] = ;               IntRegister2 := castUID;
      [*] = ;               ExecuteState('TakeDamage');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iKillerUID, castUID);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (effDuration = -1) and ((unitType = 1) or (((unitType = 3) or (unitType = 5)) and (spLifeCost = 0))) and (_unit_CheckAbility(myGOHandle, gc_ability_zombie) = 0) then
      [*] = ;            begin
      [*] = ;               // heal
      [*] = ;               if curLife < maxLife then
      [*] = ;               begin
      [*] = ;                  hit := spellPower;
      [*] = ;                  if hit > maxLife - curLife then
      [*] = ;                     hit := maxLife - curLife;
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iCurLife, curLife + hit);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_ability_ammo : begin
      [*] = ;         if spNegative then
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               // decreasing ammo
      [*] = ;               var def : Integer = 0;
      [*] = ;               if spResistPower > 0 then
      [*] = ;                  def := resist;
      [*] = ;
      [*] = ;               IntRegister0 := spellPower;
      [*] = ;               IntRegister1 := def;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               MapExecuteState('bat.GetHit');
      [*] = ;               var hit : Integer = IntRegister2;
      [*] = ;
      [*] = ;               if curAmmo < hit then
      [*] = ;                  hit := curAmmo;
      [*] = ;
      [*] = ;               if hit > 0 then
      [*] = ;               begin
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iCurAmmo, curAmmo - hit);
      [*] = ;                  var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;                  if hit > curLife then
      [*] = ;                     hit := curLife;
      [*] = ;
      [*] = ;                  IntRegister0 := hit;
      [*] = ;                  IntRegister1 := 2;
      [*] = ;                  IntRegister2 := castUID;
      [*] = ;                  ExecuteState('TakeDamage');
      [*] = ;                  if BoolRegister0 then
      [*] = ;                  begin
      [*] = ;                     SetIntValueByIndex(gc_stack_unit_iKillerUID, castUID);
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (effDuration = -1) and (curAmmo < maxAmmo) then
      [*] = ;            begin
      [*] = ;               // adding ammo
      [*] = ;               if spRestoreOnly then
      [*] = ;                  spellPower := max(maxAmmo - curAmmo,0);
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iCurAmmo, min(curAmmo + spellPower,maxAmmo));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_ability_stamina : begin
      [*] = ;         if spNegative then
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               // reducing stamina
      [*] = ;               var hit : Integer = spellPower;
      [*] = ;               if spResistPower > 0 then
      [*] = ;                  hit := hit - resist;
      [*] = ;
      [*] = ;               if hit > 0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := -hit;
      [*] = ;                  ExecuteState('ChangeStamina');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (effDuration = -1) and ((curStamina < maxStamina) or (spellPower < 0)) then
      [*] = ;            begin
      [*] = ;               if spRestoreOnly and (spellPower > 0) then
      [*] = ;                  spellPower := min(spellPower,maxStamina - curStamina);
      [*] = ;
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iCurStamina, curStamina + spellPower);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_ability_morale : begin
      [*] = ;         if spNegative then
      [*] = ;         begin
      [*] = ;            if effDuration = -1 then
      [*] = ;            begin
      [*] = ;               // fear
      [*] = ;               var hit : Integer = spellPower;
      [*] = ;               if spResistPower > 0 then
      [*] = ;                  hit := hit - resist;
      [*] = ;
      [*] = ;               if hit > 0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := -hit;
      [*] = ;                  ExecuteState('ChangeMoral');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (effDuration = -1) and ((curMoral < maxMoral) or (spellPower < 0)) then
      [*] = ;            begin
      [*] = ;               // increasing moral
      [*] = ;               if spRestoreOnly and (spellPower > 0) then
      [*] = ;                  spellPower := min(maxMoral - curMoral,spellPower);
      [*] = ;
      [*] = ;               if _log then _Log_valuesM('_MoraleDelta|CurMorale|MaxMorale',spellPower,curMoral,maxMoral,0,0,0);
      [*] = ;               IntRegister0 := spellPower;
      [*] = ;               ExecuteState('ChangeMoral');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_ability_dispel : begin
      [*] = ;         // taking off effects
      [*] = ;         spellPower := spellPower + _unit_CheckAbility(castGOHandle, 908);
      [*] = ;
      [*] = ;         if castPlHandle = myPlHandle then
      [*] = ;         begin
      [*] = ;            // friendly unit
      [*] = ;            for j := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var bDestroy : Boolean = false;
      [*] = ;
      [*] = ;               var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, j);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'AbilityID');
      [*] = ;               var parSpellID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID');
      [*] = ;               var parUpgradeID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentUpgradeID');
      [*] = ;
      [*] = ;               var pParSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, parSpellID);
      [*] = ;               var parSpNegative : Boolean = ParserGetBoolValueByKeyByHandle(pParSpell, 'Negative');
      [*] = ;               var pSpEffects : Integer = ParserSelectByHandleByKey(pParSpell, 'Effects');
      [*] = ;               var pSpEffect0 : Integer = ParserSelectByHandleByIndex(pSpEffects, 0);
      [*] = ;               var effID : Integer = ParserGetIntValueByKeyByHandle(pSpEffect0, 'AbilityID');
      [*] = ;
      [*] = ;               if (parSpellID > 0) and parSpNegative and (abilID <> gc_ability_change_side) and (effID <> 30) then
      [*] = ;               begin
      [*] = ;                  var duration : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'Duration');
      [*] = ;                  if duration > 0 then
      [*] = ;                  begin
      [*] = ;                     duration := duration - spellPower;
      [*] = ;                     if duration <= 0 then
      [*] = ;                        bDestroy := true
      [*] = ;                     else
      [*] = ;                        ParserSetIntValueByKeyByHandle(pMyEffect, 'Duration', duration);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if bDestroy then
      [*] = ;               begin
      [*] = ;                  ParserFreeByHandle(pMyEffect);
      [*] = ;                  
      [*] = ;                  if abilID = gc_ability_phantom_form then
      [*] = ;                  begin
      [*] = ;                     ExecuteState('ShowTrueForm');
      [*] = ;                     if BoolRegister0 then
      [*] = ;                        targetUID := IntRegister1;
      [*] = ;                     oldLife := GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;                  end;
      [*] = ;               
      [*] = ;                  if ParserGetBoolValueByKeyByHandle(pMyEffect, 'Visible') and _misc_IsVisibleBattle then
      [*] = ;                  case parSpellID of
      [*] = ;                     gc_spell_stone_skin : begin
      [*] = ;                        _fx_GetOrCreateFXByID(myGOHandle, 'fx_stoneskin_destroy', 0, 0, 0, 0, 0, _fx_GetIDByNodeName('fx_stoneskin'));
      [*] = ;                        _unit_CheckMaterial(myGOHandle, 'fx_stoneskin');
      [*] = ;                     end;
      [*] = ;                     gc_spell_word_of_ice : begin
      [*] = ;                        _fx_GetOrCreateFXByID(myGOHandle, 'fx_unfreeze', 0, 0, 0, 0, 0, _fx_GetIDByNodeName('fx_freeze'));
      [*] = ;                        _unit_CheckMaterial(myGOHandle, 'fx_freeze');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            // enemy unit
      [*] = ;            var chSide : Integer = -1;
      [*] = ;            var pDstEffects : Integer = pMyEffects;
      [*] = ;
      [*] = ;            for j := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var bDestroy : Boolean = false;
      [*] = ;
      [*] = ;               var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, j);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'AbilityID');
      [*] = ;               var parSpellID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID');
      [*] = ;               var parUpgradeID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentUpgradeID');
      [*] = ;               var visible : Boolean = ParserGetBoolValueByKeyByHandle(pMyEffect, 'Boolean');
      [*] = ;
      [*] = ;               var pParSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, parSpellID);
      [*] = ;               var parSpNegative : Boolean = ParserGetBoolValueByKeyByHandle(pParSpell, 'Negative');
      [*] = ;               var pSpEffects : Integer = ParserSelectByHandleByKey(pParSpell, 'Effects');
      [*] = ;               var pSpEffect0 : Integer = ParserSelectByHandleByIndex(pSpEffects, 0);
      [*] = ;               var effID : Integer = ParserGetIntValueByKeyByHandle(pSpEffect0, 'AbilityID');
      [*] = ;
      [*] = ;               if (parSpellID > 0) and ((not parSpNegative) or (abilID = gc_ability_change_side)) and (effID <> gc_ability_spell_immunity) then
      [*] = ;               begin
      [*] = ;                  var duration : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'Duration');
      [*] = ;                  if duration > 0 then
      [*] = ;                  begin
      [*] = ;                     duration := duration - spellPower;
      [*] = ;                     if duration <= 0 then
      [*] = ;                     begin
      [*] = ;                        bDestroy := true;
      [*] = ;                        if abilID = gc_ability_change_side then
      [*] = ;                           chSide := ParserGetIntValueByKeyByHandle(pMyEffect, 'Power');
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     ParserSetIntValueByKeyByHandle(pMyEffect, 'Duration', duration);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if bDestroy then
      [*] = ;               begin
      [*] = ;                  if abilID = gc_ability_phantom_form then
      [*] = ;                  begin
      [*] = ;                     ParserFreeByHandle(pMyEffect);
      [*] = ;                     ExecuteState('ShowTrueForm');
      [*] = ;                     if BoolRegister0 then
      [*] = ;                        targetUID := IntRegister1;
      [*] = ;                     oldLife := GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     ParserFreeByHandle(pMyEffect);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // damage summoned units
      [*] = ;            if bSummoned and (spellPower + effPower * 2 > resist) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := spellPower + effPower * 2;
      [*] = ;               IntRegister1 := resist;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               MapExecuteState('bat.GetHit');
      [*] = ;               var hit : Integer = IntRegister2;
      [*] = ;
      [*] = ;               var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;               if hit > curLife then
      [*] = ;                  hit := curLife;
      [*] = ;
      [*] = ;               IntRegister0 := hit;
      [*] = ;               IntRegister1 := 2;
      [*] = ;               IntRegister2 := castUID;
      [*] = ;               ExecuteState('TakeDamage');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iKillerUID, castUID);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // changing side
      [*] = ;            if chSide >= 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := chSide;
      [*] = ;               ExecuteState('ChangeSide');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_ability_web : begin
      [*] = ;         if resist <= 3 then
      [*] = ;         begin
      [*] = ;            if duration > attack then
      [*] = ;               duration := 3
      [*] = ;            else
      [*] = ;               duration := 2;
      [*] = ;
      [*] = ;            IntRegister0 := gc_upgrade_web;
      [*] = ;            ExecuteState('GetEffectParserByUpgradeID');
      [*] = ;            var pGOEffect : Integer = IntRegister1;
      [*] = ;
      [*] = ;            if pGOEffect = 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := spellID;
      [*] = ;               ExecuteState('GetEffectParserBySpellID');
      [*] = ;               pGOEffect := IntRegister1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if pGOEffect <> 0 then
      [*] = ;            begin
      [*] = ;               var duration : Integer = ParserGetIntValueByKeyByHandle(pGOEffect, 'Duration');
      [*] = ;
      [*] = ;               IntRegister0 := gc_upgrade_web;
      [*] = ;               IntRegister1 := gc_spell_web;
      [*] = ;               IntRegister2 := duration + 1;
      [*] = ;               ExecuteState('SetEffectsDuration');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var pGOEffect : Integer = _unit_AddEffect(myGOHandle, gc_ability_immobilized, 1, duration);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID', spellID);
      [*] = ;
      [*] = ;               pGOEffect := _unit_AddEffect(myGOHandle, gc_ability_defense, 1, duration);
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID', spellID);
      [*] = ;
      [*] = ;               pGOEffect := _unit_AddEffect(myGOHandle, gc_ability_ranged_defense, 1, duration);
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID', spellID);
      [*] = ;
      [*] = ;               pGOEffect := _unit_AddEffect(myGOHandle, gc_ability_does_not_fight, 1, duration);
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID', spellID);
      [*] = ;
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;               SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            spellCasted := false;
      [*] = ;      end;
      [*] = ;      gc_ability_destroy_on_hit : bDestroyOnHit := true;
      [*] = ;      gc_ability_life_drain : bLifeDrain := true;
      [*] = ;      gc_ability_friendly_fire : bFriendlyFire := true;
      [*] = ;      gc_ability_change_side : begin
      [*] = ;         var dur : Integer = 0;
      [*] = ;         if effDuration = -1 then
      [*] = ;         begin
      [*] = ;            if spellPower >= resist then
      [*] = ;               dur := 1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            dur := duration;
      [*] = ;            if spResistDuration > 0 then
      [*] = ;               dur := dur - resist;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if dur > 0 then
      [*] = ;         begin
      [*] = ;            for j := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, j);
      [*] = ;               if ParserGetIntValueByKeyByHandle(pMyEffect, 'AbilityID') = gc_ability_change_side then
      [*] = ;                  ParserFreeByHandle(pMyEffect);
      [*] = ;            end;
      [*] = ;
      [*] = ;            var myIndex : Integer = GetGameObjectIndexByHandle(myGOHandle);
      [*] = ;            var newIndex : Integer = GetPlayerGameObjectsCountByHandle(castPlHandle);
      [*] = ;
      [*] = ;            if _unit_CheckAbility(myGOHandle, gc_ability_immobilized) = 0 then
      [*] = ;            begin
      [*] = ;               var speed : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed);
      [*] = ;               SetBoolValueByIndex(gc_stack_unit_bCanAct, true);
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iMovePoints, speed);
      [*] = ;
      [*] = ;               var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;               if curStamina <= 0 then
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iCurStamina, 1);
      [*] = ;
      [*] = ;               IntRegister0 := gc_ability_march;
      [*] = ;               ExecuteState('CheckAbility');
      [*] = ;               SetBoolValueByIndex(gc_stack_unit_bCanMarch, ( IntRegister1 > 0));
      [*] = ;
      [*] = ;               if GetIntValueByIndex(gc_stack_unit_iCurMoral) <= 0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := 1;
      [*] = ;                  ExecuteState('ChangeMoral');
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iFear, 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            IntRegister0 := newIndex;
      [*] = ;            ExecuteState('ChangeSide');
      [*] = ;
      [*] = ;            var pMyEffect : Integer = _unit_AddEffect(myGOHandle, gc_ability_change_side, newIndex, dur);
      [*] = ;            ParserSetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID', spellID);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pMyEffect, 'Visible', true);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            spellCasted := false;
      [*] = ;      end;
      [*] = ;      gc_ability_extra_turn : begin
      [*] = ;         // additional turn
      [*] = ;         if ((not GetBoolValueByIndex(gc_stack_unit_bIsHero)) or (not _map_CheckGenesisMode(gc_GM_AstralEnergySpell))) and (_unit_CheckAbility(myGOHandle, gc_ability_immobilized) = 0) then
      [*] = ;         begin
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanAct, true);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanCast, true);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanMelee, true);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bCanShoot, true);
      [*] = ;            SetBoolValueByIndex(gc_stack_unit_bActionTaken, false);
      [*] = ;
      [*] = ;            if _unit_CheckAbility(myGOHandle, gc_ability_cantmove) = 0 then
      [*] = ;            begin
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iMovePoints, _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed));
      [*] = ;
      [*] = ;               IntRegister0 := gc_ability_march;
      [*] = ;               ExecuteState('CheckAbility');
      [*] = ;               SetBoolValueByIndex(gc_stack_unit_bCanMarch, ( IntRegister1 > 0));
      [*] = ;            end;
      [*] = ;
      [*] = ;            //if _log then _misc_PostConsoleCommand('dumpobjects',true);
      [*] = ;            var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;            if curStamina <= 0 then
      [*] = ;            begin
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iCurStamina, 1);
      [*] = ;               SetBoolValueByIndex(gc_stack_unit_bResting, false);
      [*] = ;            end;
      [*] = ;
      [*] = ;            var curMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;            if curMoral <= 0 then
      [*] = ;            begin
      [*] = ;               var fear : Integer = GetIntValueByIndex(gc_stack_unit_iFear);
      [*] = ;               if fear < 60 then
      [*] = ;               begin
      [*] = ;                  var bPanic : Boolean = false;
      [*] = ;
      [*] = ;                  if gBoolRegister_BattleSimulate then
      [*] = ;                  begin
      [*] = ;                     if fear >= 30 then
      [*] = ;                        bPanic := true;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if randomExt * 100 > fear then
      [*] = ;                        bPanic := false
      [*] = ;                     else
      [*] = ;                        bPanic := true;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if bPanic then
      [*] = ;                  begin
      [*] = ;                     ExecuteState('Panic');
      [*] = ;                     SetIntValueByIndex(gc_stack_unit_iFear, fear - 10);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := 1;
      [*] = ;                     ExecuteState('ChangeMoral');
      [*] = ;                     SetIntValueByIndex(gc_stack_unit_iFear, 0);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  ExecuteState('Panic');
      [*] = ;                  SetIntValueByIndex(gc_stack_unit_iFear, fear - 10);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_ability_suicide : begin
      [*] = ;         // suicide
      [*] = ;         var res : Integer = 0;
      [*] = ;         if (spResistPower > 0) then
      [*] = ;            res := resist;
      [*] = ;
      [*] = ;         if (res <= spellPower) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := myGOHandle;
      [*] = ;            IntRegister1 := -1;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            BoolRegister1 := false;
      [*] = ;            BoolRegister2 := false;
      [*] = ;            BoolRegister3 := true;
      [*] = ;            ExecuteState('GetMeleeHit');
      [*] = ;            var hit : Integer = 2 * IntRegister2;
      [*] = ;
      [*] = ;            var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;            if hit > curLife then
      [*] = ;               hit := curLife;
      [*] = ;
      [*] = ;            IntRegister0 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;            IntRegister1 := hit;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            BoolRegister1 := false;
      [*] = ;            BoolRegister2 := true;
      [*] = ;            ExecuteState('HitEffect');
      [*] = ;            //var vampire : Integer = 0;
      [*] = ;
      [*] = ;            IntRegister0 := -1;
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;
      [*] = ;            IntRegister0 := hit;
      [*] = ;            IntRegister1 := 2;
      [*] = ;            IntRegister2 := castUID;
      [*] = ;            ExecuteState('TakeDamage');
      [*] = ;            if BoolRegister0 then
      [*] = ;            begin
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iKillerUID, castUID);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            spellCasted := false;
      [*] = ;      end;
      [*] = ;      gc_ability_cure_poison : begin
      [*] = ;         // cure poison
      [*] = ;         for j := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, j);
      [*] = ;            var upgradeID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentUpgradeID');
      [*] = ;            var pUpgrade : Integer = ParserSelectByHandleByIndex(gPrototypeData.unitupgrades.handle, upgradeID);
      [*] = ;            var pUpgAbilities : Integer = ParserSelectByHandleByKey(pUpgrade, 'Upgrades');
      [*] = ;
      [*] = ;            var destroy : Boolean = false;
      [*] = ;            for k := ParserGetCountByHandle(pUpgAbilities)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pUpgAbility : Integer = ParserSelectByHandleByIndex(pUpgAbilities, k);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pUpgAbility, 'AbilityID');
      [*] = ;
      [*] = ;               if (abilID = gc_ability_poison_attack) or (abilID = gc_ability_poison_shot) then
      [*] = ;               begin
      [*] = ;                  destroy := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if destroy then
      [*] = ;               ParserFreeByHandle(pMyEffect);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if effAbilityID < 0 then
      [*] = ;            effAbilityID := -effAbilityID;
      [*] = ;
      [*] = ;         if spNegative and (myPlHandle <> castPlHandle) then
      [*] = ;         begin
      [*] = ;            if spResistDuration > 0 then
      [*] = ;               duration := duration - resist;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (duration > 0) and (spellPower <> 0) then
      [*] = ;         begin
      [*] = ;            if not spCumulative then
      [*] = ;            begin
      [*] = ;               var bFound : Boolean = false;
      [*] = ;
      [*] = ;               for j := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, j);
      [*] = ;                  var parSpellID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID');
      [*] = ;                  var abilID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'AbilityID');
      [*] = ;                  var myEffDuration : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'Duration');
      [*] = ;                  var myEffPower : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'Power');
      [*] = ;
      [*] = ;                  if (parSpellID = spellID) and (abilID = effAbilityID) then
      [*] = ;                  begin
      [*] = ;                     bFound := true;
      [*] = ;                     if (duration > myEffDuration) or (Abs(spellPower) > Abs(myEffPower)) then
      [*] = ;                     begin
      [*] = ;                        ParserSetIntValueByKeyByHandle(pMyEffect, 'Duration', duration);
      [*] = ;                        ParserSetIntValueByKeyByHandle(pMyEffect, 'Power', spellPower);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (effAbilityID > 1000) and (abilID = gc_ability_phantom_form) then
      [*] = ;                  begin
      [*] = ;                     bFound := true;
      [*] = ;                     if (duration > myEffDuration) or (Abs(spellPower) > Abs(myEffPower)) then
      [*] = ;                     begin
      [*] = ;                        ParserSetIntValueByKeyByHandle(pMyEffect, 'Duration', duration);
      [*] = ;                        IntRegister0 := effAbilityID - 1000;
      [*] = ;                        IntRegister1 := $ffff;
      [*] = ;                        ExecuteState('ShowPhantomForm');
      [*] = ;                        targetUID := IntRegister1;
      [*] = ;                        oldLife := GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if not bFound then
      [*] = ;               begin
      [*] = ;                  var pNewEffects : Integer = 0;
      [*] = ;                  var pMyEffect : Integer = _unit_AddEffect(myGOHandle, effAbilityID, spellPower, duration);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID', spellID);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pMyEffect, 'DestroyOnHit', bDestroyOnHit);
      [*] = ;
      [*] = ;                  case effAbilityID of
      [*] = ;                     gc_ability_speed : begin
      [*] = ;                        var bCanAct : Boolean = GetBoolValueByIndex(gc_stack_unit_bCanAct);
      [*] = ;                        var movePoints : Integer = GetIntValueByIndex(gc_stack_unit_iMovePoints);
      [*] = ;                        var speed : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed);
      [*] = ;
      [*] = ;                        if (spellPower > 0) and bCanAct and (_unit_CheckAbility(myGOHandle, gc_ability_cantmove) = 0) and (_unit_CheckAbility(myGOHandle, gc_ability_immobilized) = 0) then
      [*] = ;                        begin
      [*] = ;                           movePoints := movePoints + spellPower;
      [*] = ;                           if movePoints > speed then
      [*] = ;                              movePoints := speed;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        if (spellPower < 0) and (movePoints > 0) then
      [*] = ;                        begin
      [*] = ;                           movePoints := movePoints + spellPower;
      [*] = ;                           if movePoints < 1 then
      [*] = ;                              movePoints := 1;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        SetIntValueByIndex(gc_stack_unit_iMovePoints, movePoints);
      [*] = ;                     end;
      [*] = ;                     gc_ability_immobilized : SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;                     gc_ability_does_not_fight : SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if effAbilityID > 1000 then
      [*] = ;                        begin
      [*] = ;                           ParserSetIntValueByKeyByHandle(pMyEffect, 'AbilityID', gc_ability_phantom_form);
      [*] = ;                           IntRegister0 := effAbilityID - 1000;
      [*] = ;                           IntRegister1 := 7;
      [*] = ;                           ExecuteState('ShowPhantomForm');
      [*] = ;                           pNewEffects := ParserSelectByHandleByKey(ParserSelectGameObject(IntRegister0),'Effects');
      [*] = ;                           oldLife := GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var visible : Boolean;
      [*] = ;                  if (i = 0) or (bDestroyOnHit and (i = 1)) then
      [*] = ;                     visible := true
      [*] = ;                  else
      [*] = ;                     visible := false;
      [*] = ;
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pMyEffect, 'Visible', visible);
      [*] = ;
      [*] = ;                  if pNewEffects <> 0 then
      [*] = ;                  begin
      [*] = ;                     ParserSelectByHandle(pNewEffects);
      [*] = ;                     ParserCopyFromByHandle(pMyEffects);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               case effAbilityID of
      [*] = ;                  gc_ability_speed : begin
      [*] = ;                     var bCanAct : Boolean = GetBoolValueByIndex(gc_stack_unit_bCanAct);
      [*] = ;                     var movePoints : Integer = GetIntValueByIndex(gc_stack_unit_iMovePoints);
      [*] = ;
      [*] = ;                     if spellPower > 0 then
      [*] = ;                     movePoints := movePoints + spellPower
      [*] = ;                     else
      [*] = ;                     if movePoints > 0 then
      [*] = ;                     begin
      [*] = ;                        movePoints := movePoints + spellPower;
      [*] = ;                        if movePoints < 1 then
      [*] = ;                           movePoints := 1;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     SetIntValueByIndex(gc_stack_unit_iMovePoints, movePoints);
      [*] = ;                  end;
      [*] = ;                  gc_ability_immobilized : SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;                  gc_ability_does_not_fight : SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;               end;
      [*] = ;
      [*] = ;               var pMyEffect : Integer = _unit_AddEffect(myGOHandle, effAbilityID, spellPower, duration);
      [*] = ;               ParserSetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID', spellID);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pMyEffect, 'DestroyOnHit', bDestroyOnHit);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pMyEffect, 'Visible', (i = 0));
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            spellCasted := false;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var abil129 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_absorb_magic);
      [*] = ;curLife := GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;if (curLife > 0) and (abil129 > 0) then
      [*] = ;begin
      [*] = ;   curLife := curLife + abil129;
      [*] = ;   if curLife > maxLife then
      [*] = ;      curLife := maxLife;
      [*] = ;
      [*] = ;   curStamina := curStamina + abil129;
      [*] = ;   if curStamina > maxStamina then
      [*] = ;      curStamina := maxStamina;
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurLife, curLife);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurStamina, curStamina);
      [*] = ;   _unit_SetupFlyText(myGOHandle, castUID, gc_flytext_CategoryAbility, gc_ability_absorb_magic, abil129);
      [*] = ;end;
      [*] = ;
      [*] = ;if not spellCasted then
      [*] = ;   _unit_SetupFlyText(GetGameObjectHandleByUniqueId(targetUID), castUID, gc_flytext_CategoryParam, gc_battle_unit_iResist, 0);
      [*] = ;
      [*] = ;if (castGOHandle <> myGOHandle) and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   _unit_SetupStatsTextData(myGOHandle, castUID, oldLife, oldStamina, oldMoral);
      [*] = ;end;
      [*] = ;
      [*] = ;var deathAnimReady : Integer = GetIntValueByIndex(gc_stack_unit_iDeathAnimReady) + 1;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;
      [*] = ;IntRegister2 := targetUID;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

