/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:05:06 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 13:35:22 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins_helper(t_parc *head, t_env **env_list)
{
	int	i;

	i = 1;
	if (head->arg[0] != NULL)
	{
		if (ft_strncmp(head->arg[0], "echo", 5) == 0)
			ft_echo(head);
		else if (ft_strncmp(head->arg[0], "export", 7) == 0)
		{
			if (head->arg[1] == NULL)
				ft_export(head->arg, *env_list, i);
			while (head->arg[i])
				ft_export(head->arg, *env_list, i++);
		}
		else if (ft_strncmp(head->arg[0], "unset", 6) == 0)
		{
			i = 1;
			while (head->arg[i])
				ft_remove_node(env_list, head->arg[i++]);
		}
		else
			return (1);
	}
	return (0);
}

int	ft_builtins(t_parc *head, t_env **env_list)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = 1;
	if (head->arg[0] != NULL)
	{
		if (ft_builtins_helper(head, env_list) == 1)
		{
			if (ft_strncmp(head->arg[0], "env", 4) == 0)
				ft_env(env_list);
			else if (ft_strncmp(head->arg[0], "cd", 3) == 0)
				cdfunction(env_list, head->arg[1]);
			else if (ft_strncmp(head->arg[0], "pwd", 4) == 0)
			{
				ptr = pwdfunction(0);
				free(ptr);
			}
			else if (ft_strncmp(head->arg[0], "exit", 5) == 0)
				ft_exit(head);
			else
				return (1);
		}
	}
	return (0);
}
