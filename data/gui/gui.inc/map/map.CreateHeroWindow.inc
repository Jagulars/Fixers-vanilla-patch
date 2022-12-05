section.begin
   Name = map.CreateHeroWindow
   Description : struct.begin
      [*] = ;gIntRegister_GUICurHeroMode - 0 - both panels, 1 - only units panel, 2 - only spell panel
      [*] = ; see gc_HeroPanel             3 - inventory panel, 4 - spellbook, 5 - hero exchange,
      [*] = ;                              6 - add unit (when not enough space, looks as info panel)
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATEHEROWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleH1, fontHandleN : String;
      [*] = ;
      [*] = ;//const cTempOffsetFromBottom = -50;
      [*] = ;const cTempOffsetFromBottom = 0;
      [*] = ;
      [*] = ;function CreateGUITextHeroParams(ElementName : String; Parent : Integer; textString : String; hAlign, vAlign :String; posX, posY, width, height:Integer; texthAlign, textvAlign, font : String; colorR, colorG, colorB, ColorA : Float) : Integer;
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = _gui_CreateText(ElementName, Parent, textString, hAlign, vAlign, posX, posY, width, height, texthAlign, textvAlign, font, colorR, colorG, colorB, ColorA);
      [*] = ;
      [*] = ;   const cXOffset = 30;
      [*] = ;   const cYOffset = 30;
      [*] = ;   const cSizerX = 10;
      [*] = ;   const cSizerY = -2;
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;   SetGUIElementTextAlign(elmHandle, texthAlign, textvAlign, round(cXOffset*1.5), 0);
      [*] = ;   SetGUIElementAllPositionRect(elmHandle, posX-cXOffset+(cSizerX div 2), posY+(cSizerY div 2), 32+cXOffset+cSizerX, 32+cSizerY);
      [*] = ;   SetGUIElementPressState(elmHandle, 'map.DoOnClickBackground');
      [*] = ;   Result := elmHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetUnitProperty(heroHandle, indProperty : Integer) : Integer;
      [*] = ;begin
      [*] = ;   IntRegister0 := indProperty;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'GetProperty');
      [*] = ;   Result := IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetUnitParserProperty(heroHandle : Integer; prop : String; var res : String);
      [*] = ;begin
      [*] = ;   res := ParserGetValueByKeyByHandle(ParserSelectGameObject(heroHandle), prop);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateHeroSpellSlots(goHandle, Parent, windowMode : Integer);
      [*] = ;begin
      [*] = ;   //Spell close slots
      [*] = ;   var openSlots : Integer;
      [*] = ;   var level : Integer;
      [*] = ;   var matBtnName : String = 'misc.blank.black.alpha.0';
      [*] = ;   var posX, posY, xOff, yOff, tag : Integer;
      [*] = ;   var MaxSlots : Integer;
      [*] = ;   var elmImageHandle, elmBtnHandle : Integer;
      [*] = ;   var i,iLevel : Integer;
      [*] = ;
      [*] = ;   for iLevel := 1 to 4 do
      [*] = ;   begin
      [*] = ;      level := iLevel;
      [*] = ;      IntRegister0 := level;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetSpellSlots');
      [*] = ;      openSlots := IntRegister1;
      [*] = ;
      [*] = ;      if (windowMode=4) then
      [*] = ;      case level of
      [*] = ;         1 : yOff := 97*(level-1);
      [*] = ;         2 : yOff := 97*(level-1);
      [*] = ;         3 : yOff := 97*(level-1)+1;
      [*] = ;         4 : yOff := 97*(level-1);
      [*] = ;      end
      [*] = ;      else // (windowMode=0)
      [*] = ;      case level of
      [*] = ;         1 : yOff := 85*(level-1);
      [*] = ;         2 : yOff := 85*(level-1);
      [*] = ;         3 : yOff := 86*(level-1);
      [*] = ;         4 : yOff := 85*(level-1)+1;
      [*] = ;      end;
      [*] = ;      posX := -212;
      [*] = ;      posY := -164-yOff;
      [*] = ;
      [*] = ;      case iLevel of
      [*] = ;         1 : MaxSlots := 8;
      [*] = ;         2 : MaxSlots := 6;
      [*] = ;         3 : MaxSlots := 4;
      [*] = ;         4 : MaxSlots := 3;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var selSlotLevel, selSlotIndex, selSpellLevel : Integer = 0;
      [*] = ;      var pickedSpellLevel : Integer = 0;
      [*] = ;      if (gIntRegister_MapSelectedSpellSlot<>0) then
      [*] = ;      begin
      [*] = ;         selSlotLevel := gIntRegister_MapSelectedSpellSlot div 10;
      [*] = ;         selSlotIndex := gIntRegister_MapSelectedSpellSlot mod 10;
      [*] = ;
      [*] = ;         IntRegister0 := selSlotLevel;
      [*] = ;         IntRegister1 := selSlotIndex;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetSlotSpell');
      [*] = ;         var pSelSlotSpell : Integer = IntRegister2;
      [*] = ;         var selSpellID : Integer = ParserGetIntValueByKeyByHandle(pSelSlotSpell, 'spellID');
      [*] = ;
      [*] = ;         IntRegister0 := selSpellID;
      [*] = ;         MapExecuteState('GetSpellParserByID');
      [*] = ;         var pSelSpellID : Integer = IntRegister1;
      [*] = ;         selSpellLevel := ParserGetIntValueByKeyByHandle(pSelSpellID, 'Level');
      [*] = ;
      [*] = ;         if (selSpellLevel=0) then //transforming spell level rank from 0 to 1 (analog by unit ranks which is 1-4) - spells can be level=0 (first 3 spells)
      [*] = ;            selSpellLevel := 1;
      [*] = ;
      [*] = ;         if (ParserGetValueByKeyByHandle(pSelSpellID, 'Level')='') then
      [*] = ;            ErrorLogI(_log_name+' selSpellLevel = ""');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gIntRegister_MapPickedSpellID<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gIntRegister_MapPickedSpellID;
      [*] = ;         MapExecuteState( 'GetSpellParserByID');
      [*] = ;         var pPickedSpellID : Integer = IntRegister1;
      [*] = ;         pickedSpellLevel := ParserGetIntValueByKeyByHandle(pPickedSpellID, 'Level');
      [*] = ;
      [*] = ;         if (pickedSpellLevel=0) then //transforming spell level rank from 0 to 1 (analog by unit ranks which is 1-4) - spells can be level=0 (first 3 spells)
      [*] = ;            pickedSpellLevel := 1;
      [*] = ;
      [*] = ;         if (ParserGetValueByKeyByHandle(pPickedSpellID, 'Level')='') then
      [*] = ;            ErrorLogI(_log_name+' pickedSpellLevel = ""');
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to (MaxSlots-1) do
      [*] = ;      begin
      [*] = ;         xOff := 56*i;
      [*] = ;         if (i+1<=openSlots) then
      [*] = ;         begin
      [*] = ;            var matBlank : String = 'misc.blank.black.alpha.0';
      [*] = ;
      [*] = ;            IntRegister0 := level;
      [*] = ;            IntRegister1 := i;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetSlotSpell');
      [*] = ;            var pSlotSpell : Integer = IntRegister2;
      [*] = ;            var spellID : Integer = ParserGetIntValueByKeyByHandle(pSlotSpell, 'spellID');
      [*] = ;
      [*] = ;            IntRegister0 := spellID;
      [*] = ;            MapExecuteState('GetSpellParserByID');
      [*] = ;            var pSpellID : Integer = IntRegister1;
      [*] = ;            var spellLevel : Integer = ParserGetIntValueByKeyByHandle(pSpellID, 'Level');
      [*] = ;
      [*] = ;            var elmSlotHandle : Integer;
      [*] = ;            var swapAvailable : Boolean = True;
      [*] = ;            if (selSlotLevel<spellLevel) then
      [*] = ;               swapAvailable := False;
      [*] = ;
      [*] = ;            var highlight : Boolean = False;
      [*] = ;            var disabled : Boolean = False;
      [*] = ;            if (pickedSpellLevel<>0) then
      [*] = ;            begin
      [*] = ;               if (level>=pickedSpellLevel) and (spellID=0) then
      [*] = ;                  highlight := True
      [*] = ;               else
      [*] = ;                  disabled := True;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (selSpellLevel<>0) then
      [*] = ;            begin
      [*] = ;               if (level>=selSpellLevel) and (swapAvailable) then
      [*] = ;                  highlight := True
      [*] = ;               else
      [*] = ;                  disabled := True;
      [*] = ;            end;
      [*] = ;
      [*] = ;            elmSlotHandle := _gui_CreateImageSimple('heropanel_spell_open_slot', Parent, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX+xOff, posY);
      [*] = ;            SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;
      [*] = ;            IntRegister0 := level;
      [*] = ;            IntRegister1 := i;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetSlotSpell');
      [*] = ;            pSlotSpell := IntRegister2;
      [*] = ;
      [*] = ;            tag := gc_gui_hero_spellslots_btnBaseTag + 10 * level + i;
      [*] = ;            if (pSlotSpell<>0) then
      [*] = ;            begin
      [*] = ;               var spellID : Integer = ParserGetIntValueByKeyByHandle(pSlotSpell, 'SpellID');
      [*] = ;               if spellID<>0 then
      [*] = ;               begin
      [*] = ;                  elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'icon.spell.'+IntToStr(spellID), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;                  if (highlight) then
      [*] = ;                  begin
      [*] = ;                     elmImageHandle := _gui_CreateImageSimple('spell_highlight', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;                     SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('spell_slot', elmSlotHandle, 'spell_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;                  _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipSpell',spellID,$20000,$20000,cFT_SpellTypeDefault,'map.PressSpellSlot','3');
      [*] = ;                  if (disabled) then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementUserBlend(elmImageHandle, 0.3);
      [*] = ;                     SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;                     SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;                     SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  if (level=selSlotLevel) and (i=selSlotIndex) then
      [*] = ;                     SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;                  elmBtnHandle := _gui_CreateButton('dismiss', elmBtnHandle, 'dismiss', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -16, 0, 18, 18, '', 'gui|642', gc_gui_spellpanel_btnDismiss);
      [*] = ;                  SetGUIElementStringTag(elmBtnHandle, 'dismiss');
      [*] = ;                  if gIntRegister_CampaignHeroesPanel > 0 then
      [*] = ;                  begin
      [*] = ;                     SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;                     IntRegister0 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                     IntRegister1 := spellID;
      [*] = ;                     IntRegister2 := $14;
      [*] = ;                     GUIExecuteState('VVK.map.GetHeroAstralTransferPrice');
      [*] = ;                     IntRegister2 := IntRegister0;
      [*] = ;                     IntRegister0 := elmSlotHandle;
      [*] = ;                     IntRegister1 := 3;
      [*] = ;                     GUIExecuteState('vvk.map.DisplayAstralPrice');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (highlight) then
      [*] = ;               begin
      [*] = ;                  elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;                  elmBtnHandle := _gui_CreateButton('heropanel_spell_slot_highlighted', elmSlotHandle, '', matBlank, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 'map.PressSpellSlot', '', tag);
      [*] = ;                  SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;                  SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;                  SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (disabled) then
      [*] = ;               begin
      [*] = ;                  elmSlotHandle := _gui_CreateImageSimple('', Parent, 'heropanel.icon.52x52.slot.empty.disabled', 'halParentLeft', 'valParentTop', posX+xOff, posY);
      [*] = ;                  SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;                  SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, matBlank, 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImageSimple('heropanel_spell_slot_closed', Parent, 'heropanel.icon.52x52.slot.closed', 'halParentLeft', 'valParentTop', posX+xOff, posY);
      [*] = ;            SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;            SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const cEventState = 'map.EventHeroWindow';
      [*] = ;
      [*] = ;var mode : Integer = gIntRegister_GUICurHeroMode;
      [*] = ;var tag : Integer = 0;
      [*] = ;
      [*] = ;var goHandle,goUID : Integer;
      [*] = ;var elmImageHandle  : Integer;
      [*] = ;var elmBtnHandle    : Integer;
      [*] = ;var elmTextHandle   : Integer;
      [*] = ;var posX, posY : Integer;
      [*] = ;var xOff, yOff : Integer;
      [*] = ;var heroParser : Integer;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;var itemSlotPosX : array [0..16] of Integer;
      [*] = ;var itemSlotPosY : array [0..16] of Integer;
      [*] = ;
      [*] = ;var invBaseX : Integer = 0;
      [*] = ;var invBaseY : Integer = 22;
      [*] = ;var itemSize : Integer = 52;
      [*] = ;var itemOffset : Integer = itemSize+4;
      [*] = ;var miniOffset : Integer = 19;
      [*] = ;var tmp_b : Boolean = False;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(gIntRegister_GUICurHeroMode)+']',_log_trace);
      [*] = ;
      [*] = ;if (gIntRegister_GUIActiveHeroUID1=0) then
      [*] = ;   gIntRegister_GUIActiveHeroUID1 := gIntRegister_MapSelectedUID;
      [*] = ;
      [*] = ;if (not gBoolRegister_GUIExchangeSecond) then
      [*] = ;   goHandle := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1)
      [*] = ;else
      [*] = ;   goHandle := GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID2);
      [*] = ;
      [*] = ;if (gBoolRegister_BtnCastleBlink) then _gui_RemoveBlinkElement('btnCastle', tmp_b);
      [*] = ;if (gBoolRegister_BtnEndTurnBlink) then _gui_RemoveBlinkElement('btnEndTurn', tmp_b);
      [*] = ;if (gBoolRegister_BtnRitualBlink) then _gui_RemoveBlinkElement('btnRitual', tmp_b);
      [*] = ;if (gBoolRegister_BtnNextHeroBlink) then _gui_RemoveBlinkElement('btnNextHero', tmp_b);
      [*] = ;if (gBoolRegister_BtnCastleBuildBlink) then _gui_RemoveBlinkElement('btnCastleBuild', tmp_b);
      [*] = ;if (gBoolRegister_BtnStatisticsBlink) then _gui_RemoveBlinkElement('btnStatistics', tmp_b);
      [*] = ;if (gBoolRegister_BtnDiplomacyBlink) then _gui_RemoveBlinkElement('btnDiplomacy', tmp_b);
      [*] = ;
      [*] = ;if (goHandle=0) then
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+' goHandle = 0');
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;case gIntRegister_CurGameMode of
      [*] = ;   gc_GameModeStrategy : begin
      [*] = ;      if _gv_GetMapLock() = 0 then
      [*] = ;         _gv_SetMapLock(100, _log_name);
      [*] = ;   end;
      [*] = ;   gc_GameModeTactics : begin
      [*] = ;      if _gv_GetBattleLock() = 0 then
      [*] = ;         _gv_SetBattleLock(100, _log_name);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;heroParser := ParserSelectGameObject(goHandle);
      [*] = ;goUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;itemSlotPosX[0] := 1*itemOffset;//1,0
      [*] = ;itemSlotPosX[1] := 2*itemOffset;//2,0
      [*] = ;itemSlotPosX[2] := 4*itemOffset;//4,0
      [*] = ;itemSlotPosX[3] := 0;//0,1
      [*] = ;itemSlotPosX[4] := 0;//0,2
      [*] = ;itemSlotPosX[5] := 0;//0,3
      [*] = ;itemSlotPosX[6] := 3*itemOffset;//3,0
      [*] = ;itemSlotPosX[7] := 0;//0,4
      [*] = ;itemSlotPosX[8] := 4*itemOffset;//4,1
      [*] = ;itemSlotPosX[9] := 4*itemOffset;//4,2
      [*] = ;itemSlotPosX[10] := 4*itemOffset;//4,3
      [*] = ;itemSlotPosX[11] := 0;//0,0
      [*] = ;itemSlotPosX[12] := 4*itemOffset;//4,4
      [*] = ;itemSlotPosX[13] := 0;//0,5
      [*] = ;itemSlotPosX[14] := 1*itemOffset;//1,5
      [*] = ;itemSlotPosX[15] := 3*itemOffset;//3,5
      [*] = ;itemSlotPosX[16] := 4*itemOffset;//4,5
      [*] = ;
      [*] = ;itemSlotPosY[0] := 0;
      [*] = ;itemSlotPosY[1] := 0;
      [*] = ;itemSlotPosY[2] := 0;
      [*] = ;itemSlotPosY[3] := 1*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[4] := 2*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[5] := 3*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[6] := 0;
      [*] = ;itemSlotPosY[7] := 4*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[8] := 1*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[9] := 2*itemOffset+miniOffset;
      [*] = ;itemSlotPosY[10] := 3*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[11] := 0;
      [*] = ;itemSlotPosY[12] := 4*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[13] := 5*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[14] := 5*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[15] := 5*itemOffset+miniOffset*2;
      [*] = ;itemSlotPosY[16] := 5*itemOffset+miniOffset*2;
      [*] = ;
      [*] = ;// hero info
      [*] = ;var leader : Integer = GetUnitProperty(goHandle, gc_map_hero_iLeaderProperty);
      [*] = ;var health : Integer = GetUnitProperty(goHandle, gc_map_hero_iHealthProperty);
      [*] = ;var magic  : Integer = GetUnitProperty(goHandle, gc_map_hero_iMagicProperty);
      [*] = ;var initiative : Integer = GetUnitProperty(goHandle, gc_map_hero_iInitiative);
      [*] = ;var siege : Integer = GetUnitProperty(goHandle, gc_map_hero_iSiege);
      [*] = ;var mobility : Integer = GetUnitProperty(goHandle, gc_map_hero_iMobility);
      [*] = ;var life : Integer = GetUnitProperty(goHandle, gc_map_hero_iLife);
      [*] = ;var attack : Integer = GetUnitProperty(goHandle, gc_map_hero_iAttack);
      [*] = ;var counterAttack : Integer = GetUnitProperty(goHandle, gc_map_hero_iCounterAttack);
      [*] = ;var defence : Integer = GetUnitProperty(goHandle, gc_map_hero_iDefence);
      [*] = ;var rangedDefence : Integer = GetUnitProperty(goHandle, gc_map_hero_iRangedDefence);
      [*] = ;var resist : Integer = GetUnitProperty(goHandle, gc_map_hero_iResist);
      [*] = ;var speed : Integer = GetUnitProperty(goHandle, gc_map_hero_iSpeed);
      [*] = ;var rangedAttack : Integer = GetUnitProperty(goHandle, gc_map_hero_iRangedAttack);
      [*] = ;var shootingRange : Integer = GetUnitProperty(goHandle, gc_map_hero_iShootingRange);
      [*] = ;var ammo : Integer = GetUnitProperty(goHandle, gc_map_hero_iAmmo);
      [*] = ;var stamina : Integer = GetUnitProperty(goHandle, gc_map_hero_iStamina);
      [*] = ;var moral : Integer = GetUnitProperty(goHandle, gc_map_hero_iMoral);
      [*] = ;var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;var curHP : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurHP);
      [*] = ;var name : String;
      [*] = ;var unitSlots, MaxSlots, spellSlots : Integer;
      [*] = ;var elmName, matName : String;
      [*] = ;var xOffset : Integer;
      [*] = ;var elmMapHeroPanelInventory : Integer = 0;
      [*] = ;var elmMapHeroPanelLeftSide : Integer = 0;
      [*] = ;var elmMapHeroPanelTabs : Integer = 0;
      [*] = ;var elmMapHeroPanelParams : Integer = 0;
      [*] = ;var elmBtnCloseWindowHandle : Integer = 0;
      [*] = ;var invXOffset : Integer = 0;
      [*] = ;var invYOffset : Integer = 0;
      [*] = ;var invXOffset1 : Integer = 0;
      [*] = ;var invXOffset2 : Integer = 0;
      [*] = ;var invYOffset1 : Integer = 0;
      [*] = ;
      [*] = ;_hero_GetName(goHandle, name);
      [*] = ;gStringRegister_MyHeroName := name;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetClass');
      [*] = ;var classInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;var curExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;IntRegister0 := level;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetNeededExpForLevel');
      [*] = ;var prevExp : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := level+1;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetNeededExpForLevel');
      [*] = ;var nextExp : Integer = IntRegister1;
      [*] = ;
      [*] = ;var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;
      [*] = ;if gIntRegister_MapCurrentShop = 0 then
      [*] = ;   gIntRegister_MapCurrentShop := ParserSelectByHandleByKey(pProvince, 'Shop');
      [*] = ;
      [*] = ;var dummyUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var castleUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var castle : Boolean = False;
      [*] = ;if (castleUID=dummyUID) then
      [*] = ;   castle := True;
      [*] = ;var isGarr, isShop, isLibrary : Boolean = False;
      [*] = ;
      [*] = ;if (not (mode=gc_HeroPanelExtraUnit)) and (not ((mode=gc_HeroPanelBothPanels) and (gIntRegister_GUICurCastleMode=1))) and (gIntRegister_CampaignHeroesPanel = 0) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_GUIActiveHeroUID2<>0) then
      [*] = ;   begin
      [*] = ;      isGarr := True;
      [*] = ;      isShop := True;
      [*] = ;      isLibrary := True;//False;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (castle) then
      [*] = ;   begin
      [*] = ;      isGarr := True;
      [*] = ;      isShop := True;
      [*] = ;
      [*] = ;      var pProvSpells : Integer = ParserSelectByHandleByKey(pProvince, 'SpellLevels');
      [*] = ;      for [MAIN]i:=0 to ParserGetCountByHandle(pProvSpells)-1 do
      [*] = ;      begin
      [*] = ;         var pLevelSpells : Integer = ParserSelectByHandleByIndex(pProvSpells,i);
      [*] = ;         pLevelSpells := ParserSelectByHandleByKey(pLevelSpells, 'Spells');
      [*] = ;
      [*] = ;         var j : Integer;
      [*] = ;         for j:=0 to ParserGetCountByHandle(pProvSpells)-1 do
      [*] = ;         begin
      [*] = ;            var pLevelSpell : Integer = ParserSelectByHandleByIndex(pLevelSpells, j);
      [*] = ;            if (ParserGetIntValueByKeyByHandle(pLevelSpell, 'SpellID') > 0) then
      [*] = ;            begin
      [*] = ;               IsLibrary := True;
      [*] = ;               break(MAIN);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHnd, 'IsGarrison');
      [*] = ;      isGarr := BoolRegister0;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHnd, 'IsShopAndLibrary');
      [*] = ;      isShop := BoolRegister0;
      [*] = ;      isLibrary := BoolRegister1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Numbers',gc_gui_fontsize_default,'',fontHandleN);
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandleH2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // HeaderM
      [*] = ;
      [*] = ;const cFontParamsColorR = gc_gui_fontcolor_HeaderR;
      [*] = ;const cFontParamsColorG = gc_gui_fontcolor_HeaderG;
      [*] = ;const cFontParamsColorB = gc_gui_fontcolor_HeaderB;
      [*] = ;const cFontParamsColorA = 1;
      [*] = ;
      [*] = ;var hAlign, vAlign : String;
      [*] = ;if (gBoolRegister_GUIExchangeSecond) then
      [*] = ;begin
      [*] = ;   elmName := 'map_heropanel_second';
      [*] = ;   hAlign := 'halMiddle';
      [*] = ;   vAlign := 'valBottomHeight';
      [*] = ;   posX := round(639*_gui_RootWindowGetBaseScaleY());
      [*] = ;   posY := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;if ((gIntRegister_GUICurCastleMode=1) and (mode=gc_HeroPanelBothPanels)) then
      [*] = ;begin
      [*] = ;   elmName := 'map_hero_incastle_panel_info';
      [*] = ;   hAlign := 'halLeft';
      [*] = ;   vAlign := 'valBottomHeight';
      [*] = ;   posX := 327;
      [*] = ;   posY := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   elmName := 'map_heropanel';
      [*] = ;   hAlign := 'halMiddle';
      [*] = ;   vAlign := 'valBottomHeight';
      [*] = ;   posX := 0;
      [*] = ;   posY := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmName := 'map_hero_incastle_panel';
      [*] = ;   hAlign := 'halLeft';
      [*] = ;   vAlign := 'valBottomHeight';
      [*] = ;   posX := 327;
      [*] = ;   posY := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   RemoveGUIElement(_gui_GetWindow('blinker_top.blink_castle_btn'));
      [*] = ;SetGUIElementVisible(_gui_GetWindow(elmName), true);
      [*] = ;
      [*] = ;var elmParentHeroPanelHandle : Integer = _gui_GetOrCreateElement(elmName, _gui_GetLayerI(), hAlign, vAlign, posX, posY, 0, 0, Tag);
      [*] = ;SetGUIElementPosition(elmParentHeroPanelHandle, posX, posY);
      [*] = ;
      [*] = ;// hot fix, to support hero window for 768 height resolution only.
      [*] = ;if (_gui_RootWindowGetBaseScaleY() < 1) then
      [*] = ;   SetGUIElementPositionX(elmParentHeroPanelHandle, GetGUIElementPositionX(elmParentHeroPanelHandle)-35);
      [*] = ;
      [*] = ;var elmMapHeroPanelRightSide : Integer = 0;
      [*] = ;
      [*] = ;IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;gIntRegister_MapSelectedHex := IntRegister1;
      [*] = ;if (gIntRegister_CurGameMode = gc_GameModeStrategy) and (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := True;  // !! vanilla !!
      [*] = ;   //_map_gui_AddModalEvent(gc_gui_modalqueue_general,'UpdateInterface','');
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_GUIActiveHeroUID2<>0) then // hero exchange
      [*] = ;   begin
      [*] = ;      if (not gBoolRegister_GUIExchangeSecond) then
      [*] = ;      begin
      [*] = ;         gBoolRegister_GUIExchangeSecond := True;
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;         _gui_RootWindowAddExt(elmParentHeroPanelHandle,cRootWindowModal,0,(cRootWindowAttrModalNoBlack or cRootWindowAttrScaleByY),'');
      [*] = ;         _cmd_RegisterWindowState(elmParentHeroPanelHandle,'VVK.map.HeroWindowCommands',IntToStr(mode));
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _gui_RootWindowAddExt(elmParentHeroPanelHandle,cRootWindowModal,0,cRootWindowAttrScaleByY,'');
      [*] = ;         _cmd_UnRegisterWindowState(elmParentHeroPanelHandle);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var temp_str : String;
      [*] = ;      var whd : Integer;
      [*] = ;
      [*] = ;      whd := 0;
      [*] = ;      case mode of
      [*] = ;         gc_HeroPanelUnitsOnly : begin
      [*] = ;            GUIExecuteState('map.CreateUnitsWindow');
      [*] = ;            whd := _gui_GetWindow('map_unitspanel');
      [*] = ;            if whd <> 0 then
      [*] = ;               _gui_RootWindowAddExt(whd,cRootWindowModal,0,cRootWindowAttrScaleByY,'');
      [*] = ;         end;
      [*] = ;         gc_HeroPanelInventory : begin
      [*] = ;            IntRegister0 := goHandle;
      [*] = ;            GUIExecuteState('map.CreateShopWindow');
      [*] = ;            whd := _gui_GetWindow('map_shoppanel');
      [*] = ;            if whd <> 0 then
      [*] = ;               _gui_RootWindowAddExt(whd,cRootWindowModal,0,cRootWindowAttrScaleByY,'');
      [*] = ;         end;
      [*] = ;         gc_HeroPanelSpellbook : begin
      [*] = ;            GUIExecuteState('map.CreateLibraryWindow');
      [*] = ;            whd := _gui_GetWindow('map_spellpanel');
      [*] = ;            if whd <> 0 then
      [*] = ;               _gui_RootWindowAddExt(whd,cRootWindowModal,0,cRootWindowAttrScaleByY,'');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if whd <> 0 then
      [*] = ;         _cmd_UnRegisterWindowState(whd);
      [*] = ;      if (mode=gc_HeroPanelBothPanels) or (mode=gc_HeroPanelExtraUnit) then
      [*] = ;         _gui_RootWindowAddExt(elmParentHeroPanelHandle,cRootWindowModal,0,cRootWindowAttrScaleByY,'')
      [*] = ;      else
      [*] = ;         _gui_RootWindowAddExt(elmParentHeroPanelHandle,cRootWindowModal,0,(cRootWindowAttrModalNoBlack or cRootWindowAttrScaleByY),'');
      [*] = ;      temp_str := '';
      [*] = ;      _sa_AddAsInt(temp_str,mode);
      [*] = ;      if mode = gc_HeroPanelExtraUnit then
      [*] = ;         _sa_Add(temp_str,'map_heropanel.map_heropanel_leftside.map_heropanel_squad.open_4_0.icon');
      [*] = ;      _cmd_RegisterWindowState(elmParentHeroPanelHandle,'VVK.map.HeroWindowCommands',temp_str);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   _gui_RootWindowAddExt(elmParentHeroPanelHandle,cRootWindowActive,0,cRootWindowAttrScaleByY,'');
      [*] = ;   if mode = gc_HeroPanelBothPanels then
      [*] = ;      _cmd_RegisterWindowState(elmParentHeroPanelHandle,'VVK.map.HeroWindowCommands',IntToStr(mode));
      [*] = ;end;
      [*] = ;
      [*] = ;if (mode=gc_HeroPanelBothPanels) or (mode=gc_HeroPanelExtraUnit) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   begin
      [*] = ;      hAlign := 'halParentMiddle';
      [*] = ;      posX := 316;
      [*] = ;      posY := cTempOffsetFromBottom;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      hAlign := 'halLeft';
      [*] = ;      posX := 956;
      [*] = ;      posY := 0;
      [*] = ;   end;
      [*] = ;   //RightSide
      [*] = ;   elmMapHeroPanelRightSide := _gui_CreateDummy('map_heropanel_rightside', elmParentHeroPanelHandle, hAlign, 'valBottomHeight', posX, posY, 0, 0, Tag);
      [*] = ;   elmImageHandle := _gui_CreateImage('map_heropanel_rightside_background', elmMapHeroPanelRightSide, 'map.heropanel.rightside.background', 'halParentMiddle', 'valParentBottomHeight', 0, 0, 681, 1020, Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   // hot fix, to support hero window for 768 height resolution only.
      [*] = ;   if (gFloat_RootWindowScale<>1) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;         SetGUIElementPositionX(elmMapHeroPanelRightSide, GetGUIElementPositionX(elmMapHeroPanelRightSide)+44)
      [*] = ;      else
      [*] = ;         SetGUIElementPositionX(elmMapHeroPanelRightSide, round(GetGUIElementPositionX(elmMapHeroPanelRightSide)*gFloat_RootWindowScale));
      [*] = ;   end;
      [*] = ;
      [*] = ;   //elmImageHandle := _gui_CreateImageSimple('', elmMapHeroPanelRightSide, 'element.header.strip.629', 'halParentMiddle', 'valParentBottomHeight', -31, -832);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   elmMapHeroPanelInventory := _gui_CreateDummy('map_heropanel_inventory', elmMapHeroPanelRightSide, 'halParentLeft', 'valParentBottomHeight', -735, 12, GetViewerWidth, GetViewerHeight, Tag);
      [*] = ;   //elmImageHandle := _gui_CreateImage('' , elmMapHeroPanelInventory, 'decor.dragon', 'halParentMiddle', 'valParentBottomHeight', 2, -806, 678, 207, Tag);
      [*] = ;
      [*] = ;   var elmMapHeroPanelSpellbook     : Integer = _gui_CreateDummy('map_heropanel_spellbook'     , elmMapHeroPanelRightSide, 'halParentMiddle', 'valParentBottomHeight', 36, 20, 0, 0, Tag);
      [*] = ;   posX := 59;
      [*] = ;   posY := -764;
      [*] = ;   var elmMapHeroPanelJournal       : Integer = _gui_CreateDummy('map_heropanel_journal'       , elmMapHeroPanelRightSide, 'halParentMiddle', 'valParentBottomHeight', posX, posY, 0, 0, Tag);
      [*] = ;   var elmMapHeroPanelResourcePanel : Integer = _gui_CreateDummy('map_heropanel_resourcepanel' , elmMapHeroPanelRightSide, 'halParentMiddle', 'valParentBottomHeight', 0, 0, 0, 0, Tag);
      [*] = ;   CreateHeroSpellSlots(goHandle, elmMapHeroPanelSpellbook, 0);
      [*] = ;
      [*] = ;   posX := -188;
      [*] = ;   posY := -857;
      [*] = ;   var elmText : Integer = _gui_CreateText('', elmMapHeroPanelRightSide, GetLocaleTableListItemByID('gui', '618'), 'halParentLeft', 'valParentBottomHeight', posX, posY, 380, 32, 'halMiddle', 'valTop', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, cFontParamsColorA);
      [*] = ;   {   var elmMapHeroPanelMagic : Integer = _gui_CreateDummy('map_heropanel_magic', elmMapHeroPanelLeftSide,  'halParentMiddle', 'valParentBottomHeight', 0, 0, 0, 0, Tag);
      [*] = ;   posX := -31;
      [*] = ;   posY := -24;
      [*] = ;   elmImageHandle := _gui_CreateImage('map_heropanel_magic_background', elmMapHeroPanelMagic, 'map.heropanel.magic.background', 'halParentMiddle', 'valParentBottomHeight',posX, posY, 584, 531, Tag);}
      [*] = ;
      [*] = ;   if gIntRegister_CampaignHeroesPanel = 0 then
      [*] = ;   begin
      [*] = ;      //Journal Title
      [*] = ;      elmTextHandle  := _gui_CreateText('map_heropanel_journal_title', elmMapHeroPanelJournal, GetLocaleTableListItemByID('gui', '588'), 'halParentLeft', 'valParentBottomHeight', 0, 0, 202, 34, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      var pQuests : Integer = ParserSelectByHandleByKey(heroParser, 'Quests');
      [*] = ;      for i:=0 to ParserGetCountByHandle(pQuests)-1 do
      [*] = ;      begin
      [*] = ;         var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, i);
      [*] = ;         var questIndex : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Index');
      [*] = ;         var questComplete : Boolean = ParserGetBoolValueByKeyByHandle(pQuest, 'Complete');
      [*] = ;         var questProvIndex : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'ProvIndex');
      [*] = ;         var questSiteIndex : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'SiteIndex');
      [*] = ;         var pArProgress : Integer = ParserSelectByHandleByKey(pQuest, 'ArProgress');
      [*] = ;         var questProgress, questProgressMax : Integer = 0;
      [*] = ;         var pQuestProv : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, questProvIndex);
      [*] = ;         IntRegister0 := pQuestProv;
      [*] = ;         MapExecuteState('map.GetProvinceName');
      [*] = ;         var provName : String = StringRegister0;
      [*] = ;         var unitName, spellName, textProgress : String = '';
      [*] = ;         var textQuest : String = GetLocaleTableListItemByID('quest', IntToStr(questIndex));
      [*] = ;
      [*] = ;         var count : Integer = ParserGetCountByHandle(pArProgress);
      [*] = ;         if (count<>1) then
      [*] = ;            ErrorLogI(_log_name+' Quest progress count<>1, this is impossible, check it. count='+IntToStr(count));
      [*] = ;
      [*] = ;         if count > 0 then
      [*] = ;            questProgress := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pArProgress, 0), 'Progress');
      [*] = ;
      [*] = ;         var pPrototypeQuest : Integer = ParserSelectByHandleByIndex(gPrototypeData.quests.handle, questIndex);
      [*] = ;         if (pPrototypeQuest<>0) then
      [*] = ;         begin
      [*] = ;            var questProtypeType : Integer = ParserGetIntValueByKeyByHandle(pPrototypeQuest, 'Type');
      [*] = ;            var pObjectives : Integer = ParserSelectByHandleByKey(pPrototypeQuest, 'Objectives');
      [*] = ;            if (pObjectives<>0) then
      [*] = ;            begin
      [*] = ;               var pObjective : Integer = ParserSelectByHandleByIndex(pObjectives, 0);
      [*] = ;               var count : Integer = ParserGetCountByHandle(pObjectives);
      [*] = ;               if (count<>1) then
      [*] = ;                  ErrorLogI(_log_name+' Quest objectives count<>1, this is impossible, check it. count='+IntToStr(count));
      [*] = ;
      [*] = ;               case questProtypeType of
      [*] = ;                  7 : begin
      [*] = ;                     var pQuestSites : Integer = ParserSelectByHandleByKey(pQuestProv, 'Sites');
      [*] = ;                     var pQuestSite : Integer = ParserSelectByHandleByIndex(pQuestSites, questSiteIndex);
      [*] = ;                     var questData : Integer = ParserGetIntValueByKeyByHandle(pQuestSite, 'QuestData');
      [*] = ;
      [*] = ;                     var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, questData);
      [*] = ;                     var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;                     if (itemType=10) then //spell scroll
      [*] = ;                     begin
      [*] = ;                        var pItemAbilities : Integer = ParserSelectByHandleByKey(pItem, 'Abilities');
      [*] = ;                        var pItemAbility : Integer = ParserSelectByHandleByIndex(pItemAbilities, 0);
      [*] = ;                        var power : Integer = ParserGetIntValueByKeyByHandle(pItemAbility, 'Power');
      [*] = ;                        spellName := GetLocaleTableListItemByID('spell', IntToStr(power+gIntRegister_dbgZ));
      [*] = ;                        textQuest := textQuest+': '{+gc_gui_BreakLine}+spellName;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  8 : begin
      [*] = ;                     var pQuestSites : Integer = ParserSelectByHandleByKey(pQuestProv, 'Sites');
      [*] = ;                     var pQuestSite : Integer = ParserSelectByHandleByIndex(pQuestSites, questSiteIndex);
      [*] = ;                     var tmpLevel : Integer = ParserGetIntValueByKeyByHandle(pQuestSite, 'Level');
      [*] = ;                     unitName := GetLocaleTableListItemByID('unit', IntToStr(tmpLevel));
      [*] = ;                     textQuest := textQuest+': '+unitName;
      [*] = ;                     questProgressMax := ParserGetIntValueByKeyByHandle(pQuestSite, 'QuestData');
      [*] = ;                     textProgress := '('+IntToStr(questProgress)+'/'+IntToStr(questProgressMax)+')';
      [*] = ;                  end;
      [*] = ;                  9 : begin
      [*] = ;                     var questParam : Integer = ParserGetIntValueByKeyByHandle(pObjective, 'Param');
      [*] = ;                     var itemID : Integer = questParam;
      [*] = ;                     IntRegister0 := itemID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'CheckItem');
      [*] = ;                     var bItemExist : Boolean = BoolRegister0;
      [*] = ;                     var itemName : String;
      [*] = ;
      [*] = ;                     var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extitems.handle, itemID);
      [*] = ;                     var itemType : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;                     if (itemType>=10) then
      [*] = ;                     begin
      [*] = ;                        var pItemAbilities : Integer = ParserSelectByHandleByKey(pItem, 'Abilities');
      [*] = ;                        var pItemAbility : Integer = ParserSelectByHandleByIndex(pItemAbilities, 0);
      [*] = ;                        var power : Integer = ParserGetIntValueByKeyByHandle(pItemAbility, 'Power');
      [*] = ;                        case itemType of
      [*] = ;                           10 : itemName := GetLocaleTableListItemByID('spell', IntToStr(power));
      [*] = ;                           11 : itemName := GetLocaleTableListItemByID('defender', IntToStr(power));
      [*] = ;                           12 : itemName := GetLocaleTableListItemByID('outer_build', IntToStr(power));
      [*] = ;                           13 : itemName := GetLocaleTableListItemByID('ritual', IntToStr(power));
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     itemName := GetLocaleTableListItemByID('item', IntToStr(itemID));
      [*] = ;                     textQuest := textQuest+': '+itemName;
      [*] = ;                     //if (bItemExist) then
      [*] = ;                  end;
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     textQuest := textQuest+':';
      [*] = ;                     questProgressMax := ParserGetIntValueByKeyByHandle(pObjective, 'Quantity');
      [*] = ;                     textProgress := '('+IntToStr(questProgress)+'/'+IntToStr(questProgressMax)+')';
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         posX := 62;
      [*] = ;         posY := -764;
      [*] = ;         var elmJournalQuest : Integer = _gui_CreateButton('quest_slot', elmMapHeroPanelJournal, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', -3, 46*i, 202+7, 35+7, cEventState, '', gc_gui_heropanel_QuestBaseTag+questIndex);
      [*] = ;         SetGUIAllowEvents(elmJournalQuest, True, False, False);
      [*] = ;
      [*] = ;         var questHint : String = GetLocaleTableListItemByID('quest', IntToStr(questIndex)+'.description');
      [*] = ;         var elmHandle : Integer = _gui_CreateFrameBorder('', elmJournalQuest, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmJournalQuest), GetGUIElementHeight(elmJournalQuest));
      [*] = ;
      [*] = ;         questHint := StrReplace(questHint, '%prov_name%', provName);
      [*] = ;         questHint := StrReplace(questHint, '%unit_name%', unitName);
      [*] = ;         questHint := StrReplace(questHint, '%unit_num%', IntToStr(questProgressMax));
      [*] = ;         questHint := StrReplace(questHint, '%spell_name%', spellName);
      [*] = ;         SetGUIElementHint(elmJournalQuest, questHint);
      [*] = ;
      [*] = ;         if (questComplete) then
      [*] = ;            textProgress := '('+GetLocaleTableListItemByID('gui', IntToStr(73))+')';
      [*] = ;
      [*] = ;         textQuest := textQuest+' '+textProgress;
      [*] = ;         textProgress := '';
      [*] = ;         var height : Integer = 0;
      [*] = ;         if (textProgress<>'') then
      [*] = ;            height := GetGUIElementHeight(elmJournalQuest) div 2
      [*] = ;         else
      [*] = ;            height := GetGUIElementHeight(elmJournalQuest);
      [*] = ;         textQuest := GetGUIWrappedTextFormatByFont(fontHandleT, textQuest, GetGUIElementWidth(elmJournalQuest));
      [*] = ;         var tmpW, tmpH : Integer;
      [*] = ;         GetGUIElementFontTextFormatRect(fontHandleT, textQuest, tmpW, tmpH);
      [*] = ;         elmTextHandle := _gui_CreateText('questname', elmJournalQuest, textQuest, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmJournalQuest), height, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;         if (textProgress<>'') then
      [*] = ;            elmTextHandle := _gui_CreateText('questprogress', elmJournalQuest, textProgress, 'halParentLeft', 'valParentTop', 0, GetGUIElementHeight(elmJournalQuest) div 2, GetGUIElementWidth(elmJournalQuest), GetGUIElementHeight(elmJournalQuest) div 2, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;
      [*] = ;         var hint : String = 'map.event|494.1';
      [*] = ;         elmBtnHandle := _gui_CreateButton('dismiss_quest', elmJournalQuest, 'dismiss_quest', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -18, 1, 18, 18, cEventState, hint, gc_gui_heropanel_DismissQuestBaseTag+i);
      [*] = ;
      [*] = ;         SetGUIElementStringTag(elmBtnHandle, 'dismiss_quest');
      [*] = ;         SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   invXOffset := 149;
      [*] = ;   invYOffset := 76;
      [*] = ;   invXOffset1 := -8;
      [*] = ;   invXOffset2 := 0;
      [*] = ;   invYOffset1 := 4;
      [*] = ;end;
      [*] = ;
      [*] = ;if (mode<>gc_HeroPanelSpellsOnly) then
      [*] = ;begin
      [*] = ;   //LeftSide
      [*] = ;   if (gIntRegister_GUICurCastleMode=1) and (mode=gc_HeroPanelBothPanels) then
      [*] = ;   begin
      [*] = ;      hAlign := 'halLeft';
      [*] = ;      posX := -5;//634;
      [*] = ;      posY := 0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   begin
      [*] = ;      hAlign := 'halParentMiddle';
      [*] = ;      posX := -290;
      [*] = ;      posY := cTempOffsetFromBottom;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      hAlign := 'halLeft';
      [*] = ;      posX := 634;
      [*] = ;      posY := 0;
      [*] = ;   end;
      [*] = ;   elmMapHeroPanelLeftSide := _gui_CreateDummy('map_heropanel_leftside' , elmParentHeroPanelHandle, hAlign, 'valBottomHeight', posX, posY, 711, 925, Tag);
      [*] = ;
      [*] = ;   // hot fix, to support hero window for 768 height resolution only.
      [*] = ;   if (gFloat_RootWindowScale<>1) then
      [*] = ;      SetGUIElementPositionX(elmMapHeroPanelLeftSide, round(gFloat_RootWindowScale*posX));
      [*] = ;
      [*] = ;   posX := -30;
      [*] = ;   posY := -740;
      [*] = ;   _gui_CreateImage('map_heropanel_portrait_frame', elmMapHeroPanelLeftSide, 'map.heropanel.portrait.frame', 'halParentMiddle', 'valParentBottomHeight',posX, posY, 104, 104, Tag);
      [*] = ;   elmImageHandle := _gui_CreateImage('map_heropanel_portrait' , elmMapHeroPanelLeftSide, ParserGetValueByKeyByHandle(heroParser, 'Portrait'), 'halParentMiddle', 'valParentBottomHeight',posX, posY+2, 109, 109, Tag);
      [*] = ;
      [*] = ;   elmImageHandle := _gui_CreateImage('' , elmMapHeroPanelLeftSide, 'map.heropanel.leftside.background', 'halParentMiddle', 'valParentBottomHeight', 0, 0, 711, 925, Tag);
      [*] = ;   if (mode=gc_HeroPanelBothPanels) and (gIntRegister_GUICurCastleMode>0) then
      [*] = ;       SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   elmImageHandle := _gui_CreateImageSimple('', elmMapHeroPanelLeftSide, 'element.header.strip.629', 'halParentMiddle', 'valParentBottomHeight', -31, -832);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   //tag := gc_gui_hero_unitslots_btnBaseTag;
      [*] = ;   elmBtnHandle := _gui_CreateButton('map_heropanel_portrait', elmMapHeroPanelLeftSide, '', gc_gui_material_blank_0, 'halParentMiddle', 'valParentBottomHeight', posX, posY+2, 109, 109, '', '', 0);
      [*] = ;   _gui_ft_AttachHint_I6(elmBtnHandle,'VVK.FTooltipUnit',cFT_UnitMapHero,goUID,0,0,3,3); // lb=rb, strategy
      [*] = ;   SetGUIElementStringTag(elmBtnHandle, IntToStr(goUID));
      [*] = ;   if gIntRegister_CampaignHeroesPanel > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := 1;
      [*] = ;      GUIExecuteState('VVK.map.GetHeroAstralTransferPrice');
      [*] = ;      IntRegister2 := IntRegister0;
      [*] = ;      IntRegister0 := elmBtnHandle;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      GUIExecuteState('vvk.map.DisplayAstralPrice');
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Create hero skills;
      [*] = ;   var pSkills : Integer = ParserSelectByHandleByKey(heroParser, 'Skills');
      [*] = ;   const maxSkillCount = 11;
      [*] = ;   var sPosX : Integer = 61;
      [*] = ;   var sPosY : Integer = 78;
      [*] = ;   xOff := 477;
      [*] = ;   yOff := 56;
      [*] = ;
      [*] = ;   // hero class
      [*] = ;   posX := sPosX;
      [*] = ;   posY := sPosY;
      [*] = ;   var elmSlotHandle : Integer = _gui_CreateImageSimple('heropanel_skill_open_slot', elmMapHeroPanelLeftSide, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;   SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;   elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'icon.heroclass.'+IntToStr(classInd-1), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;   elmBtnHandle := _gui_CreateButton('skill_slot', elmSlotHandle, 'skill_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', 0);
      [*] = ;   _gui_ft_AttachHint_I2(elmBtnHandle,'VVK.HintHeroClassCallback',classInd,GetGameObjectUniqueIdByHandle(goHandle));
      [*] = ;
      [*] = ;   for i:=0 to maxSkillCount-1 do
      [*] = ;   begin
      [*] = ;      posX := sPosX+((i+1) div 6)*xOff;
      [*] = ;      posY := sPosY+((i+1) mod 6)*yOff;
      [*] = ;      if (i<ParserGetCountByHandle(pSkills)) then
      [*] = ;      begin
      [*] = ;         var pSkill : Integer = ParserSelectByHandleByIndex(pSkills, i);
      [*] = ;         var skillID : Integer =  ParserGetIntValueByKeyByHandle(pSkill, 'SkillID');
      [*] = ;         var level : Integer =  ParserGetIntValueByKeyByHandle(pSkill, 'Level');
      [*] = ;         var skillIconNum : Integer = 1+(skillID-1)*5+(level-1);
      [*] = ;         var elmSlotHandle : Integer = _gui_CreateImageSimple('heropanel_skill_open_slot', elmMapHeroPanelLeftSide, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         //SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;         elmImageHandle := _gui_CreateImage('', elmSlotHandle, 'icon.heroskill.'+IntToStr(skillIconNum), 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;         elmBtnHandle := _gui_CreateButton('skill_slot', elmSlotHandle, 'skill_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', 0);
      [*] = ;         _gui_ft_AttachHint_I3(elmBtnHandle,'VVK.HintHeroSkillCallback',skillID,skillIconNum,1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmImageHandle := _gui_CreateImageSimple('heropanel_skill_slot_closed', elmMapHeroPanelLeftSide, 'heropanel.icon.52x52.slot.closed', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;         SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (mode=gc_HeroPanelBothPanels) or (mode=gc_HeroPanelUnitsOnly) or (mode=gc_HeroPanelExtraUnit) then
      [*] = ;   begin
      [*] = ;      var elmMapHeroPanelSquad : Integer = _gui_CreateDummy('map_heropanel_squad', elmMapHeroPanelLeftSide,  'halParentMiddle', 'valParentBottomHeight', 0, 0, 0, 0, Tag);
      [*] = ;
      [*] = ;      IntRegister0 := goHandle;
      [*] = ;      IntRegister1 := GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;      IntRegister2 := 1;
      [*] = ;      if gIntRegister_CampaignHeroesPanel > 0 then
      [*] = ;         IntRegister2 := IntRegister2 or $100;
      [*] = ;      IntRegister3 := elmMapHeroPanelSquad;
      [*] = ;      GUIExecuteState('map.CreateSquadSlots');
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Not enough space for unit block
      [*] = ;   if (mode=gc_HeroPanelExtraUnit) then
      [*] = ;   begin
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmMapHeroPanelLeftSide, 'element.strip.240', 'halParentLeft', 'valParentTop', 361+gIntRegister_dbgX+gIntRegister_dbgZ, 461-18+gIntRegister_dbgY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmImageHandle, 'gui|641', 'halParentLeft', 'valParentTop', 1, 2, GetGUIElementWidth(elmImageHandle), 32, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) or ((gIntRegister_GUICurCastleMode=1) and ((mode=gc_HeroPanelBothPanels) or (mode=gc_HeroPanelExtraUnit))) then
      [*] = ;   begin
      [*] = ;      hAlign := 'halParentMiddle';
      [*] = ;      posX := 2;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      hAlign := 'halParentLeft';
      [*] = ;      posX := 356;
      [*] = ;   end;
      [*] = ;
      [*] = ;   elmMapHeroPanelParams := _gui_CreateDummy('map_heropanel_params', elmMapHeroPanelLeftSide,  hAlign, 'valParentBottomHeight', posX, 0, 0, 0, Tag);
      [*] = ;
      [*] = ;   //Change hero arrows, if there is more than 1 hero in province
      [*] = ;   var heroCount : Integer = 0;
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;   var curProvUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   var heroCurUID : Integer;
      [*] = ;   var skipUID : Integer;
      [*] = ;   var side : Integer;
      [*] = ;   if (gBoolRegister_GUIExchangeSecond) then
      [*] = ;   begin
      [*] = ;      heroCurUID := gIntRegister_GUIActiveHeroUID2;
      [*] = ;      skipUID := gIntRegister_GUIActiveHeroUID1;
      [*] = ;      side := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      heroCurUID := gIntRegister_GUIActiveHeroUID1;
      [*] = ;      skipUID := gIntRegister_GUIActiveHeroUID2;
      [*] = ;      side := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var heroPrevUID : Integer = 0;
      [*] = ;   var heroNextUID : Integer = 0;
      [*] = ;   var tmpPrevUID : Integer = 0;
      [*] = ;   var heroFirstUID, heroLastUID : Integer = 0;
      [*] = ;   var bFirst, bLast : Boolean = False;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;   begin
      [*] = ;      var tmpGoHnd : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var tmpGoUID : Integer = GetGameObjectUniqueIdByHandle(tmpGoHnd);
      [*] = ;      var dead : Boolean = GetGameObjectBoolValueIndByHandle(tmpGoHnd, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;      var curUID : Integer = GetGameObjectIntValueIndByHandle(tmpGoHnd, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;      if (not dead) and ((curUID=curProvUID) or (gIntRegister_CampaignHeroesPanel > 0)) then
      [*] = ;      begin
      [*] = ;         heroCount := heroCount+1;
      [*] = ;         if (tmpGoUID<>skipUID) then
      [*] = ;         begin
      [*] = ;            if (heroFirstUID=0) then
      [*] = ;               heroFirstUID := tmpGoUID;
      [*] = ;            heroLastUID := tmpGoUID;
      [*] = ;
      [*] = ;            if (tmpGoUID<>heroCurUID) then
      [*] = ;            begin
      [*] = ;               if (heroNextUID=0) and ((heroPrevUID<>0) or (bFirst)) then
      [*] = ;                  heroNextUID := tmpGoUID
      [*] = ;               else
      [*] = ;                  tmpPrevUID := tmpGoUID;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (tmpPrevUID<>0) then
      [*] = ;                  heroPrevUID := tmpPrevUID
      [*] = ;               else
      [*] = ;                  bFirst := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (heroLastUID=heroCurUID) then
      [*] = ;      bLast := True;
      [*] = ;   if (bFirst) then
      [*] = ;      heroPrevUID := heroLastUID
      [*] = ;   else
      [*] = ;      if (bLast) then
      [*] = ;         heroNextUID := heroFirstUID;
      [*] = ;
      [*] = ;   var bAllowHeroExchange : Boolean = (((gIntRegister_GUIActiveHeroUID2<>0) and (heroCount>2)) or ((gIntRegister_GUIActiveHeroUID2=0) and (heroCount>1)));
      [*] = ;
      [*] = ;   var pCurProvince : Integer = _misc_GetProvinceParserByUID(curProvUID);
      [*] = ;   var stable : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Stable');
      [*] = ;   //Params
      [*] = ;   posX := -38; posY := -860; yOff := 155;
      [*] = ;   elmTextHandle  := _gui_CreateText('heroparam_name', elmMapHeroPanelParams, name, 'halParentMiddle', 'valParentBottomHeight', posX, posY, 280, 32, 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 0.8);
      [*] = ;   if (gIntRegister_GUICurCastleMode=0) and (bAllowHeroExchange) and ((gBoolRegister_MapTurnFinished) or (gIntRegister_CampaignHeroesPanel > 0)) then
      [*] = ;   begin
      [*] = ;      var w,h : Integer;
      [*] = ;      GetGUIElementFontTextFormatRect(fontHandleH1,name,w,h);
      [*] = ;      var elmBtnArrowLeftHandle : Integer = _gui_CreateButton('arrowSliderLeft', elmTextHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentMiddle', -20, -4, 0, 0, '', '', gc_gui_heropanel_btnChooseNextHero);
      [*] = ;      SetGUIElementStringTag(elmBtnArrowLeftHandle, IntToStr(heroPrevUID)+'|'+IntToStr(side));
      [*] = ;      SetGUIElementUserBlend(elmBtnArrowLeftHandle, 0.8);
      [*] = ;      var elmBtnArrowRightHandle : Integer = _gui_CreateButton('arrowSliderRight', elmTextHandle, '', 'common.scroller.right', 'halParentRight', 'valParentBottomHeight', 2, 0, 0, 0, '', '', gc_gui_heropanel_btnChoosePrevHero);
      [*] = ;      SetGUIElementStringTag(elmBtnArrowRightHandle, IntToStr(heroNextUID)+'|'+IntToStr(side));
      [*] = ;      SetGUIElementUserBlend(elmBtnArrowRightHandle, 0.8);
      [*] = ;
      [*] = ;      var dragElmHandle : Integer = GetIntValueByName('DragElement');
      [*] = ;      if (dragElmHandle<>0) then
      [*] = ;      begin
      [*] = ;         SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;         SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var text : String = GetLocaleTableListItemByID('hero_class', IntToStr(classInd));
      [*] = ;   elmTextHandle  := _gui_CreateText('heroparam_class_'+IntToStr(classInd-1), elmMapHeroPanelParams, text, 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff, 120, 32, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmTextHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   posX := -150; posY := -782; yOff := 31; xOff := 278;
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_leader', elmMapHeroPanelParams, IntToStr(leader), 'halParentMiddle', 'valParentBottomHeight', posX, posY, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_health', elmMapHeroPanelParams, IntToStr(health), 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_magic', elmMapHeroPanelParams, IntToStr(magic) , 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff*2, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_siege', elmMapHeroPanelParams, IntToStr(siege)      , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_initiative', elmMapHeroPanelParams, IntToStr(initiative) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY+yOff, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   var sMobility : String = IntToStr(mobility);
      [*] = ;   if stable > 0 then
      [*] = ;      sMobility := sMobility + '+' + IntToStr(stable);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_mobility', elmMapHeroPanelParams, sMobility, 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY+yOff*2, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;
      [*] = ;   posX := -100+2; posY := -650; xOff := 89; yOff := 32;
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_life'          , elmMapHeroPanelParams, IntToStr(life) , 'halParentMiddle', 'valParentBottomHeight', posX, posY, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_stamina'       , elmMapHeroPanelParams, IntToStr(stamina)  , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_moral'         , elmMapHeroPanelParams, IntToStr(moral) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff*2, posY, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_speed'         , elmMapHeroPanelParams, IntToStr(speed) , 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_attack'        , elmMapHeroPanelParams, IntToStr(attack)  , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY+yOff, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_counterattack' , elmMapHeroPanelParams, IntToStr(counterattack) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff*2, posY+yOff, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_defence'       , elmMapHeroPanelParams, IntToStr(defence) , 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff*2, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_rangeddefence' , elmMapHeroPanelParams, IntToStr(rangedDefence) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY+yOff*2, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_resist'        , elmMapHeroPanelParams, IntToStr(resist) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff*2, posY+yOff*2, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_rangedattack'  , elmMapHeroPanelParams, IntToStr(rangedAttack) , 'halParentMiddle', 'valParentBottomHeight', posX, posY+yOff*3, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_shootingrange' , elmMapHeroPanelParams, IntToStr(shootingRange) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY+yOff*3, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   elmTextHandle  := CreateGUITextHeroParams('heroparam_ammo'          , elmMapHeroPanelParams, IntToStr(ammo) , 'halParentMiddle', 'valParentBottomHeight', posX+xOff*2, posY+yOff*3, 32, 32, 'halLeft', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;
      [*] = ;   posX := -110; posY := -704; xOff := 156;
      [*] = ;   elmTextHandle := _gui_CreateText('heroparam_level' , elmMapHeroPanelParams, IntToStr(level) , 'halParentMiddle', 'valParentBottomHeight', posX-1, posY, 32, 32, 'halMiddle', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmTextHandle, 'map.DoOnClickBackground');
      [*] = ;   elmTextHandle := _gui_CreateText('heroparam_curlife' , elmMapHeroPanelParams, IntToStr(curHP)  , 'halParentMiddle', 'valParentBottomHeight', posX+xOff-1, posY, 32, 32, 'halMiddle', 'valMiddle', fontHandleN, cFontParamsColorR, cFontParamsColorG, cFontParamsColorB, cFontParamsColorA);
      [*] = ;   SetGUIAllowEvents(elmTextHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmTextHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   elmMapHeroPanelTabs := _gui_CreateDummy('map_heropanel_tabs', elmMapHeroPanelLeftSide,  'halParentMiddle', 'valParentBottomHeight', 0, 0, GetViewerWidth, GetViewerHeight, Tag);
      [*] = ;   if (not gBoolRegister_GUIExchangeSecond) then
      [*] = ;   begin
      [*] = ;      //if (gIntRegister_GUICurCastleMode=0) or ((gIntRegister_GUICurCastleMode=1) and ((mode=0) or (mode=6))) then
      [*] = ;      if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;      begin
      [*] = ;         var elmTabsHandle,dragElmHandle,sh : Integer;
      [*] = ;         var temp_str : String;
      [*] = ;
      [*] = ;         posX := -31;
      [*] = ;         posY := 4;
      [*] = ;         elmTabsHandle := _gui_CreateImageSimple('', elmMapHeroPanelTabs, 'heropanel.tabs.background', 'halParentMiddle', 'valParentBottomHeight', posX, posY);
      [*] = ;         posX := 60;
      [*] = ;         posY := 12;
      [*] = ;         if gIntRegister_CampaignHeroesPanel = 0 then
      [*] = ;         begin
      [*] = ;            elmBtnHandle := _gui_CreateButton('heropanel_tabs_squad', elmTabsHandle, '', 'hero.btn.hiretroops', 'halParentLeft', 'valParentTop', posX, posY, 49, 49, '', '', gc_gui_heropanel_btnSquad);
      [*] = ;            if _cmd_CheckNF('herosquadpanel','','') <> 1 then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;            if (gIntRegister_GUIActiveHeroUID2<>0) then
      [*] = ;               SetGUIElementHint(elmBtnHandle, 'gui|678');
      [*] = ;            if (mode=gc_HeroPanelUnitsOnly) then
      [*] = ;               _gui_CreateImageSimple('', elmBtnHandle, 'hero.btn.hiretroops.pressed', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;
      [*] = ;            elmBtnHandle := _gui_CreateButton('heropanel_tabs_inventory', elmTabsHandle, '', 'hero.btn.equipitems', 'halParentLeft', 'valParentTop', posX+54, posY, 49, 49, '', '', gc_gui_heropanel_btnInventory);
      [*] = ;            if _cmd_CheckNF('heroinventorypanel','','') <> 1 then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;            if (gIntRegister_GUIActiveHeroUID2<>0) then
      [*] = ;               SetGUIElementHint(elmBtnHandle, 'gui|679');
      [*] = ;            if (mode=gc_HeroPanelInventory) then
      [*] = ;               _gui_CreateImageSimple('', elmBtnHandle, 'hero.btn.equipitems.pressed', 'halParentLeft', 'valParentTop', 0,0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('heropanel_tabs_spellbook', elmTabsHandle, '', 'hero.btn.learnspell', 'halParentLeft', 'valParentTop', posX+107, posY, 49, 49, '', '', gc_gui_heropanel_btnSpellbook);
      [*] = ;            if _cmd_CheckNF('herospellbookpanel','','') <> 1 then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;            if (mode=gc_HeroPanelSpellbook) then
      [*] = ;               _gui_CreateImageSimple('', elmBtnHandle, 'hero.btn.learnspell.pressed', 'halParentLeft', 'valParentTop', 0,0);
      [*] = ;
      [*] = ;            elmBtnHandle := _gui_CreateButton('heropanel_tabs_info', elmTabsHandle, '', 'map.radialhero.btn.info', 'halParentLeft', 'valParentTop', posX+160, posY, 49, 49, '', '', gc_gui_heropanel_btnHeroInfo);
      [*] = ;            if _cmd_CheckNF('heroinfopanel','','') <> 1 then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;            if (mode=gc_HeroPanelBothPanels) then
      [*] = ;               _gui_CreateImageSimple('', elmBtnHandle, 'map.radialhero.btn.info.checkon', 'halParentLeft', 'valParentTop', 0,0);
      [*] = ;
      [*] = ;            elmImageHandle := _gui_CreateImage('', elmTabsHandle, 'heropanel.btn.tabspanel.btnplace', 'halParentLeft', 'valParentTop', posX-146, posY-12, 0, 0, 0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('heropanel_dismiss_hero', elmImageHandle, '', 'heropanel.btn.dismiss', 'halParentLeft', 'valParentTop', 27, 27-15, 0, 0, '', '', gc_gui_heropanel_btnDismissHero);
      [*] = ;            SetGUIElementStringTag(elmBtnHandle, IntToStr(goUID));
      [*] = ;            SetGUIElementHint(elmBtnHandle, 'gui|584');
      [*] = ;            if _cmd_CheckNF('herodismisspanel','',IntToStr(goUID)) <> 1 then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            //var whd : Integer;
      [*] = ;
      [*] = ;            SetGUIElementMaterial(elmTabsHandle,gc_gui_material_blank_0);
      [*] = ;            //whd := _gui_CreateImage('info_dummy', elmTabsHandle, 'heropanel.btn.tabspanel.btnplace', 'halParentLeft', 'valParentTop', posX+253-104, posY-12, 0, 0, 0);
      [*] = ;            //whd := _gui_CreateButton('heropanel_tabs_info', whd, '', 'map.radialhero.btn.info', 'halParentLeft', 'valParentTop', 27, 27-15, 0, 0, '', '', gc_gui_heropanel_btnHeroInfo);
      [*] = ;            //if _cmd_CheckNF('heroinfopanel','','') <> 1 then
      [*] = ;            //   SetGUIElementEnabled(whd, false);
      [*] = ;         end;
      [*] = ;
      [*] = ;         elmImageHandle := _gui_CreateImage('exchange_dummy', elmTabsHandle, 'heropanel.btn.tabspanel.btnplace', 'halParentLeft', 'valParentTop', posX+253, posY-12, 0, 0, GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1));
      [*] = ;         dragElmHandle := GetIntValueByName('DragElement');
      [*] = ;         if gIntRegister_GUIActiveHeroUID2 = 0 then
      [*] = ;         begin
      [*] = ;            sh := GetGameObjectHandleByUniqueId(heroNextUID);
      [*] = ;            temp_str := 'gui|676';
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            sh := 0;
      [*] = ;            temp_str := 'gui|677';
      [*] = ;         end;
      [*] = ;         elmBtnHandle := _gui_CreateButton('heropanel_heroexchange', elmImageHandle, '', 'heropanel.btn.heroexchange', 'halParentLeft', 'valParentTop', 27, 27-15, 0, 0, 'map.DoHeroExchange', temp_str, sh);
      [*] = ;
      [*] = ;         if (gIntRegister_GUIActiveHeroUID2<>0) and (dragElmHandle = 0) then
      [*] = ;         begin
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'heropanel.btn.heroexchange.pressed', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (mode=gc_HeroPanelExtraUnit) or (not bAllowHeroExchange) or ((not gBoolRegister_MapTurnFinished) and (gIntRegister_CampaignHeroesPanel = 0))or (dragElmHandle<>0) then
      [*] = ;               SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Life&Exp meters
      [*] = ;   posX := -111; posY := -734; xOff := 155;
      [*] = ;
      [*] = ;   var meterValue : Integer = floor(((curExp - prevExp)/(nextExp - prevExp))*80);
      [*] = ;   if (meterValue>80) then
      [*] = ;      meterValue := 80;
      [*] = ;   elmImageHandle := _gui_CreateImage('' , elmMapHeroPanelParams, 'map.heropanel.exp.meter' , 'halParentMiddle', 'valParentBottomHeight', posX, posY, 8, meterValue, Tag);
      [*] = ;   if (meterValue<=0) then
      [*] = ;      SetGUIElementVisible(elmImageHandle, False);
      [*] = ;
      [*] = ;   meterValue := Floor((curHP/life)*80);
      [*] = ;   if (meterValue>80) then
      [*] = ;      meterValue := 80;
      [*] = ;   elmImageHandle := _gui_CreateImage('', elmMapHeroPanelParams, 'map.heropanel.life.meter', 'halParentMiddle', 'valParentBottomHeight', posX + xOff, posY, 8, meterValue, Tag);
      [*] = ;   if (meterValue=0) then
      [*] = ;      SetGUIElementVisible(elmImageHandle, False);
      [*] = ;
      [*] = ;   elmImageHandle := _gui_CreateImage('heroparam_exp_meter', elmMapHeroPanelParams, 'misc.blank.black.alpha.0' , 'halParentMiddle', 'valParentBottomHeight', posX, posY, 8+6, 80, Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;   elmImageHandle := _gui_CreateImage('heroparam_life_meter', elmMapHeroPanelParams, 'misc.blank.black.alpha.0' , 'halParentMiddle', 'valParentBottomHeight', posX+xOff, posY, 8+6, 80, Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   elmImageHandle := _gui_CreateImage('heroparam_exp_icon', elmMapHeroPanelParams, 'misc.blank.black.alpha.0' , 'halParentMiddle', 'valParentBottomHeight', posX+16, posY, 18, 21, Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;   elmImageHandle := _gui_CreateImage('heroparam_life_icon', elmMapHeroPanelParams, 'misc.blank.black.alpha.0' , 'halParentMiddle', 'valParentBottomHeight', posX+121+16, posY, 20, 23, Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;
      [*] = ;   //Spellbook block
      [*] = ;   if (mode = gc_HeroPanelSpellbook) then
      [*] = ;   begin
      [*] = ;      var elmMapHeroPanelMagic : Integer = _gui_CreateDummy('map_heropanel_magic', elmMapHeroPanelLeftSide,  'halParentMiddle', 'valParentBottomHeight', 0, 0, 0, 0, Tag);
      [*] = ;      posX := -31;
      [*] = ;      posY := -24;
      [*] = ;      elmImageHandle := _gui_CreateImage('map_heropanel_magic_background', elmMapHeroPanelMagic, 'map.heropanel.magic.background', 'halParentMiddle', 'valParentBottomHeight',posX, posY, 584, 531, Tag);
      [*] = ;
      [*] = ;      CreateHeroSpellSlots(goHandle, elmMapHeroPanelMagic, mode);
      [*] = ;
      [*] = ;      //bag pack
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmMapHeroPanelMagic, 'heropanel.bagpack.background', 'halParentMiddle', 'valParentBottomHeight', 150, -225, 283, 482, Tag);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Inventory doll block
      [*] = ;   if (mode<>gc_HeroPanelExtraUnit) and (mode<>gc_HeroPanelBothPanels) then
      [*] = ;   begin
      [*] = ;      elmMapHeroPanelInventory := _gui_CreateDummy('map_heropanel_inventory_doll', elmMapHeroPanelLeftSide,  'halParentLeft', 'valParentBottomHeight', 15+355, 24, 0, 0, Tag);
      [*] = ;      posX := -31;
      [*] = ;      posY := -24;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (mode=gc_HeroPanelInventory) then
      [*] = ;   begin
      [*] = ;      elmImageHandle := _gui_CreateImage('map_heropanel_inventory_background', elmMapHeroPanelInventory, 'map.heropanel.inventory.background', 'halParentMiddle', 'valParentBottomHeight', posX-3, posY, 590, 531, Tag);
      [*] = ;      invXOffset := -628;
      [*] = ;      invYOffset := 380;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ((mode<>gc_HeroPanelBothPanels) and (mode<>gc_HeroPanelExtraUnit)) or (mode=gc_HeroPanelInventory) then
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmMapHeroPanelInventory, 'heropanel.bagpack.background', 'halParentMiddle', 'valParentBottomHeight', 135, -249, 283, 482, Tag);
      [*] = ;
      [*] = ;   if (mode=gc_HeroPanelBothPanels) {or (mode=6)} then
      [*] = ;   begin
      [*] = ;      // back pack
      [*] = ;      elmImageHandle := _gui_CreateImage('', elmMapHeroPanelParams, 'heropanel.bagpack.background', 'halParentLeft', 'valParentBottomHeight', 7, -225, 283, 482, Tag);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// hero doll and inventory slots
      [*] = ;var elmParentHandle : Integer = 0;
      [*] = ;var width : Integer = 0;
      [*] = ;var height : Integer = 0;
      [*] = ;
      [*] = ;if (elmMapHeroPanelInventory<>0) then
      [*] = ;begin
      [*] = ;   var count : Integer;
      [*] = ;   count := gc_HeroInventoryCount;
      [*] = ;
      [*] = ;   var startInd, endInd : Integer;
      [*] = ;   if (mode=gc_HeroPanelInventory) or (mode=gc_HeroPanelBothPanels) {or (mode=6)} then
      [*] = ;   begin
      [*] = ;      startInd := 0;
      [*] = ;      endInd := count-1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (mode=gc_HeroPanelExtraUnit) then
      [*] = ;   begin
      [*] = ;      startInd := 0;
      [*] = ;      endInd := gc_HeroDollSlotsCount-1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      startInd := gc_HeroDollSlotsCount;
      [*] = ;      endInd := count-1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elmSlotHandle : Integer;
      [*] = ;   for i := startInd to endInd do
      [*] = ;   begin
      [*] = ;      if i < gc_HeroDollSlotsCount then
      [*] = ;      begin
      [*] = ;         posX := invBaseX + invXOffset + itemSlotPosX[i];
      [*] = ;         posY := invBaseY + invYOffset + itemSlotPosY[i]-1;
      [*] = ;         case i of
      [*] = ;            3, 8, 4, 9 : posY := posY+1;
      [*] = ;            5, 7, 10, 12 : posY := posY+2;
      [*] = ;         end;
      [*] = ;         if (i >= 13) and (i <= 16) then
      [*] = ;            posY := posY + 2;
      [*] = ;         elmParentHandle := elmMapHeroPanelInventory;
      [*] = ;         width := itemSize;
      [*] = ;         height := itemSize;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         width := itemSize;
      [*] = ;         height := itemSize;
      [*] = ;
      [*] = ;         posX := -300 + ((i - gc_HeroDollSlotsCount) mod 4) * (56);
      [*] = ;         posY := 400 + ((i - gc_HeroDollSlotsCount) div 4) * (56);
      [*] = ;
      [*] = ;         if (mode=gc_HeroPanelBothPanels) or (mode=gc_HeroPanelExtraUnit) then
      [*] = ;         begin
      [*] = ;            posX := posX-275+288;
      [*] = ;            posY := posY+24;
      [*] = ;            elmParentHandle := elmMapHeroPanelParams;//elmMapHeroPanelInventory;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            elmParentHandle := elmMapHeroPanelInventory;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var elmDummyHandle : Integer = _gui_CreateDummy('', elmParentHandle,  'halParentLeft', 'valParentBottomHeight', 329, -908, 0, 0, 0);
      [*] = ;
      [*] = ;      tag := gc_gui_HeroInventorySlots_btnBaseTag + i;
      [*] = ;
      [*] = ;      var pHeroDoll : Integer = ParserSelectByHandleByKey(heroParser, 'Doll');
      [*] = ;      var pHeroDollSlot : Integer = ParserSelectByHandleByIndex(pHeroDoll, i);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pHeroDollSlot, 'ItemID');
      [*] = ;      var itemDurability : Integer = ParserGetIntValueByKeyByHandle(pHeroDollSlot, 'Durability');
      [*] = ;      var dollSlotIndex : Integer = ParserGetIntValueByKeyByHandle(pHeroDollSlot, 'ItemSlot');
      [*] = ;
      [*] = ;      var highlight, disabled : Boolean = False;
      [*] = ;      var slotAllowItem : Boolean = True;
      [*] = ;
      [*] = ;      var pItem, itemSlot, itemType, itemMaxDurability : Integer = 0;
      [*] = ;      if (itemID<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         pItem := IntRegister1;
      [*] = ;         itemSlot := ParserGetIntValueByKeyByHandle(pItem, 'ItemSlot');
      [*] = ;         itemType := ParserGetIntValueByKeyByHandle(pItem, 'ItemType');
      [*] = ;         itemMaxDurability := ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (gIntRegister_MapPickedItemID<>0) then
      [*] = ;      begin
      [*] = ;         if (itemID<>0) and (SameText(gStringRegister_ItemPlace, 'Shop')) then
      [*] = ;         begin
      [*] = ;            disabled := True;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := gIntRegister_MapPickedItemID;
      [*] = ;            MapExecuteState('GetItemParserByID');
      [*] = ;            var pPickedItem : Integer = IntRegister1;
      [*] = ;            var pickedItemSlot : Integer = ParserGetIntValueByKeyByHandle(pPickedItem, 'ItemSlot');
      [*] = ;            var pickedItemType : Integer = ParserGetIntValueByKeyByHandle(pPickedItem, 'ItemType');
      [*] = ;            var pickedItemDurability : Integer = ParserGetIntValueByKeyByHandle(pPickedItem, 'Durability');
      [*] = ;
      [*] = ;            IntRegister0 := gIntRegister_MapPickedItemID;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;            var canUse : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            var slotAllowItem2 : Boolean = True;
      [*] = ;            var pSelectedDollSlot : Integer = ParserSelectByHandleByIndex(pHeroDoll, gIntRegister_MapSelectedItemSlot);
      [*] = ;            var slotItemSlot : Integer = ParserGetIntValueByKeyByHandle(pSelectedDollSlot, 'ItemSlot');
      [*] = ;
      [*] = ;            if (itemID<>0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := itemID;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;               var canUse2 : Boolean = BoolRegister0;
      [*] = ;               //Brain explode here
      [*] = ;               slotAllowItem2 := ((canUse2) and (ItemSlot = pickedItemSlot) or ((ItemSlot = 1) and (pickedItemSlot = 14))) or
      [*] = ;               ((dollSlotIndex=0) and (slotItemSlot=0)) or
      [*] = ;               ((dollSlotIndex=0) and SameText(gStringRegister_ItemPlace, 'Treasury'));
      [*] = ;
      [*] = ;               {if canUse and slotAllowItem2 and (ItemSlot = pickedItemSlot) or ((ItemSlot = 1) and (pickedItemSlot = 14)) then
      [*] = ;               slotAllowItem2 := False;}
      [*] = ;               if canUse and slotAllowItem2 and (ItemSlot = pickedItemSlot) or ((ItemSlot = 1) and (pickedItemSlot = 14)) then
      [*] = ;                  slotAllowItem2 := True;
      [*] = ;            end;
      [*] = ;
      [*] = ;            //Brain explode here too
      [*] = ;            slotAllowItem := ((dollSlotIndex = 0) and (itemID=0)) or
      [*] = ;            ((itemID<>0) and (slotAllowItem2) and ((dollSlotIndex=0) or ((canUse) and ((dollSlotIndex = pickedItemSlot) or ((dollSlotIndex = 1) and (pickedItemSlot = 14)))))) or
      [*] = ;            ((canUse) and ((dollSlotIndex = pickedItemSlot) or ((dollSlotIndex = 1) and (pickedItemSlot = 14))));
      [*] = ;
      [*] = ;            if (slotAllowItem) then
      [*] = ;               highlight := True;
      [*] = ;
      [*] = ;            var noFreeSpace : Boolean = False;
      [*] = ;            //Check free space for two-handed weapon
      [*] = ;            IntRegister0 := 2;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetSlotIndexByItemSlot');
      [*] = ;            var slIndex1 : Integer = IntRegister1;
      [*] = ;
      [*] = ;            var pGOShieldSlot : Integer = ParserSelectByHandleByIndex(pHeroDoll, slIndex1);
      [*] = ;            var shieldItemID : Integer = ParserGetIntValueByKeyByHandle(pGOShieldSlot, 'ItemID');
      [*] = ;            var shieldItemDur : Integer = ParserGetIntValueByKeyByHandle(pGOShieldSlot, 'Durability');
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'GetFreeInvSlotsCount');
      [*] = ;            var freeSlots : Integer = IntRegister0;
      [*] = ;
      [*] = ;            if (shieldItemID > 0) and (freeSlots < 1) then
      [*] = ;               noFreeSpace := true;
      [*] = ;
      [*] = ;            const cMeleeWeaponSlot = 3;
      [*] = ;            if (pickedItemSlot = 14) and (noFreeSpace) and (i=cMeleeWeaponSlot) then
      [*] = ;               disabled := True;
      [*] = ;
      [*] = ;            if (not slotAllowItem) and ((i<>gIntRegister_MapSelectedItemSlot) or (not SameText(gStringRegister_ItemPlace, 'Doll'))) then
      [*] = ;               disabled := True;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (itemID<>0) then
      [*] = ;      begin
      [*] = ;         var hint : String;
      [*] = ;
      [*] = ;         if (gBoolRegister_RepairItemMode) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            IntRegister1 := itemDurability;
      [*] = ;            IntRegister2 := goHandle;
      [*] = ;            IntRegister3 := gIntRegister_MapCurrentShop;
      [*] = ;            PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'GetItemRepPrice');
      [*] = ;            var repGoldPrice : Integer = IntRegister4;
      [*] = ;            var repGemPrice : Integer = IntRegister5;
      [*] = ;
      [*] = ;            var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;            var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;            var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;            if ((repGoldPrice=0) and (repGemPrice=0)) or ((repGoldPrice>0) and (plGold<repGoldPrice)) or ((repGemPrice>0) and (plGem<repGemPrice)) then
      [*] = ;               disabled := true;
      [*] = ;         end;
      [*] = ;
      [*] = ;         //var hint : String = 'itemhint%|'+IntToStr(itemID)+'|'+IntToStr(1)+'|'+IntToStr(itemDurability);
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('open', elmDummyHandle, 'heropanel.icon.52x52.slot.empty', 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         GUIInvalidateParentPositions(elmSlotHandle);
      [*] = ;         var iconName : String;
      [*] = ;         _misc_GetItemIconNameExt(itemID, iconName);
      [*] = ;         elmImageHandle := _gui_CreateImage('' , elmSlotHandle, iconName, 'halParentLeft', 'valParentTop', 0, 0, 52, 52, tag);
      [*] = ;
      [*] = ;         if (highlight) then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 'map.PressHeroInventorySlot', '', tag);
      [*] = ;            SetGUIElementStringTag(elmBtnHandle, IntToStr(goUID));
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := ItemID;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CanUseItem');
      [*] = ;         if (not  BoolRegister0) then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.icon.52x52.red', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.5);
      [*] = ;         end;
      [*] = ;
      [*] = ;         elmBtnHandle := _gui_CreateButton('item_slot', elmSlotHandle, 'item_slot', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, '', '', tag);
      [*] = ;         _gui_ft_AttachHint_I4_S2(elmBtnHandle,'VVK.FTooltipItem',itemID,cFT_ItemPriceSell,itemDurability,goUID,'map.PressHeroInventorySlot','3');
      [*] = ;         SetGUIElementStringTag(elmBtnHandle, IntToStr(goUID));
      [*] = ;         if (disabled) then
      [*] = ;         begin
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 1.0);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;            if (gBoolRegister_RepairItemMode) then
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 26, 0.5, 0.5, 0.5, 1)
      [*] = ;            else
      [*] = ;               SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (gBoolRegister_RepairItemMode) then
      [*] = ;         begin
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'UpProperty', 'heropanel.icon.52x52.slot.cover.normal', 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.cover.hover', 0, 0, 0, 0, 25, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'DownProperty', 'heropanel.icon.52x52.slot.cover.pressed', 0, 0, 0, 0, 25, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', 'heropanel.icon.52x52.slot.disabled', 0, 0, 0, 0, 26, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'heropanel.icon.52x52.slot.cover.checkon', 0, 0, 0, 0, 25, 0.5, 0.5, 0.5, 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (gIntRegister_MapSelectedItemSlot=i) and SameText(gStringRegister_ItemPlace, 'Doll') then
      [*] = ;            SetGUIElementChecked(elmBtnHandle, True);
      [*] = ;
      [*] = ;         if (isShop) then
      [*] = ;            hint := 'gui|639'
      [*] = ;         else
      [*] = ;            hint := 'gui|643';
      [*] = ;
      [*] = ;         if (itemMaxDurability>1) then
      [*] = ;         begin
      [*] = ;            var material : String;
      [*] = ;            if (itemDurability=0) then
      [*] = ;               material := 'item.broken.mark'
      [*] = ;            else
      [*] = ;            if (itemDurability < itemMaxDurability div 2) then
      [*] = ;               material := 'item.damaged.mark';
      [*] = ;            
      [*] = ;            if material <> '' then
      [*] = ;               elmImageHandle := _gui_CreateImage('', elmBtnHandle, material, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, tag);
      [*] = ;         end;
      [*] = ;
      [*] = ;         elmBtnHandle := _gui_CreateButton('dismiss', elmBtnHandle, 'dismiss', 'heropanel.onslot.btn.dismiss.18x18', 'halParentRight', 'valParentTop', -16, 0, 18, 18, '', hint, gc_gui_dollpanel_btnDismiss);
      [*] = ;         SetGUIElementStringTag(elmBtnHandle, 'dismiss');
      [*] = ;         SetGUIElementVisible(elmBtnHandle, False);
      [*] = ;         if gIntRegister_CampaignHeroesPanel > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;            IntRegister1 := itemID;
      [*] = ;            IntRegister2 := $13;
      [*] = ;            GUIExecuteState('VVK.map.GetHeroAstralTransferPrice');
      [*] = ;            IntRegister2 := IntRegister0;
      [*] = ;            IntRegister0 := elmSlotHandle;
      [*] = ;            IntRegister1 := 2;
      [*] = ;            GUIExecuteState('vvk.map.DisplayAstralPrice');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         elmSlotHandle := _gui_CreateImageSimple('hero_inventory_bag_slot_open', elmDummyHandle, 'misc.blank.black.alpha.0'{'heropanel.icon.52x52.slot.empty'}, 'halParentLeft', 'valParentTop', posX, posY);
      [*] = ;         SetGUIElementWidth(elmSlotHandle, 52);
      [*] = ;         SetGUIElementHeight(elmSlotHandle, 52);
      [*] = ;
      [*] = ;         if (highlight) then
      [*] = ;         begin
      [*] = ;            elmImageHandle := _gui_CreateImageSimple('', elmSlotHandle, 'heropanel.icon.52x52.slot.empty.highlight', 'halParentLeft', 'valParentTop', 0, 0);
      [*] = ;            elmBtnHandle := _gui_CreateButton('hero_inventory_slot_highlighted', elmSlotHandle, '', 'misc.blank.black.alpha.0', 'halParentLeft', 'valParentTop', 0, 0, 52, 52, 'map.PressHeroInventorySlot', '', tag);
      [*] = ;            SetGUIElementStringTag(elmBtnHandle, IntToStr(goUID));
      [*] = ;            SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'heropanel.icon.52x52.slot.empty.highlight.hover', 0, 0, 0, 0, 6, 0.5, 0.5, 0.5, 1);
      [*] = ;            SetGUIElementUserBlend(elmImageHandle, 0.4);
      [*] = ;            SetGUIElementUserBlend(elmBtnHandle, 0.4);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            SetGUIAllowEvents(elmSlotHandle, True, False, False);
      [*] = ;            if (i<gc_HeroDollSlotsCount) then
      [*] = ;               SetGUIElementHint(elmSlotHandle, 'item_slot|'+IntToStr(dollSlotIndex))
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               SetGUIElementHint(elmSlotHandle, 'item_slot|'+IntToStr(dollSlotIndex));
      [*] = ;               SetGUIElementUserBlend(elmSlotHandle, 0.85);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (mode = gc_HeroPanelBothPanels) or (mode = gc_HeroPanelUnitsOnly) or (mode = gc_HeroPanelInventory) or (mode = gc_HeroPanelSpellbook) or (mode=gc_HeroPanelExtraUnit) then
      [*] = ;begin
      [*] = ;   //Hero army strip element
      [*] = ;   matName := 'element.strip.341';
      [*] = ;   if gIntRegister_GUICurCastleMode <> 0 then
      [*] = ;      posY := -508
      [*] = ;   else
      [*] = ;      posY := -508+cTempOffsetFromBottom;
      [*] = ;   elmImageHandle := _gui_CreateImage('map_heropanel_strip_mode_'+IntToStr(mode), elmMapHeroPanelLeftSide, matName, 'halParentMiddle', 'valParentBottomHeight', -29, posY, GetGUITextureWidth(matName), GetGUITextureHeight(matName), Tag);
      [*] = ;   SetGUIAllowEvents(elmImageHandle, True, False, False);
      [*] = ;   SetGUIElementPressState(elmImageHandle, 'map.DoOnClickBackground');
      [*] = ;   posX := 56;
      [*] = ;   posY := 6;
      [*] = ;   var text : String;
      [*] = ;   if (mode=gc_HeroPanelInventory) then
      [*] = ;     text := GetLocaleTableListItemByID('gui', '613')
      [*] = ;   else
      [*] = ;      if (mode=gc_HeroPanelSpellbook) then
      [*] = ;         text := GetLocaleTableListItemByID('gui', '606')
      [*] = ;      else
      [*] = ;         text := GetLocaleTableListItemByID('gui', '589');
      [*] = ;
      [*] = ;   elmTextHandle  := _gui_CreateText('' , elmImageHandle, text, 'halParentLeft', 'valParentTop', posX, posY, 240, 25, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;elmBtnCloseWindowHandle := 0;
      [*] = ;if (not gBoolRegister_GUIExchangeSecond) then
      [*] = ;begin
      [*] = ;   if gIntRegister_CampaignHeroesPanel > 0 then
      [*] = ;   begin
      [*] = ;      var whd : Integer;
      [*] = ;      var p1,p2 : Integer;
      [*] = ;
      [*] = ;      elmBtnCloseWindowHandle := _gui_CreateButtonFromCollection('map_heropanel_btn_astralaccept', elmMapHeroPanelLeftSide, 'map.heropanel.btn.astralaccept', 'halParentMiddle', 'valParentBottomHeight', 290, 2, '', gc_gui_heropanel_btnAstralAccept);
      [*] = ;      if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;         p1 := gCampaign.arrcampplayers[0].energy
      [*] = ;      else
      [*] = ;         p1 := 10000;
      [*] = ;      IntRegister0 := gIntRegister_GUIActiveHeroUID1;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      GUIExecuteState('VVK.map.GetHeroAstralTransferPrice');
      [*] = ;      p2 := IntRegister0;
      [*] = ;      IntRegister0 := elmMapHeroPanelLeftSide;
      [*] = ;      IntRegister1 := p1;
      [*] = ;      IntRegister2 := p2;
      [*] = ;      GUIExecuteState('VVK.map.CreateAstralPricePanel');
      [*] = ;      whd := IntRegister0;
      [*] = ;      SetGUIElementPositionX(whd,IntRegister1);
      [*] = ;      SetGUIElementPositionY(whd,GetGUIElementHeight(elmMapHeroPanelLeftSide)-(IntRegister2+GetGUIElementHeight(whd)));
      [*] = ;      GUIElementBringToFront(elmBtnCloseWindowHandle);
      [*] = ;
      [*] = ;      if p1 >= p2 then
      [*] = ;         SetGUIElementStringTag(elmBtnCloseWindowHandle,'1')
      [*] = ;      else
      [*] = ;         SetGUIElementStringTag(elmBtnCloseWindowHandle,'2');
      [*] = ;      whd := _gui_CreateImage('astral_cancel_frame', elmBtnCloseWindowHandle, 'heropanel.btn.tabspanel.btnplace', 'halParentRight', 'valParentBottomHeight',0,0, 0, 0, 0);
      [*] = ;      whd := _gui_CreateButton('astral_cancel', whd, '', 'heropanel.btn.dismiss', 'halParentLeft', 'valParentTop', 27, 27-15, 0, 0, '', '', gc_gui_heropanel_btnCloseWindow);
      [*] = ;      //whd := _gui_CreateButton('heropanel_astral_cancel', elmBtnCloseWindowHandle, '', 'mainpanel.btn.cancel', 'halParentMiddle', 'valParentTop',0, -1*(GetGUIElementHeight(elmBtnCloseWindowHandle)+20), 0, 0, '', '', gc_gui_heropanel_btnCloseWindow);
      [*] = ;      SetGUIElementHint(whd, 'gui|no_heroes_to_astral_tooltip');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (mode<>gc_HeroPanelSpellsOnly) and (gIntRegister_GUICurCastleMode=0) then
      [*] = ;      begin
      [*] = ;         var whd : Integer;
      [*] = ;
      [*] = ;         elmBtnCloseWindowHandle := _gui_CreateButtonFromCollection('map_heropanel_btn_closewindow', elmMapHeroPanelLeftSide, 'map.heropanel.btn.closewindow', 'halParentMiddle', 'valParentBottomHeight', 290, 2, '', gc_gui_heropanel_btnCloseWindow);
      [*] = ;         SetGUIElementHint(elmBtnCloseWindowHandle, GetLocaleTableListItemByID('menu','47'));
      [*] = ;         IntRegister0 := elmMapHeroPanelLeftSide;
      [*] = ;         GUIExecuteState('VVK.map.CreateHeroResPanel');
      [*] = ;         whd := IntRegister0;
      [*] = ;         SetGUIElementPositionX(whd,GetGUIElementWidth(elmMapHeroPanelLeftSide)+IntRegister1);
      [*] = ;         SetGUIElementPositionY(whd,GetGUIElementHeight(elmMapHeroPanelLeftSide)-(IntRegister2+GetGUIElementHeight(whd)));
      [*] = ;         GUIElementBringToFront(elmBtnCloseWindowHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//SetGUIElementPressState(elmParentHeroPanelHandle, cEventState);
      [*] = ;
      [*] = ;gBoolRegister_GUIExchangeSecond := False;
      [*] = ;
      [*] = ;_misc_UpdateTutorialHint();
      [*] = ;if gTutorial.map then
      [*] = ;begin
      [*] = ;   gBoolRegister_BtnHeroCloseEnabled := true;
      [*] = ;   // item window
      [*] = ;   case mode of
      [*] = ;      // garrison
      [*] = ;      gc_HeroPanelUnitsOnly : begin
      [*] = ;         if gTutorial.hire = 1 then
      [*] = ;         begin
      [*] = ;            gBoolRegister_BtnHeroCloseEnabled := false;
      [*] = ;            gTutorial.hire := 2;
      [*] = ;
      [*] = ;            IntRegister0 := 15;
      [*] = ;            GUIExecuteState('ShowTutorial');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := -5;
      [*] = ;            MapExecuteState('CheckTutorialProgress');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      // shop
      [*] = ;      gc_HeroPanelInventory : begin
      [*] = ;         if gTutorial.trade = 1 then
      [*] = ;         begin
      [*] = ;            gBoolRegister_BtnHeroCloseEnabled := false;
      [*] = ;            gTutorial.trade := 2;
      [*] = ;
      [*] = ;            IntRegister0 := 5;
      [*] = ;            GUIExecuteState('ShowTutorial');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if gTutorial.repair = 1 then
      [*] = ;         begin
      [*] = ;            gBoolRegister_BtnHeroCloseEnabled := false;
      [*] = ;            gTutorial.repair := 2;
      [*] = ;
      [*] = ;            IntRegister0 := 46;
      [*] = ;            GUIExecuteState('ShowTutorial');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      // library
      [*] = ;      gc_HeroPanelSpellbook : begin
      [*] = ;         if (gTutorial.library = 1) then
      [*] = ;         begin
      [*] = ;            gBoolRegister_BtnHeroCloseEnabled := false;
      [*] = ;            gTutorial.library := 2;
      [*] = ;
      [*] = ;            IntRegister0 := 21;
      [*] = ;            GUIExecuteState('ShowTutorial');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (elmBtnCloseWindowHandle <> 0) then
      [*] = ;begin
      [*] = ;   if _cmd_CheckNF('heroclosepanels','1','') = 1 then
      [*] = ;      SetGUIElementEnabled(elmBtnCloseWindowHandle, true)
      [*] = ;   else
      [*] = ;      SetGUIElementEnabled(elmBtnCloseWindowHandle, false);
      [*] = ;end;
      [*] = ;
      [*] = ;if (_misc_GetTutorialHintStatus() <> gc_Tutorial_HintEnabled) and (mode = gc_HeroPanelSpellbook) then
      [*] = ;begin
      [*] = ;   IntRegister0 := -4;
      [*] = ;   MapExecuteState('CheckTutorialProgress');
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

