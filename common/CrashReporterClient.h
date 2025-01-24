//
//  CrashReporterClient.h
//  dyld
//
//  Created by Hayes Dombroski on 1/22/25.
//

#ifndef _LIBC_CRASHREPORTERCLIENT_H
#define _LIBC_CRASHREPORTERCLIENT_H

#include "stdint.h"

/* Fake the CrashReporterClient API */
#define CRGetCrashLogMessage() 0
#define CRSetCrashLogMessage(m) true
#define CRSetCrashLogMessage2(m) true

#define CRASH_REPORTER_CLIENT_HIDDEN __attribute__((visibility("hidden")))
#define CRASHREPORTER_ANNOTATIONS_VERSION 4
#define CRASHREPORTER_ANNOTATIONS_SECTION "__crash_info"

struct crashreporter_annotations_t {
    uint64_t version;        // unsigned long
    uint64_t message;        // char *
    uint64_t signature_string;    // char *
    uint64_t backtrace;        // char *
    uint64_t message2;        // char *
    uint64_t thread;        // uint64_t
    uint64_t dialog_mode;        // unsigned int
};

#endif
