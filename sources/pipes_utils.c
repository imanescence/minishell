/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:57:09 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/08/20 14:57:17 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_pipes(int src[2], int dest[2])
{
	dest[0] = src[0];
	dest[1] = src[1];
}

void	close_pipes(t_data *data)
{
	close(data->pipe_in[READ]);
	close(data->pipe_in[WRITE]);
	close(data->pipe_out[WRITE]);
	close(data->pipe_out[READ]);
}

void	waiting_children(t_data *data)
{
	int	status;

	while (wait(NULL) != -1)
	{
		waitpid(data->pid, &status, 0);
		if (WEXITSTATUS(status) == 1)
			data->exit_code = 1;
		continue ;
	}
	close_pipes(data);
}

int	link_lists_counter(t_data *data)
{
	int		i;
	t_cmd	*cmds;

	i = 0;
	cmds = (*data->cmd);
	while (cmds != NULL)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}
