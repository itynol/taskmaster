#ifndef LEXER_H
# define LEXER_H

#include "ft_string.h"

typedef enum	s_type {
	LEFT_BRACKET,
	RIGHT_BRACKET,
	BAT,
	COLON,
	SEMICOLON,
	ROUND_LEFT_BRACKET,
	ROUND_RIGHT_BRACKET,
	EQUAL,
	NEWLINE,
	WORD
}				t_type;

typedef struct	s_lexem {
	int				type;
	int				line;
	char			*data;
	struct s_lexem	*next;
}				t_lexem;

typedef struct	s_symbol {
	char		type;
	char		symbol;
	t_lexem*	(*func)(t_lexem *lexem, char **buf, int *i);
}				t_symbol;

void			pushBackLexem(t_lexem **begin, t_lexem **curr, t_lexem *new);
void			lexerHandleBackSlash(char **buf, int *i, t_string *new_word, int fd);
int				checkSpecSymbol(char c);
t_lexem			*lexer(int fd);

#endif
