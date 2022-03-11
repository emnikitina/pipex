/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:14:11 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/27 21:00:18 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

enum e_error
{
	E_SUCCESS,
	E_FAIL,
	E_ALLOC,
	E_FILENOTEXIST,
	E_OPEN_CREATE,
	E_PIPE,
	E_REDIRECT,
	E_CMD = 127
};

typedef struct s_cmds
{
	char	**cmd1;
	char	**cmd2;
	int		fds[2];
	char	*file1;
	int		file1_fd;
	char	*file2;
	int		file2_fd;
	pid_t	pid1;
	pid_t	pid2;
}				t_cmds;

char	*ft_strdup(char *str);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
int		exec_cmd_one(t_cmds **cmds, char **envp);
int		exec_cmd_two(t_cmds **cmds, char **envp);
void	ft_perror(char *str);
void	perror(const char *str);
int		ft_error(int err, char *name);
#endif
