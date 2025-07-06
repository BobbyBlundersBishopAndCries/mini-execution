#include "../minishell.h"

static char	**return_path(t_env *env)
{
	char	*path_value;
	char	**path;
	
	path_value = get_value(env, "PATH");
	if (!path_value)
		return (NULL);
	path = ft_split(path_value, ':');
	if (!path)
		return(NULL);
	return (path);
}

static char	*path_found(t_env *env, char *cmd)
{
	char	**path;
	char	*full_path;
	int		i;

	path = return_path(env);
	if (NULL == path)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		full_path = strjoin_val_path(path[i], cmd, 1);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(path);
	return (NULL);
}

void	execute_command(t_cmd *cmd)
{
	char	*p;
	
	if (!cmd || !cmd->env || !(*cmd->env))
		return ;
	if (cmd->args[0][0] == '/')
		p = ft_strdup(cmd->args[0]);
	else if(cmd->args[0][0] == '.')
		p = strjoin_val_path(get_value(*(cmd->env), "PWD"), cmd->args[0], 1);
	else if(cmd->args[0][0] == '~')
		p = strjoin_val_path(get_value(*(cmd->env), "HOME"), cmd->args[0] + 1, 1);
	else
		p = path_found(*(cmd->env), cmd->args[0]);
	if (p == NULL)
	{
		perror("command not found ");
		exit(127);
	}
	execve(p, cmd->args, cmd->envp);
	perror("execve error");
	exit(EXIT_FAILURE);
}
