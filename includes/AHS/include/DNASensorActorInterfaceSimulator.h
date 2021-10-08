/*-----------------------------------------------------------------------------------------------------*/
/*                                                                                                     */
/* DNA Sensor Actor Interface Simulator Library Header                                                 */
/*                                                                                                     */
/* This library realizes the sensor actor interface for simulators by mapping access functions to an   */
/* AHS task. This AHS task provides a callback function which can redirected to a corresponding        */
/* function in the simulator environment providing the simulated sensor and actot data. Therfore, the  */
/* application simulator can use this header file                                                      */ 
/*                                                                                                     */
/* Revision 1.0.0    18.3.2015    U.Brinkschulte                                                       */
/*                                                                                                     */
/*-----------------------------------------------------------------------------------------------------*/

#ifndef DNASensorActorInterfaceSimulator_H
#define DNASensorActorInterfaceSimulator_H

/* -------------------------------------- Includes ----------------------------------------------------*/

#include "AHS.h"

/* -------------------------------------- Global Definitions ------------------------------------------*/

/* ids for sensor and actor requests used by the AHS sensor/actor simulation task in DNASensorActorSimulationInterfaceMessage */
#define DNA_SENSOR_SIMULATOR_REQUEST        0x5a5a
#define DNA_ACTOR_SIMULATOR_REQUEST         0xa5a5

/* maximum data size for a sensor actor simulation task interface message */
#define DNA_MAX_SENSORACTOR_MESSAGE_SIZE    16

/* the task id for the sensor actor simulation task */
#define DNA_SENSORACTOR_INTERFACE_TASK_ID   210

/* -------------------------------------- Global Type Definitions -------------------------------------*/

/* type for application sensor handler function. This function will be called as soon as the sensor actor simulation task */
/* requires sensor data. The resource id and the datasize of the required data are given as parameter while the handler has */
/* to provide the related data. If the handler has no data it can return 0, otherwise a value unequal to 0 has to be returned */
typedef int DNAApplicationSimulatorSensorHandler(int resource, int datasize, void *data); 

/* type for application actor handler function. This function will be called as soon as the sensor actor simulation task */
/* delivers actor data. The resource id, the datasize and the delivered data are given as parameter. */
typedef void DNAApplicationSimulatorActorHandler(int resource, int datasize, void *data); 

/* sensor/actor simulation interface message type */
typedef struct {
    int             resource;
    int             id;
    unsigned char   data[DNA_MAX_SENSORACTOR_MESSAGE_SIZE]; 
} DNASensorActorSimulatorInterfaceMessage;

/* -------------------------------------- Global Variables --------------------------------------------*/

/* -------------------------------------- Global Functions --------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/* DNASetApplicationSimulatorSensorHandler                                                             */
/*                                                                                                     */
/* Sets the application simulator function to handle sensor data. This function is called by every     */
/* sensor request of a sensor DNA class                                                                */
/*                                                                                                     */
/* sensorHandler  : handler function                                                                   */
/*-----------------------------------------------------------------------------------------------------*/
void DNASetApplicationSimulatorSensorHandler(DNAApplicationSimulatorSensorHandler sensorHandler);

/*-----------------------------------------------------------------------------------------------------*/
/* DNASetApplicationSimulatorActorHandler                                                              */
/*                                                                                                     */
/* Sets the application simulator function to handle actor data. This function is called by every      */
/* actor request of an actor DNA class                                                                 */
/*                                                                                                     */
/* actorHandler  : handler function                                                                    */
/*-----------------------------------------------------------------------------------------------------*/
void DNASetApplicationSimulatorActorHandler(DNAApplicationSimulatorActorHandler actorHandler);

/*-----------------------------------------------------------------------------------------------------*/
/* DNAStartSensorActorSimualatorInterface                                                              */
/*                                                                                                     */
/* This functions starts the sensor actor simulator interface. The AHS must be initialized before      */
/* calling this function                                                                               */
/*                                                                                                     */
/* returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int DNAStartSensorActorSimulatorInterface(void);

/*-----------------------------------------------------------------------------------------------------*/
/* DNAStartSimulatorEnvironmentTask                                                                    */
/*                                                                                                     */
/* This functions starts an environmental helper task for the simulator. The AHS must be initialized   */
/* before calling this function. Environmental helper task ids start one above the sensor/actor        */
/* simulator interface task                                                                            */
/*                                                                                                     */
/* taskFunction : the task function to start                                                           */
/* number       : the number of the environmental helper task (starting from 0)                        */
/* messageSize  : the maximum message size for the task                                                */
/*                                                                                                     */
/* returns 0 on failure (use AHS get last error to retrieve the error code)                            */
/*-----------------------------------------------------------------------------------------------------*/
int DNAStartSimulatorEnvironmentTask(void *taskFunction, int number, int messageSize);

/*-----------------------------------------------------------------------------------------------------*/
/* DNAGetSimulatorEnvironmentTaskId                                                                    */
/*                                                                                                     */
/* This functions returns the AHS task id of the environmental helper task with the given number       */
/*                                                                                                     */
/* number       : the number of the environmental helper task (starting from 0)                        */
/*-----------------------------------------------------------------------------------------------------*/
AHSTaskId DNAGetSimulatorEnvironmentTaskId(int number);


#endif

