section.begin
   Name = EventEditorHero
   Code : struct.begin
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var configName : String = GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;const cBtnAccept = 101;
      [*] = ;const cBtnCancel = 102;
      [*] = ;const cBtnMoveToProvince = 103;
      [*] = ;const cBtnEditHero = 104;
      [*] = ;
      [*] = ;procedure GetInputValueToVar(elmPath, elmName : String; var value : String);
      [*] = ;begin
      [*] = ;   var elmParentHnd : Integer = GetGUIElementIndexByNameParent(elmPath+'.'+elmName, _gui_GetLayerI);
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent('text', elmParentHnd);
      [*] = ;   if (elmHnd<>0) and GetGUIElementVisible(elmHnd) then
      [*] = ;   begin
      [*] = ;      var className : String = GetObjectClassNameByHandle(elmHnd);
      [*] = ;      if (SameText(className, 'TXEditControl')) then
      [*] = ;      value := GetGUIElementText(elmHnd);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetInputIntValue(elmPath, elmName : String; value : Integer);
      [*] = ;begin
      [*] = ;   SetGUIElementText(GetGUIElementIndexByNameParent(elmPath+'.'+elmName+'.text', _gui_GetLayerI), IntToStr(value));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalcPlayerGoldGemSettings(player : TEditorPlayer; var gold, gem : Integer);
      [*] = ;begin
      [*] = ;   if (player.customstartres) then
      [*] = ;   begin
      [*] = ;      gold := player.gold;
      [*] = ;      gem := player.gem;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var diffIndex : Integer;
      [*] = ;      if (player.difficulty>=0) then
      [*] = ;      diffIndex := player.difficulty
      [*] = ;      else
      [*] = ;      diffIndex := 3;
      [*] = ;      var pDifficulty : Integer = ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, diffIndex);
      [*] = ;      gold := ParserGetIntValueByKeyByHandle(pDifficulty, 'StartGold');
      [*] = ;      gem := ParserGetIntValueByKeyByHandle(pDifficulty, 'StartGem');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsHeroNameChanged() : Boolean;
      [*] = ;begin
      [*] = ;   var localeName : String = GetLocaleTableListItemByID('hero_names', gMapEditor.players[gGUIEditor.selplayer].heroes[gGUIEditor.selhero].name);
      [*] = ;   var tmpName : String;
      [*] = ;   GetInputValueToVar('heroeditor.dynamic.scroll_layer', 'name', tmpName);
      [*] = ;   Result := not ((localeName=tmpName) or (gMapEditor.players[gGUIEditor.selplayer].heroes[gGUIEditor.selhero].name=tmpName));
      [*] = ;end;
      [*] = ;
      [*] = ;if (status='key') then
      [*] = ;begin
      [*] = ;   var bChanges : Boolean = IsHeroNameChanged();
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent('heroeditor.dynamic.frame.apply', _gui_GetLayerI);
      [*] = ;   SetGUIElementEnabled(elmHnd, bChanges);
      [*] = ;   elmHnd := GetGUIElementIndexByNameParent('heroeditor.dynamic.frame.reset', _gui_GetLayerI);
      [*] = ;   SetGUIElementEnabled(elmHnd, bChanges);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var bProceedPressC : Boolean = False;
      [*] = ;   if (configName='text') then
      [*] = ;   begin
      [*] = ;      var elmName : String = GetGUIElementNameByIndex(GetGUIElementParentByIndex(elmHandle));
      [*] = ;      case elmName of
      [*] = ;         'name' : begin
      [*] = ;            SetGUIEventStateOnKeyDown('EventEditorHero');
      [*] = ;         end;
      [*] = ;         else
      [*] = ;         SetGUIEventStateOnKeyDown('');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (configName<>'') then
      [*] = ;   begin
      [*] = ;      var elmListBoxHandle : Integer = GetGUIElementIndexByNameParent('heroeditor.dynamic.static_scroll_layer.'+configName, _gui_GetLayerI);
      [*] = ;      if (elmListBoxHandle<>0) then
      [*] = ;      begin
      [*] = ;         var itemInd : Integer = GetGUIListBoxItemIndex(elmListBoxHandle);
      [*] = ;         var itemTag : Integer = GetGUIListBoxItemTag(elmListBoxHandle, itemInd);
      [*] = ;         case configName of
      [*] = ;            'selecthero' : begin
      [*] = ;               gGUIEditor.selhero := itemTag;
      [*] = ;               var plHnd : Integer = GetPlayerHandleByIndex(gGUIEditor.selplayer);
      [*] = ;               var goHnd : Integer = GetGameObjectHandleByIndex(gGUIEditor.selhero, plHnd);
      [*] = ;               gIntRegister_MapSelectedUID := GetGameObjectUniqueIdByHandle(goHnd);
      [*] = ;               _editor_AssignHero(gMapEditor.players[gGUIEditor.selplayer].heroes[gGUIEditor.selhero], gMapEditor.temporary.hero);
      [*] = ;               _hero_UpdateHeroHUDs();
      [*] = ;            end;
      [*] = ;            else
      [*] = ;            bProceedPressC := True;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmListBoxHandle := GetGUIElementIndexByNameParent('heroeditor.dynamic.scroll_layer.'+configName, _gui_GetLayerI);
      [*] = ;         if (elmListBoxHandle<>0) then
      [*] = ;         begin
      [*] = ;            var itemInd : Integer = GetGUIListBoxItemIndex(elmListBoxHandle);
      [*] = ;            var itemTag : Integer = GetGUIListBoxItemTag(elmListBoxHandle, itemInd);
      [*] = ;            case configName of
      [*] = ;               'playerid' : begin
      [*] = ;                  gMapEditor.temporary.player.id := itemTag;
      [*] = ;               end;
      [*] = ;               else
      [*] = ;               bProceedPressC := True;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         bProceedPressC := True;
      [*] = ;      end;
      [*] = ;      if (not bProceedPressC) then
      [*] = ;      begin
      [*] = ;         ExecuteState('ShowEditorHero');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   bProceedPressC := True;
      [*] = ;
      [*] = ;   if (sPress='c') and (bProceedPressC) then
      [*] = ;   begin
      [*] = ;      var bChanges : Boolean = IsHeroNameChanged();
      [*] = ;      if (bChanges) then
      [*] = ;      GetInputValueToVar('heroeditor.dynamic.scroll_layer', 'name', gMapEditor.temporary.hero.name);
      [*] = ;      case tag of
      [*] = ;         cBtnMoveToProvince : begin
      [*] = ;            _editor_AssignHeroesToCustomPlayerStruct(gMapEditor.players[gGUIEditor.selplayer], gEditorCustomPlayer);
      [*] = ;            _misc_AssignGlobalVars('gEditorCustomPlayer', 'gEditorCustomPlayerTemporary');
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;            ExecuteState('ShowEditorHero');
      [*] = ;
      [*] = ;            var pProvince : Integer = gGUIEditor.selgridparser;//ParserSelectByHandleByIndex(gHexCells.handle, gGUIEditor.selgrid);
      [*] = ;            if (pProvince<>0) then
      [*] = ;            begin
      [*] = ;               var plHnd : Integer = GetPlayerHandleByIndex(gGUIEditor.selplayer);
      [*] = ;               var goHnd : Integer = GetGameObjectHandleByIndex(gGUIEditor.selhero, plHnd);
      [*] = ;               var cuid : Integer = GetGameObjectIntValueIndByHandle(goHnd, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;               IntRegister0 := pProvince;
      [*] = ;               GameObjectExecuteStateByHandle(goHnd, 'JumpToProvince');
      [*] = ;               SetGameObjectIntValueIndByHandle(goHnd, gc_map_GOStack_MapUnit_iBeforeTargetUID, cuid);
      [*] = ;               _hero_UpdateHeroHUDs();
      [*] = ;               gMapEditor.players[gGUIEditor.selplayer].heroes[gGUIEditor.selhero].provind := gGUIEditor.selgrid;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnEditHero : begin
      [*] = ;            _editor_AssignHeroesToCustomPlayerStruct(gMapEditor.players[gGUIEditor.selplayer], gEditorCustomPlayer);
      [*] = ;            gEditorCustomPlayer.curhero := gGUIEditor.selhero;
      [*] = ;            gEditorCustomPlayerTemporary.curhero := gGUIEditor.selhero;
      [*] = ;            _misc_AssignGlobalVars('gEditorCustomPlayer', 'gEditorCustomPlayerTemporary');
      [*] = ;            gIntRegister_InetHeroMode := 5;
      [*] = ;            ExecuteState('ShowEditorHeroesList');
      [*] = ;         end;
      [*] = ;         cBtnAccept : begin
      [*] = ;            _editor_AssignHero(gMapEditor.temporary.hero, gMapEditor.players[gGUIEditor.selplayer].heroes[gGUIEditor.selhero]);
      [*] = ;            ExecuteState('ShowEditorHero');
      [*] = ;         end;
      [*] = ;         cBtnCancel : begin
      [*] = ;            _editor_AssignHero(gMapEditor.players[gGUIEditor.selplayer].heroes[gGUIEditor.selhero], gMapEditor.temporary.hero);
      [*] = ;            ExecuteState('ShowEditorHero');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

