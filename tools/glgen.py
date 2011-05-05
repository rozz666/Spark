# Spark
#
# Copyright (c) 2011 Rafal Przywarski
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
import sys
import re
import string


def parseGLVersion(path, version, protoDef):
    lines = open(path).readlines()
    versionFound = False
    prototypesFound = False
    methods = []
    for line in lines:
        if re.match("#ifndef *" + version + " *", line):
            versionFound = True
        elif re.match("#endif *.*", line):
            if prototypesFound:
                prototypesFound = False
            else:
                versionFound = False
        elif versionFound:
            if re.match("#ifdef *" + protoDef + " *", line):
                prototypesFound = True
            elif prototypesFound:
                proc = re.match(" *GLAPI *(\w*) *APIENTRY *(\w*) *\((.*)\) *; *", line)
                if proc:
                    methods.append([ proc.group(1), proc.group(2), proc.group(3) ])
    return methods

def parseGLVersions(path, versions, protoDef):
    methods = []
    for ver in versions:
        methods.extend(parseGLVersion(path, ver, protoDef))
    return methods
        
def parseGL(path, versions):
    return parseGLVersions(path, versions, "GL3_PROTOTYPES")

def parseGLext(path, versions):
    return parseGLVersions(path, versions, "GL_GLEXT_PROTOTYPES")

                
def loadConfig():
    glVersions = [l.rstrip() for l in open("glversions").readlines()]
    glExtensions = [l.rstrip() for l in open("glextensions").readlines()]
    return ( glVersions, glExtensions )

def generateInterface(methods, path):
    f = open(path, 'w')
    for l in open("gllicense").readlines():
        f.write(l)
    f.write("#ifndef SPARK_VIDEO_IGLCONTEXT_HPP\n")
    f.write("#define SPARK_VIDEO_IGLCONTEXT_HPP\n")
    f.write("#include <boost/shared_ptr.hpp>\n")
    f.write("#include <GL3/gl3.h>\n\n")
    f.write("#include <GL3/glext.h>\n\n")
    f.write("namespace spark\n")
    f.write("{\n")
    f.write("namespace video\n")
    f.write("{\n\n")
    f.write("class IGLContext\n")
    f.write("{\n")
    f.write("public:\n");
    f.write("    virtual ~IGLContext() { }\n");
    for m in methods:
        f.write("    virtual {0} {1}({2}) = 0;\n".format(m[0], m[1], m[2]))
    f.write("};\n\n")
    f.write("typedef boost::shared_ptr<IGLContext> PIGLContext;\n\n");
    f.write("}\n")
    f.write("}\n")
    f.write("#endif // SPARK_VIDEO_IGLCONTEXT_HPP\n")

def generateMock(methods, path):
    f = open(path, 'w')
    for l in open("gllicense").readlines():
        f.write(l)
    f.write("#ifndef SPARK_VIDEO_MIGLCONTEXT_HPP\n")
    f.write("#define SPARK_VIDEO_MIGLCONTEXT_HPP\n")
    f.write("#include <spark/test/unit/video/MIGLContext.hpp>\n")
    f.write("#include <spark/test/googlemock.hpp>\n\n")
    f.write("namespace spark\n")
    f.write("{\n")
    f.write("namespace video\n")
    f.write("{\n\n")
    f.write("struct MIGLContext : IGLContext\n")
    f.write("{\n")
    for m in methods:
        params = []
        if m[2].strip() != "void":
            params = [re.match("(.*[ \*])\w+ *", p).group(1).strip() for p in m[2].split(",")]
        f.write("    MOCK_METHOD{0}({1}, {2}({3}));\n".format(len(params), m[1], m[0], string.join(params, ", ")))
    f.write("};\n\n")
    f.write("typedef boost::shared_ptr<MIGLContext> PMIGLContext;\n\n");
    f.write("}\n")
    f.write("}\n")
    f.write("#endif // SPARK_VIDEO_MIGLCONTEXT_HPP\n")

def generateLoader(methods, path):
    f = open(path, 'w')
    for m in methods:
        f.write("    SPARK_LOADGLPROC({0});\n".format(m[1]))
    

if len(sys.argv) != 3:
    print 'usage glgen.py <gl3.h-path> <glext.h-path>'
    sys.exit()

glVersions, glExtensions = loadConfig()
methods = []
methods.extend(parseGL(sys.argv[1], glVersions))
methods.extend(parseGLext(sys.argv[2], glExtensions))
generateInterface(methods, "IGLContext.hpp")
generateMock(methods, "MIGLContext.hpp")