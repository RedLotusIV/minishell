/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:44:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/13 19:30:18 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

char		**mini_parsing(char *commands);
int			count_parse(char *commands);
void		free_strings(char **strings);
void		free_parser(t_parser *s);
char		**duplicate_pointer_array(char **commands);
char		*remove_matching_double_quotes(char* str);
t_cmd		**parse_cmd(t_token *head);
void		allocate_cmd(t_cmd **cmd, t_token *head);
void        add_redirection(t_cmd *cmd, t_token *redir_token, char *arg);

#endif