//This file was generated by the LASAL2 CodeGenerator  -- 
//Please, do not edit this file (it might be overwritten by the next generator run)
typedef struct SvrCh_DINT 
  {
    CHMETH *pMeth;
    DINT dData;
    SVRDSC *pDsc;
  } SvrCh_DINT;

typedef struct CltCh_DINT 
  {
    struct SvrCh_DINT *pCh;
    DINT dData;
    SVRCHCMD *pCmd;
  } CltCh_DINT;

typedef struct SvrCh_FeSetup 
  {
    CHMETH *pMeth;
    FeSetup dData;
    SVRDSC *pDsc;
  } SvrCh_FeSetup;

typedef struct CltCh_FeSetup 
  {
    struct SvrCh_FeSetup *pCh;
    FeSetup dData;
    SVRCHCMD *pCmd;
  } CltCh_FeSetup;

typedef struct SvrCh_IO_State 
  {
    CHMETH *pMeth;
    IO_State dData;
    SVRDSC *pDsc;
  } SvrCh_IO_State;

typedef struct CltCh_IO_State 
  {
    struct SvrCh_IO_State *pCh;
    IO_State dData;
    SVRCHCMD *pCmd;
  } CltCh_IO_State;

typedef struct SvrCh_UDINT 
  {
    CHMETH *pMeth;
    UDINT dData;
    SVRDSC *pDsc;
  } SvrCh_UDINT;

typedef struct CltCh_UDINT 
  {
    struct SvrCh_UDINT *pCh;
    UDINT dData;
    SVRCHCMD *pCmd;
  } CltCh_UDINT;

typedef struct SvrChCmd_t_e_VaranErrors 
  {
    CMDMETH *pMeth;
    t_e_VaranErrors dData;
    SVRDSC *pDsc;
  } SvrChCmd_t_e_VaranErrors;

typedef struct CltChCmd__BusInterfaceSdiasDriveMng 
  {
    struct SvrChCmd_t_e_VaranErrors *pCh;
    t_e_VaranErrors dData;
    _BusInterfaceSdiasDriveMng *pCmd;
  } CltChCmd__BusInterfaceSdiasDriveMng;

typedef struct SvrChCmd_DINT 
  {
    CMDMETH *pMeth;
    DINT dData;
    SVRDSC *pDsc;
  } SvrChCmd_DINT;

typedef struct CltChCmd__DriveAxisSet 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _DriveAxisSet *pCmd;
  } CltChCmd__DriveAxisSet;

typedef struct CltChCmd__DriveMngBase 
  {
    struct SvrChCmd_t_e_VaranErrors *pCh;
    t_e_VaranErrors dData;
    _DriveMngBase *pCmd;
  } CltChCmd__DriveMngBase;

typedef struct CltChCmd__FileSys 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _FileSys *pCmd;
  } CltChCmd__FileSys;

typedef struct CltChCmd__Linker 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _Linker *pCmd;
  } CltChCmd__Linker;

typedef struct CltChCmd__MultiTask 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _MultiTask *pCmd;
  } CltChCmd__MultiTask;

typedef struct CltChCmd__OSKernel 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _OSKernel *pCmd;
  } CltChCmd__OSKernel;

typedef struct CltChCmd__StdLib 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _StdLib *pCmd;
  } CltChCmd__StdLib;

typedef struct CltChCmd__TaskObjectControl 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    _TaskObjectControl *pCmd;
  } CltChCmd__TaskObjectControl;

typedef struct CltChCmd__VaranDriveBase 
  {
    struct SvrChCmd_t_e_VaranErrors *pCh;
    t_e_VaranErrors dData;
    _VaranDriveBase *pCmd;
  } CltChCmd__VaranDriveBase;

typedef struct CltChCmd_DiasMaster 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    DiasMaster *pCmd;
  } CltChCmd_DiasMaster;

typedef struct CltChCmd_DiasMasterC 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    DiasMasterC *pCmd;
  } CltChCmd_DiasMasterC;

typedef struct CltChCmd_DiasMasterPostScan 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    DiasMasterPostScan *pCmd;
  } CltChCmd_DiasMasterPostScan;

typedef struct CltChCmd_DINT 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    SVRCHCMD *pCmd;
  } CltChCmd_DINT;

typedef struct CltChCmd_EEPROM 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    EEPROM *pCmd;
  } CltChCmd_EEPROM;

typedef struct CltChCmd_Hub_Base 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    Hub_Base *pCmd;
  } CltChCmd_Hub_Base;

typedef struct CltChCmd_Hub_Base_Root 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    Hub_Base_Root *pCmd;
  } CltChCmd_Hub_Base_Root;

typedef struct CltChCmd_HwControl 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    HwControl *pCmd;
  } CltChCmd_HwControl;

typedef struct CltChCmd_HwControlBase 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    HwControlBase *pCmd;
  } CltChCmd_HwControlBase;

typedef struct CltChCmd_HWRtPostScan 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    HWRtPostScan *pCmd;
  } CltChCmd_HWRtPostScan;

typedef struct CltChCmd_I2CCDIAS 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    I2CCDIAS *pCmd;
  } CltChCmd_I2CCDIAS;

typedef struct SvrChCmd_UDINT 
  {
    CMDMETH *pMeth;
    UDINT dData;
    SVRDSC *pDsc;
  } SvrChCmd_UDINT;

typedef struct CltChCmd_MerkerEx 
  {
    struct SvrChCmd_UDINT *pCh;
    UDINT dData;
    MerkerEx *pCmd;
  } CltChCmd_MerkerEx;

typedef struct CltChCmd_RAMex 
  {
    struct SvrChCmd_UDINT *pCh;
    UDINT dData;
    RAMex *pCmd;
  } CltChCmd_RAMex;

