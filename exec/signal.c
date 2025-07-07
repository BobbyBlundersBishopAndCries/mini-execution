#include "../minishell.h"

static void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	g_exit_status = 130;
}


void handle_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
