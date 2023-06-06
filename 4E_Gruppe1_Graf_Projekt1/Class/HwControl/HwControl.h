#ifndef HW_CONTROL_H
#pragma once
#define HW_CONTROL_H

// Definitions for installing Update-Calls
#ifndef SCANDEFS_H
#define SCANDEFS_H
  #define CALL_OPTION_RT_PRESCAN  2#0001
  #define CALL_OPTION_RT_POSTSCAN 2#0010
  #define CALL_OPTION_CYCLIC      2#0100
  #define CALL_OPTION_POST_INIT   2#1000
#endif // SCANDEFS_H

// maximum time for the initilisation after the last init in ms
#define POST_INIT_TIMEOUT               30000

// newinst commands
#define CMD_POST_INIT_CALL        16#8002 // when the init is blocked but the realtime is already running everything gets called so it can wait until init is finished
#define CMD_NEED_POST_INIT_CALL   16#8003 // when a module needs to initialize during last init it calls the newinst of the varanmanager with this parameter
#define CMD_POST_INIT_FINISHED    16#8004 // when the module is ready (CMD_NEED_LAST_INIT_CALL has to be called before)
#define CMD_FORCE_POST_INIT_END   16#8005 // when the Post init runs init runs into timeout, this call is used by HWControl to stop the post init phase in the VM. Otherwise UpDateCy of HWK is not called
#define CMD_HWCONTROL_LOGIN       16#8006 // general login to hwcontrol to get callbacks for post init, cyclic and realtime pre-/postscan
#define CMD_POST_INIT_RT_READY    16#8007 // when the hwcontrol has finished post init it asks every module if it's also ready with it's rt
#define CMD_POST_INIT_DO_SORT     16#8008 // command for the varan managers to sort their DOs (safety first, then all others)            
#define CMD_HWC_ERROR_TO_DIASM    16#8009 // command to send an error of the hw control to the diasmaster (necessary to stop cyclic task)
#define CMD_POST_INIT_RT_SYNC     16#800A // when the hwcontrol has finished post init it asks every module if it got the sync in realtime up and running
#define CMD_SET_VARANMANAGER_ERROR  16#800B // command to set a VaranManagerError

#define CMD_GET_HARDWARE_TREE_ENTRY 16#83B0 // returns the next hardwaretree entry. Input Var of type: t_HWCGetHardwareTreeEntryIn, Output Var of type: t_HWCGetHardwareTreeEntryOut
#define CMD_GET_HARDWARE_DIAGNOSIS  16#83B1 // returns the diagnose data for the passed hardwaretree entry: Input Var of type: t_HWCGetHardwareDiagnosisIn, Output Var of type t_HWCGetHardwareDiagnosisOut

#define HWC_INVALID_DEVICE_ID 16#FFFFFFFF

//*****************************************************************************
//** TYPES                                                                   **
//*****************************************************************************

	TYPE
    t_HwObjListSettings : BDINT
	    [
	    1 RtPreScan,
      2 RtPostScan,
      3 Cyclic,
      4 PostInit,
	    ];
      
    t_HWCRetvalReturnCode :
    (
      _HWC_RETVAL_OK,
      _HWC_RETVAL_OK_MODULE_FOUND, 
      _HWC_RETVAL_OK_HWTSTR_RETURNED, 
      _HWC_RETVAL_OK_SDIAS_SPI_ACCESS_BUSY,
      _HWC_RETVAL_OK_END_OF_LIST,
      _HWC_RETVAL_ERROR,    
      _HWC_RETVAL_ERROR_WRONG_HARDWARE,
      _HWC_RETVAL_ERROR_NO_HARDWARE,
      _HWC_RETVAL_ERROR_NO_CALIB_DATA_FOUND,
      _HWC_RETVAL_ERROR_CLASS_NOT_ONLINE,
      _HWC_RETVAL_ERROR_VARAN_MODULE_NOT_FOUND,
      _HWC_RETVAL_ERROR_SDIAS_MODULE_NOT_FOUND,
      _HWC_RETVAL_ERROR_CDIAS_MODULE_NOT_FOUND,
      _HWC_RETVAL_ERROR_DIAS_MODULE_NOT_FOUND,
      _HWC_RETVAL_ERROR_AXIS_MODULE_NOT_FOUND,
      _HWC_RETVAL_ERROR_VARAN_SPI_ACCESS_FAILED,
      _HWC_RETVAL_ERROR_SDIAS_SPI_ACCESS_FAILED
    )$UDINT;

    // Input Paramater struct for newinst command CMD_GET_HARDWARE_TREE_ENTRY
    t_HWCGetHardwareTreeEntryIn : STRUCT
      pStr_LastHardewareTreeEntry : ^Char;   // Pointer to the last HW String entry. Pass nil if you want the first HW String entry.
      us_current_index        : USINT;   //Points to the current entry of hardwaretree string
      us_current_length       : USINT;
    END_STRUCT;
    
    // Output Paramater struct for newinst command CMD_GET_HARDWARE_TREE_ENTRY
    t_HWCGetHardwareTreeEntryOut : STRUCT
      retcode         : t_HWCRetvalReturnCode;    // Return code
      pStr_NextHardewareTreeEntry : ^Char;   // Pointer to which the requested HW String entry will be stored. The maximum stringlength of (TODO determin) byte must be reserved. Pointer is guaranteed o be valid until the next call 
    END_STRUCT;
    
    // Input Paramater struct for newinst command CMD_GET_HARDWARE_DIAGNOSIS
    t_HWCGetHardwareDiagnosisIn : STRUCT
      pStr_HardewareTreeEntry : ^Char;   // Pointer to the HW String entry for which the Diagnose data is requested
      us_current_index        : USINT;   //Points to the current entry of hardwaretree string
      us_current_length       : USINT;
    END_STRUCT;
    
    // Output Paramater struct for newinst command CMD_GET_HARDWARE_DIAGNOSIS
    // All String Pointers guaranteed to be valid until the next call 
    t_HWCGetHardwareDiagnosisOut : STRUCT
      retcode           : t_HWCRetvalReturnCode;    // Return code      
      ClassState        : t_e_VaranErrors;
      pStr_DeviceName   : ^Char;
      ud_DeviceID       : UDINT;
      pStr_VendorName   : ^Char;
      ud_VendorID       : UDINT;
      pStr_SerialNo     : ^Char;
      pStr_OrderingNo   : ^Char;
      ud_LicenseNo      : UDINT;
      hd_HWVersion      : HDINT;
      ud_Variante       : UDINT;
      hd_FPGAVersion    : HDINT;
      pStr_FWVersion    : ^Char;
      hd_SafetyNumber   : HDINT;
      ud_Place          : UDINT;
      ud_AxisNo         : UDINT;
      ud_reserved_size  : UDINT;
      pud_reserved      : ^UDINT;
      ud_user_size      : UDINT;
      pud_user          : ^UDINT;
      
    END_STRUCT;
    
  END_TYPE
  

  
#endif
