// rendergl.cpp: core opengl rendering stuff

#include "engine.h"
#include "game.h"    //faned

bool hasVBO = false, hasDRE = false, hasOQ = false, hasTR = false, hasFBO = false, hasDS = false, hasTF = false, hasBE = false, hasBC = false, hasCM = false, hasNP2 = false, hasTC = false, hasS3TC = false, hasFXT1 = false, hasTE = false, hasMT = false, hasD3 = false, hasAF = false, hasVP2 = false, hasVP3 = false, hasPP = false, hasMDA = false, hasTE3 = false, hasTE4 = false, hasVP = false, hasFP = false, hasGLSL = false, hasGM = false, hasNVFB = false, hasSGIDT = false, hasSGISH = false, hasDT = false, hasSH = false, hasNVPCF = false, hasRN = false, hasPBO = false, hasFBB = false, hasUBO = false, hasBUE = false, hasMBR = false, hasFC = false, hasTEX = false;
int hasstencil = 0;

VAR(renderpath, 1, 0, 0);
VAR(glversion, 1, 0, 0);
VAR(glslversion, 1, 0, 0);

// GL_ARB_vertex_buffer_object, GL_ARB_pixel_buffer_object
PFNGLGENBUFFERSARBPROC       glGenBuffers_       = NULL;
PFNGLBINDBUFFERARBPROC       glBindBuffer_       = NULL;
PFNGLMAPBUFFERARBPROC        glMapBuffer_        = NULL;
PFNGLUNMAPBUFFERARBPROC      glUnmapBuffer_      = NULL;
PFNGLBUFFERDATAARBPROC       glBufferData_       = NULL;
PFNGLBUFFERSUBDATAARBPROC    glBufferSubData_    = NULL;
PFNGLDELETEBUFFERSARBPROC    glDeleteBuffers_    = NULL;
PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubData_ = NULL;

// GL_ARB_multitexture
PFNGLACTIVETEXTUREARBPROC       glActiveTexture_       = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTexture_ = NULL;
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2f_     = NULL;
PFNGLMULTITEXCOORD3FARBPROC     glMultiTexCoord3f_     = NULL;
PFNGLMULTITEXCOORD4FARBPROC     glMultiTexCoord4f_     = NULL;

// GL_ARB_vertex_program, GL_ARB_fragment_program
PFNGLGENPROGRAMSARBPROC              glGenProgramsARB_            = NULL;
PFNGLDELETEPROGRAMSARBPROC           glDeleteProgramsARB_         = NULL;
PFNGLBINDPROGRAMARBPROC              glBindProgramARB_            = NULL;
PFNGLPROGRAMSTRINGARBPROC            glProgramStringARB_          = NULL;
PFNGLGETPROGRAMIVARBPROC             glGetProgramivARB_           = NULL;
PFNGLPROGRAMENVPARAMETER4FARBPROC    glProgramEnvParameter4fARB_  = NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC   glProgramEnvParameter4fvARB_ = NULL;

// GL_EXT_gpu_program_parameters
PFNGLPROGRAMENVPARAMETERS4FVEXTPROC   glProgramEnvParameters4fv_   = NULL;
PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC glProgramLocalParameters4fv_ = NULL;

// GL_ARB_occlusion_query
PFNGLGENQUERIESARBPROC        glGenQueries_        = NULL;
PFNGLDELETEQUERIESARBPROC     glDeleteQueries_     = NULL;
PFNGLBEGINQUERYARBPROC        glBeginQuery_        = NULL;
PFNGLENDQUERYARBPROC          glEndQuery_          = NULL;
PFNGLGETQUERYIVARBPROC        glGetQueryiv_        = NULL;
PFNGLGETQUERYOBJECTIVARBPROC  glGetQueryObjectiv_  = NULL;
PFNGLGETQUERYOBJECTUIVARBPROC glGetQueryObjectuiv_ = NULL;

// GL_EXT_framebuffer_object
PFNGLBINDRENDERBUFFEREXTPROC        glBindRenderbuffer_        = NULL;
PFNGLDELETERENDERBUFFERSEXTPROC     glDeleteRenderbuffers_     = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC         glGenRenderbuffers_        = NULL;
PFNGLRENDERBUFFERSTORAGEEXTPROC     glRenderbufferStorage_     = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  glCheckFramebufferStatus_  = NULL;
PFNGLBINDFRAMEBUFFEREXTPROC         glBindFramebuffer_         = NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC      glDeleteFramebuffers_      = NULL;
PFNGLGENFRAMEBUFFERSEXTPROC         glGenFramebuffers_         = NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    glFramebufferTexture2D_    = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC glFramebufferRenderbuffer_ = NULL;
PFNGLGENERATEMIPMAPEXTPROC          glGenerateMipmap_          = NULL;

// GL_EXT_framebuffer_blit
PFNGLBLITFRAMEBUFFEREXTPROC         glBlitFramebuffer_         = NULL;

// OpenGL 2.0: GL_ARB_shading_language_100, GL_ARB_shader_objects, GL_ARB_fragment_shader, GL_ARB_vertex_shader
#ifndef __APPLE__
PFNGLCREATEPROGRAMPROC            glCreateProgram_            = NULL;
PFNGLDELETEPROGRAMPROC            glDeleteProgram_            = NULL;
PFNGLUSEPROGRAMPROC               glUseProgram_               = NULL;
PFNGLCREATESHADERPROC             glCreateShader_             = NULL;
PFNGLDELETESHADERPROC             glDeleteShader_             = NULL;
PFNGLSHADERSOURCEPROC             glShaderSource_             = NULL;
PFNGLCOMPILESHADERPROC            glCompileShader_            = NULL;
PFNGLGETSHADERIVPROC              glGetShaderiv_              = NULL;
PFNGLGETPROGRAMIVPROC             glGetProgramiv_             = NULL;
PFNGLATTACHSHADERPROC             glAttachShader_             = NULL;
PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog_        = NULL;
PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog_         = NULL;
PFNGLLINKPROGRAMPROC              glLinkProgram_              = NULL;
PFNGLGETUNIFORMLOCATIONPROC       glGetUniformLocation_       = NULL;
PFNGLUNIFORM1FPROC                glUniform1f_                = NULL;
PFNGLUNIFORM2FPROC                glUniform2f_                = NULL;
PFNGLUNIFORM3FPROC                glUniform3f_                = NULL;
PFNGLUNIFORM4FPROC                glUniform4f_                = NULL;
PFNGLUNIFORM1FVPROC               glUniform1fv_               = NULL;
PFNGLUNIFORM2FVPROC               glUniform2fv_               = NULL;
PFNGLUNIFORM3FVPROC               glUniform3fv_               = NULL;
PFNGLUNIFORM4FVPROC               glUniform4fv_               = NULL;
PFNGLUNIFORM1IPROC                glUniform1i_                = NULL;
PFNGLBINDATTRIBLOCATIONPROC       glBindAttribLocation_       = NULL;
PFNGLGETACTIVEUNIFORMPROC         glGetActiveUniform_         = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray_  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray_ = NULL;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer_      = NULL;

PFNGLUNIFORMMATRIX2X3FVPROC       glUniformMatrix2x3fv_       = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC       glUniformMatrix3x2fv_       = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC       glUniformMatrix2x4fv_       = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC       glUniformMatrix4x2fv_       = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC       glUniformMatrix3x4fv_       = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC       glUniformMatrix4x3fv_       = NULL;
#endif

// GL_EXT_draw_range_elements
PFNGLDRAWRANGEELEMENTSEXTPROC glDrawRangeElements_ = NULL;

// GL_EXT_blend_minmax
PFNGLBLENDEQUATIONEXTPROC glBlendEquation_ = NULL;

// GL_EXT_blend_color
PFNGLBLENDCOLOREXTPROC glBlendColor_ = NULL;

// GL_EXT_multi_draw_arrays
PFNGLMULTIDRAWARRAYSEXTPROC   glMultiDrawArrays_   = NULL;
PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElements_ = NULL;

// GL_ARB_texture_compression
PFNGLCOMPRESSEDTEXIMAGE3DARBPROC    glCompressedTexImage3D_    = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC    glCompressedTexImage2D_    = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DARBPROC    glCompressedTexImage1D_    = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC glCompressedTexSubImage3D_ = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC glCompressedTexSubImage2D_ = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC glCompressedTexSubImage1D_ = NULL;
PFNGLGETCOMPRESSEDTEXIMAGEARBPROC   glGetCompressedTexImage_   = NULL;

// GL_ARB_uniform_buffer_object
PFNGLGETUNIFORMINDICESPROC       glGetUniformIndices_       = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC     glGetActiveUniformsiv_     = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC    glGetUniformBlockIndex_    = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv_ = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC     glUniformBlockBinding_     = NULL;
PFNGLBINDBUFFERBASEPROC          glBindBufferBase_          = NULL;
PFNGLBINDBUFFERRANGEPROC         glBindBufferRange_         = NULL;

// GL_EXT_bindable_uniform
PFNGLUNIFORMBUFFEREXTPROC        glUniformBuffer_        = NULL;
PFNGLGETUNIFORMBUFFERSIZEEXTPROC glGetUniformBufferSize_ = NULL;
PFNGLGETUNIFORMOFFSETEXTPROC     glGetUniformOffset_     = NULL;

// GL_EXT_fog_coord
PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointer_ = NULL;

// GL_ARB_map_buffer_range
PFNGLMAPBUFFERRANGEPROC         glMapBufferRange_         = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange_ = NULL;

void *getprocaddress(const char *name)
{
    return SDL_GL_GetProcAddress(name);
}

VARP(ati_skybox_bug, 0, 0, 1);
VAR(ati_oq_bug, 0, 0, 1);
VAR(ati_minmax_bug, 0, 0, 1);
VAR(ati_dph_bug, 0, 0, 1);
VAR(ati_line_bug, 0, 0, 1);
VAR(ati_cubemap_bug, 0, 0, 1);
VAR(ati_ubo_bug, 0, 0, 1);
VAR(nvidia_scissor_bug, 0, 0, 1);
VAR(intel_immediate_bug, 0, 0, 1);
VAR(intel_vertexarray_bug, 0, 0, 1);
VAR(apple_glsldepth_bug, 0, 0, 1);
VAR(apple_ff_bug, 0, 0, 1);
VAR(apple_vp_bug, 0, 0, 1);
VAR(sdl_backingstore_bug, -1, 0, 1);
VAR(avoidshaders, 1, 0, 0);
VAR(preferglsl, 1, 0, 0);
VAR(minimizetcusage, 1, 0, 0);
VAR(emulatefog, 1, 0, 0);
VAR(usevp2, 1, 0, 0);
VAR(usevp3, 1, 0, 0);
VAR(usetexrect, 1, 0, 0);
VAR(hasglsl, 1, 0, 0);
VAR(useubo, 1, 0, 0);
VAR(usebue, 1, 0, 0);
VAR(usetexcompress, 1, 0, 0);
VAR(rtscissor, 0, 1, 1);
VAR(blurtile, 0, 1, 1);
VAR(rtsharefb, 0, 1, 1);

static bool checkseries(const char *s, int low, int high)
{
    while(*s && !isdigit(*s)) ++s;
    if(!*s) return false;
    int n = 0;
    while(isdigit(*s)) n = n*10 + (*s++ - '0');    
    return n >= low && n < high;
}

VAR(dbgexts, 0, 0, 1);

bool hasext(const char *exts, const char *ext)
{
    int len = strlen(ext);
    if(len) for(const char *cur = exts; (cur = strstr(cur, ext)); cur += len)
    {
        if((cur == exts || cur[-1] == ' ') && (cur[len] == ' ' || !cur[len])) return true;
    }
    return false;
}

