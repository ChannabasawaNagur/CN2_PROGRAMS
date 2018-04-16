#include <stdio.h>
#include <stdlib.h>
typedef unsigned char      byte;    
typedef unsigned short int word16;  
typedef unsigned int       word32;  
#define BUFFER_LEN        4096      // Length of buffer
word16 checksum(byte *addr, word32 count);
void main(void)
{
  byte        buff[BUFFER_LEN]; // Buffer of packet bytes
  word16      check;            // 16-bit checksum value
  word32      i;                // Loop counter
  // Load buffer with BUFFER_LEN random bytes
  for (i=0; i<BUFFER_LEN; i++)
    buff[i] = (byte) rand();
  // Compute the 16-bit checksum
  check = checksum(buff, BUFFER_LEN);
  // Output the checksum
  printf("checksum = %04X \n", check);
}
word16 checksum(byte *addr, word32 count)
{
  register word32 sum = 0;
  // Main summing loop
  while(count > 1)
  {
    sum = sum + (*((word16 *) addr))++;
    count = count - 2;
  }
  // Add left-over byte, if any
  if (count > 0)
    sum = sum + *((byte *) addr);
  // Fold 32-bit sum to 16 bits
  while (sum>>16)
    sum = (sum & 0xFFFF) + (sum >> 16);
  return(~sum);
}


