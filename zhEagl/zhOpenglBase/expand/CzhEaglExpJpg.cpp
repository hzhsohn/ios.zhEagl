//
//  CzhEaglExpJpg.cpp
//  zhOpenglEs
//
//  Created by H.zh on 13-11-21.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#include "CzhEaglExpJpg.h"


CzhEaglExpJpg::CzhEaglExpJpg()
{
    data=NULL;
}

CzhEaglExpJpg::~CzhEaglExpJpg()
{
    destroy();
}


struct my_error_mgr {
    struct jpeg_error_mgr pub;	/* "public" fields */
    
    jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
    /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    
    /* Always display the message. */
    /* We could postpone this until after returning, if we chose. */
    (*cinfo->err->output_message) (cinfo);
    
    /* Return control to the setjmp point */
    longjmp(myerr->setjmp_buffer, 1);
}


void CzhEaglExpJpg::destroy()
{
    //初始化数据
    len=0;
    gamma=0;
    width=0;
    height=0;
    if (data) {
        free(data);
        data=NULL;
    }
}

int CzhEaglExpJpg::loadFile(const char*path)
{
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
    /* More stuff */
    FILE * infile;		/* source file */
    JSAMPARRAY buffer;		/* Output row buffer */
    int row_stride;		/* physical row width in output buffer */
    
    destroy();
    
    if ((infile = fopen(path, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", path);
        return 1;
    }
    
    /* Step 1: allocate and initialize JPEG decompression object */
    
    /* We set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        /* If we get here, the JPEG code has signaled an error.
         * We need to clean up the JPEG object, close the input file, and return.
         */
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 1;
    }
    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);
    
    /* Step 2: specify data source (eg, a file) */
    
    jpeg_stdio_src(&cinfo, infile);
    
    /* Step 3: read file parameters with jpeg_read_header() */
    
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    
    width=cinfo.output_width;
    height=cinfo.output_height;
    gamma=cinfo.output_gamma;
    len=width*height*3;
    data=(unsigned char*)malloc(len);
    
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    
    int pos=0;
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        //put_scanline_someplace(buffer[0], row_stride);
        
        int i,temp;
        temp = (3 * width);
        for(i = 0; i < temp; i+=3)
        {
            memcpy(&data[pos], *buffer+i, 3);
            pos+=3;
        }
    }
    
    (void) jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    fclose(infile);

    return 0;
}
