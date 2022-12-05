section.begin
   Name = CreateAIEvent
   Code : struct.begin
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;var profile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;if profile > 0 then
      [*] = ;begin
      [*] = ;   var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;   var karma : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Karma');
      [*] = ;   
      [*] = ;   ExecuteState('GetMood');
      [*] = ;   var mood : Integer = IntRegister0;
      [*] = ;   
      [*] = ;   if _rand_Random(100) - karma div 10 + mood * 10 > 50 then // simulate evil profitable decisions
      [*] = ;   begin
      [*] = ;      var goldGain, gemGain : Integer = 0;
      [*] = ;      
      [*] = ;      if karma = 0 then
      [*] = ;      begin
      [*] = ;         goldGain := goldGain + _rand_Random(100);
      [*] = ;         gemGain := gemGain + _rand_Random(20);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if karma < 0 then
      [*] = ;         goldGain := goldGain + _rand_Random(200)
      [*] = ;      else
      [*] = ;         gemGain := gemGain + _rand_Random(40);
      [*] = ;      
      [*] = ;      goldGain := goldGain + _rand_Random(200);
      [*] = ;      gemGain := gemGain + _rand_Random(40);
      [*] = ;      
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold + goldGain);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem + gemGain);
      [*] = ;
      [*] = ;      plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + goldGain);
      [*] = ;
      [*] = ;      plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gemGain);
      [*] = ;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;      if IntRegister0 <> pProvince then
      [*] = ;      begin
      [*] = ;         IntRegister0 := plHandle;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         ExecuteState('ChangeAttitude');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := plHandle;
      [*] = ;      IntRegister1 := 1;
      [*] = ;      ExecuteState('ChangeAttitude');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

