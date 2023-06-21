/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:27:54 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 10:48:53 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_ex_heredoc(t_parc **all)
{
	t_parc	*tmp;
	int		i;

	tmp = *all;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
		{
			if (tmp->tab[i] == 4)
				return (0);
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_one_pipe(t_parc **all1, t_heredoc **idfd, t_env **env_list)
{
	t_parc	*all;
	t_pipe	*t;

	t = malloc(sizeof(t_pipe));
	all = *all1;
	t->ptr = ft_getpath(env_list);
	t->spltcmd = ft_split(t->ptr, ':');
	pipe(t->fd);
	t->id = fork();
	if (t->id == 0)
		ft_pipe_helper(&all, t, idfd, env_list);
	else
		ft_pipe_helper4(&all, t, idfd);
	free_dubl(t->spltcmd);
	free(t);
	close(t->fd[1]);
	close(t->fd[0]);
	waitpid(t->pid, &t->a, 0);
	while (waitpid(0, NULL, 0) != -1)
		;
	g_exitstatus = WEXITSTATUS(t->a);
}
