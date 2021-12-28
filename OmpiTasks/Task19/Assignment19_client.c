#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	// Get port_name from argv
	strcpy(port_name, argv[1]);
	// Connect to server using port_name
	printf("Attemp to connect\n");
	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("Client connected\n");
	// Send message to server
	int message = 42;
	MPI_Send(&message, 1, MPI_INT, 0, 0, intercomm);
	printf("Client sent value: %d\n", message);
	// Receive message from server
	int recv_message;
	MPI_Recv(&recv_message, 1, MPI_INT, 0, 0, intercomm, &status); 
	printf("Client got value: %d\n", recv_message);
	MPI_Finalize();
	return 0;
}