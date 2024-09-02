#!/usr/bin/env python3

import os

tex = open("content.tex", "w+")
md = open("overview.md", "w+")

with open("content-script") as script:
    for line in script:
        if len(line) == 0:
            continue
        if line[0] == '#':  # comment
            continue

        if line[0] == '-':  # section
            tex.write("\section{{{0}}}\n".format(line[1:].strip()))
            md.write("## {0}\n".format(line[1:].strip()))
            md.write("|name|tex|cpp|description|source|tested|\n")
            md.write("|:-  |:- |:- |:-         |:-    |:-    |\n")

        if line[0] == '+':  # codebook entry
            args = list(map(str.strip, line[1:].split(',')))
            if args[4] == "false":
                continue
            tex.write("\t\subsection{{{0}}}\n".format(args[0]))
            if not args[1] == "None":
                tex.write("\t\input{{{0}}}\n".format(args[1]))
            if not args[2] == "None":
                skip = 1
                try:
                    with open(args[2], encoding="utf-8") as f:
                        for l in f:
                            if l.startswith("#include"):
                                skip += 1
                            else:
                                break
                    tex.write(
                        f"\t\lstinputlisting[firstline={skip}]{{{args[2]}}}\n")
                except FileNotFoundError:
                    print(f"File {args[2]} is missing, exiting.")
                    exit()
                print(f"Parsed file {args[2]}")
                
            pattern = ""
            tex_str = 'None' if args[1] == 'None' else f"[{args[1]}]({args[1]})"
            cpp_str = 'None' if args[2] == 'None' else f"[{args[2]}]({args[2]})"
            md.write(
                f"|{args[0]}|{tex_str}|{cpp_str}|{args[3]}|{args[5]}|{args[6]}|\n")

tex.close()
os.system('xelatex codebook.tex')
os.system('xelatex codebook.tex')

os.remove("codebook.aux")
os.remove("codebook.log")
os.remove("codebook.toc")