void gl_checkextensions()
{
    const char *vendor = (const char *)glGetString(GL_VENDOR);
    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    const char *renderer = (const char *)glGetString(GL_RENDERER);
    const char *version = (const char *)glGetString(GL_VERSION);
    conoutf(CON_INIT, "Renderer: %s (%s)", renderer, vendor);
    conoutf(CON_INIT, "Driver: %s", version);

#ifdef __APPLE__
    extern int mac_osversion();
    int osversion = mac_osversion();  /* 0x0A0500 = 10.5 (Leopard) */
    sdl_backingstore_bug = -1;
#endif

    bool mesa = false, intel = false, ati = false, nvidia = false;
    if(strstr(renderer, "Mesa") || strstr(version, "Mesa"))
    {
        mesa = true;
        if(strstr(renderer, "Intel")) intel = true;
    }
    else if(strstr(vendor, "NVIDIA"))
        nvidia = true;
    else if(strstr(vendor, "ATI") || strstr(vendor, "Advanced Micro Devices"))
        ati = true;
    else if(strstr(vendor, "Intel"))
        intel = true;

    uint glmajorversion, glminorversion;
    if(sscanf(version, " %u.%u", &glmajorversion, &glminorversion) != 2) glversion = 100;
    else glversion = glmajorversion*100 + glminorversion*10;

    //extern int shaderprecision;
    // default to low precision shaders on certain cards, can be overridden with -f3
    // char *weakcards[] = { "GeForce FX", "Quadro FX", "6200", "9500", "9550", "9600", "9700", "9800", "X300", "X600", "FireGL", "Intel", "Chrome", NULL } 
    // if(shaderprecision==2) for(char **wc = weakcards; *wc; wc++) if(strstr(renderer, *wc)) shaderprecision = 1;

    GLint val;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);
    hwtexsize = val;

    if(hasext(exts, "GL_EXT_texture_env_combine") || hasext(exts, "GL_ARB_texture_env_combine"))
    {
        hasTE = true;
        if(hasext(exts, "GL_ARB_texture_env_crossbar")) hasTEX = true;
        if(hasext(exts, "GL_ATI_texture_env_combine3")) hasTE3 = true;
        if(hasext(exts, "GL_NV_texture_env_combine4")) hasTE4 = true;
        if(hasext(exts, "GL_EXT_texture_env_dot3") || hasext(exts, "GL_ARB_texture_env_dot3")) hasD3 = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_env_combine extension.");
    }
    else conoutf(CON_WARN, "WARNING: No texture_env_combine extension! (your video card is WAY too old)");

    if(hasext(exts, "GL_ARB_multitexture"))
    {
        glActiveTexture_       = (PFNGLACTIVETEXTUREARBPROC)      getprocaddress("glActiveTextureARB");
        glClientActiveTexture_ = (PFNGLCLIENTACTIVETEXTUREARBPROC)getprocaddress("glClientActiveTextureARB");
        glMultiTexCoord2f_     = (PFNGLMULTITEXCOORD2FARBPROC)    getprocaddress("glMultiTexCoord2fARB");
        glMultiTexCoord3f_     = (PFNGLMULTITEXCOORD3FARBPROC)    getprocaddress("glMultiTexCoord3fARB");
        glMultiTexCoord4f_     = (PFNGLMULTITEXCOORD4FARBPROC)    getprocaddress("glMultiTexCoord4fARB");
        hasMT = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_multitexture extension.");
    }
    else conoutf(CON_WARN, "WARNING: No multitexture extension!");


    if(hasext(exts, "GL_ARB_vertex_buffer_object")) 
    {
        hasVBO = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_vertex_buffer_object extension.");
    }
    else conoutf(CON_WARN, "WARNING: No vertex_buffer_object extension! (geometry heavy maps will be SLOW)");
#ifdef __APPLE__
    /* VBOs over 256KB seem to destroy performance on 10.5, but not in 10.6 */
    extern int maxvbosize;
    if(osversion < 0x0A0600) maxvbosize = min(maxvbosize, 8192);  
#endif

    if(hasext(exts, "GL_ARB_pixel_buffer_object"))
    {
        hasPBO = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_pixel_buffer_object extension.");
    }

    if(hasVBO || hasPBO)
    {
        glGenBuffers_       = (PFNGLGENBUFFERSARBPROC)      getprocaddress("glGenBuffersARB");
        glBindBuffer_       = (PFNGLBINDBUFFERARBPROC)      getprocaddress("glBindBufferARB");
        glMapBuffer_        = (PFNGLMAPBUFFERARBPROC)       getprocaddress("glMapBufferARB");
        glUnmapBuffer_      = (PFNGLUNMAPBUFFERARBPROC)     getprocaddress("glUnmapBufferARB");
        glBufferData_       = (PFNGLBUFFERDATAARBPROC)      getprocaddress("glBufferDataARB");
        glBufferSubData_    = (PFNGLBUFFERSUBDATAARBPROC)   getprocaddress("glBufferSubDataARB");
        glDeleteBuffers_    = (PFNGLDELETEBUFFERSARBPROC)   getprocaddress("glDeleteBuffersARB");
        glGetBufferSubData_ = (PFNGLGETBUFFERSUBDATAARBPROC)getprocaddress("glGetBufferSubDataARB");
    }

    if(hasext(exts, "GL_EXT_draw_range_elements"))
    {
        glDrawRangeElements_ = (PFNGLDRAWRANGEELEMENTSEXTPROC)getprocaddress("glDrawRangeElementsEXT");
        hasDRE = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_draw_range_elements extension.");
    }

    if(hasext(exts, "GL_EXT_multi_draw_arrays"))
    {
        glMultiDrawArrays_   = (PFNGLMULTIDRAWARRAYSEXTPROC)  getprocaddress("glMultiDrawArraysEXT");
        glMultiDrawElements_ = (PFNGLMULTIDRAWELEMENTSEXTPROC)getprocaddress("glMultiDrawElementsEXT");
        hasMDA = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_multi_draw_arrays extension.");
    }

#ifdef __APPLE__
    // floating point FBOs not fully supported until 10.5
    if(osversion>=0x0A0500)
#endif
    if(hasext(exts, "GL_ARB_texture_float") || hasext(exts, "GL_ATI_texture_float"))
    {
        hasTF = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_float extension.");
        shadowmap = 1;
        extern int smoothshadowmappeel;
        smoothshadowmappeel = 1;
    }

    if(hasext(exts, "GL_NV_float_buffer")) 
    {
        hasNVFB = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_NV_float_buffer extension.");
    }

    if(hasext(exts, "GL_EXT_framebuffer_object"))
    {
        glBindRenderbuffer_        = (PFNGLBINDRENDERBUFFEREXTPROC)       getprocaddress("glBindRenderbufferEXT");
        glDeleteRenderbuffers_     = (PFNGLDELETERENDERBUFFERSEXTPROC)    getprocaddress("glDeleteRenderbuffersEXT");
        glGenRenderbuffers_        = (PFNGLGENFRAMEBUFFERSEXTPROC)        getprocaddress("glGenRenderbuffersEXT");
        glRenderbufferStorage_     = (PFNGLRENDERBUFFERSTORAGEEXTPROC)    getprocaddress("glRenderbufferStorageEXT");
        glCheckFramebufferStatus_  = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) getprocaddress("glCheckFramebufferStatusEXT");
        glBindFramebuffer_         = (PFNGLBINDFRAMEBUFFEREXTPROC)        getprocaddress("glBindFramebufferEXT");
        glDeleteFramebuffers_      = (PFNGLDELETEFRAMEBUFFERSEXTPROC)     getprocaddress("glDeleteFramebuffersEXT");
        glGenFramebuffers_         = (PFNGLGENFRAMEBUFFERSEXTPROC)        getprocaddress("glGenFramebuffersEXT");
        glFramebufferTexture2D_    = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)   getprocaddress("glFramebufferTexture2DEXT");
        glFramebufferRenderbuffer_ = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)getprocaddress("glFramebufferRenderbufferEXT");
        glGenerateMipmap_          = (PFNGLGENERATEMIPMAPEXTPROC)         getprocaddress("glGenerateMipmapEXT");
        hasFBO = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_framebuffer_object extension.");

        if(hasext(exts, "GL_EXT_framebuffer_blit"))
        {
            glBlitFramebuffer_     = (PFNGLBLITFRAMEBUFFEREXTPROC)        getprocaddress("glBlitFramebufferEXT");
            hasFBB = true;
            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_framebuffer_blit extension.");
        }
    }
    else conoutf(CON_WARN, "WARNING: No framebuffer object support. (reflective water may be slow)");

    if(hasext(exts, "GL_ARB_occlusion_query"))
    {
        GLint bits;
        glGetQueryiv_ = (PFNGLGETQUERYIVARBPROC)getprocaddress("glGetQueryivARB");
        glGetQueryiv_(GL_SAMPLES_PASSED_ARB, GL_QUERY_COUNTER_BITS_ARB, &bits);
        if(bits)
        {
            glGenQueries_ =        (PFNGLGENQUERIESARBPROC)       getprocaddress("glGenQueriesARB");
            glDeleteQueries_ =     (PFNGLDELETEQUERIESARBPROC)    getprocaddress("glDeleteQueriesARB");
            glBeginQuery_ =        (PFNGLBEGINQUERYARBPROC)       getprocaddress("glBeginQueryARB");
            glEndQuery_ =          (PFNGLENDQUERYARBPROC)         getprocaddress("glEndQueryARB");
            glGetQueryObjectiv_ =  (PFNGLGETQUERYOBJECTIVARBPROC) getprocaddress("glGetQueryObjectivARB");
            glGetQueryObjectuiv_ = (PFNGLGETQUERYOBJECTUIVARBPROC)getprocaddress("glGetQueryObjectuivARB");
            hasOQ = true;
            if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_occlusion_query extension.");
#if defined(__APPLE__) && SDL_BYTEORDER == SDL_BIG_ENDIAN
            if(ati && (osversion<0x0A0500)) ati_oq_bug = 1;
#endif
            //if(ati_oq_bug) conoutf(CON_WARN, "WARNING: Using ATI occlusion query bug workaround. (use \"/ati_oq_bug 0\" to disable if unnecessary)");
        }
    }
    if(!hasOQ)
    {
        conoutf(CON_WARN, "WARNING: No occlusion query support! (large maps may be SLOW)");
        extern int vacubesize;
        vacubesize = 64;
        waterreflect = 0;
    }

    if(hasext(exts, "GL_ARB_vertex_program") && hasext(exts, "GL_ARB_fragment_program"))
    {
        hasVP = hasFP = true;
        glGenProgramsARB_ =            (PFNGLGENPROGRAMSARBPROC)            getprocaddress("glGenProgramsARB");
        glDeleteProgramsARB_ =         (PFNGLDELETEPROGRAMSARBPROC)         getprocaddress("glDeleteProgramsARB");
        glBindProgramARB_ =            (PFNGLBINDPROGRAMARBPROC)            getprocaddress("glBindProgramARB");
        glProgramStringARB_ =          (PFNGLPROGRAMSTRINGARBPROC)          getprocaddress("glProgramStringARB");
        glGetProgramivARB_ =           (PFNGLGETPROGRAMIVARBPROC)           getprocaddress("glGetProgramivARB");
        glProgramEnvParameter4fARB_ =  (PFNGLPROGRAMENVPARAMETER4FARBPROC)  getprocaddress("glProgramEnvParameter4fARB");
        glProgramEnvParameter4fvARB_ = (PFNGLPROGRAMENVPARAMETER4FVARBPROC) getprocaddress("glProgramEnvParameter4fvARB");

#ifndef __APPLE__
        glEnableVertexAttribArray_ =   (PFNGLENABLEVERTEXATTRIBARRAYPROC)   getprocaddress("glEnableVertexAttribArrayARB");
        glDisableVertexAttribArray_ =  (PFNGLDISABLEVERTEXATTRIBARRAYPROC)  getprocaddress("glDisableVertexAttribArrayARB");
        glVertexAttribPointer_ =       (PFNGLVERTEXATTRIBPOINTERPROC)       getprocaddress("glVertexAttribPointerARB");
#endif

        if(ati) ati_dph_bug = ati_line_bug = 1;

#ifdef __APPLE__
        if(osversion>=0x0A0500) // fixed in 1055 for some hardware.. but not all..
        {
            apple_ff_bug = 1;
            //conoutf(CON_WARN, "WARNING: Using Leopard ARB_position_invariant bug workaround. (use \"/apple_ff_bug 0\" to disable if unnecessary)");
        }
#endif
    }
    
    if(glversion >= 200)
    {
#ifndef __APPLE__
        glCreateProgram_ =            (PFNGLCREATEPROGRAMPROC)            getprocaddress("glCreateProgram");
        glDeleteProgram_ =            (PFNGLDELETEPROGRAMPROC)            getprocaddress("glDeleteProgram");
        glUseProgram_ =               (PFNGLUSEPROGRAMPROC)               getprocaddress("glUseProgram");
        glCreateShader_ =             (PFNGLCREATESHADERPROC)             getprocaddress("glCreateShader");
        glDeleteShader_ =             (PFNGLDELETESHADERPROC)             getprocaddress("glDeleteShader");
        glShaderSource_ =             (PFNGLSHADERSOURCEPROC)             getprocaddress("glShaderSource");
        glCompileShader_ =            (PFNGLCOMPILESHADERPROC)            getprocaddress("glCompileShader");
        glGetShaderiv_ =              (PFNGLGETSHADERIVPROC)              getprocaddress("glGetShaderiv");
        glGetProgramiv_ =             (PFNGLGETPROGRAMIVPROC)             getprocaddress("glGetProgramiv");
        glAttachShader_ =             (PFNGLATTACHSHADERPROC)             getprocaddress("glAttachShader");
        glGetProgramInfoLog_ =        (PFNGLGETPROGRAMINFOLOGPROC)        getprocaddress("glGetProgramInfoLog");
        glGetShaderInfoLog_ =         (PFNGLGETSHADERINFOLOGPROC)         getprocaddress("glGetShaderInfoLog");
        glLinkProgram_ =              (PFNGLLINKPROGRAMPROC)              getprocaddress("glLinkProgram");
        glGetUniformLocation_ =       (PFNGLGETUNIFORMLOCATIONPROC)       getprocaddress("glGetUniformLocation");
        glUniform1f_ =                (PFNGLUNIFORM1FPROC)                getprocaddress("glUniform1f");
        glUniform2f_ =                (PFNGLUNIFORM2FPROC)                getprocaddress("glUniform2f");
        glUniform3f_ =                (PFNGLUNIFORM3FPROC)                getprocaddress("glUniform3f");
        glUniform4f_ =                (PFNGLUNIFORM4FPROC)                getprocaddress("glUniform4f");
        glUniform1fv_ =               (PFNGLUNIFORM1FVPROC)               getprocaddress("glUniform1fv");
        glUniform2fv_ =               (PFNGLUNIFORM2FVPROC)               getprocaddress("glUniform2fv");
        glUniform3fv_ =               (PFNGLUNIFORM3FVPROC)               getprocaddress("glUniform3fv");
        glUniform4fv_ =               (PFNGLUNIFORM4FVPROC)               getprocaddress("glUniform4fv");
        glUniform1i_ =                (PFNGLUNIFORM1IPROC)                getprocaddress("glUniform1i");
        glBindAttribLocation_ =       (PFNGLBINDATTRIBLOCATIONPROC)       getprocaddress("glBindAttribLocation");
        glGetActiveUniform_ =         (PFNGLGETACTIVEUNIFORMPROC)         getprocaddress("glGetActiveUniform");
        glEnableVertexAttribArray_ =  (PFNGLENABLEVERTEXATTRIBARRAYPROC)  getprocaddress("glEnableVertexAttribArray");
        glDisableVertexAttribArray_ = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) getprocaddress("glDisableVertexAttribArray");
        glVertexAttribPointer_ =      (PFNGLVERTEXATTRIBPOINTERPROC)      getprocaddress("glVertexAttribPointer");

        if(glversion >= 210)
        {
            glUniformMatrix2x3fv_ =   (PFNGLUNIFORMMATRIX2X3FVPROC)       getprocaddress("glUniformMatrix2x3fv");
            glUniformMatrix3x2fv_ =   (PFNGLUNIFORMMATRIX3X2FVPROC)       getprocaddress("glUniformMatrix3x2fv");
            glUniformMatrix2x4fv_ =   (PFNGLUNIFORMMATRIX2X4FVPROC)       getprocaddress("glUniformMatrix2x4fv");
            glUniformMatrix4x2fv_ =   (PFNGLUNIFORMMATRIX4X2FVPROC)       getprocaddress("glUniformMatrix4x2fv");
            glUniformMatrix3x4fv_ =   (PFNGLUNIFORMMATRIX3X4FVPROC)       getprocaddress("glUniformMatrix3x4fv");
            glUniformMatrix4x3fv_ =   (PFNGLUNIFORMMATRIX4X3FVPROC)       getprocaddress("glUniformMatrix4x3fv");
        }
