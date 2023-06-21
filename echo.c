/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:16:10 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/18 09:49:55 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gethompath(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->var, "HOME", 4))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_write_in_fd(char **str, int fd)
{
	int	i;

	i = 1;
	if (str == NULL)
		return ;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		i++;
	}
}

void	ft_echo(t_parc *head)
{
	int	fd;

	fd = -1;
	g_exitstatus = 0;
	fd = ft_open_outfile(head);
	if (fd == -1)
	{
		ft_write_in_fd(head->arg, 1);
		printf("\n");
	}
	else
		ft_write_in_fd(head->arg, fd);
}

char	*ft_getpath(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PATH") == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}
