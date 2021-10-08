/*-----------------------------------------------------------------------------------------------------*/
/*                                                                                                     */
/* Artificial Hormome System (AHS) Utilitiy Functions Header File                                      */
/* These functions are part of the AHS library and can be used freely by the application as well       */
/*                                                                                                     */
/* Revision 1.0.0     23.1.2009    U.Brinkschulte                                                      */
/*                                                                                                     */
/*-----------------------------------------------------------------------------------------------------*/

#ifndef AHSUtilities_H
#define AHSUtilities_H

/* -------------------------------------- Includes ----------------------------------------------------*/

/* -------------------------------------- Global Types -------------------------------------------------*/

typedef struct {
  void         *next;
  void         *prev;
  char         data[4];
} AHSListElement;

typedef struct {
  AHSListElement *index;
  void           *next;
  void           *listAnchor;
  int            adjusted;
} AHSListIndexElement;

typedef AHSListIndexElement *AHSListIndex;

typedef struct {
  void                *first;
  void                *last;
  unsigned long        numberOfElements;
  AHSListIndexElement *firstIndex;
} AHSListAnchor;

typedef AHSListAnchor *AHSList;

/* -------------------------------------- List Functions ----------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSCreateList                                                                                       */
/*                                                                                                     */
/* Creates an empty list                                                                               */
/*                                                                                                     */
/* Returns list handle or NULL on failure                                                              */
/*-----------------------------------------------------------------------------------------------------*/
AHSList AHSCreateList(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSAppendListElement                                                                                */
/*                                                                                                     */
/* Appends a new element to the list                                                                   */
/*                                                                                                     */
/* list :        list to be processed                                                                  */
/* elementSize : size of the element to append                                                         */
/*                                                                                                     */
/* Returns pointer to the element appended or NULL on failure                                          */
/*-----------------------------------------------------------------------------------------------------*/
void *AHSAppendListElement(AHSList list, int elementSize);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSCreateListIndex                                                                                  */
/*                                                                                                     */
/* Creates an index to a list                                                                          */
/*                                                                                                     */
/* list :        list to be processed                                                                  */
/*                                                                                                     */
/* Returns pointer to the index created or NULL on failure                                             */
/*-----------------------------------------------------------------------------------------------------*/
AHSListIndex AHSCreateListIndex(AHSList list);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSResetListIndex                                                                                   */
/*                                                                                                     */
/* Resets an index to a list. This means the next NextListElement operation retrieves the first or     */
/* the next PrevListElementOperation retrieves the last list element                                   */
/*                                                                                                     */
/* index : list index to be reset                                                                      */
/*                                                                                                     */
/*-----------------------------------------------------------------------------------------------------*/
void AHSResetListIndex(AHSListIndex index);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDeleteListIndex                                                                                  */
/*                                                                                                     */
/* Deletes a created list index                                                                        */
/*                                                                                                     */
/* index : list index to be deleted                                                                    */
/*                                                                                                     */
/*-----------------------------------------------------------------------------------------------------*/
void AHSDeleteListIndex(AHSListIndex index);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSNextListElement                                                                                  */
/*                                                                                                     */
/* Gets the next element in the list                                                                   */
/*                                                                                                     */
/* index :   index to current list element                                                             */
/*           index is updated to the next element                                                      */
/*                                                                                                     */
/* Returns the retrieved element or NULL on end of list                                                */
/*-----------------------------------------------------------------------------------------------------*/
void *AHSNextListElement(AHSListIndex index);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSPrevListElement                                                                                  */
/*                                                                                                     */
/* Gets the previous element in the list                                                               */
/*                                                                                                     */
/* index :   index to current list element                                                             */
/*           index is updated to the previous element                                                  */
/*                                                                                                     */
/* Returns the retrieved element or NULL on end of list                                                */
/*-----------------------------------------------------------------------------------------------------*/
void *AHSPrevListElement(AHSListIndex index);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSEmptyList                                                                                        */
/*                                                                                                     */
/* Make the list empty, all indexes to this list are resetted                                          */
/*                                                                                                     */
/* list :         list to be emptied                                                                   */
/*-----------------------------------------------------------------------------------------------------*/
void AHSEmptyList(AHSList list);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDeleteList                                                                                       */
/*                                                                                                     */
/* Deletes the list                                                                                    */
/*                                                                                                     */
/* list :         list to be emptied                                                                   */
/*-----------------------------------------------------------------------------------------------------*/
void AHSDeleteList(AHSList list);
 
/*-----------------------------------------------------------------------------------------------------*/
/* AHSReplaceListElement                                                                               */
/*                                                                                                     */
/* Replaces a list element by a new one, memory occupied by the old element is freed                   */
/*                                                                                                     */
/* index :       index of list element to be replaced                                                  */
/* elementSize : size of the new element                                                               */
/*                                                                                                     */
/* Returns pointer to the new element or NULL on failure                                               */
/*-----------------------------------------------------------------------------------------------------*/
void *AHSReplaceListElement(AHSListIndex index, int elementSize);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSInsertListElement                                                                                */
/*                                                                                                     */
/* Inserts a new element to the list after position given by index                                     */
/*                                                                                                     */
/* index :       index of list element to be inserted after                                            */
/* elementSize : size of the element to insert                                                         */
/*                                                                                                     */
/* Returns pointer to the element inserted or NULL on failure                                          */
/*-----------------------------------------------------------------------------------------------------*/
void *AHSInsertListElement(AHSListIndex index, int elementSize);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDeleteListElement                                                                                */
/*                                                                                                     */
/* Deletes the element given by index, all indexes to this list are updated if affected by deletion    */
/*                                                                                                     */
/* index :       index of list element to be deleted                                                   */
/*                                                                                                     */
/* Returns 0 if failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSDeleteListElement(AHSListIndex index);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetNumberOfListElements                                                                          */
/*                                                                                                     */
/* Returns number of list elements                                                                     */
/*                                                                                                     */
/* list :         list to be processed                                                                 */
/*-----------------------------------------------------------------------------------------------------*/
int AHSGetNumberOfListElements(AHSList list);

/* ------------------------------------ Memory Functions ----------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSAllocateMemory                                                                                   */
/*                                                                                                     */
/* Allocates the requested amount of memory                                                            */
/*                                                                                                     */
/* size : number of bytes to allocate                                                                  */
/*                                                                                                     */
/* Returns pointer to allocated memory, NULL on failure                                                */
/*-----------------------------------------------------------------------------------------------------*/
void *AHSAllocateMemory(unsigned size);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSFreeMemory                                                                                       */
/*                                                                                                     */
/* Deallocates memory previously allocated by AHSAllocateMemory                                        */
/*                                                                                                     */
/* memory : pointer to memory to be deallocated                                                        */
/*-----------------------------------------------------------------------------------------------------*/
void AHSFreeMemory(void *memory);

/* -------------------------------------- Time Functions ----------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSCurrentTime                                                                                      */
/*                                                                                                     */
/* Returns the current time in seconds from any arbitrary start time                                   */
/*-----------------------------------------------------------------------------------------------------*/
unsigned long AHSCurrentTime(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSleepCurrentThread                                                                               */
/*                                                                                                     */
/* Makes the current thread sleep for the given time                                                   */
/*                                                                                                     */
/* sleepTime : time to sleep in milliseconds                                                           */
/*-----------------------------------------------------------------------------------------------------*/
void AHSSleepCurrentThread(unsigned long sleepTime);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSCreateTimer                                                                                      */
/*                                                                                                     */
/* Creates a timer                                                                                     */
/*                                                                                                     */
/* Returns a handle to the timer, NULL on failure                                                      */
/*-----------------------------------------------------------------------------------------------------*/
AHSTimerHandle AHSCreateTimer(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetTimer                                                                                         */
/*                                                                                                     */
/* Sets the given timer to produce an event at the given time                                          */
/*                                                                                                     */
/* timer    : timer to set                                                                             */
/* wakeTime : time in milliseconds until the event is produced                                         */
/*                                                                                                     */
/* Returns 0 on failure                                                                                */
/*-----------------------------------------------------------------------------------------------------*/
int AHSSetTimer(AHSTimerHandle timer, unsigned long wakeTime);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSWaitForTimer                                                                                     */
/*                                                                                                     */
/* Waits for the timer event                                                                           */
/*                                                                                                     */
/* timer : timer to wait for                                                                           */
/*-----------------------------------------------------------------------------------------------------*/
void AHSWaitForTimer(AHSTimerHandle timer);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDestroyTimer                                                                                     */
/*                                                                                                     */
/* Destroys a timer                                                                                    */
/*                                                                                                     */
/* mutex : timer to destroy                                                                            */
/*-----------------------------------------------------------------------------------------------------*/
void AHSDestroyTimer(AHSTimerHandle timer);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSGetTimestamp                                                                                     */
/*                                                                                                     */
/* Returns the current local timestamp                                                                 */
/*-----------------------------------------------------------------------------------------------------*/
unsigned long AHSGetTimestamp(void);

/* -------------------------------------- Sync Functions ----------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSCreateMutex                                                                                      */
/*                                                                                                     */
/* Creates a mutex                                                                                     */
/*                                                                                                     */
/* Returns a handle to the mutex, NULL on failure                                                      */
/*-----------------------------------------------------------------------------------------------------*/
AHSMutexHandle AHSCreateMutex(void);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSLockMutex                                                                                        */
/*                                                                                                     */
/* Locks a mutex                                                                                       */
/*                                                                                                     */
/* mutex : mutex to lock                                                                               */
/*-----------------------------------------------------------------------------------------------------*/
void AHSLockMutex(AHSMutexHandle mutex);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSUnlockMutex                                                                                      */
/*                                                                                                     */
/* Unlocks a mutex                                                                                     */
/*                                                                                                     */
/* mutex : mutex to unlock                                                                             */
/*-----------------------------------------------------------------------------------------------------*/
void AHSUnlockMutex(AHSMutexHandle mutex);

/*-----------------------------------------------------------------------------------------------------*/
/* AHSDestroyMutex                                                                                     */
/*                                                                                                     */
/* Destroys a mutex                                                                                    */
/*                                                                                                     */
/* mutex : mutex to destroy                                                                            */
/*-----------------------------------------------------------------------------------------------------*/
void AHSDestroyMutex(AHSMutexHandle mutex);

/* -------------------------------------- Error Functions ---------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------*/
/* AHSSetUserError                                                                                     */
/*                                                                                                     */
/* Sets a user error code                                                                              */
/*                                                                                                     */
/* error     : error code to set                                                                       */
/* taskHandle: handle of the task the error is related to or NULL if not related to a specific task    */
/*-----------------------------------------------------------------------------------------------------*/
void AHSSetUserError(AHSError error, AHSTaskHandle taskHandle);

#endif
