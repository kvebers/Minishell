/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvebers <kvebers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:41:48 by kvebers           #+#    #+#             */
/*   Updated: 2023/02/27 12:44:19 by kvebers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_after_break(t_data *data)
{
	free(data->prompt);
}

void	free_loop(t_data *data)
{
	int	cnt;

	cnt = 0;
	while (data->args[cnt] != NULL)
	{
		free(data->args[cnt]);
		free(data->execute[cnt].order_str);
		cnt++;
	}
	free(data->execute);
	free(data->args);
}
