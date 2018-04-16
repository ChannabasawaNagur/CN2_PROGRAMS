#include<stdio.h>	
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define maxsize 1000
char buffer[1000];
void client( int readfd, int writefd )
{
	printf("\nGive pathname: ");
	fflush(stdout);
	fgets(buffer, sizeof(buffer), stdin);
	printf("\nServer Online\nProcessing request...\n\n");
	write(writefd, buffer, sizeof( buffer ) );
	while( read( readfd, buffer, sizeof( buffer ) ) > 0 )
		printf( "%s", buffer);
}
void server( int readfd, int writefd )
{
	FILE * fp;
	char line[1000];
	read( readfd, buffer, sizeof( buffer ) );
	if( strchr( buffer, '\n' ) )
		*strchr( buffer, '\n' ) = 0;
	fp = fopen( buffer, "r" );
	if( fp == NULL )
	{
		strcpy( buffer, "cannot open file" );
		write( writefd, buffer, strlen( buffer ) );
		exit(1);
	}
	else
	{
		while( fgets( line, sizeof( line ), fp ) != NULL )
			write( writefd, line, sizeof( line ) );
		printf("\nSERVER: Transfer completed\n");
	}
}

int main()
{
	int pipe1[2], pipe2[2];
	int childpid;
	int status;
	pipe( pipe1 );
	pipe( pipe2 );
	printf("\nClient Online\n");
	childpid = fork();
	if( childpid > 0 )
	{
		close( pipe1[0] );
		close( pipe2[1] );
		client( pipe2[0], pipe1[1] );
		wait( &status );
		exit(0);
	}
	else
	{
		close( pipe1[1] );
		close( pipe2[0] );
		server( pipe1[0], pipe2[1] );
		exit(0);
	}
}
