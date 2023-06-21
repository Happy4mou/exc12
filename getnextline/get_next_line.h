/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:22:47 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/05/30 15:48:49 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*ft_strdup1(char *s1);
char	*get_next_line(int fd);
char	*ft_strchr1(char *s, int c);
char	*ft_strjoin1(char *s1, char *s2);
char	*get_line_r(char *src);
char	*get_los(char *src);
char	*get_next(int fd, char *bufjoin);
size_t	ft_strlen1(char *s);

#endif
