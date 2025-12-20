# Architecture Guide

## Components

### Driver
Kernel mode component utilizing `PsSetCreateProcessNotifyRoutineEx` for process tracking.

### Agent
User mode service collecting telemetry and enforcing rules.
