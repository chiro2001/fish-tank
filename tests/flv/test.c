#include <assert.h>
#include <stdio.h>

#include "flv.h"

#define FILENAME_READ "test.flv"
#define FILENAME_WRITE "out.flv"

int main() {
  printf("flv-test start.\n");
  flv_stream* stream = NULL;
  // printf("======== READ TEST ========\n");
  // printf("open file " FILENAME_READ "\n");
  // stream = flv_open(FILENAME_READ);
  // assert(stream);
  // printf("read header\n");
  // flv_header header;
  // assert(!flv_read_header(stream, &header));
  // printf("header->flags = %x\n", header.flags);
  // printf("read prev tag size\n");
  // uint32 prev_tag_size = 0;
  // assert(!flv_read_prev_tag_size(stream, &prev_tag_size));
  // flv_tag tag;
  // const size_t buf_size = 1024000;
  // uint8_t buf[buf_size];
  // size_t read_size = (size_t)(-1);
  // while (read_size) {
  //   assert(!flv_read_tag(stream, &tag));
  //   printf("read tag: [type=%u, len=%u, time=%u]\n", tag.type,
  //          uint24_be_to_uint32(tag.body_length),
  //          uint24_be_to_uint32(tag.timestamp));
  //   read_size =
  //       flv_read_tag_body(stream, buf, uint24_be_to_uint32(tag.body_length));
  //   printf("read %d byte\n", read_size);
  //   break;
  // }
  // flv_close(stream);

  printf("========= WRITE TEST ========\n");
  printf("create flv file\n");
  stream = flv_create(FILENAME_WRITE, FLV_FLAG_VIDEO);
  // flv_write_tag
  flv_tag script = {.type = FLV_TAG_TYPE_META,
                    .body_length = 0,
                    .stream_id = uint32_to_uint24_be(0),
                    .timestamp = uint32_to_uint24_be(0),
                    .timestamp_extended = 0};
  printf("write tag\n");
  flv_write_tag(stream->flvout, &script);
  printf("write meta\n");
  flv_write_metadata(stream);
  printf("close flv file\n");
  flv_close(stream);
  return 0;
}