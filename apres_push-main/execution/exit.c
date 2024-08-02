/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:50:13 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/02 21:33:54 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit1(char *c)
{
	int	i;

	i = 0;
	if (c && (c[i] == '+' || c[i] == '-'))
		i++;
	while (c && c[i] && (c[i] >= '0' && c[i] <= '9'))
		i++;
	if (c && c[i] == '\0')
		return (1);
	else
		return (0);
}

void	exit_multiple(char **av, int ac)
{
	int			i;
	t_static	*static_v;

	static_v = ft_static();
	i = 1;
	while (av[i])
	{
		if (ft_isdigit1(av[i]) == 0)
			break ;
		i++;
	}
	if (ac == i || (ft_isdigit1(av[1]) == 1))
	{
		ft_putstr(" too many arguments\n", 2);
		static_v->exit_status = 1;
	}
	else
	{
		ft_putstr(" numeric argument required\n", 2);
		static_v->exit_status = 2;
		free_all(static_v->info);
		exit(static_v->exit_status);
	}
}

void	print_exit(char **av)
{
	(void)av;
	ft_putstr(" numeric argument required\n", 2);
}

void	exit_error(char **av)
{
	t_static	*static_v;

	static_v = ft_static();
	print_exit(av);
	static_v->exit_status = 2;
	free_all(static_v->info);
	exit(static_v->exit_status);
}

void	builtin_exit(int ac, char **av)
{
	t_static	*static_v;

	static_v = ft_static();
	ac = 0;
	while (av[ac])
		ac++;
	if (ac == 1)
	{
		static_v->exit_status = 0;
		free_all(static_v->info);
		exit(static_v->exit_status);
	}
	else if (ac == 2)
	{
		check_error_max_exit(av);
		static_v->exit_status = ft_atoi1(av[1]);
		free_all(static_v->info);
		exit(static_v->exit_status);
	}
	else if (ac > 2)
		exit_multiple(av, ac);
}
