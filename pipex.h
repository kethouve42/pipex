/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:22:57 by kethouve          #+#    #+#             */
/*   Updated: 2024/03/13 14:50:03 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	**com1;
	char	**com2;
	char	**env;
}	t_command;

int		main(int argc, char **argv, char **envp);
void	ft_print(char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(char const *s, char c, int env, int i);
int		tabs_size(char const *s, char c, int env);
char	*put_words(char const *s, int debut, int end, int env);
int		ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, const char *s2);
char	**get_env(char **envp);
void	child_process(t_command *cmd, char **envp, int *pipfd, char **argv);
void	parent_process(t_command *cmd, char **envp, int *pipfd, char **argv);
void	pipex(char **argv, char **envp, t_command *cmd, int *pipfd);
void	free_all(t_command *cmd);

#endif 