#endif

        extern bool checkglslsupport();
        if(checkglslsupport())
        {
            hasGLSL = true;
            hasglsl = 1;
#ifdef __APPLE__
            //if(osversion<0x0A0500) ??
            if(hasVP && hasFP) apple_glsldepth_bug = 1;
#endif
            //if(apple_glsldepth_bug) conoutf(CON_WARN, "WARNING: Using Apple GLSL depth bug workaround. (use \"/apple_glsldepth_bug 0\" to disable if unnecessary");

            const char *str = (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
            uint majorversion, minorversion;
            if(!str || sscanf(str, " %u.%u", &majorversion, &minorversion) != 2) glslversion = 100;
            else glslversion = majorversion*100 + minorversion;
#ifdef __APPLE__
            if(osversion >= 0x0A0600) { if(glslversion >= 120) preferglsl = 1; }
            else
#endif
            if(glslversion >= 130) preferglsl = 1;
        }
    }

    extern int reservedynlighttc, reserveshadowmaptc, batchlightmaps, ffdynlights, fpdepthfx;
    if(ati)
    {
        //conoutf(CON_WARN, "WARNING: ATI cards may show garbage in skybox. (use \"/ati_skybox_bug 1\" to fix)");

        reservedynlighttc = 2;
        reserveshadowmaptc = 3;
        minimizetcusage = 1;
        emulatefog = 1;
        if(hasTF && hasNVFB) fpdepthfx = 1;
    }
    else if(nvidia)
    {
        reservevpparams = 10;
        rtsharefb = 0; // work-around for strange driver stalls involving when using many FBOs
        extern int filltjoints;
        if(!hasext(exts, "GL_EXT_gpu_shader4")) filltjoints = 0; // DX9 or less NV cards seem to not cause many sparklies

        if(hasFBO && !hasTF) nvidia_scissor_bug = 1; // 5200 bug, clearing with scissor on an FBO messes up on reflections, may affect lesser cards too 
        extern int fpdepthfx;
        if(hasTF && (!strstr(renderer, "GeForce") || !checkseries(renderer, 6000, 6600)))
            fpdepthfx = 1; // FP filtering causes software fallback on 6200?
    }
    else
    {
        if(intel)
        {
#ifdef __APPLE__
            apple_vp_bug = 1;
            intel_immediate_bug = 1;
#endif
#ifdef WIN32
            intel_immediate_bug = 1;
            intel_vertexarray_bug = 1;
#endif
        }

        if(!hasGLSL || !preferglsl)
        {
            avoidshaders = 1;
            if(hwtexsize < 4096)
            {
                maxtexsize = hwtexsize >= 2048 ? 512 : 256;
                batchlightmaps = 0;
            }
            if(!hasTF) ffdynlights = 0;
        }

        reservevpparams = 20;

        if(!hasOQ) waterrefract = 0;
    }

    bool hasshaders = (hasVP && hasFP) || hasGLSL;
    if(hasshaders)
    {
        extern int matskel;
        if(!avoidshaders) 
        {
            matskel = 0;
        }
    }

    if(hasext(exts, "GL_NV_vertex_program2_option")) { usevp2 = 1; hasVP2 = true; }
    if(hasext(exts, "GL_NV_vertex_program3")) { usevp3 = 1; hasVP3 = true; }

    if(hasext(exts, "GL_EXT_gpu_program_parameters"))
    {
        glProgramEnvParameters4fv_   = (PFNGLPROGRAMENVPARAMETERS4FVEXTPROC)  getprocaddress("glProgramEnvParameters4fvEXT");
        glProgramLocalParameters4fv_ = (PFNGLPROGRAMLOCALPARAMETERS4FVEXTPROC)getprocaddress("glProgramLocalParameters4fvEXT");
        hasPP = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_gpu_program_parameters extension.");
    }

    if(hasext(exts, "GL_ARB_map_buffer_range"))
    {
        glMapBufferRange_         = (PFNGLMAPBUFFERRANGEPROC)        getprocaddress("glMapBufferRange");
        glFlushMappedBufferRange_ = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)getprocaddress("glFlushMappedBufferRange");
        hasMBR = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_map_buffer_range.");
    }

    if(hasext(exts, "GL_ARB_uniform_buffer_object"))
    {
        glGetUniformIndices_       = (PFNGLGETUNIFORMINDICESPROC)      getprocaddress("glGetUniformIndices");
        glGetActiveUniformsiv_     = (PFNGLGETACTIVEUNIFORMSIVPROC)    getprocaddress("glGetActiveUniformsiv");
        glGetUniformBlockIndex_    = (PFNGLGETUNIFORMBLOCKINDEXPROC)   getprocaddress("glGetUniformBlockIndex");
        glGetActiveUniformBlockiv_ = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)getprocaddress("glGetActiveUniformBlockiv");
        glUniformBlockBinding_     = (PFNGLUNIFORMBLOCKBINDINGPROC)    getprocaddress("glUniformBlockBinding");
        glBindBufferBase_          = (PFNGLBINDBUFFERBASEPROC)         getprocaddress("glBindBufferBase");
        glBindBufferRange_         = (PFNGLBINDBUFFERRANGEPROC)        getprocaddress("glBindBufferRange");

        useubo = 1;
        hasUBO = true;
        if(ati) ati_ubo_bug = 1;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_uniform_buffer_object extension.");
    }
    else if(hasext(exts, "GL_EXT_bindable_uniform"))
    {
        glUniformBuffer_        = (PFNGLUNIFORMBUFFEREXTPROC)       getprocaddress("glUniformBufferEXT");
        glGetUniformBufferSize_ = (PFNGLGETUNIFORMBUFFERSIZEEXTPROC)getprocaddress("glGetUniformBufferSizeEXT");
        glGetUniformOffset_     = (PFNGLGETUNIFORMOFFSETEXTPROC)    getprocaddress("glGetUniformOffsetEXT");

        usebue = 1;
        hasBUE = true;
        if(ati) ati_ubo_bug = 1;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_bindable_uniform extension.");
    }

    if(hasext(exts, "GL_EXT_texture_rectangle") || hasext(exts, "GL_ARB_texture_rectangle"))
    {
        usetexrect = 1;
        hasTR = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_rectangle extension.");
    }
    else if(hasMT && hasshaders) conoutf(CON_WARN, "WARNING: No texture rectangle support. (no full screen shaders)");

    if(hasext(exts, "GL_EXT_packed_depth_stencil") || hasext(exts, "GL_NV_packed_depth_stencil"))
    {
        hasDS = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_packed_depth_stencil extension.");
    }

    if(hasext(exts, "GL_EXT_blend_minmax"))
    {
        glBlendEquation_ = (PFNGLBLENDEQUATIONEXTPROC) getprocaddress("glBlendEquationEXT");
        hasBE = true;
        if(ati) ati_minmax_bug = 1;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_blend_minmax extension.");
    }

    if(hasext(exts, "GL_EXT_blend_color"))
    {
        glBlendColor_ = (PFNGLBLENDCOLOREXTPROC) getprocaddress("glBlendColorEXT");
        hasBC = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_blend_color extension.");
    }

    if(hasext(exts, "GL_EXT_fog_coord"))
    {
        glFogCoordPointer_ = (PFNGLFOGCOORDPOINTEREXTPROC) getprocaddress("glFogCoordPointerEXT");
        hasFC = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_fog_coord extension.");
    }

    if(hasext(exts, "GL_ARB_texture_cube_map"))
    {
        GLint val;
        glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB, &val);
        hwcubetexsize = val;
        hasCM = true;
        // On Catalyst 10.2, issuing an occlusion query on the first draw using a given cubemap texture causes a nasty crash
        if(ati) ati_cubemap_bug = 1;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_cube_map extension.");
    }
    else conoutf(CON_WARN, "WARNING: No cube map texture support. (no reflective glass)");

    extern int usenp2;
    if(hasext(exts, "GL_ARB_texture_non_power_of_two"))
    {
        hasNP2 = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_non_power_of_two extension.");
    }
    else if(usenp2) conoutf(CON_WARN, "WARNING: Non-power-of-two textures not supported!");

    if(hasext(exts, "GL_ARB_texture_compression"))
    {
        glCompressedTexImage3D_ =    (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)   getprocaddress("glCompressedTexImage3DARB");
        glCompressedTexImage2D_ =    (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)   getprocaddress("glCompressedTexImage2DARB");
        glCompressedTexImage1D_ =    (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)   getprocaddress("glCompressedTexImage1DARB");
        glCompressedTexSubImage3D_ = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)getprocaddress("glCompressedTexSubImage3DARB");
        glCompressedTexSubImage2D_ = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)getprocaddress("glCompressedTexSubImage2DARB");
        glCompressedTexSubImage1D_ = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)getprocaddress("glCompressedTexSubImage1DARB");
        glGetCompressedTexImage_ =   (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)  getprocaddress("glGetCompressedTexImageARB");

        hasTC = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_texture_compression.");

        if(hasext(exts, "GL_EXT_texture_compression_s3tc"))
        {
            hasS3TC = true;
#ifdef __APPLE__
            usetexcompress = 1;
#else
            if(!mesa) usetexcompress = 2;
#endif
            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_s3tc extension.");
        }
        else if(hasext(exts, "GL_EXT_texture_compression_dxt1") && hasext(exts, "GL_ANGLE_texture_compression_dxt3") && hasext(exts, "GL_ANGLE_texture_compression_dxt5"))
        {
            hasS3TC = true;
            if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_compression_dxt1 extension.");
        }
        if(hasext(exts, "GL_3DFX_texture_compression_FXT1"))
        {
            hasFXT1 = true;
            if(mesa) usetexcompress = max(usetexcompress, 1);
            if(dbgexts) conoutf(CON_INIT, "Using GL_3DFX_texture_compression_FXT1.");
        }
    }

    if(hasext(exts, "GL_EXT_texture_filter_anisotropic"))
    {
       GLint val;
       glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &val);
       hwmaxaniso = val;
       hasAF = true;
       if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_texture_filter_anisotropic extension.");
    }

    if(hasext(exts, "GL_SGIS_generate_mipmap"))
    {
        hasGM = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_SGIS_generate_mipmap extension.");
    }

    if(hasext(exts, "GL_ARB_depth_texture"))
    {
        hasSGIDT = hasDT = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_depth_texture extension.");
    }
    else if(hasext(exts, "GL_SGIX_depth_texture"))
    {
        hasSGIDT = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_SGIX_depth_texture extension.");
    }

    if(hasext(exts, "GL_ARB_shadow"))
    {
        hasSGISH = hasSH = true;
        if(nvidia || (ati && strstr(renderer, "Radeon HD"))) hasNVPCF = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_ARB_shadow extension.");
    }
    else if(hasext(exts, "GL_SGIX_shadow"))
    {
        hasSGISH = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_SGIX_shadow extension.");
    }

    if(hasext(exts, "GL_EXT_rescale_normal"))
    {
        hasRN = true;
        if(dbgexts) conoutf(CON_INIT, "Using GL_EXT_rescale_normal extension.");
    }

    if(!hasSGIDT && !hasSGISH) shadowmap = 0;

    if(hasext(exts, "GL_EXT_gpu_shader4") && !avoidshaders)
    {
        // on DX10 or above class cards (i.e. GF8 or RadeonHD) enable expensive features
        extern int grass, glare, maxdynlights, depthfxsize, depthfxrect, depthfxfilter, blurdepthfx;
        grass = 1;
        if(hasOQ)
        {
            waterfallrefract = 1;
            glare = 1;
            maxdynlights = MAXDYNLIGHTS;
            if(hasTR)
            {
                depthfxsize = 10;
                depthfxrect = 1;
                depthfxfilter = 0;
                blurdepthfx = 0;
            }
        }
    }
}

