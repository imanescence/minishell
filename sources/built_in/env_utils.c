/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:27:48 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/08/28 14:04:21 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isalnum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
	{
		if (((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z')
				&& (str[i] < '0' || str[i] > '9')) && str[i] != ' ')
			return (-1);
		i++;
	}
	return (0);
}

int	check_error(char *var, t_data *data)
{
	if (ft_isalnum(var) == -1)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(" :not a valid identifier\n", 2);
		return (data->exit_code = 1);
	}
	return (data->exit_code = 0);
}

char	*ft_strdup_bis(const char *s)
{
	size_t		len;
	char		*cpy;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		exit (1);
	while (i < len)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else
		{
			cpy[j] = s[i];
			i++;
			j++;
		}
	}
	cpy[j] = 0;
	return (cpy);
}

int	existing_var_check(char *var_env, char *new_str, char **new_ar, int i)
{
	if (!new_str)
		return (-1);
	if (my_strncmp(var_env, new_str, char_check(0, '=', var_env)) == 0)
	{
		new_ar[i] = ft_strdup_bis(new_str);
		return (0);
	}
	return (-1);
}
