//
// Created by ninem on 11/23/2020.
//

#include "task_master.h"

char        *restartCommand(char **command) {
    t_pars *localJob;

    localJob = jobFinderByName(command[1]);
    kill(localJob->PID, SIGTERM);
    execut(localJob);
    return ft_strdup("job restarted\n");
}

char        *startCommand(char **command) {
    t_pars *localJob;

    localJob = jobFinderByName(command[1]);
    if (localJob->status != 0) {
        kill(localJob->PID, SIGCONT);
        return ft_strdup("started\n");
    } else {
        execut(localJob);
    }
    return ft_strdup("job already work\n");
}

char        *stopCommand(char **command) {
    t_pars *localJob;

    localJob = jobFinderByName(command[1]);
    if (localJob->status == 0)
        kill(localJob->PID, SIGSTOP);
    return ft_strdup("stoped\n");
}

char		*statusCommand(t_pars *listm)
{
    char	*tmpMsg;
    char	*msg;

    if (listm)
        msg = ft_strnew(0);
    while(listm)
    {
        tmpMsg = ft_strrejoin(listm->name, ft_strrejoin("\t\t", ft_itoa(listm->PID), 2), 2);
        switch (listm->status) {
            case STAT_WORK:  // online monitor
                tmpMsg = ft_strrejoin(tmpMsg, "\t\tWORK\n", 1);
                break;
            case STAT_END:
                tmpMsg = ft_strrejoin(tmpMsg, "\t\tEND\n", 1);
                break;
            case ERR_CANT_OPEN_DIR:
                tmpMsg = ft_strrejoin(tmpMsg, "\t\tCANT OPEN DIR\n", 1);
                break;
            case ERR_NOT_FOUND:
                tmpMsg = ft_strrejoin(tmpMsg, "\t\tNOT FOUND\n", 1);
                break;
            case ERR_CANT_OPEN_FILE:
                tmpMsg = ft_strrejoin(tmpMsg, "\t\tCANT OPEN FILE\n", 1);
                break;
            default:
                tmpMsg = ft_strrejoin(tmpMsg, "\t\tI DONT F KNOW\n", 1);
        }
        msg = ft_strrejoin(msg, tmpMsg, 3);
        listm = listm->next;
    }
    return (msg);
}