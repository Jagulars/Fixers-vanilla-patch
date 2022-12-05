section.begin
   Name = EventParserLoadList
   Description : struct.begin
      [*] = ;
   struct.end
   Code : struct.begin
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var activeInd : Integer = GetIntValueByName('ActiveInd');
      [*] = ;
      [*] = ;const cBtnLoadTag = 101;
      [*] = ;const cBtnDeleteTag = 102;
      [*] = ;const cBtnCloseTag = 110;
      [*] = ;const cSaveIndexBaseTag = 1000;
      [*] = ;
      [*] = ;// approves
      [*] = ;const cBtnDeleteApproveTag = 202;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if (tag<>gc_gui_hotkey_btnEscape) and (tag<>gc_gui_hotkey_btnEnter) and (tag>=cSaveIndexBaseTag) then
      [*] = ;   begin
      [*] = ;      var saveIndex : Integer = tag-cSaveIndexBaseTag;
      [*] = ;      SetIntValueByName('ActiveInd', saveIndex);
      [*] = ;      GUIExecuteState('ShowParserLoadList');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case tag of
      [*] = ;      cBtnLoadTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         if (activeInd >= 0) then
      [*] = ;         begin
      [*] = ;            _gui_FadeWindow_VVK(_gui_GetWindow('load_window'), gc_gui_FadeTime0_2, 2);
      [*] = ;            var returnState : String = GetValueByName('ReturnState');
      [*] = ;            var returnTag : Integer = GetIntValueByName('ReturnTag');
      [*] = ;            var pParser : Integer = GetIntValueByName('ParserHandle');
      [*] = ;            SetIntValueByName('ParserHandle', ParserSelectByHandleByIndex(pParser, activeInd));
      [*] = ;            SetValueByName('ReturnState', '');
      [*] = ;            SetIntValueByName('ReturnTag', 0);
      [*] = ;            SetIntValueByName('ActiveInd', -1);
      [*] = ;            SetIntValueByName('Tag', returnTag);
      [*] = ;            GUIExecuteState(returnState);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnDeleteTag : begin
      [*] = ;         _gui_ShowQuestionDialog('gui|are_you_sure', 'EventParserLoadList', cBtnDeleteApproveTag, '', 0, true, false);
      [*] = ;      end;
      [*] = ;      cBtnDeleteApproveTag : begin
      [*] = ;         var pParser : Integer = GetIntValueByName('ParserHandle');
      [*] = ;         ParserFreeByHandle(ParserSelectByHandleByIndex(pParser, activeInd));
      [*] = ;         SetIntValueByName('ActiveInd', -1);
      [*] = ;         GUIExecuteState('ShowParserLoadList');
      [*] = ;      end;
      [*] = ;      cBtnCloseTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         SetIntValueByName('ParserHandle', 0);
      [*] = ;         SetIntValueByName('ActiveInd', -1);
      [*] = ;         SetValueByName('ReturnState', '');
      [*] = ;         SetIntValueByName('ReturnTag', 0);
      [*] = ;         _gui_FadeWindow_VVK(_gui_GetWindow('load_window'), gc_gui_FadeTime0_2, 2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

