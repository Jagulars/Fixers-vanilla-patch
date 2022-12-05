section.begin
   Name = DoCleanSafe
   UsedFileName =
   Code : struct.begin
      [*] = ;function GetParserGameObject(goHnd : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserSelectGameObject(goHnd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetStructGameObject(const goHnd : Integer; const structKey : String) : Integer;
      [*] = ;begin
      [*] = ;   var parserHnd : Integer = GetParserGameObject(goHnd);
      [*] = ;   Result := ParserSelectByHandleByKey(parserHnd, structKey);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerBehaviours(ownerHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structBehavioursHnd : Integer = GetStructGameObject(ownerHnd, 'Behaviours');
      [*] = ;   for i:=ParserGetCountByHandle(structBehavioursHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var behHnd : Integer = ParserGetIntValueByIndexByHandle(structBehavioursHnd, i);
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structBehavioursHnd, i));
      [*] = ;      if (behHnd<>0) and (GetDetectClassInstance(behHnd)) then
      [*] = ;      begin
      [*] = ;         BehaviourDestroy(behHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerEffects(ownerHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structEffectsHnd : Integer = GetStructGameObject(ownerHnd, 'Effects');
      [*] = ;   for i:=ParserGetCountByHandle(structEffectsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var effHnd : Integer = ParserGetIntValueByIndexByHandle(structEffectsHnd, i);
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structEffectsHnd, i));
      [*] = ;      if (effHnd<>0) and (GetDetectClassInstance(effHnd)) then
      [*] = ;      begin
      [*] = ;         BehaviourDestroy(effHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerDecals(ownerHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structDecalsHnd : Integer = GetStructGameObject(ownerHnd, 'Decals');
      [*] = ;   for i:=ParserGetCountByHandle(structDecalsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var decalHandle : Integer = ParserGetIntValueByIndexByHandle(structDecalsHnd, i);
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structDecalsHnd, i));
      [*] = ;      if (decalHandle<>0) and (GetDetectClassInstance(decalHandle)) then
      [*] = ;      DestroyDecalByHandle(decalHandle);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearOwnerObjects(ownerHnd : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var structObjectsHnd : Integer = GetStructGameObject(ownerHnd, 'Objects');
      [*] = ;   for i:=ParserGetCountByHandle(structObjectsHnd)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var objHnd : Integer = ParserGetIntValueByIndexByHandle(structObjectsHnd, i);
      [*] = ;      ParserFreeByHandle(ParserSelectByHandleByIndex(structObjectsHnd, i));
      [*] = ;      if (objHnd<>0) and (GetDetectClassInstance(objHnd)) then
      [*] = ;      begin
      [*] = ;         if gc_RecycleFX then
      [*] = ;            _obj_Recycle(objHnd)
      [*] = ;         else
      [*] = ;            GameObjectDestroyByHandle(objHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var ownerHnd : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;if GetIntValueByIndex(gc_GOStack_fx_status) <> 5 then
      [*] = ;begin
      [*] = ;   if GetBoolValueByIndex(gc_GOStack_fx_destroyBehav) then
      [*] = ;      ClearOwnerBehaviours(ownerHnd);
      [*] = ;
      [*] = ;   if GetBoolValueByIndex(gc_GOStack_fx_destroyEffect) then
      [*] = ;      ClearOwnerEffects(ownerHnd);
      [*] = ;
      [*] = ;   if GetBoolValueByIndex(gc_GOStack_fx_destroyDecal) then
      [*] = ;      ClearOwnerDecals(ownerHnd);
      [*] = ;
      [*] = ;   if GetBoolValueByIndex(gc_GOStack_fx_destroyObject) then
      [*] = ;      ClearOwnerObjects(ownerHnd);
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_GOStack_fx_status, 5);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end

