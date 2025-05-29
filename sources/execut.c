/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:31:42 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/30 13:57:42 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_not_builtin(t_data *data)
{
	one_command(data);
}

void	child_builtin(t_cmd *cmd, t_data *data)
{
	int	status;

	status = 0;
	data->pid = fork();
	if (data->pid == 0)
	{
		if (cmd->redirection)
		{
			redirection_check(data, cmd);
			cmd->builtin(data);
			close(data->out_fd);
			exit (data->exit_code);
		}
	}
	else
	{
		waitpid(data->pid, &status, 0);
		data->exit_code = WEXITSTATUS(status);
	}
}

void	execut_simple(t_cmd *cmd, t_data *data)
{
	int	status;

	status = 0;
	if (cmd->redirection)
	{
		if (is_buitin(cmd->str[0]) == 1)
			child_builtin(cmd, data);
		else
			is_not_builtin(data);
	}
	else if (!cmd->redirection && is_buitin(cmd->str[0]) == 1)
		cmd->builtin(data);
	else
		is_not_builtin(data);
}

void	execut(t_cmd **cmd, t_data *data)
{
	t_cmd	*temp_cmd;

	temp_cmd = *cmd;
	redirect(cmd, data);
	if (temp_cmd->next == 0)
		execut_simple(temp_cmd, data);
	else
		multi_pipe(data);
}
