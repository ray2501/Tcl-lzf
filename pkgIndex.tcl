# -*- tcl -*-
# Tcl package index file, version 1.1
#
if {[package vsatisfies [package provide Tcl] 9.0-]} {
    package ifneeded tcllzf 0.5 \
	    [list load [file join $dir libtcl9tcllzf0.5.so] [string totitle tcllzf]]
} else {
    package ifneeded tcllzf 0.5 \
	    [list load [file join $dir libtcllzf0.5.so] [string totitle tcllzf]]
}
