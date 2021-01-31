#include <stdio.h>
#include <bson/bson.h>

int
main (int argc, const char **argv)
{

	// Simulate an easy-to-spot payload
	unsigned int payload_len = 0x100;
	unsigned char payload[payload_len];
	int i;
	for (i = 0; i != payload_len; ++i) payload[i] = i;

	// Begin serialization of a bson document
	bson_writer_t *writer;
	uint8_t *buf = NULL;
	size_t buflen = 0;
	writer = bson_writer_new (&buf, &buflen, 0, bson_realloc_ctx, NULL);
	bson_t *b;
	bson_writer_begin (writer, &b);

	// Mount the BSON document
	BSON_APPEND_INT32 (b, "id", 27);
	BSON_APPEND_UTF8 (b, "hello", "world");
	BSON_APPEND_BOOL (b, "bool", true);
	BSON_APPEND_BINARY(b, "payload", BSON_SUBTYPE_BINARY, payload, payload_len);

	// Dump the serialized bson
	{
		FILE *b_out = fopen("hello.bson", "w");
		fwrite(buf, bson_writer_get_length(writer), 1, b_out);
		fclose(b_out);
	}

	// Also output the json representation
	{
		char *j;
		j = bson_as_canonical_extended_json (b, NULL);
		FILE *j_out = fopen("hello.json", "w");
		fprintf (j_out, "%s\n", j);
		fclose(j_out);
		bson_free (j);
	}

	// Cleanup
	bson_writer_end (writer);
	bson_writer_destroy (writer);

	// That's all folks
	return 0;
}
