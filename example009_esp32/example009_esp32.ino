
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

/* Used to hold the handle of Task2. */
TaskHandle_t xTask2Handle;

/*-----------------------------------------------------------*/

void setup( void )
{
  Serial.begin(9600);

  xTaskCreate( vTask1, "Task 1", 2000, NULL, 1, NULL );

  for( ;; );
//  return 0;
}
/*-----------------------------------------------------------*/
void vTask2( void *pvParameters )
{

  Serial.print( "Task2 is running and about to delete itself\r\n" );
  vTaskDelete(xTask2Handle);
}
/*-----------------------------------------------------------*/
void vTask1( void *pvParameters )
{
const TickType_t xDelay500ms = 500 / portTICK_PERIOD_MS;

  for( ;; )
  {
    /* Print out the name of this task. */
    Serial.print( "Task1 is running\r\n" );

    xTaskCreate( vTask2, "Task 2", 2000, NULL, 2, &xTask2Handle );
       /* The task handle is the last parameter ^^^^^^^^^^^^^ */

    vTaskDelay( xDelay500ms );
  }
}

/*-----------------------------------------------------------*/


void loop() {}
