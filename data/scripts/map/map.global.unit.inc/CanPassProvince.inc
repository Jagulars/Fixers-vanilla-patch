section.begin
   Name = CanPassProvince
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
      [*] = ;OUT: BoolRegister0 - can player pass province
      [*] = ;OUT: BoolRegister1 - true if province is neutral without guards
      [*] = ;OUT: IntRegister1 - neutral province player index
   struct.end
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CANPASSPROVINCE';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;if gBoolRegister_MapResolveConflicts then _log_trace := $40001; // only log during resolve conflicts to avoid deluge.
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;var canPass : Boolean = false;
      [*] = ;var emptyNeutral : Boolean = false;
      [*] = ;var plIndex : Integer = -1;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(dummyUID)+','+provPlName+']',_log_trace);
      [*] = ;
      [*] = ;if dummyHandle <> 0 then
      [*] = ;begin
      [*] = ;   if SameText(myPlName, provPlName) then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'IsUnderSiege');
      [*] = ;      canPass := not BoolRegister0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if _misc_IsProvinceNeutral(pProvince) then
      [*] = ;      begin
      [*] = ;         var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;         var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;         var count : Integer = ParserGetCountByHandle(pGuardUnits);
      [*] = ;         //var lastPlayer : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;
      [*] = ;         if count > 0 then
      [*] = ;            canPass := false
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            canPass := true;
      [*] = ;            emptyNeutral := true;
      [*] = ;            var i, j : Integer;
      [*] = ;
      [*] = ;            if gBoolRegister_MapResolveConflicts then
      [*] = ;            begin
      [*] = ;               var pConflict : Integer = _misc_GetCurrentConflict();
      [*] = ;               if (ParserGetIntValueByKeyByHandle(pConflict, 'ProvUID') = dummyUID) then
      [*] = ;                  canPass := false;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if canPass then
      [*] = ;            for [MAIN]i := 0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               if i <> myPlIndex then
      [*] = ;               begin
      [*] = ;                  var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;                  //var treaty : Integer = gArrDiplomacy[myPlIndex][i].treaty;
      [*] = ;
      [*] = ;                  //if treaty = 1 then
      [*] = ;                  for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;                     if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;                     begin
      [*] = ;                        var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;                        if curUID = dummyUID then
      [*] = ;                        begin
      [*] = ;                           canPass := false;
      [*] = ;                           plIndex := i;
      [*] = ;                           break(MAIN);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         canPass := false;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(canPass)+','+BoolToStr(emptyNeutral)+','+IntToStr(plIndex)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;BoolRegister0 := canPass;
      [*] = ;BoolRegister1 := emptyNeutral;
      [*] = ;IntRegister1 := plIndex;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

