/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:05:15 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/06 19:51:56 by jeongron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int ac, char **av, char **envp)
{
	t_env_var	env_var;

	// env_var 채우기
	if (set_env_var(&env_var, envp) == 0)
		return (0);
	// 파싱 임시 처리
	char *cmd[] = {"echo", "-n", NULL};
	// 파이프 체크
	// 명령어 처리
	check_cmd(cmd, &env_var);
	// <====================TEST=====================>
	// printf("-------------exp-------------------\n");
	// print_exp(&env_var);
	// printf("-------------env----------------\n");
	// print_env(&env_var);
	return (0);
}

// 실행 파트 만들기 