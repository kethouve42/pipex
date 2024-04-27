/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:22:51 by kethouve          #+#    #+#             */
/*   Updated: 2024/03/15 16:51:48 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int			pipfd[2];
	t_command	*cmd;

	if (argc != 5)
	{
		ft_print("Error:right format is: ./prog file1 \"cmd1\" \"cmd2\" file2");
		return (0);
	}
	cmd = malloc(sizeof(t_command));
	cmd->com1 = ft_split(argv[2], ' ', 0, 0);
	cmd->com2 = ft_split(argv[3], ' ', 0, 0);
	cmd->env = get_env(envp);
	if (access(argv[1], F_OK | R_OK) < 0)
		return (ft_print("Error: file1 unreadable"), free_all(cmd), 0);
	if (pipe(pipfd) == -1)
		return (ft_print("Error: pipe error"), free_all(cmd), 0);
	pipex(argv, envp, cmd, pipfd);
	return (0);
}

void	pipex(char **argv, char **envp, t_command *cmd, int	*pipfd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_print("Error: fork error"), free_all(cmd));
	else if (pid == 0)
		child_process(cmd, envp, pipfd, argv);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(cmd, envp, pipfd, argv);
	}
}

void	child_process(t_command *cmd, char **envp, int	*pipefd, char **argv)
{
	int		fd;
	int		i;
	char	*s;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_print("Error: Open error"), free_all(cmd));
	while (cmd->env[i] && cmd->env[i][0])
	{
		s = ft_strjoin(cmd->env[i], cmd->com1[0]);
		if (access(s, F_OK | X_OK) == 0)
		{
			dup2(fd, 0);
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			if (access(ft_strjoin(cmd->env[i], cmd->com1[0]), F_OK | X_OK) == 0)
				execve(s, (cmd)->com1, envp);
		}
		free(s);
		i++;
	}
	close(fd);
	close(pipefd[1]);
	return (ft_print("Error: can't execute the command"), free_all(cmd));
}

void	parent_process(t_command *cmd, char **envp, int *pipefd, char **argv)
{
	int		fd2;
	int		i;
	char	*s;

	i = 0;
	fd2 = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd2 < 0)
		return (ft_print("Error: open error"), free_all(cmd));
	while (cmd->env[i] && cmd->env[i][0] != '\0')
	{
		s = ft_strjoin(cmd->env[i], cmd->com2[0]);
		if (access(s, F_OK | X_OK) == 0)
		{
			dup2(fd2, 1);
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			if (access(ft_strjoin(cmd->env[i], cmd->com2[0]), F_OK | X_OK) == 0)
				execve(ft_strjoin(cmd->env[i], cmd->com2[0]), cmd->com2, envp);
		}
		free(s);
		i++;
	}
	close(fd2);
	close(pipefd[0]);
	return (ft_print("Error: can't execute the command"), free_all(cmd));
}
