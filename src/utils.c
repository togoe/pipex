#include "../inc/pipex.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_error_alloc(char *str, t_var *vars)
{
	ft_error(str);
	if (!vars->line_path)
		ft_free_tab(vars->cmd);
	else if (!vars->extract_path)
	{

		ft_free_tab(vars->cmd);
		free(vars->line_path);
	}
	else if (!vars->path_join)
		ft_free_tab(vars->extract_path);
	else if (!vars->path_join_cmd)
		ft_free_tab(vars->path_join);
	
}

void free_all(t_var *vars)
{
	ft_free_tab(vars->cmd);
	ft_free_tab(vars->extract_path);
	free(vars->line_path);
}