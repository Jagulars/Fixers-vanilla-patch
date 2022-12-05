section.begin
   Name = battle.ActivateAbility
   Code : struct.begin
      [*] = ;var sPress  : String  = GetValueByName('Press');
      [*] = ;
      [*] = ;if sPress <> 'c' then
      [*] = ;   exit;
      [*] = ;
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var abilityID : Integer = tag - gc_gui_battle_btnControlAbilityBaseTag;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := 6; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;   IntRegister1 := 0; //0 - hide
      [*] = ;   GUIExecuteState('DoDragElement');
      [*] = ;   gIntRegister_CurSpell := -1;
      [*] = ;   gIntRegister_CurSpellIndex := -1;
      [*] = ;   gIntRegister_SacrificeUID := 0;
      [*] = ;   gIntRegister_TeleportUID := 0;
      [*] = ;
      [*] = ;   IntRegister0 := abilityID;
      [*] = ;   BoolRegister0 := true; //send parser when stealth or eat corpse
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'ActivateAbility');
      [*] = ;   if (not GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct)) then
      [*] = ;      GUIExecuteState('battle.SelectNextUnit');
      [*] = ;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;   GUIExecuteState('battle.ResetHexGrid');
      [*] = ;end;
   struct.end
section.end

