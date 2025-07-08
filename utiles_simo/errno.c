#include "../minishell.h"

int	exec_error_status(int err)
{
	if (err == EACCES || err == EISDIR || err == ENOEXEC || err == ETXTBSY)
		return (126);
	if (err == ENOENT || err == ENOTDIR)
		return (127);
	return (1);
}