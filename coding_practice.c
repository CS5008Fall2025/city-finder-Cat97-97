#include <stdio.h>
#include <stdlib.h>

// Problem: Two Sum (classic coding interview question)
// Given an array of integers nums and an integer target, return indices of the
// two numbers such that they add up to target. Assume exactly one solution.
//
// Approach: Use a simple hash table (open addressing) for O(n) average time.
// For clarity and keeping this self-contained, a minimal hash map is implemented.

typedef struct {
	int key;
	int value;
	int used;
} Entry;

typedef struct {
	Entry *entries;
	int capacity;
} IntMap;

static unsigned int hash_int(int x) {
	// Thomas Wang 32-bit mix
	unsigned int v = (unsigned int)x;
	v = (v ^ 61u) ^ (v >> 16);
	v = v + (v << 3);
	v = v ^ (v >> 4);
	v = v * 0x27d4eb2dU;
	v = v ^ (v >> 15);
	return v;
}

static IntMap *map_create(int capacity) {
	IntMap *m = (IntMap *)malloc(sizeof(IntMap));
	if (!m) return NULL;
	m->capacity = capacity;
	m->entries = (Entry *)calloc((size_t)capacity, sizeof(Entry));
	if (!m->entries) {
		free(m);
		return NULL;
	}
	return m;
}

static void map_free(IntMap *m) {
	if (!m) return;
	free(m->entries);
	free(m);
}

static void map_put(IntMap *m, int key, int value) {
	unsigned int h = hash_int(key);
	int idx = (int)(h % (unsigned int)m->capacity);
	for (int i = 0; i < m->capacity; i++) {
		int p = (idx + i) % m->capacity;
		if (!m->entries[p].used || m->entries[p].key == key) {
			m->entries[p].key = key;
			m->entries[p].value = value;
			m->entries[p].used = 1;
			return;
		}
	}
}

static int map_get(IntMap *m, int key, int *outValue) {
	unsigned int h = hash_int(key);
	int idx = (int)(h % (unsigned int)m->capacity);
	for (int i = 0; i < m->capacity; i++) {
		int p = (idx + i) % m->capacity;
		if (!m->entries[p].used) {
			return 0; // not found
		}
		if (m->entries[p].used && m->entries[p].key == key) {
			*outValue = m->entries[p].value;
			return 1;
		}
	}
	return 0;
}

// Returns 1 on success and writes indices into outA/outB; else 0.
static int two_sum(int *nums, int n, int target, int *outA, int *outB) {
	IntMap *m = map_create(n * 2 + 1);
	if (!m) return 0;
	for (int i = 0; i < n; i++) {
		int complement = target - nums[i];
		int j = -1;
		if (map_get(m, complement, &j)) {
			*outA = j;
			*outB = i;
			map_free(m);
			return 1;
		}
		map_put(m, nums[i], i);
	}
	map_free(m);
	return 0;
}

int main(void) {
	int nums[] = {2, 7, 11, 15};
	int n = (int)(sizeof(nums) / sizeof(nums[0]));
	int target = 9;
	int i = -1, j = -1;
	if (two_sum(nums, n, target, &i, &j)) {
		printf("Two Sum found at indices %d and %d (values %d + %d = %d)\n", i, j, nums[i], nums[j], target);
	} else {
		printf("No solution found\n");
	}
	// What I learned:
	// - Reinforced hash table open addressing mechanics (probing, termination).
	// - Tradeoffs: O(n) average time, O(n) extra space; careful with capacity.
	// - For interviews, clarity and correctness beat micro-optimizations.
	// Compared with others:
	// - Matches the canonical hash-map approach in the practice repository.
	// - Considered a sorting + two-pointer variant (O(n log n)) but it loses original indices.
	return 0;
}