void glext(char *ext)
{
    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    intret(hasext(exts, ext) ? 1 : 0);
}
COMMAND(glext, "s");

void gl_init(int w, int h, int bpp, int depth, int fsaa)
{
    glViewport(0, 0, w, h);
    glClearColor(0, 0, 0, 0);
    glClearDepth(1);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    
    glDisable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    //glHint(GL_FOG_HINT, GL_NICEST);
    GLfloat fogcolor[4] = { 0, 0, 0, 0 };
    glFogfv(GL_FOG_COLOR, fogcolor);
    

    glEnable(GL_LINE_SMOOTH);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);

#ifdef __APPLE__
    if(sdl_backingstore_bug)
    {
        if(fsaa)
        {
            sdl_backingstore_bug = 1;
            // since SDL doesn't add kCGLPFABackingStore to the pixelformat and so it isn't guaranteed to be preserved - only manifests when using fsaa?
            //conoutf(CON_WARN, "WARNING: Using SDL backingstore workaround. (use \"/sdl_backingstore_bug 0\" to disable if unnecessary)");
        }
        else sdl_backingstore_bug = -1;
    }
#endif

    extern int useshaders, forceglsl;
    bool hasshaders = (hasVP && hasFP) || hasGLSL;
    if(!useshaders || (useshaders<0 && avoidshaders) || !hasMT || !hasshaders)
    {
        if(!hasMT || !hasshaders) conoutf(CON_WARN, "WARNING: No shader support! Using fixed-function fallback. (no fancy visuals for you)");
        else if(useshaders<0 && avoidshaders) conoutf(CON_WARN, "WARNING: Disabling shaders for extra performance. (use \"/shaders 1\" to enable shaders if desired)");
        renderpath = R_FIXEDFUNCTION;
    }
    else renderpath = hasGLSL ? ((forceglsl && (forceglsl > 0 || preferglsl)) || !hasVP || !hasFP ? (forceglsl ? R_GLSLANG : R_FIXEDFUNCTION) : R_ASMGLSLANG) : R_ASMSHADER;

    extern void setupshaders();
    setupshaders();

    static const char * const rpnames[4] = { "fixed-function", "assembly shader", "GLSL shader", "assembly/GLSL shader" };
    conoutf(CON_INIT, "Rendering using the OpenGL %s path.", rpnames[renderpath]);

    inittmus();
    setuptexcompress();
}

void cleanupgl()
{
    extern int nomasks, nolights, nowater;
    nomasks = nolights = nowater = 0;

    extern void cleanupmotionblur();
    cleanupmotionblur();

    extern void clearminimap();
    clearminimap();
}

#define VARRAY_INTERNAL
#include "varray.h"

VAR(wireframe, 0, 0, 1);

ICOMMAND(getcamyaw, "", (), floatret(camera1->yaw));
ICOMMAND(getcampitch, "", (), floatret(camera1->pitch));
ICOMMAND(getcamroll, "", (), floatret(camera1->roll));
ICOMMAND(getcampos, "", (), 
{
    defformatstring(pos)("%s %s %s", floatstr(camera1->o.x), floatstr(camera1->o.y), floatstr(camera1->o.z));
    result(pos);
});

vec worldpos, camdir, camright, camup;

void findorientation()
{
    mvmatrix.transposedtransformnormal(vec(viewmatrix.getcolumn(1)), camdir);
    mvmatrix.transposedtransformnormal(vec(viewmatrix.getcolumn(0)).neg(), camright);
    mvmatrix.transposedtransformnormal(vec(viewmatrix.getcolumn(2)), camup);

    if(raycubepos(camera1->o, camdir, worldpos, 0, RAY_CLIPMAT|RAY_SKIPFIRST) == -1)
        worldpos = vec(camdir).mul(2*worldsize).add(camera1->o); //otherwise 3dgui won't work when outside of map
}

void transplayer()
{
    // move from RH to Z-up LH quake style worldspace
    glLoadMatrixf(viewmatrix.v);

    glRotatef(camera1->roll, 0, 1, 0);
    glRotatef(camera1->pitch, -1, 0, 0);
    glRotatef(camera1->yaw, 0, 0, -1);

    glTranslatef(-camera1->o.x, -camera1->o.y, -camera1->o.z);   
}

float curfov = 100, curavatarfov = 65, fovy, aspect;
int farplane;
VARP(zoominvel, 0, 250, 5000);
VARP(zoomoutvel, 0, 100, 5000);
VARP(zoomfov, 10, 35, 60);
VARP(fov, 10, 100, 150);
VAR(avatarzoomfov, 10, 25, 60);
VAR(avatarfov, 10, 65, 150);
FVAR(avatardepth, 0, 0.5f, 1);
FVARNP(aspect, forceaspect, 0, 0, 1e3f);

static float zoomprogress = 0;
VAR(zoom, -1, 0, 1);

void disablezoom()
{
    zoom = 0;
    zoomprogress = 0;
}

void computezoom()
{
    if(!zoom) { zoomprogress = 0; curfov = fov; curavatarfov = avatarfov; return; }
    if(zoom > 0) zoomprogress = zoominvel ? min(zoomprogress + float(elapsedtime) / zoominvel, 1.0f) : 1;
    else
    {
        zoomprogress = zoomoutvel ? max(zoomprogress - float(elapsedtime) / zoomoutvel, 0.0f) : 0;
        if(zoomprogress <= 0) zoom = 0;
    }
    curfov = zoomfov*zoomprogress + fov*(1 - zoomprogress);
    curavatarfov = avatarzoomfov*zoomprogress + avatarfov*(1 - zoomprogress);
}

FVARP(zoomsens, 1e-3f, 1, 1000);
FVARP(zoomaccel, 0, 0, 1000);
VARP(zoomautosens, 0, 1, 1);
FVARP(sensitivity, 1e-3f, 3, 1000);
FVARP(sensitivityscale, 1e-3f, 1, 1000);
VARP(invmouse, 0, 0, 1);
FVARP(mouseaccel, 0, 0, 1000);
 
VAR(thirdperson, 0, 0, 2);
FVAR(thirdpersondistance, 0, 20, 50);
FVAR(thirdpersonup, -25, 0, 25);
FVAR(thirdpersonside, -25, 0, 25);
physent *camera1 = NULL;
bool detachedcamera = false;
bool isthirdperson() { return player!=camera1 || detachedcamera || reflecting; }

void fixcamerarange()
{
    const float MAXPITCH = 90.0f;
    if(camera1->pitch>MAXPITCH) camera1->pitch = MAXPITCH;
    if(camera1->pitch<-MAXPITCH) camera1->pitch = -MAXPITCH;
    while(camera1->yaw<0.0f) camera1->yaw += 360.0f;
    while(camera1->yaw>=360.0f) camera1->yaw -= 360.0f;
}

void mousemove(int dx, int dy)
{
    if(!game::allowmouselook()) return;
    float cursens = sensitivity, curaccel = mouseaccel;
    if(zoom)
    {
        if(zoomautosens) 
        {
            cursens = float(sensitivity*zoomfov)/fov;
            curaccel = float(mouseaccel*zoomfov)/fov;
        }
        else 
        {
            cursens = zoomsens;
            curaccel = zoomaccel;
        }
    }
    if(curaccel && curtime && (dx || dy)) cursens += curaccel * sqrtf(dx*dx + dy*dy)/curtime;
    cursens /= 33.0f*sensitivityscale;
    camera1->yaw += dx*cursens;
    camera1->pitch -= dy*cursens*(invmouse ? -1 : 1);
    fixcamerarange();
    if(camera1!=player && !detachedcamera)
    {
        player->yaw = camera1->yaw;
        player->pitch = camera1->pitch;
    }
}

void recomputecamera()
{
    game::setupcamera();
    computezoom();

    bool shoulddetach = thirdperson > 1 || game::detachcamera();
    if(!thirdperson && !shoulddetach)
    {
        camera1 = player;
        detachedcamera = false;
    }
    else
    {
        static physent tempcamera;
        camera1 = &tempcamera;
        if(detachedcamera && shoulddetach) camera1->o = player->o;
        else
        {
            *camera1 = *player;
            detachedcamera = shoulddetach;
        }
        camera1->reset();
        camera1->type = ENT_CAMERA;
        camera1->move = -1;
        camera1->eyeheight = camera1->aboveeye = camera1->radius = camera1->xradius = camera1->yradius = 2;
       
        matrix3x3 orient;
        orient.identity();
        orient.rotate_around_y(camera1->roll*RAD);
        orient.rotate_around_x(camera1->pitch*-RAD);
        orient.rotate_around_z(camera1->yaw*-RAD);
        vec dir = vec(orient.b).neg(), side = vec(orient.a).neg(), up = orient.c;

        if(game::collidecamera()) 
        {
            movecamera(camera1, dir, thirdpersondistance, 1);
            movecamera(camera1, dir, clamp(thirdpersondistance - camera1->o.dist(player->o), 0.0f, 1.0f), 0.1f);
            if(thirdpersonup)
            {
                vec pos = camera1->o;
                float dist = fabs(thirdpersonup);
                if(thirdpersonup < 0) up.neg();
                movecamera(camera1, up, dist, 1);
                movecamera(camera1, up, clamp(dist - camera1->o.dist(pos), 0.0f, 1.0f), 0.1f);
            }
            if(thirdpersonside)
            {
                vec pos = camera1->o;
                float dist = fabs(thirdpersonside);
                if(thirdpersonside < 0) side.neg();
                movecamera(camera1, side, dist, 1);
                movecamera(camera1, side, clamp(dist - camera1->o.dist(pos), 0.0f, 1.0f), 0.1f);
            }
        }
        else 
        {
            camera1->o.add(vec(dir).mul(thirdpersondistance));
            if(thirdpersonup) camera1->o.add(vec(up).mul(thirdpersonup));
            if(thirdpersonside) camera1->o.add(vec(side).mul(thirdpersonside));
        }
    }

    setviewcell(camera1->o);
}

extern const glmatrixf viewmatrix(vec4(-1, 0, 0, 0), vec4(0, 0, 1, 0), vec4(0, -1, 0, 0));
glmatrixf mvmatrix, projmatrix, mvpmatrix, invmvmatrix, invmvpmatrix;

void readmatrices()
{
    glGetFloatv(GL_MODELVIEW_MATRIX, mvmatrix.v);
    glGetFloatv(GL_PROJECTION_MATRIX, projmatrix.v);

    mvpmatrix.mul(projmatrix, mvmatrix);
    invmvmatrix.invert(mvmatrix);
    invmvpmatrix.invert(mvpmatrix);
}

FVAR(nearplane, 0.01f, 0.54f, 2.0f);

void project(float fovy, float aspect, int farplane, bool flipx = false, bool flipy = false, bool swapxy = false, float zscale = 1)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(swapxy) glRotatef(90, 0, 0, 1);
    if(flipx || flipy!=swapxy || zscale!=1) glScalef(flipx ? -1 : 1, flipy!=swapxy ? -1 : 1, zscale);
    GLdouble ydist = nearplane * tan(fovy/2*RAD), xdist = ydist * aspect;
    glFrustum(-xdist, xdist, -ydist, ydist, nearplane, farplane);
    glMatrixMode(GL_MODELVIEW);
}

