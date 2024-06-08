/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:13:25 by amouhand          #+#    #+#             */
/*   Updated: 2024/05/22 10:20:44 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

int			ft_strcmp(char *s1, char *s2);
void		ft_strcpy(char *dst, char *src);
t_token		*tokenizer(char **commands);
void		give_type(t_token *token);
int			token_init(t_token **head, char **commands);
void		print_tokens(t_token **head);

#endif