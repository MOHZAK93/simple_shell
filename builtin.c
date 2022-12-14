#include "header.h"

/**
* b_exit - exit function buitlin
* @av: Array of command arguments.
* @l_ret: Pointer to number of the last return
*/

void b_exit(char **av, int *l_ret)
{
	char *line = av[0];
	unsigned int ac = 0, bn = 1;/*Boolean to identify if is a number*/
	int n_return = 0, i;/*Runner*/

	for (; av[ac]; ac++)
		;

	if (ac >= 2)
	{
		for (i = 0; (bn == 1) && (av[1][i] != '\0'); i++)
			if (av[1][i] < '0' || av[1][i] > '9')
				bn = 0;
		if (bn == 1)
			n_return = _atoi(av[1]);
		else
		{
			*l_ret = 2;
			n_return = prt_error(av, 2);/*Pending Handle error*/
		}
	}
	else if (ac == 1)
		n_return = *l_ret;

	free(av);
	free(line);
	exit(n_return);
}

/**
 * b_env - Print the enviroment variables
 * @av: Array of arguments
 * @l_ret: Pointer to number of the last return
 */
void b_env(char **av, int *l_ret)
{
	unsigned int ac = 0, i;/*Runer*/

	for (; av[ac]; ac++)
		;

	if (ac != 1 || !environ)
		*l_ret = 2; /*Pending- handle error*/
	else
	{
		i = 0;
		while (environ[i] != NULL)
		{
			prt_stdo(environ[i]);
			prt_stdo("\n");
			i++;
		}
		*l_ret = 0;
	}
}
