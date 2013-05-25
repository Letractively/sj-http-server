#!/bin/bash

TESTS="httprequesttest/tst_httprequest loggertest/tst_loggertest"

for t in $TESTS 
do
echo "running test [$t]"
exec "tests/$t"
done


