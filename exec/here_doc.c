/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:43 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/11 18:50:36 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_word(const char *src, int size)
{
	char *word = malloc(size + 1);
	if (!word)
		return NULL;
	strncpy(word, src, size);
	word[size] = '\0';
	return word;
}

static char *find_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return env->value;
		env = env->next;
	}
	return NULL;
}

char *expand_line(const char *line, t_env *env)
{
    char *line_ex = ft_strdup("");
		int i = 0;
		char *status;
		char *tmp;
		int key_len;
		char *key;
		char *value;
		int w_len;
		char *word;
		
		while (line[i])
		{
			if (line[i] == '$')
			{
				i++;
				if (line[i] == '?')
				{
					status = ft_itoa(g_shell.exit_status);
					tmp = ft_strjoin(line_ex, status);
					free(line_ex);
					line_ex = tmp;
					free(status);
					i++;
				}
				else if (isalpha(line[i]) || line[i] == '_')
				{
					key_len = 0;
					while (isalnum(line[i + key_len]) || line[i + key_len] == '_')
						key_len++;
					key = get_word(line + i, key_len);
					value = find_env_value(env, key);
					tmp = ft_strjoin(line_ex, value ? value : "");
					free(line_ex);
					line_ex = tmp;
					free(key);
					i += key_len;
				}
				else
				{
					tmp = ft_strjoin(line_ex, "$");
					free(line_ex);
					line_ex = tmp;
				}
			}
			else
			{
				w_len = 0;
				while (line[i + w_len] && line[i + w_len] != '$')
					w_len++;
				word = get_word(line + i, w_len);
				tmp = ft_strjoin(line_ex, word);
				free(line_ex);
				line_ex = tmp;
				free(word);
				i += w_len;
			}
		}
    return line_ex;
}

static void	write_to_pipe_from_redir(t_redir *redir, int pipe_fd[2] , t_env *env)
{
	char	*line;
	int		count = 1;

	close(pipe_fd[0]);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		
		if(!redir->deja_quoted)
			line = expand_line(line, env);
		if (!line)
		{
			ft_printf(2 , "minishell: warning: here-document delimited at line %d by end-of-file (wanted `%s')\n",
				count, redir->files);
			break ;
		}
		if (ft_strncmp(line, redir->files, ft_strlen(redir->files)) == 0
			&& line[ft_strlen(redir->files)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		count++;
	}
	close(pipe_fd[1]);
}

int	handle_heredoc(t_redir *redir , t_env *env)
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
		write_to_pipe_from_redir(redir, pipe_fd , env);
		exit(EXIT_SUCCESS);
	}

	close(pipe_fd[1]);
	waitpid(id, &status, 0);
	g_shell.in_heredoc = 0;
	handle_signals();

	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		redir->fd = -1;
		g_shell.exit_status = 130;
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

int	handle_all_heredocs(t_cmd *cmd)
{
	t_cmd	*tmp = cmd;
	t_redir	*redir;

	while (tmp)
	{
		redir = tmp->files;
		while (redir)
		{
			if (redir->index == R_HEREDOC)
			{
				if (handle_heredoc(redir , *cmd->env) != 0)
					return (1);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
