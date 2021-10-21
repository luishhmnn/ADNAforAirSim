
// Client.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "Client.h"
#include "ClientDlg.h"



extern "C" {
#include <AHS.h>
#include <AHSUtilities.h>
    //#include <DNASensorActorInterface.h>
#include <DNASensorActorInterfaceSimulator.h>
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// -------------------------------------------------------------------------------------------------
// TODO: evtl auch auslagern
// Find the first digit
int firstDigit(int n)
{
    // Remove last digit from number
    // till only one digit is left
    while (n >= 10)
        n /= 10;

    // return the first digit
    return n;
}
// -------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------
// TODO: auslagern in andere Datei

/**
 * Sensor handler function for the DNA sensor class. Delivers the requested sensor data from the
 * simulator to the sensor class instance.
 *
 * @brief Sensor handler function for the DNA sensor class.
 * @param resource ID of the resource.
 * @param dataSize Size of the data.
 * @param data Pointer to the location of the data.
 * @return Returns 1, if it was successfull.
*/
static int DNASensorHandler(int resource, int dataSize, void* data)
{

    // TODO: First, check if the connection to AirSim is established correctly.

    float res = 0.0f;

    // Client side sensors.
    if (resource == DNA_CLIENT_RESOURCE_SENSOR_STEERING) {
        res = theApp.GetSteering();
    }
    else if (resource == DNA_CLIENT_RESOURCE_SENSOR_THROTTLE) {
        res = theApp.GetThrottle();
    }
    else if (resource == DNA_CLIENT_RESOURCE_SENSOR_BRAKE) {
        res = theApp.GetBrake();
    }
    else if (resource == DNA_CLIENT_RESOURCE_SENSOR_ACC) {
        res = theApp.GetAcc();
    }
    else if (resource == DNA_CLIENT_RESOURCE_SENSOR_LCA) {
        res = theApp.GetLca();
    }
    // Car sensors.
    else if (resource == DNA_CAR_RESOURCE_SENSOR_SPEED) {
        res = res = theApp.m_airLibWrapper.GetSpeed();
    }
    else if (firstDigit(resource) == 5) {
        // Resource IDs with leading 5: Distance sensors.
        CString resourceName;

        // Get result.
        res = theApp.m_airLibWrapper.GetDistanceSensorData(resource);

        // Log the value.
        resourceName.Format(_T("distance %d"), resource);
        theApp.m_logger.LogValue(resourceName, res);
    }
    // TODO: Add other sensor types here.

    else {
        OutputDebugStringA("Warning: A sensor task tries to access a resource whose ID is not known to the client.\n");
    }

    //switch (resource)
    //{
    //case DNA_CLIENT_RESOURCE_SENSOR_STEERING:
    //    res = theApp.GetSteering();
    //    break;
    //case DNA_CLIENT_RESOURCE_SENSOR_THROTTLE:
    //    res = theApp.GetThrottle();
    //    break;
    //case DNA_CLIENT_RESOURCE_SENSOR_BRAKE:
    //    res = theApp.GetBrake();
    //    break;
    //case DNA_CLIENT_RESOURCE_SENSOR_ACC:
    //    res = theApp.GetAcc();
    //    break;
    //case DNA_CLIENT_RESOURCE_SENSOR_LCA:
    //    res = theApp.GetLca();
    //    break;
    //case DNA_CAR_RESOURCE_SENSOR_DISTANCE_LEFT_CURB:
    //    res = theApp.m_airLibWrapper.GetDistanceSensorData(DNA_CAR_RESOURCE_SENSOR_DISTANCE_LEFT_CURB);
    //    theApp.m_logger.LogValue(_T("distanceSensorLeftCurb"), res);
    //    break;
    //case DNA_CAR_RESOURCE_SENSOR_DISTANCE_RIGHT_CURB:
    //    res = theApp.m_airLibWrapper.GetDistanceSensorData(DNA_CAR_RESOURCE_SENSOR_DISTANCE_RIGHT_CURB);
    //    theApp.m_logger.LogValue(_T("distanceSensorRightCurb"), res);
    //    break;
    //case DNA_CAR_RESOURCE_SENSOR_SPEED:
    //    res = theApp.m_airLibWrapper.GetSpeed();
    //    break;
    //default:
    //    // TODO: Raise error or print to log file
    //    OutputDebugStringA("Warning: A sensor task tries to access a resource whose ID is not known to the client.\n");
    //    break;
    //}

    // deliver result
    *((float*)data) = res;

    return 1;
}


/**
 * Actor handler function for the DNA sensor class. Gets the actor data from the
 * vehicle to the actor class instance.
 *
 * @brief Actor handler function for the DNA sensor class.
 * @param resource ID of the resource.
 * @param dataSize Size of the data.
 * @param data Pointer to the location of the data.
*/
static void DNAActorHandler(int resource, int dataSize, void* data)
{
    // correct data size ?
    if (dataSize != sizeof(float)) return;

    switch (resource)
    {
    case DNA_CAR_RESOURCE_ACTOR_THROTTLE:
        theApp.m_airLibWrapper.SetThrottle(*((float*)data));
        theApp.m_logger.LogValue(_T("throttle"), *((float*)data));
        break;
    case DNA_CAR_RESOURCE_ACTOR_STEERING:
        theApp.m_airLibWrapper.SetSteering(*((float*)data));
        theApp.m_logger.LogValue(_T("steering"), *((float*)data));
        break;
    case DNA_CAR_RESOURCE_ACTOR_BRAKE:
        theApp.m_airLibWrapper.SetBrake(*((float*)data));
        theApp.m_logger.LogValue(_T("brake"), *((float*)data));
        break;
    case DNA_CLIENT_RESOURCE_ACTOR_STEERING:
        theApp.SetSteering(*((float*)data));
        break;
    case DNA_CLIENT_RESOURCE_ACTOR_DNACOMPLETE:
        theApp.SetDnaIndicator(*((float*)data));
        break;
    case DNA_CLIENT_RESOURCE_ACTOR_SPEED_INDICATOR:
        theApp.SetSpeedIndicator(*((float*)data));
        break;
    case DNA_CLIENT_RESOURCE_ACTOR_ACC_INDICATOR:
        theApp.SetAcc(*((float*)data));
        break;
    case DNA_CLIENT_RESOURCE_ACTOR_LCA_INDICATOR:
        theApp.SetLca(*((float*)data));
        break;
    default:
        // TODO: Raise error or print to log file
        OutputDebugStringA("Warning: An actor task tries to access a resource whose ID is not known to the client.\n");
        break;
    }
}

// -------------------------------------------------------------------------------------------------

// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
    //ON_COMMAND(ID_HELP, &CWinApp::OnHelp)  // F1 for help
    ON_COMMAND(ID_CONTROL_WAKESYSTEM, &CClientApp::OnWakeAHS)
    ON_COMMAND(ID_CONTROL_SLEEPSYSTEM, &CClientApp::OnSleepAHS)
    ON_COMMAND(ID_CONTROL_CONNECTTORUNNINGAIRSIMSERVER, &CClientApp::OnConnectAirSim)
    ON_COMMAND(ID_CONTROL_DISCONNECTAIRSIM, &CClientApp::OnDisconnectAirSim)
END_MESSAGE_MAP()


// CClientApp construction
CClientApp::CClientApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only CClientApp object
CClientApp theApp;


// CClientApp initialization

BOOL CClientApp::InitInstance()
{
    CWinApp::InitInstance();

    // Activate "Windows Native" visual manager for enabling themes in MFC controls
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    // Load accelerator IDR_ACCELERATOR1 which allows shortcuts
    m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDR_ACCELERATOR1));

    char outString[100];
    int hormoneLoopPeriod;
    AHSHormoneSet hormoneSet;

    hormoneLoopPeriod = HORMONE_LOOP_PERIOD;



    // TODO: init of the AHS (correct error msg)
    /* init the AHS */
    if (!AHSInit(VEHICLE_PLATFORM_ID, (AHSNetworkId)NETWORK_ID)) {
        //sprintf(outString, ERROR_AHS_INIT, (int)AHSGetLastError());
        // TODO: Fix this. 'dlg.MessageBox' will not work.
        //dlg.MessageBox(_T("ERROR"), _T(ERROR_CAPTION), MB_OK);
        OutputDebugStringA("Error: init of the AHS");
        return FALSE;
    }

    // disable hormone loop period checks
    AHSDisableHormoneLoopPeriodCheck(1);


    /* set the hormone loop period */
    if (!AHSSetHormoneLoopPeriod(hormoneLoopPeriod)) {
        //sprintf(outString, ERROR_AHS_INIT, (int)AHSGetLastError());
        //m_pMainWnd->MessageBox(outString, ERROR_CAPTION, MB_ICONEXCLAMATION | MB_OK);
        OutputDebugStringA("Error: hormone loop period");
        return FALSE;
    }


    /* select accelerator threshold */
    AHSEnableAcceleratorThreshold(1);

    /* set sensor/actor handlers */
    DNASetApplicationSimulatorSensorHandler(DNASensorHandler);
    DNASetApplicationSimulatorActorHandler(DNAActorHandler);

    /* start sensor actor simulator interface */
    if (!DNAStartSensorActorSimulatorInterface()) {
        //sprintf(outString, ERROR_AHS_ADDTASK, (int)AHSGetLastError());
        //m_pMainWnd->MessageBox(outString, ERROR_CAPTION, MB_ICONEXCLAMATION | MB_OK);
        
        OutputDebugStringA("Error: sensor actor simulator interface");
        return FALSE;
    }
    /* request high timer resolution */
    // TODO: timeBeginPeriod();
    //timeBeginPeriod(1);

    //-----------------------------------------------------------------------

    // Create the log file
    m_logger.Create();

    // Show the dialog
    CClientDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();

    // Debug print if dialog creation fails
    if (nResponse == -1)
    {
        TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
        TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
    }

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
    ControlBarCleanUp();
