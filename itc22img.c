/* itc22img.c by Kaeding 20130224 */
/* last modified 20130224 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
  FILE *infile, *outfile;
  unsigned char a, b, c, d, e, f, g, h;
  long int size, count;
  char *outname;
  int imgcount=0;
  if (!(infile = fopen (argv[1], "r"))) {
    fprintf (stderr, "unable to open input file\n");
    return 1;
    }
  while (!feof (infile)) {
    a = getc (infile);
    b = getc (infile);
    c = getc (infile);
    d = getc (infile);
    size = a * 0x01000000 + b * 0x010000 + c * 0x0100 + d;
    e = getc (infile);
    f = getc (infile);
    g = getc (infile);
    h = getc (infile);
//    if (!feof (infile))
//      printf ("%ld %c%c%c%c\n",size,e,f,g,h);
    if ((a == 'i') && (b == 't') && (c == 'c') && (d == 'h'))
      for (count=8; count<size; count++)
        getc (infile);
    size -= 8;
    a = e;
    b = f;
    c = g;
    d = h;
    while (((a != 'd') || (b != 'a') || (c != 't') || (d != 'a')) && (!feof (infile)) && (size > 0)) {
      a = b;
      b = c;
      c = d;
      d = getc (infile);
      size--;
      }
    if (size > 0) {
      outname = malloc (strlen (argv[1]) + 2);
      imgcount++;
      strcpy (outname, argv[1]);
      outname [strlen (argv[1]) - 5] = '-';
      outname [strlen (argv[1]) - 4] = imgcount + '0';
      outname [strlen (argv[1]) - 3] = '.';
      a = getc (infile);
      b = getc (infile);
      c = getc (infile);
      d = getc (infile);
      size -= 4;
      if ((a == 0) && (b == 0) && (c == 0) && (d == 0)) {
        a = getc (infile);
        b = getc (infile);
        c = getc (infile);
        d = getc (infile);
        size -= 4;
        }
      if ((a == 0x89) && (b == 'P') && (c == 'N') && (d == 'G')) {
        outname [strlen (argv[1]) - 2] = 'p';
        outname [strlen (argv[1]) - 1] = 'n';
        outname [strlen (argv[1]) - 0] = 'g';
        }
      else if ((a == 0xff) && (b == 0xd8) && (c == 0xff) && (d == 0xe0)) {
        outname [strlen (argv[1]) - 2] = 'j';
        outname [strlen (argv[1]) - 1] = 'p';
        outname [strlen (argv[1]) - 0] = 'g';
        }
     outname [strlen (argv[1]) + 1] = 0;
     if (!(outfile = fopen (outname, "w"))) {
        fprintf (stderr, "unable to open output file\n");
        return 1;
        }
      free (outname);
      putc (a, outfile);
      putc (b, outfile);
      putc (c, outfile);
      putc (d, outfile);
      while (size > 0) {
        if (feof (infile)) {
          fprintf (stderr, "input file ends early\n");
          return 1;
          }
        a = getc (infile);
        size--;
        putc (a, outfile);
        }
      fclose (outfile);
      }
    }
  fclose (infile);
  return 0;
  }
