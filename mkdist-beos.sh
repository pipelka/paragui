#!/bin/sh

rm -Rf paragui || echo "No dist dir! will create ..."

# create dir structure

echo "Creating distribution dirs ..."

mkdir paragui
mkdir paragui/gnupro
mkdir paragui/gnupro/include
mkdir paragui/gnupro/lib
mkdir paragui/gnupro/bin
mkdir paragui/gnupro/share
mkdir paragui/gnupro/share/aclocal

mkdir paragui/lib
#mkdir paragui/etc
#mkdir paragui/docs
mkdir paragui/test

# copy gnupro files

echo "Copying gnupro files ..."

cp ./include/*.h paragui/gnupro/include
cp ./src/.libs/libparagui.so paragui/gnupro/lib
cp ./src/.libs/libparagui.a paragui/gnupro/lib 
cp paragui-config paragui/gnupro/bin
cp paragui.m4 paragui/gnupro/share/aclocal
cp -rp data paragui/gnupro/share/paragui

cd paragui/gnupro/share/paragui
rm -rf `find ./ -type d -name CVS -print`
rm -rf `find ./ -name "Makefile*" -print`
cd ../../../..

# make gnupro archive

cd paragui/gnupro
zip -r -9 gnupro.zip *
mv gnupro.zip ..
cd ..
rm -Rf gnupro
cd ..

# copy lib, etc, docs

#echo "Copying docs ..."

cp ./src/.libs/libparagui.so paragui/lib
#cp ./etc/paragui.conf paragui/etc/
#cp ./doc/html/*.html paragui/docs/
#cp ./doc/html/*.gif paragui/docs/
#cp ./doc/html/*.css paragui/docs/
#cp ./doc/html/*.dot paragui/docs/

# copy samples

cp ./test/.libs/paratest paragui/test/
cp ./test/testgl paragui/test/

# copy README's

cp README* paragui/
cp COPYING paragui/

# generate INSTALL

cat <<\EOF_INSTALL > paragui/INSTALL 

To install ParaGUI on BeOS x86:

    1.  Unpack the headers and libraries (gnupro.zip) in the GNU tools directory

    2.  Copy lib/libparagui.so to ~/config/lib/

    3.  Look at the example programs in ./test, and check out the HTML
        documentation at the website to see how to use the library.

    4.  Join the ParaGUI mailing list at http://www.bms-austria.com/projects/paragui


Alexander Pipelka
pipelka@teleweb.at
http://www.bms-austria.com/projects/paragui

PS: Dont forget to install the dependency libs:
SDL
SDL_ttf
freetype
EOF_INSTALL

# wrap it in a package

echo "Wraping a package ..."

zip -r -9 paragui-beos.zip paragui

# clean up

echo "Cleaning up ..."
rm -Rf paragui

echo "Done! BeOS package ready for shipment :)"

