/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:44:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/08 02:52:37 by amouhand         ###   ########.fr       */
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

#endif