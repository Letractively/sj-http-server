#!/bin/bash

TESTS="loggertest/tst_loggertest httprequesttest/tst_httprequest"
return_code=0
env
i=1

for t in $TESTS
do
  "./tests/$t" -o "test-result-$i.xml,xml"
  i=$[i + 1]
  rc=$?
  if [ $rc != 0 ]
  then
    return_code=$rc
    echo "FAILED TEST: $t"
  fi
done

if [ $return_code = 0 ]
then
  echo "All tests PASSED"
else 
  echo "Some tests FAILED"
fi

#exit $return_code
