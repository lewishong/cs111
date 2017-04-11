#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

int errno;
int seg_flag = 0;

void signal_handler(int num)
{
	if (num == SIGSEGV)
	{
		fprintf(stderr, "Segmentation fault. Error: %s.\n", strerror(errno));
		exit(4);
	}
}

int main (int argc, char* argv[]) 
{
	int c = -1;
	int ifd = 0;
	int ofd = 1;
	char* n = NULL;

	static struct option long_options[] = 
	{
		{"input", required_argument, 0, 'i'},
		{"output", required_argument, 0, 'o'},
		{"segfault", no_argument, 0, 's'},
		{"catch", no_argument, 0, 'c'},
		{0, 0, 0, 0}
	};
	
	int option_index = 0;

	while ((c = getopt_long(argc, argv, "csi:o:", long_options, &option_index)) != -1)
	{	
		switch (c)
		{
			case 'i':
				ifd = open(optarg, O_RDONLY);
				if (ifd >= 0)
				{
					close(0);
					dup(ifd);
					close(ifd);
				}	
				else
				{
					fprintf(stderr, "Error with specified input file.");
					exit(2);
				}
				break;
			
			case 'o':
				ofd = creat(optarg, 0666);
				if (ofd >= 0)
				{
					close(1);
					dup(ofd);
					close(ofd);
				}
				else 
				{
					fprintf(stderr, "Error with specified output file.");
					exit(3);
				}
				break;
			
			case 's':
				seg_flag = 1;
				break;
				
			case 'c':
				signal(SIGSEGV, signal_handler);
				break;	
			
			default:
				fprintf(stderr, "Usage: lab0 [--segfault --catch] --input file1 --output file2\n");
				exit(1);	// RIGHT ERROR???
				break;
		}
	}
	
	if (seg_flag)
	{
		char e = *n;	// try to dereference nullptr
	}

	char buff[2048];
	int rsize;
	int wsize;

	while ((rsize = read(0, buff, 2048)) > 0)
    	{
      		wsize = write(1, buff, rsize);
    		if (rsize != wsize)
		{
			fprintf(stderr, "Unable to write to output file.\n");
			exit(3);
		}
	}
					
	exit(0);
}

