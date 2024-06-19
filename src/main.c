/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:20 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/19 21:21:27 by amouhand         ###   ########.fr       */
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
		char *prompt = ft_strjoin( "minishell$", getenv("PWD"));
		prompt = ft_strjoin(prompt, ": ");
		prompt = set_pwd(prompt);
		parser = malloc(sizeof(t_parser));
		if (!parser)
			return (NULL);
		parser->line = readline(prompt);
		if (!parser->line)
			break ;
		add_history(parser->line);
		parser->result = mini_parsing(parser->line);
		if (!parser->result)
			return (NULL);
		parser->head = tokenizer(parser->result);
		if (!parser->head)
			return (NULL);
		// print_tokens(&parser->head);
		checking_parsing(parser->head);
		parser->cmd = parse_cmd(parser->head);
		if (!parser->cmd)
			return (NULL);
		// print_command_details(parser->cmd);
		root = build_tree(parser->cmd);
		if (!root)
			return (NULL);
		// print_tree(root);
		testing_commands(root, path);
	}
	return (root);
}
