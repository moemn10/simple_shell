#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int user = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (user)
			: "r" (user));

	if (ac == 2)
	{
		user = open(av[1], O_RDONLY);
		if (user == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_erputs(av[0]);
				_erputs(": 0: Can't open ");
				_erputs(av[1]);
				_erputchar('\n');
				_erputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = user;
	}
	pop_env_list(info);
	reading_history(info);
	mkw(info, av);
	return (EXIT_SUCCESS);
}
