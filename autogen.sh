echo "Generating build information ..."
cd `dirname $0`
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

echo "Bootstrapping physfs ..."
cd src/physfs && ./bootstrap

echo "Running autogen.sh in the \"test\" directory ..."
cp -f paragui.m4 test/acinclude.m4
test/autogen.sh

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
    
echo
echo "Please run ./configure now."
