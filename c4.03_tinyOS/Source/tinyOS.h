#ifndef TINYOS_H
#define TINYOS_H

#include<stdint.h>
#include "tLib.h"
#include "tConfig.h"

#define TINYOS_TASK_STATE_RDY        0
#define TINYOS_TASK_STATE_DESTORYED  (1<<0)
#define TINYOS_TASK_STATE_DELAYED    (1<<1) 
#define TINYOS_TASK_STATE_SUSPEND    (1<<2 )

typedef uint32_t tTaskStack;

typedef struct tTask {
	tTaskStack * stack;
	tNode linkNode;
	uint32_t delayTicks;
	tNode delayNode;
	uint32_t prio;
	uint32_t state;
	uint32_t slice;
	uint32_t suspendCount;
	
	void (*clean) (void * param);
	void * cleanParam;
	uint8_t requestDeleteFlag;
}tTask;

extern tTask * currentTask;
extern tTask * nextTask;

uint32_t tTaskEnterCritical (void);
void tTaskExitCritical (uint32_t status);

void tTaskRunFirst (void);
void tTaskSwitch (void);

void tTaskSchedInit (void);
void tTaskSchedDisable (void);
void tTaskSchedEnable (void);

void tTaskSched (void);

void tTaskSchedRdy (tTask * task);
void tTaskSchedUnRdy (tTask * task);
void tTaskSchedRemove (tTask * task);
void tTimeTaskWait (tTask * task, uint32_t ticks);
void tTimeTaskWakeUp (tTask * task);
void tTimeTaskRemove (tTask * task);
void tTaskSystemTickHandler (void);
void tTaskDelay (uint32_t delay);

typedef struct tTaskInfo {
	uint32_t delayTicks;
	uint32_t prio;
	uint32_t state;
	uint32_t slice;
	uint32_t suspenCount;
}tTaskInfo;

void tTaskInit (tTask * task, void (*entry)(void *), void * param, uint32_t prio, tTaskStack * stack);

void tTaskSetCleanCallFunc (tTask * task, void (*clean) (void * param), void * param);
void tTaskForceDelete (tTask * task);
void tTaskRequestDelete (tTask * task);
uint8_t tTaskIsRequestedDelete (void);
void tTaskDeleteSelf (void);

void tTaskGetInfo(tTask * task, tTaskInfo * info);

void tSetSysTickPeriod (uint32_t ms);
void tInitApp (void);

void tTaskSuppend (tTask * task);
void tTaskWakeUp (tTask * task);


#endif
