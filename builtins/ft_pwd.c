#include "../exec.h"

int ft_pwd(void)
{
	char *abs_path;

	abs_path = getcwd(NULL, 0);
	if (!abs_path)
	{
		ft_printf(STDERR_FILENO, "pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_printf(STDOUT_FILENO, "%s\n", abs_path);
	free(abs_path);
	return (0);
}
