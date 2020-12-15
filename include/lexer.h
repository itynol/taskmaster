#ifndef LEXER_H
# define LEXER_H

typedef enum	s_type {
	LEFT_BRACKET,
	RIGHT_BRACKET,
	TAB,
	COLON,
	SEMICOLON,
	ROUND_LEFT_BRACKET,
	ROUND_RIGHT_BRACKET,
	EQUAL,
	NUMBER,
	WORD
}				t_type;

typedef struct	s_lexem {
	int				type;
	void			*data;
	struct s_lexem	*next;
}				t_lexem;

t_lexem			*lexer(int fd);

#endif
