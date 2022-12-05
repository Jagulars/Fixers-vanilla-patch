section.begin
   Name = DoBuildInnerBuilding
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;var _log_name : String = 'MISC\BUILD.INC\DOBUILDINNERBUILDING';
      [*] = ;var _log_trace : Integer = $800000;
      [*] = ;
      [*] = ;procedure RotateRelativePosition(goHandle : Integer; cPosX, cPosZ, angle : Float);
      [*] = ;begin
      [*] = ;   var posX, posY, posZ : Float;
      [*] = ;   posX := GetGameObjectPositionXByHandle(goHandle);
      [*] = ;   posY := GetGameObjectPositionYByHandle(goHandle);
      [*] = ;   posZ := GetGameObjectPositionZByHandle(goHandle);
      [*] = ;
      [*] = ;   var dirX : Float = posX-cPosX;
      [*] = ;   var dirY : Float = 0;
      [*] = ;   var dirZ : Float = posZ-cPosZ;
      [*] = ;   VectorRotateY(dirX, dirY, dirZ, angle);
      [*] = ;
      [*] = ;   var dPosX, dPosY, dPosZ : Float;
      [*] = ;   dPosX := cPosX + dirX;
      [*] = ;   dPosY := 0;
      [*] = ;   dPosZ := cPosZ + dirZ;
      [*] = ;
      [*] = ;   SetGameObjectPositionByHandle(goHandle, dPosX, dPosY, dPosZ);
      [*] = ;   GameObjectRollByHandle(goHandle, -angle);
      [*] = ;   GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ScaleRelativePosition(goHandle : Integer; cPosX, cPosZ, scale : Float);
      [*] = ;begin
      [*] = ;   var posX, posY, posZ : Float;
      [*] = ;   posX := GetGameObjectPositionXByHandle(goHandle);
      [*] = ;   posY := GetGameObjectPositionYByHandle(goHandle);
      [*] = ;   posZ := GetGameObjectPositionZByHandle(goHandle);
      [*] = ;
      [*] = ;   var ScaleX, ScaleY, ScaleZ, ScaleMod : float;
      [*] = ;   ScaleX := GetGameObjectScaleXByHandle(goHandle);
      [*] = ;   ScaleY := GetGameObjectScaleYByHandle(goHandle);
      [*] = ;   ScaleZ := GetGameObjectScaleZByHandle(goHandle);
      [*] = ;
      [*] = ;   SetGameObjectScaleByHandle(goHandle, ScaleX * scale, ScaleY * scale, ScaleZ * scale);
      [*] = ;   SetGameObjectTrackPointMoveStepByHandle(goHandle, GetGameObjectTrackPointMoveStepByHandle(goHandle) * scale);
      [*] = ;
      [*] = ;   var dPosX, dPosY, dPosZ : Float;
      [*] = ;   dPosX := cPosX + (posX-cPosX)*scale;
      [*] = ;   dPosY := 0;
      [*] = ;   dPosZ := cPosZ + (posZ-cPosZ)*scale;
      [*] = ;
      [*] = ;   SetGameObjectPositionByHandle(goHandle, dPosX, dPosY, dPosZ);
      [*] = ;   GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;function DoBuildInnerBuilding(pTownQuarter, pBuilding, pPlace, level : Integer) : Integer;
      [*] = ;begin
      [*] = ;   //var buildName : String = ParserGetValueByKeyByHandle(pBuilding, 'Name');
      [*] = ;   var quarterPosX : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterPosX');
      [*] = ;   var quarterPosZ : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterPosZ');
      [*] = ;   var quarterRotation : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterRotation');
      [*] = ;   var quarterScale : Float = ParserGetFloatValueByKeyByHandle(pTownQuarter, 'QuarterScale');
      [*] = ;   var quarterDebug : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarter, 'Debug');
      [*] = ;   var quarterEnabled : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarter, 'Enabled');
      [*] = ;   var maxDynamicCount : Integer = ParserGetIntValueByKeyByHandle(pTownQuarter, 'MaxDynamicCount');
      [*] = ;   var pTownQuarterBuildings : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Buildings');
      [*] = ;   var pTownQuarterPlaces : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Places');
      [*] = ;   var pTownQuarterPatterns : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Patterns');
      [*] = ;   var pTownQuarterMiscObjects : Integer = ParserSelectByHandleByKey(pTownQuarter, 'MiscObjects');
      [*] = ;
      [*] = ;   var globalPosX : Float = gFloatRegister_TownPositionX;
      [*] = ;   var globalPosZ : Float = gFloatRegister_TownPositionY;
      [*] = ;   const cPlName = 'townQuarter';
      [*] = ;   const cRaceName = 'buildings';
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cPlName);
      [*] = ;   if (plHnd=0) then
      [*] = ;      plHnd := CreatePlayer(cPlName, cRaceName, 'cmNone');
      [*] = ;
      [*] = ;   const cPatternPlName = 'townPattern';
      [*] = ;   const cPatternRaceName = 'nature';
      [*] = ;   var plPatternHnd : Integer = GetPlayerHandleByName(cPatternPlName);
      [*] = ;   if (plPatternHnd=0) then
      [*] = ;      plPatternHnd := CreatePlayer(cPatternPlName, cPatternRaceName, 'cmNone');
      [*] = ;   const cPatternMiscPlName = 'townMisc';
      [*] = ;   var plPatternMiscHnd : Integer = GetPlayerHandleByName(cPatternMiscPlName);
      [*] = ;   if (plPatternMiscHnd=0) then
      [*] = ;      plPatternMiscHnd := CreatePlayer(cPatternMiscPlName, cPatternRaceName, 'cmNone');
      [*] = ;
      [*] = ;   quarterPosX := globalPosX + quarterPosX;
      [*] = ;   quarterPosZ := globalPosZ + quarterPosZ;
      [*] = ;
      [*] = ;   Result := 0;
      [*] = ;   if (quarterEnabled) then
      [*] = ;   begin
      [*] = ;      if (_log) or (quarterDebug) then
      [*] = ;      begin
      [*] = ;         quarterPosX := quarterPosX;
      [*] = ;         quarterPosZ := quarterPosZ;
      [*] = ;         quarterRotation := quarterRotation;
      [*] = ;         _log_map('quarterPosX = ' + FloatToStr(quarterPosX) + ' quarterPosZ = ' + FloatToStr(quarterPosZ) + ' quarterRotation = ' + FloatToStr(quarterRotation));
      [*] = ;      end;
      [*] = ;
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pBuilding, 'Name');
      [*] = ;      var allyBuildName : String = ParserGetValueByKeyByHandle(pBuilding, 'AllyBuildName');
      [*] = ;      var minVariations : Integer;
      [*] = ;      if (ParserGetValueByKeyByHandle(pBuilding, 'MinVariations')='') then
      [*] = ;         minVariations := 1
      [*] = ;      else
      [*] = ;         minVariations := ParserGetIntValueByKeyByHandle(pBuilding, 'MinVariations');
      [*] = ;      var variationsCount : Integer = ParserGetIntValueByKeyByHandle(pBuilding, 'VariationsCount');
      [*] = ;      var scale : Float = ParserGetFloatValueByKeyByHandle(pBuilding, 'Scale');
      [*] = ;      var place : Integer = ParserGetIntValueByKeyByHandle(pBuilding, 'Place');
      [*] = ;      var baseRotateY : Float = ParserGetFloatValueByKeyByHandle(pBuilding, 'BaseRotateY');
      [*] = ;      var debugBld : Boolean = ParserGetBoolValueByKeyByHandle(pBuilding, 'Debug');
      [*] = ;      //var static : Boolean = false;
      [*] = ;      var baseName : String;
      [*] = ;      if ((minVariations=0) and (VariationsCount=1)) then
      [*] = ;         baseName := name
      [*] = ;      else
      [*] = ;         baseName := name+IntToStr(Floor(minVariations+level));
      [*] = ;
      [*] = ;      //var build : Boolean = ParserGetBoolValueByKeyByHandle(pTownQuarterBuilding, 'Build');
      [*] = ;      var buildingDecalName : String = ParserGetValueByKeyByHandle(pBuilding, 'BuildingDecalName');
      [*] = ;      var buildingDecalPosX : Float = ParserGetFloatValueByKeyByHandle(pBuilding, 'BuildingDecalPosX');
      [*] = ;      var buildingDecalPosZ : Float = ParserGetFloatValueByKeyByHandle(pBuilding, 'BuildingDecalPosZ');
      [*] = ;      var buildingPatternName : String = ParserGetValueByKeyByHandle(pBuilding, 'BuildingPatternName');
      [*] = ;      var buildingPatternPosX : Float = ParserGetFloatValueByKeyByHandle(pBuilding, 'BuildingPatternPosX');
      [*] = ;      var buildingPatternPosZ : Float = ParserGetFloatValueByKeyByHandle(pBuilding, 'BuildingPatternPosZ');
      [*] = ;
      [*] = ;      var posX : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'PosX');
      [*] = ;      var posY : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'PosY');
      [*] = ;      var posZ : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'PosZ');
      [*] = ;      var rotateY : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'RotateY');
      [*] = ;      var patternName : String = ParserGetValueByKeyByHandle(pPlace, 'PatternName');
      [*] = ;      var patternPosX : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'PatternPosX');
      [*] = ;      var patternPosZ : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'PatternPosZ');
      [*] = ;      var decalName : String = ParserGetValueByKeyByHandle(pPlace, 'DecalName');
      [*] = ;      var decalPosX : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'DecalPosX');
      [*] = ;      var decalPosZ : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'DecalPosZ');
      [*] = ;      var clearObjectsRadius : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'ClearObjectsRadius');
      [*] = ;      var clearObjectsX : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'ClearObjectsX');
      [*] = ;      var clearObjectsZ : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'ClearObjectsZ');
      [*] = ;      var debug : Boolean = ParserGetBoolValueByKeyByHandle(pPlace, 'Debug');
      [*] = ;
      [*] = ;      var createWaterField : Boolean = ParserGetBoolValueByKeyByHandle(pPlace, 'CreateWaterField');
      [*] = ;      var createWaterTX : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'CreateWaterTX');
      [*] = ;      var createWaterTZ : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'CreateWaterTZ');
      [*] = ;      var createWaterBX : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'CreateWaterBX');
      [*] = ;      var createWaterBZ : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'CreateWaterBZ');
      [*] = ;      var createWaterOffset : Float = ParserGetFloatValueByKeyByHandle(pPlace, 'CreateWaterOffset');
      [*] = ;
      [*] = ;      rotateY := rotateY + baseRotateY;
      [*] = ;
      [*] = ;      if (_log) or (debug) or (debugBld) then
      [*] = ;         _log_map('posX = ' + FloatToStr(posX) + '; posZ = ' + FloatToStr(posZ) + '; rotateY = ' + FloatToStr(rotateY) + '; baseName = ' + baseName);
      [*] = ;
      [*] = ;      var relativePosX : Float = quarterPosX;
      [*] = ;      var relativePosZ : Float = quarterPosZ;
      [*] = ;
      [*] = ;      if (createWaterField) then
      [*] = ;         WaterFieldAdd(gc_WaterNameInnerBuild, relativePosX+createWaterTX, relativePosZ+createWaterTZ, relativePosX+createWaterBX, relativePosZ+createWaterBZ, createWaterOffset);
      [*] = ;
      [*] = ;      if (clearObjectsRadius>0) then
      [*] = ;      begin
      [*] = ;         SetFloatValueByName('clearObjectsX', relativePosX+posX+clearObjectsX);
      [*] = ;         SetFloatValueByName('clearObjectsZ', relativePosZ+posZ+clearObjectsZ);
      [*] = ;         SetFloatValueByName('clearObjectsRadius', clearObjectsRadius);
      [*] = ;         GameObjectMyDelayExecuteState('DoInertiaFall', 0.5);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var currentPlaceBuilding : String = ParserGetValueByKeyByHandle(pPlace, 'CurrentPlaceBuilding');
      [*] = ;      if (currentPlaceBuilding='') then
      [*] = ;      begin
      [*] = ;         if (patternName<>'') then
      [*] = ;            StandPattern(plPatternMiscHnd{plHnd}, patternName, relativePosX+posX+patternPosX, relativePosZ+posZ+patternPosZ, 0);
      [*] = ;
      [*] = ;         if (decalName<>'') then
      [*] = ;            PutDecalByName(relativePosX+posX+decalPosX, relativePosZ+posZ+decalPosZ, decalName);
      [*] = ;
      [*] = ;         if (buildingDecalName<>'') then
      [*] = ;            PutDecalByName(relativePosX+posX+buildingDecalPosX, relativePosZ+posZ+buildingDecalPosZ, buildingDecalName);
      [*] = ;
      [*] = ;         if (buildingPatternName<>'') then
      [*] = ;            StandPattern(plPatternMiscHnd{plPatternHnd}, buildingPatternName, relativePosX+posX+buildingPatternPosX, relativePosZ+posZ+buildingPatternPosZ, 0);
      [*] = ;
      [*] = ;         gBoolRegister_NeedSeasonChangeObjects := True;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (allyBuildName<>'') then
      [*] = ;         baseName := allyBuildName;
      [*] = ;
      [*] = ;      var goHandle : Integer = CreatePlayerGameObjectHandle(cPlName, cRaceName, baseName, relativePosX+posX, 0, relativePosZ+posZ);
      [*] = ;      Result := goHandle;
      [*] = ;      GameObjectRollByHandle(goHandle, rotateY);
      [*] = ;      SetGameObjectScaleByHandle(goHandle, scale*GetGameObjectScaleXByHandle(goHandle), scale*GetGameObjectScaleYByHandle(goHandle), scale*GetGameObjectScaleZByHandle(goHandle));
      [*] = ;
      [*] = ;      RotateRelativePosition(goHandle, relativePosX, relativePosZ, quarterRotation);
      [*] = ;      ScaleRelativePosition(goHandle, relativePosX, relativePosZ, quarterScale);
      [*] = ;
      [*] = ;      if (posY<>0) then
      [*] = ;      begin
      [*] = ;         GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;         SetGameObjectAutoOffsetByHandle(goHandle, false);
      [*] = ;         SetGameObjectPositionByHandle(goHandle, GetGameObjectPositionXByHandle(goHandle), GetGameObjectPositionYByHandle(goHandle)+posY, GetGameObjectPositionZByHandle(goHandle));
      [*] = ;      end;
      [*] = ;
      [*] = ;      ParserSetBoolValueByKeyByHandle(pPlace, 'Busy', True);
      [*] = ;      ParserSetValueByKeyByHandle(pPlace, 'CurrentPlaceBuilding', name);
      [*] = ;
      [*] = ;      if (goHandle<>0) then
      [*] = ;      begin
      [*] = ;         GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;         SetGameObjectAutoOffsetByHandle(goHandle, false);
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'DoUnvisible');
      [*] = ;         GameObjectDelayExecuteStateByHandle(goHandle, 'DoConstruct', 1.25);
      [*] = ;
      [*] = ;         var myHnd : Integer = GetGameObjectMyHandle;
      [*] = ;         SetGameObjectPositionByHandle(myHnd, GetGameObjectPositionXByHandle(goHandle), GetGameObjectPositionYByHandle(goHandle), GetGameObjectPositionZByHandle(goHandle));
      [*] = ;
      [*] = ;         GameObjectPFXSrcLibCreateByHandle(myHnd, 'fx_build_boom', 'fx_build_boom');
      [*] = ;         GameObjectPFXSrcLibCreateByHandle(myHnd, 'fx_build_boom2', 'fx_build_boom2');
      [*] = ;         const fxBoomLifeTime = 0.75;
      [*] = ;         const fxBoom2LifeTime = 1.25;
      [*] = ;         var effHnd : Integer = GetEffectByKey(myHnd, 'fx_build_boom');
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'LifeTime', fxBoomLifeTime);
      [*] = ;         effHnd := GetEffectByKey(myHnd, 'fx_build_boom2');
      [*] = ;         SetBehaviourFloatProperty(effHnd, 'LifeTime', fxBoom2LifeTime);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ErrorLog(_log_name+' bld.dummy.aix : DoBuildInnerBuilding : goHnd = 0');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (StrPos('castle', baseName)>0) and (not SameText(baseName, 'castle1') and (not SameText(baseName, 'darkcastle'))) then
      [*] = ;      begin
      [*] = ;         baseName := 'castlehill';
      [*] = ;         goHandle := CreatePlayerGameObjectHandle(cPlName, cRaceName, baseName, relativePosX+posX, posY, relativePosZ+posZ);
      [*] = ;         GameObjectRollByHandle(goHandle, rotateY);
      [*] = ;         SetGameObjectScaleByHandle(goHandle, scale*GetGameObjectScaleXByHandle(goHandle), scale*GetGameObjectScaleYByHandle(goHandle), scale*GetGameObjectScaleZByHandle(goHandle));
      [*] = ;
      [*] = ;         RotateRelativePosition(goHandle, relativePosX, relativePosZ, quarterRotation);
      [*] = ;         ScaleRelativePosition(goHandle, relativePosX, relativePosZ, quarterScale);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if _log then _Log_map(_log_name+' Quarter is not yet enabled.');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pTownQuarter : Integer = IntRegister0;
      [*] = ;var pBuilding : Integer = IntRegister1;
      [*] = ;var pPlace : Integer = IntRegister2;
      [*] = ;var level : Integer = IntRegister3;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var goHnd : Integer = DoBuildInnerBuilding(pTownQuarter, pBuilding, pPlace, level);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

