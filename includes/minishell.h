#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_TreeNode
{
	char				*data;
	struct s_TreeNode	*left;
	struct s_TreeNode	*right;
}				t_TreeNode;

#endif
