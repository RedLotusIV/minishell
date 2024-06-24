/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:20 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/23 18:48:10 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_pipe	*root;
	char	**path;

	if (ac != 1 || av[1])
	{
		write(2, "Error: No Args Needed\n", 23);
		exit(1);
	}
	path = set_path(env);
	root = readfrom(path);
	if (!root)
		exit(1);
	testing_commands(root, path);
	return (0);
}

t_pipe	*readfrom(char **path)
{
	t_parser	*parser;
	t_pipe		*root;

	root = NULL;
	while (1)
	{
		parser = malloc(sizeof(t_parser));
		if (!parser)
			return (NULL);
		parser->env = path;
		parser->prompt = set_cwd();
		parser->line = readline(parser->prompt);
		if (!parser->line)
		{
			free(parser->prompt);
			free(parser->line);
			free(parser);
			return (NULL);
		}
		add_history(parser->line);
		parser->result = mini_parsing(parser->line);
		if (!parser->result)
		{
			free(parser->prompt);
			free(parser->line);
			free(parser->result);
			free(parser);
			continue;
		}
		parser->head = tokenizer(parser->result);
		if (!parser->head)
			return (free_parser(parser, root), NULL);
		print_tokens(&parser->head);
		checking_parsing(parser->head);
		parser->cmd = parse_cmd(parser->head);
		if (!parser->cmd)
			return (free_parser(parser, root), NULL);
		print_command_details(parser->cmd);
		root = build_tree(parser->cmd);
		if (!root)
			return (free_parser(parser, root), NULL);
		print_tree(root);
		testing_commands(root, path);
		execute_commands(root);
		// printf("%s\n", prompt);
		free_parser(parser, root);
	}
	return (root);
}
