# Spark
#
# Copyright (c) 2011 Rafal Przywarski
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
import sys
import os
from PyQt4 import QtGui, QtCore

class License:
    @staticmethod
    def getText():
        license = "// Spark\n"
        license += "//\n"
        license += "// Copyright (c) 2011 Rafal Przywarski\n"
        license += "//\n"
        license += "// Distributed under the Boost Software License, Version 1.0.\n"
        license += "// (See accompanying file LICENSE_1_0.txt or copy at\n"
        license += "// http://www.boost.org/LICENSE_1_0.txt)\n"
        license += "//\n"
        return license

class ClassQualifiedName:
    def __init__(self, qualifiedName):
        self._ids = qualifiedName.split(".")
    @staticmethod
    def withPrefix(prefix, qualifiedName):
        cqn = ClassQualifiedName(qualifiedName)
        cqn._ids[-1] = prefix + cqn._ids[-1]
        return cqn
    def getNamespaces(self):
        return self._ids[0:-1]
    def getName(self):
        return self._ids[-1]
    def getHeaderGuard(self):
        return "_".join(self._ids).upper() + "_HPP"
    def getIncludePath(self):
        return "/".join(self._ids) + ".hpp"
    def getHeaderPath(self):
        return self.getIncludePath()
    def getSourcePath(self):
        return "/".join(self._ids) + ".cpp"
    def getUnitTestPath(self):
        return self._ids[0] + "/test/unit/" + "/".join(self._ids[1:]) + ".cpp"
    def getMockPath(self):
        return self._ids[0] + "/test/unit/" + "/".join(self._ids[1:]) + ".hpp"
    def getFixtureName(self):
        return "_".join(self._ids)

class OsClassQualifiedName(ClassQualifiedName):
    def __init__(self, qualifiedName, os):
        ClassQualifiedName.__init__(self, qualifiedName)
        self._os = os
    @staticmethod
    def withPrefix(prefix, qualifiedName, os):
        cqn = OsClassQualifiedName(qualifiedName, os)
        cqn._ids[-1] = prefix + cqn._ids[-1]
        return cqn
    def getHeaderPath(self):
        return self._os + "/" + ClassQualifiedName.getHeaderPath(self)
    def getSourcePath(self):
        return self._os + "/" + ClassQualifiedName.getSourcePath(self)
    def getUnitTestPath(self):
        return self._os + "/" + ClassQualifiedName.getUnitTestPath(self)
    def getMockPath(self):
        return self._os + "/" + ClassQualifiedName.getMockPath(self)


class Wizard:
    def writeFile(self, fileName, text):
        path = fileName.rpartition("/")[0]
        QtCore.QDir().mkpath(path)
        f = open(fileName, "w")
        f.write(text)
        f.close()

class ClassWizard(Wizard):
    def createHeaderFile(self, classQName):
        namespaces = classQName.getNamespaces()
        guard = classQName.getHeaderGuard()
        className = classQName.getName()

        text = License.getText()
        text += "#ifndef " + guard + "\n#define " + guard + "\n\n"
        text += "#include <boost/shared_ptr.hpp>\n\n"
        for id in namespaces:
            text += "namespace " + id + "\n{\n"
        text += "\nclass " + className + "\n{\npublic:\n};\n\n"
        text += "typedef boost::shared_ptr<" + className + "> P" + className + ";\n\n"
        for id in namespaces:
            text += "}\n"
        text += "#endif /* " + guard + " */\n"
        self.writeFile(classQName.getHeaderPath(), text)

    def createSourceFile(self, classQName):
        namespaces = classQName.getNamespaces()
        text = License.getText()
        text += "#include <" + classQName.getIncludePath() + ">\n\n"
        for id in namespaces:
            text += "namespace " + id + "\n{\n"
        for id in namespaces:
            text += "}\n"
        self.writeFile(classQName.getSourcePath(), text)

    def createUnitTestFile(self, classQName):
        fixtureName = classQName.getFixtureName()
        text = License.getText()
        text += "#include <" + classQName.getIncludePath() + ">\n"
        text += "#include <spark/test/googlemock.hpp>\n"
        text += "\n"
        text += "using namespace testing;\n"
        text += "using namespace spark;\n"
        text += "\n"
        text += "struct " + fixtureName + " : testing::Test\n"
        text += "{\n"
        text += "};\n"
        text += "\n"
        text += "TEST_F(" + fixtureName + ", firstTest)\n"
        text += "{\n"
        text += "}\n"
        self.writeFile(classQName.getUnitTestPath(), text)

    def createClass(self, strName):
        classQName = ClassQualifiedName(strName)
        self.createHeaderFile(classQName)
        self.createSourceFile(classQName)
        self.createUnitTestFile(classQName)

    def createOsClass(self, strName, os):
        classQName = OsClassQualifiedName(strName, os)
        self.createHeaderFile(classQName)
        self.createSourceFile(classQName)

    def createOsClassWithUT(self, strName, os):
        classQName = OsClassQualifiedName(strName, os)
        self.createHeaderFile(classQName)
        self.createSourceFile(classQName)
        self.createUnitTestFile(classQName)