vec calcavatarpos(const vec &pos, float dist)
{
    vec eyepos;
    mvmatrix.transform(pos, eyepos);
    GLdouble ydist = nearplane * tan(curavatarfov/2*RAD), xdist = ydist * aspect;
    vec4 scrpos;
    scrpos.x = eyepos.x*nearplane/xdist;
    scrpos.y = eyepos.y*nearplane/ydist;
    scrpos.z = (eyepos.z*(farplane + nearplane) - 2*nearplane*farplane) / (farplane - nearplane);
    scrpos.w = -eyepos.z;

    vec worldpos = invmvpmatrix.perspectivetransform(scrpos);
    vec dir = vec(worldpos).sub(camera1->o).rescale(dist);
    return dir.add(camera1->o);
}

VAR(reflectclip, 0, 6, 64);
VAR(reflectclipavatar, -64, 0, 64);

glmatrixf clipmatrix;

static const glmatrixf dummymatrix;
static int projectioncount = 0;
void pushprojection(const glmatrixf &m = dummymatrix)
{
    glMatrixMode(GL_PROJECTION);
    if(projectioncount <= 0) glPushMatrix();
    if(&m != &dummymatrix) glLoadMatrixf(m.v);
    if(fogging)
    {
        glMultMatrixf(mvmatrix.v);
        glMultMatrixf(invfogmatrix.v);
    }
    glMatrixMode(GL_MODELVIEW);
    projectioncount++;
}

void popprojection()
{
    --projectioncount;
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    if(projectioncount > 0)
    {
        glPushMatrix();
        if(fogging)
        {
            glMultMatrixf(mvmatrix.v);
            glMultMatrixf(invfogmatrix.v);
        }
    }
    glMatrixMode(GL_MODELVIEW);
}

FVAR(polygonoffsetfactor, -1e4f, -3.0f, 1e4f);
FVAR(polygonoffsetunits, -1e4f, -3.0f, 1e4f);
FVAR(depthoffset, -1e4f, 0.01f, 1e4f);

void enablepolygonoffset(GLenum type)
{
    if(!depthoffset)
    {
        glPolygonOffset(polygonoffsetfactor, polygonoffsetunits);
        glEnable(type);
        return;
    }
    
    bool clipped = reflectz < 1e15f && reflectclip;

    glmatrixf offsetmatrix = clipped ? clipmatrix : projmatrix;
    offsetmatrix[14] += depthoffset * projmatrix[10];

    glMatrixMode(GL_PROJECTION);
    if(!clipped) glPushMatrix();
    glLoadMatrixf(offsetmatrix.v);
    if(fogging)
    {
        glMultMatrixf(mvmatrix.v);
        glMultMatrixf(invfogmatrix.v);
    }
    glMatrixMode(GL_MODELVIEW);
}

