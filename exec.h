#ifndef EXEC_H
#define EXEC_H
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include "libft/libft.h"
#include <errno.h>
typedef struct s_env
{
	struct s_env	*next;
	char	*valeur;
}		t_env;
/* builtins */
int 	ft_cd(char *path);
int 	ft_pwd(void);
int		ft_echo(char **av);
t_env	*create_list(char **env);
int		ft_env(char **env);
#endif