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
	char	*whole;
	char	*key;
	char	*value;
}		t_env;
/* builtins */
int 	ft_cd(int ac, char **av);
int 	ft_pwd(void);
int		ft_echo(char **av);
int		ft_env(char **env);
int 	ft_export(int ac, char **env, char **av);
// t_env utils //
char	*dup_key(char *arg);
char	*dup_value(char *arg);
t_env	*create_list(char **env);
int		addback_node(t_env **head, char *av);
void	free_env_list(t_env *head);
#endif