#!/bin/sh

set -e

# build single threaded simulator

echo "#define _ISS_ST" > ../lib/ilx_threaded_switch.h

chessmk +P32 -m ilx_st.prx

echo ""                > ../lib/ilx_threaded_switch.h
