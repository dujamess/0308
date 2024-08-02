/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:24:15 by mmondad           #+#    #+#             */
/*   Updated: 2024/08/02 21:50:37 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_dollar(t_info *info)
{
	if (info->line[info->count] == '$' && info->line[info->count + 1] == '$')
	{
		info->count += 2;
		return ("$$");
	}
	return (NULL);
}

int	dollar(char c, t_info *info)
{
	if (c == '$' && !info->flag)
		return (1);
	else if (c != '$')
		info->flag = 1;
	else if (c == '$' && info->flag)
	{
		info->flag = 0;
		return (0);
	}
	return (1);
}

char	*fake_var(t_info *info, int i)
{
	char	*dlr;

	info->flag = 0;
	dlr = append_dollar(info);
	if (dlr)
		return (dlr);
	if ((info->line[i] == '\'' || info->line[i] == '\"') && !info->quotes)
	{
		info->count++;
		return (NULL);
	}
	return (after_d(info, NULL));
}

char	*after_d(t_info *info, char *str)
{
	int			i;
	t_static	*static_v;

	static_v = ft_static();
	i = 0;
	if (info->line[info->count] && info->line[info->count + 1] == '?'
		&& info->quotes != '\'')
	{
		info->count += 2;
		return (ft_itoa(static_v->exit_status, info));
	}
	while (info->line[info->count + i] && !alpha_n(info->line[info->count + i])
		&& dollar(info->line[info->count + i], info))
	{
		set_val(info->line[info->count + i], info);
		i++;
	}
	info->flag = 0;
	return (after_d_cpy(info, str, i));
}
