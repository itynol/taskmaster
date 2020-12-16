#include "lexer.h"
#include "task_master.h"
#include <stdbool.h>

static bool		parserHandleEnv(char ***env, t_lexem **lexem)
{
	lexem = NULL;
	env = NULL;
	return true;	
}

static bool		parserHandleString(char **string, t_lexem **lexem)
{
	if ((*lexem)->type == NUMBER)
		*string = ft_itoa(*(int*)(*lexem)->data);
	else
 		*string = (char*)(*lexem)->data;
	(*lexem)->data = NULL;
	*lexem = (*lexem)->next;
	return true;
}

static bool 	parserHandleNumber(int *number, t_lexem **lexem)
{
	*number = *((int*)(*lexem)->data);
	*lexem = (*lexem)->next;
	return true;
}

static bool		parserHandleBool(bool *data, t_lexem **lexem)
{
	if (!ft_strcmp((char*)(*lexem)->data, "false"))
		*data = false;
	else if (!ft_strcmp((char*)(*lexem)->data, "true"))
		*data = true;
	else
		return false;
	*lexem = (*lexem)->next;
	return true;
}

static bool	parserHandleParamsPart2(t_lexem **lexem, char *name_arg, t_pars *data)
{
	if (!ft_strcmp(name_arg, "work_directory"))
		return (parserHandleString(&data->path_to_workdir, lexem));
	else if (!ft_strcmp(name_arg, "umask_for_programm"))
		return (parserHandleString(&data->umask, lexem));
	printf("%s not found\n", name_arg);
	return false;
}

static bool	parserHandleParams(t_lexem **lexem, char *name_arg, t_pars *data)
{
	if (!lexem)
		return false;
	if (!ft_strcmp(name_arg, "path"))
		return (parserHandleString(&data->path, lexem));
	else if (!ft_strcmp(name_arg, "number_of_process"))
		return (parserHandleNumber(&data->number_of_process, lexem));
	else if (!ft_strcmp(name_arg, "launch_from_start"))
		return (parserHandleBool(&data->launch_from_start, lexem));
	else if (!ft_strcmp(name_arg, "restart"))
		return (parserHandleNumber((int*)&data->restart, lexem));
	else if (!ft_strcmp(name_arg, "how_long_running"))
		return (parserHandleNumber(&data->how_long, lexem));
	else if (!ft_strcmp(name_arg, "howmuch_restart"))
		return (parserHandleNumber(&data->hm_wait, lexem));
	else if (!ft_strcmp(name_arg, "stop_signal"))
		return (parserHandleString(&data->signal, lexem));
	else if (!ft_strcmp(name_arg, "grasefull_stop"))
		return (parserHandleNumber(&data->grasefull, lexem));
	else if (!ft_strcmp(name_arg, "pipe"))
		return (parserHandleNumber((int*)&data->pipe, lexem));
	else if (!ft_strcmp(name_arg, "env"))
		return (parserHandleEnv(&data->env, lexem));
	return (parserHandleParamsPart2(lexem, name_arg, data));
}

void	*parserErrorNameBlock(t_lexem *lexem, int a)
{
	lexem = NULL;
	a = 0;
	return NULL;
}

static t_lexem	*parserCheckParams(t_lexem *lexem, t_pars *data)
{
	char		*name_arg;

	if (!lexem || lexem->type != TAB)
		return (lexem);
	lexem = lexem->next;
	if (!lexem || lexem->type != WORD)
		return NULL; // handle error
	name_arg = (char*)lexem->data;
	lexem = lexem->next;
	if (!lexem || lexem->type != EQUAL)
		return NULL; //handle error
	lexem = lexem->next;
	if (!parserHandleParams(&lexem, name_arg, data))
		return NULL; //handle error
	return (parserCheckParams(lexem->next, data));
}

// [ word : word ] \n
t_pars	*parser(t_lexem *lexem)
{
	t_pars	*data;

	if (!lexem)
		return (NULL);
	if (lexem->type != LEFT_BRACKET)
		return (parserErrorNameBlock(lexem, LEFT_BRACKET));
	lexem = lexem->next;
	if (!lexem || lexem->type != WORD || ft_strcmp((char*)lexem->data, "programm"))
		return (parserErrorNameBlock(lexem, WORD));
	lexem = lexem->next;
	if (!lexem || lexem->type != COLON)
		return (parserErrorNameBlock(lexem, COLON));
	lexem = lexem->next;
	if (!lexem || lexem->type != WORD)
		return (parserErrorNameBlock(lexem, WORD));
	if (!lexem->next || lexem->next->type != RIGHT_BRACKET)
		return (parserErrorNameBlock(lexem, RIGHT_BRACKET));
	data = (t_pars*)ft_memalloc(sizeof(t_pars));
	data->name = (char*)lexem->data;
	lexem->data = NULL;
	lexem = lexem->next->next;
	lexem = parserCheckParams(lexem, data);
	if (lexem)
		data->next = parser(lexem);
	return (data);
}