void disablepolygonoffset(GLenum type)
{
    if(!depthoffset)
    {
        glDisable(type);
        return;
    }
    
    bool clipped = reflectz < 1e15f && reflectclip;

    glMatrixMode(GL_PROJECTION);
    if(clipped) 
    {
        glLoadMatrixf(clipmatrix.v);
        if(fogging)
        {
            glMultMatrixf(mvmatrix.v);
            glMultMatrixf(invfogmatrix.v);
        }
    }
    else glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void calcspherescissor(const vec &center, float size, float &sx1, float &sy1, float &sx2, float &sy2)
{
    vec worldpos(center);
    if(reflecting) worldpos.z = 2*reflectz - worldpos.z; 
    vec e(mvmatrix.transformx(worldpos),
          mvmatrix.transformy(worldpos),
          mvmatrix.transformz(worldpos));
    if(e.z > 2*size) { sx1 = sy1 = 1; sx2 = sy2 = -1; return; }
    float zzrr = e.z*e.z - size*size,
          dx = e.x*e.x + zzrr, dy = e.y*e.y + zzrr,
          focaldist = 1.0f/tan(fovy*0.5f*RAD);
    sx1 = sy1 = -1;
    sx2 = sy2 = 1;
    #define CHECKPLANE(c, dir, focaldist, low, high) \
    do { \
        float nzc = (cz*cz + 1) / (cz dir drt) - cz, \
              pz = (d##c)/(nzc*e.c - e.z); \
        if(pz > 0) \
        { \
            float c = (focaldist)*nzc, \
                  pc = pz*nzc; \
            if(pc < e.c) low = c; \
            else if(pc > e.c) high = c; \
        } \
    } while(0)
    if(dx > 0)
    {
        float cz = e.x/e.z, drt = sqrtf(dx)/size;
        CHECKPLANE(x, -, focaldist/aspect, sx1, sx2);
        CHECKPLANE(x, +, focaldist/aspect, sx1, sx2);
    }
    if(dy > 0)
    {
        float cz = e.y/e.z, drt = sqrtf(dy)/size;
        CHECKPLANE(y, -, focaldist, sy1, sy2);
        CHECKPLANE(y, +, focaldist, sy1, sy2);
    }
}

static int scissoring = 0;
static GLint oldscissor[4];

int pushscissor(float sx1, float sy1, float sx2, float sy2)
{
    scissoring = 0;

    if(sx1 <= -1 && sy1 <= -1 && sx2 >= 1 && sy2 >= 1) return 0;

    sx1 = max(sx1, -1.0f);
    sy1 = max(sy1, -1.0f);
    sx2 = min(sx2, 1.0f);
    sy2 = min(sy2, 1.0f);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    int sx = viewport[0] + int(floor((sx1+1)*0.5f*viewport[2])),
        sy = viewport[1] + int(floor((sy1+1)*0.5f*viewport[3])),
        sw = viewport[0] + int(ceil((sx2+1)*0.5f*viewport[2])) - sx,
        sh = viewport[1] + int(ceil((sy2+1)*0.5f*viewport[3])) - sy;
    if(sw <= 0 || sh <= 0) return 0;

    if(glIsEnabled(GL_SCISSOR_TEST))
    {
        glGetIntegerv(GL_SCISSOR_BOX, oldscissor);
        sw += sx;
        sh += sy;
        sx = max(sx, int(oldscissor[0]));
        sy = max(sy, int(oldscissor[1]));
        sw = min(sw, int(oldscissor[0] + oldscissor[2])) - sx;
        sh = min(sh, int(oldscissor[1] + oldscissor[3])) - sy;
        if(sw <= 0 || sh <= 0) return 0;
        scissoring = 2;
    }
    else scissoring = 1;

    glScissor(sx, sy, sw, sh);
    if(scissoring<=1) glEnable(GL_SCISSOR_TEST);
    
    return scissoring;
}

void popscissor()
{
    if(scissoring>1) glScissor(oldscissor[0], oldscissor[1], oldscissor[2], oldscissor[3]);
    else if(scissoring) glDisable(GL_SCISSOR_TEST);
    scissoring = 0;
}

glmatrixf envmatrix;

void setenvmatrix()
{
    envmatrix = fogging ? fogmatrix : mvmatrix;
    if(reflecting) envmatrix.reflectz(reflectz);
    envmatrix.transpose();
}

VARR(fog, 16, 4000, 1000024);
bvec fogcolor(0x80, 0x99, 0xB3);
HVARFR(fogcolour, 0, 0x8099B3, 0xFFFFFF,
{
    fogcolor = bvec((fogcolour>>16)&0xFF, (fogcolour>>8)&0xFF, fogcolour&0xFF);
});

static float findsurface(int fogmat, const vec &v, int &abovemat)
{
    fogmat &= MATF_VOLUME;
    ivec o(v), co;
    int csize;
    do
    {
        cube &c = lookupcube(o.x, o.y, o.z, 0, co, csize);
        int mat = c.material&MATF_VOLUME;
        if(mat != fogmat)
        {
            abovemat = isliquid(mat) ? c.material : MAT_AIR;
            return o.z;
        }
        o.z = co.z + csize;
    }
    while(o.z < worldsize);
    abovemat = MAT_AIR;
    return worldsize;
}

static void blendfog(int fogmat, float blend, float logblend, float &start, float &end, float *fogc)
{
    switch(fogmat&MATF_VOLUME)
    {
        case MAT_WATER:
        {
            const bvec &wcol = getwatercolor(fogmat);
            int wfog = getwaterfog(fogmat);
            loopk(3) fogc[k] += blend*wcol[k]/255.0f;
            end += logblend*min(fog, max(wfog*4, 32));
            break;
        }

        case MAT_LAVA:
        {
            const bvec &lcol = getlavacolor(fogmat);
            int lfog = getlavafog(fogmat);
            loopk(3) fogc[k] += blend*lcol[k]/255.0f;
            end += logblend*min(fog, max(lfog*4, 32));
            break;
        }

        default:
            loopk(3) fogc[k] += blend*fogcolor[k]/255.0f;
            start += logblend*(fog+64)/8;
            end += logblend*fog;
            break;
    }
}

static void setfog(int fogmat, float below = 1, int abovemat = MAT_AIR)
{
    float fogc[4] = { 0, 0, 0, 1 };
    float start = 0, end = 0;
    float logscale = 256, logblend = log(1 + (logscale - 1)*below) / log(logscale);

    blendfog(fogmat, below, logblend, start, end, fogc);
    if(below < 1) blendfog(abovemat, 1-below, 1-logblend, start, end, fogc);

    glFogf(GL_FOG_START, start);
    glFogf(GL_FOG_END, end);
    glFogfv(GL_FOG_COLOR, fogc);
    glClearColor(fogc[0], fogc[1], fogc[2], 1.0f);
}

static void blendfogoverlay(int fogmat, float blend, float *overlay)
{
    float maxc;
    switch(fogmat&MATF_VOLUME)
    {
        case MAT_WATER:
        {
            const bvec &wcol = getwatercolor(fogmat);
            maxc = max(wcol[0], max(wcol[1], wcol[2]));
            loopk(3) overlay[k] += blend*max(0.4f, wcol[k]/min(32.0f + maxc*7.0f/8.0f, 255.0f));
            break;
        }

        case MAT_LAVA:
        {
            const bvec &lcol = getlavacolor(fogmat);
            maxc = max(lcol[0], max(lcol[1], lcol[2]));
            loopk(3) overlay[k] += blend*max(0.4f, lcol[k]/min(32.0f + maxc*7.0f/8.0f, 255.0f));
            break;
        }

        default:
            loopk(3) overlay[k] += blend;
            break;
    }
}

void drawfogoverlay(int fogmat, float fogblend, int abovemat)
{
    notextureshader->set();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    float overlay[3] = { 0, 0, 0 };
    blendfogoverlay(fogmat, fogblend, overlay);
    blendfogoverlay(abovemat, 1-fogblend, overlay);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3fv(overlay);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glEnd();
    glDisable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    defaultshader->set();
}

bool renderedgame = false;

void rendergame(bool mainpass)
{
    game::rendergame(mainpass);
    if(!shadowmapping) renderedgame = true;
}

VARP(skyboxglare, 0, 1, 1);

void drawglare()
{
    glaring = true;
    refracting = -1;

    float oldfogstart, oldfogend, oldfogcolor[4], zerofog[4] = { 0, 0, 0, 1 };
    glGetFloatv(GL_FOG_START, &oldfogstart);
    glGetFloatv(GL_FOG_END, &oldfogend);
    glGetFloatv(GL_FOG_COLOR, oldfogcolor);

    glFogf(GL_FOG_START, (fog+64)/8);
    glFogf(GL_FOG_END, fog);
    glFogfv(GL_FOG_COLOR, zerofog);

    glClearColor(0, 0, 0, 1);
    glClear((skyboxglare ? 0 : GL_COLOR_BUFFER_BIT) | GL_DEPTH_BUFFER_BIT);

    rendergeom();

    if(skyboxglare) drawskybox(farplane, false);

    renderreflectedmapmodels();
    rendergame();
    if(!isthirdperson())
    {
        project(curavatarfov, aspect, farplane, false, false, false, avatardepth);
        game::renderavatar();
        project(fovy, aspect, farplane);
    }

    renderwater();
    rendermaterials();
    renderalphageom();
    renderparticles();

    glFogf(GL_FOG_START, oldfogstart);
    glFogf(GL_FOG_END, oldfogend);
    glFogfv(GL_FOG_COLOR, oldfogcolor);

    refracting = 0;
    glaring = false;
}

VARP(reflectmms, 0, 1, 1);
VARR(refractsky, 0, 0, 1);

glmatrixf fogmatrix, invfogmatrix;

void drawreflection(float z, bool refract, int fogdepth, const bvec &col)
{
    reflectz = z < 0 ? 1e16f : z;
    reflecting = !refract;
    refracting = refract ? (z < 0 || camera1->o.z >= z ? -1 : 1) : 0;
    fading = renderpath!=R_FIXEDFUNCTION && waterrefract && waterfade && hasFBO && z>=0;
    fogging = refracting<0 && z>=0;
    refractfog = fogdepth;
    refractcolor = fogging ? col : fogcolor;

    float oldfogstart, oldfogend, oldfogcolor[4];
    glGetFloatv(GL_FOG_START, &oldfogstart);
    glGetFloatv(GL_FOG_END, &oldfogend);
    glGetFloatv(GL_FOG_COLOR, oldfogcolor);

    if(fogging)
    {
        glFogf(GL_FOG_START, camera1->o.z - z);
        glFogf(GL_FOG_END, camera1->o.z - (z-max(refractfog, 1)));
        GLfloat m[16] =
        {
             1,   0,  0, 0,
             0,   1,  0, 0,
             0,   0,  1, 0,
            -camera1->o.x, -camera1->o.y, -camera1->o.z, 1
        };
        memcpy(fogmatrix.v, m, sizeof(m));
        invfogmatrix.invert(fogmatrix);
        pushprojection();
        glPushMatrix();
        glLoadMatrixf(fogmatrix.v);
        float fogc[4] = { col.x/255.0f, col.y/255.0f, col.z/255.0f, 1.0f };
        glFogfv(GL_FOG_COLOR, fogc);
    }
    else
    {
        glFogf(GL_FOG_START, (fog+64)/8);
        glFogf(GL_FOG_END, fog);
        float fogc[4] = { fogcolor.x/255.0f, fogcolor.y/255.0f, fogcolor.z/255.0f, 1.0f };
        glFogfv(GL_FOG_COLOR, fogc);
    }

    if(fading)
    {
        float scale = fogging ? -0.25f : 0.25f, offset = 2*fabs(scale) - scale*z;
        setenvparamf("waterfadeparams", SHPARAM_VERTEX, 8, scale, offset, -scale, offset + camera1->o.z*scale);
        setenvparamf("waterfadeparams", SHPARAM_PIXEL, 8, scale, offset, -scale, offset + camera1->o.z*scale);
    }

    if(reflecting)
    {
        glPushMatrix();
        glTranslatef(0, 0, 2*z);
        glScalef(1, 1, -1);

        glFrontFace(GL_CCW);
    }

    setenvmatrix();

    if(reflectclip && z>=0)
    {
        float zoffset = reflectclip/4.0f, zclip;
        if(refracting<0)
        {
            zclip = z+zoffset;
            if(camera1->o.z<=zclip) zclip = z;
        }
        else
        {
            zclip = z-zoffset;
            if(camera1->o.z>=zclip && camera1->o.z<=z+4.0f) zclip = z;
            if(reflecting) zclip = 2*z - zclip;
        }
        plane clipplane;
        invmvmatrix.transposedtransform(plane(0, 0, refracting>0 ? 1 : -1, refracting>0 ? -zclip : zclip), clipplane);
        clipmatrix.clip(clipplane, projmatrix);
        pushprojection(clipmatrix);
    }

    renderreflectedgeom(refracting<0 && z>=0 && caustics, fogging);

    if(reflecting || refracting>0 || (refracting<0 && refractsky) || z<0)
    {
        if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        if(reflectclip && z>=0) popprojection();
        if(fogging) 
        {
            popprojection();
            glPopMatrix();
        }
        drawskybox(farplane, false);
        if(fogging) 
        {
            pushprojection();
            glPushMatrix();
            glLoadMatrixf(fogmatrix.v);
        }
        if(reflectclip && z>=0) pushprojection(clipmatrix);
        if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
    }
    else if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

    renderdecals();

    if(reflectmms) renderreflectedmapmodels();
    rendergame();

    if(refracting && z>=0 && !isthirdperson() && fabs(camera1->o.z-z) <= 0.5f*(player->eyeheight + player->aboveeye))
    {   
        glmatrixf avatarproj;
        avatarproj.perspective(curavatarfov, aspect, nearplane, farplane);
        if(reflectclip)
        {
            popprojection();
            glmatrixf avatarclip;
            plane clipplane;
            invmvmatrix.transposedtransform(plane(0, 0, refracting, reflectclipavatar/4.0f - refracting*z), clipplane);
            avatarclip.clip(clipplane, avatarproj);
            pushprojection(avatarclip);
        }
        else pushprojection(avatarproj);
        game::renderavatar();
        popprojection();
        if(reflectclip) pushprojection(clipmatrix);
    }

    if(refracting) rendergrass();
    rendermaterials();
    renderalphageom(fogging);
    renderparticles();

    if(fading) glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    if(reflectclip && z>=0) popprojection();

    if(reflecting)
    {
        glPopMatrix();

        glFrontFace(GL_CW);
    }

    if(fogging) 
    {
        popprojection();
        glPopMatrix();
    }
    glFogf(GL_FOG_START, oldfogstart);
    glFogf(GL_FOG_END, oldfogend);
    glFogfv(GL_FOG_COLOR, oldfogcolor);
    
    reflectz = 1e16f;
    refracting = 0;
    reflecting = fading = fogging = false;

    setenvmatrix();
}

bool envmapping = false;

void drawcubemap(int size, const vec &o, float yaw, float pitch, const cubemapside &side)
{
    envmapping = true;

    physent *oldcamera = camera1;
    static physent cmcamera;
    cmcamera = *player;
    cmcamera.reset();
    cmcamera.type = ENT_CAMERA;
    cmcamera.o = o;
    cmcamera.yaw = yaw;
    cmcamera.pitch = pitch;
    cmcamera.roll = 0;
    camera1 = &cmcamera;
    setviewcell(camera1->o);
   
    defaultshader->set();

    int fogmat = lookupmaterial(o)&(MATF_VOLUME|MATF_INDEX);

    setfog(fogmat);

    glClear(GL_DEPTH_BUFFER_BIT);

    int farplane = worldsize*2;

    project(90.0f, 1.0f, farplane, !side.flipx, !side.flipy, side.swapxy);

    transplayer();
    readmatrices();
    findorientation();
    setenvmatrix();

    glEnable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    xtravertsva = xtraverts = glde = gbatches = 0;

    visiblecubes();

    if(limitsky()) drawskybox(farplane, true);

    rendergeom();

    if(!limitsky()) drawskybox(farplane, false);

//    queryreflections();

    rendermapmodels();
    renderalphageom();

//    drawreflections();

//    renderwater();
//    rendermaterials();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_FOG);

    camera1 = oldcamera;
    envmapping = false;
}

bool modelpreviewing = false;

namespace modelpreview
{
    physent *oldcamera;
    float oldfogstart, oldfogend, oldfogcolor[4]; 

    physent camera;

    void start(bool background)
    {
        float fovy = 90.f, aspect = 1.f;
        envmapping = modelpreviewing = true;

        oldcamera = camera1;
        camera = *camera1;
        camera.reset();
        camera.type = ENT_CAMERA;
        camera.o = vec(0, 0, 0);
        camera.yaw = 0;
        camera.pitch = 0;
        camera.roll = 0;
        camera1 = &camera;

        glGetFloatv(GL_FOG_START, &oldfogstart);
        glGetFloatv(GL_FOG_END, &oldfogend);
        glGetFloatv(GL_FOG_COLOR, oldfogcolor);

        GLfloat fogc[4] = { 0, 0, 0, 1 };
        glFogf(GL_FOG_START, 0);
        glFogf(GL_FOG_END, 1000000);
        glFogfv(GL_FOG_COLOR, fogc);
        glClearColor(fogc[0], fogc[1], fogc[2], fogc[3]);

        glClear((background ? GL_COLOR_BUFFER_BIT : 0) | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        project(fovy, aspect, 1024);
        transplayer();
        readmatrices();
        setenvmatrix();

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }

    void end()
    {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        defaultshader->set();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glFogf(GL_FOG_START, oldfogstart);
        glFogf(GL_FOG_END, oldfogend);
        glFogfv(GL_FOG_COLOR, oldfogcolor);
        glClearColor(oldfogcolor[0], oldfogcolor[1], oldfogcolor[2], oldfogcolor[3]);

        camera1 = oldcamera;
        envmapping = modelpreviewing = false;
    }
}

bool minimapping = false;

GLuint minimaptex = 0;
vec minimapcenter(0, 0, 0), minimapradius(0, 0, 0), minimapscale(0, 0, 0);

void clearminimap()
{
    if(minimaptex) { glDeleteTextures(1, &minimaptex); minimaptex = 0; }
}

VARR(minimapheight, 0, 0, 2<<16);
bvec minimapcolor(0, 0, 0);
HVARFR(minimapcolour, 0, 0, 0xFFFFFF,
{
    minimapcolor = bvec((minimapcolour>>16)&0xFF, (minimapcolour>>8)&0xFF, minimapcolour&0xFF);
});
VARR(minimapclip, 0, 0, 1);
VARFP(minimapsize, 7, 8, 10, { if(minimaptex) drawminimap(); });

void bindminimap()
{
    glBindTexture(GL_TEXTURE_2D, minimaptex);
}

void clipminimap(ivec &bbmin, ivec &bbmax, cube *c = worldroot, int x = 0, int y = 0, int z = 0, int size = worldsize>>1)
{
    loopi(8)
    {
        ivec o(i, x, y, z, size);
        if(c[i].children) clipminimap(bbmin, bbmax, c[i].children, o.x, o.y, o.z, size>>1);
        else if(!isentirelysolid(c[i]) && (c[i].material&MATF_CLIP)!=MAT_CLIP)
        {
            loopk(3) bbmin[k] = min(bbmin[k], o[k]);
            loopk(3) bbmax[k] = max(bbmax[k], o[k] + size);
        }
    }
}

void drawminimap()
{
    if(!game::needminimap()) { clearminimap(); return; }

    renderprogress(0, "generating mini-map...", 0, !renderedframe);

    int size = 1<<minimapsize, sizelimit = min(hwtexsize, min(screen->w, screen->h));
    while(size > sizelimit) size /= 2;
    if(!minimaptex) glGenTextures(1, &minimaptex);

    extern vector<vtxarray *> valist;
    ivec bbmin(worldsize, worldsize, worldsize), bbmax(0, 0, 0);
    loopv(valist)
    {
        vtxarray *va = valist[i];
        loopk(3)
        {
            if(va->geommin[k]>va->geommax[k]) continue;
            bbmin[k] = min(bbmin[k], va->geommin[k]);
            bbmax[k] = max(bbmax[k], va->geommax[k]);
        }
    }
    if(minimapclip)
    {
        ivec clipmin(worldsize, worldsize, worldsize), clipmax(0, 0, 0);
        clipminimap(clipmin, clipmax);
        loopk(2) bbmin[k] = max(bbmin[k], clipmin[k]);
        loopk(2) bbmax[k] = min(bbmax[k], clipmax[k]); 
    }
 
    minimapradius = bbmax.tovec().sub(bbmin.tovec()).mul(0.5f); 
    minimapcenter = bbmin.tovec().add(minimapradius);
    minimapradius.x = minimapradius.y = max(minimapradius.x, minimapradius.y);
    minimapscale = vec((0.5f - 1.0f/size)/minimapradius.x, (0.5f - 1.0f/size)/minimapradius.y, 1.0f);

    envmapping = minimapping = true;

    physent *oldcamera = camera1;
    static physent cmcamera;
    cmcamera = *player;
    cmcamera.reset();
    cmcamera.type = ENT_CAMERA;
    cmcamera.o = vec(minimapcenter.x, minimapcenter.y, max(minimapcenter.z + minimapradius.z + 1, float(minimapheight)));
    cmcamera.yaw = 0;
    cmcamera.pitch = -90;
    cmcamera.roll = 0;
    camera1 = &cmcamera;
    setviewcell(vec(-1, -1, -1));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-minimapradius.x, minimapradius.x, -minimapradius.y, minimapradius.y, 0, camera1->o.z + 1);
    glScalef(-1, 1, 1);
    glMatrixMode(GL_MODELVIEW);

    transplayer();

    defaultshader->set();

    GLfloat fogc[4] = { minimapcolor.x/255.0f, minimapcolor.y/255.0f, minimapcolor.z/255.0f, 1.0f };
    glFogf(GL_FOG_START, 0);
    glFogf(GL_FOG_END, 1000000);
    glFogfv(GL_FOG_COLOR, fogc);

    glClearColor(fogc[0], fogc[1], fogc[2], fogc[3]);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, size, size);

    glDisable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glFrontFace(GL_CCW);

    xtravertsva = xtraverts = glde = gbatches = 0;

    visiblecubes(false);
    queryreflections();
    drawreflections();

    loopi(minimapheight > 0 && minimapheight < minimapcenter.z + minimapradius.z ? 2 : 1)
    {
        if(i)
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            camera1->o.z = minimapheight;
            transplayer();
        }
        rendergeom();
        rendermapmodels();
        renderwater();
        rendermaterials();
        renderalphageom();
    }

    glFrontFace(GL_CW);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_FOG);

    glViewport(0, 0, screen->w, screen->h);

    camera1 = oldcamera;
    envmapping = minimapping = false;

    glBindTexture(GL_TEXTURE_2D, minimaptex);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5, 0, 0, size, size, 0);
    setuptexparameters(minimaptex, NULL, 3, 1, GL_RGB5, GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat border[4] = { minimapcolor.x/255.0f, minimapcolor.y/255.0f, minimapcolor.z/255.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool deferdrawtextures = false;

void drawtextures()
{
    if(minimized) { deferdrawtextures = true; return; }
    deferdrawtextures = false;
    genenvmaps();
    drawminimap();
}

GLuint motiontex = 0;
int motionw = 0, motionh = 0, lastmotion = 0;

void cleanupmotionblur()
{
    if(motiontex) { glDeleteTextures(1, &motiontex); motiontex = 0; }
    motionw = motionh = 0;
    lastmotion = 0;
}

VARFP(motionblur, 0, 0, 1, { if(!motionblur) cleanupmotionblur(); });
VARP(motionblurmillis, 1, 5, 1000);
FVARP(motionblurscale, 0, 0.5f, 1);

void addmotionblur()
{
    if(!motionblur || !hasTR || max(screen->w, screen->h) > hwtexsize) return;

    if(game::ispaused()) { lastmotion = 0; return; }

    if(!motiontex || motionw != screen->w || motionh != screen->h)
    {
        if(!motiontex) glGenTextures(1, &motiontex);
        motionw = screen->w;
        motionh = screen->h;
        lastmotion = 0;
        createtexture(motiontex, motionw, motionh, NULL, 3, 0, GL_RGB, GL_TEXTURE_RECTANGLE_ARB);
    }

    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, motiontex);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_RECTANGLE_ARB);

    rectshader->set();

    glColor4f(1, 1, 1, lastmotion ? pow(motionblurscale, max(float(lastmillis - lastmotion)/motionblurmillis, 1.0f)) : 0);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(      0,       0); glVertex2f(-1, -1);
    glTexCoord2f(motionw,       0); glVertex2f( 1, -1);
    glTexCoord2f(      0, motionh); glVertex2f(-1,  1);
    glTexCoord2f(motionw, motionh); glVertex2f( 1,  1);
    glEnd();

    glDisable(GL_TEXTURE_RECTANGLE_ARB);
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
 
    if(lastmillis - lastmotion >= motionblurmillis)
    {
        lastmotion = lastmillis - lastmillis%motionblurmillis;

        glCopyTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, 0, 0, screen->w, screen->h);
    }
}

