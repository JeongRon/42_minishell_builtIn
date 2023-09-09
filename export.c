/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:56:17 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/09 17:16:10 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void print_exp(t_env_var *env_var)
{
	int	i;

	i = 0;
	while (env_var->exp[i])
	{
		printf("%s\n", env_var->exp[i]);
		i++;
	}
}

void add_exp(char *cmd, t_env_var *env_var)
{
	char 	**tmp;
	int		i;

	env_var->exp_cnt += 1;
	tmp = (char **)malloc(sizeof(char *) * (env_var->exp_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	i = -1;
	while (env_var->exp[++i])
	{
		tmp[i] = ft_strdup(env_var->exp[i]);
		if (!tmp[i])
			perror("MALLOC");
	}
	tmp[i] = ft_exp_strdup(cmd);
	tmp[i + 1] = NULL;
	ft_free(env_var->exp);
	env_var->exp = tmp;
	sort_exp(env_var);
}

void add_env(char *cmd, t_env_var *env_var)
{
	char	**tmp;
	int		i;

	env_var->env_cnt += 1;
	tmp = (char **)malloc(sizeof(char *) * (env_var->env_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	i = -1;
	while (env_var->env[++i])
	{
		tmp[i] = ft_strdup(env_var->env[i]);
		if (!tmp[i])
			perror("MALLOC");
	}
	tmp[i] = ft_strdup(cmd);
	tmp[i + 1] = NULL;
	ft_free(env_var->env);
	env_var->env = tmp;
}

int	find_equals_flag(char *cmd)
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

char *key_strdup(char *str)
{
	int		key_len;
	int		i;
	char 	*tmp;

	key_len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		key_len++;		
	}
	tmp = (char *)malloc(sizeof(char) * (key_len + 1));
	if (!tmp)
		perror("MALLOC");
	i = -1;
	while(++i < key_len)
		tmp[i] = str[i];
	tmp[i] = '\0';	
	return (tmp);
}

void del_env_key(int del_index, t_env_var *env_var)
{
	char	**tmp;
	int		x;
	int		y;

	env_var->env_cnt -= 1;
	tmp = (char **)malloc((sizeof(char *)) * (env_var->env_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	x = 0;
	y = 0;
	while (y < env_var->env_cnt)
	{
		if (x == del_index)
		{
			x++;
			continue;
		}
		tmp[y] = ft_strdup(env_var->env[x]);
		x++;
		y++;
	}
	tmp[y] = NULL;
	ft_free(env_var->env);
	env_var->env = tmp;
}

void del_env(char *cmd, t_env_var *env_var)
{
	char	*cmd_key;
	char	*env_key;
	int		i;

	cmd_key = key_strdup(cmd);
	i = -1;
	while (env_var->env[++i])
	{
		env_key = key_strdup(env_var->env[i]);
		if (ft_strcmp(cmd_key, env_key) == 0)
		{
			del_env_key(i, env_var);
			free(env_key);
			break ;
		}
		free(env_key);
	}
	free(cmd_key);
}

void del_exp_key(int del_index, t_env_var *env_var)
{
	char	**tmp;
	int		x;
	int		y;

	env_var->exp_cnt -= 1;
	tmp = (char **)malloc((sizeof(char *)) * (env_var->exp_cnt + 1));
	if (!tmp)
		perror("MALLOC");
	x = 0;
	y = 0;
	while (y < env_var->exp_cnt)
	{
		if (x == del_index)
		{
			x++;
			continue;
		}
		tmp[y] = ft_strdup(env_var->exp[x]);
		x++;
		y++;
	}
	tmp[y] = NULL;
	ft_free(env_var->exp);
	env_var->exp = tmp;
}

void del_exp(char *cmd, t_env_var *env_var)
{
	char	*cmd_key;
	char	*exp_key;
	int		i;

	cmd_key = key_strdup(cmd);
	i = -1;
	while (env_var->exp[++i])
	{
		exp_key = key_strdup(&env_var->exp[i][11]);
		if (ft_strcmp(cmd_key, exp_key) == 0)
		{
			del_exp_key(i, env_var);
			sort_exp(env_var);
			free(exp_key);
			break ;
		}
		free(exp_key);
	}
	free(cmd_key);
}

int	check_dup(char **arr, char *cmd, int flag)
{
	char	*cmd_key;
	char	*arr_key;
	int		dup_flag;
	int		i;

	cmd_key = key_strdup(cmd);
	dup_flag = 0;
	i = -1;
	while (arr[++i])
	{
		if (flag == 0)
			arr_key = key_strdup(&arr[i][11]);
		else
			arr_key = key_strdup(arr[i]);
		if (ft_strcmp(cmd_key, arr_key) == 0)
		{
			dup_flag = 1;
			free(arr_key);
			break ;
		}
		free(arr_key);
	}
	free(cmd_key);
	return (dup_flag);
}

void	search_export(char *cmd, t_env_var *env_var)
{
	int		equals_flag;
	int		env_dup_flag;
	int		exp_dup_flag;
	int		i;
	
	equals_flag = find_equals_flag(cmd);
	env_dup_flag = check_dup(env_var->env, cmd, 1);
	exp_dup_flag = check_dup(env_var->exp, cmd, 0);
	printf("-------------------------------\n");
	printf("equals_flag: %d\n", equals_flag);
	printf("env_dup_flag: %d\n", env_dup_flag);
	printf("exp_dup_flag: %d\n", exp_dup_flag);
	printf("-------------------------------\n");
	if (equals_flag == 0 && env_dup_flag == 0 && exp_dup_flag == 0)
		add_exp(cmd, env_var);
	else if (equals_flag == 1)
	{
		if (env_dup_flag == 0 && exp_dup_flag == 0)
		{
			add_env(cmd, env_var);
			add_exp(cmd, env_var);
		}
		else if (env_dup_flag == 0 && exp_dup_flag == 1)
		{
			add_env(cmd, env_var);
			del_exp(cmd, env_var);
			add_exp(cmd, env_var);
		}
		else if (env_dup_flag == 1)
		{
			del_env(cmd, env_var);
			del_exp(cmd, env_var);
			add_env(cmd, env_var);
			add_exp(cmd, env_var);
		}
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
				search_export(cmd[i], env_var);
		}
	}
	else
		print_exp(env_var);
	return (status);
}
