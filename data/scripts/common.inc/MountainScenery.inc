section.begin
   Name = MountainScenery
   UsedFileName = 
   Description : struct.begin
      [*] = ;No Clear method exists here because it would be difficult to eliminate just the mountain scenery without touching anything else because it's all same pattern-player. 
      [*] = ;Clear method for the whole pattern-player exists in TerrainScenery.inc
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MOUNTAINSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cPatternPlName = 'pattern';
      [*] = ;const cPatternPlRace = 'nature';
      [*] = ;const cPatternPlCMode = 'cmNone';
      [*] = ;
      [*] = ;var patPlHandle : Integer = _plr_GetOrCreatePlayer(cPatternPlName, cPatternPlRace, cPatternPlCMode, False);
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   var i, goHandle, childHandle, pMountain : Integer;
      [*] = ;   var patName : String;
      [*] = ;   var posX, posZ : Float;
      [*] = ;   
      [*] = ;   var machineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle);
      [*] = ;   var pMountains : Integer = ParserSelectByHandleByKey(machineParser, 'MountainPatterns');
      [*] = ;   if pMountains = 0 then
      [*] = ;      pMountains := ParserAddChildByIndex(machineParser, 'MountainPatterns');
      [*] = ;   
      [*] = ;   var count : Integer = ParserGetCountByHandle(pMountains);
      [*] = ;   if count = 0 then
      [*] = ;   begin
      [*] = ;      _map_GenerateSimpleMountainPatterns();
      [*] = ;      count := ParserGetCountByHandle(pMountains);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   _log_gui(_log_name+'[Mountain Patterns Count: '+IntToStr(ParserGetCountByHandle(pMountains))+']');
      [*] = ;   
      [*] = ;   for i := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      pMountain := ParserSelectByHandleByIndex(pMountains, i);
      [*] = ;      patName := ParserGetValueByKeyByHandle(pMountain, 'PatternName');
      [*] = ;
      [*] = ;      posX := Round(ParserGetFloatValueByKeyByHandle(pMountain, 'PosX'));
      [*] = ;      posZ := Round(ParserGetFloatValueByKeyByHandle(pMountain, 'PosZ'));
      [*] = ;
      [*] = ;      StandPattern(patPlHandle, patName, posX, posZ, 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   procedure SetupShardHolesBehaviour(const goHandle : Integer);
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
      [*] = ;      //SetBehaviourFloatProperty(behHnd, 'RollAngle', RollSpeed);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingAmpX', 0.1);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingAmpY', 0.1);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingFreqX', 1.0);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingFreqY', 1.5);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WavingFreqZ', 0.25);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WaveTimeX', 1*pi*0.05);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WaveTimeY', 1*pi*0.05);
      [*] = ;      SetBehaviourFloatProperty(behHnd, 'WaveTimeZ', 1*pi*0.05);
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
      [*] = ;   // randomize astral graphics in the holes in the shard a bit
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(patPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, patPlHandle);
      [*] = ;      if (StrPos('riverwellplane2', GetGameObjectBaseNameByHandle(goHandle)) > 0) then
      [*] = ;      begin
      [*] = ;         GameObjectRollByHandle(goHandle, Random*360);
      [*] = ;         SetupShardHolesBehaviour(goHandle);
      [*] = ;         childHandle := GetGameObjectGOHandleChildByHandle(goHandle, 0);
      [*] = ;         if (childHandle <> 0) then
      [*] = ;         begin
      [*] = ;            SetGameObjectPositionByHandle(childHandle, GetGameObjectPositionXByHandle(childHandle), GetGameObjectPositionYByHandle(childHandle)+1, GetGameObjectPositionZByHandle(childHandle));
      [*] = ;            SetGameObjectScaleByHandle(childHandle, GetGameObjectScaleXByHandle(childHandle)*0.95, GetGameObjectScaleXByHandle(childHandle)*0.95, GetGameObjectScaleXByHandle(childHandle)*0.95);
      [*] = ;            GameObjectRollByHandle(childHandle, Random*360);
      [*] = ;            SetupShardHolesBehaviour(childHandle);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;Create();
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+cPatternPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(patPlHandle))+']', $1000000 or _log_trace);
   struct.end
section.end

