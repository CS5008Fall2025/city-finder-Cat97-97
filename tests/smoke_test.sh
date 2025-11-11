#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

echo "[1/3] Building..."
make >/dev/null

echo "[2/3] Small dataset checks..."
OUT_SMALL="$(printf "what do i do?\nlist\na f\nf a\na x\nhelp\nexit\n" | ./map.out vertices.txt distances.txt)"
echo "$OUT_SMALL" | grep -q "Invalid Command"
echo "$OUT_SMALL" | grep -q "^b$"
echo "$OUT_SMALL" | grep -q "^x$"
echo "$OUT_SMALL" | grep -q "Path Found..."
echo "$OUT_SMALL" | grep -q "Total Distance: 10"
echo "$OUT_SMALL" | grep -q "Path Not Found..."
echo "$OUT_SMALL" | grep -q "Commands:"
echo "$OUT_SMALL" | grep -q "Goodbye!"

echo "[3/3] Large dataset checks..."
OUT_LARGE="$(printf "list\nexit\n" | ./map.out city_list.dat city_distances.dat)"
echo "$OUT_LARGE" | grep -q "Welcome to the shortest path finder"
echo "$OUT_LARGE" | grep -q "paris"
echo "$OUT_LARGE" | grep -q "Goodbye!"

echo "All smoke tests passed."


