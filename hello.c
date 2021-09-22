#include <stdio.h>
#include <mpi.h>
#include <math.h>
int main(int argc, char** argv)
{
int myid, numprocs;
int n = atoi(argv[1]);
double data[11]={1,2,3,4,5,6,7,8,9,10,11}, local = 0.0, res, SqrtSum=0.0;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
for (int i = myid; i < n; i=i+numprocs)
local += sqrt(data[i]);
MPI_Reduce(&local,&res,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
if (myid== 0){
printf("The SqrtSum is %f.\n", res);}
MPI_Finalize();
}