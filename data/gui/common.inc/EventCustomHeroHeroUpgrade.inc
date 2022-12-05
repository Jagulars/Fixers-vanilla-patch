section.begin
   Name = EventCustomHeroHeroUpgrade
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\EVENTCUSTOMHEROHEROUPGRADE';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;
      [*] = ;procedure EventCustomHeroHeroUpgrade(var battle : TInetBattle);
      [*] = ;begin
      [*] = ;   var sPress  : String = GetValueByName('Press');
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;   var key : String = GetValueByName('Key');
      [*] = ;
      [*] = ;   const cEventState = 'EventCustomHeroHeroUpgrade';
      [*] = ;
      [*] = ;   //const cBtnLevelUp = 101;
      [*] = ;   const cBtnBaseTagNewClass = 480;
      [*] = ;   const cBtnBaseTagHeroSkill = 500;
      [*] = ;   const cBtnBaseTagHeroSkillRemove = 600;
      [*] = ;
      [*] = ;   if (sPress='c') then
      [*] = ;   begin
      [*] = ;      if (key='LButton') and (tag>cBtnBaseTagNewClass) and (tag<=cBtnBaseTagNewClass+4) then
      [*] = ;      begin
      [*] = ;         var newClass : Integer = tag-cBtnBaseTagNewClass;
      [*] = ;         battle.hero[battle.curhero].class2 := newClass;
      [*] = ;         //battle.hero[battle.curhero].level := battle.hero[battle.curhero].level+1;
      [*] = ;         GUIExecuteState('UpdateCustomHeroWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag>cBtnBaseTagHeroSkill) and (tag<cBtnBaseTagHeroSkill+100) then
      [*] = ;      begin
      [*] = ;         if (key='LButton') then
      [*] = ;         begin
      [*] = ;            battle.hero[battle.curhero].level := battle.hero[battle.curhero].level+1;
      [*] = ;            _inet_AddHeroBonusNew(battle.hero[battle.curhero], battle.hero[battle.curhero].level);
      [*] = ;
      [*] = ;            var skillID : Integer = tag-cBtnBaseTagHeroSkill;
      [*] = ;            var freeIndex : Integer = -1;
      [*] = ;            var i : Integer;
      [*] = ;            for i:=0 to (gc_MaxHeroSkillCount-1) do
      [*] = ;            begin
      [*] = ;               var tmpSkillID : Integer = battle.hero[battle.curhero].arrskills[i].id;
      [*] = ;               if (freeIndex=-1) and (tmpSkillID=0) then
      [*] = ;               begin
      [*] = ;                  freeIndex := i;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;               if (tmpSkillID=skillID) then
      [*] = ;               begin
      [*] = ;                  battle.hero[battle.curhero].arrskills[i].level := battle.hero[battle.curhero].arrskills[i].level+1;
      [*] = ;                  freeIndex := -1;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if (freeIndex>-1) then
      [*] = ;            begin
      [*] = ;               battle.hero[battle.curhero].arrskills[freeIndex].id := skillID;
      [*] = ;               battle.hero[battle.curhero].arrskills[freeIndex].level := 1;
      [*] = ;            end;
      [*] = ;            GUIExecuteState('UpdateCustomHeroWindow');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag>=cBtnBaseTagHeroSkillRemove) and (tag<cBtnBaseTagHeroSkillRemove+100) then
      [*] = ;      begin
      [*] = ;         if (key='LButton') then
      [*] = ;         begin
      [*] = ;            var index : Integer = tag-cBtnBaseTagHeroSkillRemove;
      [*] = ;            
      [*] = ;            if ((battle.hero[battle.curhero].level-1)=9) then
      [*] = ;               battle.hero[battle.curhero].class2 := 0;
      [*] = ;            
      [*] = ;            battle.hero[battle.curhero].arrskills[index].level := battle.hero[battle.curhero].arrskills[index].level-1;
      [*] = ;            var i : Integer;
      [*] = ;            if (battle.hero[battle.curhero].arrskills[index].level<=0) then
      [*] = ;            begin
      [*] = ;               battle.hero[battle.curhero].arrskills[index].id := 0;
      [*] = ;               battle.hero[battle.curhero].arrskills[index].level := 0;
      [*] = ;               for i:=index to gc_MaxHeroSkillCount-2 do
      [*] = ;                  _inet_SwapSkill(battle.hero[battle.curhero].arrskills[i], battle.hero[battle.curhero].arrskills[i+1]);
      [*] = ;            end;
      [*] = ;            battle.hero[battle.curhero].level := battle.hero[battle.curhero].level - 1;
      [*] = ;            _inet_UpdateHeroParams(battle.hero[battle.curhero]);
      [*] = ;            GUIExecuteState('UpdateCustomHeroWindow');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;   EventCustomHeroHeroUpgrade(gEditorCustomPlayerTemporary)
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (gBoolRegister_IsHotSeat) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_HotSeatActivePlayer=0) then
      [*] = ;         EventCustomHeroHeroUpgrade(gHotSeatPlayer1)
      [*] = ;      else
      [*] = ;         EventCustomHeroHeroUpgrade(gHotSeatPlayer2)
      [*] = ;   end
      [*] = ;   else
      [*] = ;      EventCustomHeroHeroUpgrade(gInetBattle);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

