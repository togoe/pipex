/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctogoe <ctogoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:00:17 by ctogoe            #+#    #+#             */
/*   Updated: 2022/02/16 13:18:56 by ctogoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_execute(t_var *vars, char *cmd_av, char **env)
{
	int	i;

	vars->cmd = ft_split(cmd_av, ' ');
	if (!access(vars->cmd[0], X_OK))
		execve(vars->cmd[0], vars->cmd, env);
	ft_extract_path(vars, env);
	i = -1;
	while (vars->path_join[++i])
	{
		vars->path_join_cmd = ft_strjoin(vars->path_join[i], vars->cmd[0]);
		if (!vars->path_join_cmd)
			ft_error_alloc("Error allocation path_join_cmd/\n", vars);
		if (!access(vars->path_join_cmd, X_OK))
			execve(vars->path_join_cmd, vars->cmd, env);
		free(vars->path_join[i]);
		free(vars->path_join_cmd);
	}
	free_all(vars);
	free(vars->path_join);
	ft_error("command not found\n");
}

void	ft_child_process(t_var *vars, char **av, char **env, char *cmd_av)
{
	if (vars->count == 0)
		ft_first_process(av, vars);
	if (vars->count == 1)
		ft_second_process(av, vars);
	if (vars->fd_file >= 0)
	{
		close(vars->pipefd[0]);
		close(vars->pipefd[1]);
		close(vars->fd_file);
		ft_execute(vars, cmd_av, env);
	}
}

void	ft_pipe(t_var *vars, char **av, char **env, int ac)
{
	vars->count = -1;
	while (++vars->count < 2)
	{
		vars->pid[vars->count] = fork();
		if (vars->pid[vars->count] == -1)
		{
			perror("fork() failed\n");
			exit(EXIT_FAILURE);
		}
		if (vars->pid[vars->count] == 0)
			ft_child_process(vars, av, env, av[(ac - 3) + vars->count]);
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	vars;

	init_struct(&vars);
	if (ac != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		perror("The format must be: ./pipex infile cmd1 cmd2 outfile\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(vars.pipefd) == -1)
	{
		perror("pipe() failed");
		exit(EXIT_FAILURE);
	}
	ft_pipe(&vars, av, env, ac);
	close(vars.pipefd[0]);
	close(vars.pipefd[1]);
	vars.count = -1;
	while (++vars.count < 2)
		waitpid(vars.pid[vars.count], &vars.status, 0);
	return (0);
}
