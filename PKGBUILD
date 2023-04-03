pkgname=wine-aom-voobly
pkgver=8.5
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

sha512sums=('f6aaab8a32eb7bce7f48d21d99417c9e6e8fe41b3d36320762775ef954db7ddd4fcff01d56475f35038d814557834a41a9e3ae85e5cae8a1b820c5044b42a327'
            '194327242e7a6cb3c2d5f9006d8c93ac521c988ed45456da5c9d565ebda8f041fae82bb5b7197ae47f813a4435591cb8ad3c49699b03fbb688c11b79d893eff5'
            'b4b37a421cdb8833414ea87d824d3ba984f2c41fce0701839657169c3a10954e58cf871c1bfe8df9e38577fe9fa1938ac5ea1ea3bf78dc55fd14a7321bbe83be'
            '7d31583f535d971d55a6e94b41f2a081b8177b44f9b0349884687988d14d823510ccf1ba6c480111d3a98850de8fcf670ba1993e0c394460eae6229fa7da9c63'
            'f1a96c60e9882f97d5ea6b707b18b6124c1d4080521692577e39eb0aee0dc0ade3f12b3c310ac5b374ceae4826ebf259a4eb58b8f2fa1a66ab944d90ce70b91f')

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
  patch
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
    --enable-win64 \
    --with-xattr

  make -j$(nproc)

  echo "Building Wine-32..."

  export PKG_CONFIG_PATH="/usr/lib32/pkgconfig"

  cd "$srcdir/$pkgname-32-build"
  ../$pkgname/configure \
    --prefix=$_prefix \
    --libdir=$_prefix/lib32 \
    --with-x \
    --with-gstreamer \
    --with-xattr \
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
