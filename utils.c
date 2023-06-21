/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:15:00 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/18 09:58:02 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_bufcmd(char **spltcmd, char *av)
{
	int		i;
	char	*buff;

	i = 0;
	if (ft_strchr(av, '/') != NULL && access(av, X_OK) != 0)
		return (NULL);
	if (access(av, X_OK) == 0)
		return (av);
	while (spltcmd && spltcmd[i])
	{
		buff = ft_strjoin(spltcmd[i], "/");
		buff = ft_strjoin1(buff, av);
		if (access(buff, X_OK) == 0)
			return (buff);
		free(buff);
		i++;
	}
	return (NULL);
}

void	addback(t_node **head, char *ptr)
{
	t_node	*new;
	t_node	*last;

	new = malloc(sizeof(t_node));
	new->data = ptr;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_node	*ft_stockenvinlist(char **env)
{
	t_node	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		addback(&tmp, env[i]);
		i++;
	}
	return (tmp);
}

int	sizell(t_node *lls)
{
	t_node	*tmp;
	int		i;

	tmp = NULL;
	tmp = lls;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_stockenvinptr(t_node *head)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = (char **)malloc(sizeof(char *) * sizell(head) + 1);
	while (head)
	{
		ptr[i] = head->data;
		head = head->next;
		i++;
	}
	return (ptr);
}