#endif


    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}


BOOL CClientApp::ExitInstance()
{
    /* close the AHS */
    AHSClose();

    // TODO: timeEndPeriod()
    /* unrequest high timer resolution */
    //timeEndPeriod(1);

    // TODO: delete the mutex
    // delete the mutex
    // if (m_mutex != NULL) AHSDestroyMutex(m_mutex);

    // Disconnect from AirSim, if connected.
    m_airLibWrapper.Disconnect();

    int i = 1;

    return TRUE;
}


BOOL CClientApp::ProcessMessageFilter(int code, LPMSG lpMsg) {
    if (code >= 0 && m_pMainWnd && m_hAccelTable) {
        if (::TranslateAccelerator(m_pMainWnd->m_hWnd, m_hAccelTable, lpMsg))
            return TRUE;
    }
    return CWinApp::ProcessMessageFilter(code, lpMsg);
}


void CClientApp::OnConnectAirSim()
{
    // Try connecting to AirSim server.
    if (!m_airLibWrapper.Connect())
    {
        // Disable 'Connect to AirSim' menu item.
        CMenu* menu = m_pMainWnd->GetMenu();
        menu->EnableMenuItem(ID_CONTROL_DISCONNECTAIRSIM, 0);
        menu->EnableMenuItem(ID_CONTROL_CONNECTTORUNNINGAIRSIMSERVER, 1);
    }
    else
    {
        // If it fails, raise a MessageBox.
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Couldn't connect to AirSim server. Make sure it runs\nlocally on Port 41451. Do you want to try again?",
            (LPCWSTR)L"Connection Error",
            MB_ICONWARNING | MB_RETRYCANCEL
        );

        // Call the function again, if user selects retry.
        if (msgboxID == IDRETRY) OnConnectAirSim();
    }
}


