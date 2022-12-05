section.begin
   Name = DoInitial
   Description[*] = // gIntRegister_fowcloud_province - province handle
   UsedFileName = 
   Code : struct.begin
      [*] = ;// gIntRegister_fowcloud_province - province handle
      [*] = ;
      [*] = ;var goMyHnd : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;ClearVariables;
      [*] = ;
      [*] = ;// setup stack
      [*] = ;var initial : Integer = 1;  // default 0 just before initial, 1 initialized
      [*] = ;var status  : Integer = 0;  // default 0 born, 1 idle, 2 flash, 3 lightning
      [*] = ;var prohnd  : Integer = 0;  // province handle
      [*] = ;var proind  : Integer = 0;  // province index
      [*] = ;var proacc  : Integer = 0;  // province accurate
      [*] = ;var profog  : Integer = 0;  // province fogtype
      [*] = ;var curind  : Integer = 0;  // current index effects : 0 empty (default), 1 fog, 2 accurate, 3 light, 4 flashfog, 5 flashaccurate, 6 flashlight
      [*] = ;var tarind  : Integer = 0;  // target index effects (to lerp)
      [*] = ;var flanum  : Integer = 0;  // flash counter
      [*] = ;var lignum  : Integer = 0;  // lightning counter
      [*] = ;
      [*] = ;// stack indices
      [*] = ;// [0 gc_GOStack_fowcloud_init] - initialized [0..1] : (0 is empty, 1 is initialized)
      [*] = ;SetIntValueByName('init', initial);
      [*] = ;// [1 gc_GOStack_fowcloud_status] - status [0..3] : (default 0 born, 1 idle, 2 flash, 3 lightning)
      [*] = ;SetIntValueByName('status', status);
      [*] = ;// [2 gc_GOStack_fowcloud_prohnd] - province handle
      [*] = ;SetIntValueByName('prohnd', prohnd);
      [*] = ;// [3 gc_GOStack_fowcloud_proind] - province index
      [*] = ;SetIntValueByName('proind', proind);
      [*] = ;// [4 gc_GOStack_fowcloud_proacc] - province accurate [0..1] : (default 0 false, 1 true)
      [*] = ;SetIntValueByName('proacc', proacc);
      [*] = ;// [5 gc_GOStack_fowcloud_profog] - province fogtype [0..2] : (default 0 fog, 1 easy fog, 2 no fog)
      [*] = ;SetIntValueByName('profog', profog);
      [*] = ;// [6 gc_GOStack_fowcloud_curind] - current index effects [0..5] : (0 empty (default), 1 fog, 2 accurate, 3 light, 4 flashfog, 5 flashaccurate, 6 flashlight)
      [*] = ;SetIntValueByName('curind', curind);
      [*] = ;// [7 gc_GOStack_fowcloud_tarind] - target index effects (to lerp)
      [*] = ;SetIntValueByName('tarind', tarind);
      [*] = ;// [8 gc_GOStack_fowcloud_flanum] - flash counter
      [*] = ;SetIntValueByName('flanum', flanum);
      [*] = ;// [8 gc_GOStack_fowcloud_lignum] - lightning counter
      [*] = ;SetIntValueByName('lignum', lignum);
      [*] = ;
      [*] = ;
      [*] = ;if (GetGameObjectUniqueIdByHandle(goMyHnd)<=0) then
      [*] = ;GameObjectMakeUniqId(goMyHnd);
      [*] = ;
      [*] = ;//SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;//SetGameObjectSTOHandleByHandle(goMyHnd, 0);
      [*] = ;//SetGameObjectMyPlayableObject(False);
      [*] = ;
      [*] = ;SetGameObjectOnStateDestroyByHandle(goMyHnd, 'OnDestroy');
      [*] = ;
      [*] = ;ExecuteState('OnCreate');
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
