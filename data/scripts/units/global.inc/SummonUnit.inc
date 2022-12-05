section.begin
   Name = SummonUnit
   Description : struct.begin
      [*] = ;IntRegister0 - unit ID
      [*] = ;IntRegister1 - level
      [*] = ;IntRegister2 - position X
      [*] = ;IntRegister3 - position Y
      [*] = ;RET: IntRegister4 - goHandle
   struct.end
   Code : struct.begin
      [*] = ;var unitID : Integer = IntRegister0;
      [*] = ;var level : Integer = IntRegister1;
      [*] = ;var posX : Integer = IntRegister2;
      [*] = ;var posY : Integer = IntRegister3;
      [*] = ;
      [*] = ;IntRegister0 := unitID;
      [*] = ;IntRegister1 := posX;
      [*] = ;IntRegister2 := posY;
      [*] = ;ExecuteState('AddUnit');
      [*] = ;var goHandle : Integer = IntRegister3;
      [*] = ;
      [*] = ;IntRegister0 := unitID;
      [*] = ;IntRegister1 := level;
      [*] = ;MapExecuteState('GetUnitExpByLevel');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iExperience, IntRegister2);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := 0 to level-1 do
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'LevelUp');
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'CreateSpellList');
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxMoral;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurMoral, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxStamina;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurStamina, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMovePoints, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxAmmo;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurAmmo, IntRegister1);
      [*] = ;
      [*] = ;SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bSummoned, true);
      [*] = ;// these should be set to defaults during Initial:
      [*] = ;//SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iFear, 0);
      [*] = ;//SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct, true);
      [*] = ;//SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bResting, false);
      [*] = ;//SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bParry, false);
      [*] = ;
      [*] = ;if _unit_CheckAbility(goHandle, gc_ability_march) > 0 then
      [*] = ;   SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanMarch, true);
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;_unit_GUIUpdateUnitHUD(goHandle);
      [*] = ;
      [*] = ;IntRegister4 := goHandle;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

