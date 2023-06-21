/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:04:42 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 11:37:13 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_checkcmd(t_parc *head, t_env **env_list, char **env,
		t_heredoc **idfd)
{
	if (head->arg[0] != NULL)
	{
		if (ft_builtins(head, env_list) == 1)
			ft_one_cmd(head, env, idfd, env_list);
	}
	else
		return ;
}

void	ft_exc(t_parc **all, t_env **env_list, char **env, t_heredoc **idfd)
{
	ft_heredoc_list(all, idfd, *env_list);
	if ((*all)->next)
	{
		ft_one_pipe(all, idfd, env_list);
	}
	else
		ft_checkcmd(*all, env_list, env, idfd);
}
