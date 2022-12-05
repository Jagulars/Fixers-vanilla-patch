section.begin
   Name = Attack
   Description : struct.begin
      [*] = ;BoolRegister0 - is send parser for lan battle
   struct.end
   Code : struct.begin
      [*] = ;var sendParser : Boolean = BoolRegister0;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var autoBattle : Boolean = GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle);
      [*] = ;var myCustomName : String = GetGameObjectMyCustomName();
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\ATTACK';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;if not GetGameObjectMyPlayableObject then
      [*] = ;begin
      [*] = ;   ErrorLog('Unplayable unit trying to attack');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var tUID : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;//var tCustomName : String = GetGameObjectCustomNameByHandle(tGOHandle);
      [*] = ;var tCurStamina : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;var tResting : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bResting);
      [*] = ;//var tStealthMode : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;
      [*] = ;var dist : Integer = _misc_GetHexDist(GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX), GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY), GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX), GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY));
      [*] = ;var attGOHandle : Integer = 0;
      [*] = ;var defGOHandle : Integer = 0;
      [*] = ;var runBack : Boolean = false;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1, attBonus : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+myCustomName+',UID:'+IntToStr(tUID)+']',_log_trace);
      [*] = ;//if not tStealthMode then
      [*] = ;//begin
      [*] = ;   GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;   IntRegister0 := tUID;
      [*] = ;   IntRegister1 := GetGameObjectMyIntValueInd(gc_stack_unit_iLastX);
      [*] = ;   IntRegister2 := GetGameObjectMyIntValueInd(gc_stack_unit_iLastY);
      [*] = ;   ExecuteState('GetAttackBonus'); //charge bonus
      [*] = ;   attBonus := IntRegister0;
      [*] = ;
	   [*] = ;
      [*] = ;   if (_unit_CheckAbility(tGOHandle, gc_ability_first_strike) > 0) and (_unit_CheckAbility(myGOHandle, gc_ability_first_strike) = 0) and (_unit_CheckAbility(myGOHandle, gc_ability_cunning) = 0) and
      [*] = ;      (_unit_CheckAbility(tGOHandle, gc_ability_does_not_fight) = 0) and (not tResting) and (tCurStamina > 0) and (dist <= 1) then
      [*] = ;   begin	//target strikes first
      [*] = ;      attGOHandle := tGOHandle;
      [*] = ;      defGOHandle := myGOHandle;
      [*] = ;
      [*] = ;      gBoolRegister_BattleIsAttackerAction := false;
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iTargetUID, myUID);
      [*] = ;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      GameObjectExecuteStateByHandle(tGOHandle, 'DoAttack');
      [*] = ;      runBack := BoolRegister1;
      [*] = ;      _unit_SetupFlyText(tGOHandle, GetGameObjectUniqueIdByHandle(tGOHandle), gc_flytext_CategoryAbility, gc_ability_first_strike, -1);
      [*] = ;   end
      [*] = ;   else //attacker strikes first
      [*] = ;   begin
      [*] = ;      attGOHandle := myGOHandle;
      [*] = ;      defGOHandle := tGOHandle;
      [*] = ;      gBoolRegister_BattleIsAttackerAction := true;
      [*] = ;
      [*] = ;      IntRegister0 := attBonus;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      ExecuteState('DoAttack');
      [*] = ;      runBack := BoolRegister1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var animCount : Integer = 0;
      [*] = ;   if not runBack then
      [*] = ;      animCount := 1;
      [*] = ;
      [*] = ;   var defCurHP : Integer = GetGameObjectIntValueIndByHandle(defGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   var defCurStamina : Integer = GetGameObjectIntValueIndByHandle(defGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;   var defResting : Boolean = GetGameObjectBoolValueIndByHandle(defGOHandle, gc_stack_unit_bResting);
      [*] = ;   var defParry : Boolean = GetGameObjectBoolValueIndByHandle(defGOHandle, gc_stack_unit_bParry);
      [*] = ;   var defStatic : Boolean = GetGameObjectBoolValueIndByHandle(defGOHandle, gc_stack_unit_bStatic);
      [*] = ;
      [*] = ;   var magic_strike : Integer = _unit_CheckAbility(attGOHandle, gc_ability_magic_strike);
	   [*] = ;   var attAgility : Boolean = (_unit_CheckAbility(attGOHandle, gc_ability_cunning) > 0);
	   [*] = ;
      [*] = ;   // defender can fight back
      [*] = ;   if (not defStatic) and (defCurHP > 0) and (_unit_CheckAbility(defGOHandle, gc_ability_does_not_fight) = 0) and (dist <= 1) then
      [*] = ;   begin 
      [*] = ;      if (not gBoolRegister_BattleIsAttackerAction) or ((defCurStamina > 0) and (not attAgility) and (not defResting)) then
      [*] = ;      begin //counter attack
      [*] = ;         var uid : Integer = GetGameObjectUniqueIdByHandle(attGOHandle);
      [*] = ;         SetGameObjectIntValueIndByHandle(defGOHandle, gc_stack_unit_iTargetUID, uid);
      [*] = ;         gBoolRegister_BattleIsAttackerAction := not gBoolRegister_BattleIsAttackerAction;
      [*] = ;
      [*] = ;         IntRegister0 := 0;
      [*] = ;         BoolRegister0 := (attGOHandle <> myGOHandle);
      [*] = ;         GameObjectExecuteStateByHandle(defGOHandle, 'DoAttack');
      [*] = ;
      [*] = ;         animCount := animCount + 1;
      [*] = ;      end;
      [*] = ;      {else // wounded animation, when def can't counterattack
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         var uid : Integer = GetGameObjectUniqueIdByHandle(attGOHandle);
      [*] = ;         SetGameObjectIntValueIndByHandle(defGOHandle, gc_stack_unit_iTargetUID, uid);
      [*] = ;         StringRegister0 := 'wounded';
      [*] = ;         IntRegister0 := myUID;
      [*] = ;         GameObjectExecuteStateByHandle(defGOHandle, 'SetupAnimation');
      [*] = ;      end;}
      [*] = ;
      [*] = ;      if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) and (attGOHandle = myGOHandle) then
      [*] = ;      begin
      [*] = ;         var uid : Integer = GetGameObjectUniqueIdByHandle(attGOHandle);
      [*] = ;         SetGameObjectIntValueIndByHandle(defGOHandle, gc_stack_unit_iTargetUID, uid);
      [*] = ;
      [*] = ;         var pDefParser : Integer = ParserSelectGameObject(defGOHandle);
      [*] = ;         var berserkUID : Integer = ParserGetIntValueByKeyByHandle(pDefParser, 'BerserkUID');
      [*] = ;
      [*] = ;         var sf, ef : Integer;
      [*] = ;         if defParry and (magic_strike = 0) and (tCurStamina > 0) and GetGameObjectFrameAnimationDataByHandle(defGOHandle, 'parry', sf, ef) then
      [*] = ;         begin
      [*] = ;            if (not tResting) and (not attAgility) then
      [*] = ;               StringRegister0 := 'parryattack'
      [*] = ;            else
      [*] = ;               StringRegister0 := 'parry';
      [*] = ;            IntRegister0 := myUID;
      [*] = ;            GameObjectExecuteStateByHandle(defGOHandle, 'SetupAnimation');
      [*] = ;
      [*] = ;            _unit_SetupFlyText(defGOHandle, GetGameObjectUniqueIdByHandle(attGOHandle), gc_flytext_CategoryAbility, gc_ability_parry, 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var anim : String = GetGameObjectFrameAnimationNameByHandle(defGOHandle);
      [*] = ;            if (anim='idle') then
      [*] = ;            begin
      [*] = ;               var CAttCount : Integer = GetGameObjectIntValueIndByHandle(defGOHandle, gc_stack_unit_iCAttackCount);
      [*] = ;               var runBack : Boolean = GetGameObjectBoolValueIndByHandle(defGOHandle, gc_stack_unit_bRunBack);
      [*] = ;               if (CAttCount=0) and (not runBack) then
      [*] = ;               begin
      [*] = ;                  var animName : String = '';
      [*] = ;                  if berserkUID = 0 then
      [*] = ;                  begin
      [*] = ;                     if (not tResting) and (not attAgility) and (tCurStamina > 0) then
      [*] = ;                        animName := 'woundattack'
      [*] = ;                     else
      [*] = ;                        animName := 'wound';
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if (not tResting) and (not attAgility) and (tCurStamina > 0) then
      [*] = ;                        animName := 'attack'
      [*] = ;                     else
      [*] = ;                        animName := '';
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if animName <> '' then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := myUID;
      [*] = ;                     StringRegister0 := animName;
      [*] = ;                     GameObjectExecuteStateByHandle(defGOHandle, 'SetupAnimation');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      _gv_SetBattleLock(animCount,_log_name);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sendParser then
      [*] = ;      _inet_CreateOrderParser(myUID, GetGameObjectMyIntValueInd(gc_stack_unit_iLastX), GetGameObjectMyIntValueInd(gc_stack_unit_iLastY), gc_inet_actiontype_attack, 0, 0, tUID, 0, lanOrderRandKey0, lanOrderRandKey1,'Attack');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(animcount)+']',$1000000 or _log_trace);
   struct.end
section.end

