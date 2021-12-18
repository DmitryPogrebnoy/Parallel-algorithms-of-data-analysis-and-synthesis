#include <iostream>
#include "mpi.h"

using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message, previousMessage;
	previousMessage = 1000;
	bool isDescending = true;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		cout << "Hello from main process " << rank << "\n";
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (message > previousMessage) {
				isDescending = false;
			} 
			previousMessage = message;
			cout << "Message - " << message << " (process number)" << endl;
		}
		if (isDescending) {
			cout << "Messages in descending order" << endl;
		} else {
			cout << "Messages are not in descending order" << endl;
		}
	}
	else MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}