#! /bin/bash

diff hello_v1.c hello_v2.c > diffs_v1_v2
cat diffs_v1_v2
