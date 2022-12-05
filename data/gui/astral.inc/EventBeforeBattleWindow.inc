section.begin
   Name = EventBeforeBattleWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'ASTRAL.INC\EVENTBEFOREBATTLEWINDOW';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;procedure FreeBeforeBattleGUIParsers();
      [*] = ;begin
      [*] = ;   _misc_ParserGetOrCreateByKey('pBonusUnits',true);
      [*] = ;   _misc_ParserGetOrCreateByKey('pBonusItems',true);
      [*] = ;   _misc_ParserGetOrCreateByKey('pBonusBuildings',true);
      [*] = ;   _misc_ParserGetOrCreateByKey('pBonusOthers',true);
      [*] = ;   _misc_ParserGetOrCreateByKey('pScrollPosTmp',true);
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;
      [*] = ;const cBtnStartBattleTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnAstralHeroTag = 102;
      [*] = ;
      [*] = ;const cBtnUnitsScrollLeft = 200;
      [*] = ;const cBtnUnitsScrollRight = 201;
      [*] = ;const cBtnItemsScrollLeft = 202;
      [*] = ;const cBtnItemsScrollRight = 203;
      [*] = ;const cBtnBuildingsScrollLeft = 204;
      [*] = ;const cBtnBuildingsScrollRight = 205;
      [*] = ;const cBtnOthersScrollLeft = 206;
      [*] = ;const cBtnOthersScrollRight = 207;
      [*] = ;
      [*] = ;const cBtnUnitsBonusBaseTag = 1000;
      [*] = ;const cBtnItemsBonusBaseTag = 2000;
      [*] = ;const cBtnBuildingsBonusBaseTag = 3000;
      [*] = ;const cBtnOthersBonusBaseTag = 4000;
      [*] = ;
      [*] = ;var elmSliderHandle : Integer;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;   elmSliderHandle := gIntRegister_GUIScrollSliderHandle
      [*] = ;else
      [*] = ;   elmSliderHandle := GetGUIElementParentByIndex(elmHandle);
      [*] = ;var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;
      [*] = ;if (elmName='btnSlider') or (elmName='lineSlider') then
      [*] = ;begin
      [*] = ;   if (status='geMouseDown') then
      [*] = ;   begin
      [*] = ;      gIntRegister_GUIScrollSliderHandle := elmSliderHandle;
      [*] = ;
      [*] = ;      var mX, my : Integer;
      [*] = ;      var x2, y2 : Integer;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      GUIInvalidateParentPositions(elmHandle);
      [*] = ;      GetGUIElementAlignPosition(elmHandle, x2, y2);
      [*] = ;      SetIntValueByName('SliderElementDragX', mX-x2);
      [*] = ;      SetIntValueByName('SliderElementDragY', mY-y2);
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) or ((sPress='d') and (elmName='lineSlider')) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('SliderElementDragX', 14);
      [*] = ;   var sliderValue : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;
      [*] = ;   var maxValue : Integer = GetGUIElementTag(elmSliderHandle);
      [*] = ;   var resInd : Integer = -1;
      [*] = ;   case sliderID of
      [*] = ;      'goldstartamount' : resInd := 0;
      [*] = ;      'gemstartamount' : resInd := 1;
      [*] = ;      'goldincome' : resInd := 2;
      [*] = ;      'gemincome' : resInd := 3;
      [*] = ;   end;
      [*] = ;   if (resInd>=0) then
      [*] = ;   begin
      [*] = ;      var value : Integer = round(sliderValue*maxValue);
      [*] = ;      arrChosenBonuses[resInd][1] := value;
      [*] = ;      
      [*] = ;      var text : String = IntToStr(value);
      [*] = ;      if (value > 0) then
      [*] = ;      text := '+'+text;
      [*] = ;      
      [*] = ;      _gui_SetSliderText(elmSliderHandle, text);
      [*] = ;
      [*] = ;      var energyCostElmHandle : Integer = GetGUIElementIndexByNameParent('energyCost', elmSliderHandle);
      [*] = ;      if (energyCostElmHandle<>0) then
      [*] = ;      begin
      [*] = ;         var pProtBonus : Integer = ParserSelectByHandleByIndex(gPrototypeData.shardBonuses.handle, resInd+1);
      [*] = ;         if (pProtBonus<>0) then
      [*] = ;         begin
      [*] = ;            var energyCost : Integer = _misc_RoundUp(ParserGetFloatValueByKeyByHandle(pProtBonus, 'Price') * value);
      [*] = ;            //var resPrice : Float = ParserGetFloatValueByKeyByHandle(pProtBonus, 'Price');
      [*] = ;            //var price : Integer = _misc_RoundUp(resPrice*sliderValue*maxValue);
      [*] = ;            SetGUIElementText(energyCostElmHandle, IntToStr(energyCost));
      [*] = ;            SetGUIElementTextFormatted(energyCostElmHandle, True);
      [*] = ;            if not GetGUIElementVisible(energyCostElmHandle) then
      [*] = ;               SetGUIElementVisible(energyCostElmHandle, True);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if SameText(key, 'LButton') or SameText(status, 'shortcut') then
      [*] = ;   begin
      [*] = ;      var scrollPosUnits, scrollPosItems, scrollPosBuildings, scrollPosOthers : Integer = 0;
      [*] = ;      var pScrollPosTmp : Integer = _misc_ParserGetOrCreateByKey('pScrollPosTmp',false);
      [*] = ;      if (ParserGetCountByHandle(pScrollPosTmp)=0) then
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits);
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems);
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosBuildings', scrollPosBuildings);
      [*] = ;         ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosOthers', scrollPosOthers);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         scrollPosUnits := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits');
      [*] = ;         scrollPosItems := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems');
      [*] = ;         scrollPosBuildings := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosBuildings');
      [*] = ;         scrollPosOthers := ParserGetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosOthers');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (tag>=cBtnUnitsBonusBaseTag) and (tag<cBtnItemsBonusBaseTag) then
      [*] = ;      begin
      [*] = ;         var pBonusUnits : Integer = _misc_ParserGetOrCreateByKey('pBonusUnits',false);
      [*] = ;         if (ParserGetCountByHandle(pBonusUnits)<>0) then
      [*] = ;         begin
      [*] = ;            var ind : Integer = tag-cBtnUnitsBonusBaseTag;
      [*] = ;            var pBonus : Integer = ParserSelectByHandleByIndex(pBonusUnits, ind);
      [*] = ;            var checked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;            ParserSetBoolValueByKeyByHandle(pBonus, 'Checked', not checked);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag>=cBtnItemsBonusBaseTag) and (tag<cBtnBuildingsBonusBaseTag) then
      [*] = ;      begin
      [*] = ;         var pBonusItems : Integer = _misc_ParserGetOrCreateByKey('pBonusItems',false);
      [*] = ;         if (ParserGetCountByHandle(pBonusItems)<>0) then
      [*] = ;         begin
      [*] = ;            var ind : Integer = tag-cBtnItemsBonusBaseTag;
      [*] = ;            var pBonus : Integer = ParserSelectByHandleByIndex(pBonusItems, ind);
      [*] = ;            var checked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;            ParserSetBoolValueByKeyByHandle(pBonus, 'Checked', not checked);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag>=cBtnBuildingsBonusBaseTag) and (tag<cBtnOthersBonusBaseTag) then
      [*] = ;      begin
      [*] = ;         var pBonusBuildings : Integer = _misc_ParserGetOrCreateByKey('pBonusBuildings',false);
      [*] = ;         if (ParserGetCountByHandle(pBonusBuildings)<>0) then
      [*] = ;         begin
      [*] = ;            var ind : Integer = tag-cBtnBuildingsBonusBaseTag;
      [*] = ;            var pBonus : Integer = ParserSelectByHandleByIndex(pBonusBuildings, ind);
      [*] = ;            var checked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;            ParserSetBoolValueByKeyByHandle(pBonus, 'Checked', not checked);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag>=cBtnOthersBonusBaseTag) and (tag<cBtnOthersBonusBaseTag+1000) then
      [*] = ;      begin
      [*] = ;         var pBonusOthers : Integer = _misc_ParserGetOrCreateByKey('pBonusOthers',false);
      [*] = ;         if (ParserGetCountByHandle(pBonusOthers)<>0) then
      [*] = ;         begin
      [*] = ;            var ind : Integer = tag-cBtnOthersBonusBaseTag;
      [*] = ;            var pBonus : Integer = ParserSelectByHandleByIndex(pBonusOthers, ind);
      [*] = ;            var checked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;            ParserSetBoolValueByKeyByHandle(pBonus, 'Checked', not checked);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      case tag of
      [*] = ;         cBtnUnitsScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits-1);
      [*] = ;         end;
      [*] = ;         cBtnUnitsScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosUnits', scrollPosUnits+1);
      [*] = ;         end;
      [*] = ;         cBtnItemsScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems-1);
      [*] = ;         end;
      [*] = ;         cBtnItemsScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosItems', scrollPosItems+1);
      [*] = ;         end;
      [*] = ;         cBtnBuildingsScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosBuildings', scrollPosBuildings-1);
      [*] = ;         end;
      [*] = ;         cBtnBuildingsScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosBuildings', scrollPosBuildings+1);
      [*] = ;         end;
      [*] = ;         cBtnOthersScrollLeft : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosOthers', scrollPosOthers-1);
      [*] = ;         end;
      [*] = ;         cBtnOthersScrollRight : begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pScrollPosTmp, 'ScrollPosOthers', scrollPosOthers+1);
      [*] = ;         end;
      [*] = ;         cBtnStartBattleTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;            var whd : Integer = 0;
      [*] = ;
      [*] = ;            if tag = gc_gui_hotkey_btnEnter then // temp hack to support old style (before commands)
      [*] = ;            begin
      [*] = ;               whd := _gui_GetWindow('AstralBeforeBattle.start_battle_frame.start_battle');
      [*] = ;               //_log_Values('WHD|E:'+BoolToStr(GetGUIElementEnabled(whd)),whd,0,0,0,0,0);
      [*] = ;               if (whd <> 0) and (not GetGUIElementEnabled(whd)) then
      [*] = ;                  whd := 1
      [*] = ;               else
      [*] = ;                  whd := 0;
      [*] = ;            end;
      [*] = ;            if (gCampaign.arrCampPlayers[0].energy>=gIntRegister_AstralEnergySpend) and (whd = 0) then
      [*] = ;            begin
      [*] = ;               var i : Integer;
      [*] = ;               for i:=4 to gc_MaxPlayerBonus-1 do // 0-3 res sliders
      [*] = ;               begin
      [*] = ;                  arrChosenBonuses[i][0] := 0;
      [*] = ;                  arrChosenBonuses[i][1] := 0;
      [*] = ;               end;
      [*] = ;               var curArrBonusInd : Integer = 4;
      [*] = ;               for i:=0 to 3 do
      [*] = ;               begin
      [*] = ;                  var bonusParserName : String;
      [*] = ;                  case i of
      [*] = ;                     0 : bonusParserName := 'pBonusUnits';
      [*] = ;                     1 : bonusParserName := 'pBonusItems';
      [*] = ;                     2 : bonusParserName := 'pBonusBuildings';
      [*] = ;                     3 : bonusParserName := 'pBonusOthers';
      [*] = ;                  end;
      [*] = ;                  var pBonuses : Integer = _misc_ParserGetOrCreateByKey(bonusParserName,false);
      [*] = ;                  if (ParserGetCountByHandle(pBonuses)<>0) then
      [*] = ;                  begin
      [*] = ;                     var j : Integer;
      [*] = ;                     for j:=0 to ParserGetCountByHandle(pBonuses)-1 do
      [*] = ;                     begin
      [*] = ;                        var pBonus : Integer = ParserSelectByHandleByIndex(pBonuses, j);
      [*] = ;                        var bonusID : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'BonusID');
      [*] = ;                        var bonusValue : Integer = ParserGetIntValueByKeyByHandle(pBonus, 'Value');
      [*] = ;                        var checked : Boolean = ParserGetBoolValueByKeyByHandle(pBonus, 'Checked');
      [*] = ;                        if (checked) then
      [*] = ;                        begin
      [*] = ;                           arrChosenBonuses[curArrBonusInd][0] := bonusID;
      [*] = ;                           arrChosenBonuses[curArrBonusInd][1] := bonusValue;
      [*] = ;                           curArrBonusInd := curArrBonusInd+1;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               FreeBeforeBattleGUIParsers();
      [*] = ;               _gui_RootWindowRemoveWithFade(_gui_GetWindow('AstralBeforeBattle'),gc_gui_FadeTime0_2);
      [*] = ;               GUIExecuteState('CheckAttackShard');
      [*] = ;
      [*] = ;               _gv_SetAstralLock(-1,_log_name);
      [*] = ;               gBoolRegister_ShardBattleStarted := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;            FreeBeforeBattleGUIParsers();
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('AstralBeforeBattle'),gc_gui_FadeTime0_2);
      [*] = ;            GUIExecuteState('CreateControlPanel');
      [*] = ;            GUIExecuteState('DoFadeInInfoPanel');
      [*] = ;
      [*] = ;            _gv_SetAstralLock(-1,_log_name);
      [*] = ;            gIntRegister_CampAttackPlayer := -1;
      [*] = ;            gIntRegister_CampDefendPlayer := -1;
      [*] = ;
      [*] = ;            case _misc_GetTutorialHintStatus of
      [*] = ;               gc_Tutorial_HintEnabled : GUIExecuteState('DestroyTutorial');
      [*] = ;               gc_Tutorial_HintHidden : _misc_SetTutorialHintVisible(true);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnAstralHeroTag : begin
      [*] = ;            GUIExecuteState('CreateAstralHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if (tag>=cBtnUnitsScrollLeft) and (tag<=cBtnOthersScrollRight) then
      [*] = ;         GUIExecuteState('ShowBeforeBattleWindow')
      [*] = ;      else
      [*] = ;         if (tag>=cBtnUnitsBonusBaseTag) and (tag<(cBtnOthersBonusBaseTag+1000)) then
      [*] = ;            GUIExecuteState('ShowBeforeBattleWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

