#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int main (int argc, char *argv[], char *envp[])
{
	int delay;
	int length = 5;
	int i;
	int trash;
	int dist;
	int lResponse;
	char string[64];
	char response[64];
	char next;
	long long quadPart;
	struct timeval tvStart;
	struct timeval tvEnd;
	struct timeval tvDiff;
	struct timezone tz;
	FILE *outfile = stdout;

	gettimeofday(&tvStart, &tz);
	srand((unsigned int)tvStart.tv_usec);
	delay = rand() % 4;
	sleep(delay);
	for (i=1;i<argc;i++)
	{
		if (!strcmp(argv[i],"-l") && i<argc-1)
		{
			i += 1;
			length = atoi(argv[i]);
			if (length > 64)
			{
				length = 64;
			}
		}
		if (!strcmp(argv[i],"-f") && i<argc-1)
		{
			i += 1;
			outfile = fopen(argv[i], "a");
			if (outfile == NULL)
			{
				outfile = stdout;
			}
		}
	}

	for (i=0;i<length;i++)
	{
		trash = rand() % 26;
		next = 'a' + (char)trash;
		string[i] = next;
	}
	string[i] = '\000';
	fprintf(stderr,"\n%s - Repeat!\n", string);
	gettimeofday(&tvStart, &tz);
	scanf("%s", response);
	gettimeofday(&tvEnd, &tz);
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	lResponse = strlen(response);
	dist = distance(string, length, response, lResponse);
	fprintf(outfile, ",%d,%d,%d,%ld.%.6ld\n", delay, length, dist,
		tvDiff.tv_sec, tvDiff.tv_usec);
	if (outfile != stdout)
	{
		int t = tvDiff.tv_sec;
		if (tvDiff.tv_usec > 600000)
		{
			t += 1;
		}
		printf ("%d errors, %d seconds\n", dist, t);
	}

	return dist;
}

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_usec < y->tv_usec)
	{
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000)
	{
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}
	/* Compute the time remaining to wait.  tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;
	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}

int distance (const char * word1, int len1, const char * word2, int len2)
{
	int matrix[len1 + 1][len2 + 1];
	int i;
	for (i = 0; i <= len1; i++)
	{
		matrix[i][0] = i;
	}
	for (i = 0; i <= len2; i++)
	{
		matrix[0][i] = i;
	}
	for (i = 1; i <= len1; i++)
	{
		int j;
		char c1;

		c1 = word1[i-1];
		for (j = 1; j <= len2; j++)
		{
			char c2;

			c2 = word2[j-1];
			if (c1 == c2)
			{
				matrix[i][j] = matrix[i-1][j-1];
			}
			else
			{
				int delete;
				int insert;
				int substitute;
				int minimum;

				delete = matrix[i-1][j] + 1;
				insert = matrix[i][j-1] + 1;
				substitute = matrix[i-1][j-1] + 1;
				minimum = delete;
				if (insert < minimum)
				{
					minimum = insert;
				}
				if (substitute < minimum)
				{
					minimum = substitute;
				}
				matrix[i][j] = minimum;
			}
		}
	}
	return matrix[len1][len2];
}

