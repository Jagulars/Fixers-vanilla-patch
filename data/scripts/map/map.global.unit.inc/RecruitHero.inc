section.begin
   Name = RecruitHero
   Description : struct.begin
      [*] = ;IntRegister0 - hero class
      [*] = ;   if hero class < 0 then next three parameters are valid:
      [*] = ;IntRegister1 - province index where to spawn, -1 for castle province
      [*] = ;IntRegister2 - creation mode
      [*] = ;   &1 - do initial skills, army and spells setup
      [*] = ;StringRegister0 - object base name
      [*] = ;BoolRegister0 - pay for hero or not
      [*] = ;RET:
      [*] = ;   IntRegister0 - hero index
      [*] = ;   IntRegister1 - hero handle
      [*] = ;   IntRegister2 - hero uid
      [*] = ;   IntRegister3 - hero province uid
   struct.end
   Code : struct.begin
      [*] = ;procedure TakeItem(goHandle, itemID : Integer);
      [*] = ;begin
      [*] = ;   IntRegister0 := itemID;
      [*] = ;   MapExecuteState('GetItemParserByID');
      [*] = ;   IntRegister0 := itemID;
      [*] = ;   IntRegister1 := ParserGetIntValueByKeyByHandle( IntRegister1, 'Durability');
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'TakeLootItem');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure TakeUnit(goHandle, unitID, battleX, battleY : Integer);
      [*] = ;begin
      [*] = ;   IntRegister0 := ParserGetIntValueByKeyByHandle(_unit_GetUnitParserByID(unitID), 'Rank');
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetFreeUnitSlot');
      [*] = ;   if (IntRegister2 <> - 1) and (IntRegister3 <> -1) then
      [*] = ;   begin
      [*] = ;      IntRegister3 := IntRegister2;      // slot index
      [*] = ;      IntRegister2 := IntRegister1;      // slot rank
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister0 := unitID;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'AddUnitToArmy');
      [*] = ;      ParserSetIntValueByKeyByHandle( IntRegister0, 'BattleX', battleX);
      [*] = ;      ParserSetIntValueByKeyByHandle( IntRegister0, 'BattleY', battleY);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure TakeSpell(goHandle, spellID : Integer);
      [*] = ;begin
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetFreeSpellSlot');
      [*] = ;   IntRegister2 := IntRegister1;
      [*] = ;   IntRegister1 := IntRegister0;
      [*] = ;   IntRegister0 := spellID;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'AddSpellToSpellbook');
      [*] = ;end;
      [*] = ;
      [*] = ;var heroClass : Integer = IntRegister0;
      [*] = ;var pSpawnCellIndex : Integer = IntRegister1;
      [*] = ;var creation_flags : Integer = IntRegister2;
      [*] = ;var objectName : String = StringRegister0;
      [*] = ;var pay : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\RECRUITHERO';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var baseName : String;
      [*] = ;var goHandle, goUID, goIndex, pStratHexCell,provUID : Integer;
      [*] = ;var gold,gem : Integer;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;if heroClass > 0 then
      [*] = ;begin
      [*] = ;   pSpawnCellIndex := -1;
      [*] = ;   creation_flags := $ffff;
      [*] = ;   baseName := '';
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   heroClass := -1*heroClass;
      [*] = ;   baseName := objectName;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[CLASS:'+IntToStr(heroClass)+',SI:'+IntToStr(pSpawnCellIndex)+',NM:'+baseName+']',_log_trace);
      [*] = ;
      [*] = ;if baseName = '' then
      [*] = ;begin
      [*] = ;   case heroClass of
      [*] = ;      1 : baseName := 'map.warrior';
      [*] = ;      //1 : baseName := 'map.goblin';
      [*] = ;      2 : baseName := 'map.scout';
      [*] = ;      3 : baseName := 'map.commander';
      [*] = ;      4 : baseName := 'map.wizard';
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if pSpawnCellIndex = -1 then
      [*] = ;begin
      [*] = ;   ExecuteState('GetCastleParser');
      [*] = ;   pStratHexCell := IntRegister0;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var i,p : Integer;
      [*] = ;   p := gStratHexCells.handle;
      [*] = ;   for i := 0 to ParserGetCountByHandle(p)-1 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(p,i);
      [*] = ;      if ParserGetIntValueByKeyByHandle(pStratHexCell,'Index') = pSpawnCellIndex then
      [*] = ;         break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;provUID := ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;if _log then _Log_map('Idx: '+IntToStr(ParserGetIntValueByKeyByHandle(pStratHexCell,'Index'))+', pUID: '+IntToStr(provUID)+', Castle: '+ParserGetValueByKeyByHandle(pStratHexCell,'Castle'));
      [*] = ;
      [*] = ;if pay then
      [*] = ;begin
      [*] = ;   IntRegister0 := heroClass;
      [*] = ;   ExecuteState('GetHeroPrice');
      [*] = ;   gold := IntRegister1;
      [*] = ;   gem := IntRegister2;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   gold := 0;
      [*] = ;   gem := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not pay) or (((plGold >= gold) or (gold=0)) and ((plGem >= gem) or (gem=0))) then
      [*] = ;begin
      [*] = ;   var x0,y0 : Float;
      [*] = ;   var pGOParser,pGOUnit,p : Integer;
      [*] = ;
      [*] = ;   if pay then
      [*] = ;   begin
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold-gold);
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem-gem);
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Hero stand not in province center
      [*] = ;   _misc_GetProvinceHeroCoords(pStratHexCell,x0,y0);
      [*] = ;   if _log then _Log_Map('PosX: '+FloatToStr(x0)+', PosY: '+FloatToStr(y0));
      [*] = ;   goHandle := _obj_GetRecycledOrCreate(myPlHandle, GetPlayerRaceNameByHandle(myPlHandle), baseName, x0, 0, y0);
      [*] = ;   goUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;   goIndex := GetGameObjectIndexByHandle(goHandle);
      [*] = ;
      [*] = ;   pGOParser := ParserSelectGameObject(goHandle);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID, provUID);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iBeforeTargetUID, provUID);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iReachUID, provUID);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID, provUID);
      [*] = ;
      [*] = ;   GroupAddGameObjectByHandle(CreateGroupByPlHandle(myPlHandle, 'group.' + IntToStr(GetPlayerCountOfGroupsByHandle(myPlHandle))), goHandle);
      [*] = ;
      [*] = ;   // set hero skills for different classes
      [*] = ;   var pGOArmy : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;   var pGOSkills : Integer = ParserAddChildByIndex(pGOParser, 'Skills');
      [*] = ;   var pGODoll : Integer = ParserAddChildByIndex(pGOParser, 'Doll');
      [*] = ;   var pGOSpells : Integer = ParserAddChildByIndex(pGOParser, 'Spells');
      [*] = ;
      [*] = ;   if ((creation_flags and 1) <> 0) then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'CalcLevel');
      [*] = ;      var armyCount : Integer;
      [*] = ;      var pArmyUnit : Integer;
      [*] = ;      var itemID : Integer;
      [*] = ;      var skillID : Integer;
      [*] = ;      var slotRank : Integer;
      [*] = ;      var slotIndex : Integer;
      [*] = ;      var pGOSpell : Integer;
      [*] = ;      var upgradeID : Integer = 0;
      [*] = ;
      [*] = ;      case heroClass of
      [*] = ;         1 : begin
      [*] = ;            pArmyUnit := ParserSelectByHandleByIndex(pGOArmy, 0);
      [*] = ;            ParserSetIntValueByKeyByHandle(pArmyUnit, 'BattleX', 1);
      [*] = ;
      [*] = ;            skillID := Floor(8 + RandomExt * 7);
      [*] = ;
      [*] = ;            TakeItem(goHandle, 9 + 4 * Floor(RandomExt * 3));
      [*] = ;            TakeItem(goHandle, 41 + Floor(RandomExt * 2));
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            pArmyUnit := ParserSelectByHandleByIndex(pGOArmy, 0);
      [*] = ;            ParserSetIntValueByKeyByHandle(pArmyUnit, 'BattleX', 0);
      [*] = ;
      [*] = ;            upgradeID := 62 + Floor(RandomExt() * 3);
      [*] = ;            skillID := Floor(22 + RandomExt() * 7);
      [*] = ;
      [*] = ;            TakeItem(goHandle, 29);
      [*] = ;            TakeItem(goHandle, 46);
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            pArmyUnit := ParserSelectByHandleByIndex(pGOArmy, 0);
      [*] = ;            ParserSetIntValueByKeyByHandle(pArmyUnit, 'BattleX', 1);
      [*] = ;
      [*] = ;            skillID := Floor(1 + RandomExt() * 7);
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            skillID := Floor(15 + RandomExt() * 7);
      [*] = ;
      [*] = ;            TakeSpell(goHandle, 1);
      [*] = ;            TakeSpell(goHandle, Floor(2 + RandomExt() * 2));
      [*] = ;            TakeSpell(goHandle, 4);
      [*] = ;            TakeSpell(goHandle, Floor(4 + RandomExt() * 10));
      [*] = ;
      [*] = ;            case skillID of
      [*] = ;               15 :
      [*] = ;               begin
      [*] = ;                  TakeItem(goHandle, 5);
      [*] = ;               end;
      [*] = ;               16 : begin
      [*] = ;                  pGOSpell := ParserSelectByHandleByIndex(pGOSpells, 1);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOSpell, 'SpellID', 11);
      [*] = ;               end;
      [*] = ;               17 :
      [*] = ;               begin
      [*] = ;                  pGOSpell := ParserSelectByHandleByIndex(pGOSpells, 2);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOSpell, 'SpellID', 19);
      [*] = ;                  TakeItem(goHandle, 63);
      [*] = ;               end;
      [*] = ;               18 : begin
      [*] = ;                  pGOSpell := ParserSelectByHandleByIndex(pGOSpells, 1);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOSpell, 'SpellID', 13);
      [*] = ;               end;
      [*] = ;               19 : begin
      [*] = ;                  TakeSpell(goHandle, 63);
      [*] = ;               end;
      [*] = ;               20 :
      [*] = ;               begin
      [*] = ;                  TakeItem(goHandle, 37);
      [*] = ;               end;
      [*] = ;               21 :
      [*] = ;               begin
      [*] = ;                  pGOSpell := ParserSelectByHandleByIndex(pGOSpells, 2);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOSpell, 'SpellID', 14);
      [*] = ;                  TakeItem(goHandle, 1);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      p := ParserAddChildByIndex(pGOSkills, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'SkillID', skillID);
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'Level', 1);
      [*] = ;
      [*] = ;      IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iIndex);
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'AddUnitToArmy');
      [*] = ;      armyCount := ParserGetCountByHandle(pGOArmy);
      [*] = ;      pArmyUnit := ParserSelectByHandleByIndex(pGOArmy, armyCount-1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pArmyUnit, 'BattleX', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pArmyUnit, 'BattleY', 3);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pArmyUnit, 'IsHero', true);
      [*] = ;      ParserSetIntValueByKeyByHandle(pArmyUnit, 'HeroUID', goUID);
      [*] = ;
      [*] = ;      if upgradeID <> 0 then
      [*] = ;      begin
      [*] = ;         p := ParserAddChildByIndex(ParserSelectByHandleByKey(pArmyUnit, 'Upgrades'), '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(p, 'UpgradeID', upgradeID);
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := gc_map_hero_iLife;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurHP, IntRegister1);
      [*] = ;      SetGameObjectFloatValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_fCurToMaxLife, 1);
      [*] = ;
      [*] = ;      if heroClass = 3 then
      [*] = ;      begin
      [*] = ;         case skillID of
      [*] = ;            1 : begin
      [*] = ;               TakeUnit(goHandle, 3, 1, 2);
      [*] = ;               TakeItem(goHandle, 51);
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               TakeUnit(goHandle, 1, 1, 2);
      [*] = ;               TakeUnit(goHandle, 3, 1, 5);
      [*] = ;            end;
      [*] = ;            5 : begin
      [*] = ;               TakeUnit(goHandle, 2, 0, 2);
      [*] = ;            end;
      [*] = ;            else begin
      [*] = ;               TakeUnit(goHandle, 3, 1, 2);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      TakeUnit(goHandle, 1, 1, 4);
      [*] = ;      TakeUnit(goHandle, 2, 0, 4);
      [*] = ;   end;
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iUpdate, 1);
      [*] = ;   _map_RefreshProvinceHUD(provUID);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   goHandle := 0;
      [*] = ;   goUID := 0;
      [*] = ;   goIndex := 0;
      [*] = ;   provUID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[I:'+IntToStr(goIndex)+',UID:'+IntToStr(goUID)+', PROV: '+IntToStr(provUID)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister0 := goIndex;
      [*] = ;IntRegister1 := goHandle;
      [*] = ;IntRegister2 := goUID;
      [*] = ;IntRegister3 := provUID;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

