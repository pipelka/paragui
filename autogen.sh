#!/bin/sh

cd `dirname $0`
TOPDIR=`pwd`

echo
echo "Bootstrapping physfs ..."

cd ./src/physfs
sh bootstrap
cd $TOPDIR

echo "Generating build information ..."
aclocalinclude="$ACLOCAL_FLAGS"

echo "Running libtoolize ..."
libtoolize --copy --force --automake || exit 1

echo "Running aclocal $aclocalinclude ..."
aclocal $aclocalinclude || {
    echo
    echo "**Error**: aclocal failed. This may mean that you have not"
    echo "installed all of the packages you need, or you may need to"
    echo "set ACLOCAL_FLAGS to include \"-I \$prefix/share/aclocal\""
    echo "for the prefix where you installed the packages whose"
    echo "macros were not found"
    exit 1
}

echo "Running autoheader ..."
autoheader || ( echo "***ERROR*** autoheader failed." ; exit 1 )

echo "Running automake ..."
automake -c -a --foreign || ( echo "***ERROR*** automake failed." ; exit 1 )

echo "Running autoconf ..."
autoconf || ( echo "***ERROR*** autoconf failed." ; exit 1 )

echo 
echo "Checking for tools needed to maintain the package ..."
echo

echo "Checking for \"zip\" ..."
( zip -h >/dev/null 2>&1 ) || {
    echo "***ERROR*** zip utility not found!"
    echo "You need the zip utility to create theme packages"
    exit 1
}

echo "Checking for \"unix2dos\" ..."
( unix2dos -h >/dev/null 2>&1 ) || {
    echo "***WARNING** unix2dos not found!"
    echo "You will be unable to convert VisualC workspace files"
    echo "(Please don't distribute unconverted VisualC projects!)"
}

echo "Checking for \"doxygen\" ..."
( which doxygen >/dev/null 2>&1 ) || {
    echo "***WARNING** doxygen not found!"
    echo "You will be unable to generate the API documentation"
}

echo "Checking for \"dot\" ..."
( which dot >/dev/null 2>&1 ) || {
    echo "***WARNING** graphviz not found!"
    echo "Class diagrams will be disabled in your API documentation"
}

echo
echo "Please run ./configure now."
