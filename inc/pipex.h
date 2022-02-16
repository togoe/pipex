/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctogoe <ctogoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:59:56 by ctogoe            #+#    #+#             */
/*   Updated: 2022/02/16 12:07:29 by ctogoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_var
{
	char	**extract_path;
	char	**path_join;
	char	*path_join_cmd;
	char	*line_path;
	int		count;
	pid_t	pid[2];
	int		pipefd[2];
	int		fd_file;
	char	**cmd;
	int		status;
}	t_var;

void	init_struct(t_var *vars);
void	ft_first_process(char **av, t_var *vars);
void	ft_second_process(char **av, t_var *vars);
void	ft_error(char *str);
void	free_all(t_var *vars);
void	ft_free_tab(char **tab);
void	ft_error_alloc(char *str, t_var *vars);
void	ft_extract_path(t_var *vars, char **env);
void	ft_child_process(t_var *vars, char **av, char **env, char *cmd_av);

#endif
