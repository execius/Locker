pkgname=Locker
pkgver=1.0.0
pkgrel=1
pkgdesc="A security-focused password manager"
arch=('x86_64')
url="https://github.com/imrane-bit/Locker"
license=('MIT')
depends=('openssl' 'cjson' 'libb64')
makedepends=('gcc' 'make')

build() {
    cd "$srcdir/"
    make
}

package() {
    cd "$srcdir/"
	  install -Dm755 Locker "$pkgdir/usr/bin/Locker"
    make clean
}
