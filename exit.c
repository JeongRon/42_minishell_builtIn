/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:09:21 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/09 18:13:17 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// cmd 가 숫자면 1리턴, 아니면 0리턴
int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

// long long 범위 넘으면 리턴 1, 범위 안이면 리턴 0
int	is_out_of_range(char *cmd, int ch_flag)
{
	int			ch_len;
	long long	res;

	ch_len = 0;
	if (ch_flag)
		ch_len = 1;
	if (ft_strlen(cmd) >= ch_len + 20)
		return (1);
	else if (ft_strlen(cmd) == ch_len + 19)
	{
		if (ch_flag == 0)
			res = ft_strcmp(cmd, "9223372036854775807");
		else if (ch_flag == 1)
			res = ft_strcmp(&cmd[1], "9223372036854775807");
		else if (ch_flag == 2)
			res = ft_strcmp(&cmd[1], "9223372036854775808");
		if (res > 0)
			return (1);
	}
	return (0);
}

// atoi 문자->숫자로 변환해서 반환
int	get_exit_status(char *cmd)
{
	int			status;
	int			ch_flag;
	long long	num;

	status = 0;
	ch_flag = 0;
	if (cmd[0] == '+')
		ch_flag = 1;
	else if (cmd[0] == '-')
		ch_flag = 2;
	if (is_out_of_range(cmd, ch_flag) == 1)
		status = 256;
	else
	{
		num = ft_atoi(cmd);
		status = num % 256;
		if (ch_flag == 2)
		{
			status = status + 256;
			if (status == 256)
				status = 0;
		}
	}
	return (status);
}

int	print_exit_code(int e, char **cmd, t_env_var *env_var)
{
	int	status;

	status = e;
	printf("exit\n");
	if (status == 1)
		printf("bash: exit: too many arguments\n");
	else if (status == 2)
		printf("bash: exit: %s: numeric argument required\n", cmd[1]);
	else if (status == -1)
	{
		status = get_exit_status(cmd[1]);
		if (status == 256)
		{
			printf("bash: exit: %s: numeric argument required\n", cmd[1]);
			status = 2;
		}
	}
	return (status);
}

int	start_exit(char **cmd, t_env_var *env_var)
{
	int	cnt;

	cnt = ft_two_strlen(cmd);
	if (cnt == 1)
		return (print_exit_code(0, cmd, env_var));
	else
	{
		if (check_num(cmd[1]) == SUCCESS)
		{
			if (cnt == 2)
				return (print_exit_code(-1, cmd, env_var));
			else
				return (print_exit_code(1, cmd, env_var));
		}
		else
			return (print_exit_code(2, cmd, env_var));
	}
}
