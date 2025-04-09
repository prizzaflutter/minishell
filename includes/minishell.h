/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:13:05 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/09 10:43:42 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
typedef struct s_command {
	char **cmd;
	char **inoutfile;
	char *next; 
	char *prev;
} t_command;
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void my_echo(char **argv);
#endif