section.begin
   Name = Landmarks
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\LANDMARKS';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'landmarks';
      [*] = ;const cRaceName = 'nature';
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
      [*] = ;var pLandmarks : Integer = gPrototypeData.landmarks.handle;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;var hexCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if (uPlHandle=0) then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   var i, j, k, l, m : Integer;
      [*] = ;   
      [*] = ;   for i:=1 to ParserGetCountByHandle(pLandmarks)-1 do
      [*] = ;   begin
      [*] = ;      var pLandmark : Integer = ParserSelectByHandleByIndex(pLandmarks, i);
      [*] = ;      var pLandmarkTerrainTypes : Integer = ParserSelectByHandleByKey(pLandmark, 'TerrainType');
      [*] = ;      var pLandmarkPatterns : Integer = ParserSelectByHandleByKey(pLandmark, 'Patterns');
      [*] = ;      var pLandmarkProvinceTypes : Integer = ParserSelectByHandleByKey(pLandmark, 'ProvinceTypeList');
      [*] = ;      var landmarkID : Integer = ParserGetIntValueByKeyByHandle(pLandmark, 'LandmarkID');
      [*] = ;      var landmarkMaxCount : Integer = ParserGetIntValueByKeyByHandle(pLandmark, 'MaxCount');
      [*] = ;      var landmarkType : Integer = ParserGetIntValueByKeyByHandle(pLandmark, 'Type');
      [*] = ;      var landmarkSite : Integer = ParserGetIntValueByKeyByHandle(pLandmark, 'Site');
      [*] = ;      var raceName : String = ParserGetValueByKeyByHandle(pLandmark, 'RaceName');
      [*] = ;      var baseName : String = ParserGetValueByKeyByHandle(pLandmark, 'BaseName');
      [*] = ;      if (ParserGetCountByHandle(pLandmarkPatterns)>0) or ((raceName<>'') and (baseName<>'')) then
      [*] = ;      begin
      [*] = ;         var baseNameVar : Integer = ParserGetIntValueByKeyByHandle(pLandmark, 'BaseNameVar');
      [*] = ;         var maxCount : Integer = landmarkMaxCount;
      [*] = ;         if (ParserGetValueByKeyByHandle(pLandmark, 'MaxCount')='') then
      [*] = ;         maxCount := 1;
      [*] = ;   
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleLandmarksExist) then
      [*] = ;         begin
      [*] = ;            if (_worldrule_GetWorldRuleLandmarkExistByID(landmarkID)) then
      [*] = ;            maxCount := _worldrule_GetWorldRuleLandmarkMaxCountByID(landmarkID);
      [*] = ;         end;
      [*] = ;   
      [*] = ;         var curCount : Integer;
      [*] = ;         for curCount:=0 to maxCount-1 do
      [*] = ;         begin
      [*] = ;            var tBool : Boolean = False;
      [*] = ;            var rndSum : Integer = 0;
      [*] = ;            var allTerrainTypes : Boolean = False;
      [*] = ;            var landmarkTCount : Integer = 0;
      [*] = ;   
      [*] = ;            for j:=0 to ParserGetCountByHandle(pLandmarkTerrainTypes)-1 do
      [*] = ;            begin
      [*] = ;               var pLandmarkTerrainType : Integer = ParserSelectByHandleByIndex(pLandmarkTerrainTypes, j);
      [*] = ;               var tName : String = ParserGetKeyName(pLandmarkTerrainType);
      [*] = ;               tBool := ParserGetBoolValueByKeyByHandle(pLandmarkTerrainTypes, tName);
      [*] = ;               if (tBool) then
      [*] = ;               landmarkTCount := landmarkTCount+1;
      [*] = ;            end;
      [*] = ;            if (landmarkTCount=0) then
      [*] = ;            begin
      [*] = ;               landmarkTCount := 1;
      [*] = ;               allTerrainTypes := True;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            for j := 0 to ParserGetCountByHandle(pLandmarkTerrainTypes)-1 do
      [*] = ;            begin
      [*] = ;               if (landmarkTCount>0) or (allTerrainTypes) then
      [*] = ;               begin
      [*] = ;                  var pLandmarkTerrainType : Integer = ParserSelectByHandleByIndex(pLandmarkTerrainTypes, j);
      [*] = ;                  var tName : String = ParserGetKeyName(pLandmarkTerrainType);
      [*] = ;                  var tBool : Boolean = ParserGetBoolValueByKeyByHandle(pLandmarkTerrainTypes, tName);
      [*] = ;   
      [*] = ;                  StringRegister0 := tName;
      [*] = ;                  ExecuteState('GetTerrainParserByName');
      [*] = ;                  var pLMTerrainType : Integer = IntRegister0;
      [*] = ;                  var lmTerrainType : Integer = ParserGetIntValueByKeyByHandle(pLMTerrainType, 'TerrainID');
      [*] = ;   
      [*] = ;                  if (tBool) or (allTerrainTypes) then
      [*] = ;                  begin
      [*] = ;                     landmarkTCount := landmarkTCount-1;
      [*] = ;   
      [*] = ;                     for k:=0 to hexCount-1 do
      [*] = ;                     begin
      [*] = ;                        var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, k);
      [*] = ;                        var terrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;                        var provinceType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;                        if provinceType=15 then
      [*] = ;                        provinceType:=15;
      [*] = ;                        var pStratHexCellLandmarks : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Landmarks');
      [*] = ;                        var pStratHexCellSites : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Sites');
      [*] = ;                        var IsCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;                        var noLandmarks : Boolean = True;
      [*] = ;                        for l:=0 to ParserGetCountByHandle(pStratHexCellLandmarks)-1 do
      [*] = ;                        begin
      [*] = ;                           var pStratHexCellLandmark : Integer = ParserSelectByHandleByIndex(pStratHexCellLandmarks, l);
      [*] = ;                           var StratHexCellLandmarkID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCellLandmark, 'LandmarkID');
      [*] = ;                           if (StratHexCellLandmarkID<>0) then
      [*] = ;                           begin
      [*] = ;                              noLandmarks := False;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        var provinceTypeAvailable : Boolean = False;
      [*] = ;                        var ptInd : Integer;
      [*] = ;                        for ptInd := 0 to ParserGetCountByHandle(pLandmarkProvinceTypes)-1 do
      [*] = ;                        begin
      [*] = ;                           var pLandmarkProvinceType : Integer = ParserSelectByHandleByIndex(pLandmarkProvinceTypes, ptInd);
      [*] = ;                           var landmarkProvinceType : Integer = ParserGetIntValueByKeyByHandle(pLandmarkProvinceType, 'ProvinceType');
      [*] = ;                           if (landmarkProvinceType = provinceType) or (landmarkProvinceType = 0) then
      [*] = ;                           begin
      [*] = ;                              provinceTypeAvailable := true;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if {(not IsCastle) and} (noLandmarks) and (((terrainType = lmTerrainType) and provinceTypeAvailable and (not allTerrainTypes)) or ((allTerrainTypes) and (terrainType = gc_WaterTerrainType))) then
      [*] = ;                        begin
      [*] = ;                           var possibility : Integer = 0;
      [*] = ;                           if (landmarkType=0) then //Alex uses only type=0, but there is possibility to use other types for some ideas.
      [*] = ;                           begin
      [*] = ;                              if (landmarkSite=0) then
      [*] = ;                              possibility := 10
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 for m:=0 to ParserGetCountByHandle(pStratHexCellSites)-1 do
      [*] = ;                                 begin
      [*] = ;                                    var pSite : Integer = ParserSelectByHandleByIndex(pStratHexCellSites, m);
      [*] = ;                                    var siteID : Integer = ParserGetIntValueByKeyByHandle(pSite, 'SiteID');
      [*] = ;                                    if (siteID=landmarkSite) then
      [*] = ;                                    possibility := possibility+1;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                              //var TerrainTypeIndex : Integer = ParserGetValueByKeyByHandle(TerrainID, 'TerrainType');
      [*] = ;                           end;
      [*] = ;   
      [*] = ;                           if (possibility>0) then
      [*] = ;                           rndSum := rndSum + possibility;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            //SETUP
      [*] = ;            var rndValue : Float = Random*rndSum;
      [*] = ;            rndSum := 0;
      [*] = ;   
      [*] = ;            tBool := False;
      [*] = ;            allTerrainTypes := False;
      [*] = ;            landmarkTCount := 0;
      [*] = ;            for j:=0 to ParserGetCountByHandle(pLandmarkTerrainTypes)-1 do
      [*] = ;            begin
      [*] = ;               var pLandmarkTerrainType : Integer = ParserSelectByHandleByIndex(pLandmarkTerrainTypes, j);
      [*] = ;               var tName : String = ParserGetKeyName(pLandmarkTerrainType);
      [*] = ;               tBool := ParserGetBoolValueByKeyByHandle(pLandmarkTerrainTypes, tName);
      [*] = ;               if (tBool) then
      [*] = ;               landmarkTCount := landmarkTCount+1;
      [*] = ;            end;
      [*] = ;            if (landmarkTCount=0) then
      [*] = ;            begin
      [*] = ;               landmarkTCount := 1;
      [*] = ;               allTerrainTypes := True;
      [*] = ;            end;
      [*] = ;   
      [*] = ;            for [LandmarkSetup]j:=0 to ParserGetCountByHandle(pLandmarkTerrainTypes)-1 do
      [*] = ;            begin
      [*] = ;               if (landmarkTCount>0) or (allTerrainTypes) then
      [*] = ;               begin
      [*] = ;                  var pLandmarkTerrainType : Integer = ParserSelectByHandleByIndex(pLandmarkTerrainTypes, j);
      [*] = ;                  var tName : String = ParserGetKeyName(pLandmarkTerrainType);
      [*] = ;                  var tBool : Boolean = ParserGetBoolValueByKeyByHandle(pLandmarkTerrainTypes, tName);
      [*] = ;   
      [*] = ;                  StringRegister0 := tName;
      [*] = ;                  ExecuteState('GetTerrainParserByName');
      [*] = ;                  var pLMTerrainType : Integer = IntRegister0;
      [*] = ;                  var lmTerrainType : Integer = ParserGetIntValueByKeyByHandle(pLMTerrainType, 'TerrainID');
      [*] = ;   
      [*] = ;                  if tBool or allTerrainTypes then
      [*] = ;                  begin
      [*] = ;                     landmarkTCount := landmarkTCount-1;
      [*] = ;   
      [*] = ;                     for k:=0 to hexCount-1 do
      [*] = ;                     begin
      [*] = ;                        var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, k);
      [*] = ;                        if (pStratHexCell=0) then ErrorLog('pStratHexCell=0');
      [*] = ;                        var terrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;                        var provinceType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'ProvinceType');
      [*] = ;                        var pStratHexCellLandmarks : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Landmarks');
      [*] = ;                        var pStratHexCellSites : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Sites');
      [*] = ;                        var IsCastle : Boolean = ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle');
      [*] = ;                        var noLandmarks : Boolean = True;
      [*] = ;                        for l:=0 to ParserGetCountByHandle(pStratHexCellLandmarks)-1 do
      [*] = ;                        begin
      [*] = ;                           var pStratHexCellLandmark : Integer = ParserSelectByHandleByIndex(pStratHexCellLandmarks, l);
      [*] = ;                           var StratHexCellLandmarkID : Integer = ParserGetIntValueByKeyByHandle(pStratHexCellLandmark, 'LandmarkID');
      [*] = ;                           if (StratHexCellLandmarkID<>0) then
      [*] = ;                           begin
      [*] = ;                              noLandmarks := False;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        var provinceTypeAvailable : Boolean = False;
      [*] = ;                        var ptInd : Integer;
      [*] = ;                        for ptInd := 0 to ParserGetCountByHandle(pLandmarkProvinceTypes)-1 do
      [*] = ;                        begin
      [*] = ;                           var pLandmarkProvinceType : Integer = ParserSelectByHandleByIndex(pLandmarkProvinceTypes, ptInd);
      [*] = ;                           var landmarkProvinceType : Integer = ParserGetIntValueByKeyByHandle(pLandmarkProvinceType, 'ProvinceType');
      [*] = ;                           if (landmarkProvinceType = provinceType) or (landmarkProvinceType = 0) then
      [*] = ;                           begin
      [*] = ;                              provinceTypeAvailable := true;
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;   
      [*] = ;                        if {(not IsCastle) and} (noLandmarks) and (((terrainType = lmTerrainType) and (provinceTypeAvailable) and (not allTerrainTypes)) or ((allTerrainTypes) and (terrainType = gc_WaterTerrainType))) then
      [*] = ;                        begin
      [*] = ;                           var possibility : Integer = 0;
      [*] = ;                           if (landmarkType=0) then //Alex uses only type=0, but there is possibility to use other types for some ideas.
      [*] = ;                           begin
      [*] = ;                              if (landmarkSite=0) then
      [*] = ;                                 possibility := 10
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 for m:=0 to ParserGetCountByHandle(pStratHexCellSites)-1 do
      [*] = ;                                 begin
      [*] = ;                                    var pSite : Integer = ParserSelectByHandleByIndex(pStratHexCellSites, m);
      [*] = ;                                    var siteID : Integer = ParserGetIntValueByKeyByHandle(pSite, 'SiteID');
      [*] = ;                                    if (siteID=landmarkSite) then
      [*] = ;                                       possibility := possibility+1;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                              //var TerrainTypeIndex : Integer = ParserGetValueByKeyByHandle(TerrainID, 'TerrainType');
      [*] = ;                           end;
      [*] = ;   
      [*] = ;                           if (possibility>0) then
      [*] = ;                           begin
      [*] = ;                              rndSum := rndSum + possibility;
      [*] = ;                              if (rndValue<rndSum) then
      [*] = ;                              begin
      [*] = ;                                 var pStratHexCellLandmark : Integer = ParserSelectByHandleByIndex(pStratHexCellLandmarks, 0);
      [*] = ;                                 if (pStratHexCellLandmark<>0) then
      [*] = ;                                 begin
      [*] = ;                                    var StratHexCellLandmarkX : Float = ParserGetFloatValueByKeyByHandle(pStratHexCellLandmark, 'X');
      [*] = ;                                    var StratHexCellLandmarkY : Float = ParserGetFloatValueByKeyByHandle(pStratHexCellLandmark, 'Y');
      [*] = ;   
      [*] = ;                                    var patternIndex : Integer = -1;
      [*] = ;                                    var patternName : String = '';
      [*] = ;                                    if (ParserGetCountByHandle(pLandmarkPatterns)>0) then
      [*] = ;                                       patternIndex := floor(Random*ParserGetCountByHandle(pLandmarkPatterns));
      [*] = ;                                    if (patternIndex>-1) then
      [*] = ;                                    begin
      [*] = ;                                       var pLandmarkPattern : Integer = ParserSelectByHandleByIndex(pLandmarkPatterns, patternIndex);
      [*] = ;                                       patternName := ParserGetValueByKeyByHandle(pLandmarkPattern, 'Name');
      [*] = ;                                    end;
      [*] = ;   
      [*] = ;                                    var bPlaced : Boolean = False;
      [*] = ;                                    if (patternName<>'') then
      [*] = ;                                    begin
      [*] = ;                                       bPlaced := True;
      [*] = ;                                       StandPatternAdv(uPlHandle, patternName, round(StratHexCellLandmarkX), round(StratHexCellLandmarkY), 0, false, false, '', '', 0);
      [*] = ;                                    end;
      [*] = ;   
      [*] = ;                                    if (raceName<>'') and (baseName<>'') then
      [*] = ;                                    begin
      [*] = ;                                       bPlaced := True;
      [*] = ;                                       var tmpBaseName : String = baseName;
      [*] = ;                                       if (baseNameVar>0) then
      [*] = ;                                       tmpBaseName := baseName+IntToStr(floor(1+Random*baseNameVar));
      [*] = ;                                       var goHandle : Integer = CreatePlayerGameObjectHandle(cPlayerName, raceName, tmpBaseName, StratHexCellLandmarkX, 0, StratHexCellLandmarkY);
      [*] = ;                                       GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;                                    end;
      [*] = ;   
      [*] = ;                                    if (bPlaced) then
      [*] = ;                                    ParserSetIntValueByKeyByHandle(pStratHexCellLandmark, 'LandmarkID', landmarkID);
      [*] = ;   
      [*] = ;                                    break(LandmarkSetup);
      [*] = ;                                 end
      [*] = ;                                 else
      [*] = ;                                 ErrorLogI('pStratHexCellLandmarkExt=0');
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   const cPatternPlName = 'pattern';
      [*] = ;   //const cPatternPlRaceTag = 30;
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cPatternPlName);
      [*] = ;   if plHnd <> 0 then
      [*] = ;   for i:=0 to GetPlayerGameObjectsCountByHandle(uPlHandle)-1 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, uPlHandle);
      [*] = ;      var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;      var deleteRadius : Float = 1;
      [*] = ;      if SameText(GetGameObjectBaseNameByHandle(goHandle), 'eviltree') then
      [*] = ;         deleteRadius := 1.5
      [*] = ;      else
      [*] = ;      if SameText(GetGameObjectBaseNameByHandle(goHandle), 'skulltree') then
      [*] = ;         deleteRadius := 1.5
      [*] = ;      else
      [*] = ;      if StrPos('monument', GetGameObjectBaseNameByHandle(goHandle))>0 then
      [*] = ;         deleteRadius := 1.5;
      [*] = ;   
      [*] = ;      GetGameObjectsInRadius(posX, posZ, deleteRadius, false, true, plHnd, 0, 0, false, false, false, false, false, false);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to GetGameObjectListCount()-1 do
      [*] = ;      begin
      [*] = ;         var goHnd : Integer = GetGameObjectListByIndex(j);
      [*] = ;         var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;         var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;   
      [*] = ;         if (not GetGameObjectPlayableObjectByHandle(goHnd)) and (VectorDistance(posX, 0, posZ, goPosX, 0, goPosZ)<deleteRadius) then
      [*] = ;            AddObjectToDestroyList(goHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
      [*] = ;      //DeletePlayerByHandle(uPlHandle);
      [*] = ;
      [*] = ;      var i, j, pStratHexCell, pStratHexCellLandmarks, pStratHexCellLandmark, StratHexCellLandmarkID : Integer;
      [*] = ;
      [*] = ;      for i:=0 to hexCount-1 do
      [*] = ;      begin
      [*] = ;         pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         pStratHexCellLandmarks := ParserSelectByHandleByKey(pStratHexCell, 'Landmarks');
      [*] = ;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pStratHexCellLandmarks)-1 do
      [*] = ;         begin
      [*] = ;            pStratHexCellLandmark := ParserSelectByHandleByIndex(pStratHexCellLandmarks, j);
      [*] = ;            StratHexCellLandmarkID := ParserGetIntValueByKeyByHandle(pStratHexCellLandmark, 'LandmarkID');
      [*] = ;            if (StratHexCellLandmarkID<>0) then
      [*] = ;               ParserSetIntValueByKeyByHandle(pStratHexCellLandmark, 'LandmarkID', 0);
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

