section.begin
   Name = battle.EventSpellBookWindow
   Code : struct.begin
      [*] = ;procedure CloseSpellBook(do_snd : Boolean);
      [*] = ;begin
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow(cBattleSpellBookWindowName),gc_gui_FadeTime0_2);
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := true;
      [*] = ;   if do_snd then
      [*] = ;      _gui_PlaySound('interface', 'spellbook_hide');
      [*] = ;end;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const cCloseBtnTag = 101;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if (tag>=gc_gui_castle_spells_btnBaseTag) and (tag<2900) then
      [*] = ;   begin
      [*] = ;      var spellInd : Integer = tag - gc_gui_castle_spells_btnBaseTag;
      [*] = ;      var pHexCells : Integer = gHexCells.handle;
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGOSpells : Integer = ParserSelectByHandleByKey(pGOParser, 'Spells');
      [*] = ;      var pGOSpell : Integer = ParserSelectByHandleByIndex(pGOSpells, spellInd);
      [*] = ;      var spellID : Integer = ParserGetIntValueByKeyByHandle(pGOSpell, 'SpellID');
      [*] = ;
      [*] = ;      IntRegister0 := spellID;
      [*] = ;      MapExecuteState('GetSpellParserByID');
      [*] = ;      var pSpell : Integer = IntRegister1;
      [*] = ;      var spArea : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;      var spSacrifice : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Sacrifice');
      [*] = ;
      [*] = ;      gIntRegister_CurSpell := spellID;
      [*] = ;      gIntRegister_CurSpellIndex := spellInd;
      [*] = ;
      [*] = ;      var actAbility : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iActiveAbility);
      [*] = ;      if (actAbility <> 0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := actAbility;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         ExecuteState('ActivateAbility');
      [*] = ;      end;
      [*] = ;
      [*] = ;      var allowCast : Boolean = SameText(GetGameObjectAnimationCycleNameByHandle(goHandle), 'idle');
      [*] = ;      if allowCast and _misc_IsLanBattle() then
      [*] = ;         allowCast := (_gv_GetBattleLock = 0); // ensure there are no actions taken in lan battle before AfterDeath has been processed to avoid errors.
      [*] = ;
      [*] = ;      if (not spSacrifice) then
      [*] = ;      begin
      [*] = ;         // on self
      [*] = ;         if (spArea = 0) then
      [*] = ;         begin
      [*] = ;            if allowCast then
      [*] = ;            begin
      [*] = ;               var curX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;               var curY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;               var pHexParser : Integer = _map_GetBattleHex(curX, curY);
      [*] = ;
      [*] = ;               IntRegister0 := spellID;
      [*] = ;               IntRegister1 := pHexParser;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'CastSpell');
      [*] = ;            end;
      [*] = ;            gIntRegister_CurSpell := -1;
      [*] = ;            gIntRegister_CurSpellIndex := -1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         // on whole battlefield
      [*] = ;         if (spArea = 2) then
      [*] = ;         begin
      [*] = ;            if allowCast then
      [*] = ;            begin
      [*] = ;               IntRegister0 := spellID;
      [*] = ;               IntRegister1 := 0;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'CastSpell');
      [*] = ;            end;
      [*] = ;            gIntRegister_CurSpell := -1;
      [*] = ;            gIntRegister_CurSpellIndex := -1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (spellID>0) then // dont drag selfcast spell and whole battlefield
      [*] = ;         begin
      [*] = ;            IntRegister0 := 6; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;            IntRegister1 := spellID; //0 - hide
      [*] = ;            ExecuteState('DoDragElement');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if allowCast or ((spArea <> 0) and (spArea <> 2)) then // close book if cast successful or the spell needs to be targeted before cast
      [*] = ;         CloseSpellBook(false);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case tag of
      [*] = ;      cCloseBtnTag, gc_gui_hotkey_btnEscape : CloseSpellBook(true);
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

