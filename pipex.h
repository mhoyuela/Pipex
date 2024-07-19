/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-08 14:25:46 by mhoyuela          #+#    #+#             */
/*   Updated: 2024-07-08 14:25:46 by mhoyuela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include "./libft/libft.h"

int		counter(char *str, int c);
char	**split_command(char *argv);
char	**split_pipex(char *argv, char **aux);
int		count_words(char *str, char c);
void	free_matrix(char **matrix);
char	**get_path(char **envp);
char	*find_cmd(char *argv, char **path, char **envp);
void	ft_error(char *str);
void	ft_create_process(int *pipefd, char **argv, char **envp);
void	ft_create_son(int *pipefd, char **argv, char **envp);
void	ft_create_second_son(int *pipefd, char **argv, char **envp);

#endif