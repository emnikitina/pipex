/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:15:05 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/28 19:25:53 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	char	**paths;

	paths = NULL;
	while (*envp)
	{
		if (!(ft_strncmp("PATH=", *envp, 5)))
		{
			paths = ft_split(*envp + 5, ':');
			break ;
		}
		(*envp)++;
	}
	return (paths);
}

char	*get_full_path(char	*cmd, char **envp)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*str;
	int		not_exists;

	not_exists = -1;
	paths = get_paths(envp);
	i = -1;
	str = NULL;
	if (!access(cmd, 0))
		return (ft_strdup(cmd));
	while (paths[++i] && not_exists)
	{
		tmp = ft_strjoin(paths[i], "/");
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		not_exists = access(str, 0);
	}
	free(paths);
	if (not_exists == -1)
		return (NULL);
	return (str);
}

int	exec_cmd(char **cmd, char **envp, int	*fds, int file_fd)
{
	char	*full_path;
	int		ret;

	ret = E_FAIL;
	close(fds[0]);
	close(fds[1]);
	close(file_fd);
	full_path = get_full_path(cmd[0], envp);
	if (!full_path)
		ft_error(E_CMD, cmd[0]);
	else
	{
		ret = execve(full_path, cmd, envp);
		free(full_path);
		ft_perror(cmd[0]);
	}
	return (ret);
}

int	exec_cmd_one(t_cmds **cmds, char **envp)
{
	int		ret;

	ret = E_FAIL;
	if (pipe((*cmds)->fds) < 0)
		return (ft_error(E_PIPE, NULL));
	(*cmds)->pid1 = fork();
	if ((*cmds)->pid1 < 0)
		return (E_FAIL);
	else if ((*cmds)->pid1 == 0)
	{
		(*cmds)->file1_fd = open((*cmds)->file1, O_RDONLY);
		if ((*cmds)->file1_fd == -1)
			ft_error(E_FILENOTEXIST, (*cmds)->file1);
		if (dup2((*cmds)->file1_fd, STDIN_FILENO) < 0)
			ft_error(E_REDIRECT, (*cmds)->file1);
		if (dup2((*cmds)->fds[1], STDOUT_FILENO) < 0)
			ft_error(E_PIPE, NULL);
		ret = exec_cmd((*cmds)->cmd1, envp, (*cmds)->fds, (*cmds)->file1_fd);
		exit(ret);
	}
	return (ret);
}

int	exec_cmd_two(t_cmds **cmds, char **envp)
{
	int		ret;

	ret = E_FAIL;
	(*cmds)->pid2 = fork();
	if ((*cmds)->pid2 < 0)
		return (E_FAIL);
	else if ((*cmds)->pid2 == 0)
	{
		(*cmds)->file2_fd = open((*cmds)->file2, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRWXU);
		if ((*cmds)->file2_fd == -1)
			ft_error(E_OPEN_CREATE, (*cmds)->file2);
		if (dup2((*cmds)->fds[0], STDIN_FILENO) < 0)
			ft_error(E_PIPE, NULL);
		if (dup2((*cmds)->file2_fd, STDOUT_FILENO) < 0)
			ft_error(E_REDIRECT, NULL);
		ret = exec_cmd((*cmds)->cmd2, envp, (*cmds)->fds, (*cmds)->file2_fd);
		exit(ret);
	}
	close((*cmds)->fds[0]);
	close((*cmds)->fds[1]);
	return (ret);
}
