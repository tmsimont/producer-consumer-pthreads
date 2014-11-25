/* 
 * File:   main.c
 * Author: Trevor
 *
 * Created on November 9, 2014, 5:58 PM
 */

#include "server.h"


int report_status(void) {
    return 0;
}

/*
 * Initialize program and begin listening for client requests 
 */
int main(int argc, char** argv) {
    debug.print = 1;


    consumeDelay = 1;
    produceDelay = 2;
    monitorPullDelay = 1;


    pidx = 0;
    ridx = 0;

    ResourceBuffer *rb;
    Environment *env = malloc(sizeof(*env));

    // initialize mutex
    pthread_mutex_init(&bufferMutex, NULL);
    pthread_mutex_init(&consumerListMutex, NULL);
    pthread_mutex_init(&monitorListMutex, NULL);

    pthread_cond_init (&bufferHasRoom, NULL);

    // initialize consumersList
    consumerList = malloc(sizeof(*consumerList));
    consumerList->count = 0;

    // initialize monitorList
    monitorList = malloc(sizeof(*monitorList));
    monitorList->count = 0;

    // initialize buffer
    env->bufferp = resource_buffer_new(3);

    // initialize producers
    initialize_producers(env->bufferp, 5);

    // wait for connections
    server_listen(env);

    
    pthread_exit(NULL);

    return (EXIT_SUCCESS);
}


