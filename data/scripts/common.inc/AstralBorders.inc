section.begin
   Name = AstralBorders
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\ASTRALBORDERS';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'astral_borders';
      [*] = ;const cRaceName = 'misc';
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
      [*] = ;   if (uPlHandle=0) then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;   
      [*] = ;   var posX, posY, posZ, angle : Float;
      [*] = ;   
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var hexCount : Integer = Round(Sqrt(ParserGetCountByHandle(pStratHexCells)));
      [*] = ;   if (hexCount=0) then
      [*] = ;   hexCount := 8;
      [*] = ;   
      [*] = ;   const HEX_WIDTH = 10.575;
      [*] = ;   const HEX_HEIGHT = 9.35;
      [*] = ;   
      [*] = ;   var width : Float = HEX_WIDTH*hexCount+HEX_WIDTH/2;
      [*] = ;   
      [*] = ;   var scale : Float = (HEX_WIDTH/12)*(hexCount+4)*2;
      [*] = ;   var hexMapSize : Float = (hexCount+4)*HEX_WIDTH;
      [*] = ;   
      [*] = ;   var lX : Float = -(GetMapWidth/2)+15-hexCount*(2.25);
      [*] = ;   var tY : Float = -(GetMapHeight/2)+15-8*hexCount;//4.375
      [*] = ;   
      [*] = ;   
      [*] = ;   procedure SetupBehaviour(const goHandle : Integer);
      [*] = ;   begin
      [*] = ;      var scaleX : Float = GetGameObjectScaleXByHandle(goHandle);
      [*] = ;      var scaleY : Float = GetGameObjectScaleYByHandle(goHandle);
      [*] = ;      var scaleZ : Float = GetGameObjectScaleZByHandle(goHandle);
      [*] = ;      var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      var posY : Float = GetGameObjectPositionYByHandle(goHandle);
      [*] = ;      var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;   
      [*] = ;      var behHnd : Integer = BehaviourCreate(goHandle, 'TXMoveRotateWaveBehaviour', true, false);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'OffsetTime', Random);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingAmpX', 0.2);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingAmpY', 0.1);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingFreqX', 0.5);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingFreqY', 2.0);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingFreqZ', 0.5);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WaveTimeX', 2*pi*0.05);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WaveTimeY', 2*pi*0.05);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WaveTimeZ', 2*pi*0.05);
      [*] = ;      //SetBehaviourStringProperty(behHnd, 'WaveSinCosX', 'wscSin');
      [*] = ;      //SetBehaviourStringProperty(behHnd, 'WaveSinCosY', 'wscSin');
      [*] = ;      //SetBehaviourStringProperty(behHnd, 'WaveSinCosZ', 'wscCos');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'WaveSinCosX', 'wscSin');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'WaveSinCosY', 'wscCos');
      [*] = ;      SetBehaviourStringProperty(behHnd, 'WaveSinCosZ', 'wscNone');
      [*] = ;      SetBehaviourBoolProperty(behHnd, 'Enabled', true);
      [*] = ;   
      [*] = ;      var estimateTime : Float = GetBehaviourFloatProperty(behHnd, 'EstimateTime[0]');
      [*] = ;      //Log('EstimateTime : ' + FloatToStr(estimateTime));
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'StartTime[0]', GetCurrentTime-(Random*estimateTime));
      [*] = ;   end;
      [*] = ;   
      [*] = ;   procedure GroupMoveAsChildsToParent(const goHandle : Integer);
      [*] = ;   begin
      [*] = ;      var grHandle : Integer = GetGameObjectGrHandleByHandle(goHandle);
      [*] = ;      if (grHandle<>0) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         for i := GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, i);
      [*] = ;            if (goHnd<>goHandle) then
      [*] = ;            begin
      [*] = ;               GroupRemoveGameObjectByHandle(grHandle, goHnd);
      [*] = ;               GameObjectParentToChildAbsolute(goHnd, goHandle);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var goHandle : Integer;
      [*] = ;   var baseName : String;
      [*] = ;   
      [*] = ;   var i,j : Integer;
      [*] = ;   for i := 0 to 6 do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         0 : begin
      [*] = ;            posX := lX;
      [*] = ;            posZ := tY;
      [*] = ;            angle := -90;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            posX := lX;
      [*] = ;            posZ := tY+hexMapSize;
      [*] = ;            angle := -180;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            posX := lX+hexMapSize;
      [*] = ;            posZ := tY;
      [*] = ;            angle := 0;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            posX := lX+hexMapSize;
      [*] = ;            posZ := tY+hexMapSize;
      [*] = ;            angle := 90;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            posX := lX+hexMapSize;
      [*] = ;            posZ := tY+hexMapSize-10*hexCount;
      [*] = ;            angle := 90;
      [*] = ;         end;
      [*] = ;         5 : begin
      [*] = ;            posX := lX+hexMapSize-10*hexCount;
      [*] = ;            posZ := tY;
      [*] = ;            angle := 0;
      [*] = ;         end;
      [*] = ;         6 : begin
      [*] = ;            posX := lX+10*hexCount;
      [*] = ;            posZ := tY+hexMapSize-hexCount;
      [*] = ;            angle := -180;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      var parentGoHandle : Integer;
      [*] = ;      var doSetupBehaviour : Boolean = False;
      [*] = ;      var doMoveToGroup : Boolean = False;
      [*] = ;      var isParent : Boolean = False;
      [*] = ;      var grHandle : Integer = CreateGroupByPlHandle(uPlHandle, 'custom.group.'+IntToStr(GetPlayerCountOfGroupsByHandle(uPlHandle)));
      [*] = ;      var baseY : Float = -8 * hexCount * 1.1;
      [*] = ;      for j := 0 to 2 do
      [*] = ;      begin
      [*] = ;         case j of
      [*] = ;            0 : begin
      [*] = ;               baseName := 'astral_plane';
      [*] = ;               posY := baseY;
      [*] = ;               doSetupBehaviour := False;
      [*] = ;               doMoveToGroup := False;
      [*] = ;               //doMoveToGroup := True;
      [*] = ;               isParent := True;
      [*] = ;            end;
      [*] = ;            1 : begin
      [*] = ;               baseName := 'astral_plane2';
      [*] = ;               posY := baseY*1.125;
      [*] = ;               doSetupBehaviour := True;
      [*] = ;               doMoveToGroup := False;
      [*] = ;               isParent := False;
      [*] = ;               //isParent := False;
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               baseName := 'astral_plane3';
      [*] = ;               posY := baseY*0.875;
      [*] = ;               doSetupBehaviour := True;
      [*] = ;               doMoveToGroup := False;
      [*] = ;               //isParent := False;
      [*] = ;               isParent := False;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;   
      [*] = ;         if (i<4) or ((i>=4) and (j=1)) then
      [*] = ;         begin
      [*] = ;            if (i>=4) then
      [*] = ;            posY := posY-(1+Random*1.5);
      [*] = ;            goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, baseName, posX, posY{+Random*0.1}, posZ);
      [*] = ;            SetGameObjectUseNoSPCullByHandle(goHandle, True);
      [*] = ;            SetGameObjectScaleByHandle(goHandle, GetGameObjectScaleXByHandle(goHandle)*scale, GetGameObjectScaleYByHandle(goHandle)*scale, GetGameObjectScaleZByHandle(goHandle)*scale);
      [*] = ;            GameObjectRollByHandle(goHandle, angle);
      [*] = ;   
      [*] = ;            if (doSetupBehaviour) then
      [*] = ;            SetupBehaviour(goHandle);
      [*] = ;            if (doMoveToGroup) then
      [*] = ;            GroupAddGameObjectByHandle(grHandle, goHandle);
      [*] = ;            if (isParent) then
      [*] = ;            parentGoHandle := goHandle;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      GroupMoveAsChildsToParent(parentGoHandle);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   //var goIndex : Integer;
      [*] = ;   //for goIndex := GetPlayerGameObjectsCountByHandle(uPlHandle)-1 downto 0 do
      [*] = ;   //begin
      [*] = ;   //   goHandle := GetGameObjectHandleByIndex(goIndex, uPlHandle);
      [*] = ;   //   var posX, posY, posZ : Float;
      [*] = ;   //   posX := GetGameObjectPositionXByHandle(goHandle);
      [*] = ;   //   posY := GetGameObjectPositionYByHandle(goHandle);
      [*] = ;   //   posZ := GetGameObjectPositionZByHandle(goHandle);
      [*] = ;   
      [*] = ;   //   var ScaleX, ScaleY, ScaleZ, ScaleMod : float;
      [*] = ;   //   ScaleX := GetGameObjectScaleXByHandle(goHandle);
      [*] = ;   //   ScaleY := GetGameObjectScaleYByHandle(goHandle);
      [*] = ;   //   ScaleZ := GetGameObjectScaleZByHandle(goHandle);
      [*] = ;   //   ScaleMod := 0.909090909;
      [*] = ;   //   ScaleMod := pow(ScaleMod, 3*0.5);
      [*] = ;   
      [*] = ;   //   SetGameObjectScaleByHandle(goHandle, ScaleX * ScaleMod, ScaleY * ScaleMod, ScaleZ * ScaleMod);
      [*] = ;   //   SetGameObjectTrackPointMoveStepByHandle(goHandle, GetGameObjectTrackPointMoveStepByHandle(goHandle) * ScaleMod);
      [*] = ;   
      [*] = ;   //   var dPosX, dPosY, dPosZ : Float;
      [*] = ;   //   dPosX := lx + (posX-lx)*ScaleMod;
      [*] = ;   //   dPosY := 0 + (posY-0)*ScaleMod;
      [*] = ;   //   dPosZ := ty + (posZ-ty)*ScaleMod;
      [*] = ;   
      [*] = ;   //   SetGameObjectPositionByHandle(goHandle, dPosX, dPosY, dPosZ);
      [*] = ;   //end;
      [*] = ;end;
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

