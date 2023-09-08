#include "execution.h"

int		change_dir(char *path)
{
	int		status;
	char	*tmp_path;

	status = 0;
	tmp_path = NULL;

	// path : (1)정상path , (2) $들어간 path
	if ()
	{

	}
	else
	{
		if (chdir(path) != 0)
		{
			printf("bash: cd: %s: No such file or directory\n", path);
			status = 1;
		}
	}
	return (status);
}

int		start_cd(char **cmd, t_env_var *env_var)
{
	int	cnt;
	int	status;
	int	home_flag;
	
	cnt = ft_two_strlen(cmd);
	status = 1;
	home_flag = check_dup(env_var->env, "HOME", 1);
	if (cnt >= 3)
		printf("bash: cd: too many arguments\n");
	else if (cnt == 1)
	{
		if (home_flag == 0)
			printf("bash: cd: HOME not set\n");
		else
			status = change_dir("$HOME");
	}
	else if (cnt == 2)
	{
		if (cmd[1] == '~')
		{
			if (home_flag == 0)
				status = change_dir(env_var->home);
			else
				status = change_dir("$HOME");
		}
		else
			status = change_dir(cmd[1]);
	}
	return (status);
}