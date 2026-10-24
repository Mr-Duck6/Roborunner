# ROBORUNNER README

## FILE STRUCTURE
### Content:

```text
├── Level/ All levels and WBP
│   ├── Interfaces/
│   │   ├── Main_menu_WBP.uasset       WBP for Main menu      
│   │   └── Settings_menu_WBP.uasset     WBP for Setting menu
│   ├── BaseLevel.umap               Base game level                 
│   ├── BaseLevel_BuiltData.umap     Level lighting data  
│   ├── MainMenuLevel.umap           Main menu level          
│   └── PlayerEditorLevel.umap       Player editor level      
├── Map/ All BP class for game with models, texture and sounds
│   ├── Cars/ All data for cars
│   │   ├── BaseCar_BP.uasset        Base car BP    
│   │   ├── SM_ClassicCar.fbx        Base car model     
│   │   └── SM_ClassicCar.uasset     Base car mesh    
│   ├── Road/  All data for roads
│   │   ├── BaseRoad.fbx / .uasset / _BP.uasset      Base road: model, texture and BP     
│   │   ├── DangerRoad.fbx / .uasset / _BP.uasset    Denger road: model, texture and BP     
│   │   ├── SafeRoad.fbx / .uasset / _BP.uasset      Sefe road: model, texture and BP      
│   │   ├── TurrelRoad.fbx / .uasset / _BP.uasset    Turret road: model, texture and BP     
│   │   └── NewTurrelRoad.fbx                        New turret road model                     
│   ├── Cell_BP.uasset               Cell BP           
│   ├── FogKiller_BP.uasset          FogKiller BP         
│   └── GeneratorMap_BP.uasset       GeneratorMap BP      
├── Objects/ All object for road                        
│   ├── ActorTurret_BP.uasset        Turret actor BP      
│   ├── BaseObjectFence_BP.uasset    Base fence object BP  
│   ├── IO_Turrel.fbx / .uasset      Turret model and mesh      
│   ├── NewIO_Turrel.fbx             New turret model             
│   ├── SM_Barrel.fbx / .uasset      Barrel model and mesh      
│   ├── SM_Fence.fbx / .uasset       Fence model and mesh    
│   ├── SM_TallFence.fbx / .uasset   Tall fence model and mesh   
│   └── TallFance_BP.uasset          Tall fence object BP         
└── Player/ All player data                         
    ├── BasePalyerSkin.fbx           Player skin model         
    ├── BasePalyerSkin.uasset        Player skin mesh         
    ├── PlayerCamera_BP.uasset       Player camera BP      
    ├── Player_BP.uasset             Player character BP             
    └── Player_WBP.uasset            Player UI widget
 ```   
### Source:
