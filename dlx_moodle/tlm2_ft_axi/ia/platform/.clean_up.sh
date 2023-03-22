#!/bin/bash
trap "/bin/rm -f /localdev/apal/test_area/FT_tests/tmicro_cache_tlm2_AT/tmicro_cache/tlm2_ft/platform/.clean_up.sh" 0
sleep 5
exec $COWAREHOME/common/bin/process_cleanup 2248 > /dev/null 2>&1
