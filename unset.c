
#include "execution.h"

void	search_unset(char *cmd, t_env_var *env_var)
{
	del_env(cmd, env_var);
	del_exp(cmd, env_var);
}

int		start_unset(char **cmd, t_env_var *env_var)
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
				printf("bash: unset: `%s': not a valid identifier\n", cmd[i]);
				status = 1;
			}
			else
				search_unset(cmd[i], env_var);
		}
	}
	return (status);
}