bool dopostfx = false;

void invalidatepostfx()
{
    dopostfx = false;
}

void gl_drawhud(int w, int h);

int xtraverts, xtravertsva;

void gl_drawframe(int w, int h)
{
    if(deferdrawtextures) drawtextures();

    defaultshader->set();

    updatedynlights();

    aspect = forceaspect ? forceaspect : w/float(h);
    fovy = 2*atan2(tan(curfov/2*RAD), aspect)/RAD;
    
    int fogmat = lookupmaterial(camera1->o)&(MATF_VOLUME|MATF_INDEX), abovemat = MAT_AIR;
    float fogblend = 1.0f, causticspass = 0.0f;
    if(isliquid(fogmat&MATF_VOLUME))
    {
        float z = findsurface(fogmat, camera1->o, abovemat) - WATER_OFFSET;
        if(camera1->o.z < z + 1) fogblend = min(z + 1 - camera1->o.z, 1.0f);
        else fogmat = abovemat;
        if(caustics && (fogmat&MATF_VOLUME)==MAT_WATER && camera1->o.z < z)
            causticspass = renderpath==R_FIXEDFUNCTION ? 1.0f : min(z - camera1->o.z, 1.0f);
    }
    else fogmat = MAT_AIR;    
    setfog(fogmat, fogblend, abovemat);
    if(fogmat!=MAT_AIR)
    {
        float blend = abovemat==MAT_AIR ? fogblend : 1.0f;
        fovy += blend*sinf(lastmillis/1000.0)*2.0f;
        aspect += blend*sinf(lastmillis/1000.0+PI)*0.1f;
    }

    farplane = worldsize*2;

    project(fovy, aspect, farplane);
    transplayer();
    readmatrices();
    findorientation();
    setenvmatrix();

    glEnable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    xtravertsva = xtraverts = glde = gbatches = 0;

    if(!hasFBO)
    {
        if(dopostfx)
        {
            drawglaretex();
            drawdepthfxtex();
            drawreflections();
        }
        else dopostfx = true;
    }

    visiblecubes();
    
    if(shadowmap && !hasFBO) rendershadowmap();

    glClear(GL_DEPTH_BUFFER_BIT|(wireframe ? GL_COLOR_BUFFER_BIT : 0)|(hasstencil ? GL_STENCIL_BUFFER_BIT : 0));    //faned

    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);    //faned

    if(limitsky()) drawskybox(farplane, true);

    rendergeom(causticspass);

    extern int outline;
    if(outline) renderoutline();    //faned

    queryreflections();

    generategrass();

    if(!limitsky()) drawskybox(farplane, false);

    renderdecals(true);

    rendermapmodels();
    rendergame(true);
    if(!isthirdperson())
    {
        project(curavatarfov, aspect, farplane, false, false, false, avatardepth);
        game::renderavatar();
        project(fovy, aspect, farplane);
    }

    if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //faned

    if(hasFBO) 
    {
        drawglaretex();
        drawdepthfxtex();
        drawreflections();
    }

    if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //faned

    renderwater();
    rendergrass();

    rendermaterials();
    renderalphageom();

    if(wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //faned

    renderparticles(true);

    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    addmotionblur();
    addglare();
    if(isliquid(fogmat&MATF_VOLUME)) drawfogoverlay(fogmat, fogblend, abovemat);
    renderpostfx();

    defaultshader->set();
    g3d_render();

    glDisable(GL_TEXTURE_2D);
    notextureshader->set();

    gl_drawhud(w, h);

    renderedgame = false;
}

void gl_drawmainmenu(int w, int h)
{
    xtravertsva = xtraverts = glde = gbatches = 0;

    renderbackground(NULL, NULL, NULL, NULL, true, true);
    renderpostfx();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    defaultshader->set();
    glEnable(GL_TEXTURE_2D);
    g3d_render();

    notextureshader->set();
    glDisable(GL_TEXTURE_2D);

    gl_drawhud(w, h);
}

VARNP(damagecompass, usedamagecompass, 0, 1, 1);
VARP(damagecompassfade, 1, 1000, 10000);
VARP(damagecompasssize, 1, 30, 100);
VARP(damagecompassalpha, 1, 25, 100);
VARP(damagecompassmin, 1, 25, 1000);
VARP(damagecompassmax, 1, 200, 1000);

float dcompass[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
void damagecompass(int n, const vec &loc)
{
    if(!usedamagecompass || minimized) return;
    vec delta(loc);
    delta.sub(camera1->o); 
    float yaw, pitch;
    if(delta.magnitude()<4) yaw = camera1->yaw;
    else vectoyawpitch(delta, yaw, pitch);
    yaw -= camera1->yaw;
    if(yaw >= 360) yaw = fmod(yaw, 360);
    else if(yaw < 0) yaw = 360 - fmod(-yaw, 360);
    int dir = (int(yaw+22.5f)%360)/45;
    dcompass[dir] += max(n, damagecompassmin)/float(damagecompassmax);
    if(dcompass[dir]>1) dcompass[dir] = 1;

}
void drawdamagecompass(int w, int h)
{
    if(zoom) return;    //faned

    int dirs = 0;
    float size = damagecompasssize/100.0f*min(h, w)/2.0f;
    loopi(8) if(dcompass[i]>0)
    {
        if(!dirs)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1, 0, 0, damagecompassalpha/100.0f);
        }
        dirs++;

        glPushMatrix();
        glTranslatef(w/2, h/2, 0);
        glRotatef(i*45, 0, 0, 1);
        glTranslatef(0, -size/2.0f-min(h, w)/4.0f, 0);
        float logscale = 32,
              scale = log(1 + (logscale - 1)*dcompass[i]) / log(logscale);
        glScalef(size*scale, size*scale, 0);

        glBegin(GL_TRIANGLES);
        glVertex3f(1, 1, 0);
        glVertex3f(-1, 1, 0);
        glVertex3f(0, 0, 0);
        glEnd();
        glPopMatrix();

        // fade in log space so short blips don't disappear too quickly
        scale -= float(curtime)/damagecompassfade;
        dcompass[i] = scale > 0 ? (pow(logscale, scale) - 1) / (logscale - 1) : 0;
    }
}

int damageblendmillis = 0;

VARFP(damagescreen, 0, 1, 1, { if(!damagescreen) damageblendmillis = 0; });
VARP(damagescreenfactor, 1, 7, 100);
VARP(damagescreenalpha, 1, 45, 100);
VARP(damagescreenfade, 0, 125, 1000);
VARP(damagescreenmin, 1, 10, 1000);
VARP(damagescreenmax, 1, 100, 1000);

void damageblend(int n)
{
    if(!damagescreen || minimized) return;
    if(lastmillis > damageblendmillis) damageblendmillis = lastmillis;
    damageblendmillis += clamp(n, damagescreenmin, damagescreenmax)*damagescreenfactor;
}

void drawdamagescreen(int w, int h)
{
    if(lastmillis >= damageblendmillis || zoom) return;    //faned

    defaultshader->set();
    glEnable(GL_TEXTURE_2D);

    static Texture *damagetex = NULL;
    if(!damagetex) damagetex = textureload("packages/hud/damage.png", 3);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, damagetex->id);
    float fade = damagescreenalpha/100.0f;
    if(damageblendmillis - lastmillis < damagescreenfade)
        fade *= float(damageblendmillis - lastmillis)/damagescreenfade;
    glColor4f(fade, fade, fade, fade);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0); glVertex2f(0, 0);
    glTexCoord2f(1, 0); glVertex2f(w, 0);
    glTexCoord2f(0, 1); glVertex2f(0, h);
    glTexCoord2f(1, 1); glVertex2f(w, h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    notextureshader->set();
}

FANED_VARP(deathpanicscreen, 0, 1, 1);    //faned

void drawdeathpanicscreen(int w, int h)    //faned
{
    if(deathpanicscreen && game::player1->health <= 25 && game::player1->state==CS_ALIVE && !m_check(game::gamemode, M_INSTA) && !zoom)
    {
        defaultshader->set();
        glEnable(GL_TEXTURE_2D);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Texture *t = textureload("faned/hud/veins.png", 3);
        glBindTexture(GL_TEXTURE_2D, t->id);
        float fade = (1-game::player1->health/30.0f);
        glColor4f(fade, fade, fade, fade);

        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(w, 0);
        glTexCoord2f(0, 1); glVertex2f(0, h);
        glTexCoord2f(1, 1); glVertex2f(w, h);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        notextureshader->set();
    }
}

FANED_VARP(zoomscopescreen, 0, 1, 1);    //faned

void drawzoomscopescreen(int w, int h)    //faned
{
    if(zoomscopescreen && game::player1->gunselect == GUN_RIFLE && zoom)
    {
        setvar("hudgun", 0);
        defaultshader->set();
        glEnable(GL_TEXTURE_2D);
        static Texture *scopetex = NULL;
        if(!scopetex) scopetex = textureload("faned/hud/scope.png", 3);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, scopetex->id);

        float sz = min(w, h),
              x1 = w/2 - sz/2,
              x2 = w/2 + sz/2,
              y1 = h/2 - sz/2,
              y2 = h/2 + sz/2,
              border = 512/512.0f;

        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 0.5f);
        glVertex2f(x1 + 0.5f*sz, y1 + 0.5f*sz);
        loopi(8+1)
        {
            float c = 0.5f*(1 + border*cosf(i*2*M_PI/8.0f)), s = 0.5f*(1 + border*sinf(i*2*M_PI/8.0f));
            glTexCoord2f(c, s);
            glVertex2f(x1 + c*sz, y1 + s*sz);
        }
        glEnd();

        glDisable(GL_BLEND);

        glBegin(GL_TRIANGLE_STRIP);
        loopi(8+1)
        {
            float c = 0.5f*(1 + border*cosf(i*2*M_PI/8.0f)), s = 0.5f*(1 + border*sinf(i*2*M_PI/8.0f));
            glTexCoord2f(c, s);
            glVertex2f(x1 + c*sz, y1 + s*sz);
            c = c < 0.4f ? 0 : (c > 0.6f ? 1 : 0.5f);
            s = s < 0.4f ? 0 : (s > 0.6f ? 1 : 0.5f);
            glTexCoord2f(c, s);
            glVertex2f(x1 + c*sz, y1 + s*sz);
        }
        glEnd();

        if(x1 > 0 || x2 < w || y1 > 0 || y2 < h)
        {
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f(0, 0); glVertex2f(0,  0);
            glTexCoord2f(0, 0); glVertex2f(x1, y1);
            glTexCoord2f(0, 1); glVertex2f(0,  h);
            glTexCoord2f(0, 1); glVertex2f(x1, y2);

            glTexCoord2f(1, 1); glVertex2f(w, h);
            glTexCoord2f(1, 1); glVertex2f(x2, y2);
            glTexCoord2f(1, 0); glVertex2f(w, 0);
            glTexCoord2f(1, 0); glVertex2f(x2, y1);

            glTexCoord2f(0, 0); glVertex2f(0,  0);
            glTexCoord2f(0, 0); glVertex2f(x1, y1);
            glEnd();
        }
        glEnable(GL_BLEND);
    }
    else setvar("hudgun", 1);
}

