#include "lexer.h"
#include "task_master.h"
#include <stdbool.h>

static bool	checkNumber(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	parserPrintErrorAndExit(char *str, t_lexem *lexem)
{
	if (lexem)
	{
		ft_putstr_fd("parser: line ", 2);
		ft_putnbr_fd(lexem->line, 2);
		ft_putstr_fd(": ", 2);
	}
	else
		ft_putstr_fd("parser: ", 2);
	ft_putendl_fd(str, 2);
	exit(-1);
}

t_pars  *default_job_creator()
{
    t_pars *data;
    data = (t_pars*)ft_memalloc(sizeof(t_pars));
    data->launch_from_start = true;
    return data;
}

static void		parserHandleEnv(__attribute__((unused)) char ***env, __attribute__((unused)) t_lexem **lexem)
{
	
}

static void		parserHandleString(char **string, t_lexem **lexem)
{
	if ((*lexem)->type != WORD)
		parserPrintErrorAndExit("expected number", (*lexem));
 	*string = (*lexem)->data;
	(*lexem)->data = NULL;
	*lexem = (*lexem)->next;
}

static void		parserHandleNumber(int *number, t_lexem **lexem)
{
	if ((*lexem)->type != WORD || checkNumber((*lexem)->data))
		parserPrintErrorAndExit("expected number", *lexem);
	*number = ft_atoi((*lexem)->data);
	*lexem = (*lexem)->next;
}

static void		parserHandleBool(bool *data, t_lexem **lexem)
{
	if (!ft_strcmp((*lexem)->data, "false"))
		*data = false;
	else if (!ft_strcmp((*lexem)->data, "true"))
		*data = true;
	else
		parserPrintErrorAndExit("expected boolean", *lexem);
	*lexem = (*lexem)->next;
}

static void	parserHandleParamsPart2(t_lexem **lexem, char *name_arg, t_pars *data)
{
	if (!ft_strcmp(name_arg, "work_directory"))
		parserHandleString(&data->path_to_workdir, lexem);
	else if (!ft_strcmp(name_arg, "umask_for_program"))
		parserHandleString(&data->umask, lexem);
	parserPrintErrorAndExit("argument not found", *lexem);
}

static void	parserHandleParams(t_lexem **lexem, char *name_arg, t_pars *data)
{
	if (!lexem)
		return ;
	if (!ft_strcmp(name_arg, "path"))
		parserHandleString(&data->path, lexem);
	else if (!ft_strcmp(name_arg, "number_of_process"))
		parserHandleNumber(&data->number_of_process, lexem);
	else if (!ft_strcmp(name_arg, "launch_from_start"))
		parserHandleBool(&data->launch_from_start, lexem);
	else if (!ft_strcmp(name_arg, "restart"))
		parserHandleNumber((int*)&data->restart, lexem);
	else if (!ft_strcmp(name_arg, "how_long_running"))
		parserHandleNumber(&data->how_long, lexem);
	else if (!ft_strcmp(name_arg, "how_match_restart"))
		parserHandleNumber(&data->how_match_restart, lexem);
	else if (!ft_strcmp(name_arg, "stop_signal"))
		parserHandleString(&data->signal, lexem);
	else if (!ft_strcmp(name_arg, "grace_full_stop"))
		parserHandleNumber(&data->grace_full_stop, lexem);
	else if (!ft_strcmp(name_arg, "pipe"))
		parserHandleNumber((int*)&data->pipe, lexem);
	else if (!ft_strcmp(name_arg, "env"))
		parserHandleEnv(&data->env, lexem);
	else
		parserHandleParamsPart2(lexem, name_arg, data);
}

static t_lexem	*parserCheckParams(t_lexem *lexem, t_pars *data)
{
	char		*name_arg;

	if (!lexem || lexem->type != BAT)
		return (lexem);
	lexem = lexem->next;
	if (!lexem || lexem->type != WORD)
		parserPrintErrorAndExit("expected word", lexem);
	name_arg = lexem->data;
	lexem = lexem->next;
	if (!lexem || lexem->type != EQUAL)
		parserPrintErrorAndExit("expected =", lexem);
	lexem = lexem->next;
	parserHandleParams(&lexem, name_arg, data);
	if (!lexem || lexem->type != SEMICOLON)
		parserPrintErrorAndExit("expected ;", lexem);
	lexem = lexem->next;
	if (!lexem || lexem->type != NEWLINE)
		parserPrintErrorAndExit("expected newline", lexem);
	return (parserCheckParams(lexem->next, data));
}

t_pars	*parser(t_lexem *lexem)
{
	t_pars	*data;

	if (!lexem)
		return (NULL);
	if (lexem->type == NEWLINE)
		return (parser(lexem->next));
	if (lexem->type != LEFT_BRACKET)
		parserPrintErrorAndExit("expected [", lexem);
	lexem = lexem->next;
	if (!lexem || lexem->type != WORD || ft_strcmp(lexem->data, "program"))
		parserPrintErrorAndExit("expected program", lexem);
	lexem = lexem->next;
	if (!lexem || lexem->type != COLON)
		parserPrintErrorAndExit("expected :", lexem);
	lexem = lexem->next;
	if (!lexem || lexem->type != WORD)
		parserPrintErrorAndExit("expected word", lexem);
	data = default_job_creator();
	data->name = lexem->data;
	lexem->data = NULL;
	if (!lexem->next || lexem->next->type != RIGHT_BRACKET)
		parserPrintErrorAndExit("expected ]", lexem);
	lexem = lexem->next;
	if (!lexem->next || lexem->next->type != NEWLINE)
		parserPrintErrorAndExit("expected newline", lexem);
	lexem = lexem->next->next;
	lexem = parserCheckParams(lexem, data);
	data->next = parser(lexem);
	return (data);
}
