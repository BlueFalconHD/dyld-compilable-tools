#ifndef CORECRYPTO_COMPAT_H
#define CORECRYPTO_COMPAT_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <CommonCrypto/CommonCrypto.h>

#ifdef __cplusplus
}
#endif

#define CCSHA1_OUTPUT_SIZE    CC_SHA1_DIGEST_LENGTH
#define CCSHA256_OUTPUT_SIZE  CC_SHA256_DIGEST_LENGTH
#define CCSHA384_OUTPUT_SIZE  CC_SHA384_DIGEST_LENGTH

#define CS_HASHTYPE_SHA1                1
#define CS_HASHTYPE_SHA256              2
#define CS_HASHTYPE_SHA256_TRUNCATED    3
#define CS_HASHTYPE_SHA384              4

struct ccdigest_info {
    size_t   output_size;
    size_t   state_size;
    size_t   block_size;
    void   (*init)(void* ctx);
    void   (*update)(void* ctx, size_t len, const void* data);
    void   (*final)(void* ctx, unsigned char* digest);
};

const struct ccdigest_info* ccsha1_di(void);
const struct ccdigest_info* ccsha256_di(void);
const struct ccdigest_info* ccsha384_di(void);

#define CCSHA1_CONTEXT_SIZE     sizeof(CC_SHA1_CTX)
#define CCSHA256_CONTEXT_SIZE   sizeof(CC_SHA256_CTX)
#define CCSHA384_CONTEXT_SIZE   sizeof(CC_SHA512_CTX)

#define ccdigest_di_decl(di, ctx) \
    uint8_t ctx[(di)->state_size];

static inline void ccdigest_init(const struct ccdigest_info* di, void* ctx) {
    di->init(ctx);
}

static inline void ccdigest_update(const struct ccdigest_info* di, void* ctx, size_t len, const void* data) {
    di->update(ctx, len, data);
}

static inline void ccdigest_final(const struct ccdigest_info* di, void* ctx, unsigned char* digest) {
    di->final(ctx, digest);
}

static inline void ccdigest_di_clear(const struct ccdigest_info* di, void* ctx) {
    memset(ctx, 0, di->state_size);
}

#endif // CORECRYPTO_COMPAT_H
