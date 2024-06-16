/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:44:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/16 12:39:45 by amouhand         ###   ########.fr       */
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
void		allocate_cmd(t_cmd **cmd, t_token *head);
void        add_redirection(t_cmd *cmd, t_token *redir_token, char *arg);
int			count_args(t_token *start, t_token *end);
void		process_token(t_token **current, t_token **before, t_cmd **cmd, int i);
void		fill_args(t_token *start, t_token *end, t_cmd *cmd);
int			count_pipes(t_token *head);
void		print_command_details(t_cmd **cmd);
void		initialize_cmd(t_cmd **cmd, t_token *current, int i);
t_cmd		**parse_cmd(t_token *head);

#endif