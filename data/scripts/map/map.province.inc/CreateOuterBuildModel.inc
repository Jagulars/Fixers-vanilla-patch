section.begin
   Name = CreateOuterBuildModel
   Description : struct.begin
      [*] = ;IntRegister0 - outer building ID
      [*] = ;IntRegister1 - slot index
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\CREATEOUTERBUILDMODEL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var buildID : Integer = IntRegister0;
      [*] = ;var slotInd : Integer = IntRegister1;
      [*] = ;var bFadeObjects : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[ProvUID: '+IntToStr(GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle))+', Build ID: '+IntToStr(buildID)+', Slot Index: '+IntToStr(slotInd)+']',_log_trace);
      [*] = ;
      [*] = ;if (buildID > 0) and (slotInd >= 0) and (slotInd <= 2) and (gProfile.provincescenery < gc_OuterBuildSceneryLimit) then
      [*] = ;begin
      [*] = ;   var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;   var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;   var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, slotInd);
      [*] = ;
      [*] = ;   var pOuterBuilding : Integer = ParserSelectByHandleByIndex(gPrototypeData.outerBuildings.handle, buildID);
      [*] = ;
      [*] = ;   var raceName : String = ParserGetValueByKeyByHandle(pOuterBuilding, 'RaceName');
      [*] = ;   var baseName : String = ParserGetValueByKeyByHandle(pOuterBuilding, 'BaseName');
      [*] = ;   var scale : Float = ParserGetFloatValueByKeyByHandle(pOuterBuilding, 'Scale');
      [*] = ;   var rotate : Float = ParserGetFloatValueByKeyByHandle(pOuterBuilding, 'Rotate');
      [*] = ;
      [*] = ;   if (scale=0) then
      [*] = ;      scale := 1;
      [*] = ;
      [*] = ;   var plName : String = ParserGetValueByKeyByHandle(pProvOuterBuilding, 'PatternPlayer');
      [*] = ;   var grName : String = ParserGetValueByKeyByHandle(pProvOuterBuilding, 'PatternGroup');
      [*] = ;   var posX : Float = ParserGetFloatValueByKeyByHandle(pProvOuterBuilding, 'X');
      [*] = ;   var posZ : Float = ParserGetFloatValueByKeyByHandle(pProvOuterBuilding, 'Y');
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;   var grHandle : Integer = GetPlayerGrHandleByHandle(plHandle, grName);
      [*] = ;   if (grHandle=0) then
      [*] = ;      grHandle := CreateGroupByPlHandle(plHandle, grName);
      [*] = ;
      [*] = ;   var fadeTime : Float = 0;
      [*] = ;   if bFadeObjects then
      [*] = ;      fadeTime := 1;
      [*] = ;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   FloatRegister0 := fadeTime;
      [*] = ;   ExecuteState('HideShowObjects');
      [*] = ;
      [*] = ;   var goHandle : Integer = CreatePlayerGameObjectHandle(plName, raceName, baseName, posX, 0, posZ);
      [*] = ;   SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*0.6*scale, GetGameObjectScaleYByHandle(goHandle)*0.6*scale, GetGameObjectScaleZByHandle(goHandle)*0.6*scale);
      [*] = ;   GameObjectRollByHandle(goHandle, rotate);
      [*] = ;   GroupAddGameObjectByHandle(grHandle, goHandle);
      [*] = ;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   FloatRegister0 := fadeTime;
      [*] = ;   ExecuteState('HideShowObjects');
      [*] = ;
      [*] = ;   GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

