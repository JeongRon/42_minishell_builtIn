/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:49:51 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/04 16:52:42 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		start_pwd(char **cmd, t_env_var *env_var)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		perror("GETCWD");
	printf("%s\n", pwd);
	free (pwd);
	return (0);
}
