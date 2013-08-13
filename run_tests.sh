#!/bin/bash

echo "Running tests..."

TESTS=`find tests/ -name 'tst_*' | grep -vF '.'`
rm -rf ./tests/results
mkdir -p ./tests/results

for t in $TESTS
do
  test_name=`echo $t | sed -r  's|.+/tst_||g'`
  echo "  - $test_name"
  "./$t" -o "tests/results/test-result-$test_name.xml,xml"
done

echo 'All tests done'

