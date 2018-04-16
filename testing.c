#include<stdio.h>
#include<string.h>

int main()
{
  char *a="asdkfjasdk\n";
  if(strchr(a,'\n'))
    printf("haha");
  return 0;
}
