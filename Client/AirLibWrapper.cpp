
// AirLibWrapper.cpp : implementation file
//

#include "pch.h"

extern "C" {
#include <AHS.h>
#include <AHSUtilities.h>
}

#include "AirLibWrapper.h"


CAirLibWrapper::CAirLibWrapper(){
    m_mutex = AHSCreateMutex();
    m_carRpcLibClient = nullptr;
    m_carControls = CarApiBase::CarControls();
    m_vehicleName = string();
    m_connected = false;
}


int CAirLibWrapper::Connect(
    string   ipAddress,
    uint16_t port,
    float    timeoutSec,
    string   vehicleName)
{
    m_carRpcLibClient = new CarRpcLibClient(ipAddress, port, timeoutSec);

    try
    {
        m_carRpcLibClient->enableApiControl(true);
    }
    catch (const std::exception&)
    {
        OutputDebugStringA("Error: Connection could not be established!");
        return 1;
    }
    
    m_connected = true;
    m_vehicleName = vehicleName;

    return 0;
}


void CAirLibWrapper::Disconnect()
{
    if (!m_connected) return;

    // Disconnect from the AirSim server
    try
    {
        m_carRpcLibClient->reset();
        m_carRpcLibClient->enableApiControl(false);
    }
    catch (const std::exception&)
    {
        OutputDebugStringA("Error: Connection could not be closed properly.");
    }
    
    delete m_carRpcLibClient;
}


void CAirLibWrapper::SetSteering(float steering)
{
    if (!m_connected) return;

    if ((steering < 1) || (steering > 3)) return;

    // Transform position to -1 .. 0 .. 1 range and set it.
    LockMutex();
    m_carControls.steering = steering-2;
    m_carRpcLibClient->setCarControls(m_carControls);
    UnlockMutex();
}


void CAirLibWrapper::SetThrottle(float throttle)
{
    if (!m_connected) return;

    LockMutex();
    m_carControls.throttle = throttle;
    m_carRpcLibClient->setCarControls(m_carControls);
    UnlockMutex();
}


void CAirLibWrapper::SetBrake(float brake)
{
    if (!m_connected) return;

    LockMutex();
    m_carControls.brake = brake;
    m_carRpcLibClient->setCarControls(m_carControls);
    UnlockMutex();
}


float CAirLibWrapper::GetSpeed()
{
    if (!m_connected) return NAN;

    CarApiBase::CarState carState;
    carState = m_carRpcLibClient->getCarState();
    return carState.speed;
}


float CAirLibWrapper::GetDistanceSensorData(int resource)
{
    if (!m_connected) return NAN;

    try
    {
        DistanceSensorData distanceSensorData;
        string             distanceSensorName;

        // Convert resource ID to string, because AirSim API needs a string.
        distanceSensorName = std::to_string(resource);

        // Get the DistanceSensorData from AirSim server. Make sure, that settings.json
        // contains the correct distance sensor name and vehicle name!
        distanceSensorData = m_carRpcLibClient->getDistanceSensorData(distanceSensorName, m_vehicleName);

        return distanceSensorData.distance;
    }
    catch (rpc::rpc_error& e)
    {
        // get the error message
        //string msg = e.get_error().as<string>();

        // FIXME: exception handling
        //        It would be better if the MessageBox is raised by
        //        the app or the dialog, instead of the AirLibWrapper
        int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"Couldn't get distance sensor data from AirSim API.\n"
                      "Make sure that the name of the sensor in settings.json\n"
                      "matches the resource ID of your DNA.",
            (LPCWSTR)L"AirSim API Exception",
            MB_ICONWARNING | MB_RETRYCANCEL
        );

        return NAN;
    }
}


void CAirLibWrapper::LockMutex()
{
    // do it
    AHSLockMutex(m_mutex);
}


void CAirLibWrapper::UnlockMutex()
{
    // do it
    AHSUnlockMutex(m_mutex);
}

