section.begin
   Name = BeforeTurn
   Code : struct.begin
      [*] = ;const gc_StealthModeStaminaPenalty = 5;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\BEFORETURN';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;// Fly text data
      [*] = ;var oldLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;var oldStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;var oldMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;var bResting : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bResting);
      [*] = ;var bCanAct : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct);
      [*] = ;var curAmmo : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo);
      [*] = ;var curStamina : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurStamina);
      [*] = ;var curLife : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;var myGridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * myGridY + myGridX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;var tType : Integer = (ParserGetIntValueByKeyByHandle(pHexCell, 'Type') + 1) div 2;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if not GetBoolValueByIndex(gc_stack_unit_bStatic) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxStamina;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxStamina : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxAmmo;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxAmmo : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iCurMoral;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var curMoral : Integer = IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var speed : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;   var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;   var pMySpells : Integer = ParserSelectByHandleByKey(pMyParser, 'Spells');
      [*] = ;
      [*] = ;   IntRegister0 := gc_ability_archmage;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   if IntRegister1 > 0 then
      [*] = ;      SetGameObjectBoolValueIndByHandle(myGOHandle, gc_stack_unit_bArchmage, true)
      [*] = ;   else
      [*] = ;      SetGameObjectBoolValueIndByHandle(myGOHandle, gc_stack_unit_bArchmage, false);
      [*] = ;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iSurvived, GetGameObjectMyIntValueInd(gc_stack_unit_iSurvived)+1);
      [*] = ;
      [*] = ;   IntRegister0 := gc_ability_parry;
      [*] = ;   ExecuteState('CheckAbility');
      [*] = ;   if IntRegister1 > 0 then
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bParry, true)
      [*] = ;   else
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bParry, false);
      [*] = ;
      [*] = ;   var hit : Integer = 0;
      [*] = ;
      [*] = ;   if bResting or (bCanAct and (not GetBoolValueByIndex(gc_stack_unit_bActionTaken))) then
      [*] = ;   begin
      [*] = ;      var stamChange : Integer;
      [*] = ;      // check for recovering stamina ability
      [*] = ;      IntRegister0 := gc_ability_stamina_recovery;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      hit := IntRegister1;
      [*] = ;      stamChange := 2 + hit;
      [*] = ;      if tType = gc_DesertTerrainType then
      [*] = ;      begin
      [*] = ;         if _unit_CheckAbility(myGOHandle, gc_ability_desert_knowledge) = 0 then
      [*] = ;            stamChange := stamChange div 2;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gIntRegister_BattleCurrentTurn > 1 then
      [*] = ;      begin
      [*] = ;         if (curStamina < maxStamina) and (hit > 0) then
      [*] = ;            _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_stamina_recovery, hit);
      [*] = ;         curStamina := min(curStamina + stamChange,maxStamina);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // check for meditation (recovering ammo) ability
      [*] = ;      IntRegister0 := gc_ability_meditation;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      hit := IntRegister1;
      [*] = ;      if (curAmmo < maxAmmo) and (hit > 0) then
      [*] = ;         _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_meditation, hit);
      [*] = ;      curAmmo := min(curAmmo + hit,maxAmmo);
      [*] = ;
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo, curAmmo);
      [*] = ;
      [*] = ;      hit := 0;
      [*] = ;      // check for first aid ability
      [*] = ;      if _unit_CheckAbility(myGOHandle, gc_ability_zombie) = 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_ability_first_aid;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         hit := IntRegister1;
      [*] = ;         if (hit > 0) and (curLife < maxLife) then
      [*] = ;            _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_first_aid, hit);
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bResting, false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var i,st_dur,web_dur : Integer;
      [*] = ;   var chInd : Integer = -1;
      [*] = ;   var stoned,webbed : Boolean;
      [*] = ;
      [*] = ;   // decreasing effect timers
      [*] = ;   stoned := false;
      [*] = ;   webbed := false;
      [*] = ;   for i := ParserGetCountByHandle(pMyEffects)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMyEffect : Integer = ParserSelectByHandleByIndex(pMyEffects, i);
      [*] = ;      var duration : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'Duration');
      [*] = ;      var abilityID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'AbilityID');
      [*] = ;      var parUpgradeID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentUpgradeID');
      [*] = ;      var parSpellID : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'ParentSpellID');
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pMyEffect, 'Power');
      [*] = ;      var visible : Boolean = ParserGetBoolValueByKeyByHandle(pMyEffect, 'Visible'); // true only for the first effect in the bundle, to avoid multiple processions.
      [*] = ;
      [*] = ;      if (abilityID = gc_ability_life) and ((power < 0) or (_unit_CheckAbility(myGOHandle, gc_ability_zombie) = 0)) then
      [*] = ;         hit := hit + power;
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_tireless;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if (abilityID = gc_ability_stamina) and ( IntRegister1 = 0) then
      [*] = ;      begin
      [*] = ;         curStamina := curStamina + power;
      [*] = ;         curStamina := Round(Clamp(curStamina, 0, maxStamina));
      [*] = ;      end;
      [*] = ;
      [*] = ;      if duration > 0 then
      [*] = ;      begin
      [*] = ;         duration := duration - 1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyEffect, 'Duration', duration);
      [*] = ;
      [*] = ;         if duration = 0 then
      [*] = ;         begin
      [*] = ;            ParserFreeByHandle(pMyEffect);
      [*] = ;
      [*] = ;            if visible and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;            begin
      [*] = ;               if (parUpgradeID = 77) or (parSpellID = gc_spell_web) then
      [*] = ;               begin
      [*] = ;                  _fx_GetOrCreateFXByID(myGOHandle, 'fxspiderwebfinish', 0, 0, 0, 0, 0, _fx_GetIDByNodeName('fxspiderwebfinish'));
      [*] = ;                  //var fxHnd : Integer = _fx_FindFXHandleByID(myGOHandle, true, 3);
      [*] = ;                  //if (fxHnd<>0) then
      [*] = ;                  //   fxHnd := _fx_GetOrCreateFXByID(myGOHandle, 'fxspiderwebfinish', 0, 0, 0, 0, 0, 3);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (parUpgradeID = 76) then
      [*] = ;               begin
      [*] = ;                  _fx_GetOrCreateFXByID(myGOHandle, 'fxstonefinish', 0, 0, 0, 0, 0, _fx_GetIDByNodeName('fxstone'));
      [*] = ;                  _unit_CheckMaterial(myGOHandle, 'fxstone');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (parSpellID = 40) then
      [*] = ;               begin
      [*] = ;                  _fx_GetOrCreateFXByID(myGOHandle, 'fx_unfreeze', 0, 0, 0, 0, 0, _fx_GetIDByNodeName('fx_freeze'));
      [*] = ;                  _unit_CheckMaterial(myGOHandle, 'fx_freeze');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (parSpellID = 33) then
      [*] = ;               begin
      [*] = ;                  _fx_GetOrCreateFXByID(myGOHandle, 'fx_stoneskin_destroy', 0, 0, 0, 0, 0, _fx_GetIDByNodeName('fx_stoneskin'));
      [*] = ;                  _unit_CheckMaterial(myGOHandle,'fx_stoneskin');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            case abilityID of
      [*] = ;               gc_ability_change_side : chInd := power;
      [*] = ;               gc_ability_phantom_form : ExecuteState('ShowTrueForm');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if visible and (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;            begin
      [*] = ;               if (parUpgradeID = 77) or (parSpellID = gc_spell_web) then // webbed
      [*] = ;               begin
      [*] = ;                  webbed := true;
      [*] = ;                  web_dur := duration;
      [*] = ;               end;
      [*] = ;               if (parUpgradeID = 76) then
      [*] = ;               begin
      [*] = ;                  stoned := true;
      [*] = ;                  st_dur := duration;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;// stealth mode stamina penalty
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bStealthMode) then
      [*] = ;   begin
      [*] = ;      curStamina := max(0,curStamina - gc_StealthModeStaminaPenalty);
      [*] = ;      //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam, gc_battle_unit_iCurStamina, -gc_StealthModeStaminaPenalty);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if stoned then
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_stoned, st_dur);
      [*] = ;   if webbed then
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_web, web_dur);
      [*] = ;   if curStamina = 0 then
      [*] = ;   begin
      [*] = ;      if GetBoolValueByIndex(gc_stack_unit_bStealthMode) then
      [*] = ;      begin
      [*] = ;         BoolRegister0 := false;
      [*] = ;         ExecuteState('SwitchStealthModeFlag');
      [*] = ;      end;
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_immobilized, 0);
      [*] = ;   end;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurStamina, curStamina);
      [*] = ;
      [*] = ;   // check for regeneration ability
      [*] = ;   if _unit_CheckAbility(myGOHandle, gc_ability_zombie) = 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_ability_regeneration;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      hit := hit + IntRegister1;
      [*] = ;      if (IntRegister1 > 0) and (curLife < maxLife) then
      [*] = ;         _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_regeneration, IntRegister1);
      [*] = ;      hit := hit + GetIntValueByIndex(gc_stack_unit_iAddHealPoints);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // poison and regeneration
      [*] = ;   if hit + curLife < 0 then
      [*] = ;      hit := -curLife;
      [*] = ;   if (hit + curLife > maxLife) and (hit > 0) then
      [*] = ;      hit := maxLife - curLife;
      [*] = ;
      [*] = ;   var abil115 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_fire_aura);
      [*] = ;   if abil115 > 0 then
      [*] = ;   begin
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_fire_aura, 0);
      [*] = ;      BoolRegister0 := false;
      [*] = ;      IntRegister0 := myGridX;
      [*] = ;      IntRegister1 := myGridY;
      [*] = ;      ExecuteState('FindNeighbour');
      [*] = ;      var nCount : Integer = IntRegister2;
      [*] = ;
      [*] = ;      var pMyNeighbours : Integer = ParserSelectByHandleByKey(pMyParser, 'Neighbours');
      [*] = ;
      [*] = ;      for i := 0 to nCount-1 do
      [*] = ;      begin
      [*] = ;         var pMyNeighbour : Integer = ParserSelectByHandleByIndex(pMyNeighbours, i);
      [*] = ;         var nUID : Integer = ParserGetIntValueByKeyByHandle(pMyNeighbour, 'UID');
      [*] = ;         var nGOHandle : Integer = GetGameObjectHandleByUniqueId(nUID);
      [*] = ;
      [*] = ;         if _unit_CheckAbility(nGOHandle, gc_ability_fire_immunity) = 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_battle_unit_iResist;
      [*] = ;            GameObjectExecuteStateByHandle(nGOHandle, 'GetProperty');
      [*] = ;            IntRegister0 := abil115;
      [*] = ;            //IntRegister1 := IntRegister1;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            MapExecuteState('bat.GetHit');
      [*] = ;            IntRegister0 := IntRegister2;
      [*] = ;            IntRegister1 := 3;
      [*] = ;            IntRegister2 := myUID;
      [*] = ;            FloatRegister0 := 0;
      [*] = ;            GameObjectExecuteStateByHandle(nGOHandle, 'TakeDamage');
      [*] = ;            if BoolRegister0 then
      [*] = ;               GameObjectExecuteStateByHandle(nGOHandle,'CheckDeathAnimation');
      [*] = ;            
      [*] = ;            //_fx_CreateFlyText_VVK(nGOHandle, gc_flytext_CategoryParam, gc_battle_unit_iCurLife, -hit);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var isDead : Boolean = false;
      [*] = ;   if hit < 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := Round(Abs(hit));
      [*] = ;      IntRegister1 := 3;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      FloatRegister0 := 0;
      [*] = ;      ExecuteState('TakeDamage');
      [*] = ;      isDead := BoolRegister0;
      [*] = ;
      [*] = ;      //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam,gc_battle_unit_iCurLife,hit);
      [*] = ;
      [*] = ;      if isDead then
      [*] = ;         ExecuteState('CheckDeathAnimation');
      [*] = ;      
      [*] = ;      // poison
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) and _obj_EnabledByFlag(gc_ObjectFlagBattleFX) then
      [*] = ;         _fx_GetOrCreateFXByID(myGOHandle, 'fxpoisonattack', 0, 0, 0, 0, Random, 5);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not isDead then
      [*] = ;   begin
      [*] = ;      if hit > 0 then
      [*] = ;      begin
      [*] = ;         curLife := curLife + hit;
      [*] = ;         SetGameObjectMyIntValueInd(gc_stack_unit_iCurLife, curLife);
      [*] = ;         //_fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam,gc_battle_unit_iCurLife,hit);
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_immobilized;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      if (curLife > 0) and (IntRegister1 = 0) then
      [*] = ;      begin
      [*] = ;         SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, true);
	   [*] = ;         SetGameObjectMyBoolValueInd(gc_stack_unit_bCanCast, true);
      [*] = ;         SetGameObjectMyBoolValueInd(gc_stack_unit_bCanShoot, true);
      [*] = ;         SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMelee, true);
      [*] = ;
      [*] = ;         IntRegister0 := gc_ability_cantmove;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         if IntRegister1 = 0 then
      [*] = ;         begin
      [*] = ;            // restore move points
      [*] = ;            IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;            ExecuteState('GetProperty');
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, IntRegister1);
      [*] = ;
      [*] = ;            IntRegister0 := gc_ability_march;
      [*] = ;            ExecuteState('CheckAbility');
      [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMarch, ( IntRegister1 > 0));
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, 0);
      [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMarch, false);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if curStamina = 0 then
      [*] = ;         begin
      [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, false);
	   [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bCanCast, false);
      [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bCanShoot, false);
      [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMelee, false);
      [*] = ;            SetGameObjectMyBoolValueInd(gc_stack_unit_bResting, true);
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, 0);
      [*] = ;         end;
      [*] = ;
      [*] = ;         // check for panic
      [*] = ;         if curMoral <= 0 then
      [*] = ;         begin
      [*] = ;            var fear : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iFear);
      [*] = ;
      [*] = ;            if (fear >= 50) or (fear >= _rand_Random(100)) then
      [*] = ;            begin
      [*] = ;               fear := fear - 10;
      [*] = ;               ExecuteState('Panic');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := 1;
      [*] = ;               ExecuteState('ChangeMoral');
      [*] = ;               fear := 0;
      [*] = ;               SetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bInPanic, false);
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iFear, fear);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (chInd >= 0) then
      [*] = ;      begin
      [*] = ;         var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;         if curStamina > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -curStamina div 2;
      [*] = ;            ExecuteState('ChangeStamina');
      [*] = ;         end;
      [*] = ;
      [*] = ;         var curMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;         if curMoral > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -curMoral div 2;
      [*] = ;            ExecuteState('ChangeMoral');
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := chInd;
      [*] = ;         ExecuteState('ChangeSide');
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, 0);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iActionType, 0);
      [*] = ;
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bActionTaken, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bDoubleShot, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bRoundAttack, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bCrush, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bFireBreath, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bPoisonBite, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bAstralStrike, false);
      [*] = ;      SetGameObjectMyBoolValueInd(gc_stack_unit_bLunge, false);
      [*] = ;
      [*] = ;      if curStamina = 0 then
      [*] = ;         ExecuteState('SetRestMode');
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iLastX, myGridX);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iLastY, myGridY);
      [*] = ;   SetBoolValueByIndex(gc_stack_unit_bTurnDone, false);
      [*] = ;   SetBoolValueByIndex(gc_stack_unit_bBlocked, false);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iAddHealPoints, 0);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iShotCount, 0);
      [*] = ;   SetBoolValueByIndex(gc_stack_unit_bRunBack, false);
      [*] = ;
      [*] = ;   ParserClearByHandle(ParserSelectByHandleByKey(pMyParser, 'AttackList'));
      [*] = ;   ParserClearByHandle(ParserSelectByHandleByKey(pMyParser, 'AttackAnimList'));
      [*] = ;
      [*] = ;   if (not gBoolRegister_BattleSimulate) and (not gBoolRegister_QuickBattle) then
      [*] = ;   begin
      [*] = ;      _unit_SetupStatsTextData(myGOHandle, myUID, oldLife, oldStamina, oldMoral);
      [*] = ;      _unit_CreateFlyTexts(myGOHandle, myUID);
      [*] = ;      _unit_ModifyVisualParams(myGOHandle, myUID);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var timer : Integer = GetIntValueByIndex(gc_stack_unit_iTransformTimer);
      [*] = ;   timer := timer-1;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTransformTimer, timer);
      [*] = ;   if timer = 0 then
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iCurLife, 0);
      [*] = ;      IntRegister0 := 0;
      [*] = ;      ExecuteState('Death');
      [*] = ;      ExecuteState('CheckDeathAnimation');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

