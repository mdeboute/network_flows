#!/bin/bash

chmod u+x maxmin.awk
./maxmin.awk $1 > "$1.min"
exit 0
