section.begin
   Name = MakePolymorph
   Description : struct.begin
      [*] = IntRegister0 - polymorph unit ID
      [*] = IntRegister1 - spell ID
      [*] = IntRegister2 - spell power
      [*] = IntRegister3 - spell duration
      [*] = BoolRegister0 - destroy on hit
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var polUnitID : Integer = IntRegister0;
      [*] = ;var spellID : Integer = IntRegister1;
      [*] = ;var spellPower : Integer = IntRegister2;
      [*] = ;var duration : Integer = IntRegister3;
      [*] = ;var bDestroyOnHit : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;
      [*] = ;var tfUID : Integer = GetIntValueByIndex(gc_stack_unit_iTrueFormUID);
      [*] = ;if tfUID = 0 then
      [*] = ;tfUID := myUID;
      [*] = ;
      [*] = ;IntRegister0 := polUnitID;
      [*] = ;IntRegister1 := GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;IntRegister2 := GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'AddUnit');
      [*] = ;var newGOHandle : Integer = IntRegister3;
      [*] = ;var pNewParser : Integer = ParserSelectGameObject(newGOHandle);
      [*] = ;var pNewEffects : Integer = ParserSelectByHandleByKey(pNewParser, 'Effects');
      [*] = ;
      [*] = ;var unitID : Integer = GetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iUnitID);
      [*] = ;IntRegister0 := myGOHandle;
      [*] = ;GameObjectExecuteStateByHandle(newGOHandle, 'CopyStackFrom');
      [*] = ;SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iUnitID, unitID);
      [*] = ;
      [*] = ;ParserClearByHandle(pNewEffects);
      [*] = ;ParserCopyFromByHandle(pMyEffects);
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(newGOHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;// set effect
      [*] = ;var pGOEffect : Integer = _unit_AddEffect(newGOHandle, 90, spellPower, duration);
      [*] = ;ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentSpellID', spellID);
      [*] = ;ParserSetBoolValueByKeyByHandle(pGOEffect, 'DestroyOnHit', bDestroyOnHit);
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iTrueFormUID, tfUID);
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurLife, 0);
      [*] = ;SetGameObjectMyPlayableObject(false);
      [*] = ;SetGameObjectMyVisible(false);
      [*] = ;
      [*] = ;_unit_GUIUpdateUnitHUD(newGOHandle);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
