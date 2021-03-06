/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdanain <vdanain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 02:46:38 by vdanain           #+#    #+#             */
/*   Updated: 2016/12/09 07:06:10 by vdanain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

void			str_join_init(char *str)
{
	str[0] = 135;
	str[1] = '\0';
}

int				ci(char *file_name)
{
	struct stat		buf;

	if (lstat(file_name, &buf))
		return (-1);
	if (!S_ISREG(buf.st_mode))
		return (-1);
	return (0);
}
