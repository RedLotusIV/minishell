/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:01:52 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/23 00:12:25 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int		handle_regular_characters(char *command, int i, int *l, int *tmp);
int		handle_quotes(char *command, int i, int *l, int *tmp);
int		handle_special_characters(char *command, int i, int *l);
int		skip_whitespace(char *command, int i);
int		skip_quotes(char *command, int i);
int		skip_special_char(char *command, int i);
int		skip_everything_else(char *command, int i);
char	*copy_segment(char *command, int start, int end);
void	free_tokens(t_token **head);
void	free_char_array(char **array);
void	free_tree(t_pipe *root);
void	free_cmd(t_cmd *cmd);
void	free_redirections(t_redirection *redirections);
void	free_parser(t_parser *parser, t_pipe *root, char *prompt, char *cwd);

#endif