/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:36:35 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/30 13:32:11 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*red_choice(char *str, char *temp, int num_red)
{
	if (num_red == 0)
	{
		free(temp);
		return (str);
	}
	else
	{
		free(str);
		return (temp);
	}
}

char	*red_space_bis(int num_red, char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_kalloc (ft_strlen(str) + 1 + (2 * num_red) + 2, sizeof(char));
	while (str[i])
	{
		while (str[i] && str[i] != '<' && str[i] != '>')
		{
			temp[j] = str[i];
			i++;
			j++;
		}
		temp[j++] = ' ';
		while (str[i] && (str[i] == '<' || str[i] == '>'))
		{
			temp[j] = str[i++];
			j++;
		}
		temp[j++] = ' ';
	}
	return (red_choice(str, temp, num_red));
}

char	*red_space(char *str)
{
	int	i;
	int	num_red;

	i = 0;
	num_red = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' && (i != 0 && str[i - 1] != '<') \
			&& (str[i + 1] == 0 || str[i + 1] != '<'))
			num_red++;
		if (str[i] == '>' && (i != 0 && str[i - 1] != '>') \
			&& (str[i + 1] == 0 || str[i + 1] != '>'))
			num_red++;
		if (str[i] == '>' && (i != 0 && str[i - 1] != '>') \
			&& (str[i + 1] && str[i + 1] == '>'))
			num_red++;
		if (str[i] == '<' && (i != 0 && str[i - 1] != '<') \
			&& (str[i + 1] && str[i + 1] == '<'))
			num_red++;
		i++;
	}
	return (red_space_bis(num_red, str));
}

char	*str_get(t_data *data)
{
	char	*str_temp;

	str_temp = rl_gets("minishell :  ");
	str_temp = red_space(str_temp);
	str_temp = hextend(str_temp, data);
	if (str_temp)
		data->echostr = ft_strdup(str_temp);
	return (str_temp);
}

int	launch_mini(char **str, t_data *data, t_cmd **cmd, t_list **lexer )
{
	char	*str_temp;

	str_temp = str_get(data);
	if (str_temp != 0)
	{
		if (ft_strncmp(str_temp, "minishell", 9) == 0 || \
			ft_strncmp(str_temp, "./minishell", 11) == 0)
			shlvl_updater(data);
		str = ft_splite_mutan(str_temp, data);
		if (str != 0)
		{
			get_lexer(lexer, str);
			if (get_cmds(lexer, cmd) == 1)
				return (free_all(lexer, cmd, str));
			if ((*cmd)->redirection && (*cmd)->redirection->token == 6)
				error_file();
			else
				execut(cmd, data);
			free_strs(str);
			(*cmd)->fd_herdoc = -1;
		}
		return (1);
	}
	return (0);
}
