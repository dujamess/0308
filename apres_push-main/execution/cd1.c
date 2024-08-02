/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:27:22 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/02 21:34:14 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_variable	*check_variable(t_variable *my_env, char *variable, t_pwd *var)
{
	int	i;

	(void)var;
	i = 0;
	while (my_env[i].nom)
	{
		if (ft_strcmp1(my_env[i].nom, variable) == 0)
			return (&my_env[i]);
		i++;
	}
	return (NULL);
}

int	check_home(t_variable *my_env, t_variable *path, t_pwd *var)
{
	int			t;
	t_static	*static_v;

	static_v = ft_static();
	path = check_variable(my_env, "HOME", var);
	if (path == NULL)
	{
		printf("variable HOME non trouver dans votre env\n");
		static_v->exit_status = 1;
		return (0);
	}
	t = chdir(path->valeur);
	if (t == -1)
	{
		static_v->exit_status = 1;
		return (0);
	}
	return (1);
}

int	check_pwd(t_variable *my_env, t_variable *pwd_env, char *pwd, t_pwd *var)
{
	pwd_env = check_variable(my_env, "PWD", var);
	if (pwd_env == NULL)
		return (0);
	if (pwd_env)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (0);
		free(pwd_env->valeur);
		pwd_env->valeur = pwd;
	}
	return (1);
}

int	check_oldpwd(t_variable *pwd_env,
	t_variable *my_env, char *oldpwd, t_pwd *var)
{
	pwd_env = check_variable(my_env, "OLDPWD", var);
	if (pwd_env == NULL)
		return (0);
	if (pwd_env)
	{
		if (!oldpwd)
			return (0);
		free(pwd_env->valeur);
		pwd_env->valeur = oldpwd;
	}
	return (1);
}