typedef struct CltChCmd_RamFile 
  {
    struct SvrChCmd_UDINT *pCh;
    UDINT dData;
    RamFile *pCmd;
  } CltChCmd_RamFile;

typedef struct CltChCmd_SafetyManager 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    SafetyManager *pCmd;
  } CltChCmd_SafetyManager;

typedef struct CltChCmd_SdiasHubBase 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    SdiasHubBase *pCmd;
  } CltChCmd_SdiasHubBase;

typedef struct CltChCmd_SdiasManager 
  {
    struct SvrChCmd_t_e_VaranErrors *pCh;
    t_e_VaranErrors dData;
    SdiasManager *pCmd;
  } CltChCmd_SdiasManager;

typedef struct CltChCmd_SdiasSafetyManager 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    SdiasSafetyManager *pCmd;
  } CltChCmd_SdiasSafetyManager;

typedef struct CltChCmd_String 
  {
    struct SvrChCmd_UDINT *pCh;
    UDINT dData;
    String *pCmd;
  } CltChCmd_String;

typedef struct SvrChCmd_IO_State 
  {
    CMDMETH *pMeth;
    IO_State dData;
    SVRDSC *pDsc;
  } SvrChCmd_IO_State;

typedef struct CltChCmd_SyncCall 
  {
    struct SvrChCmd_IO_State *pCh;
    IO_State dData;
    SyncCall *pCmd;
  } CltChCmd_SyncCall;

typedef struct CltChCmd_t_e_VaranErrors 
  {
    struct SvrChCmd_t_e_VaranErrors *pCh;
    t_e_VaranErrors dData;
    SVRCHCMD *pCmd;
  } CltChCmd_t_e_VaranErrors;

typedef struct CltChCmd_Varan_Base 
  {
    struct SvrChCmd_t_e_VaranErrors *pCh;
    t_e_VaranErrors dData;
    Varan_Base *pCmd;
  } CltChCmd_Varan_Base;

typedef struct CltChCmd_VaranManager_Base 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    VaranManager_Base *pCmd;
  } CltChCmd_VaranManager_Base;

typedef struct CltChCmd_VaranManagerPostScan 
  {
    struct SvrChCmd_DINT *pCh;
    DINT dData;
    VaranManagerPostScan *pCmd;
  } CltChCmd_VaranManagerPostScan;

typedef struct CltChCmd_WatchdogDias 
  {
    struct SvrChCmd_IO_State *pCh;
    IO_State dData;
    WatchdogDias *pCmd;
  } CltChCmd_WatchdogDias;

typedef struct SvrCh__DRIVETYPE 
  {
    CHMETH *pMeth;
    _DRIVETYPE dData;
    SVRDSC *pDsc;
  } SvrCh__DRIVETYPE;

typedef struct SvrCh__I_HC_Type 
  {
    CHMETH *pMeth;
    _I_HC_Type dData;
    SVRDSC *pDsc;
  } SvrCh__I_HC_Type;

typedef struct SvrCh__SDDAXISSTATE 
  {
    CHMETH *pMeth;
    _SDDAXISSTATE dData;
    SVRDSC *pDsc;
  } SvrCh__SDDAXISSTATE;

typedef struct SvrCh__SDDUSERCMD 
  {
    CHMETH *pMeth;
    _SDDUSERCMD dData;
    SVRDSC *pDsc;
  } SvrCh__SDDUSERCMD;

typedef struct SvrCh__steps_PTofCls_class0 
  {
    CHMETH *pMeth;
    _steps dData;
    SVRDSC *pDsc;
  } SvrCh__steps_PTofCls_class0;

typedef struct SvrCh_BDINT 
  {
    CHMETH *pMeth;
    BDINT dData;
    SVRDSC *pDsc;
  } SvrCh_BDINT;

typedef struct SvrCh_DS402_Control 
  {
    CHMETH *pMeth;
    DS402_Control dData;
    SVRDSC *pDsc;
  } SvrCh_DS402_Control;

typedef struct SvrCh_DS402_State 
  {
    CHMETH *pMeth;
    DS402_State dData;
    SVRDSC *pDsc;
  } SvrCh_DS402_State;

typedef struct SvrCh_HDINT 
  {
    CHMETH *pMeth;
    HDINT dData;
    SVRDSC *pDsc;
  } SvrCh_HDINT;

typedef struct SvrCh_SafetyConfigStateType 
  {
    CHMETH *pMeth;
    SafetyConfigStateType dData;
    SVRDSC *pDsc;
  } SvrCh_SafetyConfigStateType;

typedef struct SvrCh_state_type_PTofCls_Abschluss 
  {
    CHMETH *pMeth;
    state_type dData;
    SVRDSC *pDsc;
  } SvrCh_state_type_PTofCls_Abschluss;

typedef struct SvrCh_t_e_SafetyMemState 
  {
    CHMETH *pMeth;
    t_e_SafetyMemState dData;
    SVRDSC *pDsc;
  } SvrCh_t_e_SafetyMemState;

typedef struct SvrCh_t_e_VaranErrors 
  {
    CHMETH *pMeth;
    t_e_VaranErrors dData;
    SVRDSC *pDsc;
  } SvrCh_t_e_VaranErrors;

typedef struct SvrCh_t_SDIAS_ErrorBits_AM441_PTofCls_AM441 
  {
    CHMETH *pMeth;
    t_SDIAS_ErrorBits_AM441 dData;
    SVRDSC *pDsc;
  } SvrCh_t_SDIAS_ErrorBits_AM441_PTofCls_AM441;

typedef struct SvrChCmd_iprStates 
  {
    CMDMETH *pMeth;
    iprStates dData;
    SVRDSC *pDsc;
  } SvrChCmd_iprStates;

