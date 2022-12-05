section.begin
   Name = AddRandomBonus
   Description : struct.begin
      [*] = ;IntRegister0 - level
      [*] = ;OUT: IntRegister1 - bonus index; 0 - leader, 1 - health, 2 - magic, 3 - life, -1 - should not add any
   struct.end
   Code : struct.begin
      [*] = ;var level : Integer = IntRegister0;
      [*] = ;var new_bonus : Integer = -1;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ADDRANDOMBONUS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name+'[L:'+IntToStr(level)+']',_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;if level = 10 then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name+'[10th Level]',$1000000 or _log_trace);
      [*] = ;   IntRegister1 := new_bonus;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;// add property bonus
      [*] = ;StringRegister0 := 'Health';
      [*] = ;ExecuteState('GetBonusLimit');
      [*] = ;var HealthLimit : Integer = IntRegister0;
      [*] = ;
      [*] = ;StringRegister0 := 'Magic';
      [*] = ;ExecuteState('GetBonusLimit');
      [*] = ;var magicLimit : Integer = IntRegister0;
      [*] = ;
      [*] = ;StringRegister0 := 'Leader';
      [*] = ;ExecuteState('GetBonusLimit');
      [*] = ;var leaderLimit : Integer = IntRegister0;
      [*] = ;
      [*] = ;var leader : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLeader);
      [*] = ;var health : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth);
      [*] = ;var magic : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMagic);
      [*] = ;var life : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLife);
      [*] = ;var heroClass : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;var addLeader : Integer = 0;
      [*] = ;var addHealth : Integer = 0;
      [*] = ;var addMagic : Integer = 0;
      [*] = ;var addLife : Integer = 0;
      [*] = ;
      [*] = ;if level > 20 then
      [*] = ;   addLife := 1
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (level >= 3) and (leader = 0) and (heroClass > 1) then
      [*] = ;      addLeader := 1
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var leftLeader : Integer = leaderLimit - leader;
      [*] = ;      var leftHealth : Integer = healthLimit - health;
      [*] = ;      var leftMagic : Integer = magicLimit - magic;
      [*] = ;
      [*] = ;      var rand : Float = RandomExt * (leftHealth + leftMagic + leftLeader);
      [*] = ;
      [*] = ;      if rand < leftHealth then
      [*] = ;         addhealth := 1
      [*] = ;      else
      [*] = ;         if rand < leftHealth + leftMagic then
      [*] = ;            addMagic := 1
      [*] = ;         else
      [*] = ;            addLeader := 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;leader := leader + addLeader;
      [*] = ;health := health + addHealth;
      [*] = ;magic := magic + addMagic;
      [*] = ;life := life + addLife;
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLeader, leader);
      [*] = ;SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth, health);
      [*] = ;SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMagic, magic);
      [*] = ;SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLife, life);
      [*] = ;
      [*] = ;if (addHealth > 0) or (addLife > 0) then
      [*] = ;begin
      [*] = ;   var pUnitLevels : Integer = gPrototypeData.unitLevels.handle;
      [*] = ;   var pHealthLevels : Integer = ParserSelectByHandleByKey(pUnitLevels, 'Health');
      [*] = ;
      [*] = ;   var lifeAdd : Integer = 0;
      [*] = ;   var stamAdd : Integer = 0;
      [*] = ;   var moralAdd : Integer = 0;
      [*] = ;   if addHealth > 0 then
      [*] = ;   begin
      [*] = ;      var pLevel : Integer = ParserSelectByHandleByIndex(pHealthLevels, health-1);
      [*] = ;      lifeAdd := ParserGetIntValueByKeyByHandle(pLevel, 'Life');
      [*] = ;      stamAdd := ParserGetIntValueByKeyByHandle(pLevel, 'Stamina');
      [*] = ;      moralAdd := ParserGetIntValueByKeyByHandle(pLevel, 'Moral');
      [*] = ;   end;
      [*] = ;   if addLife > 0 then
      [*] = ;   begin
      [*] = ;      lifeAdd := lifeAdd + addLife;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   _unit_ModifyHeroAttributes(myGOHandle, lifeAdd, stamAdd, moralAdd);
      [*] = ;end;
      [*] = ;
      [*] = ;if addLeader > 0 then
      [*] = ; new_bonus := 0
      [*] = ;else
      [*] = ;begin
      [*] = ;   if addMagic > 0 then
      [*] = ;      new_bonus := 1
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if addHealth > 0 then
      [*] = ;         new_bonus := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if addLife > 0 then
      [*] = ;            new_bonus := 3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(new_bonus)+']',$1000000 or _log_trace);
      [*] = ;IntRegister1 := new_bonus;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
   struct.end
section.end

