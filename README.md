Tcl-lzf
=====

LZF is an extremely fast (not that much slower than a pure memcpy)
compression algorithm. It is ideal for applications where you want to
save *some* space but not at the cost of speed. It is ideal for
repetitive data as well. The module is self-contained and very small.

It's written in ISO-C with no external dependencies other than what
C provides and can easily be #include'd into your code, no makefile
changes or library builds requires.

LibLZF this library was written by Marc Lehmann <schmorp@schmorp.de> 
(See also  [http://software.schmorp.de/pkg/liblzf.html](http://software.schmorp.de/pkg/liblzf.html)).

Tcl-lzf: liblzf tcl bindings.


Commands
=====
lzf::compress -  accepts a string to compress.  
lzf::decompress - accepts a string and a size in which the uncompressed 
                  result must fit.  
lzf::compressByte -  accepts a byte array to compress.  
lzf::decompressByate - accepts a byte array and a size in which the uncompressed 
                  result must fit.


Example
=====

    package require tcllzf

    set test0 "Hello liblzf, I am tickle"
    set test1 [lzf::compress $test0]
    set test2 [lzf::decompress $test1 128]

    if {[string equal $test0 $test2]==1} {
        puts "OK, get the same thing."
    }

