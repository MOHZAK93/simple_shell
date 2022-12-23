#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

/**
  *main - Entry point
  *
  *Return: 0
  */

int main(void)
{
	char *lineptr = NULL;
	size_t n  = 0;
	char *argv[] = {"/bin/ls", "-l", NULL};

	while (1)
	{

		printf("#cisfun$ ");
		getline(&lineptr, &n, stdin);

		if (execve(argv[0], argv, NULL) == -1)
		{
			printf("%s", lineptr);
			perror("./sehll");
		}
	}

	return (0);
}
