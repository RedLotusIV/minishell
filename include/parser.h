/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:44:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/19 21:22:21 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

char		**mini_parsing(char *commands);
int			count_parse(char *commands);
void		allocate_cmd(t_cmd **cmd, t_token *head);
void        add_redirection(t_cmd *cmd, t_token *redir_token, char *arg);
int			count_args(t_token *start, t_token *end);
void		process_token(t_token **current, t_token **before, t_cmd **cmd, int i);
void		fill_args(t_token *start, t_token *end, t_cmd *cmd);
int			count_pipes(t_token *head);
void		print_command_details(t_cmd **cmd);
void		initialize_cmd(t_cmd **cmd, t_token *current, int i);
t_cmd		**parse_cmd(t_token *head);
int			pipes_in_cmds(t_cmd **cmd);
void		print_tree(t_pipe *root);
void		checking_parsing(t_token *head);
void		parsing_error(char *message, int status);
int			setting_parser(char *command, char ***result, int *i, int *k);
char		**set_path(char **env);
char		*get_path(char *command, char **path);
void		testing_commands(t_pipe *root, char **path);
void		replaceWord(char* str, char* oldWord, char* newWord);
char		*set_pwd(char *old_prompt);

#endif