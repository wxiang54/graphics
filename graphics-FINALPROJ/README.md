Features Implemented
-----
- [x] Scanline Conversion
- [x] Z Buffering
- [ ] Shading
- - [x] Flat Shading
- - [ ] Goroud Shading
- - [ ] Phong Shading
- [ ] Parsing MDL input
- - [x] LIGHT (for a single light)
- - [x] AMBIENT
- - [x] SHADING ("wireframe" and "flat")
- - [ ] CONSTANTS

Known Bugs
-----
* As you increase step, there are more and more inconsistensies in scanline (undefined behavior, random lines everywhere)

Files
-----
README 		- this file.

PROJECT		- instructions for using these parsers and 
		  building your projects.

MDL.spec	- The entire languange specification.

matrix.c	- stripped down matrix code (new_matrix, free_matrix,
matrix.h	  print_matrix, and identity_matrix).

parser.h	- structures and definitions used by the parser.
		  This defines the command array that the parser fills.

symtab.h	- Symbol table routines. Structures are defined as well as
symtab.c	  add_symbol, lookup_symbol, set_value, and utility
		  symbol table printing routines.

print_pcode.c	- Contains print_pcode. A routine that will print out
		  the arry of commands that the parser fills. This
		  is for testing and debugging purposes.

scripts/test	- A sample script

scripts/\*.mdl	- valid MDL files

mdl.l		- Flex (lex) source file. Flex will use this file to build
		  the lexical scanner.

mdl.y		- Bison (yacc) source file. Bison will use this file to
		  build the parser. This file also holds main(), but
		  you can change that.

Makefile	- The project Makefile

