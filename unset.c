/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:14:19 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/18 09:46:00 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	norm_ft_re_node(t_env *tmp, t_env *prv, char *ptr)
{
	if (prv->next == NULL && ft_strcmp(prv->var, ptr) == 0 && ptr[0] != '_')
	{
		tmp->next = NULL;
		free(prv->var);
		free(prv->val);
		free(prv);
		return (1);
	}
	if (tmp == NULL)
		return (1);
	return (0);
}

int	norm_ft_re_node1(t_env **tmp, t_env **env, char *ptr)
{
	if (ft_strcmp((*env)->var, ptr) == 0)
	{
		*tmp = *env;
		free((*tmp)->var);
		free((*tmp)->val);
		free(*tmp);
		*env = (*env)->next;
		return (1);
	}
	return (0);
}

void	ft_remove_node(t_env **env, char *ptr)
{
	t_env	*tmp;
	t_env	*prv;

	tmp = *env;
	prv = *env;
	g_exitstatus = 0;
	if (ptr == NULL)
		return ;
	if (norm_ft_re_node1(&tmp, env, ptr) == 1)
		return ;
	while (prv->next != NULL)
	{
		if (ft_strcmp(prv->var, ptr) == 0)
		{
			free(tmp->next->var);
			free(tmp->next->val);
			free(tmp->next);
			tmp->next = prv->next;
			break ;
		}
		tmp = prv;
		prv = prv->next;
	}
	if (norm_ft_re_node(tmp, prv, ptr) == 1)
		return ;
}
