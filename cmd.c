/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:50:51 by oabushar          #+#    #+#             */
/*   Updated: 2022/12/26 17:52:46 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int alloc_q_cmd(char *line, int index)
{
	int		m;
	char	c;

	m = 0;
	if (!line || !line[index])
		return (0);
	while (line[index] && !ft_isspace(line[index]))
	{
		if (line[index] == 34 || line[index] == 39)
		{
			c = line[index++];
			while (line[index] != c && line[index])
			{
				index++;
				m++;
			}
		}
		if (line[index] != c && line[index])
			m++;
		index++;
	}
	return (m);
}

char *get_rest(t_info *info)
{
	int		i;
	char	*rest;
	int		r;

	i = 0;
	r = 0;
	while(info->line[i] && info->line[i] != '|')
		i++;
	if (!info->line[i])
		return (NULL);
	if (info->line[i] == '|')
		i++;
	rest = malloc (sizeof(char) * ft_strlen(info->line) - i + 1);
	if (!rest)
		return (NULL);
	while (info->line[i])
		rest[r++] = info->line[i++];
	rest[r] = '\0';
	free (info->line);
	return (rest);
}

char *get_q_cmd(t_info *info, int index)
{
	char	c;
	int		m;
	char	*ret;
	
	c = 0;
	if (info->line[index] && (info->line[index] == 34 || info->line[index] == 39))
		c = info->line[index];
	m = alloc_q_cmd(info->line, index);
	if (!m)
		return (NULL);
	ret = malloc(m + 1);
	m = 0;
	while (info->line[index] && !ft_isspace(info->line[index]))
	{
		while (info->line[index] != 34 && info->line[index] != 39 && !ft_isspace(info->line[index]))
			ret[m++] = info->line[index++];
		if (info->line[index] == 39 || info->line[index] == 34)
			c = info->line[index++];
		while (info->line[index] && info->line[index] != c && !ft_isspace(info->line[index]))
			ret[m++] = info->line[index++];
	}
	return (ret);
}

char	*get_cmd(t_info *info)
{
	int		i;
	int		m;
	char	*str;

	i = 0;
	m = 0;
	if (!info->line[i])
		return NULL;
	while (info->line[i] == 32)
		i++;
	while (info->line[i] && ft_isalpha(info->line[i]))
	{
		m++;
		i++;
	}
	if (info->line[i] == 34 || info->line[i] == 39)
		return (get_q_cmd(info, 0));
	str = malloc (sizeof(char) * m + 1);
	if (!str)
		return (NULL);
	i = 0;
	m = 0;
	while (info->line[i] == 32)
		i++;
	while (info->line[i] && ft_isalpha(info->line[i]))
	{
		str[m++] = info->line[i++];
	}
	str[m] = 0;
	return (str);
}
