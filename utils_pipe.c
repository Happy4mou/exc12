/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:37:23 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 11:37:47 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe_helper(t_parc **all, t_pipe *t, t_heredoc **idfd,
		t_env **env_list)
{
	if (!(*all)->arg)
		return ;
	t->eropin = ft_open_infile((*all), idfd);
	t->eropout = ft_open_outfile((*all));
	if (t->eropin != -1)
		dup2(t->eropin, 0);
	close(t->fd[0]);
	if (t->eropout == -1)
		dup2(t->fd[1], 1);
	else
		dup2(t->eropout, 1);
	if (ft_builtins((*all), env_list) == 1)
	{
		t->bufcmd = ft_get_bufcmd(t->spltcmd, (*all)->arg[0]);
		free_dubl(t->spltcmd);
		execve(t->bufcmd, (*all)->arg, NULL);
		free(t->bufcmd);
		(write(2, "EXECVE ERROR ! \n", 17), exit(127));
	}
	exit(0);
}

void	ft_pipe_helper2(t_parc **all, t_pipe *t, t_heredoc **idfd)
{
	if (!(*all)->arg)
		return ;
	t->eropin = ft_open_infile((*all), idfd);
	t->eropout = ft_open_outfile((*all));
	close(t->fd[0]);
	if (t->eropin == -1)
		dup2(t->idpip, 0);
	else
		dup2(t->eropin, 0);
	if (t->eropout != -1)
		dup2(t->eropout, 1);
	else
		dup2(t->fd[1], 1);
	if (ft_builtins((*all), &(*all)->env_list) == 1)
	{
		t->bufcmd = ft_get_bufcmd(t->spltcmd, (*all)->arg[0]);
		free_dubl(t->spltcmd);
		execve(t->bufcmd, (*all)->arg, NULL);
		free(t->bufcmd);
		(write(2, "EXECVE ERROR ! \n", 17), exit(127));
	}
	exit(0);
}

void	ft_pipe_helper3(t_parc **all, t_pipe *t, t_heredoc *idfd)
{
	if (!(*all)->arg)
		return ;
	t->eropin = ft_open_infile((*all), &idfd);
	t->eropout = ft_open_outfile((*all));
	close(t->fd[1]);
	if (t->eropin == -1)
		dup2(t->fd[0], 0);
	else
		dup2(t->eropin, 0);
	if (t->eropout != -1)
		dup2(t->eropout, 1);
	if (ft_builtins((*all), &(*all)->env_list) == 1)
	{
		t->bufcmd = ft_get_bufcmd(t->spltcmd, (*all)->arg[0]);
		free_dubl(t->spltcmd);
		execve(t->bufcmd, (*all)->arg, NULL);
		free(t->bufcmd);
		(write(2, "EXECVE ERROR ! \n", 17), exit(127));
	}
	exit(0);
}

void	ft_pipe_helper4(t_parc **all, t_pipe *t, t_heredoc **idfd)
{
	t_parc	*tmp;

	tmp = *all;
	tmp = tmp->next;
	if (ft_check_ex_heredoc(all) == 0)
	{
		free(*idfd);
		*idfd = (*idfd)->next;
	}
	while (tmp->next)
	{
		close(t->fd[1]);
		t->idpip = t->fd[0];
		pipe(t->fd);
		if (fork() == 0)
			ft_pipe_helper2(&tmp, t, idfd);
		close(t->idpip);
		tmp = tmp->next;
		if (ft_check_ex_heredoc(&tmp) == 0)
		{
			free(*idfd);
			*idfd = (*idfd)->next;
		}
	}
	t->pid = fork();
	if (t->pid == 0)
		ft_pipe_helper3(&tmp, t, *idfd);
}
