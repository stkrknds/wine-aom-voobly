pkgname=wine-aom-voobly
pkgver=8.20
pkgrel=1

source=(https://dl.winehq.org/wine/source/8.x/wine-$pkgver.tar.xz
        # esync
        https://raw.githubusercontent.com/Frogging-Family/wine-tkg-git/master/wine-tkg-git/wine-tkg-patches/proton/esync/esync-unix-mainline.patch
        # fsync
        https://raw.githubusercontent.com/Frogging-Family/wine-tkg-git/master/wine-tkg-git/wine-tkg-patches/proton/fsync/fsync-unix-mainline.patch
        # fsync_waitv
        https://raw.githubusercontent.com/Frogging-Family/wine-tkg-git/master/wine-tkg-git/wine-tkg-patches/proton/fsync/fsync_futex_waitv.patch
        # aom patch
        https://raw.githubusercontent.com/stkrknds/wine-aom-voobly/main/aom.patch
       )

sha512sums=('86dffc3c9e01506ff2ff75663f48bb3b18a6afaf6381fc3c43c476481cb5c0570129550d2047059f528855e454a629c63e8beb85d5c591d1fdb7a066fbca2623'
            '6564ab392e0142ae4a606bb653df0506b7986c7681d78f63b987151d819a03b10ece5cf71cde406735a96b9c1f1fc7ccaef1ba99613a2cded948699a0cb7d5d3'
            'a279eb8854787ff49cffdcf27d77f9cdddd9954d70021ed35e4eec4962e6def12ae73678df414f980cd7a069db81d21e8dcbcf554d94f040722d164c97df3346'
            '0dd50b7ae8dfab3fd363bc923f6dd3557e4ea07cf65b3d284a3e4a39ff15c55bb6518d0c8892feab11d088a5b1308925c48b72cf9b37ac5b5ff00d42995120c5'
            '5a1a464fa43617c1fca96175f3449c212598dddeaef6c00019cebf239ad81910a95128d1dd6ac6494f66c1d9dd04720982e065e20c6122094706c230304d200c')

pkgdesc="Wine for Age of Mythology & Voobly"
arch=(x86_64)
options=(staticlibs !lto)
license=(LGPL)
depends=(
  fontconfig      lib32-fontconfig
  libxcursor      lib32-libxcursor
  libxrandr       lib32-libxrandr
  libxi           lib32-libxi
  gettext         lib32-gettext
  freetype2       lib32-freetype2
  gcc-libs        lib32-gcc-libs
  libpcap         lib32-libpcap
  desktop-file-utils
)
makedepends=(autoconf bison perl flex mingw-w64-gcc
  giflib                lib32-giflib
  gnutls                lib32-gnutls
  libxinerama           lib32-libxinerama
  libxcomposite         lib32-libxcomposite
  libxxf86vm            lib32-libxxf86vm
  v4l-utils             lib32-v4l-utils
  libpulse              lib32-libpulse
  alsa-lib              lib32-alsa-lib
  libxcomposite         lib32-libxcomposite
  mesa                  lib32-mesa
  mesa-libgl            lib32-mesa-libgl
  opencl-icd-loader     lib32-opencl-icd-loader
  gst-plugins-base-libs lib32-gst-plugins-base-libs
  vulkan-icd-loader     lib32-vulkan-icd-loader
  sdl2                  lib32-sdl2
  libcups               lib32-libcups
  libgphoto2
  sane
  vulkan-headers
  samba
  opencl-headers
)
optdepends=(
  giflib                lib32-giflib
  libldap               lib32-libldap
  gnutls                lib32-gnutls
  v4l-utils             lib32-v4l-utils
  libpulse              lib32-libpulse
  alsa-plugins          lib32-alsa-plugins
  alsa-lib              lib32-alsa-lib
  libxcomposite         lib32-libxcomposite
  libxinerama           lib32-libxinerama
  opencl-icd-loader     lib32-opencl-icd-loader
  gst-plugins-base-libs lib32-gst-plugins-base-libs
  sdl2                  lib32-sdl2
  libgphoto2
  sane
  cups
  samba           dosbox
)
makedepends=(${makedepends[@]} ${depends[@]})

_prefix="/opt/wine-aom-voobly"

prepare() {
  rm -rf $pkgname
  mv wine-$pkgver $pkgname

  # Get rid of old build dirs
  rm -rf $pkgname-{32,64}-build
  mkdir $pkgname-{32,64}-build

  cd $srcdir/$pkgname

  # Apply patches

  echo "Applying aom patch"
  patch -Np1 < ../aom.patch

  echo "Applying esync patch"
  patch -Np1 < ../esync-unix-mainline.patch
 
  echo "Applying fsync patch"
  patch -Np1 < ../fsync-unix-mainline.patch

  echo "Applying futex_waitv patch"
  patch -Np1 < ../fsync_futex_waitv.patch

  # Vulkan
  echo "Running make_vulkan"
  dlls/winevulkan/make_vulkan

  tools/make_requests
  autoreconf -fiv
}

build() {
  cd $srcdir

  # credits to Frogging-Family
  _GCC_FLAGS="-O2 -ftree-vectorize"
  _LD_FLAGS="-Wl,-O1,--sort-common,--as-needed"
  _CROSS_FLAGS="-O2 -ftree-vectorize"
  _CROSS_LD_FLAGS="-Wl,-O1,--sort-common,--as-needed"

  export CFLAGS="${_GCC_FLAGS}"
  export CXXFLAGS="${_GCC_FLAGS}"
  export LDFLAGS="${_LD_FLAGS}"
  export CROSSCFLAGS="${_CROSS_FLAGS}"
  export CROSSLDFLAGS="${_CROSS_LD_FLAGS}"
 
  echo "Building Wine-64..."

  cd "$srcdir/$pkgname-64-build"
  ../$pkgname/configure \
    --prefix=$_prefix \
    --libdir=$_prefix/lib \
    --with-x \
    --with-gstreamer \
    --disable-tests \
    --enable-win64

  make -j$(nproc)

  echo "Building Wine-32..."

  export PKG_CONFIG_PATH="/usr/lib32/pkgconfig"

  cd "$srcdir/$pkgname-32-build"
  ../$pkgname/configure \
    --prefix=$_prefix \
    --libdir=$_prefix/lib32 \
    --with-x \
    --with-gstreamer \
    --disable-tests \
    --with-wine64="$srcdir/$pkgname-64-build"

  make -j$(nproc)
}

package() {
  echo "Packaging Wine-32..."
  cd "$srcdir/$pkgname-32-build"
  make prefix="$pkgdir/$_prefix" \
    libdir="$pkgdir/$_prefix/lib32" \
    dlldir="$pkgdir/$_prefix/lib32/wine" install

  echo "Packaging Wine-64..."
  cd "$srcdir/$pkgname-64-build"
  make prefix="$pkgdir/$_prefix" \
    libdir="$pkgdir/$_prefix/lib" \
    dlldir="$pkgdir/$_prefix/lib/wine" install

  i686-w64-mingw32-strip --strip-unneeded "$pkgdir"/$_prefix/lib32/wine/i386-windows/*.dll
  x86_64-w64-mingw32-strip --strip-unneeded "$pkgdir"/$_prefix/lib/wine/x86_64-windows/*.dll
}
