#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<assert.h>
#include<time.h>
#include<string.h>


int main(int argc, char **argv)
{
	
	int iflag = 0;
	int oflag = 0;
	char *inputFile = NULL;
	char *outputFile = NULL;
	FILE *fdIn;
	FILE *fdOut;
	int c;
	char *line = NULL;
	size_t len = 0;
	opterr = 0;

	//Get the input parameters to the main function
	//getting the names of the input and output files
	while ((c = getopt (argc, argv, "i:o")) != -1)
	{	
		switch (c)
		{
			case 'i':
			iflag = 1;
				//printf("Input file : %s\n", argv[ optind-1]);
			inputFile = argv[optind-1];

			break;

			case 'o':
			oflag = 1;
				//printf("Output file : %s\n", argv[optind]);
			outputFile = argv[optind];

			break;

			case '?':

			fprintf (stderr,"Unknown option character : %c\n",optopt);
			return 1;
			default:
			abort ();
		}
	}
	//Checking if all the paramters are correct
	//Checking if both input and output files are present
	if(iflag == 0 || oflag == 0)
	{
		fprintf(stderr, "Missing files!!!\n" );
		return 1;
	}
	fdIn = fopen(inputFile,"r");
	assert(fdIn != NULL);
	fdOut = fopen(outputFile,"w");
	assert(fdOut != NULL);

	//Initialize a year array containing NULL values
	int yearDates[365] = {0};

	//Seed the randomizer
	srand(time(NULL));

	//read data from the input file
	while((getline(&line,&len,fdIn))!= -1)
	{
		int counter = 0;
		int num = atoi(line);
		float prob = 0;
		int hits = 0;
		
		//Initiating the 1000 trials
		for(int x = 0; x<1000; x++)
		{
			//Clearing the yearDates array
			memset((void*)yearDates,0x00,sizeof(int)*365);
			/*for(int i = 0 ; i < 365 ; i++)
			{
				yearDates[i] = 0;
			}*/
			for(counter = 0 ; counter < num ; counter++)
			{
				
				if(yearDates[(rand()%365)] == 1)
				{
					hits++;
					break;
				}
				else
				{
					yearDates[(rand()%365)] = 1;
				}
			}
			
		}
		//Probabity Calculation
		//printf("%d\n", hits);
		prob = (float)hits/1000;
		hits = 0;
		printf("%f\n", prob);
		fprintf(fdOut, "%.2f\n",prob);
	}




	fclose(fdIn);
	fclose(fdOut);

	return 0;
}













