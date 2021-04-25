# University

This repo contains my implementations during my university years.

## The University of Edinburgh (2020-2021)

### Blockchains and Distributed Ledgers (Semester 1)

- Assignment 2: implementing a secure [Morra](https://en.wikipedia.org/wiki/Morra_%28game%29) game
    - [Report](./UoE/BDL/BDL_Assign2.pdf)
    - [Code of Solidity contract](./UoE/BDL/morra.sol)
- Assignment 3: implementing a token storing smart contract
    - [Report](./UoE/BDL/BDL_Assign3.pdf)
    - [Code of Solidity contract](./UoE/BDL/SafeMath.sol)
- Assingment 4: implementing a fair token swapping contract
    - [Report](./UoE/BDL/BDL_Assign4.pdf)
    - [Code of Solidity contract](./UoE/BDL/FairSwap.sol)

### Internet of Things Systems, Security and the Cloud

- Activity recognition system for an Andoid phone using Google Cloud and an Mbed Discovery IoT node
    - [Report](./UoE/IoTSSC/report.pdf)
    - [Code of the Google Cloud server](./UoE/IoTSSC/cloud)
    - [Code of the Android application](./UoE/IoTSSC/mobile-app)
    - [Code of the embedded device](./UoE/IoTSSC/firmware)

## Eötvös Loránd University, Budapest (2017-2020)
- Thesis: Diagnosing vulnerabilities with static analysis
    - Checkers for LLVM Clang-Tidy:
        - [Spuriously wake up function](https://github.com/llvm/llvm-project/commit/0f4c70dd3ec6d7ee831f868e3e483273daec18f0)
        - [Bad signal to kill thread](https://github.com/llvm/llvm-project/commit/8d288a0668a574863d52784084ff565c89f7366e)
        - [Signal in multithreaded program](https://reviews.llvm.org/D75229) (under review)
        - [Do not refer atomic twice](https://reviews.llvm.org/D77493) (under review)
    - Implemented test environment: [Clang Test Docker](https://github.com/abelkocsis/clang-test-docker)