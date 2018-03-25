#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_callback_handler(int signum) {
   printf("Caught signal %d\n", signum);
}

int main()
{
   // Register signal and signal handler
   for (int i = 1; i <= 31; i++) {
      signal(SIGINT, signal_callback_handler);
   }

   while(1)
   {
      printf("Running.\n");
      sleep(1);
   }
   return EXIT_SUCCESS;
}
