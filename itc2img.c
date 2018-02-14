/* itc2img.c by Kaeding 2007feb02 */
/* last modified 2011jun28 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
  FILE *infile, *outfile;
  unsigned char a, b, c, d;
  long int size, count, start;
  char *outname;
  if (!(infile = fopen (argv[1], "r"))) {
    fprintf (stderr, "unable to open input file\n");
    return 1;
    }
  a = getc (infile);
  b = getc (infile);
  c = getc (infile);
  d = getc (infile);
  size = a * 0x01000000 + b * 0x010000 + c * 0x0100 + d;
  for (count=4; count<size; count++)
    getc (infile);
  a = getc (infile);
  b = getc (infile);
  c = getc (infile);
  d = getc (infile);
  size = a * 0x01000000 + b * 0x010000 + c * 0x0100 + d;
  size -= 4;
  while (((a != 'd') || (b != 'a') || (c != 't') || (d != 'a')) && (!feof (infile))) {
    a = b;
    b = c;
    c = d;
    d = getc (infile);
    size--;
    }
  if (feof (infile)) {
    fprintf (stderr, "input file ends early\n");
    return 1;
    }
  outname = malloc (strlen (argv[1]) + 1);
  strcpy (outname, argv[1]);
  a = getc (infile);
  b = getc (infile);
  c = getc (infile);
  d = getc (infile);
  start = 4;
  if ((a == 0) && (b == 0) && (c == 0) && (d == 0)) {
    a = getc (infile);
    b = getc (infile);
    c = getc (infile);
    d = getc (infile);
    start += 4;
    }
  if ((a == 0x89) && (b == 'P') && (c == 'N') && (d == 'G')) {
    outname [strlen (argv[1]) - 3] = 'p';
    outname [strlen (argv[1]) - 2] = 'n';
    outname [strlen (argv[1]) - 1] = 'g';
    }
  else if ((a == 0xff) && (b == 0xd8) && (c == 0xff) && (d == 0xe0)) {
    outname [strlen (argv[1]) - 3] = 'j';
    outname [strlen (argv[1]) - 2] = 'p';
    outname [strlen (argv[1]) - 1] = 'g';
    }
  if (!(outfile = fopen (outname, "w"))) {
    fprintf (stderr, "unable to open output file\n");
    return 1;
    }
  free (outname);
  putc (a, outfile);
  putc (b, outfile);
  putc (c, outfile);
  putc (d, outfile);
  for (count=start; count<size; count++) {
    if (feof (infile)) {
      fprintf (stderr, "input file ends early\n");
      return 1;
      }
    a = getc (infile);
    putc (a, outfile);
    }
  fclose (infile);
  fclose (outfile);
  return 0;
  }
