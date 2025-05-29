/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:56:18 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/08/30 13:28:27 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_case(t_data *data, t_cmd *cmds)
{
	char	*pwd;

	if (ft_strncmp((*data->cmd)->str[0], "./", 2) == 0)
	{
		pwd = ft_strnjoin(getcwd(data->buf, 100),
				ft_substr((*data->cmd)->str[0],
					1, ft_strlen((*data->cmd)->str[0])));
		execve(pwd, cmds->str, data->env);
	}
	else if (ft_strncmp((*data->cmd)->str[0], "minishell", 9) == 0)
	{
		pwd = ft_strnjoin(getcwd(data->buf, 100),
				ft_strnjoin("/", (*data->cmd)->str[0]));
		execve(pwd, cmds->str, data->env);
	}
}

int	existing_path_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp("PATH=", data->env[i], 5) == 0)
			return (0);
		i++;
	}
	return (data->exit_code = 127);
}

void	redirection_check(t_data *data, t_cmd *cmds)
{
	t_list	*temp_red;

	while (cmds->redirection)
	{
		temp_red = cmds->redirection;
		while (cmds->redirection && (cmds->redirection->token == HEREDOC \
				|| cmds->redirection->token == 0))
		{
			cmds->redirection = cmds->redirection->next;
		}
		cmds->redirection = temp_red;
		if (cmds->redirection && (cmds->redirection->token == TRUNC
				|| cmds->redirection->token == APPEND))
			outfile_redirection(data, cmds);
		if (cmds->redirection && cmds->redirection->token == INPUT)
			infile_redirection(data, cmds);
		if (cmds->redirection != NULL)
			cmds->redirection = cmds->redirection->next;
	}
	cmds->redirection = temp_red;
}

void	one_command_bis(t_data *data, t_cmd *cmds)
{
	if (existing_path_check(data) != 0)
	{
		if (access((*data->cmd)->str[0], F_OK) == 0 && \
				access((*data->cmd)->str[0], X_OK) == 0)
		{
			if (cmds->redirection)
				redirection_check(data, cmds);
			execve((*data->cmd)->str[0], (*data->cmd)->str, data->env);
		}
		else
			find_cmd(data, cmds);
	}
	else
		find_cmd(data, cmds);
}

int	one_command(t_data *data)
{
	t_cmd	*cmds;
	int		status;

	cmds = (*data->cmd);
	signal(SIGQUIT, &sign_quit);
	g_glob.in_heredoc = 1;
	data->pid = fork();
	if (data->pid == 0)
	{
		if (!cmds->str[0])
			exit(0);
		one_command_bis(data, cmds);
	}
	else
	{
		waitpid(data->pid, &status, 0);
		data->exit_code = WEXITSTATUS(status);
	}
	signal(SIGQUIT, SIG_IGN);
	g_glob.in_heredoc = 0;
	return (data->exit_code);
}
