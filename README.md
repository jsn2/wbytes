# wbytes
A command line tool for writing bytes to a file.

Usage: Usage: wbytes target [source]

The tool creates a new file (name specified by 'target') and writes bytes to the file either from a source file as specidfied by '[source]', or from the standard input stream. The bytes to be written must be specified in hexadecimal format.

An example usage with a source file (containing the bytes to write) named 'input.txt':
- vbytes output input.txt

An example using PowerShell to pipe stdout of 'Write-Output' into stdin of vbytes:
- Write-Output 'A1B2C3' | vbytes output
