section.begin
   Name = EvLanConnect
   Code : struct.begin
      [*] = ;var tag : Integer;
      [*] = ;var status : String = GetValueByName('status');
      [*] = ;var press : String = GetValueByName('press');
      [*] = ;
      [*] = ;if status='shortcut' then
      [*] = ;begin
      [*] = ;   // keyboard event
      [*] = ;   case GetValueByName('key') of
      [*] = ;      'escape' : tag := 100;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if status='button' then
      [*] = ;   begin
      [*] = ;      // Button press
      [*] = ;      if press = 'c' then
      [*] = ;         tag := GetIntValueByName('tag');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;case tag of
      [*] = ;   10 : begin
      [*] = ;      // Cannot connect to server - Terminate connecting
      [*] = ;      gConnectIPIndex := -1;
      [*] = ;      LanShutdown();
      [*] = ;      _lan_timer_Reset(gc_lt_ALL,true,'MENU.INC\EVLANCONNECT');
      [*] = ;      _gui_RootWindowRemoveWithFade(_gui_GetWindow(cQuestionDialogWindowName),gc_gui_FadeTime0_2);
      [*] = ;      //_gui_RootWindowRemoveWithFade(_gui_GetWindow('internetshell'),gc_gui_FadeTime0_2); // inetshell window removed via LanShutdown
      [*] = ;      
      [*] = ;      if ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle)) and ((gIntRegister_CurGameMode = gc_GameModeStrategy) or (gIntRegister_CurGameMode = gc_GameModeStrategy)) then
      [*] = ;      begin
      [*] = ;         _misc_ParserGetOrCreateByKey('LanSync', true);
      [*] = ;         _run_DoCreateMenu(); // exit to menu when cancelling attempt to reconnect to online game
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('NewGame'), gc_gui_FadeTime0_2);
      [*] = ;      
      [*] = ;         var chatBlink : Boolean;
      [*] = ;         _gui_RemoveBlinkElement('btnOpenChatBlink', chatBlink);
      [*] = ;      
      [*] = ;         if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) then
      [*] = ;            _cmd_Post('menuaction','multiplayer','');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   20 : begin
      [*] = ;      gConnectIPIndex := -1;
      [*] = ;      LanShutdown();
      [*] = ;
      [*] = ;      if IsFileExists('update.exe') then
      [*] = ;         SwitchApplication('update.exe', GetBuildVersion + ';' + GetLocaleTableItem('CURRENT.LOCALE')+';'+gConnectHost)
      [*] = ;      else
      [*] = ;         _run_ExitGame();
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

