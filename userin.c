#include "smallsh.h"

// command arg1 arg2 arg3
static char inpbuf[MAXBUF], tokbuf[2 * MAXBUF],
* ptr = inpbuf, * tok = tokbuf;

int inarg(char c);
char *currentDirectory();

void signal_catch (int sig){
	to = 1;
	puts(" Please press the 'Enter key' to continue.\n");
}
int userin(char* p)
{
	int c, count;
	ptr = inpbuf;
	tok = tokbuf;

   // Task2: to display the current working directory  with $ in the prompt currentDirectory() from "project.c"
	char* ptr = currentDirectory();
	strcat(ptr,"$ ");
	printf("%s", ptr);
	
	// Task 4: using alarm signal to give annoying messgage and ignore the buffer if not typed in 10 sec.
	signal(SIGALRM, signal_catch);	
	alarm(10);
	to=0;

	count = 0;
	while (1)
	{
		if ((c = getchar()) == EOF)
			return(EOF);
		if (count < MAXBUF)
			inpbuf[count++] = c;
		if (c == '\n' && count < MAXBUF)
		{
			inpbuf[count] = '\0';
			return count;
		}

		if (c == '\n')
		{
			printf("smallsh: input line too long\n");
			count = 0;
			printf("%s ", p);
		}
	}

	//	printf("inpbuf=%s\n", inpbuf);
}

int gettok(char** outptr)
{
	int type;

	*outptr = tok;

	while (*ptr == ' ' || *ptr == '\t')
		ptr++;

	*tok++ = *ptr;

	switch (*ptr++) {
	case '\n':
		type = EOL;
		break;
	case '&':
		type = AMPERSAND;
		break;
	case ';':
		type = SEMICOLON;
		break;
	case '>':
		type = REDIRECT;
		break;
	case '|':
		type = PIPE;
		break;
	default:
		type = ARG;

		while (inarg(*ptr))
			*tok++ = *ptr++;
	}
	*tok++ = '\0';
	return type;
}

//****************************************************************************************
static char special[] = { ' ', '\t', '&', ';', '\n', '\0' };
int inarg(char c)
{
	char* wrk;
	for (wrk = special; *wrk; wrk++)
	{
		if (c == *wrk)
			return (0);
	}
	return (1);
}