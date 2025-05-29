/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:31:54 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/30 13:35:39 by iait-ouf         ###   ########.fr       */
/*   Updated: 2024/08/26 14:55:12 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quot_change(int i, int quot, t_data *data)
{
	if (data->echostr[i] == '\'')
	{
		if (quot == 1)
			quot = 0;
		else if (quot == 0)
			quot = 1;
	}
	return (quot);
}

int	dquot_change(int i, int dquot, t_data *data)
{
	if (data->echostr[i] == '\"')
	{
		if (dquot == 1)
			dquot = 0;
		else if (dquot == 0)
			dquot = 1;
	}
	return (dquot);
}

int	echo_write(int i, t_data *data, int quot, int dquot)
{
	if (data->echostr[i] != '\'' && data->echostr[i] \
		!= '\"' && data->echostr[i] != ' ' && data->echostr[i] != '\t')
		write(data->out_fd, &(data->echostr[i]), 1);
	else if (data->echostr[i] == ' ' || data->echostr[i] == '\t')
	{
		write(data->out_fd, &(data->echostr[i]), 1);
		if (quot == 0 && dquot == 0)
		{
			while (data->echostr[i + 1] && (data->echostr[i + 1] == ' '
					|| data->echostr[i + 1] == '\t'))
				i++;
		}
	}
	return (i + 1);
}

int	write_n(int n, t_data *data)
{
	if (n == 0)
		write(data->out_fd, "\n", 1);
	return (0);
}

int	exe_echo(t_data *data)
{
	int	i;
	int	n;
	int	quot;
	int	dquot;

	n = 0;
	i = 5;
	quot = 0;
	dquot = 0;
	if (ft_strncmp((*data->cmd)->str[1], "-n", 2) == 0)
	{
		n = 1;
		i += 3;
		if ((*data->cmd)->str[2] == NULL)
			return (data->exit_code = 0);
	}
	while ((*data->cmd)->str[1] && data->echostr[i] \
				&& ((quot != 0 || dquot != 0) || (data->echostr[i] != '<' && \
					data->echostr[i] != '>')))
	{
		quot = quot_change(i, quot, data);
		dquot = dquot_change(i, dquot, data);
		i = echo_write(i, data, quot, dquot);
	}
	return (write_n(n, data));
}
