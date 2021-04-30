#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
void child(char *);


 
 
int main (void)
{
char i;
char *s = &i;
char string[100];
int status,sc;
int p_id;
    printf("This program makes simple arithmetics\n");
     
    while(1)    
    {
        write(1,"Enter an arithmetic statement, e.g., 34 + 132 > \n",50); 
        i = scanf ("%[^\n]%*c", string);   
         
        p_id = fork();  
         
         
        if (p_id == 0)    
            child_func(string);
		
	    else if (p_id == -1)  
        {
            perror("Not possible to fork\n");
            exit(0);
        }
         
        else
        {
            if (p_id > 0)  
            {
                write(1,"\nCreated a child to make your operation, waiting\n",49); 

            wait(&status);
            sc= WEXITSTATUS(status);
            if(sc==50)
            write(1,"Wrong statement!!\n",18);
            if(sc==100)
            write(1,"Division by zero error!!\n",26);
            if(sc==200)
            write(1,"Wrong operator!!\n",18);
            }
        }
         
    }
     
    return (0);
}
 
 
 
int child_func(char *s)
{
    int a, b;
    float d = a/b;
    char op;

    write(2,"I am a child working for my parent\n",36); 
    sscanf(s, "%d %c %d", &a, &op, &b);  
     
    sleep(2);
     
    if ((sscanf(s,"%d %c %d", &a, &op, &b)) != 3)    
        exit(50);
     
    if (op == '/' && b == 0)   
        exit(100);
     
    switch (op) 
    {
        case '+':
            printf("%d %c %d = %d\n\n", a, op, b, a+b);break;
             
        case '-':
            printf("\n%d %c %d = %d\n\n", a, op, b, a-b);break;
             
        case '/':
            printf("\n%d %c %d = %f\n\n", a, op, b, d);break;
             
        case '*':
            printf("\n%d %c %d = %d\n\n", a, op, b, a*b);break;
             
        default:
            exit(200);break;
    }
    exit(0);
     
}
