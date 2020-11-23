//
// Created by ninem on 11/23/2020.
//

#include "task_master.h"

t_pars *jobFinderByName(char *name) {
    t_pars *jobList;

    jobList = list;
    while (jobList) {
        if (ft_strcmp(jobList->name, name) == 0)
            return jobList;
        jobList = jobList->next;
    }
    return NULL;
}