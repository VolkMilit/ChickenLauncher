#!/bin/sh

VER="1.4.0"

dep()
{
	dpkg -l $(dpkg -S $( ldd $1 | awk '{print $3}' ) | awk '{{sub(":"," ")} print $1}')
}

mkdir -p package/DEBIAN
mkdir -p package/usr/local/games
mkdir -p package/usr/local/share/icons/hicolor/32x32/apps
mkdir -p package/usr/local/share/applications

make -j2

mv ChickenLauncher package/usr/local/games/chickenlauncher

cp package_data/chicken.png package/usr/local/share/icons/hicolor/32x32/apps
cp package_data/ChickenLauncher.desktop package/usr/local/share/applications

sudo chown root:root package/usr/local/games/chickenlauncher
sudo chown root:root package/usr/local/share/icons/hicolor/32x32/apps/chicken.png
sudo chown root:root package/usr/local/share/applications/ChickenLauncher.desktop

make clean

tmp=$(dep ${PWD}/package/usr/local/games/chickenlauncher | awk '/amd64/ {gsub(":amd64",""); print $2, "(>="$3"),"}')

cat > package/DEBIAN/control << EOF
Package: chichenlauncher
Version: $VER
Architecture: amd64
Maintainer: Volk_Milit (aka Ja'Virr-Dar) <javirrdar@gmail.com>
Depends: $(echo $tmp | sed 's/.$//')
Section: games
Priority: optional
Description: An advenced crossplatform (G)ZDoom launcher. Helps load many mods with simple 2 clicks.
EOF

md5sum package/usr/local/games/chickenlauncher | sed 's/package\///g' > package/DEBIAN/md5sums; chmod 0644 package/DEBIAN/md5sums

dpkg --build package
mv package.deb chichenlauncher-$VER_amd64.deb

rm -rf package
