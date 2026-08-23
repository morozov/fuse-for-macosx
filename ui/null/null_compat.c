/* null_compat.c: build-completeness glue for the headless null build.

   The null build configures with --disable-sockets (so it needs neither
   Spectranet nor mbedTLS) and therefore excludes the socket compat layer and
   the Spectranet NIC engines. utils.c still references the socket helpers,
   which are not exercised headless, so trivial stubs satisfy the linker.

   The xfs engine is NOT stubbed here: 153ee311 made the RAM-backed filesystem
   engine always built, for the GDB vfile feature, so xfs_ram_engine, xfs_reset
   and the xfs-debug hooks are real symbols in every configuration.

   It also supplies main(): the fork renames fuse.c's entry point to old_main
   and expects the UI layer to provide main() (the Cocoa app does); the null UI
   does so here.

   Copyright (c) 2026 Sergei Morozov

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
*/

#include "config.h"

#include "compat.h"

/* Socket compat layer (excluded by --disable-sockets) */
void compat_socket_networking_init( void ) {}
void compat_socket_networking_end( void ) {}
int  compat_socket_close( compat_socket_t fd ) { (void)fd; return 0; }

/* Entry point: hand off to fuse.c's renamed main. */
extern int old_main( int argc, char **argv );

int
main( int argc, char **argv )
{
  return old_main( argc, argv );
}
