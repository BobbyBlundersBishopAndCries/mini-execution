/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:58:35 by feedback          #+#    #+#             */
/*   Updated: 2025/07/11 20:43:13 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_state g_shell = {.exit_status = 0, .sigint_received = 0, .in_heredoc = 0, .child_running = 0};

// Assume these types and functions are defined elsewhere:
// t_env, t_lst_cmd, t_cmd, g_shell, get_env, handle_signals, parsing,
// env_tochar, is_builtin, execute_builtin, execute_pipeline, free_all

static void handle_input_signals(void)
{
	handle_signals();
	g_shell.child_running = 0;
}
static char *get_user_input(void)
{
	char *input = readline("minishell:$ ");
	if (!input)
		write(1, "exit\n", 5);
	return input;
}

static void setup_cmd_env(t_lst_cmd *cmds, t_env *envir)
{
	t_cmd *cmd = cmds->head;
	while (cmd)
	{
		cmd->env = &envir;
		cmd->envp = env_tochar(envir);
		cmd = cmd->next;
	}
}

static void execute_cmd_list(t_lst_cmd *cmds)
{
    t_cmd *cmd = cmds->head;
    if (!cmd->next && is_builtin(cmd->args[0]))
        g_shell.exit_status = execute_builtin(cmd);
   	else
		{
        g_shell.child_running = 1;
        execute_pipeline(cmd);
        g_shell.child_running = 0;
    }
}

static void minishell_loop(t_env *envir)
{
	char *input;
	t_lst_cmd *cmds;

	while (1)
	{
		handle_input_signals();
		input = get_user_input();
		if (!input)
			break;
		if (*input)
			add_history(input);
		cmds = parsing(input, envir, &g_shell.exit_status);
		free(input);
		if (!cmds || !cmds->head)
			continue;
		setup_cmd_env(cmds, envir);
		execute_cmd_list(cmds);
		free_all(cmds->k);
	}
}

int main(int argc, char **argv, char **envp)
{
    t_env *envir;

    (void)argc;
    (void)argv;
    envir = get_env(envp);
    minishell_loop(envir);
    return g_shell.exit_status;
}