# include "minishell.h"

void	find_pwd(t_builtin *builtin, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
			builtin->pwd = envp[i] + 5;
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
			builtin->oldpwd = envp[i] + 8;
		i++;
	}
}
