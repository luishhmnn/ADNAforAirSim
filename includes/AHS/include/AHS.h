/*-----------------------------------------------------------------------------------------------------*/
/*                                                                                                     */
/* Artificial Hormome System (AHS) General Header File                                                 */
/*                                                                                                     */
/* Revision 2.0.0     25.2.2011    U.Brinkschulte                                                      */
/*                                                                                                     */
/*-----------------------------------------------------------------------------------------------------*/

#ifndef AHS_H
#define AHS_H

/* -------------------------------------- Includes ----------------------------------------------------*/

/* -------------------------------------- Global Definitions ------------------------------------------*/

/* Version of the AHS */
#define AHS_VERSION_HIGH          2
#define AHS_VERSION_MID           4
#define AHS_VERSION_LOW           0

/* least significant digit of low version indicates memory based (X.X.X0) or light weight (X.X.X1) hormone evaluation */
#ifdef AHS_LIGHTWEIGHT_HORMONE_EVALUATION
#define AHS_VERSION_LOW_LEAST_DIGIT 1
#else
#define AHS_VERSION_LOW_LEAST_DIGIT 0
#endif

/* Outdate period for hormones */
#define AHS_OUTDATE_PERIOD        4

/* Going to sleep period after sleep hormone received */
#define AHS_GOINGTOSLEEP_PERIOD   5

/* maximum possible processor id */
#define AHS_MAX_PROCESSOR_ID      255

/* maximum possible task id */
#define AHS_MAX_TASK_ID           255

/* maximum possible hormone value */
#define AHS_MAX_HORMONE_VALUE     255

/* maximum possible relation degree */
#define AHS_MAX_RELATION_DEGREE   10

/* highest task priority */
#define AHS_HIGHEST_PRIORITY      1

/* lowest task priority */
#define AHS_LOWEST_PRIORITY       255

/* default task priority */
#define AHS_DEFAULT_PRIORITY      0

/* maximum length of the log name (including path and extension) */
#define AHS_MAX_LOGNAME_LENGTH    255

/* neighbor modes */
#define AHS_LISTMODE              0
#define AHS_GRIDMODE              1

/* user hormone send modes */
#define AHS_ALL                   0
#define AHS_NEIGHBORS             1
#define AHS_MYSELF                2

/* log levels */
#define AHS_LOGLEVEL_NONE         0
#define AHS_LOGLEVEL_LOW          1
#define AHS_LOGLEVEL_MEDIUM       2
#define AHS_LOGLEVEL_HIGH         3
#define AHS_LOGLEVEL_ALL          4

/* default options */
#define AHS_DEFAULT_LOGLEVEL      AHS_LOGLEVEL_NONE /* log level */
#define AHS_DEFAULT_LOGAPPEND     1                 /* log append */
#define AHS_DEFAULT_SUPPRESSDHZS  1                 /* suppress doublle hormone zero sending */
#define AHS_DEFAULT_OFFERWFR      0                 /* offer with full release */
#define AHS_DEFAULT_SORTTBACC     1                 /* sort tasks by accelerators */
#define AHS_DEFAULT_PRIORITYTD    1                 /* priority task decision */
#define AHS_DEFAULT_AGGRESSIVETD  1                 /* aggressive task decision */
#define AHS_DEFAULT_ENHANCEDTC    1                 /* enhanced termination check */
#define AHS_DEFAULT_DISLOOPCHECK  0                 /* disable hormone loop period check */
#define AHS_DEFAULT_USEACCTHRESH  1                 /* use accelerator threshold */ 
#define AHS_DEFAULT_DETERMWAKE    1                 /* deterministic wakeup */
#define AHS_DEFAULT_LOOP_PERIOD   1000              /* default hormone loop period in milliseconds */

/* task conditions */
#define AHS_TASK_RUNNING          1                 /* the task is running */
#define AHS_TASK_PROTECTED        2                 /* the task is running and not allowed to be terminated */
#define AHS_TASK_TERMINATE        3                 /* the task is terminated virtually and waiting for real termination */

/* task options */
#define AHS_TASKOPTION_FORCE_TERMINATION          0x1    /* the AHS is allowed to kill the task directly when the task is lost */
#define AHS_TASKOPTION_SINGLE_INSTANCE            0x2    /* only one instance of this task is allowed to run on our processor */

/* message options */
#define AHS_MESSAGEOPTION_TO_ALL_INSTANCES        0x1    /* message send to all instances of a task */
#define AHS_MESSAGEOPTION_TO_LPID_INSTANCE        0x2    /* message send to task instance with lowest processor id */
#define AHS_MESSAGEOPTION_TO_HPID_INSTANCE        0x3    /* message send to task instance with highest processor id */
#define AHS_MESSAGEOPTION_TO_NLPID_INSTANCE       0x4    /* message send to task instance with next lower processor id */
#define AHS_MESSAGEOPTION_TO_NHPID_INSTANCE       0x5    /* message send to task instance with next higher processor id */
#define AHS_MESSAGEOPTION_TO_PREV_INSTANCE        0x6    /* message send to task instance used previously */

/* maximum administrative message channel */
#define AHS_MAX_ADMIN_MESSAGE_CHANNEL             31

/* -------------------------------------- Global Type Definitions -------------------------------------*/

/* Hormone value data type */
typedef unsigned char AHSHormoneValue;

/* Hormone type */
typedef unsigned char AHSHormoneType;

/* Processor ID data type */
typedef unsigned char AHSProcessorId;

/* Network ID data type */
typedef unsigned char AHSNetworkId;

/* Task ID data type */
typedef unsigned char AHSTaskId;

/* Task priority data type */
typedef unsigned char AHSTaskPriority;

/* Data type for number of related tasks */
typedef unsigned char AHSRelatedTaskNum;

/* Data type for degree of relation ship */
typedef unsigned char AHSRelationDegree;

