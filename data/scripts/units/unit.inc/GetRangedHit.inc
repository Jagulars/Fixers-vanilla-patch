section.begin
   Name = GetRangedHit
   Description : struct.begin
      [*] = ;IntRegister0 - enemy game object handle
      [*] = ;BoolRegister0 - true if simulation in progress
      [*] = ;OUT: IntRegister1 - ranged hit value
      [*] = ;     IntRegister2 - min hit value
      [*] = ;     IntRegister3 - max hit value
   struct.end
   Code : struct.begin
      [*] = ;var enGOHandle : Integer = IntRegister0;
      [*] = ;var simulate : Boolean = BoolRegister0;
      [*] = ;var rangedAttack,att,def,enResist : Integer;
      [*] = ;var damage, damage_low, damage_high : Integer = 0;
      [*] = ;
      [*] = ;enResist := -1;
      [*] = ;IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;rangedAttack := IntRegister1;
      [*] = ;att := rangedAttack;
      [*] = ;
      [*] = ;if (att > 0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_ability_magic_shot;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   if IntRegister1 > 0 then
      [*] = ;   begin
      [*] = ;      // magic shot
      [*] = ;      IntRegister0 := gc_ability_energy_control;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      def := IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iResist;
      [*] = ;      GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;      enResist := IntRegister1;
      [*] = ;      def := enResist - def;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_battle_unit_iRangedDefence;
      [*] = ;      GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;      var enRangedDefence : Integer = IntRegister1;
      [*] = ;   
      [*] = ;      IntRegister0 := gc_ability_precise_shot;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      var abil77 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_armor_piercing_shot;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if IntRegister1 > 0 then // armor-piercing shot
      [*] = ;         def := enRangedDefence div 2 - abil77
      [*] = ;      else // normal shot
      [*] = ;         def := enRangedDefence - abil77;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := att;
      [*] = ;   IntRegister1 := def;
      [*] = ;   BoolRegister0 := simulate;
      [*] = ;   MapExecuteState('bat.GetHit');
      [*] = ;   damage := IntRegister2;
      [*] = ;   damage_low := IntRegister3;
      [*] = ;   damage_high := IntRegister4;
      [*] = ;
      [*] = ;   if _unit_CheckAbility(enGOHandle, gc_ability_fire_immunity) = 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_ability_fire_arrows;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if (IntRegister1 > 0) then
      [*] = ;      begin
      [*] = ;         def := IntRegister1;
      [*] = ;         if enResist = -1 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_battle_unit_iResist;
      [*] = ;            GameObjectExecuteStateByHandle(enGOHandle, 'GetProperty');
      [*] = ;            enResist := IntRegister1;
      [*] = ;         end;
      [*] = ;         if def > enResist then
      [*] = ;         begin
      [*] = ;            def := def - enResist;
      [*] = ;            damage := damage + def;
      [*] = ;            damage_low := damage_low + def;
      [*] = ;            damage_high := damage_high + def;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;IntRegister1 := damage;
      [*] = ;IntRegister2 := damage_low;
      [*] = ;IntRegister3 := damage_high;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

