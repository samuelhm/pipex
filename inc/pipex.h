/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:51:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/14 18:10:38 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_pipedata
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipedata;

void	exec_process1(t_pipedata *data, char *comand1);
void	exec_process2(t_pipedata *data, char *comand2);
#endif
