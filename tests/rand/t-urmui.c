/* Test gmp_urandomm_ui.

Copyright 2003, 2005 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA. */

#include <stdio.h>
#include <stdlib.h>
#include "mpir.h"
#include "gmp-impl.h"
#include "tests.h"

#define printf gmp_printf

/* Expect numbers generated by rstate to obey the limit requested. */
void
check_one (const char *name, gmp_randstate_ptr rstate)
{
  static const gmp_ui  n_table[] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    123, 456, 789,

    255, 256, 257,
    1023, 1024, 1025,
    32767, 32768, 32769,

    GMP_UI_MAX/2-2, GMP_UI_MAX/2-1, GMP_UI_MAX/2, GMP_UI_MAX/2+1, GMP_UI_MAX/2+2,

    GMP_UI_MAX-2, GMP_UI_MAX-1, GMP_UI_MAX,
  };

  gmp_ui  got, n;
  int    i, j;

  for (i = 0; i < numberof (n_table); i++)
    {
      n = n_table[i];

      for (j = 0; j < 5; j++)
        {
          got = gmp_urandomm_ui (rstate, n);
          if (got >= n)
            {
              printf ("Return value out of range:\n");
              printf ("  algorithm: %s\n", name);
              printf ("  n:     %#Mx\n", n);
              printf ("  got:   %#Mx\n", got);
              abort ();
            }
        }
    }
}


int
main (int argc, char *argv[])
{
  tests_start ();

  call_rand_algs (check_one);

  tests_end ();
  exit (0);
}
