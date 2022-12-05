section.begin
   Name = DoOnClickGUI
   Code : struct.begin
      [*] = ;procedure PostToEvent(tag : Integer; state_name : String);
      [*] = ;begin
      [*] = ;   SetValueByName('Press','c');
      [*] = ;   SetIntValueByName('Tag',tag);
      [*] = ;   GUIExecuteState(state_name);
      [*] = ;end;
      [*] = ;
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;
      [*] = ;BoolRegister0 := false;
      [*] = ;GUIExecuteState('vvk.OnClickHint');
      [*] = ;if BoolRegister0 = true then
      [*] = ;   exit;
      [*] = ;
      [*] = ;const cBtnDismissCancel = 900;
      [*] = ;if SameText(key, 'LButton') then
      [*] = ;case tag of
      [*] = ;   gc_gui_unitpanel_btnDismiss :
      [*] = ;   begin
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;      var parentElmHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var parentElmTag : Integer = GetGUIElementTag(parentElmHandle);
      [*] = ;      parentElmTag := parentElmTag - gc_gui_hero_unitslots_btnBaseTag;
      [*] = ;      gIntRegister_MapDismissHeroUID := StrToInt(GetGUIElementStringTag(parentElmHandle));
      [*] = ;      const cBtnBaseTagDismissUnit = 1000;
      [*] = ;      if (gProfile.mesremoval) then
      [*] = ;      begin
      [*] = ;         _gui_ShowQuestionDialog('gui|646', 'map.EventDismissApprove', cBtnBaseTagDismissUnit+parentElmTag, 'map.EventDismissApprove', cBtnDismissCancel, true, false);
      [*] = ;         _gui_AlignQuestionDialog((gIntRegister_GUICurCastleMode=0), false, 640, 920, (gIntRegister_GUIActiveHeroUID1<>0), true);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      PostToEvent(cBtnBaseTagDismissUnit+parentElmTag, 'map.EventDismissApprove');
      [*] = ;   end;
      [*] = ;   gc_gui_garrisonpanel_btnDismiss :
      [*] = ;   begin
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;      var parentElmHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var parentElmTag : Integer = GetGUIElementTag(parentElmHandle);
      [*] = ;      parentElmTag := parentElmTag - gc_gui_hero_unitslots_btnBaseTag;
      [*] = ;      gIntRegister_MapSelectedGarrisonUnitSlot := parentElmTag;
      [*] = ;      gIntRegister_MapDismissHeroUID := gIntRegister_MapSelectedUID;
      [*] = ;      const cBtnDismissUnitGarrison = 2000;
      [*] = ;      if (gProfile.mesremoval) then
      [*] = ;      begin
      [*] = ;         _gui_ShowQuestionDialog('gui|646', 'map.EventDismissApprove', cBtnDismissUnitGarrison, 'map.EventDismissApprove', cBtnDismissCancel, true, false);
      [*] = ;         _gui_AlignQuestionDialog((gIntRegister_GUIActiveHeroUID1<>0), false, 640, 920, (gIntRegister_GUIActiveHeroUID1<>0), true);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      PostToEvent(cBtnDismissUnitGarrison, 'map.EventDismissApprove');
      [*] = ;   end;
      [*] = ;   gc_gui_spellpanel_btnDismiss :
      [*] = ;   begin
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;      var parentElmHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var parentElmTag : Integer = GetGUIElementTag(parentElmHandle);
      [*] = ;      parentElmTag := parentElmTag - gc_gui_hero_spellslots_btnBaseTag;
      [*] = ;      gIntRegister_MapSelectedSpellSlot := parentElmTag;
      [*] = ;
      [*] = ;      const cBtnDismissSpell = 5000;
      [*] = ;      if (gProfile.mesremoval) then
      [*] = ;      begin
      [*] = ;         _gui_ShowQuestionDialog('gui|647', 'map.EventDismissApprove', cBtnDismissSpell, 'map.EventDismissApprove', cBtnDismissCancel, true, false);
      [*] = ;         _gui_AlignQuestionDialog((gIntRegister_GUICurCastleMode=0), false, 640, 920, (gIntRegister_GUIActiveHeroUID1<>0), true);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      PostToEvent(cBtnDismissSpell, 'map.EventDismissApprove');
      [*] = ;   end;
      [*] = ;   gc_gui_itempanel_btnDismiss, gc_gui_dollpanel_btnDismiss :
      [*] = ;   begin
      [*] = ;      SetGUIElementVisible(elmHandle, False);
      [*] = ;      var parentElmHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var parentElmTag : Integer = GetGUIElementTag(parentElmHandle);
      [*] = ;      var pPrevSlot : Integer;
      [*] = ;      if (tag=gc_gui_itempanel_btnDismiss) then
      [*] = ;      begin
      [*] = ;         parentElmTag := parentElmTag - gc_gui_treasuryitemslots_btnBaseTag;
      [*] = ;         gIntRegister_MapSelectedItemSlot := parentElmTag;
      [*] = ;         gIntRegister_MapDismissHeroUID := gIntRegister_MapSelectedUID;
      [*] = ;
      [*] = ;         const cBtnDismissItem = 3000;
      [*] = ;         if (gProfile.mesremoval) then
      [*] = ;         begin
      [*] = ;            _gui_ShowQuestionDialog('gui|644', 'map.EventDismissApprove', cBtnDismissItem, 'map.EventDismissApprove', cBtnDismissCancel, true, false);
      [*] = ;            _gui_AlignQuestionDialog((gIntRegister_GUICurCastleMode=0), false, 640, 920, (gIntRegister_GUIActiveHeroUID1<>0), true);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         PostToEvent(cBtnDismissItem, 'map.EventDismissApprove');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      //if (tag=gc_gui_dollpanel_btnDismiss) then
      [*] = ;      begin
      [*] = ;         parentElmTag := parentElmTag - gc_gui_HeroInventorySlots_btnBaseTag;
      [*] = ;         gIntRegister_MapSelectedItemSlot := parentElmTag;
      [*] = ;         gIntRegister_MapDismissHeroUID := StrToInt(GetGUIElementStringTag(parentElmHandle));
      [*] = ;
      [*] = ;         const cBtnDismissItemDoll = 4000;
      [*] = ;
      [*] = ;         var dismissGoHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapDismissHeroUID);
      [*] = ;         var dummyUID : Integer = GetGameObjectIntValueIndByHandle(dismissGoHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         var dummyHnd : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         var plHandle : Integer;
      [*] = ;         if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;         plHandle := GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex)
      [*] = ;         else
      [*] = ;         plHandle := GetPlayerHandleInterfaceIO;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;         var pCastleProv : Integer = IntRegister0;
      [*] = ;         var castleUID : Integer = ParserGetIntValueByKeyByHandle(pCastleProv, 'DummyUID');
      [*] = ;         var castle : Boolean = False;
      [*] = ;         if (castleUID=dummyUID) then
      [*] = ;         castle := True;
      [*] = ;         var isShop : Boolean;
      [*] = ;         if gIntRegister_MapTurnIteration = 1 then // no selling items during encounters 
      [*] = ;            isShop := false
      [*] = ;         else
      [*] = ;         if (castle) then
      [*] = ;            isShop := True
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(dummyHnd, 'IsShopAndLibrary');
      [*] = ;            isShop := BoolRegister0;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var text : String;
      [*] = ;         if (isShop) then
      [*] = ;         text := 'gui|644'
      [*] = ;         else
      [*] = ;         text := 'gui|645';
      [*] = ;         if (gProfile.mesremoval) then
      [*] = ;         begin
      [*] = ;            _gui_ShowQuestionDialog(text, 'map.EventDismissApprove', cBtnDismissItemDoll, 'map.EventDismissApprove', cBtnDismissCancel, true, false);
      [*] = ;            _gui_AlignQuestionDialog((gIntRegister_GUICurCastleMode=0), false, 640, 920, (gIntRegister_GUIActiveHeroUID1<>0), true);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         PostToEvent(cBtnDismissItemDoll, 'map.EventDismissApprove');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeStrategy then ExecuteState('map.DoOnClickGUI') else
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeTactics then ExecuteState('battle.DoOnClickGUI');
   struct.end
section.end

