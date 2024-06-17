/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:20 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/17 20:06:01 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	*root;

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

t_pipe	*readfrom(void)
{
	t_parser	*parser;
	t_pipe		*root;

	root = NULL;
	while (1)
	{
		parser = malloc(sizeof(t_parser));
		if (!parser)
			return (NULL);
		parser->line = readline("minishell$ ");
		if (!parser->line)
			break ;
		add_history(parser->line);
		parser->result = mini_parsing(parser->line);
		if (!parser->result)
			return (NULL);
		parser->head = tokenizer(parser->result);
		if (!parser->head)
			return (NULL);
		checking_parsing(parser->head);
		parser->cmd = parse_cmd(parser->head);
		root = build_tree(parser->cmd);
	}
	return (root);
}
