/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyuela <mhoyuela@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-09 15:17:15 by mhoyuela          #+#    #+#             */
/*   Updated: 2024-07-09 15:17:15 by mhoyuela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_create_second_son(int *pipefd, char **argv, char **envp)
{
	int		outfd;
	char	**path;
	char	*cmd;

	outfd = open(argv[4], O_WRONLY | O_CREAT |  O_TRUNC, 0644);
	if (outfd == -1)
		ft_error("Error creating infd");
	if (dup2(outfd, STDOUT_FILENO) == -1)
		ft_error("Erorr duplicating infd");
	close(outfd);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_error("Error duplicating pipe");
	close(pipefd[0]);
	path = get_path(envp);
	if (!path)
		ft_error("Error creating the path");
	cmd = find_cmd(argv[3], path, envp);
	free_matrix(path);
	if (!cmd)
		ft_error("Error finding the comand");//revisar y preguntar
	if (execve(cmd, split_command(argv[3]), 0) == -1)
		free(cmd);
}

		/*mientras no acabe las envp tengo que iterar hasta encnotrar la varibale path, en cuanto la encuentre
		tengo que hacer el split y quedarme con lo que esta entre : y tu tienes que buscar, en esta u otra funcion(mejor en otra)
		Lo hacemos utilizando access(que come argv[1], y la ruta que me ha devuelto el split), si argv tiene acceso a ese directorio
		es el correcto tienes que ejecutarlo*/
void	ft_create_son(int *pipefd, char **argv, char **envp)
{
	int		infd;
	char	**path;
	char	*cmd;

	infd = open(argv[1], O_RDONLY);
	if (infd == -1)
		ft_error("Error creating infd");
	if (dup2(infd, STDIN_FILENO) == -1)
		ft_error("Erorr duplicating infd");
	close(infd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error("Error duplicating pipe");
	close(pipefd[1]);
	path = get_path(envp);
	if (!path)
		ft_error("Error creating the path");
	cmd = find_cmd(argv[2], path, envp);
	free_matrix(path);
	if (!cmd)
		ft_error("Error finding the comand");
	if (execve(cmd, split_command(argv[2]), envp) == -1)
		free(cmd);
}
/*en esta funcion abro el archivo dado en el argv[1] si me da -1 error
duplico el infd y le indico que este debe ser el standar de entrada, 
y lo cierro. Despues duplico la entrada de la pipe y le indico que esta debe ser la 
salida del archivo estandar. Osea estamos indicando hacia donde debe ir la salida del infd
y cerramos la pipe[1]*/

void	ft_create_process(int *pipefd, char **argv, char **envp)
{
	int	pid;
	int	pid2;
	
	
	pid = fork();
	if (pid < 0)
		ft_error("Error creating process");
	if (pid == 0)
	{
		ft_create_son(pipefd, argv, envp);
	}
	close(pipefd[1]);
	pid2 = fork();
	if (pid2 < 0)
		ft_error("Error creating process");
	if (pid2 == 0)
	{
		ft_create_second_son(pipefd, argv, envp);
	}
	close(pipefd[0]);
	waitpid(pid2, 0, 0);
}

/*En esta funcion duplicamos la entrada del infd,
y la salida del infd la redirecccionamos (con STDOUT_FILENO)
hacia la entrada de la pipe que es pipefd[1]*/

int main(int argc, char **argv, char **envp)
{
	int	pipefd[2];

	if (argc != 5)
		ft_error("Error. Incorrect number of arguments");
	else
	{
		if(pipe(pipefd) == -1)
			ft_error("Error pipe");
		ft_create_process(pipefd, argv, envp);
		
	}
}