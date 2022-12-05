section.begin
   Name = ShowProvinceInfo
   Description : struct.begin
      [*] = ;IntRegister0 - province parser handle
   struct.end
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;var mood : Integer = IntRegister0;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerUnrest');
      [*] = ;var unrest : Integer = IntRegister0;
      [*] = ;ParserSelectByHandle(pProvince);
      [*] = ;
      [*] = ;var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;var plInd : Integer = gIntRegister_MapMyPlayerIndex;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;var retStr : String = '';
      [*] = ;
      [*] = ;retStr := retStr + gc_gui_BreakLine +'___________Province info:___________';
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Index = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'Index'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    DummyUID = ' + IntToStr(dummyUID);
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Parser handle = ' + IntToStr(pProvince);
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    X = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'X'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Y = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'Y'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    CenterX = ' + FloatToStr(ParserGetFloatValueByKeyByHandle(pProvince, 'CenterX'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    CenterY = ' + FloatToStr(ParserGetFloatValueByKeyByHandle(pProvince, 'CenterY'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    TerrainType = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Player = ' + ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Castle = ' + BoolToStr(ParserGetBoolValueByKeyByHandle(pProvince, 'Castle'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    CastleDist = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'CastleDist'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ProvinceType = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceType'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ProvinceRace = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ProvinceName = ' + ParserGetValueByKeyByHandle(pProvince, 'ProvinceName');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Prefix = ' + ParserGetValueByKeyByHandle(pProvince, 'Prefix');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Suffix = ' + ParserGetValueByKeyByHandle(pProvince, 'Suffix');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ProvinceLevel = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Population = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'Population'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Fort = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'Fort'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    GoldInc = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'GoldInc'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    GemInc = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'GemInc'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Explored = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'Explored'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Resource = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'Resource'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Coast = ' + ParserGetValueByKeyByHandle(pProvince, 'Coast');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Port = ' + ParserGetValueByKeyByHandle(pProvince, 'Port');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ResourceExplore = ' + ParserGetValueByKeyByHandle(pProvince, 'ResourceExplore');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ResourceGuarded = ' + BoolToStr(ParserGetBoolValueByKeyByHandle(pProvince, 'ResourceGuarded'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Fog = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvFog, IntToStr(plInd)));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Mood = ' + IntToStr(mood);
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Unrest = ' + IntToStr(unrest);
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    PatternPlayer = ' + ParserGetValueByKeyByHandle(pProvince, 'PatternPlayer');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    PatternGroup = ' + ParserGetValueByKeyByHandle(pProvince, 'PatternGroup');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    MoveMap = ' + ParserGetValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    MobilMap = ' + ParserGetValueByKeyByHandle(pProvince, 'MobilMap');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    PrevPathInd = ' + ParserGetValueByKeyByHandle(pProvince, 'PrevPathInd');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    LastPlayer = ' + ParserGetValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Stable = ' + ParserGetValueByKeyByHandle(pProvince, 'Stable');
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    ActiveHUDHeroUID = ' + IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'ActiveHUDHeroUID'));
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    UpdatePlayer = ' + ParserGetValueByKeyByHandle(pProvince, 'UpdatePlayer');
      [*] = ;
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Neighbours : ';
      [*] = ;var pProvNeighbours : Integer = ParserSelectByHandleByKey(pProvince, 'Neighbours');
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvNeighbours)-1 do
      [*] = ;begin
      [*] = ;   var pProvNeighbour : Integer = ParserSelectByHandleByIndex(pProvNeighbours, i);
      [*] = ;   var ind : Integer = ParserGetIntValueByKeyByHandle(pProvNeighbour, 'Index');
      [*] = ;   var pNProvince : Integer = ParserSelectByHandleByIndex(pProvinces, ind);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'DummyUID');
      [*] = ;   retStr := retStr + gc_gui_BreakLine +'        DummyUID = ' + IntToStr(dummyUID);
      [*] = ;end;
      [*] = ;
      [*] = ;var pGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;var pGuardUnits : Integer = ParserSelectByHandleByKey(pGuard, 'Units');
      [*] = ;
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Guard : ';
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Dialog : ' + IntToStr(ParserGetIntValueByKeyByHandle(pGuard, 'Dialog'));
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pGuardUnits)-1 do
      [*] = ;begin
      [*] = ;   var pGuardUnit : Integer = ParserSelectByHandleByIndex(pGuardUnits, i);
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pGuardUnit, 'UnitID');
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pGuardUnit, 'CurLife');
      [*] = ;
      [*] = ;   if curLife > 0 then
      [*] = ;   begin
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'        [*] : ';
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           UnitID = ' + IntToStr(unitID);
      [*] = ;
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pUnit, 'Name');
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           Name = ' + name;
      [*] = ;      var level : Integer = ParserGetIntValueByKeyByHandle(pGuardUnit, 'Level');
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           Level = ' + IntToStr(level);
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           CurLife = ' + IntToStr(curLife);
      [*] = ;      
      [*] = ;      if level > 0 then
      [*] = ;      begin
      [*] = ;         var pUpgrades : Integer = ParserSelectByHandleByKey(pGuardUnit, 'Upgrades');
      [*] = ;         retStr := retStr + gc_gui_BreakLine +'           Upgrades : ';
      [*] = ;         for j := 0 to ParserGetCountByHandle(pUpgrades)-1 do
      [*] = ;         begin
      [*] = ;            var pUpgrade : Integer = ParserSelectByHandleByIndex(pUpgrades, j);
      [*] = ;            var upgradeID : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'UpgradeID');
      [*] = ;            var upgradeFreq : Float = ParserGetFloatValueByKeyByHandle(pUpgrade, 'Freq');
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'              [*] : ';
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'                 UpgradeID = ' + IntToStr(upgradeID);
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'                 Freq = ' + FloatToStr(upgradeFreq);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;var pDefenderUnits : Integer = ParserSelectByHandleByKey(pDefender, 'Units');
      [*] = ;
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Defender : ';
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pDefenderUnits)-1 do
      [*] = ;begin
      [*] = ;   var pDefenderUnit : Integer = ParserSelectByHandleByIndex(pDefenderUnits, i);
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pDefenderUnit, 'UnitID');
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pDefenderUnit, 'CurLife');
      [*] = ;
      [*] = ;   if curLife > 0 then
      [*] = ;   begin
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'        [*] : ';
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           UnitID = ' + IntToStr(unitID);
      [*] = ;
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;      var name : String = ParserGetValueByKeyByHandle(pUnit, 'Name');
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           Name = ' + name;
      [*] = ;      var level : Integer = ParserGetIntValueByKeyByHandle(pDefenderUnit, 'Level');
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           Level = ' + IntToStr(level);
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           CurLife = ' + IntToStr(curLife);
      [*] = ;      
      [*] = ;      if level > 0 then
      [*] = ;      begin
      [*] = ;         var pUpgrades : Integer = ParserSelectByHandleByKey(pDefenderUnit, 'Upgrades');
      [*] = ;         retStr := retStr + gc_gui_BreakLine +'           Upgrades : ';
      [*] = ;         for j := 0 to ParserGetCountByHandle(pUpgrades)-1 do
      [*] = ;         begin
      [*] = ;            var pUpgrade : Integer = ParserSelectByHandleByIndex(pUpgrades, j);
      [*] = ;            var upgradeID : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'UpgradeID');
      [*] = ;            var upgradeFreq : Float = ParserGetFloatValueByKeyByHandle(pUpgrade, 'Freq');
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'              [*] : ';
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'                 UpgradeID = ' + IntToStr(upgradeID);
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'                 Freq = ' + FloatToStr(upgradeFreq);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;
      [*] = ;retStr := retStr + gc_gui_BreakLine +'    Sites : ';
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pSites)-1 do
      [*] = ;begin
      [*] = ;   var pSite : Integer = ParserSelectByHandleByIndex(pSites, i);
      [*] = ;   retStr := retStr + gc_gui_BreakLine +'        [*] :';
      [*] = ;   retStr := retStr + gc_gui_BreakLine +'           SiteID = ' + IntToStr(ParserGetIntValueByKeyByHandle(pSite, 'SiteID'));
      [*] = ;
      [*] = ;   var pSiteGuard : Integer = ParserSelectByHandleByKey(pSite, 'Guard');
      [*] = ;   if pSiteGuard <> 0 then
      [*] = ;   begin
      [*] = ;      var pGuardUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;      retStr := retStr + gc_gui_BreakLine +'           Guard : ';
      [*] = ;      for j := 0 to ParserGetCountByHandle(pGuardUnits)-1 do
      [*] = ;      begin
      [*] = ;         var pGuardUnit : Integer = ParserSelectByHandleByIndex(pGuardUnits, j);
      [*] = ;         var name : String = ParserGetValueByKeyByHandle(pGuardUnit, 'UnitID');
      [*] = ;         retStr := retStr + gc_gui_BreakLine +'              [*] : ';
      [*] = ;         retStr := retStr + gc_gui_BreakLine +'              UnitID = ' + name;
      [*] = ;         var level : Integer = ParserGetIntValueByKeyByHandle(pGuardUnit, 'Level');
      [*] = ;         retStr := retStr + gc_gui_BreakLine +'              Level = ' + IntToStr(level);
      [*] = ;
      [*] = ;         if level > 0 then
      [*] = ;         begin
      [*] = ;            var pUpgrades : Integer = ParserSelectByHandleByKey(pGuardUnit, 'Upgrades');
      [*] = ;            retStr := retStr + gc_gui_BreakLine +'           Upgrades : ';
      [*] = ;            for k := 0 to ParserGetCountByHandle(pUpgrades)-1 do
      [*] = ;            begin
      [*] = ;               var pUpgrade : Integer = ParserSelectByHandleByIndex(pUpgrades, j);
      [*] = ;               var upgradeID : Integer = ParserGetIntValueByKeyByHandle(pUpgrade, 'UpgradeID');
      [*] = ;               var upgradeFreq : Float = ParserGetFloatValueByKeyByHandle(pUpgrade, 'Freq');
      [*] = ;               retStr := retStr + gc_gui_BreakLine +'              [*] : ';
      [*] = ;               retStr := retStr + gc_gui_BreakLine +'                 UpgradeID = ' + IntToStr(upgradeID);
      [*] = ;               retStr := retStr + gc_gui_BreakLine +'                 Freq = ' + FloatToStr(upgradeFreq);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;StringRegister0 := retStr;
   struct.end
section.end