/* Data type for error handling */
typedef unsigned short AHSError;

/* Data type for hormone spreading mode */
typedef unsigned char AHSSpreadMode;

/* Task handle type */
typedef void *AHSTaskHandle;

/* Data type for task bodies */
typedef unsigned long AHSTaskFunction(AHSTaskHandle taskHandle);

/* Task condition type */
typedef unsigned char AHSTaskCondition;

/* Task options type */
typedef unsigned char AHSTaskOptions;

/* Hormone set */
typedef struct {
  AHSHormoneValue eagervalue;
  AHSHormoneValue taskSuppressor;
  AHSHormoneValue loadSuppressor;
  AHSHormoneValue organAccelerator;
  AHSHormoneValue offerAccelerator;
} AHSHormoneSet;

/* Message type */
typedef void *AHSMessage;

/* Message options */
typedef unsigned char AHSMessageOptions;

/* Some basic handle types */
typedef void *AHSThreadHandle;
typedef void *AHSMutexHandle;
typedef void *AHSSemaphoreHandle;
typedef void *AHSTimerHandle;
typedef void *AHSEventHandle;

/* message address */
typedef struct {
  AHSProcessorId  processorId;
  AHSTaskId       taskId;
  AHSThreadHandle taskInstanceId;
} AHSMessageAddress;

/* Administrative message channel */
typedef unsigned char AHSAdminChannel;

/* -------------------------------------- Global Functions --------------------------------------------*/


