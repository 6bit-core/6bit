# Seeds

Utility to generate the `seeds.txt` list that is compiled into the client
(see [src/chainparamsseeds.h](/src/chainparamsseeds.h) and other utilities in
[contrib/seeds](/contrib/seeds)).

Be sure to update `PATTERN_AGENT` in `makeseeds.py` to include the current version,
and remove old versions as necessary. At a minimum, do this whenever
`SeedsServiceFlags()` changes its default return value, since those are the
services with which seeds are added to addrman.

Update `MIN_BLOCKS` in `makeseeds.py` and the `-m` / `--minblocks` arguments
below as needed.

Run the following command from the `/contrib/seeds` directory:

```bash
python3 generate-seeds.py . > ../../src/chainparamsseeds.h
