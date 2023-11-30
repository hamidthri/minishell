/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:18 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/30 18:33:05 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_builtin
{
	char	*pwd;
	char	*oldpwd;
	char		**env;
}	t_builtin;

void	history_add(char *cmd);
void	find_pwd(t_builtin *builtin);
void	get_env(char **envp);
int		cd_custom(t_builtin	*bltin, char *cmd_opt);
int		find_dir(t_builtin *bltin, char *s);
char	**env_dup(char	**envp);

#endif
