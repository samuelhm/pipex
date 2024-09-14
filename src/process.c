/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:09:51 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/14 18:17:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_process1(t_pipedata *data, char *comand1)
{
	char	*bash_args[4];

	data->pid1 = fork();
	if (data->pid1 == 0)
	{
		dup2(data->infile, STDIN_FILENO);
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		bash_args[0] = ft_strdup("bash");
		bash_args[1] = ft_strdup("-c");
		bash_args[2] = ft_strdup(comand1);
		bash_args[3] = NULL;
		execve("/bin/bash", bash_args, NULL);
		free(bash_args[0]);
		free(bash_args[1]);
		free(bash_args[2]);
		perror("exec Process1");
		exit(1);
	}
}

void	exec_process2(t_pipedata *data, char *comand2)
{
	char	*bash_args[4];

	data->pid2 = fork();
	if (data->pid2 == 0)
	{
		dup2(data->pipefd[0], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		bash_args[0] = ft_strdup("bash");
		bash_args[1] = ft_strdup("-c");
		bash_args[2] = ft_strdup(comand2);
		bash_args[3] = NULL;
		execve("/bin/bash", bash_args, NULL);
		free(bash_args[0]);
		free(bash_args[1]);
		free(bash_args[2]);
		perror("exec Process2");
		exit(1);
	}
}
