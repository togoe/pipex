#include "../inc/pipex.h"

void    init_struct(t_var *vars)
{
    vars->line_path = NULL;
    vars->extract_path = NULL;
    vars->path_join = NULL;
    vars->path_join_cmd = NULL;
    vars->count = 0;
    vars->cmd = 0;
    vars->status = 2;
}

void    ft_extract_path(t_var *vars, char **env)
{
    int     i;

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

void    ft_execute(t_var *vars, char *cmd_av, char **env)
{
    int i;

    vars->cmd = ft_split(cmd_av, ' ');
    if (!access(cmd_av, X_OK))
        execve(cmd_av, vars->cmd, env);
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
}

void    ft_child_process(t_var *vars, char **av,char **env, char *cmd_av)
{
    if (vars->count == 0)
    {
        vars->fd_file = open(av[1], O_RDONLY);
        if (vars->fd_file < 0)
            ft_error("An error occured:\nFile descriptor is not valid\n");
        dup2(vars->fd_file, STDIN_FILENO);
        dup2(vars->pipefd[1], STDOUT_FILENO);
    }
    if (vars->count == 1)
    {
        vars->fd_file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (vars->fd_file < 0)
            ft_error("An error occured:\nFile descriptor is not valid\n");
        dup2(vars->pipefd[0], STDIN_FILENO);
        dup2(vars->fd_file, STDOUT_FILENO);
    }
        close(vars->pipefd[0]);
        close(vars->pipefd[1]);
        close(vars->fd_file);
        ft_execute(vars, cmd_av, env);
}

void ft_pipe(t_var *vars, char **av, char **env, int ac)
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

int main(int ac, char **av, char **env)
{
    t_var   vars;
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