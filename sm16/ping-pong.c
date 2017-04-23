/*********  pre-header comment ***********
Exercise #3 is  based on our MPI timing discussion.

I feel the matrix vector product topic is not ready for prime time.
So instead I would like you to make this week's exercise an experiment in timing
MPI programs.  Please check the following program so you are sure what it does
and decide if it makes sense to you.  (If you find something senseless, make changes.)
Run it on at least three environments such as:
  porsche + nodes
  porsche + one node
  nsfri cluster (3 nodes or 1 node)
  stimpy
  stimpy + one or two other suns.
  A single machine

Make a record of the three key results for each trial run.
Calculate the ratio of T_s to T_w  and T_w to T_ma,
where T_s is the per message time,
      T_w is the per byte communicated time, and
      T_ma is the time for a multiply add step.

Also, add a print statement to print the time of one tick of the MPI clock.
How does the tick time vary from machine to machine?

Optionally, figure out how to get each procedure to print the name of it's host
machine (node).  Hint: there is an MPI call for this.

Hand in a one page note reporting the T_s, T_w, T_ma, the approximate ratios, and
the tick time for each machine(s) you try.  Comment on any thing unusual you notice.
For instance, anything to be said about the sequencing of the output lines?
Hand in code only if you make substantial modifications.  That's it.  This is not
supposed to be a hard one.

Due in class Feb 27.
*********************************************/

/* ping-pong.c -- for timing basic send/recv -- bds 2003/2
 *
 * Input: command line arg n - indicates how many ping-pong's of messages to measure.
 * Input: internal constant size - determines how much data is sent.
 * Output:  
 *    1. timing of arithmetic: multiply-adds in a loop of "size" repetitions.
 *    2. timing of per message cost: n two way send/receive's of one int.
 *    3. timing of per byte transmission cost: n two way send/receive's of "size" ints.
 *
 * Algorithm:
 *    ping - pong between processes 1 and 2.  
 *    Process 0 is idle.  This allows full control of the locations of
 *    the active processes by use of machinefiles.
 *
 * Note:
 *    Not all parallel machines allow all processors to perform I/O.
 *    This code has all procs doing I/O  
 */
#include <stdio.h>
#include "mpi.h"

main(int argc, char** argv) {
    int         R;   /* My process rank           */
    int         P;   /* The number of processes   */
    int         ping = 1;  /* server process of ping-pong */
    int         pong = 2;  /* defender process of ping-pong */
    int         tag = 0;
    int         n = 0;   /* number of ping-pong's back and forth */
    const int size = 250000; /* length of message */
    int         k[size];   /* message content */
    int         i;
    float       x = 0;  /* for the multiply-add loop */
    char       *s;
    MPI_Status  status;
    MPI_Comm    World = MPI_COMM_WORLD;
    double      start_time, elapsed_time; /* for time measurement */

    if (argc < 6) 
    {	printf("Usage: %s n [where n is number of ping-pong steps ]\n", argv[0]);
	return 0;
    }

    /* Let the system do what it needs to start up MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(World, &P); // number of procs
    if (P < 3) { printf("this requires 3 processes\n"); return 0; }
    MPI_Comm_rank(MPI_COMM_WORLD, &R); // my rank in [0..P).
    if (R == 0) printf( "%d %d %s\n", n, argc, argv[0]);

    //n = atoi(argv[1]);  // for some reason, trouble finding atoi().
    for (s = argv[1]; *s > 0; ++s) n = 10*n + (*s - '0');
    printf("n is %d\n ", n);
    
    // measure an arithmetic time
    MPI_Barrier(World);
    if (R == ping)
    {   start_time = MPI_Wtime();
        for(i = 0; i < size; ++i) x += i*i;
	elapsed_time = MPI_Wtime() - start_time;
        printf("%d multiply-adds in %g seconds, ", n, elapsed_time);
	printf(" for an average time of %g\n", elapsed_time/size);
    }

    // measure per send communication time
    MPI_Barrier(World);
    if (R == ping) /* Note:  it is not always valid that process one can output */
    {   start_time = MPI_Wtime();
	for (i = 0; i < n; ++i)
	{   k[0] = i;
	    MPI_Send(k, 1, MPI_INT, pong, tag, World);
	    MPI_Recv(k, 1, MPI_INT, pong, tag, World, &status);
	    if (k[0] != i+1) printf("invalid pong received\n");
	}
	elapsed_time = MPI_Wtime() - start_time;
        printf("%d ping-pongs in %g seconds, ", n, elapsed_time);
	printf(" for an average message time of %g\n", elapsed_time/(2*n));
    }

    if (R == pong) 
	for (i = 0; i < n; ++i)
	{   MPI_Recv(k, 1, MPI_INT, ping, tag, World, &status);
	    if (k[0] != i) printf("invalid ping received\n");
	    k[0]  += 1;
	    MPI_Send(k, 1, MPI_INT, ping, tag, World);
	}

    // measure per byte moved communication time
    MPI_Barrier(World);
    if (R == ping) /* Note:  it is not always valid that process one can output */
    {   start_time = MPI_Wtime();
	for (i = 0; i < n; ++i)
	{   k[0] = i;
	    MPI_Send(k, size, MPI_INT, pong, tag, World);
	    MPI_Recv(k, size, MPI_INT, pong, tag, World, &status);
	    if (k[0] != i+1) printf("invalid pong received\n");
	}
	elapsed_time = MPI_Wtime() - start_time;
        printf("%d ping-pongs in %g seconds, ", n, elapsed_time);
	printf(" for an average message time of %g\n", elapsed_time/(2*n*size));
    }

    if (R == pong) 
	for (i = 0; i < n; ++i)
	{   MPI_Recv(k, size, MPI_INT, ping, tag, World, &status);
	    if (k[0] != i) printf("invalid ping received\n");
	    k[0]  += 1;
	    MPI_Send(k, size, MPI_INT, ping, tag, World);
	}

    /* Shut down MPI */
    MPI_Finalize();
} /*  main  */

