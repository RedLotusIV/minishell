#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <errno.h>

typedef struct s_TreeNode
{
	void				*data;
	struct s_TreeNode	*left;
	struct s_TreeNode	*right;
}				t_TreeNode;

#endif