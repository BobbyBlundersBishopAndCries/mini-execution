
#include "minishell.h"

int	g_exit_status = 0;

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
		input = readline("\001\033[1;31m\002minishell:$ \001\033[0m\002");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		cmds = parsing(input, envir, &g_exit_status);
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
			cmd->exit_status = &g_exit_status;
			cmd = cmd->next;
		}
		cmd = cmds->head;
		if (cmd && cmd->next == NULL && is_builtin(cmd->args[0]))
			g_exit_status = execute_builtin(cmd);
		else
			execute_pipeline(cmd);
		free_all(cmds->k);
		free(input);
	}
	return (g_exit_status);
}
