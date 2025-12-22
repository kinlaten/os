#!/usr/bin/env bash

# This part is correct now!
address=$(./generate-trace.py | tr -d "[] ")

POLICIES=("LRU" "RAND" "CLOCK")

for policy in "${POLICIES[@]}"; do
  if [[ "$policy" != "CLOCK" ]]; then
    echo "--- Policy: $policy ---"
    # I added -C 3 (Cache Size) to ensure consistent testing
    ./paging-policy.py -c -a "$address" -p "$policy" -C 3
  else
    # Clock Policy logic
    for i in 0 1 2 3; do
      echo "--- Policy: CLOCK (Bits: $i) ---"
      ./paging-policy.py -c -a "$address" -p "$policy" -b "$i" -C 3
    done
  fi
done
