#include <stdio.h>
#include <bson/bson.h>

int
main (int argc, const char **argv)
{
   bson_t *b;
   char *j;

   b = BCON_NEW ("hello", BCON_UTF8 ("bson!"));
   j = bson_as_canonical_extended_json (b, NULL);
   printf ("%s\n", j);

   bson_free (j);
   bson_destroy (b);

   return 0;
}
