/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:32:37 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/30 13:36:06 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// VERIFIER LES REDIRECTIONS ICIIIIIIIIIIII

char	**ar_dup_or_raised(t_data *data, char	**original, char *new_str)
{
	int		i;
	char	**new_ar;

	i = 0;
	new_ar = (char **) malloc ((data->nb_var + 2) * sizeof (char *));
	if (!new_ar)
		exit(1);
	while (i < data->nb_var - 1 && original[i])
	{
		if (existing_var_check(original[i],
				new_str, new_ar, i) == 0)
			i++;
		new_ar[i] = ft_strdup_bis(original[i]);
		i++;
	}
	if (new_str != NULL)
	{
		new_ar[i] = ft_strdup_bis(new_str);
		i++;
	}
	new_ar[i] = NULL;
	return (new_ar);
}

void	var_adder(t_data *data, char *str_to_add)
{
	data->env_tmp = ar_dup_or_raised(data, data->env, str_to_add);
	free_char_ar(data->env);
	data->env = ar_dup_or_raised(data, data->env_tmp, NULL);
	free_char_ar(data->env_tmp);
}

int	ft_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			return (1);
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (0);
}

int	var_handler(t_data *data, int j)
{
	int	k;

	k = 0;
	if (check_error((*data->cmd)->str[j], data) == 1)
		return (data->exit_code = 1);
	while (data->env && data->env[k])
	{
		if (my_strncmp((*data->cmd)->str[j], data->env[k],
				my_strlen((*data->cmd)->str[j])) == 0)
			return (data->exit_code);
		k++;
	}
	var_adder(data, (*data->cmd)->str[j]);
	return (data->exit_code);
}

int	exe_export(t_data *data)
{
	int	j;

	j = 1;
	if ((*data->cmd)->str[1] && (ft_strncmp((*data->cmd)->str[1], "=", 2) == 0
			|| ft_digit((*data->cmd)->str[1]) == 1))
	{
		write(2, "minishell: export: ", 19);
		write(2, (*data->cmd)->str[1],
			ft_strlen((*data->cmd)->str[1]));
		write(2, " not a valid identifier\n", 24);
		return (data->exit_code = 1);
	}
	data->nb_input = count_str(data) - 1;
	if (data->nb_input > 0)
	{
		while (data->nb_input > 0)
		{
			var_handler(data, j);
			j++;
			data->nb_input--;
		}
	}
	else
		export_display(data);
	return (data->exit_code);
}
