/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/15 21:31:00 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_cmd	**parse_cmd(t_token *head)
{
	t_cmd	**cmd;
	t_token *token_tmp;
	t_cmd **tmp;
	int i;
	int count;

	i = 0;
	count = 0;
	token_tmp = head;
	while (token_tmp)
	{
		if (token_tmp->type == PIPE)
			count++;
		token_tmp = token_tmp->next;
	}
	cmd = malloc(sizeof(t_cmd *) * (count + 2));
	if (!cmd)
		return (NULL);
	allocate_cmd(cmd, head);
	tmp = cmd;
	for (int i = 0 ; tmp[i] ; i++)
	{
		for (int j = 0 ; tmp[i]->args[j] ; j++)
			printf("arg[%d] : %s at command %d\n", j + 1, tmp[i]->args[j], i + 1);
		if (tmp[i]->redirections)
		{
			printf("redir   : %s at command %d\n", tmp[i]->redirections->redir->value, i + 1);
			printf("file    : %s at command %d\n", tmp[i]->redirections->arg, i + 1);
			tmp[i]->redirections = tmp[i]->redirections->next;
		}
	}
	return (cmd);
}
void	allocate_cmd(t_cmd **cmd, t_token *head)
{
	int i;
	int j;
	t_token	*current;
	t_token	*before;
	t_token *redirect;
	t_token *file;
	t_cmd	*tmp;
	t_token *tmp_token;
	t_token *before_tmp;
	int flag;
	int count;
	
	i = 0;
	current = head;
	before = head;
	while (current)
	{
		count = 0;
		flag = 0;
		tmp_token = current;
		cmd[i] = malloc(sizeof(t_cmd));
		if (!cmd[i])
			return ;
		while (current && current->type != PIPE)
		{
			if (current->type == WORD && before->type != REDIR && before->type != PIPE
				&& before->type != INPUT && before->type != APPEND && before->type != HEREDOC)
			{
				count++;
				before = current;
				current = current->next;
			}
			else if (current->type == REDIR || current->type == PIPE || current->type == INPUT 
			|| current->type == APPEND || current->type == HEREDOC)
			{
				redirect = current;
				before = current;
				current = current->next;
				if (current->type == WORD)
					add_redirection(cmd[i], redirect, current->value);
			}
			else
			{
				before = current;
				current = current->next;
			}
		}
		cmd[i]->args = malloc(sizeof(char *) * (count + 1));
		if (!cmd[i]->args)
			return ;
		tmp = cmd[i];
		before_tmp = tmp_token;
		j = 0;
		while(tmp_token && tmp_token->type != PIPE)
		{
			if (tmp_token->type == WORD && (before_tmp->type != REDIR && before_tmp->type != PIPE
				&& before_tmp->type != INPUT && before_tmp->type != APPEND && before_tmp->type != HEREDOC))
			{
				tmp->args[j] = ft_strdup(tmp_token->value);
				j++;
			}
			before_tmp = tmp_token;
			tmp_token = tmp_token->next;
		}
		tmp->args[j] = NULL;
		if (current && current->type == PIPE)
		{
			before = current;
			current = current->next;
		}
		i++;
	}
	cmd[i] = NULL;
}

void add_redirection(t_cmd *cmd, t_token *redir_token, char *arg)
{
    t_redirection *new_redir;
	t_redirection *current;

	new_redir = malloc(sizeof(t_redirection));
    new_redir->redir = redir_token;
    new_redir->arg = strdup(arg);
    new_redir->next = NULL;
    if (cmd->redirections == NULL)
        cmd->redirections = new_redir;
	else 
	{
        current = cmd->redirections;
        while (current->next != NULL)
            current = current->next;
        current->next = new_redir;
    }
}
/* Potential issues and improvements for parser_cmd.c */

// 1. Memory Leak Risk:
// - In `parse_cmd`, if `allocate_cmd` fails and returns due to an allocation failure, the memory allocated for `cmd` is not freed.
// - In `allocate_cmd`, if allocation for `cmd[i]` or `cmd[i]->args` fails after some commands have already been allocated, there's no cleanup for previously allocated commands.
// - In `add_redirection`, if `strdup` fails due to memory allocation failure, `new_redir` is not freed.

// 2. Error Handling:
// - The function `allocate_cmd` does not have a return type and cannot signal failure to `parse_cmd`, potentially leading to use of partially initialized command structures.

// 3. Redirection Handling:
// - In `parse_cmd`, the line `tmp[i]->redirections = tmp[i]->redirections->next;` modifies the command's redirections list during printing, which could lead to issues if the list needs to be iterated over again.

// 4. Code Duplication:
// - The pattern of checking token types against multiple values is repeated multiple times. This could be simplified with a helper function.

// 5. Potential Infinite Loop:
// - If the token list has a cycle, the while loops in `parse_cmd` and `allocate_cmd` could result in an infinite loop.

// 6. Unnecessary Variables:
// - The variable `flag` in `allocate_cmd` is set but never used.

// 7. Inconsistent Error Handling:
// - There's inconsistent handling of memory allocation failures (e.g., not always checking the result of `malloc` or `strdup`).

// 8. Potential Segmentation Fault:
// - If `current->next` is NULL after a redirection token, accessing `current->type` without checking could lead to a segmentation fault.

// 9. Lack of Comments:
// - The code could benefit from more comments explaining the logic, especially in complex parts like redirection handling.

// 10. Hardcoded Array Sizes:
// - Using `sizeof(char *) * (count + 1)` assumes all arguments will fit, which might not always be the case if there are more complex parsing rules in the future.

// /* Proposed Fixes */
// - Implement comprehensive error handling and cleanup paths for memory allocation failures.
// - Introduce a return type for `allocate_cmd` to signal success or failure.
// - Avoid modifying the command's redirection list during iteration in `parse_cmd`.
// - Create a helper function to check token types, reducing code duplication.
// - Add checks or redesign to prevent potential infinite loops with malformed input.
// - Remove or utilize unused variables like `flag`.
// - Standardize and ensure all memory allocation calls are checked for failure.
// - Add null checks where dereferencing could lead to segmentation faults.
// - Increase the use of comments to improve code readability and maintainability.
// - Consider dynamic resizing for arrays or lists if fixed sizes could be exceeded.