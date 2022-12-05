section.begin
   Name = OnAfterLoad
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;const objectType = 'BattleUnit';
      [*] = ;_obj_UpdateStackVariables(myHandle, objectType);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myHandle);
      [*] = ;
      [*] = ;var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;ParserSetIntValueByKeyByHandle(pMyParser, 'UnitID', unitID);
      [*] = ;
      [*] = ;var pMyAttackList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackList');
      [*] = ;if pMyAttackList = 0 then
      [*] = ;pMyAttackList := ParserAddChildByIndex(pMyParser, 'AttackList');
      [*] = ;
      [*] = ;var pMyAttackAnimList : Integer = ParserSelectByHandleByKey(pMyParser, 'AttackAnimList');
      [*] = ;if pMyAttackAnimList = 0 then
      [*] = ;pMyAttackAnimList := ParserAddChildByIndex(pMyParser, 'AttackAnimList');
      [*] = ;
      [*] = ;var pRoundTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'RoundTargets');
      [*] = ;if pRoundTargets = 0 then
      [*] = ;pRoundTargets := ParserAddChildByIndex(pMyParser, 'RoundTargets');
      [*] = ;
      [*] = ;var pChangedParams : Integer = ParserSelectByHandleByKey(pMyParser, 'ChangedParams');
      [*] = ;if pChangedParams = 0 then
      [*] = ;pChangedParams := ParserAddChildByIndex(pMyParser, 'ChangedParams');
      [*] = ;
      [*] = ;if (GetGameObjectVisibleByHandle(myHandle)) then
      [*] = ;_fx_HideEnvironmentAroundTacticalUnit(myHandle);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

