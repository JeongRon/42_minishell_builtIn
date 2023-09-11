/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:56:17 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/11 13:54:56 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_exp(t_env_var *env_var)
{
	int	i;

	i = 0;
	while (env_var->exp[i])
	{
		printf("%s\n", env_var->exp[i]);
		i++;
	}
}

static int	check_equals_flag(char *cmd)
{
	int		flag;
	int		i;

	flag = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '=')
		{
			flag = 1;
			break ;
		}
	}
	return (flag);
}

static void	search_export(char *cmd, t_env_var *env_var, int equals_flag)
{
	int		env_dup_flag;
	int		exp_dup_flag;

	env_dup_flag = check_duplicate(env_var->env, cmd, 1);
	exp_dup_flag = check_duplicate(env_var->exp, cmd, 0);
	if (equals_flag == 0 && env_dup_flag == 0 && exp_dup_flag == 0)
		add_exp(cmd, env_var);
	else if (equals_flag == 1 && env_dup_flag == 0 && exp_dup_flag == 0)
	{
		add_env(cmd, env_var);
		add_exp(cmd, env_var);
	}
	else if (equals_flag == 1 && env_dup_flag == 0 && exp_dup_flag == 1)
	{
		add_env(cmd, env_var);
		del_exp(cmd, env_var);
		add_exp(cmd, env_var);
	}
	else if (equals_flag == 1 && env_dup_flag == 1)
	{
		del_env(cmd, env_var);
		del_exp(cmd, env_var);
		add_env(cmd, env_var);
		add_exp(cmd, env_var);
	}
}

int	start_export(char **cmd, t_env_var *env_var)
{
	int	cnt;
	int	status;
	int	i;

	cnt = ft_two_strlen(cmd) - 1;
	status = 0;
	i = 0;
	if (cnt >= 1)
	{
		while (cmd[++i])
		{
			if (!((65 <= cmd[i][0] && cmd[i][0] <= 90) || cmd[i][0] == 95
				|| (97 <= cmd[i][0] && cmd[i][0] <= 122)))
			{
				printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
				status = 1;
			}
			else
				search_export(cmd[i], env_var, check_equals_flag(cmd[i]));
		}
	}
	else
		print_exp(env_var);
	return (status);
}
