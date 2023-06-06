//This file was generated by the LASAL2 CodeGenerator  -- 
//Please, do not edit this file (it might be overwritten by the next generator run)
//{{LSL_DECLARATION

(*!
<Class
	Name               = "SDM081"
	Revision           = "1.4"
	GUID               = "{1A0F98A1-0A73-491B-85FD-92EF0F0E722C}"
	RealtimeTask       = "false"
	CyclicTask         = "false"
	BackgroundTask     = "false"
	Sigmatek           = "true"
	OSInterface        = "false"
	HighPriority       = "false"
	Automatic          = "false"
	UpdateMode         = "Prescan"
	IconPath           = ".\Class\sdm.ico"
	SharedCommandTable = "true"
	Objectsize         = "(410,120)">
	<Channels>
		<Server Name="Safe_Input1" GUID="{DA7F861D-236B-4420-A748-0D3BA84BC4FC}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of input (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Input Low&#13;&#10; 1..Input High"/>
		<Server Name="Safe_Input2" GUID="{D1AB89B4-2CFD-4D9F-922A-5B8B90E6C948}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of input (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Input Low&#13;&#10; 1..Input High"/>
		<Server Name="Safe_Input3" GUID="{D5B37546-A741-4043-9F48-57F68004FCB9}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of input (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Input Low&#13;&#10; 1..Input High"/>
		<Server Name="Safe_Input4" GUID="{EAAB4928-C70C-4E63-8CB8-DF77750AF169}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of input (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Input Low&#13;&#10; 1..Input High"/>
		<Server Name="Safe_Input5" GUID="{5CE2E52B-2586-462D-8E7A-77AF785448C5}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of input (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Input Low&#13;&#10; 1..Input High"/>
		<Server Name="Safe_Input6" GUID="{554DF3DD-4612-44A2-8030-E430EE82606B}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of input (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Input Low&#13;&#10; 1..Input High"/>
		<Server Name="Safe_Output1" GUID="{2B676776-DD4F-4040-8460-CA1534FF39FC}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of output (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Output Low&#13;&#10; 1..Output High"/>
		<Server Name="Safe_Output2" GUID="{59094D42-FE37-4647-A925-5E59275A4400}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="State of output (read only)&#13;&#10;&#13;&#10;-1..Error&#13;&#10; 0..Output Low&#13;&#10; 1..Output High"/>
		<Server Name="SafeIOError" GUID="{494367BD-AC42-4247-8353-F49010D60A9D}" Visualized="true" Initialize="false" WriteProtected="true" Retentive="false" Comment="Shows which safe in/outputs are in error.&#13;&#10;The in/outputs are bitcoded.&#13;&#10;Bit0 = Input1&#13;&#10;Bit1 = Input2&#13;&#10;Bit2 = Input3&#13;&#10;Bit3 = Input1&#13;&#10;Bit4 = Input2&#13;&#10;Bit5 = Input3&#13;&#10;Bit6 = Output1&#13;&#10;Bit7 = Output2"/>
		<Server Name="Unsafe_Output1" GUID="{AF82D7B0-2E3A-4EE9-9FE4-65770371CB38}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false" Comment="State of output (write only; default value: 0)&#13;&#10;&#13;&#10;If safety is given (output would be 1), you can still switch to zero by writing 0 to this server"/>
		<Server Name="Unsafe_Output2" GUID="{82C3D54D-B1E3-41E3-9024-4CEE159CDFE9}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false" Comment="State of output (write only; default value: 0)&#13;&#10;&#13;&#10;If safety is given (output would be 1), you can still switch to zero by writing 0 to this server"/>
	</Channels>
	<RevDoku>
		<Owner Company="Sigmatek" Author="EisMic"/>
		<Dokumentation Revision="1.4" Date="16.04.2015" Author="EisMic" Company="Sigmatek" Description="Added support for graphical hardware editor."/>
		<Dokumentation Revision="1.3" Date="05.12.2014" Author="ZoePat" Company="Sigmatek" Description="The Status of the Output2 is now shown correctly at the Server."/>
		<Dokumentation Revision="1.2" Date="31.10.2014" Author="lanste" Company="Sigmatek" Description="Fixed error: Safe IO were displayed on wrong safety hardwareclass if the class is not required and not online.&#13;&#10;Fixed error: Safe IO were displayed on wrong safety hardwareclass if the hardware configuration did not match the project configuration.&#13;&#10;Set IOs to -2 if Class is not online."/>
		<Dokumentation Revision="1.1" Date="31.07.2014" Author="PieSte" Company="Sigmatek" Description="Added QuitComError server to quit errors on safety cpu."/>
		<Dokumentation Revision="1.0" Date="24.03.2013" Author="EisMic" Company="Sigmatek" Description="First library version"/>
	</RevDoku>
	<Network Name="SDM081">
		<!-- List of Components in this network -->
		<Components>
			<Object
				Name       = "_base"
				GUID       = "{32855BA4-01AF-4D0C-914B-678CC8703A4D}"
				Class      = "SdiasSafetyBase"
				Position   = "(218,120)"
				Visualized = "false">
				<Channels>
					<Server Name="CallCommand"/>
					<Server Name="ClassState"/>
					<Server Name="DeviceID"/>
					<Server Name="QuitComError"/>
					<Server Name="RetryCounteruC1"/>
					<Server Name="RetryCounteruC2"/>
					<Server Name="SafetyNumber"/>
					<Server Name="SerialNo"/>
					<Client Name="InputsNeeded" Value="6"/>
					<Client Name="OutputsNeeded" Value="2"/>
					<Client Name="Place"/>
					<Client Name="Required" Value="1"/>
					<Client Name="SdiasSafetyIn"/>
					<Client Name="SetDeviceID" Value="2#101001"/>
				</Channels>
			</Object>
		</Components>
		<Comments>
		</Comments>
		<!-- List of Connections in this network -->
		<Connections>
			<Connection Source="this.ClassState" Destination="_base.ClassState" Vertices="(992,210),(820,210),"/>
			<Connection Source="_base.SdiasSafetyIn" Destination="this.SdiasSafetyIn" Vertices="(218,210),(38,210),"/>
			<Connection Source="_base.Place" Destination="this.Place" Vertices="(218,270),(38,270),"/>
			<Connection Source="this.DeviceID" Destination="_base.DeviceID" Vertices="(992,270),(820,270),"/>
			<Connection Source="_base.Required" Destination="this.Required" Vertices="(218,330),(38,330),"/>
			<Connection Source="this.SerialNo" Destination="_base.SerialNo" Vertices="(992,330),(820,330),"/>
			<Connection Source="this.SafetyNumber" Destination="_base.SafetyNumber" Vertices="(992,390),(820,390),"/>
			<Connection Source="this.RetryCounteruC1" Destination="_base.RetryCounteruC1" Vertices="(992,450),(820,450),"/>
			<Connection Source="this.RetryCounteruC2" Destination="_base.RetryCounteruC2" Vertices="(992,510),(820,510),"/>
			<Connection Source="this.QuitComError" Destination="_base.QuitComError" Vertices="(992,570),(820,630),"/>
		</Connections>
		<!-- Headerfiles -->
		<Options>
		</Options>
	</Network>
</Class>
*)
#pragma using SdiasSafetyBase

