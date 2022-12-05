section.begin
   Name = UnitFromArrayToParser
   Description : struct.begin
      [*] = ;IntRegister0 - dst parser
      [*] = ;IntRegister1 - cfg parser
      [*] = ;IntRegister2 - owner map object UID or 0 if none
      [*] = ;StringRegister0 - unit pars string array
      [*] = ;StringRegister1 - unit pars names array
      [*] = ;StringRegister2 - unit upgrades string array
      [*] = ;StringRegister3 - unit medals string array
   struct.end
   Code : struct.begin
      [*] = ;var dst_p : Integer = IntRegister0;
      [*] = ;var cfg_p : Integer = IntRegister1;
      [*] = ;var owner_uid : Integer = IntRegister2;
      [*] = ;var src_s : String = StringRegister0;
      [*] = ;var src_sn : String = StringRegister1;
      [*] = ;var src_su : String = StringRegister2;
      [*] = ;var src_sm : String = StringRegister3;
      [*] = ;var s,sn : String;
      [*] = ;var i,sp,p,no : Integer;
      [*] = ;
      [*] = ;sp := ParserSelectByHandleByKey(cfg_p,'UnitStack');
      [*] = ;for i := 0 to ParserGetCountByHandle(sp)-1 do
      [*] = ;begin
      [*] = ;   p := ParserSelectByHandleByIndex(sp,i);
      [*] = ;   if ParserGetIntValueByKeyByHandle(p,'Default') <> 0 then
      [*] = ;      ParserSetValueByKeyByHandle(dst_p,ParserGetValueByKeyByHandle(p,'ImpexName'),ParserGetValueByKeyByHandle(p,'DefaultValue'));
      [*] = ;end;
      [*] = ;
      [*] = ;no := _sa_GetNum(src_s);
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   _sa_Get(src_s,i,s);
      [*] = ;   if s <> '' then
      [*] = ;   begin
      [*] = ;      _sa_Get(src_sn,i,sn);
      [*] = ;      ParserSetValueByKeyByHandle(dst_p,sn,s);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;ParserSetFloatValueByKeyByHandle(dst_p,'FCurLife',ParserGetIntValueByKeyByHandle(dst_p,'CurLife'));
      [*] = ;
      [*] = ;no := ParserGetIntValueByKeyByHandle(dst_p,'Level');
      [*] = ;if (no <> 0) and (ParserGetIntValueByKeyByHandle(dst_p,'Exp') = 0) then
      [*] = ;begin
      [*] = ;   if owner_uid <> 0 then
      [*] = ;      owner_uid := GetGameObjectHandleByUniqueId(owner_uid);
      [*] = ;   ParserSetIntValueByKeyByHandle(dst_p,'Exp',_unit_GetNeededExpForLevel(no,ParserGetIntValueByKeyByHandle(dst_p,'UnitID'),owner_uid))
      [*] = ;end;
      [*] = ;
      [*] = ;sp := ParserAddChildByIndex(dst_p,'Upgrades');
      [*] = ;no := _sa_GetNum(src_su);
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   p := ParserAddChildByIndex(sp,'*');
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'UpgradeID',_sa_GetAsInt(src_su,i));
      [*] = ;end;
      [*] = ;
      [*] = ;sp := ParserAddChildByIndex(dst_p,'Medals');
      [*] = ;no := _sa_GetNum(src_sm);
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   p := ParserAddChildByIndex(sp,'*');
      [*] = ;   ParserSetIntValueByKeyByHandle(p,'MedalID',_sa_GetAsInt(src_sm,i));
      [*] = ;end;
   struct.end
section.end
