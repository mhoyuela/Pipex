/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-11 15:17:05 by mhoyuela          #+#    #+#             */
/*   Updated: 2024-07-11 15:17:05 by mhoyuela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_words(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str != '\0' && *str != c)
				str++;
		}
		else
			str++;
	}
	return (count);
}
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
char	**get_path(char **envp)
{
	char **path;
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(&envp[i][5], ':');
		}
		i++;
	}
	return (path);
}
char	*find_cmd(char *argv, char **path, char **envp)
{
	char	**cmd;
	char	*cmd_and_path;
	char	*aux;
	int		i;

	i = 0;
	(void)envp;
	cmd = ft_split(argv, ' ');
	aux = ft_strjoin(path[i], "/");
	cmd_and_path = ft_strjoin(aux, cmd[0]);
	while (path[i])
	{
		if (access(cmd_and_path, X_OK) == 0)
		{
			/* if (execve(cmd_and_path, cmd, envp) == -1)
				ft_error("Execution error"); */
			return (cmd_and_path);
		}
		else
		{
			free(aux);
			free(cmd_and_path);
			aux = ft_strjoin(path[i++], "/");
			cmd_and_path = ft_strjoin(aux, cmd[0]);
		}
	}
	if (aux)
		free(aux);
	return (free(cmd_and_path), NULL);
}
void ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

