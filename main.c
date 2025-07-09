
#include "minishell.h"

t_shell_state g_shell = {
	.exit_status = 0,
	.sigint_received = 0,
	.in_heredoc = 0
};

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lst_cmd	*cmds;
	t_env		*envir;
	t_cmd		*cmd;

	(void)argc;
	(void)argv;
	envir = get_env(envp);
	while (1)
	{
		handle_signals();
		input = readline("\001\033[1;34m\002minishell:$ \001\033[0m\002");
		if (!input)
		{
			write(1, "exit\n", ft_strlen("exit\n"));
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		cmds = parsing(input, envir, &g_shell.exit_status);
		if (!cmds || !cmds->head)
		{
			free(input);
			continue ;
		}
		cmd = cmds->head;
		char **env_char = env_tochar(envir);
		while (cmd)
		{
			cmd->env = &envir;
			cmd->envp = env_char;
			cmd->exit_status = &g_shell.exit_status;
			cmd = cmd->next;
		}
		cmd = cmds->head;
		if (cmd && cmd->next == NULL && is_builtin(cmd->args[0]))
			g_shell.exit_status = execute_builtin(cmd);
		else
			execute_pipeline(cmd);
		free_all(cmds->k);
		free(input);
	}
	return (g_shell.exit_status);
}
