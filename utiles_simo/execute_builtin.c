#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "unset") == 0
	);
}

int apply_redirections(t_redir *redir_list, int *saved_stdout)
{
	t_redir *tmp;
	
	tmp = redir_list;
	while (tmp)
	{
		if (tmp->index == R_OUT)
			tmp->fd = open_file(tmp, R_OUT);
		else if (tmp->index == R_APPEND)
			tmp->fd = open_file(tmp, R_APPEND);
		if (tmp->fd < 0)
			return (perror("open"), -1);
		*saved_stdout = dup(STDOUT_FILENO);
		if (*saved_stdout < 0 || dup2(tmp->fd, STDOUT_FILENO) < 0)
			return (perror("dup/dup2"), -1);
		tmp = tmp->next;
	}
	return (0);
}

void restore_redirections(int saved_stdout)
{
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	execute_builtin(t_cmd *cmd)
{
	int status;
	int saved_stdout;

	saved_stdout = -1;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (apply_redirections(cmd->files, &saved_stdout) < 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		status = ft_env(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = ft_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		status = ft_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = ft_export(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = ft_unset(cmd);
	else
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0 || ft_strcmp(cmd->args[0], "unset") == 0)
	{
		if (cmd->envp)
			free_array(cmd->envp);
		cmd->envp = env_tochar(*(cmd->env));
	}
	restore_redirections(saved_stdout);
	return (status);
}
