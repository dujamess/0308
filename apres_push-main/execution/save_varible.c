/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_varible.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:55:44 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/02 22:04:58 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_builtin_redirection(t_info	*info, t_variable *my_env, int *ptr)
{
	int		count;

	count = *ptr;
	run_buil_red(my_env, info, &count);
}

int	number_commande(t_info info)
{
	int	count;

	count = 0;
	if (info.plist && info.plist->parts)
	{
		while (info.plist->parts[count])
			count++;
	}
	return (count);
}

void	env_reserver1(t_variable *env_nu)
{
	env_nu[3].nom = ft_strdup1("OLDPWD");
	env_nu[3].valeur = ft_strdup1("");
	env_nu[3].flag_print = 1;
	env_nu[3].flag_ega = 0;
	env_nu[3].env_join = NULL;
	env_nu[4].nom = NULL;
	env_nu[4].valeur = NULL;
	env_nu[4].env_join = NULL;
}

t_variable	*env_reserver(t_variable *env_nu)
{
	char	*str;

	env_nu = malloc(sizeof(t_variable) * 5);
	env_nu[0].nom = ft_strdup1("PWD");
	env_nu[0].valeur = getcwd(NULL, 0);
	env_nu[0].flag_print = 0;
	str = ft_strjoin1(env_nu[0].nom, "=");
	env_nu[0].env_join = ft_strjoin1(str, env_nu[0].valeur);
	free(str);
	env_nu[1].nom = ft_strdup1("SHLVL");
	env_nu[1].valeur = ft_strdup1("0");
	env_nu[1].flag_print = 0;
	str = ft_strjoin1(env_nu[1].nom, "=");
	env_nu[1].env_join = ft_strjoin1(str, env_nu[1].valeur);
	free(str);
	env_nu[2].nom = ft_strdup1("_");
	env_nu[2].valeur = ft_strdup1("/usr/bin/env");
	env_nu[2].flag_print = 0;
	str = ft_strjoin1(env_nu[2].nom, "=");
	env_nu[2].env_join = ft_strjoin1(str, env_nu[2].valeur);
	free(str);
	env_reserver1(env_nu);
	return (env_nu);
}

void	child_ps_1_commande(t_info *info, char **en, t_variable *env, int *fd)
{
	t_static	*static_v;

	static_v = ft_static();
	cherch_output(info);
	if (static_v->error_red == 1)
		exit(1);
	dup_input_1(info, fd);
	if (info->plist->parts[0])
	{
		if (check_is_builtin(info) == 1)
		{
			env = exec_builtin(env, info, info->lst_size);
			static_v->g_env = env;
			exit(static_v->exit_status);
		}
		else if (info->plist->parts[0])
			check_commande(info, en);
	}
	else
	{
		static_v->exit_status = 0;
		exit(static_v->exit_status);
	}
}
