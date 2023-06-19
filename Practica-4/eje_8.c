#include <mpi.h>
#include <stdio.h>


int main(int argc, char **argv) {
  int num_procs, my_id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &my_id);
    printf("Hello world! i'm process %i out of %i processes\n", my_id, num_procs);
    MPI_Finalize();
    return 0;
}
