/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:20 by amouhand          #+#    #+#             */
/*   Updated: 2024/05/30 19:38:57 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_TreeNode	*root;

	(void)env;
	if (ac != 1 || av[1])
	{
		write(2, "Error: No Args Needed\n", 23);
		exit(1);
	}
	root = readfrom();
	if (!root)
		exit(-1);
	return (0);
}

t_TreeNode	*readfrom(void)
{
	t_parser	*parser;
	t_TreeNode	*root;
	t_cmd		*head;

	while (1)
	{
		parser = malloc(sizeof(t_parser));
		if (!parser)
			return (NULL);
		parser->line = readline("minishell$ ");
		if (!parser->line)
			break ;
		add_history(parser->line);
		parser->commands = ft_split(parser->line, ' ');
		if (!parser->commands)
			return (NULL);
		parser->result = mini_parsing(parser->commands);
		if (!parser->result)
			return (NULL);
		parser->head = tokenizer(parser->result);
		if (!parser->head)
			return (NULL);
		parse_cmd(parser->head);
		// root = build_tree(parser->head);
	}
	return (root);
}