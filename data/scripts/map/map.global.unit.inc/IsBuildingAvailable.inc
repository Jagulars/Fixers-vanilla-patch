section.begin
   Name = IsBuildingAvailable
   Description : struct.begin
      [*] = ;IntRegister0 - BuildingID [| (ExtraBuildingToAddToPlayer's list << $10)]
      [*] = ;OUT: BoolRegister0 - is building available
      [*] = ;OUT: BoolRegister1 - is building impossible to build because of max building count for this building type reached
      [*] = ;OUT: BoolRegister2 - is building built
      [*] = ;OUT: BoolRegister3 - is building ever buildable (if there is no unbuildable buildings in reqs that can't be built cause of fullgroup reqs)
      [*] = ;OUT: BoolRegister4 - is campaign found, for non campaign gametype<>2 will result true
      [*] = ;OUT: BoolRegister5 - are prerequisite buildings built
      [*] = ;OUT: IntRegister0 - bit mask of:
      [*] = ;  &1 - set if built, not set otherwise
      [*] = ;  &2 - impossible to build, bits 2-3 are the reason
      [*] = ;  &0xc - 0 - some requirements are not met yet
      [*] = ;         1 - impossible to build because of rules/already built buildings restrictions (can't be cured)
      [*] = ;         2 - impossible to build because alliance is needed
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var buildID : Integer = (IntRegister0 and $ffff);
      [*] = ;var extraPlayerBuildingID : Integer = ((IntRegister0 and $ffff0000) shr $10);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pPlProvince : Integer = IntRegister0;
      [*] = ;var pPlBuildings : Integer = ParserSelectByHandleByKey(pPlProvince, 'InnerBuildings');
      [*] = ;
      [*] = ;var pBuildGroups : Integer = gPrototypeData.buildGroups.handle;
      [*] = ;var pInnerBuildings : Integer = gPrototypeData.innerBuildings.handle;
      [*] = ;
      [*] = ;var bEverBuildable : Boolean = True;
      [*] = ;type GroupData = class
      [*] = ;no : Integer;
      [*] = ;id : Array [0..$10] of Integer; // HACK - should use define
      [*] = ;end;
      [*] = ;var grp_count : array [0..gc_inner_buildings_max_groups] of GroupData;
      [*] = ;var i_ext,grp_max : Integer;
      [*] = ;
      [*] = ;grp_max := 0;
      [*] = ;for i_ext := 0 to gc_inner_buildings_max_groups-1 do
      [*] = ;begin
      [*] = ;   grp_count[i_ext].no := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsBuildingBuilt(_buildID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var r : Boolean = false;
      [*] = ;   var i : Integer;
      [*] = ;   
      [*] = ;   for i := ParserGetCountByHandle(pPlBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pPlBuilding : Integer = ParserSelectByHandleByIndex(pPlBuildings, i);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pPlBuilding, 'BuildingID');
      [*] = ;      if id = _buildID then
      [*] = ;      begin
      [*] = ;         r := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (not r) and (extraPlayerBuildingID <> 0) and (extraPlayerBuildingID = _buildID) then
      [*] = ;   r := true;
      [*] = ;   Result := r;
      [*] = ;end;
      [*] = ;
      [*] = ;function UnionRestrict(buildID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var unionRace : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iUnion);
      [*] = ;   Result := false;
      [*] = ;   
      [*] = ;   var pInnerBuilding : Integer = ParserSelectByHandleByIndex(pInnerBuildings, buildID);
      [*] = ;   var pBuildAbilities : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'Abilities');
      [*] = ;   
      [*] = ;   for i := ParserGetCountByHandle(pBuildAbilities)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pBuildAbility : Integer = ParserSelectByHandleByIndex(pBuildAbilities, i);
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'AbilityID');
      [*] = ;      
      [*] = ;      if abilID = gc_inner_build_race_alliance then
      [*] = ;      begin
      [*] = ;         var param1 : Integer = ParserGetIntValueByKeyByHandle(pBuildAbility, 'Param1');
      [*] = ;         if param1 <> unionRace then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if not Result then
      [*] = ;   begin
      [*] = ;      var pReqBuildings : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'RequiredBuildings');
      [*] = ;      for i := ParserGetCountByHandle(pReqBuildings)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pReqBuilding : Integer = ParserSelectByHandleByIndex(pReqBuildings, i);
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pReqBuilding, 'BuildingID');
      [*] = ;         
      [*] = ;         if UnionRestrict(id) then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function EverBuildable(_BuildID : Integer;var groupID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   IntRegister0 := _BuildID;
      [*] = ;   MapExecuteState('GetInnerBuildParserByID');
      [*] = ;   var pReqInnerBuilding : Integer = IntRegister1;
      [*] = ;   var reqGroup : Integer = ParserGetIntValueByKeyByHandle(pReqInnerBuilding, 'Group');
      [*] = ;   
      [*] = ;   groupID := reqGroup;
      [*] = ;   if (reqGroup<>0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := (reqGroup or (extraPlayerBuildingID shl $10));
      [*] = ;      ExecuteState('IsFullBuildGroup');
      [*] = ;      
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsCampaignFound(buildID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var bCampaignFound : Boolean;
      [*] = ;   if (gGame.gametype=2) then
      [*] = ;   begin
      [*] = ;      var lordIndex : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;      if (lordIndex<>0) then
      [*] = ;      begin
      [*] = ;         if (gCampaign.arrcamplords[lordIndex].arrbuilds[buildID]=1) then
      [*] = ;         bCampaignFound := True
      [*] = ;         else
      [*] = ;         bCampaignFound := False;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var profileIndex : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;         if (gCampaign.arrcampplayers[profileIndex].arrbuilds[buildID]=1) then
      [*] = ;         bCampaignFound := True
      [*] = ;         else
      [*] = ;         bCampaignFound := False;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   bCampaignFound := True;
      [*] = ;   
      [*] = ;   Result := bCampaignFound;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsScenarioAllowed(buildID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var bAllowed : Boolean = True;
      [*] = ;   
      [*] = ;   if (gScenario.enabled) and (not gScenario.players[myPlIndex].allowedbuildings[buildID]) then
      [*] = ;   bAllowed := False;
      [*] = ;
      [*] = ;   Result := bAllowed;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckBuild(BuildingID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   IntRegister0 := BuildingID;
      [*] = ;   MapExecuteState('GetInnerBuildParserByID');
      [*] = ;   var pInnerBuilding : Integer = IntRegister1;
      [*] = ;   var pRequiredBuildings : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'RequiredBuildings');
      [*] = ;   var grp_id : Integer;
      [*] = ;   //var pRequiredBuildGroups : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'RequiredBuildGroups');
      [*] = ;   
      [*] = ;   // VVK BUGFIX: In a case if building has no requirements, its built status was always 'buildable' even if its group is full
      [*] = ;      // is building already built?
      [*] = ;      if (not IsBuildingBuilt(BuildingID)) and (not EverBuildable(BuildingID,grp_id)) then
      [*] = ;      begin
      [*] = ;         bEverBuildable := False;
      [*] = ;         Result := False;
      [*] = ;      // VVK BUGFIX: END
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var i,j : Integer;
      [*] = ;      var eb,ge : Boolean;
      [*] = ;      
      [*] = ;      for i:=0 to ParserGetCountByHandle(pRequiredBuildings)-1 do
      [*] = ;      begin
      [*] = ;         var pReqBuilding : Integer = ParserSelectByHandleByIndex(pRequiredBuildings, i);
      [*] = ;         var reqID : Integer = ParserGetIntValueByKeyByHandle(pReqBuilding, 'BuildingID');
      [*] = ;         if (CheckBuild(reqID)) and (IsCampaignFound(reqID)) and (IsScenarioAllowed(reqID)) then
      [*] = ;         begin
      [*] = ;            var isBuilt : Boolean = IsBuildingBuilt(reqID);
      [*] = ;            if (not isBuilt) then
      [*] = ;            begin
      [*] = ;               eb := EverBuildable(reqID,grp_id);
      [*] = ;               if grp_id <> 0 then
      [*] = ;               begin
      [*] = ;                  if grp_id > grp_max then
      [*] = ;                  grp_max := grp_id;
      [*] = ;                  
      [*] = ;                  ge := False;
      [*] = ;                  for j :=0 to grp_count[grp_id-1].no-1 do
      [*] = ;                  begin
      [*] = ;                     if grp_count[grp_id-1].id[j] = reqID then
      [*] = ;                     begin
      [*] = ;                        ge := True;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if (not ge) then
      [*] = ;                  begin
      [*] = ;                     grp_count[grp_id-1].id[grp_count[grp_id-1].no] := reqID;
      [*] = ;                     grp_count[grp_id-1].no := grp_count[grp_id-1].no + 1;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (not eb) then
      [*] = ;               begin
      [*] = ;                  bEverBuildable := False;
      [*] = ;                  Result := False;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            bEverBuildable := False;
      [*] = ;            Result := False;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := buildID;
      [*] = ;MapExecuteState('GetInnerBuildParserByID');
      [*] = ;var pInnerBuilding : Integer = IntRegister1;
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;var available : Boolean = true;
      [*] = ;var notFullGroup : Boolean = true;
      [*] = ;var isBuilt : Boolean = false;
      [*] = ;var bRequirementsBuilt : Boolean = false;
      [*] = ;
      [*] = ;var buildGroup : Integer = ParserGetIntValueByKeyByHandle(pInnerBuilding, 'Group');
      [*] = ;
      [*] = ;// check for build group count
      [*] = ;if buildGroup > 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := (buildGroup or (extraPlayerBuildingID shl $10));
      [*] = ;   ExecuteState('IsFullBuildGroup');
      [*] = ;   
      [*] = ;   if BoolRegister0 then
      [*] = ;   notFullGroup := false;
      [*] = ;end;
      [*] = ;
      [*] = ;var pRequiredBuildings : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'RequiredBuildings');
      [*] = ;var pRequiredBuildGroups : Integer = ParserSelectByHandleByKey(pInnerBuilding, 'RequiredBuildGroups');
      [*] = ;
      [*] = ;// VVK BUGFIX: In a case if building has no requirements, its built status was always 'not built'
      [*] = ;   // is building already built?
      [*] = ;for k := ParserGetCountByHandle(pPlBuildings)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pPlBuilding : Integer = ParserSelectByHandleByIndex(pPlBuildings, k);
      [*] = ;   var id : Integer = ParserGetIntValueByKeyByHandle(pPlBuilding, 'BuildingID');
      [*] = ;   if id = buildID then
      [*] = ;   begin
      [*] = ;      isBuilt := true;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if (not isBuilt) and (extraPlayerBuildingID <> 0) and (extraPlayerBuildingID = buildID) then
      [*] = ;   isBuilt := true;
      [*] = ;// VVK BUGFIX: END
      [*] = ;// check for required buildings
      [*] = ;for j := ParserGetCountByHandle(pRequiredBuildings)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pReqBuilding : Integer = ParserSelectByHandleByIndex(pRequiredBuildings, j);
      [*] = ;   var reqID : Integer = ParserGetIntValueByKeyByHandle(pReqBuilding, 'BuildingID');
      [*] = ;   var f : Boolean = false;
      [*] = ;   
      [*] = ;   for k := ParserGetCountByHandle(pPlBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pPlBuilding : Integer = ParserSelectByHandleByIndex(pPlBuildings, k);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pPlBuilding, 'BuildingID');
      [*] = ;      if id = reqID then
      [*] = ;      begin
      [*] = ;         f := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (not f) and (extraPlayerBuildingID <> 0) and (extraPlayerBuildingID = buildID) then
      [*] = ;   f := true;
      [*] = ;   
      [*] = ;   if not f then
      [*] = ;   begin
      [*] = ;      available := false;
      [*] = ;      bRequirementsBuilt := false;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// check for required build groups
      [*] = ;for j := ParserGetCountByHandle(pRequiredBuildGroups)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pReqGroup : Integer = ParserSelectByHandleByIndex(pRequiredBuildGroups, j);
      [*] = ;   var groupID : Integer = ParserGetIntValueByKeyByHandle(pReqGroup, 'GroupID');
      [*] = ;   var pBuildGroup : Integer = ParserSelectByHandleByIndex(pBuildGroups, groupID);
      [*] = ;   
      [*] = ;   var maxGrCount : Integer = ParserGetIntValueByKeyByHandle(pBuildGroup, 'MaxCount');
      [*] = ;   var count : Integer = 0;
      [*] = ;   
      [*] = ;   var pPlBuilding : Integer;
      [*] = ;   var grIndex : Integer;
      [*] = ;   
      [*] = ;   for k := ParserGetCountByHandle(pPlBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pPlBuilding := ParserSelectByHandleByIndex(pPlBuildings, k);
      [*] = ;      grIndex := ParserGetIntValueByKeyByHandle(pPlBuilding, 'Group');
      [*] = ;      if grIndex = groupID then
      [*] = ;      count := count + 1;
      [*] = ;   end;
      [*] = ;   if (extraPlayerBuildingID <> 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := extraPlayerBuildingID;
      [*] = ;      MapExecuteState('GetInnerBuildParserByID');
      [*] = ;      pPlBuilding := IntRegister1;
      [*] = ;      grIndex := ParserGetIntValueByKeyByHandle(pPlBuilding, 'Group');
      [*] = ;      if grIndex = groupID then
      [*] = ;      count := count + 1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if count < maxGrCount then
      [*] = ;   begin
      [*] = ;      available := false;
      [*] = ;      bRequirementsBuilt := false;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var bUnionRestrict : Boolean = UnionRestrict(buildID);
      [*] = ;if bUnionRestrict then
      [*] = ;available := false;
      [*] = ;
      [*] = ;CheckBuild(BuildID);
      [*] = ;
      [*] = ;if bEverBuildable then
      [*] = ;begin
      [*] = ;   for i_ext:=0 to grp_max-1 do
      [*] = ;   begin
      [*] = ;      if grp_count[i_ext].no > 1 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := ((i_ext+1) or (extraPlayerBuildingID shl $10));
      [*] = ;         ExecuteState('IsFullBuildGroup');
      [*] = ;         if (IntRegister0+grp_count[i_ext].no) > IntRegister1 then
      [*] = ;         begin
      [*] = ;            bEverBuildable := False;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var bCampaignFound : Boolean = IsCampaignFound(buildID);
      [*] = ;var bScenarioAllowed : Boolean = IsScenarioAllowed(buildID);
      [*] = ;
      [*] = ;if bCampaignFound then
      [*] = ;bCampaignFound := not bUnionRestrict;
      [*] = ;
      [*] = ;if bScenarioAllowed then
      [*] = ;bScenarioAllowed := not bUnionRestrict;
      [*] = ;
      [*] = ;if (not bCampaignFound) or (not bScenarioAllowed) then
      [*] = ;begin
      [*] = ;   available := False;
      [*] = ;   bEverBuildable := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if isBuilt then
      [*] = ;IntRegister0 := 1
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (not available) or (not notFullGroup) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 2;
      [*] = ;      if bUnionRestrict then
      [*] = ;      IntRegister0 := IntRegister0 or (2 shl 2)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not bEverBuildable) then
      [*] = ;         IntRegister0 := IntRegister0 or (1 shl 2);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   IntRegister0 := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gScenario.enabled) then
      [*] = ;bCampaignFound := bScenarioAllowed;
      [*] = ;
      [*] = ;BoolRegister0 := available;
      [*] = ;BoolRegister1 := notFullGroup;
      [*] = ;BoolRegister2 := isBuilt;
      [*] = ;BoolRegister3 := bEverBuildable;
      [*] = ;BoolRegister4 := bCampaignFound;
      [*] = ;BoolRegister5 := bRequirementsBuilt;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

