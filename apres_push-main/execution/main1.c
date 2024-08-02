/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:15:09 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/02 22:17:33 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run1_minishell(t_info *info, t_variable **my_env)
{
	int			check;
	t_static	*static_v;

	static_v = ft_static();
	check = parsing(info);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	free_d((*my_env)->env_exec);
	(*my_env)->env_exec = return_env(*my_env);
	if (!check && info->plist)
	{
		static_v->exit_status = 0;
		run_minishell(my_env, info, (*my_env)->env_exec);
	}
}

void	minishell_execut(t_info *info)
{
	while (info->head_f)
	{
		unlink(info->head_f->file_name);
		info->head_f = info->head_f->next;
	}
	free_list(info, 0);
	free(info->tmp_line);
}

t_static	*ft_static(void)
{
	static t_static	a;

	return (&a);
}

void	my_minishell(t_info *info, t_variable *my_env)
{
	t_static	*static_v;

	static_v = ft_static();
	static_v->fd0 = dup(0);
	static_v->fd1 = dup(1);
	while (1)
	{
		static_v->red = 0;
		static_v->error_red = 0;
		dup2(static_v->fd0, 0);
		dup2(static_v->fd1, 1);
		signals();
		init_info(my_env, info);
		run1_minishell(info, &my_env);
		minishell_execut(info);
	}
}
