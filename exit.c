/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:29:33 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/17 16:17:24 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_diget(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ft_isdigit(ptr[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_parc *all)
{
	if (all->arg[1])
	{
		if (ft_check_diget(all->arg[1]) == 0 && all->arg[2] == NULL)
		{
			g_exitstatus = ft_atoi(all->arg[1]);
			exit(ft_atoi(all->arg[1]));
		}
		else if (ft_check_diget(all->arg[1]) != 0)
		{
			g_exitstatus = 255;
			(printf("exit: %s: numeric argument required", all->arg[1]),
				exit(255));
		}
		else if (ft_check_diget(all->arg[1]) == 0 && all->arg[2] != NULL)
		{
			g_exitstatus = 1;
			printf("exit: too many arguments\n");
			return ;
		}
	}
	else
	{
		g_exitstatus = 0;
		exit(0);
	}
}
