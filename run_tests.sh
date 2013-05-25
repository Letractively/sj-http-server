#!/bin/bash

TESTS="loggertest/tst_loggertest httprequesttest/tst_httprequest"

return_code=0

for t in $TESTS 
do
echo "running test [$t]"
"tests/$t"
rc=$?
if [ $rc != 0 ]
then
  return_code=$rc
echo "$return_code 123"
fi
done

echo $return_code
exit $return_code
