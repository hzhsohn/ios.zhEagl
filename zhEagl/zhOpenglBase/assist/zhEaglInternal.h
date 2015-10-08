/*
<codex>
<version>1.0</version>
</codex>
*/

/* Degrees / Radians conversion */
#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * M_PI)
#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) / M_PI * 180.0)

/* Generic error reporting */
#define REPORT_ERROR(__FORMAT__, ...) printf("%s: %s\n", __FUNCTION__, [[NSString stringWithFormat:__FORMAT__, __VA_ARGS__] UTF8String])

/* EAGL and GL functions calling wrappers that log on error */
#define CALL_EAGL_FUNCTION(__FUNC__, ...) ({ EAGLError __error = __FUNC__( __VA_ARGS__ ); if(__error != kEAGLErrorSuccess) printf("%s() called from %s returned error %i\n", #__FUNC__, __FUNCTION__, __error); (__error ? NO : YES); })
#define CHECK_GL_ERROR() ({ GLenum __error = glGetError(); if(__error) printf("OpenGL error 0x%04X in %s\n", __error, __FUNCTION__); (__error ? NO : YES); })

/* Optional delegate methods support */
#ifndef __DELEGATE_IVAR__
#define __DELEGATE_IVAR__ _delegate
#endif
#ifndef __DELEGATE_METHODS_IVAR__
#define __DELEGATE_METHODS_IVAR__ _delegateMethods
#endif
#define TEST_DELEGATE_METHOD_BIT(__BIT__) (self->__DELEGATE_METHODS_IVAR__ & (1 << __BIT__))
#define SET_DELEGATE_METHOD_BIT(__BIT__, __NAME__) { if([self->__DELEGATE_IVAR__ respondsToSelector:@selector(__NAME__)]) self->__DELEGATE_METHODS_IVAR__ |= (1 << __BIT__); else self->__DELEGATE_METHODS_IVAR__ &= ~(1 << __BIT__); }



#ifndef GL_VERSION_1_2
    // 1.2 definitions...
    #define GL_BGR                          0x80E0
    #define GL_BGRA                         0x80E1
    #define GL_UNSIGNED_BYTE_3_3_2          0x8032
    #define GL_UNSIGNED_BYTE_2_3_3_REV      0x8362
    #define GL_UNSIGNED_SHORT_5_6_5         0x8363
    #define GL_UNSIGNED_SHORT_5_6_5_REV     0x8364
    #define GL_UNSIGNED_SHORT_4_4_4_4       0x8033
    #define GL_UNSIGNED_SHORT_4_4_4_4_REV   0x8365
    #define GL_UNSIGNED_SHORT_5_5_5_1       0x8034
    #define GL_UNSIGNED_SHORT_1_5_5_5_REV   0x8366
    #define GL_UNSIGNED_INT_8_8_8_8         0x8035
    #define GL_UNSIGNED_INT_8_8_8_8_REV     0x8367
    #define GL_UNSIGNED_INT_10_10_10_2      0x8036
    #define GL_UNSIGNED_INT_2_10_10_10_REV  0x8368
#endif

#ifndef GL_COMPRESSED_ALPHA
    #define GL_COMPRESSED_ALPHA             0x84E9
    #define GL_COMPRESSED_LUMINANCE         0x84EA
    #define GL_COMPRESSED_LUMINANCE_ALPHA   0x84EB
    #define GL_COMPRESSED_INTENSITY         0x84EC
    #define GL_COMPRESSED_RGB               0x84ED
    #define GL_COMPRESSED_RGBA              0x84EE
#endif
