/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:19:17 by rchmouk           #+#    #+#             */
/*   Updated: 2023/06/21 10:40:32 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    close_all(void)
{
    int    i;

    i = 3;
    while (i < 1024)
        close(i++);
}

int	main(int ac, char **av, char **env)
{
	t_parc		*all;
	char		*buffer = NULL;
	char		**container;
	t_env		*env_list;
	int			len;
	int			id;
	int			i;
	t_heredoc	*idfd;

		i = 0;
	id = 0;
    if(*env != NULL)
	    env_list = ft_fill_lst2(env);
    else
        env_list = NULL;idfd = NULL;
	while (ac && av)
	{
        
		buffer = readline(">minishell: ");
        
		if (buffer != NULL && buffer[0])
			{add_history(buffer);
			buffer = ft_expand(buffer, env_list, 0);
			len = ft_strlen(buffer);
			container = p_split_pro(buffer, len);
			all = ft_fill_lst(container);
			remoev_cout(all);
            ft_exc(&all, &env_list, env, &idfd);
			free_all(all, container, buffer);
            close_all();
            //free (idfd);
		}
		else 
            printf("\n");
	}
    
}
