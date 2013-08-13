#!/bin/bash

TESTS=`find tests/ -name 'tst_*' | grep -vF '.'`
rm -rf ./tests/results
mkdir -p ./tests/results

for t in $TESTS
do
  echo $t
  test_name=`echo $t | sed -r  's|.+/tst_||g'`
  echo "Running test $test_name"
  "./$t" -o "tests/results/test-result-$test_name.xml,xml"
done

echo 'All tests done'

