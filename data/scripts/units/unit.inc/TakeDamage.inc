section.begin
   Name = TakeDamage
   Description : struct.begin
      [*] = ;IntRegister0 - damage value
      [*] = ;IntRegister1 - damage type
      [*] = ;IntRegister2 - attacker UID
      [*] = ;FloatRegister0 - delay time - NOT USED
      [*] = ;OUT: BoolRegister0 - is dead
   struct.end
   Code : struct.begin
      [*] = ;var hit : Integer = IntRegister0;
      [*] = ;var dType : Integer = IntRegister1;
      [*] = ;var aUID : Integer = IntRegister2;
      [*] = ;//var delayTime : Float = FloatRegister0; // ???
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\TAKEDAMAGE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var curLife : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurLife);
      [*] = ;var curMoral : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurMoral);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName;
      [*] = ;
      [*] = ;var myGridX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(GetGameObjectMyHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+myCustomName+',H:'+IntToStr(hit)+',T:'+IntToStr(dType)+',AUID:'+IntToStr(aUID)+']',_log_trace);
      [*] = ;case dType of
      [*] = ;   0 : begin
      [*] = ;      var meleeDamageTaken : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMeleeDamageTaken);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iMeleeDamageTaken, meleeDamageTaken + hit);
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      var rangeDamageTaken : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iRangeDamageTaken);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iRangeDamageTaken, rangeDamageTaken + hit);
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      var spellDamageTaken : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iSpellDamageTaken);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iSpellDamageTaken, spellDamageTaken + hit);
      [*] = ;   end;
      [*] = ;   3 : begin
      [*] = ;      var poisonDamageTaken : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iPoisonDamageTaken);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iPoisonDamageTaken, poisonDamageTaken + hit);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, i);
      [*] = ;   if ParserGetBoolValueByKeyByHandle(pMyEffect, 'DestroyOnHit') then
      [*] = ;      ParserFreeByHandle(pMyEffect);
      [*] = ;end;
      [*] = ;
      [*] = ;curLife := max(0,curLife - hit);
      [*] = ;if curLife = 0 then
      [*] = ;begin
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurLife, 0);
      [*] = ;
      [*] = ;   IntRegister0 := aUID;
      [*] = ;   ExecuteState('Death');
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var pDestUnit : Integer = _log_battle_GetDestUnitParseryUID(_log_battle_GetLastLogElement(), myUID);
      [*] = ;
      [*] = ;      if pDestUnit <> 0 then
      [*] = ;         ParserSetIntValueByKeyByHandle(pDestUnit, 'ActionResult', 1);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxMoral;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxMoral : Integer = IntRegister1;
      [*] = ;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurLife, curLife);
      [*] = ;
      [*] = ;   if ((hit >= maxLife / 4) or (hit > 9)) and (dType <> 3) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_ability_berserk;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      var abil25 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_berserk;
      [*] = ;      ExecuteState('IsAbilityInEffects');
      [*] = ;      var isEff25 : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;      if (abil25 > 0) and (not isEff25) then
      [*] = ;      begin
      [*] = ;         if curMoral < maxMoral then
      [*] = ;            curMoral := maxMoral;
      [*] = ;         SetGameObjectMyIntValueInd(gc_stack_unit_iCurMoral, curMoral);
      [*] = ;
      [*] = ;         _unit_AddEffect(myGOHandle, 2, abil25, 0);
      [*] = ;         var pNewEffect : Integer = _unit_AddEffect(myGOHandle, 25, abil25, 0);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pNewEffect, 'Visible', true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewEffect, 'ParentUpgradeID', 55);
      [*] = ;         _unit_AddEffect(myGOHandle, 13, 1, 0);
      [*] = ;         _unit_AddEffect(myGOHandle, 19, 1, 0);
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyParser, 'BerserkUID', aUID);
      [*] = ;         _unit_SetupFlyText(GetGameObjectMyHandle(), aUID, gc_flytext_CategoryAbility, gc_ability_berserk, 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var moralChange : Integer = -1;
      [*] = ;         // world rule
      [*] = ;         if _worldrule_GetWorldRuleAbilityExistByID(15) then
      [*] = ;            moralChange := moralChange+_worldrule_GetWorldRuleAbilityParam1(15);
      [*] = ;
      [*] = ;         IntRegister0 := moralChange;
      [*] = ;         ExecuteState('ChangeMoral');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(curLife)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;BoolRegister0 := (curLife = 0);
   struct.end
section.end

