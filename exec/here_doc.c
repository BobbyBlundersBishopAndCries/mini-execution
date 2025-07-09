/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:43 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/09 15:02:48 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_to_pipe_from_redir(t_redir *redir, int pipe_fd[2])
{
	char *line;

	close(pipe_fd[0]);  // Close read end; child writes
	while (1)
	{
		write(1, "> ", 2);  // heredoc prompt
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, redir->files, ft_strlen(redir->files)) == 0 &&
			line[ft_strlen(redir->files)] == '\n')
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
}

int	handle_heredoc(t_redir *redir)
{
	pid_t	id;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
		return (1); 
	g_shell.in_heredoc = 1;
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
	{
		restore_signals_to_default();
		write_to_pipe_from_redir(redir, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
   		close(pipe_fd[1]);
   		waitpid(id, &status, 0);
	    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    	{
       		redir->fd = -1;
        	g_shell.exit_status = 130;
       		g_shell.in_heredoc = 0;   
        	return (1);                 
    	}
    	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    	{
        	close(pipe_fd[0]);
       		redir->fd = -1;
       		g_shell.exit_status = WEXITSTATUS(status);
        	return (1);
    	}
    redir->fd = pipe_fd[0];
    return (0);
}
}

int	handle_all_heredocs(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	t_redir *redir;

	while (tmp)
	{
		redir = tmp->files;
		while (redir)
		{
			if (redir->index == R_HEREDOC)
			{
				if (handle_heredoc(redir) != 0)
					return (1);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
