section.begin
   Name = EvaluateOrderParser
   Code : struct.begin
      [*] = ;var pOrder : Integer = IntRegister0;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\EVALUATEORDERPARSER';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if (pOrder<>0) then
      [*] = ;begin
      [*] = ;   //var myUID : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'myUID');
      [*] = ;   var tx : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'targetX');
      [*] = ;   var ty : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'targetY');
      [*] = ;   var actType : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'actionType');
      [*] = ;   var spellID : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'spellID');
      [*] = ;   var abilityID : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'abilityID');
      [*] = ;   //var tUID : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'targetUID');
      [*] = ;   //var tPlInd : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'enPlayer');
      [*] = ;   //var tGOInd : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'enGOIndex');
      [*] = ;   var stackActionType : Integer = ParserGetIntValueByKeyByHandle(pOrder, 'stackActionType');
      [*] = ;   var pDoll : Integer = ParserSelectByHandleByKey(pOrder, 'Doll');
      [*] = ;   var unit_handle, target_handle : Integer;
      [*] = ;   //var enPlHandle : Integer = GetPlayerHandleByIndex(tPlInd);
      [*] = ;   //var enGOHandle : Integer = GetGameObjectHandleByIndex(tGOInd, enPlHandle);
      [*] = ;   var tUID,myUID,randKey0,randKey1 : Integer;
      [*] = ;   //var bDelayedOrder : Boolean = (actType<>gc_inet_actiontype_firedamage) and (GetGameObjectMyTrackPointMovementMode()<>'mmNone');
      [*] = ;   var bDelayedOrder : Boolean = _gv_GetBattleLock() > 0;
      [*] = ;   
      [*] = ;   gBoolRegister_InetLanIsEvaluateOrder := True;
      [*] = ;
      [*] = ;   myUID := _lan_ConvertToBattleUID(ParserGetIntValueByKeyByHandle(pOrder, 'src_index'));
      [*] = ;   tUID := _lan_ConvertToBattleUID(ParserGetIntValueByKeyByHandle(pOrder, 'target_index'));
      [*] = ;   unit_handle := GetGameObjectHandleByUniqueId(myUID);
      [*] = ;   target_handle := GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;   randKey0 := ParserGetIntValueByKeyByHandle(pOrder, 'randKey0');
      [*] = ;   randKey1 := ParserGetIntValueByKeyByHandle(pOrder, 'randKey1');
      [*] = ;   if (not bDelayedOrder) then
      [*] = ;   begin
      [*] = ;      if _log then _Log_lan('EvaluateOrderParser : not bDelayedOrder : baseName = '+GetGameObjectMyBaseName());
      [*] = ;      ExecuteState('Select');
      [*] = ;      gIntRegister_InetLanActionSyncEnum := gIntRegister_InetLanActionSyncEnum+1;
      [*] = ;   end;
      [*] = ;   _log_map('EvaluateOrderParser, received randKey0: '+IntToStr(randKey0)+' received randKey1: '+IntToStr(randKey1));
      [*] = ;   var randKey1my, randKey0my : Integer;
      [*] = ;   GetRandomExtKey64(randKey0my, randKey1my);
      [*] = ;   Log('EvaluateOrderParser: my randKey0 '+IntToStr(randKey0my)+' my randKey1 '+IntToStr(randKey1my));
      [*] = ;   //SetRandomExtKey64(randKey0, randKey1);
      [*] = ;
      [*] = ;   if (bDelayedOrder) then
      [*] = ;   begin
      [*] = ;      if _log then _Log_lan('EvaluateOrderParser : bDelayedOrder : baseName = '+GetGameObjectMyBaseName);
      [*] = ;      var pMyParser : Integer = ParserSelectGameObject(GetGameObjectMyHandle());
      [*] = ;      var pLanUnitSyncs : Integer = ParserSelectByHandleByKey(pMyParser, 'LanUnitSyncs');
      [*] = ;      if (pLanUnitSyncs<>0) and (ParserGetParent(pOrder)<>pLanUnitSyncs) then
      [*] = ;      begin
      [*] = ;         var pLanUnitSync : Integer = ParserAddChildByIndex(pLanUnitSyncs, '*');
      [*] = ;         ParserCopyFromByHandle(pOrder);
      [*] = ;         ParserFreeByHandle(pOrder);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      SetIntValueByIndex(gc_stack_unit_iActionType, stackActionType);
      [*] = ;      case actType of
      [*] = ;         gc_inet_actiontype_attack : begin
      [*] = ;            if tUID > 0 then
      [*] = ;            begin
      [*] = ;               var tmpX : Integer = GetIntValueByIndex(gc_stack_unit_iLastX);
      [*] = ;               var tmpY : Integer = GetIntValueByIndex(gc_stack_unit_iLastY);
      [*] = ;
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iLastX, tx);
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iLastY, ty);
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iTargetUID, tUID);
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('Attack');
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iLastX, tmpX);
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iLastY, tmpY);
      [*] = ;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('CheckAttackAnimation');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_fireattack : begin
      [*] = ;            if tUID > 0 then
      [*] = ;            begin
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iTargetUID, tUID);
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('FireAttack');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_firedamage : begin
      [*] = ;            IntRegister0 := myUID;
      [*] = ;            IntRegister1 := tUID;
      [*] = ;            MapExecuteState('bat.DoProjectileDamage');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_spell : begin
      [*] = ;            var ind : Integer = gc_battle_GridSize * ty + tx;
      [*] = ;            var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;
      [*] = ;            if tUID > 0 then
      [*] = ;            begin
      [*] = ;               var pSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, spellID);
      [*] = ;               var sacrifice : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Sacrifice');
      [*] = ;               var pSpellAbilities : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;               var pSpellAbility0 : Integer = ParserSelectByHandleByIndex(pSpellAbilities, 0);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellAbility0, 'AbilityID');
      [*] = ;
      [*] = ;               gIntRegister_TeleportUID := 0;
      [*] = ;               gIntRegister_SacrificeUID := 0;
      [*] = ;
      [*] = ;               if abilID = 89 then
      [*] = ;                  gIntRegister_TeleportUID := tUID
      [*] = ;               else
      [*] = ;                  if sacrifice then
      [*] = ;                     gIntRegister_SacrificeUID := tUID;
      [*] = ;            end;
      [*] = ;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            IntRegister1 := pHexCell;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('CastSpell');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_heal : begin
      [*] = ;            IntRegister0 := GetGameObjectHandleByUniqueId(tUID);
      [*] = ;            BoolRegister0 := false;
      [*] = ;            ExecuteState('HealUnit');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_rest : begin
      [*] = ;            ExecuteState('SetRestMode');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_changeweapon : begin
      [*] = ;            var mapHeroUID : Integer = GetIntValueByIndex(gc_stack_unit_iHeroUID);
      [*] = ;               
      [*] = ;            if mapHeroUID > 0 then
      [*] = ;            begin
      [*] = ;               var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(mapHeroUID);
      [*] = ;               var mapHeroParser : Integer = ParserSelectGameObject(mapHeroHandle);
      [*] = ;               var pHeroDoll : Integer = ParserSelectByHandleByKey(mapHeroParser, 'Doll');
      [*] = ;               ParserClearByHandle(pHeroDoll);
      [*] = ;               ParserCopyFromByHandle(pDoll);
      [*] = ;               ExecuteState('AfterSwitchWeapon');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_activateability : begin
      [*] = ;            IntRegister0 := abilityID;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            ExecuteState('ActivateAbility');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_move : begin
      [*] = ;            var ind : Integer = gc_battle_GridSize * ty + tx;
      [*] = ;            var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;
      [*] = ;            IntRegister0 := tnHandle;
      [*] = ;            IntRegister1 := tUID;
      [*] = ;            IntRegister2 := stackActionType;
      [*] = ;            ExecuteState('Position');
      [*] = ;            if (not BoolRegister0 ) and _log then ErrorLogI(_log_name+' Warning: unit positioning to '+IntToStr(tx)+','+IntToStr(ty)+'failed');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_teleport : begin
      [*] = ;            IntRegister0 := tx;
      [*] = ;            IntRegister1 := ty;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            ExecuteState('Replace');
      [*] = ;         end;
      [*] = ;         gc_inet_actiontype_turn : begin
      [*] = ;            IntRegister0 := tx;
      [*] = ;            ExecuteState('Turn');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (not bDelayedOrder) then
      [*] = ;   begin
      [*] = ;      ParserFreeByHandle(pOrder);
      [*] = ;      pOrder := 0;
      [*] = ;      _inet_ExecuteLanSyncParser();
      [*] = ;      _inet_ExecuteUnitLanSyncParser(GetGameObjectMyHandle());
      [*] = ;   end;
      [*] = ;
      [*] = ;   gBoolRegister_InetLanIsEvaluateOrder := False;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

