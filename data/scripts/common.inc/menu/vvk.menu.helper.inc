section.begin
   Name = VVK.Menu.Helper
   Description : struct.begin
      [*] = ;we SHOULD NOT use any functions instead of core because at the time of initial execution we are not allowed to invoke any states or lib functions
      [*] = ;
      [*] = ;IntRegister0 - mode
      [*] = ;   0 - check DLC availability
      [*] = ;      IntRegister1 - DLC ID
      [*] = ;      RET: BoolRegister0 - true if available, even if not installed
      [*] = ;   1 - Process inclusions
      [*] = ;      StringRegister0 - inclusions file name
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure ProcessExclusions(filePath : String; bInclude : Boolean);
      [*] = ;begin
      [*] = ;   procedure ProcessExclusion(pChange, pData : Integer; id_key : String);
      [*] = ;   begin
      [*] = ;      if pChange <> 0 then
      [*] = ;      begin
      [*] = ;         var i, j, tid, id, pThing : Integer;
      [*] = ;
      [*] = ;         for i := 0 to ParserGetCountByHandle(pChange)-1 do
      [*] = ;         begin
      [*] = ;            id := ParserGetIntValueByIndexByHandle(pChange, i);
      [*] = ;         
      [*] = ;            for j := 0 to ParserGetCountByHandle(pData)-1 do
      [*] = ;            begin
      [*] = ;               pThing := ParserSelectByHandleByIndex(pData, j);
      [*] = ;               tid := ParserGetIntValueByKeyByHandle(pThing, id_key);
      [*] = ;               if bInclude then
      [*] = ;                  tid := -1*tid;
      [*] = ;            
      [*] = ;               if tid = id then
      [*] = ;               begin
      [*] = ;                  if not bInclude then
      [*] = ;                     tid := -1*tid;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pThing, id_key, tid);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var pRoot : Integer = ParserSelectByKey(gc_ParsersRoot);
      [*] = ;   if pRoot = 0 then 
      [*] = ;      pRoot := ParserCreate(gc_ParsersRoot);
      [*] = ;
      [*] = ;   var pExclusions : Integer = ParserSelectByHandleByKey(pRoot, 'exclusions');
      [*] = ;   if (pExclusions = 0) then
      [*] = ;      pExclusions := ParserAddChildByIndex(pRoot, 'exclusions')
      [*] = ;   else
      [*] = ;      ParserClearByHandle(pExclusions);
      [*] = ;   
      [*] = ;   ParserLoadFromFileByHandle(pExclusions, filePath);
      [*] = ;
      [*] = ;   ProcessExclusion(ParserSelectByHandleByKey(pExclusions, 'Units'), gPrototypeData.units.handle, 'UnitID');
      [*] = ;   ProcessExclusion(ParserSelectByHandleByKey(pExclusions, 'Spells'), gPrototypeData.spells.handle, 'SpellID');
      [*] = ;   ProcessExclusion(ParserSelectByHandleByKey(pExclusions, 'WorldRules'), gPrototypeData.worldrules.handle, 'WorldRuleID');
      [*] = ;   ProcessExclusion(ParserSelectByHandleByKey(pExclusions, 'Items'), gPrototypeData.items.handle, 'ItemID');
      [*] = ;   ProcessExclusion(ParserSelectByHandleByKey(pExclusions, 'Rituals'), gPrototypeData.rituals.handle, 'RitualID');
      [*] = ;   
      [*] = ;   ParserClearByHandle(pExclusions);
      [*] = ;end;
      [*] = ;
      [*] = ;case IntRegister0 of
      [*] = ;   0 : begin
      [*] = ;      var id : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if SteamAPPTriggerAchievements('-3|'+IntToStr(IntRegister1),gc_gui_DelimiterChar,gc_gui_QuoteChar) <> 0 then
      [*] = ;         BoolRegister0 := true
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ErrorLog('DLC '+IntToStr(id)+' is not available.');
      [*] = ;         BoolRegister0 := false;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   1 : ProcessExclusions( StringRegister0, True );
      [*] = ;   2 : ProcessExclusions( StringRegister0, False );
      [*] = ;end;
   struct.end
section.end

