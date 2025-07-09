#include "minishell.h"

t_shell_state g_shell = {
	.exit_status = 0,
	.sigint_received = 0,
	.in_heredoc = 0,
	.is_interactive = 0
};

void	init_shell_terminal_control(void)
{
	pid_t shell_pgid;

	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	shell_pgid = getpid();
	if (setpgid(shell_pgid, shell_pgid) < 0)
		perror("setpgid");

	if (tcsetpgrp(STDIN_FILENO, shell_pgid) < 0)
		perror("tcsetpgrp");
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lst_cmd	*cmds;
	t_cmd		*cmd;
	t_env		*envir;
	char		**env_char;

	(void)argc;
	(void)argv;

	g_shell.is_interactive = isatty(STDIN_FILENO);
	if (g_shell.is_interactive)
		handle_signals();
	envir = get_env(envp);
	while (1)
	{
		if (g_shell.is_interactive)
			input = readline("\001\033[1;34m\002minishell:$ \001\033[0m\002");
		else
			input = get_next_line(STDIN_FILENO);

		if (!input)
		{
			if (g_shell.is_interactive)
				write(1, "exit\n", 5);
			break;
		}

		if (*input == '\0')
		{
			free(input);
			continue;
		}

		if (g_shell.is_interactive)
			add_history(input);

		cmds = parsing(input, envir, &g_shell.exit_status);
		free(input);
		if (!cmds || !cmds->head)
			continue;

		cmd = cmds->head;
		env_char = env_tochar(envir);

		while (cmd)
		{
			cmd->env = &envir;
			cmd->envp = env_char;
			cmd = cmd->next;
		}
		cmd = cmds->head;

		if (cmd && cmd->next == NULL && is_builtin(cmd->args[0]))
			g_shell.exit_status = execute_builtin(cmd);
		else
			execute_pipeline(cmd);
		free_all(cmds->k);
		free_array(env_char);
	}
	return (g_shell.exit_status);
}
