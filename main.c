/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:09:38 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/28 19:29:42 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *str)
{
	char	*copy;
	int		i;
	int		len;

	len = ft_strlen(str);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < len)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

int	ft_error(int err, char *name)
{
	char	*str;

	write(STDERR_FILENO, "pipex: ", 7);
	str = "Unknown error\n";
	if (err == E_FILENOTEXIST)
		perror(name);
	else
	{
		if (name)
		{
			write(STDERR_FILENO, name, ft_strlen(name));
			write(STDERR_FILENO, ": ", 2);
		}
		if (err == E_ALLOC)
			str = "Allocation error\n";
		if (err == E_OPEN_CREATE)
			str = "Cannot create file\n";
		if ((err == E_PIPE) || (err == E_REDIRECT))
			str = "Cannot create pipe or redirect\n";
		if (err == E_CMD)
			str = "command not found\n";
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	exit(err);
	return (err);
}

void	ft_perror(char *str)
{
	write(STDERR_FILENO, "pipex: ", 7);
	perror(str);
}

void	free_all(t_cmds **cmds)
{
	int	i;

	i = -1;
	if ((*cmds)->cmd1)
	{
		while ((*cmds)->cmd1[++i])
			free((*cmds)->cmd1[i]);
		free((*cmds)->cmd1);
	}
	i = -1;
	if ((*cmds)->cmd2)
	{
		while ((*cmds)->cmd2[++i])
			free((*cmds)->cmd2[i]);
		free((*cmds)->cmd2);
	}
	free((*cmds)->file1);
	free((*cmds)->file2);
	free(*cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmds	*cmds;
	int		ret;
	int		status;

	if (argc != 5)
		return (write(STDERR_FILENO, "Wrong number of args\n", 21));
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmds)
		ft_error(E_ALLOC, NULL);
	cmds->cmd1 = ft_split(argv[2], ' ');
	cmds->file1 = ft_strdup(argv[1]);
	cmds->cmd2 = ft_split(argv[3], ' ');
	cmds->file2 = ft_strdup(argv[4]);
	ret = exec_cmd_one(&cmds, envp);
	ret = exec_cmd_two(&cmds, envp);
	waitpid(cmds->pid1, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	waitpid(cmds->pid2, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	free_all(&cmds);
	return (ret);
}
