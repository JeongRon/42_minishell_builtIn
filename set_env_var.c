/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:06:30 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/09 18:19:52 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	allocate_env_exp(t_env_var *env_var, int cnt)
{
	env_var->env = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!env_var->env)
		return (FAIL);
	env_var->exp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!env_var->exp)
		return (FAIL);
	return (SUCCESS);
}

static int	check_path(char *envp)
{
	if (envp[0] == 'P' && envp[1] == 'A'
		&& envp[2] == 'T' && envp[3] == 'H'
		&& envp[4] == '=')
		return (SUCCESS);
	return (FAIL);
}

int	check_home(char *envp)
{
	if (envp[0] == 'H' && envp[1] == 'O'
		&& envp[2] == 'M' && envp[3] == 'E'
		&& envp[4] == '=')
		return (SUCCESS);
	return (FAIL);
}

static int	fill_env_exp(t_env_var *env_var, char **envp, int i)
{
	env_var->env[i] = ft_strdup(envp[i]);
	if (!env_var->env[i])
		return (FAIL);
	env_var->exp[i] = ft_exp_strdup(envp[i]);
	if (!env_var->exp[i])
		return (FAIL);
	if (check_path(envp[i]))
	{
		env_var->path = ft_split(&envp[i][5], ':');
		if (!env_var->path)
			return (FAIL);
	}
	if (check_home(envp[i]))
	{
		env_var->home = ft_strdup(&envp[i][5]);
		if (!env_var->home)
			return (FAIL);
	}
	return (SUCCESS);
}

int	set_env_var(t_env_var *env_var, char **envp)
{
	int	i;
	int	env_cnt;

	env_cnt = 0;
	while (envp[env_cnt])
		env_cnt++;
	if (allocate_env_exp(env_var, env_cnt) == FAIL)
		perror("MALLOC");
	i = -1;
	while (++i < env_cnt)
		if (fill_env_exp(env_var, envp, i) == FAIL)
			perror("MALLOC");
	env_var->env[i] = NULL;
	env_var->exp[i] = NULL;
	env_var->env_cnt = env_cnt;
	env_var->exp_cnt = env_cnt;
	env_var->status = 0;
	sort_exp(env_var);
	add_exp("OLDPWD", env_var);
	return (1);
}
