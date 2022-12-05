section.begin
   Name = InnerBuildScenery
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\INNERBUILDSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'townQuarter';
      [*] = ;const cRaceName = 'buildings';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;      
      [*] = ;const cTownRadius = 30;
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if uPlHandle = 0 then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   function UpgradeBuilt(const buildID, pInnerBuildings : Integer) : Boolean;
      [*] = ;   begin
      [*] = ;      Result := False;
      [*] = ;      
      [*] = ;      var i : Integer;
      [*] = ;      for i := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pInnerBuildings, i), 'BuildingID');
      [*] = ;         ExecuteState('GetInnerBuildParserByID');
      [*] = ;         if ParserGetIntValueByKeyByHandle(IntRegister1, 'Upgrade') = buildID then
      [*] = ;         begin
      [*] = ;            Result := True;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;               
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;   var pCastle : Integer = IntRegister0;
      [*] = ;   
      [*] = ;   var pInnerBuilding, buildID : Integer;
      [*] = ;   var pInnerBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'InnerBuildings');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pInnerBuildings)-1 do
      [*] = ;   begin
      [*] = ;      pInnerBuilding := ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;      buildID := ParserGetIntValueByKeyByHandle(pInnerBuilding, 'BuildingID');
      [*] = ;                     
      [*] = ;      if not UpgradeBuilt(buildID, pInnerBuildings) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := buildID;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'CreateInnerBuildModel');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;   begin
      [*] = ;      var pTownQuarters : Integer = gPrototypeData.townQuarters.handle;
      [*] = ;      
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle); // this player should never be deleted because otherwise new buildings can't be constructed
      [*] = ;      ClearPlayerGameObjectsByHandle(GetPlayerHandleByName('townMisc'));  // clear annexed patterns also
      [*] = ;      _map_ClearWaterFieldsByName(gc_WaterNameInnerBuild);
      [*] = ;      _map_ClearDecalsInArea(gFloatRegister_TownPositionX, gFloatRegister_TownPositionY, cTownRadius, 'torch');
      [*] = ;       
      [*] = ;      var i, j, pTownQuarter, pPlaces, pPlace : Integer;
      [*] = ;      for i := 0 to ParserGetCountByHandle(pTownQuarters)-1 do
      [*] = ;      begin
      [*] = ;         pTownQuarter := ParserSelectByHandleByIndex(pTownQuarters, i);
      [*] = ;         pPlaces := ParserSelectByHandleByKey(pTownQuarter, 'Places');
      [*] = ;                  
      [*] = ;         for j := 0 to ParserGetCountByHandle(pPlaces)-1 do
      [*] = ;         begin
      [*] = ;            pPlace := ParserSelectByHandleByIndex(pPlaces, j);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pPlace, 'Busy', False);
      [*] = ;            ParserSetValueByKeyByHandle(pPlace, 'CurrentPlaceBuilding', '');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then Clear();
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;sTrace := _log_name;
      [*] = ;if (runFlags and 2) > 0 then sTrace := sTrace + '['+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle))+']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace, $1000000 or _log_trace);
   struct.end
section.end

