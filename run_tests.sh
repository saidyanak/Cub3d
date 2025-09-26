#!/bin/bash
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR"

echo "Building inspect_map helper..."
# Compile inspect_map by linking only source files (exclude main.c to avoid duplicate main)
gcc -o inspect_map inspect_map.c parse_utils.c parser.c map_check.c ft_libft.c \
    get_next_line/get_next_line.c get_next_line/get_next_line_utils.c -I. || {
  echo "Failed to build inspect_map from sources."; exit 2;
}

TESTS=( *.cub )
declare -A RESULTS

for t in "${TESTS[@]}"; do
  echo
  echo "=== TEST: $t ==="
  echo "--- Parsed struct (inspect_map) ---"
  ./inspect_map "$t"
  r1=$?
  echo "inspect_map exit: $r1"
  echo "--- Runtime check (./cud3d) ---"
  ./cud3d "$t"
  r2=$?
  echo "cud3d exit: $r2"
  RESULTS["$t"]="$r1,$r2"
done

echo
echo "=== SUMMARY ==="
for k in "${!RESULTS[@]}"; do
  IFS=, read -r p r <<< "${RESULTS[$k]}"
  printf "%s -> inspect_map:%d  cud3d:%d\n" "$k" "$p" "$r"
done

echo "All tests completed."
