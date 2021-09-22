#define N 1000000
#define a 10
#define b 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
int main(int argc, char** argv)
{
int myid,numprocs;
int i;
double local=0.0, dx=(double)(b-a)/N;
double inte, x;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
MPI_Comm_size(MPI_COMM_WORLD,&numprocs);--numprocs;
if (myid== 0){
clock_t start,end;
start = clock();
for (int i = 0; i < N; ++i )
{ x = a+i*dx+dx/2;
MPI_Send(&x, 1, MPI_DOUBLE, i%numprocs+1, 1 ,MPI_COMM_WORLD);}
for (int source = 1; source <= numprocs; ++source)
{ MPI_Recv(&local, 1, MPI_DOUBLE, source, 99, MPI_COMM_WORLD, &status);inte += local ; }
end = clock();
printf("time=%f\n",(double)(end-start)/CLOCKS_PER_SEC);
}else
{ for (i = myid-1; i < N; i=i+numprocs)
{ MPI_Recv(&local, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status); inte+= local*local*local*dx; }
MPI_Send(&inte, 1, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
}
printf("I am process %d. My part of inte=%f.\n", myid, inte);
MPI_Finalize();
}