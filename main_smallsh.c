#include "smallsh.h"

char *prompt = "Command>>> ";

int userin(char *p);
void procline(void);

int main()
{
        printf("\nHello, please enter a command within 10 seconds...\n\n");
	while (userin(prompt) != EOF)
		if (to!=1)
			procline();
		else
			printf("Can you please enter a command within 10 seconds again ...\n\n");
}
