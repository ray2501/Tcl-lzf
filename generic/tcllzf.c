/*
 * Copyright (c) 2014-2018 Danilo Chang
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */ 

#include <tcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcl_lzf.h"

/*
 *----------------------------------------------------------------------
 *
 * Tcllzf_Init --
 *
 *	Initialize the new package. 
 *
 * Results:
 *	A standard Tcl result
 *
 *----------------------------------------------------------------------
 */
int Tcllzf_Init(Tcl_Interp *interp)
{
    /*
     * This may work with 8.0, but we are using strictly stubs here,
     * which requires 8.1.
     */
    if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION) != TCL_OK) {
	return TCL_ERROR;
    }

    Tcl_CreateNamespace(interp, "::lzf", NULL, NULL);
    
    Tcl_CreateObjCommand(interp, "::lzf::compress", COMPRESS, (ClientData) NULL, NULL);
    Tcl_CreateObjCommand(interp, "::lzf::decompress", DECOMPRESS, (ClientData) NULL, NULL);
    Tcl_CreateObjCommand(interp, "::lzf::compressByte", COMPRESSB, (ClientData) NULL, NULL);
    Tcl_CreateObjCommand(interp, "::lzf::decompressByte", DECOMPRESSB, (ClientData) NULL, NULL);

    return TCL_OK;
}
