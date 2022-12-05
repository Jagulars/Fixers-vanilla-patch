section.begin
   Name = GetHeroImportData
   Description : struct.begin
      [*] = ;BoolRegister0 - true if export should be into gCampMapHero global
      [*] = ;IntRegister0 - parser (only if BoolRegister0 is false)
      [*] = ;IntRegister1 - cfg parser (editor_impex_data.cfg)
      [*] = ;IntRegister2 - global map import parser (only if BoolRegister0 is false)
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\GETHEROIMPORTDATA';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = false;
      [*] = ;var import_from_global : Boolean = BoolRegister0;
      [*] = ;var obj_p : Integer = IntRegister0;
      [*] = ;var this_h : Integer = IntRegister1;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var i,ind,j,p,p2,id,sp,dp,no,uid,this_p : Integer;
      [*] = ;var s,su,sn,sm : String;
      [*] = ;
      [*] = ;if this_h <> 0 then
      [*] = ;begin
      [*] = ;   this_p := ParserSelectGameObject(this_h);
      [*] = ;   uid := GetGameObjectUniqueIdByHandle(this_h);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   this_p := _misc_ParserGetOrCreateByKey('astral_hero',true);
      [*] = ;   ParserAddChildByIndex(this_p,'Skills');
      [*] = ;   ParserAddChildByIndex(this_p,'Spells');
      [*] = ;   ParserAddChildByIndex(this_p,'Doll');
      [*] = ;   ParserAddChildByIndex(this_p,'Units');
      [*] = ;end;
      [*] = ;
      [*] = ;var cfg_p : Integer = _misc_ParserGetOrCreateByKey('MapExportConfig',false);
      [*] = ;if ParserSelectByHandleByKey(cfg_p,'ProvinceRecordsToExport') = 0 then
      [*] = ;   ParserLoadFromFileByHandle(cfg_p,'.\data\game\var\editor_impex_data.cfg');
      [*] = ;
      [*] = ;sp := ParserSelectByHandleByKey(cfg_p,'HeroStack');
      [*] = ;if not import_from_global then
      [*] = ;begin
      [*] = ;   dp := ParserSelectByHandleByKey(obj_p,'HeroStack');
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(sp)-1 do
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByIndex(sp,i);
      [*] = ;      s := ParserGetValueByKeyByHandle(p,'ImpexName');
      [*] = ;      case ParserGetIntValueByKeyByHandle(p,'Type') of
      [*] = ;         0 : SetGameObjectValueIndByHandle(this_h,ParserGetIntValueByKeyByHandle(p,'IngameIndex'),ParserGetValueByKeyByHandle(dp,s));
      [*] = ;         1 : SetGameObjectIntValueIndByHandle(this_h,ParserGetIntValueByKeyByHandle(p,'IngameIndex'),ParserGetIntValueByKeyByHandle(dp,s));
      [*] = ;         2 : SetGameObjectFloatValueIndByHandle(this_h,ParserGetIntValueByKeyByHandle(p,'IngameIndex'),ParserGetFloatValueByKeyByHandle(dp,s));
      [*] = ;         3 : SetGameObjectBoolValueIndByHandle(this_h,ParserGetIntValueByKeyByHandle(p,'IngameIndex'),ParserGetBoolValueByKeyByHandle(dp,s));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetGameObjectIntValueIndByHandle(this_h,gc_map_GOStack_MapUnit_iClassInd1,ParserGetIntValueByKeyByHandle(obj_p,'HeroClass'));
      [*] = ;   p := ParserSelectByHandleByIndex(gStratHexCells.handle,ParserGetIntValueByKeyByHandle(obj_p,'SpawnIndex'));
      [*] = ;   SetGameObjectIntValueIndByHandle(this_h,gc_map_GOStack_MapUnit_iCurrentUID,ParserGetIntValueByKeyByHandle(p,'DummyUID'));
      [*] = ;   SetGameObjectIntValueIndByHandle(this_h,gc_map_GOStack_MapUnit_iCastleDist,ParserGetIntValueByKeyByHandle(p,'CastleDist'));
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   su := gCampMapHero.stack;
      [*] = ;   for i := 0 to ParserGetCountByHandle(sp)-1 do
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByIndex(sp,i);
      [*] = ;      _sa_Get(su,i,sn);
      [*] = ;      ind := ParserGetIntValueByKeyByHandle(p,'IngameIndex');
      [*] = ;      s := ParserGetValueByKeyByHandle(p,'ImpexName');
      [*] = ;      case ParserGetIntValueByKeyByHandle(p,'Type') of
      [*] = ;         0 : begin
      [*] = ;            if this_h <> 0 then
      [*] = ;            SetGameObjectValueIndByHandle(this_h,ind,sn);
      [*] = ;            ParserSetValueByKeyByHandle(this_p,s,sn);
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            if this_h <> 0 then
      [*] = ;            SetGameObjectIntValueIndByHandle(this_h,ind,StrToInt(sn));
      [*] = ;            ParserSetIntValueByKeyByHandle(this_p,s,StrToInt(sn));
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            if this_h <> 0 then
      [*] = ;            SetGameObjectFloatValueIndByHandle(this_h,ind,StrToFloat(sn));
      [*] = ;            ParserSetFloatValueByKeyByHandle(this_p,s,StrToFloat(sn));
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            if this_h <> 0 then
      [*] = ;            SetGameObjectBoolValueIndByHandle(this_h,ind,StrToBool(sn));
      [*] = ;            ParserSetBoolValueByKeyByHandle(this_p,s,StrToBool(sn));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if this_h <> 0 then
      [*] = ;   SetGameObjectIntValueIndByHandle(this_h,gc_map_GOStack_MapUnit_iClassInd1,gCampMapHero.hero_class);
      [*] = ;end;
      [*] = ;if this_h <> 0 then
      [*] = ;begin
      [*] = ;   SetGameObjectIntValueIndByHandle(this_h,gc_map_GOStack_MapUnit_iUpdate, 1);
      [*] = ;   SetGameObjectIntValueIndByHandle(this_h,gc_map_GOStack_MapUnit_iUID,uid);
      [*] = ;end;
      [*] = ;
      [*] = ;sp := ParserSelectByHandleByKey(cfg_p,'HeroParser');
      [*] = ;if not import_from_global then
      [*] = ;begin
      [*] = ;   for i := 0 to ParserGetCountByHandle(sp)-1 do
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByIndex(sp,i);
      [*] = ;      s := ParserGetValueByKeyByHandle(p,'Name');
      [*] = ;      case ParserGetIntValueByKeyByHandle(p,'Type') of
      [*] = ;         0 : ParserSetValueByKeyByHandle(this_p,s,ParserGetValueByKeyByHandle(obj_p,s));
      [*] = ;         1 : ParserSetIntValueByKeyByHandle(this_p,s,ParserGetIntValueByKeyByHandle(obj_p,s));
      [*] = ;         2 : ParserSetFloatValueByKeyByHandle(this_p,s,ParserGetFloatValueByKeyByHandle(obj_p,s));
      [*] = ;         3 : ParserSetBoolValueByKeyByHandle(this_p,s,ParserGetBoolValueByKeyByHandle(obj_p,s));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   su := gCampMapHero.parser;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(sp)-1 do
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByIndex(sp,i);
      [*] = ;      s := ParserGetValueByKeyByHandle(p,'Name');
      [*] = ;      _sa_Get(su,i,sn);
      [*] = ;      case ParserGetIntValueByKeyByHandle(p,'Type') of
      [*] = ;         0 : ParserSetValueByKeyByHandle(this_p,s,sn);
      [*] = ;         1 : ParserSetIntValueByKeyByHandle(this_p,s,StrToInt(sn));
      [*] = ;         2 : ParserSetFloatValueByKeyByHandle(this_p,s,StrToFloat(sn));
      [*] = ;         3 : ParserSetBoolValueByKeyByHandle(this_p,s,StrToBool(sn));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;dp := ParserSelectByHandleByKey(this_p,'Skills');
      [*] = ;ParserClearByHandle(dp);
      [*] = ;if not import_from_global then
      [*] = ;   s := ParserGetValueByKeyByHandle(obj_p,'SkillsList')
      [*] = ;else
      [*] = ;   s := gCampMapHero.skills;
      [*] = ;no := _sa_GetNum(s) div 2;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   p := ParserAddChildByIndex(dp,'*');
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'SkillID',_sa_GetAsInt(s,i*2));
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'Level',_sa_GetAsInt(s,i*2+1));
      [*] = ;end;
      [*] = ;
      [*] = ;dp := ParserSelectByHandleByKey(this_p,'Spells');
      [*] = ;ParserClearByHandle(dp);
      [*] = ;s := ParserGetValueByKeyByHandle(obj_p,'SpellsList');
      [*] = ;if not import_from_global then
      [*] = ;   s := ParserGetValueByKeyByHandle(obj_p,'SpellsList')
      [*] = ;else
      [*] = ;   s := gCampMapHero.spells;
      [*] = ;no := _sa_GetNum(s) div 3;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   p := ParserAddChildByIndex(dp,'*');
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'SpellID',_sa_GetAsInt(s,i*3));
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'SlotLevel',_sa_GetAsInt(s,i*3+1));
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'Slotindex',_sa_GetAsInt(s,i*3+2));
      [*] = ;end;
      [*] = ;
      [*] = ;if not import_from_global then
      [*] = ;   s := ParserGetValueByKeyByHandle(obj_p,'DollList')
      [*] = ;else
      [*] = ;   s := gCampMapHero.doll;
      [*] = ;
      [*] = ;no := _sa_GetNum(s) div 3;
      [*] = ;dp := ParserSelectByHandleByKey(this_p,'Doll');
      [*] = ;if this_h = 0 then
      [*] = ;for i := 0 to no-1 do
      [*] = ;   p := ParserAddChildByIndex(dp,'*');
      [*] = ;   
      [*] = ;for i := 0 to ParserGetCountByHandle(dp)-1 do
      [*] = ;begin
      [*] = ;   p := ParserSelectByHandleByIndex(dp,i);
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'ItemID',0);
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   id := _sa_GetAsInt(s,i*3);
      [*] = ;   for j := 0 to ParserGetCountByHandle(dp)-1 do
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByIndex(dp,j);
      [*] = ;      if ((ParserGetIntValueByKeyByHandle(p,'ItemSlot') = id) or (this_h = 0)) and (ParserGetIntValueByKeyByHandle(p,'ItemID') = 0) then
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'ItemID',_sa_GetAsInt(s,i*3+1));
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'Durability',_sa_GetAsInt(s,i*3+2));
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;dp := ParserSelectByHandleByKey(this_p,'Units');
      [*] = ;if dp = 0 then
      [*] = ;   dp := ParserAddChildByIndex(this_p,'Units')
      [*] = ;else
      [*] = ;   ParserClearByHandle(dp);
      [*] = ;if not import_from_global then
      [*] = ;begin
      [*] = ;   sp := ParserSelectByHandleByKey(obj_p,'Units');
      [*] = ;   no := ParserGetCountByHandle(sp) div 3;
      [*] = ;end
      [*] = ;else
      [*] = ;   no := gCampMapHero.units_no;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   if not import_from_global then
      [*] = ;   begin
      [*] = ;      s := ParserGetValueByKeyByHandle(sp,'Unit_'+IntToStr(i));
      [*] = ;      su := ParserGetValueByKeyByHandle(sp,'UnitUpgrades_'+IntToStr(i));
      [*] = ;      sn := ParserGetValueByKeyByHandle(sp,'UnitKeys_'+IntToStr(i));
      [*] = ;      sm := ParserGetValueByKeyByHandle(sp,'UnitMedals_'+IntToStr(i));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      s := gCampMapHero.units[i].values;
      [*] = ;      su := gCampMapHero.units[i].upgrades;
      [*] = ;      sn := gCampMapHero.units[i].keys;
      [*] = ;      sm := gCampMapHero.units[i].medals;
      [*] = ;   end;
      [*] = ;   p := ParserAddChildByIndex(dp,'*');
      [*] = ;   IntRegister0 := p;
      [*] = ;   IntRegister1 := cfg_p;
      [*] = ;   IntRegister2 := GetGameObjectUniqueIdByHandle(this_h);
      [*] = ;   StringRegister0 := s;
      [*] = ;   StringRegister1 := sn;
      [*] = ;   StringRegister2 := su;
      [*] = ;   StringRegister3 := sm;
      [*] = ;   MapExecuteState('UnitFromArrayToParser');
      [*] = ;   if ParserGetBoolValueByKeyByHandle(p,'IsHero') then
      [*] = ;   begin
      [*] = ;      if this_h <> 0 then
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'HeroUID',GetGameObjectUniqueIdByHandle(this_h));
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'HeroClass1',GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iClassInd1));
      [*] = ;         ParserSetIntValueByKeyByHandle(p,'HeroClass2',GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iClassInd2));
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(this_p,'Class1',gCampMapHero.hero_class);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if not import_from_global then
      [*] = ;   ParserSetValueByKeyByHandle(this_p,'HeroMapTriggers',ParserGetValueByKeyByHandle(obj_p,'HeroMapTriggers'));
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

