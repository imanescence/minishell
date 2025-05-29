/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:55:26 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/08/15 16:01:27 by ssteveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

int	error_in(t_data *data, char *cmd, int flag)
{
	if (flag == 1)
		printf("minishell: %s: No such file or directory\n", cmd);
	return (data->exit_code = 1);
}

int	mini_pars_in(t_data *data, t_cmd *cmds)
{
	int		i;
	t_list	*list;

	i = 0;
	list = cmds->redirection;
	while (list != NULL && list->token == INPUT)
	{
		list = list->next;
		data->out_fd = open(list->str, O_RDONLY);
		if (data->out_fd == -1)
			return (error_in(data, list->str, 1));
		list = list->next;
	}
	return (0);
}

int	infile_redirection(t_data *data, t_cmd *cmds)
{
	if (cmds->redirection->token == HEREDOC)
	{
		data->out_fd = open("herdoc.txt", O_RDONLY);
		data->out_fd = STDOUT_FILENO;
		if (cmds->str[0])
			cmds->builtin(data);
	}
	else if (mini_pars_in(data, cmds) != 0)
	{
		return (error_in(data, NULL, 0));
	}
	else if (dup2(data->out_fd, STDIN_FILENO) == -1)
	{
		close(data->out_fd);
		return (error_in(data, NULL, 0));
	}
	close(data->out_fd);
	return (data->exit_code = 0);
}
