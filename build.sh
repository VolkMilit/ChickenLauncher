#!/bin/sh

mkdir -p package/DEBIAN
mkdir -p package/usr/local/games

make -j2
chmod 0755 ./ChickenLauncher
mv ChickenLauncher package/usr/local/games/chickenlauncher
make clean

cat > package/DEBIAN/control << EOF
Package: chichenlauncher
Version: 1.3.1
Architecture: amd64
Maintainer: Volk_Milit <javirrdar@gmail.com>
Depends: libaudio2, libc6, libexpat1, libffi6, libfontconfig1, libfreetype6, libgcc1, libglib2.0-0, libice6, libpcre3, libpng12-0, libqtcore4, libqtgui4, libsm6, libstdc++6, libuuid1, libx11-6, libxau6, libc6, libglib2.0-0, libxcb1, libxdmcp6, libxext6, libxrender1, libxt6, zlib1g
Section: games
Priority: optional
Description: An advenced crossplatform (G)ZDoom launcher. Helps load many mods with simple 2 clicks.
EOF

md5sum package/usr/local/games/chickenlauncher | sed 's/package\///g' > package/DEBIAN/md5sums

dpkg --build package
mv package.deb chichenlauncher-1.3_amd64.deb

rm -rf package
