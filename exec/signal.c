#include "../minishell.h"

void	error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}
void	sigint_handler(int signo)
{
	(void)signo;
	g_shell.sigint_received = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void handle_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

void	restore_signals_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
