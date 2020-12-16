#include "libft.h"
#include "lexer.h"
#include "ft_string.h"

void	push_back_lexem(t_lexem **begin, t_lexem **curr, t_lexem *new)
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

t_lexem	*check_type_lexem(char *buf, int *i)
{
	t_lexem		*lexem;
	int			type;

	if (buf[*i] == '[')
		type = LEFT_BRACKET;		
	else if (buf[*i] == ']')
		type = RIGHT_BRACKET;
	else if (buf[*i] == ':')
		type = COLON;
	else if (buf[*i] == '(')
		type = ROUND_LEFT_BRACKET;
	else if (buf[*i] == ')')
		type = ROUND_RIGHT_BRACKET;
	else if (buf[*i] == ';')
		type = SEMICOLON;
	else if (buf[*i] == '\t')
		type = BAT;
	else if (buf[*i] == '=')
		type = EQUAL;
	else
		return (NULL);
	(*i)++;
	lexem = (t_lexem*)ft_memalloc(sizeof(t_lexem));
	lexem->type = type;
	return (lexem);
}

int		check_spec_symbol(char c);

t_lexem *check_number_lexem(char *buf, int *i)
{
	t_lexem	*lexem;
	int		j;
	int		number;

	j = *i;
	if (buf[j] == '+' || buf[j] == '-')
		j++;
	while (buf[j])
	{
		if (check_spec_symbol(buf[j]) || ft_isspace(buf[j]))
			break ;
		else if (!ft_isdigit(buf[j]))
			return (NULL);
		j++;
	}
	lexem = (t_lexem*)ft_memalloc(sizeof(t_lexem));
	number = ft_atoi(&buf[*i]);
	lexem->type = NUMBER;
	lexem->data = (void*)ft_memalloc(sizeof(int));
	ft_memcpy(lexem->data, (void*)&number, sizeof(int)); //maybe ft_atoll?
	*i = j;
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

int		check_spec_symbol(char c) {
	if (c == '[')
		return 1;
	else if (c == ']')
		return 1;
	else if (c == '(')
		return 1;
	else if (c == ')')
		return 1;
	else if (c == ':')
		return 1;
	else if (c == ';')
		return 1;
	else if (c == '=')
		return 1;
	return 0;
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
		if (check_spec_symbol(current_buf[j]) || ft_isspace(current_buf[j]))
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
			else if ((new = check_type_lexem(buf, &i))
					|| (new = check_number_lexem(buf, &i))
					|| (new = check_word_lexem(&buf, &i, fd)))
				push_back_lexem(&begin, &curr, new);
			else
			{
				ft_putstr_fd("taskmaster: error lexer\n", 2);
				exit(-1);
			}
		}
		free(buf);
	}
	return (begin);
}
