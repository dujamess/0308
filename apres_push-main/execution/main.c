/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:57:53 by mmondad           #+#    #+#             */
/*   Updated: 2024/08/02 23:54:00 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_commande_red(t_info *info,
		t_variable **my_env, int count, t_static	*static_v)
{
	info->fd0 = 0;
	info->fd1 = 1;
	static_v->red = 1;
	command_builtin_redirection(info, *my_env, &count);
}

void	run_minishell(t_variable **my_env, t_info *info,
		char **env_exec)
{
	int			count;
	t_file		*head ;
	t_static	*static_v;

	static_v = ft_static();
	head = NULL;
	open_herdoc_in_main(*info, &head);
	info->head_f = head;
	signal(SIGINT, handel);
	count = number_commande(*info);
	split_path(*my_env, &info->path);
	static_v->g_env = *my_env;
	if ((check_is_builtin(info) == 1) && (info->plist->next == NULL))
	{
		save_pwd(info);
		if (info->plist->reds)
			run_commande_red(info, my_env, count, static_v);
		else
			run_builtin_final(my_env, info, count);
	}
	else if (!static_v->exit_status)
		execution_cmd(*my_env, info, env_exec);
}

int	main(int argc, char **argv, char **penv)
{
	t_info		info;
	t_variable	*my_env;
	t_variable	*pwd_env;
	t_static	*static_v;

	(void)argc;
	(void)argv;
	static_v = ft_static();
	my_env = NULL;
	pwd_env = NULL;
	init_data(&info);
	my_env = set_env(my_env, penv);
	my_env->env_exec = NULL;
	info.path = (t_path){};
	info.path.var_path = NULL;
	info.var = malloc(sizeof(t_pwd));
	if (!info.var)
		return (1);
	info.var->pwd = NULL;
	augment_level_shlvl(my_env, &info);
	static_v->info = &info;
	static_v->g_env = my_env;
	my_minishell(&info, my_env);
}
