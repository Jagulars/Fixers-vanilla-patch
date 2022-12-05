section.begin
   Name = GetGoldAndGemTaste
   Description : struct.begin
      [*] = IntRegister0 - item ID
      [*] = IntRegister1 - item durability
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;//var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;
      [*] = ;var goldTaste, gemTaste : Float = 1.0;
      [*] = ;
	  [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;if not bImprovedAI then
      [*] = ;begin
      [*] = ;{var plGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;var goldIncIrreg : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldIncIrreg);
      [*] = ;var goldInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;var gemInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;var gemIncIrreg : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemIncIrreg);
      [*] = ;var goldLimit : Integer = Max(50, GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldLimit));
      [*] = ;var gemLimit : Integer = Max(20, GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemLimit));
      [*] = ;   
      [*] = ;var maxGoldMod : Integer = goldLimit div 50;
      [*] = ;var maxGemMod : Integer = gemLimit div 20;
      [*] = ;   
      [*] = ;var surplus : Integer = gold - goldLimit;
      [*] = ;if surplus < 0 then
      [*] = ;   goldTaste := 1 + Abs(surplus) / goldLimit
      [*] = ;else
      [*] = ;   goldTaste := goldLimit / gold;
      [*] = ;   
      [*] = ;surplus := gem - gemLimit;
      [*] = ;if surplus < 0 then
      [*] = ;   gemTaste := 1 + Abs(surplus) / gemLimit
      [*] = ;else
      [*] = ;   gemTaste := 1 + gemLimit / gem;
      [*] = ;         
      [*] = ;goldTaste := Clamp(goldTaste, 0, maxGoldMod);
      [*] = ;gemTaste := Clamp(gemTaste, 0, maxGemMod);}
      [*] = ;end;
      [*] = ;
      [*] = ;FloatRegister0 := goldTaste;
      [*] = ;FloatRegister1 := gemTaste;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
