/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 20:51:42 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 07:02:30 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

/*
**	cree une nouvelle action de type assignation
*/

/*
**	creee une nouvelle action => assignation de variable
*/

t_assign	*new_assignation(char *name, char *value)
{
	t_assign		*new;

	new = (t_assign *)malloc(sizeof(t_assign));
	new->name = ft_strtrim(name);
	new->value = ft_strtrim(value);
	return (new);
}
