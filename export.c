/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:00:26 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 07:45:59 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_check_name(char **var, char **arg, t_env *env, int x)
{
	int	i;

	i = -1;
	if (arg[x] && ft_isalpha(arg[x][0]) == 0 && arg[x][0] != '_')
	{
		g_exitstatus = 1;
		printf(" not a valid identifier\n");
		return (-1);
	}
	if (print_env(arg, env) == 1)
		return (-1);
	while (arg[x][++i])
	{
		if (ft_isalpha(arg[x][i]) == 0 && ft_isdigit(arg[x][i]) == 0
			&& arg[x][i] != '_')
			break ;
	}
	*var = ft_substr(arg[x], 0, i);
	if ((arg[x][i] != '+' && arg[x][i] != '=' && arg[x][i]) || (arg[x][i]
			&& arg[x][i] == '+' && arg[x][i + 1] != '='))
		return (g_exitstatus = 1, ft_putstr_fd(arg[x], 1),
			ft_putstr_fd(": not a valid identifier\n", 1), -1);
	return (i);
}

void	ft_export_helper2(char **arg, int x, t_env *tmp, int i)
{
	if (arg[x][i] == '+' && arg[x][i + 1] == '=')
		tmp->val = ft_strjoin1(tmp->val, &arg[x][i + 2]);
	else if (arg[x][i] == '=')
	{
		if (tmp->val != NULL)
			free(tmp->val);
		tmp->val = ft_strdup(&arg[x][i + 1]);
	}
}

void	ft_export(char **arg, t_env *env, int x)
{
	int		i;
	t_env	*tmp;
	char	*var;

	i = ft_export_check_name(&var, arg, env, x);
	if (i == -1)
		return ;
	if (check_dub(i, var, env) == 0)
	{
		tmp = malloc(sizeof(t_env));
		tmp->var = ft_strdup(var);
		tmp->val = NULL;
		tmp->next = NULL;
		ft_lst_add_back2(env, tmp);
		ft_export_helper2(arg, x, tmp, i);
	}
	else
	{
		ft_export_hepler1(env, arg, x, var);
	}
	free(var);
	g_exitstatus = 0;
}

void	ft_env(t_env **env)
{
	t_env	*tmp;

	g_exitstatus = 0;
	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}
