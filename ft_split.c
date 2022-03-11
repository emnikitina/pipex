/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:57:10 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/25 17:41:01 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_num_str(char const *str, char c)
{
	int		num;
	size_t	i;
	size_t	len;

	num = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		while ((str[i] == c) && (str[i] != '\0'))
			i++;
		if ((str[i] != c) && (str[i] != '\0'))
			num++;
		while ((str[i] != c) && (str[i] != '\0'))
			i++;
	}
	return (num);
}

static void	ft_free_words(char **arr_str, size_t *i)
{
	while (*i--)
		free(arr_str[*i]);
}

static char	*ft_mem_word(char const *str, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while ((*str != c) && (*str != '\0'))
	{
		str++;
		len++;
	}
	str -= len;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, str, len);
	word[len] = '\0';
	return (word);
}

static int	ft_word(char **arr_str, char const *str, char c, size_t num)
{
	char	*word;
	size_t	i;

	i = 0;
	while (i < num)
	{
		while ((*str == c) && (*str != '\0'))
			str++;
		if ((*str != c) && (*str != '\0'))
		{
			word = ft_mem_word(str, c);
			if (!word)
			{
				ft_free_words(arr_str, &i);
				free(arr_str);
				return (1);
			}
			arr_str[i] = word;
			str += ft_strlen(word);
			i++;
		}
	}
	arr_str[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_str;
	size_t	num;

	if (!s)
		return (NULL);
	num = ft_num_str(s, c);
	arr_str = (char **)malloc((num + 1) * sizeof(char *));
	if (!arr_str)
		return (NULL);
	if (ft_word(arr_str, s, c, num))
		return (NULL);
	return (arr_str);
}
