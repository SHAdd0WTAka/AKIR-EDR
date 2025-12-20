# AKIR - Advanced Kernel-Level Integrity & Resilience Framework

**Version:** 1.0.0  
**Created:** December 20, 2025  
**License:** MIT

## Overview
AKIR is a structured Endpoint Detection and Response (EDR) solution designed for enterprise environments. It combines kernel-level monitoring with a robust user-mode agent and comprehensive automation scripts.

## Architecture

- **Driver (Ring 0):** `edrdrv.sys` - Handles process, image, and registry callbacks.
- **Agent (Ring 3):** `EDRAgent.exe` - Processes events, communicates with the backend, and enforces policies.
- **Scripts:** PowerShell automation for deployment, maintenance, and testing (MITRE ATT&CK simulations).

## Structure

- `/Driver`: Windows Kernel-Mode Driver (WDM/WDF)
- `/Agent`: C++ User-Mode Service
- `/Scripts`: PowerShell Automation
- `/Docs`: Documentation and Playbooks

## Getting Started

See [Docs/Deployment-Guide.md](Docs/Deployment-Guide.md) for installation instructions.