/*=====================================================================================================*/
/*                                 Initialization Functions                                            */
/*                                                                                                     */
/* These functions init and close the AHS. They have to be called by the initializing control flow     */
/* before and after using the AHS.                                                                     */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSInit                                                                                             */
/*                                                                                                     */
/* Initializes the artificial hormone system, sets the processor ID of our processor                   */
/* (must be unique in the overall system)                                                              */
/*                                                                                                     */
/* processorId : unique processor id (0 is not allowed)                                                */
/* networkId   : logical network id (this allow several different hormone systems using the same       */
/*                                   physical network, distinguished by different network ids)         */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSInit(AHSProcessorId processorId, AHSNetworkId networkId);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSClose                                                                                            */
/*                                                                                                     */
/* Closes the artificial hormone system                                                                */
/* This function kills all tasks regardless of mode or protection. If all tasks should be safely       */
/* terminated before closing, use AHSSendToSleep (for the entire) or AHSSetSuspendProcessor (for the   */
/* local processor only) and then AHSAllTasksTerminated before calling AHSClose                        */
/*-----------------------------------------------------------------------------------------------------*/
void AHSClose(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetNeighborMode                                                                                  */
/*                                                                                                     */
/* Sets the neighbor mode. In grid mode, neighborship is defined by processor ids. The lower 4 bits    */
/* of the Id define the row and the upper for bits the column of the processor in the grid.            */
/* In list mode, neighborship is defined by a neighbor list set up with the function AHSDefineNeighbor.*/
/* Setting neighbor mode to list mode resets this list                                                 */
/*                                                                                                     */
/* mode: AHS_LISTMODE or AHS_GRIDMODE                                                                  */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetNeighborMode(int mode);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetNeighborMode                                                                                  */
/*                                                                                                     */
/* Returns the current neighbor mode.                                                                  */
/*-----------------------------------------------------------------------------------------------------*/
int AHSGetNeighborMode(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSAddNeighbor                                                                                      */
/*                                                                                                     */
/* Adds a neighbor when in list mode                                                                   */
/*                                                                                                     */
/* id : processor id of a neighbor                                                                     */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSAddNeighbor(AHSProcessorId id);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetHormoneLoopPeriod                                                                             */
/*                                                                                                     */
/* Sets the hormone loop period in milliseconds                                                        */
/*                                                                                                     */
/* period : new period                                                                                 */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetHormoneLoopPeriod(unsigned long period);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDisableHormoneLoopPeriodCheck                                                                    */
/*                                                                                                     */
/* Disables checking for minimum hormone loop period when using AHSSetHormoneLoopPeriod                */
/* (Usually the AHS sets a lower limit for the hormone loop period based on the communication time     */
/*  provided by the communication subsystem to guarantee proper hormone loop operation. This time is   */
/*  a worst-case value so faster hormone loop periods might be possible own own risk                   */
/*                                                                                                     */
/* value : 1 disable, 0 enable                                                                         */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSDisableHormoneLoopPeriodCheck(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSEnableAcceleratorThreshold                                                                       */
/*                                                                                                     */
/* Enables the accelerator threshold mode. In this mode accelerators are only added to eagervalues     */
/* if the eagervalue is already above 0 without the accelerators. This ensures stability of the        */
/* hormone system even if large accelerator values to attract related tasks have been chosen           */
/*                                                                                                     */
/* value : 1 enable, 0 disable                                                                         */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSEnableAcceleratorThreshold(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSuppressDoubleZeroHormoneSending                                                                 */
/*                                                                                                     */
/* Suppresses double sending of zero hormone values                                                    */
/*                                                                                                     */
/* value : 1 suppress, 0 don't suppress                                                                */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSuppressDoubleZeroHormoneSending(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSOfferWithFullRelease                                                                             */
/*                                                                                                     */
/* Offer tasks with full release of load suppressor                                                    */
/*                                                                                                     */
/* value : 1 do it, 0 don't do it                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSOfferWithFullRelease(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSPriorityTaskDecision                                                                             */
/*                                                                                                     */
/* Use priority based task decision                                                                    */
/*                                                                                                     */
/* value : 1 do it, 0 don't do it                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSPriorityTaskDecision(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSAggressiveTaskDecision                                                                           */
/*                                                                                                     */
/* Use aggressive priority based task decision                                                         */
/*                                                                                                     */
/* value : 1 do it, 0 don't do it                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSAggressiveTaskDecision(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSortTasksByAccelerators                                                                          */
/*                                                                                                     */
/* Sort tasks by accelerators                                                                          */
/*                                                                                                     */
/* value : 1 do it, 0 don't do it                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSortTasksByAccelerators(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDeterministicWake                                                                                */
/*                                                                                                     */
/* Sets determinictic wakeup behavior regarding task allocation                                        */
/* (under the same conditions try to produce the same task allocation)                                 */
/*                                                                                                     */
/* value : 1 do it, 0 don't do it                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSDeterministicWake(int value);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSEnhancedTaskTerminationCheck                                                                     */
/*                                                                                                     */
/* Enhanced termination check of tasks                                                                 */
/*                                                                                                     */
/* value : 1 do it, 0 don't do it                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSEnhancedTaskTerminationCheck(int value);

/*=====================================================================================================*/
/*                             AHS Task Definition Functions                                           */
/*                                                                                                     */
/* These functions are used to define AHS tasks. They can be called at start time by the initializing  */
/* control flow or by any AHS task.                                                                    */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSAddTask                                                                                          */
/*                                                                                                     */
/* Adds a new task as a candidate to be executed on this processor.                                    */
/* New tasks are ignored by the hormone loop until they are committed by the AHSCommitTasks function.  */
/* This allows to complete all necessary task info (like e.g. adding related tasks, see next function) */
/* before a task is used by the hormone loop.                                                          */
/*                                                                                                     */
/* taskFunction :    function body of the task                                                         */
/* taskId :          id of the task                                                                    */
/* hormoneSet :      the set of hormones for this task on this processor                               */
/*                   eagervalue       : eagervalue of the task on this processor                       */
/*                   taskSuppressor   : suppressor sent to this task on all other processors when task */
/*                                      is taken here                                                  */
/*                   organAccelerator : accelerator sent to related tasks on neighbor processors when  */
/*                                      the task is taken here to form up an organ                     */
/*                   loadSuppressor   : suppressor sent to all tasks on this processor when task is    */
/*                                      taken here                                                     */
/*                   offerAccelerator : accelerator sent to this task on this processor when offered   */
/* offerPeriod :     period to offer this task                                                         */
/* lifesignPeriod :  the period the task has to give lifesigns to be considered alive (0:no lifesigns) */
/* priority :        the priority of the task (0 means default, 1 highest, max lowest)                 */
/* maxMessageNumber: the maximal number of messages the task can receive simultaneously                */
/* maxMessageSize :  the maximal size of a message the task can receive                                */
/* options :         task options, can be combined by |                                                */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSAddTask(void *taskFunction, AHSTaskId taskId, AHSHormoneSet hormoneSet, unsigned offerPeriod,
               unsigned lifesignPeriod, AHSTaskPriority priority, unsigned short maxMessageNumber,
               unsigned short maxMessageSize, AHSTaskOptions options);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSRemoveTask                                                                                       */
/*                                                                                                     */
/* Removes a task as a candidate to be executed on this processor.                                     */
/* Removed tasks are still handled by the hormone loop until they are committed by the AHSCommitTasks  */
/* function. This allows to bundle and complete all necessary other removements before the tasks       */
/* candidates are really dismissed. Task candidates not committed after being added are removed        */
/* immediately. Furthermore, if a task candidate is removed all task relationships origining from the  */
/* removed task candidate are removed as well. Relationships haveing the removed task candidate as     */
/* desitiantion are not affected (since the removed task candidate might still be present on other     */
/* processors). If these relationships shall also be removed use the AHSRemoveRelatedTask function     */
/*                                                                                                     */
/* taskId :          id of the task (0 means all tasks)                                                */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSRemoveTask(AHSTaskId taskId);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetTaskStackSize                                                                                 */
/*                                                                                                     */
/* Sets the stack size for a task                                .                                     */
/* This function can be used to set a specific stack size for a task. Ususally, the standard operating */
/* system stack size is used for each task. With this function the stack size can be adapted           */
/* individially for a task. This is interesting for systems with low RW memory capabilities.           */
/* This function is only effective if called before the corresponding task starts to run on the        */
/* processor. Therefore, the best  time to call this function is after adding the task and before      */
/* committing the added tasks.                                                                         */
/*                                                                                                     */
/* taskId :          id of the task (0 means all tasks)                                                */
/* stackSize :       size of the task stack in bytes (0 means use default size)                        */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetTaskStackSize(AHSTaskId taskId, unsigned long stackSize);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSAddRelatedTask                                                                                   */
/*                                                                                                     */
/* Adds a new related task to a task candidate on this processor                                       */
/*                                                                                                     */
/* taskId :          id of the task                                                                    */
/* relatedTaskId :   id of the related task                                                            */
/* relationDegree :  degree of relationship (0 .. 10)                                                  */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSAddRelatedTask(AHSTaskId taskId, AHSTaskId relatedTaskId, AHSRelationDegree relationDegree);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSRemoveRelatedTask                                                                                */
/*                                                                                                     */
/* Removes a related task from a task candidate on this processor                                      */
/*                                                                                                     */
/* taskId :          id of the task (0 means all tasks)                                                */
/* relatedTaskId :   id of the related task (0 means all tasks)                                        */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSRemoveRelatedTask(AHSTaskId taskId, AHSTaskId relatedTaskId);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSCommitTasks                                                                                      */
/*                                                                                                     */
/* Commits all tasks newly added since the last call of this function. The tasks will be used by       */
/* the hormone loop now. Furthermore all tasks marked for removement will be removed. Note that the    */
/* removement might not be finished when this function returns. Use AHSWaitForTaskRemovePending to     */
/* test this                                                                                           */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSCommitTasks(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWaitForPendingTaskRemove                                                                         */
/*                                                                                                     */
/* Waits until all pending task removements are finished (all running instances of the task are        */
/* stopped and all task related data is removed)                                                       */
/*                                                                                                     */
/* timeout: maximal wait time in multiples of the hormone loop cycle time (0 means no timeout, 1 means */
/*          don't wait, just test)                                                                     */
/*                                                                                                     */
/* returns 0 if not all pending tasks are removed after wait                                           */
/*-----------------------------------------------------------------------------------------------------*/
int AHSWaitForPendingTaskRemove(unsigned long timeout);


/*=====================================================================================================*/
/*                                    Starting Functions                                               */
/*                                                                                                     */
/* These functions are used to start and stop the AHS. They can be called by the initializing control  */
/* flow or by any AHS task.                                                                            */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWakeup                                                                                           */
/*                                                                                                     */
/* Wakes up the entire artificial hormone system                                                       */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSWakeup(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSendToSleep                                                                                      */
/*                                                                                                     */
/* Sends the entire hormone system to sleep, stops all tasks there                                     */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSendToSleep(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSuspendProcessor                                                                                 */
/*                                                                                                     */
/* Suspends the local processor, stops all tasks                                                       */
/*                                                                                                     */
/* susp : suspend if 1, resume if 0                                                                    */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSuspendProcessor(int susp);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWaitForAllTasksOnProcessorTerminated                                                             */
/*                                                                                                     */
/* Waits for all tasks on our processor are really terminated.                                         */
/*                                                                                                     */
/* timeout: maximal wait time in multiples of the hormone loop cycle time (0 means no timeout, 1 means */
/*          don't wait, just test)                                                                     */
/*                                                                                                     */
/* returns 0 if not all tasks are terminated after wait                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSWaitForAllTasksOnProcessorTerminated(unsigned long timeout);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWaitForHormoneSystemSleeping                                                                     */
/*                                                                                                     */
/* Waits for hormone system fallen asleep.                                                             */
/* (Note: this means all hormone spreading has stopped. It doesn't necessarily mean all tasks are      */
/*  already terminated, since termination of individual tasks can be delayed by the user. Use          */
/*  AHSWaitForAllTasksOnProcessorTerminated to find out about local tasks.)                            */
/*                                                                                                     */
/* timeout: maximal wait time in multiples of the hormone loop cycle time (0 means no timeout, 1 means */
/*          don't wait, just test)                                                                     */
/*                                                                                                     */
/* returns 0 if not asleep after wait                                                                  */
/*-----------------------------------------------------------------------------------------------------*/
int AHSWaitForHormoneSystemSleeping(unsigned long timeout);


/*=====================================================================================================*/
/*                                 General Information Functions                                       */
/*                                                                                                     */
/* These functions deliver general information on the AHS. They can be called by the initializing      */
/* control flow or by any AHS task.                                                                    */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetVersion                                                                                       */
/*                                                                                                     */
/* Delivers the version number high.mid.low of the AHS. The version is returned optionally as the      */
/* three numbers or as a string                                                                        */
/*                                                                                                     */
/* versionHigh : the high part of the version number (if not NULL)                                     */
/* versionMid :  the mid part of the version number (if not NULL)                                      */
/* versionLow :  the low part of the version number (if not NULL)                                      */ 
/* versionStr :  the version as a string "high.mid.low" (if not NULL)                                  */
/*                                                                                                     */
/* The least significant digit of the low version part indicates memory based (X.X.X0) or light        */
/* weight (X.X.X1) hormone evaluation                                                                  */
/*-----------------------------------------------------------------------------------------------------*/
void AHSGetVersion(int *versionHigh, int *versionMid, int *versionLow, char *versionStr);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSIsLightWeight                                                                                    */
/*                                                                                                     */
/* Returns 1 if light weight hormone evaluation, 0 otherwise                                           */
/*-----------------------------------------------------------------------------------------------------*/
int AHSIsLightWeight(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyProcessorId                                                                                 */
/*                                                                                                     */
/* Returns the processor id (or 0, if not yet defined                                                  */
/*-----------------------------------------------------------------------------------------------------*/
AHSProcessorId AHSGetMyProcessorId(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyNetworkId                                                                                   */
/*                                                                                                     */
/* Returns the network id                                                                              */
/*-----------------------------------------------------------------------------------------------------*/
AHSProcessorId AHSGetMyNetworkId(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetHormoneLoopPeriod                                                                             */
/*                                                                                                     */
/* returns the hormone loop period in milliseconds or 0 on failure                                     */
/*-----------------------------------------------------------------------------------------------------*/
unsigned long AHSGetHormoneLoopPeriod(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSIsNeighbor                                                                                       */
/*                                                                                                     */
/* id : processor id to be tested for neighborhood                                                     */
/*                                                                                                     */
/* Returns 1 if the given processor id is a neighbor to us                                             */
/*-----------------------------------------------------------------------------------------------------*/
int  AHSIsNeighbor(AHSProcessorId id);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSTaskIsActive                                                                                     */
/*                                                                                                     */
/* Tests if the given task is active in the system.                                                    */
/*                                                                                                     */
/* taskId : id of the task                                                                             */
/* processorId : id of the processor where the task should be tested (0 means the entire system)       */
/*                                                                                                     */
/* If a special processor is asked (processorId != 0), this function returns:                          */
/* 0 if the task is not active, 1 if the task is safely running, 2 if the task is running but          */
/* endangered to be lost                                                                               */
/* If the entire system is asked (processorId == 0), this function returns:                            */
/* 0 if the task is not active, otherwise the number of processor elements where the task is running   */
/*-----------------------------------------------------------------------------------------------------*/
int AHSTaskIsActive(AHSTaskId taskId, AHSProcessorId processorId);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSTasksActiveOnMyProcessor                                                                         */
/*                                                                                                     */
/* Delivers a map of the tasks active on my processor.                                                 */
/*                                                                                                     */
/* taskIds :      array of task ids active on my processor                                             */
/* length       : length of the task id array, contains the actual number of tasks on return           */
/*                                                                                                     */
/* returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSTasksActiveOnMyProcessor(AHSTaskId *taskIds, unsigned *length);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetTaskUserHormoneLevel                                                                          */
/*                                                                                                     */
/* Gets the user hormone level for a given task                                                        */
/*                                                                                                     */
/* taskId       : id of the task                                                                       */ 
/* hormoneType  : type of user hormone                                                                 */
/*                                                                                                     */
/* Returns value of hormone level                                                                      */
/*-----------------------------------------------------------------------------------------------------*/
AHSHormoneValue AHSGetTaskUserHormoneLevel(AHSTaskId taskId, AHSHormoneType hormoneType);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMaxMessageSize                                                                                */
/*                                                                                                     */
/* Returns the maximum possible size of a message in the system                                        */
/* (this is the maximum possible value which can be given as the maxMessageSize parameter of the       */
/*  AHSAddTaskFunction)                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
unsigned short AHSGetMaxMessageSize(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetCommSystemInfo                                                                                */
/*                                                                                                     */
/* Returns a pointer to the information string which classifies the underlying communication system    */
/*-----------------------------------------------------------------------------------------------------*/
char *AHSGetCommSystemInfo(void);

/*=====================================================================================================*/
/*                                 Error Handling and Logging Functions                                */
/*                                                                                                     */
/* These functions are used to retrieve error codes and set logging levels. They can be called by the  */
/* initializing control flow or by any AHS task.                                                       */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetLastError                                                                                     */
/*                                                                                                     */
/* Returns the last error code occured, deletes this error code                                        */
/*-----------------------------------------------------------------------------------------------------*/
AHSError AHSGetLastError(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetLogLevel                                                                                      */
/*                                                                                                     */
/* Sets the current log level for the system (taskId = 0) or a specific task (taskId > 0)              */
/*                                                                                                     */
/* level :  the new log level                                                                          */
/* taskId : the task id                                                                                */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetLogLevel(unsigned level, AHSTaskId taskId);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetLogLevel                                                                                      */
/*                                                                                                     */
/* taskId : the task id                                                                                */
/*                                                                                                     */
/* Returns the current log level for the system (taskId = 0) or a specific task (taskId > 0)           */
/*-----------------------------------------------------------------------------------------------------*/
unsigned AHSGetLogLevel(AHSTaskId taskId);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetLogPath                                                                                       */
/*                                                                                                     */
/* Sets the current log path                                                                           */
/*                                                                                                     */
/* path : the new log path                                                                             */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetLogPath(char *path);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetLogAppend                                                                                     */
/*                                                                                                     */
/* Sets the current log append mode                                                                    */
/*                                                                                                     */
/* append : log file will be appended if 1, else newly created each time                               */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetLogAppend(int append);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWriteUserLogEntry                                                                                */
/*                                                                                                     */
/* Writes a user entry to the log file                                                                 */
/*                                                                                                     */
/* taskHandle : handle of the task                                                                     */ 
/* format :     formated entry to write(can be formated like printf)                                   */
/* level :      write the entry if the log level for the task given by task handle is greate or equal  */
/*              to the level given here                                                                */
/* additional variable arguments according to the format specifications in format                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSWriteUserLogEntry(AHSTaskHandle taskHandle, char *str, unsigned level, ...);

/*=====================================================================================================*/
/*                                 Monitoring Hormone Functions                                        */
/*                                                                                                     */
/* These functions are used to set the monitoring hormone levels. They can be called by the            */
/* initializing control flow or by any AHS task.                                                       */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetMonitoringSuppressor                                                                          */
/*                                                                                                     */
/* Sets the monitoring suppressor                                                                      */
/*                                                                                                     */
/* suppressor : new value                                                                              */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetMonitoringSuppressor(AHSHormoneValue suppressor);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetMonitoringAccelerator                                                                         */
/*                                                                                                     */
/* Sets the monitoring accelerator                                                                     */
/*                                                                                                     */
/* accelerator : new value                                                                             */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetMonitoringAccelerator(AHSHormoneValue accelerator);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSClearOverloadSuppressor                                                                          */
/*                                                                                                     */
/* Clears the overload suppressor. The overload suppressor is an additional monitoring suppressor      */
/* which is maintained automatically by the hormone system in case of internal overload conditions     */
/* (e.g. out of memory conditions). The overload suppressor is internally cleared when initializing    */
/* the AHS, but is not modified by reawakening the system after sending it to sleep. So the AHS keeps  */
/* its knowledge about its load limits also when going to sleep. You can call this function to         */
/* manually clear this suppressor, e.g. after setting a new task or modifying the existing task set    */
/* which might cause a differnt load scenario.                                                         */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSClearOverloadSuppressor(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetOverloadSuppressor                                                                            */
/*                                                                                                     */
/* Gets the current value of the overload supproessor (for information purpose).                       */
/*                                                                                                     */
/* Returns the value                                                                                   */
/*-----------------------------------------------------------------------------------------------------*/
AHSHormoneValue AHSGetOverloadSuppressor(void);

/*=====================================================================================================*/
/*                                    AHS Task Related Functions                                       */
/*                                                                                                     */
/* These functions are related to the AHS tasks and called by AHS tasks. The calling task identifies   */
/* itself by its TaskHandle given at start parameter of each task.                                     */
/* Some of these function can be called by the initializing control flow as well by setting TaskHandle */
/* to NULL (see function definitions to find out which).                                               */
/* Note: use this special feature only when calling such a function by the initializing control flow.  */
/* NULL must not be used when calling these functions from a AHS task, because AHS tasks might be      */
/* terminated asynchronously by the AHS. So TaskHandle is used as well to protect AHS tasks from       */
/* termination when running in a critical function section. Otherwise, resources might not be released */
/* properly on termination causing the AHS to be blocked.                                              */
/*                                                                                                     */
/*=====================================================================================================*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyTaskId                                                                                      */
/*                                                                                                     */
/* taskHandle : handle of the task                                                                     */ 
/*                                                                                                     */
/* Returns the id of the task given by the task handle or 0 on failure. This is treated as a lifesign  */
/* of the task in case of lifesign monitoring.                                                         */
/*-----------------------------------------------------------------------------------------------------*/
AHSTaskId AHSGetMyTaskId(AHSTaskHandle taskHandle);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyTaskCondition                                                                               */
/*                                                                                                     */
/* taskHandle :    handle of the task                                                                  */ 
/* lastTaskError : returns the last error code specific to this task (NULL if not interested)          */
/*                                                                                                     */
/* Returns the condition of the task given by the task handle. If requested, the last task related     */
/* error is reported too (AHSGetLastError reports the last error by all tasks and the system. So a     */
/* task specific error might be overwritten by others tasks or the system before it could be retrieved */
/* by the task. That will not happen to this error code)                                               */
/* The call of this function is treated as a lifesign of the task in case of lifesign monitoring.      */
/*-----------------------------------------------------------------------------------------------------*/
AHSTaskCondition AHSGetMyTaskCondition(AHSTaskHandle taskHandle, AHSError *lastTaskError);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSProtectMyTask                                                                                    */
/*                                                                                                     */
/* Protect the task given by the task handle against termination. This is treated as a lifesign        */
/* of the task in case of lifesign monitoring.                                                         */
/*                                                                                                     */
/* taskHandle : handle of the task                                                                     */ 
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSProtectMyTask(AHSTaskHandle taskHandle);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSUnprotectMyTask                                                                                  */
/*                                                                                                     */
/* Removes protection of the task given by the task handle against termination. This is treated as a   */
/* lifesign of the task in case of lifesign monitoring.                                                */
/*                                                                                                     */
/* taskHandle : handle of the task                                                                     */ 
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSUnprotectMyTask(AHSTaskHandle taskHandle);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSMyTaskLifesign                                                                                   */
/*                                                                                                     */
/* taskHandle : handle of the task                                                                     */ 
/*                                                                                                     */
/* Gives a lifesign for the task when lifesign monitoring                                              */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSMyTaskLifesign(AHSTaskHandle taskHandle);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSTaskIsActiveWhere                                                                                */
/*                                                                                                     */
/* Delivers a map on which processors a given task is active in the system.                            */
/*                                                                                                     */
/* taskHandle   : handle of the calling task (used for protection, can be NULL when not called from    */
/*                a task)                                                                              */
/* taskId       : id of the task to query                                                              */
/* processorIds : array of processor ids where the task is active                                      */
/* length       : length of the processor id array, contains the actual number of processors on return */
/*                                                                                                     */
/* returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSTaskIsActiveWhere(AHSTaskHandle taskHandle, AHSTaskId taskId, AHSProcessorId *processorIds, unsigned *length);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSpreadMyUserHormone                                                                              */
/*                                                                                                     */
/* Spreads user hormones for the task given by the task handle                                         */
/*                                                                                                     */
/* taskHandle   : handle of the spreading task or NULL if spreaded by the processor itself             */ 
/* spreadMode   : way to spread hormone: AHS_ALL, AHS_NEIGHBORS, AHS_MYSELF                            */
/* hormoneType  : type of user hormone                                                                 */
/* forTaskId    : the task this hormone is for, 0 means for all                                        */
/* hormoneValue : value of the user hormone                                                            */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSpreadMyUserHormone(AHSTaskHandle taskHandle, AHSSpreadMode spreadMode, AHSHormoneType hormoneType, AHSTaskId forTaskId, AHSHormoneValue hormoneValue);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyUserHormoneLevel                                                                            */
/*                                                                                                     */
/* Gets the user hormone level for the task given by the task handle                                   */
/*                                                                                                     */
/* taskHandle   : handle of the task                                                                   */ 
/* hormoneType  : type of user hormone                                                                 */
/*                                                                                                     */
/* Returns value of hormone level                                                                      */
/*-----------------------------------------------------------------------------------------------------*/
AHSHormoneValue AHSGetMyUserHormoneLevel(AHSTaskHandle taskHandle, AHSHormoneType hormoneType);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWaitForMyUserHormoneLevelChange                                                                  */
/*                                                                                                     */
/* The task given by the handle waits until the the user hormone level retrieved at last using the     */
/* AHSGetMyTaskUserHormoneLevel function changes                                                       */
/*                                                                                                     */
/* taskHandle   : handle of the task                                                                   */ 
/* timeout      : maximal wait time in multiples of the hormone loop cycle time (0 means no timeout,   */
/*                1 means don't wait, just test)                                                       */
/*                                                                                                     */
/* Returns 0 if not changed (wait may end due to timeout or task termination request)                  */
/*-----------------------------------------------------------------------------------------------------*/
int AHSWaitForMyUserHormoneLevelChange(AHSTaskHandle taskHandle, unsigned long timeout);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyTaskHormoneInfo                                                                             */
/*                                                                                                     */
/* taskHandle :         handle of the task (or NULL if not called from within an AHS task)             */
/* taskId :             id of the task if taskHandle is NULL, otherwise ignored                        */
/* greatestEagervalue : the greatest eagervalue for this task in the system                            */
/* sumSuppressors :     the sum of all suppressors for this task in the system                         */
/* sumAccelerators :    the sum of all accelerators for this task in the system                        */
/*                                                                                                     */
/* Gets the current highest eagervalue and sum of suppressors and accelerators for the task for info   */
/* purpose.                                                                                            */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSGetMyTaskHormoneInfo(AHSTaskHandle taskHandle, AHSTaskId taskId, unsigned *greatestEagervalue, unsigned *sumSuppressors, unsigned *sumAccelerators);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSendMessage                                                                                      */
/*                                                                                                     */
/* Sends a message to the given task.                                                                  */
/*                                                                                                     */
/* taskHandle   : handle of the sending task or NULL if send by the processor itself                   */ 
/* toTask       : task to send the message to (0 means to all tasks)                                   */
/* message      : message to send                                                                      */
/* messageSize  : size of the message to send                                                          */
/* options      : sending options                                                                      */
/*                 none                                : send to the best suited task instance         */
/*                 AHS_MESSAGEOPTION_TO_LPID_INSTANCE  : send to the task instance with lowest         */
/*                                                       processor id                                  */
/*                 AHS_MESSAGEOPTION_TO_HPID_INSTANCE  : send to the task instance with highest        */
/*                                                       processor id                                  */
/*                 AHS_MESSAGEOPTION_TO_ALL_INSTANCES  : send to all instances of the given task       */
/*                                                                                                     */
/*                 the following options are only available when taskHandle != NULL:                   */
/*                                                                                                     */
/*                 AHS_MESSAGEOPTION_TO_NLPID_INSTANCE : send to the task instance with next lower     */
/*                                                       processor id then last time                   */
/*                 AHS_MESSAGEOPTION_TO_NHPID_INSTANCE : send to the task instance with next higher    */
/*                                                       processor id then last time                   */
/*                 AHS_MESSAGEOPTION_TO_PREV_INSTANCE  : send to the task instance with same           */
/*                                                       processor id then last time                   */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSendMessage(AHSTaskHandle taskHandle, AHSTaskId toTaskId, AHSMessage message, unsigned messageSize, AHSMessageOptions options);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSReceiveMessage                                                                                   */
/*                                                                                                     */
/* Waits for receiving a message from a given task.                                                    */
/*                                                                                                     */
/* taskHandle   : handle of the receiving task                                                         */ 
/* fromTask     : task to receive the message from (0 means from any task, contains the task id the    */
/*                                                  message was received from on return)               */
/* fromTask     : task to receive the message from (0 means from any task)                             */
/* message      : message received                                                                     */
/* messageSize  : size of the message buffer on calling and size of the message received on return     */
/* timeout      : maximal wait time in multiples of the hormone loop cycle time (0 means no timeout,   */
/*                1 means don't wait, just test if message is available)                               */
/*                                                                                                     */
/* Returns 0 on failure (may be caused e.g. by a timeout or the task we want to receive a message      */
/* from has moved or vanished)                                                                         */
/*-----------------------------------------------------------------------------------------------------*/
int AHSReceiveMessage(AHSTaskHandle taskHandle, AHSTaskId *fromTaskId, AHSMessage message, unsigned *messageSize, unsigned long timeout);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSendReplyMessage                                                                                 */
/*                                                                                                     */
/* Sends a reply message to the last message received using the AHSReceiveMessage function. The reply  */
/* is send to the exactly same task instance the last message was received from.                       */
/*                                                                                                     */
/* taskHandle   : handle of the sending task                                                           */ 
/* message      : message to send                                                                      */
/* messageSize  : size of the message to send                                                          */
/* options      : sending options                                                                      */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSendReplyMessage(AHSTaskHandle taskHandle, AHSMessage message, unsigned messageSize, AHSMessageOptions options);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSReceiveReplyMessage                                                                              */
/*                                                                                                     */
/* Waits for receiving a reply message for the last message send using the AHSSendMessage function.    */
/* The reply is expected to be received from the exactly same task instance the last message was sent  */
/* to.                                                                                                 */
/*                                                                                                     */
/* taskHandle   : handle of the receiving task                                                         */ 
/* message      : message received                                                                     */
/* messageSize  : size of the message received                                                         */
/* timeout      : maximal wait time in multiples of the hormone loop cycle time (0 means no timeout,   */
/*                1 means don't wait, just test if message is available)                               */
/*                                                                                                     */
/* Returns 0 on failure (may be caused e.g. by a timeout or the task we want to receive a message      */
/* from has moved or vanished)                                                                         */
/*-----------------------------------------------------------------------------------------------------*/
int AHSReceiveReplyMessage(AHSTaskHandle taskHandle, AHSMessage message, unsigned *messageSize, unsigned long timeout);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSaveReceivedMessageAddress                                                                       */
/*                                                                                                     */
/* Save the sender address (processor, task, instance) of the last message received by                 */
/* AHSReceiveMessage or AHSReceiveReplyMessage to a variable. This address can be restored later       */
/* by the function AHSRestoreReceivedMessageAddress allowing to reply later.                           */
/*                                                                                                     */
/* taskHandle     : handle of the calling task                                                         */ 
/* messageAddress : takes the sender address of the last message received                              */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSaveReceivedMessageAddress(AHSTaskHandle taskHandle, AHSMessageAddress *messageAddress);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSRestoreReceivedMessageAddress                                                                    */
/*                                                                                                     */
/* Restores the sender address (processor, task, instance) of a message saved by                       */
/* AHSSaveReceivedMessageAddress. After restoring a call to AHSSendReplyMessage can be used to reply   */
/* to this sender                                                                                      */
/*                                                                                                     */
/* taskHandle     : handle of the calling task                                                         */ 
/* messageAddress : contains the sender address saved by AHSSaveReceivedMessageAddress                 */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSRestoreReceivedMessageAddress(AHSTaskHandle taskHandle, AHSMessageAddress messageAddress);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSaveSentMessageAddress                                                                           */
/*                                                                                                     */
/* Save the receiver address (processor, task, instance) of the last message send by                   */
/* AHSSendMessage or AHSSendReplyMessage to a variable. This address can be restored later             */
/* by the function AHSRestoreSentMessageAddress allowing to wait for a reply or sending to the same    */
/* receiver later.                                                                                     */
/*                                                                                                     */
/* taskHandle     : handle of the calling task                                                         */ 
/* messageAddress : takes the receiver address of the last message sent                                */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSaveSentMessageAddress(AHSTaskHandle taskHandle, AHSMessageAddress *messageAddress);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSRestoreSentMessageAddress                                                                        */
/*                                                                                                     */
/* Restores the receiver address (processor, task, instance) of a message saved by                     */
/* AHSSaveSentMessageAddress. After restoring a call to AHSReceiveReplyMessage or AHSSendMessage can   */ 
/* be used to wait for a reply of this receiver or send another message to this receiver               */
/*                                                                                                     */
/* taskHandle     : handle of the calling task                                                         */ 
/* messageAddress : contains the receiver address saved by AHSSaveSentMessageAddress                   */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSRestoreSentMessageAddress(AHSTaskHandle taskHandle, AHSMessageAddress messageAddress);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSendAdminMessage                                                                                 */
/*                                                                                                     */
/* Sends an administrative message to a processor                                                      */
/*                                                                                                     */
/* taskHandle :    handle of the calling task (or NULL if not called by a task)                        */
/* toProcessorId : id of the target processor (0 means all processors)                                 */
/* channel  :      administration channel to use for transmission                                      */
/* message :       pointer to the buffer containing the message                                        */
/* messageLength : length of the message                                                               */
/*                                                                                                     */
/* Note: this function is usually not called by a AHS task (taskHandle = NULL), since it is used to    */
/*       send administrative messages between processors (and not tasks). However, it is save to call  */
/*       this function also in an AHS task context (taskHandle != NULL)                                */
/* Note: sending an administrative message to a dedicated processor (not a broadcast) requires either  */
/*       the hormone system to be awake or at least an administrative message from this processor has  */
/*       to be received when the hormone system is sleeping. Otherwise the AHS does not know yet how   */
/*       to reach this.                                                                                */                 
/*                                                                                                     */
/* Returns the number of bytes send or 0 on failure                                                    */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSendAdminMessage(AHSTaskHandle taskHandle, AHSProcessorId toProcessorId, AHSAdminChannel channel, AHSMessage message, unsigned messageLength);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSReceiveAdminMessage                                                                              */
/*                                                                                                     */
/* Delivers a received admin message from. If no message availabe the                                  */
/* function blocks depending on the value of the timeout parameter                                     */
/*                                                                                                     */
/* taskHandle :      handle of the calling task (or NULL if not called by a task)                      */
/* message :         the message buffer (can be NULL if the message simply shall be dropped)           */
/* messageLength :   length of the message buffer, delivers the actual length of the message retrieved */
/*                   (can be NULL if the message simply shall be dropped)                              */
/* fromProcessorId : delivers the sender processor id (can be NULL if not needed)                      */
/* broadcast :       delivers if the received message was a broadcast (1) or dedicated to this         */
/*                   processor (0) (can be NULL if not needed)                                         */
/* channel :         delivers the admin channel the message was received (can be NULL if not needed)   */
/* timeout :         timeout if no message is available (0 means no timeout, wait forever,             */
/*                   > 0 means timeout in msec, < 0 means do not wait, just try)                       */
/*                                                                                                     */
/* Note: this function is usually not called by a AHS task (taskHandle = NULL), since it is used to    */
/*       send administrative messages between processors (and not tasks). You can call this function   */
/*       also in an AHS task context (taskHandle != NULL), but take care: as long as the function      */
/*       waits for a message the calling task is protected against termination. Also, if more than     */
/*       one task call this function concurrently, it is a competition. A message will only be         */
/*       retrieved once. Which task gets the message is unpredictable.                                 */
/* Note: before receiving admin messages the size of the admin receive buffer has to be set by calling */
/*       the function AHSSetAdminReceiveBuffer and the corresponding receive channel has to be         */
/*       enabled by calling the function AHSEnableAdminReceiveChannel                                  */
/*                                                                                                     */
/* Returns the number of bytes retrieved or 0 on none available (timeout or just try)                  */
/*-----------------------------------------------------------------------------------------------------*/
int AHSReceiveAdminMessage(AHSTaskHandle taskHandle, AHSMessage message, int *messageLength, AHSProcessorId *fromProcessorId, int *broadcast, AHSAdminChannel *channel, long timeout);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetAdminReceiveBuffer                                                                            */
/*                                                                                                     */
/* Creates the buffer necessary to receive admin messages                                              */
/*                                                                                                     */
/* taskHandle :      handle of the calling task (or NULL if not called by a task)                      */
/* bufferSize :      size of the buffer in bytes                                                       */
/*                                                                                                     */
/* Returns 0 if failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetAdminReceiveBuffer(AHSTaskHandle taskHandle, unsigned long bufferSize);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSEnableAdminReceiveChannel                                                                        */
/*                                                                                                     */
/* Enables or disable a receive channel for admin messages                                             */
/*                                                                                                     */
/* taskHandle :      handle of the calling task (or NULL if not called by a task)                      */
/* channel :         channel to enable or disable                                                      */
/* enable :          if 0 the channel is disabled, otherwise enabled                                   */
/*                                                                                                     */
/* Returns 0 if failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSEnableAdminReceiveChannel(AHSTaskHandle taskHandle, AHSAdminChannel channel, int enable);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetMyMaxMessageSize                                                                              */
/*                                                                                                     */
/* taskHandle     : handle of the calling task                                                         */ 
/*                                                                                                     */
/* Returns the maximum possible size of a message for the calling task                                 */
/* (this is the actual maximum size for the calling task defined by the maxMessageSize parameter       */
/* of the AHSAddTaskFunction when adding the task)                                                     */
/*-----------------------------------------------------------------------------------------------------*/
unsigned short AHSGetMyMaxMessageSize(AHSTaskHandle taskHandle);

#endif
