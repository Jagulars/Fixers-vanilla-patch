section.begin
   Name = HitEffect
   Description : struct.begin
      [*] = ;IntRegister0 - target UID
      [*] = ;IntRegister1 - hit value
      [*] = ;BoolRegister0 - is attack or counter attack
      [*] = ;BoolRegister1 - is round attack
      [*] = ;BoolRegister2 - apply effects
      [*] = ;OUT: IntRegister2 - vampire value
   struct.end
   Code : struct.begin
      [*] = ;var tUID : Integer = IntRegister0;
      [*] = ;var hit : Integer = IntRegister1;
      [*] = ;var bAtt : Boolean = BoolRegister0;
      [*] = ;var bCanRound : Boolean = BoolRegister1;
      [*] = ;var bApplyEffects : Boolean = BoolRegister2;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\HITEFFECT';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myUnitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;var pMyUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, myUnitID);
      [*] = ;var isHero : Boolean =GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;var myGridX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var curLife : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var tIsHero : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bIsHero);
      [*] = ;var tUnitID : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iUnitID);
      [*] = ;var pTarUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, tUnitID);
      [*] = ;var tUnitType : Integer = ParserGetIntValueByKeyByHandle(pTarUnit, 'UnitType');
      [*] = ;
      [*] = ;var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName+', Target: '+GetGameObjectCustomNameByHandle(tGOHandle)+']',_log_trace);
      [*] = ;
      [*] = ;var FrameShift : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iDamageFrame);
      [*] = ;var goIntFactor : Float = GetGameObjectIntervalFactorByHandle(myGOHandle);
      [*] = ;var goOrignInt  : Integer = GetGameObjectOrignIntervalByHandle(myGOHandle);
      [*] = ;var delayTime : Float = FrameShift*goOrignInt/(1000*goIntFactor);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var vampire : Integer = 0;
      [*] = ;
      [*] = ;var abil40 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_stunning_blow);
      [*] = ;var abil41 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_poison_attack);
      [*] = ;var abil42 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_poison_immunity);
      [*] = ;var abil50 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_fear);
      [*] = ;var abil126 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_poison_bite);
      [*] = ;
      [*] = ;var tAbil96 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_poison_flesh);
      [*] = ;var tAbil42 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_poison_immunity);
      [*] = ;
      [*] = ;if bApplyEffects then
      [*] = ;begin
      [*] = ;   // poisonous strike
      [*] = ;   if (abil41 > 0) and (tAbil42 = 0) then
      [*] = ;   begin
      [*] = ;      var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 1, -abil41, gc_PoisonDuration);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 71);
      [*] = ;      _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_poison_attack, 0);
      [*] = ;      //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_poison_attack, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // poisonous bite
      [*] = ;   var poisonBite : Boolean = GetBoolValueByIndex(gc_stack_unit_bPoisonBite);
      [*] = ;   if poisonBite and (tAbil42 = 0) then
      [*] = ;   begin
      [*] = ;      var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 1, -abil126, gc_PoisonDuration);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 71);
      [*] = ;      _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_poison_bite, 0);
      [*] = ;      //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_poison_bite, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // poisonous flesh
      [*] = ;   if (abil42 = 0) and (tAbil96 > 0) then
      [*] = ;   begin
      [*] = ;      var pGOEffect : Integer = _unit_AddEffect(myGOHandle, 1, -tAbil96, gc_PoisonDuration);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;      ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 71);
      [*] = ;      _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_poison_flesh, 0);
      [*] = ;      //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_poison_flesh, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // stunning strike
      [*] = ;   if (abil40 > 0) and (_unit_CheckAbility(tGOHandle, gc_ability_tireless) = 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := -abil40;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'ChangeStamina');
      [*] = ;      _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_stunning_blow, 0);
      [*] = ;      //_fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryAbility, gc_ability_stunning_blow, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // frightening
      [*] = ;   if (abil50 > 0) and (_unit_CheckAbility(tGOHandle, gc_ability_fearless) = 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := -abil50;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'ChangeMoral');
      [*] = ;      _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_fear, 0);
      [*] = ;      //_fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryAbility, gc_ability_fear, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if myUID <> tUID then
      [*] = ;begin
      [*] = ;   if bApplyEffects then
      [*] = ;   begin
      [*] = ;      var tCurAmmo : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurAmmo);
      [*] = ;      var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;      IntRegister0 := gc_battle_unit_iResist;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'GetProperty');
      [*] = ;      var tResist : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var abil43 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_hex);
      [*] = ;      var abil44 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_weapons_thief);
      [*] = ;      var abil45 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_armor_damage);
      [*] = ;      var abil51 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_hamstring_bite);
      [*] = ;      var abil67 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_roots);
      [*] = ;      var abil79 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_vulnerability);
      [*] = ;      var abil80 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_disease);
      [*] = ;      var abil123 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_desecration);
      [*] = ;
      [*] = ;      var tAbil30 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_spell_immunity);
      [*] = ;      var tAbil52 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_damage_weapon);
      [*] = ;      var tAbil96 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_poison_flesh);
      [*] = ;      var tAbil109 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_web_immunity);
      [*] = ;      var tAbil123 : Integer = _unit_CheckAbility(tGOHandle, gc_ability_desecration);
      [*] = ;
      [*] = ;      // stealing ammo
      [*] = ;      if (abil44 > 0) and (tCurAmmo > 0) then
      [*] = ;      begin
      [*] = ;         var sa : Integer;
      [*] = ;
      [*] = ;         sa := min(tCurAmmo,abil44);
      [*] = ;         SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurAmmo, tCurAmmo - sa);
      [*] = ;         if sa > 0 then
      [*] = ;            _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_weapons_thief, sa);
      [*] = ;            //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_weapons_thief, sa);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // damaging armor
      [*] = ;      if (abil45 > 0) then
      [*] = ;      begin
      [*] = ;         var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 4, -1, abil45);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 75);
      [*] = ;
      [*] = ;         if tIsHero then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 1;
      [*] = ;            IntRegister1 := myUID;
      [*] = ;            GameObjectExecuteStateByHandle(tGOHandle, 'DamageArmor');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // roots
      [*] = ;      if (abil67 > 0) and (tCurLife > hit) and (tAbil109 = 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 109;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;         var pGOEffect : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if pGOEffect <> 0 then
      [*] = ;         begin
      [*] = ;            var duration : Integer = ParserGetIntValueByKeyByHandle(pGOEffect, 'Duration');
      [*] = ;            if duration < abil67 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 109;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               IntRegister2 := abil67;
      [*] = ;               GameObjectExecuteStateByHandle(tGOHandle, 'SetEffectsDuration');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 88, 1, abil67);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 109);
      [*] = ;         end;
      [*] = ;         _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_roots, 0);
      [*] = ;         //_fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryAbility, gc_ability_roots, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // damage weapon
      [*] = ;      if tAbil52 > 0 then
      [*] = ;      begin
      [*] = ;         var pGOEffect : Integer = _unit_AddEffect(myGOHandle, 2, -1, tAbil52);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 82);
      [*] = ;
      [*] = ;         pGOEffect := _unit_AddEffect(myGOHandle, 3, -1, tAbil52);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 82);
      [*] = ;
      [*] = ;         if isHero then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 2;
      [*] = ;            IntRegister1 := 1;
      [*] = ;            ExecuteState('DamageWeapon');
      [*] = ;            IntRegister0 := 2;
      [*] = ;            IntRegister1 := 2;
      [*] = ;            ExecuteState('DamageWeapon');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // hamstring bite
      [*] = ;      if abil51 > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 81;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;         var pGOEffect : Integer = IntRegister1;
      [*] = ;
      [*] = ;         if pGOEffect <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := 81;
      [*] = ;            IntRegister1 := 0;
      [*] = ;            IntRegister2 := 2;
      [*] = ;            GameObjectExecuteStateByHandle(tGOHandle, 'SetEffectsDuration');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 7, -1, 2);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 81);
      [*] = ;         end;
      [*] = ;         _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_hamstring_bite, 0);
      [*] = ;         //_fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryAbility, gc_ability_hamstring_bite, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // curse
      [*] = ;      if (abil43 > tResist) and (tAbil30 = 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 73;
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;         var pGOEffect : Integer = IntRegister1;
      [*] = ;         var sa : Integer = abil43 - tResist;
      [*] = ;
      [*] = ;         if pGOEffect <> 0 then
      [*] = ;         begin
      [*] = ;            var duration : Integer = ParserGetIntValueByKeyByHandle(pGOEffect, 'Duration');
      [*] = ;
      [*] = ;            if duration < sa then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 73;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               IntRegister2 := sa;
      [*] = ;               GameObjectExecuteStateByHandle(tGOHandle, 'SetEffectsDuration');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var pGOEffect : Integer = _unit_AddEffect(tGOHandle, 2, -1, sa);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 73);
      [*] = ;
      [*] = ;            pGOEffect := _unit_AddEffect(tGOHandle, 4, -1, sa);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 73);
      [*] = ;
      [*] = ;            pGOEffect := _unit_AddEffect(tGOHandle, 5, -1, sa);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 73);
      [*] = ;
      [*] = ;            pGOEffect := _unit_AddEffect(tGOHandle, 6, -1, sa);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', 73);
      [*] = ;         end;
      [*] = ;         if sa > 0 then
      [*] = ;            _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_hex, 0);
      [*] = ;            //_fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryAbility, gc_ability_hex, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // vulnerability
      [*] = ;      var pSpEffects : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gPrototypeData.spells.handle, 21), 'Effects');
      [*] = ;      var effDuration : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pSpEffects, 0), 'Duration');
      [*] = ;
      [*] = ;      if (abil79 > 0) and (effDuration >= tResist) and (tAbil30 = 0) then
      [*] = ;      begin
      [*] = ;         var ind : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;
      [*] = ;         IntRegister0 := 21;
      [*] = ;         IntRegister1 := pHexCell;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         ExecuteState('CastSpell');
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'DeathAnimReady');
      [*] = ;      end;
      [*] = ;
      [*] = ;      // disease
      [*] = ;      pSpEffects := ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gPrototypeData.spells.handle, 30), 'Effects');
      [*] = ;      effDuration := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pSpEffects, 0), 'Duration');
      [*] = ;
      [*] = ;      if (abil80 > 0) and (effDuration >= tResist) and (tAbil30 = 0) and (tUnitType <> 2) and (tUnitType <> 4) then
      [*] = ;      begin
      [*] = ;         var ind : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;
      [*] = ;         IntRegister0 := 30;
      [*] = ;         IntRegister1 := pHexCell;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         ExecuteState('CastSpell');
      [*] = ;         GameObjectExecuteStateByHandle(tGOHandle, 'DeathAnimReady');
      [*] = ;      end;
      [*] = ;
      [*] = ;      // desecration
      [*] = ;      if (abil123 > 0) and (tAbil123 = 0) and ((tUnitType = 1) or (tUnitType = 5)) then
      [*] = ;      begin
      [*] = ;         var dur : Integer = abil123 - tResist;
      [*] = ;         if dur > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_upgrade_desecration;
      [*] = ;            GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;            var pGOEffect : Integer = IntRegister1;
      [*] = ;
      [*] = ;            if pGOEffect <> 0 then
      [*] = ;            begin
      [*] = ;               var duration : Integer = ParserGetIntValueByKeyByHandle(pGOEffect, 'Duration');
      [*] = ;               if duration < dur then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gc_upgrade_desecration;
      [*] = ;                  IntRegister1 := 0;
      [*] = ;                  IntRegister2 := dur;
      [*] = ;                  GameObjectExecuteStateByHandle(tGOHandle, 'SetEffectsDuration');
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var pGOEffect : Integer = _unit_AddEffect(tGOHandle, gc_ability_zombie, 1, dur);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pGOEffect, 'Visible', true);
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOEffect, 'ParentUpgradeID', gc_upgrade_desecration);
      [*] = ;            end;
      [*] = ;            _unit_SetupFlyText(tGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_desecration, 0);
      [*] = ;            //_fx_CreateFlyText_VVK(tGOHandle, gc_flytext_CategoryAbility, gc_ability_desecration, 0);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // round attack, fire breath, lightning
      [*] = ;   var bRoundAttack : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bRoundAttack);
      [*] = ;   var bFireBreath : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bFireBreath);
      [*] = ;
      [*] = ;   var isRound : Boolean = bCanRound and ((_unit_CheckAbility(myGOHandle, gc_ability_common_attack) > 0) or (bRoundAttack and bAtt));
      [*] = ;   var isFireBreath : Boolean = bCanRound and bFireBreath and bAtt;
      [*] = ;   var isLightning : Boolean = bCanRound and (_unit_CheckAbility(myGOHandle, gc_ability_lightning) > 0);
      [*] = ;
      [*] = ;   if isRound or isLightning or isFireBreath then
      [*] = ;   begin
      [*] = ;      var bEffect : Boolean = false;
      [*] = ;      var pMyNeighbours : Integer = ParserSelectByHandleByKey(pMyParser, 'Neighbours');
      [*] = ;      var pMyRoundTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'RoundTargets');
      [*] = ;      ParserClearByHandle(pMyRoundTargets);
      [*] = ;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      if isRound then
      [*] = ;      begin
      [*] = ;         IntRegister0 := myGridX;
      [*] = ;         IntRegister1 := myGridY;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := tGridX;
      [*] = ;         IntRegister1 := tGridY;
      [*] = ;      end;
      [*] = ;      ExecuteState('FindNeighbour');
      [*] = ;      var nCount : Integer = IntRegister2;
      [*] = ;
      [*] = ;      for i := 0 to nCount-1 do
      [*] = ;      begin
      [*] = ;         var pMyNeighbour : Integer = ParserSelectByHandleByIndex(pMyNeighbours, i);
      [*] = ;         var nUID : Integer = ParserGetIntValueByKeyByHandle(pMyNeighbour, 'UID');
      [*] = ;         var nGOHandle : Integer = GetGameObjectHandleByUniqueId(nUID);
      [*] = ;         var nCurLife : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;         var neiAttack : Boolean = isRound or isLightning;
      [*] = ;         if (not neiAttack) and isFireBreath then
      [*] = ;         begin
      [*] = ;            var myX : Float = GetGameObjectMyPositionX();
      [*] = ;            var myZ : Float = GetGameObjectMyPositionZ();
      [*] = ;            var tarX : Float = GetGameObjectPositionXByHandle(tGOHandle);
      [*] = ;            var tarZ : Float = GetGameObjectPositionZByHandle(tGOHandle);
      [*] = ;            var neiX : Float = GetGameObjectPositionXByHandle(nGOHandle);
      [*] = ;            var neiZ : Float = GetGameObjectPositionZByHandle(nGOHandle);
      [*] = ;            var angle : Float = VectorAngle(myX - tarX, 0, myZ - tarZ, neiX - tarX, 0, neiZ - tarZ);
      [*] = ;            neiAttack := (Round(angle / 60) = 3);
      [*] = ;            if neiAttack then
      [*] = ;               neiAttack := (_unit_CheckAbility(nGOHandle, 121) = 0);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if neiAttack and (nCurLife > 0) and (nUID <> tUID) then
      [*] = ;         begin
      [*] = ;            bEffect := true;
      [*] = ;            
      [*] = ;            // check slyboots ability
      [*] = ;            var runBack : Boolean = false;
      [*] = ;            if gBoolRegister_BattleIsAttackerAction then
      [*] = ;            begin
      [*] = ;               IntRegister0 := myUID;
      [*] = ;               GameObjectExecuteStateByHandle(nGOHandle, 'CheckSlyBootsAbility');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  if (( _unit_CheckAbility(nGOHandle, gc_ability_immobilized) = 0 ) and ( _unit_CheckAbility(nGOHandle, gc_ability_cantmove) = 0 )) then
      [*] = ;                  begin
      [*] = ;                     SetGameObjectBoolValueIndByHandle(nGOHandle, gc_stack_unit_bRunBack, true);
      [*] = ;                     runBack := true;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if not runBack then
      [*] = ;            begin
      [*] = ;               var nCurLife : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;               IntRegister0 := nGOHandle;
      [*] = ;               IntRegister1 := -1;
      [*] = ;               BoolRegister0 := bAtt;
      [*] = ;               BoolRegister1 := isLightning;
      [*] = ;               BoolRegister2 := isLightning;
      [*] = ;               BoolRegister3 := true;
      [*] = ;               ExecuteState('GetMeleeHit');
      [*] = ;               var hit : Integer = IntRegister2;
      [*] = ;
      [*] = ;               if hit > nCurLife then
      [*] = ;                  hit := nCurLife;
      [*] = ;
      [*] = ;               // Fly text data
      [*] = ;               var oldLife : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurLife);
      [*] = ;               var oldStamina : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;               var oldMoral : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;               IntRegister0 := nUID;
      [*] = ;               IntRegister1 := hit;
      [*] = ;               BoolRegister0 := bAtt;
      [*] = ;               BoolRegister1 := false;
      [*] = ;               BoolRegister2 := true;
      [*] = ;               ExecuteState('HitEffect');
      [*] = ;               vampire := vampire + IntRegister2;
      [*] = ;
      [*] = ;               IntRegister0 := hit;
      [*] = ;               IntRegister1 := 1;
      [*] = ;               IntRegister2 := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;               FloatRegister0 := delayTime;
      [*] = ;               GameObjectExecuteStateByHandle(nGOHandle, 'TakeDamage');
      [*] = ;               var isDead : Boolean = BoolRegister0;
      [*] = ;               var deathAnimReady : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iDeathAnimReady) + 1;
      [*] = ;               SetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;
      [*] = ;               if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;                  _unit_SetupStatsTextData(nGOHandle, myUID, oldLife, oldStamina, oldMoral);
      [*] = ;
      [*] = ;               if isDead then
      [*] = ;               begin
      [*] = ;                  SetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iKillerUID, myUID);
      [*] = ;
      [*] = ;                  IntRegister0 := nUID;
      [*] = ;                  ExecuteState('SoulSteal');
      [*] = ;               end;
      [*] = ;               
      [*] = ;               if _log then _log_obj(_log_name+'[Collateral: '+GetGameObjectCustomNameByHandle(nGOHandle)+', DAR: '+IntToStr(GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iDeathAnimReady)));
      [*] = ;            end;
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pMyRoundTargets, '*'), 'UID', nUID);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // vampirism
      [*] = ;   var va: Integer = _unit_CheckAbility(myGOHandle, gc_ability_vampire);
      [*] = ;   if (va > 0) and (tUnitType <> 2) and (tUnitType <> 4) and (curLife < maxLife) then
      [*] = ;   begin
      [*] = ;      var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;      var drain : Integer = (hit * va) div 100;
      [*] = ;
      [*] = ;      if drain > maxLife - curLife then
      [*] = ;         drain := maxLife - curLife;
      [*] = ;
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iCurLife, curLife + drain);
      [*] = ;      vampire := vampire + drain;
      [*] = ;
      [*] = ;      if (drain<>0) then
      [*] = ;      begin
      [*] = ;         _unit_SetupFlyText(myGOHandle, myUID, gc_flytext_CategoryAbility, gc_ability_vampire, 0);
      [*] = ;         //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_vampire, 0);
      [*] = ;         //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam,gc_battle_unit_iCurLife, drain);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[LD: '+IntToStr(vampire)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister2 := vampire;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