VAR(hidestats, 0, 0, 1);
VAR(hidehud, 0, 0, 1);

VARP(crosshairsize, 0, 15, 50);
VARP(cursorsize, 0, 30, 50);
VARP(crosshairfx, 0, 1, 1);
vec haircolor(1.0f, 1.0f, 1.0f);
FANED_HVARFP(crosshaircolor, 0, 0xFFFFFF, 0xFFFFFF, {
        const float factor = 1.0f/0xff;
        haircolor.x = factor * (crosshaircolor >> 16 & 0xff);
        haircolor.y = factor * (crosshaircolor >> 8 & 0xff);
        haircolor.z = factor * (crosshaircolor & 0xff);
    });    //faned
VARP(crosshaircolors, 0, 1, 1);

#define MAXCROSSHAIRS 4
static Texture *crosshairs[MAXCROSSHAIRS] = { NULL, NULL, NULL, NULL };

void loadcrosshair(const char *name, int i)
{
    if(i < 0 || i >= MAXCROSSHAIRS) return;
	crosshairs[i] = name ? textureload(name, 3, true) : notexture;
    if(crosshairs[i] == notexture) 
    {
        name = game::defaultcrosshair(i);
        if(!name) name = "data/crosshair.png";
        crosshairs[i] = textureload(name, 3, true);
    }
}

void loadcrosshair_(const char *name, int *i)
{
	loadcrosshair(name, *i);
}

COMMANDN(loadcrosshair, loadcrosshair_, "si");

ICOMMAND(getcrosshair, "i", (int *i), 
{
    const char *name = "";
    if(*i >= 0 && *i < MAXCROSSHAIRS)
    {
        name = crosshairs[*i] ? crosshairs[*i]->name : game::defaultcrosshair(*i);
        if(!name) name = "data/crosshair.png";
    }
    result(name);
});
 
void writecrosshairs(stream *f)
{
    loopi(MAXCROSSHAIRS) if(crosshairs[i] && crosshairs[i]!=notexture)
        f->printf("loadcrosshair %s %d\n", escapestring(crosshairs[i]->name), i);
    f->printf("\n");
}

void drawcrosshair(int w, int h)
{
    bool windowhit = g3d_windowhit(true, false);
    if(!windowhit && (hidehud || mainmenu)) return; //(hidehud || player->state==CS_SPECTATOR || player->state==CS_DEAD)) return;

    float r = haircolor.x, g = haircolor.y, b = haircolor.z, cx = 0.5f, cy = 0.5f, chsize;    //faned
    Texture *crosshair;
    if(windowhit)
    {
        static Texture *cursor = NULL;
        if(!cursor) cursor = textureload("data/guicursor.png", 3, true);
        crosshair = cursor;
        chsize = cursorsize*w/900.0f;
        g3d_cursorpos(cx, cy);
    }
    else
    { 
        int index = game::selectcrosshair(r, g, b);
        if(index < 0) return;
        if(!crosshairfx) index = 0;
        if(!crosshairfx || !crosshaircolors) r = g = b = 1;
        crosshair = crosshairs[index];
        if(!crosshair) 
        {
            loadcrosshair(NULL, index);
            crosshair = crosshairs[index];
        }
        chsize = crosshairsize*w/900.0f;
    }
    if(crosshair->type&Texture::ALPHA) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    else glBlendFunc(GL_ONE, GL_ONE);
    glColor3f(r, g, b);
    float x = cx*w - (windowhit ? 0 : chsize/2.0f);
    float y = cy*h - (windowhit ? 0 : chsize/2.0f);
    glBindTexture(GL_TEXTURE_2D, crosshair->id);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0, 0); glVertex2f(x,          y);
    glTexCoord2f(1, 0); glVertex2f(x + chsize, y);
    glTexCoord2f(0, 1); glVertex2f(x,          y + chsize);
    glTexCoord2f(1, 1); glVertex2f(x + chsize, y + chsize);
    glEnd();
}

VARP(wallclock, 0, 0, 1);
VARP(wallclock24, 0, 0, 1);
VARP(wallclocksecs, 0, 0, 1);

static time_t walltime = 0;

VARP(showfps, 0, 1, 1);
VARP(showfpsrange, 0, 0, 1);
VAR(showeditstats, 0, 0, 1);
VAR(statrate, 1, 200, 1000);
FVARP(conscale, 1e-3f, 0.33f, 1e3f);

//start faned
FANED_VARP(hideversion, 0, 0, 1);
string version = "20140809155750";
string versionfull = "Cube 2: Fanatic Edition | Version 20140809155750";
ICOMMAND(getversion, "", (), result(version));
ICOMMAND(getversionfull, "", (), result(versionfull));

extern int sehud;

FANED_VARP(showspeed, 0, 0, 1);    //faned
FANED_VARP(showtimeremaining, 0, 1, 1);    //faned

void gl_drawhud(int w, int h)
{
    if(forceaspect) w = int(ceil(h*forceaspect));

    if(editmode && !hidehud && !mainmenu)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);

        renderblendbrush();

        rendereditcursor();

        glDepthMask(GL_TRUE);
        glDisable(GL_DEPTH_TEST);
    }

    gettextres(w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3f(1, 1, 1);

    extern int debugsm;
    if(debugsm)
    {
        extern void viewshadowmap();
        viewshadowmap();
    }

    extern int debugglare;
    if(debugglare)
    {
        extern void viewglaretex();
        viewglaretex();
    }

    extern int debugdepthfx;
    if(debugdepthfx)
    {
        extern void viewdepthfxtex();
        viewdepthfxtex();
    }

    glEnable(GL_BLEND);
    
    if(!mainmenu)
    {
        drawdamagescreen(w, h);
        drawdamagecompass(w, h);
        drawdeathpanicscreen(w, h);    //faned
        drawzoomscopescreen(w, h);    //faned
    }

    glEnable(GL_TEXTURE_2D);
    defaultshader->set();

    //start faned
    int conw = int(w/conscale), conh = int(h/conscale), abovehud = conh - FONTH, limitgui = abovehud;
    if(sehud && !mainmenu && game::player1->state != CS_EDITING && game::player1->state != CS_SPECTATOR && !m_check(game::gamemode, M_INSTA))
    {
        conw = int(w/conscale), conh = int(h/conscale), abovehud = h*2.48f - FONTH, limitgui = h*2.9 - FONTH;
    }
    else conw = int(w/conscale), conh = int(h/conscale), abovehud = conh - FONTH, limitgui = abovehud-250;

    if(mainmenu && !hideversion)
    {
        glPushMatrix();
        glScalef(1/3.5f, 1/3.5f, 1);
        int tw, th;
        text_bounds(version, tw, th);
        draw_textf("\f7%s", 30, h*3.5f-th-20, version);
        glPopMatrix();
    }
    //end faned

    if(!hidehud && !mainmenu)
    {
        if(!hidestats)
        {
            glPushMatrix();
            glScalef(conscale, conscale, 1);

            int roffset = 0;

            if(showspeed && !sehud)    //faned
            {
                float speed = game::player1->vel.magnitude2();
                speed+= 0.5;
                int result = (int)speed;
                draw_textf("speed %d", conw-5*FONTH, conh-FONTH*3/2, result);
                roffset += FONTH;
            }

            if(showfps && !sehud)    //faned
            {
                static int lastfps = 0, prevfps[3] = { 0, 0, 0 }, curfps[3] = { 0, 0, 0 };
                if(totalmillis - lastfps >= statrate)
                {
                    memcpy(prevfps, curfps, sizeof(prevfps));
                    lastfps = totalmillis - (totalmillis%statrate);
                }
                int nextfps[3];
                getfps(nextfps[0], nextfps[1], nextfps[2]);
                loopi(3) if(prevfps[i]==curfps[i]) curfps[i] = nextfps[i];
                if(showfpsrange) draw_textf("fps %d+%d-%d", conw-7*FONTH, conh-FONTH*3/2, curfps[0], curfps[1], curfps[2]);
                else draw_textf("fps %d", conw-5*FONTH, conh-FONTH*3/2-roffset, curfps[0]);
                roffset += FONTH;
            }

            if(wallclock && !sehud)    //faned
            {
                if(!walltime) { walltime = time(NULL); walltime -= totalmillis/1000; if(!walltime) walltime++; }
                time_t walloffset = walltime + totalmillis/1000;
                struct tm *localvals = localtime(&walloffset);
                static string buf;
                if(localvals && strftime(buf, sizeof(buf), wallclocksecs ? (wallclock24 ? "%H:%M:%S" : "%I:%M:%S%p") : (wallclock24 ? "%H:%M" : "%I:%M%p"), localvals))
                {
                    // hack because not all platforms (windows) support %P lowercase option
                    // also strip leading 0 from 12 hour time
                    char *dst = buf;
                    const char *src = &buf[!wallclock24 && buf[0]=='0' ? 1 : 0];
                    while(*src) *dst++ = tolower(*src++);
                    *dst++ = '\0'; 
                    draw_text(buf, conw-5*FONTH, conh-FONTH*3/2-roffset);
                    roffset += FONTH;
                }
            }

            if(showtimeremaining && !m_check(game::gamemode, M_EDIT))    //faned
            {
                int val = max(game::maplimit - lastmillis, 0)/1000;
                defformatstring(time)("%s%d:%02d", val/60 < 1 ? "\fZ" : "\f7", val/60, val%60);
                draw_textf("-%s", conw-(game::cmode ? 6.5 : 4)*FONTH, FONTH*(game::cmode ? 11 : 1), time);
            }
                       
            if(editmode || showeditstats)
            {
                static int laststats = 0, prevstats[8] = { 0, 0, 0, 0, 0, 0, 0 }, curstats[8] = { 0, 0, 0, 0, 0, 0, 0 };
                if(totalmillis - laststats >= statrate)
                {
                    memcpy(prevstats, curstats, sizeof(prevstats));
                    laststats = totalmillis - (totalmillis%statrate);
                }
                int nextstats[8] =
                {
                    vtris*100/max(wtris, 1),
                    vverts*100/max(wverts, 1),
                    xtraverts/1024,
                    xtravertsva/1024,
                    glde,
                    gbatches,
                    getnumqueries(),
                    rplanes
                };
                loopi(8) if(prevstats[i]==curstats[i]) curstats[i] = nextstats[i];

                abovehud -= 2*FONTH;
                draw_textf("wtr: %dk (%d%%) wvt: %dk (%d%%) evt: %dk eva: %dk", FONTH/2, abovehud, wtris/1024, curstats[0], wverts/1024, curstats[1], curstats[2], curstats[3]);
                draw_textf("ond: %d va: %d gl: %d (%d) oq: %d lm: %d rp: %d pvs: %d", FONTH/2, abovehud+FONTH, allocnodes*8, allocva, curstats[4], curstats[5], curstats[6], lightmaps.length(), curstats[7], getnumviewcells());
                limitgui = abovehud;
            }

            if(editmode || showeditstats)
            { 
                abovehud -= FONTH;
                draw_textf("campos: %s %s %s cube: %s%d%s", FONTH/2, abovehud, floatstr(camera1->o.x), floatstr(camera1->o.y), floatstr(camera1->o.z), selchildcount<0 ? "1/" : "", abs(selchildcount), showmat && selchildmat > 0 ? getmaterialdesc(selchildmat, ": ") : "");
                char *editinfo = executestr("edithud");
                if(editinfo)
                {
                    if(editinfo[0])
                    {
                        int tw, th;
                        text_bounds(editinfo, tw, th);
                        th += FONTH-1; th -= th%FONTH;
                        abovehud -= max(th, FONTH);
                        draw_text(editinfo, FONTH/2, abovehud);
                    }
                    DELETEA(editinfo);
                }
            }
            else if(identexists("gamehud"))
            {
                char *gameinfo = executestr("gamehud");
                if(gameinfo)
                {
                    if(gameinfo[0])
                    {
                        int tw, th;
                        text_bounds(gameinfo, tw, th);
                        th += FONTH-1; th -= th%FONTH;
                        roffset += max(th, FONTH);    
                        draw_text(gameinfo, conw-max(5*FONTH, 2*FONTH+tw), conh-FONTH/2-roffset);
                    }
                    DELETEA(gameinfo);
                }
            }
            glPopMatrix();
        }

        if(hidestats || (!editmode && !showeditstats))
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            game::gameplayhud(w, h);
            if(!sehud) abovehud = min(abovehud, int(conh*game::abovegameplayhud(w, h)));    //faned
        }
        rendertexturepanel(w, h);
    }
    
    g3d_limitscale((2*limitgui - conh) / float(conh));

    glPushMatrix();
    glScalef(conscale, conscale, 1);
    abovehud -= rendercommand(FONTH/2, abovehud - FONTH/2, conw-FONTH);
    extern int fullconsole;
    if(!hidehud || fullconsole) renderconsole(conw, conh, abovehud - FONTH/2);
    glPopMatrix();

    drawcrosshair(w, h);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