SDM081 : CLASS
: SdiasSafetyBase
  //Servers:
	Safe_Input1 	: SvrCh_DINT;
	Safe_Input2 	: SvrCh_DINT;
	Safe_Input3 	: SvrCh_DINT;
	Safe_Input4 	: SvrCh_DINT;
	Safe_Input5 	: SvrCh_DINT;
	Safe_Input6 	: SvrCh_DINT;
	Safe_Output1 	: SvrCh_DINT;
	Unsafe_Output1 	: SvrCh_DINT;
	Safe_Output2 	: SvrCh_DINT;
	Unsafe_Output2 	: SvrCh_DINT;
	SafeIOError 	: SvrCh_BDINT;
  //Clients:
  //Variables:
		TempInputState : ARRAY [0..9] OF DINT;

		Filter : ARRAY [0..9] OF DINT;

  //Functions:
	
	FUNCTION VIRTUAL GLOBAL Init;
	
	FUNCTION VIRTUAL GLOBAL RtWork
		VAR_INPUT
			EAX 	: UDINT;
		END_VAR
		VAR_OUTPUT
			state (EAX) 	: UDINT;
		END_VAR;
				//! <Function Comment="Called when class state was set to _NoHardware &#13;&#10;No Implementation Overload in derived classes if needed " Name="SetClassStateError"/>
	FUNCTION VIRTUAL SetClassStateError;
	
	FUNCTION VIRTUAL GLOBAL Unsafe_Output1::Write
		VAR_INPUT
			input (EAX) 	: DINT;
		END_VAR
		VAR_OUTPUT
			result (EAX) 	: DINT;
		END_VAR;
	
	FUNCTION VIRTUAL GLOBAL Unsafe_Output2::Write
		VAR_INPUT
			input (EAX) 	: DINT;
		END_VAR
		VAR_OUTPUT
			result (EAX) 	: DINT;
		END_VAR;
  //Tables:
	FUNCTION @STD
		VAR_OUTPUT
			ret_code	: CONFSTATES;
		END_VAR;
	FUNCTION GLOBAL TAB @CT_;
