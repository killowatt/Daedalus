functions = open("functions.txt", "r").read().splitlines()
cpp = open("daedalusGL.cpp", "w")
header = open("daedalusGL.h", "w")

for line in functions:
    if "//" in line or line.isspace() or len(line) == 0:
        continue
    
    cpp.write(line + " = (PFN" + line.upper() + 'PROC)wglGetProcAddress("' + line + '");\n')
    header.write("PFN" + line.upper() + "PROC " + line + ";\n")
    
