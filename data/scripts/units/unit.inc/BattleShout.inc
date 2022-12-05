section.begin
   Name = BattleShout
   Code : struct.begin
      [*] = ;if GetIntValueByIndex(gc_stack_unit_iCurStamina) >= 3 then
      [*] = ;begin
      [*] = ;   var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;   var i,mp_bonus : Integer;
      [*] = ;   var myGridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;   var myGridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;   var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;   GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;   mp_bonus := _unit_CheckAbility(myGOHandle, gc_ability_battle_cry);
      [*] = ;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   IntRegister0 := myGridX;
      [*] = ;   IntRegister1 := myGridY;
      [*] = ;   ExecuteState('FindNeighbour');
      [*] = ;
      [*] = ;   var pMyNeighbours : Integer = ParserSelectByHandleByKey(ParserSelectGameObject(myGOHandle), 'Neighbours');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pMyNeighbours)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pMyNeighbour : Integer = ParserSelectByHandleByIndex(pMyNeighbours, i);
      [*] = ;      var nUID : Integer = ParserGetIntValueByKeyByHandle(pMyNeighbour, 'UID');
      [*] = ;      var nGOHandle : Integer = GetGameObjectHandleByUniqueId(nUID);
      [*] = ;      var canAct : Boolean = GetGameObjectBoolValueIndByHandle(nGOHandle, gc_stack_unit_bCanAct);
      [*] = ;
      [*] = ;      if canAct and (_unit_CheckAbility(nGOHandle, gc_ability_immobilized) = 0) and (_unit_CheckAbility(nGOHandle, gc_ability_cantmove) = 0) then
      [*] = ;      begin
      [*] = ;         var movePoints : Integer = GetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iMovePoints);
      [*] = ;         SetGameObjectIntValueIndByHandle(nGOHandle, gc_stack_unit_iMovePoints, movePoints + mp_bonus);
      [*] = ;         _fx_CreateFlyText_VVK(nGOHandle, gc_flytext_CategoryParam, gc_battle_unit_iMovePoints, mp_bonus);
      [*] = ;      end;
      [*] = ;   end;
	  [*] = ;   IntRegister0 := -3;
	  [*] = ;   ExecuteState('ChangeStamina');
      [*] = ;   ExecuteState('ActionDone');
      [*] = ;   _inet_CreateOrderParser(GetGameObjectUniqueIdByHandle(myGOHandle), -1, -1, gc_inet_actiontype_activateability, 0, gc_ability_battle_cry, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'BattleShout');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

