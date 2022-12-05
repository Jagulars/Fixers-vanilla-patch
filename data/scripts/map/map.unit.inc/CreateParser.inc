section.begin
   Name = CreateParser
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\CREATEPARSER';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;function AddName(nm : String; v : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var n : Integer;
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   n := _sa_GetNum_D(nm,$2e);
      [*] = ;   if n > 2 then
      [*] = ;   begin
      [*] = ;      n := _sa_GetAsInt_D(nm,n-1,$2e)-1;
      [*] = ;      if (n > 0) and (n < gc_MaxRoll) then
      [*] = ;      begin
      [*] = ;         if gArrRollerN[n] > 0 then
      [*] = ;            gArrRollerN[n] := -1*v
      [*] = ;         else
      [*] = ;            Result := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillNPTable(class_idx,p_idx,o_idx : Integer; pkey : String);
      [*] = ;begin
      [*] = ;   var ph,i,j,obj,p_no : Integer;
      [*] = ;   var nm : String;
      [*] = ;   var isMenu : Boolean = (not ((gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeTactics)));
      [*] = ;
      [*] = ;   if isMenu then
      [*] = ;      p_no := 1
      [*] = ;   else
      [*] = ;      p_no := gGame.map.players-1;
      [*] = ;   for i := 0 to p_no-1 do
      [*] = ;   begin
      [*] = ;      ph := GetPlayerHandleByIndex(i);
      [*] = ;      if (not isMenu) and _plr_IsInGame(ph) then
      [*] = ;      begin
      [*] = ;         for j := 0 to GetPlayerGameObjectsCountByHandle(ph)-1 do
      [*] = ;         begin
      [*] = ;            if (p_idx <> i) or (o_idx <> j) then
      [*] = ;            begin
      [*] = ;               obj := GetGameObjectHandleByIndex(j, ph);
      [*] = ;               if not GetGameObjectBoolValueIndByHandle(obj, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;               begin
      [*] = ;                  if GetGameObjectIntValueIndByHandle(obj,gc_map_GOStack_MapUnit_iClassInd1) = class_idx then
      [*] = ;                  begin
      [*] = ;                     nm := ParserGetValueByKeyByHandle(ParserSelectGameObject(obj),'Name');
      [*] = ;                     if p_idx = i then
      [*] = ;                        AddName(nm,-1)
      [*] = ;                     else
      [*] = ;                        AddName(nm,-2);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myIndex : Integer = GetGameObjectIndexByHandle(myHandle);
      [*] = ;var myClass1 : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;//var myClass2 : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iClassInd2);
      [*] = ;var pMyParser : Integer = ParserCreateGameObject(myHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;
      [*] = ;var i,j,count,n : Integer;
      [*] = ;
      [*] = ;// setting hero name
      [*] = ;var pHeroClass : Integer = ParserSelectByHandleByIndex(gPrototypeData.heroClasses.handle, myClass1);
      [*] = ;var pHeroNames : Integer = ParserSelectByHandleByKey(pHeroClass, 'NameList');
      [*] = ;
      [*] = ;_rand_ClearRoll();
      [*] = ;count := min(gc_MaxRoll,ParserGetCountByHandle(pHeroNames));
      [*] = ;for i := 0 to count-1 do
      [*] = ;begin
      [*] = ;   gArrRollerN[i] := i + 1;
      [*] = ;   gArrRollerP[i] := 1;
      [*] = ;end;
      [*] = ;
      [*] = ;FillNPTable(myClass1,GetPlayerIndexByHandle(myPlHandle),myIndex,'Name');
      [*] = ;// check if any name is available
      [*] = ;for i := 0 to count-1 do
      [*] = ;begin
      [*] = ;   if gArrRollerN[i] > 0 then
      [*] = ;      break;
      [*] = ;end;
      [*] = ;
      [*] = ;if i = count then // no free names at all
      [*] = ;begin
      [*] = ;   n := 0;
      [*] = ;   for i := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      if gArrRollerN[i] = -2 then
      [*] = ;      begin
      [*] = ;         gArrRollerN[i] := i + 1;
      [*] = ;         n := n + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if n <> 0 then
      [*] = ;      i := 0;
      [*] = ;end;
      [*] = ;if i <> count then
      [*] = ;   i := _rand_Roll_VVK(false)-1
      [*] = ;else
      [*] = ;   i := _rand_Random(count);
      [*] = ;
      [*] = ;ParserSetValueByKeyByHandle(pMyParser, 'Name', ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pHeroNames, i), 'Name'));
      [*] = ;if _log then _Log_map('Hero name: '+ParserGetValueByKeyByHandle(pMyParser, 'Name'));
      [*] = ;
      [*] = ;// setting hero portrait
      [*] = ;pHeroNames := ParserSelectByHandleByKey(pHeroClass, 'PortraitList');
      [*] = ;
      [*] = ;_rand_ClearRoll();
      [*] = ;count := min(gc_MaxRoll,ParserGetCountByHandle(pHeroNames));
      [*] = ;for i := 0 to count-1 do
      [*] = ;begin
      [*] = ;   gArrRollerN[i] := i + 1;
      [*] = ;   gArrRollerP[i] := 1;
      [*] = ;end;
      [*] = ;
      [*] = ;FillNPTable(myClass1,GetPlayerIndexByHandle(myPlHandle),myIndex,'Portrait');
      [*] = ;// check if any name is available
      [*] = ;for i := 0 to count-1 do
      [*] = ;begin
      [*] = ;   if gArrRollerN[i] > 0 then
      [*] = ;      break;
      [*] = ;end;
      [*] = ;
      [*] = ;if i = count then // no free names at all
      [*] = ;begin
      [*] = ;   n := 0;
      [*] = ;   for i := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      if gArrRollerN[i] = -2 then
      [*] = ;      begin
      [*] = ;         gArrRollerN[i] := i + 1;
      [*] = ;         n := n + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if n <> 0 then
      [*] = ;      i := 0;
      [*] = ;end;
      [*] = ;if i <> count then
      [*] = ;   i := _rand_Roll_VVK(false)-1
      [*] = ;else
      [*] = ;   i := _rand_Random(count);
      [*] = ;
      [*] = ;ParserSetValueByKeyByHandle(pMyParser, 'Portrait', ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pHeroNames, i), 'Portrait'));
      [*] = ;if _log then _Log_map('Hero portrait: '+ParserGetValueByKeyByHandle(pMyParser, 'Portrait'));
      [*] = ;
      [*] = ;ParserAddChildByIndex(pMyParser, 'Units');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Spells');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Skills');
      [*] = ;
      [*] = ;ParserAddChildByIndex(pMyParser, 'EnemyTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'NeutralTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'PassableTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'EnemyPassTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'SiteTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'SiegeTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'RuinSiegeTargets');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Quests');
      [*] = ;// Index = Integer
      [*] = ;// Complete = Boolean
      [*] = ;// ProvIndex = Integer
      [*] = ;// SiteIndex = Integer
      [*] = ;// Time = Integer
      [*] = ;// Found = Integer
      [*] = ;// ArProgress : array
      [*] = ;//    Progress = Integer
      [*] = ;
      [*] = ;// setting hero inventory
      [*] = ;var pMyDoll : Integer = ParserAddChildByIndex(pMyParser, 'Doll');
      [*] = ;
      [*] = ;for i := 0 to gc_HeroInventoryCount-1 do
      [*] = ;begin
      [*] = ;   var pMyDollItem : Integer = ParserAddChildByIndex(pMyDoll, '*');
      [*] = ;
      [*] = ;   case i of
      [*] = ;      0  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 9);
      [*] = ;      1  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 4);
      [*] = ;      2  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 6);
      [*] = ;      3  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 1);
      [*] = ;      4  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 12);
      [*] = ;      5  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 10);
      [*] = ;      6  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 3);
      [*] = ;      7  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 5);
      [*] = ;      8  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 2);
      [*] = ;      9  : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 13);
      [*] = ;      10 : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 10);
      [*] = ;      11 : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 8);
      [*] = ;      12 : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 7);
      [*] = ;      13, 14, 15, 16 : ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 11)
      [*] = ;      else ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemSlot', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyDollItem, 'ItemID', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyDollItem, 'Durability', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;ParserAddChildByIndex(pMyParser, 'SiteLootItems');
      [*] = ;ParserAddChildByIndex(pMyParser, 'LeftLootItems');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