class InterfaceWizard(Wizard):
    def createHeaderFile(self, classQName):
        namespaces = classQName.getNamespaces()
        guard = classQName.getHeaderGuard()
        className = classQName.getName()

        text = License.getText()
        text += "#ifndef " + guard + "\n#define " + guard + "\n\n"
        text += "#include <boost/shared_ptr.hpp>\n\n"
        for id in namespaces:
            text += "namespace " + id + "\n{\n"
        text += "\nclass " + className + "\n"
        text += "{\n"
        text += "public:\n"
        text += "    virtual ~" + className + "() { }\n"
        text += "protected:\n"
        text += "    " + className + "& operator=(const " + className + "& ) { return *this; }\n"
        text += "};\n\n"
        text += "typedef boost::shared_ptr<" + className + "> P" + className + ";\n\n"
        for id in namespaces:
            text += "}\n"
        text += "#endif /* " + guard + " */\n"
        self.writeFile(classQName.getHeaderPath(), text)

    def createInterface(self, strName):
        classQName = ClassQualifiedName(strName)
        self.createHeaderFile(classQName)

    def createOsInterface(self, strName, os):
        classQName = OsClassQualifiedName(strName, os)
        self.createHeaderFile(classQName)

class MockWizard(Wizard):
    def createMockFile(self, classQName, origClassQName):
        namespaces = classQName.getNamespaces()
        guard = classQName.getHeaderGuard()
        className = classQName.getName()

        text = License.getText()
        text += "#ifndef " + guard + "\n#define " + guard + "\n\n"
        text += "#include <" + origClassQName.getHeaderPath() + ">\n"
        text += "#include <spark/test/googlemock.hpp>\n\n"
        for id in namespaces:
            text += "namespace " + id + "\n{\n"
        text += "\nstruct " + className + " : " + origClassQName.getName() + "\n"
        text += "{\n"
        text += "};\n\n"
        text += "typedef boost::shared_ptr<" + className + "> P" + className + ";\n\n"
        for id in namespaces:
            text += "}\n"
        text += "#endif /* " + guard + " */\n"
        self.writeFile(classQName.getMockPath(), text)

    def createMock(self, strName):
        classQName = ClassQualifiedName.withPrefix("M", strName)
        origClassQName = ClassQualifiedName(strName)
        self.createMockFile(classQName, origClassQName)

    def createOsMock(self, strName, os):
        classQName = OsClassQualifiedName.withPrefix("M", strName, os)
        origClassQName = OsClassQualifiedName(strName, os)
        self.createMockFile(classQName, origClassQName)

class FactoryWizard(Wizard):
    def createFactory(self, strName):
        classQName = ClassQualifiedName(strName)
        ClassWizard().createHeaderFile(classQName)
        ClassWizard().createSourceFile(classQName)
        MockWizard().createMock(strName)


