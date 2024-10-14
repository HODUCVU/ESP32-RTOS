//#include <freertos/FreeRTOS.h>
//#include <freertos/task.h>

/* The two task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

/* Used to hold the handle of Task2. */
TaskHandle_t xTask2Handle;

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(9600);
  xTaskCreate( vTask1, "Task 1", 1000, NULL, 2, NULL );
        /* The task is created at priority 2 ^. */

  xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle);
         /* The task handle is the last parameter ^^^^^^^^^^^^^ */

  for( ;; );
//  return 0;
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
UBaseType_t uxPriority;
//UBaseType_t uxPriority2 ;

  uxPriority = uxTaskPriorityGet( NULL );
  // uxPriority2 = uxTaskPriorityGet(xTask2Handle);

  for( ;; )
  {
    /* Print out the name of this task. */
    Serial.print( "Task1 is running with priority " );
    Serial.println(uxPriority);
    //Serial.println(configMAX_PRIORITIES);

    Serial.print( "About to raise the Task2 priority\r\n" );
    vTaskPrioritySet(xTask2Handle, uxPriority + 1 );
    vTaskDelay(500/portTICK_PERIOD_MS); 

  }
}

/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
UBaseType_t uxPriority;

  uxPriority = uxTaskPriorityGet( NULL );

  for( ;; )
  {

    Serial.print( "Task2 is running with priority " );
    Serial.println(uxPriority); 

    Serial.print( "About to lower the Task2 priority\r\n" );
    vTaskPrioritySet( NULL,uxPriority - 2 );
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}
/*-----------------------------------------------------------*/
void loop(){
  delay(10);
}
