/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:55:46 by jtranchi          #+#    #+#             */
/*   Updated: 2016/12/11 16:14:56 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int				ft_strisdigit(char *str)
{
	int i;

	if (str && str[0] == '-')
		i = 0;
	else
		i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void			ft_display_history(t_history *hist)
{
	int i;

	i = -1;
	while (++i < 16 && hist && hist->next)
	{
		(hist->i < 1000) ? ft_putchar_fd(' ', 2) : 0;
		(hist->i < 100) ? ft_putchar_fd(' ', 2) : 0;
		(hist->i < 10) ? ft_putchar_fd(' ', 2) : 0;
		ft_putnbr(hist->i);
		ft_putstr(" ");
		ft_putendl(hist->var);
		hist = hist->next;
	}
}

int				builtin_history2(t_group *grp, t_parse *parse)
{
	if (ft_atoi(parse->cmdsplit[1]) > 0)
	{
		if (ft_atoi(parse->cmdsplit[1]) > grp->history->i)
		{
			error_cmd("history", "invalid parameter", 1);
			return (1);
		}
		if (ft_atoi(parse->cmdsplit[1]) == grp->history->i)
		{
			(grp->history->i < 1000) ? ft_putchar_fd(' ', 2) : 0;
			(grp->history->i < 100) ? ft_putchar_fd(' ', 2) : 0;
			(grp->history->i < 10) ? ft_putchar_fd(' ', 2) : 0;
			ft_putnbr(grp->history->i);
			ft_putstr(" ");
			ft_putendl(grp->history->var);
		}
		else
			ft_display_history(ft_history_get_by_id(grp,
			ft_atoi(parse->cmdsplit[1])));
	}
	else
		ft_display_history(ft_history_get_by_id(grp, grp->history->i +
		ft_atoi(parse->cmdsplit[1])));
	return (0);
}

static void		history_display_help(void)
{
	ft_putendl("usage: history [ -h | index ]");
	ft_putendl("history displays the last fifteen commands int the historic.");
	ft_putstr("If an index is given as an argument, ");
	ft_putendl("historic will be displayed from this index.");
	ft_putstr("You can use \'!\' operator to access a part");
	ft_putendl("icular command in historic : ![index]");
	ft_putendl("\'!!\' will refer to the last command.");
	ft_putendl("-h: display help");
}

int				builtin_history(t_group *grp, t_parse *parse)
{
	char	**cmdsplit;

	grp->history = ft_history_get_last(grp);
	cmdsplit = parse->cmdsplit;
	if (!cmdsplit[1])
	{
		if (grp->history->i > 16)
			ft_display_history(ft_history_get_by_id(grp, grp->history->i - 16));
		else
			ft_display_history(ft_history_get_first(grp));
	}
	else if (ft_strcmp(cmdsplit[1], "-h") == 0)
		history_display_help();
	else
	{
		if (!ft_strisdigit(cmdsplit[1]))
		{
			error_cmd("history", "invalid parameter", 1);
			return (1);
		}
		if (builtin_history2(grp, parse))
			return (1);
	}
	return (0);
}
