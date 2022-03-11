/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odomenic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:51:29 by odomenic          #+#    #+#             */
/*   Updated: 2021/09/25 17:48:33 by odomenic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	if (len == 0)
		return (0);
	while ((len != 0) && (*s1 != '\0') && (*s2 != '\0'))
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		len--;
	}
	if (len != 0)
	{
		if (((*s1 != '\0') && (*s2 == '\0'))
			|| ((*s2 != '\0') && (*s1 == '\0')))
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		else
			return (0);
	}
	return (0);
}
