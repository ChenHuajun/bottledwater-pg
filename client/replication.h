#ifndef REPLICATION_H
#define REPLICATION_H

#include "protocol_client.h"
#include <avro.h>
#include <libpq-fe.h>
#include <server/postgres_fe.h>
#include <server/access/xlogdefs.h>

struct replication_stream {
    PGconn *conn;
    XLogRecPtr recvd_lsn;
    XLogRecPtr fsync_lsn;
    int64 last_checkpoint;
    frame_reader_t frame_reader;
};

typedef struct replication_stream *replication_stream_t;

bool consume_stream(PGconn *conn, char *slot_name, XLogRecPtr start_pos);
bool check_replication_connection(PGconn *conn);
bool create_replication_slot(PGconn *conn, const char *slot_name, const char *output_plugin,
        XLogRecPtr *startpos, char **snapshot_name);

#endif /* REPLICATION_H */
