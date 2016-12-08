/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobsbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:40:36 by jmontija          #+#    #+#             */
/*   Updated: 2016/12/08 02:28:31 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fortytwo.h"

int		ft_sigcont(t_jobs *curr)
{
	if (curr->terminate == CLD_STOPPED)
	{
		if (kill (-curr->pid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
		return (1);
	}
	return (0);
}

int		check_jobs_enabled(t_jobs *jobs)
{
	t_jobs	*pipe;
	int stopped;
	int	count;

	stopped = 0;
	count = 1;
	if (jobs->terminate == CLD_EXITED || jobs->terminate == CLD_KILLED || 
		jobs->terminate == CLD_STOPPED)
		stopped += 1;
	pipe = jobs->next_pipe;
	while (pipe)
	{
		if (pipe->terminate == CLD_EXITED || pipe->terminate == CLD_KILLED || 
			pipe->terminate == CLD_STOPPED)
			stopped += 1;
		count++;
		pipe = pipe->next_pipe;
	}
	return (count == stopped ? false : true);
}

void	put_in_fg(t_group *grp, t_jobs *parent)
{
	if (grp)
		;
	tcsetpgrp(STDIN_FILENO, parent->pid);
	ft_sigcont(parent) ? change_state(parent, CLD_CONTINUED) : 0;
	while (42)
	{
		if (check_jobs_enabled(parent) == false)
			break ;
	}
	tcsetpgrp(STDIN_FILENO, grp->program_pid);
	//grp->exit = (parent->terminate > 1 && parent->terminate != CLD_CONTINUED && parent->terminate != CLD_STOPPED ? 1 : 0);
}

int		builtin_fg(t_group *grp, int idx)
{
	t_jobs	*curr;

	curr = get_jobs_idx(grp, idx);
	if (curr != NULL)
		put_in_fg(grp, curr);
	return (1);
}

int	builtin_bg(t_group *grp, int idx)
{
	t_jobs *curr;

	curr = get_jobs_idx(grp, idx);
	if (curr)
		ft_sigcont(curr);
	return (1);
}
