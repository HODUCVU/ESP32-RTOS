// #include <Arduino_FreeRTOS.h>
#define mainDELAY_LOOP_COUNT    400000

/* The task function. */
void vTaskFunction( void *pvParameters );

const char *pcTextForTask1 = "Task 1 is running\r\n";
const char *pcTextForTask2 = "Task 2 is running\t\n";

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(9600);
  /* Create the first task at priority 1... */
  xTaskCreatePinnedToCore( vTaskFunction, "Task 1", 2000, (void*)pcTextForTask1, 1, NULL,1 );

  /* ... and the second task at priority 2.  The priority is the second to
  last parameter. */
  xTaskCreatePinnedToCore( vTaskFunction, "Task 2", 2000, (void*)pcTextForTask2, 2, NULL,1 );

  /* Start the scheduler so our tasks start executing. */
  //vTaskStartScheduler(); // 

  for( ;; );
//  return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
volatile unsigned long ul;

  /* The string to print out is passed in via the parameter.  Cast this to a
  character pointer. */
  pcTaskName = ( char * ) pvParameters;

  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
    /* Print out the name of this task. */
    Serial.print( pcTaskName );

    /* Delay for a period. */
    for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
    {
    }
  }
}
//-----------------------------------------------------------------
void loop() {}

