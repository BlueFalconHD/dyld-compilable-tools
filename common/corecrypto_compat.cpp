//
//  corecrypto_compat.cpp
//  dyld
//
//  Created by Hayes Dombroski on 1/22/25.
//

#include "corecrypto_compat.h"

const struct ccdigest_info* ccsha1_di(void) {
    static const struct ccdigest_info di = {
        CCSHA1_OUTPUT_SIZE,
        CCSHA1_CONTEXT_SIZE,
        CC_SHA1_BLOCK_BYTES,
        (void (*)(void*))CC_SHA1_Init,
        (void (*)(void*, size_t, const void*))CC_SHA1_Update,
        (void (*)(void*, unsigned char*))CC_SHA1_Final
    };
    return &di;
}

const struct ccdigest_info* ccsha256_di(void) {
    static const struct ccdigest_info di = {
        CCSHA256_OUTPUT_SIZE,
        CCSHA256_CONTEXT_SIZE,
        CC_SHA256_BLOCK_BYTES,
        (void (*)(void*))CC_SHA256_Init,
        (void (*)(void*, size_t, const void*))CC_SHA256_Update,
        (void (*)(void*, unsigned char*))CC_SHA256_Final
    };
    return &di;
}

const struct ccdigest_info* ccsha384_di(void) {
    static const struct ccdigest_info di = {
        CCSHA384_OUTPUT_SIZE,
        CCSHA384_CONTEXT_SIZE,
        CC_SHA384_BLOCK_BYTES,
        (void (*)(void*))CC_SHA384_Init,
        (void (*)(void*, size_t, const void*))CC_SHA384_Update,
        (void (*)(void*, unsigned char*))CC_SHA384_Final
    };
    return &di;
}
