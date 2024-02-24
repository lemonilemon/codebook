import os

tex = open("content.tex", "w+")
md =  open("overview.md", "w+")

with open("content-script") as script:
    for line in script:
        if len(line) == 0:
            continue
        if line[0] == '#': # comment
            continue
        
        print(line)

        if line[0] == '-': # section
            tex.write("\section{{{0}}}\n".format(line[1:].strip()))
            md.write("## {0}\n".format(line[1:].strip()))
            md.write("|name|tex|cpp|description|source|tested|\n")
            md.write("|:-  |:- |:- |:-         |:-    |:-    |\n")

        if line[0] == '+': # codebook entry
            args = list(map(str.strip, line[1:].split(',')))
            if args[4] == "false":
                continue
            tex.write("\t\subsection{{{0}}}\n".format(args[0]))
            if not args[1] == "None":
                tex.write("\t\input{{{0}}}\n".format(args[1]))
            if not args[2] == "None":
                tex.write("\t\lstinputlisting[firstline=2]{{{0}}}\n".format(args[2]))
            md.write("|{0} |{1}|{2}|{3}        |{4}   |{5}|\n".format(args[0], 
                                                                    '' if args[1] == 'None' else "[{0}]({0})".format(args[1]),
                                                                    '' if args[2] == 'None' else "[{0}]({0})".format(args[2]),
                                                                    args[3],
                                                                    args[4],
                                                                    args[6]))
            

tex.close()
os.system('xelatex codebook.tex')
os.system('xelatex codebook.tex')

os.remove("codebook.aux")
os.remove("codebook.log")
os.remove("codebook.toc")