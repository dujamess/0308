/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_dollar1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:25:30 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/02 21:50:50 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	b_dollar_lenght1(t_info *info, int *count)
{
	while (check_reds(info->line[info->count + *count])
		|| check_escape(info->line[info->count + *count]))
	{
		(*count)++;
		set_val(info->line[info->count + *count], info);
	}
	if (info->line[info->count + *count] == '$' && !info->quotes)
	{
		while (info->line[info->count + *count]
			&& !check_escape(info->line[info->count + *count]))
		{
			(*count)++;
			set_val(info->line[info->count + *count], info);
		}
	}
}

int	b_dollar_lenght(t_info *info)
{
	int	i;
	int	count;

	i = info->count;
	count = 0;
	while (info->line[i + count] && info->line[i + count] != '$')
	{
		set_val(info->line[i + count], info);
		if (check_reds(info->line[i + count]))
			b_dollar_lenght1(info, &count);
		if (info->line[i + count] && info->line[i + count] != '$')
			count++;
	}
	return (count);
}

void	b_dollar_copy(t_info *info, char *str)
{
	int	i;

	i = 0;
	while (info->line[info->count] && info->line[info->count] != '$')
	{
		if (check_reds(info->line[info->count]))
		{
			while (check_reds(info->line[info->count])
				|| check_escape(info->line[info->count]))
				str[i++] = info->line[info->count++];
			if (info->line[info->count] == '$' && !info->quotes)
			{
				while (info->line[info->count]
					&& !check_escape(info->line[info->count]))
					str[i++] = info->line[info->count++];
			}
		}
		if (info->pipe && !check_escape(info->line[info->count]))
			info->pipe = 0;
		if (info->line[info->count] == '|')
			info->pipe = 1;
		if (info->line[info->count] && info->line[info->count] != '$')
			str[i++] = info->line[info->count++];
	}
	str[i] = '\0';
}

char	*b_dollar(t_info *info)
{
	int		len;
	int		i;
	char	*str;
	char	*ss;
	int		tmp;

	i = 0;
	info->pipe = 0;
	tmp = info->quotes;
	len = heredoc_ex_l(info->line + info->count, &i, info);
	if (info->quotes)
		set_val(info->quotes, info);
	if (i)
	{
		ss = ft_substr(info->line + info->count, 0, len, info);
		info->count += len;
		return (ss);
	}
	info->quotes = tmp;
	len = b_dollar_lenght(info);
	str = allocate(info, len + 1);
	if (!str)
		free_list(info, 1);
	b_dollar_copy(info, str);
	return (str);
}

char	*after_d_cpy(t_info *info, char *str, int i)
{
	str = allocate(info, i + 1);
	if (!str)
		free_list(info, 1);
	i = 0;
	while (info->line[info->count] && !alpha_n(info->line[info->count])
		&& dollar(info->line[info->count], info))
		str[i++] = info->line[info->count++];
	str[i] = '\0';
	return (str);
}
