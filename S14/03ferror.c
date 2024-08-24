/* CELEBF10                                      

   This example puts data out to a stream and then checks that                  
   a write error has not occurred.                                              
                                                                                
 */                                                                             
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

int main(void)
{
   FILE *stream;
   char *string = "Important information";
   stream = fopen("myfile.dat","w");
   if(stream==NULL) {
       perror("Error");
       return 1;
   }
   fprintf(stream, "%s\n", string);
   if (ferror(stream))
   {
      printf("write error¥n");
      clearerr(stream);
   }
   if (fclose(stream))
      printf("fclose error¥n");
      printf("%s(%d)\n",__FILE__,__LINE__);
   return 0;
}
