/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
=======
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
