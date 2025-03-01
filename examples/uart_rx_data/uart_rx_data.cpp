#include "SerialTransfer.h"
#include "stdio.h"
#include "hardware/uart.h"


SerialTransfer myTransfer;

struct __attribute__((packed)) STRUCT {
  char z;
  float y;
} testStruct;

char arr[6];


int main()
{
  stdio_usb_init();
  myTransfer.begin(uart0);


	while (true)
	{
		printf("afkhadskghlaskghk\n");
	  if(myTransfer.available())
	  {
	    // use this variable to keep track of how many
	    // bytes we've processed from the receive buffer
	    uint16_t recSize = 0;

	    recSize = myTransfer.rxObj(testStruct, recSize);
	    printf("%d", testStruct.z);
	    printf("%d", testStruct.y);
	    printf(" | ");

	    recSize = myTransfer.rxObj(arr, recSize);
	    printf("%d", arr);
	    printf("%d", arr);
	  }
	}
}
