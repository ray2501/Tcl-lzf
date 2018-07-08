#ifndef _TCLLZF
#define _TCLLZF

#include <tcl.h>

/*
 * Windows needs to know which symbols to export.
 */

#ifdef BUILD_tcllzf
#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLEXPORT
#endif /* BUILD_tcllzf */


/*
 * For C++ compilers, use extern "C"
 */

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Only the _Init function is exported.
 */

EXTERN int	Tcllzf_Init(Tcl_Interp * interp);

int COMPRESS (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST obj[]);
int DECOMPRESS (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST obj[]);
int COMPRESSB (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST obj[]);
int DECOMPRESSB (ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST obj[]);


/*
 * end block for C++
 */

#ifdef __cplusplus
}
#endif

#endif /* _TCLLZF */
