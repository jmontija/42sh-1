/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <jtranchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 20:56:16 by jmontija          #+#    #+#             */
/*   Updated: 2016/11/19 22:37:55 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
** builtin history :
** replacing !! by last command in history
*/

void		ft_replace_last_cmd(t_group *grp, int i)
{
	char		*tmp;
	t_history	*hist;

	hist = ft_history_get_last(grp);
	if (!hist)
		return (ft_putendl_fd("42sh: no previous command", 2));
	ft_putendl_fd(hist->var, 2);
	if (!TERM(cmd_line)[i + 2])
	{
		TERM(cmd_line)[i] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), hist->var, 1);
	}
	else
	{
		tmp = SDUP(&TERM(cmd_line)[i + 2]);
		TERM(cmd_line)[i] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), hist->var, 1);
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 3);
	}
}

/*
** builtin history :
** replacing the hisotry result in cmd_line
*/

void		ft_replace_command(t_group *grp, t_history *hist, int start,
int end)
{
	char	*tmp2;

	if (TERM(cmd_line)[end + 1])
	{
		tmp2 = SDUP(&TERM(cmd_line)[end]);
		TERM(cmd_line)[start - 1] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), hist->var, 1);
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp2, 3);
	}
	else
	{
		TERM(cmd_line)[start - 1] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), hist->var, 1);
	}
}

/*
** builtin history
** replacing command with given history id
*/

void		ft_replace_by_id(t_group *grp, int i)
{
	int			start;
	int			end;
	char		*tmp;
	t_history	*hist;

	start = i;
	while (TERM(cmd_line)[i] && ft_isdigit(TERM(cmd_line)[i]))
		i++;
	tmp = ft_strsub(TERM(cmd_line), start, i);
	hist = ft_history_get_by_id(grp, ft_atoi(tmp));
	if (hist)
	{
		ft_putendl_fd(hist->var, 2);
		ft_replace_command(grp, hist, start, i);
	}
	else
	{
		ft_putstr_fd("42sh: no historic at indice: ", 2);
		ft_putendl_fd(tmp, 2);
	}
	REMOVE(&tmp);
}

/*
** builtin history :
** deleting unwanted chars
*/

void		ft_escape_parse(t_group *grp, int i)
{
	char	*tmp;

	if (TERM(cmd_line)[i + 2])
	{
		tmp = SDUP(&TERM(cmd_line)[i + 2]);
		TERM(cmd_line)[i + 1] = '\0';
		TERM(cmd_line) = JOINF(TERM(cmd_line), tmp, 3);
	}
	else
		TERM(cmd_line)[i + 1] = '\0';
}

/*
** preparsing command for insertting in history
** replacing builtin hisotry result
** replace escaped chars
*/

void		ft_pre_parse(t_group *grp)
{
	int i;

	i = -1;
	while (TERM(cmd_line) && TERM(cmd_line)[++i])
	{
		if (i > 0 && TERM(cmd_line)[i] == '\\' &&
			TERM(cmd_line)[i + 1] && TERM(cmd_line)[i + 1] == '\n')
		{
			ft_escape_parse(grp, i - 1);
			ft_escape_parse(grp, i - 1);
		}
		if (TERM(cmd_line)[i] == '!' && TERM(cmd_line)[i + 1] &&
			TERM(cmd_line)[i + 1] == '!')
		{
			ft_replace_last_cmd(grp, i);
		}
		else if (TERM(cmd_line)[i] == '!' && TERM(cmd_line)[i + 1])
			ft_replace_by_id(grp, i + 1);
	}
}
