/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:22:16 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/21 11:23:11 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exc/getnextline/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_heredoc
{
	int					data;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_index
{
	int					index;
	int					arg_i;
}						t_index;

typedef struct s_count
{
	int					count_dir;
	int					count_arg;
}						t_count;

typedef struct s_list2
{
	char				*var;
	char				*val;
	struct s_list2		*next;
}						t_env;

typedef struct node
{
	char				*data;
	struct node			*next;
}						t_node;

int						g_exitstatus;

typedef struct s_pipe
{
	int					eropin;
	int					eropout;
	int					id;
	int					i;
	char				*bufcmd;
	int					fd[2];
	char				**spltcmd;
	int					j;
	int					idpip;
	int					pid;
	int					a;
	char				*ptr;

	struct s_pipe		*next;
}						t_pipe;

typedef struct s_list
{
	char				*env;
	t_env				*env_list;
	int					*tab;
	char				**name;
	char				**arg;
	struct s_list		*next;
}						t_parc;

typedef struct s_hr
{
	int		perout;
	int		fd[2];
	char	*buffer;
	char	*bufptr;
	struct s_hr		*next;
}						t_hr;

int						*string_to_nbr(char *str);
int						*string_to_nbr2(char *str);
char					**p_split_pro(char *str, int len);
t_parc					*ft_fill_lst(char **container);
void					ft_lst_add_back(t_parc *lst, t_parc *new);
void					free_all(t_parc *all, char **container, char *buffer);
int						ft_count_arg(char **container, int j);
void					count_dir(int *j, int *count_dir, int count_arg,
							char **cont);
void					remoev_cout(t_parc *all);
void					ft_lst_add_back2(t_env *lst, t_env *new);
t_env					*ft_fill_lst2(char **env);
char					*ft_expand(char *str, t_env *env, int i);
void					str_free(char *s1, char *s2, char *s3, char *s4);
char					*replace_free(char *s1, char *env);

void					ft_remove_node(t_env **env, char *ptr);
int						ft_heredoc(t_parc *head, char *ptr, t_env *env);
void					ft_echo(t_parc *head);
void					ft_write_in_fd(char **str, int fd);
void					cdfunction(t_env **head, char *ptr);
char					*gethompath(t_env **head);
char					*pwdfunction(int c);
char					*getpwdpath(t_env **head);
void					ft_heredoc_list(t_parc **head, t_heredoc **idfd,
							t_env *env);
char					*ft_get_bufcmd(char **spltcmd, char *av);
char					*ft_getpath(t_env **env_list);
int						ft_open_infile(t_parc *all, t_heredoc **idfd);
void					ft_one_cmd(t_parc *all, char **env, t_heredoc **idfd,
							t_env **env_list);
int						ft_open_outfile(t_parc *all);
void					ft_one_pipe(t_parc **all1, t_heredoc **idfd,
							t_env **env_list);
void					ft_checkcmd(t_parc *head, t_env **env_list, char **env,
							t_heredoc **idfd);
int						print_env(char **arg, t_env *env);
int						check_dub(int end, char *str, t_env *env);
void					ft_export(char **arg, t_env *env, int x);
void					ft_env(t_env **env);
void					ft_exc(t_parc **all, t_env **env_list, char **env,
							t_heredoc **idfd);
void					ft_addback(t_heredoc **head, int ptr);
void					ft_exit(t_parc *all);
int						ft_check_diget(char *ptr);
int						p_syntax_error(char **container, char *buffer);
void					ft_one_cmd_helper(t_parc *all, char **env,
							char **spltcmd, t_heredoc **idfd);
int						ft_builtins(t_parc *head, t_env **env_list);
void					ft_pipe_helper(t_parc **all, t_pipe *t,
							t_heredoc **idfd, t_env **env_list);
void					ft_pipe_helper2(t_parc **all, t_pipe *t,
							t_heredoc **idfd);
void					ft_pipe_helper3(t_parc **all, t_pipe *t,
							t_heredoc *idfd);
void					ft_pipe_helper4(t_parc **all, t_pipe *t,
							t_heredoc **idfd);
int						ft_check_ex_heredoc(t_parc **all);
int						print_env(char **arg, t_env *env);
int						check_dub(int end, char *str, t_env *env);
void					ft_export_hepler1(t_env *env, char **arg, int x,
							char *var);
int						ft_export_check_name(char **var, char **arg, t_env *env,
							int x);
void					ft_export_helper2(char **arg, int x, t_env *tmp, int i);
int						ft_builtins_helper(t_parc *head, t_env **env_list);
char					*ft_strjoin12(char const *s1, char const *s2);
int						norm_ft_re_node(t_env *tmp, t_env *prv, char *ptr);
int						norm_ft_re_node1(t_env **tmp, t_env **env, char *ptr);
void					free_dubl(char **str);

#endif
