/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_comand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-17 16:13:41 by mhoyuela          #+#    #+#             */
/*   Updated: 2024-07-17 16:13:41 by mhoyuela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	counter(char *str, int c)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while(str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
char	**split_command(char *argv)
{
	int	count;
	char	**cmd_split;
	char	**aux;

	count = counter(argv, '\'');
	if (count % 2 == 0)
	{
		aux = ft_split(argv, '\'');
		cmd_split = split_pipex(argv, aux);
		free_matrix(aux);
		return (cmd_split);
	}
	else
	{
		cmd_split = ft_split(argv, ' ');
		return (cmd_split);
	}

}
char	**split_pipex(char *argv, char **aux)
{
	int		i;
	char	**cmd;

	i = 1;
	cmd = (char **)malloc(sizeof(char *) *counter(argv, '\''));
	if (!cmd)
		ft_error("Error in malloc");
	cmd[0] = ft_strtrim(argv, " ");
	while (aux[i])
	{
		cmd[i] = aux[i];
		i++;
	}
cmd[i] = NULL;
return (cmd);
}