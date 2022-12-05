section.begin
   Name = CanInnerBuild
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var bCanBuild : Boolean = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanInnerBuild) > 0;
      [*] = ;var bNotification : Boolean = false;
      [*] = ;
      [*] = ;if bCanBuild then
      [*] = ;begin
      [*] = ;   var bInterfacePlayer : Boolean = (GetPlayerHandleInterfaceIO = myPlHandle);
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;            
      [*] = ;   var goldPercent : Integer = Round(gProfile.mesbuildgold * 100);
      [*] = ;   var gemPercent : Integer = Round(gProfile.mesbuildgem * 100);
      [*] = ;   
      [*] = ;   bCanBuild := false;
      [*] = ;   
      [*] = ;   var pInnerBuildings : Integer = gPrototypeData.innerbuildings.handle;
      [*] = ;      
      [*] = ;   var i, pBuild, buildID, buildGold, buildGem : Integer;
      [*] = ;   for i := 1 to ParserGetCountByHandle(pInnerBuildings)-1 do
      [*] = ;   begin
      [*] = ;      pBuild := ParserSelectByHandleByIndex(pInnerBuildings, i);
      [*] = ;      buildID := ParserGetIntValueByKeyByHandle(pBuild, 'BuildingID');
      [*] = ;
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      ExecuteState('GetBuildPrice');
      [*] = ;      buildGold := IntRegister1;
      [*] = ;      buildGem := IntRegister2;
      [*] = ;
      [*] = ;      if ((plGold >= buildGold) or (buildGold = 0)) and ((plGem >= buildGem) or (buildGem = 0)) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := buildID;
      [*] = ;         ExecuteState('IsBuildingAvailable');
      [*] = ;         if BoolRegister0 then
      [*] = ;         begin
      [*] = ;            bCanBuild := true;
      [*] = ;            
      [*] = ;            if bInterfacePlayer then
      [*] = ;            begin 
      [*] = ;               // notify only when the cost is less than a defined percentage of the player's available gold/gem.
      [*] = ;               if ((buildGold = 0) or ((plGold > 0) and (goldPercent > 0) and (Round(buildGold / plGold * 100) <= goldPercent)))
      [*] = ;               and ((buildGem = 0) or ((plGem > 0) and (gemPercent > 0) and (Round(buildGem / plGem * 100) <= gemPercent))) then
      [*] = ;               begin
      [*] = ;                  bNotification := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := bCanBuild;
      [*] = ;BoolRegister1 := bNotification;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
