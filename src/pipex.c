/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:55:11 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/14 18:13:41 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipedata	*init_pipedata(void)
{
	t_pipedata	*data;

	data = ft_calloc(sizeof(t_pipedata), 1);
	if (!data)
		return (NULL);
	return (data);
}

static void	open_files(t_pipedata *data, char *pathin, char *pathout)
{
	if (!data)
		return ;
	data->infile = open(pathin, O_RDONLY);
	data->outfile = open(pathout, O_WRONLY | O_CREAT | O_TRUNC, 0644);

}

static bool	data_is_ok(t_pipedata *data)
{
	if (!data)
	{
		perror("data NULL");
		return (false);
	}
	if (data->infile < 0 || data->outfile < 0)
	{
		perror("file");
		return (false);
	}
	if (pipe(data->pipefd) == -1)
	{
		perror("pipe");
		return (false);
	}
	return (true);
}

static void	close_all(t_pipedata *data)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->infile);
	close(data->outfile);
}

int	main(int argc, char *argv[])
{
	t_pipedata	*data;

	if (argc != 5)
	{
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (1);
	}
	data = init_pipedata();
	open_files(data, argv[1], argv[4]);
	if (!data_is_ok(data))
	{
		free(data);
		return (1);
	}
	exec_process1(data, argv[2]);
	exec_process2(data, argv[3]);
	close_all(data);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
	free(data);
	return (0);


}
