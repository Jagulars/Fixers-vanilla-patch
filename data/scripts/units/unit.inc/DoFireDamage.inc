section.begin
   Name = DoFireDamage
   Description : struct.begin
      [*] = ;IntRegister0 - target UID
      [*] = ;BoolRegister0 - half damage
   struct.end
   Code : struct.begin
      [*] = ;var tUID : Integer = IntRegister0;
      [*] = ;var isHalf : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\DOFIREDAMAGE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myIsHero : Boolean = GetBoolValueByIndex(gc_stack_unit_bIsHero);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var autoBattle : Boolean = GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle);
      [*] = ;
      [*] = ;var actAbility : Integer = GetIntValueByIndex(gc_stack_unit_iActiveAbility);
      [*] = ;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var tCustomName : String = GetGameObjectCustomNameByHandle(tGOHandle);
      [*] = ;var tIsHero : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bIsHero);
      [*] = ;var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;var oldLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var oldStamina : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;var oldMoral : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iResist;
      [*] = ;GameObjectExecuteStateByHandle(tGOHandle, 'GetProperty');
      [*] = ;var enResist : Integer = IntRegister1;
      [*] = ;
      [*] = ;var abil46 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_stoned);
      [*] = ;var abil47 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_web);
      [*] = ;var abil135 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_bolo);
      [*] = ;
      [*] = ;var shotDone : Boolean = false;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName+', Target: '+GetGameObjectCustomNameByHandle(tGOHandle)+']',_log_trace);
      [*] = ;
      [*] = ;// stone
      [*] = ;if (abil46 > 0) then
      [*] = ;begin
      [*] = ;   var abil108 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_stone_immunity);
      [*] = ;   if (abil46 > enResist) and (abil108 = 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_upgrade_stoned;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;      var pGOEffect : Integer = IntRegister1;
      [*] = ;      var duration : Integer;
      [*] = ;
      [*] = ;      if pGOEffect <> 0 then
      [*] = ;      begin
      [*] = ;         duration := ParserGetIntValueByKeyByHandle(pGOEffect, 'Duration');
      [*] = ;         if duration < abil46 - enResist then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_upgrade_stoned;
      [*] = ;            IntRegister1 := 0;
      [*] = ;            IntRegister2 := abil46 - enResist;
      [*] = ;            duration := IntRegister2;
      [*] = ;            GameObjectExecuteStateByHandle(tGOHandle, 'SetEffectsDuration');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         duration := abil46 - enResist;
      [*] = ;
      [*] = ;         var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 36, 1, duration);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', gc_upgrade_stoned);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 4, 3, duration);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', gc_upgrade_stoned);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 5, 3, duration);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', gc_upgrade_stoned);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 38, 1, duration);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', gc_upgrade_stoned);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 6, 3, duration);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', gc_upgrade_stoned);
      [*] = ;
      [*] = ;         SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iMovePoints, 0);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanAct, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanMelee, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanShoot, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanCast, false);
      [*] = ;      end;
      [*] = ;      _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_stoned, duration);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryParam, gc_battle_unit_iResist, 0);
      [*] = ;
      [*] = ;   shotDone := true;
      [*] = ;end;
      [*] = ;
      [*] = ;// web and bolo
      [*] = ;if (abil47 > 0) or (abil135 > 0) then
      [*] = ;begin
      [*] = ;   if (_unit_CheckAbility(tGOHandle, gc_ability_web_immunity) = 0) then
      [*] = ;   begin
      [*] = ;      var duration : Integer;
      [*] = ;      IntRegister0 := gc_battle_unit_iAttack;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetProperty');
      [*] = ;      var enAttack : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var effTime : Integer = 2;
      [*] = ;      if ((abil47 > 0) and (abil47 > enAttack)) or ((abil135 > 0) and (abil135 > enAttack)) then
      [*] = ;         effTime := 3;
      [*] = ;
      [*] = ;      var upgradeID,spellID : Integer;
      [*] = ;      if abil47 > 0 then
      [*] = ;      begin
      [*] = ;         upgradeID := gc_upgrade_web;
      [*] = ;         spellID := gc_spell_web;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         upgradeID := gc_upgrade_bolo;
      [*] = ;         spellID := 0;
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := gc_upgrade_bolo;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;      var pGOEffect : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if (pGOEffect = 0) and (abil47 > 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := spellID;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserBySpellID');
      [*] = ;         pGOEffect := IntRegister1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pGOEffect <> 0 then
      [*] = ;      begin
      [*] = ;         duration := ParserGetIntValueByKeyByHandle(pGOEffect, 'Duration') + 1;
      [*] = ;
      [*] = ;         IntRegister0 := upgradeID;
      [*] = ;         IntRegister1 := spellID;
      [*] = ;         IntRegister2 := duration;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'SetEffectsDuration');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 36, 1, effTime);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', upgradeID);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 4, 1, effTime);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', upgradeID);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 5, 1, effTime);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', upgradeID);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(tGOHandle, 38, 1, effTime);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', upgradeID);
      [*] = ;
      [*] = ;         SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iMovePoints, 0);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanAct, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanMelee, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanShoot, false);
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bCanCast, false);
      [*] = ;         duration := effTime;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if abil47 > 0 then
      [*] = ;         _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_web, duration)
      [*] = ;      else
      [*] = ;         _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_bolo, duration);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryParam, gc_battle_unit_iResist, 0);
      [*] = ;
      [*] = ;   //if abil47 > 0 then
      [*] = ;   //   shotDone := true;
      [*] = ;end;
      [*] = ;
      [*] = ;var tIsDead : Boolean = false;
      [*] = ;
      [*] = ;{var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iShotFrame);
      [*] = ;var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;var DelayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);}
      [*] = ;
      [*] = ;if not shotDone then
      [*] = ;begin
      [*] = ;   IntRegister0 := tGOHandle;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('GetRangedHit');
      [*] = ;   var hit : Integer = IntRegister1;
      [*] = ;
      [*] = ;   if isHalf then
      [*] = ;      hit := hit div 2;
      [*] = ;
      [*] = ;   if hit > tCurLife then
      [*] = ;      hit := tCurLife;
      [*] = ;
      [*] = ;   var myRangeDamageDone : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iRangeDamageDone);
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iRangeDamageDone, myRangeDamageDone + hit);
      [*] = ;
      [*] = ;   if tIsHero and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 1;
      [*] = ;      IntRegister1 := myUID;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'DamageArmor');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if myIsHero and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 1;
      [*] = ;      IntRegister1 := 2;
      [*] = ;      ExecuteState('DamageWeapon');
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := tUID;
      [*] = ;   IntRegister1 := hit;
      [*] = ;   ExecuteState('ShootEffect');
      [*] = ;
      [*] = ;   var typo : Integer = 1;
      [*] = ;   IntRegister0 := gc_ability_magic_shot;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   if IntRegister1 > 0 then
      [*] = ;      typo := 2;
      [*] = ;
      [*] = ;   IntRegister0 := hit;
      [*] = ;   IntRegister1 := typo;
      [*] = ;   IntRegister2 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   //FloatRegister0 := delayTime;
      [*] = ;   GameObjectExecuteStateByHandle(tGOHandle, 'TakeDamage');
      [*] = ;   tIsDead := BoolRegister0;
      [*] = ;   var deathAnimReady : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady) + 1;
      [*] = ;   SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;
      [*] = ;   //_Log_Map('Attack points: ' + IntToStr(damage));
      [*] = ;   //_Log_Map('Health points: ' + IntToStr(goHP));
      [*] = ;
      [*] = ;   if tIsDead then
      [*] = ;   begin
      [*] = ;      var myEnemyShooted : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iEnemyShooted);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iEnemyShooted, myEnemyShooted + 1);
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iKillerUID, myUID);
      [*] = ;
      [*] = ;      IntRegister0 := 1;
      [*] = ;      ExecuteState('ChangeMoral');
      [*] = ;
      [*] = ;      var summoned : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bSummoned);
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_necromant;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if (IntRegister1 > 0) and (not summoned) then
      [*] = ;         SetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bRaiseCorpse, true);
      [*] = ;   end;
      [*] = ;end;
	   [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
	   [*] = ;begin
      [*] = ;   _unit_SetupStatsTextData(tGOHandle, myUID, oldLife, oldStamina, oldMoral);
      [*] = ;   _log_battle_Show();
	   [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iDeathAnimReady))+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;{if (actAbility = gc_ability_double_shot) and (gBoolRegister_QuickBattle or gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iActiveAbility, 0);
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('FireAttack');
      [*] = ;end;}
      [*] = ;
      [*] = ;//PlayerExecuteStateByHandle(myPlHandle , 'LogPlayersInfo');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

