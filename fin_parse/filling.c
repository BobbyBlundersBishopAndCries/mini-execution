#include "../minishell.h"

size_t get_all_argscmd(t_token *token)
{
  size_t count;
  t_token *prev;

  prev = NULL;
  count = 0;
  while (token && token->type != PIPE)
  {
    if(prev && !is_redir(prev) && token->type == WORD)
      count++;
    prev = token;
    token = token->next;
  }
  return count;
}
t_redir * add_in_file(t_token *redir , t_token *file , t_redir *head,  t_lst_hk *x)
{
  t_redir *r;
  t_redir *tmp;

  r = ft_malloc(sizeof(t_redir), x);
  r->files = ft_strdump(file->token, x);
  if(redir->type == REDIR_APPEND)
    r->index = R_APPEND;
  else if(redir->type == REDIR_IN)
    r->index = R_IN;
  else if(redir->type == REDIR_OUT)
    r->index = R_OUT;
  else if(redir->type == HEREDOC)
    r->index = R_HEREDOC;
  r->next = NULL;
  if (!head)
    head = r;
  else
  {
    tmp = head;
    while(tmp->next)
      tmp = tmp->next;
    tmp->next = r;
  }
  return head;
}

t_cmd *get_cmd(t_token **t , t_lst_hk *x , t_env *env)
{
  t_token *token;
  size_t count;
  t_cmd *cmd;
  size_t index;

  index = 0;
  token = *t;
  cmd = ft_malloc(sizeof(t_cmd), x);
  count = get_all_argscmd(token);
  cmd->args = ft_malloc(sizeof(char *) * (count + 2), x);
  cmd->files = NULL;
  cmd->next = NULL;
  cmd->env = &env;
  while (token && token->type != PIPE)
  {
    if (is_redir(token) && token->next && token->next->type == WORD)
    {
      cmd->files = add_in_file(token, token->next, cmd->files, x);
      token = token->next;
    }
    else if (token->type == WORD)
      cmd->args[index++] = ft_strdump(token->token, x);
    token = token->next;
  }
  cmd->args[index] = NULL;
  *t = token;
  return cmd;
}

t_lst_cmd *fill_struct(t_lst_token *lst_token, t_lst_hk *x , t_env *env)
{
	t_lst_cmd *lst_cmds = ft_malloc(sizeof(t_lst_cmd), x);
	t_token *token = lst_token->head;
	t_cmd *tail = NULL;
  t_cmd *cmd = NULL;
  lst_cmds->head = NULL;

  while (token)
	{
    cmd = get_cmd(&token, x, env);
    if (!lst_cmds->head)
    {
			lst_cmds->head = cmd;
			tail = cmd;
		}
		else
		{
			tail->next = cmd;
			tail = cmd;
		}
		if (token && token->type == PIPE)
			token = token->next;
	}
	return lst_cmds;
}
