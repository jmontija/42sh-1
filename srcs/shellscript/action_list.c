/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 01:19:24 by vdanain           #+#    #+#             */
/*   Updated: 2017/01/19 14:53:16 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	rajoute une nouvelle action a la fin de la liste d'action
*/

void			add_to_action(void *action, t_script *script,
	int type, t_action **begin)
{
	t_action		*new;
	t_action		*tmp;

	if (script)
		;
	if (!action)
		error_handler(script);
	new = (t_action *)malloc(sizeof(t_action));
	new->type = type;
	new->action = action;
	new->next = NULL;
	tmp = *begin;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		*begin = new;
	else
		tmp->next = new;
}

/*
**	reader des actions => appelle le correct handler.
*/

void			action_reader(t_script *script, t_action *begin)
{
	t_action	*tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp->type == ASSIGN_T)
			assignation_handler((t_assign *)tmp->action, script);
		else if (tmp->type == LINE_T)
			line_handler(tmp->action, script, get_grp());
		else if (tmp->type == COND_T)
			condition_handler(tmp->action, script);
		else if (tmp->type == LOOP_T)
			loop_handler(tmp->action, script);
		tmp = tmp->next;
	}
}

/*
**	plus de place ds checklib -> s'occupe de gestion erreur calc
*/

int				calc_checker(char *line)
{
	size_t		i;

	i = 0;
	if (!ft_strchr(line, '='))
		return (0);
	while (line[i])
	{
		if (line[i] == '+' || line[i] == '-' || line[i] == '%'
			|| line[i] == '*' || line[i] == '/')
		{
			if (i > 0 && line[i - 1] == ' ')
				return (E_INVALID_OP);
			if (i < ft_strlen(line) - 1 && line[i + 1] == ' ')
				return (E_INVALID_OP);
		}
		i++;
	}
	return (0);
}
