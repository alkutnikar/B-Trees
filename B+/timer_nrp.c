// Tweaked from James Rochkind's description in the book
// "Advanced unix programming".
#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>

//#define DEBUG
//#define SELF_TEST

static struct tms tbuf1;
static clock_t real1;
static long clock_ticks;

void timeStart(void)
{
     real1 = times(&tbuf1);
     clock_ticks = sysconf(_SC_CLK_TCK);
     return;
}

double timeStop(char *msg)
{
     struct tms tbuf2;
     clock_t real2;

     real2 = times(&tbuf2);
     
	 double user = ((double)(tbuf2.tms_utime ) - (tbuf1.tms_utime )) / clock_ticks;
	 double system = ((double)(tbuf2.tms_stime ) - (tbuf1.tms_stime )) / clock_ticks;
#ifdef DEBUG
	 double real = (double)(real2 - real1) / clock_ticks;
#endif
	 double userPlusSys = user+system;

#ifdef DEBUG 
	 // This printing is just for self verification.
     printf("%s : Total %.2f (user/sys/real), %.2f , %.2f , %.2f \n", msg,userPlusSys, user, system, real);
#endif
     return userPlusSys;
}

#ifdef SELF_TEST

#define REPS 100000000
main()
{
	double dt;
	long unsigned i;
	timeStart();
	for (i=0; i<= REPS; i++)
	{
		(void)getpid();
	}
	dt = timeStop("pid");
	// do anything with dt
}
#endif
