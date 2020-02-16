#include "android_logger.h"

#include <iostream>
#include <unistd.h>
#include <android/log.h>

namespace {

static int pfd[2];
static pthread_t thr;
static const char *tag = "app";

static void *thread_func(void*)
{
    ssize_t rdsz;
    char buf[128];
    while((rdsz = read(pfd[0], buf, sizeof buf - 1)) > 0) {
        if(buf[rdsz - 1] == '\n') --rdsz;
        buf[rdsz] = 0;  /* add null-terminator */
        __android_log_write(ANDROID_LOG_INFO, tag, buf);
    }
    __android_log_write(ANDROID_LOG_INFO, tag, "logger done");
    return 0;
}

}

int start_logger(const char *app_name) {
    tag = app_name;

    /* make stdout line-buffered and stderr unbuffered */
    setvbuf(stdout, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);

    /* create the pipe and redirect stdout and stderr */
    pipe(pfd);
    dup2(pfd[1], 1);
    dup2(pfd[1], 2);

    /* spawn the logging thread */
    if (pthread_create(&thr, 0, thread_func, 0) == -1) {
        return -1;
    }
    pthread_detach(thr);
    return 0;
}
