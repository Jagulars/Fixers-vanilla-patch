section.begin
   Name = ShardEdgesScenery
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\SHARDEDGESSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'astral_edge_stones';
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
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if uPlHandle = 0 then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   const cEdgesPlayerName = 'astral_edge';
      [*] = ;   var edgesPlHandle : Integer = GetPlayerHandleByName(cEdgesPlayerName);
      [*] = ;
      [*] = ;   var curVisualID : Integer = 0;
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;      curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;      
      [*] = ;   _obj_CleanPruner();
      [*] = ;
      [*] = ;   var graphicsLevel : Integer = gProfile.shardscenery;
      [*] = ;   var pPruner : Integer = _obj_GetPrunerByStateName('ShardScenery', 'ShardEdgesScenery');
      [*] = ;   var pPlayer : Integer = _obj_GetPlayerPruner(pPruner, cPlayerName);
      [*] = ;   var pObjects : Integer = ParserSelectByHandleByKey(pPlayer, 'Objects');
      [*] = ;
      [*] = ;   var i, j, edgeGOHandle, goHandle, index : Integer;
      [*] = ;   var baseName, baseNameNew : String;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(edgesPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      edgeGOHandle := GetGameObjectHandleByIndex(i, edgesPlHandle);
      [*] = ;      baseName := GetGameObjectBaseNameByHandle(edgeGOHandle);
      [*] = ;      
      [*] = ;      if (StrPos('shard_edge', baseName) > 0) then // gotta check name because there are just rocks in there too
      [*] = ;      begin
      [*] = ;         var bRoundedEdge : Boolean = (StrPos('shard_edge3', baseName) > 0);
      [*] = ;         var sPosX : Float = GetGameObjectPositionXByHandle(edgeGOHandle);
      [*] = ;         var sPosY : Float = GetGameObjectPositionYByHandle(edgeGOHandle);
      [*] = ;         var sPosZ : Float = GetGameObjectPositionZByHandle(edgeGOHandle);
      [*] = ;         var sUX : Float = GetGameObjectTransformedVirtualUpXByHandle(edgeGOHandle);
      [*] = ;         var sUY : Float = GetGameObjectTransformedVirtualUpYByHandle(edgeGOHandle);
      [*] = ;         var sUZ : Float = GetGameObjectTransformedVirtualUpZByHandle(edgeGOHandle);
      [*] = ;         var uX, uY, uZ, posX, posY, posZ, xOffset, yOffset : Float;
      [*] = ;
      [*] = ;         if (bRoundedEdge) then
      [*] = ;         VectorRotateY(sUX, sUY, sUZ, 135);
      [*] = ;
      [*] = ;         if (Random < 0.35) and (StrPos('shard_edge1', baseName) > 0) then
      [*] = ;         begin
      [*] = ;            baseNameNew := 'edgeroots';
      [*] = ;            if not _obj_CheckPruning(pObjects, baseNameNew, graphicsLevel) then
      [*] = ;            begin
      [*] = ;               uX := sUX;
      [*] = ;               uY := sUY;
      [*] = ;               uZ := sUZ;
      [*] = ;               VectorRotateY(uX, uY, uZ, -90);
      [*] = ;               var offset : Float = 0.3;
      [*] = ;               posX := sPosX+uX*offset;
      [*] = ;               posZ := sPosZ+uZ*offset;
      [*] = ;               var scale : Float = 1.65;
      [*] = ;               //goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, 'edgeroots'+IntToStr(1+Floor(Random*4)), posX, posY, posZ);
      [*] = ;               goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseNameNew, posX, posY, posZ);
      [*] = ;               if (curVisualID=gc_ShardVisualVulcan) then
      [*] = ;                  SetGameObjectMaterialNameByHandle(goHandle, 'edgeroots_vulcan')
      [*] = ;               else
      [*] = ;               if (curVisualID=gc_ShardVisualIce) then
      [*] = ;                  SetGameObjectMaterialNameByHandle(goHandle, 'edgeroots_ice');
      [*] = ;               SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;               GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (Random < 0.35) and (StrPos('shard_edge1', baseName) > 0) then
      [*] = ;         begin
      [*] = ;            if (Random<0.5) then
      [*] = ;               baseNameNew := 'edgeroots5'
      [*] = ;            else
      [*] = ;               baseNameNew := 'edgeroots6';
      [*] = ;            if not _obj_CheckPruning(pObjects, baseNameNew, graphicsLevel) then
      [*] = ;            begin
      [*] = ;               uX := sUX;
      [*] = ;               uY := sUY;
      [*] = ;               uZ := sUZ;
      [*] = ;               VectorRotateY(uX, uY, uZ, -90);
      [*] = ;               var offset : Float = -0.15;
      [*] = ;               var hOffset : Float = -0.5-Random*4;
      [*] = ;               posX := sPosX+uX*offset;
      [*] = ;               posY := sPosY;
      [*] = ;               posZ := sPosZ+uZ*offset;
      [*] = ;               var scale : Float = (0.9+Random*0.4);
      [*] = ;               //goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, 'edgeroots'+IntToStr(1+Floor(Random*4)), posX, posY, posZ);
      [*] = ;               goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseNameNew, posX, posY, posZ);
      [*] = ;               if (curVisualID=gc_ShardVisualVulcan) then
      [*] = ;                  SetGameObjectMaterialNameByHandle(goHandle, 'edgeroots_vulcan')
      [*] = ;               else
      [*] = ;               if (curVisualID=gc_ShardVisualIce) then
      [*] = ;                  SetGameObjectMaterialNameByHandle(goHandle, 'edgeroots_ice');
      [*] = ;               SetGameObjectPositionByHandle(goHandle, posX, posY+hOffset, posZ);
      [*] = ;               SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;               GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;               SetGameObjectAutoOffsetByHandle(goHandle, False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //Deep down roots
      [*] = ;         var count : Integer = Floor(Random*4);
      [*] = ;         for j := 0 to count-1 do
      [*] = ;         begin
      [*] = ;            //if (Random<1) and (StrPos('shard_edge', baseName) > 0) then
      [*] = ;            begin
      [*] = ;               if (Random<0.5) then
      [*] = ;                  baseNameNew := 'edgeroots5'
      [*] = ;               else
      [*] = ;                  baseNameNew := 'edgeroots6';
      [*] = ;               if not _obj_CheckPruning(pObjects, baseNameNew, graphicsLevel) then
      [*] = ;               begin
      [*] = ;                  posX := sPosX+((0.5-Random)*5);
      [*] = ;                  posZ := sPosZ+((0.5-Random)*5);
      [*] = ;                  uX := sUX;
      [*] = ;                  uY := sUY;
      [*] = ;                  uZ := sUZ;
      [*] = ;                  VectorRotateY(uX, uY, uZ, -90);
      [*] = ;                  var offset : Float;
      [*] = ;                  if (bRoundedEdge) then
      [*] = ;                  offset := 5+Random*2
      [*] = ;                  else
      [*] = ;                  offset := 3+Random*2;
      [*] = ;                  var hOffset : Float = -3.5-Random*2;
      [*] = ;                  posX := posX+uX*offset;
      [*] = ;                  posY := sPosY;
      [*] = ;                  posZ := posZ+uZ*offset;
      [*] = ;                  var scale : Float = (1.3+Random*0.5);
      [*] = ;                  //goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, 'edgeroots'+IntToStr(1+Floor(Random*4)), posX, posY, posZ);
      [*] = ;                  goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseNameNew, posX, posY, posZ);
      [*] = ;                  if (curVisualID=gc_ShardVisualVulcan) then
      [*] = ;                     SetGameObjectMaterialNameByHandle(goHandle, 'edgeroots_vulcan')
      [*] = ;                  else
      [*] = ;                  if (curVisualID=gc_ShardVisualIce) then
      [*] = ;                     SetGameObjectMaterialNameByHandle(goHandle, 'edgeroots_ice');
      [*] = ;                  SetGameObjectPositionByHandle(goHandle, posX, posY+hOffset, posZ);
      [*] = ;                  SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;                  GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;                  SetGameObjectAutoOffsetByHandle(goHandle, False);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (curVisualID=gc_ShardVisualVulcan) then
      [*] = ;         begin
      [*] = ;            //if not bRoundedEdge then
      [*] = ;            if (Random < 0.6) then
      [*] = ;            begin
      [*] = ;               count := Floor(3+Random*6);
      [*] = ;               for j := 0 to count-1 do
      [*] = ;               begin
      [*] = ;                  var randNum : Integer = Floor(Random * 8)+1;
      [*] = ;                  baseNameNew := 'wellstones'+IntToStr(randNum)+'vulcan';
      [*] = ;                  if not _obj_CheckPruning(pObjects, baseNameNew, graphicsLevel) then
      [*] = ;                  begin
      [*] = ;                     posX := sPosX+sUX*((0.5-Random)*4);
      [*] = ;                     posZ := sPosZ+sUZ*((0.5-Random)*4);
      [*] = ;                     uX := sUX;
      [*] = ;                     uY := sUY;
      [*] = ;                     uZ := sUZ;
      [*] = ;                     VectorRotateY(uX, uY, uZ, -90);
      [*] = ;                     if (bRoundedEdge) then
      [*] = ;                     begin
      [*] = ;                        posX := posX+uX*(2.5+Random*1);
      [*] = ;                        posZ := posZ+uZ*(2.5+Random*1);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        posX := posX+uX*(1.25+0*Random*1.5);
      [*] = ;                        posZ := posZ+uZ*(1.25+0*Random*1.5);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     var scale : Float = 0.5+0.8+Random*0.4;
      [*] = ;                     case randNum of
      [*] = ;                        1 : scale:=scale*0.75;
      [*] = ;                        2 : scale:=scale*0.75;
      [*] = ;                        3 : scale:=scale*1.15;
      [*] = ;                        5 : scale:=scale*1.15;
      [*] = ;                        7 : scale:=scale*1.25;
      [*] = ;                        8 : scale:=scale*1.5;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseNameNew, posX, posY, posZ);
      [*] = ;                     SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;                     GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;
      [*] = ;                     if SameText(GetGameObjectMaterialNameByHandle(goHandle), 'shard_edge') then
      [*] = ;                        SetGameObjectMaterialNameByHandle(goHandle, 'shard_edge_vulcan');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            count := Floor(Random*15);
      [*] = ;            for j := 0 to count-1 do
      [*] = ;            begin
      [*] = ;               var randNum : Integer = Floor(Random * 8)+1;
      [*] = ;               baseNameNew := 'wellstones'+IntToStr(randNum);
      [*] = ;               if not _obj_CheckPruning(pObjects, baseNameNew, graphicsLevel) then
      [*] = ;               begin
      [*] = ;                  //if (curVisualID=gc_ShardVisualIce) then // changes in CreateSeasons
      [*] = ;                  //baseNameNew := baseNameNew+'ice';
      [*] = ;                  posX := sPosX+sUX*((0.5-Random)*3);
      [*] = ;                  posZ := sPosZ+sUZ*((0.5-Random)*3);
      [*] = ;                  uX := sUX;
      [*] = ;                  uY := sUY;
      [*] = ;                  uZ := sUZ;
      [*] = ;                  VectorRotateY(uX, uY, uZ, -90);
      [*] = ;                  if (bRoundedEdge) then
      [*] = ;                  begin
      [*] = ;                     posX := posX+uX*(1+0.25+Random*2);
      [*] = ;                     posZ := posZ+uZ*(1+0.25+Random*2);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     posX := posX+uX*(0.25+Random*2);
      [*] = ;                     posZ := posZ+uZ*(0.25+Random*2);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var scale : Float = 0.8+Random*0.4;
      [*] = ;                  goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseNameNew, posX, posY, posZ);
      [*] = ;                  SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;                  GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;
      [*] = ;                  // world rule Deadland
      [*] = ;                  if (curVisualID=gc_ShardVisualDead) then
      [*] = ;                  begin
      [*] = ;                     var goMat : String = GetGameObjectMaterialNameByHandle(goHandle);
      [*] = ;                     if SameText(goMat, 'shard_edge') then
      [*] = ;                     SetGameObjectMaterialNameByHandle(goHandle, 'shard_edge_dark');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (curVisualID=gc_ShardVisualVulcan) then
      [*] = ;                  begin
      [*] = ;                     var goMat : String = GetGameObjectMaterialNameByHandle(goHandle);
      [*] = ;                     if SameText(goMat, 'shard_edge') then
      [*] = ;                     SetGameObjectMaterialNameByHandle(goHandle, 'shard_edge_vulcan');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (curVisualID=gc_ShardVisualIce) then
      [*] = ;                  begin
      [*] = ;                     var goMat : String = GetGameObjectMaterialNameByHandle(goHandle);
      [*] = ;                     if SameText(goMat, 'shard_edge') then
      [*] = ;                     SetGameObjectMaterialNameByHandle(goHandle, 'shard_edge_ice');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
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

