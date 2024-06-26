/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:20 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/26 00:07:21 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_parser	*parser;
	char		**path;

	parser = NULL;
	if (ac != 1 || av[1])
	{
		write(2, "Error: No Args Needed\n", 23);
		exit(1);
	}
	path = set_path(env);
	parser = readfrom(path);
	if (!parser)
		exit(1);
	testing_commands(parser->root, path);
	return (0);
}

t_parser	*readfrom(char **path)
{
	t_parser	*parser;
	
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
		{
			free(parser->prompt);
			free(parser->line);
			free_char_array(parser->result);
			free_tokens(&parser->head);
			free(parser);
			return (NULL);	
		}
		print_tokens(&parser->head);
		checking_parsing(parser->head);
		parser->cmd = parse_cmd(parser->head);
		if (!parser->cmd)
		{
			free(parser->prompt);
			free(parser->line);
			free_char_array(parser->result);
			free_tokens(&parser->head);
			// free_cmd(parser->cmd);
			free(parser);
		}
		print_command_details(parser->cmd);
		parser->root = build_tree(parser->cmd);
		if (!parser->root)
			return (free_parser(parser), NULL);
		print_tree(parser->root);
		testing_commands(parser->root, path);
		execute_commands(parser->root);
		// printf("%s\n", prompt);
		free_parser(parser);
	}
	return (parser);
}
