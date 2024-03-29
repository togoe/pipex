/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctogoe <ctogoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:13:41 by ctogoe            #+#    #+#             */
/*   Updated: 2022/02/16 10:13:46 by ctogoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_error_alloc(char *str, t_var *vars)
{
	if (!vars->extract_path)
		ft_free_tab(vars->cmd);
	if (!vars->path_join)
	{
		ft_free_tab(vars->extract_path);
		ft_free_tab(vars->cmd);
	}
	else if (!vars->cmd)
	{
		ft_free_tab(vars->path_join);
		ft_free_tab(vars->extract_path);
	}
	else if (!vars->path_join_cmd)
	{
		ft_free_tab(vars->cmd);
		ft_free_tab(vars->path_join);
		ft_free_tab(vars->extract_path);
	}
	ft_error(str);
}

void	free_all(t_var *vars)
{
	ft_free_tab(vars->cmd);
	ft_free_tab(vars->extract_path);
}
