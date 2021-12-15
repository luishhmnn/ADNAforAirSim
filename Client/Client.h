
// Client.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "AirLibWrapper.h"
#include "CLogger.h"

// ---------------------------------
// Constants

#define  ERROR_CAPTION                    "Error"
#define VEHICLE_PLATFORM_ID 200 // unique processor ids in our system
#define NETWORK_ID 0 // the network id
#define  ERROR_AHS_INIT                   "Cannot init the AHS, errorcode %x"
#define HORMONE_LOOP_PERIOD 100 // hormone loop period in milliseconds

// DNA sensor resources of the client
#define DNA_CLIENT_RESOURCE_SENSOR_STEERING					101
#define DNA_CLIENT_RESOURCE_SENSOR_THROTTLE					102
#define DNA_CLIENT_RESOURCE_SENSOR_BRAKE					103
#define DNA_CLIENT_RESOURCE_SENSOR_ACC						104
#define DNA_CLIENT_RESOURCE_SENSOR_LCA						105

// DNA actor resources of the client
#define DNA_CLIENT_RESOURCE_ACTOR_STEERING		            201
#define DNA_CLIENT_RESOURCE_ACTOR_DNACOMPLETE	            202
#define DNA_CLIENT_RESOURCE_ACTOR_SPEED_INDICATOR           203
#define DNA_CLIENT_RESOURCE_ACTOR_ACC_INDICATOR	            204
#define DNA_CLIENT_RESOURCE_ACTOR_LCA_INDICATOR	            205
#define DNA_CLIENT_RESOURCE_ACTOR_REFERENCE_SPEED_INDICATOR 206

// DNA actor resources of the server (car)
#define DNA_CAR_RESOURCE_ACTOR_STEERING						301
#define DNA_CAR_RESOURCE_ACTOR_THROTTLE						302          
#define DNA_CAR_RESOURCE_ACTOR_BRAKE						303

// DNA sensor resources of the server (car)
// Car state
#define DNA_CAR_RESOURCE_SENSOR_SPEED						401


// CClientApp:
// See Client.cpp for the implementation of this class
//

class CClientApp : public CWinApp
{
public:
	CClientApp();
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	HACCEL m_hAccelTable;
	DECLARE_MESSAGE_MAP()
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

public:
	CAirLibWrapper m_airLibWrapper;
	CLogger m_logger;

	afx_msg void OnConnectAirSim();
	afx_msg void OnDisconnectAirSim();
	afx_msg void OnSleepAHS();
	afx_msg void OnWakeAHS();

	float GetSteering();
	float GetThrottle();
	float GetBrake();
	float GetAcc();
	float GetLca();

	void SetSteering(float value);
	void SetDnaIndicator(float value);
	void SetSpeedIndicator(float value);
	void SetReferenceSpeedIndicator(float value);
	void SetAcc(float value);
	void SetLca(float value);
};

extern CClientApp theApp;
