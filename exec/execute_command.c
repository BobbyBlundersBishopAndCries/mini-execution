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

int is_directory(const char *path)
{
    struct stat st;

    if (stat(path, &st) == -1)
        return 0;
    return S_ISDIR(st.st_mode);
}

void	execute_command(t_cmd *cmd)
{
	char	*p;
	char	*to_befreed;

	if (!cmd || !(cmd->args) || !(cmd->args[0]) || !cmd->args[0][0])
		return ;
	if (is_directory(cmd->args[0]))
    {
        ft_printf(2, "minishell: %s: Is a directory\n", cmd->args[0]);
        exit(126);
	}
	if (!cmd || !cmd->env || !(*cmd->env))
		return ;
	if (cmd->args[0][0] == '/')
		p = ft_strdup(cmd->args[0]);
	else if(cmd->args[0][0] == '.')
	{
		to_befreed = getcwd(NULL,0);	
		p = strjoin_val_path(to_befreed, cmd->args[0], 1);
		free(to_befreed);
	}
	else if(cmd->args[0][0] == '~')
		p = strjoin_val_path(get_value(*(cmd->env), "HOME"), cmd->args[0] + 1, 1);
	else
		p = path_found(*(cmd->env), cmd->args[0]);
	if (p == NULL)
	{
		ft_printf(2, "minishell:  %s: command not found\n", cmd->args[0]);
		*(cmd->exit_status) = 127;
		exit(127);
	}
	if (cmd->args == NULL || cmd->args[0] == NULL || cmd->args[0][0] == '\0')
    	return;
	execve(p, cmd->args, cmd->envp);
	perror("execve error");
	exit(EXIT_FAILURE);
}
