/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:36:09 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/14 13:25:14 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	cd => with no argument -> go the HOME directory (from env)
	cd ~ or ~/some/path -> also go to home (if you want to support it)
	cd - -> go back to previous directory (if implementin it)
	cd path -> go to specified path (relative or absolute)
*/
///@brief chdir is a system call in C that changes the current working directory of the calling precess to the directory specified in its argument. 
///@return   0 ==> on success.
///@return   1 ==> on failure (if the path doesn't exit of isn't a directory).

int my_cd (char **argv)
{
	if (!argv[1]){
		printf("cd: path required\n");
		return 0;
	}
	printf("the path is : %s\n", argv[1]);
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (0);
	}
	return (0);
}