void CClientApp::OnDisconnectAirSim()
{
    // Disconnect from AirSim server
    m_airLibWrapper.Disconnect();
    // Disable 'Disconnect to AirSim' menu item.
    CMenu* menu = m_pMainWnd->GetMenu();
    menu->EnableMenuItem(ID_CONTROL_DISCONNECTAIRSIM, 1);
    menu->EnableMenuItem(ID_CONTROL_CONNECTTORUNNINGAIRSIMSERVER, 0);
}



void CClientApp::OnWakeAHS()
{
    // TODO: Add your command handler code here
    AHSWakeup();
}


void CClientApp::OnSleepAHS()
{
    // TODO: Add your command handler code here
    AHSSendToSleep();
}




float CClientApp::GetSteering()
{
    /* do it */
    return ((CClientDlg*)m_pMainWnd)->GetSteering();
}


float CClientApp::GetThrottle()
{
    /* do it */
    return ((CClientDlg*)m_pMainWnd)->GetThrottle();
}


float CClientApp::GetBrake()
{
    /* do it */
    return ((CClientDlg*)m_pMainWnd)->GetBrake();
}


float CClientApp::GetAcc()
{
    return ((CClientDlg*)m_pMainWnd)->GetAcc();
}


float CClientApp::GetLca()
{
    return ((CClientDlg*)m_pMainWnd)->GetLca();
}


void CClientApp::SetSteering(float value)
{
    /* do it */
    ((CClientDlg*)m_pMainWnd)->SetSteering(value);
}


void CClientApp::SetDnaIndicator(float value)
{
    ((CClientDlg*)m_pMainWnd)->SetDnaIndicator(value);
}


void CClientApp::SetSpeedIndicator(float value)
{
    ((CClientDlg*)m_pMainWnd)->SetSpeedIndicator(value);
}


void CClientApp::SetAcc(float value)
{
    ((CClientDlg*)m_pMainWnd)->SetAcc(value);
}


void CClientApp::SetLca(float value)
{
    ((CClientDlg*)m_pMainWnd)->SetLca(value);
}
