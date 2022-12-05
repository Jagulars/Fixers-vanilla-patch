section.begin
   Name = map.EventChooseHeroWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.EVENTCHOOSEHEROWINDOW';
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var stringTag : String = GetGUIElementStringTag(elmHandle);
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;if SameText(key, 'LButton') then
      [*] = ;begin
      [*] = ;   if SameText(stringTag, 'choose_defender') then
      [*] = ;   begin
      [*] = ;      if (sPress='d') then
      [*] = ;      begin
      [*] = ;         var elmHnd : Integer = GetGUIElementIndexByNameParent('button_hero', elmHandle);
      [*] = ;         if (elmHnd<>0) then
      [*] = ;         SetGUIElementMaterial(elmHnd, 'map.heroselection.button.pressed')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmHnd := GetGUIElementIndexByNameParent('button_defender', elmHandle);
      [*] = ;            if (elmHnd<>0) then
      [*] = ;            SetGUIElementMaterial(elmHnd, 'icons.52x52.cover.pressed');
      [*] = ;         end;
      [*] = ;         elmHnd := GetGUIElementIndexByNameParent('text_name', elmHandle);
      [*] = ;         SetGUIElementColor(elmHnd, gc_gui_fontcolor_HoverR, gc_gui_fontcolor_HoverG, gc_gui_fontcolor_HoverB, 1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (sPress='u') {or (sPress='c')} then
      [*] = ;      begin
      [*] = ;         var elmHnd : Integer = GetGUIElementIndexByNameParent('button_hero', elmHandle);
      [*] = ;         if (elmHnd<>0) then
      [*] = ;         SetGUIElementMaterial(elmHnd, 'map.heroselection.button.normal')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmHnd := GetGUIElementIndexByNameParent('button_defender', elmHandle);
      [*] = ;            if (elmHnd<>0) then
      [*] = ;               SetGUIElementMaterial(elmHnd, 'icons.52x52.cover.normal');
      [*] = ;         end;
      [*] = ;         elmHnd := GetGUIElementIndexByNameParent('text_name', elmHandle);
      [*] = ;         SetGUIElementColor(elmHnd, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;
      [*] = ;         if (sPress='u') then
      [*] = ;         begin
      [*] = ;            if gIntRegister_MapPickedRitualID > 0 then
      [*] = ;            begin
      [*] = ;               var heroHandle : Integer = tag;
      [*] = ;
      [*] = ;               _gui_PlaySound('rituals', 'ritual'+IntToStr(gIntRegister_MapPickedRitualID));
      [*] = ;               IntRegister0 := gIntRegister_MapSelectedHex;
      [*] = ;               IntRegister1 := gIntRegister_MapPickedRitualID;
      [*] = ;               IntRegister2 := GetGameObjectUniqueIdByHandle(heroHandle);
      [*] = ;               PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'CastRitual');
      [*] = ;
      [*] = ;               IntRegister0 := 5; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;               IntRegister1 := 0; //0 - hide
      [*] = ;               ExecuteState('DoDragElement');
      [*] = ;
      [*] = ;               var elmHudProvHandle : Integer = GetGUIElementTopIndexByName('hudprov');
      [*] = ;               if (elmHudProvHandle<>0) then
      [*] = ;                  SetGUIElementVisible(elmHudProvHandle, True);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var curPlHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;               var curGOHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, curPlHandle);
      [*] = ;               var tUID : Integer = GetGameObjectIntValueIndByHandle(curGOHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;               var pProvince : Integer;
      [*] = ;
      [*] = ;               if curGOHandle <> 0 then
      [*] = ;                  pProvince := _misc_GetProvinceParserByUID(tUID)
      [*] = ;               else
      [*] = ;                  pProvince := gIntRegister_MapBattleProvince;
      [*] = ;
      [*] = ;               if _log then _log_valuesL('PL_HANDLE|GO_HANDLE|TUID|GI_BATPROV|PROV',curPlHandle,curGOHandle,tUID,gIntRegister_MapBattleProvince,pProvince,0);
      [*] = ;               if (gGame.gameType = gc_GameTypeLanShard) and gBoolRegister_MapResolveConflicts and (GetLanMode() = 1) then
      [*] = ;               begin
      [*] = ;                  _gv_SetMapTurnFinished(false,_log_name);
      [*] = ;
      [*] = ;                  var pTmpParser : Integer = _misc_ParserGetOrCreateByKey('mechw_ChooseHero',true);
      [*] = ;                  var provIndex : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTmpParser, 'ProvIndex', provIndex);
      [*] = ;
      [*] = ;                  var heroInd : Integer;
      [*] = ;                  if tag > 0 then
      [*] = ;                     heroInd := GetGameObjectIndexByHandle(tag)
      [*] = ;                  else
      [*] = ;                     heroInd := -1;
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTmpParser, 'Player', gIntRegister_MapMyPlayerIndex);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTmpParser, 'HeroIndex', heroInd);
      [*] = ;
      [*] = ;                  _lan_LanSendParserToServer(gc_LAN_SHARD_CHOOSEHERO, pTmpParser);
      [*] = ;                  GUIExecuteState('map.CloseChooseHeroWindow');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := pProvince;
      [*] = ;                  IntRegister1 := tag;
      [*] = ;                  ExecuteState('map.ProcessChooseHero');
      [*] = ;                  // start battle
      [*] = ;                  {var curPlHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;                  var curGOHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, curPlHandle);
      [*] = ;                  var tUID : Integer = GetGameObjectIntValueIndByHandle(curGOHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;
      [*] = ;                  var pProvince : Integer;
      [*] = ;                  if curGOHandle <> 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := tUID;
      [*] = ;                     StateMachineExecuteState(initMachine, 'GetProvinceParserByUID', 0);
      [*] = ;                     pProvince := IntRegister1;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  pProvince := gIntRegister_MapBattleProvince;
      [*] = ;
      [*] = ;                  var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;                  var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;                  var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;                  var heroHandle : Integer = tag;
      [*] = ;                  var pDefendArmy : Integer;
      [*] = ;
      [*] = ;                  if tag > 0 then
      [*] = ;                  begin
      [*] = ;                     pDefendArmy := ParserSelectGameObject(heroHandle);
      [*] = ;                     //gBoolRegister_IsHumanPlayer := true;
      [*] = ;                     gBoolRegister_IsDefenderBattle := false;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     pDefendArmy := pProvDefender;
      [*] = ;                     //gBoolRegister_IsHumanPlayer := false;
      [*] = ;                     gBoolRegister_IsDefenderBattle := true;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if curGOHandle <> 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := pDefendArmy;
      [*] = ;                     IntRegister1 := heroHandle;
      [*] = ;                     GameObjectExecuteStateByHandle(curGOHandle, 'AttackTargetProvinceArmy');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     //gIntRegister_BattleDefendArmy := pDefendArmy;
      [*] = ;                     //gIntRegister_BattleDefendHeroHandle := heroHandle;
      [*] = ;                     //gIntRegister_BattleDefendPlayer := GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;                     IntRegister0 := pDefendArmy;
      [*] = ;                     IntRegister1 := heroHandle;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'StartRebel');
      [*] = ;                  end;}
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         ExecuteState('map.CloseChooseHeroWindow');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case tag of
      [*] = ;         gc_gui_selectdefender_btnScrollUp, gc_gui_selectdefender_btnScrollDown :
      [*] = ;         begin
      [*] = ;            if (sPress='c') then
      [*] = ;            begin
      [*] = ;               var elementScrollLayer : Integer = GetGUIElementIndexByNameParent('dialog_without_image.scroll_layer', _gui_GetLayerI());
      [*] = ;               var elementScrollUp : Integer = GetGUIElementIndexByNameParent('dialog_without_image.scroll_up', _gui_GetLayerI());
      [*] = ;               var elementScrollDown : Integer = GetGUIElementIndexByNameParent('dialog_without_image.scroll_down', _gui_GetLayerI());
      [*] = ;               //var elementScrollSlider : Integer = GetGUIElementIndexByNameParent('dialog_without_image.scroll_slider', _gui_GetLayerI());
      [*] = ;
      [*] = ;               var elmChildrenCount : Integer = GetGUIElementChildrenCount(elementScrollLayer)-2;
      [*] = ;               var scrollStep : Float = 58/((elmChildrenCount-3)*58);
      [*] = ;               var elementScroll : Integer = GetGUIElementVScroll(elementScrollLayer);
      [*] = ;               var curScrollBarPosition : Float = GetGUIScrollBarPosition(elementScroll);
      [*] = ;               var newScrollBarPosition : Float;
      [*] = ;               if (tag=gc_gui_selectdefender_btnScrollUp) then
      [*] = ;               newScrollBarPosition := curScrollBarPosition-scrollStep
      [*] = ;               else
      [*] = ;               newScrollBarPosition := curScrollBarPosition+scrollStep;
      [*] = ;               SetGUIScrollBarPosition(elementScroll, newScrollBarPosition);
      [*] = ;
      [*] = ;               if elmChildrenCount <= 3 then
      [*] = ;               begin
      [*] = ;                  SetGUIElementEnabled(elementScrollUp, false);
      [*] = ;                  SetGUIElementEnabled(elementScrollDown, false);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  SetGUIElementEnabled(elementScrollUp, true);
      [*] = ;                  SetGUIElementEnabled(elementScrollDown, true);
      [*] = ;
      [*] = ;                  if newScrollBarPosition >= 1 then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elementScrollUp, true);
      [*] = ;                     SetGUIElementEnabled(elementScrollDown, false);
      [*] = ;                  end;
      [*] = ;                  if newScrollBarPosition <= 0 then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementEnabled(elementScrollUp, false);
      [*] = ;                     SetGUIElementEnabled(elementScrollDown, true);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var curIndex : Integer = round(newScrollBarPosition/scrollStep);
      [*] = ;               var i : Integer;
      [*] = ;               for i:=0 to elmChildrenCount-1 do
      [*] = ;               begin
      [*] = ;                  var elmHandle : Integer = GetGUIElementIndexByNameParent('dialog_without_image.scroll_points_'+IntToStr(i), _gui_GetLayerI());
      [*] = ;                  if (i<curIndex) or (i>curIndex+2) then
      [*] = ;                  SetGUIElementUserBlend(elmHandle, 0.0)
      [*] = ;                  else
      [*] = ;                  SetGUIElementUserBlend(elmHandle, 1);
      [*] = ;               end;
      [*] = ;               //SetGUIElementPositionY(elementScrollSlider, GetGUIElementPositionY(elementScrollUp)+32+round(newScrollBarPosition*67));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

