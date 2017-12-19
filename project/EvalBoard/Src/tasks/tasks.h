
#ifndef TASKS_TASKS_H_
#define TASKS_TASKS_H_

void heartbeat_task(void *pvParameters);
//void i2c_task(void *pvParameters);
//void temp_task(void *pvParameters);
void can_task(void *pvParameters);

#endif /* TASKS_TASKS_H_ */
