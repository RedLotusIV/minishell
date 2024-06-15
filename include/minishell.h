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

typedef enum s_pipe_type
{
	PIPE_CMD,
	PIPE_PIPE
} t_pipe_type;

typedef struct s_redirection
{
	t_token					*redir;
	char					*arg;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_cmd
{
	char			**args;
	t_redirection	*redirections;
}				t_cmd;

typedef struct s_pipe
{
	struct s_pipe	*right;
	t_pipe_type  	left_type;
	union
	{
		struct s_pipe *pipe;
		t_cmd         *cmd;
	}	left;
}				t_pipe;

typedef struct	s_parser
{
	char	*line;
	t_token	*head;
	char	**result;
}				t_parser;

// project libraries
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"

t_pipe	*build_tree(t_token *head);
t_pipe	*readfrom(void);

#endif
