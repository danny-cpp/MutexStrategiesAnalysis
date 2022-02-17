#include "Lab2ProvidedAPI.h"


#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

int Lab2ProvidedAPI::ParseMsg(char *msg, Lab2ProvidedAPI::ClientRequest *rqst) {
    char *token;
    token = strsep(&msg, "-");
    rqst->pos = atoi(token);
    token = strsep(&msg, "-");
    rqst->is_read = atoi(token);
    token = strsep(&msg, "-");
    memcpy(rqst->msg, token, strlen(token)+1);
    return 0;
}

void Lab2ProvidedAPI::setContent(char *src, int pos, char **theArray) {
    int i;
    char *dst = theArray[pos];
    int length = MIN(strlen(src)+1, COM_BUFF_SIZE);
    usleep(ART_DELAY);
    for (i=0; i<length; ++i){
        dst[i] = src[i];
    }
}

void Lab2ProvidedAPI::getContent(char *dst, int pos, char **theArray) {
    int i;
    char *src = theArray[pos];
    int length = MIN(strlen(src)+1, COM_BUFF_SIZE);
    usleep(ART_DELAY);
    for (i=length-1;i>=0; --i ){
        dst[i] = src[i];
    }
}

void Lab2ProvidedAPI::saveTimes(double *time, int length) {
    FILE* op;
    int i;
    double elapsed_time = 0;
    for (i=0; i<length; ++i){
        elapsed_time += time[i];
    }
    elapsed_time /= length;
    if ((op = fopen("server_output_time_aggregated","a+")) == NULL){
        printf("Error opening the output file: server_output_time_aggregated.\n");
        exit(1);
    }
    fprintf(op, "%e\n", elapsed_time);
    fclose(op);
}


