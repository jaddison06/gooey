#!/usr/bin/env python3

# https://gist.github.com/jaddison06/05e38544eee1b78c4e1d214f4a01b4a7

# run once then just do `make makefile` whenever you add new source files
# directory structure:
# - root/
#   |- main.cpp
#   |- build/
#      |- generate_makefile.py
#      |- objects/
#         |- <build artefacts go here>
#
# if shit hits the fan with something like "g++: no such directory build/objects" you
# might need to recreate this structure manually
#
# this is caused by make clean failing - it'll delete the dirs but not get around to recreating them

import os
import os.path as path
import itertools

LIBRARIES = ['SDL2', 'SDL2_ttf'] # eg ['SDL2', 'SOMETHING_ELSE_IDK']
WARNINGS = ['all'] # just tags them on. eg ['all', 'no-sign-compare']
CXX_STANDARD = 11 # if thine softwares are not broketh, do not fixeth
EXEC_NAME = 'gooey_demo' # the executable to produce
COMPILER = 'g++' # if you don't use g++ it'll all break. you can, however, use a 
                 # different version of g++

def contains_list(iterable):
    for item in iterable:
        if type(item) == list:
            return True

    return False

def getAllFiles(dirName="."):
    allItems = os.listdir(dirName)
    allFiles = []

    for item in allItems:
        fullPath = os.path.join(dirName, item)
        if path.isdir(fullPath):
            allFiles.append(getAllFiles(fullPath))
        else:
            allFiles.append(fullPath)

    return allFiles

def genString(items, prefix):
    if len(items) == 0:
        return ''
    return prefix + ((' ' + prefix).join(items))

# flatten. can't use itertools.chain_from_iterable() because it counts strings as iterable,
# and because we don't know the depth until runtime
files = getAllFiles()
filesCopy = files.copy()
while contains_list(files):
    #print('\n\n'.join([str(item) for item in files]))
    for item in files:
        #print(item)
        if type(item) == list:
            filesCopy.remove(item)
            for i in item:
                filesCopy.append(i)

    files = filesCopy.copy()



fnames = []

for f in files:
    if ".cpp" in f:
        fnames.append(f[:-4])

objFiles = f"build/objects/{'.o build/objects/'.join([ f[f.rfind('/')+1:] for f in fnames ])}.o"
debugFiles = f"build/objects/{'-debug.o build/objects/'.join([ f[f.rfind('/')+1:] for f in fnames ])}-debug.o"

libraries = genString(LIBRARIES, "-l")
warnings = genString(WARNINGS, "-W")

makefile = ""
makefile += f"main: {objFiles}\n		{COMPILER} {objFiles} -o ./{EXEC_NAME} {libraries}\n\n"
makefile += f"debug: {debugFiles}\n		{COMPILER} {debugFiles} -g -O0 -o ./{EXEC_NAME} {libraries}\n\n"
makefile += f"clean:\n		rm -r ./build/objects\n		mkdir ./build/objects\n		rm ./{EXEC_NAME}\n\n"
makefile += "makefile:\n		python3 ./build/generate_makefile.py\n\n"


# assumes that every .cpp file has a .h file with the same name
for f in fnames:
    rootF = f[f.rfind('/')+1:]

    # main entry
    makefile += f"build/objects/{rootF}.o: {f}.cpp"

    # main.h doesn't exist
    if not f=="./main":
        makefile += f" {f}.h"

    makefile += f"\n		{COMPILER} -c {f}.cpp -I . {warnings} -std=c++{CXX_STANDARD} -o ./build/objects/{rootF}.o\n\n"

    # debug entry
    makefile += f"build/objects/{rootF}-debug.o: {f}.cpp"

    if not f=="./main":
        makefile += f" {f}.h"

    makefile += f"\n		{COMPILER} -c {f}.cpp -I . {warnings} -std=c++{CXX_STANDARD} -g -O0 -o ./build/objects/{rootF}-debug.o\n\n"


print(f"Generated makefile:\n\n{makefile}")
with open("./Makefile", "wt") as fh:
    fh.write(makefile)