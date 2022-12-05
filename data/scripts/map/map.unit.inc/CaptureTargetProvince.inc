section.begin
   Name = CaptureTargetProvince
   Description : struct.begin
      [*] = ;BoolRegister0 - is diplomatic capture
   struct.end
   Code : struct.begin
      [*] = ;var diplCapture : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\CAPTURETARGETPROVINCE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var dummyUID : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;var dummyGOHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;IntRegister0 := dummyUID;
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;var pProvince : Integer = IntRegister1;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;var x, z : Float;
      [*] = ;_misc_GetProvinceHeroCoords(pProvince, x, z);
      [*] = ;SetGameObjectMyPosition(x, 0, z);
      [*] = ;GameObjectMyDoRayCastTerrain;
      [*] = ;SetIntValueByIndex(gc_map_GOStack_MapUnit_iUpdate, 1);
      [*] = ;
      [*] = ;ExecuteState('CheckVisible');
      [*] = ;
      [*] = ;IntRegister0 := myPlHandle;
      [*] = ;BoolRegister0 := diplCapture;
      [*] = ;GameObjectExecuteStateByHandle(dummyGOHandle, 'CaptureProvince');
      [*] = ;var endGame : Boolean = BoolRegister1;
      [*] = ;
      [*] = ;if not endGame then
      [*] = ;begin
      [*] = ;   var cMode : String = GetPlayerControlModeByHandle(provPlHandle);
      [*] = ;   //if (GetPlayerIndexByHandle(provPlHandle) = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   if SameText(cMode, 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;         gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_playerLostProvince)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if _plr_IsInGame(provPlHandle) then
      [*] = ;         begin
      [*] = ;            StringRegister0 := IntToStr(gc_gui_query_playerLostProvince);
      [*] = ;            BoolRegister0 := true;
      [*] = ;            PlayerExecuteStateByHandle(provPlHandle, 'CheckRequestQuery');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

