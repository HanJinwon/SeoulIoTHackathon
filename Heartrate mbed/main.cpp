#include "mbed.h"
#include "PulseSensor.h"
 #include "WS2812.h"
#include "PixelArray.h"
 
#define WS2812_BUF 150
#define NUM_COLORS 6
#define NUM_LEDS_PER_COLOR 14
 
PixelArray px(WS2812_BUF);
DigitalOut led(LED1);
 
// See the program page for information on the timing numbers
// The given numbers are for the K64F
WS2812 ws(D8, WS2812_BUF, 4, 13, 10, 17); // 0H, 0L, 1H, 1L

    
 
/** Print the data in a format that can be parsed by the 
 *  Processing application available here: http://pulsesensor.myshopify.com/pages/code-and-guide
 */
void sendDataToProcessing(char symbol, int data)
{
    if(symbol == 'B') 
	   printf("%d\r\n", data);
}
 
 
 
int main() {
    
    PulseSensor sensor(A0, sendDataToProcessing);
 
    pc.baud(115200);
    
    sensor.start();
 
 

    

    while(1) {
	
        }
    
}
