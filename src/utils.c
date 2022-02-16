/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctogoe <ctogoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:11:38 by ctogoe            #+#    #+#             */
/*   Updated: 2022/02/16 12:08:01 by ctogoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	init_struct(t_var *vars)
{
	vars->line_path = NULL;
	vars->extract_path = NULL;
	vars->path_join = NULL;
	vars->path_join_cmd = NULL;
	vars->count = 0;
	vars->cmd = 0;
	vars->status = 2;
}

void	ft_extract_path(t_var *vars, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		ft_error("PATH variable not found\n");
	vars->extract_path = ft_split(env[i] + 5, ':');
	if (!vars->extract_path)
		ft_error_alloc("Error allocation extract_path\n", vars);
	i = 0;
	while (vars->extract_path[i])
		i++;
	vars->path_join = ft_calloc((i + 1), sizeof(char *));
	if (!vars->path_join)
		ft_error_alloc("Error allocation path_join/", vars);
	i = -1;
	while (vars->extract_path[++i])
		vars->path_join[i] = ft_strjoin(vars->extract_path[i], "/");
}

void	ft_first_process(char **av, t_var *vars)
{
	vars->fd_file = open(av[1], O_RDONLY);
	if (vars->fd_file < 0)
	{
		close(vars->pipefd[0]);
		close(vars->pipefd[1]);
		ft_error("An error occured:\nFile descriptor is not valid\n");
	}
	dup2(vars->fd_file, STDIN_FILENO);
	dup2(vars->pipefd[1], STDOUT_FILENO);
}

void	ft_second_process(char **av, t_var *vars)
{
	vars->fd_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vars->fd_file < 0)
	{
		close(vars->pipefd[0]);
		close(vars->pipefd[1]);
		ft_error("An error occured:\nFile descriptor is not valid\n");
	}
	dup2(vars->pipefd[0], STDIN_FILENO);
	dup2(vars->fd_file, STDOUT_FILENO);
}
