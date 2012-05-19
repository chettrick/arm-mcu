# Makefile for building ARM toolchain for OpenBSD

# $Id$

MAKE		= gmake
TAR		= gtar

BINUTILVER	!= awk '/BINUTILVER.*=/ { print $$3 }'	<Makefile
GCCVER		!= awk '/GCCVER.*=/     { print $$3 }'	<Makefile
NEWLIBVER	!= awk '/NEWLIBVER.*=/	{ print $$3 }'	<Makefile
GDBVER		!= awk '/GDBVER.*=/	{ print $$3 }'	<Makefile
PACKAGENAME	:= arm-eabi-tools-$(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(GDBVER).tgz

default_openbsd: $(PACKAGENAME)

fakeroot:
	$(MAKE) source.done
	patch -b -p0 <openbsd.pch.patch
	$(MAKE) fakeroot TAR=$(TAR) GCCEXTRACONFIG="--with-gmp=/usr/local --with-mpc=/usr/local --with-mpfr=/usr/local"

CONTENTS: fakeroot
	echo "@owner root"				>CONTENTS
	echo "@group wheel"				>>CONTENTS
	echo "@mode -w"					>>CONTENTS
	echo "@cwd /usr/local"				>>CONTENTS
	find fakeroot/usr/local/arm-eabi-tools -type d | awk '{ printf("@dir %s\n", substr($$1, 20)); }' >>CONTENTS
	find fakeroot -type f | cut -c 20- | sort	>>CONTENTS

COMMENT:
	echo "ARM Microcontroller Toolchain"		>COMMENT

$(PACKAGENAME): CONTENTS COMMENT
	pkg_create -A `uname -m` -f CONTENTS -D COMMENT="`cat COMMENT`" -d COMMENT -p / -B fakeroot $(PACKAGENAME)
	@-rm CONTENTS
	@-rm COMMENT
