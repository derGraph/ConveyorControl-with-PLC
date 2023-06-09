//This file was generated by the LASAL2 CodeGenerator  -- 
//Please, do not edit this file (it might be overwritten by the next generator run)
//{{LSL_DECLARATION

(*!
<Class
	Name               = "Abschluss"
	Revision           = "0.0"
	GUID               = "{BB19EDAB-8D7A-40B3-81F9-F577FC003029}"
	RealtimeTask       = "false"
	CyclicTask         = "true"
	DefCyclictime      = "10 ms"
	BackgroundTask     = "false"
	Sigmatek           = "false"
	OSInterface        = "false"
	HighPriority       = "false"
	Automatic          = "false"
	UpdateMode         = "Prescan"
	SharedCommandTable = "true"
	Objectsize         = "(398,120)">
	<Channels>
		<Server Name="Alarm" GUID="{D6D33915-50FC-4D43-905D-2F7A102ACBEA}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="auto" GUID="{E9FA69DF-A111-4CB3-AB3D-4492A1B234F8}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="auto_spd" GUID="{2E8B1E83-9BB8-4921-BCDC-0BEF3F4AC5AF}" Visualized="true" Initialize="true" DefValue="500" WriteProtected="false" Retentive="false"/>
		<Server Name="ClassSvr" GUID="{D66A182C-7CEE-4972-9956-849067C52A2D}" Visualized="false" Initialize="false" WriteProtected="true" Retentive="false"/>
		<Server Name="hand" GUID="{9BE87AAC-6EEA-4311-B618-01FC3F8F81C2}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="input_S1" GUID="{1BA4D985-5BCF-4CDC-A592-28D9A9E90519}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="input_S2" GUID="{9C7F4C39-07A2-4869-8D0A-0510158CB92B}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="input_S3" GUID="{87E6E1BC-6441-4164-86E0-8D66BFB3F3B2}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="spd" GUID="{6582BC91-540F-4B07-8A59-5D13324A9D15}" Visualized="false" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="status" GUID="{137BE5C2-C85E-470B-9D07-28FF3B9C8921}" Visualized="false" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Server Name="stop" GUID="{7D89A164-10BD-42BC-8512-2F056C01F67F}" Visualized="true" Initialize="false" WriteProtected="false" Retentive="false"/>
		<Client Name="MTR_enable" Required="true" Internal="false"/>
		<Client Name="MTR_speed" Required="true" Internal="false"/>
	</Channels>
</Class>
*)
Abschluss : CLASS
	TYPE
	  state_type :  //! <Type Public="true" Name="state_type"/>
	  (
	    waitForInput:=0,
	    auto_mtr_on:=1,
	    auto_mtr_fill:=2,
	    hand_active:=3,
	    err
	  )$UDINT;
	END_TYPE
  //Servers:
	ClassSvr 	: SvrChCmd_DINT;
	status 	: SvrCh_state_type_PTofCls_Abschluss;
	auto 	: SvrCh_DINT;
	spd 	: SvrCh_DINT;
	hand 	: SvrCh_DINT;
	input_S1 	: SvrCh_DINT;
	input_S2 	: SvrCh_DINT;
	input_S3 	: SvrCh_DINT;
	stop 	: SvrCh_DINT;
	Alarm 	: SvrCh_DINT;
	auto_spd 	: SvrCh_DINT;
  //Clients:
	MTR_speed 	: CltCh_DINT;
	MTR_enable 	: CltCh_DINT;
  //Variables:
  //Functions:
	
	FUNCTION VIRTUAL GLOBAL CyWork
		VAR_INPUT
			EAX 	: UDINT;
		END_VAR
		VAR_OUTPUT
			state (EAX) 	: UDINT;
		END_VAR;
  //Tables:
	FUNCTION @STD
		VAR_OUTPUT
			ret_code	: CONFSTATES;
		END_VAR;
	FUNCTION GLOBAL TAB @CT_;
END_CLASS;

//}}LSL_DECLARATION


