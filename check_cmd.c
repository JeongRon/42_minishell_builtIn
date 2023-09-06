/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:21:25 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/06 19:45:43 by jeongron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_cmd(char **cmd, t_env_var *env_var)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		env_var->status = start_env(cmd, env_var);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		env_var->status = start_pwd(cmd, env_var);
	else if (ft_strcmp(cmd[0], "export") == 0)
		env_var->status = start_export(cmd, env_var);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		env_var->status = start_unset(cmd, env_var);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		env_var->status = start_echo(cmd, env_var);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		env_var->status = start_exit(cmd, env_var);
		//
		printf("satus value: %d\n", env_var->status);
	}
}
