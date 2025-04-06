# Compiler flags
AM_CPPFLAGS = \
  -I$(top_srcdir)/src \
  -I$(top_srcdir)/lib \
  $(EXTRA_CFLAGS) \
  $(SIMD_FLAGS) \
  $(PTHREAD_CFLAGS)

# Fuzzer binary name
noinst_PROGRAMS = fuzz_ugrep

# Source files for the fuzz target
fuzz_ugrep_SOURCES = fuzz_ugrep.cpp target.cc

# Link statically to the core ugrep and reflex libs
fuzz_ugrep_LDADD = \
  $(top_builddir)/src/libugrep.a \
  $(top_builddir)/lib/libreflex.a \
  $(PTHREAD_LIBS)

