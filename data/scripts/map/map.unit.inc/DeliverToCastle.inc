section.begin
   Name = DeliverToCastle
   Description[*] = ;IntRegister0 - distance to castle
   UsedFileName =
   Code : struct.begin
      [*] = ;var dist : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myCustomName : String = GetGameObjectCustomNameByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;ExecuteState('CancelOrders');
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var x, y : Float;
      [*] = ;_misc_GetProvinceHeroCoords(pCastle, x, y);
      [*] = ;
      [*] = ;SetBoolValueByIndex(gc_map_GOStack_MapUnit_bIsDead, true);
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iCastleDist, dist+1);
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iBeforeTargetUID, GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID)); // we'll be using this to know which province it was in before delivery
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID, dummyUID);
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iTargetUID, dummyUID);
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iReachUID, dummyUID);
      [*] = ;SetGameObjectMyVisible(false);
      [*] = ;SetGameObjectMyPosition(x, 0, y);
      [*] = ;GameObjectMyDoRayCastTerrain;
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iUpdate, 1);
      [*] = ;if (GetGameObjectUniqueIdByHandle(myGOHandle)=gIntRegister_MapSelectedUID) then
      [*] = ;   gIntRegister_MapSelectedUID := 0;
      [*] = ;
      [*] = ;_map_RefreshProvinceHUD(DummyUID);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

