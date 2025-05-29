/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:08:55 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/08/30 13:31:40 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_and_null(char *str)
{
	free(str);
	str = NULL;
}

char	*path_builder(t_data *data, t_cmd *cmds)
{
	char	*cmd;
	int		i;
	int		j;
	int		n;

	i = 0;
	while (ft_strncmp(data->env[i], "PATH=", 5) != 0)
		i++;
	j = (char_check(0, '=', data->env[i]) + 1);
	n = j;
	while (data->env[i][j++])
	{
		if (char_check(data->env[i][j], ':', NULL) != -1)
		{
			data->env[i][j] = '/';
			j++;
			cmd = ft_substr(data->env[i], n, j - n);
			cmd = ft_strnjoin(cmd, cmds->str[0]);
			if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
				return (cmd);
			free_and_null(cmd);
			n = j;
		}
	}
	return (NULL);
}

int	find_cmd(t_data *data, t_cmd *cmds)
{
	char	*cmd;

	cmd = NULL;
	if (access((*data->cmd)->str[0], F_OK) == 0 && \
			access((*data->cmd)->str[0], X_OK) == 0)
	{
		if (cmds->redirection)
			redirection_check(data, cmds);
		execve((*data->cmd)->str[0], (*data->cmd)->str, data->env);
	}
	if (existing_path_check(data) == 0)
		cmd = path_builder(data, cmds);
	if (cmd != NULL)
	{
		if (cmds->redirection)
			redirection_check(data, cmds);
		execve(cmd, cmds->str, data->env);
	}
	else if (ft_strncmp((*data->cmd)->str[0], "./", 2) == 0)
		minishell_case(data, cmds);
	else if (ft_strncmp((*data->cmd)->str[0], "minishell", 9) == 0)
		minishell_case(data, cmds);
	ft_printf("%s: minishell: command not found\n", (*data->cmd)->str[0]);
	exit(127);
}
