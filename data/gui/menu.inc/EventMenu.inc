section.begin
   Name = EventMenu
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const cBtnCampaign = $20001;
      [*] = ;const cBtnDemo = $20002;
      [*] = ;const cBtnCustomGame = $20003;
      [*] = ;const cBtnMultiplayer = $20004;
      [*] = ;const cBtnProfile = $20005;
      [*] = ;const cBtnSettings = $20006;
      [*] = ;const cBtnCredits = $20007;
      [*] = ;const cBtnEditor = 210+$20000;
      [*] = ;const cBtnTools = 236+$20000;
      [*] = ;const cBtnExit = $20008;
      [*] = ;const cBtnAchievements = $20009;
      [*] = ;// campaign menu
      [*] = ;const cBtnNewCampaign = 42+$20000;
      [*] = ;const cBtnCampContinue = 16+$20000;
      [*] = ;const cBtnLoadCampaign = 39+$20000;
      [*] = ;const cBtnBack = 11+$20000;
      [*] = ;// custom menu
      [*] = ;const cBtnNewCustom = 21+$20000;
      [*] = ;const cBtnCustContinue = 17+$20000;
      [*] = ;const cBtnLoadCustom = 13+$20000;
      [*] = ;const cBtnBookMasters = 14+$20000;
      [*] = ;// demo
      [*] = ;const cBtnBattle1 = 124 + $20000;
      [*] = ;const cBtnBattle2 = 125 + $20000;
      [*] = ;const cBtnBattle3 = 126 + $20000;
      [*] = ;const cBtnBattle4 = 10 + $20000;
      [*] = ;// multiplayer
      [*] = ;const cBtnInternetSettings = 225 + $20000;
      [*] = ;const cBtnInternetBattle = 156 + $20000;
      [*] = ;const cBtnInternetShard = 224 + $20000;
      [*] = ;const cBtnHotSeat = 157 + $20000;
      [*] = ;const cBtnShardHotSeat = 223 + $20000;
      [*] = ;const cBtnShardHotSeatLoad = 226 + $20000;
      [*] = ;const cBtnShardLanLoad = 227 + $20000;
      [*] = ;// tools
      [*] = ;const cBtnWindowDesigner = 237 + $20000;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if _log then Log('EventMenu: tag='+IntToStr(tag));
      [*] = ;   case tag of
      [*] = ;      cBtnCampaign : _cmd_Post('menumainbutton','campaign','');
      [*] = ;      cBtnDemo : _cmd_Post('menumainbutton','demo','');
      [*] = ;      cBtnCustomGame : _cmd_Post('menumainbutton','custom','');
      [*] = ;      cBtnMultiplayer : _cmd_Post('menumainbutton','multiplayer','');
      [*] = ;      cBtnProfile : _cmd_Post('menumainbutton','profile','');
      [*] = ;      cBtnAchievements : _cmd_Post('menumainbutton','achievements','');
      [*] = ;      cBtnSettings : _cmd_Post('menumainbutton','settings','');
      [*] = ;      cBtnCredits : _cmd_Post('menumainbutton','credits','');
      [*] = ;      cBtnExit: _cmd_Post('menumainbutton','exit','');
      [*] = ;      cBtnEditor: _cmd_Post('menumainbutton','editor','');
      [*] = ;      cBtnTools: _cmd_Post('menumainbutton','tools','');
      [*] = ;      cBtnBack: _cmd_Post('menumainbutton','back','');
      [*] = ;
      [*] = ;      cBtnNewCampaign: _cmd_Post('menuaction','campaignnew','');
      [*] = ;      cBtnCampContinue: _cmd_Post('menuaction','campaigncont','');
      [*] = ;      cBtnLoadCampaign: _cmd_Post('menuaction','campaignload','');
      [*] = ;
      [*] = ;      cBtnNewCustom: _cmd_Post('menuaction','customnew','');
      [*] = ;      cBtnCustContinue: _cmd_Post('menuaction','customcont','');
      [*] = ;      cBtnLoadCustom: _cmd_Post('menuaction','customload','');
      [*] = ;      cBtnBookMasters: _cmd_Post('menucustombutton','masters','');
      [*] = ;
      [*] = ;      cBtnBattle1: _cmd_Post('menudemobutton','demo1','');
      [*] = ;      cBtnBattle2: _cmd_Post('menudemobutton','demo2','');
      [*] = ;      cBtnBattle3: _cmd_Post('menudemobutton','demo3','');
      [*] = ;      cBtnBattle4: _cmd_Post('menudemobutton','demo4','');
      [*] = ;
      [*] = ;      cBtnInternetBattle: _cmd_Post('menuaction','lanbattle','');
      [*] = ;      cBtnInternetShard: _cmd_Post('menuaction','lanshard','');
      [*] = ;      cBtnInternetSettings: _cmd_Post('menumultiplayerbutton','lanprofile','');
      [*] = ;      cBtnHotSeat: _cmd_Post('menuaction','hotseatbattle','');
      [*] = ;      cBtnShardHotSeat: _cmd_Post('menuaction','hotseatshard','');
      [*] = ;      cBtnShardHotSeatLoad: _cmd_Post('menuaction','hotseatload','');
      [*] = ;      cBtnShardLanLoad: _cmd_Post('menuaction','lanload','');
      [*] = ;
      [*] = ;      cBtnWindowDesigner: _cmd_Post('menuaction','windowdesigner','');
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

