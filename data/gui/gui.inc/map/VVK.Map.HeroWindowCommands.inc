section.begin
   Name = VVK.Map.HeroWindowCommands
   UsedFileName =
   Description : struct.begin
      [*] = ;IntRegister0 - execution mode (0-execute, 1-return status)
      [*] = ;IntRegister1 - command id
      [*] = ;IntRegister3 - (!) window handle to which this one attached
      [*] = ;StringRegister0 - command name
      [*] = ;StringRegister1 - command parameters (from cfg file)
      [*] = ;StringRegister2 - state parameters (passed in RegisterWindowState)
      [*] = ;StringRegister3 - extra state parameters (passed in PostCommand)
      [*] = ;RETURNS:
      [*] = ;   IntRegister2 - (&0xff: 1 - command available, stop execution, 2 - command unavailable, stop execution, 0 - not supported, continue execution)
      [*] = ;                  high 24 bits are for user defined check availability attributes!
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\VVK.MAP.HEROWINDOWCOMMANDS';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;procedure SaveHeroToCampVar(uid : Integer);
      [*] = ;begin
      [*] = ;   var h : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;
      [*] = ;   gCampMapHero.units_no := 0;
      [*] = ;   if h <> 0 then
      [*] = ;   begin
      [*] = ;      var cfg_p : Integer;
      [*] = ;
      [*] = ;      cfg_p := _misc_ParserGetOrCreateByKey('MapExportConfig',false);
      [*] = ;      if ParserSelectByHandleByKey(cfg_p,'ProvinceRecordsToExport') = 0 then
      [*] = ;         ParserLoadFromFileByHandle(cfg_p,'.\data\game\var\editor_impex_data.cfg');
      [*] = ;      BoolRegister0 := true;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      IntRegister1 := cfg_p;
      [*] = ;      GameObjectExecuteStateByHandle(h,'ExportHero');
      [*] = ;      IntRegister0 := uid;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      GUIExecuteState('VVK.map.GetHeroAstralTransferPrice');
      [*] = ;      gCampaign.arrcampplayers[0].energy := gCampaign.arrcampplayers[0].energy - IntRegister0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var cmd_attr : String = StringRegister1;
      [*] = ;var reg_attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var res,whd,w_mode,c_mode: Integer;
      [*] = ;var temp_str : String;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;res := 1;
      [*] = ;if (gIntRegister_GUICurCastleMode <> 0) and (_gui_GetWindow('map_hero_incastle_panel_info') = 0) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   IntRegister2 := 0;
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;w_mode := _sa_GetAsInt(reg_attr,0);
      [*] = ;if (w_mode <> gc_HeroPanelBothPanels) and (gIntRegister_GUICurCastleMode=1) then
      [*] = ;   c_mode := 0
      [*] = ;else
      [*] = ;   c_mode := 1;
      [*] = ;
      [*] = ;if _log then _log_Values('WMODE|CMODE',w_mode,c_mode,0,0,0,0);
      [*] = ;case StrToLowerCase(cmd) of
      [*] = ;   'heroclosepanels' : begin
      [*] = ;      if (mode = 0) then
      [*] = ;      begin
      [*] = ;         if gIntRegister_CampaignHeroesPanel = 0 then
      [*] = ;         begin
      [*] = ;            if (user_attr = '') and (w_mode = gc_HeroPanelExtraUnit) then
      [*] = ;            begin
      [*] = ;               _sa_Get(reg_attr,1,temp_str);
      [*] = ;               whd := _gui_GetWindow(temp_str);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               whd := 0;
      [*] = ;
      [*] = ;            if (user_attr <> '') or (whd = 0) then
      [*] = ;            begin
      [*] = ;               _cmd_Post('generalcanceldrag','0','');
      [*] = ;               gBoolRegister_RepairItemMode := False;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GUIExecuteState('map.CloseHeroWindow');
      [*] = ;               if (gIntRegister_GUICurCastleMode <> 0) then
      [*] = ;                  _cmd_Post('castleheroes','','');
      [*] = ;            end
      [*] = ;            else
      [*] = ;               _gui_ShowQuestionDialog('gui|unit_will_be_lost', '#heroclosepanels||1', 0, '', 0, false, false);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if user_attr = '' then
      [*] = ;            begin
      [*] = ;               if _sa_GetAsInt(cmd_attr,0) = 1 then // enter key was pressed
      [*] = ;               begin
      [*] = ;                  var hero_nm : String;
      [*] = ;
      [*] = ;                  _hero_GetName( GetGameObjectHandleByUniqueId(gIntRegister_GUIActiveHeroUID1),hero_nm);
      [*] = ;                  gStringRegister_MyHeroName := hero_nm;
      [*] = ;                  _gui_ShowQuestionDialog('gui|map_confirm_hero_transfer_to_astral', '#heroclosepanels||2', 0, '', 0, false, false);
      [*] = ;                  //_gui_ShowQuestionDialog('%hero_name%', '#heroclosepanels||2', 0, '', 0, false, false);
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  _gui_ShowQuestionDialog('gui|map_confirm_noheroes_transfer_to_astral', '#heroclosepanels||1', 0, '', 0, false, false);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               whd := _sa_GetAsInt(user_attr,0);
      [*] = ;               //ErrorLogI('Campaign mode chosen: '+IntToStr(whd)+', hero UID: '+IntToStr(gIntRegister_GUIActiveHeroUID1));
      [*] = ;               if whd = 2 then
      [*] = ;                  SaveHeroToCampVar(gIntRegister_GUIActiveHeroUID1);
      [*] = ;               gIntRegister_CampaignHeroesPanel := 0;
      [*] = ;               _cmd_Post('generalcanceldrag','0','');
      [*] = ;               gBoolRegister_RepairItemMode := False;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GUIExecuteState('map.CloseHeroWindow');
      [*] = ;               // root
      [*] = ;               //whd := _plr_GetWinLoseStatus(GetPlayerHandleInterfaceIO());
      [*] = ;               //if (whd > 0) then
      [*] = ;               // vanilla
      [*] = ;               if gBoolRegister_MapWin then
      [*] = ;               //
      [*] = ;               begin
      [*] = ;                  if gCampaign.defender then
      [*] = ;                  begin
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     GUIExecuteState('map.CreateStatistics');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     GUIExecuteState('map.CreateShardCapture');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gIntRegister_CampaignHeroesPanel <> 0) and (_sa_GetAsInt(cmd_attr,0) = 1) then
      [*] = ;         begin
      [*] = ;            whd := _gui_GetWindow('map_heropanel.map_heropanel_leftside.map_heropanel_btn_astralaccept');
      [*] = ;            //ErrorLogI('WHD: '+IntToStr(whd));
      [*] = ;            if whd = 0 then
      [*] = ;               res := 2
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (_sa_GetAsInt(GetGUIElementStringTag(whd),0) = 2) then
      [*] = ;               begin
      [*] = ;                  res := 2;
      [*] = ;                  SetGUIElementHint(whd, 'gui|hero_to_astral_no_energy_tooltip');
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  SetGUIElementHint(whd, 'gui|accept_hero_to_astral_tooltip');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   'herosquadpanel' : begin
      [*] = ;      if (w_mode <> gc_HeroPanelExtraUnit) and (w_mode <> gc_HeroPanelUnitsOnly) {and (gIntRegister_GUIActiveHeroUID2 = 0)} and (c_mode <> 0) then
      [*] = ;         res := _cmd_CheckNF('herosquad','','')
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         _cmd_Process('herosquad','','');
      [*] = ;   end;
      [*] = ;   'heroinventorypanel' : begin
      [*] = ;      if (w_mode <> gc_HeroPanelExtraUnit) and (w_mode <> gc_HeroPanelInventory) {and (gIntRegister_GUIActiveHeroUID2 = 0)} and (c_mode <> 0) then
      [*] = ;         res := _cmd_CheckNF('heroinventory','','')
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         _cmd_Process('heroinventory','','');
      [*] = ;   end;
      [*] = ;   'herospellbookpanel' : begin
      [*] = ;      if (w_mode <> gc_HeroPanelExtraUnit) and (w_mode <> gc_HeroPanelSpellbook) {and (gIntRegister_GUIActiveHeroUID2 = 0)} and (c_mode <> 0) then
      [*] = ;         res := _cmd_CheckNF('herospellbook','','')
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         _cmd_Process('herospellbook','','');
      [*] = ;   end;
      [*] = ;   'heroinfopanel' : begin
      [*] = ;      if (w_mode <> gc_HeroPanelExtraUnit) and (w_mode <> gc_HeroPanelBothPanels) then
      [*] = ;         res := _cmd_CheckNF('heroinfo','','')
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         _cmd_Process('heroinfo','','');
      [*] = ;   end;
      [*] = ;   'herodismisspanel' : begin
      [*] = ;      if (w_mode <> gc_HeroPanelExtraUnit) then
      [*] = ;         res := _cmd_CheckNF('herodismiss','',user_attr)
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;
      [*] = ;      if (mode = 0) and (res = 1) then
      [*] = ;         _cmd_Process('herodismiss','',user_attr);
      [*] = ;   end;
      [*] = ;   'herogotocastle' : begin
      [*] = ;      if mode = 0 then
      [*] = ;         res := _cmd_Process('mapgotocastle','',user_attr)
      [*] = ;      else
      [*] = ;         res := _cmd_Check('mapgotocastle','',user_attr);
      [*] = ;   end;
      [*] = ;   'mapgotocastle', 'heroinfo', 'herospellbook', 'heroinventory', 'herosquad', 'herodismiss' : begin
      [*] = ;      res := 0;
      [*] = ;   end;
      [*] = ;   'castleheroes' : begin
      [*] = ;      if (mode = 0) and (c_mode <> 0) then
      [*] = ;      begin
      [*] = ;         res := _cmd_Process('heroclosepanels','','1');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   else begin
      [*] = ;      if ((_cmd_GetAttributes(cmd) and (gc_gui_command_attr_system or gc_gui_command_attr_top)) <> 0) or StrExists(cmd,'mbdown') or StrExists(cmd,'mbup') or (c_mode <> 0) then
      [*] = ;         res := 0
      [*] = ;      else
      [*] = ;         res := 2;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister2 := res;
   struct.end
section.end

