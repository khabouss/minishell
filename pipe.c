void    ft_execve(char *str_pips, t_list *env_list)
{
    char *path;
    char **args;

    path = getcwd(path,0);
    args = ft_split(str_pips, ' ');
    if (ft_strcmp("echo",args[0]) == 0)
        ft_echo(STDOUT_FILENO, args);
    else if (ft_strcmp("cd",args[0]) == 0)
        ft_cd(STDOUT_FILENO, args,path,env_list);
    else if (ft_strcmp("pwd",args[0]) == 0)
        ft_pwd(STDOUT_FILENO);
    else if (ft_strcmp("env",args[0]) == 0)
        ft_env(STDOUT_FILENO, env_list);
    else if (ft_strcmp("unset",args[0]) == 0)
        ft_unset(args,env_list);
    else if (ft_strcmp("export",args[0]) == 0)
        ft_export(STDOUT_FILENO, args,env_list);
    else
    {
        path = check_fill_path(env_list, args);
        int r = execve(path, fill_paramlist(path, args), NULL);   
        printf("error %d\n", r); 
    }
    
}

void handle_pipe(char **str_pips, t_list *env_list, int pips)
{
    int pipe_fd[2];
    int status;
    pid_t pid;

    pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        ft_execve(str_pips[0], env_list);
        ft_putstr(STDOUT_FILENO, 0);
    }
    pid = fork();
    if (pid == 0)
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        ft_execve(str_pips[1], env_list);
        ft_putstr(STDOUT_FILENO, 0);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);

}