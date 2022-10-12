# wbytes
A command line tool for writing bytes to a file.

Usage: Usage: wbytes target [source]

The tool creates a new file (name specified by 'target') and writes bytes to the file either from a source file as specidfied by '[source]', or from the standard input stream. The bytes to be written must be specified in hexadecimal format.

An example usage with a source file (containing the bytes to write) named 'input.txt':
- .\wbytes output input.txt

An example using PowerShell to pipe stdout of 'Write-Output' into stdin of wbytes:
- Write-Output 'A1B2C3' | .\wbytes output

Screenshots:

![image](https://user-images.githubusercontent.com/72470804/195349101-da459e1f-f9ba-4006-8ed9-75d52ea56583.png)
