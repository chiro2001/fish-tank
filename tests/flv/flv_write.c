#include <assert.h>

#include "flv.h"

flv_stream *flv_create(const char *file, uint8_bitmask flags) {
  flv_stream *stream = (flv_stream *)malloc(sizeof(flv_stream));
  if (stream == NULL) {
    return NULL;
  }
  stream->flvin = NULL;
  stream->flvout = fopen(file, "wb");
  if (stream->flvout == NULL) {
    free(stream);
    return NULL;
  }
  stream->current_tag_body_length = 0;
  stream->current_tag_body_overflow = 0;
  stream->current_tag_offset = 0;
  stream->state = FLV_STREAM_STATE_WRITE_START;

  flv_header header;
  header.signature[0] = FLV_SIGNATURE[2];
  header.signature[1] = FLV_SIGNATURE[1];
  header.signature[2] = FLV_SIGNATURE[0];
  header.version = 1;
  header.flags = flags;
  header.offset = 0;
  flv_write_header(stream->flvout, &header);
  return stream;
}

int flv_write_prev_tag_size(flv_stream *stream, size_t val) {
  if (fwrite(&val, 1, 1, stream->flvout) == 0) return FLV_ERROR_OPEN_WRITE;
  stream->state = FLV_STREAM_STATE_PREV_TAG_SIZE;
  return FLV_OK;
}

int flv_write_metadata(flv_stream *stream) {
  // write "onMetaData"
  amf_data *metadata = amf_str("onMetaData");
  printf("meta str\n");
  amf_data_file_write(metadata, stream->flvout);
  amf_data *array = amf_array_new();
  assert(array);
  amf_array_push(array, amf_str("width"));
  amf_array_push(array, amf_number_new(800));
  // amf_array_push(amf_str("height"), amf_number_new(600));
  printf("meta array\n");
  amf_data_file_write(array, stream->flvout);
  printf("wrote\n");
  return FLV_OK;
}