END_CLASS;

//}}LSL_DECLARATION


FUNCTION GLOBAL TAB SDM081::@CT_
0$UINT,
2#0100000000000000$UINT, //TY_SDM081
1$UINT, 4$UINT, (SIZEOF(::SDM081))$UINT, 
11$UINT, 0$UINT, 0$UINT, 
TO_UDINT(2650799298), "SDM081", //Class
TO_UDINT(2010300054), "SdiasSafetyBase", 1$UINT, 6$UINT, //Baseclass
//Servers:
(::SDM081.Safe_Input1.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(53251858), "Safe_Input1", 
(::SDM081.Safe_Input2.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2586173096), "Safe_Input2", 
(::SDM081.Safe_Input3.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(3978489406), "Safe_Input3", 
(::SDM081.Safe_Input4.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(1933999005), "Safe_Input4", 
(::SDM081.Safe_Input5.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(71387915), "Safe_Input5", 
(::SDM081.Safe_Input6.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2638748337), "Safe_Input6", 
(::SDM081.Safe_Output1.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2712786485), "Safe_Output1", 
(::SDM081.Unsafe_Output1.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(4011610486), "Unsafe_Output1", 
(::SDM081.Safe_Output2.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(951617423), "Safe_Output2", 
(::SDM081.Unsafe_Output2.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(1981087948), "Unsafe_Output2", 
(::SDM081.SafeIOError.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(1952502172), "SafeIOError", 
//Clients:
END_FUNCTION


#define USER_CNT_SDM081 1

TYPE
	_LSL_STD_VMETH	: STRUCT
			CmdTable	: CMDMETH;
			UserFcts	: ARRAY[0..USER_CNT_SDM081] OF ^Void;
	END_STRUCT;
END_TYPE

FUNCTION SDM081::@STD
	VAR_OUTPUT
		ret_code	: CONFSTATES;
	END_VAR
	VAR
		vmt	: _LSL_STD_VMETH;
		nCmdSize	: UINT;
	END_VAR

	ret_code	:= SdiasSafetyBase::@STD();
	IF ret_code <> C_OK THEN
		RETURN;
	END_IF;
	nCmdSize		:= SdiasSafetyBase::ClassState.pMeth^.nCmds$UINT*SIZEOF(pVoid) + CMDMETH.Init;

	_memcpy((#vmt.CmdTable)$^USINT, SdiasSafetyBase::ClassState.pMeth, nCmdSize);
	vmt.CmdTable.nCmds		:= nSTDCMD + USER_CNT_SDM081;
	vmt.CmdTable.Init		:= #Init();
	vmt.CmdTable.RtWork		:= #RtWork();
#pragma warning (disable : 74)
	vmt.UserFcts[0]		:= #SetClassStateError();

#pragma warning (default : 74)
	SdiasSafetyBase::ClassState.pMeth		:= StoreCmd (pCmd := #vmt.CmdTable, SHARED);

	IF SdiasSafetyBase::ClassState.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	Unsafe_Output1.pMeth			:= StoreMethod( #M_RD_DIRECT(), #Unsafe_Output1::Write() );
	IF Unsafe_Output1.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	Unsafe_Output2.pMeth			:= StoreMethod( #M_RD_DIRECT(), #Unsafe_Output2::Write() );
	IF Unsafe_Output2.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;

END_FUNCTION

//{{LSL_IMPLEMENTATION


FUNCTION VIRTUAL GLOBAL SDM081::RtWork
	VAR_INPUT
		EAX 	: UDINT;
	END_VAR
	VAR_OUTPUT
		state (EAX) 	: UDINT;
	END_VAR

  // 0 = inputs, 1 = outputs
  if EAX = 0 then

#ifdef SB_SAFETY_INPUT_FILTER
    // if AcceptState bit is set => accept state
    if IOStates AND 2#10 then
      TempInputState[0] := to_dint(IOStates AND 2#1);
      
      if TempInputState[0] < Safe_Input1 then
        if Filter[0] <= 0 then
          Safe_Input1 := TempInputState[0];
        else
          Filter[0] -= 1;
        end_if;
      else
        Safe_Input1 := TempInputState[0];
        Filter[0] := SB_SAFETY_INPUT_FILTER;
      end_if;

      // show error state of this IO
      SafeIOError.1 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input1 := -1;

      // show error state of this IO
      SafeIOError.1 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#1000 then
      TempInputState[1] := to_dint(IOStates AND 2#100) SHR 2;
      
      if TempInputState[1] < Safe_Input2 then
        if Filter[1] <= 0 then
          Safe_Input2 := TempInputState[1];
        else
          Filter[1] -= 1;
        end_if;
      else
        Safe_Input2 := TempInputState[1];
        Filter[1] := SB_SAFETY_INPUT_FILTER;
      end_if;

      // show error state of this IO
      SafeIOError.2 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input2 := -1;

      // show error state of this IO
      SafeIOError.2 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#100000 then
      TempInputState[2] := to_dint(IOStates AND 2#10000) SHR 4;

      if TempInputState[2] < Safe_Input3 then
        if Filter[2] <= 0 then
          Safe_Input3 := TempInputState[2];
        else
          Filter[2] -= 1;
        end_if;
      else
        Safe_Input3 := TempInputState[2];
        Filter[2] := SB_SAFETY_INPUT_FILTER;
      end_if;
      
      // show error state of this IO
      SafeIOError.3 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input3 := -1;

      // show error state of this IO
      SafeIOError.3 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#10000000 then
      TempInputState[3] := to_dint(IOStates AND 2#1000000) SHR 6;

      if TempInputState[3] < Safe_Input4 then
        if Filter[3] <= 0 then
          Safe_Input4 := TempInputState[3];
        else
          Filter[3] -= 1;
        end_if;
      else
        Safe_Input4 := TempInputState[3];
        Filter[3] := SB_SAFETY_INPUT_FILTER;
      end_if;
      
      // show error state of this IO
      SafeIOError.4 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input4 := -1;

      // show error state of this IO
      SafeIOError.4 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#1000000000 then
      TempInputState[4] := to_dint(IOStates AND 2#100000000) SHR 8;

      if TempInputState[4] < Safe_Input5 then
        if Filter[4] <= 0 then
          Safe_Input5 := TempInputState[4];
        else
          Filter[4] -= 1;
        end_if;
      else
        Safe_Input5 := TempInputState[4];
        Filter[4] := SB_SAFETY_INPUT_FILTER;
      end_if;

      // show error state of this IO
      SafeIOError.5 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input5 := -1;

      // show error state of this IO
      SafeIOError.5 := TRUE;
    end_if;
    
    // if AcceptState bit is set => accept state
    if IOStates AND 2#100000000000 then
      TempInputState[5] := to_dint(IOStates AND 2#10000000000) SHR 10;
      
      if TempInputState[5] < Safe_Input6 then
        if Filter[5] <= 0 then
          Safe_Input6 := TempInputState[5];
        else
          Filter[5] -= 1;
        end_if;
      else
        Safe_Input6 := TempInputState[5];
        Filter[5] := SB_SAFETY_INPUT_FILTER;
      end_if;

      // show error state of this IO
      SafeIOError.6 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input6 := -1;

      // show error state of this IO
      SafeIOError.6 := TRUE;
    end_if;

   
     
#else

    // if AcceptState bit is set => accept state
    if IOStates AND 2#10 then
      Safe_Input1 := to_dint(IOStates AND 2#1);

      // show error state of this IO
      SafeIOError.1 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input1 := -1;

      // show error state of this IO
      SafeIOError.1 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#1000 then
      Safe_Input2 := to_dint(IOStates AND 2#100) SHR 2;

      // show error state of this IO
      SafeIOError.2 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input2 := -1;

      // show error state of this IO
      SafeIOError.2 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#100000 then
      Safe_Input3 := to_dint(IOStates AND 2#10000) SHR 4;

      // show error state of this IO
      SafeIOError.3 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input3 := -1;

      // show error state of this IO
      SafeIOError.3 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#10000000 then
      Safe_Input4 := to_dint(IOStates AND 2#1000000) SHR 6;

      // show error state of this IO
      SafeIOError.4 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input4 := -1;

      // show error state of this IO
      SafeIOError.4 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#1000000000 then
      Safe_Input5 := to_dint(IOStates AND 2#100000000) SHR 8;

      // show error state of this IO
      SafeIOError.5 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input5 := -1;

      // show error state of this IO
      SafeIOError.5 := TRUE;
    end_if;
    
    // if AcceptState bit is set => accept state
    if IOStates AND 2#100000000000 then
      Safe_Input6 := to_dint(IOStates AND 2#10000000000) SHR 10;

      // show error state of this IO
      SafeIOError.6 := FALSE;
    else
      // otherwise, there's an error
      Safe_Input6 := -1;

      // show error state of this IO
      SafeIOError.6 := TRUE;
    end_if;
#endif

  //  EAX = 1 : Outputs
  else
  
  // if AcceptState bit is set => accept state
    if IOStates AND 2#10 then
      Safe_Output1 := to_dint(IOStates AND 2#1);

      // show error state of this IO
      SafeIOError.7 := FALSE;
    else
      // otherwise, there's an error
      Safe_Output1 := -1;

      // show error state of this IO
      SafeIOError.7 := TRUE;
    end_if;

    // if AcceptState bit is set => accept state
    if IOStates AND 2#1000 then
      Safe_Output2 := to_dint(IOStates AND 2#100) SHR 2;

      // show error state of this IO
      SafeIOError.8 := FALSE;
    else
      // otherwise, there's an error
      Safe_Output2 := -1;

      // show error state of this IO
      SafeIOError.8 := TRUE;
    end_if;
  
  
  end_if;
  
	state := READY;

END_FUNCTION


FUNCTION VIRTUAL GLOBAL SDM081::Unsafe_Output1::Write
	VAR_INPUT
		input (EAX) 	: DINT;
	END_VAR
	VAR_OUTPUT
		result (EAX) 	: DINT;
	END_VAR

  if input then
    result := Unsafe_Output1 := 1;
    UnsafeOutputStates.1 := TRUE;
  else
    result := Unsafe_Output1 := 0;
    UnsafeOutputStates.1 := FALSE;
  end_if;

END_FUNCTION


FUNCTION VIRTUAL GLOBAL SDM081::Unsafe_Output2::Write
	VAR_INPUT
		input (EAX) 	: DINT;
	END_VAR
	VAR_OUTPUT
		result (EAX) 	: DINT;
	END_VAR

  if input then
    result := Unsafe_Output2 := 1;
    UnsafeOutputStates.2 := TRUE;
  else
    result := Unsafe_Output2 := 0;
    UnsafeOutputStates.2 := FALSE;
  end_if;

END_FUNCTION


FUNCTION VIRTUAL GLOBAL SDM081::Init

  SdiasSafetyBase::Init();
  
  if us_FirstScan = 1 then
    Unsafe_Output1 := Unsafe_Output1 <> 0;
    Unsafe_Output2 := Unsafe_Output2 <> 0;
   
    
    UnsafeOutputStates.1 := to_bool(Unsafe_Output1);
    UnsafeOutputStates.2 := to_bool(Unsafe_Output2);
    
  end_if;

END_FUNCTION


FUNCTION VIRTUAL SDM081::SetClassStateError
  VAR
    i : UDINT;
    pServer : ^DINT;
  END_VAR
  
  pServer := #Safe_Input1;
  
  for i := 0 to 5 do
    pServer^ := SDIAS_SAFETY_INVALID_IO_NOHW;
    pServer += sizeof(SvrCh);
  end_for;
  
  Safe_Output1 := SDIAS_SAFETY_INVALID_IO_NOHW;
  Safe_Output2 := SDIAS_SAFETY_INVALID_IO_NOHW;  
  
END_FUNCTION