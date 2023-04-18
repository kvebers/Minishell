/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_selector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/18 14:39:54 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor.h"	// needed for executor_child(),
						// executor_parent()
#include "minishell.h"	// needed for t_data
#include <unistd.h>		// needed for NULL, access()
#include "libft.h"		// needed for ft_split(), ft_strlen()
#include "libme.h"		// needed for ft_str_check_needle(),
						// ft_str_join_delimiter()
#include <stdio.h>		// needed for printf()
#include "redirector.h"

int	child_execute_builtin(t_data *data, int index);

static int	selector_fork_and_execute(t_data *data, int **fd_pipes, int index,
				int flag_cmd)
{
	// @note i should be forking even on an error prob

	if (flag_cmd == ERROR)
	{
		executor_parent(data, fd_pipes, index);
		return (ERROR);
	}
	else if (flag_cmd == COMMAND_NOT_FOUND)
	{
		executor_parent(data, fd_pipes, index);
		printf("WIP: command not found!\n"); // @todo replace with an alternative that prints to STDERROR OUT
		return (EXECUTED);
	}
	if (fd_pipes == NULL && flag_cmd == BUILTIN)
	{
		data->flag_builtin_only = 1;
		child_handle_indirection(data);
		child_handle_outdirection(data);
		if (child_execute_builtin(data, index) == ERROR)
		{
			return(ERROR);
		}
		executor_parent(data, fd_pipes, index);
		return (EXECUTED);
	}
	data->child_pids[data->index_processes] = fork();
	if (data->child_pids[data->index_processes] == -1)
	{
		executor_parent(data, fd_pipes, index);
		return (ERROR);
	}
	if (data->child_pids[data->index_processes] == 0)
	{
		executor_child(data, fd_pipes, index, flag_cmd);
	}
	else
	{
		executor_parent(data, fd_pipes, index);
	}
	return (EXECUTED);
}

int	executor_cmd_selector(t_data *data, int **fd_pipes, int index)
{
	int	return_value;

	if (redirector_handle_redirections(data, index) == ERROR)
	{
		return (ERROR);
	}
	index = pipex_skip_non_commands(data, index);
	if (is_builtin(data->combine[index].command->order_numb) == 1)
	{
		return_value = BUILTIN;
	}
	else if (selector_is_cmd_path_valid(&data->combine[index]) == EXTERN)
	{
		return_value = EXTERN;
	}
	else
	{
		return_value = selector_is_cmd_valid(&data->combine[index], data->envp);
	}
	if (selector_fork_and_execute(data, fd_pipes, index, return_value) == ERROR)
	{
		return (ERROR);
	}
	return (EXECUTED);
}
