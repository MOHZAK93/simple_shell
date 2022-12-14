#include "header.h"

/**
 * exc_ext - Execute a command indicate in a string.
 * @av: Array of command arguments
 * Return: 0 if succes or -1 if fork fail.
 */
int exc_ext(char **av)
{
	char *path = NULL, *line = NULL;/*Complet command*/
	pid_t child_pid;
	int status, n_return = 0;

	if (av)
		path = _getpath(av);
	/*Verify acces to command*/
	if (!path || !av || (access(path, F_OK) == -1))
	{
		if (errno == EACCES)
			return (prt_error(av, 126));
		else
			return (prt_error(av, 127));
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error child:");
		return (1);
	}
	if (child_pid == 0)
	{
		execve(path, av, environ);
		if (errno == EACCES)
			n_return = prt_error(av, 126);
		line = av[0];
		free(path);
		free(av);
		free(line);
		_exit(n_return);
	}
	else
	{
		wait(&status);
		n_return = WEXITSTATUS(status);
	}
	free(path);
	return (n_return);
}

/**
 * main - Super simple shell.
 * @argc: Numbers of arguments.
 * @argv: Array of shell arguments.
 * Return: 0 in succes.
 */
int main(int argc, char **argv)
{
	char *line = NULL, **av = NULL;
	size_t len = 0;
	int n_chars = 0, n_return = 0, c_spaces = 0, i = 0;
	FILE *fp = stdin;

	ex_name = argv[0];
	hist = 0;

	while (argc)
	{
		/*If is interactive mode*/
		if (isatty(STDIN_FILENO) && fp == stdin)
			prt_stdo("#cisfun$ ");
		n_chars = getline(&line, &len, fp);
		for (c_spaces = 0, i = 0; n_chars != -1 && line[i] != '\0'; i++)
		{
			if (line[i] == ' ')
				c_spaces++;
		}
		hist++;
		if (n_chars == -1)
		{
			if (isatty(STDIN_FILENO) && fp == stdin)
				prt_stdo("\n");
			break;
		}
		else if (*line != '\n' && !(c_spaces >= n_chars - 1))
		{
			if (line[n_chars - 1] == '\n')
				line[n_chars - 1] = '\0';
			av = get_array(line);
			n_return = execute(av, &n_return);
			free(av);
			free(line);
			av = NULL;
			line = NULL;
		}
	}
	free(line);
	return (n_return);
}
