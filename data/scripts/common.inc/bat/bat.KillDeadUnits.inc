section.begin
   Name = bat.KillDeadUnits
   Description : struct.begin
      [*] = ;Make sure that all units with zero curlife are dead
      [*] = ;IntRegister0 - player handle
   struct.end
   Code : struct.begin
      [*] = ;{var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure ProcessPlayer(ph : Integer);
      [*] = ;begin
      [*] = ;   var i,oh : Integer;
      [*] = ;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(ph)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      oh := GetGameObjectHandleByIndex(i,ph);
      [*] = ;
      [*] = ;      if GetGameObjectPlayableObjectByHandle(oh) then
      [*] = ;         GameObjectExecuteStateByHandle(oh, 'MakeSureUnitIsDead');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var ph : Integer = IntRegister0;
      [*] = ;
      [*] = ;if _gv_GetBattleLock() = 0 then
      [*] = ;begin
      [*] = ;   ProcessPlayer(ph);
      [*] = ;   PlayerExecuteStateByHandle(ph, 'GetEnemyPlHandle');
      [*] = ;   ProcessPlayer( IntRegister0 );
      [*] = ;end;}
   struct.end
section.end
