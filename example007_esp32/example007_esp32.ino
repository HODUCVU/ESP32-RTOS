#include <freertos\FreeRTOS.h>
#include <esp_freertos_hooks.h>

void vTaskFunction( void *pvParameters );

/* A variable that is incremented by the idle task hook function. */
volatile unsigned long ulIdleCycleCount = 0UL;

const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\t\n";

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(9600);
  /* Create the first task at priority 1... */
  xTaskCreate( vTaskFunction, "Task 1", 2000, (void*)pcTextForTask1, 1, NULL );

  xTaskCreate( vTaskFunction, "Task 2", 2000, (void*)pcTextForTask2, 2, NULL );


  for( ;; );
//  return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;


  pcTaskName = ( char * ) pvParameters;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {

    Serial.print(pcTaskName);
    Serial.println(ulIdleCycleCount );

    vTaskDelay( 250 / portTICK_PERIOD_MS );
  }
}
/*-----------------------------------------------------------*/

extern "C"{ // FreeRTOS expects C linkage
  void vApplicationIdleHook( void )
  {
    /* This hook function does nothing but increment a counter. */
    ulIdleCycleCount++;
  }
}
//------------------------------------------------------------------------------
void loop() {}

