/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:16:26 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/21 11:36:35 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addback(t_heredoc **head, int ptr)
{
	t_heredoc	*new;
	t_heredoc	*last;

	new = malloc(sizeof(t_heredoc));
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

void	ft_heredoc_list(t_parc **head, t_heredoc **idfd, t_env *env)
{
	t_parc	*tmp;
	int		i;
	int		x;

	x = 0;
	i = 0;
	tmp = *head;
	while (tmp)
	{
		i = 0;
		while (tmp->name[i])
		{
			if (tmp->tab[i] == 4)
				x = ft_heredoc(*head, tmp->name[i], env);
			i++;
		}
		if (x)
			ft_addback(idfd, x);
		tmp = tmp->next;
	}
}

void	ft_heredoc_helper(t_hr *t, t_env *env, char *ptr, t_parc *head)
{
	while (1)
	{
		t->buffer = get_next_line(0);
		t->bufptr = ft_strtrim(t->buffer, "\n");
		if (ft_strcmp(t->bufptr, ptr) == 0)
		{
			free(t->buffer);
			free(t->bufptr);
			break ;
		}
		t->buffer = ft_expand(t->buffer, env, 0);
		t->perout = ft_open_outfile(head);
		ft_putstr_fd(t->buffer, t->fd[1]);
		free(t->bufptr);
		free(t->buffer);
	}
}

int	ft_heredoc(t_parc *head, char *ptr, t_env *env)
{
	t_hr	t;

	t.perout = -1;
	pipe(t.fd);
	if (fork() == 0)
	{
		ft_heredoc_helper(&t, env, ptr, head);
		exit(0);
	}
	else
	{
		waitpid(0, NULL, 0);
	}
	close(t.fd[1]);
	return (t.fd[0]);
}
