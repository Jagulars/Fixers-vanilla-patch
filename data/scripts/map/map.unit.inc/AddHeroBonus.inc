section.begin
   Name = AddHeroBonus
   Description : struct.begin
      [*] = ;IntRegister0 - bonus type
      [*] = ;IntRegister1 - bonus value
   struct.end
   Code : struct.begin
      [*] = ;var bonusType : Integer = IntRegister0;
      [*] = ;var bonusValue : Integer = IntRegister1;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;var health : Integer = 0;
      [*] = ;            
      [*] = ;case bonusType of
      [*] = ;   0 : begin
      [*] = ;      var leader : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLeader);
      [*] = ;      SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLeader, leader + bonusValue);
      [*] = ;   end;
      [*] = ;   1 : begin
      [*] = ;      var magic : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMagic);
      [*] = ;      SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMagic, magic + bonusValue);
      [*] = ;   end;
      [*] = ;   2 : begin
      [*] = ;      health := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth);
      [*] = ;      health := health + bonusValue;
      [*] = ;      SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iHealth, health);
      [*] = ;   end;
      [*] = ;   3 : begin
      [*] = ;      var bonusLife : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLife);
      [*] = ;      SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLife, bonusLife + bonusValue);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// modify health attributes
      [*] = ;if ((bonusType = 2) or (bonusType = 3)) and (bonusValue > 0) then
      [*] = ;begin
      [*] = ;   var lifeAdd, stamAdd, moralAdd : Integer = 0;
      [*] = ;   
      [*] = ;   if (bonusType = 2) then
      [*] = ;   begin
      [*] = ;      var pUnitLevels : Integer = gPrototypeData.unitLevels.handle;
      [*] = ;      var pHealthLevels : Integer = ParserSelectByHandleByKey(pUnitLevels, 'Health');
      [*] = ;      var pLevel : Integer = ParserSelectByHandleByIndex(pHealthLevels, health-1);
      [*] = ;      lifeAdd := ParserGetIntValueByKeyByHandle(pLevel, 'Life');
      [*] = ;      stamAdd := ParserGetIntValueByKeyByHandle(pLevel, 'Stamina');
      [*] = ;      moralAdd := ParserGetIntValueByKeyByHandle(pLevel, 'Moral');
      [*] = ;   end;
      [*] = ;   if (bonusType = 3) then
      [*] = ;      lifeAdd := lifeAdd + bonusValue;
      [*] = ;      
      [*] = ;   _unit_ModifyHeroAttributes(myGOHandle, lifeAdd, stamAdd, moralAdd);
      [*] = ;end;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

