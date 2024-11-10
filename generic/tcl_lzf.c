/*
 * tcl_lzf.c --
 *
 *	This file implements compress/decompress function from liblzf.
 *
 * Copyright (c) 2014-2018 Danilo Chang
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tcl_lzf.h"
#include "lzf.h"

TCL_DECLARE_MUTEX(tcllzf_mutex);


int COMPRESS (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const obj[])
{
    char *inbuffer = NULL, *outbuffer = NULL;
    Tcl_Size inlen = 0;
    int outlen = 0;
    Tcl_Obj *outstr;

    if(objc != 2)
    {
        Tcl_WrongNumArgs(interp, 1, obj, "inString");
        return TCL_ERROR;
    }

    inlen = Tcl_GetCharLength(obj[1]);
    inbuffer = (char *) Tcl_GetStringFromObj(obj[1], &inlen);
    if(!inbuffer || inlen < 1) {
        return TCL_ERROR;
    }

    outlen = inlen * 2;  /* We maybe need prepare more buffer for output need. */
    if(outlen <= 0) {
	return TCL_ERROR;
    }

    if (inlen == 1) outlen++;

    outbuffer = (char *)malloc(outlen + 1);
    if (outbuffer == NULL) {
	return TCL_ERROR;
    }

    Tcl_MutexLock(&tcllzf_mutex);
    outlen = lzf_compress(inbuffer, inlen, outbuffer, outlen + 1);
    Tcl_MutexUnlock(&tcllzf_mutex);

    if (outlen) {
        /* create a string object and return result */
        outstr = (Tcl_Obj *) Tcl_NewStringObj(outbuffer, outlen);
        Tcl_SetObjResult(interp, outstr);
    } else {
        if(outbuffer) free(outbuffer);  /* free outbuffer before we quit */
	return TCL_ERROR;
    }

    if(outbuffer) free(outbuffer);

    return TCL_OK;
}


int DECOMPRESS (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const obj[])
{
    char *inbuffer = NULL, *outbuffer = NULL;
    Tcl_Size inlen = 0;
    int outlen = 0;
    Tcl_Obj *outstr; 

    if(objc != 3)
    {
        Tcl_WrongNumArgs(interp, 2, obj, "inString outLength");
        return TCL_ERROR;
    }
   
    inlen = Tcl_GetCharLength(obj[1]);
    inbuffer = (char *) Tcl_GetStringFromObj(obj[1], &inlen);
    if(!inbuffer || inlen < 1) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, obj[2], &outlen) != TCL_OK) {
        return TCL_ERROR;
    }

    if(outlen <= 0) {
	return TCL_ERROR;
    }

    outbuffer = (char *)malloc(outlen);
    Tcl_MutexLock(&tcllzf_mutex);
    outlen = lzf_decompress(inbuffer, inlen, outbuffer, outlen);
    Tcl_MutexUnlock(&tcllzf_mutex);

    if (outlen) {
        outstr = (Tcl_Obj *) Tcl_NewStringObj(outbuffer, outlen);
        Tcl_SetObjResult(interp, outstr);
    } else {
        if(outbuffer) free(outbuffer);  /* free outbuffer before we quit */
	return TCL_ERROR;
    }

    if(outbuffer) free(outbuffer);

    return TCL_OK;
}

int COMPRESSB (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const obj[])
{
    unsigned char *inbuffer = NULL, *outbuffer = NULL;
    Tcl_Size inlen = 0;
    int outlen = 0;
    Tcl_Obj *outstr; 

    if(objc != 2)
    {
        Tcl_WrongNumArgs(interp, 1, obj, "byte_array");
        return TCL_ERROR;
    }

    inlen = Tcl_GetCharLength(obj[1]);
    inbuffer = (unsigned char *) Tcl_GetByteArrayFromObj(obj[1], &inlen);
    if(!inbuffer || inlen < 1) {
        return TCL_ERROR;
    }

    outlen = inlen * 2;  /* We maybe need prepare more buffer for output need. */
    if(outlen <= 0) {
	return TCL_ERROR;
    }

    if (inlen == 1) outlen++;

    outbuffer = (unsigned char *)malloc(outlen + 1);
    if (outbuffer == NULL) {
	return TCL_ERROR;
    }

    Tcl_MutexLock(&tcllzf_mutex);
    outlen = lzf_compress(inbuffer, inlen, outbuffer, outlen + 1);
    Tcl_MutexUnlock(&tcllzf_mutex);

    if (outlen) {
        /* create a byte array object and return result */
        outstr = (Tcl_Obj *) Tcl_NewByteArrayObj(outbuffer, outlen);
        Tcl_SetObjResult(interp, outstr);
    } else {
        if(outbuffer) free(outbuffer);  /* free outbuffer before we quit */
	return TCL_ERROR;
    }

    if(outbuffer) free(outbuffer);

    return TCL_OK;
}


int DECOMPRESSB (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const obj[])
{
    unsigned char *inbuffer = NULL, *outbuffer = NULL;
    Tcl_Size inlen = 0;
    int outlen = 0;
    Tcl_Obj *outstr;

    if(objc != 3)
    {
        Tcl_WrongNumArgs(interp, 2, obj, "byte_array outLength");
        return TCL_ERROR;
    }

    inlen = Tcl_GetCharLength(obj[1]);
    inbuffer = (unsigned char *) Tcl_GetByteArrayFromObj(obj[1], &inlen);
    if(!inbuffer || inlen < 1) {
        return TCL_ERROR;
    }

    if(Tcl_GetIntFromObj(interp, obj[2], &outlen) != TCL_OK) {
        return TCL_ERROR;
    }

    if(outlen <= 0) {
	return TCL_ERROR;
    }

    outbuffer = (unsigned char *)malloc(outlen);
    Tcl_MutexLock(&tcllzf_mutex);
    outlen = lzf_decompress(inbuffer, inlen, outbuffer, outlen);
    Tcl_MutexUnlock(&tcllzf_mutex);

    if (outlen) {
        outstr = (Tcl_Obj *) Tcl_NewByteArrayObj(outbuffer, outlen);
        Tcl_SetObjResult(interp, outstr);
    } else {
        if(outbuffer) free(outbuffer);  /* free outbuffer before we quit */
	return TCL_ERROR;
    }

    if(outbuffer) free(outbuffer);

    return TCL_OK;
}
