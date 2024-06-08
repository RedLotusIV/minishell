#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type
{
	WORD = 1,
	PIPE,
	REDIR,
	INPUT,
	APPEND,
	HEREDOC,
}				t_type;

typedef struct	s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}				t_token;

typedef struct s_TreeNode
{
	struct s_token		*token;
	struct s_TreeNode	*left;
	struct s_TreeNode	*right;
}				t_TreeNode;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_token			*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct	s_parser
{
	char	*line;
	char	**commands;
	t_token	*head;
	char	**result;
}				t_parser;

// project libraries
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"

t_TreeNode	*build_tree(t_token *head);
t_TreeNode	*readfrom(void);

#endif