class CodeWizard(QtGui.QMainWindow):

    def __init__(self):
        super(CodeWizard, self).__init__()
        self.initUi()

    def initUi(self):

        createClassAction = QtGui.QAction("Create Class with UT", self)
        createClassAction.setStatusTip("Create a class with a test suite")
        createUnixClassAction = QtGui.QAction("Create Unix Class", self)
        createUnixClassAction.setStatusTip("Create a Unix class")
        createUnixClassWithUTAction = QtGui.QAction("Create Unix Class with UT", self)
        createUnixClassWithUTAction.setStatusTip("Create a Unix class with a test suite")
        createWin32ClassAction = QtGui.QAction("Create Win32 Class", self)
        createWin32ClassAction.setStatusTip("Create a Win32 class")
        createWin32ClassWithUTAction = QtGui.QAction("Create Win32 Class with UT", self)
        createWin32ClassWithUTAction.setStatusTip("Create a Win32 class with a test suite")
        createInterfaceAction = QtGui.QAction("Create Interface", self)
        createInterfaceAction.setStatusTip("Create an interface")
        createUnixInterfaceAction = QtGui.QAction("Create Unix Interface", self)
        createUnixInterfaceAction.setStatusTip("Create a unix interface")
        createWin32InterfaceAction = QtGui.QAction("Create Win32 Interface", self)
        createWin32InterfaceAction.setStatusTip("Create a win32 interface")
        createMockAction = QtGui.QAction("Create Mock", self)
        createMockAction.setStatusTip("Create a mock")
        createUnixMockAction = QtGui.QAction("Create Unix Mock", self)
        createUnixMockAction.setStatusTip("Create a unix mock")
        createWin32MockAction = QtGui.QAction("Create Win32 Mock", self)
        createWin32MockAction.setStatusTip("Create a win32 mock")
        createFactoryAction = QtGui.QAction("Create Factory", self)
        createFactoryAction.setStatusTip("Create a factory")
        self.connect(createClassAction, QtCore.SIGNAL("triggered()"), self.createClass)
        self.connect(createUnixClassAction, QtCore.SIGNAL("triggered()"), self.createUnixClass)
        self.connect(createUnixClassWithUTAction, QtCore.SIGNAL("triggered()"), self.createUnixClassWithUT)
        self.connect(createWin32ClassAction, QtCore.SIGNAL("triggered()"), self.createWin32Class)
        self.connect(createWin32ClassWithUTAction, QtCore.SIGNAL("triggered()"), self.createWin32ClassWithUT)
        self.connect(createInterfaceAction, QtCore.SIGNAL("triggered()"), self.createInterface)
        self.connect(createUnixInterfaceAction, QtCore.SIGNAL("triggered()"), self.createUnixInterface)
        self.connect(createWin32InterfaceAction, QtCore.SIGNAL("triggered()"), self.createWin32Interface)
        self.connect(createMockAction, QtCore.SIGNAL("triggered()"), self.createMock)
        self.connect(createUnixMockAction, QtCore.SIGNAL("triggered()"), self.createUnixMock)
        self.connect(createWin32MockAction, QtCore.SIGNAL("triggered()"), self.createWin32Mock)
        self.connect(createFactoryAction, QtCore.SIGNAL("triggered()"), self.createFactory)

        self.toolbar = self.addToolBar("Main")
        self.toolbar.addAction(createClassAction)
        self.toolbar.addAction(createUnixClassAction)
        self.toolbar.addAction(createUnixClassWithUTAction)
        self.toolbar.addAction(createWin32ClassAction)
        self.toolbar.addAction(createWin32ClassWithUTAction)
        self.toolbar.addAction(createInterfaceAction)
        self.toolbar.addAction(createUnixInterfaceAction)
        self.toolbar.addAction(createWin32InterfaceAction)
        self.toolbar.addAction(createMockAction)
        self.toolbar.addAction(createUnixMockAction)
        self.toolbar.addAction(createWin32MockAction)
        self.toolbar.addAction(createFactoryAction)
        self.toolbar.setOrientation(QtCore.Qt.Vertical)

        self.setSizePolicy(QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Minimum))
        self.setWindowTitle('Code Wizard')

    def createClass(self):
        classQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Class', 'Enter class name:')
        if not ok:
            return
        ClassWizard().createClass(str(classQualifiedName))

    def createUnixClass(self):
        classQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Unix Class', 'Enter class name:')
        if not ok:
            return
        ClassWizard().createOsClass(str(classQualifiedName), 'unix')

    def createUnixClassWithUT(self):
        classQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Unix Class', 'Enter class name:')
        if not ok:
            return
        ClassWizard().createOsClassWithUT(str(classQualifiedName), 'unix')

    def createWin32Class(self):
        classQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Win32 Class', 'Enter class name:')
        if not ok:
            return
        ClassWizard().createOsClass(str(classQualifiedName), 'win32')

    def createWin32ClassWithUT(self):
        classQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Win32 Class', 'Enter class name:')
        if not ok:
            return
        ClassWizard().createOsClassWithUT(str(classQualifiedName), 'win32')

    def createInterface(self):
        interfaceQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Interface', 'Enter interface name:')
        if not ok:
            return
        InterfaceWizard().createInterface(str(interfaceQualifiedName))

    def createUnixInterface(self):
        interfaceQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Unix Interface', 'Enter interface name:')
        if not ok:
            return
        InterfaceWizard().createOsInterface(str(interfaceQualifiedName), 'unix')

    def createWin32Interface(self):
        interfaceQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Win32 Interface', 'Enter interface name:')
        if not ok:
            return
        InterfaceWizard().createOsInterface(str(interfaceQualifiedName), 'win32')

    def createMock(self):
        mockQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Mock', 'Enter mock name:')
        if not ok:
            return
        MockWizard().createMock(str(mockQualifiedName))

    def createUnixMock(self):
        mockQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Unix Mock', 'Enter mock name:')
        if not ok:
            return
        MockWizard().createOsMock(str(mockQualifiedName), 'unix')

    def createWin32Mock(self):
        mockQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Win32 Mock', 'Enter mock name:')
        if not ok:
            return
        MockWizard().createOsMock(str(mockQualifiedName), 'win32')

    def createFactory(self):
        factoryQualifiedName, ok = QtGui.QInputDialog.getText(self, 'Create Factory', 'Enter factory name:')
        if not ok:
            return
        FactoryWizard().createFactory(str(factoryQualifiedName))


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon(os.path.dirname(sys.argv[0]) + "/wizard.png"))
    ex = CodeWizard()
    ex.show()
    sys.exit(app.exec_())
