#!/bin/bash

chessmk -r ./examples/jpeg/jpeg.prx
chessmk -r ./lib/trv32p3.prx
chessmk -r ./model.prx
find ./ -name "chesswork" -type d -exec rm -rf {} \; -prune
find ./ -name "Release" -type d -exec rm -rf {} \; -prune
find ./ -name "Debug" -type d -exec rm -rf {} \; -prune
find ./ -name "Native" -type d -exec rm -rf {} \; -prune
