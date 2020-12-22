#include "libft.h"
#include "lexer.h"
#include "ft_string.h"

const t_symbol	token_symbol[] = {
	{LEFT_BRACKET, '[', NULL},
	{RIGHT_BRACKET, ']', NULL},
	{BAT, '\t', NULL},
	{COLON, ':', NULL},
	{SEMICOLON, ';', NULL},
	{ROUND_LEFT_BRACKET, '(', NULL},
	{ROUND_RIGHT_BRACKET, ')', NULL},
	{EQUAL, '=', NULL},
	{-1, 0, NULL}
};

void	lexemPushBack(t_lexem **begin, t_lexem **curr, t_lexem *new)
{
	if (!*begin)
	{
		*begin = new;
		*curr = new;
	}
	else
	{
		(*curr)->next = new;
		*curr = new;
	}
}

t_lexem	*check_type_lexem(char *buf, int *pointer_buf)
{
	const t_symbol	*current_symbol;
	t_lexem			*lexem;
	int				type;

	type = -1;
	current_symbol = (const t_symbol*)&token_symbol[0];
	while (current_symbol->type != -1)
	{
		if (current_symbol->symbol == buf[*pointer_buf])
		{
			type = current_symbol->type;
			break ;
		}
		current_symbol++;
	}
	if (type == -1)
		return (NULL);
	(*pointer_buf)++;
	lexem = (t_lexem*)ft_memalloc(sizeof(t_lexem));
	lexem->type = type;
	return (lexem);
}


void	lexer_handle_back_slash(char **buf, int *i, t_string *new_word, int fd)
{
	(*i)++;
	if (!*buf[*i])
	{
		free(*buf);
		*i = 0;
		get_next_line(fd, buf);
		str_addback_char(new_word, '\n');
	}
	else
	{
		str_addback_char(new_word, *buf[*i]);
		(*i)++;
	}
}

int		checkReservedSymbol(char c) {
	const t_symbol	*current_symbol;

	current_symbol = (const t_symbol*)&token_symbol[0];
	while (current_symbol->type != -1)
	{
		if (current_symbol->symbol == c)
			return (1);
		current_symbol++;
	}
	return (0);
}

void	lexer_handle_quote(char **buf, int *i, t_string *new_string, int fd)
{
	char	*current_buf;
	int		j;

	current_buf = *buf;
	j = *i + 1;
	while (current_buf[j] != '\'')
	{
		if (!current_buf[j])
		{
			free(*buf);
			j = 0;
			if (get_next_line(fd, &current_buf) < 1)
			{
				ft_putendl_fd("Error: lexer quote", 2);
				exit(-1);
			}
			*buf = current_buf;
			str_addback_char(new_string, '\n');
			continue ;
		}
		str_addback_char(new_string, current_buf[j]);
		j++;
	}
	*i = j + 1;
}

t_lexem	*check_word_lexem(char **buf, int *i, int fd)
{
	t_lexem	*lexem;
	t_string new_string;
	char	*current_buf;
	int 	j;

	current_buf = *buf;
	j = *i;
	lexem = (t_lexem*)ft_memalloc(sizeof(t_lexem));
	ft_memset(&new_string, '\0', sizeof(new_string));
	lexem->type = WORD;
	while (current_buf[j])
	{
		if (checkReservedSymbol(current_buf[j]) || ft_isspace(current_buf[j]) || current_buf[j] == '#')
			break ;
		if (current_buf[j] == '\'')
			lexer_handle_quote(&current_buf, &j, &new_string, fd);
		else if (current_buf[j] == '\\')
			lexer_handle_back_slash(&current_buf, &j, &new_string, fd);
		else
		{
			str_addback_char(&new_string, current_buf[j]);
			j++;
		}
	}
	lexem->data = new_string.s;
	*buf = current_buf;
	*i = j;
	return lexem;
}

static void	lexerAddNewlineLexem(t_lexem **begin, t_lexem **curr)
{
	t_lexem	*tmp;

	tmp = (t_lexem*)ft_memalloc(sizeof(t_lexem));
	tmp->type = NEWLINE;
	lexemPushBack(begin, curr, tmp);
}

t_lexem	*lexer(int fd)
{
	char	*buf;
	t_lexem	*new;
	t_lexem	*begin;
	t_lexem	*curr;
	int		i;

	begin = NULL;
	curr = NULL;
	while (get_next_line(fd, &buf))
	{
		i = 0;
		while (buf[i])
		{
			if (buf[i] != '\t' && ft_isspace(buf[i]))
				i++;
			else if (buf[i] == '#')
				break ;
			else if ((new = check_type_lexem(buf, &i))
					|| (new = check_word_lexem(&buf, &i, fd)))
				lexemPushBack(&begin, &curr, new);
			else
			{
				ft_putstr_fd("taskmaster: error lexer\n", 2);
				exit(-1);
			}
		}
		lexerAddNewlineLexem(&begin, &curr);
		free(buf);
	}
	return (begin);
}
