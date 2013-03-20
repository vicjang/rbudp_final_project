#include <stdio.h>
#include <sys/types.h>

int main(void)
{
    printf( "this is a test\n" );

    pid_t childPid1;
    pid_t childPid2;

    //splitFile();


    if( ( childPid1 = fork() ) == 0 )
    {
        // child 1
        printf( "first clause %d\n", childPid1 );
        system( "./ttt.abc" );
        //RBUDP_send();
    }
    else
    {
        // parent
        if( ( childPid2 = fork() ) == 0 )
        {
            // child 2
            printf( "second clause %d\n", childPid2 );
            system( "./ttt.abc" );
            //RBUDP_send();
        }
        else
        {
            // parent
            usleep( 100000 );

            FILE *fp;
            int status;
            char path[1035];

            /* Open the command for reading. */
            fp = popen( "pgrep ttt.abc", "r" );
            if( fp == NULL)
            {
                printf("Failed to run command\n" );
                return 0;
            }

            int core = 0;

            /* Read the output a line at a time - output it. */
            while( fgets( path, sizeof( path ) - 1, fp ) != NULL )
            {
                char cmd[40];

                // convert pid
                int pid = atoi( path );
                //sprintf( cmd, "taskset -c %d %d", core, pid );
                //system( cmd );

                // move on to next core
                core++;
                printf( "pid %d\n", pid );
                //printf("--- %s", path);
                if( core == 2 )
                {
                    printf( " core = 2 \n" );
                    break;
                }
            }

            // close
            pclose(fp);

            printf( "pid = %d, childPid1 = %d, childPid2 = %d \n", getpid(), childPid1, childPid2 );
        }
    }

    while( 1 );
    return 0;
}
