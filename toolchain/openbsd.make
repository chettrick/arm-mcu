# Makefile for building ARM toolchain for OpenBSD

# $Id$

MAKE		= gmake
TAR		= gtar

BINUTILVER	!= awk '/BINUTILVER.*=/ { print $$3 }'	<Makefile
GCCVER		!= awk '/GCCVER.*=/     { print $$3 }'	<Makefile
NEWLIBVER	!= awk '/NEWLIBVER.*=/	{ print $$3 }'	<Makefile
GDBVER		!= awk '/GDBVER.*=/	{ print $$3 }'	<Makefile
PACKAGENAME	:= arm-tools-$(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(GDBVER).tgz

default_openbsd: $(PACKAGENAME)

fakeroot:
	$(MAKE) source.done
	patch -b -p0 <openbsd.pch.patch
	$(MAKE) fakeroot TAR=$(TAR) GCCEXTRACONFIG="--with-gmp=/usr/local --with-mpc=/usr/local --with-mpfr=/usr/local"
# Why aren't these links already present on OpenBSD?
	ln -s liblto_plugin.so.0.0 fakeroot/usr/local/arm-tools/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so
	ln -s liblto_plugin.so.0.0 fakeroot/usr/local/arm-tools/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so.0

CONTENTS: fakeroot
	echo "@owner root"				>CONTENTS
	echo "@group wheel"				>>CONTENTS
	echo "@mode -w"					>>CONTENTS
	echo "@cwd /usr/local"				>>CONTENTS
	find fakeroot/usr/local/arm-tools -type d | awk '{ printf("@dir %s\n", substr($$1, 20)); }' >>CONTENTS
	find fakeroot -type f | cut -c 20- | sort	>>CONTENTS
	find fakeroot -type l | awk '{ printf("echo %s `readlink %s`\n", $$1, $$1); }' | sh | \
	awk '{ printf("@exec ln -s %s %s\n", $$2, substr($$1,9)); }'            >>CONTENTS
	find fakeroot -type l | awk '{ printf("@unexec rm %s\n", substr($$1, 9)); }' >>CONTENTS

COMMENT:
	echo "ARM Microcontroller Toolchain"		>COMMENT

$(PACKAGENAME): CONTENTS COMMENT
	pkg_create -A `uname -m` -f CONTENTS -D COMMENT="`cat COMMENT`" -d COMMENT -p / -B fakeroot $(PACKAGENAME)
	@-rm CONTENTS
	@-rm COMMENT

clean:
	 $(MAKE) clean

distclean:
	 $(MAKE) distclean
