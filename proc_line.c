#include "smallsh.h"

int gettok(char **outptr);
int runcommand(char **cline, int where);

int join(char *com1[]);
void redirect(char *com1[], int arc);

void procline(void)
{
	char *arg[MAXARG + 1];

	int toktype;
	int narg;
	int type;

	narg = 0;
	first = 0, second = 0;
	int c = 1, r = 0;
	int re = 0;

	for (;;)
	{
		switch (toktype = gettok(&arg[narg]))
		{
		case ARG:
			if (narg < MAXARG)
			{
				narg++;
				c == 1 ? first++ : second++;
			}
			break;
		
		case REDIRECT:
			printf("\nREDIRECT\n");
			r = 1;
			re = narg;
			break;
		
		case PIPE:
			printf("\nPIPE\n");
			is_Pipe = PIPE;
			c = 0;
			break;

		case EOL:
		case SEMICOLON:
		case AMPERSAND:
			// Handling pipe
			if (is_Pipe == PIPE)
			{
				int ret = join(arg);
				is_Pipe = 0;
			}
			else if (r == 1)
			{
				redirect(arg, re);
			}
			else
			{
				if (toktype == AMPERSAND)
					type = BACKGROUND;
				else
					type = FOREGROUND;
				if (narg != 0)
				{
					arg[narg] = NULL;
					
					argc_c = narg; //It is  use to change directory

					//Task 3: exit the prompt if user  just type “exit” or “quit” 
					//then terminate the shell.
					// Further handles the error if  more arguments with exit or quit
					if (strcmp(arg[0], "exit") == 0 || strcmp(arg[0], "quit") == 0)
					{
						if (narg == 1)
							    exit(1);
						else
							    printf("error to exit/quit \n");
					}
					else if (strcmp(arg[0], "calculator") == 0 || strcmp(arg[0], "./calculator") == 0)
					{
						if (narg == 1)
							{
								strcpy(arg[0],"./calculator");
							    runcommand(arg,type);
							}
						else
							printf("error to exit/quit\n");
					}
					else
						runcommand(arg, type);
				}
			}
			if (toktype == EOL)
				return;
			narg = 0;
			break;
		}
	}
}
