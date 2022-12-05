section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;ClearVariables();
      [*] = ;
      [*] = ;SetIntValueByName('amod', 0);
      [*] = ;SetBoolValueByName('auto', false);
      [*] = ;SetIntValueByName('lmod', 100);
      [*] = ;SetIntValueByName('cmod', 0);
      [*] = ;SetIntValueByName('gsp', 0);
      [*] = ;SetIntValueByName('mb', 0);
      [*] = ;SetIntValueByName('tuid', 0);
      [*] = ;SetBoolValueByName('pan', false);
      [*] = ;SetBoolValueByName('upl', true);
      [*] = ;SetIntValueByName('idle', gc_battle_idle_skip_global);
      [*] = ;SetBoolValueByName('csb', false);
      [*] = ;
      [*] = ;var pTowers : Integer = ParserAddChildByIndex(ParserCreatePlayer(GetPlayerCurrentPlHandle), 'Towers');
      [*] = ;ParserClearByHandle(pTowers);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

