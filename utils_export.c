/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:59:10 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/17 18:00:58 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin12(char const *s1, char const *s2)
{
	int		i;
	char	*s3;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	j = ft_strlen(s1);
	i = 0;
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (0);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		s3[j] = s2[i];
		i++;
		j++;
	}
	s3[j] = '\0';
	return (s3);
}

int	print_env(char **arg, t_env *env)
{
	if (arg[1] == NULL)
	{
		while (env)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->var, 1);
			if (env->val)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env->val, 1);
				ft_putchar_fd('\"', 1);
			}
			ft_putchar_fd('\n', 1);
			env = env->next;
		}
		return (1);
	}
	return (0);
}

int	check_dub(int end, char *str, t_env *env)
{
	while (env)
	{
		if (strncmp(env->var, str, end + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_export_hepler1(t_env *env, char **arg, int x, char *var)
{
	int	i;

	i = 0;
	while (arg[x][i] && arg[x][i] != '+' && arg[x][i] != '=')
		i++;
	while (env)
	{
		if (strncmp(env->var, var, i + 1) == 0)
			break ;
		env = env->next;
	}
	if (arg[x][i] == '+' && arg[x][i + 1] == '=')
		env->val = ft_strjoin1(env->val, &arg[x][i + 2]);
	else if (arg[x][i] == '=')
	{
		if (env->val != NULL)
			free(env->val);
		env->val = ft_strdup(&arg[1][i + 1]);
	}
}
