
static void vSenderTask( void *pvParameters );
static void vReceiverTask( void *pvParameters );

QueueHandle_t xQueue;


void setup( void )
{
  Serial.begin(9600);
  
    /* The queue is created to hold a maximum of 5 long values. */
    xQueue = xQueueCreate( 5  , sizeof( long ) );

  if( xQueue != NULL )
  {
    xTaskCreate( vSenderTask, "Sender1", 1000, ( void * ) 100, 1, NULL );
    xTaskCreate( vSenderTask, "Sender2", 1000, ( void * ) 200, 1, NULL );

    xTaskCreate( vReceiverTask, "Receiver", 1000, NULL, 2, NULL );

    /* Start the scheduler so the created tasks start executing. */
   // vTaskStartScheduler();
  }
  else
  {
    /* The queue could not be created. */
    Serial.println("The queue could not be created.");
  }

  for( ;; );
}
/*-----------------------------------------------------------*/

static void vSenderTask( void *pvParameters )
{
long lValueToSend;
BaseType_t xStatus;

  lValueToSend = ( long ) pvParameters;
  
  Serial.print("lValueToSend = ");
  Serial.println(lValueToSend);
  
  for( ;; )
  {

    xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );

    if( xStatus != pdPASS )
    {
      Serial.print( "Could not send to the queue.\r\n" );
    }

    taskYIELD();
  }
}
/*-----------------------------------------------------------*/

static void vReceiverTask( void *pvParameters )
{
/* Declare the variable that will hold the values received from the queue. */
long lReceivedValue;
BaseType_t xStatus;
const TickType_t xTicksToWait = 100 / portTICK_PERIOD_MS;

  for( ;; )
  {

    xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );

    if( xStatus == pdPASS )
    {
      Serial.print("Received = ");
      Serial.println(lReceivedValue);
    }
    else
    {
      Serial.print( "Could not receive from the queue.\r\n" );
    }
  }
}
//------------------------------------------------------------------------------
void loop() {}


