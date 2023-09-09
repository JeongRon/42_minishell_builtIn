/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:49:51 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/09 17:21:19 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	print_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		perror("GETCWD");
	printf("%s\n", pwd);
	free (pwd);
	return (0);
}

char	*get_pwd_value(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		perror("GETCWD");
	return (pwd);
}
