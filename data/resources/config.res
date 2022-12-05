section.begin
   resource : struct.begin
      Default = .\data\resources\resource.lib
      benchmark : struct.begin
         ultra : struct.begin
            minlevel = 1
            minvideopoint = 18000
            minvideopointsm20 = 6000
         struct.end
         high : struct.begin
            minlevel = 1
            minvideopoint = 8000
            minvideopointsm20 = 2000
         struct.end
         medium : struct.begin
            minlevel = 1
            minvideopoint = 6000
            minvideopointsm20 = 2000
         struct.end
      struct.end
      form : struct.begin
         locale = tools
         width = 512
         height = 590
         visible : struct.begin
            TabSheetVideo = True
            TabSheetEffects = True
            TabSheetControl = True
            TabSheetSound = True
            TabSheetInterface = False
            SpeedButtonUltra = False
            SpeedButtonHigh = False
            SpeedButtonMedium = False
            SpeedButtonLow = False
            SpeedButtonLowest = False
            SpeedButtonAutoDetect = False
            BevelApplyRun = False
         struct.end
         click : struct.begin
            SpeedButtonUltra : struct.begin
               HDRType = htPseudoHDR
               ShaderType = stSM30
               AntiAliasing = aa4xHQ
               TextureFilteringQuality = tfAnisotropic16x
               WaterReflection = wrmUltra
               ShadowMap = 4096
               ShadowMapEnabled = True
            struct.end
            SpeedButtonHigh : struct.begin
               HDRType = htPseudoHDR
               ShaderType = stSM30
               AntiAliasing = aaNone
               TextureFilteringQuality = tfNone
               WaterReflection = wrmHigh
               ShadowMap = 2048
               ShadowMapEnabled = True
            struct.end
            SpeedButtonMedium : struct.begin
               HDRType = htPseudoHDR
               ShaderType = stSM20
               AntiAliasing = aaNone
               TextureFilteringQuality = tfNone
               WaterReflection = wrmMedium
               ShadowMap = 1024
               ShadowMapEnabled = False
            struct.end
            SpeedButtonLow : struct.begin
               HDRType = htPseudoHDR
               ShaderType = stNone
               AntiAliasing = aaNone
               TextureFilteringQuality = tfNone
               WaterReflection = wrmMedium
               ShadowMap = 1024
               ShadowMapEnabled = False
            struct.end
            SpeedButtonLowest : struct.begin
               HDRType = htNone
               ShaderType = stNone
               AntiAliasing = aaNone
               TextureFilteringQuality = tfNone
               WaterReflection = wrmMedium
               ShadowMap = 1024
               ShadowMapEnabled = False
            struct.end
         struct.end
      struct.end
      static : struct.begin
         Name = main
         DirPath =
         ProfileName = player0
         RacesFileName = .\data\objects\objects.lib
         TileBlocksLibMatFileName = .\data\terrain\tiles\tiles.mat
         TileBlockLibraryFileName = .\data\terrain\tiles\tiles.lib
         CliffBlockSetLibraryFileName = .\data\terrain\cliffs\cliffs.lib
         CliffBlockSetLibraryMaterialsFileName = .\data\terrain\cliffs\cliffs.mat
         WaterLibraryFileName = .\data\water\water.lib
         CoverManagerFileName = .\data\terrain\covers\covers.lib
         BloomCollectionFileName = .\data\posteffects\posteffects.lib
         HDRCollectionFileName =
         TerrainSetLibraryFileName = .\data\terrain\tiles\terrain.presets
         SeasonSetLibraryFileName = .\data\terrain\tiles\terrain.lib
         DecalCollectionFileName = .\data\terrain\decals\decals.lib
         DecalCollectionMaterialFileName = .\data\terrain\decals\decals.mat
         EnvironmentFileName = .\data\env\env.cfg
         ButtonCollectionFileName = .\data\hud\hud.lib
         ButtonCollectionMaterialFileName = .\data\hud\hud.mat
         CursorsCollectionFileName = .\data\cursors\cursors.lib
         FontsCollectionFileName = .\data\hud\font.lib
         ProgressBarCollectionFileName = .\data\hud\bar.lib
         SoundManagerFileName = .\data\sounds\manager.cfg
         SoundLibraryCollectionFileName = .\data\sounds\sounds.slc
         SoundLibraryAmbientName=Ambient
         SoundLibraryVolumesName=Volumes
         PFXCollectionFileName = .\data\pfx\manager.lib
         PFXSourceLibraryFileName = .\data\pfx\source.pfx
         MaterialLibraryInterfaceCollectionFileName = .\data\materials\materials.lib
         LODActorLibraryFileName = .\data\actors\actors.lib
         LODActorAnimationGroupsRuleFileName =
         BaseControlFileName = .\data\gui\menu.cfg
         GenMapZonesFileName =
         GenClimaticZonesFileName =
         GenMapObjectsSettingsFileName =
         GenConfigFileName =
         TileGroupsFileName =
         TileSubgroupsFileName =
         ObjectGroupsFileName =
         ZoneTilesFileName =
         CastleTypesFileName =
         CastleVariationsFileName =
         TileCollisionTagCollectionFileName =
         AngleCollisionTagCollectionFileName =
         SelectionBrushFileName = .\data\brushes\selection.cfg
         StretchBrushFileName = .\data\brushes\stretch.cfg
         ArrowBrushFileName = .\data\brushes\arrow.cfg
         CameraElasticFileName = .\data\cameras\camera.cfg
         ProgressBarLoadName = load.game
         ProgressBarSaveName = save.game
         BrushMaterialLibraryFileName = .\data\brushes\brushes.mat
         UserStateMachineFileName = .\data\scripts\user\user.aix
         LocaleTableFileName = .\data\locale\en\table.lng
         DMScriptGlobalFileName = .\data\scripts\dmscript.global
         AnimationsLibraryFileName = .\data\animations\acl\acl.lib
         GUITextureLibraryFileName = .\data\hud\hud.tex
         PFXMaterialLibraryFileName = .\data\pfx\material.mat
         LightShaderFileName = .\data\shaders\shaders.lib
         PreviewVideoLibraryFileName = .\data\video\video.lib
         TrackPointLibraryFileName =
         PatternCollectionFileName = .\data\pattern\pattern.lib
         PatternRootDir = .\data\pattern\
         PatternRootExt = .pattern
         TileSeasonLibraryFileName = .\data\terrain\tiles\tiles.season
         LightPatternsLibraryFileName = .\data\env\lights\light.presets
         GenTerrainGlobalParamsFileName = .\data\gen\globalparams.cfg
         GenTerrainLocalParamsFileName = .\data\gen\localparams.cfg
         MapCoverCollectionFileName = .\data\gen\mapcover.cfg
         GlobalMapSettingsFileName =
         DecalSetListFileName = .\data\terrain\decals\decals.presets
         RiverDecalManagerFileName =
         LocaleTableListFileName = .\data\locale\en\table.lib
         WideTableListFileName =
         PHDRMaterialLibraryFileName = .\data\posteffects\posteffects.mat
         PHDRShaderLibFileName = .\data\posteffects\posteffects.shaders
         MapStateMachineFileName = .\data\scripts\common.aix
         MapInitState = OnInit
         MapSaveState = OnSave
         MapLoadState = OnLoad
         MapLoadFullState = OnLoadFull
         MapStateMachineStore = False
         MapStackStore = True
         MapStateMachineReset = False
         MapInfoStructStore = True
         MapInfoStructReset = True
         OnLoadScriptFileName = .\data\scripts\resource.script
         HelloScreenLocale = tools;HELLO.SCREEN
         DisplayMode = dmFullScreen
      struct.end

      config : struct.begin
         //-----------------------------
         // *********************
         // TabSheetEffects
         // *********************
         //-----------------------------
         [*] : struct.begin
            Name = LocaleTableFileName
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = list
               Top   = 4
               Caption = CFG.PROFILE.LANGUAGE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = .\data\locale\en\table.lng
                  key = CFG.VALUE.EN
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\en\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
               [*] : struct.begin
                  value = .\data\locale\ru\table.lng
                  key = CFG.VALUE.RU
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\ru\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.ru.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
               [*] : struct.begin
                  value = .\data\locale\pl\table.lng
                  key = CFG.VALUE.PL
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\pl\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.pl.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.pl.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
               [*] : struct.begin
                  value = .\data\locale\de\table.lng
                  key = CFG.VALUE.DE
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\de\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.de.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.de.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
               [*] : struct.begin
                  value = .\data\locale\sp\table.lng
                  key = CFG.VALUE.SP
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\sp\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.sp.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.sp.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
               [*] : struct.begin
                  value = .\data\locale\it\table.lng
                  key = CFG.VALUE.IT
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\it\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.it.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.it.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
               [*] : struct.begin
                  value = .\data\locale\fr\table.lng
                  key = CFG.VALUE.FR
                  setting : struct.begin
                     [*] : struct.begin
                        name = LocaleTableListFileName
                        value = .\data\locale\fr\table.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = FontsCollectionFileName
                        value = .\data\hud\font.fr.lib
                        type = resource
                     struct.end
                     [*] : struct.begin
                        name = PreviewVideoLibraryFileName
                        value = .\data\video\video.fr.lib
                        type = resource
                     struct.end
                  struct.end
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = DisplayMode
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 288
               Caption = CFG.PROFILE.DISPLAYMODE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = dmFullScreen
                  key = CFG.PROFILE.DISPLAYMODE.FULLSCREEN
               struct.end
               [*] : struct.begin
                  value = dmWindow
                  key = CFG.PROFILE.DISPLAYMODE.WINDOW
               struct.end
               [*] : struct.begin
                  value = dmWindowFullScreen
                  key = CFG.PROFILE.DISPLAYMODE.WINDOWEDFULLSCREEN
               struct.end
            struct.end
         struct.end
         //-----------------------------
      struct.end
   struct.end

   engine : struct.begin
      static : struct.begin
         ScreenResolution : struct.begin
            Width =
            Height =
            Frequency =
         struct.end
         AntiAliasing = aaDefault
         TextureFilteringQuality = tfNone
         ShadowMapEnabled = True
         ShadowMap = 2048
         ShaderType = stSM30
         HDRType = htPseudoHDR
         DOFEnable = True
         WaterReflection = wrmUltra
         VSyncMode = vsmNoSync
         HorizonRenderEnabled = False
         CoverEnabled = False
         CoverPPLEnabled = False
         SelfShadowingTerrain = False
         PFX = True
         Sound : struct.begin
            svgMusic = 1
            svgAmbient = 1
            svgSFX = 1
            svgInterface = 1
            svgVoice = 1
            Master = 1
         struct.end
      struct.end

      config : struct.begin
         //-----------------------------
         // *********************
         // TabSheetVideo
         // *********************
         //-----------------------------
         [*] : struct.begin
            Name = ScreenResolution
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = screenres
               Top   = 24
               Caption = CFG.PROFILE.RESOLUTION
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = AntiAliasing
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 48
               Caption = CFG.PROFILE.ANTIALIASING
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = aaDefault
                  key = CFG.VALUE.AADEFAULT
               struct.end
               [*] : struct.begin
                  value = aaNone
                  key = CFG.VALUE.AANONE
               struct.end
               [*] : struct.begin
                  value = aa2x
                  key = CFG.VALUE.AA2X
               struct.end
               [*] : struct.begin
                  value = aa2xHQ
                  key = CFG.VALUE.AA2XHQ
               struct.end
               [*] : struct.begin
                  value = aa4x
                  key = CFG.VALUE.AA4X
               struct.end
               [*] : struct.begin
                  value = aa4xHQ
                  key = CFG.VALUE.AA4XHQ
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = TextureFilteringQuality
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 72
               Caption = CFG.PROFILE.TEXTUREFILTERINGQUALITY
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = tfNone
                  key = CFG.VALUE.TFNONE
               struct.end
               [*] : struct.begin
                  value = tfIsotropic
                  key = CFG.VALUE.TFISOTROPIC
               struct.end
               [*] : struct.begin
                  value = tfAnisotropic
                  key = CFG.VALUE.TFANISOTROPIC
               struct.end
               [*] : struct.begin
                  value = tfAnisotropic4x
                  key = CFG.VALUE.TFANISOTROPIC4X
               struct.end
               [*] : struct.begin
                  value = tfAnisotropic8x
                  key = CFG.VALUE.TFANISOTROPIC8X
               struct.end
               [*] : struct.begin
                  value = tfAnisotropic16x
                  key = CFG.VALUE.TFANISOTROPIC16X
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = ShadowMapEnabled
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 96
               Caption = CFG.PROFILE.SHADOWMAPENABLED
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = False
                  key = CFG.VALUE.OFF
               struct.end
               [*] : struct.begin
                  value = True
                  key = CFG.VALUE.ON
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = ShadowMap
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 120
               Caption = CFG.PROFILE.SHADOWMAPRESOLUTION
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = 1024
                  key = 1024x1024
               struct.end
               [*] : struct.begin
                  value = 2048
                  key = 2048x2048
               struct.end
               [*] : struct.begin
                  value = 4096
                  key = 4096x4096
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = ShaderType
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 144
               Caption = CFG.PROFILE.SHADERTYPE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = stNone
                  key = CFG.VALUE.SHADERTYPE.1
               struct.end
               [*] : struct.begin
                  value = stSM20
                  key = CFG.VALUE.SHADERTYPE.2
               struct.end
               [*] : struct.begin
                  value = stSM30
                  key = CFG.VALUE.SHADERTYPE.3
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = HDRType
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 168
               Caption = CFG.PROFILE.HDR
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = htNone
                  key = CFG.VALUE.HDR.NONE
               struct.end
               [*] : struct.begin
                  value = htPseudoHDR
                  key = CFG.VALUE.HDR.NORMAL
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = WaterReflection
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 192
               Caption = CFG.PROFILE.WATERREFLECTION
            struct.end
            Values : struct.begin
               //[*] : struct.begin
               //   value = wrmLow
               //   key = CFG.VALUE.WRMLOW
               //struct.end
               [*] : struct.begin
                  value = wrmMedium
                  key = CFG.VALUE.WRMLOW
               struct.end
               [*] : struct.begin
                  value = wrmHigh
                  key = CFG.VALUE.WRMMEDIUM
               struct.end
               [*] : struct.begin
                  value = wrmUltra
                  key = CFG.VALUE.WRMHIGH
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = VSyncMode
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 216
               Caption = CFG.PROFILE.VSYNCMODE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = vsmNoSync
                  key = CFG.VALUE.VSMNOSYNC
               struct.end
               [*] : struct.begin
                  value = vsmSync
                  key = CFG.VALUE.VSMSYNC
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = lightchange
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = list
               Top   = 264
               Caption = CFG.PROFILE.LIGHTCHANGE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = 0
                  key = CFG.VALUE.LIGHTCHANGE.0
               struct.end
               [*] : struct.begin
                  value = 1
                  key = CFG.VALUE.LIGHTCHANGE.1
               struct.end
               //[*] : struct.begin
               //   value = 2
               //   key = CFG.VALUE.LIGHTCHANGE.2
               //struct.end
               [*] : struct.begin
                  value = 3
                  key = CFG.VALUE.LIGHTCHANGE.3
               struct.end
               [*] : struct.begin
                  value = 4
                  key = CFG.VALUE.LIGHTCHANGE.4
               struct.end
               [*] : struct.begin
                  value = 5
                  key = CFG.VALUE.LIGHTCHANGE.5
               struct.end
               [*] : struct.begin
                  value = 6
                  key = CFG.VALUE.LIGHTCHANGE.6
               struct.end
               [*] : struct.begin
                  value = 7
                  key = CFG.VALUE.LIGHTCHANGE.7
               struct.end
               [*] : struct.begin
                  value = 8
                  key = CFG.VALUE.LIGHTCHANGE.8
               struct.end
            struct.end
         struct.end
         //-----------------------------
         //[*] : struct.begin
         //   Name = guiBevelVideoLine
         //   Tab = TabSheetVideo
         //   Gui : struct.begin
         //      Class = bevelline
         //      Top = 240
         //      Left = 0
         //      Height = 1
         //      Width = 494
         //      Caption =
         //   struct.end
         //struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetUltra
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = button
               Top = 21
               Left = 370
               Height = 21
               Width = 100
               Caption =
               ButtonCaption = GUI.SET.ULTRA
               OnClick : struct.begin
                  HDRType = htPseudoHDR
                  ShaderType = stSM30
                  AntiAliasing = aa4xHQ
                  TextureFilteringQuality = tfAnisotropic16x
                  WaterReflection = wrmUltra
                  ShadowMap = 4096
                  ShadowMapEnabled = True
                  SimpleGraphics = False
                  ObjectFlags = 0
                  ShardScenery = 0
                  TownScenery = 0
                  ProvinceScenery = 0
                  BattleScenery = 0
               struct.end
               OnClickDoHardwareCompatible = True
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetHigh
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = button
               Top = 45
               Left = 370
               Height = 21
               Width = 100
               Caption =
               ButtonCaption = GUI.SET.HIGH
               OnClick : struct.begin
                  HDRType = htPseudoHDR
                  ShaderType = stSM30
                  AntiAliasing = aaNone
                  TextureFilteringQuality = tfNone
                  WaterReflection = wrmHigh
                  ShadowMap = 2048
                  ShadowMapEnabled = True
                  SimpleGraphics = False
                  ObjectFlags = 0
                  ShardScenery = 1
                  TownScenery = 1
                  ProvinceScenery = 1
                  BattleScenery = 1
               struct.end
               OnClickDoHardwareCompatible = True
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetMedium
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = button
               Top = 69
               Left = 370
               Height = 21
               Width = 100
               Caption =
               ButtonCaption = GUI.SET.MEDIUM
               OnClick : struct.begin
                  HDRType = htPseudoHDR
                  ShaderType = stSM20
                  AntiAliasing = aaNone
                  TextureFilteringQuality = tfNone
                  WaterReflection = wrmMedium
                  ShadowMap = 1024
                  ShadowMapEnabled = True
                  SimpleGraphics = False
                  ObjectFlags = 0
                  ShardScenery = 2
                  TownScenery = 2
                  ProvinceScenery = 2
                  BattleScenery = 2
               struct.end
               OnClickDoHardwareCompatible = True
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetLow
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = button
               Top = 93
               Left = 370
               Height = 21
               Width = 100
               Caption =
               ButtonCaption = GUI.SET.LOW
               OnClick : struct.begin
                  HDRType = htPseudoHDR
                  ShaderType = stNone
                  AntiAliasing = aaNone
                  TextureFilteringQuality = tfNone
                  WaterReflection = wrmMedium
                  ShadowMap = 1024
                  ShadowMapEnabled = False
                  SimpleGraphics = False
                  ObjectFlags = 1
                  ShardScenery = 3
                  TownScenery = 3
                  ProvinceScenery = 3
                  BattleScenery = 3
               struct.end
               OnClickDoHardwareCompatible = True
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetLowest
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = button
               Top = 117
               Left = 370
               Height = 21
               Width = 100
               Caption =
               ButtonCaption = GUI.SET.LOWEST
               OnClick : struct.begin
                  HDRType = htNone
                  ShaderType = stNone
                  AntiAliasing = aaNone
                  TextureFilteringQuality = tfNone
                  WaterReflection = wrmMedium
                  ShadowMap = 1024
                  ShadowMapEnabled = False
                  SimpleGraphics = False
                  ObjectFlags = 7
                  ShardScenery = 4
                  TownScenery = 4
                  ProvinceScenery = 4
                  BattleScenery = 4
               struct.end
               OnClickDoHardwareCompatible = True
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetAutoDetect
            Tab = TabSheetVideo
            Gui : struct.begin
               Class = button
               Top = 141
               Left = 370
               Height = 21
               Width = 100
               Caption =
               ButtonCaption = GUI.SET.AUTODETECT
               OnClickDoAutoDetect = True
            struct.end
         struct.end
         //-----------------------------
      struct.end
   struct.end

   game : struct.begin
      static : struct.begin
         name = CFG.PROFILE.NAME.DEF
         land = CFG.PROFILE.LAND.DEF
         difficulty = 0
         sndmute = 0
         sndmaster = 0,75
         sndmusic = 0,75
         sndambient = 0,75
         sndfx = 0,75
         sndvoice = 0,75
         sndinterface = 0,33
         scrollspeed = 0,5
         wheelspeed = 0,5
         keyspeed = 0,5
         battlespeed = 0,09090909
         autosave = 3
         tutorialmode = -1
         lightchange = 0
      struct.end

      locale : struct.begin
         [*] = name
         [*] = land
      struct.end

      config : struct.begin
         //-----------------------------
         // *********************
         // TabSheetEffects
         // *********************
         //-----------------------------
         [*] : struct.begin
            Name = name
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = edit
               Top = 52
               Caption = CFG.PROFILE.NAME
               Width = 145
            struct.end
            Values : struct.begin
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = land
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = edit
               Top = 76
               Caption = CFG.PROFILE.LAND
               Width = 145
            struct.end
            Values : struct.begin
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = difficulty
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = list
               Top   = 100
               Caption = CFG.PROFILE.DIFFICULTY
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = 0
                  key = CFG.VALUE.NOVICE
               struct.end
               [*] : struct.begin
                  value = 1
                  key = CFG.VALUE.SKILLED
               struct.end
               [*] : struct.begin
                  value = 2
                  key = CFG.VALUE.ADVANCED
               struct.end
               [*] : struct.begin
                  value = 3
                  key = CFG.VALUE.EXPERT
               struct.end
               [*] : struct.begin
                  value = 4
                  key = CFG.VALUE.MASTER
               struct.end
               [*] : struct.begin
                  value = 5
                  key = CFG.VALUE.GRANDMASTER
               struct.end
               [*] : struct.begin
                  value = 6
                  key = CFG.VALUE.OVERLORD
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = autosave
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = list
               Top   = 124
               Caption = CFG.PROFILE.AUTOSAVE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = 0
                  key = CFG.PROFILE.AUTOSAVE_0
               struct.end
               [*] : struct.begin
                  value = 1
                  key = CFG.PROFILE.AUTOSAVE_1
               struct.end
               [*] : struct.begin
                  value = 2
                  key = CFG.PROFILE.AUTOSAVE_2
               struct.end
               [*] : struct.begin
                  value = 3
                  key = CFG.PROFILE.AUTOSAVE_3
               struct.end
               [*] : struct.begin
                  value = 5
                  key = CFG.PROFILE.AUTOSAVE_4
               struct.end
               [*] : struct.begin
                  value = 10
                  key = CFG.PROFILE.AUTOSAVE_5
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = tutorialmode
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = list
               Top   = 28
               Caption = CFG.PROFILE.TUTORIALMODE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = 0
                  key = CFG.VALUE.OFF
               struct.end
               [*] : struct.begin
                  value = -1
                  key = CFG.VALUE.ON
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetDefaultGame
            Tab = TabSheetEffects
            Gui : struct.begin
               Class = button
               Top = 4
               Left = 370
               Height = 21
               Width = 112
               Caption =
               ButtonCaption = GUI.SET.DEFAULT.GAME
               OnClick : struct.begin
                  name = CFG.PROFILE.NAME.DEF
                  land = CFG.PROFILE.LAND.DEF
                  difficulty = 0
                  tutorialmode = -1
                  autosave = 3
                  //LocaleTableFileName = .\data\locale\en\table.lng
               struct.end
            struct.end
         struct.end
         //-----------------------------
         // *********************
         // TabSheetControl
         // *********************
         //-----------------------------
         [*] : struct.begin
            Name = scrollspeed
            Tab = TabSheetControl
            Gui : struct.begin
               Class = slider
               Top   = 24
               Caption = CFG.PROFILE.SCROLLSPEED
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = wheelspeed
            Tab = TabSheetControl
            Gui : struct.begin
               Class = slider
               Top   = 48
               Caption = CFG.PROFILE.WHEELSPEED
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = keyspeed
            Tab = TabSheetControl
            Gui : struct.begin
               Class = slider
               Top   = 72
               Caption = CFG.PROFILE.KEYSPEED
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = battlespeed
            Tab = TabSheetControl
            Gui : struct.begin
               Class = slider
               Top   = 96
               Caption = CFG.PROFILE.BATTLESPEED
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         //[*] : struct.begin
         //   Name = warendturn
         //   Tab = TabSheetControl
         //   Gui : struct.begin
         //      Class = list
         //      Top   = 120
         //      Caption = CFG.PROFILE.WARENDTURN
         //   struct.end
         //   Values : struct.begin
         //      [*] : struct.begin
         //         value = 0
         //         key = CFG.VALUE.OFF
         //      struct.end
         //      [*] : struct.begin
         //         value = -1
         //         key = CFG.VALUE.ON
         //      struct.end
         //   struct.end
         //struct.end
         //-----------------------------
         //[*] : struct.begin
         //   Name = warautospell
         //   Tab = TabSheetControl
         //   Gui : struct.begin
         //      Class = list
         //      Top   = 144
         //      Caption = CFG.PROFILE.WARAUTOSPELL
         //   struct.end
         //   Values : struct.begin
         //      [*] : struct.begin
         //         value = 0
         //         key = CFG.PROFILE.WARAUTOSPELL.0
         //      struct.end
         //      [*] : struct.begin
         //         value = 1
         //         key = CFG.PROFILE.WARAUTOSPELL.1
         //      struct.end
         //      [*] : struct.begin
         //         value = 2
         //         key = CFG.PROFILE.WARAUTOSPELL.2
         //      struct.end
         //      [*] : struct.begin
         //         value = 3
         //         key = CFG.PROFILE.WARAUTOSPELL.3
         //      struct.end
         //   struct.end
         //struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetDefaultControl
            Tab = TabSheetControl
            Gui : struct.begin
               Class = button
               Top = 21
               Left = 370
               Height = 21
               Width = 112
               Caption =
               ButtonCaption = GUI.SET.DEFAULT.CONTROL
               OnClick : struct.begin
                  scrollspeed = 0,5
                  wheelspeed = 0,5
                  keyspeed = 0,5
                  battlespeed = 0,09090909
               struct.end
            struct.end
         struct.end
         //-----------------------------
         // *********************
         // TabSheetSound
         // *********************
         //-----------------------------
         [*] : struct.begin
            Name = sndmute
            Tab = TabSheetSound
            Gui : struct.begin
               Class = list
               Top   = 24
               Caption = CFG.PROFILE.SNDMUTE
            struct.end
            Values : struct.begin
               [*] : struct.begin
                  value = 0
                  key = CFG.VALUE.ON
               struct.end
               [*] : struct.begin
                  value = 1
                  key = CFG.VALUE.OFF
               struct.end
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = sndmaster
            Tab = TabSheetSound
            Gui : struct.begin
               Class = slider
               Top   = 52
               Caption = CFG.PROFILE.SNDMASTER
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = sndmusic
            Tab = TabSheetSound
            Gui : struct.begin
               Class = slider
               Top   = 80
               Caption = CFG.PROFILE.SNDMUSIC
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = sndambient
            Tab = TabSheetSound
            Gui : struct.begin
               Class = slider
               Top   = 108
               Caption = CFG.PROFILE.SNDAMBIENT
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = sndfx
            Tab = TabSheetSound
            Gui : struct.begin
               Class = slider
               Top   = 136
               Caption = CFG.PROFILE.SNDFX
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         [*] : struct.begin
            Name = sndinterface
            Tab = TabSheetSound
            Gui : struct.begin
               Class = slider
               Top   = 164
               Caption = CFG.PROFILE.SNDINTERFACE
            struct.end
            Values : struct.begin
               min = 0
               max = 1
            struct.end
         struct.end
         //-----------------------------
         //[*] : struct.begin
         //   Name = sndvoice
         //   Tab = TabSheetSound
         //   Gui : struct.begin
         //      Class = slider
         //      Top   = 192
         //      Caption = CFG.PROFILE.SNDVOICE
         //   struct.end
         //   Values : struct.begin
         //      min = 0
         //      max = 1
         //   struct.end
         //struct.end
         //-----------------------------
         [*] : struct.begin
            Name = guiSetDefaultSound
            Tab = TabSheetSound
            Gui : struct.begin
               Class = button
               Top = 21
               Left = 370
               Height = 21
               Width = 112
               Caption =
               ButtonCaption = GUI.SET.DEFAULT.SOUND
               OnClick : struct.begin
                  sndmute = 0
                  sndmaster = 0,75
                  sndmusic = 0,75
                  sndambient = 0,75
                  sndfx = 0,75
                  sndinterface = 0,33
               struct.end
            struct.end
         struct.end
      struct.end
   struct.end
section.end
