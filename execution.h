/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongron <jeongron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:03:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/06 18:43:33 by jeongron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define FAIL 0
# define SUCCESS 1

// (1) env_var 구조체 만들기 
// (+) 환경변수 관련 구조체
typedef struct s_env_var
{
	char	**path;
	char	**env;
	char	**exp;
	int		env_cnt;
	int		exp_cnt;
	int		status;
}	t_env_var;

// set_env_var.c
int 	set_env_var(t_env_var *env_var, char **envp);
// sort_exp.c
void 	sort_exp(t_env_var *env_var);
// check_cmd.c
void	check_cmd(char **cmd, t_env_var *env_var);
// env.c
int		start_env(char **cmd, t_env_var *env_var);
void	print_env(t_env_var *env_var);
// pwd.c
int		start_pwd(char **cmd, t_env_var *env_var);
// export.c
int		start_export(char **cmd, t_env_var *env_var);
void 	print_exp(t_env_var *env_var);
void 	del_env(char *cmd, t_env_var *env_var);
void 	del_exp(char *cmd, t_env_var *env_var);
// unset.c
int		start_unset(char **cmd, t_env_var *env_var);
void	search_unset(char *cmd, t_env_var *env_var);
// echo.c
int		start_echo(char **cmd, t_env_var *env_var);
// exit.c
int		start_exit(char **cmd, t_env_var *env_var);

// utils.c
size_t	ft_strlen(const char *str);
int		ft_two_strlen(char **str);
char	*ft_strdup(const char *src);
char	*ft_exp_strdup(const char *src);
int		ft_strcmp(const char *s1, const char *s2);
void 	ft_free(char **str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
long long	ft_atoi(const char *str);

// split.c
char	**ft_split(char const *s, char c);

#endif