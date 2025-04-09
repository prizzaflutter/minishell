/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:13:05 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/09 11:18:42 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command {
	char **cmd;
	char **inoutfile;
	char *next; 
	char *prev;
} t_command;

typedef struct s_token {
	char *str;
	int type;
	struct s_token *next;
} t_token;

enum token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
};
// EXEC FUNCTIONS
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void my_echo(char **argv);


// PARSING FUNCTIONS
t_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);

#endif