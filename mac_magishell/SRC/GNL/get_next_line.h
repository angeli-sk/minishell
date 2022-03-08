/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 14:09:11 by akramp        #+#    #+#                 */
/*   Updated: 2021/03/30 12:32:26 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int			get_next_line(int fd, char **line);
int			fft_strlen(const char *str);
void		*fft_memcpy(void *dst, const void *src, int n);
char		*fft_strjoin(char *s1, char *s2);
int			fft_strlcpy(char *dst, const char *src, int dstsize);
char		*fft_fill(char *str, char const *s1, char const *s2);
int			fg_n_l_read(char **str, char **buffer, int fd, int *i);
void		fg_n_l_eol(int ret, char **str, int *i, char **buffer);
int			fft_free(char **str, char **buffer, int check);
int			fempty_s(char **str);

#endif
