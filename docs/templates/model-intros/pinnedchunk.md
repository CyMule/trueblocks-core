<!-- markdownlint-disable MD033 MD036 MD041 -->
The TrueBlocks index scraper periodically creates a chunked portion of the index so that it can
be more easily stored in a content-addresable data store such as IPFS. We call these
periodically-created chunks, PinnedChunks. The format of said item is described here. A pinned
chunk is effectively a relational table relating all of the addresses appearing in the chunk
with a list of appearances appearing in the chunk.
