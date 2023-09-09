/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:02:40 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/09 18:07:11 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_echo(char **cmd, int opt, int index)
{
	int	last_index;

	last_index = ft_two_strlen(cmd) - 1;
	while (cmd[index])
	{
		printf("%s", cmd[index]);
		if (last_index != index)
			printf(" ");
		index++;
	}
	if (opt == 0)
		printf("\n");
}

// -n 옵션이면 1 리턴, -n 옵션 아니면 0리턴
int	search_option(char *cmd)
{
	int	i;
	int	return_flag;

	i = 1;
	return_flag = 0;
	if (ft_strlen(cmd) < 2)
		return (return_flag);
	if (cmd[0] == '-' && cmd[1] == 'n')
	{
		return_flag = 1;
		while (cmd[++i])
		{
			if (cmd[i] == 'n')
				continue ;
			else
			{
				return_flag = 0;
				break ;
			}
		}
		return (return_flag);
	}
	return (return_flag);
}

// 해당 cmd 에서 -n 옵션 확인 + echo 시작 인덱스 값 가져오기
void	search_echo_flag(char **cmd, int *opt, int *start)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (*start == 0)
		{
			if (search_option(cmd[i]) == 0)
				*start = i;
			else
				*opt += 1;
		}
		else
			return ;
	}
}

int	start_echo(char **cmd, t_env_var *env_var)
{
	int		option_flag;
	int		start_flag;
	int		status;
	char	**echo_arr;

	option_flag = 0;
	start_flag = 0;
	status = 0;
	search_echo_flag(cmd, &option_flag, &start_flag);
	if (start_flag == 0)
	{
		if (option_flag == 0)
			printf("\n");
	}
	else
		print_echo(cmd, option_flag, start_flag);
	return (status);
}
