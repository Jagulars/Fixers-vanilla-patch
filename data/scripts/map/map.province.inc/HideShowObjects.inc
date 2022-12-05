section.begin
   Name = HideShowObjects
   Description : struct.begin
      [*] = ;BoolRegister0 - true if show
      [*] = ;When a building is constructed/demolished this makes other objects around it disappear/appear
   struct.end
   Code : struct.begin
      [*] = ;var do_show : Boolean = BoolRegister0;
      [*] = ;var fadeTime : Float = FloatRegister0;
      [*] = ;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var myPatPlName : String = ParserGetValueByKeyByHandle(pProvince, 'PatternPlayer');
      [*] = ;var myPatPlHandle : Integer = GetPlayerHandleByName(myPatPlName);
      [*] = ;var patGroupName : String = 'group.prov.' + IntToStr(dummyUID);
      [*] = ;var grHandle : Integer = GetPlayerGrHandleByHandle(myPatPlHandle, patGroupName);
      [*] = ;if (grHandle=0) then
      [*] = ;   grHandle := CreateGroup(myPatPlName, patGroupName);
      [*] = ;
      [*] = ;const cPlInvisName = 'pattern';
      [*] = ;var grInvisName : String = 'group.invis.'+IntToStr(dummyUID);
      [*] = ;var plInvisHandle : Integer = GetPlayerHandleByName(cPlInvisName);
      [*] = ;var grInvisHandle : Integer = GetPlayerGrHandleByHandle(plInvisHandle, grInvisName);
      [*] = ;if (grInvisHandle=0) then
      [*] = ;   grInvisHandle := CreateGroupByPlHandle(plInvisHandle, grInvisName);
      [*] = ;
      [*] = ;var castle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;var removeRadius : Float;
      [*] = ;if (castle) then
      [*] = ;   removeRadius := gc_map_RemoveObjCastleRadius
      [*] = ;else
      [*] = ;   removeRadius := gc_map_RemoveObjRadius;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;if do_show then
      [*] = ;begin
      [*] = ;   for i := GetGroupCountGameObjectsByHandle(grInvisHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var invisGOHandle : Integer = GetGroupGOHandleByGOIndexByHandle(grInvisHandle, i);
      [*] = ;      var posX : Float = GetGameObjectPositionXByHandle(invisGOHandle);
      [*] = ;      var posZ : Float = GetGameObjectPositionZByHandle(invisGOHandle);
      [*] = ;      var doVisible : Boolean = True;
      [*] = ;      for j:=0 to GetGroupCountGameObjectsByHandle(grHandle)-1 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, j);
      [*] = ;         var posXtmp : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;         var posZtmp : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;         if VectorDistance(posX, 0, posZ, posXtmp, 0, posZtmp) <= removeRadius then
      [*] = ;         begin
      [*] = ;            doVisible := False;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (doVisible) then
      [*] = ;      begin
      [*] = ;         if fadeTime > 0 then
      [*] = ;            _map_ProvDoFadeGameObject(invisGOHandle, GetGameObjectMyHandle(), fadeTime, '', True, False);
      [*] = ;         
      [*] = ;         SetGameObjectVisibleByHandle(invisGOHandle, True);
      [*] = ;         
      [*] = ;         GroupRemoveGameObjectByHandle(grInvisHandle, invisGOHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   for i := GetGroupCountGameObjectsByHandle(grHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGroupGOHandleByGOIndexByHandle(grHandle, i);
      [*] = ;      var posX : Float = GetGameObjectPositionXByHandle(goHandle);
      [*] = ;      var posZ : Float = GetGameObjectPositionZByHandle(goHandle);
      [*] = ;      GetGameObjectsInAreaFloat(posX, posZ, removeRadius+2, cPlInvisName);
      [*] = ;      var arCount : Integer = ArrayGetCount();
      [*] = ;      for j := 0 to arCount-1 do
      [*] = ;      begin
      [*] = ;         var tmpGOHandle : Integer = ArrayGetValueByIndex(j);
      [*] = ;         var tmpGrHandle : Integer = GetGameObjectGrHandleByHandle(tmpGOHandle);
      [*] = ;         if (tmpGrHandle<>grInvisHandle) then
      [*] = ;         begin
      [*] = ;            var posXtmp : Float = GetGameObjectPositionXByHandle(tmpGOHandle);
      [*] = ;            var posZtmp : Float = GetGameObjectPositionZByHandle(tmpGOHandle);
      [*] = ;            if VectorDistance(posX, 0, posZ, posXtmp, 0, posZtmp) <= removeRadius then
      [*] = ;            begin
      [*] = ;               if (gBoolRegister_GeneratorFinished) and (GetGameObjectIsVolumeClippedByHandle(tmpGOHandle)) and (fadeTime > 0) then
      [*] = ;                  _map_ProvDoFadeGameObject(tmpGOHandle, GetGameObjectMyHandle(), fadeTime, 'FadeEffectOnEndReach', False, False)
      [*] = ;               else
      [*] = ;                  SetGameObjectVisibleByHandle(tmpGOHandle, false);
      [*] = ;               GroupAddGameObjectByHandle(grInvisHandle, tmpGOHandle);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
