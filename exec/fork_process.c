#include "../minishell.h"

void	error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

static void	exec_or_builtin(t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
	{
		*(cmd->exit_status) = execute_builtin(cmd);
		exit(*(cmd->exit_status));
	}
	execute_command(cmd);
	exit(EXIT_FAILURE);
}

static void	setup_pipe_and_fork(t_cmd *cmd, int prev_fd[2])
{
	int		next_fd[2];
	pid_t	pid;

	if (cmd->next && pipe(next_fd) == -1)
		error();

	pid = fork();
	if (pid < 0)
		error();

	if (pid == 0)
	{
		handle_signals();
		if (prev_fd[0] != -1)
		{
			dup2(prev_fd[0], STDIN_FILENO);
			close(prev_fd[0]);
		}
		// STDOUT to next pipe
		if (cmd->next)
		{
			close(next_fd[0]);
			dup2(next_fd[1], STDOUT_FILENO);
			close(next_fd[1]);
		}
		// Redirections (now HEREDOC fd is already set)
		if (setup_redirections(cmd->files))
			exit(EXIT_FAILURE);
		close_redirs(cmd->files);
		exec_or_builtin(cmd);
	}

	// Parent cleanup
	if (prev_fd[0] != -1)
		close(prev_fd[0]);
	if (cmd->next)
	{
		prev_fd[0] = next_fd[0];
		close(next_fd[1]);
	}
	else
		prev_fd[0] = -1;
}

void	execute_pipeline(t_cmd *cmd)
{
	int		prev_fd[2] = {-1, -1};
	int		status;
	t_cmd	*tmp = cmd;

	if (handle_all_heredocs(cmd))
		return;

	while (tmp)
	{
		setup_pipe_and_fork(tmp, prev_fd);
		tmp = tmp->next;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*(cmd->exit_status) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
    		*(cmd->exit_status) = 128 + WTERMSIG(status);
	}
}
