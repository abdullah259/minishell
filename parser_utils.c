/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:36:18 by oabushar          #+#    #+#             */
/*   Updated: 2022/12/06 04:48:41 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	incrementer(char *s, int i)
{
	char	c;

	if ((s[i] == 39 || s[i] == 34))
	{
		c = s[i];
		i++;
		while (s[i] != c && s[i])
			i++;
	}
	return (i);
}

int	num_cmds(t_info *info)
{
	int		count;
	int		i;
	char	q;

	i = 0;
	count = 1;
	while (info->line[i])
	{
		if (info->line[i] == '|')
			count++;
		if (info->line[i] == 39 || info->line[i] == 34)
		{
			q = info->line[i++];
			while (info->line[i] != q && info->line[i])
				i++;
			if (info->line[i] != q)
				info->open_q = 1;
		}
		i++;
	}
	return (count);
}

void	lst_add(t_cmd **list, t_info *info)
{
	t_cmd	*new;
	t_cmd	*ptr;

	new = ((t_cmd *) malloc (sizeof(t_cmd)));
	if (!new)
		return ;
	new->next = NULL;
	get_list(new, info);
	// printf("%s \n", new->cmd);
	if (!(*list))
		*list = new;
	else
	{
		ptr = *list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}