#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <pwd.h>


using namespace std;
char gpath[1024];




uid_t uid = geteuid ();
struct passwd *pw = getpwuid (uid);
string user_name = pw->pw_name;
void handle(int signo)
{
       cout<<endl<<endl;
     
	cout << user_name << " $ " << gpath <<endl;
	fflush(stdout);
}

int basic(char *s,int len)
{
    int j=0,status;
     j++;
    int pid;
    char *t=strtok(s," ");
    char *argv1[100];
    argv1[0]=t;
    while(t!=NULL)
    {
        t=strtok(NULL,"k");
        if(t==NULL)
            break;
        argv1[j]=t;
        j++;
    }
    argv1[j]=NULL;
    pid=fork();

    if(pid==0)
    {
        execvp(*argv1,argv1);

        cout<<"Error";
    }
    
    
          wait(&status);
    

}

int pipe(char *s[],int n)
{ int count;
  char *argv[1024];
   pid_t pid;
    int fds[2];
    int fd=0;   
    int status;
      int j;

    for(j=0;j<n;j++)
    {
	pipe(fds);
        char *t;
        
        t=strtok(s[j]," ");
        argv[0]=t;
        int m=1;
        while(t!=NULL)
        {
            t=strtok(NULL," ");
            if(t==NULL)
                break;
            argv[m]=t;
            m++;
        }
        argv[m]=NULL;
                 
                
	
	if (fork()==0) 
 
	{
          close(fds[0]);
      dup2(fd,0);
               //cout<<"child\n";
                //close(fds[0]);
		//dup2(fds[0], 0);
                if(j!=n-1)
                dup2(fds[1],1);
                //cout<<"Line 48";
		//close(fds[1]);
                execvp(*argv, argv);
                 //cout<<"Line 50";
                _exit(status);

	}
        else 
	{
    	 	  //wait(&status);  
     	  	 //close(fds[1]);
             	 //cout<<"parent\n";
              //  dup2(fds[0],0);
		close(fds[1]);
		fd=fds[0];
                //execvp(*argv, argv);
        	
	}
  
         
    }
	/*if(count==1){
		close(fds[1]);
           dup2(fds[0], 0);
      //close(fds[0]);
		//dup2(fds[1], 1);
		close(fds[0]);
		execvp(*argv, argv);}
*/
    //  wait(&status); 

}
int outputdirect(char *s1,char *s2)
{
    char *t=strtok(s1," ");
    char *argv[500];
    argv[0]=t;
    int i=1,status;
    while(t)
    {
        t=strtok(NULL," ");
        if(t==NULL)
            break;
        argv[i]=t;
        i++;
    }
    argv[i]=NULL;
    char *dest=s2;
    int out;
    out = open(dest, O_WRONLY | O_TRUNC | O_CREAT|O_APPEND,0777);
    if (fork() == 0)
    {
        dup2(out,1);
        close(out);
        execvp(*argv,argv);
    }

     close(out);
  
    wait(NULL);

}

int appenddirect(char *s1,char *s2)
{
    char *t=strtok(s1," ");
    char *argv[200];
    argv[0]=t;
    int i=1,status;
    while(t!=NULL)
    {
        t=strtok(NULL," ");
        if(t==NULL)
            break;
        argv[i]=t;
        i++;
    }
    argv[i]=NULL;
    char *dest=s2;
    int out;
    out = open(dest, O_WRONLY | O_APPEND,0700);
    if (fork() == 0)
    {
        dup2(out,1);
        close(out);
        execvp(*argv,argv);
    }

     close(out);

    wait(NULL);

}


 
int main()
{
    char str[1024];
    char str1[1024];
char *key,*value;
    getcwd(gpath,sizeof(gpath));
    char tempj_path[1024]; 
          FILE *fp; 
            fp = fopen("env.txt", "r");  
           
            if (fp == NULL) {
            perror ("open");
    }
 
          while(fgets(str1,1024,fp)!=NULL)
	    {
                    key=strtok(str1,"=");
                    value=strtok(NULL,"=");
                    setenv(key,value,1);
                }
    char *path=getenv("HOME");
    char path1[1024];
    for(int j=0;j<strlen(path);j++)
    {
        path1[j]=path[j];
    }
    signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle);
        cout << user_name << " $ " << gpath;
	int ofd,rfd;
	while(fgets(str,1024,stdin)!=NULL)
	{
            char *t;
            char *s[1024];
            int len=strlen(str);
            if(!strstr(str,"!"))
            {

                ofd= open(path1, O_WRONLY|O_CREAT|O_APPEND,0700);
                int w=write(ofd,str,strlen(str));
                close(ofd);
            }
            str[strlen(str)-1]='\0';
            if(strstr(str,"cd"))
            {
                t=strtok(str," ");
                t=strtok(NULL," ");
                if(t)
                {
                 chdir(t);
                 getcwd(gpath,sizeof(gpath));
                }
                else
                 {
                    chdir(path);
                    getcwd(gpath,sizeof(gpath));
                 }
            }
            if(strstr(str,"exit"))
            {
                cout<<"Closing Window"<<endl;
                exit(0);
            }
            if(strstr(str,"echo"))
            {
                if(strstr(str,"$$"))
                {
                     pid_t process_id;
                     process_id = getpid();
                     cout<<process_id<<endl;
                   
                }
                else{
            
            
                if(strstr(str,"$")&& !strstr(str,"$$"))
                {
                  t=strtok(str,"$");
                    t=strtok(NULL,"$");
                 
                    cout<<getenv(t)<<endl;
                    
                }
           }
}

           char *hh=strstr(str,"<");
            if(hh==NULL)
            {
             if(strstr(str,">>")){
               
                  t=strtok(str,">>");
                    s[0]=t;
                    t=strtok(NULL,">>");
                    s[1]=t;
                    appenddirect(s[0],s[1]);

             }


            if(strstr(str,">"))
            {
                 if(!strstr(str,"|"))
                 {
                    t=strtok(str,">");
                    s[0]=t;
                    t=strtok(NULL,">");
                    s[1]=t;
                    outputdirect(s[0],s[1]);
                }
            }
           else if(strstr(str,"|"))
            {
                t=strtok(str,"|");
                s[0]=t;
                int i=1;
                while(t!=NULL)
                {
                    t=strtok(NULL,"|");
                    if(t==NULL)
                        break;
                    s[i]=t;
                    i++;
                }
           
           pipe(s,i);
           }
           else
           {
                if(!(strstr(str,"exit")||strstr(str,"cd")))
                 {
                         s[0]=str;
                         basic(s[0],0);
                 }
           
            cout << user_name << " $ " << gpath;

}
	}
}
}
