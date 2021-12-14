// AirLibWrapper.h : header file

#pragma once

#include <common/common_utils/StrictMode.hpp>
STRICT_MODE_OFF
#ifndef RPCLIB_MSGPACK
#define RPCLIB_MSGPACK clmdep_msgpack
#endif // !RPCLIB_MSGPACK
#include "rpc/rpc_error.h"
STRICT_MODE_ON

#include <vehicles/car/api/CarRpcLibClient.hpp>

extern "C" {
#include <AHS.h>
#include <AHSUtilities.h>
}

// AirSim server constants
#define IP_ADRESS    "localhost"
#define PORT         41451
#define TIMEOUT_SEC  60.0f
#define VEHICLE_NAME "Car"


using namespace msr::airlib;


class CAirLibWrapper
{
public:
    /**
     * @brief Creates a new CAirLibWrapper object.
    */
    CAirLibWrapper();
   
    /**
     * @brief Establishes connection to a running AirSim server.
     * @param ipAddress IP adress of the AirSim server.
     * @param port Port of the AirSim server.
     * @param timeoutSec
     * @param vehicleName Name of the vehicle in AirSim's settings JSON.
     * @return 0 if connection can be established, 1 otherwise.
    */
    int Connect(string   ipAddress=IP_ADRESS,
                 uint16_t port=PORT,
                 float    timeoutSec=TIMEOUT_SEC,
                 string   vehicleName=VEHICLE_NAME);

    /**
     * @brief Disconnects from an AirSim server.
    */
    void Disconnect();

    /**
     * Sets the steering of the car. Valid position range is from:
     * 1 (left) ... 2 (middle) ... 3 (right).
     * All other positions are invalid and ignored. This allows us to 
     * ignore 0 output when the processor with the steering actor fails.
     * 
     * @brief Sets the steering of the car.
     * @param steering Value between 1 and 3.
    */
    void SetSteering(float steering);

    /**
     * @brief Sets the throttle of the engine.
     * @param throttle Value between 0 (no throttle) and 1 (full throttle).
    */
    void SetThrottle(float throttle);

    /**
     * @brief Sets the value of the brake.
     * @param brake Value between 0 (no braking) and 1 (full braking).
    */
    void SetBrake(float brake);

    /**
     * @return Speed of the car.
    */
    float GetSpeed();

    /**
     * @brief Returns the distance value of a distance sensor.
     * @param resource ID of the distance sensor.
     * @return distance value.
    */
    float GetDistanceSensorData(int resource);

    /**
     * @brief Locks the mutex.
    */
    void LockMutex();

    /**
     * @brief Unlocks the mutex.
    */
    void UnlockMutex();
private:
    AHSMutexHandle          m_mutex;
    CarRpcLibClient*        m_carRpcLibClient;
    CarApiBase::CarControls m_carControls;
    string                  m_vehicleName;
    bool                    m_connected;
};
