section.begin
   Name = SetupPlayerFlag
   Description : struct.begin
      [*] = ;IntRegister0 - player handle
   struct.end
   Code : struct.begin
      [*] = ;var plHandle : Integer = IntRegister0;
      [*] = ;var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\SETUPPLAYERFLAG';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;_gv_traceState(_log_name+'['+plName+']',_log_trace);
      [*] = ;
      [*] = ;var dummyHandle : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;const cPlName = 'PlProvinceFlags';
      [*] = ;const cPlRace = 'misc';
      [*] = ;const cFlagMediumBaseName = 'flag_medium';
      [*] = ;const cClearDist = 1.5;
      [*] = ;
      [*] = ;procedure SetupFlagMaterial(var goFlag : Integer; sign, color1, color2 : Integer);
      [*] = ;begin
      [*] = ;   var cr, cg, cb : Float;
      [*] = ;   _gui_GetHerbHDRColorByIndex(color2, cr, cg, cb);
      [*] = ;   var behHnd : Integer = EffectCreate(goFlag, 'TXSecMaterialEffect', true, false);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'Multitexture', False);
      [*] = ;   SetBehaviourStringProperty(behHnd, 'LibMaterialName', 'flag_medium_herb_'+IntToStr(sign));
      [*] = ;   SetBehaviourVectorProperty(behHnd, 'Emission', cr, cg, cb, 1);
      [*] = ;   SetBehaviourBoolProperty(behHnd, 'UseDiffuse', False);
      [*] = ;   SetGameObjectMaterialNameByHandle(goFlag, 'flag_medium_color_'+IntToStr(color1));
      [*] = ;end;
      [*] = ;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var isNeutral : Boolean = _misc_IsProvinceNeutral(pProvince);
      [*] = ;var goFlag : Integer = 0;
      [*] = ;
      [*] = ;//Setup province flag objects
      [*] = ;var plProvFlagHandle : Integer = GetPlayerHandleByName(cPlName);
      [*] = ;if plProvFlagHandle = 0 then
      [*] = ;   CreatePlayer(cPlName, cPlRace, 'cmNone')
      [*] = ;else
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(cPlName);
      [*] = ;   if (plHandle<>0) or (isNeutral) then
      [*] = ;   begin
      [*] = ;      var j : Integer;
      [*] = ;      var goHandle : Integer;
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         goHandle := GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         if VectorDistance(GetGameObjectPositionXByHandle(dummyHandle), 0, GetGameObjectPositionZByHandle(dummyHandle), GetGameObjectPositionXByHandle(goHandle), 0, GetGameObjectPositionZByHandle(goHandle)) < cClearDist then
      [*] = ;         begin
      [*] = ;            if gc_RecycleProvinceFlags then
      [*] = ;               goFlag := goHandle
      [*] = ;            else
      [*] = ;               GameObjectDestroyByHandle(goHandle);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (plHandle<>0) and _obj_CreationStateEnabled('ProvinceFlags') then
      [*] = ;begin
      [*] = ;   var flagScale : Float = 0.315;
      [*] = ;   var fPosX, fPosY, fPosZ : Float;
      [*] = ;   fPosX := GetGameObjectPositionXByHandle(dummyHandle);
      [*] = ;   fPosY := GetGameObjectPositionYByHandle(dummyHandle);
      [*] = ;   fPosZ := GetGameObjectPositionZByHandle(dummyHandle);
      [*] = ;
      [*] = ;   var castle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;   var yOff : Float;
      [*] = ;   if (castle) then
      [*] = ;   yOff := -0.5
      [*] = ;   else
      [*] = ;   yOff := -1.15;
      [*] = ;
      [*] = ;   //var goFlag : Integer = CreatePlayerGameObjectHandle(cPlName, cPlRace, cFlagMediumBaseName, fPosX, fPosY, fPosZ);
      [*] = ;   if (goFlag = 0) then
      [*] = ;   begin
      [*] = ;      goFlag := CreatePlayerGameObjectHandle(cPlName, cPlRace, cFlagMediumBaseName, fPosX, fPosY, fPosZ);
      [*] = ;      
      [*] = ;      SetGameObjectPositionByHandle(goFlag, fPosX, fPosY + yOff, fPosZ);
      [*] = ;      SetGameObjectScaleByHandle(goFlag, GetGameObjectScaleXByHandle(goFlag) * flagScale, GetGameObjectScaleYByHandle(goFlag) * flagScale, GetGameObjectScaleZByHandle(goFlag) * flagScale);
      [*] = ;      GameObjectRollByHandle(goFlag, -90);
      [*] = ;   end
      [*] = ;   else
      [*] = ;      SetGameObjectVisibleByHandle(goFlag, True);
      [*] = ;
      [*] = ;   if (plHandle<>0) then
      [*] = ;   begin
      [*] = ;      var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;      if SameText(cMode, 'cmPlayer') then
      [*] = ;      begin
      [*] = ;         var sign : Integer;
      [*] = ;         var color1 : Integer;
      [*] = ;         var color2 : Integer;
      [*] = ;
      [*] = ;         case gGame.gameType of
      [*] = ;            gc_GameTypeLanShard : begin
      [*] = ;               sign := gLanShardGame.arrLanPlayers[plIndex].profile.sign;
      [*] = ;               color1 := gLanShardGame.arrLanPlayers[plIndex].profile.color1;
      [*] = ;               color2 := gLanShardGame.arrLanPlayers[plIndex].profile.color2;
      [*] = ;            end;
      [*] = ;            gc_GameTypeHotseat : begin
      [*] = ;               sign := gArrHotseatProfiles[plIndex].sign;
      [*] = ;               color1 := gArrHotseatProfiles[plIndex].color1;
      [*] = ;               color2 := gArrHotseatProfiles[plIndex].color2;
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               sign := gProfile.sign;
      [*] = ;               color1 := gProfile.color1;
      [*] = ;               color2 := gProfile.color2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         SetupFlagMaterial(goFlag, sign, color1, color2);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var profile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;         if profile > 0 then
      [*] = ;         begin
      [*] = ;            var pPlayer : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;            var sign : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Herb');
      [*] = ;            var color1 : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Color1');
      [*] = ;            var color2 : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Color2');
      [*] = ;
      [*] = ;            SetupFlagMaterial(goFlag, sign, color1, color2);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            // local lord
      [*] = ;            var lordInd : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;            SetGameObjectMaterialNameByHandle(goFlag, 'flag_medium_color_' + IntToStr(lordInd-1));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (goFlag <> 0) then
      [*] = ;   SetGameObjectVisibleByHandle(goFlag, False);
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateMapHexGrid := True;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

