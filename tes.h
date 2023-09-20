#include <stdio.h>
#include <inttypes.h>

uint16_t
crc16_update(uint16_t crc, uint8_t a)
{
    int i;

    crc ^= a;
    for (i = 0; i < 8; ++i)
    {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xA001;
        else
            crc = (crc >> 1);
    }

    return crc;
}

#define COUNT 5

int main()
{
  uint16_t crc = ~0;
  uint8_t i;

  // last two values represent 16 bit crc value gathered in a first step 
  uint8_t arr[COUNT] = {0x01, 0x01, 0x01, 0xe0, 0x50};

  // 1. check the crc value of the data
  for(i=0;i<(COUNT-2);i++)
  {
  	crc = crc16_update(crc, arr[i]);
  }

  printf("0x%x 0x%x\n", crc & 0xFF, crc >> 8);

  // 2. check if the crc will be null after using a function for crc value as well
  crc = ~0;

  for(i=0;i<COUNT;i++)
  {
  	crc = crc16_update(crc, arr[i]);
  }

  printf("0x%x 0x%x\n", crc & 0xFF, crc >> 8);


  return 0;
}