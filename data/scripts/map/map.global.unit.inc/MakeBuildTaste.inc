section.begin
   Name = MakeBuildTaste
   Description : struct.begin
      [*] = ;IntRegister0 - inner building ID
      [*] = ;IntRegister1 - building taste
      [*] = ;IntRegister2 - building tastes parser handle
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;// TODO: Can be optimized
      [*] = ;
      [*] = ;var buildID : Integer = IntRegister0;
      [*] = ;var taste : Integer = IntRegister1;
      [*] = ;var pBuildTastes : Integer = IntRegister2;
      [*] = ;
      [*] = ;_misc_AntiFreeze;
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var pMyInnerBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'InnerBuildings');
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var pInnerBuildings : Integer = gPrototypeData.innerBuildings.handle;
      [*] = ;
      [*] = ;var pBuildTaste : Integer = ParserSelectByHandleByIndex(pBuildTastes, buildID);
      [*] = ;var buildTaste : Integer = ParserGetIntValueByKeyByHandle(pBuildTaste, 'Taste');
      [*] = ;buildTaste := buildTaste + taste;
      [*] = ;ParserSetIntValueByKeyByHandle(pBuildTaste, 'Taste', buildTaste);
      [*] = ;
      [*] = ;taste := taste div 2;
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;if (taste > 0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := buildID;
      [*] = ;   ExecuteState('IsBuildingAvailable'); 
      [*] = ;   if (not BoolRegister0) and (not BoolRegister1) and (not BoolRegister2) and BoolRegister3 and BoolRegister4 and (not BoolRegister5) then // when could build but prerequisite buildings are not yet built
      [*] = ;   begin
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetInnerBuildParserByID', 0);
      [*] = ;      var pInnerBuild : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var pRequiredBuildings : Integer = ParserSelectByHandleByKey(pInnerBuild, 'RequiredBuildings');
      [*] = ;      for i := ParserGetCountByHandle(pRequiredBuildings)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pRequiredBuilding : Integer = ParserSelectByHandleByIndex(pRequiredBuildings, i);
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pRequiredBuilding, 'BuildingID');
      [*] = ;
      [*] = ;         IntRegister0 := id;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;         if not BoolRegister0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := id;
      [*] = ;            IntRegister1 := taste;
      [*] = ;            IntRegister2 := pBuildTastes;
      [*] = ;            ExecuteState('MakeBuildTaste');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pRequiredBuildGroups : Integer = ParserSelectByHandleByKey(pInnerBuild, 'RequiredBuildGroups');
      [*] = ;      for i := ParserGetCountByHandle(pRequiredBuildGroups)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pRequiredBuildGroup : Integer = ParserSelectByHandleByIndex(pRequiredBuildGroups, i);
      [*] = ;         var groupID : Integer = ParserGetIntValueByKeyByHandle(pRequiredBuildGroup, 'GroupID');
      [*] = ;
      [*] = ;         IntRegister0 := groupID;
      [*] = ;         ExecuteState('IsFullBuildGroup');
      [*] = ;         var isFull : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;         if not isFull then
      [*] = ;         for j := ParserGetCountByHandle(pInnerBuildings)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, j);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'BuildingID');
      [*] = ;            var grID : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Group');
      [*] = ;
      [*] = ;            if grID = groupID then
      [*] = ;            begin
      [*] = ;               IntRegister0 := id;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;               if not BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := id;
      [*] = ;                  IntRegister1 := taste;
      [*] = ;                  IntRegister2 := pBuildTastes;
      [*] = ;                  ExecuteState('MakeBuildTaste');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

