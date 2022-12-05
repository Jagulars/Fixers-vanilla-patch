section.begin
   Name = ApplyAllVisualParams
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;_unit_CreateAllFlyTexts(myPlHandle, myUID);
      [*] = ;_unit_ModifyAllVisualParams(myPlHandle, myUID);
      [*] = ;            
      [*] = ;_unit_CreateAllFlyTexts(enPlHandle, myUID);
      [*] = ;_unit_ModifyAllVisualParams(enPlHandle, myUID);
      [*] = ;
      [*] = ;_fx_StartFlyText_VVK(0);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
