/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:33:03 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/29 16:09:15 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ar_dup_and_trimed(t_data *data, char	**original, int i_2_avoid)
{
	int		i;
	int		j;
	char	**new_ar;

	i = 0;
	j = 0;
	new_ar = (char **) malloc ((data->nb_var + 1) * sizeof (char *));
	if (!new_ar)
		exit(1);
	while (i < data->nb_var - 1 && original[i])
	{
		if (i == i_2_avoid)
			i++;
		new_ar[j] = ft_strdup(original[i]);
		i++;
		j++;
	}
	new_ar[j] = NULL;
	return (new_ar);
}

void	var_trimer(t_data *data, int i_2_avoid)
{
	data->env_tmp = NULL;
	data->env_tmp = ar_dup_and_trimed(data, data->env, i_2_avoid);
	free_char_ar(data->env);
	data->env = NULL;
	data->env = ar_dup_or_raised(data, data->env_tmp, NULL);
	free_char_ar(data->env_tmp);
	data->env_tmp = NULL;
}

int	error_unset(t_data *data, int i)
{
	printf("minishell: unset: `%s': not a valid identifier\n",
		(*data->cmd)->str[i]);
	return (data->exit_code = 1);
}

int	mini_pars(t_data *data, int i)
{
	if (ft_isalpha((*data->cmd)->str[i][0]) == 0)
		return (error_unset(data, i));
	if (ft_str_isalnum((*data->cmd)->str[i]) == 1)
		return (error_unset(data, i));
	return (0);
}

int	exe_unset(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while ((*data->cmd)->str && (*data->cmd)->str[i])
	{
		if (mini_pars(data, i) == 1)
			i++;
		while (data->env && data->env[j])
		{
			if (ft_strncmp((*data->cmd)->str[i], data->env[j],
					char_check(0, '=', data->env[j])) == 0)
			{
				data->nb_var--;
				var_trimer(data, j);
			}
			j++;
		}
		j = 0;
		if ((*data->cmd)->str[i] != NULL)
			i++;
	}
	return (data->exit_code);
}
