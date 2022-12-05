section.begin
   Name = AddUnit
   Description : struct.begin
      [*] = ;IntRegister0 - unit ID
      [*] = ;IntRegister1 - position X
      [*] = ;IntRegister2 - position Y
      [*] = ;OUT: IntRegister3 - game object handle
   struct.end
   Code : struct.begin
      [*] = ;var unitID : Integer = IntRegister0;
      [*] = ;var posX : Integer = IntRegister1;
      [*] = ;var posY : Integer = IntRegister2;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var pHexGrid : Integer = gHexCells.handle;
      [*] = ;var ind : Integer = posY * gc_battle_GridSize + posX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(pHexGrid, ind);
      [*] = ;var x, y, z : Float;
      [*] = ;
      [*] = ;var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;var objectName : String = '';
      [*] = ;var baseName : String = ParserGetValueByKeyByHandle(pUnit, 'Name');
      [*] = ;if _misc_IsVisibleBattle then
      [*] = ;   objectName := baseName
      [*] = ;else
      [*] = ;   objectName := 'unit_dummy';
      [*] = ;
      [*] = ;GetTrackNodePositionByIndex(ind, x, y, z);
      [*] = ;
      [*] = ;var plRace : String = GetPlayerRaceNameByHandle(myPlHandle);
      [*] = ;var isAttack : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;var goHandle : Integer = _obj_GetRecycledOrCreate(myPlHandle, plRace, baseName, x, 0, z);
      [*] = ;SetGameObjectCustomNameByHandle(goHandle, baseName+'_'+IntToStr(GetGameObjectUniqueIdByHandle(goHandle)));
      [*] = ;
      [*] = ;if not gBoolRegister_BattleSimulate then
      [*] = ;begin
      [*] = ;   GameObjectTrackPointClearByHandle(goHandle);
      [*] = ;   GameObjectTrackPointAddByHandle(goHandle, x, y, z);
      [*] = ;
      [*] = ;   if isAttack = 1 then
      [*] = ;   begin
      [*] = ;      GameObjectRollByHandle(goHandle, 180);
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iFacing, 3);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iFacing, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID, unitID);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iBattleX, posX);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iBattleY, posY);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLastX, posX);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLastY, posY);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX, posX);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY, posY);
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMeleeDamageDone, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iRangeDamageDone, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMeleeDamageTaken, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iRangeDamageTaken, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iSpellDamageTaken, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iPoisonDamageTaken, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iDamageHealed, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iSpellCast, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iEnemyShooted, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iEnemySlayed, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iStaminaUsed, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iSurvived, 0);
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pHexCell, 'UID', GetGameObjectUniqueIdByHandle(goHandle));
      [*] = ;
      [*] = ;_fx_HideEnvironmentAroundTacticalUnit(goHandle);
      [*] = ;
      [*] = ;IntRegister3 := goHandle;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
