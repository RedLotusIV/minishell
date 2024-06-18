/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:10:13 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/18 13:39:39 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tokenizer(char **commands)
{
	t_token	*head;
	t_token	*tmp;
	int		i;

	i = 0;
	if (token_init(&head, commands))
		return (NULL);
	tmp = head;
	while (head)
	{
		head->value = malloc(sizeof(char) * (ft_strlen(commands[i]) + 1));
		if (!head->value)
			return (NULL);
		ft_strcpy(head->value, commands[i]);
		give_type(head);
		head = head->next;
		i++;
	}
	head = tmp;
	return (head);
}

void	give_type(t_token *token)
{
	if (!ft_strcmp(token->value, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->value, ">"))
		token->type = REDIR;
	else if (!ft_strcmp(token->value, "<"))
		token->type = INPUT;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->type = HEREDOC;
	else
		token->type = WORD;
}

int	token_init(t_token **head, char **commands)
{
	t_token	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
		i++;
	*head = malloc(sizeof(t_token));
	if (!*head)
		return (1);
	tmp = *head;
	while (j < i - 1)
	{
		tmp->next = malloc(sizeof(t_token));
		if (!tmp->next)
			return (1);
		tmp = tmp->next;
		j++;
	}
	tmp->next = NULL;
	return (0);
}

void	print_tokens(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		printf("Value : %s\n", current->value);
		printf("token : %d\n", current->type);
		printf("____________________\n");
		current = current->next;
	}
}
