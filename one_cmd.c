/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:39:29 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 07:46:18 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_one_cmd_helper(t_parc *all, char **env, char **spltcmd,
		t_heredoc **idfd)
{
	int		eropin;
	int		eropout;
	char	*bufcmd;

	if (!all->arg)
		return ;
	eropin = ft_open_infile(all, idfd);
	eropout = ft_open_outfile(all);
	bufcmd = ft_get_bufcmd(spltcmd, all->arg[0]);
	if (eropin != -1)
	{
		dup2(eropin, 0);
	}
	if (eropout != -1)
		dup2(eropout, 1);
	free_dubl(spltcmd);
	execve(bufcmd, all->arg, env);
	free(bufcmd);
	(write(2, "EXECVE ERROR ! \n", 17), exit(127));
}

void	ft_one_cmd(t_parc *all, char **env, t_heredoc **idfd, t_env **env_list)
{
	int		id;
	char	**spltcmd;
	int		a;
	char	*ptr;

	ptr = ft_getpath(env_list);
	spltcmd = ft_split(ptr, ':');
	id = fork();
	if (id == 0)
	{
		ft_one_cmd_helper(all, env, spltcmd, idfd);
	}
	free_dubl(spltcmd);
	waitpid(id, &a, 0);
	g_exitstatus = WEXITSTATUS(a);
}
