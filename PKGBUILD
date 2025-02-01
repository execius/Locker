pkgname=Locker
pkgver=1.0.0
pkgrel=1
pkgdesc="A security-focused password manager"
arch=('x86_64')
url="https://github.com/imrane-bit/Locker"
license=('MIT')
depends=('openssl' 'cjson' 'libb64')
makedepends=('gcc' 'make')


prepare() {
    mkdir -p "$srcdir/source"  # Ensure the directory exists
    cp -r "$startdir/source" "$srcdir/"  # Copy your source directory to srcdir
}
build() {
    cd "$srcdir/source"
    make
}

package() {
    cd "$srcdir/source"
	  install -Dm755 Locker "$pkgdir/usr/bin/Locker"
}
