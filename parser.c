/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:03:02 by oabushar          #+#    #+#             */
/*   Updated: 2022/12/28 16:35:14 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit()
{
	printf("There was an error in the arguements\n");
	exit(1);
}

void	parse_cmds(t_cmd *input, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_cmd && info->split[i] && input)
	{
		input->full_cmd = info->split[i++];
		get_list(input, info);
		input = input->next;
	}
}

void	get_list(t_cmd *input, t_info *info)
{
	int i;

	i = 0;
	if (!input)
		return;
	(void)info;
	get_redir(input);
	get_short_cmd(input);
	input->s_cmd = ft_split_q(input->new_cmd, ' ');
	// while (input->s_cmd[i])
	// {
	// 	printf("the s is (%s)\n", input->s_cmd[i++]);
	// }
	// input->cmd = get_cmd(info);
	// if (input->cmd == NULL)
	// 	return ;
	free_double(input->files);
	free_double(input->redir);
}

void	parse_line(t_info *info, t_cmd *input)
{
	int i;

	i = 0;
	info->open_q = 0;
	input = (NULL);
	info->n_cmd = num_cmds(info);
	info->split = ft_split_q(info->line, '|');
	while (i < info->n_cmd)
	{
		lst_add(&input);
		i++;
	}
	parse_cmds(input, info);
	i = 0;
	while (input && input->s_cmd[i])
	{
		printf("the (%s)  \n", input->s_cmd[i++]);
	}
}

int	main(void)
{
	// char buf[1024];
	t_info	info;
	t_cmd	input;
	while (1)
	{
		printf("%s", PURPLE);
		info.line = readline("minishell> \033[0m");
		add_history(info.line);
		parse_line(&info, &input);
	}
	return 0;
}