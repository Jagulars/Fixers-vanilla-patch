section.begin
   Name = CreateInnerBuildModel
   Description : struct.begin
      [*] = ;IntRegister0 - inner building ID
   struct.end
   Code : struct.begin
      [*] = ;var buildID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CREATEINNERBUILDMODEL';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;IntRegister0 := buildID;
      [*] = ;MapExecuteState('GetInnerBuildParserByID');
      [*] = ;var pInnerBuild : Integer = IntRegister1;
      [*] = ;
      [*] = ;var buildName : String = ParserGetValueByKeyByHandle(pInnerBuild, 'BuildName');
      [*] = ;var upgrade : Integer = ParserGetIntValueByKeyByHandle(pInnerBuild, 'Upgrade');
      [*] = ;var parentBuildID : Integer = buildID;
      [*] = ;var pParentBuilding : Integer = pInnerBuild;
      [*] = ;var level : Integer = 0;
      [*] = ;if (buildName='') then
      [*] = ;begin
      [*] = ;   while (upgrade<>0) do
      [*] = ;   begin
      [*] = ;      level := level+1;
      [*] = ;      parentBuildID := upgrade;
      [*] = ;      IntRegister0 := parentBuildID;
      [*] = ;      MapExecuteState('GetInnerBuildParserByID');
      [*] = ;      pParentBuilding := IntRegister1;
      [*] = ;      upgrade := ParserGetIntValueByKeyByHandle(pParentBuilding, 'Upgrade');
      [*] = ;   end;
      [*] = ;   buildName := ParserGetValueByKeyByHandle(pParentBuilding, 'BuildName');
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _Log_Map(_log_name+' Building name: '+buildName+', Level: '+IntToStr(level));
      [*] = ;
      [*] = ;var pBuilding, pPlace, pTownQuarter : Integer = 0;
      [*] = ;
      [*] = ;if (buildName<>'') then
      [*] = ;begin
      [*] = ;   var pTownQuarters : Integer = gPrototypeData.townQuarters.handle;
      [*] = ;
      [*] = ;   if (pTownQuarters<>0) then
      [*] = ;   begin
      [*] = ;      for [MAIN]i:=0 to ParserGetCountByHandle(pTownQuarters)-1 do
      [*] = ;      begin
      [*] = ;         var pTownQuarterTmp : Integer = ParserSelectByHandleByIndex(pTownQuarters, i);
      [*] = ;         var pBuildings : Integer = ParserSelectByHandleByKey(pTownQuarterTmp, 'Buildings');
      [*] = ;         if (pBuildings<>0) then
      [*] = ;         begin
      [*] = ;            for j:=0 to ParserGetCountByHandle(pBuildings)-1 do
      [*] = ;            begin
      [*] = ;               var pBuildingTmp : Integer = ParserSelectByHandleByIndex(pBuildings, j);
      [*] = ;               var name : String = ParserGetValueByKeyByHandle(pBuildingTmp, 'Name');
      [*] = ;               if SameText(buildName, name) then
      [*] = ;               begin
      [*] = ;                  pBuilding := pBuildingTmp;
      [*] = ;                  pTownQuarter := pTownQuarterTmp;
      [*] = ;                  var place : Integer = ParserGetIntValueByKeyByHandle(pBuilding, 'Place');
      [*] = ;                  var pPlaces : Integer = ParserSelectByHandleByKey(pTownQuarter, 'Places');
      [*] = ;                  if (pPlaces<>0) then
      [*] = ;                  begin
      [*] = ;                     var k : Integer;
      [*] = ;                     for k:=0 to ParserGetCountByHandle(pPlaces)-1 do
      [*] = ;                     begin
      [*] = ;                        var pPlaceTmp : Integer = ParserSelectByHandleByIndex(pPlaces, k);
      [*] = ;                        if (place<>-1) then
      [*] = ;                        begin
      [*] = ;                           var placeName : Integer = ParserGetIntValueByKeyByHandle(pPlaceTmp, 'Name');
      [*] = ;                           if (placeName=place) then
      [*] = ;                           begin
      [*] = ;                              pPlace := pPlaceTmp;
      [*] = ;                              break(MAIN);
      [*] = ;                           end;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           if (not ParserGetBoolValueByKeyByHandle(pPlaceTmp, 'Static')) then
      [*] = ;                           begin
      [*] = ;                              var bBusy : Boolean = ParserGetBoolValueByKeyByHandle(pPlaceTmp, 'Busy');
      [*] = ;                              var curPlaceBuilding : String = ParserGetValueByKeyByHandle(pPlaceTmp, 'CurrentPlaceBuilding');
      [*] = ;                              if (not bBusy) or (bBusy and SameText(buildName, curPlaceBuilding)) then
      [*] = ;                              begin
      [*] = ;                                 pPlace := pPlaceTmp;
      [*] = ;                                 break(MAIN);
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
      [*] = ;end
      [*] = ;else
      [*] = ;   ErrorLog(_log_name+' pTownQuarters=0');
      [*] = ;
      [*] = ;if (pTownQuarter<>0) and (pBuilding<>0) and (pPlace<>0) then
      [*] = ;begin
      [*] = ;   const cPlName = 'townQuarter';
      [*] = ;   const cRaceName = 'misc';
      [*] = ;   const cBaseName = 'build';
      [*] = ;   var goHandle : Integer = CreatePlayerGameObjectHandle(cPlName, cRaceName, cBaseName, 0, 0, 0);
      [*] = ;   IntRegister0 := pTownQuarter;
      [*] = ;   IntRegister1 := pBuilding;
      [*] = ;   IntRegister2 := pPlace;
      [*] = ;   IntRegister3 := level;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'DoBuildInnerBuilding');
      [*] = ;end
      [*] = ;else
      [*] = ;   ErrorLog(_log_name+': (pTownQuarter=0) or (pBuilding=0) or (pPlace=0)');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

