section.begin
   Name = ActivateAbility
   Description : struct.begin
      [*] = ;IntRegister0 - ability ID
   struct.end
   Code : struct.begin
      [*] = ;var abilityID : Integer = IntRegister0;
      [*] = ;
      [*] = ;case abilityID of
      [*] = ;   gc_ability_ammo_gather : ExecuteState('GatherAmmo');
      [*] = ;   gc_ability_march : ExecuteState('GoMarch');
      [*] = ;   gc_ability_flesh_eater : ExecuteState('EatCorpse');
      [*] = ;   gc_ability_battle_cry : ExecuteState('BattleShout');
      [*] = ;   gc_ability_crushing_blow : ExecuteState('SwitchCrushFlag');
      [*] = ;   gc_ability_round_attack : ExecuteState('SwitchRoundAttackFlag');
      [*] = ;   gc_ability_stealth : ExecuteState('SwitchStealthModeFlag');
      [*] = ;   gc_ability_fire_breath : ExecuteState('SwitchFireBreathFlag');
      [*] = ;   gc_ability_poison_bite : ExecuteState('SwitchPoisonBiteFlag');
      [*] = ;   gc_ability_astral_strike : ExecuteState('SwitchAstralStrikeFlag');
      [*] = ;   gc_ability_lunge : ExecuteState('SwitchLungeFlag');
      [*] = ;   else begin
      [*] = ;      var curAbilID : Integer = GetIntValueByIndex(gc_stack_unit_iActiveAbility);
      [*] = ;      var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;      GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;      if abilityID = curAbilID then
      [*] = ;         SetIntValueByIndex(gc_stack_unit_iActiveAbility, 0)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if curAbilID = 0 then
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iActiveAbility, abilityID);
      [*] = ;      end;
      [*] = ;      _inet_CreateOrderParser(GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle()), -1, -1, gc_inet_actiontype_activateability, 0, abilityID, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'ActivateAbility');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

