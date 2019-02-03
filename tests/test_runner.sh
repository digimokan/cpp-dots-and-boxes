#!/bin/sh

cd .. && \
./third_party/smart-build/src/smart-build.sh \
  --clean-all \
  --build-type-release \
  --make-tests && \
./test_runner.sh --no-skip