FUNCTION GLOBAL TAB Abschluss::@CT_
0$UINT,
2#0100000000000010$UINT, //TY_ABSCHLUSS
0$UINT, 0$UINT, (SIZEOF(::Abschluss))$UINT, 
11$UINT, 2$UINT, 0$UINT, 
TO_UDINT(1869306653), "Abschluss", //Class
TO_UDINT(0), 0, 0$UINT, 0$UINT, //Baseclass
//Servers:
(::Abschluss.ClassSvr.pMeth)$UINT, _CH_CMD$UINT, 2#0000000000000000$UINT, TO_UDINT(619352855), "ClassSvr", 
(::Abschluss.status.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2348327578), "status", 
(::Abschluss.auto.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(1345308750), "auto", 
(::Abschluss.spd.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(1521586470), "spd", 
(::Abschluss.hand.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(301444923), "hand", 
(::Abschluss.input_S1.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(1484701458), "input_S1", 
(::Abschluss.input_S2.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(3245862568), "input_S2", 
(::Abschluss.input_S3.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(3060850238), "input_S3", 
(::Abschluss.stop.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2411985666), "stop", 
(::Abschluss.Alarm.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2211153005), "Alarm", 
(::Abschluss.auto_spd.pMeth)$UINT, _CH_SVR$UINT, 2#0000000000000000$UINT, TO_UDINT(2329545139), "auto_spd", 
//Clients:
(::Abschluss.MTR_speed.pCh)$UINT, _CH_CLT_DATA$UINT, 2#0000000000000010$UINT, TO_UDINT(1870300197), "MTR_speed", 
(::Abschluss.MTR_enable.pCh)$UINT, _CH_CLT_DATA$UINT, 2#0000000000000010$UINT, TO_UDINT(3614717934), "MTR_enable", 
END_FUNCTION


#define USER_CNT_Abschluss 0

TYPE
	_LSL_STD_VMETH	: STRUCT
			CmdTable	: CMDMETH;
			UserFcts	: ARRAY[0..USER_CNT_Abschluss] OF ^Void;
	END_STRUCT;
END_TYPE

FUNCTION Abschluss::@STD
	VAR_OUTPUT
		ret_code	: CONFSTATES;
	END_VAR
	VAR
		vmt	: _LSL_STD_VMETH;
	END_VAR

	//Command Methods
	InitCmdTable (nCmd := nSTDCMD + USER_CNT_Abschluss, pCmd := #vmt.CmdTable);
	vmt.CmdTable.CyWork		:= #CyWork();
	ClassSvr.pMeth		:= StoreCmd (pCmd := #vmt.CmdTable, SHARED);

	IF ClassSvr.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	status.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF status.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	auto.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF auto.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	spd.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF spd.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	hand.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF hand.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	input_S1.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF input_S1.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	input_S2.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF input_S2.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	input_S3.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF input_S3.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	stop.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF stop.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	Alarm.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF Alarm.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;
	auto_spd.pMeth			:= StoreMethod( #M_RD_DIRECT(), #M_WR_DIRECT() );
	IF auto_spd.pMeth THEN
		ret_code	:= C_OK;
	ELSE
		ret_code	:= C_OUTOF_NEAR;
		RETURN;
	END_IF;

END_FUNCTION

//{{LSL_IMPLEMENTATION


FUNCTION VIRTUAL GLOBAL Abschluss::CyWork
	VAR_INPUT
		EAX 	: UDINT;
	END_VAR
	VAR_OUTPUT
		state (EAX) 	: UDINT;
	END_VAR
    
    if input_S3 = 1 or stop = 1 then
      Alarm:=1;
      stop:=1;
      MTR_enable := 0;
      status := err;
      else
        Alarm:=0;
    end_if;
    
    if hand = 1 then
      status := hand_active;
    else
      if auto = 1 then
        status := auto_mtr_on;
        else if status = hand_active or stop = 1 then
              status := waitForInput;
             end_if;
          
      end_if;
    end_if;

  
  case status of
    err:
      
    
    waitForInput:
      Alarm := 2;
      if stop = 1 then
        Alarm := 1;
      end_if;
      
      spd := 0;
      MTR_enable := 0;
    
    auto_mtr_on:
      MTR_enable := 1;
      spd := auto_spd;
      if input_S1 = 1 then
        status := auto_mtr_fill;
      end_if;

    auto_mtr_fill:
      MTR_enable := 0;
      spd := 0;
      if input_S2 = 1 then
        status := auto_mtr_on;
      end_if;
      
    hand_active:
      MTR_enable := 1;
      spd := auto_spd*2;
      

  end_case;

  
  
  MTR_speed.Write (spd);
  MTR_enable.Write (MTR_enable);
  
	state := READY;

END_FUNCTION
