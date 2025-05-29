/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:03:33 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/08/29 15:22:55 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_special_cases(t_data *struc, char **env, int i)
{
	if (ft_strncmp("PATH=", env[i], 5) == 0)
	{
		struc->env[i] = ft_strdup(env[i]);
		return (1);
	}
	if (ft_strncmp("OLDPWD=", env[i], 7) == 0)
	{
		struc->env[i] = ft_strdup("OLDPWD");
		return (1);
	}
	if (ft_strncmp("USER=", env[i], 5) == 0)
	{
		struc->user = ft_substr(env[i],
				char_check(0, '=', env[i]), ft_strlen(env[i]) - 5);
		return (0);
	}
	return (0);
}

t_data	*init_env(t_data *struc, char **env, t_cmd **cmd)
{
	int	i;

	i = 0;
	struc->nb_var = 35;
	struc->shlvl = 2;
	struc->out_fd = STDOUT_FILENO;
	struc->env = (char **)malloc(struc->nb_var * sizeof(char *));
	if (!struc->env)
		exit(EXIT_FAILURE);
	while (i < struc->nb_var - 1 && env[i])
	{
		if (env_special_cases(struc, env, i) == 1)
			i++;
		struc->env[i] = ft_strdup(env[i]);
		i++;
	}
	struc->cmd = cmd;
	struc->env[i] = NULL;
	return (struc);
}
