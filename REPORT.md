# CUDA N-Body Galaxy Simulator: Technical Report and Development Plan

**Repository:** https://github.com/Mairaelefante/cuda-nbody-galaxy-simulator  
**Project owner:** Maira Elefante  
**Report date:** 2026-11-09  
**Status:** Existing personal project; further work proposed, not yet implemented.

## 1. Overview

This repository contains a direct-summation gravitational N-body simulation in C++17 and CUDA, with a CPU reference path, a GPU path using shared-memory tiling, simple CSV output, a plotting script, and a benchmark mode. Its intended audience is people exploring numerical astrophysics, GPU programming, and comparisons of CPU and GPU implementations.

The simulation uses **synthetic initial conditions and dimensionless units**. It should not be interpreted as a calibrated physical model of a real galaxy.

## 2. Existing implementation (verified by source inspection)

- `include/nbody.hpp`: particle structure and public function declarations.
- `src/common.cpp`: seeded synthetic galaxy initialization, CSV serialization, and a position-error comparison helper.
- `src/cpu.cpp`: O(N²) pairwise gravitational force computation, softening, and a velocity-then-position integration update.
- `src/gpu.cu`: O(N²) CUDA gravitational update with shared-memory tiles and a device buffer swap between timesteps.
- `src/main_cpu.cpp` and `src/main_cuda.cu`: command-line entry points; the CUDA program also offers a benchmark mode and a small-case CPU/GPU position comparison.
- `plot.py`: creates a two-dimensional scatter plot from a saved particle CSV.
- `CMakeLists.txt`: CPU build by default, optional CUDA build.

No build, execution, GPU benchmark, CI run, or security-history audit was performed in preparing this report. Therefore runtime correctness, numerical accuracy, and hardware speedups are **not yet validated**.

## 3. Technical review: risks and work to verify

### 3.1 CUDA barrier safety for incomplete blocks (high priority)

In `src/gpu.cu`, the kernel exits threads with `if (i >= n) return;` before reaching `__syncthreads()`. In a partially filled final block, not all threads participate in the barrier. This is a CUDA synchronization hazard and must be fixed before relying on arbitrary particle counts. A candidate remediation is to keep all threads in the block participating in barriers and mask inactive particle computations and writes. **This is an identified source-level issue, not a demonstrated test failure.**

### 3.2 CUDA error handling and edge cases

Check the return values of CUDA event operations, kernel execution after synchronization, and memory allocation cleanup on failure. Establish clear behavior for N = 0, invalid input arguments, non-positive timesteps, and non-finite particle states. Test sizes just below, equal to, and just above block-size boundaries.

### 3.3 Numerical validation

The implementation compares CPU and GPU positions in limited small cases, but does not provide an automated regression suite or tolerances justified across particle counts and timesteps. Implement momentum and energy diagnostics, compare to CPU reference results, and document effects of numerical precision and timestep selection.

### 3.4 Performance interpretation

The existing GPU benchmark times the kernel-loop region with CUDA events, whereas the CPU timing uses a host wall clock. Document exactly what each metric includes before reporting speedups. Benchmark repeated runs, provide meaningful summaries, and distinguish transfer-inclusive from compute-only performance.

### 3.5 Documentation and reproducibility

Document prerequisites (CMake, compatible C++ compiler, optional CUDA toolkit and NVIDIA GPU, Python/Matplotlib for plotting), command examples, expected output format, limitations, and a reproducible test matrix. Add `.gitignore` for generated builds, CSVs, plots, and local environment files.

## 4. Proposed roadmap (future work, not claims of completion)

These are **planning estimates** for substantive development work. They should be undertaken only if they match the owner's actual development intentions.

| Workstream | Planned work | Estimated effort |
| --- | --- | ---: |
| CUDA correctness | Repair barrier hazard, handle tail blocks and edge cases, add launch/error checks | 5 h |
| Test suite | Automated CPU invariants, small-N GPU comparisons, reproducible seeded tests | 5 h |
| Physics diagnostics | Compute energy and momentum trends; analyze timestep and softening effects | 5 h |
| Benchmark methodology | Repeatable CPU/GPU timing, transfer-inclusive comparison, CSV metrics | 4 h |
| Visualization | Time-series trajectory snapshots, plots of physical diagnostics, richer CLI output | 4 h |
| Developer experience | CI for CPU build/tests, documentation, examples and platform requirements | 3 h |
| **Total planned** | | **26 h** |

The roadmap is a proposal rather than a record of previously worked hours or a commitment to paid hours. Work should be tracked through real commits and/or issues as it occurs.

## 5. Suggested validation criteria

1. CPU-only build and tests run without a CUDA toolkit.
2. GPU outputs agree with the CPU reference within documented tolerances for supported small test cases, including sizes not divisible by 256.
3. No illegal synchronization or memory access is reported by available CUDA validation tools.
4. Diagnostics describe numerical drift for explicitly documented configurations.
5. Benchmarks state hardware, compiler/toolkit versions, particle counts, repetition counts, and timing boundaries.
6. README explains how to reproduce at least one CPU result and, where supported, one GPU result.

## 6. Project provenance and submission checklist

- Public repository with original commit history: present when reviewed.
- Personal ownership: stated by repository owner; third-party rights were not independently audited.
- License: MIT, see `LICENSE`.
- Documentation: README exists, but additional onboarding detail is recommended.
- At least 20 hours of planned work: a **26-hour proposed roadmap** is recorded above; owner should confirm it represents work they genuinely intend to undertake.
- Secrets and personal data: no complete repository-history or credentials scan has yet been performed; complete this before submitting to any external project.
- Existing work for clients, employers, universities, or model-training infrastructure must not be introduced into this project.

## 7. Next actions

Prioritize the CUDA barrier fix and a small automated CPU test suite, then validate GPU output where compatible hardware is available. Keep source changes and measured results in subsequent commits; do not claim tests passed until actually executed.
